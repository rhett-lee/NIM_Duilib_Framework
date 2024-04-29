#include "MainThread.h"
#include "MyDuilibForm.h"

WorkerThread::WorkerThread(ThreadId threadID, const char* name)
	: FrameworkThread(name)
	, m_threadID(threadID)
{
}

WorkerThread::~WorkerThread()
{
}

void WorkerThread::Init()
{
	::OleInitialize(nullptr);
	nbase::ThreadManager::RegisterThread(m_threadID);
}

void WorkerThread::Cleanup()
{
	nbase::ThreadManager::UnregisterThread();
	::OleUninitialize();
}

MainThread::MainThread(): 
	nbase::FrameworkThread("MainThread") 
{
}

MainThread::~MainThread()
{
}

void MainThread::Init()
{
	::OleInitialize(nullptr);
	nbase::ThreadManager::RegisterThread(kThreadUI);

	//���������߳�
	m_workerThread.reset(new WorkerThread(kThreadWorker, "WorkerThread"));
	m_workerThread->Start();

	//����DPI����Ӧ����
	bool bAdaptDpi = true;

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

	// Debug ģʽ��ʹ�ñ����ļ�����Ϊ��Դ
	// Ĭ��Ƥ��ʹ�� resources\\themes\\default
	// Ĭ������ʹ�� resources\\lang\\zh_CN
	// �����޸���ָ�� Startup �����������
	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);

	//����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	MyDuilibForm* window = new MyDuilibForm();
	window->CreateWnd(nullptr, MyDuilibForm::kClassName.c_str(), UI_WNDSTYLE_FRAME, WS_EX_LAYERED);
	window->CenterWindow();
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Instance().Shutdown();
	if (m_workerThread != nullptr) {
		m_workerThread->Stop();
		m_workerThread.reset(nullptr);
	}
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
	::OleUninitialize();
}
