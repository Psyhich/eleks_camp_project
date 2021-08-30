#ifndef DATABASE_API
#define DATABASE_API

#include <optional>

#include "criteria.h"
#include "data_containers.h"
#include "recipe.h"
#include "results.h"

#include "i_database_api.h"

namespace server {
namespace dbAPI {

class DataBase : public IDataBase{
    // state members may be added if necessary
public:
    DataBase();
    virtual ~DataBase();

    std::optional<initializer::DataContainers> getInitData() override;
    std::optional<searcher::Results> find(const searcher::Criteria& searchCriteria) override;

    bool add(const recipe::Recipe& newRecipe) override;
    bool edit(const recipe::Recipe& changedRecipe) override;
    bool remove(unsigned int id) override;
};

}   // dbAPI 
}   // server

#endif // DATABASE_API