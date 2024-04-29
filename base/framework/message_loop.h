// This file trys to implement a cross flatform message loop,
// the mechanism of which is from the Google Chrome project.

#ifndef BASE_FRAMEWORK_MESSAGE_LOOP_H_
#define BASE_FRAMEWORK_MESSAGE_LOOP_H_

#include <queue>									// for std::queue, std::priority_queue
#include <memory>
#include "base/base_types.h"						// for OS_WIN and NULL, etc.
#include "base/framework/default_message_pump.h"
#include "base/framework/message_loop_proxy.h"		// for MessageLoopProxy
#include "base/framework/observer_list.h"			// for ObserverList
#if defined(OS_WIN)
#include "base/framework/win_io_message_pump.h"
#include "base/framework/win_ui_message_pump.h"
#elif defined(OS_POSIX)
#include "base/framework/libevent_message_pump.h"
#endif // OS_WIN
#include "base/synchronization/lock.h"				// for NLock
#include "base/time/time.h"
#include "base/callback/callback.h"

namespace nbase
{

// һ���߳����ֻ��ʹ��һ��MessageLoop��
// MessageLoop���ڴ���Task��ͬʱ���������͵Ĳ�ͬ��MessageLoop�����ܴ���Windows��Ϣ����ʱ����IO�¼���
// �����ر�˵����MessageLoop�����еĳ�Ա������ֻ������ִ��MessageLoop���߳��ϵ���
//
// MessageLoop��Task���뱣����Ҳ����˵��һ��Taskִ�й����������˵ڶ���Task��
// ��ô�ڶ���Task���ڵ�һ��Taskִ�����֮��Żᱻִ�У���Ϊ�ڶ���Task��Ҳ������һ��MessagePump��
// Ҫ���������Ϊ����Ҫʹ��SetNestableTasksAllowed������������������˵��

class UIMessageLoop;
class IOMessageLoop;
class UvMessageLoop;
class MessageLoopProxy;

#if defined(OS_WIN)
	typedef WinIOMessagePump IOMessagePump;
	typedef WinUIMessagePump UIMessagePump;
	typedef WinMessagePump::Dispatcher Dispatcher;
#elif defined(OS_POSIX)
	typedef LibeventMessagePump IOMessagePump;
#else
#error Not support currently!
#endif
	
class BASE_EXPORT MessageLoop : public MessagePump::Delegate
{
public:	

	enum Type
	{
		kDefaultMessageLoop,
		kUIMessageLoop,
		kIOMessageLoop,
		kCustomMessageLoop,
	};

	explicit MessageLoop();
	virtual ~MessageLoop();
	static MessageLoop* current();

#if defined(OS_WIN)
	// ת���ɶ�Ӧ�������͵�MessageLoopָ��
	// ���ԭָ��Ƕ�Ӧ���͵�ָ�룬������NULL
	UIMessageLoop* ToUIMessageLoop();
	IOMessageLoop* ToIOMessageLoop();
#elif defined(OS_POSIX)
	IOMessageLoop* ToIOMessageLoop();	
#endif

	MessagePump * pump() { return pump_.get(); }

	Type type() const { return type_; }

	// ����MessageLoop
	void Run();
#if defined(OS_WIN)
	void RunWithDispatcher(Dispatcher *dispatcher);
#endif

	// �������д������Task��Windows��Ϣ��IO�¼��ȵȣ����ǽ���Wait/Sleep��
	// �����д������Task��������ɺ������Ӷ���������ĵ��÷���
	void RunAllPending();

	// ֪ͨMessageLoop�ڴ������д���������֮���Run�����з��ء�
	// �������ֻ���ڵ���Run�������Ǹ��߳��б�����
	// Ҫ�˳������̵߳�MessageLoop����Ҫʹ��PostTask�庯��Ͷ��һ��QuitTask�������棩
	void Quit();

	// Quit�����ı��壬����������Run���ض��������κδ������Task
	void QuitNow();

