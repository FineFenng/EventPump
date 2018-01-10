//
// Created by finefenng on 2018/1/7.
//

#ifndef EVENTPUMP_EVENTLOOPTHREAD_H
#define EVENTPUMP_EVENTLOOPTHREAD_H

#include <boost/noncopyable.hpp>
#include <condition_variable>
#include <mutex>
#include <thread>

namespace pump
{

namespace net
{


class EventLoop;

class EventLoopThread : boost::noncopyable
{
public:
	EventLoopThread();

	~EventLoopThread();

	EventLoop* start();

	void stop();

private:
	void run();

	int index_;
	EventLoop* loop_;
	std::thread thread_;
	std::mutex mutex_;
	std::condition_variable cond_;
};

}

}


#endif //EVENTPUMP_EVENTLOOPTHREAD_H
