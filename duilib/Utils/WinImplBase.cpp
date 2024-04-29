#include "WinImplBase.h"
#include "duilib/Core/WindowBuilder.h"
#include "duilib/Core/Box.h"

namespace ui
{

WindowImplBase::WindowImplBase()
{
}

WindowImplBase::~WindowImplBase()
{
}

void WindowImplBase::OnInitWindow()
{
}

Control* WindowImplBase::CreateControl(const std::wstring& /*strClass*/)
{
    return nullptr;
}

UINT WindowImplBase::GetStyle() const
{
    ASSERT(::IsWindow(GetHWND()));
    UINT styleValue = (UINT)::GetWindowLong(GetHWND(), GWL_STYLE);

    //ʹ���Ի�ı���������ԭ��������ʽ�У��Ƴ� WS_CAPTION ����
    styleValue &= ~WS_CAPTION;
    return styleValue;
}

LRESULT WindowImplBase::OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    LRESULT lRes = 0;
    bHandled = false;
    switch (uMsg)
    {
    case WM_CREATE:			lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
    case WM_SYSCOMMAND:		lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
    //������Ϣ���޾���ʵ��
    case WM_CLOSE:			lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
    case WM_DESTROY:		lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
    case WM_MOUSEMOVE:		lRes = OnMouseMove(uMsg, wParam, lParam, bHandled); break;
    case WM_MOUSEWHEEL:		lRes = OnMouseWheel(uMsg, wParam, lParam, bHandled); break;
    case WM_MOUSEHOVER:		lRes = OnMouseHover(uMsg, wParam, lParam, bHandled); break;
    case WM_LBUTTONDOWN:	lRes = OnLButtonDown(uMsg, wParam, lParam, bHandled); break;
    case WM_LBUTTONUP:		lRes = OnLButtonUp(uMsg, wParam, lParam, bHandled); break;
    case WM_LBUTTONDBLCLK:	lRes = OnLButtonDbClk(uMsg, wParam, lParam, bHandled); break;
    case WM_RBUTTONDOWN:	lRes = OnRButtonDown(uMsg, wParam, lParam, bHandled); break;
    case WM_RBUTTONUP:		lRes = OnRButtonUp(uMsg, wParam, lParam, bHandled); break;
    case WM_RBUTTONDBLCLK:	lRes = OnRButtonDbClk(uMsg, wParam, lParam, bHandled); break;
    case WM_CHAR:			lRes = OnChar(uMsg, wParam, lParam, bHandled); break;
    case WM_KEYDOWN:		lRes = OnKeyDown(uMsg, wParam, lParam, bHandled); break;
    case WM_KEYUP:			lRes = OnKeyUp(uMsg, wParam, lParam, bHandled); break;
    case WM_SYSKEYDOWN:		lRes = OnSysKeyDown(uMsg, wParam, lParam, bHandled); break;
    case WM_SYSKEYUP:		lRes = OnSysKeyUp(uMsg, wParam, lParam, bHandled); break;
    case WM_HOTKEY:		    lRes = OnHotKey(uMsg, wParam, lParam, bHandled); break;
    default:
        bHandled = false;
        break;
    }
    return lRes;
}

LRESULT WindowImplBase::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    ::SetWindowLong(this->GetHWND(), GWL_STYLE, GetStyle());

    InitWnd(GetHWND());
    SetResourcePath(GetSkinFolder());

    std::wstring strSkinFile;
    std::wstring xmlFile = GetSkinFile();
    if (!xmlFile.empty() && xmlFile.front() == L'<') {
        //���ص�������XML�ļ����ݣ��������ļ�·��
        strSkinFile = std::move(xmlFile);
    }
    else {
        strSkinFile = GetResourcePath() + xmlFile;
    }
    auto callback = nbase::Bind(&WindowImplBase::CreateControl, this, std::placeholders::_1);
    WindowBuilder builder;
    Box* pRoot = builder.Create(strSkinFile, callback, this);

    ASSERT(pRoot && L"Faield to load xml file.");
    if (pRoot == nullptr) {
        return -1;
    }

    if (IsUseSystemCaption()) {
        //�ر���Ӱ
        SetShadowAttached(false);
    }

    //�������ڸ�����Ӱ
    pRoot = AttachShadow(pRoot);

    //����Root����
    AttachBox(pRoot);

    //�����Ի��Ʊ�����״̬
    OnUseSystemCaptionBarChanged();
    if (!IsUseSystemCaption()) {
        Control* pControl = (Control*)FindControl(DUI_CTR_BUTTON_CLOSE);
        if (pControl) {
            ASSERT(pControl->GetType() == DUI_CTR_BUTTON);
            pControl->AttachClick(nbase::Bind(&WindowImplBase::OnButtonClick, this, std::placeholders::_1));
        }

        pControl = (Control*)FindControl(DUI_CTR_BUTTON_MIN);
        if (pControl) {
            ASSERT(pControl->GetType() == DUI_CTR_BUTTON);
            pControl->AttachClick(nbase::Bind(&WindowImplBase::OnButtonClick, this, std::placeholders::_1));
        }

        pControl = (Control*)FindControl(DUI_CTR_BUTTON_MAX);
        if (pControl) {
            ASSERT(pControl->GetType() == DUI_CTR_BUTTON);
            pControl->AttachClick(nbase::Bind(&WindowImplBase::OnButtonClick, this, std::placeholders::_1));
        }

        pControl = (Control*)FindControl(DUI_CTR_BUTTON_RESTORE);
        if (pControl) {
            ASSERT(pControl->GetType() == DUI_CTR_BUTTON);
            pControl->AttachClick(nbase::Bind(&WindowImplBase::OnButtonClick, this, std::placeholders::_1));
        }
        pControl = (Control*)FindControl(DUI_CTR_BUTTON_FULLSCREEN);
        if (pControl) {
            ASSERT(pControl->GetType() == DUI_CTR_BUTTON);
            pControl->AttachClick(nbase::Bind(&WindowImplBase::OnButtonClick, this, std::placeholders::_1));
        }
    }
    return 0;
}

