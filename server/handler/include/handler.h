#ifndef HANDLER
#define HANDLER

#include "i_initializer.h"
#include "i_modifier.h"
#include "i_searcher.h"
#include "requests.h"
#include "responses.h"

#include "i_handler.h"

namespace server {
namespace handler {

class Handler : public IHandler {
protected:
    initializer::IInitializer& initializer;
    searcher::ISearcher& searcher;
    modifier::IModifier& modifier;
public:
    Handler(
        initializer::IInitializer& initializer,
        searcher::ISearcher& searcher,
        modifier::IModifier& modifier
    );

    virtual ~Handler() = default;

    virtual responses::ResponseVar operator()(const requests::Error& errorRequest) const override;
    virtual responses::ResponseVar operator()(const requests::GetInitData& getInitDataRequest) const override;
    virtual responses::ResponseVar operator()(const requests::Find& findRequest) const override;
    virtual responses::ResponseVar operator()(const requests::Add& addRequest) const override;
    virtual responses::ResponseVar operator()(const requests::Edit& editRequest) const override;
    virtual responses::ResponseVar operator()(const requests::Remove& removeRequest) const override;
};

} // namespace handler
} // namespace server


#endif // HANDLER