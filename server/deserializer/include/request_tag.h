#ifndef REQUEST_TAG
#define REQUEST_TAG

namespace server {
namespace deserializer {

enum class RequestTag {
    getInitData = 1,
    find,
    add,
    edit,
    remove
};

} // namespace deserializer
} // namespace server

#endif // REQUEST_TAG