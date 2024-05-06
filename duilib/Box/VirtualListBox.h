#ifndef UI_BOX_VIRTUAL_LISTBOX_H_
#define UI_BOX_VIRTUAL_LISTBOX_H_

#pragma once

#include "duilib/Box/ListBox.h"
#include "duilib/Box/VirtualHLayout.h"
#include "duilib/Box/VirtualVLayout.h"
#include "duilib/Box/VirtualHTileLayout.h"
#include "duilib/Box/VirtualVTileLayout.h"
#include "base/callback/callback.h"
#include <functional>

namespace ui {

typedef std::function<void(size_t nStartIndex, size_t nEndIndex)> DataChangedNotify;
typedef std::function<void()> CountChangedNotify;

class UILIB_API VirtualListBoxElement : public virtual nbase::SupportWeakCallback
{
public:
    VirtualListBoxElement();

    /** ����һ��������
    * @return ���ش������������ָ��
    */
    virtual ui::Control* CreateElement() = 0;

    /** ���ָ��������
    * @param [in] pControl ������ؼ�ָ��
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    */
    virtual bool FillElement(ui::Control* pControl, size_t nElementIndex) = 0;

    /** ��ȡ����������
    * @return ��������������
    */
    virtual size_t GetElementCount() const = 0;

    /** ����ѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] bSelected true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual void SetElementSelected(size_t nElementIndex, bool bSelected) = 0;

    /** ��ȡѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @return true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual bool IsElementSelected(size_t nElementIndex) const = 0;

    /** ��ȡѡ���Ԫ���б�
    * @param [in] selectedIndexs ���ص�ǰѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    */
    virtual void GetSelectedElements(std::vector<size_t>& selectedIndexs) const = 0;

    /** �Ƿ�֧�ֶ�ѡ
    */
    virtual bool IsMultiSelect() const = 0;

    /** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
    * @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
    */
    virtual void SetMultiSelect(bool bMultiSelect) = 0;

public:
    /** ע���¼�֪ͨ�ص�
    * @param [in] dcNotify �������ݱ仯֪ͨ�ӿ�
    * @param [in] ccNotify ����������仯֪ͨ�ӿ�
    */
    void RegNotifys(const DataChangedNotify& dcNotify, const CountChangedNotify& ccNotify);

protected:

    /** ����֪ͨ���������ݷ����仯
    * @param [in] nStartElementIndex ���ݵĿ�ʼ�±�
    * @param [in] nEndElementIndex ���ݵĽ����±�
    */
    void EmitDataChanged(size_t nStartElementIndex, size_t nEndElementIndex);

    /** ����֪ͨ����������������仯
    */
    void EmitCountChanged();

private:

    /** �������ݷ����仯����Ӧ����
    */
    DataChangedNotify m_pfnDataChangedNotify;

    /** ���ݸ��������仯����Ӧ����
    */
    CountChangedNotify m_pfnCountChangedNotify;
};

/** ���ʵ�ֵ�ListBox��֧�ִ���������ֻ֧�����������
*/
class UILIB_API VirtualListBox : public ListBox
{
    friend class VirtualHLayout;
    friend class VirtualVLayout;    
    friend class VirtualHTileLayout;
    friend class VirtualVTileLayout;
public:
    explicit VirtualListBox(Layout* pLayout);

    /** �������ݴ������
    * @param[in] pProvider ��������Ҫ��д VirtualListBoxElement �Ľӿ�����Ϊ���ݴ������
    */
    virtual void SetDataProvider(VirtualListBoxElement* pProvider);

    /** ��ȡ���ݴ������
    */
    VirtualListBoxElement* GetDataProvider() const;

    /** �Ƿ������ݴ������ӿ�
    */
    bool HasDataProvider() const;

    /** �Ƿ�֧�ֶ�ѡ
    */
    virtual bool IsMultiSelect() const override;

    /** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
    * @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
    */
    virtual void SetMultiSelect(bool bMultiSelect) override;

public:
    /** ��ȡ����Ԫ������
    * @return ��������Ԫ���ܸ���
    */
    size_t GetElementCount() const;

    /** ��ȡ��ǰѡ�������Ԫ��������(����ѡʱ��Ч)
    @return ����ѡ�������Ԫ�������ţ���Χ��[0, GetElementCount())
    */
    size_t GetCurSelElement() const;

    /** ����ѡ��״̬, ͬʱ������½�����ʾ
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] bSelected true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    void SetElementSelected(size_t nElementIndex, bool bSelected);

    /** ��������ѡ��Ԫ��, ͬʱ������½�����ʾ
    * @param [in] selectedIndexs ��Ҫ����ѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    * @return ��������ݱ仯����true�����򷵻�false
    */
    bool SetSelectedElements(const std::vector<size_t>& selectedIndexs, bool bClearOthers);

