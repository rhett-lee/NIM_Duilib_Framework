#ifndef UI_CORE_WINDOW_H_
#define UI_CORE_WINDOW_H_

#pragma once

#include "duilib/Utils/Delegate.h"
#include "base/callback/callback.h"
#include "duilib/Core/ControlFinder.h"
#include "duilib/Core/ColorManager.h"
#include "duilib/Core/UiTypes.h"

#include <string>

namespace ui
{

class Box;
class Control;
class IRender;
class Shadow;
class ToolTip;
class WindowDropTarget;
class ControlDropTarget;

/**  ������Ϣ���˽ӿڣ����ڽػ񴰿ڹ��̵���Ϣ��������Window�������Ϣ����
*/
class IUIMessageFilter
{
public:
    /**  ��Ϣ���������������ȼ�����Window�����Ϣ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ������ true ��ʾ�����ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT FilterMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////
//

/** ������
*  �ⲿ������Ҫ��ʼ���Ļ������̣�
*  1. ����Window::CreateWnd�������ڣ�
*  2. Window::InitWnd��
*  3. Window::SetResourcePath��
*  4. WindowBuilder::Create, �õ�Box* pRoot��
*  5. Window::AttachShadow(pRoot), �õ�������Ӱ��Box* pRoot, ��֧�ִ�����ӰЧ��
*  6. Window::AttachBox(pRoot)
*/
class UILIB_API Window : public virtual nbase::SupportWeakCallback
{
public:
    Window();
    Window(const Window& r) = delete;
    Window& operator=(const Window& r) = delete;
    virtual ~Window();

public:
    /** @name ���ڴ��������١��¼���������ؽӿ�
    * @{
    */

    /** ��������, ��ʹ�� OnInitWindow �ӿ���ʵ�ִ��ڴ�����ɺ���Զ�������
    * @param [in] hwndParent �����ھ��
    * @param [in] windowName ��������
    * @param [in] dwStyle ������ʽ
    * @param [in] dwExStyle ������չ��ʽ, �������ò㴰�ڣ�WS_EX_LAYERED��������
    * @param [in] rc ���ڴ�С
    */
    virtual bool CreateWnd(HWND hwndParent,
                           const wchar_t* windowName,
                           uint32_t dwStyle,
                           uint32_t dwExStyle,
                           const UiRect& rc = UiRect(0, 0, 0, 0));

    /** �Ƿ�����Ч�Ĵ��ھ��
    */
    bool IsWindow() const;

    /** ��ȡ���������� Windows ���
    */
    HWND GetHWND() const;

    /** ���໯���ڣ����Ĵ��ڹ��̺�����
    * @param [in] ���ھ��
    */
    bool Subclass(HWND hWnd);

    /** ȡ�����໯���ڣ��ָ�ԭ���Ĵ��ڹ��̺�����
    */
    void Unsubclass();

    /** �رմ���, �첽�رգ����������غ�IsClosing() ״̬Ϊtrue
    * @param [in] nRet �ر���Ϣ, �������£�
                0 - ��ʾ "ȷ��" �رձ�����
                1 - ��ʾ������ڵ� "�ر�" ��ť�رձ�����(Ĭ��ֵ)
                2 - ��ʾ "ȡ��" �رձ�����
    */
    virtual void CloseWnd(UINT nRet = 1);

    /** �Ƿ�Ҫ�ر�
    */
    bool IsClosingWnd() const { return m_bCloseing; }

    /** �������ڹر��¼�
    * @param [in] callback ָ���رպ�Ļص�������������wParam�����ڹرյĴ��������
                          0 - ��ʾ "ȷ��" �رձ�����
                          1 - ��ʾ������ڵ� "�ر�" ��ť�رձ�����(Ĭ��ֵ)
                          2 - ��ʾ "ȡ��" �رձ�����
    */
    void AttachWindowClose(const EventCallback& callback);

protected:
    /** ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ��������
    * @return ���෵�ؿմ�������������ʵ�ֲ����ش���Ψһ��������
    */
    virtual std::wstring GetWindowClassName() const;

    /** ��ȡ�ؼ�������
    * @return ���ؿؼ������࣬�û��෵�ؿմ�
    */
    virtual std::wstring GetSuperClassName() const;

    /** ��ȡ���������ʽ���÷�����ʵ����������ʵ�֣�https://docs.microsoft.com/en-us/windows/desktop/winmsg/window-class-styles
    * @return ���ش��������ʽ���÷������෵�� CS_DBLCLKS
    */
    virtual UINT GetClassStyle() const;

    /** ��ȡ��Դ�ľ��
    * @return Ĭ�Ϸ��ص�ǰ����exe�ľ��
    */
    virtual HMODULE GetResModuleHandle() const;

    /** ���ڽ��յ� WM_CREATE ��Ϣʱ�ᱻ����
    * @param [in] hWnd ���ھ��
    */
    virtual void InitWnd(HWND hWnd);

    /** �����յ����ڴ�����Ϣʱ�����ã�����������һЩ��ʼ���Ĺ���
     */
    virtual void OnInitWindow();

    /** �ڴ����յ� WM_NCDESTROY ��Ϣʱ�ᱻ����
    * @param [in] hWnd ���ھ��
    */
    virtual void OnFinalMessage(HWND hWnd);

    /** @} */

public:
    /** @name ������ʾ�����ء���С��λ�õ�״̬��ؽӿ�
    * @{
    */

