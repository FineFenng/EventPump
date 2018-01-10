//
// Created by finefenng on 2018/1/2.
//

#ifndef EVENTPUMP_PUMP_H
#define EVENTPUMP_PUMP_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <ev++.h>
#include <map>
#include <mutex>
#include <thread>
#include <vector>
#include <iostream>


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

public:
	typedef boost::function<void()> IdleCallback;

	void queueInIdleEventList(const IdleCallback& cb)
	{
		idleWatcherEventList_.push_back(cb);
	}

	void executeIdleEvent(ev::idle& idle, int revents);


private:
	BACKEND flags_;
	struct ev_loop* loop_;
	bool running_;
	std::thread::id threadId_;


private:
	typedef std::vector<Watcher*> IOWatcherList;
	typedef std::vector<boost::function<void()>> IdleEventList;
	ev::idle idle_;

	IOWatcherList watcherList_;
	IdleEventList idleWatcherEventList_;
	std::mutex mutex_;
};

}
}


#endif //EVENTPUMP_PUMP_H
