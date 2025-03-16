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
    std::unordered_map<std::string, int> varIndexMap; // Map variable names to indices
    std::string line;
    std::string currentMethod = "main";

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string op, arg;
        
        iss >> op;
        if (op == "method") {
            if (!instructions.empty()) {
                // Ensure stop instruction is present before closing the method
                if (instructions.empty() || instructions.back().id != STOP) {
                    instructions.emplace_back(STOP, 0);
                }
                methods[currentMethod] = Method(instructions, variables);
                instructions.clear();
                variables.clear();
                varIndexMap.clear(); // Reset variable mapping per method
            }
            iss >> currentMethod;
        } else if (op == "var") {
            iss >> arg;
            if (varIndexMap.find(arg) == varIndexMap.end()) {
                varIndexMap[arg] = variables.size();
                variables.push_back(arg);
            }
        } else {
            if (iss >> arg) {
                int instrId = -1;
                int argValue = 0;
                bool isConstant = false;

                // Check if the argument is a number (constant)
                if (isdigit(arg[0]) || arg[0] == '-') {
                    argValue = std::stoi(arg);
                    isConstant = true;
                } else {
                    // Variable handling
                    auto it = varIndexMap.find(arg);
                    if (it != varIndexMap.end()) {
                        argValue = it->second; // Get existing index
                    } else {
                        // New variable found, assign it a new index
                        argValue = variables.size();
                        variables.push_back(arg);
                        varIndexMap[arg] = argValue;
                    }
                }

                // Match operation
                if (op == "iload" && isConstant) instrId = ICONST; // Fix: use ICONST for constants
                else if (op == "iload") instrId = ILOAD;
                else if (op == "iconst") instrId = ICONST;
                else if (op == "istore") instrId = ISTORE;
                else if (op == "iadd") instrId = IADD;
                else if (op == "isub") instrId = ISUB;
                else if (op == "imul") instrId = IMUL;
                else if (op == "idiv") instrId = IDIV;
                else if (op == "ilt") instrId = ILT;
                else if (op == "iand") instrId = IAND;
                else if (op == "ior") instrId = IOR;
                else if (op == "inot") instrId = INOT;
                else if (op == "goto") instrId = GOTO;
                else if (op == "iffalse_goto") instrId = IFFALSEGOTO;
                else if (op == "invokevirtual") instrId = INVOKEVIRTUAL;
                else if (op == "ireturn") instrId = IRETURN;
                else if (op == "print") instrId = PRINT;
                else if (op == "stop") instrId = STOP;
                else if (op == "class") instrId = CLASS;
                else if (op == "new") instrId = NEW;
                else if (op == "label") instrId = LABEL;

                if (instrId != -1) {
                    instructions.emplace_back(instrId, argValue);
                }
            }
        }
    }

    // Ensure the last instruction in main is STOP
    if (instructions.empty() || instructions.back().id != STOP) {
        instructions.emplace_back(STOP, 0);
    }

    if (!instructions.empty()) {
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
