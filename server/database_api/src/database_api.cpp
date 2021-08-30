#include "database_api.h"

namespace server {
namespace dbAPI {

    Database::Database() : db(databaseName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        createCoursesTable();
        createCuisinesTable();
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
                db.exec(createCuisinesTable);
            }
            catch (std::exception& e) {
                std::cerr << "error: cannot create " << cuisinesTableName << " table" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }
    }

}   // dbAPI 
}   // server