#include "BackgroundWorker.h"


void BackgroundWorker::startWork()
{
	startToWork = true;
	task_cv.notify_one();
}

BackgroundWorker::BackgroundWorker():
	alive(true),
	startToWork(false),
	_isBusy(false),
	backgroundThread(&BackgroundWorker::threadRunning, this)
{

}


BackgroundWorker::~BackgroundWorker()
{
	alive = false;
	startWork(); //wake up thread
	backgroundThread.join();
}

bool BackgroundWorker::isBusy() const
{
	return _isBusy.load();
}

void BackgroundWorker::threadRunning()
{
	while (alive) {
			std::unique_lock<std::mutex> lock{ task_m };
			task_cv.wait(lock, [this]() { return startToWork; });
			if (alive == false) break;
			_isBusy.store(true);
			workTask();
			_isBusy.store(false);
			startToWork = false;
	}	
}
