#include "modifier.h"

namespace server {
namespace modifier {

    Modifier::Modifier(dbAPI::IDatabase& db) : db{db} {}

    bool Modifier::add(const recipe::Recipe& newRecipe) {
        return db.add(newRecipe);
    }

    bool Modifier::edit(const recipe::Recipe& changedRecipe) {
        return db.edit(changedRecipe);
    }

    bool Modifier::remove(unsigned int id) {
        return db.remove(id);
    }

} // namespace modifier
} // namespace server