#ifndef UI_CONTROL_SPLIT_H_
#define UI_CONTROL_SPLIT_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Core/Box.h"

namespace ui
{

/** �ָ����ؼ�������ͨ���϶��ָ����ı����һ������������ؼ��Ŀ�Ȼ��߸߶�
*   Ӧ�ã�������ں��򲼾֣�HLayout���У��������϶�
*        ����������򲼾֣�VLayout���У��������϶�
*   ע�������������ؼ�������Ϊ�������͵ģ���ָ����޷�����������
*/
template<typename InheritType = Control>
class UILIB_API SplitTemplate : public InheritType
{
public:
    SplitTemplate();

    virtual std::wstring GetType() const override;
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
 
    /** �Ƿ�����϶�
    */
    bool IsSplitDragValid();

    /** ֹͣ�϶�
    */
    void StopSplitDrag();

    /** ���õ�ֻ��һ���ؼ���ʱ���Ƿ������������
    */
    void SetEnableSplitSingle(bool bEnableSplitSingle);

    /** ��ȡ��ֻ��һ���ؼ���ʱ���Ƿ������������
    */
    bool IsEnableSplitSingle() const;

    /** �����϶����¼�
     * @param [in] callback ��ѡ��ʱ�����Ļص�����
     */
    void AttachSplitDraged(const EventCallback& callback) { this->AttachEvent(kEventSplitDraged, callback); }

protected:
    virtual bool MouseEnter(const EventArgs& msg) override;
    virtual bool ButtonDown(const EventArgs& msg) override;
    virtual bool ButtonUp(const EventArgs& msg) override;
    virtual bool MouseMove(const EventArgs& msg) override;

private:
    //�Ƿ�Ϊ��ֱ���ֵ�����
    bool IsVLayout(Control* pControl) const;

    //�Ƿ�Ϊˮƽ���ֵ�����
    bool IsHLayout(Control* pControl) const;

    /** ���������ؼ��У�����һ����pFirst���ؼ��Ŀ�Ȼ��߸߶�
    * @param [in] bHLayout true��ʾ���򲼾֣�false��ʾ���򲼾�
    * @param [in] nTotal �����ؼ��������Ȼ��߸߶�
    * @param [in] nOffset ���Ŀ�Ȼ��߸߶�ƫ����
    * @param [in] pFirst ��һ���ؼ��ӿڣ��ú���������ýӿڶ�Ӧ�ؼ��Ŀ�Ȼ��߸߶�
    * @param [in] nFirstFixedInt ��һ���ؼ���ԭʼ��Ȼ��߸߶�ֵ������갴��ʱ��¼��
    * @param [in] pSecond �ڶ����ؼ��ӿڣ���ȡ����Сֵ�����������һ���ؼ�ʱδ�������㹻��С�ռ�
    * @return ���ص�һ���ؼ��Ŀ�Ȼ��߸߶�
    */
    int32_t CalculateControlPos(bool bHLayout, const int32_t nTotal, const int32_t nOffset,
                                Control* pFirst, const UiFixedInt& nFirstFixedInt,
                                const Control* pSecond) const;

    /** ������һ���ؼ��Ĵ�С
    */
    void OnMouseMoveSingle(const EventArgs& msg);

private:
    //��ࣨ�����϶��������ϲࣨ�����϶����Ŀؼ��ӿ�
    Control* m_pLeftTop;

    //�Ҳࣨ�����϶��������²ࣨ�����϶����Ŀؼ��ӿ�
    Control* m_pRightBottom;

    //��ࣨ�����϶��������ϲࣨ�����϶����Ŀؼ��Ŀ�ȣ������϶������߸߶ȣ������϶���
    UiFixedInt m_nLeftUpFixedValue;

    //�Ҳࣨ�����϶��������²ࣨ�����϶����Ŀؼ��Ŀ�ȣ������϶������߸߶ȣ������϶���
    UiFixedInt m_nRightBottomFixedValue;

    //��ʼ�϶�ʱ�����λ��
    UiPoint m_ptStart;

    //���ַ���: true��ʾ���򲼾֣�false��ʾ���򲼾�
    bool m_bHLayout;

