#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "INTERPRETER.h"
#include "BYTECODE.h"

InstructionType mapToEnum(const std::string& op) {
    if (op == "iconst") return ICONST;
    if (op == "iload") return ILOAD;
    if (op == "istore") return ISTORE;
    if (op == "iadd") return IADD;
    if (op == "isub") return ISUB;
    if (op == "imul") return IMUL;
    if (op == "idiv") return IDIV;
    if (op == "ilt") return ILT;
    if (op == "igt") return IGT;
    if (op == "equal") return EQUAL;
    if (op == "iand") return IAND;
    if (op == "ior") return IOR;
    if (op == "inot") return INOT;
    if (op == "goto") return GOTO;
    if (op == "iffalse_goto") return IFFALSEGOTO;
    if (op == "invokevirtual") return INVOKEVIRTUAL;
    if (op == "ireturn") return IRETURN;
    if (op == "print") return PRINT;
    if (op == "stop") return STOP;
    if (op == "new") return NEW;
    if (op == "label") return STOP;
    throw std::runtime_error("Unknown opcode: " + op);
}

struct ParsedProgram {
    Program program;
    std::unordered_map<std::string, int> labelMap;
};

// renamed to avoid conflict with INTERPRETER.h
ParsedProgram parseBytecodeFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) throw std::runtime_error("Could not open bytecode file: " + filename);

    std::unordered_map<std::string, Method> methods;
    std::unordered_map<std::string, int> labelMap;
    std::vector<Instruction> currentInstructions;
    std::vector<std::string> currentVars;
    std::string currentMethodName;
    int currentPc = 0;

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        std::istringstream iss(lines[i]);
        std::string op, op1, op2;
        iss >> op;

        if (op == "method") {
            if (!currentMethodName.empty()) {
                methods[currentMethodName] = Method(currentInstructions, currentVars);
                currentInstructions.clear();
                currentVars.clear();
                currentPc = 0;
            }
            std::string className, methodName;
            iss >> className >> methodName;
            currentMethodName = methodName;
            continue;
        }

        if (op.back() == ':') {
            std::string label = op.substr(0, op.length() - 1);
            labelMap[label] = currentPc;
            continue;
        }

        if (op == "label") {
            iss >> op1;
            labelMap[op1] = currentPc;
            continue;
        }

        iss >> op1 >> op2;
        InstructionType type = mapToEnum(op);

        if (type == ICONST) {
            int val = std::stoi(op1);
            currentInstructions.emplace_back(type, "", val);
        } else if (type == ILOAD || type == ISTORE || type == INVOKEVIRTUAL ||
                   type == GOTO || type == IFFALSEGOTO || type == NEW) {
            currentInstructions.emplace_back(type, op1);
            if (std::find(currentVars.begin(), currentVars.end(), op1) == currentVars.end()) {
                currentVars.push_back(op1);
            }
        } else {
            currentInstructions.emplace_back(type, "");
        }

        currentPc++;
    }

    if (!currentMethodName.empty()) {
        methods[currentMethodName] = Method(currentInstructions, currentVars);
    }

    ParsedProgram result;
    result.program = Program(methods);
    result.labelMap = labelMap;
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./interpreter <output.bytecode>" << std::endl;
        return 1;
    }

    std::string bytecodePath = argv[1];

    try {
        ParsedProgram parsed = parseBytecodeFile(bytecodePath);
        Interpreter interpreter(parsed.program);
        interpreter.labelMap = parsed.labelMap;
        interpreter.execute();
    } catch (const std::exception& ex) {
        std::cerr << "Interpreter error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
