#include "taskbar_manager.h"
#include "duilib/RenderGdiPlus/BitmapHelper.h"
#include "dwm_util.h"
#include <shobjidl.h>

using namespace ui;

TaskbarTabItem::TaskbarTabItem(ui::Control *bind_control)
{
	ASSERT(NULL != bind_control);
	bind_control_ = bind_control;
	is_win7_or_greater_ = IsWindows7OrGreater();
	taskbar_manager_ = NULL;
}

ui::Control* TaskbarTabItem::GetBindControl()
{
	return bind_control_;
}

std::string& TaskbarTabItem::GetId()
{
	return id_;
}

void TaskbarTabItem::Init(const std::wstring &taskbar_title, const std::string &id)
{
	id_ = id;
	if (!is_win7_or_greater_)
		return;

	CreateWnd(NULL, taskbar_title.c_str(), WS_OVERLAPPED, 0);

	HRESULT ret = S_OK;
	BOOL truth = TRUE;
	ret |= DwmSetWindowAttribute(GetHWND(), DWMWA_HAS_ICONIC_BITMAP, &truth, sizeof(truth));
	ret |= DwmSetWindowAttribute(GetHWND(), DWMWA_FORCE_ICONIC_REPRESENTATION, &truth, sizeof(truth));
	if (ret != S_OK)
	{
		is_win7_or_greater_ = false;
	}
}

void TaskbarTabItem::UnInit()
{
	if (NULL != GetHWND())
		DestroyWindow(GetHWND());
}

void TaskbarTabItem::SetTaskbarTitle(const std::wstring &title)
{
	::SetWindowTextW(GetHWND(), title.c_str());
}

void TaskbarTabItem::SetTaskbarManager(TaskbarManager *taskbar_manager)
{
	taskbar_manager_ = taskbar_manager;
}

TaskbarManager* TaskbarTabItem::GetTaskbarManager()
{
	return taskbar_manager_;
}

bool TaskbarTabItem::InvalidateTab()
{
	if (!is_win7_or_greater_ || NULL == taskbar_manager_)
		return false;

	return (S_OK == DwmInvalidateIconicBitmaps(this->GetHWND()));
}

void TaskbarTabItem::OnSendThumbnail(int width, int height)
{
	if (!is_win7_or_greater_ || NULL == taskbar_manager_)
		return;

	ui::IBitmap* pBitmap = taskbar_manager_->GenerateBindControlBitmap(bind_control_, width, height);
	HBITMAP hBitmap = ui::BitmapHelper::CreateGDIBitmap(pBitmap);
	DwmSetIconicThumbnail(GetHWND(), hBitmap, 0);
	if (pBitmap != nullptr) {
		delete pBitmap;
		pBitmap = nullptr;
	}
	if (hBitmap != nullptr) {
		::DeleteObject(hBitmap);
		hBitmap = nullptr;
	}
}

void TaskbarTabItem::OnSendPreview()
{
	if (!is_win7_or_greater_ || NULL == taskbar_manager_)
		return;

	ui::IBitmap* pBitmap = taskbar_manager_->GenerateBindControlBitmapWithForm(bind_control_);
	HBITMAP hBitmap = ui::BitmapHelper::CreateGDIBitmap(pBitmap);
	DwmSetIconicLivePreviewBitmap(GetHWND(), hBitmap, NULL, 0);
	if (pBitmap != nullptr) {
		delete pBitmap;
		pBitmap = nullptr;
	}
	if (hBitmap != nullptr) {
		::DeleteObject(hBitmap);
		hBitmap = nullptr;
	}
}

std::wstring TaskbarTabItem::GetWindowClassName() const
{
	return L"Nim.TaskbarItem";
}

LRESULT TaskbarTabItem::OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	bHandled = true;
	if (uMsg == WM_DWMSENDICONICTHUMBNAIL)
	{
		OnSendThumbnail(HIWORD(lParam), LOWORD(lParam));
		return 0;
	}
	else if (uMsg == WM_DWMSENDICONICLIVEPREVIEWBITMAP)
	{
		OnSendPreview();
		return 0;
	}
	else if (uMsg == WM_GETICON)
	{
		InvalidateTab();
	}
	else if (uMsg == WM_CLOSE)
	{
		if (NULL != taskbar_manager_)
			taskbar_manager_->OnTabItemClose(*this);

		return 0;
	}
	else if (uMsg == WM_ACTIVATE)
	{
		if (NULL != taskbar_manager_)
		{
			if (wParam != WA_INACTIVE)
			{
				taskbar_manager_->OnTabItemClicked(*this);
			}
		}
			
		return 0;
	}
	return __super::OnWindowMessage(uMsg, wParam, lParam, bHandled);
}

void TaskbarTabItem::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

