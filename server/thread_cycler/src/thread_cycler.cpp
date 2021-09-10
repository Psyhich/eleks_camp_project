#include "thread_cycler.h"

namespace server {
namespace helpers {

ThreadCycler::~ThreadCycler() {
    stop();
}

void ThreadCycler::start() {
    if (stopFlag.load()){
        stopFlag.store(false);
        threadPtr.reset(new std::thread([this](){run();}));
    }
}

void ThreadCycler::stop() {
    if (!stopFlag.load()){
        stopFlag.store(true);
        threadPtr->join();
    }
}

void ThreadCycler::run() {
    while (true){
        work();
        if (stopFlag.load()){
            break;
        }
    }
}

} // namespace helpers
} // namespace server