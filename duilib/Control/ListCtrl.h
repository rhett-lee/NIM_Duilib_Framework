#ifndef UI_CONTROL_LIST_CTRL_H_
#define UI_CONTROL_LIST_CTRL_H_

#pragma once

#include "duilib/Control/ListCtrlDefs.h"
#include "duilib/Control/ListCtrlHeader.h"
#include "duilib/Control/ListCtrlHeaderItem.h"
#include "duilib/Control/ListCtrlItem.h"
#include "duilib/Control/ListCtrlSubItem.h"
#include "duilib/Control/ListCtrlData.h"
#include "duilib/Core/ImageList.h"

namespace ui
{
/** ListCtrl�ؼ�
*/
class ListCtrl: public VBox
{
    friend class ListCtrlData;          //�б����ݹ�������
    friend class ListCtrlReportView;    //�б�������ʾUI�ؼ�
    friend class ListCtrlIconView;    //�б�������ʾUI�ؼ�
    friend class ListCtrlHeader;
    friend class ListCtrlHeaderItem;
    friend class ListCtrlItem;
    friend class ListCtrlSubItem;
    friend class ListCtrlIconViewItem;
    friend class ListCtrlListViewItem;
public:
	ListCtrl();
	virtual ~ListCtrl();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
    virtual void HandleEvent(const EventArgs& msg) override;

public:
    /** ���ñ�����ͣ�Ĭ��ΪReport���ͣ�
    */
    void SetListCtrlType(ListCtrlType type);

    /** ��ȡ�������
    */
    ListCtrlType GetListCtrlType() const;

    /** ����ͼƬ�б�ÿ����ͼ��һ��������ͼƬ�б�
    * @param [in] type ��ͼ����
    * @param [in] pImageList ͼƬ��Դ�ӿڣ����ú����ڲ�����������������
    */
    void SetImageList(ListCtrlType type, ImageList* pImageList);

    /** ��ȡͼƬ�б��������ͼƬ��Դ���������б�����ʾͼ����Դ
    */
    ImageList* GetImageList(ListCtrlType type);

    /** ��ȡͼƬ�б��������б�����ʾͼ����Դ
    */
    const ImageList* GetImageList(ListCtrlType type) const;

public:
    /** ��ȡ�еĸ���
    */
    size_t GetColumnCount() const;

    /** ��ָ��λ�����һ��
    * @param [in] columnIndex �ڵڼ����Ժ������У������-1����ʾ�����׷��һ��
    * @param [in] columnInfo �еĻ�������
    * @return ������һ�еı�ͷ�ؼ��ӿ�
    */
    ListCtrlHeaderItem* InsertColumn(int32_t columnIndex, const ListCtrlColumn& columnInfo);

    /** ��ȡ�п��
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    int32_t GetColumnWidth(size_t columnIndex) const;

    /** �����еĿ��(���ݸ������ݵ�ʵ�ʿ������Ӧ)
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    * @param [in] nWidth �п�ֵ
    * @param [in] bNeedDpiScale �Ƿ���Ҫ���п�ֵ����DPI����Ӧ
    */
    bool SetColumnWidth(size_t columnIndex, int32_t nWidth, bool bNeedDpiScale);

    /** �Զ������еĿ��(���ݸ������ݵ�ʵ�ʿ������Ӧ)
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    bool SetColumnWidthAuto(size_t columnIndex);

    /** ��ȡ�б�ͷ�Ŀؼ��ӿ�
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    ListCtrlHeaderItem* GetColumn(size_t columnIndex) const;

    /** ��ȡ�б�ͷ�Ŀؼ��ӿ�
    * @param [in] columnId �е�IDֵ��ͨ��ListCtrlHeaderItem::GetColomnId()������ȡ
    */
    ListCtrlHeaderItem* GetColumnById(size_t columnId) const;

    /** ��ȡ�е��������
    * @param [in] columnId �е�IDֵ��ͨ��ListCtrlHeaderItem::GetColomnId()������ȡ
    * @return �е���ţ�[0, GetColumnCount())������ڼ���
    */
    size_t GetColumnIndex(size_t columnId) const;

    /** ��ȡ�е�ID
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    size_t GetColumnId(size_t columnIndex) const;

    /** ɾ��һ��
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    bool DeleteColumn(size_t columnIndex);

    /** ��ȡ��ͷ�ؼ��ӿ�, �ڿؼ���ʼ���Ժ����ֵ
    */
    ListCtrlHeader* GetHeaderCtrl() const;

    /** �����Ƿ�֧���б�ͷ�϶��ı��е�˳��
    */
    void SetEnableHeaderDragOrder(bool bEnable);

