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
        return responses::ResponseVar(std::in_place_type<responses::Error>, "Хибний формат запиту.");
    }

    responses::ResponseVar Handler::operator()(const requests::GetInitData& getInitDataRequest) const {
        auto initDataOpt = initializer.getInitData();
        if (initDataOpt){
            return responses::ResponseVar(std::in_place_type<responses::GetInitDataResult>, *initDataOpt, getInitDataRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося одержати дані ініціалізації.", getInitDataRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Find& findRequest) const {
        auto searchResultsOpt = searcher.find(findRequest.getSearchCriteria());
        if (searchResultsOpt) {
            return responses::ResponseVar(std::in_place_type<responses::FindResult>, *searchResultsOpt, findRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося провести пошук.", findRequest.getClientID()); 
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Add& addRequest) const {
        if (modifier.add(addRequest.getNewRecipe())){
            return responses::ResponseVar(std::in_place_type<responses::AddSuccess>, addRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося додати рецепт.", addRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Edit& editRequest) const {
        if (modifier.edit(editRequest.getChangedRecipe())){
            return responses::ResponseVar(std::in_place_type<responses::EditSuccess>, editRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося змінити рецепт.", editRequest.getClientID());
        }
    }

    responses::ResponseVar Handler::operator()(const requests::Remove& removeRequest) const {
        if (modifier.remove(removeRequest.getRecipeID())){
            return responses::ResponseVar(std::in_place_type<responses::RemoveSuccess>, removeRequest.getClientID());
        } else {
            return responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося видалити рецепт.", removeRequest.getClientID());
        }        
    }

} // namespace handler
} // namespace server