    /** ��������ѡ��Ԫ��, �����½�����ʾ
    * @param [in] selectedIndexs ��Ҫ����ѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SetSelectedElements(const std::vector<size_t>& selectedIndexs, 
                             bool bClearOthers,
                             std::vector<size_t>& refreshIndexs);

    /** ��ȡѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @return true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    bool IsElementSelected(size_t nElementIndex) const;

    /** ��ȡѡ���Ԫ���б�
    * @param [in] selectedIndexs ���ص�ǰѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    */
    void GetSelectedElements(std::vector<size_t>& selectedIndexs) const;

    /** ѡ��ȫ��, ͬʱ������½�����ʾ
    * @return ��������ݱ仯����true�����򷵻�false
    */
    bool SetSelectAll();

    /** ȡ������ѡ��, ͬʱ������½�����ʾ
    * @return ��������ݱ仯����true�����򷵻�false
    */
    bool SetSelectNone();

    /** ȡ������ѡ��, �����½�����ʾ���������ⲿˢ�½�����ʾ
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SetSelectNone(std::vector<size_t>& refreshIndexs);

    /** ȡ������ѡ��(���ų�����Ԫ��), �����½�����ʾ���������ⲿˢ�½�����ʾ
    * @param [in] excludeIndexs ��Ҫ�ų���Ԫ�������ţ��ⲿ��Ԫ�ص�ѡ��״̬����ԭ״
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SetSelectNoneExclude(const std::vector<size_t>& excludeIndexs, 
                              std::vector<size_t>& refreshIndexs);

    /** ��ȡ��ǰ���пɼ��ؼ�������Ԫ������
    * @param [out] collection �����б���Ч��Χ��[0, GetElementCount())
    */
    void GetDisplayElements(std::vector<size_t>& collection) const;

    /** ��ȡһ��Ԫ�ض�Ӧ��ʾ�ؼ���������
    * @param [in] nElementIndex Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
    * @return ���ظ�Ԫ�ض�ӦUI�ؼ��������ţ���Ч��Χ��[0, GetItemCount())
    */
    size_t GetDisplayItemIndex(size_t nElementIndex) const;

    /** ��ȡһ����ʾ�ؼ�������Ԫ��������
    * @param [in] nItemIndex UI�ؼ��������ţ���Ч��Χ��[0, GetItemCount())
    * @return ��UI�ؼ�����������Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
    */
    size_t GetDisplayItemElementIndex(size_t nItemIndex) const;

    /** �ÿؼ��ڿɼ���Χ��
    * @param [in] nElementIndex Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
    * @param [in] bToTop �Ƿ������Ϸ�
    */
    void EnsureVisible(size_t nElementIndex, bool bToTop);

    /** ˢ��ָ����Χ�����ݣ����������������ʾͬ�������ݷ�Χ: [nStartElementIndex, nEndElementIndex]
    * @param [in] nStartElementIndex ���ݵĿ�ʼ�±�
    * @param [in] nEndElementIndex ���ݵĽ����±�
    */
    void RefreshElements(size_t nStartElementIndex, size_t nEndElementIndex);

    /** ˢ��ָ�������ݣ����������������ʾͬ��
    * @param [elementIndexs] �б���ΪԪ�������ţ���Ч��Χ��[0, GetElementCount())
    */
    void RefreshElements(const std::vector<size_t>& elementIndexs);

    /** ˢ���б�
    */
    virtual void Refresh();

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
							     ListBoxHorVisible hVisibleType = ListBoxHorVisible::kVisible) override;

public:
    /** ����ѡ��������¼�
    * @param[in] callback ѡ������ʱ�Ļص�����
    * ����˵��:
    *   wParam: ��ǰ��ѡ�������ID����Ч��Χ��[0, GetItemCount())
    *	lParam: ԭ����ѡ�������ID����Ч��Χ��[0, GetItemCount())������Ϊ��ЧֵBox::InvalidIndex
    *   ����ͨ�� GetDisplayItemElementIndex �����õ�����������Ԫ��������
    */
    void AttachSelect(const EventCallback& callback) { AttachEvent(kEventSelect, callback); }

    /** ����˫���¼�
     * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
     *  ����˵��:
     *    wParam: ˫��������ID����Ч��Χ��[0, GetItemCount())�����ֵBox::InvalidIndex����ʾδ˫���κ�����
     *    lParam: ����������ID��Ӧ������Ԫ�������ţ���Ч��Χ��[0, GetElementCount())�����ֵBox::InvalidIndex����ʾ�޹���������Ԫ��
     */
    void AttachDoubleClick(const EventCallback& callback) { AttachEvent(kEventMouseDoubleClick, callback); }