	// PostTask�庯�������ڸ�MessageLoop����첽ִ�е�����
	//
	// - PostTask���������ͨ��Ƕ������
	// - PostDelayedTask������Ӷ�ʱ�����ʺ�һЩ��Ҫ���Ӻ�ָ��ʱ��ִ�е�Ƕ������
	// - PostNonNestableTask������ӷ�Ƕ��ִ�е�������������ֻ������MessageLoop��Run�����б�ִ�е�����
	//   ��Ƕ�׵�MessageLoop��PostNonNestableTask����ô��Щ��Post��Task�����ݴ档
	// - PostNonNestableDelayedTask������ӷ�Ƕ�׵Ķ�ʱ������������ֻ���ض�ʱ��������MessageLoop��Run����
	//   �б�ִ�е�������������Ƕ�׵�MessageLoop�У��ʺ���Ҫ���Ӻ�ָ��ʱ��ִ�еķ�Ƕ������
	//
	// PostTask�庯�����̰߳�ȫ��һ���߳̿���ʹ����Щ�����������̷߳�������
	//
	// ע�⣺һ������Post��MessageLoop֮�����������ڽ������MessageLoop���ڵ��߳̿���
	void PostTask(const StdClosure &task);
	void PostDelayedTask(const StdClosure &task, TimeDelta delay);
	void PostNonNestableTask(const StdClosure &task);
	void PostNonNestableDelayedTask(const StdClosure &task, TimeDelta delay);

	// SetNestableTasksAllowed�������û��߽���Ƕ��������
	// �������Ƕ��������ôTask��������ִ�У������ȱ��ݴ���һ��������ֱ���ϲ�����ִ�������ִ��
	// ���͵ĳ�����
	// - �߳�������һ��MessageLoop
	// - �߳��յ���һ��Task��Task #1
	// - Task #1ִ�й����е�����һ��MessageBox�Ӷ���ʽ�ؽ�����һ��MessageLoop����MessageBox��Ϣѭ����
	// - ��MessageBox��MessageLoop��δ����ǰ���߳����յ�����һ��Task��Task #2
	// - �����ʱǶ�����������ã���ôTask #2��������ִ�У�����Task #1�Ƿ��Ѿ���������
	//   ����Task #2����Task #1��ִ����ɺ������̵߳�MessageLoop��ִ�С�
	void SetNestableTasksAllowed(bool allowed);
	bool IsNestableTasksAllowed() const { return nestable_tasks_allowed_; }
	bool IsNested() const { if (state_) return state_->run_depth > 1; return false; }

	// MessageLoopProxy�ṩ���̰߳�ȫ����MessageLoop�Ļ��ƣ�
	// ���з��߳��ڵ�PostTask�庯������ͨ��MessageLoopProxy����
	std::shared_ptr<MessageLoopProxy> message_loop_proxy() {
		return message_loop_proxy_;
	}

	// MessageLoop���ٹ۲��ߣ�MessageLoop����ǰ����֪ͨ��Щ�۲���
	class BASE_EXPORT DestructionObserver
	{
	public:
		virtual void PreDestroyCurrentMessageLoop() = 0;
		virtual ~DestructionObserver() {}
	};

	void AddDestructionObserver(DestructionObserver *observer);
	void RemoveDestructionObserver(DestructionObserver *observer);

	// ����۲��ߣ�ÿ�����񱻴���ǰ�ʹ�������֪ͨ��Щ�۲���
	class BASE_EXPORT TaskObserver
	{
	public:
		virtual void PreProcessTask() = 0;
		virtual void PostProcessTask() = 0;

	protected:
		virtual ~TaskObserver();
	};

