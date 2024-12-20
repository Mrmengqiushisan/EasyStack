
#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>

#include "../base/timestamp.h"
namespace net
{

	class Channel;
	class EPollPoller;

	///
	/// Reactor, at most one per thread.
	///
	/// This is an interface class, so don't expose too much details.
	class EventLoop
	{
	public:
		typedef std::function<void()> Functor;

		EventLoop();
		~EventLoop();  // force out-line dtor, for scoped_ptr members.

		///
		/// Loops forever.
		///
		/// Must be called in the same thread as creation of the object.
		///
		void loop();

		/// Quits loop.
		///
		/// This is not 100% thread safe, if you call through a raw pointer,
		/// better to call through shared_ptr<EventLoop> for 100% safety.
		void quit();

		///
		/// Time when poll returns, usually means data arrival.
		///
		Timestamp pollReturnTime() const { return pollReturnTime_; }

		int64_t iteration() const { return iteration_; }

		/// Runs callback immediately in the loop thread.
		/// It wakes up the loop, and run the cb.
		/// If in the same loop thread, cb is run within the function.
		/// Safe to call from other threads.
		void runInLoop(const Functor& cb);
		/// Queues callback in the loop thread.
		/// Runs after finish pooling.
		/// Safe to call from other threads.
		void queueInLoop(const Functor& cb);

		void setFrameFunctor(const Functor& cb);

		// internal usage
		void wakeup();
		void updateChannel(Channel* channel);
		void removeChannel(Channel* channel);
		bool hasChannel(Channel* channel);

		// pid_t threadId() const { return threadId_; }
		void assertInLoopThread()
		{
			if (!isInLoopThread())
			{
				abortNotInLoopThread();
			}
		}
		bool isInLoopThread() const { return threadId_ == std::this_thread::get_id(); }
		// bool callingPendingFunctors() const { return callingPendingFunctors_; }
		bool eventHandling() const { return eventHandling_; }

		static EventLoop* getEventLoopOfCurrentThread();

		const std::thread::id getThreadID() const
		{
			return threadId_;
		}

	private:
		void abortNotInLoopThread();
		void handleRead();  // waked up
		void doPendingFunctors();

		void printActiveChannels() const; // DEBUG

		typedef std::vector<Channel*> ChannelList;

		bool looping_; /* atomic */
		bool quit_; /* atomic and shared between threads, okay on x86, I guess. */
		bool eventHandling_; /* atomic */
		bool callingPendingFunctors_; /* atomic */
		int64_t iteration_;
		const std::thread::id threadId_;
		Timestamp pollReturnTime_;
		std::shared_ptr<EPollPoller> poller_;

		int wakeupFd_;
		// unlike in TimerQueue, which is an internal class,
		// we don't expose Channel to client.
		std::shared_ptr<Channel> wakeupChannel_;
	
		// scratch variables
		ChannelList activeChannels_;
		Channel* currentActiveChannel_;

		std::mutex mutex_;
		std::vector<Functor> pendingFunctors_; // @GuardedBy mutex_

		Functor frameFunctor_;
	};

}
