#ifndef UI_CONTROL_LIST_CTRL_DATA_PROVIDER_H_
#define UI_CONTROL_LIST_CTRL_DATA_PROVIDER_H_

#pragma once

#include "duilib/Box/VirtualListBox.h"
#include "duilib/Control/ListCtrlDefs.h"

namespace ui
{
/** �б�������ݹ�����
*/
class ListCtrl;
struct ListCtrlSubItemData;
class ListCtrlData : public ui::VirtualListBoxElement
{
public:
    //���ڴ洢�����ݽṹ
    typedef ListCtrlSubItemData2 Storage;
    typedef std::shared_ptr<Storage> StoragePtr;
    typedef std::vector<StoragePtr> StoragePtrList;
    typedef std::unordered_map<size_t, StoragePtrList> StorageMap;
    typedef std::vector<ListCtrlItemData> RowDataList;

public:
    ListCtrlData();

    /** ����һ��������
    * @return ���ش������������ָ��
    */
    virtual Control* CreateElement() override;

    /** ���ָ��������
    * @param [in] pControl ������ؼ�ָ��
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    */
    virtual bool FillElement(ui::Control* pControl, size_t nElementIndex) override;

    /** ��ȡ����������
    * @return ��������������
    */
    virtual size_t GetElementCount() const override;

    /** ����ѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] bSelected true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual void SetElementSelected(size_t nElementIndex, bool bSelected) override;

    /** ��ȡѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @return true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual bool IsElementSelected(size_t nElementIndex) const override;

    /** ��ȡѡ���Ԫ���б�
    * @param [in] selectedIndexs ���ص�ǰѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    */
    virtual void GetSelectedElements(std::vector<size_t>& selectedIndexs) const override;

    /** �Ƿ�֧�ֶ�ѡ
    */
    virtual bool IsMultiSelect() const override;

    /** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
    * @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
    */
    virtual void SetMultiSelect(bool bMultiSelect) override;

public:
    /** ������ͼ�ӿ�
    */
    void SetListView(IListCtrlView* pListView);

    /** �����Ƿ��Զ���ѡѡ���������(������Header��ÿ��)
    */
    void SetAutoCheckSelect(bool bAutoCheckSelect);

    /** ��ȡ�Ƿ��Զ���ѡѡ���������
    */
    bool IsAutoCheckSelect() const;

    /** ����Ĭ�ϵ��ı�����
    */
    void SetDefaultTextStyle(int32_t nTextStyle);

    /** ����Ĭ�ϵ��и�
    */
    void SetDefaultItemHeight(int32_t nItemHeight);

public:
    /** ����һ��, ��ˢ�½�����ʾ
    * @param [in] columnId �е�ID
    */
    bool AddColumn(size_t columnId);

    /** ɾ��һ��, ��ˢ�½�����ʾ
    * @param [in] columnId �е�ID
    */
    bool RemoveColumn(size_t columnId);

    /** ��ȡĳ�еĿ�����ֵ
    * @return ���ظ��п�ȵ����ֵ�����ص���DPI����Ӧ���ֵ�� ���ʧ�ܷ���-1
    */
    int32_t GetMaxColumnWidth(size_t columnId) const;

    /** ����һ�еĹ�ѡ״̬��Checked����UnChecked��
    * @param [in] columnId �е�ID
    * @param [in] bChecked true��ʾѡ��false��ʾȡ��ѡ��
    * @param [in] bRefresh �Ƿ�ˢ�½�����ʾ
    */
    bool SetColumnCheck(size_t columnId, bool bChecked, bool bRefresh);

    /** ��ȡ�������ܸ���
    */
    size_t GetDataItemCount() const;

    /** �����������ܸ���, ��ˢ�½�����ʾ
    * @param [in] itemCount �����������������ÿ������������ݣ�ͨ���ص��ķ�ʽ������䣨�ڲ�Ϊ���ʵ�֣�
    */
    bool SetDataItemCount(size_t itemCount);

    /** ��������һ��������, ��ˢ�½�����ʾ
    * @param [in] columnId �е�ID
    * @param [in] dataItem �����������
    * @return �ɹ�������������������ţ�ʧ���򷵻�Box::InvalidIndex
    */
    size_t AddDataItem(size_t columnId, const ListCtrlSubItemData& dataItem);

