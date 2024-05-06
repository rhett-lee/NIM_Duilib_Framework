#ifndef UI_CONTROL_TABCTRL_H_
#define UI_CONTROL_TABCTRL_H_

#pragma once

#include "duilib/Box/ListBox.h"
#include "duilib/Core/ControlDragable.h"

namespace ui
{
/** ���ǩ�ؼ�������������Ķ��ǩ��
*/
class TabBox;
class TabCtrl: public ListBox
{
public:
	TabCtrl();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
	/** ���ð󶨵�TabBox�ؼ�����
	*/
	void SetTabBoxName(const std::wstring& tabBoxName);

	/** ��ȡ�󶨵�TabBox�ؼ�����
	*/
	std::wstring GetTabBoxName() const;

	/** ���ð󶨵�TabBox�ӿ�
	*/
	void SetTabBox(TabBox* pTabBox);

	/** ��ȡ�󶨵�TabBox�ӿ�
	*/
	TabBox* GetTabBox() const;

public:
	/** ���������λ������
	 * @param [in] pControl ����ָ��
	 * @param [in] iIndex �����ţ���Χ�ǣ�[0, GetItemCount())
	 */
	virtual bool SetItemIndex(Control* pControl, size_t iIndex) override;

	/** ׷��һ�����ĩβ
	 * @param [in] pControl ����ָ��
	 */
	virtual bool AddItem(Control* pControl) override;

	/** ��ָ��λ��֮�����һ������
	 * @param [in] pControl ����ָ��
	 * @param[in] iIndex Ҫ�����λ����������Χ�ǣ�[0, GetItemCount())
	 */
	virtual bool AddItemAt(Control* pControl, size_t  iIndex) override;

	/** ��������ָ��
	 * @param [in] pControl ����ָ��
	 */
	virtual bool RemoveItem(Control* pControl) override;

	/** ���������Ƴ�һ������
	 * @param [in] iIndex ������������Χ�ǣ�[0, GetItemCount())
	 */
	virtual bool RemoveItemAt(size_t iIndex) override;

	/** �Ƴ���������
	 */
	virtual void RemoveAllItems() override;

protected:
	/** ��ʼ���ӿ�
	*/
	virtual void OnInit() override;

	/** ��Ϣ������
	* @param [in] msg ��Ϣ����
	*/
	virtual void HandleEvent(const EventArgs& msg) override;

private:
	/** Ĭ��ѡ�������
	*/
	size_t m_nSelectedId;

	/** �󶨵�TabBox����
	*/
	UiString m_tabBoxName;

	/** �󶨵�TabBox�ӿ�
	*/
	TabBox* m_pTabBox;
};

/** ���ǩ�ؼ���һ����ǩҳ
*/
class TabCtrlItem : public ControlDragableT<ListBoxItemH>
{
public:
	TabCtrlItem();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void SetVisible(bool bVisible) override;
	virtual std::wstring GetToolTipText() const override;

public:
	/** ����ͼ��
	* @param [in] iconImageString ͼ����Դ�ַ���
	*/
	void SetIcon(const std::wstring& iconImageString);

	/** ��ȡͼ��
	* @return ����ͼ����Դ�ַ���
	*/
	std::wstring GetIcon() const;

	/** ������������
	*/
	void SetTitle(const std::wstring& title);

	/** ��ȡ��������
	*/
	std::wstring GetTitle() const;

public:
	/** ���ð󶨵�TabBox����������
	*/
	void SetTabBoxItemIndex(size_t nTabBoxItemIndex);

	/** ��ȡ�󶨵�TabBox����ID������
	*/
	size_t GetTabBoxItemIndex() const;

public:
	/** ��ȡͼ��ؼ�
	*/
	Control* GetIconControl() const { return m_pIcon; }

	/** ��ȡ�ı��ؼ�
	*/
	Label* GetTextLabel() const { return m_pLabel; }

	/** ��ȡ�رհ�ť
	*/
	Button* GetCloseButton() const { return m_pCloseBtn; }

public:
	/** ͼ��ؼ���Class
	*/
	void SetIconClass(const std::wstring& iconClass);
	std::wstring GetIconClass() const;

	/** �ı��ؼ���Class
	*/
	void SetTitleClass(const std::wstring& titleClass);
	std::wstring GetTitleClass() const;

	/** �رհ�ť�ؼ���Class
	*/
	void SetCloseButtonClass(const std::wstring& closeButtonClass);
	std::wstring GetCloseButtonClass() const;

	/** �ָ��߿ؼ���Class
	*/
	void SetLineClass(const std::wstring& lineClass);
	std::wstring GetLineClass() const;

public:
	/** ����ѡ��״̬�ı�ǩԲ�Ǵ�С
	* @param [in] szCorner Բ�ǵĿ�Ⱥ͸߶�
	* @param [in] bNeedDpiScale �Ƿ���� DPI ����Ӧ��Ĭ��Ϊ true
	*/
	void SetSelectedRoundCorner(UiSize szCorner, bool bNeedDpiScale);

