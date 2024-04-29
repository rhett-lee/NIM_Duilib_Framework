#ifndef UI_CORE_CONTROL_DRAGABLE_H_
#define UI_CORE_CONTROL_DRAGABLE_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Core/Box.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Core/DragWindow.h"
#include "duilib/Box/VBox.h"
#include "duilib/Box/HBox.h"

namespace ui
{
/** ��Ҫ���ܣ�֧����ͬBox�ڵ��ӿؼ�ͨ���϶�������˳��
*/
template<typename T = Control>
class UILIB_API ControlDragableT: public T
{
public:
    ControlDragableT();
    virtual ~ControlDragableT();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;	
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/** �����Ƿ�֧���϶��ı�ؼ���˳��
	*/
	void SetEnableDragOrder(bool bEnable);

	/** �ж��Ƿ�֧���϶��ı�ؼ���˳��
	*/
	virtual bool IsEnableDragOrder() const;

	/** �����϶�˳��ʱ���ؼ���͸����
	*/
	void SetDragAlpha(uint8_t nAlpha);

	/** ��ȡ�϶�˳��ʱ���ؼ���͸����
	*/
	uint8_t GetDragAlpha() const;

    /** �����Ƿ�֧���ϳ�����
    */
    void SetEnableDragOut(bool bEnable);

    /** �ж��Ƿ�֧���ϳ�����
    */
    virtual bool IsEnableDragOut() const;

	/** ��ǰ�Ƿ�����ק���������
	*/
	bool IsInDraggingOrder() const;

    /** ��ǰ�Ƿ����ϳ�������
    */
    bool IsInDraggingOut() const;

protected:
	/** @name �϶���صĳ�Ա����
	* @{ */

	virtual bool ButtonDown(const EventArgs& msg) override;
	virtual bool ButtonUp(const EventArgs& msg) override;
	virtual bool MouseMove(const EventArgs& msg) override;
	virtual bool OnWindowKillFocus(const EventArgs& msg) override;//�ؼ������Ĵ���ʧȥ����
    virtual void HandleEvent(const EventArgs& msg) override;

protected:
	/** �ӿؼ���״̬
	*/
	struct ItemStatus
	{
		Control* m_pItem = nullptr;
		UiRect m_rcPos;
		uint8_t m_nPaintOrder = 0;
		size_t m_index = Box::InvalidIndex;
	};

	/** �������λ�õ��������ؼ���λ��(�϶�������һ����)
	* @param [in] pt ��ǰ����λ��
	* @param [in] ptMouseDown ��갴��ʱ��λ��
	* @param [in] rcItemList �ӿؼ����б�
	*/
	virtual void AdjustItemPos(const UiPoint& pt, const UiPoint& ptMouseDown,
							   const std::vector<ItemStatus>& rcItemList) const;

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
								  size_t& nNewItemIndex);

	/** �ؼ�λ���϶�����¼�����ͬһ�������ڣ�
	* @param [in] nOldItemIndex ԭ��������������
	* @param [in] nNewItemIndex ���µ�����������
	*/
	virtual void OnItemOrdersChanged(size_t nOldItemIndex, size_t nNewItemIndex);

	/** ����϶�״̬���ָ�ԭ״̬
	*/
    virtual void ClearDragStatus();

    /** ����ǰ���λ�ã�ת������������������Ч�ķ�Χ��
    */
    virtual void GetValidPointInItemRects(UiPoint& pt) const;

	/** @} */

protected:
    /** @name ����ͬ�����ڲ�ͬ��Box���϶���صĳ�Ա����
    * @{ */

    /** ��ק�Ϸ��¼�
    * @param [in] ptMouse ��ǰ�������λ��
    * @return ����true��ʾƥ�䵽����Ŀؼ�������false��ʾδ�ҵ�����Ŀؼ�λ��
    */
    virtual bool OnDragOutMouseOver(Box* pTargetBox, Box* pOldTargetBox, const UiPoint& ptMouse);

    /** �����ϳ�����ʱ����ʾ�ĸ��洰��
    */
    virtual DragWindow* CreateDragWindow();

    /** Ŀ��λ��ָʾ�ؼ�
    * @param [in] pTargetBox ���������Ŀ��Box�ؼ��ӿ�
    */
    virtual Control* CreateDestControl(Box* pTargetBox);

    /** ���ɿؼ��ϳ�ʱ��λͼ
    */
    virtual std::shared_ptr<IBitmap> CreateDragoutImage();

    /** �ж����λ���Ƿ��ڿؼ��ľ��η�Χ��
    */
    virtual bool IsPtInControlRect(Control* pControl, const UiPoint& pt) const;

    /** �ؼ����������϶�����¼�����ͬһ������/���߲�ͬ�����ڣ�
    * @param [in] pOldBox �ؼ�ԭ�������������ӿ�
    * @param [in] nOldItemIndex ԭ��������������
    * @param [in] pNewBox �ؼ����������������ӿ�
    * @param [in] nNewItemIndex ���µ�����������
    */
    virtual void OnItemBoxChanged(Box* pOldBox, size_t nOldItemIndex, 
                                  Box* pNewBox, size_t nNewItemIndex);