    /** ��ָ����λ�����һ��������, ��ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [in] dataItem �����������
    */
    bool InsertDataItem(size_t itemIndex, size_t columnId, const ListCtrlSubItemData& dataItem);

    /** ɾ��ָ���е�������, ��ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    */
    bool DeleteDataItem(size_t itemIndex);

    /** ɾ�������е�������, ��ˢ�½�����ʾ
    * @return ��������ݱ�ɾ������true�����򷵻�false
    */
    bool DeleteAllDataItems();

    /** ���������������������, ��ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] itemData ����������
    * @param [out] bChanged ���������Ƿ�仯
    * @param [out] bCheckChanged ����bCheck��־�Ƿ�仯
    */
    bool SetDataItemData(size_t itemIndex, const ListCtrlItemData& itemData, 
                         bool& bChanged, bool& bCheckChanged);

    /** ��ȡ�����������������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] itemData ����������
    */
    bool GetDataItemData(size_t itemIndex, ListCtrlItemData& itemData) const;

    /** ����������Ŀɼ���, ��ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bVisible �Ƿ�ɼ�
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemVisible(size_t itemIndex, bool bVisible, bool& bChanged);

    /** ��ȡ������Ŀɼ���
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ��������������Ŀɼ���
    */
    bool IsDataItemVisible(size_t itemIndex) const;

    /** �����������ѡ������, ��ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bSelected �Ƿ�ѡ��״̬
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemSelected(size_t itemIndex, bool bSelected, bool& bChanged);

    /** ��ȡ�������ѡ������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ���������������ѡ��״̬
    */
    bool IsDataItemSelected(size_t itemIndex) const;

    /** �������׵�ͼ��, ��ˢ�½��棬���ⲿ������ý���ˢ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] imageId ͼ����ԴId�����Ϊ-1��ʾ���ײ���ʾͼ��, ��ID��ImageList����
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemImageId(size_t itemIndex, int32_t imageId, bool& bChanged);

    /** ��ȡ���׵�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    int32_t GetDataItemImageId(size_t itemIndex) const;

    /** ��ȡѡ��״̬(bSelect)
    * @param [out] bSelected �Ƿ�ѡ��
    * @param [out] bPartSelected �Ƿ񲿷�ѡ��
    */
    void GetDataItemsSelectStatus(bool& bSelected, bool& bPartSelected) const;

    /** ����������Ĺ�ѡ���ԣ�ÿ��ǰ���CheckBox��, ��ˢ�½��棬���ⲿ������ý���ˢ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bChecked �Ƿ�ѡ״̬
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemChecked(size_t itemIndex, bool bChecked, bool& bChanged);

    /** ��ȡ�������ѡ�����ԣ�ÿ��ǰ���CheckBox��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ��������������Ĺ�ѡ״̬
    */
    bool IsDataItemChecked(size_t itemIndex) const;

    /** ���������еĹ�ѡ״̬��Checked����UnChecked��, ��ˢ�½�����ʾ
    * @param [in] bChecked true��ʾ��ѡ��false��ʾȡ����ѡ
    */
    bool SetAllDataItemsCheck(bool bChecked);

    /** �������ù�ѡ��������׵�CheckBox�򹴵����ݣ�, ��ˢ�½��棬���ⲿ������ý���ˢ��
    * @param [in] itemIndexs ��Ҫ���ù�ѡ�������������ţ���Ч��Χ��[0, GetDataItemCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SetCheckedDataItems(const std::vector<size_t>& itemIndexs,
                             bool bClearOthers,
                             std::vector<size_t>& refreshIndexs);

    /** ��ȡ��ѡ��Ԫ���б����׵�CheckBox�򹴵����ݣ�
    * @param [in] itemIndexs ���ص�ǰ��ѡ�������������ţ���Ч��Χ��[0, GetDataItemCount())
    */
    void GetCheckedDataItems(std::vector<size_t>& itemIndexs) const;

    /** ��ȡ��ѡ״̬(bChecked)
    * @param [out] bChecked �Ƿ�ѡ
    * @param [out] bPartChecked �Ƿ񲿷ֹ�ѡ
    */
    void GetDataItemsCheckStatus(bool& bChecked, bool& bPartChecked) const;

