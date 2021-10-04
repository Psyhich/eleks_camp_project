#include "server_output.h"

namespace server {

ServerOutput output;

void ServerOutput::info(const std::string& message) {
    std::scoped_lock outputLock(outputMut);
    if (!afterCommand.load()){
        std::cout<<std::endl;
    }
    std::cout<<message<<std::endl;
    printPrompt();
    afterCommand.store(false);
}
void ServerOutput::error(const std::string& message) {
    std::scoped_lock outputLock(outputMut);
    if (!afterCommand.load()){
        std::cout<<std::endl;
    }
    std::cerr<<message<<std::endl;
    printPrompt();
    afterCommand.store(false);
}

void ServerOutput::prompt() {
    std::scoped_lock outputLock(outputMut);
    if (!afterCommand.load()){
        std::cout<<std::endl;
    }
    printPrompt();
    afterCommand.store(false);
}

void ServerOutput::setServerStoppedPrompt(const std::string& prompt) {
    serverStoppedPrompt = prompt;
}

void ServerOutput::setServerRunningPrompt(const std::string& prompt) {
    serverRunningPrompt = prompt;
}
void ServerOutput::setServerStopped(bool stopped) {
    serverStopped.store(stopped);
}

void ServerOutput::setAfterCommand(bool after) {
    afterCommand.store(after);
}

void ServerOutput::printPrompt() {
    if (serverStopped.load()) {
        std::cout << serverStoppedPrompt;
    } else {
        std::cout << serverRunningPrompt;
    }
}

} // namespace server