#ifndef INDEXED_CONTAINER
#define INDEXED_CONTAINER

#include <condition_variable>
#include <mutex>
#include <utility>
#include <vector>

namespace server {
namespace helpers {

template <typename T>
class IndexedContainer {
protected:
    std::mutex vectorMut;
    std::vector<T> vectorContainer;
public:
    IndexedContainer() = default;
    IndexedContainer(const IndexedContainer&) = delete;
    virtual ~IndexedContainer() { clear(); }

    bool empty() {
        std::scoped_lock vectorLock(vectorMut);
        return vectorContainer.empty();
    }

    size_t size() {
        std::scoped_lock vectorLock(vectorMut);
        return vectorContainer.size();
    }

    T& at(size_t index) {
        std::scoped_lock vectorLock(vectorMut);
        return vectorContainer.at(index);
    }

    template <typename T>
    void push_back(T&& value) {
        std::scoped_lock vectorLock(vectorMut);
        vectorContainer.push_back(std::forward<T>(value));
    }

    void clear() {
        std::scoped_lock vectorLock(vectorMut);
        vectorContainer.clear();
    }
};

} // namespace helpers
} // namespace server

#endif // INDEXED_CONTAINER