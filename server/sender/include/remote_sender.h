#ifndef TRANSFER_SENDER
#define TRANSFER_SENDER

#include "i_serializer.h"
#include "i_transfer.h"
#include "responses.h"

#include "i_sender.h"


namespace server {
namespace sender {

class RemoteSender : public ISender {
protected:
    transfer::ITransfer& transfer;
    serializer::ISerializer& serializer;
public:
    RemoteSender(transfer::ITransfer& transfer, serializer::ISerializer& serializer);
    virtual ~RemoteSender() = default;

    virtual void sendResponse(const responses::ResponseVar& response) const override;
};


} // namespace sender
} // namespace server

#endif // TRANSFER_SENDER