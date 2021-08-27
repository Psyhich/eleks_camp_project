#include "recipe.h"

#include <cassert>
#include <utility>

namespace server {
namespace recipe {

Recipe::Recipe (
        unsigned int id,
        const std::string& name,
        const std::string& course,
        const std::string& cuisine,
        const IngredientsList& ingredients,
        double outCalories,
        double outWeight,
        double outPortions,
        const std::string& preparation,
        const std::string& presentation,
        const std::string& remarks
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

Recipe::Recipe (
        unsigned int id,
        const std::string& name,
        const std::string& course,
        const std::string& cuisine,
        const IngredientsList& ingredients,
        double outCalories,
        double outWeight,
        double outPortions,
        const std::string& preparation,
        const std::string& presentation,
        const std::string& remarks
    ) :
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

void Recipe::setOutPortions (double newOutPortions) {
        assert(("Number of portions cannot be <= 0", newOutPortions>0));
        auto proportion = newOutPortions/outPortions;
        outCalories*=proportion;
        outWeight*=proportion;
        for (auto& [name, amount]:ingredients){
            amount.quantity*=proportion;
        }
    }

} // namespace recipe
} // namespace server