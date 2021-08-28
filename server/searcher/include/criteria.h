#ifndef CRITERIA
#define CRITERIA

#include <set>
#include <string>

namespace server {
namespace searcher {

class Criteria {
    std::set<unsigned int> favoriteIDs;
    std::string nameSubstring;
    std::string course;
    std::string cuisine;
    std::set<std::string> ingredientsSubset;
    bool exclusiveIngredients;

public:
    Criteria(
        const std::set<unsigned int>& favoriteIDs,
        const std::string& nameSubstring,
        const std::string& course,
        const std::string& cuisine,
        const std::set<std::string> ingredientsSubset,
        bool exclusiveIngredients = false
    ) :
        favoriteIDs{favoriteIDs},
        nameSubstring{nameSubstring},
        course {course},
        cuisine {cuisine},
        ingredientsSubset {ingredientsSubset},
        exclusiveIngredients {exclusiveIngredients}
        {}

    Criteria(
        std::set<unsigned int>& favoriteIDs,
        std::string& nameSubstring,
        std::string& course,
        std::string& cuisine,
        std::set<std::string> ingredientsSubset,
        bool exclusiveIngredients = false
    ) noexcept :
        favoriteIDs{std::move(favoriteIDs)},
        nameSubstring{std::move(nameSubstring)},
        course {std::move(course)},
        cuisine {std::move(cuisine)},
        ingredientsSubset {std::move(ingredientsSubset)},
        exclusiveIngredients {exclusiveIngredients}
        {}

        Criteria(const Criteria&) = default;
        Criteria(Criteria&&) noexcept = default;

        auto getFavoriteIDs() const noexcept {return favoriteIDs;}
        auto getNameSubstring() const noexcept {return nameSubstring;}
        auto getCourse() const noexcept {return course;}
        auto getCuisine() const noexcept {return cuisine;}
        auto getIngredientsSubset() const noexcept {return ingredientsSubset;}
        auto getExclusiveIngredients() const noexcept {return exclusiveIngredients;}
};

} // searcher
} // server

#endif // CRITERIA