#include "tcp_transfer.h"

#include <algorithm>
#include <chrono>
#include <utility>

namespace server {
namespace transfer {

TCPTransfer::TCPTransfer(unsigned short port)
    :
    port{port} {
}

TCPTransfer::~TCPTransfer() {
    stop();
}
     
void TCPTransfer::start() {
    if (stopFlag.load()) {
        inQueue.start();
        clients.push_back(std::make_unique<Client>(*this, nullptr, 0));
        ioContext.reset(new asio::io_context);
        work.reset(new asio::io_context::work(*ioContext));
        acceptor.reset(new Acceptor(*this));
        acceptor->start();
        makeIOContextRunPool();
        stopFlag.store(false);
        logInfo ("Server started.");
    }
}

void TCPTransfer::stop() {
    if (!stopFlag.load()) {
        acceptor->stop();
        clearAllClients();
        inQueue.stop();
        work.reset();
        ioContext->stop();
        destroyIOContextRunPool();
        stopFlag.store(true);
        logInfo("Server stopped.");
    }
}

Pack TCPTransfer::getPack() {
    inQueue.wait();
    if (!inQueue.empty()) {
        return inQueue.popGet();
    }
    else {
        return { "", 0 };
    }
}

void TCPTransfer::sendPack(const Pack& outPack) {
    if (outPack.clientID > 0 && outPack.clientID < clients.size()) {
        clients.at(outPack.clientID)->sendMessage(outPack.data);
    }
}

void TCPTransfer::makeIOContextRunPool() {
    unsigned int poolSize = std::max(minThreadPoolSize, std::thread::hardware_concurrency());
    for (unsigned int i{ 0 }; i < poolSize; ++i) {
        ioContextRunPool.push_back(std::make_unique<std::thread>([this] {ioContext->run(); }));
    }
}

void TCPTransfer::destroyIOContextRunPool() {
    for (auto& thr : ioContextRunPool) {
        thr->join();
    }
    ioContextRunPool.clear();
}

void TCPTransfer::clearAllClients() {
    for (size_t i{ 0 }; i < clients.size(); ++i) {
        clients.at(i)->stop();
    }
    clients.clear();
    clientIDTable.clear();
    clientIDCounter = 1;
}

void TCPTransfer::logError(const asio::error_code& ec, const std::string& intro) {
    output.error(
        intro+
        "Error code: "+
        std::to_string(ec.value())+"; "+
        "error message: \""+
        ec.message()+"\"");
}

void TCPTransfer::logInfo(const std::string& info) {
    output.info(info);
}


TCPTransfer::Acceptor::Acceptor(TCPTransfer& transfer)
    :
    transfer{transfer},
    acceptor{ *transfer.ioContext, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), transfer.port) }
{}

TCPTransfer::Acceptor::~Acceptor() {
    stop();
}

void TCPTransfer::Acceptor::start() {
    acceptor.listen();
    acceptClient();
}

void TCPTransfer::Acceptor::stop() {
    asio::error_code ec;
    acceptor.close(ec);
    handleError(ec);
}

void TCPTransfer::Acceptor::acceptClient() {
    freshSock.reset(new asio::ip::tcp::socket(*transfer.ioContext));
    acceptor.async_accept(
        *freshSock,
        [this](const asio::error_code& ec) {
            onAccept(ec);
        }
    );
}

void TCPTransfer::Acceptor::onAccept(const asio::error_code& ec) {
    if (!acceptor.is_open()) {
        return;
    } else if (ec) {
        handleError(ec);
    } else {
        handleClient();
    }
    acceptClient();
}

void TCPTransfer::Acceptor::handleClient() {
    auto freshEndpoint = freshSock->remote_endpoint();
    if (transfer.clientIDTable.find(freshEndpoint) != transfer.clientIDTable.end()) {
        auto& currentClient = transfer.clients.at(transfer.clientIDTable.at(freshEndpoint));
        currentClient->stop();
        freshSock.swap(currentClient->getSocket());
        freshSock.reset();
        currentClient->start();
        transfer.logInfo("Client " + std::to_string(transfer.clientIDTable.at(freshEndpoint)) + " reconnected."); // temporary
    }
    else {
        auto freshClientID = transfer.clientIDCounter++;
        transfer.clientIDTable.insert({ freshEndpoint, freshClientID });
        transfer.clients.push_back(std::make_unique<Client>(transfer, std::move(freshSock), freshClientID));
        freshSock.reset();
        transfer.clients.at(freshClientID)->start();
        transfer.logInfo("Client " + std::to_string(freshClientID) + " connected."); // temporary
    }
}

