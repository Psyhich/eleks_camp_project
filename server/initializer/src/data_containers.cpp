#include "data_containers.h"

#include <utility>

namespace server {
namespace initializer {

DataContainers::DataContainers(
    const CourseSet& fullCourseSet,
    const CuisineSet& fullCuisineSet,
    const IngredientSet& fullIngredientSet
) :
    fullCourseSet{fullCourseSet},
    fullCuisineSet{fullCuisineSet},
    fullIngredientSet{fullIngredientSet}
    {}

DataContainers::DataContainers(
    CourseSet&& fullCourseSet,
    CuisineSet&& fullCuisineSet,
    IngredientSet&& fullIngredientSet
) :
    fullCourseSet{std::move(fullCourseSet)},
    fullCuisineSet{std::move(fullCuisineSet)},
    fullIngredientSet{std::move(fullIngredientSet)}
    {}


} // namespace initializer
} // namespace server