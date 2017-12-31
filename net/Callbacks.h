//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CALLBACKS_H
#define EVENTPUMP_CALLBACKS_H


#include <functional>

namespace eventpump
{
typedef std::function<void()> ReadableCallback;
typedef std::function<void()> WritableCallback;

}

#endif //EVENTPUMP_CALLBACKS_H
