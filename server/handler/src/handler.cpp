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

    std::optional<responses::ResponseVar> Handler::operator()(const requests::ShutDown& shutDownRequest) const {
        if (shutDownRequest.getClientID()==0){
            return std::nullopt;
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Ви не маєте прав, щоб зупинити сервер.", shutDownRequest.getClientID()));
        }
    }

    std::optional<responses::ResponseVar> Handler::operator()(const requests::GetInitData& getInitDataRequest) const {
        auto initDataOpt = initializer.getInitData();
        if (initDataOpt){
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::GetInitDataResult>, *initDataOpt, getInitDataRequest.getClientID()));
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося одержати дані ініціалізації.", getInitDataRequest.getClientID()));
        }
    }

    std::optional<responses::ResponseVar> Handler::operator()(const requests::Find& findRequest) const {
        auto searchResultsOpt = searcher.find(findRequest.getSearchCriteria());
        if (searchResultsOpt) {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::FindResult>, *searchResultsOpt, findRequest.getClientID()));
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося провести пошук.", findRequest.getClientID())); 
        }
    }

    std::optional<responses::ResponseVar> Handler::operator()(const requests::Add& addRequest) const {
        if (modifier.add(addRequest.getNewRecipe())){
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::AddSuccess>, addRequest.getClientID()));
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося додати рецепт.", addRequest.getClientID()));
        }
    }

    std::optional<responses::ResponseVar> Handler::operator()(const requests::Edit& editRequest) const {
        if (modifier.edit(editRequest.getChangedRecipe())){
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::EditSuccess>, editRequest.getClientID()));
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося змінити рецепт.", editRequest.getClientID()));
        }
    }

    std::optional<responses::ResponseVar> Handler::operator()(const requests::Remove& removeRequest) const {
        if (modifier.remove(removeRequest.getRecipeID())){
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::RemoveSuccess>, removeRequest.getClientID()));
        } else {
            return std::make_optional(responses::ResponseVar(std::in_place_type<responses::Error>, "Не вдалося видалити рецепт.", removeRequest.getClientID()));
        }        
    }

} // namespace handler
} // namespace server