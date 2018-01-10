cmake_minimum_required(VERSION 3.9)
project(EventPump)

set(CMAKE_CXX_STANDARD 11)

add_executable(EventPump
               net/Callbacks.h
               net/Platform.h
               net/conn_test.cpp
               net/Acceptor.cpp
               net/Socket.cpp
               net/Watcher.cpp
               net/EventLoop.cpp
               net/SocketsOps.cpp
               net/InetAddress.cpp
               net/TcpConnection.cpp
               net/TcpServer.cpp
               )

target_link_libraries(EventPump libev.dylib libglog.dylib pthread)


