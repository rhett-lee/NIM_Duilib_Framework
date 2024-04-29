#ifndef UI_CONTROL_CHECKCOMBO_H_
#define UI_CONTROL_CHECKCOMBO_H_

#pragma once

#include "duilib/Box/ScrollBox.h"

namespace ui
{

class CCheckComboWnd;
class UILIB_API CheckCombo : public ui::Box
{
	friend class CCheckComboWnd;
public:
	CheckCombo();
	CheckCombo(const CheckCombo& r) = delete;
	CheckCombo& operator=(const CheckCombo& r) = delete;
	virtual ~CheckCombo();

public:
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void Activate() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual bool AddItem(Control* pControl) override;
	virtual bool AddItemAt(Control* pControl, size_t iIndex) override;
	virtual bool RemoveItem(Control* pControl) override;
	virtual bool RemoveItemAt(size_t iIndex) override;
	virtual void RemoveAllItems() override;
	virtual Control* GetItemAt(size_t iIndex) const override;
	virtual size_t GetItemIndex(Control* pControl) const override;
	virtual bool SetItemIndex(Control* pControl, size_t iIndex) override;
	virtual size_t GetItemCount() const override;

	/** ���һ����������б���
	*/
	bool AddTextItem(const std::wstring& itemText);

	/** ��ȡѡ����ı��б�
	*/
	void GetSelectedText(std::vector<std::wstring>& selectedText) const;

	/** ��������б����ѡ����
	*/
	void ClearAll();

public:
	/** ��ȡ��ǰ������ List ����
	*/
	ui::ScrollBox* GetListBox() { return m_pDropList.get(); }

	/** �����������������Ϣ
	* @param [in] pstrList ת���� XML ��ʽ�����б�
	*/
	void SetDropBoxAttributeList(const std::wstring& pstrList);

	/** ��ȡ������������С
	*/
	ui::UiSize GetDropBoxSize() const;

	/** ����������������С
	* @param[in] szDropBox Ҫ���õĴ�С��Ϣ
	*/
	void SetDropBoxSize(ui::UiSize szDropBox);

	/** ���� Combobox �Ƿ����ϵ���
	* @param [in] top Ϊ true �����ϵ�����false Ϊ���µ���
	*/
	void SetPopupTop(bool top) { m_bPopupTop = top; };

	/** �ж� Combobox ����ģʽ�Ƿ������ϵ���
	*/
	bool IsPopupTop() const { return m_bPopupTop; };

	/** ���������б���ÿһ���б��������
	*/
	void SetDropboxItemClass(const std::wstring& classValue);

	/** ����ѡ������ÿһ�����������
	*/
	void SetSelectedItemClass(const std::wstring& classValue);

	/** ���������б��ڵ�λ��
	*/
	void UpdateComboWndPos();

	/** �����������ر��¼�
	* @param[in] callback �������رպ󴥷��Ļص�����
	*/
	void AttachWindowClose(const ui::EventCallback& callback) { AttachEvent(ui::kEventWindowClose, callback); }

private:
	/** Ĭ�ϵ����ѡ������
	* @param[in] args �����б�
	* @return ʼ�շ��� true
	*/
	bool OnSelectItem(const ui::EventArgs& args);
	bool OnUnSelectItem(const ui::EventArgs& args);
	bool OnListButtonDown(const ui::EventArgs& args);

private:
	/** ���������б�
	*/
	void ParseAttributeList(const std::wstring& strList,
							std::vector<std::pair<std::wstring, std::wstring>>& attributeList) const;

	/** ���ÿؼ��������б�
	*/
	void SetAttributeList(Control* pControl, const std::wstring& classValue);

	/** ����ѡ���б�ĸ߶�
	*/
	void UpdateSelectedListHeight();

protected:
	/** ������Ĵ��ڽӿ�
	*/
	CCheckComboWnd* m_pCheckComboWnd;

	/** �����б�����
	*/
	std::unique_ptr<ui::ScrollBox> m_pDropList;

	/** ѡ����б�������
	*/
	std::unique_ptr<ui::ScrollBox> m_pList;
	
	/** ������Ŀ�Ⱥ͸߶�
	*/
	ui::UiSize m_szDropBox;

	/** �������Ƿ����ϵ���
	*/
	bool m_bPopupTop;

	/** �����ĸ߶�
	*/
	int32_t m_iOrgHeight;

	/** ѡ������ı�
	*/
	std::vector<std::string> m_vecDate;

	/** �����б���ÿһ���б��������
	*/
	UiString m_dropboxItemClass;

	/** ѡ������ÿһ�����������
	*/
	UiString m_selectedItemClass;
};

} //namespace ui

#endif //UI_CONTROL_CHECKCOMBO_H_
