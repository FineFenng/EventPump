//
// Created by finefenng on 2018/1/5.
//

#include "TcpServer.h"
#include "Acceptor.h"

#include <glog/logging.h>
#include <memory>

using namespace eventpump::net;
using namespace std::placeholders;

TcpServer::TcpServer(Pump* pump, InetAddress& listenAddr)
:pump_(pump), name_(listenAddr.toIpPort()), acceptor_(new Acceptor(pump_, listenAddr, true)), started_(false), nextConnId_(1)
{
	acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, _1, _2));

}

void TcpServer::start()
{
	if (!started_) {
		started_ = true;
	}

	if (!acceptor_->isListennig()) {
		acceptor_->listen();
	}
}

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
	char buff[32] = {0};
	snprintf(buff, sizeof(buff), "#%d", nextConnId_);
	nextConnId_++;
	std::string connName = name_ + buff;

	LOG(INFO) << "TcpServer::newConnection [" << name_
	          << "] - new connection [" << connName
	          << "] from" << peerAddr.toIpPort();

	InetAddress localAddr(socketops::SocketGetLocalAddr(sockfd));

	TcpConnectionPtr conn = std::make_shared(pump_, connName, sockfd, localAddr, peerAddr);
	connections_[connName] = conn;
}

