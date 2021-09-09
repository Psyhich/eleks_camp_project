#include "json_deserializer.h"

#include <utility>
#include <variant>

#include "nlohmann_extend.h"
#include "request_tag.h"

namespace server {
namespace deserializer {

requests::RequestVar JsonDeserializer::getRequest(const transfer::Pack& inPack) const {
    auto j = nlohmann::json::parse(inPack.data);
    deserializer::RequestTag requestTag = j.at("requestTag");
    switch (requestTag){
        case RequestTag::getInitData : {
            return requests::RequestVar(std::in_place_type<requests::GetInitData>, inPack.clientID);
        }
        case RequestTag::find : {
            return requests::RequestVar(std::in_place_type<requests::Find>, j.at("searchCriteria"), inPack.clientID);
        }
        case RequestTag::add : {
            return requests::RequestVar(std::in_place_type<requests::Add>, j.at("newRecipe"), inPack.clientID);
        }
        case RequestTag::edit : {
            return requests::RequestVar(std::in_place_type<requests::Edit>, j.at("changedRecipe"), inPack.clientID);
        }
        case RequestTag::remove : {
            return requests::RequestVar(std::in_place_type<requests::Remove>, j.at("recipeID"), inPack.clientID);
        }
    }
}

} // namespace deserializer
} // namespace server