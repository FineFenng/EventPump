//
// Created by finefenng on 2018/1/1.
//

#include "Acceptor.h"
#include <glog/logging.h>

using namespace eventpump::net;

Acceptor::Acceptor(Pump* pump, InetAddress& listenAddr, bool reuseport)
: pump_(pump), socket_(socketops::SocketOpen(SOCK_STREAM)),
  watcher_(pump_, socket_.fd()), listening_(false), newConnectionCallback_(nullptr)
{
	watcher_.setReadableCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
	watcher_.disableAll();
	watcher_.removeWathcer();
}
void Acceptor::handleRead()
{
	struct sockaddr_in peeraddr;

	HSocket connfd = socketops::SocketAccept(socket_.fd(), &peeraddr);
	if (socketops::IsValidSocketHandle(connfd)) {
		if (newConnectionCallback_) {
			newConnectionCallback_(connfd, &peeraddr);
		} else {
			socketops::SocketClose(connfd);
		}
	}
	LOG(FATAL) << "todo";
}

void Acceptor::listen()
{
	listening_ = true;
	socket_.listen(30);
	watcher_.enableReadable();
}

bool Acceptor::isListenig() const
{
	return listening_;
}








