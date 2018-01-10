//
// Created by finefenng on 2018/1/8.
//

#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"

using namespace pump::net;


EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop)
		: baseLoop_(baseLoop),
		  started_(false),
		  threadNum_(0),
		  next_(0)
{


}

EventLoopThreadPool::~EventLoopThreadPool()
{

}

void EventLoopThreadPool::start()
{
	started_ = true;

	for (int i = 0; i < threadNum_; ++i) {
		EventLoopThread* t = new EventLoopThread();
		threads_.push_back(t);
		loops_.push_back(t->start());
	}
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
	EventLoop* loop = baseLoop_;

	if (!loops_.empty()) {
		loop = loops_[next_++];
		if (static_cast<size_t>(next_) >= loops_.size()) {
			next_ = 0;
		}
	}
	return loop;
}

