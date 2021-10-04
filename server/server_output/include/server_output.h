#ifndef SERVER_OUTPUT
#define SERVER_OUTPUT

#include <atomic>
#include <iostream>
#include <mutex>
#include <string>

namespace server {

class ServerOutput {
    std::mutex outputMut;
    std::atomic<bool> serverStopped {true};
    std::atomic<bool> afterCommand {false};
    std::string serverStoppedPrompt;
    std::string serverRunningPrompt;
public:
    ServerOutput() = default;
    ServerOutput(const ServerOutput&) = delete;
    ServerOutput& operator=(const ServerOutput&) = delete;

    void info(const std::string& message);
    void error(const std::string& message);
    void prompt();

    void setServerStoppedPrompt(const std::string& prompt);
    void setServerRunningPrompt(const std::string& prompt);
    void setServerStopped(bool stopped);
    void setAfterCommand(bool after);

private:
    void printPrompt();
};

extern ServerOutput output;

} // namespace server

#endif // SERVER_OUTPUT