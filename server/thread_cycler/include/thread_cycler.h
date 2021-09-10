#ifndef THREAD_CYCLER
#define THREAD_CYCLER

#include <atomic>
#include <memory>
#include <thread>

namespace server {
namespace helpers {

class ThreadCycler {
protected:
    std::unique_ptr<std::thread> threadPtr;
    std::atomic<bool> stopFlag {true};

public:
    virtual ~ThreadCycler();

    void start();
    void stop();

protected:
    void run();
    virtual void work() = 0;
};

} // namespace helpers
} // namespace server


#endif // THREAD_CYCLER