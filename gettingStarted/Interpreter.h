#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stack>

enum InstructionType {
    ILOAD, // iload n Push integer value stored in local variable n.
    ICONST, // iconst v Push integer value v.
    ISTORE, // istore n Pop value v and store it in local variable n
    IADD, // iadd Pop value v1 and v2. Push v2 + v1
    ISUB, // isub Pop value v1 and v2. Push v2 - v1
    IMUL, // imul Pop value v1 and v2. Push v2 * v1
    IDIV, // idiv Pop value v1 and v2. Push v2 / v1
    ILT, // ilt Pop value v1 and v2. Push 1 if v2 < v1, else 0
    IAND, // iand Pop value v1 and v2. Push 0 if v2 * v1 == 0, else push 1.
    IOR, // ior Pop value v1 and v2. Push 0 if v2 + v1 == 0, else push 1
    INOT, // inot Pop value v. Push 1 if v == 0, else push 0.
    GOTO, // goto i Jump to instruction labeled i unconditionally
    IFFALSEGOTO, // iffalse goto i Pop value v from the data stack. If v == 0 jump to instruction labeled i,
                 //else continue with the following instruction

    INVOKEVIRTUAL,  // invokevirtual m Push current activation to the activation stack and
                    // switch to the method with qualified name m.
    IRETURN, // ireturn Pop the activation from the activation stack and continue 
    PRINT,  // print Pop the value from the data stack and print it
    STOP    // stop Execution completed
    
  
    
    
};

class Instruction {
public:
    int id;
    int argument;

    Instruction();
    Instruction(int id, int argument);
    void printInstruction();
};

class Method {
public:
    std::vector<Instruction> instructions;
    std::vector<std::string> variables;

    Method();
    Method(std::vector<Instruction> instructions, std::vector<std::string> variables);
    void printMethod();
};

class Program {
public:
    std::unordered_map<std::string, Method> methods;

    Program();
    Program(std::unordered_map<std::string, Method> methods);
    void printProgram();
    Method getMainMethod();
};

class Activation {
public:
    int pc;
    std::unordered_map<std::string, int> local_variables;
    Method method;

    Activation();
    Activation(int p, Method m);
    Instruction *  getNextInstruction();
    void storeValue(std::string& var, int value);
};

class Interpreter {
public:
    Program program;
    Method main;
    
std::unordered_map<std::string, int> labelMap; // Store labels with their instruction index
std::unordered_map<std::string, int> objectHeap; // Simulate object creation


    Interpreter();
    Interpreter(Program program);
    void execute();
};

#endif
