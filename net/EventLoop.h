//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_EVENTLOOP_H
#define EVENTPUMP_EVENTLOOP_H

#include <event2/event.h>
#include <memory>
#include <map>
#include <vector>

#include "boost/noncopyable.hpp"


namespace eventpump
{

namespace net
{



class Channel;
class Poller;

typedef std::vector<Channel*> ChannelList;

class EventLoop : boost::noncopyable
{
public:
    static const int kNoLock;
public:
    EventLoop();
    EventLoop(struct event_config*& config, int flags = kNoLock);

    ~EventLoop();

    struct event_base* eventBase() const { return eventBase_; }

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

private:

private:
    struct event_config* config_;
    struct event_base* eventBase_;
    std::unique_ptr<Poller> poller_;
    ChannelList channelList_;
};

}
}

#endif //EVENTPUMP_EVENTLOOP_H

