//
// Created by finefenng on 2018/1/1.
//

#include "Socket.h"
#include "InetAddress.h"

using namespace eventpump::net;

Socket::~Socket()
{
	socketops::SocketClose(fd_);
}

void Socket::bindAddress(const InetAddress& addr)
{
	socketops::SocketBind(fd_, addr.getSockAddr());

}

void Socket::listen(int backlog)
{
	socketops::SocketListen(fd_, backlog);
}

void Socket::accept(InetAddress* addr)
{
	socketops::SocketAccept(fd_, addr->getSockAddr());
}




