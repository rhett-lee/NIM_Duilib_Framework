#ifndef UI_BOX_LISTBOX_H_
#define UI_BOX_LISTBOX_H_

#pragma once

#include "duilib/Box/ListBoxItem.h"
#include "duilib/Box/ScrollBox.h"
#include "duilib/Control/Option.h"

namespace ui 
{

/** �û��Զ����������
@param [in] pControl1 ��һ���ؼ��ӿ�
@param [in] pControl2 �ڶ����ؼ��ӿ�
@param [in] pCompareContext �û��Զ�������������
@return < 0 �ؼ�1С�ڿؼ�2
        = 0 �ؼ�1���ڿؼ�2
		> 0 �ؼ�1���ڿؼ�2
*/
typedef int (CALLBACK *PFNCompareFunc)(Control* pControl1, Control* pControl2, void* pCompareContext);

/** ȷ���ɼ��ĸ��ӱ�־(��ֱ���򣬴�ֱ������)
*/
enum class ListBoxVerVisible
{
	kVisible,			//��֤��ʾ�ڿɼ�����
	kVisibleAtTop,		//��֤��ʾ�ڿɼ�����Ķ���
	kVisibleAtCenter,	//��֤��ʾ�ڿɼ�������м�
	kVisibleAtBottom,	//��֤��ʾ�ڿɼ�����ĵͲ�
};

/** ȷ���ɼ��ĸ��ӱ�־(ˮƽ����ˮƽ������)
*/
enum class ListBoxHorVisible
{
	kVisible,			//��֤��ʾ�ڿɼ�����
	kVisibleAtLeft,		//��֤��ʾ�ڿɼ���������
	kVisibleAtCenter,	//��֤��ʾ�ڿɼ�������м�
	kVisibleAtRight,	//��֤��ʾ�ڿɼ�������Ҳ�
};

/** ListBox�����߽ӿ�
*/
class UILIB_API IListBoxOwner
{
public:
	/** �����¼�
	*/
	virtual void SendEvent(const EventArgs& event) = 0;

	/** ��ȡ��ǰѡ���������(�������Ч�������򷵻�Box::InvalidIndex)
	*/
	virtual size_t GetCurSel() const = 0;

	/** ���õ�ǰѡ�������
	* @param [in] iIndex ����Ŀ��ID
	*/
	virtual void SetCurSel(size_t iIndex) = 0;

	/** ѡ������
	*  @param [in] iIndex ����Ŀ��ID
	*  @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventSelect�¼�
	*  @param [in] vkFlag ������־, ȡֵ��Χ�μ� enum VKFlag �Ķ���
	*/
	virtual bool SelectItem(size_t iIndex, bool bTakeFocus, 
							bool bTriggerEvent, uint64_t vkFlag = 0) = 0;

	/** ȡ��ѡ������
	*  @param [in] iIndex ����Ŀ��ID
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventUnSelect�¼�
	*/
	virtual bool UnSelectItem(size_t iIndex, bool bTriggerEvent) = 0;

	/** �����ѡ��״̬�仯�¼�������״̬ͬ��
	* @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	* @param [in] pListBoxItem �������б���ӿ�
	*/
	virtual void OnItemSelectedChanged(size_t iIndex, IListBoxItem* pListBoxItem) = 0;

	/** ����Ĺ�ѡ״̬�仯�¼�������״̬ͬ��
	* @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	* @param [in] pListBoxItem �������б���ӿ�
	*/
	virtual void OnItemCheckedChanged(size_t iIndex, IListBoxItem* pListBoxItem) = 0;

	/** ȷ����������ɼ�
	* @param [in] rcItem �ɼ�����ľ��η�Χ
	* @param [in] vVisibleType ��ֱ����ɼ��ĸ��ӱ�־
	* @param [in] hVisibleType ˮƽ����ɼ��ĸ��ӱ�־
	*/
	virtual void EnsureVisible(const UiRect& rcItem, 
							   ListBoxVerVisible vVisibleType,
		                       ListBoxHorVisible hVisibleType) = 0;

	/** ֹͣ����������
	*/
	virtual void StopScroll() = 0;

