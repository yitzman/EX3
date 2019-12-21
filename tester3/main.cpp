#include <iostream>
#include <thread>
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
static bool is_done = false;
int main() {
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

    std::cout << "Hello, World!" << std::endl;
    return 0;
}