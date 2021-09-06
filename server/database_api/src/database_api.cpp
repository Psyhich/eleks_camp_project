#include "database_api.h"

namespace server {
namespace dbAPI {

    Database::Database() : db(databaseName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        createCoursesTable();
        createCuisinesTable();
        createRecipesTable();
        createIngredientsTable();
        createUnitsTable();
        createRecipeIngredientsTable();
    }

    Database::~Database() {
        // to be implemented
        // data base close-down probably goes here
    }

    std::optional<initializer::DataContainers> Database::getInitData() {
        try {
            string selectQuery = "SELECT * FROM %tableName%";

            std::vector<string> tableNames{coursesTableName, cuisinesTableName, ingredientsTableName};
            std::vector<std::set<string>> setsToInitialize(tableNames.size(), std::set<string>{});

            for (int i = 0; i < tableNames.size(); i++) {
                string query = selectQuery;
                bindTableName(query, tableNames[i]);

                SQLite::Statement statement{db, query};
                while (statement.executeStep()) {
                    setsToInitialize[i].insert(statement.getColumn(1));
                }
            }

            initializer::DataContainers container{setsToInitialize[0], setsToInitialize[1], setsToInitialize[2]};
            return container;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot initialize DataContainers" << std::endl;
            std::cerr << e.what() << std::endl;
            return std::nullopt;
        }
    }

    std::optional<searcher::Results> Database::find(const searcher::Criteria& searchCriteria) {
        try {
            std::set ids = fetchIDs(searchCriteria);

            searcher::RecipeSet recipeSet;
            for (auto id : ids) {
                auto recipe = fetchRecipe(id);
                if (recipe.has_value()) {
                    recipeSet.insert(recipe.value());
                }
            }

            return searcher::Results(recipeSet);
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return std::nullopt;
        }
    }

