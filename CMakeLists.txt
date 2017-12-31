cmake_minimum_required(VERSION 3.9)
project(EventPump)

set(CMAKE_CXX_STANDARD 11)

include_directories(~/MyInclude)

add_library(EventPump library.cpp library.h net/EventLoop.cpp net/EventLoop.h net/Poller.cpp net/Poller.h net/Channel.cpp net/Channel.h net/Callbacks.h tests/event_base_configs.cpp)

target_link_libraries(EventPump libevent_core.dylib libevent_extra.dylib libextra_pthread.dylib)