	void AddTaskObserver(TaskObserver* observer);
	void RemoveTaskObserver(TaskObserver* observer);

#if defined(OS_WIN)
	bool os_modal_loop() const  { return os_modal_loop_; }
	void set_os_modal_loop(bool os_modal_loop) { os_modal_loop_ = os_modal_loop; }
#endif // OS_WIN

protected:
	struct RunState
	{
		int run_depth;
		bool quit_received;
#if defined(OS_WIN)
		Dispatcher* dispatcher;
#endif
	};

	class BASE_EXPORT AutoRunState : RunState
	{
	public:
		explicit AutoRunState(MessageLoop* loop);
		~AutoRunState();
	private:
		MessageLoop* loop_;
		RunState* previous_state_;
	};

	class ScopedNestableTaskAllower {
	public:
		explicit ScopedNestableTaskAllower(MessageLoop* loop)
			: loop_(loop),
			old_state_(loop_->IsNestableTasksAllowed()) {
				loop_->SetNestableTasksAllowed(true);
		}
		~ScopedNestableTaskAllower() {
			loop_->SetNestableTasksAllowed(old_state_);
		}

	private:
		MessageLoop* loop_;
		bool old_state_;
	};
	
	struct PendingTask
	{
		PendingTask(const StdClosure &task);
		PendingTask(const StdClosure &task,
			nbase::TimeTicks delayed_run_time,
			bool nestable);

		~PendingTask();

		// �������ȶ��е�����std::heapĬ��Ϊ�󶥶ѣ�
		// ������Ҫ����С���ѣ������������������ʵ�ʵ÷��ش��ڵıȽϽ��
		bool operator<(const PendingTask& other) const;
		// �������е�ʱ�̣����Ҳ���ڼ���ʱ������Ƕ�ʱ����
		nbase::TimeTicks delayed_run_time;
		// ��ʱ������ţ�����Ϊ��ʱ����ĵڶ���������Ƕ�ʱ���������Ч
		int sequence_num;
		// �Ƿ�������Ƕ�׵�MessageLoop�б�ִ��
		bool nestable;

		void Run()
		{
			if (std_task) {
				std_task();
			}
			else {
				assert(false);
			}
		}

	private:
		StdClosure std_task;
	};

	class TaskQueue : public std::queue<PendingTask>
	{
	public:
		void Swap(TaskQueue* queue)
		{
			c.swap(queue->c);  // ����ʱ�临�Ӷȵ��ڴ潻��
		}
	};

	typedef std::priority_queue<PendingTask> DelayedTaskQueue;

	virtual bool DoWork();
	virtual bool DoDelayedWork(nbase::TimeTicks* next_delayed_work_time);
	virtual bool DoIdleWork();

	void RunInternal();

	// AddToIncomingQueue�����̰߳�ȫ�������Ϊ���̰߳�ȫ
	virtual void AddToIncomingQueue(const PendingTask &task);
	void AddToDelayedWorkQueue(const PendingTask &task);
	void ReloadWorkQueue();
	bool DeferOrRunPendingTask(const PendingTask &task);
	void RunTask(const PendingTask &task);
	bool ProcessNextDelayedNonNestableTask();
	bool DeletePendingTasks();

	void PreDestruct();
	void PreProcessTask();
	void PostPrecessTask();

	static TimeTicks EvalDelayedRuntime(int64_t delay_ms);

	// MessageLoop����
	Type type_;
	// ����״̬
	RunState *state_;
	// ��Ϣ��
	std::shared_ptr<MessagePump> pump_;

#if defined(OS_WIN)
	// OS�Ƿ���ģ̬ѭ���У����������MessageBox֮����Ϣѭ����OS�ӹܣ������ʹ���OSģ̬ѭ����
	bool os_modal_loop_;
#endif // OS_WIN

	// �Ƿ�����Ƕ������
	bool nestable_tasks_allowed_;
	// ����������У��κξ���Post�庯��������������Ƚ���ö��У�֮��������Run���̷߳��䵽����רְ����
	TaskQueue incoming_queue_;
	// ���������
	NLock incoming_queue_lock_;

