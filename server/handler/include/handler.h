#ifndef HANDLER
#define HANDLER

#include <optional>

#include "initializer.h"
#include "modifier.h"
#include "requests.h"
#include "responses.h"
#include "searcher.h"

#include "i_handler.h"

namespace server {
namespace handler {

class Handler : public IHandler {
protected:
    initializer::Initializer& initializer;
    searcher::Searcher& searcher;
    modifier::Modifier& modifier;
public:
    Handler(
        initializer::Initializer& initializer,
        searcher::Searcher& searcher,
        modifier::Modifier& modifier
    );

    virtual ~Handler() = default;

    virtual std::optional<responses::ResponseVar> operator()(const requests::ShutDown& shutDownRequest) const override;
    virtual std::optional<responses::ResponseVar> operator()(const requests::GetInitData& getInitDataRequest) const override;
    virtual std::optional<responses::ResponseVar> operator()(const requests::Find& findRequest) const override;
    virtual std::optional<responses::ResponseVar> operator()(const requests::Add& addRequest) const override;
    virtual std::optional<responses::ResponseVar> operator()(const requests::Edit& editRequest) const override;
    virtual std::optional<responses::ResponseVar> operator()(const requests::Remove& removeRequest) const override;
};

} // namespace handler
} // namespace server


#endif // HANDLER