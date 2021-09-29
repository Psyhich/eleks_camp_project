#ifndef DATA_QUEUE
#define DATA_QUEUE

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <utility>

namespace server {
namespace helpers {

template <typename T, int Ms> class DataQueue {
protected:
    std::mutex queueMut;
    std::deque<T> queueContainer;
    std::atomic<bool> stopFlag{ false };
    std::condition_variable waitCV;
    std::mutex waitMut;

public:
    DataQueue() = default;
    DataQueue(const DataQueue&) = delete;
    virtual ~DataQueue() { clear(); }

    void start() {
        stopFlag.store(false);
    }

    void stop() {
        stopFlag.store(true);
    }

    bool empty() {
        std::scoped_lock queueLock(queueMut);
        return queueContainer.empty();
    }

    size_t size() {
        std::scoped_lock queueLock(queueMut);
        return queueContainer.size();
    }

    const T& peekFront() {
        std::scoped_lock queueLock(queueMut);
        return queueContainer.front();
    }

    const T& peekBack() {
        std::scoped_lock queueLock(queueMut);
        return queueContainer.back();
    }

    T popGet() {
        std::scoped_lock queueLock(queueMut);
        auto temp = std::move(queueContainer.front());
        queueContainer.pop_front();
        return temp;
    }

    void push(const T& value) {
        std::scoped_lock queueLock(queueMut);
        queueContainer.push_back(value);
        std::unique_lock waitLock(waitMut);
        waitCV.notify_one();
    }

    void clear() {
        std::scoped_lock queueLock(queueMut);
        queueContainer.clear();
    }

    void wait() {
        while (empty() && !stopFlag.load()) {
            std::unique_lock waitLock(waitMut);
            waitCV.wait_for(waitLock, std::chrono::milliseconds{ Ms }, [this] {return !empty() || stopFlag.load(); });
        }
    }};

} // namespace helpers
} // namespace server

#endif // DATA_QUEUE