//
// Created by finefenng on 2018/1/5.
//


#ifndef EVENTPUMP_CSOCKETWRAP_H
#define EVENTPUMP_CSOCKETWRAP_H

#include "platform.h"


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

namespace eventpump
{
namespace net
{
namespace socketops
{


int InitializeSocketEnvironment();

void FreeSocketEnvironment();

void GetAddressFrom(sockaddr_in* addr, const char* ip, int port);

void GetIpAddress(char* ip, sockaddr_in* addr);

bool IsValidSocketHandle(HSocket handle);

int GetLastSocketError();

HSocket SocketOpen(int type);

int SocketBind(HSocket hs, sockaddr_in* peeraddr);

int SocketListen(HSocket hs, int maxconn);

HSocket SocketAccept(HSocket hs, sockaddr_in* addr);

void SocketClose(HSocket& handle);

//int SocketBlock(HSocket hs, bool bblock);

//int SocketTimeOut(HSocket hs, int recvtimeout, int sendtimeout, int lingertimeout);

void SocketSend(HSocket hs, const char* ptr, int nbytes, transresult_t& rt);

void SocketRecv(HSocket hs, char* ptr, int nbytes, transresult_t& rt);


/*
void SocketTryRecv(HSocket hs, char* ptr, int nbytes, int milliseconds, transresult_t& rt);

void SocketTrySend(HSocket hs, const char* ptr, int nbytes, int milliseconds, transresult_t& rt);

void SocketClearRecvBuffer(HSocket hs);
 */
}
}
}


/*
class CSockWrap
{
public:

    CSockWrap(int tcpudp);

    ~CSockWrap();

    void SetAddress(const char* ip, int port);

    void SetAddress(sockaddr_in* addr);

    int SetTimeOut(int recvtimeout, int sendtimeout, int lingertimeout);

    int SetBufferSize(int recvbuffersize, int sendbuffersize);

    int SetBlock(bool bblock);

    HSocket GetHandle() { return m_hSocket; }

    void Reopen(bool bForceClose);

    void Close();

    transresult_t Send(void* ptr, int nbytes);

    transresult_t Recv(void* ptr, int nbytes);

    transresult_t TrySend(void* ptr, int nbytes, int milliseconds);

    transresult_t TryRecv(void* ptr, int nbytes, int milliseconds);

    void ClearRecvBuffer();

protected:
    HSocket m_hSocket;
    sockaddr_in m_stAddr;
    int m_tcpudp;
};
 */





#endif //EVENTPUMP_CSOCKETWRAP_H
