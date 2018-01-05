//
// Created by finefenng on 2018/1/5.
//

#ifndef EVENTPUMP_INETADDRESS_H
#define EVENTPUMP_INETADDRESS_H

#include <cstdint>
#include <string>
#include "SocketsOps.h"

namespace eventpump
{
namespace net
{

class InetAddress
{
public:
	/// Constructs an endpoint with given port number.
	/// Mostly used in TcpServer listening.
	explicit InetAddress(uint16_t port = 0, bool loopbackOnly = false);

	/// Constructs an endpoint with given ip and port.
	/// @c ip should be "1.2.3.4"
	InetAddress(char* ip, uint16_t port);

	/// Constructs an endpoint with given struct @c sockaddr_in
	/// Mostly used when accepting new connections
	explicit InetAddress(const struct sockaddr_in addr)
			: addr_(addr)
	{ }

	sa_family_t family() const { return addr_.sin_family; }

	std::string toIp() const;

	uint16_t toPort() const;
	std::string toIpPort() const;

	struct sockaddr_in* getSockAddr() const { return &addr_; }

private:
	struct sockaddr_in addr_;
};
}
}


#endif //EVENTPUMP_INETADDRESS_H
