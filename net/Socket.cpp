//
// Created by finefenng on 2018/1/1.
//

#include "Socket.h"
#include "InetAddress.h"

using namespace pump::net;

Socket::~Socket()
{
	socketops::SocketClose(fd_);
}

void Socket::bindAddress(InetAddress& addr)
{
	socketops::SocketBind(fd_, addr.sockAddr());

}

void Socket::listen(int backlog)
{
	socketops::SocketListen(fd_, backlog);
}

void Socket::accept(InetAddress* addr)
{
	socketops::SocketAccept(fd_, addr->sockAddr());
}




