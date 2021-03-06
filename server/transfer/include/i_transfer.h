#ifndef I_TRANSFER
#define I_TRANSFER

#include "pack.h"

namespace server{
namespace transfer{

class ITransfer {
public:
    virtual ~ITransfer() = default;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual Pack getPack() = 0;
    virtual void sendPack(const Pack& pack) = 0;
};

} // namespace transfer
} // namespace server

#endif // I_TRANSFER