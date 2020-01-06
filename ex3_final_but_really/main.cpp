#include <iostream>
#include <thread>
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommend.h"
#include "Lexer.h"
#include "Parser.h"


int main(int argc, char *argv[]) {

    if (argc < 0) {
        cout << "error"<<endl;
    }
    vector<vector<string>> v;
    Lexer* l = new Lexer();
    std::fstream fs;
    fs.open (argv[1], std::fstream::in | std::fstream::out | std::fstream::app);
    v = l->cutFile(&fs);

    Parser* p = new Parser(v);
    p->executeScope();

}
