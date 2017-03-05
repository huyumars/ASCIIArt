#include "ThreadPool.h"
#include <thread>
#include <iostream>

ThreadPool::ThreadPool(int _threadNum):threadNum(_threadNum),alive(true)
{
	for (int i = 0; i < _threadNum; ++i) {
		threads.emplace_back(&ThreadPool::_schedule,this);
	}
}

void ThreadPool::join()
{
	for (int i = 0; i < taskResults.size(); i++)
		taskResults[i].get();
	taskResults.clear();
}


ThreadPool::~ThreadPool()
{
	alive = false;
	cv_task.notify_all(); // wake up all thread to dead
	for (int i = 0; i < threadNum; ++i) {	
		threads[i].join();
	}
}

void ThreadPool::_schedule()
{
	while (alive) {
		ThreadTask task = getTask();		
		task();
	}
}

ThreadTask ThreadPool::getTask()
{
	std::unique_lock<std::mutex> lock{ taskQueueMutex };
	cv_task.wait(lock, [this]() { return !alive||!taskQueue.empty(); });
	if (alive == false|| taskQueue.empty()) return []() {};  //return empty function
	ThreadTask task = taskQueue.front();
	taskQueue.pop();
	return task;
}
