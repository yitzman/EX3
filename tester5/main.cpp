#include <iostream>
#include <thread>
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommend.h"
#include "Lexer.h"
#include "Parser.h"

static bool is_done = false;
int main() {
    vector<vector<string>> v;
    Lexer* l = new Lexer();
    std::fstream fs;
    fs.open ("fly.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    v = l->cutFile(&fs);

    Parser* p = new Parser(v);
    p->execute();
    cout<<"done";

}
/*
 * Parser* p = new Parser(v);
    p->execute();
 *
 * cout<<"hi";
    v = l->cutFile(f);
    Parser* p = new Parser(v);
    p->execute();
    Lexer l();

    ifstream myReadFile;
    myReadFile.open("fly.txt");

    vector<vector<string>> vec = l.cutFile(&myReadFile);
    Parser parser(vec);
    parser.execute();

    return 0;
     */

/*
   OpenServerCommand op("5400");
   //op.execute();

   std::thread t1(&OpenServerCommand::execute, ref(op));

   std::this_thread::sleep_for(1s);
//
//    ConnectCommand con_com("127.0.0.1", "5400");
//    thread t2(&ConnectCommand::execute, std::ref(con_com));
//
//    std::this_thread::sleep_for(1s);
//
//    t2.join();
//
//    con_com.sendMassageToServer("bla");

   t1.join();
    */