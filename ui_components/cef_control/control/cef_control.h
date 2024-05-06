/** @file cef_control.h
 * @brief ��װCef���������Ϊduilib�ؼ�
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2016/7/19
 */
#pragma once
#include "ui_components/cef_control/control/cef_control_base.h"
#include "ui_components/cef_control/util/memory_dc.h"
#include "duilib/Core/Window.h"

namespace nim_comp {

class CefControl :public CefControlBase, public ui::IUIMessageFilter
{	
public:
	CefControl(void);
	~CefControl(void);	

	/// ��д����ӿڣ��ṩ���Ի�����
	virtual void Init() override;
	virtual void SetPos(ui::UiRect rc) override;
	virtual void HandleEvent(const ui::EventArgs& msg) override;
	virtual void SetVisible(bool bVisible) override;
	virtual void Paint(ui::IRender* pRender, const ui::UiRect& rcPaint) override;
	virtual void SetWindow(ui::Window* pManager) override;

	virtual LRESULT FilterMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override; // ��������Ϣ��ת����Cef���������

	/**
	* @brief �򿪿����߹���
	* @param[in] view һ�� CefControl �ؼ�ʵ��(����CefControl������Ҫ����)
	* @return �ɹ����� true��ʧ�ܷ��� false
	*/
	virtual bool AttachDevTools(Control* view) override;

	/**
	* @brief �رտ����߹���
	* @return ��
	*/
	virtual void DettachDevTools() override;

protected:
	virtual void ReCreateBrowser() override;

	// �ڷ�UI�߳��б�����
	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) override;

protected:
	/**
	 * @brief ת����갴����Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendButtonDownEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת�����˫����Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendButtonDoubleDownEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת����굯����Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendButtonUpEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת������ƶ���Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendMouseMoveEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת����������Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendMouseWheelEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת������뿪��Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendMouseLeaveEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת�����������Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

	/**
	 * @brief ת�����񽹵���Ϣ�� BrowserHost
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ��Ϣ���Ӳ���
	 * @param[in] lParam ��Ϣ���Ӳ���
	 * @param[out] bHandled �Ƿ����������Ϣ
	 * @return ������Ϣ������
	 */
	LRESULT SendCaptureLostEvent(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	
	/**
	 * @brief �ж��Ƿ��а�������
	 * @param[in] wparam ��Ϣ���Ӳ���
	 * @return ���� true ��ʾ�а������£�false ��ʾû�а�������
	 */
	static bool IsKeyDown(WPARAM wparam);

	/**
	 * @brief ת����ͨ������Ϣ�� CEF ��ʶ��ļ�����Ϣ
	 * @param[in] wparam ��Ϣ���Ӳ���
	 * @param[in] lparam ��Ϣ���Ӳ���
	 * @return ����ת����Ľ��
	 */
	static int GetCefKeyboardModifiers(WPARAM wparam, LPARAM lparam);

	/**
	 * @brief ת����ͨ�����Ϣ�� CEF ��ʶ��������Ϣ
	 * @param[in] wparam ��Ϣ���Ӳ���
	 * @return ����ת����Ľ��
	 */
	static int GetCefMouseModifiers(WPARAM wparam);

private:
	// ���������Ⱦ���ݱ仯ʱ���ᴥ���˽ӿڣ���ʱ����Ⱦ���ݱ��浽�ڴ�dc
	// ����֪ͨ����ˢ�¿ؼ����ڿؼ���Paint��������ڴ�dc��λͼ����������
	// �ɴ�ʵ��������Ⱦ���ݻ���������
	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		CefRenderHandler::PaintElementType type,
		const CefRenderHandler::RectList& dirtyRects,
		const std::string* buffer,
		int width,
		int height) OVERRIDE;

	virtual void ClientToControl(POINT &pt) OVERRIDE;

	virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) OVERRIDE;

	virtual void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect) OVERRIDE;

	//����DPI����Ӧ��������Ⱦģʽ������ģʽ��ͬ��
	void AdaptDpiScale(CefMouseEvent& mouse_event);

private:
	MemoryDC			dc_cef_;		// �ڴ�dc,��cef������Ⱦ�����ݱ��浽dc��
	MemoryDC			dc_cef_popup_;	// �ڴ�dc,��cef��popup���ڵ�������Ⱦ���ݱ��浽dc��
	CefRect				rect_popup_;	// ����ҳ����Ͽ�һ��Ŀؼ�����ʱ����¼������λ��
	CefControl*         devtool_view_;  //�����߹��߶�Ӧ�Ŀؼ�
};

}