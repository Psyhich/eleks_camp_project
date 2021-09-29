#include "handler.h"

#include <utility>

namespace server{
namespace handler {

    Handler::Handler(
        initializer::IInitializer& initializer,
        searcher::ISearcher& searcher,
        modifier::IModifier& modifier
    ) :
        initializer{initializer},
        searcher{searcher},
        modifier{modifier}
    {}

    responses::ResponseVar Handler::operator()(const requests::Error& errorRequest) const {
        return responses::ResponseVar(std::in_place_type<responses::Error>, "Invalid request format.", errorRequest.getClientID());
    }

    responses::ResponseVar Handler::operator()(const requests::GetInitData& getInitDataRequest) const {
        auto initDataOpt = initializer.getInitData();
        if (initDataOpt){
            return responses::ResponseVar(std::in_place_type<responses::GetInitDataResult>, *initDataOpt, getInitDataRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Failed to fetch initialization data.", getInitDataRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Find& findRequest) const {
        auto searchResultsOpt = searcher.find(findRequest.getSearchCriteria());
        if (searchResultsOpt) {
            return responses::ResponseVar(std::in_place_type<responses::FindResult>, *searchResultsOpt, findRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Failed to perform search.", findRequest.getClientID()); 
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Add& addRequest) const {
        if (modifier.add(addRequest.getNewRecipe())){
            return responses::ResponseVar(std::in_place_type<responses::AddSuccess>, addRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Failed to add recipe.", addRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Edit& editRequest) const {
        if (modifier.edit(editRequest.getChangedRecipe())){
            return responses::ResponseVar(std::in_place_type<responses::EditSuccess>, editRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Failed to modify recipe.", editRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Remove& removeRequest) const {
        if (modifier.remove(removeRequest.getRecipeID())){
            return responses::ResponseVar(std::in_place_type<responses::RemoveSuccess>, removeRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Failed to delete recipe.", removeRequest.getClientID());
        }        
    }

} // namespace handler
} // namespace server