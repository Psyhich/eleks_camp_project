#ifndef DATABASE_API
#define DATABASE_API

#include <optional>
#include <iostream>
#include <vector>

#include "SQLiteCpp/SQLiteCpp.h"

#include "i_database_api.h"

namespace server {
namespace dbAPI {

using string = std::string;

class Database : public IDatabase{
    // state members may be added if necessary
public:
    Database();
    virtual ~Database();

    std::optional<initializer::DataContainers> getInitData() override;
    std::optional<searcher::Results> find(const searcher::Criteria& searchCriteria) override;

    unsigned int add(const recipe::Recipe& newRecipe) override;
    bool edit(const recipe::Recipe& changedRecipe) override;
    bool remove(unsigned int id) override;

private:
    SQLite::Database db;

    //time that database wait until return SQLITE_BUSY
    static constexpr unsigned int busyTime = 100;

    //names are used only to create tables
    static constexpr char databaseName[] = "cookbook.db";
    static constexpr char coursesTableName[] = "courses";
    static constexpr char cuisinesTableName[] = "cuisines";
    static constexpr char recipesTableName[] = "recipes";
    static constexpr char ingredientsTableName[] = "ingredients";
    static constexpr char unitsTableName[] = "units";
    static constexpr char recipeIngredientsTableName[] = "recipe_ingredients";

    void createCoursesTable();
    void createCuisinesTable();
    void createRecipesTable();
    void createIngredientsTable();
    void createUnitsTable();
    void createRecipeIngredientsTable();

    //default ingredient unit
    static constexpr char defaultUnit[] = "g";
    void insertDefaultUnit();
    bool containsDefaultUnit();

    enum class ItemType {
        COURSE, CUISINE, INGREDIENT, UNIT
    };
    //add functions add only if it is not exist
    //return true if exists or added
    bool addItem(ItemType type, string name);
    bool checkItem(ItemType type, string name);

    void removeUnusedElements();

    std::set<unsigned int> fetchIDs(const searcher::Criteria& searchCriteria);
    std::optional<recipe::Recipe> fetchRecipe(unsigned int id);
    recipe::IngredientsList fetchIngredientsForRecipe(unsigned int id);

    void insertIngredientsForRecipe(recipe::IngredientsList ingredients, unsigned int id);
    void removeIngredientsForRecipe(unsigned int id);

    void bindTableName(string& query, string tableName);
};

}   // dbAPI 
}   // server

#endif // DATABASE_API