void TCPTransfer::Acceptor::handleError(const asio::error_code& ec) {
    if (ec && ec != asio::error::operation_aborted) {
        transfer.logError(ec);
    }
}


TCPTransfer::Client::Client(TCPTransfer& transfer, SocketPtr&& socket, unsigned int id) noexcept
    :
    transfer {transfer},
    socket {std::move(socket)},
    id {id}
{}

TCPTransfer::Client::~Client() {
    stop();
}

void TCPTransfer::Client::start() {
    if (stopFlag.load()) {
        stopFlag.store(false);
        runFlag.store(true);
        outQueue.start();
        readInMessage();
    }
}

void TCPTransfer::Client::stop() {
    if (!stopFlag.load()) {
        stopFlag.store(true);
        disconnect();
        std::unique_lock finishLock(finishMut);
        finishCV.wait(finishLock, [this] {return !runFlag.load(); });
    }
}

void TCPTransfer::Client::sendMessage(const std::string& outMessage) {
    outQueue.push(outMessage);
}

void TCPTransfer::Client::readInMessage() {
    asio::async_read_until(
        *socket,
        inBuff,
        messageDelimiter,
        [this](const asio::error_code& ec, size_t bytesRead) {
            onMessageRead(ec, bytesRead);
        }
    );
}

void TCPTransfer::Client::onMessageRead(const asio::error_code& ec, size_t bytesRead) {
    if (ec) {
        handleError(ec);
        finish();
        return;
    }
    processInMessage();
    if (outMessage.empty()) {
        finish();
        return;
    }
    writeOutMessage();
}

void TCPTransfer::Client::processInMessage() {
    std::string inMessage(asio::buffers_begin(inBuff.data()), asio::buffers_end(inBuff.data()));
    inBuff.consume(inBuff.size());
    inMessage.pop_back();
    transfer.inQueue.push(transfer::Pack{ inMessage, id });
    getOutMessage();
    if (!outMessage.empty()) {
        outMessage.push_back(messageDelimiter);
    }
}

void TCPTransfer::Client::getOutMessage() {
    outQueue.wait();
    if (!outQueue.empty()) {
        outMessage = outQueue.popGet();
    }
}

void TCPTransfer::Client::writeOutMessage() {
    asio::async_write(
        *socket,
        asio::buffer(outMessage),
        [this](const asio::error_code& ec, size_t bytesWritten) {
            onMessageWritten(ec, bytesWritten);
        }
    );
}

void TCPTransfer::Client::onMessageWritten(const asio::error_code& ec, size_t bytesWritten) {
    if (ec) {
        handleError(ec);
    }
    transfer.logInfo("Bytes written to client "+ std::to_string(id)+": "+std::to_string(bytesWritten)); // temporary
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    finish();
}

void TCPTransfer::Client::handleError(const asio::error_code& ec) {
    if (ec && (ec != asio::error::operation_aborted && ec!= asio::error::bad_descriptor)) {
        transfer.logError(ec);
    }
}

void TCPTransfer::Client::finish() {
    if (!stopFlag.load()) {
        disconnect();
        stopFlag.store(true);
    }
    outQueue.stop();
    inBuff.consume(inBuff.size());
    outMessage.clear();
    runFlag.store(false);
    transfer.logInfo("Client " + std::to_string(id) + " disconnected."); // temporary
    finishCV.notify_one();
}

void TCPTransfer::Client::disconnect() {
    if (socket && socket->is_open()) {
        asio::error_code ec;
        socket->cancel(ec);
        handleError(ec);
        socket->shutdown(asio::ip::tcp::socket::shutdown_both, ec);
        handleError(ec);
        socket->close(ec);
        handleError(ec);
    }
}

} // namespace transfer
} // namespace server