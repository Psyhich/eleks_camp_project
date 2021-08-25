#ifndef DATA_BASE_API
#define DATA_BASE_API

#include <optional>

#include "criteria.h"
#include "data_containers.h"
#include "recipe.h"
#include "results.h"

namespace server {
namespace dbAPI {

class Extractor {
public:
    static std::optional<initializer::DataContainers> getInitData();
    static std::optional<searcher::Results> find(searcher::Criteria searchCriteria);
};

class Modifier {
public:
    static bool add(const recipe::Recipe& newRecipe);
    static bool edit(const recipe::Recipe& changedRecipe);
    static bool makeFavorite(unsigned int id);
    static bool remove(unsigned int id);
};

}   // dbAPI 
}   // server

#endif // DATA_BASE_API