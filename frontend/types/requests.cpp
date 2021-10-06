#include "requests.h"

using namespace BaseTypes::Requests;

// SearchQueryRequest class
QString SearchQuery::toJSONString() {
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

server::requests::RequestVar SearchQuery::translate() {
	std::set<unsigned int> favoriteIDs;
	for(auto id : favoriteIDs){
	  favoriteIDs.insert(id);
	}

	std::string course;
	if(courses.size() > 0) {
	  course = courses.values()[0].toStdString();
	}
	std::string cusine;
	if(cusines.size() > 0) {
	  cusine = cusines.values()[0].toStdString();
	}
	std::set<std::string> ingredients;
	for(auto ingredient : this->ingredients){
		ingredients.insert(ingredient.toStdString());
	}

	return server::requests::Find(server::searcher::Criteria(
					favoriteIDs,
					searchSubtring.toStdString(),
					course,
					cusine,
					ingredients,
					searchExclusively
				), 1);
}

// AddRecipeRequest class
QString AddRecipeRequest::toJSONString(){
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

server::requests::RequestVar AddRecipeRequest::translate() {
	return server::requests::Add(this->recipeToAdd->translateToServer(), 1);
}

// EditRecipeRequest class
QString EditRecipeRequest::toJSONString() {
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

server::requests::RequestVar EditRecipeRequest::translate() {
  return server::requests::Edit( this->editedRecipe->translateToServer(), 1);
}

// RemoveRecipeRequest class
QString RemoveRecipeRequest::toJSONString(){
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

server::requests::RequestVar RemoveRecipeRequest::translate() {
  return server::requests::Remove(recipeIDToRemove, 1);
}

// GetInitDataRequest
QString GetInitDataRequest::toJSONString() {
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}
server::requests::RequestVar GetInitDataRequest::translate() {
  return server::requests::GetInitData(1);
}

//Error class
QString Error::toJSONString() {
  throw std::runtime_error("NOT IMPLEMENTED"); // TODO implement
}

server::requests::RequestVar Error::translate() {
  return server::requests::Error(1);
}