	/** �Ƿ����ѡ��״̬�µı���ɫ���ṩ�麯����Ϊ��ѡ��
	   ������ListBox/TreeView�ڵ��ڶ�ѡʱ�������й�ѡ�������Ҫ����ѡ��״̬�ı���ɫ��
	   @param [in] bHasStateImages ��ǰ�б����Ƿ���CheckBox��ѡ��
	*/
	virtual bool CanPaintSelectedColors(bool bHasStateImages) const = 0;

	/** �Ƿ������ѡ
	*/
	virtual bool IsMultiSelect() const = 0;

	/** ѡ���������¼�����ѡʱ���ڱ�ֻ֤��һ��ѡ����
	*/
	virtual void EnsureSingleSelection() = 0;
};

/////////////////////////////////////////////////////////////////////////////////////
//

/** �б�����������չʾһ������ʹ��
*   ͨ���޸Ĳ��֣��γ� HListBox��VListBox��TileListBox��������
*/
class UILIB_API ListBox : public ScrollBox, public IListBoxOwner
{
public:
	explicit ListBox(Layout* pLayout);
	ListBox(const ListBox& r) = delete;
	ListBox& operator=(const ListBox& r) = delete;

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void HandleEvent(const EventArgs& msg) override;
	virtual bool ButtonDown(const EventArgs& msg) override;
	virtual void SendEvent(EventType eventType, WPARAM wParam = 0, LPARAM lParam = 0, TCHAR tChar = 0,
						   const UiPoint& mousePos = UiPoint()) override;
	virtual void SendEvent(const EventArgs& event) override;

	//IListBoxOwner �ӿڵ�ʵ��
	virtual void StopScroll() override;
	virtual bool CanPaintSelectedColors(bool bHasStateImages) const override;
	virtual void EnsureSingleSelection() override;

public:
	/** �Ƿ�֧�ֶ�ѡ
	*/
	virtual bool IsMultiSelect() const override;

	/** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
	* @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
	*/
	virtual void SetMultiSelect(bool bMultiSelect);

	/** ��ȡ��ǰѡ�������(����ѡʱ��Ч)
	@return ����ѡ����������������Ч�������򷵻�Box::InvalidIndex
	*/
	virtual size_t GetCurSel() const override;

	/** ���õ�ǰѡ�������(����ѡʱ��Ч)
	* @param [in] iIndex ����Ŀ��ID
	*/
	virtual void SetCurSel(size_t iIndex) override;

	/** ��ȡ�Ƿ��������ֵĹ����ı�ѡ��������(��ѡ�����ѡ��Ч)
	* @return ���� true ��ʾ����������ı�ѡ�������Ϊ false
	*/
	bool IsScrollSelect() const;

	/** �����Ƿ��������ֵĹ����ı�ѡ��������(��ѡ�����ѡ��Ч)
	 * @param[in] bScrollSelect Ϊ true ��Ϊ����������ı�ѡ���false Ϊ������
	 */
	void SetScrollSelect(bool bScrollSelect);

	/** ���Ƴ�һ�������, ������Ƴ�����ѡ����Ƿ��Զ�ѡ����һ��(��ѡ�����ѡ��Ч)
	 */
	bool IsSelectNextWhenActiveRemoved() const;

	/** ���Ƴ�һ�������, ������Ƴ�����ѡ������Զ�ѡ����һ��(��ѡ�����ѡ��Ч)
	 * @param [in] bSelectNextItem Ϊ true ʱ�Զ�ѡ����һ�false Ϊ���Զ�ѡ��
	 */
	void SetSelectNextWhenActiveRemoved(bool bSelectNextItem);

public:
	/** ������һ����ѡ�ؼ�������
	 * @param[in] iIndex ָ��Ҫ��ʼ���ҵ�����
	 * @param[in] bForward true Ϊ�������ң� false Ϊ�ݼ�����
	 * @return ��һ����ѡ�ؼ������������� Box::InvalidIndex Ϊû�п�ѡ�ؼ�
	 */
	virtual size_t FindSelectable(size_t iIndex, bool bForward = true) const;

	/** ��ȡ��ǰѡ�������(֧�ֵ�ѡ�Ͷ�ѡ)��ѡ��ʱ�ų�!IsVisible() �� !IsEnabled() ����
	* @param [out] selectedIndexs ����ѡ�������ID����Χ�ǣ�[0, GetItemCount())
	*/
	virtual void GetSelectedItems(std::vector<size_t>& selectedIndexs) const;

