//
// Created by finefenng on 2018/1/2.
//

#ifndef EVENTPUMP_WATCHER_H
#define EVENTPUMP_WATCHER_H

#include <boost/noncopyable.hpp>
#include <ev++.h>

#include "Callbacks.h"

namespace pump
{

namespace net
{

class EventLoop;
class Watcher : boost::noncopyable
{
public:
    Watcher(EventLoop *loop, int sockfd);


    ReadableCallback readableCallback() const { return readableCallback_; }
    WritableCallback writableCallback() const { return writableCallback_; }

    bool isReadable() { return static_cast<bool>(events_ &= ev::READ ); }
    bool isWritable() { return static_cast<bool>(events_ &= ev::WRITE); }

    void enableReadable() { events_ |= ev::READ ; updateWatcher(); }
    void enableWritable() { events_ |= ev::WRITE; updateWatcher(); }

    void disableReadable() { events_ &= ~ev::READ; updateWatcher(); }
    void disableWritable() { events_ &= ~ev::WRITE; updateWatcher(); }
    void disableAll() { events_ = 0; updateWatcher(); }

    void setReadableCallback(const ReadableCallback& cb) { readableCallback_ = cb; }
    void setWritableCallback(const WritableCallback& cb) { writableCallback_ = cb; }

    ssize_t index() const { return index_; }
    void setIndex(ssize_t idx) { index_ = idx; }
    int events() const { return events_; }
    int revents() const { return revents_; }
    EventLoop* pump() const { return loop_; }
    int fd() const { return sockfd_;}
    ev::io* io() const { return io_; }

	void operator()(ev::io& io, int revents);
	void removeWatcher();
private:
    void init();
    void updateWatcher();
private:

    ssize_t index_;
    int events_;
    int revents_;
    EventLoop* loop_;
    int sockfd_;
    ev::io* io_;

	ReadableCallback readableCallback_;
    WritableCallback writableCallback_;
};

}
}


#endif //EVENTPUMP_WATCHER_H
