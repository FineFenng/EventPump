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

namespace pump
{
namespace net
{



class EventLoop;

class InetAddress;

class Socket;

class Watcher;

class TcpConnection : boost::noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(EventLoop* pump,
	              const std::string& name,
	              HSocket fd,
	              const InetAddress& localAddr,
	              const InetAddress& peerAddr);

	~TcpConnection();

	EventLoop* getLoop()
	{
		return loop_;
	}

	const std::string name() const
	{ return name_; }

	void setMessageCallback(const MessageCallback& cb)
	{
		messageCallback_ = cb;
	}

	void setWritableCallback(const WritableCallback& cb)
	{
		writableCallback_ = cb;
	}

	void setClosedCallback(const ClosedCallback& cb)
	{
		closedCallback_ = cb;
	}

	void send(const std::string& message);
	void send(const char* message);
	void shutdown();


public:
	void handleRead();

	void handleWrite();

	void connectDestoryed();

private:
	void handleClose();

	void handleError();

	void sendInIdle();
	void shutdownInIdle();


private:
	enum StateE
	{
		kConnecting,
		kConnected,
		kDisconnecting,
		kDisconnected,
	};

	EventLoop* loop_;
	std::string name_;
	HSocket fd_;
	StateE state_;
	std::unique_ptr<Socket> socket_;
	std::shared_ptr<Watcher> watcher_;
	InetAddress localAddr_;
	InetAddress peerAddr_;

	Buffer* inputBuffer_;
	Buffer* outputBuffer_;

	MessageCallback messageCallback_;
	WritableCallback writableCallback_;
	ClosedCallback closedCallback_;
};

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
}

}


#endif //EVENTPUMP_TCPCONNECTION_H
