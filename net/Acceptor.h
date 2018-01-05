//
// Created by finefenng on 2018/1/1.
//

#ifndef EVENTPUMP_ACCEPTOR_H
#define EVENTPUMP_ACCEPTOR_H


#include <boost/noncopyable.hpp>
#include <event2/listener.h>

#include "Callbacks.h"



namespace eventpump
{

namespace net
{

class Pump;
class InetAddress
class Acceptor : boost::noncopyable
{
public:
    Acceptor(Pump* pump, InetAddress& listenAddr, bool reuseport);
    ~Acceptor();

    void listen(const char* serverIp, unsigned short serverPort);
    void setNewConnectionCallback(const NewConnectionCallback& cb ) { newConnectionCallback_ = cb; }

public:



private:

    EventPump* eventPump_;
    struct evconnlistener* listener_;
    NewConnectionCallback newConnectionCallback_;

};

}
}


#endif //EVENTPUMP_ACCEPTOR_H
