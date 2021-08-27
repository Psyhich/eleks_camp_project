#ifndef RECIPE
#define RECIPE

#include <string>
#include <unordered_map>
#include <utility>

namespace server {
namespace recipe {

struct IngredientAmount{
    double quantity;
    std::string unit;
};

using IngredientsList = std::unordered_map<std::string, IngredientAmount>;

class Recipe {
    unsigned int id;              // 0 value should be reserved to indicate a new recipe to be added
    std::string name;
    std::string course;           // appetizer, main course, drink etc.
    std::string cuisine;          // nationality of the cuisine
    IngredientsList ingredients;
    double outCalories;
    double outWeight;
    unsigned int outPortions;    
    std::string preparation;
    std::string presentation;
    std::string remarks;

public:
    Recipe(
        unsigned int id,
        const std::string& name,
        const std::string& course,
        const std::string& cuisine,
        const IngredientsList& ingredients,
        double outCalories,
        double outWeight,
        unsigned int outPortions,
        const std::string& preparation,
        const std::string& presentation = "",
        const std::string& remarks = ""
    ) :
        id {id},
        name {name},
        course {course},
        cuisine {cuisine},
        ingredients {ingredients},
        outCalories {outCalories},
        outWeight {outWeight},
        outPortions {outPortions},
        preparation {preparation},
        presentation {presentation},
        remarks {remarks}
        {}

    Recipe(
        unsigned int id,
        std::string&& name,
        std::string&& course,
        std::string&& cuisine,
        IngredientsList&& ingredients,
        double outCalories,
        double outWeight,
        unsigned int outPortions,
        std::string&& preparation,
        std::string&& presentation = "",
        std::string&& remarks = ""
    ) noexcept :
        id {id},
        name {std::move(name)},
        course {std::move(course)},
        cuisine {std::move(cuisine)},
        ingredients {std::move(ingredients)},
        outCalories {outCalories},
        outWeight {outWeight},
        outPortions {outPortions},
        preparation {std::move(preparation)},
        presentation {std::move(presentation)},
        remarks {std::move(remarks)}
        {}    

    explicit Recipe (const Recipe&) = default;     
    explicit Recipe (Recipe&&) noexcept = default;

    auto getId() const noexcept {return id;}
    auto getName() const noexcept {return name;}
    auto getCourse() const noexcept {return course;}
    auto getCuisine() const noexcept {return cuisine;}
    auto getIngredients() const noexcept {return ingredients;}
    auto getOutCalories() const noexcept {return outCalories;}
    auto getOutWeight() const noexcept {return outWeight;}
    auto getOutPortions() const noexcept {return outPortions;}
    auto getPreparation() const noexcept {return preparation;}
    auto getPresentation() const noexcept {return presentation;}
    auto getRemarks() const noexcept {return remarks;}

    bool operator<(const Recipe& other) const noexcept {return id < other.id;}
};

} // namespace recipe
} // namespace server

#endif // RECIPE