TaskbarManager::TaskbarManager()
{
	taskbar_delegate_ = NULL;
	taskbar_list_ = NULL;
}

void TaskbarManager::Init(ITaskbarDelegate *taskbar_delegate)
{
	ASSERT(NULL != taskbar_delegate);
	taskbar_delegate_ = taskbar_delegate;

	::CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&taskbar_list_));
	if (taskbar_list_)
	{
		taskbar_list_->HrInit();

		BOOL truth = FALSE;
		DwmSetWindowAttribute(taskbar_delegate_->GetHandle(), DWMWA_HAS_ICONIC_BITMAP, &truth, sizeof(truth));
		DwmSetWindowAttribute(taskbar_delegate_->GetHandle(), DWMWA_FORCE_ICONIC_REPRESENTATION, &truth, sizeof(truth));
	}
		
}

bool TaskbarManager::RegisterTab(TaskbarTabItem &tab_item)
{
	if (taskbar_list_ && NULL == tab_item.GetTaskbarManager())
	{
		if (S_OK == taskbar_list_->RegisterTab(tab_item.GetHWND(), taskbar_delegate_->GetHandle()))
		{
			if (S_OK == taskbar_list_->SetTabOrder(tab_item.GetHWND(), NULL))
			{
				tab_item.SetTaskbarManager(this);
				return true;
			}			
		}
	}

	return false;
}

bool TaskbarManager::UnregisterTab(TaskbarTabItem &tab_item)
{
	if (taskbar_list_)
	{
		tab_item.SetTaskbarManager(NULL);
		return (S_OK == taskbar_list_->UnregisterTab(tab_item.GetHWND()));
	}
	else
		return false;
}

bool TaskbarManager::SetTabOrder(const TaskbarTabItem &tab_item, const TaskbarTabItem &tab_item_insert_before)
{
	if (taskbar_list_)
	{
		return (S_OK == taskbar_list_->SetTabOrder(tab_item.GetHWND(), tab_item_insert_before.GetHWND()));
	}
	else
		return false;
}

bool TaskbarManager::SetTabActive(const TaskbarTabItem &tab_item)
{
	if (taskbar_list_)
	{
		return (S_OK == taskbar_list_->SetTabActive(tab_item.GetHWND(), taskbar_delegate_->GetHandle(), 0));
	}
	else
		return false;
}

ui::IBitmap* TaskbarManager::GenerateBindControlBitmapWithForm(ui::Control *control)
{
	ASSERT( NULL != control);
	if ( NULL == control)
		return NULL;

	int window_width = 0, window_height = 0;
	RECT rc_wnd;
	bool check_wnd_size = false;
	if (::IsIconic(taskbar_delegate_->GetHandle())) //��ǰ����С��״̬
	{
		WINDOWPLACEMENT placement{ sizeof(WINDOWPLACEMENT) };
		::GetWindowPlacement(taskbar_delegate_->GetHandle(), &placement);
		if (placement.flags == WPF_RESTORETOMAXIMIZED) //��С��ǰ�����״̬
		{
			MONITORINFO oMonitor = { sizeof(MONITORINFO) };
			::GetMonitorInfo(::MonitorFromWindow(taskbar_delegate_->GetHandle(), MONITOR_DEFAULTTONEAREST), &oMonitor);
			rc_wnd = oMonitor.rcWork;
		}
		else
		{
			rc_wnd = placement.rcNormalPosition;
			check_wnd_size = true; //��������£�WINDOWPLACEMENT::rcNormalPosition����ȷ
		}
	}
	else
		::GetWindowRect(taskbar_delegate_->GetHandle(), &rc_wnd);
	window_width = rc_wnd.right - rc_wnd.left;
	window_height = rc_wnd.bottom - rc_wnd.top;
	if (window_width == 0 || window_height == 0)
		return nullptr;

	// 1.�����ڴ�dc
	std::unique_ptr<IRender> render;
	IRenderFactory* pRenderFactory = GlobalManager::Instance().GetRenderFactory();
	ASSERT(pRenderFactory != nullptr);
	if (pRenderFactory != nullptr) {
		render.reset(pRenderFactory->CreateRender());
	}
	ASSERT(render != nullptr);
	render->Resize(window_width, window_height);

	// 2.�Ѵ���˫�����λͼ�����ڴ�dc
	render->BitBlt(0, 0, window_width, window_height, taskbar_delegate_->GetTaskbarRender(), 0, 0, RopMode::kSrcCopy);

	// 3.��ĳ���Ự���ӵ�λͼ�����ڴ�dc������ԭ���ڶ�Ӧλ�õ�λͼ
	UiRect rcPaint = control->GetPos();
	if (rcPaint.IsEmpty())
		return NULL;
	rcPaint.Intersect(UiRect(0, 0, window_width, window_height));

	// ���ﲻ���ü������򣬾��޷���������
	{
		AutoClip rectClip(render.get(), rcPaint);
		control->Paint(render.get(), rcPaint);
	}

	// 4.�޸����������alphaͨ��
	render->RestoreAlpha(rcPaint);
	return render->DetachBitmap();
}

