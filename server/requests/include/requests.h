#ifndef REQUESTS
#define REQUESTS

#include <utility>

#include "criteria.h"
#include "recipe.h"

namespace server {
namespace requests {

class GetInitData {
public:
    GetInitData() {}
};

class Find {
    searcher::Criteria searchCriteria;
public:
    Find(const searcher::Criteria& searchCriteria) : searchCriteria{searchCriteria} {}
    Find(searcher::Criteria&& searchCriteria) : searchCriteria{std::move(searchCriteria)} {}
    auto getSearchCriteria() const noexcept {return searchCriteria;}
};

class Add {
    recipe::Recipe newRecipe;
public:
    Add(const recipe::Recipe& newRecipe) : newRecipe{newRecipe} {}
    Add(recipe::Recipe&& newRecipe) : newRecipe{std::move(newRecipe)} {}
    auto getNewRecipe() const noexcept {return newRecipe;}
};

class Edit {
    recipe::Recipe changedRecipe;
public:
    Edit(const recipe::Recipe changedRecipe) : changedRecipe{changedRecipe} {}
    Edit(recipe::Recipe&& changedRecipe) : changedRecipe{std::move(changedRecipe)} {}
    auto getChangedRecipe() const noexcept {return changedRecipe;}
};

class Remove {
    const unsigned int id;
public:
    Remove(unsigned int id) : id{id} {}
    auto getId() const noexcept {return id;}
};

} // requests
} // server

#endif // REQUESTS