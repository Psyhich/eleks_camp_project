#ifndef PACK
#define PACK

#include <string>

namespace server {
namespace transfer {

struct Pack {
    std::string data;
    unsigned int clientID {0};
};

} // namespace transfer
} // namespace server

#endif // PACK