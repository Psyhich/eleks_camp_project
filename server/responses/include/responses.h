#ifndef RESPONSES
#define RESPONSES

#include <string>
#include <utility>

#include "data_containers.h"
#include "results.h"

namespace server {
namespace responses {

class Error {
    std::string message;
public:
    Error(const std::string& message) : message{message} {}
    Error(std::string&& message) noexcept : message{std::move(message)} {}
    auto getMessage() const noexcept {return message;}
};

class GetInitDataResult {
    initializer::DataContainers initData;
public:
    GetInitDataResult(const initializer::DataContainers& initData) : initData{initData} {}
    GetInitDataResult(initializer::DataContainers&& initData) noexcept : initData{std::move(initData)} {}
    auto getInitData() const noexcept {return initData;}
};

class FindResult {
    searcher::Results results;
public:
    FindResult(const searcher::Results& results) : results{results} {}
    FindResult(searcher::Results&& results) noexcept : results{std::move(results)} {}
    auto getResults() const noexcept {return results;}
};

class AddResult {
    bool success;
public:
    AddResult(bool success) : success{success} {}
    bool getSuccess() const noexcept {return success;}
};

class EditResult {
    bool success;
public:
    EditResult(bool success) : success{success} {}
    bool getSuccess() const noexcept {return success;} 

};

class RemoveResult {
    bool success;
public:
    RemoveResult(bool success) : success{success} {}
    bool getSuccess() const noexcept {return success;}
};

} // responses
} // server

#endif // RESPONSES