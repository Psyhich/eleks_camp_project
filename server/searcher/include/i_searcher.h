#ifndef I_SEARCHER
#define I_SEARCHER

#include <optional>

#include "criteria.h"
#include "results.h"

namespace server {
namespace searcher {

class ISearcher {
public:
    virtual ~ISearcher() = default;

    virtual std::optional<Results> find(const Criteria& searchCriteria) const = 0;
};

} // searcher
} // server

#endif // I_SEARCHER