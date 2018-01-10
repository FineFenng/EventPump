//
// Created by finefenng on 2018/1/8.
//

#ifndef EVENTPUMP_EVENTLOOPTHREADPOOL_H
#define EVENTPUMP_EVENTLOOPTHREADPOOL_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <thread>

namespace pump
{

namespace net
{


class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : boost::noncopyable
{
public:
	EventLoopThreadPool(EventLoop* baseLoop);

	~EventLoopThreadPool();

	void setThreadNum(int threadNum)
	{
		threadNum_ = threadNum;
	}

	void start();

	EventLoop* getNextLoop();

private:
	EventLoop* baseLoop_;
	bool started_;
	int threadNum_;
	int next_;
	std::vector<EventLoopThread*> threads_;
	std::vector<EventLoop*> loops_;


};
}

}


#endif //EVENTPUMP_EVENTLOOPTHREADPOOL_H
