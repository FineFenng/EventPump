//
// Created by finefenng on 2018/1/1.
//

#ifndef EVENTPUMP_ACCEPTOR_H
#define EVENTPUMP_ACCEPTOR_H


#include <boost/noncopyable.hpp>
#include <event2/listener.h>

#include "Callbacks.h"

#include "Socket.h"
#include "Watcher.h"



namespace eventpump
{

namespace net
{

class Pump;
class InetAddress
class Watcher;
class Acceptor : boost::noncopyable
{
public:
    Acceptor(Pump* pump, InetAddress& listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectionCallback& cb ) { newConnectionCallback_ = cb; }
	void listen();
	bool isListenig() const;

	void handleRead();
public:
private:



private:
	Pump* pump_;
	Socket socket_;
	Watcher watcher_;
	bool listening_;
    NewConnectionCallback newConnectionCallback_;

};

}
}


#endif //EVENTPUMP_ACCEPTOR_H