    /** @} */

private:
    /** ����ƶ�ʱִ�е��ϳ�����
    * @return ����true��ʾ�����ϳ������У�����false��ʾδִ���ϳ�����
    */
    bool DragOutMouseMove(const EventArgs& msg);

    /** ��굯��ʱִ�е��ϳ�����
    * @return ����true��ʾִ�����ϳ�����������false��ʾδִ���ϳ�����
    */
    bool DragOutMouseUp(const EventArgs& msg);

    /** ��갴��ʱִ�е��϶�����˳�����
    */
    void DragOrderMouseDown(const EventArgs& msg);

    /** ����ƶ�ʱִ�е��϶�����˳�����
    * @return ����true��ʾ�����϶���������У�����false��ʾδִ���϶��������
    */
    bool DragOrderMouseMove(const EventArgs& msg);

    /** ��굯��ʱִ�е��ϳ�����
    */
    void DragOrderMouseUp(const EventArgs& msg);

private:
	/** @name ����ͬ������ͬһ��Box���϶���صĳ�Ա����
	* @{ */

	/** �Ƿ�֧���϶��ı��е�˳��(���ܿ���)
	*/
	bool m_bEnableDragOrder;

	/** �Ƿ�����������
	*/
	bool m_bMouseDown;

	/** �Ƿ�����ק���������
	*/
	bool m_bInDraggingOrder;

	/** �϶�˳��ʱ���ؼ���͸����
	*/
	uint8_t m_nDragAlpha;

	/** ԭ����͸����
	*/
	uint8_t m_nOldAlpha;

	/** ��갴��ʱ�����λ��
	*/
	UiPoint m_ptMouseDown;

	/** ��갴��ʱ�Ŀؼ���������
	*/
	UiRect m_rcMouseDown;

	/** ��갴��ʱ���������У�ÿ���ؼ���λ��
	*/
	std::vector<ItemStatus> m_rcItemList;

	/** @} */

    /** @name ����ͬ�����ڲ�ͬ��Box���϶���صĳ�Ա����
    * @{ */

    /** �Ƿ�֧���ϳ�����(���ܿ���)
    */
    bool m_bEnableDragOut;

    /** Ŀ��Box
    */
    Box* m_pTargetBox;

    /** Ŀ��λ��ָʾ�ؼ�
    */
    Control* m_pDestControl;

    /** ��ק��״̬����
    */
    DragWindow* m_pDragWindow;

    /** ���ϳ��ؼ���λͼ
    */
    std::shared_ptr<IBitmap> m_pDragImage;

    /** ��ǰ�Ƿ�����ִ���ϳ�����
    */
    bool m_bDraggingOut;

    /** @} */
};

template<typename T>
ControlDragableT<T>::ControlDragableT():
    m_bEnableDragOrder(true),
    m_bMouseDown(false),
    m_bInDraggingOrder(false),
    m_nDragAlpha(216),
    m_nOldAlpha(255),
    m_bEnableDragOut(true),
    m_pTargetBox(nullptr),
    m_pDestControl(nullptr),
    m_pDragWindow(nullptr),
    m_bDraggingOut(false)
{
}

template<typename T>
ControlDragableT<T>::~ControlDragableT()
{
}

template<typename T>
inline std::wstring ControlDragableT<T>::GetType() const { return DUI_CTR_CONTROL_DRAGABLE; }

template<>
inline std::wstring ControlDragableT<Box>::GetType() const { return DUI_CTR_BOX_DRAGABLE; }

template<>
inline std::wstring ControlDragableT<HBox>::GetType() const { return DUI_CTR_HBOX_DRAGABLE; }

template<>
inline std::wstring ControlDragableT<VBox>::GetType() const { return DUI_CTR_VBOX_DRAGABLE; }

template<typename T>
void ControlDragableT<T>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == L"drag_order") {
        //�Ƿ�֧���϶�����˳����ͬһ�������ڣ�
		SetEnableDragOrder(strValue == L"true");
	}
	else if (strName == L"drag_alpha") {
		SetDragAlpha((uint8_t)_wtoi(strValue.c_str()));
	}
    else if (strName == L"drag_out") {
        //�Ƿ�֧���ϳ����ݣ�����ͬ���ڵĲ�ͬ�����ڣ�
        SetEnableDragOut(strValue == L"true");
    }
	else {
		__super::SetAttribute(strName, strValue);
	}
}

template<typename T>
void ControlDragableT<T>::SetEnableDragOrder(bool bEnable)
{
    m_bEnableDragOrder = bEnable;
}

template<typename T>
bool ControlDragableT<T>::IsEnableDragOrder() const
{
    return m_bEnableDragOrder;
}

template<typename T>
void ControlDragableT<T>::SetDragAlpha(uint8_t nAlpha)
{
    m_nDragAlpha = nAlpha;
}

template<typename T>
uint8_t ControlDragableT<T>::GetDragAlpha() const
{
    return m_nDragAlpha;
}

