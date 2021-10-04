#include <exception>
#include <iostream>
#include <string>

#include "i_server.h"
#include "remote_server_keeper.h"
#include "server_output.h"

int main(){
    try {
        bool stopped{true};
        std::string command;
        server::RemoteServerKeeper serverKeeper;
        server::IServer& server = serverKeeper.getServer();
        server::output.setServerStoppedPrompt("start/exit >");
        server::output.setServerRunningPrompt("stop/exit >");
        server::output.setAfterCommand(true);
        server::output.prompt();
        while (true){
            std::cin>>command;
            if (command == "start"){
                server::output.setAfterCommand(true);
                if (stopped){
                    server::output.setServerStopped(false);
                    try{
                        server.start();
                    } catch (std::exception& e) {
                        server::output.setServerStopped(true);
                        server::output.error(std::string("Server failed to start: ")+e.what());
                    }
                    stopped = false;
                } else {
                    server::output.prompt();
                }
            } else if (command == "stop") {
                server::output.setAfterCommand(true);
                if (!stopped){
                    server::output.setServerStopped(true);
                    server.stop();
                    stopped = true;
                } else {
                    server::output.prompt();
                }
            } else if (command == "exit") {
                server::output.setAfterCommand(true);
                server::output.setServerStopped(true);
                server.stop();
                stopped = true;
                break;
            } else {
                server::output.setAfterCommand(true);
                server::output.prompt();
            }
        } 
    } catch (std::exception& e) {
        server::output.error(e.what());
        return 1;
    }
    return 0;
}