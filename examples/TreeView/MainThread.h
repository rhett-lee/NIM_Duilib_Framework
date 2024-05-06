#pragma once

#include "resource.h"

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

#include <memory>

//�߳�ID
enum ThreadId
{
	kThreadUI,
	kThreadWorker
};

/** �����߳�
*/
class WorkerThread : public nbase::FrameworkThread
{
public:
	WorkerThread(ThreadId threadID, const char* name)
		: FrameworkThread(name)
		, m_threadID(threadID) {}

	~WorkerThread(void) {}

private:
	/**
	* �麯������ʼ���߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�����߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

private:

	/** �߳�ID
	*/
	ThreadId m_threadID;
};

/** ���߳�
*/
class MainThread : public nbase::FrameworkThread
{
public:
	MainThread() : nbase::FrameworkThread("MainThread") {}
	virtual ~MainThread() {}

private:
	/**
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

private:
	/** �����߳�
	*/
	std::unique_ptr<WorkerThread> m_workerThread;
};


