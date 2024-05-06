#ifndef UI_CONTROL_MENU_H_
#define UI_CONTROL_MENU_H_

#pragma once

#include "duilib/duilib_defs.h"
#include "duilib/Utils/WinImplBase.h"
#include "duilib/Box/ListBox.h"

namespace ui {

//�˵����뷽ʽ
enum MenuAlignment
{
	eMenuAlignment_Left			= 1 << 1,
	eMenuAlignment_Top			= 1 << 2,
	eMenuAlignment_Right		= 1 << 3,
	eMenuAlignment_Bottom		= 1 << 4,
	eMenuAlignment_Intelligent	= 1 << 5    //���ܵķ�ֹ���ڱ�
};

//�˵��ر�����
enum class MenuCloseType
{
	eMenuCloseThis,  //�����ڹرյ�ǰ����Ĳ˵����ڣ����������ʱ
	eMenuCloseAll     //�ر����в˵����ڣ���ʧȥ����ʱ
};

//�˵�����λ�õ�����
enum class MenuPopupPosType
{					    //�������point���ڲ˵����ĸ�λ��    1.-----.2       1���� 2����              
												   //     |     |
	//����ٶ��û���ϲ�����ܵ�                                3.-----.4       3���� 4����
	RIGHT_BOTTOM	= eMenuAlignment_Right | eMenuAlignment_Bottom | eMenuAlignment_Intelligent,
	RIGHT_TOP		= eMenuAlignment_Right | eMenuAlignment_Top    | eMenuAlignment_Intelligent,
	LEFT_BOTTOM		= eMenuAlignment_Left  | eMenuAlignment_Bottom | eMenuAlignment_Intelligent,
	LEFT_TOP		= eMenuAlignment_Left  | eMenuAlignment_Top    | eMenuAlignment_Intelligent,
	//������normal�������ܵ�
	RIGHT_BOTTOM_N	= eMenuAlignment_Right | eMenuAlignment_Bottom,
	RIGHT_TOP_N		= eMenuAlignment_Right | eMenuAlignment_Top,
	LEFT_BOTTOM_N	= eMenuAlignment_Left  | eMenuAlignment_Bottom,
	LEFT_TOP_N		= eMenuAlignment_Left  | eMenuAlignment_Top
};

#include "observer_impl_base.hpp"
struct ContextMenuParam
{
	MenuCloseType wParam;
	HWND hWnd;
};

typedef class ObserverImpl<BOOL, ContextMenuParam> ContextMenuObserver;
typedef class ReceiverImpl<BOOL, ContextMenuParam> ContextMenuReceiver;

/////////////////////////////////////////////////////////////////////////////////////
//

/** �˵���
*/
class CMenuElementUI;
class CMenuWnd : public ui::WindowImplBase, public ContextMenuReceiver
{
public:
	/** ���캯������ʼ���˵��ĸ����ھ��
	*/
	explicit CMenuWnd(HWND hParent);

	/** ������Դ���ص��ļ������ƣ����û���ã��ڲ�Ĭ��Ϊ "menu"
	*   XML�ļ��е���Դ��ͼƬ��XML�ȣ�����������ļ����в���
	*/
	void SetSkinFolder(const std::wstring& skinFolder);

	/** ���ö༶�Ӳ˵���XMLģ���ļ�������
	@param [in] submenuXml �Ӳ˵���XMLģ���ļ��������û���ã��ڲ�Ĭ��Ϊ "submenu.xml"
	@param [in] submenuNodeName �Ӳ˵�XML�ļ��У��Ӳ˵������λ�õĽڵ����ƣ����û���ã��ڲ�Ĭ��Ϊ "submenu"
	*/
	void SetSubMenuXml(const std::wstring& submenuXml, const std::wstring& submenuNodeName);

	/** ��ʼ���˵����ã�������ʾ�˵�
	*   ���غ󣬿���ͨ��FindControl�������ҵ��˵�����к�������
	* @param [in] xml �˵�XML��Դ�ļ������ڲ�����GetSkinFolder()ƴ�ӳ�����·��
	* @param [in] point �˵�����λ��
	* @param [in] popupPosType �˵�����λ������
	* @param [in] noFocus �˵������󣬲�����ڣ�����������
	* @Param [in] pOwner ���˵��Ľӿڣ�������ֵ����nullptr��������˵��Ƕ༶�˵�ģʽ
	*/
	void ShowMenu(const std::wstring& xml, 
		          const UiPoint& point,
		          MenuPopupPosType popupPosType = MenuPopupPosType::LEFT_TOP, 
		          bool noFocus = false,
		          CMenuElementUI* pOwner = nullptr);

