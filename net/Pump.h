//
// Created by finefenng on 2018/1/2.
//

#ifndef EVENTPUMP_PUMP_H
#define EVENTPUMP_PUMP_H

#include <boost/noncopyable.hpp>

#include <ev.h>
#include <map>
#include <vector>

namespace eventpump
{
enum class BACKEND : unsigned int
{
    kDefault = EVFLAG_AUTO,
    KSelect = EVBACKEND_SELECT,
    KPoll = EVBACKEND_POLL,
    KEPoll = EVBACKEND_EPOLL,
    kKQueue = EVBACKEND_KQUEUE,
};

enum class RUN : int
{
    kNOWAIT = EVRUN_NOWAIT,
    kONCE = EVRUN_ONCE,
};


namespace net
{

class Pump;

thread_local Pump* t_pump = nullptr;

class Watcher;
class Pump : boost::noncopyable
{
public:

    explicit Pump(BACKEND backend);
    Pump();

    ~Pump();

public:
    void run(RUN runOption);
    void stop();
    Watcher* findWatcher(struct ev_io* watcher) const;

public:
    struct ev_loop* ev_loop() const { return loop_; }
    void updateWatcher(Watcher* watcher);
    void removeWatcher(Watcher* watcher);


private:
    BACKEND flags_;
    struct ev_loop* loop_;
	bool running_;
private:
    typedef std::map<struct ev_io*, Watcher*> WatcherMap;
    typedef std::vector<Watcher*> WatcherList;
    WatcherMap watcherMap_;
    WatcherList watcherList_;
};

}
}


#endif //EVENTPUMP_PUMP_H
