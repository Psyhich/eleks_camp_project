#ifndef NLOHMANN_EXTEND
#define NLOHMANN_EXTEND

#include "json.hpp"

#include "criteria.h"
#include "data_containers.h"
#include "recipe.h"
#include "results.h"

namespace nlohmann {

template<> struct adl_serializer<server::initializer::DataContainers> {
    static server::initializer::DataContainers from_json(const json& j);
    static void to_json(json& j, server::initializer::DataContainers initData);
};

template<> struct adl_serializer<server::searcher::Criteria> {
    static server::searcher::Criteria from_json(const json& j);
    static void to_json(json& j, server::searcher::Criteria searchCriteria);
};

template<> struct adl_serializer<server::recipe::IngredientsList> {
    static server::recipe::IngredientsList from_json(const json& j);
    static void to_json(json& j, server::recipe::IngredientsList ingredients);
};

template<> struct adl_serializer<server::recipe::Recipe> {
    static server::recipe::Recipe from_json(const json& j);
    static void to_json(json& j, server::recipe::Recipe recipe);
};

template<> struct adl_serializer<server::searcher::Results> {
    static server::searcher::Results from_json(const json& j);
    static void to_json(json& j, server::searcher::Results searchResults);
};

} // namespace nlohmann

#endif // NLOHMANN_EXTEND