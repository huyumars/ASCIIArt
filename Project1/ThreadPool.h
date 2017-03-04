#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>

typedef std::function<void(void)> ThreadTask;

class ThreadPool
{
public:
	ThreadPool(int _threadNum = 4);
	void runTask(ThreadTask task );
	~ThreadPool();
private:
	std::queue<ThreadTask> taskQueue;
	std::vector<std::thread> threads;
	int threadNum;
	void _schedule();
	ThreadTask getTask();
	std::condition_variable cv_task;
	std::mutex taskQueueMutex;
};

