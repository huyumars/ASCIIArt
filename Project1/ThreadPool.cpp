#include "ThreadPool.h"
#include <thread>


ThreadPool::ThreadPool(int _threadNum):threadNum(_threadNum)
{
	for (int i = 0; i < _threadNum; ++i) {
		//threads.emplace_back()
	}
}

void ThreadPool::runTask(ThreadTask task)
{

}


ThreadPool::~ThreadPool()
{
}

void ThreadPool::_schedule()
{
	while (true) {

	}
}

ThreadTask ThreadPool::getTask()
{
	std::unique_lock<std::mutex> lock{ taskQueueMutex };
	cv_task.wait(lock, [this]() { return !taskQueue.empty(); });
}
