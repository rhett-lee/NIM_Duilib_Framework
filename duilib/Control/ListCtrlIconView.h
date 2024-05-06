#ifndef UI_CONTROL_LIST_CTRL_ICON_VIEW_H_
#define UI_CONTROL_LIST_CTRL_ICON_VIEW_H_

#pragma once

#include "duilib/Control/ListCtrlDefs.h"

namespace ui
{
/** �б�������ʾ�Ͳ��ֹ���(Icon����)
*/
class ListCtrl;
class ListCtrlData;
class ListCtrlIconView : public ListCtrlView, public IListCtrlView
{
public:
    /** �����Ƿ�ΪListģʽ
    * @param [in] bListMode true��ʾ�б���ͼ������Ϊͼ����ͼ
    */
    explicit ListCtrlIconView(bool bListMode);
    virtual ~ListCtrlIconView();

    virtual std::wstring GetType() const override { return L"ListCtrlIconView"; }
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue);
    virtual void HandleEvent(const EventArgs& msg) override;

public:
    /** ����ListCtrl�ؼ��ӿ�
    */
    void SetListCtrl(ListCtrl* pListCtrl);

    /** �������ݴ������
    * @param[in] pProvider ���ݴ������
    */
    virtual void SetDataProvider(VirtualListBoxElement* pProvider) override;

public:
    /** ���ò��ַ���Ĭ������£�Icon��ͼ�����򲼾֣�List��ͼ�Ǻ��򲼾֣�
    * @param [in] bHorizontal true��ʾ���򲼾֣�false��ʾ���򲼾�
    */
    void SetHorizontalLayout(bool bHorizontal);

    /** �жϵ�ǰ���ַ����Ƿ�Ϊ���򲼾�
    */
    bool IsHorizontalLayout() const;

protected:
    /** ����һ��������
    * @return ���ش������������ָ��
    */
    virtual Control* CreateDataItem() override;

    /** ���ָ��������
    * @param [in] pControl ������ؼ�ָ��
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] itemData ����������е����ԣ�
    * @param [in] subItemList �����������ÿһ�е�����, ��1�����е�ID����2�����е����ݣ�
    */
    virtual bool FillDataItem(Control* pControl,
                              size_t nElementIndex,
                              const ListCtrlItemData& itemData,
                              const std::vector<ListCtrlSubItemData2Pair>& subItemList) override;


    /** ��ȡĳ�еĿ�����ֵ
    * @param [in] subItemList �����������ÿһ�е����ݣ�
    * @return ���ظ��п�ȵ����ֵ�����ص���DPI����Ӧ���ֵ�� ���ʧ�ܷ���-1
    */
    virtual int32_t GetMaxDataItemWidth(const std::vector<ListCtrlSubItemData2Ptr>& subItemList) override;

private:
    /** ListCtrl �ؼ��ӿ�
    */
    ListCtrl* m_pListCtrl;

    /** ���ݽӿ�
    */
    ListCtrlData* m_pData;

    /** �Ƿ�ΪListģʽ: true��ʾ�б���ͼ������Ϊͼ����ͼ 
    */
    const bool m_bListMode;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_ICON_VIEW_H_
