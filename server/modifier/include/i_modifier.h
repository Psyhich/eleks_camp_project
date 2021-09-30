#ifndef I_MODIFIER
#define I_MODIFIER

#include "recipe.h"

namespace server {
namespace modifier {

class IModifier {
public:
    virtual ~IModifier() = default;

    virtual unsigned int add(const recipe::Recipe& newRecipe) const = 0;
    virtual bool edit(const recipe::Recipe& changedRecipe) const = 0;
    virtual bool remove(unsigned int id) const = 0;
};

} // namespace modifier
} // namespace server


#endif // I_MODIFIER