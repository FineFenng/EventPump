//
// Created by finefenng on 2018/1/1.
//

#ifndef EVENTPUMP_ACCEPTOR_H
#define EVENTPUMP_ACCEPTOR_H


#include <boost/noncopyable.hpp>

#include "Callbacks.h"

#include "Socket.h"
#include "Watcher.h"


namespace pump
{

namespace net
{

class EventLoop;

class InetAddress;

class Watcher;

class Acceptor : boost::noncopyable
{
public:
	Acceptor(EventLoop* loop, InetAddress& listenAddr, bool reuseport);

	~Acceptor();

	void setNewConnectionCallback(const NewConnectionCallback& cb) { newConnectionCallback_ = cb; }

	void listen();

	bool isListening() const;

	void handleRead();

private:
	EventLoop* loop_;
	InetAddress listenAddr_;
	Socket socket_;
	Watcher watcher_;
	bool listening_;
	NewConnectionCallback newConnectionCallback_;

};

}
}


#endif //EVENTPUMP_ACCEPTOR_H
