//
// Created by finefenng on 2018/1/5.
//

#ifndef EVENTPUMP_TCPCONNECTION_H
#define EVENTPUMP_TCPCONNECTION_H

#include <boost/noncopyable.hpp>
#include <string>
#include <memory>

#include "Callbacks.h"
#include "InetAddress.h"
#include "SocketsOps.h"

namespace eventpump
{
namespace net
{


class Pump;
class InetAddress;
class Socket;
class Watcher;
class TcpConnection : boost::noncopyable
{
public:
	TcpConnection(Pump* pump,
	              const std::string& name,
	              HSocket fd,
	              const InetAddress& localAddr,
	              const InetAddress& peerAddr);

	~TcpConnection();

	const std::string name() const { return name_; }

public:
	void handleRead();
	void handleWrite();
private:
	enum StateE {
		kConnecting,
		kConnected,
		kDisconnecting,
		kDisconnected,
	};

	Pump* pump_;
	std::string name_;
	HSocket fd_;
	StateE state_;
	std::unique_ptr<Socket> socket_;
	std::shared_ptr<Watcher> watcher_;
	InetAddress localAddr_;
	InetAddress peerAddr_;


	NewConnectionCallback newConnectionCallback_;
};
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
}

}


#endif //EVENTPUMP_TCPCONNECTION_H
