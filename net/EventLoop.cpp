//
// Created by finefenng on 2018/1/2.
//

#include "EventLoop.h"

#include <glog/logging.h>

#include "Watcher.h"


using namespace pump::net;

thread_local EventLoop* t_eventLoop = nullptr;

EventLoop::EventLoop(BACKEND flags)
		: flags_(flags),
		  loop_(nullptr),
		  running_(false),
		  threadId_(),
		  idle_()
{

	if (t_eventLoop == nullptr) {
		t_eventLoop = this;
		threadId_ = std::this_thread::get_id();
		std::cout << "EventLoop[" << this << "] created in thread " << threadId_ << std::endl;

		if (!(loop_ = ev_loop_new(EVBACKEND_KQUEUE))) {
			std::cout << "Initial ev_loop struct failed" << std::endl;
		}

		idle_.set(loop_);
		idle_.set<EventLoop, &EventLoop::executeIdleEvent>(this);
		idle_.start();

	} else {
		std::cout << "Another EventLoop[" << t_eventLoop << "] exits in thread " << threadId_ << std::endl;
	}
}


EventLoop::~EventLoop()
{
	ev_loop_destroy(loop_);
}

void EventLoop::run()
{
	ev_run(loop_, 0);
}

void EventLoop::stop()
{
	idle_.stop();
	ev_break(loop_);
}

void EventLoop::updateWatcher(Watcher* watcher)
{
	ev::io* io = watcher->io();

	if (watcher->index() < 0) {
		watcherList_.push_back(watcher);
		watcher->setIndex(watcherList_.size() - 1);
		io->set(watcher->fd(), watcher->events());
		io->set(loop_);
	} else {
		if (ev_is_active(io)) {
			ev_io_stop(loop_, io);
		}
		io->set(watcher->events());
	}
	io->start();
}


void EventLoop::removeWatcher(Watcher* watcher)
{
	ssize_t idx = watcher->index();
	Watcher* deletedWatcher = watcherList_[idx];
	if (idx != watcherList_.size() - 1) {
		Watcher* lastWatcher = watcherList_.back();
		watcherList_[idx] = lastWatcher;
		lastWatcher->setIndex(idx);
	}
	deletedWatcher->io()->stop();
	watcherList_.pop_back();
}

void EventLoop::executeIdleEvent(ev::idle& idle, int revents)
{

	if (!idleWatcherEventList_.empty()) {
		std::vector<IdleCallback> cbs;

		{
			std::lock_guard<std::mutex> lock(mutex_);
			cbs.swap(idleWatcherEventList_);
		}

		for (auto it : cbs) {
			it();
		}
	}
}










