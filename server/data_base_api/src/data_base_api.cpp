#include "data_base_api.h"

namespace server {
namespace dbAPI {

std::optional<initializer::DataContainers> Extractor::getInitData() {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

std::optional<searcher::Results> Extractor::find(searcher::Criteria searchCriteria) {
    // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
    // note: "nothing found" is not an error
}

bool Modifier::add(const recipe::Recipe& newRecipe) {
    // to be implemented; returns true if success, false if error
}

bool Modifier::edit(const recipe::Recipe& changedRecipe) {
    // to be implemented; returns true if success, false if error
}

bool Modifier::makeFavorite(unsigned int id) {
    // to be implemented; returns true if success, false if error
}

bool Modifier::remove(unsigned int id) {
    // to be implemented; returns true if success, false if error    
}

}   // dbAPI 
}   // server