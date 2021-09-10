#ifndef I_SERVER
#define I_SERVER

namespace server {

class IServer {
public:
    virtual ~IServer() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
};

} // namespace server

#endif // I_SERVER