template<typename T>
void ControlDragableT<T>::SetEnableDragOut(bool bEnable)
{
    m_bEnableDragOut = bEnable;
}

template<typename T>
bool ControlDragableT<T>::IsEnableDragOut() const
{
    return m_bEnableDragOut;
}

template<typename T>
bool ControlDragableT<T>::IsInDraggingOrder() const
{
    return m_bInDraggingOrder;
}

template<typename T>
bool ControlDragableT<T>::IsInDraggingOut() const
{
    return m_bDraggingOut;
}

template<typename T>
bool ControlDragableT<T>::ButtonDown(const EventArgs& msg)
{
    m_bMouseDown = false;
    bool bRet = __super::ButtonDown(msg);
    if (!IsEnableDragOrder() && !IsEnableDragOut()) {
        return bRet;
    }
    Box* pParent = this->GetParent();
    if (pParent == nullptr) {
        return bRet;
    }
    Layout* pLayout = pParent->GetLayout();
    if ((pLayout == nullptr) || (!pLayout->IsHLayout() && !pLayout->IsVLayout())) {
        return bRet;
    }
    UiPoint pt(msg.ptMouse);
    pt.Offset(this->GetScrollOffsetInScrollBox());

    m_bMouseDown = true;
    m_ptMouseDown = pt;
    m_rcMouseDown = this->GetRect();

    DragOrderMouseDown(msg); 
    return bRet;
}

template<typename T>
bool ControlDragableT<T>::MouseMove(const EventArgs& msg)
{
    bool bRet = __super::MouseMove(msg);
    if (m_bMouseDown) {
        m_bDraggingOut = DragOutMouseMove(msg);
        if (!m_bDraggingOut) {
            DragOrderMouseMove(msg);
        }
    }
    return bRet;
}

template<typename T>
bool ControlDragableT<T>::ButtonUp(const EventArgs& msg)
{
    bool bRet = __super::ButtonUp(msg);
    if (!DragOutMouseUp(msg)) {
        DragOrderMouseUp(msg);
    }
    ClearDragStatus();
    return bRet;
}

template<typename T>
bool ControlDragableT<T>::OnWindowKillFocus(const EventArgs& msg)
{
    bool bRet = __super::OnWindowKillFocus(msg);
    ClearDragStatus();
    return bRet;
}

template<typename T>
void ControlDragableT<T>::HandleEvent(const EventArgs& msg)
{
    __super::HandleEvent(msg);
    if ((msg.Type == kEventMouseClickChanged) ||
        (msg.Type == kEventMouseClickEsc) ||
        (msg.Type == kEventMouseRButtonDown)) {
        //ȡ���϶���������ϳ�����
        ClearDragStatus();
    }
}

template<typename T>
void ControlDragableT<T>::GetValidPointInItemRects(UiPoint& pt) const
{
    Box* pParent = this->GetParent();
    if (pParent == nullptr) {
        return;
    }

    UiRect boxRect = pParent->GetRect();
    UiRect rcItemRects = boxRect;
    for (size_t nIndex = 0; nIndex < m_rcItemList.size(); ++nIndex) {
        const ItemStatus& itemStatus = m_rcItemList[nIndex];
        if ((itemStatus.m_pItem != nullptr) && !itemStatus.m_pItem->IsFloat()) {
            if (itemStatus.m_rcPos.left > rcItemRects.left) {
                rcItemRects.left = itemStatus.m_rcPos.left;
            }
            if (itemStatus.m_rcPos.top > rcItemRects.top) {
                rcItemRects.top = itemStatus.m_rcPos.top;
            }
            break;
        }
    }
    for (int32_t nIndex = (int32_t)m_rcItemList.size() - 1; nIndex >= 0; --nIndex) {
        const ItemStatus& itemStatus = m_rcItemList[nIndex];
        if ((itemStatus.m_pItem != nullptr) && !itemStatus.m_pItem->IsFloat()) {
            if (itemStatus.m_rcPos.right < rcItemRects.right) {
                rcItemRects.right = itemStatus.m_rcPos.right;
            }
            if (itemStatus.m_rcPos.bottom < rcItemRects.bottom) {
                rcItemRects.bottom = itemStatus.m_rcPos.bottom;
            }
            break;
        }
    }
    if (pt.x < rcItemRects.left) {
        pt.x = rcItemRects.left;
    }
    if (pt.x >= rcItemRects.right) {
        pt.x = rcItemRects.right - 1;
    }
    if (pt.y < rcItemRects.top) {
        pt.y = rcItemRects.top;
    }
    if (pt.y >= rcItemRects.bottom) {
        pt.y = rcItemRects.bottom - 1;
    }
}

