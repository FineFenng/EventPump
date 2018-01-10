//
// Created by finefenng on 2018/1/5.
//

#ifndef EVENTPUMP_INETADDRESS_H
#define EVENTPUMP_INETADDRESS_H

#include <cstdint>
#include <string>
#include "SocketsOps.h"

namespace pump
{
namespace net
{

class InetAddress
{
public:
	explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);

	InetAddress(const char* ip, uint16_t port);

	explicit InetAddress(const struct sockaddr_in addr)
			: addr_(addr)
	{ }

	sa_family_t family() const
	{ return addr_.sin_family; }

	std::string toIp() const;

	uint16_t toPort() const;

	std::string toIpPort() const;

	struct sockaddr_in* sockAddr()
	{ return &addr_; }

private:
	struct sockaddr_in addr_;
};
}
}


#endif //EVENTPUMP_INETADDRESS_H