	/** ѡ������
	*  @param [in] iIndex ����Ŀ��ID
	*  @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventSelect�¼�
	*  @param [in] vkFlag ������־, ȡֵ��Χ�μ� enum VKFlag �Ķ���
	*/
	virtual bool SelectItem(size_t iIndex, bool bTakeFocus, 
							bool bTriggerEvent, uint64_t vkFlag = 0) override;

	/** ȡ��ѡ������
	*  @param [in] iIndex ����Ŀ��ID
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventUnSelect�¼�
	*/
	virtual bool UnSelectItem(size_t iIndex, bool bTriggerEvent) override;

	/** ѡ����һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemPrevious(bool bTakeFocus, bool bTriggerEvent);

	/** ѡ����һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemNext(bool bTakeFocus, bool bTriggerEvent);

	/** ���Ϲ���һҳ��ѡ��һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemPageUp(bool bTakeFocus, bool bTriggerEvent);

	/** ���¹���һҳ��ѡ��һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemPageDown(bool bTakeFocus, bool bTriggerEvent);

	/** ��������һҳ��ѡ�е�һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemHome(bool bTakeFocus, bool bTriggerEvent);

	/** ���������һҳ��ѡ�����һ���ȷ��ѡ����ɼ�
	* @return ����ѡ�е�������������Ч��Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t SelectItemEnd(bool bTakeFocus, bool bTriggerEvent);

public:	
	/** ȷ����������ɼ�
	* @param [in] rcItem �ɼ�����ľ��η�Χ
	* @param [in] vVisibleType ��ֱ����ɼ��ĸ��ӱ�־
	* @param [in] hVisibleType ˮƽ����ɼ��ĸ��ӱ�־
	*/
	virtual void EnsureVisible(const UiRect& rcItem,
							   ListBoxVerVisible vVisibleType,
							   ListBoxHorVisible hVisibleType) override;

	/** ȷ������ɼ�
	* @param [in] iIndex ������������Χ�ǣ�[0, GetItemCount())
	* @param [in] vVisibleType ��ֱ����ɼ��ĸ��ӱ�־
	* @param [in] hVisibleType ˮƽ����ɼ��ĸ��ӱ�־
	* @return ��������ʵ�֣����ظ�Ԫ�ض�Ӧ���µĿؼ������ţ���Χ�ǣ�[0, GetItemCount())
	*/
	virtual size_t EnsureVisible(size_t iIndex,
							     ListBoxVerVisible vVisibleType = ListBoxVerVisible::kVisible,
							     ListBoxHorVisible hVisibleType = ListBoxHorVisible::kVisible);

	/** ������ָ������λ��
	 * @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	 */
	virtual bool ScrollItemToTop(size_t iIndex);

	/** ������ָ������λ��
	 * @param [in] itemName ��������(����Control::GetName())
	 */
	virtual bool ScrollItemToTop(const std::wstring& itemName);

	/** ��ȡ��ǰ��������(Control::GetPos())�еĵ�һ������
	 */
	virtual Control* GetTopItem() const;

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

public:
	/** ����������
	 * @param [in] pfnCompare �Զ���������
	 * @param [in] pCompareContext ���ݸ��ȽϺ������û��Զ�������
	 */
	virtual bool SortItems(PFNCompareFunc pfnCompare, void* pCompareContext);

	/** ����ѡ��������¼�
	* @param[in] callback ѡ������ʱ�Ļص�����
	*            ����˵��:
	*                   wParam: ��ǰ��ѡ�������ID
	*					lParam: ԭ����ѡ�������ID������Ϊ��ЧֵBox::InvalidIndex
	*/
	void AttachSelect(const EventCallback& callback) { AttachEvent(kEventSelect, callback); }

	/** ����ȡ��ѡ��������¼�
	* @param[in] callback ȡ��ѡ������ʱ�Ļص�����
	*            ����˵��:
	*                   wParam: ȡ��ѡ�������ID
	*					lParam: ��ЧֵBox::InvalidIndex
	*/
	void AttachUnSelect(const EventCallback& callback) { AttachEvent(kEventUnSelect, callback); }

protected:
	/** ���Ӷ�ѡ�л�Ϊ��ѡģʽ��ʱ����Ҫȷ���б���ֻ��һ��ѡ����
	* @return ����б仯����true�����򷵻�false
	*/
	virtual bool OnSwitchToSingleSelect();

