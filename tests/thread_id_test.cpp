//
// Created by finefenng on 2018/1/6.
//
#include <glog/logging.h>
#include <thread>

int main(int argc, char* argv[])
{
	google::InitGoogleLogging(argv[0]);
	FLAGS_log_dir = "./Log";

	auto threadId = std::this_thread::get_id();
	LOG(INFO) << "thread id is" << threadId;
	return 0;
}
