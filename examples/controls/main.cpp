// controls.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "main.h"
#include "controls_form.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//���������ģ��WM_POINTER��Ϣ
	//BOOL isOk = EnableMouseInPointer(TRUE);
	//BOOL isOk2 = IsMouseInPointerEnabled();

	MainThread().RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

	return 0;
}

void MiscThread::Init()
{
	nbase::ThreadManager::RegisterThread(thread_id_);
}

void MiscThread::Cleanup()
{
	nbase::ThreadManager::UnregisterThread();
}

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	// �������´����߳�
	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "Global Misc Thread"));
	misc_thread_->Start();

	//����DPI����Ӧ����
	bool bAdaptDpi = true;

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	std::wstring app_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Instance().Startup(app_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);

	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	ControlForm* window = new ControlForm();
	window->CreateWnd(NULL, ControlForm::kClassName.c_str(), UI_WNDSTYLE_FRAME, WS_EX_LAYERED);
	window->CenterWindow();
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Instance().Shutdown();

	misc_thread_->Stop();
	misc_thread_.reset(nullptr);

	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
