//
// Created by finefenng on 2018/1/5.
//

#ifndef EVENTPUMP_TCPSERVER_H
#define EVENTPUMP_TCPSERVER_H

#include <boost/noncopyable.hpp>
#include <map>
#include <memory>
#include <string>

#include "Callbacks.h"
#include "TcpConnection.h"

namespace eventpump
{
namespace net
{

class Acceptor;
class Pump;
class TcpServer:boost::noncopyable
{
public:
	TcpServer(Pump* pump, InetAddress& listenAddr);
	~TcpServer();

	void start();
	void newConnection(int sockfd, const InetAddress& peerAddr);
	void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }

private:
	typedef std::map<std::string,TcpConnectionPtr> ConnectionMap;



	Pump* pump_;
	const std::string name_;
	std::unique_ptr<Acceptor> acceptor_;
	NewConnectionCallback newConnectionCallback_;
	bool started_;
	int nextConnId_;
	ConnectionMap connections_;
};
}

}


#endif //EVENTPUMP_TCPSERVER_H