    /** ������������ö�״̬, ��ˢ�½��棬���ⲿ������ý���ˢ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] nAlwaysAtTop �ö�״̬��-1��ʾ���ö�, 0 ���� ������ʾ�ö�����ֵԽ�����ȼ�Խ�ߣ�������ʾ��������
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemAlwaysAtTop(size_t itemIndex, int8_t nAlwaysAtTop, bool& bChanged);

    /** ��ȡ��������ö�״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ����������������ö�״̬��-1��ʾ���ö�, 0 ���� ������ʾ�ö�����ֵԽ�����ȼ�Խ�ߣ�������ʾ��������
    */
    int8_t GetDataItemAlwaysAtTop(size_t itemIndex) const;

    /** ������������и�, ��ˢ�½��棬���ⲿ������ý���ˢ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] nItemHeight �и�, -1��ʾʹ��ListCtrl���õ�Ĭ���иߣ�����ֵ��ʾ���е������и�
    * @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    * @param [out] bChanged ���������Ƿ�仯
    */
    bool SetDataItemHeight(size_t itemIndex, int32_t nItemHeight, bool bNeedDpiScale, bool& bChanged);

    /** ��ȡ��������и�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ����������������и�, -1��ʾʹ��ListCtrl���õ�Ĭ���иߣ�����ֵ��ʾ���е������и�
    */
    int32_t GetDataItemHeight(size_t itemIndex) const;

    /** ������������Զ�������, ��ˢ�½���
    * @param [in] itemIndex �������������
    * @param [in] userData ������������Զ�������
    */
    bool SetDataItemUserData(size_t itemIndex, size_t userData);

    /** ��ȡ��������Զ�������
    * @param [in] itemIndex �������������
    * @return ����������������Զ�������
    */
    size_t GetDataItemUserData(size_t itemIndex) const;

public:
    /** ����ָ��<��,��>���������ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] subItemData ָ������������ݣ��������dataItem.nColumnIndex��ָ��
    * @param [out] bCheckChanged bChecked״̬�Ƿ�仯
    */
    bool SetSubItemData(size_t itemIndex, size_t columnId,
                        const ListCtrlSubItemData& subItemData, bool& bCheckChanged);

    /** ��ȡָ��<��,��>��������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [out] subItemData ָ�������������
    */
    bool GetSubItemData(size_t itemIndex, size_t columnId, ListCtrlSubItemData& subItemData) const;

    /** ����ָ����������ı�����ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [in] text ��Ҫ���õ��ı�����
    */
    bool SetSubItemText(size_t itemIndex, size_t columnId, const std::wstring& text);

    /** ��ȡָ����������ı�
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @return ������������ı�����
    */
    std::wstring GetSubItemText(size_t itemIndex, size_t columnId) const;

    /** ����ָ����������ı���ɫ����ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [in] textColor ��Ҫ���õ��ı���ɫ
    */
    bool SetSubItemTextColor(size_t itemIndex, size_t columnId, const UiColor& textColor);

    /** ��ȡָ����������ı���ɫ����ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [out] textColor ������������ı���ɫ
    */
    bool GetSubItemTextColor(size_t itemIndex, size_t columnId, UiColor& textColor) const;

    /** ����ָ����������ı����ԣ��ı����뷽ʽ�ȣ�����ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] nTextFormat ��Ҫ���õ��ı�����
    */
    bool SetSubItemTextFormat(size_t itemIndex, size_t columnId, int32_t nTextFormat);

    /** ��ȡָ����������ı����ԣ��ı����뷽ʽ�ȣ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @return ������������ı�����
    */
    int32_t GetSubItemTextFormat(size_t itemIndex, size_t columnId) const;

    /** ����ָ��������ı�����ɫ����ˢ�½�����ʾ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [in] bkColor ��Ҫ���õı�����ɫ
    */
    bool SetSubItemBkColor(size_t itemIndex, size_t columnId, const UiColor& bkColor);

    /** ��ȡָ��������ı�����ɫ
    * @param [in] itemIndex �������������
    * @param [in] columnId �е�ID
    * @param [out] bkColor ����������ı�����ɫ
    */
    bool GetSubItemBkColor(size_t itemIndex, size_t columnId, UiColor& bkColor) const;

    /** �Ƿ���ʾCheckBox
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    */
    bool IsSubItemShowCheckBox(size_t itemIndex, size_t columnId) const;

    /** �����Ƿ���ʾCheckBox����ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] bShowCheckBox true��ʾ��ʾ��false��ʾ����ʾ
    */
    bool SetSubItemShowCheckBox(size_t itemIndex, size_t columnId, bool bShowCheckBox);

