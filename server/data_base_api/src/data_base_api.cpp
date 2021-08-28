#include "data_base_api.h"

namespace server {
namespace dbAPI {

DataBase::DataBase() {
    // to be implemented
    // data base initialization
}

DataBase::~DataBase() {
    // to be implemented
    // data base close-down probably goes here
}

std::optional<initializer::DataContainers> DataBase::getInitData() {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

std::optional<searcher::Results> DataBase::find(const searcher::Criteria& searchCriteria) {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

bool DataBase::add(const recipe::Recipe& newRecipe) {
    // to be implemented; returns true if success, false if error
}

bool DataBase::edit(const recipe::Recipe& changedRecipe) {
    // to be implemented; returns true if success, false if error
}

bool DataBase::remove(unsigned int id) {
    // to be implemented; returns true if success, false if error    
}

}   // dbAPI 
}   // server