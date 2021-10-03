#ifndef TCP_TRANSFER
#define TCP_TRANSFER

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif // _WIN32

#define ASIO_STANDALONE

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "asio.hpp"
#include "data_queue.h"
#include "indexed_container.h"
#include "pack.h"
#include "server_output.h"

#include "i_transfer.h"

namespace server {
namespace transfer{

class TCPTransfer: public ITransfer {
    static constexpr int queueTimeoutMs = 1000;
    static constexpr unsigned int minThreadPoolSize = 2;

    class Acceptor;
    class Client;

    using PackQueue = helpers::DataQueue<Pack, queueTimeoutMs>;
    using IDTable = std::map<asio::ip::tcp::endpoint, unsigned int>;
    using ClientContainer = helpers::IndexedContainer<std::unique_ptr<Client>>;
    using WorkPtr = std::unique_ptr<asio::io_context::work>;
    using IOContextPtr = std::unique_ptr<asio::io_context>;
    using AcceptorPtr = std::unique_ptr<Acceptor>;
    using ThreadPool = std::vector<std::unique_ptr<std::thread>>;

    using SocketPtr = std::unique_ptr<asio::ip::tcp::socket>;

protected:
    std::atomic<bool> stopFlag{true};

    unsigned int clientIDCounter{1};
    IDTable clientIDTable;
    ClientContainer clients;
    PackQueue inQueue;
    IOContextPtr ioContext;
    WorkPtr work;
    AcceptorPtr acceptor;
    ThreadPool ioContextRunPool;
    unsigned short port;
    
 public:
    TCPTransfer(unsigned short port);
    virtual ~TCPTransfer();

    virtual void start() override;
    virtual void stop() override;

    virtual Pack getPack() override;
    virtual void sendPack(const Pack& outPack) override;

protected:
    void makeIOContextRunPool();
    void destroyIOContextRunPool();
    void clearAllClients();

    void logError (const asio::error_code& ec, const std::string& intro = "");  // temporary
    void logInfo(const std::string& info);                                      // temporary
};

class TCPTransfer::Acceptor {
protected:
    transfer::TCPTransfer& transfer;
    asio::ip::tcp::acceptor acceptor;

    SocketPtr freshSock;

public:
    Acceptor(transfer::TCPTransfer& transfer);
    ~Acceptor();

    void start();
    void stop();

protected:
    void acceptClient();
    void onAccept(const asio::error_code& ec);
    void handleClient();
    void handleError(const asio::error_code& ec);
};

class TCPTransfer::Client {
    static constexpr char messageDelimiter = '\0';

    using StringQueue = helpers::DataQueue<std::string, queueTimeoutMs>;

protected:
    std::atomic<bool> stopFlag{true};
    std::atomic<bool> runFlag{false};
    std::mutex finishMut;
    std::condition_variable finishCV;


    TCPTransfer& transfer;
    SocketPtr socket;
    StringQueue outQueue;
    unsigned int id;

    asio::streambuf inBuff;
    std::string outMessage;

public:
    Client(TCPTransfer& transfer, SocketPtr&& socket, unsigned int id) noexcept;
    ~Client();

    void start();
    void stop();

    void sendMessage(const std::string& outMessage);

    SocketPtr& getSocket() {return socket;}

protected:
    void readInMessage();
    void onMessageRead(const asio::error_code& ec, size_t bytesRead);
    void processInMessage();
    void getOutMessage();
    void writeOutMessage();
    void onMessageWritten(const asio::error_code& ec, size_t bytesWritten);
    void handleError(const asio::error_code& ec);
    void finish();
    void disconnect();
};

} // namespace transfer
} // namespace server

#endif // TCP_TRANSFER