    /** ����CheckBox�Ĺ�ѡ״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] bChecked true��ʾ��ѡ��false��ʾ����ѡ
    * @param [in] bRefresh true��ʾˢ�¸�Ԫ�صĽ�����ʾ��false��ʾ����Ҫˢ�½���
    */
    bool SetSubItemCheck(size_t itemIndex, size_t columnId, bool bChecked, bool bRefresh);

    /** ��ȡCheckBox�Ĺ�ѡ״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [out] bChecked true��ʾ��ѡ��false��ʾ����ѡ
    */
    bool GetSubItemCheck(size_t itemIndex, size_t columnId, bool& bChecked) const;

    /** ��ȡĳһ�еĹ�ѡ״̬(bChecked)
    * @param [in] columnId �е�ID
    * @param [out] bChecked �Ƿ�ѡ��
    * @param [out] bPartChecked �Ƿ񲿷�ѡ��
    */
    void GetColumnCheckStatus(size_t columnId, bool& bChecked, bool& bPartChecked) const;

    /** ���ø��е�ͼ�꣬��ˢ�½�����ʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] imageId ͼ����ԴId�����Ϊ-1��ʾ���ײ���ʾͼ��, ��ID��ImageList����
    */
    bool SetSubItemImageId(size_t itemIndex, size_t columnId, int32_t imageId);

    /** ��ȡ���е�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    */
    int32_t GetSubItemImageId(size_t itemIndex, size_t columnId) const;

    /** ���ø��е��ı��Ƿ�ɱ༭
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @param [in] bEditable true��ʾ�ɱ༭��false��ʾ���ɱ༭
    */
    bool SetSubItemEditable(size_t itemIndex, size_t columnId, bool bEditable);

    /** ��ȡ���е��ı��Ƿ�ɱ༭
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    */
    bool IsSubItemEditable(size_t itemIndex, size_t columnId) const;

    /** ���������򣬲�ˢ�½�����ʾ
    * @param [in] columnId �е�ID
    * @param [in] nColumnIndex �е����
    * @param [in] bSortedUp true��ʾ����false��ʾ����
    * @param [in] pfnCompareFunc ���ݱȽϺ���
    * @param [in] pUserData �û��Զ������ݣ����ñȽϺ�����ʱ��ͨ���������ظ��ȽϺ���
    */
    bool SortDataItems(size_t nColumnId, size_t nColumnIndex, bool bSortedUp,
                       ListCtrlDataCompareFunc pfnCompareFunc, void* pUserData);

    /** �����ⲿ�Զ����������, �滻Ĭ�ϵ�������
    * @param [in] pfnCompareFunc ���ݱȽϺ���
    * @param [in] pUserData �û��Զ������ݣ����ñȽϺ�����ʱ��ͨ���������ظ��ȽϺ���
    */
    void SetSortCompareFunction(ListCtrlDataCompareFunc pfnCompareFunc, void* pUserData);

public:
    /** ��������ѡ��Ԫ��, �����½�����ʾ
    * @param [in] selectedIndexs ��Ҫ����ѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SetSelectedElements(const std::vector<size_t>& selectedIndexs,
                             bool bClearOthers,
                             std::vector<size_t>& refreshIndexs);

    /** ѡ��ȫ��(�ų����ɼ�Ԫ�ء��ö�Ԫ��), �����½�����ʾ
    * @return ��������ݱ仯����true�����򷵻�false
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    bool SelectAll(std::vector<size_t>& refreshIndexs);

    /** ȡ������ѡ��, �����½�����ʾ���������ⲿˢ�½�����ʾ
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SelectNone(std::vector<size_t>& refreshIndexs);

    /** ȡ������ѡ��(���ų�����Ԫ��), �����½�����ʾ���������ⲿˢ�½�����ʾ
    * @param [in] excludeIndexs ��Ҫ�ų���Ԫ�������ţ��ⲿ��Ԫ�ص�ѡ��״̬����ԭ״
    * @param [out] refreshIndexs ������Ҫˢ����ʾ��Ԫ��������
    */
    void SelectNoneExclude(const std::vector<size_t>& excludeIndexs,
                           std::vector<size_t>& refreshIndexs);

    /** �ж�һ���������Ƿ��ѡ��
    */
    bool IsSelectableRowData(const ListCtrlItemData& rowData) const;

