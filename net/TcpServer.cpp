//
// Created by finefenng on 2018/1/5.
//

#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoopThreadPool.h"
#include "Acceptor.h"
#include "EventLoop.h"
#include <boost/bind.hpp>
#include <cassert>

#include <iostream>

using namespace pump::net;
using namespace boost::placeholders;

TcpServer::TcpServer(EventLoop* loop, InetAddress& listenAddr)
		: loop_(loop),
		  name_(listenAddr.toIpPort()),
		  acceptor_(new Acceptor(loop_, listenAddr, true)),
		  threadNum_(0),
		  started_(false),
		  nextConnId_(1),
		  loops_(),
		  threadPool_(new EventLoopThreadPool(loop_))
{
	acceptor_->setNewConnectionCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
	std::cout << "建立服务器成功" << std::endl;
	initialEventLoopThreadPool();
}

void TcpServer::start()
{
	if (!started_) {
		started_ = true;
		threadPool_->start();
	}

	if (!acceptor_->isListening()) {
		acceptor_->listen();
	}
}

void TcpServer::newConnection(int sockfd, InetAddress& peerAddr)
{
	char buff[32] = {0};
	snprintf(buff, sizeof(buff), "#%d", nextConnId_);
	++nextConnId_;
	std::string connName = name_ + buff;

	std::cout << "TcpServer::newConnection[" << name_
	          << "] - new connection [" << connName
	          << "] from " << peerAddr.toIpPort() << std::endl;

	InetAddress localAddr(socketops::SocketGetLocalAddr(sockfd));
	EventLoop* nextLoop = threadPool_->getNextLoop();
	TcpConnectionPtr conn(new TcpConnection(nextLoop, connName, sockfd, localAddr, peerAddr));
	connections_[connName] = conn;
	conn->setMessageCallback(messageCallback_);
	conn->setClosedCallback(boost::bind(&TcpServer::removeConnection, this, _1));
	newConnectionCallback_(sockfd, peerAddr);

}

TcpServer::~TcpServer()
{
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
	loop_->queueInIdleEventList(boost::bind(&TcpServer::removeConnectionInIdle, this, conn));
}


void TcpServer::removeConnectionInIdle(const TcpConnectionPtr& conn)
{
	size_t n = connections_.erase(conn->name());
	assert(n == 1);
	EventLoop* ioLoop = conn->getLoop();
	ioLoop->queueInIdleEventList(boost::bind(&TcpConnection::connectDestoryed, conn));
}

void TcpServer::initialEventLoopThreadPool()
{
	threadPool_->setThreadNum(threadNum_);
}

void TcpServer::setThreadNum(int threadNum)
{

	if (threadNum < threadNum_) {
		threadNum_ = threadNum;
	}
}
