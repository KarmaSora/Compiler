#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <iostream>

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
    STOP,    // stop Execution completed
    
    EQUAL,    // checks ==
    IGT, // igt Pop value v1 and v2. Push 1 if v2 > v1, else 0
    
    NEW // new Create a new object of the class specified by the argument

    
  
    
    
};

class Instruction {
public:
    InstructionType type;
    std::string operand; // variable name, label, or method name
    int intValue;        // numeric value, e.g., for iconst or jump targets

    Instruction();
    Instruction(InstructionType t, const std::string& op, int val = 0);
    void printInstruction() const;
};

class Method {
public:
    std::vector<Instruction> instructions;
    std::vector<std::string> variables;

    Method();
    Method(std::vector<Instruction> instructions, std::vector<std::string> variables);
    void printMethod() const ;
};

class Program {
public:
    std::unordered_map<std::string, Method> methods;

    Program();
    Program(std::unordered_map<std::string, Method> methods);
    void printProgram() const;
    Method getMainMethod();
};

class Activation {
public:
    int pc;
    std::unordered_map<std::string, int> local_variables;
    Method method;

    Activation();
    Activation(int p, Method m);
    Instruction* getNextInstruction();
    void storeValue(const std::string& var, int value);
};

class Interpreter {
public:
    Program program;
    Method main;

    std::unordered_map<std::string, int> labelMap;           // Label to instruction index
    std::unordered_map<std::string, int> objectHeap;         // Simulated object heap

    Interpreter();
    Interpreter(Program program);
    void execute();
};

// Load a bytecode program from a file into memory
Program loadProgramFromFile(const std::string& filename);

#endif // INTERPRETER_H
