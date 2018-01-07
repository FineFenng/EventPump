//
// Created by finefenng on 2018/1/5.
//


#ifndef EVENTPUMP_CSOCKETWRAP_H
#define EVENTPUMP_CSOCKETWRAP_H

#include "Platform.h"


// Win32
#if defined(Q_OS_WIN32)
#include <winsock2.h>
typedef SOCKET HSocket;
#endif

// Linux
#if defined(Q_OS_LINUX)
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

typedef int HSocket;
#define SOCKET_ERROR (-1)
#define INVALID_SOCKET 0
#endif

// MacOS
#if defined(Q_OS_MAC)

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

typedef int HSocket;
#define SOCKET_ERROR (-1)
#define INVALID_SOCKET 0
#endif


typedef struct
{
	int block;
	int sendbuffersize;
	int recvbuffersize;
	int lingertimeout;
	int recvtimeout;
	int sendtimeout;
} socketoption_t;


typedef struct
{
	int nbytes;
	int nresult;
} transresult_t;

namespace pump
{
namespace net
{
namespace socketops
{


int InitializeSocketEnvironment();

void FreeSocketEnvironment();

void GetAddressFrom(sockaddr_in* addr, const char* ip, int port);

void GetIpAddress(char* ip, const sockaddr_in* addr);

bool IsValidSocketHandle(HSocket handle);

int GetLastSocketError();

HSocket SocketOpen(int type);

int SocketBind(HSocket hs, const sockaddr_in* peeraddr);

int SocketListen(HSocket hs, int maxconn);

HSocket SocketAccept(HSocket hs, sockaddr_in* addr);

void SocketClose(HSocket& handle);

struct sockaddr_in SocketGetLocalAddr(HSocket hs);

struct sockaddr_in SocketGetPeerAddr(HSocket hs);

int SocketBlock(HSocket hs, bool on);

void SockReuseAddress(HSocket hs, bool on);


void SocketSend(HSocket hs, const char* ptr, int nbytes, transresult_t& rt);

void SocketRecv(HSocket hs, char* ptr, int nbytes, transresult_t& rt);


}
}
}

#endif //EVENTPUMP_CSOCKETWRAP_H
