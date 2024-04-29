#ifndef UI_MAINTHREAD_H_
#define UI_MAINTHREAD_H_

#pragma once

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

//�߳�ID
enum ThreadId
{
	kThreadUI,		//���߳�ID
	kThreadWorker	//�����߳�ID
};

/** �����߳�
*/
class WorkerThread : public nbase::FrameworkThread
{
public:
	WorkerThread(ThreadId threadID, const char* name);
	virtual ~WorkerThread();

private:
	/** ��ʼ���߳�
	*/
	virtual void Init() override;

	/** �߳��˳�ʱ����һЩ������
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
	MainThread();
	virtual ~MainThread();

private:
	/** ��ʼ�����߳�
	*/
	virtual void Init() override;

	/** ���߳��˳�ʱ����һЩ������
	*/
	virtual void Cleanup() override;

private:
	/** �����߳�(�������Ҫ���̴߳���ҵ�񣬿����Ƴ������̵߳Ĵ���)
	*/
	std::unique_ptr<WorkerThread> m_workerThread;
};

#endif // UI_MAINTHREAD_H_
