#include <iostream>

#include "remote_server_keeper.h"

int main(){
    try {
        bool stopped{true};
        std::string command;
        server::RemoteServerKeeper serverKeeper;
        while (true){
            if (stopped){
                std::cout<<"start/exit >";
            } else {
                std::cout<<"stop/exit >";
            }
            std::cin>>command;
            if (command == "start"){
                serverKeeper.start();
                stopped = false;
            } else if (command == "stop") {
                serverKeeper.stop();
                stopped = true;
            } else if (command == "exit") {
                if (!stopped){
                    serverKeeper.stop();
                }
                break;
            }
        } 
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}