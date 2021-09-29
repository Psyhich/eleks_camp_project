#ifndef TRANSFER_RECEIVER
#define TRANSFER_RECEIVER

#include "i_deserializer.h"
#include "i_transfer.h"
#include "requests.h"

#include "i_receiver.h"

namespace server {
namespace receiver {

class RemoteReceiver : public IReceiver {
protected:
    transfer::ITransfer& transfer;
    deserializer::IDeserializer& deserializer;
public:
    RemoteReceiver(transfer::ITransfer& transfer, deserializer::IDeserializer& deserializer);
    virtual ~RemoteReceiver() = default;

    virtual void start() override;
    virtual void stop() override;
    
    virtual requests::RequestVar getRequest() const override;
};

} // namespace receiver
} // namespace server

#endif // TRANSFER_RECEIVER