#pragma once
#include <functional>
#include <future>
#include <condition_variable>
#include <atomic>
#include <mutex>
class RunningWorkingException : std::exception {
	virtual char const* what() const {
		return "this worker is running, cannot assigned work";
	}
};

class BackgroundWorker
{
public:
	template<class F, class... Args>
	auto  commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))> {
		if (isBusy()) {   //is running
			throw RunningWorkingException();
		}
		using ResType = decltype(f(args...));    // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
		auto task = std::make_shared<std::packaged_task<ResType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);    
		workTask = std::function<void(void)>([task]() { (*task)(); });
		std::future<ResType> future = task->get_future();
		return future;
	}
	void startWork();
	BackgroundWorker();
	~BackgroundWorker();

	bool isBusy() const;
private:
	bool alive;
	bool startToWork;
	std::atomic<bool> _isBusy;
	std::function<void(void)> workTask;
	std::condition_variable task_cv;
	std::mutex task_m;
	void threadRunning();
	std::thread backgroundThread;
};

