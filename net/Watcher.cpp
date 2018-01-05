//
// Created by finefenng on 2018/1/2.
//

#include "Watcher.h"

#include <cassert>
#include "Pump.h"


using namespace eventpump::net;

namespace
{

void eventpump::net::Handle(ev_loop* loop, struct ev_io* io_watcher, int revents)
{
    Watcher* watcher = t_pump->findWatcher(io_watcher);

    assert(loop == t_pump->ev_loop());
    watcher->handle(revents);

}

}


Watcher::Watcher(Pump* pump, int sockfd)
        : io_(static_cast<struct ev_io*>(malloc(sizeof(struct ev_io)))),
          index_(-1), sockfd_(sockfd), events_(0), revents_(0), pump_(pump),
          readableCallback_(), writableCallback_()
{
    init();
}

void Watcher::handle(int revents)
{

    if (revents && EV_READ) {
        if (readableCallback()) readableCallback()();
    }

    if (revents && EV_WRITE) {
        if (writableCallback()) readableCallback()();
    }
}

void Watcher::init()
{
    ev_init(io_, Handle);

}

void Watcher::updateWatcher()
{
    pump_->updateWatcher(this);
}


void Watcher::removeWathcer()
{
    pump_->removeWatcher(this);
}


