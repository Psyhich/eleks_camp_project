#ifndef THREAD_CYCLER
#define THREAD_CYCLER

#include <atomic>
#include <condition_variable>
#include <exception>
#include <memory>
#include <mutex>
#include <thread>

namespace server {
namespace helpers {

class ThreadCycler {
protected:
    std::unique_ptr<std::thread> thr;
    std::atomic<bool> stopFlag {true};
    std::atomic<bool> runFlag{ false };
    std::mutex finishMut;
    std::condition_variable finishCV;

public:
    ThreadCycler() = default;
    virtual ~ThreadCycler();

    virtual void start();
    virtual void stop();

protected:
    virtual void run();
    virtual void work() {}
    virtual void prepareStop() {}
    virtual void handleNonFatalThreadException (std::exception&e) {}
    virtual void handleFatalThreadException (std::exception& e);
};

} // namespace helpers
} // namespace server


#endif // THREAD_CYCLER