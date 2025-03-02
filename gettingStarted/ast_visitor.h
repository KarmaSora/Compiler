# include "Node.h"
# include "symtab.h"
# include <algorithm>
# include <unordered_set>

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
    vector<string> method_scope_name;
    unordered_set<string> declared_vars; // Track local declarations
public:
    ASTVisitor(SymbolTable &st) : symtab(st) {}

    void visit_THE_WHOLE_AST_FOR_THE_SYMTAB(Node* node){
        if (!node) return;

        //bool handled = false;
        // if (node->type == "var declaration"){ //REMOVE THIS LATER JUST PUT HANDLE_VARIABLE IN BOTH MAIN CLASS AND CLASS DEC
        //     handle_variable(node);
        // }
        //cout << "AAAA " << node->type << " name: " << node->value<< endl;
        if (node->type == "goal" || node->type == "classDeclarations"){
            
            for (auto child : node->children) visit_THE_WHOLE_AST_FOR_THE_SYMTAB(child);
        }
        if (node->type == "classDeclaration"){
            Node* class_name_node = node->children.front(); // identifier:DuplicateIdentifiers
            
            curr_class_name = class_name_node->value; // Set current class

            Symbol class_sym {
                class_name_node->value,
                CLASS,
                "regular class",
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
            Node* left_assign = node->children.front();
            Node* either_an_ident_or_exp_DOT_ident = *std::next(node->children.begin()); // it can even be an operator like ADD OR EVEN AN NEW LIKE WHAAAT
            // @error - semantic ('e' does not exist in the current scope)
            Symbol* found_the_non_existent = symtab.lookup(left_assign->value); // IMPORTANT

            bool flag = false; //used for when its okay for example i1 = ia1[1] + ia2[2]; or b1 = i1 < i2;



            if (either_an_ident_or_exp_DOT_ident->type == "NEW INT LEFT_BRACKET expression RIGHT_BRACKET"){
                Node* ident = either_an_ident_or_exp_DOT_ident->children.front();
                
                if (ident->type == "TRUE" || ident->type == "FALSE"){ //FALSE doesnt exist in the tests but who knows?
                    // @error - semantic ('true': is of wrong type)
                    string error_msg = "semantic ('" + ident->type + "': is of wrong type)";
                    res.push_back(std::make_tuple(node->lineno, error_msg));
                    symtab.error_count++;
                }

                if (found_the_non_existent->type != ident->type &&
                    found_the_non_existent->type != "INT LB RB"){
                    // @error - semantic ('x' and expression new int[1] new are of different types)
                    string error_msg = "semantic ('" + found_the_non_existent->name + "' and expression new int[1] new are of different types)";
                    res.push_back(std::make_tuple(node->lineno, error_msg));
                    symtab.error_count++;
                }
                
            }

            if (either_an_ident_or_exp_DOT_ident->type == "expression DOT LENGTH"){
                Node* get_exp = either_an_ident_or_exp_DOT_ident->children.front();

                Symbol* get_sym_exp = symtab.lookup(get_exp->value); // identifier:e

                if (get_sym_exp){
                    //cout << "name: "<<get_sym_exp->name<<" "<< get_sym_exp->type << endl;
                    if (get_sym_exp->type == "INT LB RB" && found_the_non_existent->type == "INT"){
                        flag = true; //its okay because a = e.length; is valid since a is an INT and e is an INT LB RB
                    }

                    if (get_sym_exp->type != found_the_non_existent->type && !flag){
                        // @error - semantic ('x' and expression 'e.length' are of different types)
                        string error_msg = "semantic ('" + found_the_non_existent->name + "' and expression '" +\
                        get_sym_exp->name + ".length' are of different types)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }
                }

                if (get_exp->type == "expression LEFT_BRACKET expression RIGHT_BRACKET"){
                    Node* get_var_name_arr = get_exp->children.front();
                    // @error - semantic ('e' is undefined or wrong)
                    string error_msg = "semantic ('" + get_var_name_arr->value + "' is undefined or wrong)";
                    res.push_back(std::make_tuple(node->lineno, error_msg));
                    symtab.error_count++;
                }
            }

            else if (either_an_ident_or_exp_DOT_ident->type == "NEW identifier LP RP"){
                Node* find_var_in_NEW = either_an_ident_or_exp_DOT_ident->children.front();
                Symbol* find_the_NEW_var = symtab.lookup(find_var_in_NEW->value);

                if (!find_the_NEW_var){
                    string error_msg = "semantic ('" + find_var_in_NEW->value + "' is not a valid Class)";
                    res.push_back(std::make_tuple(node->lineno, error_msg));
                    symtab.error_count++;
                }
                else if (find_the_NEW_var){
                    //c = new Element();// @error - semantic ('c' and expression 'Element' new are of different types)
                    if (found_the_non_existent->type != find_the_NEW_var->name){ //BECAUSE THIS IS A CLASS WE USE NAME NOT TYPE (CLASS NAME IS THE TYPE)
                        string error_msg = "semantic ('" + found_the_non_existent->name + "'and expression '" +\
                        find_the_NEW_var->name + "' new are of different types)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }
                }
            }

            else if (either_an_ident_or_exp_DOT_ident->type == "EXCLAMATION_MARK expression"){
                Node* var_in_exclamation_mark = either_an_ident_or_exp_DOT_ident->children.front(); 

                // find it
                Symbol* var_sym_in_exclamation_mark = symtab.lookup(var_in_exclamation_mark->value);

                if (var_sym_in_exclamation_mark){
                    if (var_sym_in_exclamation_mark->type != "BOOLEAN"){
                        res.push_back(std::make_tuple(node->lineno, "semantic"));
                        symtab.error_count++;
                    }
                }
            }

            if (either_an_ident_or_exp_DOT_ident->type == "AddExpression"){
                
                //then get the two types yalla
                Node* left_after_equal = either_an_ident_or_exp_DOT_ident->children.front(); //identifier:i1
                Node* right_after_equal = *std::next(either_an_ident_or_exp_DOT_ident->children.begin()); //identifier:b1
                //does it even exist?
                Symbol* left_sym_after_equal = symtab.lookup(left_after_equal->value);
                Symbol* right_sym_after_equal =  symtab.lookup(right_after_equal->value);


                if (found_the_non_existent->type == "BOOLEAN"){//b1 = b1 + b1;// @error - semantic
                    if (left_sym_after_equal->type == "BOOLEAN" && right_sym_after_equal->type == "BOOLEAN"){
                        res.push_back(std::make_tuple(node->lineno, "semantic"));
                        symtab.error_count++;
                    }
                }
               

                if (left_sym_after_equal && right_sym_after_equal) { //it does indeed exist.
                    if (found_the_non_existent->type != left_sym_after_equal->type){ 
                        //i1 = b1 + b1;// @error - semantic ('b1' is of wrong type)
                        string error_msg = "semantic ('" + left_sym_after_equal->name +\
                        "' is of wrong type)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }
                    else if (found_the_non_existent->type != right_sym_after_equal->type){
                        // now the same as before but for right side.
                        string error_msg = "semantic ('" + right_sym_after_equal->name +\
                        "' is of wrong type)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }    
                    else if (found_the_non_existent->type == "INT LB RB"){//ia1 = ia1 + ia2;// @error - semantic
                        res.push_back(std::make_tuple(node->lineno, "semantic"));
                        symtab.error_count++;
                    }       
                }
                if (left_after_equal->type == "expression LEFT_BRACKET expression RIGHT_BRACKET" &&
                    right_after_equal->type == "expression LEFT_BRACKET expression RIGHT_BRACKET"){
                    
                    Node* vararr_of_left = left_after_equal->children.front();
                    Node* vararr_of_right = right_after_equal->children.front();
                    
                    Symbol* left_sym = symtab.lookup(vararr_of_left->value);
                    Symbol* right_sym = symtab.lookup(vararr_of_right->value);

                    if (left_sym && right_sym){
                        if (left_sym->type == right_sym->type){ //THEY BOTH ARE SAME TYPE arrays.
                            if (left_sym->type == "INT LB RB" && right_sym->type == "INT LB RB"){
                                if (found_the_non_existent->type == "INT"){
                                    flag = true; // ITS OKAY THEY BOTH ARRAYS ARE INT AND THE LEFT ASSIGN VAR IS ALSO AN INT.
                                }
                            }
                        }
                    }
                }
                if (right_after_equal->type == "expression LEFT_BRACKET expression RIGHT_BRACKET"){
                    //i1 = ia1 + ia1[0];// @error - semantic ('ia1' is of wrong type)

                    //now get the two childs:
                    Node* var_name_for_arr = right_after_equal->children.front(); //identifier:ia1
                    Node* get_inside_brackets = *std::next(right_after_equal->children.begin()); // INT:0
                    //cout << var_name_for_arr->value << endl;
                    //cout << get_inside_brackets->type << endl;
                    Symbol* find_the_variable_as_arr = symtab.lookup(var_name_for_arr->value);
                    if (find_the_variable_as_arr){
                        // its okay if they both are INT [] and the left  assign (found_the_non_existent) is an int.
                        
                        if (found_the_non_existent->type != find_the_variable_as_arr->type && !flag){
                            
                            string error_msg = "semantic ('" + find_the_variable_as_arr->name +\
                            "' is of wrong type)";
                            res.push_back(std::make_tuple(node->lineno, error_msg));
                            symtab.error_count++;
                        }
                    }
                }
                
            }

            else if (either_an_ident_or_exp_DOT_ident->type == "AND"){
                //get the two childs:
                Node* left_in_AND = either_an_ident_or_exp_DOT_ident->children.front();
                Node* right_in_AND = *std::next(either_an_ident_or_exp_DOT_ident->children.begin());

                Symbol* left_sym_in_AND = symtab.lookup(left_in_AND->value);
                Symbol* right_sym_in_AND = symtab.lookup(right_in_AND->value);

                if (left_sym_in_AND->type != right_sym_in_AND->type && !flag){
                    res.push_back(std::make_tuple(node->lineno, "semantic"));
                    symtab.error_count++;
                }

                if (left_sym_in_AND && right_sym_in_AND){
                    
                    if (found_the_non_existent->type != left_sym_in_AND->type && found_the_non_existent->type != right_sym_in_AND->type){
                        //@error - semantic ('c1' is of wrong type, 'i1' and expression 'c1 && c1' are of different types)
                        string error_msg = "semantic ('" + left_sym_in_AND->name +\
                        "' is of wrong type, '" + found_the_non_existent->name + "' and expression '" +\
                        left_sym_in_AND->name + " && " + right_sym_in_AND->name + "' are of different types)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }
                    else if (found_the_non_existent->type == "INT LB RB"){//ia1 = ia1 + ia2;// @error - semantic
                        res.push_back(std::make_tuple(node->lineno, "semantic"));
                        symtab.error_count++;
                    }  
                }
            }

            else if (either_an_ident_or_exp_DOT_ident->type == "OR" ||
                either_an_ident_or_exp_DOT_ident->type == "LESS_THAN" ||
                either_an_ident_or_exp_DOT_ident->type == "EQUAL"){
                
                Node* left_of_op = either_an_ident_or_exp_DOT_ident->children.front();
                Node* right_of_op = *std::next(either_an_ident_or_exp_DOT_ident->children.begin());

                Symbol* left_sym_of_op = symtab.lookup(left_of_op->value);
                Symbol* right_sym_of_op = symtab.lookup(right_of_op->value);
                
                //sometimes its okay.
                

                if (left_sym_of_op && right_sym_of_op){

                    if (left_sym_of_op->type == right_sym_of_op->type){
                        if (left_sym_of_op->type == "BOOLEAN" &&
                            right_sym_of_op->type == "BOOLEAN" &&
                            found_the_non_existent->type == "BOOLEAN"){
                            res.push_back(std::make_tuple(node->lineno, "semantic"));
                            symtab.error_count++;
                        }
                        if (found_the_non_existent->type == "BOOLEAN" &&
                            right_sym_of_op->type != "BOOLEAN" &&
                            left_sym_of_op->type != "BOOLEAN"){
                            flag = true; //THIS IS OKAY b1 = i1 < i2;
                        }
                    }
                    
                    if (left_sym_of_op->type != right_sym_of_op->type && !flag){
                        res.push_back(std::make_tuple(node->lineno, "semantic"));
                        symtab.error_count++;
                    }

                    if (found_the_non_existent->type != left_sym_of_op->type &&
                        found_the_non_existent->type != right_sym_of_op->type && !flag){
                            res.push_back(std::make_tuple(node->lineno, "semantic"));
                            symtab.error_count++;
                        }
                }

            }
            //cout<< "SOMETHING " << found_the_non_existent<< endl;
            // kolla i klassen scope
            if (found_the_non_existent){ // variable exists later or sooner.
                //cout << "is this a d ?? " << found_the_non_existent->name << endl;
                
                    //Scope* check_if_var_in_scope = symtab.get_class_scope(found_the_non_existent->name);
                    // cout << "LASDASDASDASD" << endl;
                    // for (auto i : declared_vars){
                        
                    //     cout << i << " ";
                    // }
                    if (!declared_vars.count(left_assign->value)){
                        
                        string error_message = "semantic ('" + left_assign->value + "' is not defined yet)";
                        res.push_back(std::make_tuple(node->lineno, error_message));
                        symtab.error_count++;
                    }
                
                
            }
            
            
            if (either_an_ident_or_exp_DOT_ident->type == "identifier" && found_the_non_existent){


                Symbol* right_assign = symtab.lookup(either_an_ident_or_exp_DOT_ident->value);

                



                // @error - semantic ('a' and expression 'b' are of different types)
                if (found_the_non_existent->type != right_assign->type){
                    string error_message = "semantic ('" + found_the_non_existent->name + "' and expression '" \
                    + right_assign->name + " are of different types)";
                    res.push_back(std::make_tuple(node->lineno, error_message));
                    symtab.error_count++;
                }
                // else if (!declared_vars.count(either_an_ident_or_exp_DOT_ident->value)){
                //     string error_message = "semantic ('" + left_assign->value + "' is not defined yet)";
                //     res.push_back(std::make_tuple(node->lineno, error_message));
                //     symtab.error_count++;
                // }
            }

            if (!found_the_non_existent ){ // @error - semantic ('e' does not exist in the current scope) 
                // Scope* class_scoping = symtab.get_class_scope(found_the_non_existent->type); //Get class scope (e.g., "classdata")
                // if (class_scoping){
                //     string error_message = "semantic ('" + left_assign->value + "' does not exist in the current scope)";
                //     res.push_back(std::make_tuple(node->lineno, error_message));
                //     symtab.error_count++;
                // }
                string error_message = "semantic ('" + left_assign->value + "' does not exist in the current scope)";
                res.push_back(std::make_tuple(node->lineno, error_message));
                symtab.error_count++;
                //cout << "AAAAAAAAAAAAA"<<endl;
            }

            // om d är en identifier (classdata) så går vi in i d. Sen kollar vi om d har funktionen yfunc.
            // kolla return type of yfunc jämför (if) om a = d.func om a är valid type boolean
            
            //PROBABLY CHANGE LATER:
            if (either_an_ident_or_exp_DOT_ident->type == "exp DOT ident LP exp COMMA exp RP"){
                Node* method_name_node = *std::next(either_an_ident_or_exp_DOT_ident->children.begin()); //yFunc
                Node* obj_node = either_an_ident_or_exp_DOT_ident->children.front(); //
                Node* argument_list_or_argument = *std::next(either_an_ident_or_exp_DOT_ident->children.begin(), 2);
                // try to see if even the function (.zzFunc) even exists.
                Symbol* does_this_exist = symtab.lookup(method_name_node->value);
                
                if (argument_list_or_argument->type == "argument_list"){
                    // this one below can be 3 things (1. exp_dot_ident 2. argument 3. INT)
                    Node* check_if_argument_or_DOT_ident = argument_list_or_argument->children.front();
                    if (check_if_argument_or_DOT_ident->type == "identifier"){
                        Node* check_if_argument_exist = check_if_argument_or_DOT_ident->children.front();
                        if (check_if_argument_exist){ // loop through all arguments.
                            for (auto child : node->children) visit(child);
                        }
                    }
                }
                else if (argument_list_or_argument->type == "argument"){
                    Node* check_if_its_an_THIS = either_an_ident_or_exp_DOT_ident->children.front();
                    Node* get_the_name = *std::next(either_an_ident_or_exp_DOT_ident->children.begin());
                    cout<<"YWDAWDAWD "<<check_if_its_an_THIS->type<<endl;
                    if (check_if_its_an_THIS->type == "THIS"){
                        Symbol* check_its_type = symtab.lookup(get_the_name->value);
                        cout << "FOUND YUEA " << check_its_type<<endl;
                    }
                }

                // KIND OF CORRECT BUT MAY NEEDS CHANGINGS.
                if (obj_node->type == "exp DOT ident LP exp COMMA exp RP"){
                    
                    Node* check_this = obj_node->children.front(); // THIS
                    Node* ident_name_to_find = *std::next(obj_node->children.begin()); // identifier:extract 
                    // Node* argument_list_or_argument = *std::next(obj_node->children.begin(), 2);
                    // cout << argument_list_or_argument->type<<endl;
                    // if (check_this->type == "exp DOT ident LP exp COMMA exp RP" ){

                    // }

                    if (check_this->type == "THIS"){
                        Symbol* method_sym = symtab.lookup(ident_name_to_find->value);
    
                        if (method_sym && method_sym->kind == METHOD) {
                            // 1. Get class scope (parent of current method scope)
                            Scope* class_scope = symtab.current_scope->parent;
                            
                            // 2. Find method's own scope
                            Scope* method_scope = nullptr;
                            for (Scope* child : class_scope->children) {
                                if (child->name == method_sym->name) {
                                    method_scope = child;
                                    break;
                                }
                            }
                            
                            // 3. Extract parameter types
                            vector<string> param_types;
                            if (method_scope) {
                                for (const auto& entry : method_scope->symbols) {
                                    if (entry.second.kind == PARAMETER) {
                                        param_types.push_back(entry.second.type);
                                    }
                                }
                            }
                            
                            // Now param_types contains ["int"] for a1()
                            // Use these to validate arguments
                        }
                    }
                }

                // just incorrect:
                if (does_this_exist){
                    Node* check_if_this = either_an_ident_or_exp_DOT_ident->children.front(); // THIS
                    Node* check_left_name_for_lookup = *std::next(either_an_ident_or_exp_DOT_ident->children.begin());

                    if (check_left_name_for_lookup && check_if_this){ // just to be sure to not get segmentation fault
                        if (check_if_this->type == "THIS"){       
                            //cout << "GOTOOTTO " <<check_left_name_for_lookup->value<<endl;
                            Symbol* find_me = symtab.lookup(check_left_name_for_lookup->value);
                            //cout << "LOSADOAKDOASKDOKSD " << find_me->name << endl;
                            //if (check_left_name_for_lookup->type == ) 
                        }
                    }
                    
                    //Scope* method_sym = symtab.get_class_scope(does_this_exist->type);
                    // Extract arguments from the method call node
                    vector<Node*> args;
                    //cout << symtab.writeAllSymbols()<<endl;
                    extract_arguments(obj_node, args);
                    //for (auto i : args) cout << i->value << " ";
                    //cout << "size: " << does_this_exist->type << endl; // BOOLEAN == ?
                    //if (does_this_exist->type == );
                    //if (args.size() != does_this_exist->param_types.size()) cout <<"DOHNAODSADOIANSD"; 
                    // if (args.size() != does_this_exist->param_types.size()) {
                    //     string error_msg = "semantic (method '" + method_name_node->value + 
                    //                       "' expects " + to_string(does_this_exist->param_types.size()) + 
                    //                       " parameters)";
                    //     res.push_back(make_tuple(node->lineno, error_msg));
                    //     symtab.error_count++;
                    // } else {
                    //     // Check each argument type
                    //     for (int i = 0; i < args.size(); i++) {
                    //         string arg_type = get_exp_type(args[i]);
                    //         if (arg_type != does_this_exist->param_types[i]) {
                    //             string error_msg = "semantic (parameter " + to_string(i+1) + 
                    //                               " of '" + method_name_node->value + 
                    //                               "' expects " + does_this_exist->param_types[i] + 
                    //                               ", got " + arg_type + ")";
                    //             res.push_back(make_tuple(node->lineno, error_msg));
                    //             symtab.error_count++;
                    //         }
                    //     }
                    // }
                    //Node* args_node = *std::next(either_an_ident_or_exp_DOT_ident->children.begin(), 2);  //change
                    //cout << "args_node " << args_node->type << endl;
                }
                
                // if (!does_this_exist){ //it doesnt exist.
                //     Scope* class_scope = symtab.get_class_scope(does_this_exist->type); //Get class scope (e.g., "classdata")
                //     if (!class_scope){
                //         string error_msg = "semantic ('" + method_name_node->value + "' does not exist)";
                //         res.push_back(std::make_tuple(node->lineno, error_msg));
                //         //semantic ('zzFunc' does not exist)
                //         symtab.error_count++;
                //     }
                    
                // }


                // THIS IS GOOD: (other errors.)
                if (obj_node->type == "THIS"){
                    Symbol* obj_sym = symtab.lookup(method_name_node->value);
                    //cout << "found it name " << obj_sym->name <<" type "<<obj_sym->type<< endl;
                    if (obj_sym){
                        if (obj_sym->type != found_the_non_existent->type){
                            res.push_back(std::make_tuple(node->lineno, "semantic (type mismatch)"));
                            symtab.error_count++;
                        }
                    }
                    else {
                        //// @error - semantic ('zFunc' does not exist)
                        string error_msg = "semantic ('" + method_name_node->value + "' does not exist)";
                        res.push_back(std::make_tuple(node->lineno, error_msg));
                        symtab.error_count++;
                    }
                }
                else if (obj_node->type == "identifier") {
                    Symbol* obj_sym = symtab.lookup(obj_node->value); // check type of the first node (type of "d")
                    //cout << symtab.writeAllSymbols() << endl;
                    if (obj_sym) {
                        string class_name = obj_sym->type;
                        Scope* class_scope = symtab.get_class_scope(class_name); //Get class scope (e.g., "classdata")
                        
                        //cout << "just look here: " << method_name_node->value <<" and here "<<class_scope->name<< endl;
                        if (class_scope) {
                            //cout << "class scope name " << class_scope->name<<endl; 
                            // Look up the method in the class's scope
                            Symbol* method_sym = class_scope->lookup(method_name_node->value);
                            //cout << "NEWEWEWEWE " << method_sym->name <<" AADNADNADNADNADNANDNA " << method_sym->type<< endl;
                            if (method_sym) {
                                // Check return type compatibility, etc.
                                if (found_the_non_existent->type != method_sym->type){
                                    string error_msg = "semantic ('" + found_the_non_existent->name + "' and expression '" +\
                                    obj_node->value + "." + method_name_node->value + "()' are of different types)";
                                    
                                    // ('a' and expression 'd.yFunc()' are of different types)
                                    res.push_back(std::make_tuple(node->lineno, error_msg));
                                    symtab.error_count++;
                                }  
                            }
                            else {
                                string error_msg = "semantic ('" + method_name_node->value + "' does not exist)";
                                res.push_back(std::make_tuple(node->lineno, error_msg));
                                //semantic ('zzFunc' does not exist)
                                symtab.error_count++;
                            } 
                        }
                    }
                } 
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
        
        if (node->type == "argument"){ // check SOMETHING ASSIGNED TO SOMETHING.

        }
        
    }

private:
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