    /** �������������
    * @param[in] callback Ҫ�󶨵Ļص�����
    *  ����˵��:
    *    wParam: ���������ID����Ч��Χ��[0, GetItemCount())�����ֵBox::InvalidIndex����ʾδ˫���κ�����
    *    lParam: ����������ID��Ӧ������Ԫ�������ţ���Ч��Χ��[0, GetElementCount())�����ֵBox::InvalidIndex����ʾ�޹���������Ԫ��
    */
    void AttachClick(const EventCallback& callback) { AttachEvent(kEventClick, callback); }

    /** ������Ҽ����������
    * @param[in] callback Ҫ�󶨵Ļص�����
    *  ����˵��:
    *    wParam: ���������ID����Ч��Χ��[0, GetItemCount())�����ֵBox::InvalidIndex����ʾδ˫���κ�����
    *    lParam: ����������ID��Ӧ������Ԫ�������ţ���Ч��Χ��[0, GetElementCount())�����ֵBox::InvalidIndex����ʾ�޹���������Ԫ��
    */
    void AttachRClick(const EventCallback& callback) { AttachEvent(kEventRClick, callback); }

    /** �����س��¼�
     * @param[in] callback �յ��س�ʱ�Ļص�����
     *  ����˵��:
     *    wParam: ����������ID����Ч��Χ��[0, GetItemCount())�����ֵBox::InvalidIndex����ʾδ˫���κ�����
     *    lParam: ����������ID��Ӧ������Ԫ�������ţ���Ч��Χ��[0, GetElementCount())�����ֵBox::InvalidIndex����ʾ�޹���������Ԫ��
     */
    void AttachReturn(const EventCallback& callback) { this->AttachEvent(kEventReturn, callback); }

public:
    /// ��д����ӿڣ��ṩ���Ի�����
    virtual void SetScrollPos(UiSize64 szPos) override;
    virtual void SetPos(UiRect rc) override;
    virtual void PaintChild(IRender* pRender, const UiRect& rcPaint) override;
    virtual void SendEvent(EventType eventType, WPARAM wParam = 0, LPARAM lParam = 0, TCHAR tChar = 0,
                           const UiPoint& mousePos = UiPoint()) override;
    virtual void SendEvent(const EventArgs& event) override;

protected:
    //����ɾ����������ֹ�ⲿ����
    virtual bool RemoveItem(Control* pControl) override;
    virtual bool RemoveItemAt(size_t iIndex) override;
    virtual void RemoveAllItems() override;

    /** ��������ָ����Ԫ�أ�Ϊ����ṩ�������ݵĻ��ᣩ
	* @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
	* @param [in] mode  ���ҵ�ģʽ
	* @param [in] nCount ���ҵĿؼ��ĵڼ�������
	* @param [out] nDestItemIndex ���ؼ��غ��Ŀ��ؼ������ţ���Ч��Χ: [0, GetItemCount())
	* @return ����true��ʾ�����ݼ�����Ϊ��false��ʾ���κζ���
	*/
	virtual bool OnFindSelectable(size_t nCurSel, SelectableMode mode, 
								  size_t nCount, size_t& nDestItemIndex) override;

    /** ��ѯ��������ǰ�滹�м������ݣ�֧��������ݣ�
    * @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
    */
    virtual size_t GetItemCountBefore(size_t nCurSel) override;

    /** ��ѯ�������ݺ��滹�м������ݣ�֧��������ݣ�
    * @param [in] nCurSel ��ǰѡ�����ʾ�ؼ�������
    */
    virtual size_t GetItemCountAfter(size_t nCurSel) override;

    /** �ж�һ������Ԫ���Ƿ�Ϊ��ѡ����
	* @param [in] nElementIndex Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
	*/
    virtual bool IsSelectableElement(size_t nElementIndex) const;

    /** ��ȡ��һ����ѡ�������Ԫ��
    * @param [in] nElementIndex Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
    * @param [in] bForward true��ʾ��ǰ���ң�false��ʾ������
    */
    virtual size_t FindSelectableElement(size_t nElementIndex, bool bForward) const;

    /** ����������
     * @param [in] pfnCompare �Զ���������
     * @param [in] pCompareContext ���ݸ��ȽϺ������û��Զ�������
     */
    virtual bool SortItems(PFNCompareFunc pfnCompare, void* pCompareContext) override;

