//
// Created by finefenng on 2018/1/2.
//

#include "EventLoop.h"

#include <glog/logging.h>
#include <iostream>

#include "Watcher.h"


using namespace pump::net;

thread_local EventLoop* t_eventLoop = nullptr;

EventLoop::EventLoop(BACKEND flags)
		: flags_(flags), loop_(nullptr), running_(false), threadId_()
{

	if (t_eventLoop == nullptr) {
		t_eventLoop = this;
		threadId_ = std::this_thread::get_id();
		std::cout << "EventLoop[" << this << "] created in thread " << threadId_ << std::endl;

		if (!(loop_ = ev_loop_new(static_cast<unsigned int>(flags_)))) {
			std::cout << "Initial ev_loop struct failed" << std::endl;
		}

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
	ev_io_stop(loop_, deletedWatcher->io());
	watcherList_.pop_back();
}










