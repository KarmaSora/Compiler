# include "Node.h"
# include "symtab.h"
# include <algorithm>
# include <unordered_set>
#include "IR.h" 
 /*
 My own lexicon of errors:  
 Node* id_node = *std::next(var_node->children.begin(), 2000); gives segmentation fault if the child/node does not exist.
 
 Use the identifier node's line number for DECLARATIONS (classes/methods/variables).
 and Use the node's own line number for OTHER CONSTRUCTS:(statements/expressions)

 for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child); RUN THIS TO SEE ALL CHILDS
 
 recipe:
    add symbol
    enter scope
    do something
    exit scope

maybe in future problem with scoping in class.method like 

class DuplicateIdentifiers {    
    public boolean func() {
        return true;
    }
}
in this case its: "DuplicateIdentifiers.func"
 */

 //python3 testScript.py -semantic -valid -lexical -syntax

class ASTVisitor {
private:
    SymbolTable &symtab;
    vector<tuple<int, string>> res; // line number, error message
    string curr_class_name; // Track current class name

    Node* curr_class_for_returns = nullptr;
    //Node* curr_method_for_returns = nullptr;
    bool flag = false; //used for when its okay for example i1 = ia1[1] + ia2[2]; or b1 = i1 < i2;
    Symbol* a1 = nullptr;

    vector<string> method_scope_name;
    unordered_set<string> declared_vars; // Track local declarations
public:
    ASTVisitor(SymbolTable &st) : symtab(st) {}

