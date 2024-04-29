// basic.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "main.h"
#include "browser/multi_browser_manager.h"

#include <clocale>

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

	_wsetlocale(LC_ALL, L"chs");

#ifdef _DEBUG
	AllocConsole();
	FILE* fp = NULL;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	wprintf_s(L"Command:\n%s\n\n", lpCmdLine);
#endif

	HRESULT hr = ::OleInitialize(NULL);
	if (FAILED(hr))
		return 0;

	//������CefManager::Initializeǰ���ã�����DPI����Ӧ���ԣ�����ᵼ����ʾ������
	ui::GlobalManager::Instance().Dpi().SetAdaptDPI(bAdaptDpi);

	// ��ʼ�� CEF
	CefSettings settings;
	if (!nim_comp::CefManager::GetInstance()->Initialize(nbase::win32::GetCurrentModuleDirectory() + L"cef_temp\\", settings, true))
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

	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();
	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);

	nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
	std::string timeStamp = nbase::StringPrintf("%I64u", time_delta.ToMilliseconds());
	MultiBrowserManager::GetInstance()->CreateBorwserBox(NULL, timeStamp, L"");
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Instance().Shutdown();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
