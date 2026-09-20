//main.cpp

#include <fstream>
#include <iostream>
#include <sstream>


#include "include/dfa.hpp"
#include "include/scanner.hpp"
#include "include/token.hpp"

static void dumpTable(std::ostream&out){
    out<< "| state |";
    for(int c = 0;c< NUM_CLASSES;c++){
        out<< " " << c << " |";
    }
    out<< "\n|---|";
    for(int c = 0;c< NUM_CLASSES;c++){
        out<< "---|";
    }
    out<< "\n";
    
    for(int s = 0;s< NUM_STATES;s++){
       out << "| " << s << ' ' << STATE_NAMES[s]
        << (ACTION[s] != A_NONE ? "*" : "") << " |";
        for(int c = 0;c< NUM_CLASSES;c++){
            out<< " " << TRANSITION[s][c] << " |";
        }
        out<< "\n";
    }
}





int main(int argc, char** argv) {
        if (argc >= 2 && std::string(argv[1]) == "--dump-table") {

        dumpTable(std::cout);
        return 0;
    }
    if (argc < 2) {
        std::cerr << "usage: lexer <file.oc> [-o <out>]  |  lexer --dump-table\n";
        return 2;
    }
        std::ifstream in(argv[1]);
    if (!in) { std::cerr << "cannot open " << argv[1] << '\n'; return 2; }
    std::stringstream buf;
    buf << in.rdbuf();

    Scanner scanner(buf.str());
    for (;;) {
        Token t = scanner.next();
        std::cout << '<' << tokenTypeName(t.type) << ',';
        if (hasValuePart(t.type)) std::cout << ' ' << t.value;
        std::cout << ">\n";
        if (t.type == COMPILER_ERROR)
            std::cerr << argv[1] << ':' << t.line << ':' << t.column
                      << ": error: unrecognized lexeme '" << t.value << "'\n";
        if (t.type == COMPILER_EOF) break;
    }
    return 0;
}