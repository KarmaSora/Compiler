# include "Node.h"
# include "symtab.h"


 /*
 My own lexicon of errors:  
 Node* id_node = *std::next(var_node->children.begin(), 2000); gives segmentation fault if the child/node does not exist.
 
 */
class ASTVisitor {
private:
    SymbolTable &symtab;
    
public:
    ASTVisitor(SymbolTable &st) : symtab(st) {}

   
    void visitAllNodesForSymtab(Node* node){ /* VISIT ALL THE NODES IN THE AST (pdf file or smthn)*/
        if (!node) return;

        bool handled = false;
        // right:
        if (node->type == ""){  }

     
        if (!handled) for (auto child : node->children) visitAllNodesForSymtab(child);
    }

private:

    void add_parameter(Node* id_node, Node* type_node, Symbol& method_sym) {
        Symbol param_sym{
            id_node->value,
            PARAMETER,
            type_node->type,
            id_node->lineno
        };
        if (!symtab.add_symbol(param_sym)) {
            // std::cerr << "semantic @error  line " << id_node->lineno
            //           << ": Duplicate parameter '" << id_node->value
            //           << "' in method '" << method_sym.name << "'\n";
        }
        symtab.printAllSymbols(symtab);

    }

    /* InvalidArrayInteger.java (handle arrays access) */
    void handle_array_access(Node* array_access){

        if (array_access->children.size() == 3){ // SOMETHING [ASSIGNED] = TO SOMETHING with expression DOT LENGTH:
            Node* array_node = array_access->children.front();
            Node* index_node = *std::next(array_access->children.begin());
            Node* third_assigned_to_or_length = *std::next(array_access->children.begin(), 2);

            // num_aux[3] = num.length; // @error - semantic (member .length is used incorrectly)
            if (third_assigned_to_or_length->type == "expression DOT LENGTH") {
                string array_type = get_exp_type(array_node);
                if (array_type.rfind("[]") == string::npos) {
                    std::cerr << "\n@error Line " << array_node->lineno
                          << ": semantic (member .length is used incorrectly)" << std::endl;
                    symtab.error_count++;
                }
            }
        }   

        if (array_access->children.size() < 2) return;

        Node* array_node = array_access->children.front();
        Node* index_node = *std::next(array_access->children.begin());
        //Node* third_assigned_to_or_length = *std::next(array_access->children.begin(), 2);
        //cout << index_node->type << endl;
        string array_type = get_exp_type(array_node);

        // if (array_type.rfind("[]") != array_type.size() - 2) { /* similiar to ends_with("[]")*/
        //     std::cerr << "semantic @error  line " << index_node->lineno
        //           << ": Invalid array access on non-array type '" << array_type << "'\n";
        //     symtab.error_count++;
        // }

        string index_type = get_exp_type(index_node); // exp DOT ident LP exp COMMA exp RP
        //cout << index_type << endl;
        if (index_type != "int") {
            std::cerr << "\n@error Line " << index_node->lineno
                  << ": semantic (invalid type of array index)" << std::endl;
                  //<<index_type
                  //<< "', expected 'int'\n";
            symtab.error_count++;
        }
        
        // if (third_assigned_to_or_length->type == "") CONTINUE HERE
         

        /* if: int a;    and a[0] = 2*/
        Symbol* symlookup = symtab.lookup(array_node->value);
        
        /**
         *    std::cout <<"symLoopUp" << std::endl;
        std::cout<< symlookup->name << std::endl;
        std::cout<< symlookup->type << std::endl;
        std::cout<< symlookup->kind << std::endl;
        std::cout<< symlookup->dimension << std::endl;
        std::cout <<"symLoopUp END" << std::endl;
     

         * 
         */
     
      
         if (symlookup->type == "INT") {
            std::cerr << "\n@error Line " << array_node->lineno
            << ": semantic (trying to use int as int array)" /*<< array_type */<< "\n";
            //<< ": Invalid array access on non-array type '" << array_type << "'\n";
            symtab.error_count++;
        }
     

    }
    

    string get_exp_type(Node* exp_node) {
        if (!exp_node) return "unknown";
        /* handle literals */
        
        if (exp_node->type == "FALSE" || exp_node->type == "TRUE") return "boolean";
        if (exp_node->type == "Int") return "int";
        
        //cout << "yo " << exp_node->type << endl;

        /* handle identifiers */
        if (exp_node->type == "identifier") {
            Symbol* sym = symtab.lookup(exp_node->value);
            if (sym) return sym->type;
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
        // Handle array access
        if (exp_node->type == "expression LEFT_BRACKET expression RIGHT_BRACKET") {
            Node* array_node = exp_node->children.front();
            string base_type = get_exp_type(array_node);
            if (base_type.rfind("[]") != string::npos) {
                return base_type.substr(0, base_type.length() - 2); // Remove [] from type
            }
        }
        // Handle .length
        
        if (exp_node->type == "expression DOT LENGTH") {
            // Retrieve the expression on which .length is applied.
            Node* lhs = exp_node->children.front();
            string lhs_type = get_exp_type(lhs);
            cout << "DBNWAOIDWNAODNWADINWADOIAW" << endl;
            // Check if the type is an array type (i.e. ends with "[]")
            if (lhs_type.size() < 2 || lhs_type.substr(lhs_type.size()-2) != "[]") {
                 std::cerr << "\n@error Line " << exp_node->lineno
                           << ": semantic (member .length is used incorrectly)" << std::endl;
                           //<<"on non-array type '" 
                           //<< lhs_type << "', expected an array type\n";
                 symtab.error_count++;
                 return "unknown";
            }
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

        return "unknown";
    }
    Node* find_return_statement(Node* method_node) {
        for (auto child : method_node->children) {
            if (child->type == "RETURN") return child;
            Node* found = find_return_statement(child);
            if (found) return found;
        }
        return nullptr;
    }

    void handle_expr_lb_expr_rb(Node* node){

        Node* array_node = node->children.front(); // identifier:num_aux
        Node* index_node = *std::next(node->children.begin()); // exp DOT ident LP exp COMMA exp RP: (ROOT)

        Node* index_node2 = *std::next(index_node->children.begin()); // identifier:a2

        //symtab.lookup(array_node->value);
        //Symbol* symlookup = symtab.lookup(index_node2->value);

        Symbol* array_sym = symtab.lookup(array_node->value);
        if (array_sym) {
            if (array_sym->type.find("[]") == string::npos) {
                std::cerr << "\n@error Line " << array_node->lineno
                      << ": semantic Attempting to use array access on non-array variable '" 
                      << array_node->value << "'\n";
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
                    std::cerr << "\n@error Line " << index_node->lineno
                          << ": semantic Invalid array index type '" << method_sym->type 
                          << "', expected 'int'\n";
                    symtab.error_count++;
                }
            }
        } 
        else if (index_type != "int") {
            std::cerr << "\n@error Line " << index_node->lineno
                  << ": semantic Invalid array index type '" << index_type 
                  << "', expected 'int'\n";
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


};