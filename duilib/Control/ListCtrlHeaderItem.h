#ifndef UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_
#define UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_

#pragma once

#include "duilib/Control/Button.h"
#include "duilib/Control/CheckBox.h"
#include "duilib/Control/Split.h"
#include "duilib/Image/Image.h"
#include "duilib/Core/ControlDragable.h"

namespace ui
{

/** ListCtrl�ı�ͷ�ؼ�����ʾ��
*/
class ListCtrlHeader;
class ListCtrlHeaderItem:
    public ControlDragableT<ButtonBox>
{
public:
    ListCtrlHeaderItem();
    virtual ~ListCtrlHeaderItem();

    /** ��ȡ�ؼ�����
    */
    virtual std::wstring GetType() const override;

    /** ��������
    */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

    /** ��������
    */
    virtual void PaintText(IRender* pRender) override;

    /** ��ť����¼�
    */
    virtual void Activate() override;

public:
    /** ����ʽ
    */
    enum class SortMode
    {
        kNone, //��֧������
        kUp,   //����
        kDown  //����
    };

    /** ��������ʽ
    * @param [in] sortMode ����ʽ
    * @param [in] bTriggerEvent true��ʾ��������仯�¼����������������򣬷��򲻴����¼�
    */
    void SetSortMode(SortMode sortMode, bool bTriggerEvent = false);

    /** ��ȡ����ʽ
    */
    SortMode GetSortMode() const;

    /** ��������ͼ�꣺����
    */
    void SetSortedDownImage(const std::wstring& sImageString);

    /** ��������ͼ�꣺����
    */
    void SetSortedUpImage(const std::wstring& sImageString);

    /** ��ȡΨһID
    */
    size_t GetColomnId() const;

    /** ���ù�����Split�ؼ��ӿ�
    */
    void SetSplitBox(SplitBox* pSplitBox);

    /** ��ȡ������Split�ؼ��ӿ�
    */
    SplitBox* GetSplitBox() const;

    /** �����Ƿ���������п�
    */
    void SetColumnResizeable(bool bResizeable);

    /** ��ȡ�Ƿ���������п�
    */
    bool IsColumnResizeable() const;

    /** �����п�
    * @param [in] nWidth �п�ֵ
    * @param [in] bNeedDpiScale �Ƿ���Ҫ���п�ֵ����DPI����Ӧ
    */
    void SetColumnWidth(int32_t nWidth, bool bNeedDpiScale);

    /** ��ȡ�п�ֵ
    */
    int32_t GetColumnWidth() const;

    /** ����������ͼ��֮��ļ�������أ�
    */
    void SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale);

    /** ��ȡ������ͼ��֮��ļ�������أ�
    */
    int32_t GetIconSpacing() const;

    /** ����ͼ����ʾ�������Ϸ���������ʾ
    */
    void SetShowIconAtTop(bool bShowIconAtTop);

    /** ��ȡͼ���Ƿ���ʾ�������Ϸ�
    */
    bool IsShowIconAtTop() const;

    /** �����ı�ˮƽ���뷽ʽ
    */
    void SetTextHorAlign(HorAlignType alignType);

    /** ��ȡ�ı�ˮƽ���뷽ʽ
    */
    HorAlignType GetTextHorAlign() const;

    /** ���ù���ͼ��Id, ���Ϊ-1��ʾ����ʾͼ�꣬ͼ����ʾ���ı�ǰ��
    */
    void SetImageId(int32_t imageId);

    /** ��ȡ����ͼ��Id
    */
    int32_t GetImageId() const;

    /** �����Ƿ�֧���б�ͷ�϶��ı��е�˳��
    */
    virtual bool IsEnableDragOrder() const override;

public:
    /** �����Ƿ���ʾCheckBox
    * @param [in] bVisible true��ʾ��ʾ��false��ʾ����
    */
    bool SetCheckBoxVisible(bool bVisible);

    /** �жϵ�ǰCheckBox�Ƿ�����ʾ״̬
    @return ����true��ʾCheckBox���ڣ����ҿɼ��� �������CheckBox������false
    */
    bool IsCheckBoxVisible() const;

