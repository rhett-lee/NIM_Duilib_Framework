#ifndef UI_UTILS_WINIMPLBASE_H_
#define UI_UTILS_WINIMPLBASE_H_

#pragma once

#include "duilib/duilib_defs.h"
#include "duilib/Core/Window.h"

namespace ui
{

#define UI_WNDSTYLE_FRAME		(WS_VISIBLE | WS_OVERLAPPEDWINDOW)
#define UI_WNDSTYLE_DIALOG		(WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

#define UI_CLASSSTYLE_FRAME		(CS_VREDRAW | CS_HREDRAW)
#define UI_CLASSSTYLE_DIALOG	(CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)

/** ʵ��һ�����б������Ĵ��壬������󻯡���С������ԭ��ť��֧��
* ��ʵ��֧�ִ�����Ӱ�������ṩ���� WS_EX_LAYERED ���Դ�����Ӱ��
* ����ʵ�֣���װ��2�ִ���ģʽ��
* ��1������ģʽ����������Ӱ�Ĵ��ڣ�����ͨ��XML�����ļ�<Window>�������ã���������
*              shadow_attached="false" layered_window="false" ������Ҫ����alpha���ԣ���֧��alpha����;
*              �������õ�ͬ�ڣ�layered_window="false"��������shadow_attached����
* ��2��������Ӱ����ģʽ����Ҫʹ�ò㴰��(����WS_EX_LAYERED����)������ͨ��XML�����ļ�<Window>�������ã���������
*              shadow_attached="true" layered_window="true" ��alphaΪ��ѡ�����ô���͸���ȣ����������Ĭ��Ϊ255��
*              �������õ�ͬ�ڣ�layered_window="true"��������shadow_attached����
*/
class UILIB_API WindowImplBase : public Window
{
public:
    WindowImplBase();

protected:
    //���������������ⲿ���ã�����OnFinalMessage�����У���delete this����
    virtual ~WindowImplBase();

public:
    /**  ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ��Ŀ¼
    * @return ������ʵ�ֲ����ش���Ƥ��Ŀ¼
    */
    virtual std::wstring GetSkinFolder() = 0;

    /**  ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ�� XML �����ļ�
    * @return ������ʵ�ֲ����ش���Ƥ�� XML �����ļ�
    *         ���ص����ݣ�������XML�ļ����ݣ����ַ�'<'Ϊ��ʼ���ַ�������
    *         �������ļ�·����������'<'�ַ���ʼ���ַ��������ļ�Ҫ��GetSkinFolder()·�����ܹ��ҵ�
    */
    virtual std::wstring GetSkinFile() = 0;

    /** ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ��������
    * @return ������ʵ�ֲ����ش���Ψһ��������
    */
    virtual std::wstring GetWindowClassName() const override = 0;

    /** ��ȡ������ʽ
    * @return Ĭ�Ϸ��ص�ǰ���ڵ���ʽȥ��WS_CAPTION����
    *         ���������д�ú����󣬷���ֵΪ0���򲻸ı䵱ǰ���ڵ���ʽ
    */
    virtual UINT GetStyle() const;

public:

    /** ��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú���
    * @param [in] strClass �ؼ�����
    * @return ����һ���Զ���ؼ�ָ�룬һ������¸��� strClass ���������Զ���Ŀؼ�
    */
    virtual Control* CreateControl(const std::wstring& strClass);

protected:
    /** �����յ����ڴ�����Ϣʱ�����ã�����������һЩ��ʼ���Ĺ���
     */
    virtual void OnInitWindow() override;

    /** ������Ϣ���ɷ�����, ����̳иú�������д�����У���Ҫ���û���ĺ���
    * @param [in] uMsg ��Ϣ��
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ��Ϣ�Ƿ��Ѿ�����
                ���� true  �����Ѿ��ɹ�������Ϣ������Ҫ�ٴ��ݸ����ڹ��̣�
                ���� false ��ʾ����Ϣ�������ݸ����ڹ��̴���
    * @return ������Ϣ�Ĵ�����
    */
    virtual LRESULT OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

