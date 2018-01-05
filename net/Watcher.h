//
// Created by finefenng on 2018/1/2.
//

#ifndef EVENTPUMP_WATCHER_H
#define EVENTPUMP_WATCHER_H

#include <ev.h>
#include <boost/noncopyable.hpp>

#include "Callbacks.h"


namespace eventpump
{


enum class EVENT
{
    kRead = EV_READ,
    kWrite = EV_WRITE,
};

namespace net
{


class Pump;
class Watcher : boost::noncopyable
{

public:
    Watcher(Pump* pump, int sockfd);

    friend void Handle(ev_loop* loop, struct ev_io* io_watcher, int revents);

    ReadableCallback readableCallback() const { return readableCallback_; }
    WritableCallback writableCallback() const { return writableCallback_; }

    bool isReadable() { return static_cast<bool>(events_ &= EV_READ ); }
    bool isWritable() { return static_cast<bool>(events_ &= EV_WRITE); }

    void enableReadable() { events_ |= EV_READ ; updateWatcher(); }
    void enableWritable() { events_ |= EV_WRITE; updateWatcher(); }

    void disableReadable() { events_ &= ~EV_READ; updateWatcher(); }
    void disableWritable() { events_ &= ~EV_WRITE; updateWatcher(); }
    void disableAll() { events_ = 0; updateWatcher(); }

    void setReadableCallback(const ReadableCallback& cb) const { readableCallback_ = cb; }
    void setWritableCallback(const WritableCallback& cb) const { writableCallback_ = cb; }

    ssize_t index() const { return index_; }
    void setIndex(ssize_t idx) { index_ = idx; }
    int events() const { return events_; }
    int revents() const { return revents_; }
    Pump* pump() const { return pump_; }
    int fd() const { return sockfd_;}
    struct ev_io* io() const { return io_; }

	void removeWathcer();
private:
    void init();
    void handle(int revents);
    void updateWatcher();
private:

    ssize_t index_;
    int events_;
    int revents_;
    Pump* pump_;
    int sockfd_;
    struct ev_io* io_;

    ReadableCallback readableCallback_;
    WritableCallback writableCallback_;
};

void Handle(ev_loop* loop, struct ev_io* io_watcher, int revents);
}
}


#endif //EVENTPUMP_WATCHER_H