    /** ��ʾ�����ش���
     * @param [in] bShow Ϊ true ʱ��ʾ���ڣ�Ϊ false ʱΪ���ش��ڣ�Ĭ��Ϊ true
     * @param [in] bTakeFocus �Ƿ��ý��㣨����ڣ���Ĭ��Ϊ true
    */
    virtual void ShowWindow(bool bShow = true, bool bTakeFocus = true);

    /** ��ʾģ̬�Ի���
    * @param [in] hParentWnd �����ھ��
    */
    void ShowModalFake(HWND hParentWnd);

    /** �Ƿ���ģ̬��ʾ
    */
    bool IsFakeModal() const;

    /** ���д��ڣ�֧����չ��Ļ
    */
    void CenterWindow();

    /** ����������Ϊ�ö�����
    */
    void ToTopMost();

    /** �����ڵ���Ϊ���㴰��
    */
    void BringToTop();

    /** �����
    *   �����ǰ����Ϊ��С��������л�ԭ��
    *   �����ǰ����Ϊ���أ�����ʾ��������Ϊǰ�˴���
    *   �����ǰ����Ϊ��ʾ��������Ϊǰ�˴���
    */
    void ActiveWindow();

    /** �������
    */
    bool Maximized();

    /** ��ԭ���ڣ��˳����
    */
    bool Restore();

    /** ������С��
    */
    bool Minimized();

    /** ʹ���ڽ���ȫ��״̬
    */
    bool EnterFullScreen();

    /** ʹ�����˳�ȫ��״̬ (Ĭ�ϰ�ESC��ʱ���˳�ȫ��)
    */
    bool ExitFullScreen();

    /** ���ô���Ϊǰ�˴���
    */
    bool SetForeground();

    /** ʹ���ڳ�Ϊ���㴰��
    */
    bool SetFocused();

    /** �رմ���, ͬ���ر�
    */
    void Close();

    /** ��ǰ�����Ƿ�Ϊ���뽹�㴰��
    */
    bool IsWindowFocused() const;

    /** ��ǰ�����Ƿ�Ϊǰ�˴���
    */
    bool IsWindowForeground() const;

    /** �����Ƿ�Ϊ���״̬
    */
    bool IsWindowMaximized() const;

    /** �����Ƿ�Ϊ��С��״̬
    */
    bool IsWindowMinimized() const;

    /** �����Ƿ�Ϊȫ��״̬
    */
    bool IsWindowFullScreen() const;

    /** ���´��ڣ�ִ���ػ� 
    */
    bool UpdateWindow() const;

public:
    /** ��ȡ����λ����Ϣ
     * @param [in] bContainShadow �Ƿ������Ӱ��true Ϊ������Ĭ��Ϊ false ������
     */
    UiRect GetWindowPos(bool bContainShadow = false) const;

    /** ���ô���λ�ã��� ::SetWindowPos API ��һ���װ��
    * @param [in] rc ����λ��
    * @param [in] bNeedDpiScale Ϊ false ��ʾ����Ҫ�� rc ���� DPI �Զ�����
    * @param [in] uFlags ��Ӧ ::SetWindowPos API �� uFlags ѡ��
    * @param [in] hWndInsertAfter ��Ӧ SetWindowPos �� hWndInsertAfter ѡ��
    * @param [in] bContainShadow rc�����Ƿ������Ӱ��Χ��Ĭ��Ϊ false
    */
    bool SetWindowPos(const UiRect& rc, bool bNeedDpiScale, UINT uFlags, HWND hWndInsertAfter = NULL, bool bContainShadow = false);

    /** ���ô���λ�ã��� ::SetWindowPos API ��һ���װ��
    * @param [in] hWndInsertAfter ��Ӧ SetWindowPos �� hWndInsertAfter ѡ��
    * @param [in] X ���ڵ�X����
    * @param [in] Y ���ڵ�Y����
    * @param [in] cx ���ڵĿ��
    * @param [in] cy ���ڵĸ߶�
    * @param [in] uFlags ��Ӧ ::SetWindowPos API �� uFlags ѡ�� 
    */
    bool SetWindowPos(HWND hWndInsertAfter, int32_t X, int32_t Y, int32_t cx, int32_t cy, UINT uFlags);

    /** ���ô��ڴ�С
    * @param [in] cx ���
    * @param [in] cy �߶�
    * @param [in] bContainShadow Ϊ false ��ʾ cx cy ��������Ӱ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ������ DPI ����
    */
    void Resize(int cx, int cy, bool bContainShadow = false, bool bNeedDpiScale = true);

    /** ���ô���ͼ��
    *  @param [in] nRes ����ͼ����Դ ID
    */
    void SetIcon(UINT nRes);

    /** ���ô��ڱ������ı�
    * @param [in] strText ���ڱ������ı�
    */
    void SetText(const std::wstring& strText);

    /** ���������б��е��ı� ID�� ����ID���ô��ڱ������ı�
    * @param [in] strTextId ���� ID���� ID �����������ļ��д���
    */
    void SetTextId(const std::wstring& strTextId);

    /** @} */

public:
    /** @name ���ڳ�ʼ��С������������ؽӿ�
    * @{
    */
    /** ��ȡ�����ı߿����췶Χ�Ĵ�С
    */
    const UiRect& GetSizeBox() const;

