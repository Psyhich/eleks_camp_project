#ifndef DATABASE_API
#define DATABASE_API

#include <optional>
#include <iostream>

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

    bool add(const recipe::Recipe& newRecipe) override;
    bool edit(const recipe::Recipe& changedRecipe) override;
    bool remove(unsigned int id) override;

private:
    static constexpr char databaseName[] = "cookbook.db";
    static constexpr char coursesTableName[] = "courses";
    static constexpr char cuisinesTableName[] = "cuisines";
    static constexpr char recipesTableName[] = "recipes";
    static constexpr char ingredientsTableName[] = "ingredients";
    static constexpr char unitsTableName[] = "units";
    static constexpr char recipeIngredientsTableName[] = "recipe_ingredients";

    static constexpr char defaultUnit[] = "г";

    SQLite::Database db;

    void createCoursesTable();
    void createCuisinesTable();
    void createRecipesTable();
    void createIngredientsTable();
    void createUnitsTable();
    void createRecipeIngredientsTable();

    void insertDefaultUnit();
    bool containsDefaultUnit();

    void bindTableName(string& query, string tableName);
};

}   // dbAPI 
}   // server

#endif // DATABASE_API