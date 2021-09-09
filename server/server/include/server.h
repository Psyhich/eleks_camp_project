#ifndef SERVER
#define SERVER

#include <atomic>
#include <memory>
#include <thread>

#include "i_handler.h"
#include "i_receiver.h"
#include "i_sender.h"
#include "requests.h"
#include "responses.h"

namespace server {

class Server {
protected:
    std::unique_ptr<std::thread> threadPtr;
    std::atomic<bool> stopFlag {true};

    handler::IHandler& handler;
    receiver::IReceiver& receiver;
    sender::ISender& sender;
    
public:
    Server(
        handler::IHandler& handler,
        receiver::IReceiver& receiver,
        sender::ISender& sender
    );
    virtual ~Server();

    virtual void start();
    virtual void stop();

protected:
    void run();
    requests::RequestVar getRequest() const; 
    responses::ResponseVar handleRequest(const requests::RequestVar& request) const;
    void sendResponse(const responses::ResponseVar& response) const;
};

} // namespace server

#endif // SERVER
