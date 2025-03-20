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
        std::cout << "[DEBUG] Parsing opcode: " << op << std::endl;

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
        } 
        else if (op == "var") {
            iss >> arg;
            if (varIndexMap.find(arg) == varIndexMap.end()) {
                varIndexMap[arg] = variables.size();
                variables.push_back(arg);
            }
        } 
        else {
            // Map opcodes to instruction IDs
            static const std::unordered_map<std::string, int> opcodes = {
                {"iadd", IADD}, {"isub", ISUB}, {"imul", IMUL}, {"idiv", IDIV},
                {"ilt", ILT}, {"igt", IGT}, {"iand", IAND}, {"ior", IOR},
                {"inot", INOT}, {"print", PRINT}, {"ireturn", IRETURN},
                {"stop", STOP}, {"equal", EQUAL}, {"invokevirtual", INVOKEVIRTUAL},
                {"goto", GOTO}, {"iffalse_goto", IFFALSEGOTO}, {"iload", ILOAD},
                {"iconst", ICONST}, {"istore", ISTORE}, {"new", NEW} // Added "new"
            };

            auto it = opcodes.find(op);
            if (it != opcodes.end()) {
                int instrId = it->second;
                std::cout << "[DEBUG] Mapped opcode '" << op << "' to ID: " << instrId << std::endl;

                if (instrId == ILOAD || instrId == ICONST || instrId == ISTORE ||
                    instrId == GOTO || instrId == IFFALSEGOTO || instrId == INVOKEVIRTUAL ||
                    instrId == NEW) { // "new" instruction requires an argument
                    
                    if (!(iss >> arg)) {
                        throw std::runtime_error("Missing argument for instruction: " + op);
                    }

                    int argValue;
                    if (isdigit(arg[0]) || arg[0] == '-') {
                        argValue = std::stoi(arg); // Handle numeric constants
                    } else {
                        auto varIt = varIndexMap.find(arg);
                        if (varIt != varIndexMap.end()) {
                            argValue = varIt->second; // Use existing variable index
                        } else {
                            argValue = variables.size();
                            variables.push_back(arg);
                            varIndexMap[arg] = argValue;
                        }
                    }

                    std::cout << "[DEBUG] Adding instruction: " << op << " (ID=" << instrId 
                              << ", Arg=" << argValue << ")" << std::endl;
                    instructions.emplace_back(instrId, argValue);
                } 
                else {
                    std::cout << "[DEBUG] Adding instruction: " << op << " (ID=" << instrId << ")" << std::endl;
                    instructions.emplace_back(instrId, 0);
                }
                
                std::cout << "[DEBUG] Available methods in program: ";
                for (const auto& method : methods) {
                    std::cout << method.first << " ";
                }
                std::cout << std::endl;


            } 
            else {
                throw std::runtime_error("Unknown opcode encountered: " + op);
            }
        }
    }

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
