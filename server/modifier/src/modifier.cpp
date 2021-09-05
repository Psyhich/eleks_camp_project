#include "modifier.h"

namespace server {
namespace modifier {

    Modifier::Modifier(dbAPI::IDatabase& db) : db{db} {}

    bool Modifier::add(const recipe::Recipe& newRecipe) const {
        return db.add(newRecipe);
    }

    bool Modifier::edit(const recipe::Recipe& changedRecipe) const {
        return db.edit(changedRecipe);
    }

    bool Modifier::remove(unsigned int id) const {
        return db.remove(id);
    }

} // namespace modifier
} // namespace server