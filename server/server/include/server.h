#ifndef SERVER
#define SERVER

#include "i_handler.h"
#include "i_receiver.h"
#include "i_sender.h"
#include "requests.h"
#include "responses.h"
#include "thread_cycler.h"

#include "i_server.h"

namespace server {

class Server : virtual public helpers::ThreadCycler, virtual public IServer {
protected:
    handler::IHandler& handler;
    receiver::IReceiver& receiver;
    sender::ISender& sender;
    
public:
    Server(
        handler::IHandler& handler,
        receiver::IReceiver& receiver,
        sender::ISender& sender
    );
    virtual ~Server() = default;

    virtual void start() override;
    virtual void stop() override;

protected:
    virtual void work() override;
    virtual void handleFatalThreadException(std::exception& e) override;

    requests::RequestVar getRequest() const; 
    responses::ResponseVar handleRequest(const requests::RequestVar& request) const;
    void sendResponse(const responses::ResponseVar& response) const;
};

} // namespace server

#endif // SERVER