    /** �Ƿ�֧���б�ͷ�϶��ı��е�˳��
    */
    bool IsEnableHeaderDragOrder() const;

    /** �����Ƿ���ʾ��ͷ�ؼ�
    */
    void SetHeaderVisible(bool bVisible);

    /** ��ǰ�Ƿ���ʾ��ͷ�ؼ�
    */
    bool IsHeaderVisible() const;

    /** ���ñ�ͷ�ؼ��ĸ߶�
    * @param[in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    */
    void SetHeaderHeight(int32_t nHeaderHeight, bool bNeedDpiScale);

    /** ��ȡ��ͷ�ؼ��ĸ߶�
    */
    int32_t GetHeaderHeight() const;

public:
    /** ��ȡ�������ܸ���
    */
    size_t GetDataItemCount() const;

    /** �����������ܸ���(��Ӧ����)
    * @param [in] itemCount �����������
    */
    bool SetDataItemCount(size_t itemCount);

    /** ��������һ��������(����+1), ���ݹ�������һ�У������Ϊ0��
    * @param [in] dataItem �����������
    * @return �ɹ�������������ţ���Ч��Χ��[0, GetDataItemCount()); ʧ���򷵻�Box::InvalidIndex
    */
    size_t AddDataItem(const ListCtrlSubItemData& dataItem);

    /** ��ָ����λ�����һ��������(����+1)
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] dataItem �����������
    */
    bool InsertDataItem(size_t itemIndex, const ListCtrlSubItemData& dataItem);

    /** ɾ��ָ���е�������(����-1)
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    bool DeleteDataItem(size_t itemIndex);

    /** ɾ�������е�������(����Ϊ0)
    */
    bool DeleteAllDataItems();

    /** �����������Ĭ�ϸ߶�(�и�)
    * @param [in] nItemHeight �߶�ֵ
    * @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    */
    void SetDataItemHeight(int32_t nItemHeight, bool bNeedDpiScale);

    /** ��ȡ�������Ĭ�ϸ߶�(�и�)
    */
    int32_t GetDataItemHeight() const;

public:
    /** ���������������������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] itemData ����������
    */
    bool SetDataItemData(size_t itemIndex, const ListCtrlItemData& itemData);

    /** ��ȡ�����������������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] itemData ����������
    */
    bool GetDataItemData(size_t itemIndex, ListCtrlItemData& itemData) const;

    /** ����������Ŀɼ���
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bVisible �Ƿ�ɼ�
    */
    bool SetDataItemVisible(size_t itemIndex, bool bVisible);

    /** ��ȡ������Ŀɼ���
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ��������������Ŀɼ���
    */
    bool IsDataItemVisible(size_t itemIndex) const;

    /** �����������ѡ������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bSelected �Ƿ�ѡ��״̬
    */
    bool SetDataItemSelected(size_t itemIndex, bool bSelected);

    /** ��ȡ�������ѡ������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ���������������ѡ��״̬
    */
    bool IsDataItemSelected(size_t itemIndex) const;

    /** �������׵�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] imageId ͼ����ԴId�����Ϊ-1��ʾ���ײ���ʾͼ��, ��ID��ImageList����
    */
    bool SetDataItemImageId(size_t itemIndex, int32_t imageId);

    /** ��ȡ���׵�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    int32_t GetDataItemImageId(size_t itemIndex) const;

    /** ������������ö�״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] nAlwaysAtTop �ö�״̬��-1��ʾ���ö�, 0 ���� ������ʾ�ö�����ֵԽ�����ȼ�Խ�ߣ�������ʾ��������
    */
    bool SetDataItemAlwaysAtTop(size_t itemIndex, int8_t nAlwaysAtTop);

    /** ��ȡ��������ö�״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ����������������ö�״̬��-1��ʾ���ö�, 0 ���� ������ʾ�ö�����ֵԽ�����ȼ�Խ�ߣ�������ʾ��������
    */
    int8_t GetDataItemAlwaysAtTop(size_t itemIndex) const;

    /** ������������и�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] nItemHeight �и�, -1��ʾʹ��ListCtrl���õ�Ĭ���иߣ�����ֵ��ʾ���е������и�
    * @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    */
    bool SetDataItemHeight(size_t itemIndex, int32_t nItemHeight, bool bNeedDpiScale);

    /** ��ȡ��������и�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ����������������и�, -1��ʾʹ��ListCtrl���õ�Ĭ���иߣ�����ֵ��ʾ���е������и�
    */
    int32_t GetDataItemHeight(size_t itemIndex) const;