void WindowImplBase::OnFinalMessage(HWND hWnd)
{
    __super::OnFinalMessage(hWnd);
    delete this;
}

LRESULT WindowImplBase::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    bHandled = true;
    if (wParam == SC_CLOSE) {
        //�����رմ���
        Close();
        return 0;
    }
    //���ȵ���Ĭ�ϵĴ��ں�����ʹ��������Ч
    BOOL bZoomed = ::IsZoomed(GetHWND());
    LRESULT lRes = this->CallDefaultWindowProc(uMsg, wParam, lParam);
    if (::IsZoomed(GetHWND()) != bZoomed) {
        if (wParam == 0xF012) {
            //�޸�������󻯺ͻ�ԭ��ť��״̬���������ʱ�������϶������������ڻ�ı�Ϊ�����״̬��
            ProcessMaxRestoreStatus();
        }
    }

    return lRes;
}

bool WindowImplBase::OnButtonClick(const EventArgs& msg)
{
    if (IsUseSystemCaption()) {
        return true;
    }
    ASSERT(msg.pSender != nullptr);
    if (msg.pSender == nullptr) {
        return false;
    }
    std::wstring sCtrlName = msg.pSender->GetName();
    if (sCtrlName == DUI_CTR_BUTTON_CLOSE) {
        //�رհ�ť
        CloseWnd();
    }
    else if (sCtrlName == DUI_CTR_BUTTON_MIN) {
        //��С����ť
        Minimized();
    }
    else if (sCtrlName == DUI_CTR_BUTTON_MAX) {
        //��󻯰�ť        
        Maximized();
    }
    else if (sCtrlName == DUI_CTR_BUTTON_RESTORE) {
        //��ԭ��ť        
        Restore();
    }
    else if (sCtrlName == DUI_CTR_BUTTON_FULLSCREEN) {
        //ȫ����ť
        EnterFullScreen();
    }

    return true;
}

void WindowImplBase::OnWindowEnterFullScreen()
{
    if (!IsUseSystemCaption()) {
        Control* pCaptionBar = FindControl(DUI_CTR_CAPTION_BAR);
        if (pCaptionBar != nullptr) {
            pCaptionBar->SetVisible(false);
        }
    }
}

void WindowImplBase::OnWindowExitFullScreen()
{
    if (!IsUseSystemCaption()) {
        Control* pCaptionBar = FindControl(DUI_CTR_CAPTION_BAR);
        if (pCaptionBar != nullptr) {
            pCaptionBar->SetVisible(true);
        }
        ProcessMaxRestoreStatus();
    }
}

void WindowImplBase::OnWindowMaximized()
{
    ProcessMaxRestoreStatus();
}

void WindowImplBase::OnWindowRestored()
{
    ProcessMaxRestoreStatus();
}

void WindowImplBase::OnWindowMinimized()
{
}

void WindowImplBase::OnUseSystemCaptionBarChanged()
{
    __super::OnUseSystemCaptionBarChanged();
    if (GetRoot() == nullptr) {
        return;
    }
    Control* pCaptionBar = FindControl(DUI_CTR_CAPTION_BAR);
    if (pCaptionBar != nullptr) {
        pCaptionBar->SetVisible(!IsUseSystemCaption());
        if (!IsUseSystemCaption()) {
            ProcessMaxRestoreStatus();
        }
    }
}

void WindowImplBase::ProcessMaxRestoreStatus()
{
    if (IsUseSystemCaption()) {
        return;
    }
    Control* pMaxButton = (Control*)FindControl(DUI_CTR_BUTTON_MAX);
    Control* pRestoreButton = (Control*)FindControl(DUI_CTR_BUTTON_RESTORE);
    bool bWindowMax = IsWindowMaximized();
    if (pMaxButton != nullptr) {
        pMaxButton->SetFadeVisible(bWindowMax ? false : true);
    }
    if (pRestoreButton != nullptr) {
        pRestoreButton->SetFadeVisible(bWindowMax ? true : false);
    }
}

LRESULT WindowImplBase::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnMouseHover(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnLButtonDbClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnRButtonDbClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnChar(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnSysKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnSysKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, bool& bHandled)
{
    bHandled = false;
    return 0;
}

LRESULT WindowImplBase::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
    ASSERT_UNUSED_VARIABLE(uMsg == WM_HOTKEY);
    UNUSED_VARIABLE(wParam);
    UNUSED_VARIABLE(lParam);
    bHandled = false;
    return 0;
}

}
