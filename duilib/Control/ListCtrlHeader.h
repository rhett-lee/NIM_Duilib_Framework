#ifndef UI_CONTROL_LIST_CTRL_HEADER_H_
#define UI_CONTROL_LIST_CTRL_HEADER_H_

#pragma once

#include "duilib/Box/ListBoxItem.h"

namespace ui
{

/** ListCtrl�ı�ͷ�ؼ�
*/
class ListCtrl;
class ListCtrlHeaderItem;
struct ListCtrlColumn;
class ListCtrlHeader : public ListBoxItemH
{
    friend class ListCtrlHeaderItem;
public:
    ListCtrlHeader();
    virtual ~ListCtrlHeader();

    /** ��ȡ�ؼ�����
    */
    virtual std::wstring GetType() const override;

    /** ��������
    */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

    /** �жϿؼ������Ƿ�Ϊ��ѡ���
     * @return Ĭ�Ϸ���false
     */
    virtual bool IsSelectableType() const override;

public:
    /** ��ָ��λ�����һ��
    *  ��ͷ�ؼ��Ļ����ṹ���£�
    * 
    *   <ListCtrlHeader>
    *       <ListCtrlHeaderItem> CheckBox[��ѡ] </ListCtrlHeaderItem>
    *       <SplitBox> <Control/> </SplitBox>
    *       ..
    *       <ListCtrlHeaderItem> CheckBox[��ѡ] </ListCtrlHeaderItem>
    *       <SplitBox> <Control/> </SplitBox>
    *   </ListCtrlHeader>
    * 
    * @param [in] columnIndex �ڵڼ����Ժ������У������-1����ʾ�����׷��һ��
    * @param [in] columnInfo �еĻ�������
    * @return ������һ�еı�ͷ�ؼ��ӿ�
    */
    ListCtrlHeaderItem* InsertColumn(int32_t columnIndex, const ListCtrlColumn& columnInfo);

    /** ��ȡ�еĸ���
    */
    size_t GetColumnCount() const;

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

    /** ��ȡ�б�ͷ�Ŀؼ��ӿ�
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    ListCtrlHeaderItem* GetColumn(size_t columnIndex) const;

    /** ��ȡ�б�ͷ�Ŀؼ��ӿ�
    * @param [in] columnId �е�IDֵ��ͨ��ListCtrlHeaderItem::GetColomnId()������ȡ
    */
    ListCtrlHeaderItem* GetColumnById(size_t columnId) const;

    /** ��ȡ�п�Ⱥ����������
    * @param [in] columnId �е�IDֵ��ͨ��ListCtrlHeaderItem::GetColomnId()������ȡ
    * @param [out] columnIndex �е���ţ�[0, GetColumnCount())������ڼ���
    * @param [out] nColumnWidth �еĿ��ֵ
    */
    bool GetColumnInfo(size_t columnId, size_t& columnIndex, int32_t& nColumnWidth) const;

    /** ��ȡ�е��������
    * @param [in] columnId �е�IDֵ��ͨ��ListCtrlHeaderItem::GetColomnId()������ȡ
    * @return �е���ţ�[0, GetColumnCount())������ڼ���
    */
    size_t GetColumnIndex(size_t columnId) const;

    /** ��ȡ�е��������
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    * @return �е�ID�����ƥ�䲻�����򷵻�Box::InvalidIndex
    */
    size_t GetColumnId(size_t columnIndex) const;

    /** ɾ��һ��
    * @param [in] columnIndex ��������ţ�[0, GetColumnCount())
    */
    bool DeleteColumn(size_t columnIndex);

    /** �����Ƿ���Header��ʾCheckBox
    * @param [in] bShow true��ʾ�ڱ�ͷ��ʾCheckBox��false��ʾ����ʾ
    */
    bool SetShowCheckBox(bool bShow);

    /** �ж��Ƿ���ʾ��CheckBox
    */
    bool IsShowCheckBox() const;

    /** ��ֹ/����CheckBox��ѡ��仯�¼�
    * @return ����ԭ����״̬�����ڻ�ԭ
    */
    bool SetEnableCheckChangeEvent(bool bEnable);

    /** ��������Paddingֵ�������������ж�����ʾ
    */
    void SetPaddingLeftValue(int32_t nPaddingLeft);