template<typename T>
void ControlDragableT<T>::AdjustItemPos(const UiPoint& pt, const UiPoint& ptMouseDown,
                                        const std::vector<ItemStatus>& rcItemList) const
{
    Control* pMouseItem = nullptr;
    size_t nMouseItemIndex = Box::InvalidIndex;
    size_t nMouseDownItemIndex = Box::InvalidIndex;
    for (const ItemStatus& itemStatus : rcItemList) {
        if (itemStatus.m_rcPos.ContainsPt(pt)) {
            pMouseItem = itemStatus.m_pItem;
            nMouseItemIndex = itemStatus.m_index;
        }
        if (itemStatus.m_pItem == this) {
            nMouseDownItemIndex = itemStatus.m_index;
        }
    }
    if ((pMouseItem == nullptr) ||
        (nMouseItemIndex == Box::InvalidIndex) ||
        (nMouseDownItemIndex == Box::InvalidIndex)) {
        return;
    }
    ControlDragableT<T>* pItem = dynamic_cast<ControlDragableT<T>*>(pMouseItem);
    if (pItem == nullptr) {
        //��겻�ڿ��϶��ؼ���
        return;
    }
    if (!pItem->IsEnableDragOrder()) {
        //��ǰ��Ϊ�̶������������˳��
        return;
    }

    const size_t itemCount = rcItemList.size();
    int32_t xOffset = pt.x - ptMouseDown.x;
    if (pMouseItem == this) {
        //��ǰ���λ�ã��������λ�ã��ָ������ؼ���ʵ��λ��
        for (const ItemStatus& item : rcItemList) {
            if (item.m_pItem == this) {
                continue;
            }
            if (item.m_pItem->GetRect() != item.m_rcPos) {
                item.m_pItem->SetPos(item.m_rcPos);
            }
        }
    }
    else if (xOffset < 0) {
        //��ǰ���λ�ã��ڰ��µ����࣬���Ҳ��ƶ��ؼ�
        for (size_t index = 0; index < itemCount; ++index) {
            const ItemStatus& item = rcItemList[index];
            if ((item.m_index >= nMouseItemIndex) && (item.m_index < nMouseDownItemIndex)) {
                //���Ҳ��ƶ�
                if ((index + 1) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index + 1];
                    item.m_pItem->SetPos(nextItem.m_rcPos);
                }
                else {
                    if (item.m_pItem->GetRect() != item.m_rcPos) {
                        item.m_pItem->SetPos(item.m_rcPos);
                    }
                }
            }
            else {
                //�ָ�ԭλ��
                if (item.m_pItem->GetRect() != item.m_rcPos) {
                    item.m_pItem->SetPos(item.m_rcPos);
                }
            }
        }
    }
    else {
        //��ǰ���λ�ã��ڰ��µ���Ҳ࣬������ƶ��ؼ�
        for (size_t index = 0; index < itemCount; ++index) {
            const ItemStatus& item = rcItemList[index];
            if ((item.m_index > nMouseDownItemIndex) && (item.m_index <= nMouseItemIndex)) {
                //������ƶ�
                if ((index - 1) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index - 1];
                    item.m_pItem->SetPos(nextItem.m_rcPos);
                }
                else {
                    if (item.m_pItem->GetRect() != item.m_rcPos) {
                        item.m_pItem->SetPos(item.m_rcPos);
                    }
                }
            }
            else {
                //�ָ�ԭλ��
                if (item.m_pItem->GetRect() != item.m_rcPos) {
                    item.m_pItem->SetPos(item.m_rcPos);
                }
            }
        }
    }
}

template<typename T>
bool ControlDragableT<T>::AdjustItemOrders(const UiPoint& pt,
                                           const std::vector<ItemStatus>& rcItemList,
                                           size_t& nOldItemIndex,
                                           size_t& nNewItemIndex)
{
    nOldItemIndex = Box::InvalidIndex;
    nNewItemIndex = Box::InvalidIndex;
    Box* pParent = this->GetParent();
    if (pParent == nullptr) {
        return false;
    }

    bool bOrderChanged = false;
    const size_t itemCount = pParent->GetItemCount();
    size_t nMouseItemIndex = Box::InvalidIndex;
    size_t nCurrentItemIndex = Box::InvalidIndex;
    for (const ItemStatus& itemStatus : rcItemList) {
        if (itemStatus.m_rcPos.ContainsPt(pt)) {
            nMouseItemIndex = itemStatus.m_index;
            ControlDragableT<T>* pItem = dynamic_cast<ControlDragableT<T>*>(itemStatus.m_pItem);
            if ((pItem != nullptr) && !pItem->IsEnableDragOrder()) {
                //��ǰ�ؼ�Ϊ�̶������������˳��
                nMouseItemIndex = Box::InvalidIndex;
            }
        }
        if ((itemStatus.m_pItem == this) && !itemStatus.m_rcPos.ContainsPt(pt)) {
            nCurrentItemIndex = itemStatus.m_index;
        }
    }
    if ((nMouseItemIndex < itemCount) && (nCurrentItemIndex < itemCount)) {
        //�����ؼ���λ��
        pParent->SetItemIndex(this, nMouseItemIndex);
        nOldItemIndex = nCurrentItemIndex;
        nNewItemIndex = nMouseItemIndex;
        bOrderChanged = true;
    }
    return bOrderChanged;
}

template<typename T>
void ControlDragableT<T>::OnItemOrdersChanged(size_t /*nOldItemIndex*/, size_t /*nNewItemIndex*/)
{
}