    /** ������������Զ�������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] userData ������������Զ�������
    */
    bool SetDataItemUserData(size_t itemIndex, size_t userData);

    /** ��ȡ��������Զ�������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ����������������Զ�������
    */
    size_t GetDataItemUserData(size_t itemIndex) const;

public:
    /** ����ָ��<��,��>��������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] subItemData ָ������������ݣ��������dataItem.nColumnIndex��ָ��
    */
    bool SetSubItemData(size_t itemIndex, size_t columnIndex, const ListCtrlSubItemData& subItemData);

    /** ��ȡָ��<��,��>��������
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [out] subItemData ָ�������������
    */
    bool GetSubItemData(size_t itemIndex, size_t columnIndex, ListCtrlSubItemData& subItemData) const;

    /** ����ָ����������ı�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] text ��Ҫ���õ��ı�����
    */
    bool SetSubItemText(size_t itemIndex, size_t columnIndex, const std::wstring& text);

    /** ��ȡָ����������ı�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @return ������������ı�����
    */
    std::wstring GetSubItemText(size_t itemIndex, size_t columnIndex) const;

    /** ����ָ����������ı���ɫ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] textColor ��Ҫ���õ��ı���ɫ
    */
    bool SetSubItemTextColor(size_t itemIndex, size_t columnIndex, const UiColor& textColor);

    /** ��ȡָ����������ı���ɫ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    UiColor GetSubItemTextColor(size_t itemIndex, size_t columnIndex) const;

    /** ����ָ����������ı����ԣ��ı����뷽ʽ�ȣ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] nTextFormat ��Ҫ���õ��ı�����
    */
    bool SetSubItemTextFormat(size_t itemIndex, size_t columnIndex, int32_t nTextFormat);

    /** ��ȡָ����������ı����ԣ��ı����뷽ʽ�ȣ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @return ������������ı�����
    */
    int32_t GetSubItemTextFormat(size_t itemIndex, size_t columnIndex) const;

    /** ����ָ��������ı�����ɫ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] bkColor ��Ҫ���õı�����ɫ
    */
    bool SetSubItemBkColor(size_t itemIndex, size_t columnIndex, const UiColor& bkColor);

    /** ��ȡָ��������ı�����ɫ
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    UiColor GetSubItemBkColor(size_t itemIndex, size_t columnIndex) const;

    /** �Ƿ���ʾCheckBox
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    bool IsSubItemShowCheckBox(size_t itemIndex, size_t columnIndex) const;

    /** �����Ƿ���ʾCheckBox
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] bShowCheckBox true��ʾ��ʾ��false��ʾ����ʾ
    */
    bool SetSubItemShowCheckBox(size_t itemIndex, size_t columnIndex, bool bShowCheckBox);

    /** ����CheckBox�Ĺ�ѡ״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] bChecked true��ʾ��ѡ��false��ʾ����ѡ
    */
    bool SetSubItemCheck(size_t itemIndex, size_t columnIndex, bool bChecked);

    /** ��ȡCheckBox�Ĺ�ѡ״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    bool IsSubItemChecked(size_t itemIndex, size_t columnIndex) const;

    /** ���ø��е�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] imageId ͼ����ԴId�����Ϊ-1��ʾ���ײ���ʾͼ��, ��ID��ImageList����
    */
    bool SetSubItemImageId(size_t itemIndex, size_t columnIndex, int32_t imageId);

    /** ��ȡ���е�ͼ��
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    int32_t GetSubItemImageId(size_t itemIndex, size_t columnIndex) const;

    /** ���ø��е��ı��Ƿ�ɱ༭
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] bEditable true��ʾ�ɱ༭��false��ʾ���ɱ༭
    */
    bool SetSubItemEditable(size_t itemIndex, size_t columnIndex, bool bEditable);

    /** ��ȡ���е��ı��Ƿ�ɱ༭
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    */
    bool IsSubItemEditable(size_t itemIndex, size_t columnIndex) const;

public:
    /** ����������
    * @param [in] columnIndex �е������ţ���Ч��Χ��[0, GetColumnCount())
    * @param [in] bSortedUp true��ʾ����false��ʾ����
    * @param [in] pfnCompareFunc �Զ���ıȽϺ��������Ϊnullptr, ��ʹ��Ĭ�ϵıȽϺ���
    * @param [in] pUserData �û��Զ������ݣ����ñȽϺ�����ʱ��ͨ���������ظ��ȽϺ���
    */
    bool SortDataItems(size_t columnIndex, bool bSortedUp, 
                       ListCtrlDataCompareFunc pfnCompareFunc = nullptr,
                       void* pUserData = nullptr);

