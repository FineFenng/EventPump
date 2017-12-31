//
// Created by finefenng on 2017/12/28.
//

#include "Channel.h"

#include "EventLoop.h"

using namespace eventpump::net;

static const short Channel::kReadableEvent = EV_READ;
static const short Channel::kWritableEvent = EV_WRITE;
static const short Channel::kPersistEvent = EV_PERSIST;


Channel::Channel(EventLoop* loop,  evutil_socket_t fd)
: loop_(loop), fd_(fd), events_(0), event_(nullptr), index_(-1)
{
    event_ = event_new(loop_->eventBase(), fd_, events_, &Channel::Handle, this);
}

void Channel::update()
{
    loop_->updateChannel(this);
}

void Channel::handle(short events)
{
    if (events & EV_READ) {
        if (readableCallback_) { readableCallback_();
        }
    }
    if (events & EV_WRITE) {
        if (writableCallback_) {
            writableCallback_();
        }
    }

}

void Channel::Handle(evutil_socket_t fd, short events, void* arg)
{
    Channel* channel = reinterpret_cast<Channel*>(arg);
    channel->handle(events);
}




