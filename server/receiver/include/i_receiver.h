#ifndef I_RECEIVER
#define I_RECEIVER

#include "requests.h"

namespace server {
namespace receiver {

class IReceiver {
public:
    virtual ~IReceiver() = default;
    
    virtual requests::RequestVar getRequest() const = 0;
};

} // namespace receiver
} // namespace server

#endif // I_RECEIVER