    /** �����ⲿ�Զ����������, �滻Ĭ�ϵ�������
    * @param [in] pfnCompareFunc ���ݱȽϺ���
    * @param [in] pUserData �û��Զ������ݣ����ñȽϺ�����ʱ��ͨ���������ظ��ȽϺ���
    */
    void SetSortCompareFunction(ListCtrlDataCompareFunc pfnCompareFunc, void* pUserData);

public:
    /** �Ƿ�֧�ֶ�ѡ
    */
    bool IsMultiSelect() const;

    /** �����Ƿ�֧�ֶ�ѡ
    */
    void SetMultiSelect(bool bMultiSelect);

    /** ��������ѡ��������
    * @param [in] selectedIndexs ��Ҫ����ѡ��������������ţ���Ч��Χ��[0, GetDataItemCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    */
    void SetSelectedDataItems(const std::vector<size_t>& selectedIndexs, bool bClearOthers);

    /** ��ȡѡ���Ԫ���б�
    * @param [in] itemIndexs ���ص�ǰѡ��������������ţ���Ч��Χ��[0, GetDataItemCount())
    */
    void GetSelectedDataItems(std::vector<size_t>& itemIndexs) const;

    /** ѡ��ȫ��
    */
    void SetSelectAll();

    /** ȡ������ѡ��
    */
    void SetSelectNone();

public:
    /** ��ȡ��ǰ��ʾ���������б�˳���Ǵ��ϵ���
    * @param [in] itemIndexList ��ǰ��ʾ���������������б�, ÿһԪ�صĵ���Ч��Χ��[0, GetDataItemCount())
    */
    void GetDisplayDataItems(std::vector<size_t>& itemIndexList) const;

    /** �õ��ɼ���Χ�ڵ�һ���������������
    * @return ����������������ţ� ��Ч��Χ��[0, GetDataItemCount())
    */
    size_t GetTopDataItem() const;

    /** �ж�һ���������Ƿ�ɼ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    bool IsDataItemDisplay(size_t itemIndex) const;

    /** ȷ������������ɼ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bToTop �Ƿ�ȷ�������Ϸ�
    */
    bool EnsureDataItemVisible(size_t itemIndex, bool bToTop);

    /** ˢ�½��棬������������ʾͬ��
    */
    void Refresh();

    /** ˢ��ָ��������
    * @param [in] dataItemIndexs ��Ҫˢ�µ�������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    void RefreshDataItems(std::vector<size_t> dataItemIndexs);

    /** �Ƿ�����ˢ�½���
    * @param [in] bEnable ���Ϊtrue������ͨ��Refresh()����ˢ�½���; ���Ϊfalse��������ͨ��Refresh()����ˢ�½���
    * @return ���ؾɵ�IsEnableRefresh()״̬
    */
    bool SetEnableRefresh(bool bEnable);

    /** �ж��Ƿ�����ˢ�½���
    */
    bool IsEnableRefresh() const;

public:
    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Report��ͼ��
    * @return ���ؽ���ؼ��ӿ�
              ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlItem* GetFirstDisplayItem() const;

    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Report��ͼ��
    * @param [in] pItem ��ǰ����ؼ��ӿ�
    * @return ���ص�ǰ����ؼ�����һ������ؼ��ӿڣ������ǰ�Ѿ������һ��������nullptr
    *         ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlItem* GetNextDisplayItem(ListCtrlItem* pItem) const;

public:
    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Icon��ͼ��
    * @return ���ؽ���ؼ��ӿ�
              ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlIconViewItem* GetFirstDisplayIconItem() const;

    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Icon��ͼ��
    * @param [in] pItem ��ǰ����ؼ��ӿ�
    * @return ���ص�ǰ����ؼ�����һ������ؼ��ӿڣ������ǰ�Ѿ������һ��������nullptr
    *         ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlIconViewItem* GetNextDisplayIconItem(ListCtrlIconViewItem* pItem) const;

    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Icon��ͼ��
    * @return ���ؽ���ؼ��ӿ�
              ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlListViewItem* GetFirstDisplayListItem() const;

    /** ��ȡ��һ��������Ľ���ؼ��ӿڣ�Icon��ͼ��
    * @param [in] pItem ��ǰ����ؼ��ӿ�
    * @return ���ص�ǰ����ؼ�����һ������ؼ��ӿڣ������ǰ�Ѿ������һ��������nullptr
    *         ע���������ˢ�º󣬽���ؼ�������Ԫ��֮��Ĺ�ϵ�ᶯ̬�仯
    */
    ListCtrlListViewItem* GetNextDisplayListItem(ListCtrlListViewItem* pItem) const;

