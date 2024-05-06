#ifndef UI_CONTROL_LIST_CTRL_VIEW_H_
#define UI_CONTROL_LIST_CTRL_VIEW_H_

#pragma once

#include "duilib/Box/VirtualListBox.h"

namespace ui
{
/** ListCtrl�б���ͼUI�ؼ��Ļ��ࣨʵ������ѡ���ܣ��������������ݼ������ѡ���߼��ȣ�
*   ʹ��������ʱ����Ҫ�� ListCtrlItemTemplate ģ�����γ�������ΪListBoxItem
*/
class ListCtrlView : public VirtualListBox
{
public:
    explicit ListCtrlView(Layout* pLayout);
    virtual ~ListCtrlView();

    virtual std::wstring GetType() const override { return L"ListCtrlView"; }
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue);
    virtual void HandleEvent(const EventArgs& msg) override;

    /** ѡ������
    *  @param [in] iIndex ����Ŀ��ID
    *  @param [in] bTakeFocus �Ƿ�������ؼ���Ϊ����ؼ�
    *  @param [in] bTriggerEvent �Ƿ񴥷�ѡ���¼�, ���Ϊtrue���ᴥ��һ��kEventSelect�¼�
    *  @param [in] vkFlag ������־, ȡֵ��Χ�μ� enum VKFlag �Ķ���
    */
    virtual bool SelectItem(size_t iIndex, bool bTakeFocus,
                            bool bTriggerEvent, uint64_t vkFlag) override;

public:
    /** ����ѡ������仯���¼�
     * @param[in] callback ѡ������ʱ�Ļص�����
     */
    void AttachSelChange(const EventCallback& callback) { AttachEvent(kEventSelChange, callback); }

    /** �����¼��ĺ���
    */
    virtual void SendEvent(EventType eventType, WPARAM wParam = 0, LPARAM lParam = 0, TCHAR tChar = 0,
                           const UiPoint& mousePos = UiPoint()) override;
    virtual void SendEvent(const EventArgs& event) override;

public:
    /** ��ȡ����Ԫ�ص�������
    */
    virtual size_t GetTopElementIndex() const;

    /** �ж�һ���������Ƿ�ɼ�
    * @param [in] itemIndex �������������, ��Ч��Χ��[0, GetDataItemCount())
    */
    virtual bool IsDataItemDisplay(size_t itemIndex) const;

    /** ��ȡ��ǰ��ʾ���������б�˳���Ǵ��ϵ���
    * @param [in] itemIndexList ��ǰ��ʾ���������������б�
    */
    virtual void GetDisplayDataItems(std::vector<size_t>& itemIndexList) const;

    /** ȷ������������ɼ�
    * @param [in] itemIndex �������������
    * @param [in] bToTop �Ƿ�ȷ�������Ϸ�
    */
    virtual bool EnsureDataItemVisible(size_t itemIndex, bool bToTop);

public:
    /** ������ͨ�б����Header�����ö�����top����
    */
    void SetNormalItemTop(int32_t nNormalItemTop);

    /** ��ȡ��ͨ�б����Header�����ö�����top����
    */
    int32_t GetNormalItemTop() const;

protected:
    /** �ؼ���ʼ��
    */
    virtual void OnInit() override;

    /** �����ӿؼ�
    */
    virtual void PaintChild(IRender* pRender, const UiRect& rcPaint) override;

    /** ����ListBoxItem������¼�����ʵ������ѡ����
    */
    virtual void AttachMouseEvents(Control* pListBoxItem);

    /** ѡ��״̬�����仯
    */
    virtual void OnSelectStatusChanged();

    /** ��ȡ������ͼ�Ĺ�������
    */
    virtual void GetScrollDeltaValue(int32_t& nHScrollValue, int32_t& nVScrollValue) const;

    /** ִ��������ѡ����
    * @param [in] left ��ѡ��X����leftֵ
    * @param [in] right ��ѡ��X����rightֵ
    * @param [in] top ��ѡ��Y����topֵ
    * @param [in] bottom ��ѡ��Y����bottomֵ
    * @return �����ѡ��仯����true�����򷵻�false
    */
    virtual bool OnFrameSelection(int64_t left, int64_t right, int64_t top, int64_t bottom);

    /** ��������ѡ�ı߿�������ɫ
    */
    void PaintFrameSelection(IRender* pRender);

protected:
    //�����Ϣ������true����ʾ��Ϣ�Ѵ�������false�����ʾ��Ϣδ������ת�������ؼ���
    virtual bool ButtonDown(const EventArgs& msg) override;
    virtual bool ButtonUp(const EventArgs& msg) override;
    virtual bool RButtonDown(const EventArgs& msg) override;
    virtual bool RButtonUp(const EventArgs& msg) override;
    virtual bool MouseMove(const EventArgs& msg) override;
    virtual bool OnWindowKillFocus(const EventArgs& msg) override;//�ؼ������Ĵ���ʧȥ����

private:
    void OnButtonDown(const UiPoint& ptMouse, Control* pSender);
    void OnButtonUp(const UiPoint& ptMouse, Control* pSender);
    void OnRButtonDown(const UiPoint& ptMouse, Control* pSender);
    void OnRButtonUp(const UiPoint& ptMouse, Control* pSender);
    void OnMouseMove(const UiPoint& ptMouse, Control* pSender);
    void OnWindowKillFocus();

private:
    /** ����ͼ�հ״������������/�Ҽ�
    */
    bool OnListCtrlClickedBlank();

    /** ����Ƿ���Ҫ������ͼ
    */
    void OnCheckScrollView();

    /** ���򲼾֣���������
    */
    int32_t CalcRows() const;

    /** ���򲼾֣���������
    */
    int32_t CalcColumns() const;