ui::IBitmap* TaskbarManager::GenerateBindControlBitmap(ui::Control *control, const int dest_width, const int dest_height)
{
	ASSERT(dest_width > 0 && dest_height > 0 && NULL != control);
	if (dest_width <= 0 || dest_height <= 0 || NULL == control)
		return NULL;

	int window_width = 0, window_height = 0;
	RECT rc_wnd;
	bool check_wnd_size = false;
	if (::IsIconic(taskbar_delegate_->GetHandle())) //��ǰ����С��״̬
	{
		WINDOWPLACEMENT placement{ sizeof(WINDOWPLACEMENT) };
		::GetWindowPlacement(taskbar_delegate_->GetHandle(), &placement);
		if (placement.flags == WPF_RESTORETOMAXIMIZED) //��С��ǰ�����״̬
		{
			MONITORINFO oMonitor = { sizeof(MONITORINFO) };
			::GetMonitorInfo(::MonitorFromWindow(taskbar_delegate_->GetHandle(), MONITOR_DEFAULTTONEAREST), &oMonitor);
			rc_wnd = oMonitor.rcWork;
		}
		else
		{
			rc_wnd = placement.rcNormalPosition;
			check_wnd_size = true; //��������£�WINDOWPLACEMENT::rcNormalPosition����ȷ
		}
	}
	else
		::GetWindowRect(taskbar_delegate_->GetHandle(), &rc_wnd);
	window_width = rc_wnd.right - rc_wnd.left;
	window_height = rc_wnd.bottom - rc_wnd.top;
	if (window_width == 0 || window_height == 0)
		return nullptr;

	// 1.�����ڴ�dc
	std::unique_ptr<IRender> render;
	IRenderFactory* pRenderFactory = GlobalManager::Instance().GetRenderFactory();
	ASSERT(pRenderFactory != nullptr);
	if (pRenderFactory != nullptr) {
		render.reset(pRenderFactory->CreateRender());
	}
	ASSERT(render != nullptr);
	render->Resize(window_width, window_height);

	// 2.��ĳ���Ự���ӵ�λͼ�����ڴ�dc������ԭ���ڶ�Ӧλ�õ�λͼ
	UiRect rcPaint = control->GetPos();
	if (rcPaint.IsEmpty())
		return NULL;
	rcPaint.Intersect(UiRect(0, 0, window_width, window_height));

	// ���ﲻ���ü������򣬾��޷���������
	{
		AutoClip rectClip(render.get(), rcPaint);
		control->Paint(render.get(), rcPaint);
	}

	// 3.�޸����������alphaͨ��
	render->RestoreAlpha(rcPaint);

	// 4.���ŵ�Ŀ��ߴ�
	UiRect rcControl = control->GetPos();
	return ResizeBitmap(dest_width, dest_height, render.get(), rcControl.left, rcControl.top, rcControl.Width(), rcControl.Height());
}

ui::IBitmap* TaskbarManager::ResizeBitmap(int dest_width, int dest_height, ui::IRender* pSrcRender, int src_x, int src_y, int src_width, int src_height)
{
	std::unique_ptr<IRender> render;
	IRenderFactory* pRenderFactory = GlobalManager::Instance().GetRenderFactory();
	ASSERT(pRenderFactory != nullptr);
	if (pRenderFactory != nullptr) {
		render.reset(pRenderFactory->CreateRender());
	}
	ASSERT(render != nullptr);
	if (render->Resize(dest_width, dest_height))
	{
		int scale_width = 0;
		int scale_height = 0;

		float src_scale = (float)src_width / (float)src_height;
		float dest_scale = (float)dest_width / (float)dest_height;
		if (src_scale >= dest_scale)
		{
			scale_width = dest_width;
			scale_height = (int)(dest_width * (float)src_height / (float)src_width);
		}
		else
		{
			scale_height = dest_height;
			scale_width = (int)(dest_height * (float)src_width / (float)src_height);
		}

		render->AlphaBlend((dest_width - scale_width) / 2, (dest_height - scale_height) / 2, scale_width, scale_height, pSrcRender, src_x, src_y, src_width, src_height);
	}

	return render->DetachBitmap();
}

void TaskbarManager::OnTabItemClose(TaskbarTabItem &tab_item)
{
	taskbar_delegate_->CloseTaskbarItem(tab_item.GetId());
}

void TaskbarManager::OnTabItemClicked(TaskbarTabItem &tab_item)
{
	taskbar_delegate_->SetActiveTaskbarItem(tab_item.GetId());
}