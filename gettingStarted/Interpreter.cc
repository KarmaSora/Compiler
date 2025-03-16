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
    for ( auto& method : methods) {
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
    for (auto& instr : instructions) {
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
Activation::Activation() : pc(0) {
    std::cout << "Activation frame created, pc = " << pc << std::endl;
}

Activation::Activation(int p, Method m) : pc(p), method(m) {
    std::cout << "Activation frame created, pc = " << p << std::endl;
}


Instruction* Activation::getNextInstruction() {
    if (pc < method.instructions.size()) {
        return &method.instructions[pc++];
    } else {
        throw std::runtime_error("No more instructions to execute.");
    }
}


void Activation::storeValue(std::string& var, int value) {
        local_variables[var] = value;
    
}

// ==========================
// Interpreter class definitions
// ==========================
Interpreter::Interpreter() {
    std::cout << "Interpreter constructed." << std::endl;
}

Interpreter::Interpreter(Program program) : program(program), main(program.getMainMethod()) {}


void Interpreter::execute() {
    Method m = this->main;
    Activation* current_activation = new Activation(0, m);
    
    int instruction_id = -1;
    std::stack<Activation*> activations_stack;
    std::stack<int> data_stack;

    std::cout << "Execution started...\n";

    while (instruction_id != InstructionType::STOP) {
        if (current_activation->pc >= current_activation->method.instructions.size()) {
            std::cerr << "Interpreter error: No more instructions to execute.\n";
            break;
        }

        Instruction* currentInstr = current_activation->getNextInstruction();

        // Debug: Print the instruction being executed
        std::cout << "Executing instruction: ID=" << currentInstr->id 
                  << ", Argument=" << currentInstr->argument << "\n";

        switch (currentInstr->id)
        {
        case ICONST:
            data_stack.push(currentInstr->argument);
            std::cout << "Pushed to stack: " << currentInstr->argument << "\n";
            break;
        case ISTORE:
            if (data_stack.empty()) {
                throw std::runtime_error("Data stack underflow in ISTORE");
            }
            {
                int value = data_stack.top(); // Ensure we store the multiplication result
                data_stack.pop();
                std::string varName = std::to_string(currentInstr->argument);
                if (currentInstr->argument < current_activation->method.variables.size()) {
                    varName = current_activation->method.variables[currentInstr->argument];
                }
                current_activation->storeValue(varName, value);
                std::cout << "Stored " << value << " in variable " << varName << "\n"; // Debug
            }
        break;
        case ILOAD:
            {
                std::string varName = std::to_string(currentInstr->argument);
                if (currentInstr->argument < current_activation->method.variables.size()) {
                    varName = current_activation->method.variables[currentInstr->argument];
                }
                if (current_activation->local_variables.find(varName) == current_activation->local_variables.end()) {
                    throw std::runtime_error("Variable " + varName + " not initialized.");
                }
                data_stack.push(current_activation->local_variables[varName]);
                std::cout << "Loaded variable " << varName << " onto stack\n";
            }
            break;

        case PRINT:
            if (data_stack.empty()) {
                throw std::runtime_error("Data stack underflow in PRINT");
            }
            std::cout << "Output: " << data_stack.top() << std::endl;
            data_stack.pop();
            break;

        case STOP:
            std::cout << "Execution completed.\n";
            instruction_id = InstructionType::STOP;
            break;

        default:
            std::cerr << "Unknown instruction encountered.\n";
            break;
        }
    }

    delete current_activation;
}


