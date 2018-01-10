//
// Created by finefenng on 2018/1/6.
//

#include "TcpServer.h"
#include "EventLoop.h"

using namespace pump::net;



static int count = 0;

void ewConnectionCallback(HSocket fd, InetAddress& cliAddr)
{
}

void messageTest(const TcpConnectionPtr& conn, Buffer* buffer)
{
	std::cout << buffer->retrieveAsString() << std::endl;
}






int main(int argc, char* argv[])
{

	EventLoop loop;
	InetAddress serverAddr("192.168.2.172", 9997);
	TcpServer server(&loop, serverAddr);
	server.setNewConnectionCallback(ewConnectionCallback);
	server.setMessageCallback(messageTest);
	server.start();
	loop.run();
}

