#include "database_api.h"

namespace server {
namespace dbAPI {

    Database::Database() : db(databaseName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE, busyTime) {
        createTables();
        insertDefaultUnit();
    }

    Database::Database(string path) : db(path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE, busyTime) {
        createTables();
        insertDefaultUnit();
    }

    Database::~Database() {
        // to be implemented
        // data base close-down probably goes here
    }

    std::optional<initializer::DataContainers> Database::getInitData() {
        try {
            string selectQuery = "SELECT * FROM %tableName%";

            std::vector<string> tableNames{coursesTableName, cuisinesTableName, ingredientsTableName, unitsTableName};
            std::vector<std::set<string>> setsToInitialize(tableNames.size(), std::set<string>{});

            for (int i = 0; i < tableNames.size(); i++) {
                string query = selectQuery;
                bindTableName(query, tableNames[i]);

                SQLite::Statement statement{db, query};
                while (statement.executeStep()) {
                    setsToInitialize[i].insert(statement.getColumn(1));
                }
            }

            initializer::DataContainers container{setsToInitialize[0], setsToInitialize[1], setsToInitialize[2], setsToInitialize[3]};
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
            std::cerr << e.what() << std::endl;
            return std::nullopt;
        }
    }

    unsigned int Database::add(const recipe::Recipe& newRecipe) {
        try {
            addItem(ItemType::COURSE, newRecipe.getCourse());
            addItem(ItemType::CUISINE, newRecipe.getCuisine());

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
            return id;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot insert recipe" << std::endl;
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }

    bool Database::edit(const recipe::Recipe& changedRecipe) {
        try {
            bool status{};
            addItem(ItemType::COURSE, changedRecipe.getCourse());
            addItem(ItemType::CUISINE, changedRecipe.getCuisine());

            string query = "UPDATE recipes\n"
                           "SET recipe_name = :name, recipe_preparation = :preparation, recipe_presentation = :presentation,\n"
                           "recipe_weight = :weight, recipe_portion_amount = :amount,\n"
                           "recipe_portion_nutritional_value = :calories, recipe_cuisine_id = results.cuisine_id,\n"
                           "recipe_course_id = results.course_id, recipe_remarks = :remarks\n"
                           "FROM (SELECT *\n"
                           "FROM cuisines, courses\n"
                           "WHERE cuisines.cuisine_name= :cuisine\n"
                           "AND courses.course_name = :course) as results\n"
                           "WHERE recipes.recipe_id = :id\n";
            SQLite::Statement updateRecipeQuery(db, query);
            updateRecipeQuery.bind(":id", changedRecipe.getId());
            updateRecipeQuery.bind(":name", changedRecipe.getName());
            updateRecipeQuery.bind(":preparation", changedRecipe.getPreparation());
            updateRecipeQuery.bind(":presentation", changedRecipe.getPresentation());
            updateRecipeQuery.bind(":weight", changedRecipe.getOutWeight());
            updateRecipeQuery.bind(":amount", changedRecipe.getOutPortions());
            updateRecipeQuery.bind(":calories", changedRecipe.getOutCalories());
            updateRecipeQuery.bind(":cuisine", changedRecipe.getCuisine());
            updateRecipeQuery.bind(":course", changedRecipe.getCourse());
            updateRecipeQuery.bind(":remarks", changedRecipe.getRemarks());
            int recordsCount = updateRecipeQuery.exec();
            if (!recordsCount) {
                std::cerr << "error: cannot edit recipe. no recipe with ID: " << changedRecipe.getId() << std::endl;
            }
            else {
                removeIngredientsForRecipe(changedRecipe.getId());
                insertIngredientsForRecipe(changedRecipe.getIngredients(), changedRecipe.getId());
                status = true;
            }
            removeUnusedElements();
            return status;
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot update recipe with ID: " << changedRecipe.getId() << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool Database::remove(unsigned int id) {
        try {
            removeIngredientsForRecipe(id);
            string query = "DELETE FROM recipes\n"
                           "WHERE recipe_id = :id";
            SQLite::Statement deleteQuery(db, query);
            deleteQuery.bind(":id", id);

            bool status = deleteQuery.exec();
            removeUnusedElements();
            return status;
        }
        catch (std::exception &e) {
            std::cerr << "error: cannot remove recipe" << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    void Database::insertDefaultUnit() {
        addItem(ItemType::UNIT, defaultUnit);
    }

    void Database::bindTableName(string& query, string tableName) {
        string keyword = "%tableName%";
        unsigned int startPosition = query.find(keyword);
        query.replace(startPosition, keyword.length(), tableName);
    }

    std::set<unsigned int> Database::fetchIDs(const searcher::Criteria& searchCriteria) {
        try {
            std::vector<string> itemsToBind;

            string query = "SELECT recipes.recipe_id\n"
                           "FROM recipes \n";
            if (!searchCriteria.getCourse().empty()) {
                query += "INNER JOIN courses ON courses.course_id = recipes.recipe_course_id\n";
            }
            if (!searchCriteria.getCuisine().empty()) {
                query += "INNER JOIN cuisines ON cuisines.cuisine_id = recipes.recipe_cuisine_id\n";
            }
            if (!searchCriteria.getIngredientsSubset().empty()) {
                auto ingredientSubset = searchCriteria.getIngredientsSubset();
                query += "INNER JOIN (\n"
                         "\tSELECT recipe_id, COUNT(recipe_id) as ingredient_count\n"
                         "\tFROM recipe_ingredients\n"
                         "\tINNER JOIN ingredients ON recipe_ingredients.ingredient_id = ingredients.ingredient_id\n"
                         "\tWHERE ingredients.ingredient_name IN (";
                for (auto it = ingredientSubset.begin(); it != ingredientSubset.end(); ++it) {
                    query += "?";
                    query += (it != --ingredientSubset.end()) ? ", " : "";
                    itemsToBind.push_back(*it);
                }
                query += ")\n"
                         "\tGROUP BY recipe_id\n";
                unsigned int criteriaIngredientsCount = searchCriteria.getIngredientsSubset().size();
                query += "\tHAVING ingredient_count = " + std::to_string(criteriaIngredientsCount);
                query += "\n)ids ON recipes.recipe_id = ids.recipe_id\n";
            }
            if (!searchCriteria.getIngredientsSubset().empty() && searchCriteria.getExclusiveIngredients()) {
                query += "INNER JOIN (\n"
                         "\tSELECT recipe_id, COUNT(recipe_id) as ingredient_count\n"
                         "\tFROM recipe_ingredients\n"
                         "\tGROUP BY recipe_id\n"
                         ") ingredient_count ON recipes.recipe_id = ingredient_count.recipe_id\n";
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
            if (!searchCriteria.getIngredientsSubset().empty() && searchCriteria.getExclusiveIngredients()) {
                query += "AND ingredient_count.ingredient_count = ids.ingredient_count\n";
            }
            if (!searchCriteria.getCourse().empty()) {
                query += "AND courses.course_name = ?\n";
                itemsToBind.push_back(searchCriteria.getCourse());
            }
            if (!searchCriteria.getCuisine().empty()) {
                query += "AND cuisines.cuisine_name = ?\n";
                itemsToBind.push_back(searchCriteria.getCuisine());
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
                                           "FROM recipes\n"
                                           "INNER JOIN courses ON recipes.recipe_course_id = courses.course_id\n"
                                           "INNER JOIN cuisines ON recipes.recipe_cuisine_id = cuisines.cuisine_id\n"
                                           "WHERE recipe_id = :recipeID";
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
                                 "WHERE recipe_ingredients.recipe_id = :recipeID\n"
                                 "ORDER BY recipe_ingredients.record_id\n";
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

    void Database::insertIngredientsForRecipe(recipe::IngredientsList ingredients, unsigned int id) {
        for (auto item : ingredients) {
            addItem(ItemType::INGREDIENT, item.first);
            addItem(ItemType::UNIT, item.second.unit);

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

    void Database::removeIngredientsForRecipe(unsigned int id) {
        try {
            string query = "DELETE FROM recipe_ingredients\n"
                           "WHERE recipe_id = :id";
            SQLite::Statement deleteQuery(db, query);
            deleteQuery.bind(":id", id);
            deleteQuery.exec();
        }
        catch (std::exception &e) {
            std::cerr << "error: cannot remove ingredients for recipe" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    void Database::removeUnusedElements() {
        try {
            db.exec(
                    "DELETE FROM cuisines\n"
                    "WHERE cuisine_name IN(\n"
                    "SELECT cuisine_name\n"
                    "FROM cuisines\n"
                    "LEFT JOIN recipes ON cuisines.cuisine_id = recipes.recipe_cuisine_id\n"
                    "GROUP BY cuisine_name\n"
                    "HAVING count(recipe_cuisine_id) = 0)");

            db.exec("DELETE FROM courses\n"
                    "WHERE course_name IN(\n"
                    "SELECT course_name\n"
                    "FROM courses\n"
                    "LEFT JOIN recipes ON courses.course_id = recipes.recipe_course_id\n"
                    "GROUP BY course_name\n"
                    "HAVING count(recipe_course_id) = 0)");

            db.exec("DELETE FROM ingredients\n"
                    "WHERE ingredient_name IN (\n"
                    "SELECT ingredient_name\n"
                    "FROM ingredients\n"
                    "LEFT JOIN recipe_ingredients ON recipe_ingredients.ingredient_id = ingredients.ingredient_id\n"
                    "GROUP BY ingredient_name\n"
                    "HAVING count(recipe_ingredients.ingredient_id) = 0)");

            db.exec("DELETE FROM units\n"
                    "WHERE unit_name IN (\n"
                    "SELECT unit_name\n"
                    "FROM units\n"
                    "LEFT JOIN recipe_ingredients ON recipe_ingredients.unit_id = units.unit_id\n"
                    "GROUP BY unit_name\n"
                    "HAVING count(recipe_ingredients.unit_id) = 0)\n"
                    "AND unit_name <> " + string(defaultUnit));
        }
        catch (std::exception &e) {
            std::cerr << "error: cannot remove unused elements" << std::endl;
            std::cerr << e.what() << std::endl;
        }
    }

    bool Database::checkItem(Database::ItemType type, string name) {
        string table{};
        string field{};
        switch (type) {
            case ItemType::COURSE:
                table = field = coursesTableName;
                break;
            case ItemType::CUISINE:
                table = field = cuisinesTableName;
                break;
            case ItemType::INGREDIENT:
                table = field = ingredientsTableName;
                break;
            case ItemType::UNIT:
                table = field = unitsTableName;
                break;
        }
        field.back() = '_';
        field.append("name");
        try {
            string query = "SELECT * FROM " + table + "\n"
                           "WHERE " + field + " = :name";
            SQLite::Statement checkQuery(db, query);
            checkQuery.bind(":name", name);
            return checkQuery.executeStep();
        }
        catch (std::exception& e) {
            std::cerr << "error: cannot check " << field << std::endl;
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    bool Database::addItem(ItemType type, string name) {
        if (!checkItem(type, name)) {
            string table{};
            switch (type) {
                case ItemType::COURSE:
                    table = coursesTableName;
                    break;
                case ItemType::CUISINE:
                    table = cuisinesTableName;
                    break;
                case ItemType::INGREDIENT:
                    table = ingredientsTableName;
                    break;
                case ItemType::UNIT:
                    table = unitsTableName;
                    break;
            }
            try {
                string query = "INSERT INTO " + table + "\n"
                               "VALUES (NULL, :name)";
                SQLite::Statement insertQuery(db, query);
                insertQuery.bind(":name", name);
                return insertQuery.exec();
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot add item to " << table << std::endl;
                std::cerr << e.what() << std::endl;
                return false;
            }
        }
        else {
            return true;
        }
    }

    bool Database::createTables() {
        std::vector<std::pair<string, string>> createQueries;
        createQueries.push_back(std::pair(coursesTableName, "CREATE TABLE \"%tableName%\" (\n"
                                          "\t\"course_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                          "\t\"course_name\"\tTEXT NOT NULL UNIQUE\n"
                                          ");"));

        createQueries.push_back(std::pair(cuisinesTableName, "CREATE TABLE \"%tableName%\" (\n"
                                           "\t\"cuisine_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                           "\t\"cuisine_name\"\tTEXT NOT NULL UNIQUE\n"
                                           ");"));

        createQueries.push_back(std::pair(recipesTableName, "CREATE TABLE \"%tableName%\" (\n"
                                          "\t\"recipe_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                          "\t\"recipe_name\"\tTEXT NOT NULL,\n"
                                          "\t\"recipe_preparation\"\tTEXT NOT NULL,\n"
                                          "\t\"recipe_presentation\"\tTEXT,"
                                          "\t\"recipe_weight\"\tREAL NOT NULL,\n"
                                          "\t\"recipe_portion_amount\"\tINTEGER NOT NULL DEFAULT 1,\n"
                                          "\t\"recipe_portion_nutritional_value\"\tREAL NOT NULL DEFAULT 0,\n"
                                          "\t\"recipe_cuisine_id\"\tINTEGER,\n"
                                          "\t\"recipe_course_id\"\tINTEGER,\n"
                                          "\t\"recipe_remarks\"\tTEXT,"
                                          "\tFOREIGN KEY(\"recipe_cuisine_id\") REFERENCES \"cuisines\"(\"cuisine_id\"),\n"
                                          "\tFOREIGN KEY(\"recipe_course_id\") REFERENCES \"courses\"(\"course_id\")\n"
                                          ");"));

        createQueries.push_back(std::pair(ingredientsTableName, "CREATE TABLE \"%tableName%\" (\n"
                                              "\t\"ingredient_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                              "\t\"ingredient_name\"\tTEXT NOT NULL UNIQUE\n"
                                              ");"));

        createQueries.push_back(std::pair(unitsTableName, "CREATE TABLE \"%tableName%\" (\n"
                                        "\t\"unit_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                        "\t\"unit_name\"\tTEXT NOT NULL UNIQUE\n"
                                        ");"));

        createQueries.push_back(std::pair(recipeIngredientsTableName, "CREATE TABLE \"%tableName%\" (\n"
                                                    "\t\"record_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                    "\t\"recipe_id\"\tINTEGER NOT NULL,\n"
                                                    "\t\"ingredient_id\"\tINTEGER NOT NULL,\n"
                                                    "\t\"unit_id\"\tINTEGER NOT NULL,\n"
                                                    "\t\"ingredient_amount\"\tREAL NOT NULL,\n"
                                                    "\tFOREIGN KEY(\"unit_id\") REFERENCES \"units\"(\"unit_id\"),\n"
                                                    "\tFOREIGN KEY(\"ingredient_id\") REFERENCES \"ingredients\"(\"ingredient_id\"),\n"
                                                    "\tFOREIGN KEY(\"recipe_id\") REFERENCES \"recipes\"(\"recipe_id\")\n"
                                                    ");"));

        bool status{true};
        for (auto stringQuery : createQueries) {
            if (!db.tableExists(stringQuery.first)) {
                try {
                    bindTableName(stringQuery.second, stringQuery.first);
                    status = !db.tryExec(stringQuery.second);
                }
                catch (std::exception& e) {
                    std::cerr << "error: cannot create " << stringQuery.first << " table" << std::endl;
                    std::cerr << e.what() << std::endl;
                    status = false;
                }
            }
            status = status && true;
        }

        return status;
    }

}   // dbAPI 
}   // server
