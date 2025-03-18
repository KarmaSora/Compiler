#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "Interpreter.h"

Program loadProgramFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open bytecode file: " + filename);
    }

    std::unordered_map<std::string, Method> methods;
    std::vector<Instruction> instructions;
    std::vector<std::string> variables;
    std::unordered_map<std::string, int> varIndexMap;
    std::string line;
    std::string currentMethod = "main";

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string op, arg;
        
        iss >> op;
        if (op == "method") {
            if (!instructions.empty()) {
                if (instructions.back().id != STOP) {
                    instructions.emplace_back(STOP, 0);
                }
                methods[currentMethod] = Method(instructions, variables);
                instructions.clear();
                variables.clear();
                varIndexMap.clear();
            }
            iss >> currentMethod;
        } else if (op == "var") {
            iss >> arg;
            if (varIndexMap.find(arg) == varIndexMap.end()) {
                varIndexMap[arg] = variables.size();
                variables.push_back(arg);
            }
        } else {
            // Check if the instruction is one without an argument
            bool noArgInstr = false;
            int instrId = -1;
            if (op == "iadd") {
                instrId = IADD;
                noArgInstr = true;
            } else if (op == "isub") {
                instrId = ISUB;
                noArgInstr = true;
            } else if (op == "imul") {
                instrId = IMUL;
                noArgInstr = true;
            } else if (op == "idiv") {
                instrId = IDIV;
                noArgInstr = true;
            } else if (op == "ilt") {
                instrId = ILT;
                noArgInstr = true;
            } else if (op == "iand") {
                instrId = IAND;
                noArgInstr = true;
            } else if (op == "ior") {
                instrId = IOR;
                noArgInstr = true;
            } else if (op == "inot") {
                instrId = INOT;
                noArgInstr = true;
            } else if (op == "print") {
                instrId = PRINT;
                noArgInstr = true;
            } else if (op == "ireturn") {
                instrId = IRETURN;
                noArgInstr = true;
            } else if (op == "stop") {
                instrId = STOP;
                noArgInstr = true;
            }

            else if(op == "equal"){
                instrId = EQUAL;
                noArgInstr = true;
            }
            else if(op == "invokevirtual"){
                instrId = INVOKEVIRTUAL;
                noArgInstr = true;
            }
            else if(op == "goto"){
                instrId = GOTO;
                noArgInstr = true;
            }
            else if(op == "iffalse_goto"){
                instrId = IFFALSEGOTO;
                noArgInstr = true;
            }
            else if( op == "igt"){
                instrId = IGT;
                noArgInstr = true;
            }


            if (noArgInstr) {
                // Add instruction with dummy argument (0)
                instructions.emplace_back(instrId, 0);
            } else {
                // Handle instructions with arguments
                if (iss >> arg) {
                    bool isConstant = false;
                    int argValue = 0;

                    if (isdigit(arg[0]) || arg[0] == '-') {
                        argValue = std::stoi(arg);
                        isConstant = true;
                    } else {
                        auto it = varIndexMap.find(arg);
                        if (it != varIndexMap.end()) {
                            argValue = it->second;
                        } else {
                            argValue = variables.size();
                            variables.push_back(arg);
                            varIndexMap[arg] = argValue;
                        }
                    }

                    // Determine instruction ID for ops with arguments
                    if (op == "iload" && isConstant) {
                        instrId = ICONST;
                    } else if (op == "iload") {
                        instrId = ILOAD;
                    } else if (op == "iconst") {
                        instrId = ICONST;
                    } else if (op == "istore") {
                        instrId = ISTORE;
                    } else if (op == "goto") {
                        instrId = GOTO;
                    } else if (op == "iffalse_goto") {
                        instrId = IFFALSEGOTO;
                    } else if (op == "invokevirtual") {
                        instrId = INVOKEVIRTUAL;
                    } 

                    if (instrId != -1) {
                        instructions.emplace_back(instrId, argValue);
                    }
                } else {
                    throw std::runtime_error("Missing argument for instruction: " + op);
                }
            }
        }
    }

    // Handle remaining instructions after loop
    if (!instructions.empty()) {
        if (instructions.back().id != STOP) {
            instructions.emplace_back(STOP, 0);
        }
        methods[currentMethod] = Method(instructions, variables);
    }

    return Program(methods);
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <bytecode file>" << std::endl;
        return 1;
    }

    try {
        Program program = loadProgramFromFile(argv[1]);
        Interpreter interpreter(program);
        interpreter.execute();
    } catch (const std::exception& e) {
        std::cerr << "Interpreter error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