    void visit_THE_WHOLE_AST_FOR_THE_SYMTAB(Node* node){
        if (!node) return;
        
        
        if (node->type == "goal" || node->type == "classDeclarations"){
            
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);
        }
        if (node->type == "classDeclaration"){
            Node* class_name_node = node->children.front(); // identifier:DuplicateIdentifiers
            
            curr_class_name = class_name_node->value; // Set current class

            Symbol class_sym {
                class_name_node->value,
                CLASS,
                class_name_node->value,
                class_name_node->lineno ///SDASDASDASDASD
            };
            
            symtab.add_symbol(class_sym);
            symtab.enter_scope(class_sym.name);
            // identifier:DuplicateIdentifiers, reqVarDeclaration, reqMethodDeclaration methodDeclaration:
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);  
            symtab.exit_scope();
            curr_class_name.clear(); // Reset after class processing
        }
        
        if (node->type == "var declarations"){
            
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);  
            
        }

        if (node->type == "var declaration"){
            
            handle_variable(node);
        }

        if (node->type == "methodDeclarations"){
            // look for all childs until it sees something in style with "METHODDECLARATION VARDECLARATION:"
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);
            // THEN IT WILL GO TO AN IF STATEMENT (DOWN BELOW)
        }

        if (node->type == "methodDec"){
            string type_char_check_or_NOT;
            Node* method_type = node->children.front(); // INT RETURN TYPE (HERERERERE) open it up if it needs usage

            if (method_type->type == "typechar"){
                Node* method_type_ident_because_it_has_typechar = method_type->children.front();
                type_char_check_or_NOT = method_type_ident_because_it_has_typechar->value;
            }
            else { type_char_check_or_NOT = method_type->type; }

            Node* indentifier_method = *std::next(node->children.begin()); // identifier:func
            //cout << "TESTING " << indentifier_method->value << endl;
            method_scope_name.push_back(curr_class_name + "." + indentifier_method->value); // Class.method

            Symbol method_sym {
                indentifier_method->value,
                METHOD,
                type_char_check_or_NOT,
                indentifier_method->lineno
            };
            //symtab.exit_scope();
            symtab.add_symbol(method_sym);
            symtab.enter_scope(method_sym.name); // different here
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);  

            // Collect parameter types from current scope (method's scope)
            vector<string> param_types;

            for (const auto& entry : symtab.current_scope->symbols){
                if (entry.second.kind == PARAMETER){
                    //cout << entry.second.name <<" "; 
                    param_types.push_back(entry.second.name);
                }
            }

            // Update method symbol in CLASS scope with parameters
            Scope* class_scope = symtab.current_scope->parent;
            if (class_scope) {
                Symbol* method_symbol = class_scope->lookup(method_sym.name);
                if (method_symbol) {
                    method_symbol->param_types = param_types;
                }
            }

            symtab.exit_scope();

        }
        if (node->type == "methodBody"){
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child); //int param; // @error - semantic (Already Declared parameter: 'param')
        }

        if (node->type == "parameters"){
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);             
        }
        if (node->type == "parameter"){
            Node* typeNode = node->children.front();    // e.g. "INT LB RB" OR SOME CASES TYPECHAR
            Node* idNode   = node->children.back();     // e.g. "identifier:param"
            
            string type_str;
            if (typeNode->type == "typechar") {
                Node* class_node_val = typeNode->children.front();
                type_str = class_node_val->value;
            } else {
                type_str = typeNode->type;
            }

            Symbol paramSym {
                idNode->value,            // "param"
                PARAMETER,
                type_str,           // "INT LB RB" or "some_class_name"
                node->lineno
            };
            symtab.add_symbol(paramSym);

        }

        

        if (node->type == "MAIN CLASS"){
            Node* main_class_name_node = node->children.front();

            Symbol main_sym {
                main_class_name_node->value,
                CLASS,
                main_class_name_node->type,
                node->lineno
            };

            symtab.add_symbol(main_sym);
            symtab.enter_scope(main_sym.name);
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);  
            symtab.exit_scope();
        }

        
        
    }

    void visit(Node* node){ /* VISIT ALL THE NODES IN THE AST (pdf file or smthn)*/
        if (!node) return;
        flag = false; //reset
        if (node->type == "goal" || node->type == "classDeclarations"){
            for (auto child : node->children) visit(child);
        }
        if (node->type == "classDeclaration"){
            curr_class_for_returns = node;
            

            Node* class_name_node = node->children.front(); // identifier:DuplicateIdentifiers
            
            curr_class_name = class_name_node->value; // Set current class

        
            symtab.enter_scope(class_name_node->value);
            // identifier:DuplicateIdentifiers, reqVarDeclaration, reqMethodDeclaration methodDeclaration:
            for (auto child : node->children) visit(child); // visit all children of classDeclaration
            declared_vars.clear();
            symtab.exit_scope();
            curr_class_name.clear(); // Reset after class processing

        }
        if (node->type == "methodDeclarations"){ for (auto child : node->children) visit(child);}

        if (node->type == "methodDec") 
        {   
            
            Node* first_type_of_method = node->children.front();

            Node* methodDec_return_node_but_not_type = *std::next(node->children.begin(), 4); //RETURN
            Node* method_return_node_type = methodDec_return_node_but_not_type->children.front(); // INT:0

            //cout << "Lokokokokokokok " << first_type_of_method->type << endl;
            
            Node* indentifier_method = *std::next(node->children.begin()); // identifier:func
            //cout << "TESTING " << indentifier_method->value << endl;
            //method_scope_name.push_back(curr_class_name + "." + indentifier_method->value); // Class.method
            
            symtab.enter_scope(indentifier_method->value); // different here

            if (method_return_node_type->type != first_type_of_method->type){
                // if (method_return_node_type->type != "THIS" && first_type_of_method->type != "typechar"){
                //     res.push_back(std::make_tuple(first_type_of_method->lineno, "semantic (type mismatch)"));
                //     symtab.error_count++;
                // }
                
                if (method_return_node_type->type == "identifier"){
                    Symbol* found = symtab.lookup(method_return_node_type->value);
                    if (first_type_of_method->type == "typechar"){
                        Node* what_is_this_typechar = first_type_of_method->children.front(); //identifier:A 
                        if (found->type != what_is_this_typechar->value){
                            res.push_back(std::make_tuple(first_type_of_method->lineno, "semantic (type mismatch)"));
                            symtab.error_count++;
                        }
                    }
                    else {
                        
                        //cout << symtab.writeAllSymbols();

                        // THIS IS // @error - semantic (type mismatch)
                        // BUT IN InvalidReturn ITS // @error - semantic (invalid return type) LIKE WHAT
                        if (found){
                            if (found->type != first_type_of_method->type){
                                res.push_back(std::make_tuple(first_type_of_method->lineno, "semantic (type mismatch)"));
                                symtab.error_count++;
                            }
                        }
                    }
                }
            }
            if (methodDec_return_node_but_not_type->type == "RETURN"){
                Node* check_if_its_an_exp = methodDec_return_node_but_not_type->children.front();

                if (check_if_its_an_exp->type == "exp DOT ident LP exp COMMA exp RP"){
                    Node* get_var_name_for_return = *std::next(check_if_its_an_exp->children.begin());
                    Node* get_arguments = *std::next(check_if_its_an_exp->children.begin(), 2);
                    //cout <<"THIS SHOULD BE zxFu " <<  get_var_name_for_return->value << endl;
                    Symbol* get_sym_var_name_for_return = symtab.lookup(get_var_name_for_return->value);

                    //go into Element to find InInt.
                    //HOW CAN WE FIND WHAT CLASS InInt belong to?
                    // COME HERE
                    string found_class = extractClass(method_scope_name, get_var_name_for_return->value);
                    int arg_count = 0;
                    if (get_arguments->type == "argument"){ // no arguments given in the function.
                        arg_count = 0;
                    }
                    else if (get_arguments->type == "argument_list"){ //there is atleast 1 argument
                        arg_count++;
                    }
                    
                    //cout << found_class <<endl;
                    Scope* get_class_scope = symtab.get_class_scope(found_class); // FIND InInt (Element)

                    //cout << get_class_scope->name; //Element
                    if (get_class_scope){ // Element
                        Symbol* method_sym_sym = get_class_scope->lookup(get_var_name_for_return->value); //InInt
                        if (method_sym_sym){
                            // cout<<"DOWNODIWNOIAWD"<<endl;
                            //cout <<method_sym_sym->name<<endl; //InInt
                            Scope* get_method_scope = symtab.get_method_scope(get_class_scope->name, method_sym_sym->name);
                            if (get_method_scope){
                                // for (auto parameters : method_sym_sym->param_types){
                                //     //parameters is x
                                //     //cout << parameters << " ";
                                //     Symbol* find_parameter_type = get_method_scope->lookup(parameters);
                                //     if(find_parameter_type){ // found the parameter
                                        
                                //     }
                                //     // if (parameters != )
                                // }
                                if (method_sym_sym->param_types.size() != arg_count){
                                    // @error - semantic (missing parameter)
                                    res.push_back(std::make_tuple(get_var_name_for_return->lineno, "semantic (missing parameter)"));
                                    symtab.error_count++;
                                }
                            }
                            
                            
                            //cout<<method_sym_sym->name<<" ";
                            //cout << get_method_scope <<endl;
                            // for (auto parameters : method_sym_sym->param_types){
                            //     //parameters is x
                            //     Symbol* find_parameter_type = symtab.lookup(parameters);
                            //     if(find_parameter_type)cout <<find_parameter_type->type<<" ";
                            //     // if (parameters != )
                            // }
                            
                        }
                    }

                    
                    
                    if (get_sym_var_name_for_return){
                        //cout<<get_sym_var_name_for_return->type<<" oaisdoiasnd ";
                        if (get_sym_var_name_for_return->type != first_type_of_method->type){
                            res.push_back(std::make_tuple(first_type_of_method->lineno, "semantic (invalid return type)"));
                            symtab.error_count++;
                        }
                    }
                }
                else if (check_if_its_an_exp->type == "expression LEFT_BRACKET expression RIGHT_BRACKET"){
                    Node* check_if_its_an_exp2 = *std::next(check_if_its_an_exp->children.begin());

                    Node* get_var_for_THIS = *std::next(check_if_its_an_exp2->children.begin());//yzFunc

                    Symbol* find_return_THIS = symtab.lookup(get_var_for_THIS->value);

                    if (find_return_THIS){
                        if (find_return_THIS->type != first_type_of_method->type){
                            res.push_back(std::make_tuple(get_var_for_THIS->lineno, "semantic (invalid type in the return statement)"));
                            symtab.error_count++;
                        }
                    }
                }
            }
            
            


            for (auto child : node->children) visit(child);
            symtab.exit_scope();

        }
        if (node->type == "methodBody") for (auto child : node->children) visit(child);

        if (node->type == "statement"){
            // here we visit SOMETHING [ASSIGNED] = TO SOMETHING, IF LP expression RP statement ELSE statement    etc..
            for (auto child : node->children) visit(child); 
        } 

        if (node->type == "SOMETHING ASSIGNED = TO SOMETHING"){
            Node* leftNode = node->children.front();
            Node* rightNode = *std::next(node->children.begin(),1);

            if(getNodeReturnType(leftNode)!= getNodeReturnType(rightNode)){
                std::cout << "typeLeft : "<<leftNode->type <<
                " typeRight: " << rightNode->type <<std::endl;
                std::cout <<" funcretTYPE: "<< getNodeReturnType(leftNode)<< " rightFuncRetTYPE: " << getNodeReturnType(rightNode) << std::endl;
                res.push_back(std::make_tuple(node->lineno, "Type missmatch!"));
                symtab.error_count++;
            }

        }

        if (node->type == "SOMETHING [ASSIGNED] = TO SOMETHING"){
            Node* identifier_arr = node->children.front(); // identifier:num_aux
            Node* inside_arr_brackets = *std::next(node->children.begin()); // FALSE
            Node* assigned_arr_to = *std::next(node->children.begin(), 2); // INT:2

            if (inside_arr_brackets->type != "INT"){
                res.push_back(std::make_tuple(node->lineno, "semantic (invalid type of array index)"));
                symtab.error_count++;
            }

            if (assigned_arr_to->type == "expression DOT LENGTH"){
                Node* type_dot_length = assigned_arr_to->children.front(); // identifier:num
                //cout << "value or smthn: " << type_dot_length->value << endl;
                
                Symbol* test = symtab.lookup(type_dot_length->value);
                //if(test) cout << "FOUND IT: \n type" << test->type  << "\nname" << test->name<< endl;
                if (test){
                    if("INT LB RB" != test->type){
                        res.push_back(std::make_tuple(node->lineno, "semantic (member .length is used incorrectly)"));
                        symtab.error_count++;
                    }
                }
                //what type is num ? if its not INT LB RB then its NOT okay.
                //cout << symtab.writeAllSymbols();
                //cout << "dadasdasdasdasdasdasd " << symtab.lookup(type_dot_length->value);
                type_dot_length->value; //num

            }

            // trying to use int as an array.
            if (identifier_arr->type == "identifier"){
                Symbol* found = symtab.lookup(identifier_arr->value);
                if (found->type != "INT LB RB"){
                    res.push_back(std::make_tuple(node->lineno, "semantic (trying to use int as int array)"));
                    symtab.error_count++;
                }
            }
            

        }

        if (node->type == "IF LP expression RP statement ELSE statement") for (auto child : node->children) visit(child);
        if (node->type == "LESS_THAN") for (auto child : node->children) visit(child);
        if (node->type == "expression LEFT_BRACKET expression RIGHT_BRACKET"){
            for (auto child : node->children) visit(child);
            
            Node* check_if_its_a_ident_or_exp_DOT_ident = *std::next(node->children.begin());

            if (check_if_its_a_ident_or_exp_DOT_ident->type == "exp DOT ident LP exp COMMA exp RP"){
                Node* this_or_new = check_if_its_a_ident_or_exp_DOT_ident->children.front(); // THIS
                Node* identifier_for_this = *std::next(check_if_its_a_ident_or_exp_DOT_ident->children.begin()); // identifier:a2
                
                if (this_or_new->type == "THIS"){
                    //find return statement of this (THIS IS VALID IF THIS.a2 IF a2 IS AN INT)
    
                    // for example if (num_aux[this.a2()] < 1) (find return for a2)
                    Node* return_this_method = find_declared_method_type(curr_class_for_returns, identifier_for_this->value);
    
                    // look if the node before is an method then its also ok.
                    if (return_this_method->type != "INT"){
                        res.push_back(std::make_tuple(node->lineno, "semantic (invalid type of array index)"));
                        symtab.error_count++;
                    }
                }
            }

            
        } 
        
        
        if (node->type == "var declarations") for (auto child : node->children) visit(child);

        if (node->type == "var declaration"){
            Node* check_if_type_or_type = node->children.front(); // typechar or INT etc..
            Node* check_name = *std::next(node->children.begin());
            if (check_if_type_or_type->type == "typechar"){
                Node* check_class_name = check_if_type_or_type->children.front();
                //declared_vars.insert(check_class_name->value);
                Symbol* trytofindme = symtab.lookup(check_class_name->value);
                if (!trytofindme){
                    //// @error - semantic ('classthatdoesntExist' is undefined)
                    string error_msg = "semantic ('" + check_class_name->value + "' is undefined)";
                    res.push_back(std::make_tuple(node->lineno, error_msg));
                    symtab.error_count++;
                }
                
            }
            
            declared_vars.insert(check_name->value);
            
        
        }
        if (node->type == "parameters"){
            for (auto child : node->children) visit(child);
        }
        if (node->type == "parameter"){
            Node* name_of_parameter = *std::next(node->children.begin());
            declared_vars.insert(name_of_parameter->value);
        }
        // if (node->type == "SOMETHING [ASSIGNED] = TO SOMETHING") { 
        //     cout << "YOOOOOOOOOOOOOOOOOOOOOOOO";
        //     handle_array_access(node); 
        // } // num_aux[false] = 2;
        //cout << "WE ARE HERE: " << node->type << endl;
        
        if (node->type == "functionCall"){ // check SOMETHING ASSIGNED TO SOMETHING.
            for (auto child : node->children) visit(child);
            //cout<<"NDIAOWDNAWIODNAWIOD"<<endl;
            Node* func_name = *std::next(node->children.begin());//identifier:a1
            //go into a1 scope
            Symbol* get_class_name_for_func = symtab.lookup(func_name->value);
            //cout<<get_class_name_for_func->type<<endl;
            if (get_class_name_for_func){
                Scope* get_class_for_func = symtab.get_class_scope(get_class_name_for_func->type);
                if(get_class_for_func){
                    //CP
                    //cout<<"AAAA"<<endl;
                    Symbol* func_sym = get_class_for_func->lookup(func_name->value);
                    a1 = func_sym;
                    if (func_sym){
                        for(auto i : func_sym->param_types){ //loop through all arguments of a1
                            //cout << i <<" ";
                        }
                    }
                    //cout<<endl;
                }
            }
            

        }

        if (node->type == "argument_list"){
            for (auto child : node->children) visit(child);
            Node* functionCall_or_argument = node->children.front();
            if (functionCall_or_argument->type != "functionCall"){//its arguments.
                
            }
        }
        if (node->type == "exp DOT ident LP exp COMMA exp RP"){
            //for (auto child : node->children) visit(child);
            Node* get_func_var = *std::next(node->children.begin()); // a3
            //find a3 type:
            string found_class = extractClass(method_scope_name, get_func_var->value);

            Scope* get_class_scope = symtab.get_class_scope(found_class); // FIND a3 (A)
            if (get_class_scope){
                Symbol* get_class_name_for_func = get_class_scope->lookup(get_func_var->value);
                cout<<found_class<<endl;
                if (get_class_name_for_func){
                    Scope* get_method_for_func = symtab.get_method_scope(get_class_scope->name, get_func_var->value);
                    if (get_method_for_func){
                        Symbol* func_sym = get_method_for_func->lookup(get_func_var->value);
                        //cout<<"ASDASDASD " << func_sym->name <<" "<<node->lineno<<endl;
                        for (int i=0; i<func_sym->param_types.size(); i++){
                            //if ()
                        }
                    }
                }
            }
            
            
        }
    }


    void visit_for_IR(Node* node){
        if(!node) return;
        //visit Nodes for Intermediate Representation

        if (node->type == "goal" || node->type == "classDeclarations"){
            for (auto child : node->children) visit_for_IR(child);
        }

        if (node->type == "classDeclaration"){
            for (auto child : node->children) visit_for_IR(child);
            
        }
    }
