#ifndef MODIFIER
#define MODIFIER

#include "i_database_api.h"

namespace server {
namespace modifier {

class Modifier {
    dbAPI::IDatabase& db;
public:
    Modifier(dbAPI::IDatabase& db);
    bool add(const recipe::Recipe& newRecipe);
    bool edit(const recipe::Recipe& changedRecipe);
    bool remove(unsigned int id);
};

} // namespace modifier
} // namespace server


#endif // MODIFIER