    /** �����ѡ��״̬�仯�¼�������״̬ͬ��
    * @param [in] iIndex ����Ŀ��ID����Χ�ǣ�[0, GetItemCount())
    * @param [in] pListBoxItem �������б���ӿ�
    */
    virtual void OnItemSelectedChanged(size_t iIndex, IListBoxItem* pListBoxItem) override;

protected:

    /** ��������ֽӿ�
    */
    void SetVirtualLayout(VirtualLayout* pVirtualLayout);

    /** ��ȡ����ֽӿ�
    */
    VirtualLayout* GetVirtualLayout() const;

public:
    struct RefreshData
    {
        size_t nItemIndex;      //����ؼ���������
        Control* pControl;      //����ؼ��Ľӿ�
        size_t nElementIndex;   //����Ԫ�ص�������
    };
    typedef std::vector<RefreshData> RefreshDataList;

    /** ִ���˽���ˢ�²���, �����UI�ؼ��������ܻᷢ���仯
    */
    virtual void OnRefreshElements(const RefreshDataList& /*refreshDataList*/) {}

protected:
    /** ����һ������
    * @return ���ش����������ָ��
    */
    Control* CreateElement();

    /** ���ָ��������
    * @param[in] pControl ������ؼ�ָ��
    * @param[in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    */
    void FillElement(Control* pControl, size_t nElementIndex);

    /** ���²�������
    * @param[in] bForce �Ƿ�ǿ�����²���
    */
    void ReArrangeChild(bool bForce);

    /** �������ݷ����仯�����¼�����Ҫ���¼���չʾ����
    */
    void OnModelDataChanged(size_t nStartElementIndex, size_t nEndElementIndex);

    /** ���ݸ��������仯�����¼�����Ҫ���¼���չʾ����
    */
    void OnModelCountChanged();

    /** �Ƿ�����ӽ���״̬ͬ�����洢״̬
    */
    bool IsEnableUpdateProvider() const;

    /** �����¼��ĺ���
    * @param [in] args �¼�����
    * @param [in] bFromItem true��ʾ�����ӿؼ���false��ʾ��������
    */
    void VSendEvent(const EventArgs& args, bool bFromItem);

private:
    /** ���ݴ������ӿڣ��ṩչʾ����
    */
    VirtualListBoxElement* m_pDataProvider;

    /** ����ֽӿ�
    */
    VirtualLayout* m_pVirtualLayout;

    /** �Ƿ�����ӽ���״̬ͬ�����洢״̬
    */
    bool m_bEnableUpdateProvider;
};

/** ���򲼾ֵ����ListBox
*/
class UILIB_API VirtualHListBox : public VirtualListBox
{
public:
    VirtualHListBox() :
        VirtualListBox(new VirtualHLayout)
    {
        VirtualLayout* pVirtualLayout = dynamic_cast<VirtualHLayout*>(GetLayout());
        SetVirtualLayout(pVirtualLayout);
    }

    virtual std::wstring GetType() const override { return DUI_CTR_VIRTUAL_HLISTBOX; }
};

/** ���򲼾ֵ����ListBox
*/
class UILIB_API VirtualVListBox : public VirtualListBox
{
public:
    VirtualVListBox() :
        VirtualListBox(new VirtualVLayout)
    {
        VirtualLayout* pVirtualLayout = dynamic_cast<VirtualVLayout*>(GetLayout());
        SetVirtualLayout(pVirtualLayout);
    }

    virtual std::wstring GetType() const override { return DUI_CTR_VIRTUAL_VLISTBOX; }
};

/** ��Ƭ���ֵ����ListBox(���򲼾�)
*/
class UILIB_API VirtualHTileListBox : public VirtualListBox
{
public:
    VirtualHTileListBox() :
        VirtualListBox(new VirtualHTileLayout)
    {
        VirtualLayout* pVirtualLayout = dynamic_cast<VirtualHTileLayout*>(GetLayout());
        SetVirtualLayout(pVirtualLayout);
    }

    virtual std::wstring GetType() const override { return DUI_CTR_VIRTUAL_HTILE_LISTBOX; }
};

/** ��Ƭ���ֵ����ListBox(���򲼾�)
*/
class UILIB_API VirtualVTileListBox : public VirtualListBox
{
public:
    VirtualVTileListBox() :
        VirtualListBox(new VirtualVTileLayout)
    {
        VirtualLayout* pVirtualLayout = dynamic_cast<VirtualVTileLayout*>(GetLayout());
        SetVirtualLayout(pVirtualLayout);
    }

    virtual std::wstring GetType() const override { return DUI_CTR_VIRTUAL_VTILE_LISTBOX; }
};

}

#endif //UI_BOX_VIRTUAL_LISTBOX_H_
