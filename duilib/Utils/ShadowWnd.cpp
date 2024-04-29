#include "ShadowWnd.h"
#include "duilib/Core/Box.h"
#include "duilib/Core/Shadow.h"

namespace ui {

/**@brief һ�����ӵ�����������Χ�Ĵ��ڣ����� WS_EX_LAYERED ������ʵ����Ӱ
	* @copyright (c) 2016, NetEase Inc. All rights reserved
	* @date 2019-03-22
	*/
class ShadowWndBase : public ui::WindowImplBase, public ui::IUIMessageFilter
{
public:
	ShadowWndBase();

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	virtual LRESULT FilterMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;
	bool Create(Window* window);
private:
	Window* m_pWindow;
	//��Ǳ�����Ĵ����Ƿ�����״λ���
	bool m_isFirstPainted;
};

ShadowWndBase::ShadowWndBase():
	m_pWindow(nullptr),
	m_isFirstPainted(false)
{
}

std::wstring ShadowWndBase::GetSkinFolder()
{
	return L"";
}

std::wstring ShadowWndBase::GetSkinFile()
{
	return L"public/shadow/shadow.xml";
}

std::wstring ShadowWndBase::GetWindowClassName() const
{
	return L"ShadowWnd";
}

bool ShadowWndBase::Create(Window* window)
{
	m_pWindow = window;
	return Window::CreateWnd(NULL, L"ShadowWnd", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
}

LRESULT ShadowWndBase::FilterMessage(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& bHandled)
{
	bHandled = false;
	if ((m_pWindow == nullptr) || (m_pWindow->GetHWND() == nullptr)) {
		return 0;
	}
	HWND hWnd = m_pWindow->GetHWND();
	switch (uMsg)
	{
		case WM_ERASEBKGND:
		case WM_PAINT:
		case WM_MOVE:
		case WM_SIZE:
		case WM_SIZING:
		case WM_WINDOWPOSCHANGING:
		case WM_WINDOWPOSCHANGED:
		case WM_ACTIVATE:
		case WM_NCACTIVATE:
			if (m_isFirstPainted || (uMsg == WM_PAINT)) {
				if (::IsWindowVisible(hWnd)) {
					RECT rc = { 0 };
					::GetWindowRect(hWnd, &rc);
					SetWindowPos(ui::UiRect(rc.left, rc.top, rc.right, rc.bottom), false, SWP_SHOWWINDOW | SWP_NOACTIVATE, hWnd);
					m_isFirstPainted = true;
				}
			}			
			break;
		case WM_CLOSE:
			ShowWindow(false, false);
			break;
		case WM_SHOWWINDOW:
			ShowWindow(wParam == 0 ? false : true, false);
			break;
		default:
			break;
	}
	return 0;
}

ShadowWnd::ShadowWnd():
	m_pShadowWnd(nullptr)
{
}

bool ShadowWnd::CreateWnd(HWND hwndParent, const wchar_t* windowName, uint32_t dwStyle, uint32_t dwExStyle, const ui::UiRect& rc )
{
	ASSERT((m_pShadowWnd == nullptr) && (GetHWND() == nullptr));
	if ((m_pShadowWnd != nullptr) || (GetHWND() != nullptr)){
		return false;
	}
	//ȡ���㴰������
	dwExStyle &= ~WS_EX_LAYERED;
	__super::CreateWnd(hwndParent, windowName, dwStyle, dwExStyle, rc);

	bool needCreateShadowWnd = NeedCreateShadowWnd();
	if (!needCreateShadowWnd) {
		//�����ļ��������˲㴰�ڣ����߹ر���Ӱ�����ٸ���͸����Ӱ		
		return GetHWND() != nullptr;
	}
	//�ر�Ĭ�ϵĴ�����Ӱ
	if (IsShadowAttached()) {
		if (IsUseDefaultShadowAttached()) {
			SetShadowAttached(false);
			SetUseDefaultShadowAttached(true);
		}
		else {
			SetShadowAttached(false);
		}
	}	
	 
	//ͨ��XML�����ļ�<Window>��������ʱ��������͸�����ڵ���Ӱ��
	//   layered_window = "false" shadow_attached = "true";
	if (m_pShadowWnd != nullptr) {
		m_pShadowWnd->Create(this);
		::EnableWindow(m_pShadowWnd->GetHWND(), FALSE);
		if (::IsWindowVisible(GetHWND())) {
			m_pShadowWnd->ShowWindow();
		}
	}
	return GetHWND() != nullptr;
}

Box* ShadowWnd::AttachShadow(Box* pRoot)
{
	ASSERT(m_pShadowWnd == nullptr);
	if (m_pShadowWnd != nullptr) {
		return __super::AttachShadow(pRoot);
	}

	bool needCreateShadowWnd = NeedCreateShadowWnd();
	if (!needCreateShadowWnd) {
		//�����㸽��͸��������Ӱ��������ԭ���߼�
		return __super::AttachShadow(pRoot);
	}
	else {
		//������Ĭ�ϵ���Ӱ�����Ǵ����Լ���͸�����ڣ���Ϊ��Ӱ
		m_pShadowWnd = new ShadowWndBase;
		AddMessageFilter(m_pShadowWnd);

		//���õ���Ӱ������Ҫ��ԭ��������ΪԲ�ǣ�����Բ�Ǵ����ֺ�ɫ����
		UiSize borderRound = Shadow::GetChildBoxBorderRound();
		SetRoundCorner(borderRound.cx, borderRound.cy);
		pRoot->SetBorderRound(borderRound);
		return pRoot;
	}
}

bool ShadowWnd::NeedCreateShadowWnd() const
{
	if (IsLayeredWindow()) {
		//�����˲㴰�����ԣ�������
		return false;
	}
	if (IsUseDefaultShadowAttached()) {
		//�����ļ��У������ⲿ�ӿ��У�δ����ShadowAttached���ԣ�����
		return true;
	}
	else {
		//�����ļ��������ã��������ļ��е�����Ϊ׼
		return IsShadowAttached();
	}	
}

} // namespace ui
