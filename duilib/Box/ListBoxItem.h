#ifndef UI_BOX_LISTBOX_ITEM_H_
#define UI_BOX_LISTBOX_ITEM_H_

#pragma once

#include "duilib/Box/VBox.h"
#include "duilib/Box/HBox.h"
#include "duilib/Control/Option.h"

namespace ui 
{
class IListBoxOwner;

/** ListBoxItem �ӿ�
*/
class UILIB_API IListBoxItem
{
public:
	virtual ~IListBoxItem() = default;

	/** ����Option���ѡ����, ֻ���½����ѡ��״̬
	* @param [in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
	 * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��
	*/
	virtual void OptionSelected(bool bSelect, bool bTriggerEvent) = 0;

	/** ����ѡ��״̬, ����洢״̬ͬ�������������κ��¼�(������ͬ��״̬)
	*/
	virtual void SetItemSelected(bool bSelected) = 0;

	/** �жϵ�ǰ�Ƿ���ѡ��״̬
	 * @return ���� true Ϊѡ��״̬������Ϊ false
	 */
	virtual bool IsSelected() const = 0;

	/** ��ȡ������
	 */
	virtual IListBoxOwner* GetOwner() = 0;

	/** ���ø�����
	 * @param[in] pOwner ������ָ��
	 */
	virtual void SetOwner(IListBoxOwner* pOwner) = 0;

	/** ��ȡ���������ţ���Χ��[0, GetItemCount())
	 */
	virtual size_t GetListBoxIndex() const = 0;

	/** ������������������
	 * @param[in] iIndex ������, ��Χ��[0, GetItemCount())
	 */
	virtual void SetListBoxIndex(size_t iIndex) = 0;

	/** ��ȡ�������Ԫ�������ţ�����֧�������Χ��[0, GetElementCount())
	 */
	virtual size_t GetElementIndex() const = 0;

