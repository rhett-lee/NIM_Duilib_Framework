#include "MainThread.h"

void WorkerThread::Init()
{
	::OleInitialize(NULL);
	nbase::ThreadManager::RegisterThread(m_threadID);
}

void WorkerThread::Cleanup()
{
	nbase::ThreadManager::UnregisterThread();
	::OleUninitialize();
}

void MainThread::Init()
{
	::OleInitialize(NULL);
	nbase::ThreadManager::RegisterThread(kThreadUI);

	//启动工作线程
	m_workerThread.reset(new WorkerThread(kThreadWorker, "WorkerThread"));
	m_workerThread->Start();

	//开启DPI自适应功能
	bool bAdaptDpi = true;

	// 获取资源路径，初始化全局参数
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

	// Debug 模式下使用本地文件夹作为资源
	// 默认皮肤使用 resources\\themes\\default
	// 默认语言使用 resources\\lang\\zh_CN
	// 如需修改请指定 Startup 最后两个参数
	ui::GlobalManager::Instance().Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), bAdaptDpi);

	ui::ColorPicker* pColorPicker = new ui::ColorPicker;
	pColorPicker->CreateWnd(nullptr, ui::ColorPicker::kClassName.c_str(), UI_WNDSTYLE_FRAME, WS_EX_LAYERED);
	pColorPicker->CenterWindow();
	pColorPicker->ShowWindow();

	//设置选择前的颜色
	pColorPicker->SetSelectedColor(ui::UiColor(ui::UiColors::White));

	//窗口关闭事件
	pColorPicker->AttachWindowClose([this](const ui::EventArgs& args) {
		//关闭窗口后，退出主线程
		PostQuitMessage(0L);
		return true;
		});
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
