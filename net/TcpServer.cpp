//
// Created by finefenng on 2018/1/5.
//

#include "TcpServer.h"
#include "Acceptor.h"
#include <boost/bind.hpp>

#include <glog/logging.h>
#include <iostream>

using namespace pump::net;
using namespace boost::placeholders;

TcpServer::TcpServer(EventLoop* loop, InetAddress& listenAddr)
		: loop_(loop),
		  name_(listenAddr.toIpPort()),
		  acceptor_(new Acceptor(loop_, listenAddr, true)),
		  started_(false),
		  nextConnId_(1)
{
	acceptor_->setNewConnectionCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
	std::cout << "建立服务器成功" << std::endl;
}

void TcpServer::start()
{
	if (!started_) {
		started_ = true;
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
	TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockfd, localAddr, peerAddr));
	connections_[connName] = conn;
	newConnectionCallback_(sockfd, peerAddr);
}

TcpServer::~TcpServer()
{



}