    /** �����Ƿ�֧������༭
    */
    void SetEnableItemEdit(bool bEnableItemEdit);

    /** �ж��Ƿ�֧������༭
    */
    bool IsEnableItemEdit() const;

    /** ��ȡ�༭��ؼ��Ľӿ�(ֻ��ִ�б༭�����Ժ󣬲���ֵ)
    */
    RichEdit* GetRichEdit() const;

public:
    /** @name CheckBox���м�����������
    * @{ */

    /** �����Ƿ��Զ���ѡѡ���������(������Header��ÿ��)
    */
    void SetAutoCheckSelect(bool bAutoCheckSelect);

    /** ��ȡ�Ƿ��Զ���ѡѡ���������
    */
    bool IsAutoCheckSelect() const;

    /** �����Ƿ��ڱ�ͷ�������ʾCheckBox
    * @param [in] bShow true��ʾ��ʾCheckBox��false��ʾ����ʾ
    */
    bool SetHeaderShowCheckBox(bool bShow);

    /** �ж��Ƿ���ÿ��������ʾCheckBox
    */
    bool IsHeaderShowCheckBox() const;

    /** �����Ƿ���ÿ��������ʾCheckBox
    * @param [in] bShow true��ʾ��ʾCheckBox��false��ʾ����ʾ
    */
    void SetDataItemShowCheckBox(bool bShow);

    /** �ж��Ƿ���ÿ��������ʾCheckBox
    */
    bool IsDataItemShowCheckBox() const;

    /** ����������Ĺ�ѡ����
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] bCheck �Ƿ�ѡ״̬
    */
    bool SetDataItemCheck(size_t itemIndex, bool bCheck);

    /** ��ȡ������Ĺ�ѡ����
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @return ��������������Ĺ�ѡ״̬
    */
    bool IsDataItemCheck(size_t itemIndex) const;

    /** �������ù�ѡ��������׵�CheckBox�򹴵����ݣ�
    * @param [in] itemIndexs ��Ҫ���ù�ѡ�������������ţ���Ч��Χ��[0, GetDataItemCount())
    * @param [in] bClearOthers ���Ϊtrue����ʾ��������ѡ��Ľ������ѡ��ֻ�����������õ�Ϊѡ����
    */
    void SetCheckedDataItems(const std::vector<size_t>& itemIndexs, bool bClearOthers);

    /** ��ȡ��ѡ��Ԫ���б����׵�CheckBox�򹴵����ݣ�
    * @param [in] itemIndexs ���ص�ǰ��ѡ�������������ţ���Ч��Χ��[0, GetDataItemCount())
    */
    void GetCheckedDataItems(std::vector<size_t>& itemIndexs) const;

    /** @} */

public:
    /** ���������ߵĿ��
    * @param [in] nLineWidth �����ߵĿ�ȣ����Ϊ0��ʾ����ʾ����������
    * @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    */
    void SetRowGridLineWidth(int32_t nLineWidth, bool bNeedDpiScale);
    int32_t GetRowGridLineWidth() const;

    /** ���������ߵ���ɫ
    * @param [in] color ���������ߵ���ɫ
    */
    void SetRowGridLineColor(const std::wstring& color);
    std::wstring GetRowGridLineColor() const;

    /** ���������ߵĿ��
    * @param [in] nLineWidth �����ߵĿ�ȣ����Ϊ0��ʾ����ʾ����������
    * @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
    */
    void SetColumnGridLineWidth(int32_t nLineWidth, bool bNeedDpiScale);
    int32_t GetColumnGridLineWidth() const;

    /** ���������ߵ���ɫ
    * @param [in] color ���������ߵ���ɫ
    */
    void SetColumnGridLineColor(const std::wstring& color);
    std::wstring GetColumnGridLineColor() const;

    /** �Ƿ�֧��˫��Header�ķָ����Զ������п�
    */
    void SetEnableColumnWidthAuto(bool bEnable);
    bool IsEnableColumnWidthAuto() const;

public:
    /** ����ѡ��������¼�
     * @param[in] callback ѡ������ʱ�Ļص�����
     * ����˵��:
     *   wParam: ѡ������Ľ���ؼ��ӿ�ָ�룬����Ϊ��ListCtrlItem*
     *	 lParam: ѡ��������������ţ���Ч��Χ��[0, GetDataItemCount())
     */
    void AttachSelect(const EventCallback& callback) { AttachEvent(kEventSelect, callback); }

    /** ����ѡ������仯���¼�
     * @param[in] callback ѡ������ʱ�Ļص�����
     */
    void AttachSelChange(const EventCallback& callback) { AttachEvent(kEventSelChange, callback); }

