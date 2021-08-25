#ifndef RECIPE
#define RECIPE

#include <string>
#include <unordered_map>

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
    std::string course;           // appetizer, main course, drink etc., decided not to make it enum after all
    std::string cuisine;          // nationality of the cuisine
    IngredientsList ingredients;
    double outCalories;
    double outWeight;
    double outPortions;           // type double provides for the case of fractional portions
    std::string preparation;
    std::string presentation;
    std::string remarks;
    bool favorite;                // we must be able to mark some recipes as favorite

public:
    Recipe(
        unsigned int id,
        const std::string& name,
        const std::string& course,
        const std::string& cuisine,
        const IngredientsList& ingredients,
        double outCalories,
        double outWeight,
        double outPortions,
        const std::string& preparation,
        const std::string& presentation = "",
        const std::string& remarks = "",
        bool favorite = false
    );

    Recipe(
        unsigned int id,
        std::string&& name,
        std::string&& course,
        std::string&& cuisine,
        IngredientsList&& ingredients,
        double outCalories,
        double outWeight,
        double outPortions,
        std::string&& preparation,
        std::string&& presentation = "",
        std::string&& remarks = "",
        bool favorite = false
    ) noexcept;    

    explicit Recipe (const Recipe& otherRecipe) = default;     
    explicit Recipe (Recipe&& otherRecipe) noexcept = default;


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
    auto getFavorite() const noexcept {return favorite;}

    bool operator<(const Recipe& other) const noexcept {return id < other.id;}

    void setOutPortions (double newOutPortions);
};

} // namespace recipe
} // namespace server

#endif // RECIPE