#ifndef COMMON_BASE_TYPES
#define COMMON_BASE_TYPES

namespace CommonBaseTypes {
// This base type can(and should) be parsed into classes
// that are easier to interact
struct Recipe {
  unsigned int id;
  char *name;
  char **tags;
  // Should be changed or be carefull with this
  char **ingredients;
  char **ingredientCounts;
  unsigned long ingredientsCount;

  double onePortionCalories;
  unsigned int outPortions;
  char *recipeText;
};
} // namespace CommonBaseTypes

#endif