    /** ����CheckBox�Ĺ�ѡ״̬
    * @param [in] bChecked true��ʾ��ѡ��false��ʾ����ѡ
    * @param [in] ���bChecked��bPartCheckedͬʱΪtrue����ʾ����ѡ��
    */
    bool SetCheckBoxCheck(bool bChecked, bool bPartChecked);

    /** ��ȡCheckBox�Ĺ�ѡ״̬
    * @param [out] bChecked true��ʾ��ѡ��false��ʾ����ѡ
    * @param [out] ���bSelected��bPartSelectͬʱΪtrue����ʾ����ѡ��
    */
    bool GetCheckBoxCheck(bool& bChecked, bool& bPartChecked) const;

    /** ��ʾ/���ظ���
    */
    void SetColumnVisible(bool bColumnVisible);

    /** �жϸ����Ƿ���ʾ
    * @return ����true��ʾ������ʾ�������ʾ��������
    */
    bool IsColumnVisible() const;

    /** ���ù�����Header�ӿ�
    */
    void SetHeaderCtrl(ListCtrlHeader* pHeaderCtrl);

    /** ��ȡ������Header�ӿ�
    */
    ListCtrlHeader* GetHeaderCtrl() const;

private:
    /** ͬ���п���UI�ؼ����
    */
    void CheckColumnWidth();

    /** ʹ��Ŀ�������������
    */
    void VAlignRect(UiRect& rc, uint32_t textStyle, int32_t nImageHeight);

protected:
    /** @name �϶�������صĳ�Ա����
    * @{ */
    /** �������λ�õ��������ؼ���λ��(�϶�������һ����)
	* @param [in] pt ��ǰ����λ��
	* @param [in] ptMouseDown ��갴��ʱ��λ��
	* @param [in] rcItemList �ӿؼ����б�
	*/
	virtual void AdjustItemPos(const UiPoint& pt, const UiPoint& ptMouseDown,
							   const std::vector<ItemStatus>& rcItemList) const override;

	/** ���������ؼ���λ�ã����˳�����
	* @param [in] pt ��ǰ����λ��
	* @param [in] rcItemList �ӿؼ����б�
	* @param [in] nOldItemIndex ԭ��������������
	* @param [in] nNewItemIndex ���µ�����������
	* @return �����˳�����������true�����򷵻�false
	*/
	virtual bool AdjustItemOrders(const UiPoint& pt,
								  const std::vector<ItemStatus>& rcItemList,
								  size_t& nOldItemIndex,
								  size_t& nNewItemIndex) override;

	/** �ؼ�λ���϶�����¼�
	* @param [in] nOldItemIndex ԭ��������������
	* @param [in] nNewItemIndex ���µ�����������
	*/
	virtual void OnItemOrdersChanged(size_t nOldItemIndex, size_t nNewItemIndex) override;

    /** @} */

protected:
    //��ֹ�ⲿ���õ����ɼ��Եĺ������������ݲ�ͬ��
    virtual void SetFadeVisible(bool bVisible) override;
    virtual void SetVisible(bool bVisible) override;

private:
    /** ����ͼ�꣺����
    */
    Image* m_pSortedDownImage;

    /** ����ͼ�꣺����
    */
    Image* m_pSortedUpImage;

    /** ������Split�ؼ��ӿ�
    */
    SplitBox* m_pSplitBox;

    /** ����ʽ
    */
    SortMode m_sortMode;

    /** �п�
    */
    int32_t m_nColumnWidth;

    /** �Ƿ�����ı��п�
    */
    bool m_bColumnResizeable;

    /** ������ͼ��֮��ļ��(ͼ����ʾ�����ֵ��Ҳ�������ʱ)
    */
    int32_t m_nIconSpacing;

    /** ͼ����ʾ�������Ϸ���������ʾ
    */
    bool m_bShowIconAtTop;

    /** ��ʾ/���ظ���
    */
    bool m_bColumnVisible;

    /** ����ͼ��Id, ���Ϊ-1��ʾ����ʾͼ�꣬ͼ����ʾ���ı�ǰ��
    */
    int32_t m_imageId;

    /** ������Header�ӿ�
    */
    ListCtrlHeader* m_pHeaderCtrl;
};

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_HEADER_ITEM_H_