	/** ͬ����ǰѡ�����ѡ��״̬
	* @return ����б仯����true�����򷵻�false
	*/
	bool UpdateCurSelItemSelectStatus();

	/** ���ҵ�ģʽ
	*/
	enum class SelectableMode
	{
		kForward,	//�ӵ�ǰԪ��nCurSel��ǰ���ҵ�nCount������
		kBackward,	//�ӵ�ǰԪ��nCurSel�����ҵ�nCount������
		kSelect,	//��λ����ǰ��ѡ������ݣ����ģʽ�£�ѡ������ݿ��ܲ�����ʾ����
		kHome,		//��λ����һ������
		kEnd		//��λ�����һ������
	};
	/** ��������ָ����Ԫ�أ�Ϊ����ṩ�������ݵĻ��ᣩ
	* @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
	* @param [in] mode  ���ҵ�ģʽ
	* @param [in] nCount ���ҵĿؼ��ĵڼ�������
	* @param [out] nDestItemIndex ���ؼ��غ��Ŀ��ؼ������ţ���Ч��Χ: [0, GetItemCount())
	* @return ����true��ʾ�����ݼ�����Ϊ��false��ʾ���κζ���
	*/
	virtual bool OnFindSelectable(size_t nCurSel, SelectableMode mode, 
								  size_t nCount, size_t& nDestItemIndex);

	/** ��ѯ��������ǰ�滹�м������ݣ�֧��������ݣ�
	* @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
	*/
	virtual size_t GetItemCountBefore(size_t nCurSel);

	/** ��ѯ�������ݺ��滹�м������ݣ�֧��������ݣ�
	* @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
	*/
	virtual size_t GetItemCountAfter(size_t nCurSel);

	/** �����ѡ��״̬�仯�¼�������״̬ͬ��
	* @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	* @param [in] pListBoxItem �������б���ӿ�
	*/
	virtual void OnItemSelectedChanged(size_t iIndex, IListBoxItem* pListBoxItem) override;

	/** ����Ĺ�ѡ״̬�仯�¼�������״̬ͬ��
	* @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	* @param [in] pListBoxItem �������б���ӿ�
	*/
	virtual void OnItemCheckedChanged(size_t iIndex, IListBoxItem* pListBoxItem) override;

	/** ��ӦKeyDown��Ϣ
	* @return ����true��ʾ�ɹ���������false��ʾδ�������Ϣ
	*/
	bool OnListBoxKeyDown(const EventArgs& msg);

	/** ��ӦMouseWheel��Ϣ
	@return ����true��ʾ�ɹ���������false��ʾδ�������Ϣ
	*/
	bool OnListBoxMouseWheel(const EventArgs& msg);

protected:
	/**
	 * @brief Ĭ�ϵ�����Աȷ���
	 * @param[in] pvlocale ���� List ָ��
	 * @param[in] item1 ����1
	 * @param[in] item2 ����2
	 * @return ���ضԱȽ��
	 */
	static int __cdecl ItemComareFunc(void* pvlocale, const void* item1, const void* item2);
	int __cdecl ItemComareFunc(const void* item1, const void* item2);

	/** ѡ������(��ѡ)
	*  @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	*  @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventSelect�¼�
	*/
	bool SelectItemSingle(size_t iIndex, bool bTakeFocus, bool bTriggerEvent);

	/** ѡ������(��ѡ)
	*  @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	*  @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
	*  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventSelect�¼�
	*/
	bool SelectItemMulti(size_t iIndex, bool bTakeFocus, bool bTriggerEvent);

	/** ѡ�����ѡ�к�������ؼ���Ϊ����ؼ���������һ��kEventSelect�¼�
	*   Ϊ���η�װ�������൱�ڣ�SelectItem(iIndex, true, true);
	*  @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	*/
	bool SelectItem(size_t iIndex);