private:
std::string getNodeReturnType(Node* n) {
    if (!n) return "unknown";

    // 1) Handle literals
    if (n->type == "INT" || n->type == "expression DOT LENGTH") {
        return "INT";
    }
    if (n->type == "TRUE" || n->type == "FALSE") {
        return "BOOLEAN";
    }

    // 2) Handle Identifiers
    if (n->type == "identifier") {
        Symbol* sym = symtab.lookup(n->value);
        if (sym) {
            return sym->type;
        }
        return "unknown";
    }

    // 3) Handle Function Calls (`functionCall`)
    if (n->type == "functionCall") {
        if (n->children.size() < 2) {
            return "unknown";
        }

        auto firstChildIter = n->children.begin();
        Node* functionNameNode = *std::next(firstChildIter);

        if (!functionNameNode || functionNameNode->value.empty()) {
            return "unknown";
        }

        std::string functionName = functionNameNode->value;
        Symbol* funcSym = symtab.lookup(functionName);
        if (funcSym && !funcSym->type.empty()) {
            return funcSym->type;
        }

        Scope* classScope = symtab.get_class_scope(curr_class_name);
        if (classScope) {
            Symbol* methodSym = classScope->lookup(functionName);
            if (methodSym && !methodSym->type.empty()) {
                return methodSym->type;
            }
        }

        return "unknown";
    }

    // 4) Handle `THIS` keyword
    if (n->type == "THIS") {
        return curr_class_name;
    }

    // 5) Handle Class Instantiation (`new ClassName()`)
    if (n->type == "NEW identifier LP RP") {
        if (n->children.empty()) {
            return "unknown";
        }

        Node* classNameNode = n->children.front();
        if (!classNameNode || classNameNode->value.empty()) {
            return "unknown";
        }

        std::string className = classNameNode->value;
        Scope* classScope = symtab.get_class_scope(className);
        if (!classScope) {
            return "unknown";
        }

        return className;
    }

    // 6) Handle Array Allocation (`new int[expression]`)
    if (n->type == "NEW INT LEFT_BRACKET expression RIGHT_BRACKET") {
        std::cout << "DEBUG: Resolving 'new int[expression]' to 'INT LB RB'" << std::endl;
        return "INT LB RB";  // Represents an `int[]`
    }

    // 7) Handle Method Calls (`exp DOT ident LP arguments RP`)
    if (n->type == "exp DOT ident LP arguments RP" || n->type == "exp DOT ident LP exp COMMA exp RP") {
        if (n->children.size() < 2) {
            return "unknown";
        }

        Node* objectNode = n->children.front();
        Node* methodNameNode = *std::next(n->children.begin());

        if (!methodNameNode || methodNameNode->value.empty()) {
            return "unknown";
        }

        std::string objectType = getNodeReturnType(objectNode);
        std::string methodName = methodNameNode->value;

        if (objectType == "unknown") {
            return "unknown";
        }

        Scope* classScope = symtab.get_class_scope(objectType);
        if (!classScope) {
            return "unknown";
        }

        Symbol* methodSym = classScope->lookup(methodName);
        if (!methodSym || methodSym->type.empty()) {
            return "unknown";
        }

        return methodSym->type;
    }

    // 8) Handle Arithmetic Expressions
    if (n->type == "MultExpression" || n->type == "AddExpression" || n->type == "SubExpression") {
        if (n->children.size() < 2) {
            return "unknown";
        }

        Node* leftNode  = n->children.front();
        Node* rightNode = *std::next(n->children.begin());

        std::string leftType  = getNodeReturnType(leftNode);
        std::string rightType = getNodeReturnType(rightNode);

        if (leftType == "INT" && rightType == "INT") {
            return "INT";
        }

        return "unknown";
    }

    // 9) Assignment Validation: Prevent `int = int[]`
    if (n->type == "assignment") {
        if (n->children.size() < 2) {
            return "unknown";
        }

        Node* leftNode = n->children.front();
        Node* rightNode = *std::next(n->children.begin());

        std::string leftType = getNodeReturnType(leftNode);
        std::string rightType = getNodeReturnType(rightNode);

        std::cout << "DEBUG: Assignment leftType: " << leftType 
                  << " rightType: " << rightType << std::endl;

        if (leftType == "INT" && rightType == "INT LB RB") {
            std::cout << "Error: Cannot assign 'int[]' to 'int'" << std::endl;
            return "unknown";
        }

        return leftType;
    }

    // 10) Recursive Fallback
    for (Node* child : n->children) {
        std::string childType = getNodeReturnType(child);
        if (childType != "unknown") {
            return childType;
        }
    }

    return "unknown";
}


