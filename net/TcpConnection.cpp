//
// Created by finefenng on 2018/1/5.
//

#include "TcpConnection.h"

#include "Socket.h"
#include "Watcher.h"

#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace pump::net;
using namespace boost::placeholders;

TcpConnection::TcpConnection(pump::net::EventLoop* pump, const std::string& name, HSocket fd,
                             const pump::net::InetAddress& localAddr,
                             const pump::net::InetAddress& peerAddr)
		: pump_(pump), name_(name), fd_(fd), localAddr_(localAddr), peerAddr_(peerAddr),
		  socket_(new Socket(fd_)), watcher_(new Watcher(pump_, fd_))
{
	watcher_->setReadableCallback(boost::bind(&TcpConnection::handleRead, this));
	watcher_->setWritableCallback(boost::bind(&TcpConnection::handleWrite, this));
}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::handleRead()
{

}

void TcpConnection::handleWrite()
{

}
