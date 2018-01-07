//
// Created by finefenng on 2018/1/5.
//

#include "InetAddress.h"

using namespace pump::net;

static const char* kInaddrLoopback = "127.0.0.1";
static const uint32_t kInaddrAny = INADDR_ANY;
static const int kInetAddrStrlen = 16;


InetAddress::InetAddress(uint16_t port, bool loopbackOnly)
{
	bzero(&addr_, sizeof(addr_));
	addr_.sin_family = AF_INET;
	if (loopbackOnly) {
		inet_pton(AF_INET, kInaddrLoopback, &addr_.sin_addr);
	} else {
		addr_.sin_addr.s_addr = htonl(kInaddrAny);
	}
	addr_.sin_port = htons(port);
}

InetAddress::InetAddress(const char* ip, uint16_t port)
{
	bzero(&addr_, sizeof(addr_));
	addr_.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &addr_.sin_addr);
	addr_.sin_port = htons(port);
}

std::string InetAddress::toIp() const
{
	char ipArray[kInetAddrStrlen] = {0};
	socketops::GetIpAddress(ipArray, &addr_);
	return std::string(ipArray);
}
uint16_t InetAddress::toPort() const
{
	return ntohs(addr_.sin_port);
}

std::string InetAddress::toIpPort() const
{
	char portArray[16] = {0};
	snprintf(portArray, 16, ":%d", toPort());
	return toIp()+std::string(portArray);
}







