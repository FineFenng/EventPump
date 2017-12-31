//
// Created by finefenng on 2017/12/28.
//

#include "EventLoop.h"
#include "Channel.h"
#include "Poller.h"

#include <iostream>


using namespace eventpump::net;

thread_local EventLoop* t_eventLoop = nullptr;

static  const int EventLoop::kNoLock = EVENT_BASE_FLAG_NOLOCK;

EventLoop::EventLoop()
        : eventBase_(event_base_new()), poller_(new Poller(this))
{
    if (t_eventLoop == nullptr) {
        t_eventLoop = this;
    } else {
        std::cout << "Another EventLoop " << t_eventLoop
                  << "has exits in this thread \n";
    }
}


EventLoop::EventLoop(struct event_config*& config, int flags = kNoLock)
    : config_(event_config_new()), poller_(new Poller(this)), eventBase_(nullptr)
{
     if (t_eventLoop == nullptr) {
        t_eventLoop = this;
    } else {
        std::cout << "Another EventLoop " << t_eventLoop
                  << "has exits in this thread \n";
    }

    event_config_set_flag(config_, flags);
    eventBase_ = event_base_new_with_config(config_);
}


EventLoop::~EventLoop()
{
    event_base_free(eventBase_);
}

void EventLoop::updateChannel(Channel* channel)
{
    poller_->updateChannel(channel);

}

void EventLoop::removeChannel(Channel* channel)
{

}