string extractClass(const vector<string>& vec, string toFind) {
        for (const string& s : vec) {
            // Check if the string contains "InInt"
            if (s.find(toFind) != string::npos) {
                // Extract the part before the '.' (i.e., "Element")
                size_t dotPos = s.find('.');
                if (dotPos != string::npos) {
                    return s.substr(0, dotPos);
                }
            }
        }
        return ""; // Return an empty string if "InInt" is not found
    }

    void extract_arguments(Node* args_node, vector<Node*>& args) {
        if (!args_node) return;
        // args_node is exp DOT ident LP exp COMMA exp RP
        
        // if (args_node->type == "argument_list") {
        //     for (auto child : args_node->children) {
        //         if (child->type == "expression") {
        //             args.push_back(child);
        //         }
        //     }
        // }
        if (args_node->type == "exp DOT ident LP exp COMMA exp RP"){
            Node* var_name = *std::next(args_node->children.begin());//identifier:a3
            Node* if_argument_or_argument_list = *std::next(args_node->children.begin(), 2); //argument
            
            if (if_argument_or_argument_list->type == "argument"){
                args.push_back(var_name);
            }
            if (if_argument_or_argument_list->type == "argument_list"){ // send back the third node
                for (auto child : if_argument_or_argument_list->children){
                    extract_arguments(child, args);
                }
            }
            if (args_node->type == "exp DOT ident LP exp COMMA exp RP"){
                for (auto child : args_node->children){
                    extract_arguments(child, args);
                }
                
            }
        }
        
    }

    Node* find_declared_method_type(Node* n, const string& searched){
        //cout << n->type << endl;
        if (n->type == "methodDec"){
            Node* identifier = *std::next(n->children.begin());
            //cout << identifier->value << endl; // a1
            if (identifier->value == searched) { //found it 
                return n->children.front();
            }
            // if (identifier->type != "INT LB RB");
            return nullptr;
        }
       
        for (auto child : n->children){
            Node* result = find_declared_method_type(child, searched);
            if (result) return result; // Propagate found result immediately
        }
        return nullptr;
        
    }

    void handle_variable(Node* node){
        // its a normal variable just add it to the symtab
        Node* type_node = node->children.front(); // type of variable (int, string)
        Node* indentifier_var = *std::next(node->children.begin()); //identifier (a, bar)

        //string type_str = (type_node->type == "INT LB RB") ? "INT[]" : type_node->type;
        string type_str;
        if (type_node->type == "typechar") {
            Node *class_name = type_node->children.front();
            type_str = class_name->value; // Use class name "classdata"
        } else {
            type_str = type_node->type;  // Primitive types like "INT", "boolean"
        }

        Symbol var_sym {
            indentifier_var->value,
            VARIABLE,
            type_str,  // Store as "INT[]" for arrays
            node->lineno
        };
        
        symtab.add_symbol(var_sym);
    }

    //helper function:
    //handle requsiverly
    Node* rec_classDeclaration_all_childs(Node* child_of_method_dec){
        //used to find METHODDECLARATION VARDECLARATION
        // because it can be anywhere in the AST so we do it recursively until we find it. 
        //Mark please. When found.
        
        if (child_of_method_dec->type == "reqMethodDeclaration methodDeclaration"){
            for (auto i : child_of_method_dec->children){
                rec_classDeclaration_all_childs(i);
            }
            //rec_classDeclaration_all_childs(child_of_method_dec->children);
        }
        
        else if (child_of_method_dec->type == "METHODDECLARATION VARDECLARATION"){
            Node* children_of_METHOD_DECLARATION  = child_of_method_dec;

            for (auto i : children_of_METHOD_DECLARATION->children){
                if (i->type == "identifier"){
                    //add it to the sym tab
                    cout << "I ACTUALLY GOT HERE";
                }
            }
        }

    }


    // void handle_parameter_list(Node* param_list, Symbol& method_sym) {

    //     if (!param_list) return;

    //     // Base case: type identifier
    //     if (param_list->children.size() == 2) {
    //         Node* type_node = param_list->children.front();
    //         Node* id_node = *std::next(param_list->children.begin());
    //         add_parameter(id_node, type_node, method_sym);
    //     }
    //     // Recursive case: parameter_list COMMA type identifier
    //     else if (param_list->children.size() >= 3) {
    //         handle_parameter_list(param_list->children.front(), method_sym);
    //         Node* type_node = *std::next(param_list->children.begin(), 1);
    //         Node* id_node = *std::next(param_list->children.begin(), 2);
            
    //         add_parameter(id_node, type_node, method_sym);
    //     }
        
    // }
    /*
     public int Pen(int param, int param) {// @error - semantic (Already Declared parameter: 'param')
        return 1;
    }
    */

    /* InvalidArrayINTeger.java (handle arrays access) */
    void handle_array_this_access(Node* array_this_access){

        
        Node* array_node = array_this_access->children.front(); // identifier:num_aux
        Node* index_node = *std::next(array_this_access->children.begin()); // exp DOT ident LP exp COMMA exp RP:

        if (index_node->type == "exp DOT ident LP exp COMMA exp RP"){
            Node* type_index_node = *std::next(index_node->children.begin()); // identifier:a2

            string type_index = get_exp_type(type_index_node);
            // run writeAllSymbols
            cout << symtab.writeAllSymbols() << endl;
            cout << "EHHEHEHEHEHEH " << type_index << endl;
        }


    }
    
    void handle_array_access(Node* array_access){

        if (array_access->children.size() == 3){ // SOMETHING [ASSIGNED] = TO SOMETHING with expression DOT LENGTH:

            Node* array_node = array_access->children.front();
            Node* index_node = *std::next(array_access->children.begin());
            Node* third_assigned_to_or_length = *std::next(array_access->children.begin(), 2);
            //cout << "wgoreiujnowgn0ieognwoiegnogeniwogwien " << index_node->type << endl;
            string type_ = get_exp_type(index_node); // if its int, unknown, boolean [int, unknown, boolean]
            //cout << "wgoreiujnowgn0ieognwoiegnogeniwogwien " << type_ << endl;
            // num_aux[3] = num.length; // @error - semantic (member .length is used incorrectly)


            //cout << "WAKAKAKAKKAKKAKAKAKAKAKA " << third_assigned_to_or_length->type << endl;

            if (third_assigned_to_or_length->type == "expression DOT LENGTH") {
                string array_type = get_exp_type(array_node);
                //cout << "EHHERHERHERHERH " << array_type << endl;
                Node* type_of_child_length = third_assigned_to_or_length->children.front(); // identifier:num

                string type_of_child_length_type = get_exp_type(type_of_child_length); // int LB RB

                if (type_of_child_length_type != "INT LB RB"){
                    res.push_back(std::make_tuple(array_node->lineno, "semantic (member .length is used incorrectly)"));
                    symtab.error_count++;
                }


                
            }

            
            if (type_ == "int") return; // return directly because 2nd child is an INT
            if (type_ != "INT") { // the type is in INT with capital (its the type of the node)
                // std::cerr << "\n@error Line " << index_node->lineno
                //       << ": semantic (invalid type of array index)" << std::endl;
                      //<<index_type
                      //<< "', expected 'int'\n";
                res.push_back(std::make_tuple(index_node->lineno, "semantic (invalid type of array index)"));
                //cout << "wgoreiujnowgn0ieognwoiegnogeniwogwien";
                symtab.error_count++;
            }
            // handle case with identifiers
            
        }   

    }
    
    Symbol* findSymbol(Node* node){
        //cout << "HERE " << node->type << endl;
        if (node->type == "identifier"){
            //cout << "HERE " << node->value << endl;
            return symtab.lookup(node->value);
        }
        for (auto child : node->children){
            Symbol* result = findSymbol(child);
            if (result) return result;
        }
        return nullptr;
    }

    string get_exp_type(Node* exp_node) {
        if (!exp_node) return "unknown";
        /* handle literals */
        
        if (exp_node->type == "FALSE" || exp_node->type == "TRUE") return "boolean";
        if (exp_node->type == "INT" || exp_node->type == "INT") return "int";
        
        //cout << "yo " << exp_node->type << endl;

        /* handle identifiers */
        if (exp_node->type == "identifier") {
            cout << "THIS SHOULD BE (a2)      " << exp_node->value << endl;
            Symbol* sym = symtab.lookup(exp_node->value);
            if (sym) return sym->type; // if its int or not
            return "unknown"; // Identifier not found
        }   
        // Handle method calls (both direct and through 'this')
        if (exp_node->type == "exp DOT ident LP exp COMMA exp RP") {
            Node* method_name_node = *std::next(exp_node->children.begin());
            Symbol* sym = symtab.lookup(method_name_node->value);
            if (!sym) {
                // Try the mangled key if the plain lookup failed.
                sym = symtab.lookup(method_name_node->value + "$m");
            }
            if (sym) return sym->type;
        }
        // // Handle array access
        // if (exp_node->type == "expression LEFT_BRACKET expression RIGHT_BRACKET") {
        //     Node* array_node = exp_node->children.front();
        //     string base_type = get_exp_type(array_node);
        //     if (base_type.rfind("[]") != string::npos) {
        //         return base_type.substr(0, base_type.length() - 2); // Remove [] from type
        //     }
        // }
        // Handle .length
        
        if (exp_node->type == "expression DOT LENGTH") {
            // Retrieve the expression on which .length is applied.
            Node* lhs = exp_node->children.front();
            string lhs_type = get_exp_type(lhs);
            cout << "DBNWAOIDWNAODNWADINWADOIAW" << endl;
            // Check if the type is an array type (i.e. ends with "[]")
            if (lhs_type != "INT LB RB") {
                // Error: .length called on a non-array
                res.push_back(std::make_tuple(exp_node->lineno,
                    "semantic (member .length is used incorrectly)"));
                symtab.error_count++;
                return "unknown";
            }
            // If it's "INT LB RB", then arr.length is valid:
            return "int";
        }

        // UNSURE:
        /* handle array accesses recursively */
        // Recursive handling for complex expressions
        for (auto child : exp_node->children) {
            string child_type = get_exp_type(child);
            if (child_type != "unknown") return child_type;
        }
        /* TODO: more cases */
        if (exp_node->type == "expression DOT LENGTH") {
            Node* lhs = exp_node->children.front();
            string lhs_type = get_exp_type(lhs);
    
            // Handle array types stored as "INT[]" or "INT LB RB"
            if (lhs_type != "INT[]" && lhs_type != "INT LB RB") {
                res.push_back(std::make_tuple(exp_node->lineno, 
                    "semantic (member .length is used incorrectly)"));
                symtab.error_count++;
                return "unknown";
            }
            return "int";
        }

        return "unknown";
    }
    // Node* find_return_statement(Node* method_node) {
    //     for (auto child : method_node->children) {
    //         if (child->type == "RETURN") return child;
    //         Node* found = find_return_statement(child);
    //         if (found) return found;
    //     }
    //     return nullptr;
    // }

    void handle_expr_lb_expr_rb(Node* node){

        Node* array_node = node->children.front(); // identifier:num_aux
        Node* index_node = *std::next(node->children.begin()); // exp DOT ident LP exp COMMA exp RP: (ROOT)

        Node* index_node2 = *std::next(index_node->children.begin()); // identifier:a2

        //symtab.lookup(array_node->value);
        //Symbol* symlookup = symtab.lookup(index_node2->value);

        Symbol* array_sym = symtab.lookup(array_node->value);
        if (array_sym) {
            if (array_sym->type.find("[]") == string::npos) {
                // std::cerr << "\n@error Line " << array_node->lineno
                //       << ": semantic Attempting to use array access on non-array variable '" 
                //       << array_node->value << "'\n";
                res.push_back(std::make_tuple(array_node->lineno, "semantic Attempting to use array access on non-array variable '" + array_node->value + "'"));
                symtab.error_count++;
                return;
            }
        }

        string index_type = get_exp_type(index_node);
        
        if (index_node->type == "exp DOT ident LP exp COMMA exp RP") {
            Node* method_name_node = *std::next(index_node->children.begin()); // Get method name node
            Symbol* method_sym = symtab.lookup(method_name_node->value);
            
            if (method_sym) {
                // Check if method return type is not int
                if (method_sym->type != "int") {
                    // std::cerr << "\n@error Line " << method_name_node->lineno
                    //       << ": semantic Invalid array index type '" << method_sym->type
                    //       << "', expected 'int'\n";
                    res.push_back(std::make_tuple(method_name_node->lineno, "semantic Invalid array index type '" + method_sym->type + "', expected 'int'"));
                    symtab.error_count++;
                }
            }
        } 
        else if (index_type != "int") {
            // std::cerr << "\n@error Line " << index_node->lineno
            //       << ": semantic Invalid array index type '" << index_type 
            //       << "', expected 'int'\n";

            res.push_back(std::make_tuple(index_node->lineno, "semantic Invalid array index type '" + index_type + "', expected 'int'"));

            symtab.error_count++;
        }

        // if (symlookup == nullptr) {
        //     std::cerr << "semantic @error  line " << index_node2->lineno
        //           << ": Invalid array index type '" << index_node2->value 
        //           << "', expected 'int'\n";
        //     symtab.error_count++;
        // }


        //cout << symlookup->name << endl; segmentation fault if symlookup is null
    }
public:



    void printCorrect(){
        // print only string not the int, the int is the line number
        // sort based on the int in the tuple
        std::sort(res.begin(), res.end());
        for (auto i : res){
            std::cerr << "\n@error at line " << std::get<0>(i) << ": "<< std::get<1>(i) << std::endl;
        }
    }
};

/*
        if (node->type == "reqVarOrStmt statement"){
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);  
        }
        if (node->type == "SOMETHING [ASSIGNED] = TO SOMETHING"){
            Node* identifier_arr = node->children.front(); // identifier:num_aux
            Node* inside_arr_brackets = *std::next(node->children.begin()); // FALSE
            Node* assigned_arr_to = *std::next(node->children.begin(), 2); // INT:2

            Symbol array_sym {
                identifier_arr->value,
                VARIABLE,
                "array var",
                node->lineno
            };
            // SOLVE SEMANTIC MAYBE JUST IN A SEPERATE LIKE DOWN BELOW IN VISIT FOR NOW WE JUST SOLVE DUPLICATES
            symtab.add_symbol(array_sym);
        }*/