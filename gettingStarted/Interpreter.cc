#include "Interpreter.h"

#include <iostream>

// ========== Instruction ==========
Instruction::Instruction() : type(STOP), operand(""), intValue(0) {}
Instruction::Instruction(InstructionType t, const std::string& op, int val)
    : type(t), operand(op), intValue(val) {}

void Instruction::printInstruction() const{
    std::cout << "Instruction: " << type << " " << operand << " " << intValue << "\n";
}

// ========== Method ==========
Method::Method() {}
Method::Method(std::vector<Instruction> instructions, std::vector<std::string> variables)
    : instructions(instructions), variables(variables) {}

void Method::printMethod() const {
    for (const auto& instr : instructions) {
        instr.printInstruction();
    }
}

// ========== Program ==========
Program::Program() {}
Program::Program(std::unordered_map<std::string, Method> methods) : methods(methods) {}

void Program::printProgram() const{
    for (const auto& entry : methods) {
        std::cout << "Method: " << entry.first << "\n";
        entry.second.printMethod();
    }
}

Method Program::getMainMethod() {
    auto it = methods.find("Main");
    if (it == methods.end()) {
        throw std::runtime_error("Main method not found.");
    }
    return it->second;
}

// ========== Activation ==========
Activation::Activation() : pc(0) {}
Activation::Activation(int p, Method m) : pc(p), method(m) {}

Instruction* Activation::getNextInstruction() {
    if (pc >= method.instructions.size()) return nullptr;
    return &method.instructions[pc];
}

void Activation::storeValue(const std::string& var, int value) {
    local_variables[var] = value;
}

// ========== Interpreter ==========
Interpreter::Interpreter() {}
Interpreter::Interpreter(Program program)
    : program(program), main(program.getMainMethod()) {}

    void Interpreter::execute() {
        std::stack<Activation*> activations;
        std::stack<int> data;
        Activation* current = new Activation(0, main);
    
        while (true) {
            if (current->pc >= current->method.instructions.size()) {
                throw std::runtime_error("Instruction pointer out of bounds");
            }
    
            Instruction* instr = current->getNextInstruction();
            if (!instr) break;
    
            InstructionType type = instr->type;
    
            // Debug
            std::cout << "Executing [" << current->pc << "]: " << type << " (" << instr->operand << ", " << instr->intValue << ")\n";
    
            bool didJump = false;
    
            switch (type) {
                case ICONST:
                    data.push(instr->intValue);
                    break;
    
                case ILOAD:
                    data.push(current->local_variables[instr->operand]);
                    break;
    
                case ISTORE: {
                    if (data.empty()) throw std::runtime_error("Stack underflow: ISTORE");
                    int val = data.top(); data.pop();
                    current->storeValue(instr->operand, val);
                    break;
                }
    
                case IADD: case ISUB: case IMUL: case IDIV: case ILT:
                case IGT: case EQUAL: case IAND: case IOR: {
                    if (data.size() < 2) throw std::runtime_error("Stack underflow");
                    int v1 = data.top(); data.pop();
                    int v2 = data.top(); data.pop();
                    int result = 0;
                    if (type == IADD) result = v2 + v1;
                    else if (type == ISUB) result = v2 - v1;
                    else if (type == IMUL) result = v2 * v1;
                    else if (type == IDIV) {
                        if (v1 == 0) throw std::runtime_error("Division by zero");
                        result = v2 / v1;
                    }
                    else if (type == ILT) result = v2 < v1;
                    else if (type == IGT) result = v2 > v1;
                    else if (type == EQUAL) result = v2 == v1;
                    else if (type == IAND) result = (v1 != 0 && v2 != 0);
                    else if (type == IOR) result = (v1 != 0 || v2 != 0);
                    data.push(result);
                    break;
                }
    
                case INOT: {
                    if (data.empty()) throw std::runtime_error("Stack underflow: INOT");
                    int v = data.top(); data.pop();
                    data.push(v == 0 ? 1 : 0);
                    break;
                }
    
                case PRINT: {
                    if (data.empty()) throw std::runtime_error("Stack underflow: PRINT");
                    std::cout << "Output: " << data.top() << std::endl;
                    data.pop();
                    break;
                }
    
                case GOTO: {
                    auto it = labelMap.find(instr->operand);
                    if (it == labelMap.end()) throw std::runtime_error("Unknown label: " + instr->operand);
                    current->pc = it->second;
                    didJump = true;
                    break;
                }
    
                case IFFALSEGOTO: {
                    if (data.empty()) throw std::runtime_error("Stack underflow: IFFALSEGOTO");
                    int cond = data.top(); data.pop();
                    if (cond == 0) {
                        auto it = labelMap.find(instr->operand);
                        if (it == labelMap.end()) throw std::runtime_error("Unknown label: " + instr->operand);
                        current->pc = it->second;
                        didJump = true;
                    }
                    break;
                }
    
                case INVOKEVIRTUAL: {
                    std::string methodName = instr->operand;
                    auto it = program.methods.find(methodName);
                    if (it == program.methods.end()) throw std::runtime_error("Method not found: " + methodName);
                
                    Method method = it->second;
                    Activation* newActivation = new Activation(0, method);
                
                    int argCount = instr->intValue;
                    if (argCount > method.variables.size()) {
                        throw std::runtime_error("Not enough variables in method to hold arguments.");
                    }
                
                    // Pop arguments and assign to first N declared variables
                    for (int i = argCount - 1; i >= 0; --i) {
                        if (data.empty()) throw std::runtime_error("Stack underflow during argument passing");
                        int val = data.top(); data.pop();
                        const std::string& varName = method.variables[i];
                        newActivation->local_variables[varName] = val;
                    }
                
                    activations.push(current);
                    current = newActivation;
                    didJump = true;
                    break;
                }
                
                
                
    
                case IRETURN: {
                    if (activations.empty()) {
                        delete current;
                        std::cout << "Execution completed." << std::endl;
                        return;
                    }
                    Activation* prev = current;
                    current = activations.top(); activations.pop();
                    current->pc++; // 🔥 advance past the CALL after returning
                    delete prev;
                    didJump = true;
                    break;
                }
                
                
    
                case STOP:
                    delete current;
                    std::cout << "Program stopped." << std::endl;
                    return;
    
                case NEW:
                    // For now, just push dummy object reference (e.g., ID or address)
                    static int nextObjectId = 1000;
                    data.push(nextObjectId++);
                    break;
    
                default:
                    throw std::runtime_error("Unknown or unhandled instruction type.");
            }
    
            if (!didJump) {
                current->pc++;
            }
        }
    
        delete current;
    }
    