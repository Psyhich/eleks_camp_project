#ifndef RESPONSE_TAG
#define RESPONSE_TAG

namespace server {
namespace serializer {

enum class ResponseTag {
    error,
    getInitDataResult,
    findResult,
    addSuccess,
    editSuccess,
    removeSuccess
};

} // namespace deserializer
} // namespace server

#endif // RESPONSE_TAG