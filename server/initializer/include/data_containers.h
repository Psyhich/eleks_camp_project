#ifndef DATA_CONTAINERS
#define DATA_CONTAINERS

#include <set>
#include <string>
#include <utility>

namespace server {
namespace initializer {

using CourseSet = std::set<std::string>;
using CuisineSet = std::set<std::string>;
using IngredientSet = std::set<std::string>;

class DataContainers {
    CourseSet fullCourseSet;
    CuisineSet fullCuisineSet;
    IngredientSet fullIngredientSet;

public:
    DataContainers(
        const CourseSet& fullCourseSet,
        const CuisineSet& fullCuisineSet,
        const IngredientSet& fullIngredientSet
    ) :
        fullCourseSet{fullCourseSet},
        fullCuisineSet{fullCuisineSet},
        fullIngredientSet{fullIngredientSet}
        {}
    
    DataContainers(
        CourseSet&& fullCourseSet,
        CuisineSet&& fullCuisineSet,
        IngredientSet&& fullIngredientSet
    ) noexcept :
        fullCourseSet{std::move(fullCourseSet)},
        fullCuisineSet{std::move(fullCuisineSet)},
        fullIngredientSet{std::move(fullIngredientSet)}
        {}

    DataContainers(const DataContainers&) = default;
    DataContainers(DataContainers&&) noexcept = default;

    CourseSet getFullCourseSet() const noexcept {return fullCourseSet;}
    CuisineSet getFullCuisineSet() const noexcept {return fullCuisineSet;}
    IngredientSet getFullIngredientSet() const noexcept {return fullIngredientSet;}
};

} // namespace initializer
} // namespace server

#endif // DATA_CONTAINERS
