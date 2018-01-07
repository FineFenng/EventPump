//
// Created by finefenng on 2018/1/2.
//

#include "Watcher.h"

#include "EventLoop.h"


using namespace pump::net;


Watcher::Watcher(EventLoop* loop, int sockfd)
		: loop_(loop),
		  io_(new ev::io()),
		  index_(-1),
		  sockfd_(sockfd),
		  events_(0),
		  revents_(0)
{
	init();
}

void Watcher::operator()(ev::io& io, int revents)
{

	if (revents && EV_READ) {
		if (readableCallback_) readableCallback_();
	}

	if (revents && EV_WRITE) {
		if (writableCallback_) writableCallback_();
	}
}

void Watcher::init()
{
	io_->set(this);
}

void Watcher::updateWatcher()
{
	loop_->updateWatcher(this);
}


void Watcher::removeWatcher()
{
	loop_->removeWatcher(this);
}