    /** ���ô����ı߿����췶Χ�Ĵ�С
    * @param [in] rcSizeBox Ҫ���õĴ�С
    */
    void SetSizeBox(const UiRect& rcSizeBox);

    /** ��ȡ���ڱ��������򣨿��϶����򣩣���Ӧ XML �� caption ����
    */
    const UiRect& GetCaptionRect() const;

    /** ���ô��ڱ���������
    * @param [in] rcCaption Ҫ���õ�����Χ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ������ DPI ����
    */
    void SetCaptionRect(const UiRect& rcCaption, bool bNeedDpiScale = true);

    /** �����Ƿ�ʹ��ϵͳ������
    */
    void SetUseSystemCaption(bool bUseSystemCaption);

    /** ��ȡ�Ƿ�ʹ��ϵͳ������
    */
    bool IsUseSystemCaption() const;

    /** ��ȡ����Բ�Ǵ�С����Ӧ XML �� roundcorner ����
    */
    const UiSize& GetRoundCorner() const;

    /** ���ô���Բ�Ǵ�С
    * @param [in] cx Բ�ǿ�
    * @param [in] cy Բ�Ǹ�
    */
    void SetRoundCorner(int cx, int cy);

    /** ��ȡ���������Ϣ
    */
    const UiRect& GetMaximizeInfo() const;

    /** ���ô��������Ϣ
    * @param [in] rcMaximize Ҫ���õ������ֵ
    */
    void SetMaximizeInfo(const UiRect& rcMaximize);

    /** ��ȡ͸��ͨ���޲���Χ�ĵľŹ�����������Ӧ XML �� alphafixcorner ����
    */
    const UiRect& GetAlphaFixCorner() const;

    /** ����͸��ͨ���޲���Χ�ĵľŹ�������
    * @param [in] rc Ҫ���õ��޲���Χ
    */
    void SetAlphaFixCorner(const UiRect& rc);

    /** ��ȡ������С��Χ����Ӧ XML �� mininfo ����
    * @param [in] bContainShadow �Ƿ������Ӱ��Χ��Ĭ��Ϊ false
    */
    UiSize GetMinInfo(bool bContainShadow = false) const;

    /** ���ô�����С��Χ
    * @param [in] cx ���
    * @param [in] cy �߶�
    * @param [in] bContainShadow Ϊ false ��ʾ cx cy ��������Ӱ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ����Ҫ�� rc ���� DPI �Զ�����
    */
    void SetMinInfo(int cx, int cy, bool bContainShadow = false, bool bNeedDpiScale = true);

    /** ��ȡ�������Χ����Ӧ XML �� maxinfo ����
    * @param [in] bContainShadow �Ƿ������Ӱ��Χ��Ĭ��Ϊ false
    */
    UiSize GetMaxInfo(bool bContainShadow = false) const;

    /** ���ô������Χ
    * @param [in] cx ���
    * @param [in] cy �߶�
    * @param [in] bContainShadow Ϊ false ��ʾ cx cy ��������Ӱ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ����Ҫ�� rc ���� DPI �Զ�����
    */
    void SetMaxInfo(int cx, int cy, bool bContainShadow = false, bool bNeedDpiScale = true);

    /** ��ȡ���ڳ�ʼ��С
    * @param [in] bContainShadow �Ƿ������Ӱ��Χ��Ĭ��Ϊ false
    */
    UiSize GetInitSize(bool bContainShadow = false) const;

    /** ���ô��ڳ�ʼ��С
    * @param [in] cx ���
    * @param [in] cy �߶�
    * @param [in] bContainShadow Ϊ false ��ʾ cx cy ��������Ӱ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ������ DPI ����
    */
    void SetInitSize(int cx, int cy, bool bContainShadow = false, bool bNeedDpiScale = true);

    /** @}*/

public:
    /** @name ���ڲ�����ؽӿ�
    * @{
    */
    /** �󶨴��ڵĶ�������
    * @param [in] pRoot ����ָ��
    */
    bool AttachBox(Box* pRoot);

    /** ��ȡ��������������
    */
    Box* GetRoot() const;

    /** ��ȡ������Դ·��
    */
    const std::wstring& GetResourcePath() const;

    /** ���ô�����Դ·��
    * @param [in] strPath Ҫ���õ�·��
    */
    void SetResourcePath(const std::wstring& strPath);

    /** ��ʼ���ؼ�������������ӿؼ�ʱ�ᱻ���ã����ڶԿؼ����������棩
    * @param [in] pControl �ؼ�ָ��
    */
    bool InitControls(Control* pControl);

    /** ��ʼ������
    */
    virtual void OnInitLayout();

    /** ���տؼ�
    * @param [in] pControl �ؼ�ָ��
    */
    void ReapObjects(Control* pControl);

    /** �ӳ�����һ���ؼ�
    * @param [in] pControl �ؼ�ָ��
    */
    void AddDelayedCleanup(Control* pControl);

    /** ���һ��ͨ����ʽ
    * @param [in] strClassName ͨ����ʽ������
    * @param [in] strControlAttrList ͨ����ʽ�� XML ת���ʽ����
    */
    void AddClass(const std::wstring& strClassName, const std::wstring& strControlAttrList);

    /** ��ȡָ��ͨ����ʽ������
    * @param [in] strClassName ͨ����ʽ����
    * @return ����ָ�����Ƶ�ͨ����ʽ���ݣ�XML ת���ʽ����
    */
    std::wstring GetClassAttributes(const std::wstring& strClassName) const;