    /** ����һ��Ԫ�صľ�������
    */
    void CalcElementRectV(size_t nElemenetIndex, const UiSize& szItem, 
                          int32_t nColumns, int32_t childMarginX, int32_t childMarginY,
                          int64_t& iLeft, int64_t& iTop, int64_t& iRight, int64_t& iBottom) const;

    /** ����һ��Ԫ�صľ�������
    */
    void CalcElementRectH(size_t nElemenetIndex, const UiSize& szItem, 
                          int32_t nRows, int32_t childMarginX, int32_t childMarginY,
                          int64_t& iLeft, int64_t& iTop, int64_t& iRight, int64_t& iBottom) const;


    /** ��ӦKeyDown��Ϣ
    * @return ����true��ʾ�ɹ���������false��ʾδ�������Ϣ
    */
    bool OnListCtrlKeyDown(const EventArgs& msg);

private:
    /** �Ƿ��������ͼ�а�����������Ҽ�
    */
    bool m_bMouseDownInView;

    /** �Ƿ�����������
    */
    bool m_bMouseDown;

    /** �Ƿ�����Ҽ�����
    */
    bool m_bRMouseDown;

    /** �Ƿ�����껬��������
    */
    bool m_bInMouseMove;

    /** ��갴��ʱ�����λ��
    */
    UiSize64 m_ptMouseDown;

    /** ��껬��ʱ�����λ��
    */
    UiSize64 m_ptMouseMove;

    /** ��갴��ʱ�Ŀؼ��ӿ�
    */
    Control* m_pMouseSender;

    /** ��ʱ��������ͼʱ��ȡ������
    */
    nbase::WeakCallbackFlag m_scrollViewFlag;

    /** ����ѡ���ܵ�����
    */
    bool m_bEnableFrameSelection; //�Ƿ�֧������ѡ����
    UiString m_frameSelectionColor; //��ѡ�����ɫ
    uint8_t m_frameSelectionAlpha;  //��ѡ�����ɫ��Alphaֵ
    UiString m_frameSelectionBorderColor; //��ѡ�߿���ɫ
    uint8_t m_frameSelectionBorderSize; //��ѡ�߿��С

private:
    /** û��Shift��ʱ�����һ��ѡ�����Ч��Χ��[0, GetElementCount())
    */
    size_t m_nLastNoShiftIndex;

private:
    /** ��ͨ�б����Header�����ö�����top����
    */
    int32_t m_nNormalItemTop;
};

/** ListCtrl������ͼ��������Ļ���ģ��
*/
template<typename InheritType>
class UILIB_API ListCtrlItemTemplate : public ListBoxItemTemplate<InheritType>
{
public:
    ListCtrlItemTemplate() {}
    virtual ~ListCtrlItemTemplate() {}

    /** ���ÿؼ��Ƿ�ѡ��״̬
  * @param [in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
  * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��Ĭ��Ϊ false
  */
    virtual void Selected(bool bSelect, bool bTriggerEvent) override
    {
        if (__super::IsSelected() != bSelect) {
            __super::Selected(bSelect, bTriggerEvent);
        }
    }

protected:
    /** �����
    */
    virtual void Activate() override
    {
        //��д�����ʵ���߼�������ֻ����һ��Click�¼�
        if (this->IsActivatable()) {
            this->SendEvent(kEventClick);
        }
    }

    /** �����������¼�������ѡ�������¼�
    */
    virtual bool ButtonDown(const EventArgs& msg) override
    {
        if (this->IsEnabled() && this->IsActivatable() && this->IsPointInWithScrollOffset(msg.ptMouse)) {
            uint64_t vkFlag = kVkLButton;
#ifdef UILIB_IMPL_WINSDK
            if (msg.wParam & MK_CONTROL) {
                vkFlag |= kVkControl;
            }
            if (msg.wParam & MK_SHIFT) {
                vkFlag |= kVkShift;
            }
#endif
            //������µ�ʱ��ѡ��
            SelectItem(vkFlag);
        }
        return __super::ButtonDown(msg);
    }

    /** ����Ҽ������¼�������ѡ�������¼�
    */
    virtual bool RButtonDown(const EventArgs& msg) override
    {
        if (this->IsEnabled() && this->IsActivatable() && this->IsPointInWithScrollOffset(msg.ptMouse)) {
            uint64_t vkFlag = kVkRButton;
#ifdef UILIB_IMPL_WINSDK
            if (msg.wParam & MK_CONTROL) {
                vkFlag |= kVkControl;
            }
            if (msg.wParam & MK_SHIFT) {
                vkFlag |= kVkShift;
            }
#endif
            //�Ҽ����µ�ʱ��ѡ��
            SelectItem(vkFlag);
        }
        return __super::RButtonDown(msg);
    }

    /** ִ��ѡ����
    * @param [in] vkFlag ������־, ȡֵ��Χ�μ� enum VKFlag �Ķ���
    */
    void SelectItem(uint64_t vkFlag)
    {
        IListBoxOwner* pOwner = this->GetOwner();
        ASSERT(pOwner != nullptr);
        if (pOwner != nullptr) {
            size_t nListBoxIndex = this->GetListBoxIndex();
            pOwner->SelectItem(nListBoxIndex, true, true, vkFlag);
        }
    }
};

typedef ListCtrlItemTemplate<Box> ListCtrlItemBase;   //����Ϊ��ListBoxItem
typedef ListCtrlItemTemplate<HBox> ListCtrlItemBaseH; //����Ϊ��ListBoxItemH
typedef ListCtrlItemTemplate<VBox> ListCtrlItemBaseV; //����Ϊ��ListBoxItemV

}//namespace ui

#endif //UI_CONTROL_LIST_CTRL_VIEW_H_
