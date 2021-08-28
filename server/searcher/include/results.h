#ifndef RESULTS_CONTAINER
#define RESULTS_CONTAINER

#include <set>
#include <utility>

#include "recipe.h"

namespace server {
namespace searcher {

    using RecipeSet = std::set<recipe::Recipe>;

    class Results {
        RecipeSet foundRecipes;
    public:
        Results(const RecipeSet& foundRecipes) : foundRecipes{foundRecipes} {}
        Results(RecipeSet&& foundRecipes) noexcept : foundRecipes{std::move(foundRecipes)} {}

        Results(const Results&) = default;
        Results(Results&&) noexcept = default;

        auto getFoundRecipes() const noexcept {return foundRecipes;}
    };

} // searcher
} // server

#endif // RESULTS_CONTAINER