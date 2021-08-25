#ifndef CRITERIA
#define CRITERIA

#include <set>
#include <string>

namespace server {
namespace searcher {

struct Criteria {
    bool favorite{true};
    std::string nameSubstring;
    std::string course;
    std::string cuisine;
    std::set<std::string> ingredientsSubset;
    bool exclusiveIngredients;
};

} // searcher
} // server

#endif // CRITERIA