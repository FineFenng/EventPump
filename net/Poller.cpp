//
// Created by finefenng on 2017/12/28.
//

#include "Poller.h"

#include "Channel.h"
#include "EventLoop.h"

using namespace eventpump::net;

Poller::Poller(EventLoop* loop, int flags = EVLOOP_ONCE)
: loop_(loop), flags_(flags)
{


}

void Poller::poll()
{
    event_base_loop(loop_->eventBase(), flags_);
}

Poller::~Poller()
{
    event_base_loopexit(loop_->eventBase(), nullptr);
}

void Poller::updateChannel(Channel* channel)
{
    /*
    event_set(channel->event(), channel->fd(), channel->events(), &Channel::Handle, channel);
     */

    if (channel->index() < 0) {
        channelList_.push_back(channel);
        int idx = static_cast<int>(channelList_.size()) - 1;
        channel->setIndex(idx);
        event_add(channel->event(), nullptr);
    } else {
        event_set(channel->event(), channel->fd(), channel->events(), &Channel::Handle, channel);
    }
}

void Poller::removeChannel(Channel* channel)
{



}
