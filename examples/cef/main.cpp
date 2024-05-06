// basic.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "main.h"
#include "cef_form.h"

enum ThreadId
{
	kThreadUI
};

//����DPI����Ӧ����
bool bAdaptDpi = true;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �� bin\\cef Ŀ¼��ӵ������������������Խ����� CEF ����ļ��ŵ���Ŀ¼�£��������
	// ����Ŀ����->������->���룬�ӳټ��� nim_libcef.dll
	nim_comp::CefManager::GetInstance()->AddCefDllToPath();

	HRESULT hr = ::OleInitialize(NULL);
	if (FAILED(hr))
		return 0;

	//������CefManager::Initializeǰ���ã�����DPI����Ӧ���ԣ�����ᵼ����ʾ������
	ui::GlobalManager::Instance().Dpi().SetAdaptDPI(bAdaptDpi);

	// ��ʼ�� CEF
	CefSettings settings;
	if (!nim_comp::CefManager::GetInstance()->Initialize(nbase::win32::GetCurrentModuleDirectory() + L"cef_temp\\", settings, kEnableOffsetRender))
	{
		return 0;
	}

	// �������߳�
	MainThread thread;

	// ִ�����߳�ѭ��
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

    // ���� CEF
	nim_comp::CefManager::GetInstance()->UnInitialize();

	::OleUninitialize();

	return 0;
}

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	// Ĭ��Ƥ��ʹ�� resources\\themes\\default
	// Ĭ������ʹ�� resources\\lang\\zh_CN
	// �����޸���ָ�� Startup �����������
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);

	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	CefForm* window = new CefForm();
	uint32_t dwExStyle = 0;
	if (nim_comp::CefManager::GetInstance()->IsEnableOffsetRender()) {
		dwExStyle |= WS_EX_LAYERED;
	}
	window->CreateWnd(NULL, CefForm::kClassName.c_str(), UI_WNDSTYLE_FRAME, dwExStyle);
	window->CenterWindow();
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Instance().Shutdown();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
