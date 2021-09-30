#ifndef MODIFIER
#define MODIFIER

#include "i_database_api.h"

#include "i_modifier.h"

namespace server {
namespace modifier {

class Modifier : public IModifier {
protected:
    dbAPI::IDatabase& db;
public:
    Modifier(dbAPI::IDatabase& db);
    virtual ~Modifier() = default;

    virtual unsigned int add(const recipe::Recipe& newRecipe) const override;
    virtual bool edit(const recipe::Recipe& changedRecipe) const override;
    virtual bool remove(unsigned int id) const override;
};

} // namespace modifier
} // namespace server

#endif // MODIFIER