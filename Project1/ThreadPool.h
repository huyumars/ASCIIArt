#pragma once
#include <queue>
#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>

typedef std::function<void(void)> ThreadTask;

class ThreadPool
{
public:
	ThreadPool(int _threadNum = 4);
	template<class F, class ...Args>
	void runTask(F &&f, Args&&... args) {
		TaskReType res = enqueue([f,args...]() {
			f(args...);
			return true;
		});
		taskResults.push_back(std::move(res));
	}
	template<class F, class ...Args>
	auto enqueue(F &&f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
		using return_type = typename std::result_of<F(Args...)>::type;
		auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		{
			std::unique_lock<std::mutex> lock{ taskQueueMutex };
			if(!alive)
				throw std::runtime_error("enqueue on stopped ThreadPool");
			taskQueue.emplace([task]() { (*task)(); });
		}
		cv_task.notify_all();
		return task->get_future();
	}
	void join();
	~ThreadPool();
private:
	volatile bool alive;
	typedef std::future<bool> TaskReType;
	std::vector<TaskReType> taskResults;
	std::queue<ThreadTask> taskQueue;
	std::vector<std::thread> threads;
	int threadNum;
	void _schedule();
	ThreadTask getTask();
	std::condition_variable cv_task;
	std::mutex taskQueueMutex;
};