	/** ��ȡѡ��״̬�ı�ǩԲ�Ǵ�С
	*/
	UiSize GetSelectedRoundCorner() const;

	/** ������ͣ״̬�ı�ǩԲ�Ǵ�С
	* @param [in] szCorner Բ�ǵĿ�Ⱥ͸߶�
	* @param [in] bNeedDpiScale �Ƿ���� DPI ����Ӧ��Ĭ��Ϊ true
	*/
	void SetHotRoundCorner(UiSize szCorner, bool bNeedDpiScale);

	/** ��ȡ��ͣ״̬�ı�ǩԲ�Ǵ�С
	*/
	UiSize GetHotRoundCorner() const;

	/** ����Hot״̬�ı���ɫ���ڱ߾�
	* @param [in] rcPadding �ڱ߾�����
	* @param [in] bNeedDpiScale �Ƿ���� DPI ����Ӧ��Ĭ��Ϊ true
	*/
	void SetHotPadding(UiPadding rcPadding, bool bNeedDpiScale);

	/** ��ȡHot״̬�ı���ɫ���ڱ߾�
	*/
	UiPadding GetHotPadding() const;

	/** ���ùرհ�ť�Ƿ��Զ�����
	* @param [in] bAutoHideCloseBtn true��ʾ�Զ����عرհ�ť��false��ʾ�رհ�ťʼ����ʾ
	*/
	void SetAutoHideCloseButton(bool bAutoHideCloseBtn);

	/** ��ȡ�رհ�ť�Ƿ��Զ�����
	*/
	bool IsAutoHideCloseButton() const;

	/** ����ָ��ߵ���ʾ��������
	*/
	void AdjustItemLineStatus();

protected:
	/** ��ʼ���ӿ�
	*/
	virtual void OnInit() override;

	/** ��Ϣ������
	* @param [in] msg ��Ϣ����
	*/
	virtual void HandleEvent(const EventArgs& msg) override;

	/** �������������Ϣ
	*/
	virtual bool MouseEnter(const EventArgs& msg) override;

	/** ��������Ƴ���Ϣ
	*/
	virtual bool MouseLeave(const EventArgs& msg) override;

	/** ������������Ϣ
	*/
	virtual bool ButtonDown(const EventArgs& msg) override;

	/** ���ƿؼ�״̬��ɫ�ĺ���
	*/
	virtual void PaintStateColors(IRender* pRender) override;

	/** ѡ��״̬�仯�¼�(m_bSelected���������仯)
	*/
	virtual void OnPrivateSetSelected() override;

	/** ���Ʊ�ǩҳ(ѡ��״̬)
	*/
	virtual void PaintTabItemSelected(IRender* pRender) ;

	/** ���Ʊ�ǩҳ(��ͣ״̬)
	*/
	virtual void PaintTabItemHot(IRender* pRender);

	/** ���·��, �γ�Բ�Ǿ���
	*/
	void AddTabItemPath(IPath* path, const UiRect& rect, UiSize roundSize) const;

	/** �����ӿؼ���˳��
	*/
	void AdjustSubItemIndex();

	/** ��ȡTabCtrl�ӿ�
	*/
	TabCtrl* GetTabCtrl() const;

private:
	/** ѡ���ǩ��Բ�Ǵ�С
	*/
	struct RoundCorner
	{
		uint8_t cx; //Բ�ǵĿ��
		uint8_t cy; //Բ�ǵĸ߶�
	};

	/** Hot��ǩ��״̬Paddingֵ
	*/
	struct HotPadding
	{
		uint8_t left;
		uint8_t top;
		uint8_t right;
		uint8_t bottom;
	};

	/** ѡ��״̬�ı�ǩԲ�Ǵ�С
	*/
	RoundCorner m_rcSelected;

	/** ��ͣ״̬�ı�ǩԲ�Ǵ�С
	*/
	RoundCorner m_rcHot;

	/** Hot��ǩ��״̬Paddingֵ
	*/
	HotPadding m_hotPadding;

	/** �رհ�ť�Ƿ��Զ�����
	*/
	bool m_bAutoHideCloseBtn;

	/** ͼ��ؼ�
	*/
	Control* m_pIcon;

	/** �ı��ؼ�
	*/
	Label* m_pLabel;

	/** �رհ�ť
	*/
	Button* m_pCloseBtn;

	/** ��ǩ֮��ķָ���
	*/
	Control* m_pLine;

	/** ͼ��ؼ���Class
	*/
	UiString m_iconClass;

	/** �ı��ؼ���Class
	*/
	UiString m_titleClass;

	/** �رհ�ť�ؼ���Class
	*/
	UiString m_closeBtnClass;

	/** �ָ��ߵ�Class
	*/
	UiString m_lineClass;

	/** �ı�����
	*/
	UiString m_title;

	/** ͼ����Դ�ַ���
	*/
	UiString m_iconImageString;

private:
	/** �󶨵�TabBox����������
	*/
	size_t m_nTabBoxItemIndex;
};

}//namespace ui

#endif //UI_CONTROL_TABCTRL_H_
