#include "database_api.h"

namespace server {
namespace dbAPI {

Database::Database() {
    // to be implemented
    // data base initialization
}

Database::~Database() {
    // to be implemented
    // data base close-down probably goes here
}

std::optional<initializer::DataContainers> Database::getInitData() {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

std::optional<searcher::Results> Database::find(const searcher::Criteria& searchCriteria) {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

bool Database::add(const recipe::Recipe& newRecipe) {
    // to be implemented; returns true if success, false if error
}

bool Database::edit(const recipe::Recipe& changedRecipe) {
    // to be implemented; returns true if success, false if error
}

bool Database::remove(unsigned int id) {
    // to be implemented; returns true if success, false if error    
}

}   // dbAPI 
}   // server