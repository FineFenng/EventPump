//
// Created by finefenng on 2018/1/5.
//

#include "TcpConnection.h"

#include "Socket.h"
#include "Watcher.h"

using namespace eventpump::net;
using namespace std::placeholders;

TcpConnection::TcpConnection(eventpump::net::Pump* pump, const std::string& name, HSocket fd,
                             const eventpump::net::InetAddress& localAddr,
                             const eventpump::net::InetAddress& peerAddr)
		: pump_(pump), name_(name), fd_(fd), localAddr_(localAddr), peerAddr_(peerAddr),
		  socket_(new Socket(fd_)), watcher_(std::make_shared(pump_, fd_))
{
	watcher_->setReadableCallback(std::bind(&TcpConnection::handleRead, this, _1));
	watcher_->setWritableCallback(std::bind(&TcpConnection::handleWrite, this));
}

TcpConnection::~TcpConnection()
{

}
