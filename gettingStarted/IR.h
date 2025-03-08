// IR.h
#ifndef IR_H
#define IR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;
// Forward declarations
class BasicBlock;
class CFG;

struct BlockContext {
    BasicBlock* current_block; // Current block for TAC insertion
    CFG* cfg; // Entire control flow graph
};

//enum class OpCode { ADD, SUB, MOV, LOAD, STORE };

enum class TACType {
    ASSIGN,    
    BIN_OP,    
    COND_JUMP, 
    JUMP,      
    LABEL,     
    CALL,      
    RETURN,    
    PRINT,     
    NEW,       
    CLASS,     // e.g., CLASS Foo
    METHOD     // e.g., METHOD bar
};


class TAC {
public:
    TACType type;
    std::string dest;   // Destination operand (if applicable)
    std::string src1;   // First source operand
    std::string src2;   // Second source operand (for binary ops)
    std::string label;  // Label for jumps (e.g., "L1")
    std::string object; // Method calls

    TAC(TACType t, const std::string& d, const std::string& s1, const std::string& s2, const std::string& l = "")
        : type(t), dest(d), src1(s1), src2(s2), label(l) {}

        void printAll() const {
            switch (type) {
                case TACType::ASSIGN:
                    printf("%s := %s\n", dest.c_str(), src1.c_str());
                    break;
                case TACType::BIN_OP:
                    printf("%s := %s %s %s\n", dest.c_str(), src1.c_str(), label.c_str(), src2.c_str());
                    break;
                case TACType::COND_JUMP:
                    printf("if %s goto %s else goto %s\n", src1.c_str(), label.c_str(), src2.c_str());
                    break;
                case TACType::JUMP:
                    printf("goto %s\n", label.c_str());
                    break;
                case TACType::CALL:
                    printf("%s := CALL %s(%s)\n", dest.c_str(), src1.c_str(), src2.c_str());
                    break;
                case TACType::RETURN:
                    printf("RETURN %s\n", src1.c_str());
                    break;
                case TACType::PRINT:
                    printf("PRINT %s\n", src1.c_str());
                    break;
                case TACType::NEW:
                    printf("%s := NEW %s\n", dest.c_str(), src1.c_str());
                    break;
                case TACType::CLASS:
                    printf("CLASS %s\n", dest.c_str());
                    break;
                case TACType::METHOD:
                    printf("METHOD %s IN %s\n", dest.c_str(), src1.c_str());
                    break;
                default:
                    printf("Unknown TAC type\n");
            }
        }
        
  
};

class BasicBlock {
public:
    string label;  // Unique identifier (e.g., "block_0")
    vector<TAC> tacInstructions;
    BasicBlock* next_true;   // Successor for true condition (if applicable)
    BasicBlock* next_false;  // Successor for false condition (if applicable)
    // For simplicity, track predecessors if needed


    // TAC condition;
    // Block *trueExit, *falseExit;

    //Block() : trueExit(NULL), falseExit(NULL) {}
    
    void printInstructions() {
        for (const auto& tac : tacInstructions) {
            tac.printAll();
        }
    }
};

class CFG {
public:
    BasicBlock* entry_block;   // Entry block of the CFG
    std::vector<BasicBlock*> blocks;  // All basic blocks


    void addBlock(BasicBlock* block){
        blocks.push_back(block);
    }
    void generateDot(const std::string& filename) {
        std::ofstream outStream(filename);
        outStream << "digraph CFG {" << std::endl;
        outStream << "graph [splines=ortho];" << std::endl; // Add ortho splines
        outStream << "node [shape=box];" << std::endl;       // Set node shape to box
    
        for (const auto& block : blocks) {
            // Build the label with TAC instructions
            std::string label = block->label + "\\n";
            for (const TAC& tac : block->tacInstructions) {
                switch (tac.type) {
                    case TACType::ASSIGN:
                        label += tac.dest + " := " + tac.src1 + "\\n";
                        break;
                    case TACType::BIN_OP:
                        label += tac.dest + " := " + tac.src1 + " " + tac.label + " " + tac.src2 + "\\n";
                        break;
                    case TACType::COND_JUMP:
                        label += "if " + tac.src1 + " goto " + tac.label + " else goto " + tac.src2 + "\\n";
                        break;
                    case TACType::JUMP:
                        label += "goto " + tac.label + "\\n";
                        break;
                    case TACType::CALL:
                        label += tac.dest + " := CALL " + tac.src1 + "(" + tac.src2 + ")\\n";
                        break;
                    case TACType::RETURN:
                        label += "RETURN " + tac.src1 + "\\n";
                        break;
                    case TACType::PRINT:
                        label += "PRINT " + tac.src1 + "\\n";
                        break;
                    case TACType::NEW:
                        label += tac.dest + " := NEW " + tac.src1 + "\\n";
                        break;
                    
                    default:
                        break;
                }
            }
    
            // Write the node with formatted label
            outStream << block->label << " [label=\"" << label << "\"];" << std::endl;
    
            // Add edges with xlabel
            if (block->next_true) {
                outStream << block->label << " -> " << block->next_true->label 
                          << " [xlabel=\"true\"];" << std::endl;
            }
            if (block->next_false) {
                outStream << block->label << " -> " << block->next_false->label 
                          << " [xlabel=\"false\"];" << std::endl;
            }
        }
    
        outStream << "}" << std::endl;
        outStream.close();
    }

    void printAllInstructions() {
        std::cout <<"size of blocks: " << blocks.size() << std::endl;
        for (const auto& block : blocks) {
            block->printInstructions();
        }
    }
};

#endif