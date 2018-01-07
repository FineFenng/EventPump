//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CALLBACKS_H
#define EVENTPUMP_CALLBACKS_H

#include <boost/function.hpp>
#include "SocketsOps.h"
#include "InetAddress.h"


namespace pump
{

namespace net
{

typedef boost::function<void()> ReadableCallback;
typedef boost::function<void()> WritableCallback;
typedef boost::function<void(HSocket, InetAddress&)> NewConnectionCallback;

}
}

#endif //EVENTPUMP_CALLBACKS_H
