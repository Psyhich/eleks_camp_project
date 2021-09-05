#include "nlohmann_extend.h"

#include <string>
#include <vector>

namespace nlohmann {

// server::initializer::DataContainers converter

server::initializer::DataContainers adl_serializer<server::initializer::DataContainers>::from_json(const json& j){
    return server::initializer::DataContainers(
            j.at("fullCourseSet"),
            j.at("fullCuisineSet"),
            j.at("fullIngredientSet")
        );
}

void adl_serializer<server::initializer::DataContainers>::to_json(json& j, server::initializer::DataContainers initData){
    j["fullCourseSet"] = initData.getFullCourseSet();
    j["fullCuisineSet"] = initData.getFullCuisineSet();
    j["fullIngredientSet"] = initData.getFullIngredientSet();
}

// server::searcher::Criteria converter

server::searcher::Criteria adl_serializer<server::searcher::Criteria>::from_json(const json& j){
    return server::searcher::Criteria(
            j.at("favoriteIDs"),
            j.at("nameSubstring"),
            j.at("course"),
            j.at("cuisine"),
            j.at("ingredientsSubset"),
            j.at("exclusiveIngredients")
        );
}

void adl_serializer<server::searcher::Criteria>::to_json(json& j, server::searcher::Criteria searchCriteria){
    j["favoriteIDs"] = searchCriteria.getFavoriteIDs();
    j["nameSubstring"] = searchCriteria.getNameSubstring();
    j["course"] = searchCriteria.getCourse();
    j["cuisine"] = searchCriteria.getCuisine();
    j["ingredientsSubset"] = searchCriteria.getIngredientsSubset();
    j["exclusiveIngredients"] = searchCriteria.getExclusiveIngredients();
}

// server::recipe::IngredientsList converter

server::recipe::IngredientsList adl_serializer<server::recipe::IngredientsList>::from_json(const json& j){
    auto ingredientNameArray = j.at("ingredientNameArray");
    auto ingredientQuantityArray = j.at("ingredientQuantityArray");
    auto ingredientUnitArray = j.at("ingredientUnitArray");
    server::recipe::IngredientsList ingredients;
    for (size_t i{0}; i<ingredientNameArray.size(); ++i){
        ingredients[ingredientNameArray.at(i)] = {ingredientQuantityArray.at(i), ingredientUnitArray.at(i)};
    }
    return ingredients;
}

void adl_serializer<server::recipe::IngredientsList>::to_json(json& j, server::recipe::IngredientsList ingredients){
    std::vector<std::string> ingredientNameArray;
    std::vector<double> ingredientQuantityArray;
    std::vector<std::string> ingredientUnitArray; 
    for (const auto& [ingredientName, ingredientAmount] : ingredients){
        ingredientNameArray.emplace_back(ingredientName);
        ingredientQuantityArray.emplace_back(ingredientAmount.quantity);
        ingredientUnitArray.emplace_back(ingredientAmount.unit);
    }
    j["ingredientNameArray"] = ingredientNameArray;
    j["ingredientQuantityArray"] = ingredientQuantityArray;
    j["ingredientUnitArray"] = ingredientUnitArray;
}

// server::recipe::Recipe converter

server::recipe::Recipe adl_serializer<server::recipe::Recipe>::from_json(const json& j){
    return server::recipe::Recipe(
        j.at("id"),
        j.at("name"),
        j.at("course"),
        j.at("cuisine"),
        j.at("ingredients"),
        j.at("outCalories"),
        j.at("outWeight"),
        j.at("outPortions"),
        j.at("preparation"),
        j.at("presentation"),
        j.at("remarks")
    );
}

void adl_serializer<server::recipe::Recipe>::to_json(json& j, server::recipe::Recipe recipe){
    j["id"] = recipe.getId();
    j["name"] = recipe.getName();
    j["course"] = recipe.getCourse();
    j["cuisine"] = recipe.getCuisine();
    j["ingredients"] = recipe.getIngredients();
    j["outCalories"] = recipe.getOutCalories();
    j["outWeight"] = recipe.getOutWeight();
    j["outPortions"] = recipe.getOutPortions();
    j["preparation"] = recipe.getPreparation();
    j["presentation"] = recipe.getPresentation();
    j["remarks"] = recipe.getRemarks();
}

// server::searcher::Results converter

server::searcher::Results adl_serializer<server::searcher::Results>::from_json(const json& j){
    return server::searcher::Results(j.at("foundRecipes"));
}

void adl_serializer<server::searcher::Results>::to_json(json& j, server::searcher::Results searchResults){
    j["foundRecipes"] = searchResults.getFoundRecipes();
}

} // nlohmann