    bool Database::add(const recipe::Recipe& newRecipe) {
        try {
            addCourse(newRecipe.getCourse());
            addCuisine(newRecipe.getCuisine());

            string query = "INSERT INTO recipes(recipe_name, recipe_preparation, recipe_presentation, recipe_weight, recipe_portion_amount,\n"
                           "recipe_portion_nutritional_value, recipe_cuisine_id, recipe_course_id, recipe_remarks)\n"
                           "SELECT :name, :preparation, :presentation, :weight, :amount, :calories, cuisines.cuisine_id, courses.course_id, :remarks\n"
                           "FROM cuisines, courses\n"
                           "WHERE cuisines.cuisine_name= :cuisine\n"
                           "AND courses.course_name = :course";
            SQLite::Statement insertRecipeInformationQuery(db, query);
            insertRecipeInformationQuery.bind(":name", newRecipe.getName());
            insertRecipeInformationQuery.bind(":preparation", newRecipe.getPreparation());
            insertRecipeInformationQuery.bind(":presentation", newRecipe.getPresentation());
            insertRecipeInformationQuery.bind(":weight", newRecipe.getOutWeight());
            insertRecipeInformationQuery.bind(":amount", newRecipe.getOutPortions());
            insertRecipeInformationQuery.bind(":calories", newRecipe.getOutCalories());
            insertRecipeInformationQuery.bind(":cuisine", newRecipe.getCuisine());
            insertRecipeInformationQuery.bind(":course", newRecipe.getCourse());
            insertRecipeInformationQuery.bind(":remarks", newRecipe.getRemarks());
            insertRecipeInformationQuery.exec();

            unsigned int id = 0;
            SQLite::Statement selectID(db, "SELECT last_insert_rowid()");
            if (selectID.executeStep()) {
                id = selectID.getColumn(0);
            }

            insertIngredientsForRecipe(newRecipe.getIngredients(), id);
            return true;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot insert recipe" << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool Database::edit(const recipe::Recipe& changedRecipe) {
        // to be implemented; returns true if success, false if error
    }

    bool Database::remove(unsigned int id) {
        // to be implemented; returns true if success, false if error
    }

    void Database::createCoursesTable() {
        if (!db.tableExists(coursesTableName)) {
            try {
                string createCoursesTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                                "\"course_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                "\"course_name\"\tTEXT NOT NULL UNIQUE\n"
                                                ");";
                bindTableName(createCoursesTableQuery, coursesTableName);
                db.setBusyTimeout(50);
                db.exec(createCoursesTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << coursesTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Database::createCuisinesTable() {
        if (!db.tableExists(cuisinesTableName)) {
            try {
                string createCuisinesTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                                 "\"cuisine_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\"cuisine_name\"\tTEXT NOT NULL UNIQUE\n"
                                                 ");";
                bindTableName(createCuisinesTableQuery, cuisinesTableName);
                db.setBusyTimeout(50);
                db.exec(createCuisinesTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << cuisinesTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Database::createRecipesTable() {
        if (!db.tableExists(recipesTableName)) {
            try {
                string createRecipesTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                                 "\"recipe_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\"recipe_name\"\tTEXT NOT NULL,\n"
                                                 "\"recipe_preparation\"\tTEXT NOT NULL,\n"
                                                 "\"recipe_presentation\"\tTEXT,"
                                                 "\"recipe_weight\"\tREAL NOT NULL,\n"
                                                 "\"recipe_portion_amount\"\tINTEGER NOT NULL DEFAULT 1,\n"
                                                 "\"recipe_portion_nutritional_value\"\tREAL NOT NULL DEFAULT 0,\n"
                                                 "\"recipe_cuisine_id\"\tINTEGER,\n"
                                                 "\"recipe_course_id\"\tINTEGER,\n"
                                                 "\"recipe_remarks\"\tTEXT,"
                                                 "FOREIGN KEY(\"recipe_cuisine_id\") REFERENCES \"cuisines\"(\"cuisine_id\"),\n"
                                                 "FOREIGN KEY(\"recipe_course_id\") REFERENCES \"courses\"(\"course_id\")\n"
                                                 ");";
                bindTableName(createRecipesTableQuery, recipesTableName);
                db.setBusyTimeout(50);
                db.exec(createRecipesTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << recipesTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Database::createIngredientsTable() {
        if (!db.tableExists(ingredientsTableName)) {
            try {
                string createIngredientsTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                                     "\"ingredient_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                     "\"ingredient_name\"\tTEXT NOT NULL UNIQUE\n"
                                                     ");";
                bindTableName(createIngredientsTableQuery, ingredientsTableName);
                db.setBusyTimeout(50);
                db.exec(createIngredientsTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << ingredientsTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    void Database::createUnitsTable() {
        if (!db.tableExists(unitsTableName)) {
            try {
                string createUnitsTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                               "\"unit_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                               "\"unit_name\"\tTEXT NOT NULL UNIQUE\n"
                                               ");";
                bindTableName(createUnitsTableQuery, unitsTableName);
                db.setBusyTimeout(50);
                db.exec(createUnitsTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << unitsTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
        if (!containsDefaultUnit()) {
            insertDefaultUnit();
        }
    }

    void Database::insertDefaultUnit() {
        try {
            string insertDefaultUnitQuery = "INSERT INTO %tableName% VALUES (NULL, :defaultUnit);";
            bindTableName(insertDefaultUnitQuery, unitsTableName);

            SQLite::Statement insertQuery(db, insertDefaultUnitQuery);
            insertQuery.bind(":defaultUnit", defaultUnit);
            insertQuery.exec();
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot insert default unit" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    bool Database::containsDefaultUnit() {
        try {
            string checkDefaultUnitQuery = "SELECT * FROM %tableName% WHERE unit_name = :unitName";
            bindTableName(checkDefaultUnitQuery, unitsTableName);

            SQLite::Statement checkQuery(db, checkDefaultUnitQuery);
            checkQuery.bind(":unitName", defaultUnit);
            db.setBusyTimeout(50);
            return checkQuery.executeStep();
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot check containing default unit" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    void Database::bindTableName(string& query, string tableName) {
        string keyword = "%tableName%";
        unsigned int startPosition = query.find(keyword);
        query.replace(startPosition, keyword.length(), tableName);
    }

    void Database::createRecipeIngredientsTable() {
        if (!db.tableExists(recipeIngredientsTableName)) {
            try {
                string createRecipeIngredientsTableQuery = "CREATE TABLE \"%tableName%\" (\n"
                                                           "\"recipe_id\"\tINTEGER NOT NULL,\n"
                                                           "\"ingredient_id\"\tINTEGER NOT NULL,\n"
                                                           "\"unit_id\"\tINTEGER NOT NULL,\n"
                                                           "\"ingredient_amount\"\tREAL NOT NULL,\n"
                                                           "FOREIGN KEY(\"unit_id\") REFERENCES \"units\"(\"unit_id\"),\n"
                                                           "FOREIGN KEY(\"ingredient_id\") REFERENCES \"ingredients\"(\"ingredient_id\"),\n"
                                                           "FOREIGN KEY(\"recipe_id\") REFERENCES \"recipes\"(\"recipe_id\")\n"
                                                           ");";
                bindTableName(createRecipeIngredientsTableQuery, recipeIngredientsTableName);
                db.setBusyTimeout(50);
                db.exec(createRecipeIngredientsTableQuery);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << recipeIngredientsTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

    std::set<unsigned int> Database::fetchIDs(const searcher::Criteria& searchCriteria) {
        try {
            std::vector<string> itemsToBind;

            string query = "SELECT recipes.recipe_id\n"
                           "FROM recipes \n";
            if (!searchCriteria.getCourse().empty()) {
                query += "INNER JOIN courses ON courses.course_name = ?\n";
                itemsToBind.push_back(searchCriteria.getCourse());
            }
            if (!searchCriteria.getCuisine().empty()) {
                query += "INNER JOIN cuisines ON cuisines.cuisine_name = ?\n";
                itemsToBind.push_back(searchCriteria.getCuisine());
            }
            if (!searchCriteria.getIngredientsSubset().empty()) {
                auto ingredientSubset = searchCriteria.getIngredientsSubset();
                query += "INNER JOIN (\n"
                         "SELECT recipe_id, COUNT(recipe_id) as ingredient_count\n"
                         "FROM recipe_ingredients\n"
                         "INNER JOIN ingredients ON recipe_ingredients.ingredient_id = ingredients.ingredient_id\n"
                         "WHERE ingredients.ingredient_name IN (";
                for (auto it = ingredientSubset.begin(); it != ingredientSubset.end(); ++it) {
                    query += "?";
                    query += (it != --ingredientSubset.end()) ? ", " : "";
                    itemsToBind.push_back(*it);
                }
                query += ")\n"
                         "GROUP BY recipe_id\n";
                unsigned int criteriaIngredientsCount = searchCriteria.getIngredientsSubset().size();
                query += "HAVING ingredient_count = " + std::to_string(criteriaIngredientsCount) + "\n";
                query += ") ids ON recipes.recipe_id = ids.recipe_id\n"
                         "INNER JOIN (\n"
                         "SELECT recipe_id, COUNT(recipe_id) as ingredient_count\n"
                         "FROM recipe_ingredients\n"
                         "GROUP BY recipe_id\n"
                         ") ingredient_count\n";
            }
            query +=     "WHERE recipes.recipe_id = recipes.recipe_id\n";
            if (!searchCriteria.getNameSubstring().empty()) {
                query += "AND recipes.recipe_name LIKE ?\n";
                string subName = "%" + searchCriteria.getNameSubstring() + "%";
                itemsToBind.push_back(subName);
            }
            if (!searchCriteria.getFavoriteIDs().empty()) {
                auto favoriteIDs = searchCriteria.getFavoriteIDs();
                query += "AND (";
                for (auto it = favoriteIDs.begin(); it != favoriteIDs.end(); ++it) {
                    string toConcat = "recipes.recipe_id = " + std::to_string(*it);
                    toConcat += (it != --favoriteIDs.end()) ? " OR " : "";
                    query += toConcat;
                }
                query += ")\n";
            }
            if (searchCriteria.getExclusiveIngredients()) {
                query += "AND ingredient_count.ingredient_count = ids.ingredient_count";
            }

            SQLite::Statement fetchQuery{db, query};
            for (auto i = 0; i < itemsToBind.size(); ++i) {
                fetchQuery.bind(i + 1, itemsToBind[i]);
            }
            std::set<unsigned int> ids{};
            while(fetchQuery.executeStep()) {
                ids.insert(fetchQuery.getColumn(0));
            }
            return ids;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot fetch recipe ids" << std::endl;
            std::cerr << e.what() << std::endl;
            return std::set<unsigned int>{};
        }
    }

    std::optional<recipe::Recipe> Database::fetchRecipe(unsigned int id) {
        std::string name{};
        std::string course{};
        std::string cuisine{};
        recipe::IngredientsList ingredients{};
        double outCalories{};
        double outWeight{};
        unsigned int outPortions{};
        std::string preparation{};
        std::string presentation{};
        std::string remarks{};

        try {
            string selectRecipeInfoQuery = "SELECT recipe_name, recipe_preparation, recipe_presentation, recipe_weight, recipe_portion_amount,\n"
                                           "recipe_portion_nutritional_value, courses.course_name, cuisines.cuisine_name, recipe_remarks\n"
                                           "FROM %tableName%\n"
                                           "INNER JOIN courses ON recipes.recipe_course_id = courses.course_id\n"
                                           "INNER JOIN cuisines ON recipes.recipe_cuisine_id = cuisines.cuisine_id\n"
                                           "WHERE recipe_id = :recipeID";
            bindTableName(selectRecipeInfoQuery, recipesTableName);
            SQLite::Statement fetchRecipeInfo(db, selectRecipeInfoQuery);
            fetchRecipeInfo.bind(":recipeID", id);
            if (fetchRecipeInfo.executeStep()) {
                name = fetchRecipeInfo.getColumn(0).getString();
                preparation = fetchRecipeInfo.getColumn(1).getString();
                presentation = fetchRecipeInfo.getColumn(2).getString();
                outWeight = fetchRecipeInfo.getColumn(3).getDouble();
                outPortions = fetchRecipeInfo.getColumn(4).getInt();
                outCalories = fetchRecipeInfo.getColumn(5).getDouble();
                course = fetchRecipeInfo.getColumn(6).getString();
                cuisine = fetchRecipeInfo.getColumn(7).getString();
                remarks = fetchRecipeInfo.getColumn(8).getString();
                ingredients = fetchIngredientsForRecipe(id);
            }
            else {
                throw std::runtime_error("no recipe with ID: " + std::to_string(id));
            }
            return recipe::Recipe{id, name, course, cuisine, ingredients, outCalories, outWeight, outPortions, preparation, presentation, remarks};
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot fetch recipe with ID: " << id << std::endl;
            std::cerr << e.what() << std::endl;
            return std::nullopt;
        }
    }

    recipe::IngredientsList Database::fetchIngredientsForRecipe(unsigned int id) {
        try {
            recipe::IngredientsList ingredients{};
            string selectIngredientsQuery = "SELECT ingredients.ingredient_name, ingredient_amount, units.unit_name\n"
                                 "FROM recipe_ingredients\n"
                                 "INNER JOIN units ON units.unit_id = recipe_ingredients.unit_id\n"
                                 "INNER JOIN ingredients ON ingredients.ingredient_id = recipe_ingredients.ingredient_id\n"
                                 "WHERE recipe_ingredients.recipe_id = :recipeID";
            SQLite::Statement fetchIngredientsQuery{db, selectIngredientsQuery};
            fetchIngredientsQuery.bind(":recipeID", id);
            while (fetchIngredientsQuery.executeStep()) {
                recipe::IngredientAmount amount{fetchIngredientsQuery.getColumn(1).getDouble(),
                                                fetchIngredientsQuery.getColumn(2).getString()};
                ingredients[fetchIngredientsQuery.getColumn(0)] = amount;
            }
            return ingredients;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot fetch ingredients for recipe with ID: " << id << std::endl;
            std::cerr << e.what() << std::endl;
            return recipe::IngredientsList {};
        }
    }

    bool Database::addCourse(string course) {
        if (!checkCourse(course)) {
            try {
                string query = "INSERT INTO courses\n"
                               "VALUES (NULL, :course)";
                SQLite::Statement insertQuery(db, query);
                insertQuery.bind(":course", course);
                return insertQuery.exec();
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot add course" << std::endl;
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
        else {
            return true;
        }
    }

    bool Database::removeCourse(string course) {
        if (checkCourse(course)) {
            try {
                string query = "DELETE FROM courses\n"
                               "WHERE course_name = :course";
                SQLite::Statement insertQuery(db, query);
                insertQuery.bind(":course", course);
                return insertQuery.exec();
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot remove course" << std::endl;
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
        else {
            return true;
        }
    }

    bool Database::addCuisine(string cuisine) {
        if (!checkCuisine(cuisine)) {
            try {
                string query = "INSERT INTO cuisines\n"
                               "VALUES (NULL, :cuisine)";
                SQLite::Statement insertQuery(db, query);
                insertQuery.bind(":cuisine", cuisine);
                return insertQuery.exec();
            }
            catch (std::exception &e) {
                std::cerr << "error: cannot add cuisine" << std::endl;
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
        else {
            return true;
        }
    }

    bool Database::removeCuisine(string cuisine) {
        if (checkCuisine(cuisine)) {
            try {
                string query = "DELETE FROM cuisines\n"
                               "WHERE cuisine_name = :cuisine";
                SQLite::Statement insertQuery(db, query);
                insertQuery.bind(":cuisine", cuisine);
                return insertQuery.exec();
            }
            catch (std::exception &e) {
                std::cerr << "error: cannot remove cuisine" << std::endl;
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
        else {
            return true;
        }
    }

    void Database::insertIngredientsForRecipe(recipe::IngredientsList ingredients, unsigned int id) {
        for (auto item : ingredients) {
            string query = "INSERT INTO recipe_ingredients (recipe_id, ingredient_id, unit_id, ingredient_amount)\n"
                           "SELECT :id, ingredients.ingredient_id, units.unit_id, :amount\n"
                           "FROM ingredients, units\n"
                           "WHERE ingredients.ingredient_name = :ingredient\n"
                           "AND units.unit_name = :unit";
            SQLite::Statement insertRecipeIngredientQuery(db, query);

            insertRecipeIngredientQuery.bind(":id", id);
            insertRecipeIngredientQuery.bind(":amount", item.second.quantity);
            insertRecipeIngredientQuery.bind(":ingredient", item.first);
            insertRecipeIngredientQuery.bind(":unit", item.second.unit);

            insertRecipeIngredientQuery.exec();
        }
    }

    bool Database::checkCuisine(string cuisine) {
        try {
            string query = "SELECT * FROM cuisines\n"
                           "WHERE cuisine_name = :cuisine";
            SQLite::Statement checkQuery(db, query);
            checkQuery.bind(":cuisine", cuisine);
            return checkQuery.executeStep();
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot check cuisine" << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool Database::checkCourse(string course) {
        try {
            string query = "SELECT * FROM courses\n"
                           "WHERE course_name = :course";
            SQLite::Statement checkQuery(db, query);
            checkQuery.bind(":course", course);
            return checkQuery.executeStep();
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot check course" << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

}   // dbAPI 
}   // server