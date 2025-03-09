#include "Node.h"
#include "IR.h"


/*

Expressions: Return a std::string (temporary variable/value).

    Examples: AddExpression, SubExpression, MethodCall, NEW, THIS, INT, TRUE, FALSE.

Statements: Return BasicBlock* (exit block for control flow).

    Examples: IfStatement, WhileLoop, Assignment, PrintStatement, ReturnStatement.

Declarations: Process children but return "" (no value).

    Examples: methodDec, classDeclaration, varDeclaration.

Generic Nodes: Process all children without specific handling.

    Examples: goal, statements, methodBody

*/

class IRvisitor{
private:
    // counters
    int temp_counter = 0;
    int block_counter = 0;
    
    string new_temp() {
        return "__t" + std::to_string(temp_counter++);
    }
    BasicBlock* create_block(CFG* cfg) {
        BasicBlock* block = new BasicBlock();
        block->label = "block_" + std::to_string(block_counter++); // Unique label
        cfg->addBlock(block); // Add to CFG
        return block;
    }
public:

    CFG* generate_IR(Node* root) {
        CFG* cfg = new CFG(); // Create a CFG on the heap
        BasicBlock* entry_block = create_block(cfg); // Pass CFG to create_block
        cfg->entry_block = entry_block;

        BlockContext ctx{entry_block, cfg};
        traverse_generic(root, ctx);

        return cfg; // Return the fully built CFG
    }

private:

