#include "remote_sender.h"

namespace server {
namespace sender {

RemoteSender::RemoteSender(
    transfer::ITransfer& transfer,
    serializer::ISerializer& serializer
    ) :
    transfer{transfer},
    serializer{serializer}
{}

void RemoteSender::sendResponse(const responses::ResponseVar& response) const {
    transfer.sendPack(serializer.getPack(response));
}    

} // sender    
} // server