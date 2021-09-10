#ifndef HASH_CONTAINER
#define HASH_CONTAINER

#include <condition_variable>
#include <map>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <utility>

namespace server {
namespace helpers {

template <typename Key, typename Obj>
class HashContainer {
protected:
    std::mutex mapMut;
    std::map<Key, Obj> mapContainer;
public:
    HashContainer() = default;
    HashContainer(const HashContainer&) = delete;
    virtual ~HashContainer() {clear()}

    bool empty() {
        std::scoped_lock mapLock(mapMut);
        return mapContainer.empty();
    }

    size_t size() {
        std::scoped_lock mapLock(mapMut);
        return mapContainer.size();   
    }

    template <typename Key>
    std::optional<Obj&> at(Key&& key) {
        std::scoped_lock mapLock(mapMut);
        try {
            auto& temp = mapContainer.at(std::forward(key));
            return std::make_optional(temp);
        } catch (const std::out_of_range&) {
            return std::nullopt;
        }
    }

    template <typename Key, typename Obj>
    bool insert(Key&& key, Obj&& obj) {
        std::scoped_lock mapLock(mapMut);
        return mapContainer.insert(std::pair(std::forward(key), std::forward(obj))).second;
    }

    bool erase(const Key& key) {
        std::scoped_lock mapLock(mapMut);
        return mapContainer.erase(key);
    }

    void clear(){
        std::scoped_lock mapLock(mapMut);
        mapContainer.clear();
    }
};

} // helpers
} // server

#endif // HASH_CONTAINER