	/** �رղ˵�
	*/
	void CloseMenu();

public:
	//����Ӳ˵���
	bool AddMenuItem(CMenuElementUI* pMenuItem);
	bool AddMenuItemAt(CMenuElementUI* pMenuItem, size_t iIndex);

	//ɾ���˵���
	bool RemoveMenuItem(CMenuElementUI* pMenuItem);
	bool RemoveMenuItemAt(size_t iIndex);

	//��ȡ�˵������
	size_t GetMenuItemCount() const;

	//��ȡ�˵���ӿ�
	CMenuElementUI* GetMenuItemAt(size_t iIndex) const;
	CMenuElementUI* GetMenuItemByName(const std::wstring& name) const;

private:
	friend CMenuElementUI; //��Ҫ���ʲ���˽�г�Ա����

	//��ȡȫ�ֲ˵�Observer����
	static ContextMenuObserver& GetMenuObserver();

	//�븸�˵�����Ӵ�������ϵ
	void DetachOwner();		//add by djj 20200506

private:
	// ���µ����˵��Ĵ�С
	void ResizeMenu();

	// ���µ����Ӳ˵��Ĵ�С
	void ResizeSubMenu();

private:

	virtual BOOL Receive(ContextMenuParam param) override;

	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual void OnInitWindow() override;
	virtual void OnFinalMessage(HWND hWnd) override;
	virtual LRESULT OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

private:
	//�˵������ھ��
	HWND m_hParent;

	//�˵�����λ��
	UiPoint m_menuPoint;

	//�˵�����λ�õ�����
	MenuPopupPosType m_popupPosType;

	//��Դ���ص��ļ�������
	UiString m_skinFolder;

	//�Ӳ˵���XMLģ���ļ���
	UiString m_submenuXml;

	//�Ӳ˵�XML�ļ��У��Ӳ˵������λ�õĽڵ�����
	UiString m_submenuNodeName;

	//�˵���Դ��xml�ļ���
	UiString m_xml;

	//�˵�����ʱ���Ƿ�Ϊ�޾۽�ģʽ
	bool m_noFocus;

	//�˵��ĸ��˵��ӿ�
	CMenuElementUI* m_pOwner;

	//�˵��Ĳ��ֽӿ�
	ui::ListBox* m_pLayout;
};

/** �˵���
*/
class CMenuElementUI : public ui::ListBoxItem
{
public:
	CMenuElementUI();

	//����Ӳ˵���
	bool AddSubMenuItem(CMenuElementUI* pMenuItem);
	bool AddSubMenuItemAt(CMenuElementUI* pMenuItem, size_t iIndex);

	//ɾ���Ӳ˵���
	bool RemoveSubMenuItem(CMenuElementUI* pMenuItem);
	bool RemoveSubMenuItemAt(size_t iIndex);
	void RemoveAllSubMenuItem();

	//��ȡ�Ӳ˵������
	size_t GetSubMenuItemCount() const;

	//��ȡ�Ӳ˵���ӿ�
	CMenuElementUI* GetSubMenuItemAt(size_t iIndex) const;
	CMenuElementUI* GetSubMenuItemByName(const std::wstring& name) const;


private:
	//��ȡһ���˵����������Ӳ˵���Ľӿ�(�������˵�����Ԫ��)
	static void GetAllSubMenuItem(const CMenuElementUI* pParentElementUI, 
						          std::vector<CMenuElementUI*>& submenuItems);

	//��ȡһ���˵����������Ӳ˵��ؼ��Ľӿ�(�����˵�����Ԫ�غ������ؼ�)
	static void GetAllSubMenuControls(const CMenuElementUI* pParentElementUI,
						              std::vector<Control*>& submenuControls);

private:
	virtual bool ButtonUp(const ui::EventArgs& msg) override;
	virtual bool MouseEnter(const ui::EventArgs& msg) override;
	virtual void PaintChild(ui::IRender* pRender, const ui::UiRect& rcPaint) override;

private:
	friend CMenuWnd; //��Ҫ���ʲ���˽�г�Ա����

	//����Ӳ˵���������¼��˵����򴴽��¼��˵����ڣ�����ʾ
	bool CheckSubMenuItem();

	//�����¼��˵����ڣ�����ʾ
	void CreateMenuWnd();

private:
	//�¼��˵����ڽӿ�
	CMenuWnd* m_pSubWindow;
};

} // namespace ui

#endif // UI_CONTROL_MENU_H_
