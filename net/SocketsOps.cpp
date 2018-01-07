//
// Created by finefenng on 2018/1/5.
//

#include "SocketsOps.h"


#include <errno.h>

#define INVALIDSOCKHANDLE INVALID_SOCKET

#if defined(Q_OS_WIN32)

#include <windows.h>

#define ISSOCKHANDLE(x) ((x) != INVALID_SOCKET)
#define BLOCKREADWRITE 0
#define NONBLOCKREADWRITE 0
#define SENDNOSIGNAL 0
#define ETRYAGAIN(x) ((x) == WSAEWOULDBLOCK || (x) == WSAETIMEDOUT)
#define gxsprintf sprintf_s

#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)

#include <unistd.h>
#include <strings.h>
#include <fcntl.h>

#define ISSOCKHANDLE(x) ((x) > 0)
#define BLOCKREADWRITE MSG_WAITALL
#define NONBLOCKREADWRITE MSG_DONTWAIT
#define SENDNOSIGNAL MSG_NOSIGNAL
#define ETRYAGAIN(x) ((x) == EAGAIN || (x) == EWOULDBLOCK)
#define gxsprintf sprintf_s
#endif

namespace pump
{
namespace net
{
namespace socketops
{

int InitializeSocketEnvironment()
{
#if defined(Q_OS_WIN32)
	WSADATA Ws;
//Init Windows Socket
if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 ) {
	return -1;
 }
#endif
	return 0;
}

void GetAddressFrom(sockaddr_in* addr, const char* ip, int port)
{
	bzero(addr, sizeof(sockaddr_in));
	addr->sin_family = AF_INET; /*地址类型为AF_INET*/
	if (ip) {
		addr->sin_addr.s_addr = inet_addr(ip);
	} else {
		/*网络地址为INADDR_ANY，这个宏表示本地的任意IP地址，因为服务器可能有多个网卡，每个网卡也可能绑定多个IP地址，
        这样设置可以在所有的IP地址上监听，直到与某个客户端建立了连接时才确定下来到底用哪个IP地址*/
		addr->sin_addr.s_addr = htonl(INADDR_ANY);
	}
	addr->sin_port = htons(port); /*端口号*/
}

void GetIpAddress(char* ip, const sockaddr_in* addr)
{
	inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
}


int GetLastSocketError()
{
#if defined(Q_OS_WIN32)
	return WSAGetLastError();
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
	return errno;
#endif
}

bool IsValidSocketHandle(HSocket handle)
{
	return ISSOCKHANDLE(handle);
}

void SocketClose(HSocket& handle)
{
	if (ISSOCKHANDLE(handle)) {
#if defined(Q_OS_WIN32)
		closesocket(handle);
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
		close(handle);
#endif
		handle = INVALIDSOCKHANDLE;
	}
}

HSocket SocketOpen(int type)
{
	int protocol = 0;
	HSocket hs;
#if defined(Q_OS_WIN32)
	if(type== SOCK_STREAM) protocol=IPPROTO_TCP;
	else if (type== SOCK_DGRAM) protocol = IPPROTO_UDP;
#endif
	hs = socket(AF_INET, type, protocol);
	return hs;
}

int SocketBind(HSocket hs, const sockaddr_in* peeraddr)
{
	return bind(hs, (struct sockaddr*) peeraddr, sizeof(sockaddr_in));
}

int SocketListen(HSocket hs, int maxconn)
{
#if defined(Q_OS_WIN32)
	return listen(hs, maxconn);
#endif

	return listen(hs, SOMAXCONN);
}

HSocket SocketAccept(HSocket hs, sockaddr_in* peeraddr)
{
#if defined(Q_OS_WIN32)
	int cliAddr_len = sizeof(sockaddr_in);
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
	socklen_t cliAddr_len = sizeof(sockaddr_in);
#endif
	return accept(hs, (struct sockaddr*) peeraddr, &cliAddr_len);
}

struct sockaddr_in SocketGetLocalAddr(HSocket hs)
{
	struct sockaddr_in localAddr;
	bzero(&localAddr, sizeof(localAddr));
	socklen_t localAddrLen;
	getsockname(hs, (struct sockaddr*) &localAddr, &localAddrLen);
	return localAddr;
}

struct sockaddr_in SocketGetPeerAddr(HSocket hs)
{
	struct sockaddr_in peerAddr;
	bzero(&peerAddr, sizeof(peerAddr));
	socklen_t localAddrLen;
	getpeername(hs, (struct sockaddr*) &peerAddr, &localAddrLen);
	return peerAddr;
}

int SocketBlock(HSocket hs, bool on)
{
	unsigned long mode;
	if (ISSOCKHANDLE(hs)) {
#if defined(Q_OS_WIN32)
		mode = on ? 0 : 1;
		return ioctlsocket(hs, FIONBIO, &mode);
#endif

#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
		mode = fcntl(hs, F_GETFL, 0);                  //获取文件的flags值。
		//设置成阻塞模式                                      //非阻塞模式
		return on ? fcntl(hs, F_SETFL, mode & ~O_NONBLOCK) : fcntl(hs, F_SETFL, mode | O_NONBLOCK);
#endif
	}
	return -1;
}

void SockReuseAddress(HSocket hs, bool on)
{
	int mode = on ? 1 : 0;
#if defined(Q_OS_WIN32)
	/*todo*/
#endif
#if defined(Q_OS_LINUX) || defined(Q_OS_MAC)
	setsockopt(hs, SOL_SOCKET, SO_REUSEADDR, &mode, sizeof(mode));
#endif
}

/*
 * if timeout occurs, nbytes=-1, nresult=1,
 * if socket error, nbyte=-1, nresult=-1,
 * if the other side has disconnected in either block mode or nonblock mode, nbytes=0, nresult=-1,
 * otherwise nbytes= the count of bytes sent , nresult=0.
 */

void SocketSend(HSocket hs, const char* ptr, int nbytes, transresult_t& rt)
{
	rt.nbytes = 0;
	rt.nresult = 0;
	if (!ptr || nbytes < 1) return;

	//Linux: flag can be MSG_DONTWAIT, MSG_WAITALL, 使用MSG_WAITALL的时候, socket 必须是处于阻塞模式下，否则WAITALL不能起作用
	rt.nbytes = send(hs, ptr, nbytes, NONBLOCKREADWRITE);
	if (rt.nbytes > 0) {
		rt.nresult = (rt.nbytes == nbytes) ? 0 : 1;
	} else if (rt.nbytes == 0) {
		rt.nresult = -1;
	} else {
		rt.nresult = GetLastSocketError();
		rt.nresult = ETRYAGAIN(rt.nresult) ? 1 : -1;
	}
}


// if timeout occurs, nbytes=-1, nresult=1
// if socket error, nbyte=-1, nresult=-1
// if the other side has disconnected in either block mode or nonblock mode, nbytes=0, nresult=-1
void SocketRecv(HSocket hs, char* ptr, int nbytes, transresult_t& rt)
{
	rt.nbytes = 0;
	rt.nresult = 0;
	if (!ptr || nbytes < 1) return;

	rt.nbytes = recv(hs, ptr, nbytes, BLOCKREADWRITE);
	if (rt.nbytes > 0) {
		return;
	} else if (rt.nbytes == 0) {
		rt.nresult = -1;
	} else {
		rt.nresult = GetLastSocketError();
		rt.nresult = ETRYAGAIN(rt.nresult) ? 1 : -1;
	}
}

}
}
}
