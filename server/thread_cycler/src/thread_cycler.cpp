#include "thread_cycler.h"

namespace server {
namespace helpers {

ThreadCycler::~ThreadCycler() {
    stop();
}

void ThreadCycler::start() {
    if (stopFlag.load()){
        stopFlag.store(false);
        thr.reset(new std::thread([this](){run();}));
        thr->detach();
    }
}

void ThreadCycler::stop() {
    if (!stopFlag.load()){
        stopFlag.store(true);
        std::unique_lock finishLock(finishMut);
        finishCV.wait(finishLock, [this] {return !runFlag.load(); });
    }
}

void ThreadCycler::run() {
    runFlag.store(true);
    try {
        while (!stopFlag.load()){
            try{
                work();
            } catch (std::exception& e){
                handleNonFatalThreadException(e);
            }
        }
    } catch (std::exception& e) {
        handleFatalThreadException(e);
    }
    runFlag.store(false);
    finishCV.notify_one();
}

void ThreadCycler::handleNonFatalThreadException (std::exception&e) {
    throw;
}

void ThreadCycler::handleFatalThreadException(std::exception& e) {
    runFlag.store(false);
    finishCV.notify_one();
}

} // namespace helpers
} // namespace server