template<typename T>
void ControlDragableT<T>::ClearDragStatus()
{
    //�ָ��ϳ�������״̬
    if ((m_pDestControl != nullptr) && (m_pTargetBox != nullptr)) {
        if (m_pTargetBox->RemoveItem(m_pDestControl)) {
            m_pDestControl = nullptr;
        }
    }
    if (m_pDragWindow != nullptr) {
        if (!m_pDragWindow->IsClosingWnd()) {
            m_pDragWindow->SetDragImage(nullptr);
            m_pDragWindow->CloseWnd();
        }
        m_pDragWindow->Release();
        m_pDragWindow = nullptr;
    }
    m_pDragImage.reset();
    m_pTargetBox = nullptr;
    m_bDraggingOut = false;
    this->SetVisible(true);

    //�ָ��϶����������״̬
    if (m_bInDraggingOrder) {
        this->SetAlpha(m_nOldAlpha);
        m_nOldAlpha = 255;
        m_bInDraggingOrder = false;
    }
    m_bMouseDown = false;
    if (!m_rcItemList.empty()) {
        //�ָ��ӿؼ��Ļ���˳��
        for (const ItemStatus& itemStatus : m_rcItemList) {
            if ((itemStatus.m_pItem != nullptr) &&
                (itemStatus.m_nPaintOrder != itemStatus.m_pItem->GetPaintOrder())) {
                itemStatus.m_pItem->SetPaintOrder(itemStatus.m_nPaintOrder);
            }
        }
        m_rcItemList.clear();
        //�Ը��ؼ��ػ�
        Control* pParent = this->GetParent();
        if (pParent != nullptr) {
            pParent->Invalidate();
            pParent->SetPos(pParent->GetPos());
        }
    }
}

template<typename T>
bool ControlDragableT<T>::DragOutMouseUp(const EventArgs& msg)
{
    if (!IsInDraggingOut() || !IsEnableDragOut() || (m_pTargetBox == nullptr)) {
        return false;
    }
    //�ؼ��ϳ�����
    Box* pParent = this->GetParent();
    UiPoint pt(msg.ptMouse);
    pt.Offset(m_pTargetBox->GetScrollOffsetInScrollBox());
    if ((pParent == nullptr) || !m_pTargetBox->GetRect().ContainsPt(pt)) {
        return false;
    }
    size_t nIndex = Box::InvalidIndex;
    if (m_pDestControl != nullptr) {
        nIndex = m_pTargetBox->GetItemIndex(m_pDestControl);
    }
    if (nIndex == Box::InvalidIndex) {
        const size_t nCount = m_pTargetBox->GetItemCount();
        for (size_t nItem = 0; nItem < nCount; ++nItem) {
            Control* pControl = m_pTargetBox->GetItemAt(nItem);
            if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
                continue;
            }
            if (IsPtInControlRect(pControl, pt)) {
                nIndex = nItem;
                break;
            }
        }
    }
    if (nIndex < m_pTargetBox->GetItemCount()) {
        if (m_pDestControl != nullptr) {
            m_pTargetBox->RemoveItem(m_pDestControl);
            m_pDestControl = nullptr;
        }

        Box* pOldBox = pParent;
        size_t nOldItemIndex = pParent->GetItemIndex(this);
        Box* pNewBox = m_pTargetBox;
        size_t nNewItemIndex = nIndex;

        bool bAutoDestroyChild = pParent->IsAutoDestroyChild();
        pParent->SetAutoDestroyChild(false);
        pParent->RemoveItem(this);
        pParent->SetAutoDestroyChild(bAutoDestroyChild);

        this->SetVisible(true);
        m_pTargetBox->AddItem(this);
        m_pTargetBox->SetItemIndex(this, nIndex);
        m_pTargetBox = nullptr;

        //�����¼�
        OnItemBoxChanged(pOldBox, nOldItemIndex, pNewBox, nNewItemIndex);
        return true;
    }
    return false;
}

template<typename T>
void ControlDragableT<T>::OnItemBoxChanged(Box* /*pOldBox*/, size_t /*nOldItemIndex*/,
                                           Box* /*pNewBox*/, size_t /*nNewItemIndex*/)
{
}

template<typename T>
void ControlDragableT<T>::DragOrderMouseUp(const EventArgs& msg)
{
    if (!IsEnableDragOrder() || !IsInDraggingOrder()) {
        return;
    }
    //�ؼ��ڣ��϶��ı�˳��
    UiPoint pt(msg.ptMouse);
    pt.Offset(this->GetScrollOffsetInScrollBox());
    GetValidPointInItemRects(pt);
    size_t nOldItemIndex = Box::InvalidIndex;
    size_t nNewItemIndex = Box::InvalidIndex;
    bool bOrderChanged = AdjustItemOrders(pt, m_rcItemList, nOldItemIndex, nNewItemIndex);
    ClearDragStatus();
    if (bOrderChanged) {
        //�����н����¼�
        OnItemOrdersChanged(nOldItemIndex, nNewItemIndex);
    }
}

