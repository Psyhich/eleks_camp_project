#ifndef SERVER
#define SERVER

#include "i_handler.h"
#include "i_receiver.h"
#include "i_sender.h"
#include "requests.h"
#include "responses.h"

namespace server {

class Server {
    handler::IHandler& handler;
    receiver::IReceiver& receiver;
    sender::ISender& sender;
    
public:
    Server(
        handler::IHandler& handler,
        receiver::IReceiver& receiver,
        sender::ISender& sender
    );

    void operator()();

private:
    requests::RequestVar getRequest() const; 
    responses::ResponseVar handleRequest(const requests::RequestVar& request) const;
    void sendResponse(const responses::ResponseVar& response) const;
};

} // namespace server

#endif // SERVER