    /** ɾ��һ��ͨ����ʽ
    * @param [in] strClassName Ҫɾ����ͨ����ʽ����
    */
    bool RemoveClass(const std::wstring& strClassName);

    /** ɾ������ͨ����ʽ
    */
    void RemoveAllClass();

    /** ���һ����ɫֵ�ṩ������ʹ��
    * @param [in] strName ��ɫ���ƣ��� white��
    * @param [in] strValue ��ɫ������ֵ���� #FFFFFFFF��
    */
    void AddTextColor(const std::wstring& strName, const std::wstring& strValue);

    /** ���һ����ɫֵ�ṩ������ʹ��
    * @param [in] strName ��ɫ���ƣ��� white��
    * @param [in] argb ��ɫ������ֵ, ��ARGB��ʽ��ʾ
    */
    void AddTextColor(const std::wstring& strName, UiColor argb);

    /** �������ƻ�ȡһ����ɫ�ľ�����ֵ
    * @param [in] strName Ҫ��ȡ����ɫ����
    * @return ���� DWORD ��ʽ����ɫ����ֵ
    */
    UiColor GetTextColor(const std::wstring& strName) const;

    /** ���һ��ѡ����
    * @param [in] strGroupName ������
    * @param [in] pControl �ؼ�ָ��
    */
    bool AddOptionGroup(const std::wstring& strGroupName, Control* pControl);

    /** ��ȡָ��ѡ�����пؼ��б�
    * @param [in] strGroupName ָ��������
    * @return ���ظ����µ����пؼ��б�
    */
    std::vector<Control*>* GetOptionGroup(const std::wstring& strGroupName);

    /** ɾ��һ��ѡ����
    * @param [in] strGroupName ������
    * @param [in] pControl �ؼ�����
    */
    void RemoveOptionGroup(const std::wstring& strGroupName, Control* pControl);

    /** ɾ������ѡ����
    */
    void RemoveAllOptionGroups();

    /** @}*/

public:
    /** @name ������Ϣ��صĽӿ�
    * @{
    */
    /** ���һ����Ϣ����������ʱ��Ϣ�Ѿ��ɷ����ýӿڵ���Ϣ�������ȼ�����Window�����Ϣ������
    * @param [in] pFilter һ���̳��� IUIMessageFilter �Ķ���ʵ������Ҫʵ�ֽӿ��еķ���
    */
    bool AddMessageFilter(IUIMessageFilter* pFilter);

    /** �Ƴ�һ����Ϣ������
    * @param [in] pFilter һ���̳��� IUIMessageFilter �Ķ���ʵ��
    */
    bool RemoveMessageFilter(IUIMessageFilter* pFilter);

    /** ������Ϣ���� Windows SendMessage ��һ���װ
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ���ش��ڶ���Ϣ�Ĵ�����
    */
    LRESULT SendMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);

    /** Ͷ��һ����Ϣ����Ϣ����
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ���ش��ڶ���Ϣ�Ĵ�����
    */
    LRESULT PostMsg(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);

    /** ��������һ����Ϣ, ���͸��ô��ڵ��¼��ص���������m_OnEvent����ע�����Ϣ������
    * @param [in] eventType ת�������Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    */
    bool SendNotify(EventType eventType, WPARAM wParam = 0, LPARAM lParam = 0);

    /** ����ϵͳĬ�ϵĴ��ڴ��������� CallWindowProc API ��һ���װ
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ������Ϣ������
    */
    LRESULT CallDefaultWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:

    /** ������Ϣ�Ĵ�����, ��ϵͳ���յ���Ϣ�󣬽���ĵ�һ��������
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ������Ϣ�Ĵ�����
    */
    LRESULT WindowMessageProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

    /** ������Ϣ���ɷ�����
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ��Ϣ�Ƿ��Ѿ�����
                ���� true  �����Ѿ��ɹ�������Ϣ������Ҫ�ٴ��ݸ����ڹ��̣�
                ���� false ��ʾ����Ϣ�������ݸ����ڹ��̴���
    * @return ������Ϣ�Ĵ�����
    */
    virtual LRESULT OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ������Ϣ���ɷ����������ȵ����ڲ�������������ڲ��޴����߼��������WindowsĬ�ϴ������������Ϣ
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ��Ϣ�Ƿ��Ѿ��������� true �����Ѿ��ɹ�������Ϣ��������Ϣ�������ݸ����ڹ���
    * @return ������Ϣ�Ĵ�����
    */
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** @}*/

    /** ����ȫ��״̬
    */
    virtual void OnWindowEnterFullScreen() {}

    /** �˳�ȫ��״̬
    */
    virtual void OnWindowExitFullScreen() {}

    /** �������״̬
    */
    virtual void OnWindowMaximized() {}

    /** ����󻯻�ԭ
    */
    virtual void OnWindowRestored() {}

    /** ������С��״̬
    */
    virtual void OnWindowMinimized() {}

