#include "Interpreter.h"
#include <iostream>

// ==========================
// Program class definitions
// ==========================
Program::Program() {
    std::cout << "Program constructed." << std::endl;
}

Program::Program(std::unordered_map<std::string, Method> methods) : methods(methods) {
    std::cout << "Program constructed with methods." << std::endl;
}

void Program::printProgram() {
    for (const auto& method : methods) {
        std::cout << "Method name: " << method.first << std::endl;
        method.second.printMethod();
    }
}

Method Program::getMainMethod() {
    if (methods.find("main") != methods.end()) {
        return methods["main"];
    } else {
        throw std::runtime_error("Main method not found.");
    }
}

// ==========================
// Instruction class definitions
// ==========================
Instruction::Instruction() : id(0), argument(0) {}

Instruction::Instruction(int id, int argument) : id(id), argument(argument) {}

void Instruction::printInstruction() {
    std::cout << "Instruction ID: " << id << ", Argument: " << argument << std::endl;
}

// ==========================
// Method class definitions
// ==========================
Method::Method() {
    std::cout << "Method constructed." << std::endl;
}

Method::Method(std::vector<Instruction> instr, std::vector<std::string> vars)
    : instructions(instr), variables(vars) {}

void Method::printMethod() {
    std::cout << "Method: " << std::endl;
    for (const auto& instr : instructions) {
        instr.printInstruction();
    }
    std::cout << "Method variables: " << std::endl;

    for (const auto& var : variables) {
        std::cout << var << std::endl;
    }
}

// ==========================
// Activation class definitions
// ==========================
Activation::Activation() : PC(0) {
    std::cout << "Activation frame created, PC = " << PC << std::endl;
}

Activation::Activation(int pc, Method method) : PC(pc), method(method) {
    std::cout << "Activation frame created, PC = " << PC << std::endl;
}


Instruction Activation::getNextInstruction() {
    if (PC < method.instructions.size()) {
        return method.instructions[PC];
    } else {
        throw std::runtime_error("No more instructions to execute.");
    }
}

void Activation::storeValue(std::string var, int value) {
    if (std::find(method.variables.begin(), method.variables.end(), var) != method.variables.end()) {
        local_variables[var] = value;
    } else {
        throw std::runtime_error("Variable not found in method.");
    }
}

// ==========================
// Interpreter class definitions
// ==========================
Interpreter::Interpreter() {
    std::cout << "Interpreter constructed." << std::endl;
}

Interpreter::Interpreter(Program program) : program(program), main(program.getMainMethod()) {}

void Interpreter::execute() {
    Method *m = this->main;
    Activation* current_activation = new Activation(0, m);
    
    int instruction_id = -1;

    std::stack<Activation> activations_stack;
    std::stack<int> data_stack;

    while (instruction_id != InstructionType::STOP) {
        Instruction* currentInstr = current_activation->getNextInstruction();

        switch (currentInstr->id)
        {
        case ICONST:
            /* code */
            data_stack.push(currentInstr->argument);
            break;
        case ISTORE:
            /* code */
            current_activation->storeValue(currentInstr->argument, data_stack.top());
            data_stack.pop();
            break;
        case IADD:
            /* code */
            int first = data_stack.top();
            data_stack.pop();
            int second = data_stack.top();
            data_stack.pop();
            data_stack.push(first + second);
            break;
        case ISUB:
            /* code */
            int first = data_stack.top();
            data_stack.pop();
            int second = data_stack.top();
            data_stack.pop();
            data_stack.push(first - second);
            break;
        case IMUL:
            /* code */
            int first = data_stack.top();
            data_stack.pop();
            int second = data_stack.top();
            data_stack.pop();
            data_stack.push(first * second);
            break;
        case IDIV:
            /* code */
            int first = data_stack.top();
            data_stack.pop();
            int second = data_stack.top();
            data_stack.pop();
            data_stack.push(first / second);
            break;
        case PRINT:
            /* code */
            std::cout << data_stack.top() << std::endl;
            data_stack.pop();
            break;
        case GOTO:
            /* code */
            current_activation->PC = currentInstr->argument;
            break;
                    
        default:
            break;
        }
        
        
       
    }

    delete current_activation;
}
