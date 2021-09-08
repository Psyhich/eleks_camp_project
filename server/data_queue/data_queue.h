#ifndef DATA_QUEUE
#define DATA_QUEUE

#include <condition_variable>
#include <queue>
#include <mutex>
#include <utility>

namespace server {
namespace helpers {

template <typename T> class DataQueue {
protected:
    std::mutex queueMut;
    std::queue<T> queueContainer;
    std::condition_variable waitCV;
    std::mutex waitMut;

public:
    DataQueue() = default;
    DataQueue(const DataQueue<T>&) = delete;
    virtual ~DataQueue() {clear()}

    bool empty(){
        std::scoped_lock queueLock(queueMut);
        return queueContainer.empty();
    }

    size_t size(){
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

    T popGet(){
        std::scoped_lock queueLock(queueMut);
        auto temp = std::move(queueContainer.front());
        queueContainer.pop();
        return temp;
    }

    void push(T&& value){
        std::scoped_lock queueLock(queueMut);
        queueContainer.push(std::forward<T>(value));
        std::unique_lock waitLock(waitMut);
        waitCV.notify_one();
    }

    void clear() {
        std::scoped_lock queueLock(queueMut);
        queueContainer.clear();
    }

    void wait() {
        while(empty()){
            std::unique_lock waitLock(waitMut);
            waitCV.wait(waitLock);
        }
    }
};

} // helpers
} // server

#endif // DATA_QUEUE