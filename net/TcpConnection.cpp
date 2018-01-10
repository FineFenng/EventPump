//
// Created by finefenng on 2018/1/5.
//

#include "TcpConnection.h"

#include <iostream>

#include "EventLoop.h"
#include "Socket.h"
#include "Watcher.h"
#include "../util/Buffer.h"


using namespace pump::net;
using namespace pump::util;
using namespace boost::placeholders;

TcpConnection::TcpConnection(pump::net::EventLoop* pump, const std::string& name, HSocket fd,
                             const pump::net::InetAddress& localAddr,
                             const pump::net::InetAddress& peerAddr)
		: loop_(pump), name_(name), fd_(fd), localAddr_(localAddr), peerAddr_(peerAddr),
		  socket_(new Socket(fd_)), watcher_(new Watcher(loop_, fd_)), inputBuffer_(new Buffer()), outputBuffer_(new Buffer())
{
	watcher_->setReadableCallback(boost::bind(&TcpConnection::handleRead, this));
	watcher_->setWritableCallback(boost::bind(&TcpConnection::handleWrite, this));
	watcher_->enableReadable();
}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::handleRead()
{
	int saveErrno = 0;
	ssize_t n = inputBuffer_->readSockFd(socket_->fd(), &saveErrno);
	if (n > 0) {
		messageCallback_(shared_from_this(), inputBuffer_);
	} else if (n == 0) {
		handleClose();
	} else {
		errno = saveErrno;
		handleError();
	}

}

void TcpConnection::handleWrite()
{

}

void TcpConnection::handleClose()
{
	watcher_->disableAll();
	closedCallback_(shared_from_this());
}

void TcpConnection::handleError()
{

}

void TcpConnection::connectDestoryed()
{
	watcher_->disableAll();
	loop_->removeWatcher(watcher_.get());
	std::cout << "断开连接:" << peerAddr_.toIpPort() << std::endl;
}
