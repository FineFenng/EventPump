//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_POLLER_H
#define EVENTPUMP_POLLER_H


#include <evrpc.h>

#include <vector>

#include "boost/noncopyable.hpp"

namespace eventpump
{

namespace net
{


class EventLoop;
class Channel;

typedef std::vector<Channel*> ChannelList;

class Poller :boost::noncopyable
{
public:
    Poller(EventLoop* loop, int flags = EVLOOP_ONCE);

    ~Poller();

    void poll();

    int flags() { return flags_; }
    void setFlags(int flags) { flags_ = flags; }

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);


private:
    EventLoop* loop_;
    int flags_;
    ChannelList channelList_;
};

}

}


#endif //EVENTPUMP_POLLER_H
