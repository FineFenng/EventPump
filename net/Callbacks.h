//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CALLBACKS_H
#define EVENTPUMP_CALLBACKS_H


#include <functional>
#include "SocketsOps.h"
#include "InetAddress.h"


namespace eventpump
{

namespace net
{

typedef std::function<void()> ReadableCallback;
typedef std::function<void()> WritableCallback;
typedef std::function<void(HSocket, InetAddress&)> NewConnectionCallback;


}
}

#endif //EVENTPUMP_CALLBACKS_H