    /** ����������ͼ��֮��ļ�������أ�
    */
    void SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale);

    /** ��ȡ������ͼ��֮��ļ�������أ�
    */
    int32_t GetIconSpacing() const;

public:

    /** ���ù�����ListCtrl�ӿ�
    */
    void SetListCtrl(ListCtrl* pListCtrl);

    /** ��ȡ������ListCtrl�ӿ�
    */
    ListCtrl* GetListCtrl() const;

public:
    /** �б�ͷ����Ҽ����������
    * @param[in] callback Ҫ�󶨵Ļص�����, 
    *   ����˵����wParam�����Ϊ0����ֵ�ǣ�ListCtrlHeaderItem*
    *           ����ͨ�� ListCtrlHeaderItem* pHeaderItem = (ListCtrlHeaderItem*)wParam; ��ȡ�������������
    *           ���wParam���Ϊ0��˵���ǵ������ListCtrlHeader����հ״���û�е�����κ���
    */
    void AttachRClick(const EventCallback& callback) { AttachEvent(kEventRClick, callback); }

protected:
    /** �Ƿ�֧���б�ͷ�϶��ı��е�˳��
    */
    bool IsEnableHeaderDragOrder() const;

    /** �϶��б�ͷ�ı��п���¼���Ӧ����
    * @param [in] pLeftHeaderItem �����б�ͷ�ؼ��ӿ�
    * @param [in] pRightHeaderItem �Ҳ���б�ͷ�ؼ��ӿ�
    */
    void OnHeaderColumnResized(Control* pLeftHeaderItem, Control* pRightHeaderItem);

    /** ����б�ͷ����������¼���Ӧ����
    * @param [in] pHeaderItem �б�ͷ�ؼ��ӿ�
    */
    void OnHeaderColumnSorted(ListCtrlHeaderItem* pHeaderItem);

    /** ͨ���϶��б�ͷ���������е�˳��
    */
    void OnHeaderColumnOrderChanged();

    /** CheckBox�Ĺ�ѡ�����
    * @param [in] pHeaderItem �б�ͷ�ؼ��ӿ�
    * @param [in] bChecked true��ʾ��ѡ��Checked״̬����false��ʾȡ����ѡ��UnChecked״̬��
    */
    void OnHeaderColumnCheckStateChanged(ListCtrlHeaderItem* pHeaderItem, bool bChecked);

    /** ��ͷ�е���ʾ���Է����仯
    */
    void OnHeaderColumnVisibleChanged();

    /** �б�ͷ�еķָ���˫���¼�
    * @param [in] pHeaderItem �б�ͷ�ؼ��ӿ�
    */
    void OnHeaderColumnSplitDoubleClick(ListCtrlHeaderItem* pHeaderItem);

    /** �Ƿ�֧�ֹ�ѡģʽ��Ŀǰ��TreeView/ListCtrl��ʹ�����ģʽ��
        ��ѡģʽ��ָ��
        ��1��ֻ�е����CheckBoxͼƬ�ϵ�ʱ�򣬹�ѡ��ͼƬ����ѡ��״̬���ǹ�ѡģʽ�£��ǵ���ڿؼ������ھ�ѡ��
        ��2����ѡ״̬��ѡ��״̬���룬��������ͬ��״̬
    */
    virtual bool SupportCheckedMode() const override;

    /** ��ѡ״̬�仯�¼�(m_bChecked���������仯)
    */
    virtual void OnPrivateSetChecked() override;

    /** ��ȡCheckBox��ͼƬ���
    */
    int32_t GetCheckBoxImageWidth();

    /** ����Padding��ȷ��������ͼ�겻�ص�
    */
    void UpdatePaddingLeft();

private:
    /** ������ListCtrl�ӿ�
    */
    ListCtrl* m_pListCtrl;

    /** ���õ�CheckBox���ֵ
    */
    int32_t m_nCheckBoxPadding;

    /** ����Paddingֵ�������������ж�����ʾ
    */
    int32_t m_nPaddingLeftValue;

    /** �Ƿ�����CheckBox��ѡ��仯�¼�
    */
    bool m_bEnableCheckChangeEvent;

    /** ������ͼ��֮��ļ��(ͼ����ʾ�����ֵ��Ҳ�������ʱ)
    */
    int32_t m_nIconSpacing;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_HEADER_H_
