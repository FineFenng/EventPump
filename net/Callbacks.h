//
// Created by finefenng on 2017/12/28.
//

#ifndef EVENTPUMP_CALLBACKS_H
#define EVENTPUMP_CALLBACKS_H

#include <boost/function.hpp>
#include "SocketsOps.h"
#include "InetAddress.h"
#include "../util/Buffer.h"

using namespace pump::util;

namespace pump
{

namespace net
{

class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

typedef boost::function<void()> ReadableCallback;
typedef boost::function<void()> WritableCallback;
typedef boost::function<void(HSocket, InetAddress&)> NewConnectionCallback;
typedef boost::function<void(const TcpConnectionPtr&, Buffer*)> MessageCallback;
typedef boost::function<void(const TcpConnectionPtr&)> ClosedCallback;


}
}

#endif //EVENTPUMP_CALLBACKS_H