	/** ����ҳ�ķ�ʽѡ������
	*/
	size_t SelectItemPage(bool bTakeFocus, bool bTriggerEvent, bool bForward, int32_t nDeltaValue);

	/** ����ԾnCount������ķ�ʽѡ������
	*/
	size_t SelectItemCountN(bool bTakeFocus, bool bTriggerEvent, bool bForward, size_t nCount);

	/** ��ȡ��ǰ���ַ���
	* @return ����true��ʾΪ���򲼾֣�����Ϊ���򲼾�
	*/
	bool IsHorizontalLayout() const;

	/** �жϵ�ǰ�����Ƿ�Ϊ���������
	*/
	bool IsHorizontalScrollBar() const;

	/** ȷ��ѡ����ɼ�
	* @param [in] itemIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	* @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
	* return �����µĿؼ�������(��������¿ռ������ſ��ܻᷢ���仯)����Χ�ǣ�[0, GetItemCount())
	*/
	size_t SelectEnsureVisible(size_t itemIndex, bool bTakeFocus);

	/** �ж�һ�������Ƿ�Ϊ��ѡ����
	* @param [in] itemIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
	*/
	bool IsSelectableItem(size_t itemIndex) const;

	/** ���㱾ҳ������ʾ��������
	* @param [in] bIsHorizontal ��ǰ�����Ƿ�Ϊˮƽ����
	* @param [out] nColumns ��������
	* @param [out] nRows ��������
	* @return ���ؿ���������ʾ�ļ�¼��
	*/
	virtual size_t GetDisplayItemCount(bool bIsHorizontal, size_t& nColumns, size_t& nRows) const;

	/** ������Ƭ���֣��������ʾ����
	* @return ����ֵ��>= 1
	*/
	int32_t CalcHTileRows(HTileLayout* pHTileLayout) const;

	/** ������Ƭ���֣��������ʾ����
	* @return ����ֵ��>= 1
	*/
	int32_t CalcHTileColumns(HTileLayout* pHTileLayout) const;

	/** ������Ƭ���֣���������
	* @return ����ֵ��>= 1
	*/
	int32_t CalcVTileColumns(VTileLayout* pVTileLayout) const;

	/** ������Ƭ���֣��������ʵ����
	* @return ����ֵ��>= 1
	*/
	int32_t CalcVTileRows(VTileLayout* pVTileLayout) const;

private:
	//�Ƿ�������ı�ѡ����
	bool m_bScrollSelect;

	//���Ƴ�һ��������Զ�ѡ����һ��
	bool m_bSelectNextWhenActiveRemoved;

	//�Ƿ������ѡ��Ĭ��Ϊ��ѡ��
	bool m_bMultiSelect;

	//��ѡ��ʱ���Ƿ���ʾѡ�񱳾�ɫ: 0 - Ĭ�Ϲ���; 1 - ��ʾ����ɫ; 2: ����ʾ����ɫ
	uint8_t m_uPaintSelectedColors;

	//��ǰѡ�������ID, ����Ƕ�ѡ��ָ�����һ��ѡ����
	size_t m_iCurSel;

	//�û��Զ��������ȽϺ���
	PFNCompareFunc m_pCompareFunc;

	//�û��Զ��������ȽϺ����е�����������
	void* m_pCompareContext;
};

/////////////////////////////////////////////////////////////////////////////////////
//

/** ���򲼾ֵ�ListBox
*/
class UILIB_API HListBox : public ListBox
{
public:
	HListBox() :
		ListBox(new HLayout)
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_HLISTBOX; }
};

/** ���򲼾ֵ�ListBox
*/
class UILIB_API VListBox : public ListBox
{
public:
	VListBox() :
		ListBox(new VLayout)
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_VLISTBOX; }
};

/** ��Ƭ���ֵ�ListBox(���򲼾�)
*/
class UILIB_API HTileListBox : public ListBox
{
public:
	HTileListBox() :
		ListBox(new HTileLayout)
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_HTILE_LISTBOX; }
};

/** ��Ƭ���ֵ�ListBox(���򲼾�)
*/
class UILIB_API VTileListBox : public ListBox
{
public:
	VTileListBox() :
		ListBox(new VTileLayout)
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_VTILE_LISTBOX; }
};

} // namespace ui

#endif // UI_BOX_LISTBOX_H_