    /** �ж�һ������Ԫ���Ƿ�Ϊ��ѡ����
    * @param [in] nElementIndex Ԫ�������ţ���Ч��Χ��[0, GetElementCount())
    */
    bool IsSelectableElement(size_t nElementIndex) const;

private:
    /** ����ת��Ϊ�洢���ݽṹ
    */
    void SubItemToStorage(const ListCtrlSubItemData& item, Storage& storage) const;

    /** �洢����ת��Ϊ�ṹ����
    */
    void StorageToSubItem(const Storage& storage, ListCtrlSubItemData& item) const;

    /** �ж�һ�������������Ƿ���Ч
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    bool IsValidDataItemIndex(size_t itemIndex) const;

    /** �ж�һ����ID�����ݴ洢���Ƿ���Ч
    */
    bool IsValidDataColumnId(size_t nColumnId) const;

    /** ��ȡָ�������������, ��ȡ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @return ���ʧ���򷵻�nullptr
    */
    StoragePtr GetSubItemStorage(size_t itemIndex, size_t nColumnId) const;

    /** ��ȡָ�������������, д��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnId �е�ID
    * @return ���ʧ���򷵻�nullptr
    */
    StoragePtr GetSubItemStorageForWrite(size_t itemIndex, size_t nColumnId);

    /** ��ȡ�����е����ݣ�����UIչʾ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [out] subItemList ���ظ��������е������б�
    */
    bool GetSubItemStorageList(size_t itemIndex, std::vector<ListCtrlSubItemData2Pair>& subItemList) const;

public:
    /** ��ȡ����������
    */
    const RowDataList& GetItemDataList() const;

    /** �Ƿ�Ϊ��׼ģʽ���и߶�ΪĬ���иߣ��������У����ö��У�
    */
    bool IsNormalMode() const;

private:
    /** ��������
    */
    struct StorageData
    {
        size_t index;       //ԭ��������������
        StoragePtr pStorage;
    };

    /** ����������
    * @param [in] dataList �����������
    * @param [in] nColumnId �е�ID
    * @param [in] nColumnIndex �е����
    * @param [in] bSortedUp true��ʾ����false��ʾ����
    * @param [in] pfnCompareFunc ���ݱȽϺ���
    * @param [in] pUserData �û��Զ������ݣ����ñȽϺ�����ʱ��ͨ���������ظ��ȽϺ���
    */
    bool SortStorageData(std::vector<StorageData>& dataList,
                         size_t nColumnId, size_t nColumnIndex, bool bSortedUp,
                         ListCtrlDataCompareFunc pfnCompareFunc,
                         void* pUserData);

    /** Ĭ�ϵ����ݱȽϺ���
    * @param [in] a ��һ���Ƚ�����
    * @param [in] b �ڶ����Ƚ�����
    * @return ��� (a < b)������true�����򷵻�false
    */
    bool SortDataCompareFunc(const ListCtrlSubItemData2& a, const ListCtrlSubItemData2& b) const;

    /** ���¸��Ի����ݣ������С��иߡ��ö��ȣ�
    */
    void UpdateNormalMode();

private:
    /** ��ͼ�ؼ��ӿ�
    */
    IListCtrlView* m_pListView;

    /** �Ƿ��Զ���ѡѡ���������
    */
    bool m_bAutoCheckSelect;

    /** ���ݣ����б��棬ÿ����һ������
    */
    StorageMap m_dataMap;

    /** �е���������
    */
    RowDataList m_rowDataList;

    /** �ⲿ���õ�������
    */
    ListCtrlDataCompareFunc m_pfnCompareFunc;

    /** �ⲿ���õ���������������
    */
    void* m_pUserData;

    /** �����еĸ���
    */
    int32_t m_hideRowCount;

    /** ��Ĭ���и��еĸ���
    */
    int32_t m_heightRowCount;

    /** �ö��еĸ���
    */
    int32_t m_atTopRowCount;

    /** �Ƿ�֧�ֶ�ѡ
    */
    bool m_bMultiSelect;

    /** ��ѡ��ʱ��ѡ���Ԫ��������
    */
    size_t m_nSelectedIndex;

    /** ��ǰĬ�ϵ��ı�����
    */
    int32_t m_nDefaultTextStyle;

    /** ��ǰĬ�ϵ��и�
    */
    int32_t m_nDefaultItemHeight;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_DATA_PROVIDER_H_
