#ifndef DATA_BASE_API
#define DATA_BASE_API

#include <optional>

#include "criteria.h"
#include "data_containers.h"
#include "recipe.h"
#include "results.h"

#include "i_data_base_api.h"

namespace server {
namespace dbAPI {

class DataBase : public IDataBase{
    // state members may be added if necessary
public:
    DataBase();
    virtual ~DataBase();

    std::optional<initializer::DataContainers> getInitData() override;
    std::optional<searcher::Results> find(searcher::Criteria searchCriteria) override;

    bool add(const recipe::Recipe& newRecipe) override;
    bool edit(const recipe::Recipe& changedRecipe) override;
    bool remove(unsigned int id) override;
};

}   // dbAPI 
}   // server

#endif // DATA_BASE_API