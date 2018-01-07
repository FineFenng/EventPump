//
// Created by finefenng on 2018/1/6.
//

#include "TcpServer.h"
#include "EventLoop.h"
#include <iostream>

using namespace pump::net;



static int count = 0;

void ewConnectionCallback(HSocket fd, InetAddress& cliAddr)
{
	std::cout << "Socket is" << fd;
}



int main(int argc, char* argv[])
{
	EventLoop loop;
	InetAddress serverAddr("192.168.2.172", 9999);
	TcpServer server(&loop, serverAddr);
	server.setNewConnectionCallback(ewConnectionCallback);
	server.start();
	loop.run();
}