    /** ��ֻ��һ���ؼ���ʱ���Ƿ������������
    */
    bool m_bEnableSplitSingle;
};

template<typename InheritType>
SplitTemplate<InheritType>::SplitTemplate():
    m_pLeftTop(nullptr),
    m_pRightBottom(nullptr),
    m_bHLayout(true),
    m_bEnableSplitSingle(false)
{
    this->SetMouseEnabled(true);
}

template<typename InheritType>
inline std::wstring SplitTemplate<InheritType>::GetType() const { return DUI_CTR_SPLIT; }

template<>
inline std::wstring SplitTemplate<Box>::GetType() const { return DUI_CTR_SPLITBOX; }

template<typename InheritType>
void SplitTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"enable_split_single") {
        SetEnableSplitSingle(strValue == L"true");
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

template<typename InheritType>
void SplitTemplate<InheritType>::SetEnableSplitSingle(bool bEnableSplitSingle)
{
    m_bEnableSplitSingle = bEnableSplitSingle;
}

template<typename InheritType>
bool SplitTemplate<InheritType>::IsEnableSplitSingle() const
{
    return m_bEnableSplitSingle;
}

template<typename InheritType>
bool SplitTemplate<InheritType>::IsSplitDragValid() 
{
    bool bDragValid = false;
    if (IsEnableSplitSingle()) {
        bDragValid = (m_pLeftTop != nullptr) || (m_pRightBottom != nullptr);
    }
    else {
        bDragValid = (m_pLeftTop != nullptr) && (m_pRightBottom != nullptr);
    }
    return bDragValid;
}

template<typename InheritType>
void SplitTemplate<InheritType>::StopSplitDrag() 
{
    m_pLeftTop = nullptr; 
    m_pRightBottom = nullptr;
}

template<typename InheritType>
bool SplitTemplate<InheritType>::IsVLayout(Control* pControl) const
{
    Box* pBox = dynamic_cast<Box*>(pControl);
    if (pBox == nullptr) {
        return false;
    }
    Layout* pLayout = pBox->GetLayout();
    if (pLayout == nullptr) {
        return false;
    }
    return pLayout->IsVLayout();
}

template<typename InheritType>
bool SplitTemplate<InheritType>::IsHLayout(Control* pControl) const
{
    Box* pBox = dynamic_cast<Box*>(pControl);
    if (pBox == nullptr) {
        return false;
    }
    Layout* pLayout = pBox->GetLayout();
    if (pLayout == nullptr) {
        return false;
    }
    return pLayout->IsHLayout();
}

template<typename InheritType>
bool SplitTemplate<InheritType>::MouseEnter(const EventArgs& msg)
{
    if (IsHLayout(this->GetParent())) {
        //���򲼾�
        if (this->GetCursorType() != kCursorSizeWE) {
            this->SetCursorType(kCursorSizeWE);
        }
    }
    else if (IsVLayout(this->GetParent())) {
        //���򲼾�
        if (this->GetCursorType() != kCursorSizeNS) {
            this->SetCursorType(kCursorSizeNS);
        }
    }
    return __super::MouseEnter(msg);
}

template<typename InheritType>
bool SplitTemplate<InheritType>::ButtonDown(const EventArgs& msg)
{
    bool bRet = __super::ButtonDown(msg);
    Box* pParent = this->GetParent();
    if (!this->IsEnabled() || (pParent == nullptr)) {
        return bRet;
    }
    size_t nChildCount = pParent->GetItemCount();
    Control* pPrev = nullptr;
    Control* pNext = nullptr;
    Control* pThis = nullptr;
    for (size_t i = 0; i < nChildCount; ++i) {
        Control* pControl = pParent->GetItemAt(i);
        if (!pControl->IsVisible() || pControl->IsFloat()) {
            continue;
        }
        if (pThis) {
            pNext = pControl;
            break;
        }
        if (pControl == this) {
            pThis = pControl;
        }
        else {
            pPrev = pControl;
        }
    }
    bool bDragValid = false;
    if (IsEnableSplitSingle()) {
        bDragValid = (pPrev != nullptr) || (pNext != nullptr);
    }
    else {
        bDragValid = (pPrev != nullptr) && (pNext != nullptr);
    }
    if (bDragValid && (pThis != nullptr)) {
        if (IsVLayout(pParent)) {
            m_bHLayout = false;
            m_pLeftTop = pPrev;
            m_pRightBottom = pNext;
            m_ptStart = msg.ptMouse;

            m_nLeftUpFixedValue = UiFixedInt(0);
            if (m_pLeftTop != nullptr) {
                m_nLeftUpFixedValue = m_pLeftTop->GetFixedHeight();
                if (!m_nLeftUpFixedValue.IsStretch()) {
                    m_nLeftUpFixedValue.SetInt32(m_pLeftTop->GetHeight());
                }
            }

            m_nRightBottomFixedValue = UiFixedInt(0);
            if (m_pRightBottom != nullptr) {
                m_nRightBottomFixedValue = m_pRightBottom->GetFixedHeight();
                if (!m_nRightBottomFixedValue.IsStretch()) {
                    m_nRightBottomFixedValue.SetInt32(m_pRightBottom->GetHeight());
                }
            }
        }
        else if (IsHLayout(pParent)) {
            m_bHLayout = true;
            m_pLeftTop = pPrev;
            m_pRightBottom = pNext;
            m_ptStart = msg.ptMouse;

            m_nLeftUpFixedValue = UiFixedInt(0);
            if (m_pLeftTop != nullptr) {
                m_nLeftUpFixedValue = m_pLeftTop->GetFixedWidth();
                if (!m_nLeftUpFixedValue.IsStretch()) {
                    m_nLeftUpFixedValue.SetInt32(m_pLeftTop->GetWidth());
                }
            }
            
            m_nRightBottomFixedValue = UiFixedInt(0);
            if (m_pRightBottom != nullptr) {
                m_nRightBottomFixedValue = m_pRightBottom->GetFixedWidth();
                if (!m_nRightBottomFixedValue.IsStretch()) {
                    m_nRightBottomFixedValue.SetInt32(m_pRightBottom->GetWidth());
                }
            }
        }
    }
    if (!IsSplitDragValid()) {
        StopSplitDrag();
    }
    if ((m_pLeftTop != nullptr) && (m_pRightBottom != nullptr)) {
        //��������ؼ������������͵ģ���ô�����(�ϲ�)�ı�Ϊ������ģ������϶�����
        if (m_nLeftUpFixedValue.IsStretch() && m_nRightBottomFixedValue.IsStretch()) {
            m_nLeftUpFixedValue.SetInt32(m_pLeftTop->GetWidth());
        }
    }
    this->Invalidate();
    return bRet;
}

template<typename InheritType>
bool SplitTemplate<InheritType>::ButtonUp(const EventArgs& msg)
{
    bool bRet = __super::ButtonUp(msg);
    StopSplitDrag();
    return bRet;
}

template<typename InheritType>
int32_t SplitTemplate<InheritType>::CalculateControlPos(bool bHLayout, const int32_t nTotal, const int32_t nOffset,
                                                        Control* pFirst, const UiFixedInt& nFirstFixedInt,
                                                        const Control* pSecond) const
{
    int32_t nNewValue = nFirstFixedInt.GetInt32() + nOffset; //��ֵ��������������Ҳ�����Ǹ���
    if (nNewValue < 0) {
        nNewValue = 0;
    }

    int32_t nMin = 0; //��Сֵ
    if (bHLayout) {
        nMin = pFirst->GetMinWidth();
    }
    else {
        nMin = pFirst->GetMinHeight();
    }    
    //���Ʋ�С����Сֵ
    if (nNewValue < nMin) {
        nNewValue = nMin;
    }

    int32_t nMax = 0; //���ֵ, ���Ұ�����һ�����Сֵ���ã�������С�ռ�
    if (bHLayout) {
        nMax = pFirst->GetMaxWidth();
        if (pSecond->GetMinWidth() > 0) {
            int32_t nNewMax = nTotal - pSecond->GetMinWidth();
            if ((nNewMax > 0) && (nMax > nNewMax)) {
                nMax = nNewMax;
            }
        }
    }
    else {
        nMax = pFirst->GetMaxHeight();
        if (pSecond->GetMinHeight() > 0) {
            int32_t nNewMax = nTotal - pSecond->GetMinHeight();
            if ((nNewMax > 0) && (nMax > nNewMax)) {
                nMax = nNewMax;
            }
        }
    }
    //���Ʋ��������ֵ
    if (nNewValue > nMax) {
        nNewValue = nMax;
    }
    return nNewValue;    
}

template<typename InheritType>
bool SplitTemplate<InheritType>::MouseMove(const EventArgs& msg)
{
    bool bRet = __super::MouseMove(msg);
    if (!IsSplitDragValid() || !this->IsMouseFocused()) {
        return bRet;
    }

    if ((m_pLeftTop == nullptr) || (m_pRightBottom == nullptr)) {
        //ֻ��һ���ؼ���Ҫ������С
        OnMouseMoveSingle(msg);
        return bRet;
    }
    
    int32_t nOffset = 0; //�϶��ķ�Χ����Ȼ��߸߶ȵ�ƫ����, ������������Ҳ�����Ǹ�����
    if (m_bHLayout) {
        nOffset = msg.ptMouse.x - m_ptStart.x;
    }
    else {
        nOffset = msg.ptMouse.y - m_ptStart.y;
    }

    //�϶�ʱ�����ܳ����ܵĿ��ֵ�����ܵĸ߶�ֵ
    if (nOffset > 0) {
        if (!m_nRightBottomFixedValue.IsStretch()) {
            if (nOffset > m_nRightBottomFixedValue.GetInt32()) {
                nOffset = m_nRightBottomFixedValue.GetInt32();
            }
        }
    }
    else if(nOffset < 0){
        if (!m_nLeftUpFixedValue.IsStretch()) {
            if (-nOffset > m_nLeftUpFixedValue.GetInt32()) {
                nOffset = -m_nLeftUpFixedValue.GetInt32();
            }
        }
    }
    else {
        return bRet;
    }
    
    int32_t nTotal = 0; //�ܵĿ��ֵ�����ܵĸ߶�ֵ
    if (m_nLeftUpFixedValue.IsInt32() && m_nRightBottomFixedValue.IsInt32()) {
        nTotal = m_nLeftUpFixedValue.GetInt32() + m_nRightBottomFixedValue.GetInt32();
    }
    else {
        if (m_bHLayout) {
            nTotal = m_pLeftTop->GetWidth() + m_pRightBottom->GetWidth();
        }
        else {
            nTotal = m_pLeftTop->GetHeight() + m_pRightBottom->GetHeight();
        }
    }

    //�����������͵Ŀؼ����������������������Զ���������������ؼ������������͵ģ��ָ������޷������ˣ�
    Control* pControl1 = nullptr;
    Control* pControl2 = nullptr;
    int32_t nNewValue1 = 0;
    int32_t nNewValue2 = 0;
    if (!m_nLeftUpFixedValue.IsStretch()) {
        pControl1 = m_pLeftTop;
        nNewValue1 = CalculateControlPos(m_bHLayout, nTotal, nOffset, m_pLeftTop, m_nLeftUpFixedValue, m_pRightBottom);
    }
    else {
        nNewValue1 = -1;
    }
    if (!m_nRightBottomFixedValue.IsStretch()) {
        pControl2 = m_pRightBottom;
        nNewValue2 = CalculateControlPos(m_bHLayout, nTotal, -nOffset, m_pRightBottom, m_nRightBottomFixedValue, m_pLeftTop);
    }
    else {
        nNewValue2 = -1;
    }
    if ((nNewValue1 < 0) && (nNewValue2 < 0)) {
        //�����ؼ������������͵ģ�������
        return bRet;
    }
    else if ((nNewValue1 >= 0) && (nNewValue2 >= 0)) {
        if ((nNewValue1 + nNewValue2) != nTotal) {
            //�������ƣ�������
            return bRet;
        }
    }
    else if (nNewValue1 >= 0) {
        if (nNewValue1 > nTotal) {
            //�������ƣ�������
            return bRet;
        }
    }
    else if (nNewValue2 >= 0) {
        if (nNewValue2 > nTotal) {
            //�������ƣ�������
            return bRet;
        }
    }
    
    bool bAdjusted = false;
    if ((pControl1 != nullptr) && (nNewValue1 >= 0)) {
        bAdjusted = true;
        if (m_bHLayout) {
            pControl1->SetFixedWidth(UiFixedInt(nNewValue1), true, false);
        }
        else {
            pControl1->SetFixedHeight(UiFixedInt(nNewValue1), true, false);
        }
    }
    if ((pControl2 != nullptr) && (nNewValue2 >= 0)) {
        bAdjusted = true;
        if (m_bHLayout) {
            pControl2->SetFixedWidth(UiFixedInt(nNewValue2), true, false);
        }
        else {
            pControl2->SetFixedHeight(UiFixedInt(nNewValue2), true, false);
        }
    }

    if (bAdjusted && (pControl1 != nullptr) || (pControl2 != nullptr)) {
        this->SendEvent(kEventSplitDraged, (WPARAM)pControl1, (LPARAM)pControl2);
    }
    return bRet;
}

template<typename InheritType>
void SplitTemplate<InheritType>::OnMouseMoveSingle(const EventArgs& msg)
{
    if ((m_pLeftTop == nullptr) && (m_pRightBottom == nullptr)) {
        return;
    }
    if ((m_pLeftTop != nullptr) && (m_pRightBottom != nullptr)) {
        return;
    }
    if ((m_pRightBottom != nullptr) && m_nRightBottomFixedValue.IsStretch()) {
        //�ؼ�Ϊ�������ͣ�������
        return;
    }
    if ((m_pLeftTop != nullptr) && m_nLeftUpFixedValue.IsStretch()) {
        //�ؼ�Ϊ�������ͣ�������
        return;
    }

    int32_t nOffset = 0; //�϶��ķ�Χ����Ȼ��߸߶ȵ�ƫ����, ������������Ҳ�����Ǹ�����
    if (m_bHLayout) {
        nOffset = msg.ptMouse.x - m_ptStart.x;
    }
    else {
        nOffset = msg.ptMouse.y - m_ptStart.y;
    }

    //�϶�ʱ�����ܳ����ܵĿ��ֵ�����ܵĸ߶�ֵ
    if (nOffset > 0) {
        if ((m_pRightBottom != nullptr) && !m_nRightBottomFixedValue.IsStretch()) {
            if (nOffset > m_nRightBottomFixedValue.GetInt32()) {
                nOffset = m_nRightBottomFixedValue.GetInt32();
            }
        }
    }
    else if (nOffset < 0) {
        if ((m_pLeftTop != nullptr) && !m_nLeftUpFixedValue.IsStretch()) {
            if (-nOffset > m_nLeftUpFixedValue.GetInt32()) {
                nOffset = -m_nLeftUpFixedValue.GetInt32();
            }
        }
    }
    else {
        return;
    }

    UiFixedInt nFixedInt;
    Control* pControl = nullptr;
    if (m_pLeftTop != nullptr) {
        pControl = m_pLeftTop;
        nFixedInt = m_nLeftUpFixedValue;
    }
    else if (m_pRightBottom != nullptr) {
        pControl = m_pRightBottom;
        nFixedInt = m_nRightBottomFixedValue;
    }
    else {
        return;
    }

    int32_t nNewValue = nFixedInt.GetInt32() + nOffset; //��ֵ��������������Ҳ�����Ǹ���
    if (nNewValue < 0) {
        nNewValue = 0;
    }
    int32_t nMin = 0; //��Сֵ
    bool bHLayout = m_bHLayout;
    if (bHLayout) {
        nMin = pControl->GetMinWidth();
    }
    else {
        nMin = pControl->GetMinHeight();
    }
    //���Ʋ�С����Сֵ
    if (nNewValue < nMin) {
        nNewValue = nMin;
    }

    int32_t nMax = 0; //���ֵ, ���Ұ�����һ�����Сֵ���ã�������С�ռ�
    if (bHLayout) {
        nMax = pControl->GetMaxWidth();
    }
    else {
        nMax = pControl->GetMaxHeight();
    }
    //���Ʋ��������ֵ
    if (nNewValue > nMax) {
        nNewValue = nMax;
    }

    bool bAdjusted = false;
    if ((pControl != nullptr) && (nNewValue >= 0)) {
        bAdjusted = true;
        if (bHLayout) {
            pControl->SetFixedWidth(UiFixedInt(nNewValue), true, false);
        }
        else {
            pControl->SetFixedHeight(UiFixedInt(nNewValue), true, false);
        }
    }
    if (bAdjusted && (pControl != nullptr)) {
        this->SendEvent(kEventSplitDraged, (WPARAM)pControl, (LPARAM)nullptr);
    }
}

typedef SplitTemplate<Control> Split;
typedef SplitTemplate<Box> SplitBox;

}//name space ui

#endif // UI_CONTROL_SPLIT_H_