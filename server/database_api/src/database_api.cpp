#include "database_api.h"

namespace server {
namespace dbAPI {

    Database::Database() : db(databaseName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        createCoursesTable();
        createCuisinesTable();
        createRecipesTable();
        createIngredientsTable();
    }

    Database::~Database() {
        // to be implemented
        // data base close-down probably goes here
    }

    std::optional<initializer::DataContainers> Database::getInitData() {
        // to be implemented; returns container variable wrapped in std::optional if success, std::nullopt if error
        // note: "nothing found" is not an error
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
                std::string createCoursesTable = "CREATE TABLE \"courses\" (\n"
                                                 "\t\"course_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\t\"course_name\"\tTEXT NOT NULL\n"
                                                 ");";
                db.setBusyTimeout(50);
                db.exec(createCoursesTable);
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
                std::string createCuisinesTable = "CREATE TABLE \"cuisines\" (\n"
                                                 "\t\"cuisine_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\t\"cuisine_name\"\tTEXT NOT NULL\n"
                                                 ");";
                db.setBusyTimeout(50);
                db.exec(createCuisinesTable);
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
                std::string createRecipesTable = "CREATE TABLE \"recipes\" (\n"
                                                 "\t\"recipe_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                 "\t\"recipe_name\"\tTEXT NOT NULL,\n"
                                                 "\t\"recipe_text\"\tTEXT NOT NULL,\n"
                                                 "\t\"recipe_mass\"\tREAL NOT NULL,\n"
                                                 "\t\"recipe_portion_amount\"\tINTEGER NOT NULL DEFAULT 1,\n"
                                                 "\t\"recipe_nutritional_value\"\tREAL DEFAULT 0,\n"
                                                 "\t\"recipe_cuisine_id\"\tINTEGER,\n"
                                                 "\t\"recipe_course_id\"\tINTEGER,\n"
                                                 "\tFOREIGN KEY(\"recipe_cuisine_id\") REFERENCES \"cuisines\"(\"cuisine_id\"),\n"
                                                 "\tFOREIGN KEY(\"recipe_course_id\") REFERENCES \"courses\"(\"course_id\")\n"
                                                 ");";
                db.setBusyTimeout(50);
                db.exec(createRecipesTable);
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
                std::string createIngredientsTable = "CREATE TABLE \"ingredients\" (\n"
                                                     "\t\"ingredient_id\"\tINTEGER PRIMARY KEY AUTOINCREMENT,\n"
                                                     "\t\"ingredient_name\"\tTEXT NOT NULL UNIQUE\n"
                                                     ");";
                db.setBusyTimeout(50);
                db.exec(createIngredientsTable);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << ingredientsTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

}   // dbAPI 
}   // server