	// ����������е������Ϊ������޶ȼ��ٶ�������еļ���������
	// ���ֹ�ϵ������˫������ƣ���������ݴ汾�̺߳������߳�Ͷ�ݹ���������
	// �������������������Run�������̲߳�����ֻ���̼߳�鵽��������Ϊ�ղŻ�ȥ�������������ŵ���������Ȼ��������С�
	// ��������˽����ڴ�ķ���������������Ч�ʣ�Ҳ����˵������Ĳ�����ʵ����һ��һ��������������ƶ���������ɵģ�
	// ����ֱ�ӽ���˫�����ڴ棬�����������������˲ʱ��գ������������ӵ����֮ǰ����������е����ݡ�
	TaskQueue work_queue_;
	// MessageLoop����Ƕ����ʱ����Ƕ�����񽫱���ʱ������������У���MessageLoop�ص������ʱ����ͨ��DoIdleWork���ִ��֮
	TaskQueue deferred_non_nestable_work_queue_;
	// ��ʱ������У�Ƕ�׺ͷ�Ƕ�ף�
	DelayedTaskQueue delayed_work_queue_;
	// ��һ����ʱ��������к�
	int next_delayed_task_sequence_num_;
	// ���һ�ε���TimeTicks::Now������ʱ��
	TimeTicks recent_tick_;
	// ����۲����б�
	ObserverList<TaskObserver> task_observers_;
	// MessageLoop���ٹ۲����б�
	ObserverList<DestructionObserver> destruction_observers_;
	// The message loop proxy associated with this message loop, if one exists.
	std::shared_ptr<MessageLoopProxy> message_loop_proxy_;

	DISALLOW_COPY_AND_ASSIGN(MessageLoop);
};

#if defined(OS_WIN)

class BASE_EXPORT UIMessageLoop : public MessageLoop
{
public:

#if defined(OS_WIN)
	typedef WinUIMessagePump::UIObserver UIObserver;
#else
#error Not support currently!
#endif

	UIMessageLoop();

	static UIMessageLoop* current()
	{
		return reinterpret_cast<UIMessageLoop *>(MessageLoop::current());
	}

	void AddUIObserver(UIObserver *observer);
	void RemoveUIObserver(UIObserver *observer);
};

#endif // OS_WIN

class BASE_EXPORT IOMessageLoop : public MessageLoop
{
public:

#if defined(OS_WIN)
	typedef WinIOMessagePump::IOHandler  IOHandler;
	typedef WinIOMessagePump::IOContext  IOContext;
	typedef WinIOMessagePump::IOObserver IOObserver;
#elif defined(OS_POSIX)
	typedef LibeventMessagePump::Watcher Watcher;
	typedef LibeventMessagePump::FileDescriptorWatcher FileDescriptorWatcher;
	typedef LibeventMessagePump::IOObserver IOObserver;

	enum Mode
	{
		WATCH_READ = LibeventMessagePump::WATCH_READ,
		WATCH_WRITE = LibeventMessagePump::WATCH_WRITE,
		WATCH_READ_WRITE = LibeventMessagePump::WATCH_READ_WRITE
	};
#else
#error Not support currently!
#endif

	IOMessageLoop();

	static IOMessageLoop* current()
	{
		return reinterpret_cast<IOMessageLoop *>(MessageLoop::current());
	}

	void AddIOObserver(IOObserver *observer);
	void RemoveIOObserver(IOObserver *observer);

#if defined(OS_WIN)
	void RegisterIOHandler(HANDLE file_handle, IOHandler *handler);
	bool WaitForIOCompletion(DWORD timeout, IOHandler *handler);

#elif defined(OS_POSIX)
	bool WatchFileDescriptor(int fd,
		                     bool persistent,
		                     Mode mode,
		                     FileDescriptorWatcher *controller,
		                     Watcher *delegate);
#endif
};



} // namespace nbase

#endif // BASE_FRAMEWORK_MESSAGE_LOOP_H_
