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
    
    std::stack<Activation*> activations_stack;
    std::stack<int> data_stack;

    std::cout << "Execution started...\n";



    while (true) {
        if (current_activation->pc >= current_activation->method.instructions.size()) {
            std::cerr << "Interpreter error: No more instructions to execute.\n";
            break;
        }

        Instruction* currentInstr = current_activation->getNextInstruction();
        //std::cout << "Executing instruction: ID=" << currentInstr->id 
        //          << ", Argument=" << currentInstr->argument << "\n";


        std::cout << "Executing instruction: ID=" << currentInstr->id
        << ", Argument=" << currentInstr->argument << std::endl;
        switch (currentInstr->id) {
            case ICONST:
                data_stack.push(currentInstr->argument);
                //std::cout << "Pushed constant: " << currentInstr->argument << "\n";
                break;

            case ISTORE: {
                if (data_stack.empty()) throw std::runtime_error("Stack underflow in ISTORE");
                int value = data_stack.top();
                data_stack.pop();
                std::string varName = current_activation->method.variables[currentInstr->argument];
                current_activation->storeValue(varName, value);
                std::cout << "Stored " << value << " in " << varName << "\n";
                break;
            }

            case ILOAD: {
                std::string varName = current_activation->method.variables[currentInstr->argument];
                if (current_activation->local_variables.find(varName) == current_activation->local_variables.end()) {
                    throw std::runtime_error("Variable " + varName + " not initialized.");
                }
                data_stack.push(current_activation->local_variables[varName]);
                //std::cout << "Loaded " << varName << ": " << current_activation->local_variables[varName] << "\n";
                break;
            }

            case IADD: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IADD");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push(v2 + v1);
                //std::cout << "Added " << v2 << " + " << v1 << " = " << (v2 + v1) << "\n";
                break;
            }

            case ISUB: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in ISUB");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push(v2 - v1);
                //std::cout << "Subtracted " << v2 << " - " << v1 << " = " << (v2 - v1) << "\n";
                break;
            }

            case IMUL: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IMUL");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push(v2 * v1);
                //std::cout << "Multiplied " << v2 << " * " << v1 << " = " << (v2 * v1) << "\n";
                break;
            }

            case IDIV: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IDIV");
                int v1 = data_stack.top(); data_stack.pop();
                if (v1 == 0) throw std::runtime_error("Division by zero");
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push(v2 / v1);
                std::cout << "Divided " << v2 << " / " << v1 << " = " << (v2 / v1) << "\n";
                break;
            }

            case ILT: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in ILT");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push((v2 < v1) ? 1 : 0);
                std::cout << "Compared " << v2 << " < " << v1 << " ? " << (v2 < v1) << "\n";
                break;
            }

            case IAND: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IAND");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push((v1 != 0 && v2 != 0) ? 1 : 0);
                std::cout << "Logical AND: " << v2 << " && " << v1 << " = " << (v1 && v2) << "\n";
                break;
            }

            case EQUAL: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IAND");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push((v1 ==v2 ) ? 1 : 0);
                std::cout << "Compared: " << v2 << " == " << v1 << " ? " << (v1 == v2) << "\n";
                break;
            }
            case IOR: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IOR");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push((v1 != 0 || v2 != 0) ? 1 : 0);
                std::cout << "Logical OR: " << v2 << " || " << v1 << " = " << (v1 || v2) << "\n";
                break;
            }

            case INOT: {
                if (data_stack.empty()) throw std::runtime_error("Stack underflow in INOT");
                int v = data_stack.top(); data_stack.pop();
                data_stack.push((v == 0) ? 1 : 0);
                std::cout << "Logical NOT: !" << v << " = " << !v << "\n";
                break;
            }

            case GOTO: {
                auto labelIt = labelMap.find(std::to_string(currentInstr->argument));
                if (labelIt == labelMap.end()) throw std::runtime_error("Label not found");
                current_activation->pc = labelIt->second;
                std::cout << "Jumped to label " << currentInstr->argument << " (PC=" << labelIt->second << ")\n";
                break;
            }

            case IFFALSEGOTO: {
                if (data_stack.empty()) throw std::runtime_error("Stack underflow in IFFALSEGOTO");
                int condition = data_stack.top(); data_stack.pop();
                if (condition == 0) {
                    auto labelIt = labelMap.find(std::to_string(currentInstr->argument));
                    if (labelIt == labelMap.end()) throw std::runtime_error("Label not found");
                    current_activation->pc = labelIt->second;
                    std::cout << "Jumped to label " << currentInstr->argument << " (PC=" << labelIt->second << ")\n";
                }
                break;
            }

            case INVOKEVIRTUAL: {
                std::string methodName = current_activation->method.variables[currentInstr->argument];
                auto methodIt = program.methods.find(methodName);
                if (methodIt == program.methods.end()) throw std::runtime_error("Method not found");
                activations_stack.push(current_activation);
                current_activation = new Activation(0, methodIt->second);
                std::cout << "Invoked method: " << methodName << "\n";
                break;
            }

            case IRETURN: {
                if (activations_stack.empty()) {
                    std::cout << "Execution completed.\n";
                    delete current_activation;
                    return;
                } else {
                    Activation* old = current_activation;
                    current_activation = activations_stack.top();
                    activations_stack.pop();
                    delete old;
                    std::cout << "Returned to previous method\n";
                }
                break;
            }



            case PRINT: {
                if (data_stack.empty()) throw std::runtime_error("Stack underflow in PRINT");
                std::cout << "Output: " << data_stack.top() << "\n\n";
                data_stack.pop();
                break;
            }

            case STOP: {
                std::cout << "Execution stopped.\n";
                delete current_activation;
                return;
            }

            case IGT: {
                if (data_stack.size() < 2) throw std::runtime_error("Stack underflow in IGT");
                int v1 = data_stack.top(); data_stack.pop();
                int v2 = data_stack.top(); data_stack.pop();
                data_stack.push((v2 > v1) ? 1 : 0);
                std::cout << "Compared " << v2 << " > " << v1 << " ? " << (v2 > v1) << "\n";
                break;
            }
            case NEW: {
                std::cout << "Executing NEW instruction for class: " << currentInstr->argument << std::endl;
                
                // Validate class index (Argument should map to a class name in methods)
                if (currentInstr->argument >= main.variables.size()) {
                    throw std::runtime_error("Invalid class reference in NEW instruction.");
                }
            
                std::string className = main.variables[currentInstr->argument];  // Get the class name
                auto methodIt = program.methods.find(className);  // Check if class exists
            
                if (methodIt == program.methods.end()) {
                    throw std::runtime_error("Class " + className + " not found in method table.");
                }
            
                // Create a new Activation frame for the object (Heap allocation simulation)
                Activation* newActivation = new Activation(0, methodIt->second);
                std::cout << "Created new instance of " << className << std::endl;
            
                // Store a reference (Just store an integer reference for now)
                int newRef = activations_stack.size() + 1;  // Unique reference ID
                data_stack.push(newRef);
            
                break;
            }
            

            


            default:
                throw std::runtime_error("Unsupported instruction" + std::to_string(currentInstr->id)); 
        }
    }
}

