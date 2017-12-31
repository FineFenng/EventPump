//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CHANNEL_H
#define EVENTPUMP_CHANNEL_H

#include <event2/util.h>


#include "Callbacks.h"

#include "boost/noncopyable.hpp"


namespace eventpump
{

namespace net
{


class EventLoop;

class Channel:boost::noncopyable
{
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();
    static void Handle(evutil_socket_t fd, short events, void* arg);

    void handle(short events);

    bool isReadable() { return static_cast<bool>(events_ &= kReadableEvent ); }
    bool isWritable() { return static_cast<bool>(events_ &= kWritableEvent); }

    void enableReadable() { events_ |= (kReadableEvent | kPersistEvent) ; update(); }
    void enableWritable() { events_ |= (kWritableEvent | kPersistEvent); update(); }

    void disableReadable() { events_ &= ~kReadableEvent; }
    void disableWritable() { events_ &= ~kWritableEvent; }

    void setReadableCallback(const ReadableCallback& cb) const { readableCallback_ = cb; }
    void setWritableCallback(const WritableCallback& cb) const { writableCallback_ = cb; }

    int fd() { return fd_; }
    short events() { return events_; }
    struct event* event() const { return event_; }

    int index() { return index_; }
    void setIndex(int idx) { index_ = idx; }

private:
    void update();

private:
    EventLoop* loop_;
    evutil_socket_t fd_;

    short events_;
    struct event* event_;

    ReadableCallback readableCallback_;
    WritableCallback writableCallback_;

    int index_;

    static const short kReadableEvent;
    static const short kWritableEvent;
    static const short kPersistEvent;

};

}
}


#endif //EVENTPUMP_CHANNEL_H