    /** ����˫���¼�
     * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
     * ����˵��:
     *   wParam: ���������Ľ���ؼ��ӿ�ָ�룬����Ϊ��ListCtrlItem*�����δ��������Ϊ0
     *	 lParam: �����������������ţ���Ч��Χ��[0, GetDataItemCount()), ����wParam��Ϊ0ʱ��Ч
     */
    void AttachDoubleClick(const EventCallback& callback) { AttachEvent(kEventMouseDoubleClick, callback); }

    /** �������������
     * @param[in] callback Ҫ�󶨵Ļص�����
     * ����˵��:
     *   wParam: ���������Ľ���ؼ��ӿ�ָ�룬����Ϊ��ListCtrlItem*�����δ��������Ϊ0
     *	 lParam: �����������������ţ���Ч��Χ��[0, GetDataItemCount()), ����wParam��Ϊ0ʱ��Ч
     */
    void AttachClick(const EventCallback& callback) { AttachEvent(kEventClick, callback); }

    /** ������Ҽ����������
     * @param[in] callback Ҫ�󶨵Ļص�����
     *  ����˵��:
     *   wParam: ���������Ľ���ؼ��ӿ�ָ�룬����Ϊ��ListCtrlItem*�����δ��������Ϊ0
     *	 lParam: �����������������ţ���Ч��Χ��[0, GetDataItemCount()), ����wParam��Ϊ0ʱ��Ч
     */
    void AttachRClick(const EventCallback& callback) { AttachEvent(kEventRClick, callback); }

    /** �����س��¼�
     * @param[in] callback �յ��س�ʱ�Ļص�����
      * ����˵��:
     *   wParam: ����������Ľ���ؼ��ӿ�ָ�룬����Ϊ��ListCtrlItem*�����δ��������Ϊ0
     *	 lParam: �����������������ţ���Ч��Χ��[0, GetDataItemCount())
     */
    void AttachReturn(const EventCallback& callback) { this->AttachEvent(kEventReturn, callback); }

    /** ������ʼ�༭�¼�
     * @param[in] callback �¼��ص�����
      * ����˵��:
     *   wParam: �ǽӿ�ָ�룺ListCtrlEditParam*������ͨ������bCancelledȡ������
     */
    void AttachEnterEdit(const EventCallback& callback) { this->AttachEvent(kEventEnterEdit, callback); }

    /** ���������༭�¼�
     * @param[in] callback �¼��ص�����
      * ����˵��:
     *   wParam: �ǽӿ�ָ�룺ListCtrlEditParam*������ͨ������bCancelledȡ������
     */
    void AttachLeaveEdit(const EventCallback& callback) { this->AttachEvent(kEventLeaveEdit, callback); }

protected:
    /** �ؼ���ʼ��
    */
    virtual void OnInit() override;

    /** ��ʼ��Report��ͼ
    */
    void InitReportView();

    /** ��ʼ��Icon��ͼ
    */
    void InitIconView();

    /** ��ʼ��List��ͼ
    */
    void InitListView();

    /** ����ListCtrlHeader������Class
    */
    void SetHeaderClass(const std::wstring& className);

    /** ListCtrlHeaderItem������Class
    */
    void SetHeaderItemClass(const std::wstring& className);
    std::wstring GetHeaderItemClass() const;

    /** ListCtrlHeader/SplitBox������Class
    */
    void SetHeaderSplitBoxClass(const std::wstring& className);
    std::wstring GetHeaderSplitBoxClass() const;

    /** ListCtrlHeader/SplitBox/Control������Class
    */
    void SetHeaderSplitControlClass(const std::wstring& className);
    std::wstring GetHeaderSplitControlClass() const;

    /** CheckBox��Class����(Ӧ����Header��ListCtrl����)
    */
    void SetCheckBoxClass(const std::wstring& className);
    std::wstring GetCheckBoxClass() const;

    /** ����Report��ͼ�е�ListBox��Class����
    */
    void SetReportViewClass(const std::wstring& className);
    std::wstring GetReportViewClass() const;

    /** ListCtrlItem��Class����
    */
    void SetDataItemClass(const std::wstring& className);
    std::wstring GetDataItemClass() const;

    /** ListCtrlItem/ListCtrlSubItem��Class����
    */
    void SetDataSubItemClass(const std::wstring& className);
    std::wstring GetDataSubItemClass() const;

    /** ����Icon��ͼ�е�ListBox��Class����
    */
    void SetIconViewClass(const std::wstring& className);
    std::wstring GetIconViewClass() const;

    /** ����Icon��ͼ�е�ListBox������Class����
    */
    void SetIconViewItemClass(const std::wstring& className);
    std::wstring GetIconViewItemClass() const;

