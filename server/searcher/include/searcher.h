#ifndef SEARCHER
#define SEARCHER

#include <optional>

#include "criteria.h"
#include "i_database_api.h"
#include "results.h"

namespace server {
namespace searcher {

class Searcher {
    dbAPI::IDataBase& db;
public:
    Searcher(dbAPI::IDataBase& db);
    std::optional<Results> find(const Criteria& searchCriteria) const;
};

} // searcher
} // server

#endif // SEARCHER