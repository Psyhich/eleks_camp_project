#include <exception>
#include <iostream>

#include "i_server.h"
#include "remote_server_keeper.h"

int main(){
    try {
        bool stopped{true};
        std::string command;
        server::RemoteServerKeeper serverKeeper;
        server::IServer& server = serverKeeper.getServer();
        while (true){
            if (stopped){
                std::cout<<"start/exit >";
            } else {
                std::cout<<"stop/exit >";
            }
            std::cin>>command;
            if (command == "start"){
                try{
                    server.start();
                    stopped = false;
                } catch (std::exception& e) {
                    std::cerr << "Server failed to start.";
                }
            } else if (command == "stop") {
                server.stop();
                stopped = true;
            } else if (command == "exit") {
                if (!stopped){
                    server.stop();
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