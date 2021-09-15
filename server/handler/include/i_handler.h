#ifndef I_HANDLER
#define I_HANDLER

#include "requests.h"
#include "responses.h"

namespace server{
namespace handler {

class IHandler {
public:
    virtual ~IHandler() = default;

    virtual responses::ResponseVar operator()(const requests::Error& errorRequest) const = 0;
    virtual responses::ResponseVar operator()(const requests::GetInitData& getInitDataRequest) const = 0;
    virtual responses::ResponseVar operator()(const requests::Find& findRequest) const = 0;
    virtual responses::ResponseVar operator()(const requests::Add& addRequest) const = 0;
    virtual responses::ResponseVar operator()(const requests::Edit& editRequest) const = 0;
    virtual responses::ResponseVar operator()(const requests::Remove& removeRequest) const = 0;
};

} // namespace handler
} // namespace server


#endif // I_HANDLER