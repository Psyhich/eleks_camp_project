#ifndef SEARCHER
#define SEARCHER

#include <optional>

#include "criteria.h"
#include "i_database_api.h"
#include "results.h"

#include "i_searcher.h"

namespace server {
namespace searcher {

class Searcher : public ISearcher {
protected:
    dbAPI::IDatabase& db;
public:
    Searcher(dbAPI::IDatabase& db);
    virtual ~Searcher() = default;

    virtual std::optional<Results> find(const Criteria& searchCriteria) const override;
};

} // searcher
} // server

#endif // SEARCHER