    std::string visit_expr(Node* node, BlockContext& ctx) {
        if (!node) return "";

        if (node->type == "AddExpression") {
            std::string left = visit_expr(node->children.front(), ctx);
            std::string right = visit_expr(*std::next(node->children.begin()), ctx);
            std::string temp = new_temp();
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::BIN_OP, temp, left, right, "+"}
            );
            return temp;
        }
        else if (node->type == "NEW identifier LP RP") {
            Node* class_node = node->children.front(); // Get the class name
            std::string temp = new_temp();
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::NEW, temp, class_node->value, ""}
            );
            return temp;
        }
        else if (node->type == "SubExpression") {
            std::string left = visit_expr(node->children.front(), ctx);
            std::string right = visit_expr(*std::next(node->children.begin()), ctx);
            std::string temp = new_temp();
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::BIN_OP, temp, left, right, "-"}
            );
            return temp;
        }
        else if (node->type == "exp DOT ident LP arguments RP") 
        {
            // 1) Evaluate object and arguments
            Node* obj_node    = node->children.front();                // The left part: object
            Node* method_node = *std::next(node->children.begin());    // The identifier
            Node* args_node   = *std::next(node->children.begin(), 2); // The arguments
        
            std::string obj_temp = visit_expr(obj_node, ctx);
        
            std::vector<std::string> argTemps;
            for (auto child : args_node->children) {
                argTemps.push_back(visit_expr(child, ctx));
            }
            // Convert argTemps into a comma‐separated list
            std::string args_str;
            for (size_t i = 0; i < argTemps.size(); i++) {
                args_str += argTemps[i];
                if (i < argTemps.size() - 1) args_str += ", ";
            }
        
            // 2) Generate TAC for the call
            std::string result_temp = new_temp();  // e.g. "__t7"
            ctx.current_block->tacInstructions.push_back(
                TAC{
                    TACType::CALL,      // type
                    result_temp,        // dest
                    method_node->value, // src1 (method name)
                    args_str,           // src2 (arguments)
                    obj_temp            // label: sometimes used for “object”
                }
            );
        
            // 3) Optionally connect your CFG block to the method’s block
            //    (If you want a single CFG that physically links calls)
            std::string method_label = "method_" + method_node->value;
            for (BasicBlock* block : ctx.cfg->blocks) {
                if (block->label == method_label) {
                    ctx.current_block->next_true = block;
                    // Usually we break once we find it
                    break;
                }
            }
        
            // 4) Return the temp holding the call’s result
            return result_temp;
        }
                
        else if (node->type == "exp DOT ident LP exp COMMA exp RP") 
        {
            // 1) Extract components: object, method name, and arguments
            Node* obj_node    = node->children.front();                // The object being called on
            Node* method_node = *std::next(node->children.begin());    // The method name
            Node* args_node   = *std::next(node->children.begin(), 2); // The argument list
        
            // 2) Evaluate the object
            std::string obj_temp = visit_expr(obj_node, ctx);
        
            // 3) Process argument expressions
            std::vector<std::string> arg_temps;
            for (auto child : args_node->children) {
                arg_temps.push_back(visit_expr(child, ctx));
            }
        
            // 4) Convert the argument list into a string
            std::string args_str;
            for (size_t i = 0; i < arg_temps.size(); i++) {
                args_str += arg_temps[i];
                if (i < arg_temps.size() - 1) args_str += ", ";
            }
        
            // 5) Create a new basic block for the function call
            BasicBlock* call_block = create_block(ctx.cfg);
            call_block->label = "call_" + method_node->value;  // Name it uniquely
            if (!ctx.cfg->blocks.empty() && ctx.cfg->blocks.back() != call_block) {
                ctx.cfg->addBlock(call_block);
            }
                    
            // 6) Generate a temporary variable for function return
            std::string result_temp = new_temp();
        
            // 7) Insert `CALL` TAC into the new block
            call_block->tacInstructions.push_back(
                TAC{TACType::CALL, result_temp, method_node->value, args_str, obj_temp}
            );
        
            // 8) Link current block to function call block
            ctx.current_block->next_true = call_block;
        
            // 9) Update the context's current block to continue from this call
            ctx.current_block = call_block;
        
            // 10) Return the function's result temp (useful for assignments)
            return result_temp;
        }
        
        
        else if (node->type == "LESS_THAN") {
            std::string left = visit_expr(node->children.front(), ctx);
            std::string right = visit_expr(*std::next(node->children.begin()), ctx);
            std::string temp = new_temp();
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::BIN_OP, temp, left, right, "<"}
            );
            return temp;
        }
        else if (node->type == "INT") {
            std::string temp = new_temp();
            ctx.current_block->tacInstructions.push_back(TAC{TACType::ASSIGN, temp, node->value, ""});
            return temp;
        }
        return "";
    }


    BasicBlock* visit_stmt(Node* node, BlockContext& ctx) {
        if (!node) return ctx.current_block;
    
        if (node->type == "IfStatement") {
            BasicBlock* cond_block = create_block(ctx.cfg);
            BasicBlock* true_block = create_block(ctx.cfg);
            BasicBlock* false_block = create_block(ctx.cfg);
            BasicBlock* merge_block = create_block(ctx.cfg);
    
            // Link current block to cond_block
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::JUMP, "", "", "", cond_block->label}
            );
            ctx.cfg->addBlock(cond_block);
    
            // Evaluate condition
            ctx.current_block = cond_block;
            std::string cond_temp = visit_expr(node->children.front(), ctx);
            cond_block->tacInstructions.push_back(
                TAC{TACType::COND_JUMP, cond_temp, "", true_block->label, false_block->label}
            );
    
            // Process true branch
            ctx.current_block = true_block;
            BasicBlock* true_exit = visit_stmt(*std::next(node->children.begin()), ctx);
            true_exit->tacInstructions.push_back(TAC{TACType::JUMP, "", "", "", merge_block->label});
    
            // Process false branch
            ctx.current_block = false_block;
            BasicBlock* false_exit = visit_stmt(*std::next(node->children.begin(), 2), ctx);
            false_exit->tacInstructions.push_back(TAC{TACType::JUMP, "", "", "", merge_block->label});
    
            // Update current block to merge_block
            ctx.current_block = merge_block;
            return merge_block;
        }
        else if (node->type == "SOMETHING ASSIGNED = TO SOMETHING") {
            
            Node* lhs = node->children.front(); // Left-hand side (variable)
            Node* rhs = *std::next(node->children.begin()); // Right-hand side (expression)
    
            std::string rhs_temp = visit_expr(rhs, ctx);
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::ASSIGN, lhs->value, rhs_temp, ""}
            );
            return ctx.current_block;
        }
        else if (node->type == "RETURN") {
            Node* ret_val = node->children.front();
            std::string ret_temp = visit_expr(ret_val, ctx);
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::RETURN, "", ret_temp, ""}
            );
            return ctx.current_block;
        }
        else if (node->type == "SIMPLE PRINT LOL") {
            Node* value_node = node->children.front();
            std::string print_temp = visit_expr(value_node, ctx);
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::PRINT, "", print_temp, ""}
            );
            return ctx.current_block;
        }
        else if (node->type == "var declaration") {
            if (node->children.size() > 1) { // Initialized variable
                Node* lhs = node->children.front(); // Variable name
                Node* rhs = *std::next(node->children.begin()); // Initial value
                std::string rhs_temp = visit_expr(rhs, ctx);
                ctx.current_block->tacInstructions.push_back(
                    TAC{TACType::ASSIGN, lhs->value, rhs_temp, ""}
                );
            }
            return ctx.current_block;
        }
        
        
        
        // ... handle other statements (WhileLoop, Assignment, etc.)
        else if (node->type == "WHILE LP expression RP statement") {
            BasicBlock* cond_block = create_block(ctx.cfg);
            BasicBlock* body_block = create_block(ctx.cfg);
            BasicBlock* exit_block = create_block(ctx.cfg);
        
            // Link current block to condition block
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::JUMP, "", "", "", cond_block->label}
            );
        
            // Evaluate condition
            ctx.current_block = cond_block;
            std::string cond_temp = visit_expr(node->children.front(), ctx);
            cond_block->tacInstructions.push_back(
                TAC{TACType::COND_JUMP, cond_temp, "", body_block->label, exit_block->label}
            );
        
            // Process loop body
            ctx.current_block = body_block;
            BasicBlock* body_exit = visit_stmt(*std::next(node->children.begin()), ctx);
            body_exit->tacInstructions.push_back(TAC{TACType::JUMP, "", "", "", cond_block->label});
        
            // Set exit block as next block
            ctx.current_block = exit_block;
            return exit_block;
        }
        
        else if (node->type == "IF LP expression RP statement") {  // No ELSE
            BasicBlock* cond_block = create_block(ctx.cfg);
            BasicBlock* true_block = create_block(ctx.cfg);
            BasicBlock* merge_block = create_block(ctx.cfg);
        
            // Link current block to condition block
            ctx.current_block->tacInstructions.push_back(
                TAC{TACType::JUMP, "", "", "", cond_block->label}
            );
        
            // Evaluate condition
            ctx.current_block = cond_block;
            std::string cond_temp = visit_expr(node->children.front(), ctx);
            cond_block->tacInstructions.push_back(
                TAC{TACType::COND_JUMP, cond_temp, "", true_block->label, merge_block->label}
            );
        
            // Process true branch
            ctx.current_block = true_block;
            BasicBlock* true_exit = visit_stmt(*std::next(node->children.begin()), ctx);
            true_exit->tacInstructions.push_back(TAC{TACType::JUMP, "", "", "", merge_block->label});
        
            // Set merge block as the next block
            ctx.current_block = merge_block;
            return merge_block;
        }
        

        return ctx.current_block; // Default return
    }
    
    void traverse_generic(Node* node, BlockContext& ctx) {
        if (!node) return;
        
        //std::cerr << "Visiting node: " << node->type << std::endl;

        
/*
        else if (node->type == "methodDec") {
            std::string method_name = node->value;
            std::cerr << "Processing method declaration: " << method_name << std::endl;
        
            // Create method entry block inside the existing CFG
            BasicBlock* method_entry = create_block(ctx.cfg);
            method_entry->label = "method_" + method_name;
            ctx.cfg->addBlock(method_entry);
        
            BlockContext method_ctx{method_entry, ctx.cfg};
        
            // Add METHOD TAC instruction (metadata)
            //method_entry->tacInstructions.push_back(TAC{TACType::METHOD, method_name, "", ""});
        
            // Process method body
            for (auto child : node->children) {
                traverse_generic(child, method_ctx);
            }
        
            // Ensure return statement exists at the end of the method
            Node* retNode = node->children.back(); // Check last child for return
            if (retNode && retNode->type == "RETURN" && !retNode->children.empty()) {
                method_entry->tacInstructions.push_back(TAC{TACType::RETURN, "", retNode->children.front()->value, ""});
            } else {
                method_entry->tacInstructions.push_back(TAC{TACType::RETURN, "", "0", ""}); // Default return value
            }
        }
*/                                                
        else if (node->type == "statements") {
            for (auto child : node->children) {
                traverse_generic(child, ctx);
            }
        }
        else if (node->type == "MAIN METHOD") {
            for (auto child : node->children) {
                if (child->type == "SIMPLE PRINT LOL") {
                    // Handle top-level statements in the main method
                    ctx.current_block = visit_stmt(child, ctx);
                } else {
                    traverse_generic(child, ctx);
                }
            }
        }
        else if( node->type == "classDeclarations"){
            for (auto child : node->children)
            traverse_generic(child, ctx);
        }
        else if (node->type == "classDeclaration") {
            std::string class_name = node->children.front()->value; // Class name
        
            // Add CLASS TAC only as metadata (not part of CFG)
            ctx.current_block->tacInstructions.push_back(TAC{TACType::CLASS, class_name, "", ""});
        
            // Traverse class members without creating a new CFG
            for (auto child : node->children) {
                traverse_generic(child, ctx);
            }
        }
        else if (node->type == "exp DOT ident LP exp COMMA exp RP") {
            visit_expr(node, ctx);
        }
        else {
            std::cerr << "Generic traversal for node type: " << node->type << std::endl;
            for (auto child : node->children) {
                traverse_generic(child, ctx);
            }
        }
    }

};


