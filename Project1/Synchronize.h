#pragma once
#include <mutex>
#include <deque>
#include <queue>
namespace Synchronize {

	template < class T, class Container = std::deque<T>>
	class queue {
	public:
		explicit queue(const Container & ctnr = Container()) : storage(ctnr) { }
		bool empty(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.empty(); }

		size_t size(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.size(); }

		T & back(void) { std::lock_guard<std::mutex> lock(mutex); return storage.back(); }
		const T & back(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.back(); }

		T & front(void) { std::lock_guard<std::mutex> lock(mutex); return storage.front(); }
		const T & front(void) const { std::lock_guard<std::mutex> lock(mutex); return storage.front(); }

		void push(const T & u) { std::lock_guard<std::mutex> lock(mutex); storage.push(u); }

		void pop(void) { std::lock_guard<std::mutex> lock(mutex); storage.pop(); }
	private:
		std::queue<T, Container> storage;
		mutable std::mutex mutex;
	};

}