template<typename T>
bool ControlDragableT<T>::OnDragOutMouseOver(Box* pTargetBox, Box* pOldTargetBox, const UiPoint& ptMouse)
{
    bool bDropped = false;
    if ((pTargetBox == nullptr) || (pTargetBox->GetLayout() == nullptr)) {
        return bDropped;
    }
    if ((pOldTargetBox != nullptr) && (pOldTargetBox != pTargetBox) && (m_pDestControl != nullptr)) {
        //�Ӿɵ����Ƴ�
        size_t nIndex = pOldTargetBox->GetItemIndex(m_pDestControl);
        if (nIndex != Box::InvalidIndex) {
            if (pOldTargetBox->RemoveItem(m_pDestControl)) {
                m_pDestControl = nullptr;
            }
        }
    }

    UiPoint pt(ptMouse);
    pt.Offset(pTargetBox->GetScrollOffsetInScrollBox());
    const size_t nCount = pTargetBox->GetItemCount();
    for (size_t nIndex = 0; nIndex < nCount; ++nIndex) {
        Control* pControl = pTargetBox->GetItemAt(nIndex);
        if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
            continue;
        }
        if ((pControl == m_pDestControl) && (IsPtInControlRect(pControl, pt))) {
            //�����ָʾ�ؼ���
            bDropped = true;
            break;
        }
        if (IsPtInControlRect(pControl, pt)) {
            bDropped = true;
            if (m_pDestControl == nullptr) {
                m_pDestControl = CreateDestControl(pTargetBox);
            }
            if (m_pDestControl == nullptr) {
                break;
            }
            size_t nOldIndex = pTargetBox->GetItemIndex(m_pDestControl);
            if (nOldIndex == Box::InvalidIndex) {
                pTargetBox->AddItem(m_pDestControl);
            }
            UiRect rc = pControl->GetRect();
            if (pTargetBox->GetLayout()->IsHLayout()) {
                size_t nNewIndex = nIndex;
                if ((pt.x - rc.left) > rc.Width() / 2) {
                    if (nNewIndex < (pTargetBox->GetItemCount() - 1)) {
                        nNewIndex += 1;
                    }
                    if (nOldIndex != nNewIndex) {
                        pTargetBox->SetItemIndex(m_pDestControl, nNewIndex);
                    }
                }
                else {
                    if (nOldIndex != (nNewIndex - 1)) {
                        pTargetBox->SetItemIndex(m_pDestControl, nNewIndex);
                    }
                }
            }
            else {
                size_t nNewIndex = nIndex;
                if ((pt.y - rc.top) > rc.Height() / 2) {
                    if (nNewIndex < (pTargetBox->GetItemCount() - 1)) {
                        nNewIndex += 1;
                    }
                    if (nOldIndex != nNewIndex) {
                        pTargetBox->SetItemIndex(m_pDestControl, nNewIndex);
                    }
                }
                else {
                    if (nOldIndex != (nNewIndex - 1)) {
                        pTargetBox->SetItemIndex(m_pDestControl, nNewIndex);
                    }
                }
            }
            break;
        }
    }
    if (!bDropped && pTargetBox->GetRect().ContainsPt(pt)) {
        bDropped = true;
        if (m_pDestControl == nullptr) {
            m_pDestControl = CreateDestControl(pTargetBox);
        }
        size_t nOldIndex = pTargetBox->GetItemIndex(m_pDestControl);
        if (nOldIndex == Box::InvalidIndex) {
            pTargetBox->AddItem(m_pDestControl);
        }
    }
    return bDropped;
}

template<typename T>
DragWindow* ControlDragableT<T>::CreateDragWindow()
{
    return new DragWindow;
}

template<typename T>
Control* ControlDragableT<T>::CreateDestControl(Box* pTargetBox)
{
    Control* pDestControl = new Control;
    pDestControl->SetAttribute(L"bkcolor", L"#FF5D6B99");
    pDestControl->SetAttribute(L"valign", L"center");
    pDestControl->SetAttribute(L"halign", L"center");

    Layout* pLayout = nullptr;
    if (pTargetBox != nullptr) {
        pLayout = pTargetBox->GetLayout();
    }
    bool bInited = false;
    if ((pLayout != nullptr) && pLayout->IsTileLayout()) {
        UiSize szItem;
        szItem.cx = this->GetFixedWidth().GetInt32();
        szItem.cy = this->GetFixedHeight().GetInt32();
        if ((szItem.cx > 0) && (szItem.cy > 0)) {
            pDestControl->SetAlpha(128);
            pDestControl->SetFixedHeight(UiFixedInt(szItem.cy), false, false);
            pDestControl->SetFixedWidth(UiFixedInt(szItem.cx), false, false);
            bInited = true;
        }
    }
    if (!bInited) {        
        if (pLayout->IsVLayout()) {
            pDestControl->SetAttribute(L"height", L"4");
            pDestControl->SetAttribute(L"width", L"80%");
        }
        else {
            pDestControl->SetAttribute(L"width", L"4");
            pDestControl->SetAttribute(L"height", L"80%");
        }
    }
    return pDestControl;
}