    /** �յ����ڴ�����Ϣ��WM_CREATE��ʱ�����ã���ʹ�� OnInitWindow �ӿ���ʵ���Զ�������
    * @param [in] uMsg ��ϢID
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ��Ϣ�Ƿ��Ѿ�������
    * @return ������Ϣ������
    */
    virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** �ڴ����յ� WM_NCDESTROY ��Ϣʱ�ᱻ����
    * @param [in] hWnd Ҫ���ٵĴ��ھ��
    */
    virtual void OnFinalMessage(HWND hWnd) override;

    /** ���մ��ڿ���������Ϣʱ��WM_SYSCOMMAND��������
    *  @param [in] uMsg ��Ϣ����
    *  @param [in] wParam ��Ϣ���Ӳ���
    *  @param [in] lParam ��Ϣ���Ӳ���
    *  @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    *  @return ������Ϣ������
    */
    virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    /** ���յ����ڹر���Ϣ(WM_CLOSE)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ����ڱ�������Ϣ(WM_DESTROY)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�����ƶ���Ϣ(WM_MOUSEMOVE)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** �����յ�(WM_MOUSEWHEEL)��Ϣʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** �����յ�(WM_MOUSEHOVER)��Ϣʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������������Ϣ(WM_LBUTTONDOWN)ʱ������
    *  @param [in] uMsg ��Ϣ����
    *  @param [in] wParam ��Ϣ���Ӳ���
    *  @param [in] lParam ��Ϣ���Ӳ���
    *  @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    *  @return ������Ϣ������
    */
    virtual LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������������Ϣ(WM_LBUTTONUP)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������˫����Ϣ(WM_LBUTTONDBLCLK)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnLButtonDbClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������������Ϣ(WM_RBUTTONDOWN)ʱ������
    *  @param [in] uMsg ��Ϣ����
    *  @param [in] wParam ��Ϣ���Ӳ���
    *  @param [in] lParam ��Ϣ���Ӳ���
    *  @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    *  @return ������Ϣ������
    */
    virtual LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������������Ϣ(WM_RBUTTONUP)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���յ�������˫����Ϣ(WM_RBUTTONDBLCLK)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnRButtonDbClk(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** �����յ��ַ�������Ϣʱ��WM_CHAR��������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���ռ��̰���������Ϣ(WM_KEYDOWN)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���ռ��̰���������Ϣ(WM_KEYUP)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���ռ��̰���������Ϣ(WM_SYSKEYDOWN)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param[out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnSysKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���ռ��̰���������Ϣ(WM_SYSKEYUP)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param [out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnSysKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

    /** ���ռ��̰���������Ϣ(WM_HOTKEY)ʱ������
    * @param [in] uMsg ��Ϣ����
    * @param [in] wParam ��Ϣ���Ӳ���
    * @param [in] lParam ��Ϣ���Ӳ���
    * @param [out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
    * @return ������Ϣ������
    */
    virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    /** ����ȫ��״̬
    */
    virtual void OnWindowEnterFullScreen() override;

    /** �˳�ȫ��״̬
    */
    virtual void OnWindowExitFullScreen() override;

    /** �������״̬
    */
    virtual void OnWindowMaximized() override;

    /** ����󻯻�ԭ
    */
    virtual void OnWindowRestored() override;

    /** ������С��״̬
    */
    virtual void OnWindowMinimized() override;

    /** �л�ϵͳ���������Ի������
    */
    virtual void OnUseSystemCaptionBarChanged() override;

private:
    /** ���ڹ��ܰ�ť�����ʱ����
    * @param [in] param Я���Ĳ���
    * @return ʼ�շ��� true
    */
    bool OnButtonClick(const EventArgs& param);

    /** �������/��ԭ��ť��״̬
    */
    void ProcessMaxRestoreStatus();
};
}

#endif // UI_UTILS_WINIMPLBASE_H_
