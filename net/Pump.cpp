//
// Created by finefenng on 2018/1/2.
//

#include "Pump.h"

#include <glog/logging.h>

#include "Watcher.h"

using namespace eventpump::net;

Pump::Pump(BACKEND flags)
: flags_(flags), loop_(nullptr)
{

    if (t_pump == nullptr) {
        t_pump = this;
        LOG(INFO) << "EventPump " << this << "created in thread ";

        if (!(loop_ = ev_loop_new(static_cast<unsigned int>(flags_)))) {
            LOG(FATAL) << "Initial ev_loop struct failed";
        }

    } else {
        LOG(FATAL) << "Another EventPump " << t_pump << "exits in thread ";
    }
}

Pump::Pump() : Pump(BACKEND::kDefault)
{

}

Pump::~Pump()
{
    ev_loop_destroy(loop_);
}

void Pump::run(eventpump::RUN runOption)
{
    ev_run(loop_, static_cast<int>(runOption));
}

void Pump::stop()
{
    ev_break(loop_);
}

Watcher* Pump::findWatcher(struct ev_io* watcher) const
{
    watcherMap_.find(watcher)->second;
}

void Pump::updateWatcher(Watcher* watcher)
{
    struct ev_io* ioPtr = watcher->io();
    if (watcher->index() < 0) {
        watcherList_.push_back(watcher);
        watcher->setIndex(watcherList_.size() - 1);
        ev_io_set(ioPtr, watcher->fd(), watcher->events());
    } else {
        if (ev_is_active(ioPtr)) {
            ev_io_stop(loop_, ioPtr);
        }
        ev_io_set(ioPtr, watcher->fd(), watcher->events());
    }
    ev_io_start(loop_, ioPtr);
}


void Pump::removeWatcher(Watcher* watcher)
{
    ssize_t idx = watcher->index();
    Watcher* deletedWatcher = watcherList_[idx];
    if (idx != watcherList_.size() - 1) {
        Watcher* lastWatcher = watcherList_.back();
        watcherList_[idx] = lastWatcher;
        lastWatcher->setIndex(idx);
    }
    ev_io_stop(loop_, deletedWatcher->io());
    watcherList_.pop_back();
}