template<typename T>
std::shared_ptr<IBitmap> ControlDragableT<T>::CreateDragoutImage()
{
    UiRect rc = this->GetRect();
    if (rc.IsEmpty()) {
        return nullptr;
    }
    std::unique_ptr<IRender> render;
    IRenderFactory* pRenderFactory = GlobalManager::Instance().GetRenderFactory();
    ASSERT(pRenderFactory != nullptr);
    if (pRenderFactory != nullptr) {
        render.reset(pRenderFactory->CreateRender());
    }
    ASSERT(render != nullptr);
    // const int32_t kDragImageWidth = GlobalManager::Instance().Dpi().GetScaleInt(90);
    // const int32_t kDragImageHeight = GlobalManager::Instance().Dpi().GetScaleInt(90);
    const int32_t kDragImageWidth = rc.Width();
    const int32_t kDragImageHeight = rc.Height();
    if (render->Resize(kDragImageWidth, kDragImageHeight)) {
        int32_t destWidth = 0;
        int32_t destHeight = 0;
        float scale = (float)rc.Width() / (float)rc.Height();
        if (scale >= 1.0) {
            destWidth = kDragImageWidth;
            destHeight = (int32_t)(kDragImageWidth * (float)rc.Height() / (float)rc.Width());
        }
        else {
            destHeight = kDragImageHeight;
            destWidth = (int32_t)(kDragImageHeight * (float)rc.Width() / (float)rc.Height());
        }
        render->AlphaBlend((kDragImageWidth - destWidth) / 2, 0, destWidth, destHeight,
            this->GetWindow()->GetRender(),
            rc.left, rc.top, rc.Width(), rc.Height());
    }
    std::shared_ptr<IBitmap> pDragImage(render->DetachBitmap());
    return pDragImage;
}

template<typename T>
bool ControlDragableT<T>::IsPtInControlRect(Control* pControl, const UiPoint& pt) const
{
    if (pControl == nullptr) {
        return false;
    }
    UiRect rc = pControl->GetRect();
    if (rc.ContainsPt(pt)) {
        return true;
    }
    UiMargin rcMargin = pControl->GetMargin();
    rc.Inflate(rcMargin);
    if (rc.ContainsPt(pt)) {
        return true;
    }
    Layout* pLayout = nullptr;
    Box* pBox = pControl->GetParent();
    if (pBox != nullptr) {
        pLayout = pBox->GetLayout();
    }
    if (pLayout != nullptr) {
        int32_t nChildMarginX = pLayout->GetChildMarginX() / 2;
        int32_t nChildMarginY = pLayout->GetChildMarginY() / 2;
        if ((nChildMarginX > 0) || (nChildMarginY > 0)) {
            rc = pControl->GetRect();
            rc.left -= nChildMarginX;
            rc.right += nChildMarginX;
            rc.top -= nChildMarginY;
            rc.bottom += nChildMarginY;
            if (rc.ContainsPt(pt)) {
                return true;
            }
        }
    }
    return false;
}

template<typename T>
void ControlDragableT<T>::DragOrderMouseDown(const EventArgs& /*msg*/)
{
    m_rcItemList.clear();
    if (!IsEnableDragOrder()) {
        return;
    }
    Box* pParent = this->GetParent();
    if (pParent == nullptr) {
        return;
    }
    //�ؼ��ڵ�˳���������¼ÿ���ؼ���ԭʼλ����Ϣ
    size_t nItemCount = pParent->GetItemCount();
    for (size_t index = 0; index < nItemCount; ++index) {
        ItemStatus itemStatus;
        itemStatus.m_index = index;
        itemStatus.m_pItem = pParent->GetItemAt(index);
        if (itemStatus.m_pItem != nullptr) {
            itemStatus.m_rcPos = itemStatus.m_pItem->GetRect();
            itemStatus.m_nPaintOrder = itemStatus.m_pItem->GetPaintOrder();
            m_rcItemList.push_back(itemStatus);
        }
        if (itemStatus.m_pItem == this) {
            //��ǰ�ؼ�������˳����Ҫ����󣬱��ⱻ�����ؼ��ڵ�
            itemStatus.m_pItem->SetPaintOrder(255);
            ASSERT(itemStatus.m_rcPos.ContainsPt(m_ptMouseDown));
        }
    }
}

