#ifndef RESPONSES
#define RESPONSES

#include <string>
#include <utility>
#include <variant>

#include "data_containers.h"
#include "results.h"

namespace server {
namespace responses {

class Response {
    unsigned int clientID{0};
protected:
    Response(unsigned int clientID) : clientID {clientID} {}
public:
    auto getClientID() const noexcept {return clientID;}
};


class Error : public Response {
    std::string message;
public:
    Error(const std::string& message, unsigned int clientID)
        :
        Response(clientID),
        message{message}
    {}

    Error(std::string&& message, unsigned int clientID) noexcept
        :
        Response(clientID),
        message{std::move(message)}
    {}

    auto getMessage() const noexcept {return message;}
};

class GetInitDataResult : public Response {
    initializer::DataContainers initData;
public:
    GetInitDataResult(const initializer::DataContainers& initData, unsigned int clientID)
        :
        Response(clientID),
        initData{initData}
    {}

    GetInitDataResult(initializer::DataContainers&& initData, unsigned int clientID) noexcept
        :
        Response (clientID),
        initData{std::move(initData)}
    {}

    auto getInitData() const noexcept {return initData;}
};

class FindResult : public Response {
    searcher::Results searchResults;
public:
    FindResult(const searcher::Results& searchResults, unsigned int clientID)
        :
        Response(clientID),
        searchResults{searchResults}
    {}

    FindResult(searcher::Results&& searchResults, unsigned int clientID) noexcept
        :
        Response(clientID),
        searchResults{std::move(searchResults)}
    {}

    auto getResults() const noexcept {return searchResults;}
};

class AddSuccess : public Response {
public:
    AddSuccess(unsigned int clientID) : Response(clientID) {}
};

class EditSuccess : public Response {
public:
    EditSuccess(unsigned int clientID) : Response(clientID) {}
};

class RemoveSuccess : public Response {
public:
    RemoveSuccess(unsigned int clientID) : Response(clientID) {}
};

using ResponseVar = std::variant<Error, GetInitDataResult, FindResult, AddSuccess, EditSuccess, RemoveSuccess>;

} // responses
} // server

#endif // RESPONSES