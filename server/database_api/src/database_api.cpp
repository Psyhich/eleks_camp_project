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
        // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
        // note: "nothing found" is not an error
    }

    bool Database::add(const recipe::Recipe& newRecipe) {
        // to be implemented; returns true if success, false if error
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
                                                "\t\"course_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                "\t\"course_name\"\tTEXT NOT NULL UNIQUE\n"
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
                                                 "\t\"cuisine_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\t\"cuisine_name\"\tTEXT NOT NULL UNIQUE\n"
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
                                                 "\t\"recipe_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\t\"recipe_name\"\tTEXT NOT NULL,\n"
                                                 "\t\"recipe_text\"\tTEXT NOT NULL,\n"
                                                 "\t\"recipe_mass\"\tINTEGER NOT NULL,\n"
                                                 "\t\"recipe_portion_amount\"\tINTEGER NOT NULL DEFAULT 1,\n"
                                                 "\t\"recipe_portion_nutritional_value\"\tREAL NOT NULL DEFAULT 0,\n"
                                                 "\t\"recipe_cuisine_id\"\tINTEGER,\n"
                                                 "\t\"recipe_course_id\"\tINTEGER,\n"
                                                 "\tFOREIGN KEY(\"recipe_cuisine_id\") REFERENCES \"cuisines\"(\"cuisine_id\"),\n"
                                                 "\tFOREIGN KEY(\"recipe_course_id\") REFERENCES \"courses\"(\"course_id\")\n"
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
                                                     "\t\"ingredient_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                     "\t\"ingredient_name\"\tTEXT NOT NULL UNIQUE\n"
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
                                               "\t\"unit_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                               "\t\"unit_name\"\tTEXT NOT NULL UNIQUE\n"
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
                                                           "\t\"recipe_id\"\tINTEGER NOT NULL,\n"
                                                           "\t\"ingredient_id\"\tINTEGER NOT NULL,\n"
                                                           "\t\"measure_id\"\tINTEGER NOT NULL,\n"
                                                           "\t\"ingredient_amount\"\tNUMERIC NOT NULL,\n"
                                                           "\tFOREIGN KEY(\"measure_id\") REFERENCES \"units\"(\"measure_id\"),\n"
                                                           "\tFOREIGN KEY(\"ingredient_id\") REFERENCES \"ingredients\"(\"ingredient_id\"),\n"
                                                           "\tFOREIGN KEY(\"recipe_id\") REFERENCES \"recipes\"(\"recipe_id\")\n"
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

}   // dbAPI 
}   // server