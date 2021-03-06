#ifndef REQUESTS
#define REQUESTS

#include <utility>
#include <variant>

#include "criteria.h"
#include "recipe.h"

namespace server {
namespace requests {

class Request {
    unsigned int clientID{0};
protected:
    Request(unsigned int clientID) : clientID {clientID} {}
public:
    auto getClientID() const noexcept {return clientID;}
};

class Error : public Request {
public:
    Error(unsigned int clientID) : Request(clientID) {}
};

class GetInitData : public Request {
public:
    GetInitData(unsigned int clientID) : Request(clientID) {}
};

class Find : public Request {
    searcher::Criteria searchCriteria;
public:
    Find(const searcher::Criteria& searchCriteria, unsigned int clientID)
        :
        Request(clientID),
        searchCriteria{searchCriteria}
    {}

    Find(searcher::Criteria&& searchCriteria, unsigned int clientID) noexcept
        :
        Request (clientID),
        searchCriteria{std::move(searchCriteria)}
    {}

    auto getSearchCriteria() const noexcept {return searchCriteria;}
};

class Add : public Request {
    recipe::Recipe newRecipe;
public:
    Add(const recipe::Recipe& newRecipe, unsigned int clientID)
        :
        Request(clientID),
        newRecipe{newRecipe}
    {}

    Add(recipe::Recipe&& newRecipe, unsigned int clientID) noexcept
        :
        Request(clientID),
        newRecipe{std::move(newRecipe)}
    {}

    auto getNewRecipe() const noexcept {return newRecipe;}
};

class Edit : public Request {
    recipe::Recipe changedRecipe;
public:
    Edit(const recipe::Recipe& changedRecipe, unsigned int clientID)
        :
        Request(clientID),
        changedRecipe{changedRecipe}
    {}

    Edit(recipe::Recipe&& changedRecipe, unsigned int clientID) noexcept
        :
        Request(clientID),
        changedRecipe{std::move(changedRecipe)}
    {}
    auto getChangedRecipe() const noexcept {return changedRecipe;}
};

class Remove : public Request {
    unsigned int recipeID;
public:
    Remove(unsigned int recipeID, unsigned int clientID)
        :
        Request(clientID),
        recipeID{recipeID}
    {}

    auto getRecipeID() const noexcept {return recipeID;}
};

using RequestVar = std::variant<Error, GetInitData, Find, Add, Edit, Remove>;

} // requests
} // server

#endif // REQUESTS