	/** �����������Ԫ��������
	 * @param[in] iIndex ������, ����֧�������Χ��[0, GetElementCount())
	 */
	virtual void SetElementIndex(size_t iIndex) = 0;
};

/** �б������������������б���չʾ���ݵ�����
*/
template<typename InheritType = Box>
class UILIB_API ListBoxItemTemplate:
	public OptionTemplate<InheritType>,
	public IListBoxItem
{
public:
	ListBoxItemTemplate();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;	
	virtual void HandleEvent(const EventArgs& msg) override;

	/** �Ƿ����ѡ��״̬�µı���ɫ���ṩ�麯����Ϊ��ѡ��
	   ������ListBox/TreeView�ڵ��ڶ�ѡʱ�������й�ѡ�������Ҫ����ѡ��״̬�ı���ɫ��
	*/
	virtual bool CanPaintSelectedColors() const override;

	/** �жϿؼ������Ƿ�Ϊ��ѡ���
	 * @return ����true
	 */
	virtual bool IsSelectableType() const override;

	/** ���ÿؼ��Ƿ�ѡ��״̬
	 * @param [in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
	 * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��
	 */
	virtual void Selected(bool bSelect, bool bTriggerEvent) override;

	/** ����Option���ѡ����, ֻ���½����ѡ��״̬
	* @param [in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
	 * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��
	*/
	virtual void OptionSelected(bool bSelect, bool bTriggerEvent) override;

	/** ����ѡ��״̬, ����洢״̬ͬ�������������κ��¼�(������ͬ��״̬)
	*/
	virtual void SetItemSelected(bool bSelected) override;

	/** �жϵ�ǰ�Ƿ���ѡ��״̬
	 * @return ���� true Ϊѡ��״̬������Ϊ false
	 */
	virtual bool IsSelected() const override;

	/** ��ȡ������
	 */
	virtual IListBoxOwner* GetOwner() override;

	/** ���ø�����
	 * @param[in] pOwner ������ָ��
	 */
	virtual void SetOwner(IListBoxOwner* pOwner) override;

	/** ��ȡ���������ţ���Χ��[0, GetItemCount())
	 */
	virtual size_t GetListBoxIndex() const override;

	/** ������������������
	 * @param[in] iIndex ������, ��Χ��[0, GetItemCount())
	 */
	virtual void SetListBoxIndex(size_t iIndex) override;

	/** ��ȡ�������Ԫ�������ţ�����֧�������Χ��[0, GetElementCount())
	 */
	virtual size_t GetElementIndex() const override;

	/** �����������Ԫ��������
	 * @param[in] iIndex ������, ����֧�������Χ��[0, GetElementCount())
	 */
	virtual void SetElementIndex(size_t iIndex) override;

public:
	/** �������������
	* @param[in] callback Ҫ�󶨵Ļص�����
	*/
	void AttachClick(const EventCallback& callback) { this->AttachEvent(kEventClick, callback); }

	/** ������Ҽ����������
	* @param[in] callback Ҫ�󶨵Ļص�����
	*/
	void AttachRClick(const EventCallback& callback) { this->AttachEvent(kEventRClick, callback); }

	/** �����ؼ�˫���¼�
	 * @param[in] callback �յ�˫����Ϣʱ�Ļص�����
	 */
	void AttachDoubleClick(const EventCallback& callback) { this->AttachEvent(kEventMouseDoubleClick, callback); }

	/** �����س��¼�
	 * @param[in] callback �յ��س�ʱ�Ļص�����
	 */
	void AttachReturn(const EventCallback& callback) { this->AttachEvent(kEventReturn, callback); }

protected:
	/** ѡ��״̬�仯�¼�(m_bSelected���������仯)
	*/
	virtual void OnPrivateSetSelected() override;

	/** ��ѡ״̬�仯�¼�(m_bChecked���������仯)
	*/
	virtual void OnPrivateSetChecked() override;

private:
	/** ��ListBox�����е����������ţ���Χ��[0, GetItemCount())
	*/
	size_t m_iListBoxIndex;

	/** �������Ԫ�����������ţ�����֧�������Χ��[0, GetElementCount())
	*/
	size_t m_iElementIndex;

	/** ��ListBox�����ӿ�
	*/
	IListBoxOwner* m_pOwner;
};

/////////////////////////////////////////////////////////////////////////////////////

template<typename InheritType>
ListBoxItemTemplate<InheritType>::ListBoxItemTemplate():
	m_iListBoxIndex(Box::InvalidIndex),
	m_iElementIndex(Box::InvalidIndex),
	m_pOwner(nullptr)
{
	this->SetTextStyle(TEXT_LEFT | TEXT_VCENTER | TEXT_END_ELLIPSIS | TEXT_NOCLIP | TEXT_SINGLELINE, false);
}

template<typename InheritType>
std::wstring ListBoxItemTemplate<InheritType>::GetType() const { return DUI_CTR_LISTBOX_ITEM; }

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::SetItemSelected(bool bSelected)
{
	if (OptionTemplate<InheritType>::IsSelected() == bSelected) {
		return;
	}
	//ֱ���޸��ڲ�״̬
	OptionTemplate<InheritType>::SetSelected(bSelected);
	if (m_pOwner == nullptr) {
		return;
	}

	//ͬ��ListBox��ѡ��ID
	bool bChanged = false;
	if (bSelected) {
		m_pOwner->SetCurSel(m_iListBoxIndex);
		bChanged = true;
	}
	else {
		if (m_pOwner->GetCurSel() == m_iListBoxIndex) {
			m_pOwner->SetCurSel(Box::InvalidIndex);
			bChanged = true;
		}
	}

	if (bChanged && !m_pOwner->IsMultiSelect()) {
		//��ѡ����Ҫ����ѡ����, ��ֻ֤��һ��ѡ����
		m_pOwner->EnsureSingleSelection();
	}
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::OptionSelected(bool bSelect, bool bTriggerEvent)
{
	return OptionTemplate<InheritType>::Selected(bSelect, bTriggerEvent);
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::Selected(bool bSelected, bool bTriggerEvent)
{
	//�������Ȳ�������ѡ�����
	if (!this->IsEnabled()) {
		return;
	}
	if (m_pOwner != nullptr) {
		if (bSelected) {
			m_pOwner->SelectItem(m_iListBoxIndex, false, bTriggerEvent);
		}
		else {
			m_pOwner->UnSelectItem(m_iListBoxIndex, bTriggerEvent);
		}
	}
}

template<typename InheritType>
bool ListBoxItemTemplate<InheritType>::IsSelected() const
{
	return OptionTemplate<InheritType>::IsSelected();
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::OnPrivateSetSelected()
{
	if (m_pOwner != nullptr) {
		m_pOwner->OnItemSelectedChanged(m_iListBoxIndex, this);
	}
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::OnPrivateSetChecked()
{
	if (m_pOwner != nullptr) {
		m_pOwner->OnItemCheckedChanged(m_iListBoxIndex, this);
	}
}

template<typename InheritType>
bool ListBoxItemTemplate<InheritType>::CanPaintSelectedColors() const
{
	bool bHasStateImages = this->HasStateImages();
	if (m_pOwner != nullptr) {
		return m_pOwner->CanPaintSelectedColors(bHasStateImages);
	}
	return OptionTemplate<InheritType>::CanPaintSelectedColors();
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::HandleEvent(const EventArgs& msg)
{
	if (this->IsDisabledEvents(msg)) {
		//�������������Ϣ�����ҿؼ���Disabled�ģ�ת����Owner�ؼ�
		if (m_pOwner != nullptr) {
			m_pOwner->SendEvent(msg);
		}
		else {
			OptionTemplate<InheritType>::HandleEvent(msg);
		}
		return;
	}
	if (msg.Type == kEventMouseDoubleClick) {
		if (!this->IsActivatable()) {
			return;
		}
	}
	else if (msg.Type == kEventKeyDown && this->IsEnabled()) {
		if (msg.chKey == VK_RETURN) {
			if (this->IsActivatable()) {
				this->SendEvent(kEventReturn);
			}
			return;
		}
	}
	OptionTemplate<InheritType>::HandleEvent(msg);

	// An important twist: The list-item will send the event not to its immediate
	// parent but to the "attached" list. A list may actually embed several components
	// in its path to the item, but key-presses etc. needs to go to the actual list.
	//if( m_pOwner != NULL ) m_pOwner->HandleMessage(event); else Control::HandleMessage(event);
}

template<typename InheritType>
IListBoxOwner* ListBoxItemTemplate<InheritType>::GetOwner()
{
	return m_pOwner;
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::SetOwner(IListBoxOwner* pOwner)
{
	m_pOwner = pOwner;
}

template<typename InheritType>
size_t ListBoxItemTemplate<InheritType>::GetListBoxIndex() const
{
	return m_iListBoxIndex;
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::SetListBoxIndex(size_t iIndex)
{
	m_iListBoxIndex = iIndex;
}

template<typename InheritType>
size_t ListBoxItemTemplate<InheritType>::GetElementIndex() const
{
	return m_iElementIndex;
}

template<typename InheritType>
void ListBoxItemTemplate<InheritType>::SetElementIndex(size_t iIndex)
{
	m_iElementIndex = iIndex;
}

template<typename InheritType>
bool ListBoxItemTemplate<InheritType>::IsSelectableType() const
{
	return true;
}

/** ���Ͷ���
*/
typedef ListBoxItemTemplate<Box> ListBoxItem;
typedef ListBoxItemTemplate<HBox> ListBoxItemH;
typedef ListBoxItemTemplate<VBox> ListBoxItemV;

} // namespace ui

#endif // UI_BOX_LISTBOX_ITEM_H_