template<typename T>
bool ControlDragableT<T>::DragOrderMouseMove(const EventArgs& msg)
{
    bool bRet = false;
    if (!IsEnableDragOrder()) {
        //�ÿؼ���ֹ�϶�����
        return bRet;
    }    
    Box* pParent = this->GetParent();
    if (pParent == nullptr) {
        return bRet;
    }
    Layout* pLayout = pParent->GetLayout();
    if ((pLayout == nullptr) || pLayout->IsTileLayout() || (!pLayout->IsHLayout() && !pLayout->IsVLayout())) {
        return bRet;
    }
    UiPoint pt(msg.ptMouse);
    pt.Offset(this->GetScrollOffsetInScrollBox());
    GetValidPointInItemRects(pt);
    if (pLayout->IsHLayout()) {
        int32_t xOffset = pt.x - m_ptMouseDown.x;
        if (std::abs(xOffset) < GlobalManager::Instance().Dpi().GetScaleInt(3)) {
            return bRet;
        }
        //���������ؼ���λ��
        AdjustItemPos(pt, m_ptMouseDown, m_rcItemList);

        UiRect rect = m_rcMouseDown;
        rect.left += xOffset;
        rect.right += xOffset;

        this->SetPos(rect);
    }
    else {
        int32_t yOffset = pt.y - m_ptMouseDown.y;
        if (std::abs(yOffset) < GlobalManager::Instance().Dpi().GetScaleInt(3)) {
            return bRet;
        }
        //���������ؼ���λ��
        AdjustItemPos(pt, m_ptMouseDown, m_rcItemList);

        UiRect rect = m_rcMouseDown;
        rect.top += yOffset;
        rect.bottom += yOffset;
        this->SetPos(rect);
    }

    if (!m_bInDraggingOrder) {
        bRet = true;
        m_bInDraggingOrder = true;
        m_nOldAlpha = (uint8_t)this->GetAlpha();
        //����Ϊ��͸����Ч��
        this->SetAlpha(m_nDragAlpha);
    }
    return bRet;
}

template<typename T>
bool ControlDragableT<T>::DragOutMouseMove(const EventArgs& msg)
{
    bool bRet = false;
    if (!IsEnableDragOut()) {
        //�ÿؼ���ֹ�ϳ�����
        return bRet;
    }
    Window* pWindow = this->GetWindow();
    Box* pParent = this->GetParent();
    if ((pParent == nullptr) || (pWindow == nullptr)) {
        return bRet;
    }
    if (pParent->GetDragOutId() == 0) {
        //��������֧���ϳ�����
        return bRet;
    }
    Layout* pLayout = pParent->GetLayout();
    if ((pLayout == nullptr) || (!pLayout->IsHLayout() && !pLayout->IsVLayout())) {
        return bRet;
    }
    UiPoint pt(msg.ptMouse);
    pt.Offset(this->GetScrollOffsetInScrollBox());
    if (!IsInDraggingOut()) {
        int32_t xOffset = pt.x - m_ptMouseDown.x;
        int32_t yOffset = pt.y - m_ptMouseDown.y;
        int32_t nMinOffset = GlobalManager::Instance().Dpi().GetScaleInt(5);
        if ((std::abs(xOffset) < nMinOffset) && (std::abs(yOffset) < nMinOffset)) {
            return bRet;
        }
    }

    std::shared_ptr<IBitmap> pDragImage = m_pDragImage;
    if (pDragImage == nullptr) {
        pDragImage = CreateDragoutImage();
        m_pDragImage = pDragImage;
    }

    bool bDropped = false;
    Box* pOldTargetBox = m_pTargetBox;
    m_pTargetBox = pWindow->FindDroppableBox(msg.ptMouse, pParent->GetDragOutId());
    if (m_pTargetBox != nullptr) {
        bDropped = OnDragOutMouseOver(m_pTargetBox, pOldTargetBox, msg.ptMouse);
    }
    if (!bDropped) {
        if ((m_pDestControl != nullptr) && (m_pTargetBox != nullptr)) {
            if (m_pTargetBox->RemoveItem(m_pDestControl)) {
                m_pDestControl = nullptr;
            }
        }
        if ((m_pDestControl != nullptr) && (pOldTargetBox != nullptr)) {
            if (pOldTargetBox->RemoveItem(m_pDestControl)) {
                m_pDestControl = nullptr;
            }
        }
        if (m_pDestControl != nullptr) {
            delete m_pDestControl;
            m_pDestControl = nullptr;
        }
    }
    if (!bDropped) {
        m_pTargetBox = nullptr;
    }

    //�ϳ�������
    if ((m_pDragWindow == nullptr) || m_pDragWindow->IsClosingWnd()) {
        if (m_pDragWindow != nullptr) {
            m_pDragWindow->Release();
            m_pDragWindow = nullptr;
        }
        m_pDragWindow = CreateDragWindow();
        ASSERT(m_pDragWindow != nullptr);
        if (m_pDragWindow != nullptr) {
            m_pDragWindow->AddRef();
            m_pDragWindow->CreateWnd(this->GetWindow()->GetHWND(), L"", WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_LAYERED);
            if (m_pDragWindow->IsWindow()) {
                m_pDragWindow->AddRef();
            }
            m_pDragWindow->SetDragImage(pDragImage);
        }
    }
    if (m_pDragWindow != nullptr) {
        m_pDragWindow->AdjustPos();
    }
    if (this->IsVisible()) {
        this->SetVisible(false);
    }    
    bRet = true;
    return bRet;
}

typedef ControlDragableT<Control> ControlDragable;
typedef ControlDragableT<Box> BoxDragable;
typedef ControlDragableT<HBox> HBoxDragable;
typedef ControlDragableT<VBox> VBoxDragable;

}

#endif // UI_CORE_CONTROL_DRAGABLE_H_