    /** ����Icon��ͼ�е�ListBox��������ͼƬ��Class����
    */
    void SetIconViewItemImageClass(const std::wstring& className);
    std::wstring GetIconViewItemImageClass() const;

    /** ����Icon��ͼ�е�ListBox��������Label��Class����
    */
    void SetIconViewItemLabelClass(const std::wstring& className);
    std::wstring GetIconViewItemLabelClass() const;

    /** ����List��ͼ�е�ListBox��Class����
    */
    void SetListViewClass(const std::wstring& className);
    std::wstring GetListViewClass() const;

    /** ����List��ͼ�е�ListBox������Class����
    */
    void SetListViewItemClass(const std::wstring& className);
    std::wstring GetListViewItemClass() const;

    /** ����List��ͼ�е�ListBox�������ͼƬ��Class����
    */
    void SetListViewItemImageClass(const std::wstring& className);
    std::wstring GetListViewItemImageClass() const;

    /** ����List��ͼ�е�ListBox�������Label��Class����
    */
    void SetListViewItemLabelClass(const std::wstring& className);
    std::wstring GetListViewItemLabelClass() const;

    /** �༭���Class����
    */
    void SetRichEditClass(const std::wstring& richEditClass);
    std::wstring GetRichEditClass() const;

protected:
    /** ����һ��
    * @param [in] nColumnId �е�ID
    */
    void OnHeaderColumnAdded(size_t nColumnId);

    /** ɾ��һ��
    * @param [in] nColumnId �е�ID
    */
    void OnHeaderColumnRemoved(size_t nColumnId);

    /** �����еĿ�ȣ��϶��п������ÿ�ε��������еĿ�ȣ�
    * @param [in] nColumnId1 ��һ�е�ID
    * @param [in] nColumnId2 �ڶ��е�ID
    */
    void OnColumnWidthChanged(size_t nColumnId1, size_t nColumnId2);

    /** ��������
    * @param [in] nColumnId �е�ID
    * @param [in] bSortedUp ���Ϊtrue��ʾ�������Ϊfalse��ʾ����
    */
    void OnColumnSorted(size_t nColumnId, bool bSortedUp);

    /** ͨ���϶��б�ͷ���������е�˳��
    */
    void OnHeaderColumnOrderChanged();

    /** ��ͷ��CheckBox��ѡ����(�м�)
    * @param [in] nColumnId �е�ID
    * @param [in] bChecked true��ʾ��ѡ��Checked״̬����false��ʾȡ����ѡ��UnChecked״̬��
    */
    void OnHeaderColumnCheckStateChanged(size_t nColumnId, bool bChecked);

    /** ��ͷ��CheckBox��ѡ����(�м�)
    * @param [in] bChecked true��ʾ��ѡ��Checked״̬����false��ʾȡ����ѡ��UnChecked״̬��
    */
    void OnHeaderCheckStateChanged(bool bChecked);

    /** ��ͷ�е���ʾ���Է����仯
    */
    void OnHeaderColumnVisibleChanged();

    /** �б�ͷ�еķָ���˫���¼�
    * @param [in] pHeaderItem �б�ͷ�ؼ��ӿ�
    */
    void OnHeaderColumnSplitDoubleClick(ListCtrlHeaderItem* pHeaderItem);

    /** ͬ��UI��Check״̬(�м����CheckBox)
    * @param [in] nColumnId ��ID, ���ΪBox::InvalidIndex��ʾ����������
    */
    void UpdateHeaderColumnCheckBox(size_t nColumnId);

    /** ͬ��UI��Check״̬(�м����CheckBox)
    */
    void UpdateHeaderCheckBox();

private:
    /** ����༭״̬
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    * @param [in] nColumnId �е�ID
    * @param [in] pItem �б���Ľӿ�
    * @param [in] pSubItem �б�������Ľӿ�
    */
    void OnItemEnterEditMode(size_t itemIndex, size_t nColumnId,
                             IListBoxItem* pItem, ListCtrlLabel* pSubItem);

    /** ����༭״̬�Ķ�ʱ��ȡ������
    */
    nbase::WeakCallbackFlag m_editModeFlag;

    /** �Ӷ�ʱ������༭״̬
    */
    void OnItemEditMode(ListCtrlEditParam editParam);

    /** У��༭״̬������������Ƿ���Ч
    */
    bool IsValidItemEditParam(const ListCtrlEditParam& editParam) const;

    /** У���Ƿ�����ɱ༭״̬
    */
    bool IsValidItemEditState(const ListCtrlEditParam& editParam) const;

