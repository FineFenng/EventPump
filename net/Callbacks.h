//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CALLBACKS_H
#define EVENTPUMP_CALLBACKS_H


#include <functional>
#include <event2/util.h>

namespace eventpump
{
typedef std::function<void()> ReadableCallback;
typedef std::function<void()> WritableCallback;
typedef std::function<void(int, struct sockaddr)> NewConnectionCallback;

}

#endif //EVENTPUMP_CALLBACKS_H
