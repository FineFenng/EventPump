//
// Created by finefenng on 2018/1/1.
//

#ifndef EVENTPUMP_SOCKET_H
#define EVENTPUMP_SOCKET_H

#include <boost/noncopyable.hpp>

#include "SocketsOps.h"

namespace pump
{


namespace net
{

class InetAddress;
class Socket : boost::noncopyable
{
public:
	explicit Socket(HSocket fd)
	: fd_(fd)
	{ }

	~Socket();

public:
	HSocket fd () const { return fd_; }
	void bindAddress(InetAddress& addr);
	void listen(int backlog);
	void accept(InetAddress* addr);

private:
    HSocket fd_;
};

}
}


#endif //EVENTPUMP_SOCKET_H
