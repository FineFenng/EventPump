//
// Created by finefenng on 2018/1/1.
//

#include "Acceptor.h"

#include <event2/listener.h>
using namespace eventpump::net;


void Acceptor::listen(const char* serverIp, unsigned short serverPort)
{
    listener_ = evconnlistener_new_bind(eventPump_->eventBase(), )



}
