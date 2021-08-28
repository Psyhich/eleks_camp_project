#include "searcher.h"

namespace server{
namespace searcher{

Searcher::Searcher(dbAPI::IDataBase& db) : db{db} {}

std::optional<Results> Searcher::find(const Criteria& searchCriteria) const {
    return db.find(searchCriteria);
}

} // namespace searcher
} // namespace server


