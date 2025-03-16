#include "interpreter.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./interpreter <bytecode_file>" << std::endl;
        return 1;
    }

    Interpreter interpreter;
    interpreter.loadBytecode(argv[1]);
    interpreter.execute();

    return 0;
}
