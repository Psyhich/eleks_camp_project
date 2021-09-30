#include "json_serializer.h"

#include <variant>

#include "nlohmann_extend.h"
#include "response_tag.h"

namespace server {
namespace serializer {

struct JsonSerializer::Process {
    transfer::Pack operator()(const responses::Error& errorResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::error},
                            {"message", errorResponse.getMessage()}};
        return {j.dump(), errorResponse.getClientID()};
    }

    transfer::Pack operator()(const responses::GetInitDataResult& getInitDataResultResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::getInitDataResult},
                            {"initData", getInitDataResultResponse.getInitData()}};
        return {j.dump(), getInitDataResultResponse.getClientID()};
    }

    transfer::Pack operator()(const responses::FindResult& findResultResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::findResult},
                            {"searchResults", findResultResponse.getResults()}};
        return {j.dump(), findResultResponse.getClientID()};
    }

    transfer::Pack operator()(const responses::AddSuccess& addSuccessResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::addSuccess},
                            {"recipeID", addSuccessResponse.getRecipeID()}};
        return {j.dump(), addSuccessResponse.getClientID()};
    }

    transfer::Pack operator()(const responses::EditSuccess& editSuccessResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::editSuccess}};
        return {j.dump(), editSuccessResponse.getClientID()};
    }

    transfer::Pack operator()(const responses::RemoveSuccess& removeSuccessResponse) const {
        nlohmann::json j = {{"responseTag", ResponseTag::removeSuccess}};
        return {j.dump(), removeSuccessResponse.getClientID()};
    }    
};

transfer::Pack JsonSerializer::getPack(const responses::ResponseVar& resp) const {
    return std::visit(Process{}, resp);
}

} // serializer
} // server