    /** ����RichEdit�ؼ���λ�úʹ�С
    */
    void UpdateRichEditSize(ListCtrlLabel* pSubItem);

    /** ����༭�¼�
    */
    void OnItemEdited(const ListCtrlEditParam& editParam, const std::wstring& newItemText);

    /** ��ͼ���յ������Ϣ
    */
    void OnViewMouseEvents(const EventArgs& msg);

    /** ��ͼ���յ������Ϣ
    */
    void OnViewKeyboardEvents(const EventArgs& msg);

    /** �����༭״̬
    */
    void LeaveEditMode();

    /** ������б༭״̬���¼�����
    */
    void ClearEditEvents();

private:
    /** ������ͣ�Ĭ��ΪReport���ͣ�
    */
    ListCtrlType m_listCtrlType;

	/** ��ͷ�ؼ�
	*/
	ListCtrlHeader* m_pHeaderCtrl;

	/** �б�����չʾ(Report��ͼ)
	*/
    ListCtrlReportView* m_pReportView;

    /** �б�����չʾ(Icon��ͼ)
    */
    ListCtrlIconView* m_pIconView;

    /** �б�����չʾ(List��ͼ)
    */
    ListCtrlIconView* m_pListView;

	/** �б����ݹ���
	*/
    ListCtrlData* m_pData;

    /** ListCtrlHeader������Class
    */
    UiString m_headerClass;

    /** ListCtrlHeaderItem������Class
    */
    UiString m_headerItemClass;

    /** ListCtrlHeader/SplitBox������Class
    */
    UiString m_headerSplitBoxClass;

    /** ListCtrlHeader/SplitBox/Control������Class
    */
    UiString m_headerSplitControlClass;

    /** CheckBox��Class
    */
    UiString m_checkBoxClass;

    /** �Ƿ�֧���϶��ı��е�˳��
    */
    bool m_bEnableHeaderDragOrder;

    /** ListCtrlItem��Class����
    */
    UiString m_dataItemClass;

    /** ListCtrlItem/ListCtrlSubItem��Class����
    */
    UiString m_dataSubItemClass;

    /** ListBox��Report��ͼClass����
    */
    UiString m_reportViewClass;

    /** ListBox��Icon��ͼClass����(Icon��ͼ)
    */
    UiString m_iconViewClass;

    /** ListBox��Icon��ͼ����Class����(Icon��ͼ)
    */
    UiString m_iconViewItemClass;

    /** ListBox��Icon��ͼͼ������Class����(Icon��ͼ)
    */
    UiString m_iconViewItemImageClass;

    /** ListBox��Icon��ͼ�ı�����Class����(Icon��ͼ)
    */
    UiString m_iconViewItemLabelClass;

    /** ListBox��List��ͼClass����(List��ͼ)
    */
    UiString m_listViewClass;

    /** ListBox��List��ͼClass����(List��ͼ)
    */
    UiString m_listViewItemClass;

    /** ListBox��List��ͼͼ������Class����(List��ͼ)
    */
    UiString m_listViewItemImageClass;

    /** ListBox��List��ͼ�ı�����Class����(List��ͼ)
    */
    UiString m_listViewItemLabelClass;

    /** ListCtrl�ı༭��Class����
    */
    UiString m_listCtrlRichEditClass;

    /** ��ͷ�ĸ߶�
    */
    int32_t m_nHeaderHeight;

    /** �Ƿ���ʾ��ͷ�ؼ�
    */
    bool m_bShowHeaderCtrl;

    /** ������ĸ߶�
    */
    int32_t m_nItemHeight;

    /** �Ƿ�����ˢ�½���
    */
    bool m_bEnableRefresh;

    /** �Ƿ�֧�ֶ�ѡ(Ĭ���ǵ�ѡ)
    */
    bool m_bMultiSelect;

    /** �Ƿ�֧��˫��Header�ķָ����Զ������п�
    */
    bool m_bEnableColumnWidthAuto;

    /** �Ƿ��Զ���ѡѡ����������Windows��ListCtrl��LVS_EX_AUTOCHECKSELECT�������ƣ�
    */
    bool m_bAutoCheckSelect;

    /** �Ƿ���ʾHeader��CheckBox���м���
    */
    bool m_bHeaderShowCheckBox;

    /** �Ƿ���ʾ�������CheckBox���м���
    */
    bool m_bDataItemShowCheckBox;

    /** ͼƬ�б�
    */
    ImageList* m_imageList[3];

    /** �༭��ؼ�
    */
    RichEdit* m_pRichEdit;

    /** �Ƿ�֧������༭
    */
    bool m_bEnableItemEdit;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_H_
