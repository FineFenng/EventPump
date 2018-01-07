//
// Created by finefenng on 2018/1/1.
//

#include "Acceptor.h"
#include <glog/logging.h>
#include <boost/bind.hpp>
#include "SocketsOps.h"
#include <iostream>
#include <functional>

using namespace pump::net;

Acceptor::Acceptor(EventLoop* loop, InetAddress& listenAddr, bool reuseport)
: loop_(loop),
  listenAddr_(listenAddr),
  socket_(socketops::SocketOpen(SOCK_STREAM)),
  watcher_(loop_, socket_.fd()),
  listening_(false)
{
	socketops::SockReuseAddress(socket_.fd(), reuseport);
	watcher_.setReadableCallback(boost::bind(&Acceptor::handleRead,this));
}

Acceptor::~Acceptor()
{
	watcher_.disableAll();
	watcher_.removeWatcher();
}
void Acceptor::handleRead()
{
	struct sockaddr_in peeraddr;

	HSocket connfd = socketops::SocketAccept(socket_.fd(), &peeraddr);
	if (socketops::IsValidSocketHandle(connfd)) {
		if (newConnectionCallback_) {
			socketops::SocketBlock(connfd, false);
			InetAddress peerAddr(peeraddr);
			newConnectionCallback_(connfd, peerAddr);
		} else {
			socketops::SocketClose(connfd);
		}
	}
}

void Acceptor::listen()
{
	listening_ = true;
	socket_.bindAddress(listenAddr_);
	socket_.listen(30);
	watcher_.enableReadable();
}

bool Acceptor::isListening() const
{
	return listening_;
}
