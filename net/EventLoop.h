//
// Created by finefenng on 2018/1/2.
//

#ifndef EVENTPUMP_PUMP_H
#define EVENTPUMP_PUMP_H

#include <boost/noncopyable.hpp>
#include <ev++.h>
#include <map>
#include <thread>
#include <vector>


namespace pump
{

enum class BACKEND : unsigned int
{
    kDefault = EVFLAG_AUTO,
    KSelect = EVBACKEND_SELECT,
    KPoll = EVBACKEND_POLL,
    KEPoll = EVBACKEND_EPOLL,
    kKQueue = EVBACKEND_KQUEUE,
};


/*

enum class RUN : int
{
    kNOWAIT = EVRUN_NOWAIT,
    kONCE = EVRUN_ONCE,
};

 */

namespace net
{

class EventLoop;
class Watcher;

class EventLoop : boost::noncopyable
{
public:
    explicit EventLoop(BACKEND backend = BACKEND::kDefault);
    ~EventLoop();

public:
    void run();
    void stop();

public:
    void updateWatcher(Watcher* watcher);
    void removeWatcher(Watcher* watcher);

private:
    BACKEND flags_;
    struct ev_loop* loop_;
	bool running_;
	std::thread::id threadId_;

private:
    typedef std::vector<Watcher*> WatcherList;

    WatcherList watcherList_;
};

}
}


#endif //EVENTPUMP_PUMP_H
