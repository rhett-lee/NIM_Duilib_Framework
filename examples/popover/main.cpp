// popover.cpp : ����Ӧ�ó������ڵ㡣
//

#include "framework.h"
#include "popover_form.h"

enum ThreadId
{
  kThreadUI
};

class MainThread : public nbase::FrameworkThread
{
public:
  MainThread() : nbase::FrameworkThread("MainThread") {}
  virtual ~MainThread() {}

private:

  virtual void Init() override
  {
	nbase::ThreadManager::RegisterThread(kThreadUI);

	// ��ȡ��Դ·������ʼ��ȫ�ֲ���
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

	//����DPI����Ӧ����
	bool bAdaptDpi = true;

	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);


	// ����һ��Ĭ�ϴ�����Ӱ�ľ��д���
	PopoverForm* window = new PopoverForm();
	window->CreateWnd(NULL, PopoverForm::kClassName.c_str(), UI_WNDSTYLE_FRAME, WS_EX_LAYERED);
	window->CenterWindow();
	window->ShowWindow();
  }

  /**
  * �麯�������߳��˳�ʱ����һЩ������
  * @return void	�޷���ֵ
  */
  virtual void Cleanup() override
  {
    ui::GlobalManager::Instance().Shutdown();
    SetThreadWasQuitProperly(true);
    nbase::ThreadManager::UnregisterThread();
  }
};


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	// �������߳�
	MainThread thread;

	// ִ�����߳�ѭ��
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

    return 0;
}