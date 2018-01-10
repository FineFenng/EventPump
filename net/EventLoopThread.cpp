//
// Created by finefenng on 2018/1/7.
//

#include "EventLoopThread.h"

#include "EventLoop.h"

using namespace pump::net;

EventLoopThread::EventLoopThread()
		: loop_(nullptr), thread_(), mutex_(), cond_()
{

}

EventLoopThread::~EventLoopThread()
{

}

EventLoop* EventLoopThread::start()
{
	thread_ = std::move(std::thread(std::bind(&EventLoopThread::run, this)));
	{
		std::unique_lock<std::mutex> lock(mutex_);
		while (loop_ == nullptr) {
			cond_.wait(lock);
		}
	}
	return loop_;
}


void EventLoopThread::stop()
{
	loop_->stop();
}

void EventLoopThread::run()
{
	EventLoop loop;
	{
		std::lock_guard<std::mutex> lock(mutex_);
		loop_ = &loop;
		cond_.notify_one();
	}
	loop.run();
}


