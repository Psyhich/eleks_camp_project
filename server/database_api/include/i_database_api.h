#ifndef I_DATABASE_API
#define I_DATABASE_API

#include <optional>

#include "criteria.h"
#include "data_containers.h"
#include "recipe.h"
#include "results.h"

namespace server {
namespace dbAPI {

class IDatabase {
public:
    IDatabase() = default;
    virtual ~IDatabase() = default;

    virtual std::optional<initializer::DataContainers> getInitData() = 0;
    virtual std::optional<searcher::Results> find(const searcher::Criteria& searchCriteria) = 0;

    virtual bool add(const recipe::Recipe& newRecipe) = 0;
    virtual bool edit(const recipe::Recipe& changedRecipe) = 0;
    virtual bool remove(unsigned int id) = 0;
};

}   // dbAPI 
}   // server

#endif // I_DATABASE_API