    /** �л�ϵͳ���������Ի������
    */
    virtual void OnUseSystemCaptionBarChanged();

private:
    /** @name ˽�д�����Ϣ�������
    * @{
    */
    //������Ϣ����������ʵ�ֻ�������    
    LRESULT OnNcActivateMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnNcCalcSizeMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnNcHitTestMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnNcLButtonDbClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    LRESULT OnCloseMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnGetMinMaxInfoMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnWindowPosChangingMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSizeMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnMoveMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnEraseBkGndMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnPaintMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    LRESULT OnMouseHoverMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnMouseLeaveMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnMouseMoveMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnMouseWheelMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnLButtonDownMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnRButtonDownMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnLButtonDoubleClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnRButtonDoubleClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnLButtonUpMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnRButtonUpMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnContextMenuMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    LRESULT OnIMEStartCompositionMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnIMEEndCompositionMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSetFocusMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnKillFocusMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnCharMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnKeyDownMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnKeyUpMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSysKeyDownMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSysKeyUpMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSetCusorMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnNotifyMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnCommandMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnSysCommandMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnHotKeyMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnCtlColorMsgs(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    LRESULT OnTouchMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
    LRESULT OnPointerMsgs(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

private:
    //���Ȱ�����Ϣ������
    void OnButtonDown(EventType eventType, WPARAM wParam, LPARAM lParam, const UiPoint& pt);

    //���ȵ�����Ϣ������
    void OnButtonUp(EventType eventType, WPARAM wParam, LPARAM lParam, const UiPoint& pt);

    //����ƶ���Ϣ������
    void OnMouseMove(WPARAM wParam, LPARAM lParam, const UiPoint& pt);

    /** ��������Ϣ������
    *  @param [in] wParam ������ת�ľ��룬��ֵ��ʾ������ǰ��ת��Զ���û�;��ֵ��ʾ����������û���ת��
    *  @param [in] lParam �������⴦�� 0��ʾ�ϸ���wParamָ���ľ������, ��0��ʾ���ճ����߼����������ת�ľ���
    *  @param [in] pt ������ڵ�����ֵ��Ϊ���ڿͻ�������
    */
    void OnMouseWheel(WPARAM wParam, LPARAM lParam, const UiPoint& pt);

    //��������̲���״̬
    void ClearStatus();

    /** �ж��Ƿ���Ҫ������������뿪��Ϣ
    * @param [in] pt ��굱ǰλ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ���� true ��Ҫ������������뿪��Ϣ������ false Ϊ����Ҫ
    */
    bool HandleMouseEnterLeave(const UiPoint& pt, WPARAM wParam, LPARAM lParam);

    /** @}*/

public:
    /** @name ���ڽ�����ؽӿ�
    * @{
    */
    /** ��ȡ��ǰ���н���Ŀؼ�
    */
    Control* GetFocus() const;

    /** ��ȡ��ǰ����¼��Ŀؼ�
    */
    Control* GetEventClick() const;

    /** ���ý��㵽ָ���ؼ���(���ô���Ϊ���㴰�ڣ������øÿؼ�Ϊ����ؼ�)
    * @param [in] pControl �ؼ�ָ��
    */
    void SetFocus(Control* pControl);

    /** �ÿؼ�ʧȥ���㣨��Ӱ�촰�ڽ��㣩
    */
    void KillFocus();

    /** ���õ�Ҫ�������괰�ھ��Ϊ��ǰ���ƴ���
    * @param [in]
    */
    void SetCapture();

    /** �����ڲ���Ҫ�������ʱ�ͷ���Դ
    */
    void ReleaseCapture();

    /** �жϵ�ǰ�Ƿ񲶻��������
    */
    bool IsCaptured() const;

    /** ��ȡ��ǰ������ĸ��ؼ���
    */
    Control* GetHoverControl() const;

    /** ��ȡ�����������
    */
    const UiPoint& GetLastMousePos() const;

    /** �л��ؼ����㵽��һ��������һ�����ؼ�
    * @param [in] bForward true Ϊ��һ���ؼ�������Ϊ false��Ĭ��Ϊ true
    */
    bool SetNextTabControl(bool bForward = true);

    /** @}*/

public:
    /** @name ������Ӱ���㴰��͸������ؽӿ�
    * @{
    */
    /** ���Ӵ�����Ӱ
    */
    virtual Box* AttachShadow(Box* pRoot);

    /** ���ô����Ƿ񸽼���ӰЧ��
    * @param [in] bShadowAttached Ϊ true ʱ���ӣ�false ʱ������
    */
    void SetShadowAttached(bool bShadowAttached);

    /** ��ȡ�Ƿ񸽼���ӰЧ��
    */
    bool IsShadowAttached() const;

    /** ��ǰ��ӰЧ��ֵ���Ƿ�ΪĬ��ֵ
    */
    bool IsUseDefaultShadowAttached() const;

    /** ���õ�ǰ��ӰЧ��ֵ���Ƿ�ΪĬ��ֵ
    */
    void SetUseDefaultShadowAttached(bool isDefault);

    /** ��ȡ��ӰͼƬ
    */
    const std::wstring& GetShadowImage() const;

    /** ���ô�����ӰͼƬ
    * @param [in] strImage ͼƬλ��
    */
    void SetShadowImage(const std::wstring& strImage);

    /** ��ȡ��Ӱ�ľŹ���������Ϣ
    */
    UiPadding GetShadowCorner() const;

    /** ָ����Ӱ�زĵľŹ�������
    * @param [in] padding �Ź���������Ϣ
    * @param [in] bNeedDpiScale Ϊ false ��ʾ����Ҫ�� rc ���� DPI �Զ�����
    */
    void SetShadowCorner(const UiPadding& padding, bool bNeedDpiScale = true);

    /** ���ô���͸����
    * @param [in] nAlpha ͸������ֵ[0, 255]
    */
    void SetWindowAlpha(int nAlpha);

    /** ��ȡ����͸����
    * @param [in] nAlpha ͸������ֵ[0, 255]
    */
    uint8_t GetWindowAlpha() const;

    /** �����Ƿ�Ϊ�㴰��
    */
    void SetLayeredWindow(bool bIsLayeredWindow);

    /** �Ƿ�Ϊ�㴰��
    */
    bool IsLayeredWindow() const;

    /** @}*/

public:
    /** @name ���ڻ�����ؽӿ�
    * @{
    */
    /** ���ÿؼ��Ƿ��Ѿ�����
    * @param [in] bArrange true Ϊ�Ѿ����У�����Ϊ false
    */
    void SetArrange(bool bArrange);

    /** �����ػ���Ϣ
    * @param [in] rcItem �ػ淶Χ
    */
    void Invalidate(const UiRect& rcItem);

    /** ��ȡ�������� DC
    */
    HDC GetPaintDC() const;

    /** ��ȡ���ƶ���
    */
    IRender* GetRender() const;

    /** ���ƺ�����
    */
    void Paint();

    /** �жϵ�ǰ�Ƿ���Ⱦ͸��ͼ��
    */
    bool IsRenderTransparent() const;

    /** ������Ⱦ͸��ͼ��
    * @param [in] bCanvasTransparent ���� true Ϊ��Ⱦ͸��ͼ�㣬����Ϊ false
    */
    bool SetRenderTransparent(bool bCanvasTransparent);

    /** ����ͼƬ����
    */
    void ClearImageCache();

    /** @} */

public:

    /**@name �ؼ�������ؽӿ�
    * @{
    */
    /** �����������ָ���ؼ�������Ĭ�����ԣ�UIFIND_VISIBLE | UIFIND_HITTEST | UIFIND_TOP_FIRST
    * @param [in] pt ָ������
    */
    Control* FindControl(const UiPoint& pt) const;

    /**
    *  ����������ҿ�����ӦWM_CONTEXTMENU�Ŀؼ�
    * @param [in] pt ָ������
    */
    Control* FindContextMenuControl(const UiPoint* pt) const;

    /** ���ҿ���֧���Ϸŵ�Box����
    * @param [in] pt ָ������
    * @param [in] nDropInId �Ϸŵ�IDֵ��ÿ���ؼ���������һ��ID���������Ϸţ�
    */
    Box* FindDroppableBox(const UiPoint& pt, uint8_t nDropInId) const;

    /** ���ݿؼ����Ʋ��ҿؼ�
    * @param [in] strName �ؼ�����
    */
    Control* FindControl(const std::wstring& strName) const;

    /** ������������ӿؼ�
    * @param [in] pParent Ҫ�����Ŀؼ�
    * @param [in] pt Ҫ���ҵ�����
    */
    Control* FindSubControlByPoint(Control* pParent, const UiPoint& pt) const;

    /** �������ֲ����ӿؼ�
    * @param [in] pParent Ҫ�����Ŀؼ�
    * @param [in] strName Ҫ���ҵ�����
    */
    Control* FindSubControlByName(Control* pParent, const std::wstring& strName) const;

    /** @} */

public:
    /** ��ȡ��ǰ���ڵĿͻ�������
    */
    void GetClientRect(UiRect& rcClient) const;

    /** ��ȡ��ǰ���ڵĴ���������
    */
    void GetWindowRect(UiRect& rcWindow) const;

    /** ����Ļ����ת��Ϊ��ǰ���ڵĿͻ�������
    */
    void ScreenToClient(UiPoint& pt) const;

    /** ����ǰ���ڵĿͻ�������ת��Ϊ��Ļ����
    */
    void ClientToScreen(UiPoint& pt) const;

    /** ��ȡ��ǰ�����������
    */
    void GetCursorPos(UiPoint& pt) const;

    /* ��rc�����Ͻ���������½�����������ڵ�ǰ���ڵ�����ռ�ת��Ϊ��������洰�ڵ�����ռ�
    */
    void MapWindowRect(UiRect& rc) const;

    /** ��ȡһ�����Ӧ�Ĵ��ڽӿ�
    */
    Window* WindowFromPoint(const UiPoint& pt);

    /** ��ȡ��ǰ����������ʾ���Ĺ��������Σ���������Ļ�����ʾ��
        ��ע�⣬�����ʾ����������ʾ������һЩ���ε���������Ǹ�ֵ��
    */
    bool GetMonitorWorkRect(UiRect& rcWork) const;

    /** ��ȡָ����������ʾ���Ĺ��������Σ���������Ļ�����ʾ��
        ��ע�⣬�����ʾ����������ʾ������һЩ���ε���������Ǹ�ֵ��
    */
    bool GetMonitorWorkRect(const UiPoint& pt, UiRect& rcWork) const;

    /** ע��һ���ϷŽӿ�
    */
    bool RegisterDragDrop(ControlDropTarget* pDropTarget);

    /** ע��һ���ϷŽӿ�
    */
    bool UnregisterDragDrop(ControlDropTarget* pDropTarget);

    /** ����ToolTip��Ϣ����ʱToolTip����Ϣ�Ѿ������仯��
    */
    void UpdateToolTip();

public:
    /** ����ϵͳ������ȼ���ע��󰴴��ȼ���ϵͳ�����Զ��������
    * @param [in] wVirtualKeyCode ��������룬���磺VK_DOWN�ȣ��ɲο���https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
    *             ���wVirtualKeyCodeΪ0����ʾȡ�������ڼ����ȼ�
    * @param [in] wModifiers �ȼ���ϼ���־λ���μ�HotKeyModifiersö�����͵�ֵ
    * @return ����ֵ˵��:
       -1: �������ɹ�;�ȼ���Ч��
        0: �������ɹ�;������Ч��
        1: �����ɹ�������û���������ھ�����ͬ���ȼ���
        2: �����ɹ�������һ�������Ѿ�����ͬ���ȼ���
    */
    int32_t SetWindowHotKey(uint8_t wVirtualKeyCode, uint8_t wModifiers);

    /** ��ȡϵͳ������ȼ�
    * @param [out] wVirtualKeyCode ��������룬���磺VK_DOWN��
    * @param [out] wModifiers �ȼ���ϼ���־λ���μ�HotKeyModifiersö�����͵�ֵ
    * @return �������false��ʾû��ע�ᴰ�ڼ����ȼ��������ʾ��ע�ᴰ�ڼ����ȼ�
    */
    bool GetWindowHotKey(uint8_t& wVirtualKeyCode, uint8_t& wModifiers) const;

    /** ע��ϵͳȫ���ȼ���ע��ɹ��󣬰����ȼ��󣬸ô��ڻ��յ�WM_HOTKEY��Ϣ
    * @param [in] wVirtualKeyCode ��������룬���磺VK_DOWN��
    * @param [in] wModifiers �ȼ���ϼ���־λ���μ�HotKeyModifiersö�����͵�ֵ
    * @param [in] id ����ID��Ӧ�ó��������0x0000��0xBFFF�ķ�Χ��ָ�� ID ֵ�� 
                  Ϊ�˱������������� DLL ������ȼ���ʶ����ͻ��DLL Ӧʹ�� GlobalAddAtom ������ȡ�ȼ���ʶ����
    */
    bool RegisterHotKey(uint8_t wVirtualKeyCode, uint8_t wModifiers, int32_t id);

    /** ע��ϵͳȫ���ȼ�
    * @param [in] id ����ID����ע��ʱʹ�õ�����ID 
    */
    bool UnregisterHotKey(int32_t id);

private:
    /**@name ����Ч����ؽӿ�
    * @{
    */
    /** ���û���ƫ��
    * @param [in] renderOffset ƫ��ֵ
    */
    void SetRenderOffset(UiPoint renderOffset);

    /** ���û���ƫ�� x ����
    * @param [in] renderOffsetX ����ֵ
    */
    void SetRenderOffsetX(int renderOffsetX);

    /** ���û���ƫ�� y ����
    * @param [in] renderOffsetY ����ֵ
    */
    void SetRenderOffsetY(int renderOffsetY);

    /** @} */

private:
    /** ����Ļ����ת��Ϊָ�����ڵĿͻ�������
    */
    void ScreenToClient(HWND hWnd, UiPoint& pt) const;

    /** ��ָ�����ڵĿͻ�������ת��Ϊ��Ļ����
    */
    void ClientToScreen(HWND hWnd, UiPoint& pt) const;

    /** ��ȡָ�����ڵĿͻ�������
    */
    void GetClientRect(HWND hWnd, UiRect& rcClient) const;

    /** ��ȡָ�����ڵĴ���������
    */
    void GetWindowRect(HWND hWnd, UiRect& rcWindow) const;

    /** ��ȡָ������������ʾ���Ĺ��������Σ���������Ļ�����ʾ��
        ��ע�⣬�����ʾ����������ʾ������һЩ���ε���������Ǹ�ֵ��
    */
    bool GetMonitorWorkRect(HWND hWnd, UiRect& rcWork) const;

    /** ��ȡָ������������ʾ������ʾ�����κ͹���������
    */
    bool GetMonitorRect(HWND hWnd, UiRect& rcMonitor, UiRect& rcWork) const;

    /** �滻���ں���
    */
    WNDPROC SubclassWindow(HWND hWnd, WNDPROC pfnWndProc) const;

    /** ��ȡ��ǰ����Owner���ھ��
    */
    HWND GetWindowOwner() const;

    /* ��rc�����Ͻ���������½������������һ�����ڵ�����ռ�ת��Ϊ�������һ�����ڵ�����ռ�
    */
    void MapWindowRect(HWND hwndFrom, HWND hwndTo, UiRect& rc) const;

    /** ����root�Զ��������ڴ�С
    */
    void AutoResizeWindow(bool bRepaint);

    /** �Կؼ����в��ֵ���
    */
    void ArrangeRoot();

private:
    /** ��鲢ȷ����ǰ����Ϊ���㴰��
    */
    void CheckSetFocusWindow();

    /** ע�ᴰ����
    */
    bool RegisterWindowClass();

    /** ע��ؼ������ࣨ�봰�ڵĹ��̺�����ͬ��
    */
    bool RegisterSuperClass();

    /** ���ڹ��̺���(��GetSuperClassName()�������ز�Ϊ�մ�ʱʹ��)
    * @param [in] hWnd ���ھ��
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ������Ϣ������
    */
    static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /** ���ڹ��̺���(��GetSuperClassName()�������ؿմ�ʱʹ��) 
    * @param [in] hWnd ���ھ��
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @return ������Ϣ������
    */
    static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /** ��ȡ���ڶ�Ӧ��Window����ӿ�
    * @param [in] hWnd ���ھ��
    * @return ���ش��ھ����Ӧ��Window����ӿ�
    */
    static Window* GetWindowObject(HWND hWnd);

private:
    //���ھ��
    HWND m_hWnd;

    //ԭ���Ĵ��ڹ��̺���
    WNDPROC m_OldWndProc;

    //�Ƿ����໯��Subclass������
    bool m_bSubclassed;

    //�¼��ص�������
    EventMap m_OnEvent;

private:
    //���ڵĳ�ʼ����С
    UiSize m_szInitWindowSize;

    //������С��Ϣ
    UiSize m_szMinWindow;

    //���������Ϣ
    UiSize m_szMaxWindow;

    //���������Ϣ
    UiRect m_rcMaximizeInfo;

    //�����ı߿����췶Χ��Ϣ
    UiRect m_rcSizeBox;

    //͸��ͨ���޲���Χ�ĵľŹ�������
    UiRect m_rcAlphaFix;

    //����Բ����Ϣ
    UiSize m_szRoundCorner;

    //������������Ϣ
    UiRect m_rcCaption;

    //�����Ƿ�仯������仯(true)����Ҫ���¼��㲼��
    bool m_bIsArranged;

    //�����Ƿ���Ҫ��ʼ��
    bool m_bFirstLayout;

    //�Ƿ�ʹ��ϵͳ�ı�����
    bool m_bUseSystemCaption;

private:
    //����DC
    HDC m_hDcPaint;

    //�Ƿ�Ϊ�㴰��
    bool m_bIsLayeredWindow;

    //����͸����(����ʹ�ò㴰��ʱ��Ч)
    uint8_t m_nWindowAlpha;

    //����ʱ��ƫ�����������ã�
    UiPoint m_renderOffset;

    //��������
    std::unique_ptr<IRender> m_render;

private:

    //��������
    std::unique_ptr<ToolTip> m_toolTip;

    //����ؼ�
    Control* m_pFocus;

    //�������ͣ�ؼ�
    Control* m_pEventHover;

    /** ����Ŀؼ���
        �� WM_LBUTTONDOWN/WM_RBUTTONDOWN/WM_LBUTTONDBLCLK ��ֵ
        �� WM_LBUTTONUP��/WM_KILLFOCUS ���
    */
    Control* m_pEventClick;

    /** ���̰��µĿؼ�
    *   �� WM_KEYDOWN / WM_SYSKEYDOWN ��ֵ
    *   �� WM_KEYUP / WM_SYSKEYUP���
    */
    Control* m_pEventKey;

    //�������λ��
    UiPoint m_ptLastMousePos;

    //����¼��Ĳ���״̬
    bool m_bMouseCapture;

private:
    //ÿ�����ڵ���Դ·��(�������Դ��Ŀ¼��·��)
    std::wstring m_strResourcePath;

    //����������class����������ӳ���ϵ
    std::map<std::wstring, std::wstring> m_defaultAttrHash;

    //������ɫ�ַ�������ɫֵ��ARGB����ӳ���ϵ
    ColorMap m_colorMap;

    //�ô�����ÿ��Option group�µĿؼ�������ѡ�ؼ��Ƿ���ģ�
    std::map<std::wstring, std::vector<Control*>> m_mOptionGroup;

    //�ô�����Ϣ�������б�
    std::vector<IUIMessageFilter*> m_aMessageFilters;

    //�ӳ��ͷŵĿؼ��ӿ�
    std::vector<Control*> m_aDelayedCleanup;

    //�첽�رմ��ڻص�������Դ��Ч�Ա�־
    nbase::WeakCallbackFlag m_closeFlag;

    //������Ӱ
    std::unique_ptr<Shadow> m_shadow;

    //��ǰ�����Ƿ���ʾΪģ̬�Ի���
    bool m_bFakeModal;

    //�����Ѿ��ӳٹرգ�add by djj 20200428 ����Closeʱ���ӳ�Post WM_CLOSE, ����ڼ���Ҫ��һ����ʶ����'���ر�״̬'
    bool m_bCloseing;

private:
    /**@name ȫ�����״̬
    * @{

    /** �����Ƿ�Ϊȫ��״̬
    */
    bool m_bFullScreen;

    /** ȫ��ǰ�Ĵ��ڷ��
    */
    DWORD m_dwLastStyle;

    /** ȫ��ǰ�Ĵ���λ��/���ڴ�С����Ϣ
    */
    WINDOWPLACEMENT m_rcLastWindowPlacement;

    /** @} */

private:
    /** �ؼ����Ҹ�����
    */
    ControlFinder m_controlFinder;

    /** ���ڹ��������������ڵ�
    */
    Box* m_pRoot;

    /** ���ڵ��ϷŲ�������ӿ�
    */
    WindowDropTarget* m_pWindowDropTarget;

    /** ϵͳȫ���ȼ���ID
    */
    std::vector<int32_t> m_hotKeyIds;
};

} // namespace ui

#endif // UI_CORE_WINDOW_H_
