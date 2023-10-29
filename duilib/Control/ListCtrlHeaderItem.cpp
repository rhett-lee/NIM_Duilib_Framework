#include "ListCtrlHeaderItem.h"
#include "ListCtrl.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Render/IRender.h"

namespace ui
{
ListCtrlHeaderItem::ListCtrlHeaderItem() :
    m_pSortedDownImage(nullptr),
    m_pSortedUpImage(nullptr),
    m_sortMode(SortMode::kDown),
    m_pSplitBox(nullptr),
    m_bColumnResizeable(true),
    m_nColumnWidth(0),
    m_bMouseDown(false),
    m_bInDragging(false),
    m_nOldAlpha(255),
    m_bShowIconAtTop(true),
    m_bColumnVisible(true)
{
    m_nIconSpacing = GlobalManager::Instance().Dpi().GetScaleInt(6);
}

ListCtrlHeaderItem::~ListCtrlHeaderItem()
{
    if (m_pSortedDownImage != nullptr) {
        delete m_pSortedDownImage;
        m_pSortedDownImage = nullptr;
    }
    if (m_pSortedUpImage != nullptr) {
        delete m_pSortedUpImage;
        m_pSortedUpImage = nullptr;
    }
}
 
std::wstring ListCtrlHeaderItem::GetType() const { return L"ListCtrlHeaderItem"; }

void ListCtrlHeaderItem::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"sorted_up_image") {
        SetSortedUpImage(strValue);
    }
    else if (strName == L"sorted_down_image") {
        SetSortedDownImage(strValue);
    }
    else if (strName == L"icon_spacing") {
        SetIconSpacing(_wtoi(strValue.c_str()), true);
    }
    else if (strName == L"show_icon_at_top") {
        SetShowIconAtTop(strValue == L"true");
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

void ListCtrlHeaderItem::PaintText(IRender* pRender)
{
    __super::PaintText(pRender);
    if (pRender == nullptr) {
        return;
    }

    Image* pImage = nullptr;
    if (m_sortMode == SortMode::kUp) {
        //����
        pImage = m_pSortedUpImage;
    }
    else if (m_sortMode == SortMode::kDown) {
        //����
        pImage = m_pSortedDownImage;
    }
    if (pImage == nullptr) {
        return;
    }
    
    //ȷ������ͼ���λ��
    UiRect rc = GetRect();
    UiPadding rcPadding = GetControlPadding();
    rc.Deflate(rcPadding);
    if (IsShowIconAtTop()) {
        //ͼ����ʾ�����ֵ��Ϸ���������ʾ
        int32_t nImageWidth = 0;
        int32_t nImageHeight = 0;
        if (pImage != nullptr) {
            if (pImage->GetImageCache() == nullptr) {
                LoadImageData(*pImage);
            }
            if (pImage->GetImageCache() != nullptr) {
                nImageWidth = pImage->GetImageCache()->GetWidth();
                nImageHeight = pImage->GetImageCache()->GetHeight();
            }
        }
        if (nImageWidth > 0) {
            rc.left = rc.CenterX() - nImageWidth / 2;
            rc.right = rc.left + nImageWidth;
        }
        if (nImageHeight > 0) {
            rc.bottom = rc.top + nImageHeight;
        }
    }
    else {
        //ͼ����ʾ�����ֵĺ��棨��������룬���ж��룩������ǰ�棨���ֿ��Ҷ��룩
        rc.Deflate(GetTextPadding());
        int32_t nIconTextSpacing = GetIconSpacing();
        uint32_t textStyle = GetTextStyle();
        std::wstring textValue = GetText();
        UiRect textRect = pRender->MeasureString(textValue, GetFontId(), textStyle);
        if (textStyle & TEXT_CENTER) {
            rc.left = rc.CenterX() + textRect.Width() / 2;
            rc.left += nIconTextSpacing;
        }
        else if (textStyle & TEXT_RIGHT) {
            rc.left = rc.right - textRect.Width() - nIconTextSpacing;
            if (pImage != nullptr) {
                if (pImage->GetImageCache() == nullptr) {
                    LoadImageData(*pImage);
                }
                if (pImage->GetImageCache() != nullptr) {
                    rc.left -= pImage->GetImageCache()->GetWidth();
                }
            }
        }
        else {
            rc.left += textRect.Width();
            rc.left += nIconTextSpacing;
        }
    }
    rc.Validate();

    //��������ͼ��
    PaintImage(pRender, pImage, L"", -1, nullptr, &rc, nullptr);
}

void ListCtrlHeaderItem::Activate()
{
    if (m_bInDragging) {
        //�����϶��ı���˳���״̬
        return;
    }
    if (!this->IsActivatable()) {
        return;
    }
    bool bSortChanged = false;
    if (m_sortMode == SortMode::kUp) {
        m_sortMode = SortMode::kDown;
        bSortChanged = true;
        Invalidate();
    }
    else if (m_sortMode == SortMode::kDown) {
        m_sortMode = SortMode::kUp;
        bSortChanged = true;
        Invalidate();        
    }

    if (bSortChanged) {
        ListCtrlHeader* pHeader = dynamic_cast<ListCtrlHeader*>(GetParent());
        ASSERT(pHeader != nullptr);
        if (pHeader != nullptr) {
            pHeader->OnHeaderColumnSorted(this);
        }
    }
    __super::Activate();
}

void ListCtrlHeaderItem::SetFadeVisible(bool bVisible)
{
    __super::SetFadeVisible(bVisible);
}

void ListCtrlHeaderItem::SetVisible(bool bVisible)
{
    __super::SetVisible(bVisible);
}

void ListCtrlHeaderItem::SetSortMode(SortMode sortMode, bool bTriggerEvent)
{
    if (m_sortMode != sortMode) {
        m_sortMode = sortMode;
        Invalidate();
        if (bTriggerEvent && (m_sortMode != SortMode::kNone)) {
            ListCtrlHeader* pHeader = dynamic_cast<ListCtrlHeader*>(GetParent());
            ASSERT(pHeader != nullptr);
            if (pHeader != nullptr) {
                pHeader->OnHeaderColumnSorted(this);
            }
        } 
    }
}

ListCtrlHeaderItem::SortMode ListCtrlHeaderItem::GetSortMode() const
{
    return m_sortMode;
}

void ListCtrlHeaderItem::SetSortedDownImage(const std::wstring& sImageString)
{
    if (m_pSortedDownImage == nullptr) {
        m_pSortedDownImage = new Image;
    }
    m_pSortedDownImage->SetImageString(sImageString);
    Invalidate();
}

void ListCtrlHeaderItem::SetSortedUpImage(const std::wstring& sImageString)
{
    if (m_pSortedUpImage == nullptr) {
        m_pSortedUpImage = new Image;
    }
    m_pSortedUpImage->SetImageString(sImageString);
    Invalidate();
}

size_t ListCtrlHeaderItem::GetColomnId() const
{
    return (size_t)this;
}

void ListCtrlHeaderItem::SetSplitBox(SplitBox* pSplitBox)
{
    m_pSplitBox = pSplitBox;
    if (pSplitBox != nullptr) {
        ASSERT(pSplitBox->GetFixedWidth().IsInt32());
        pSplitBox->SetEnabled(IsColumnResizeable() ? true : false);
    }
    if (GetColumnWidth() > 0) {
        CheckColumnWidth();
    }
}

SplitBox* ListCtrlHeaderItem::GetSplitBox() const
{
    return m_pSplitBox;
}

void ListCtrlHeaderItem::SetColumnResizeable(bool bResizeable)
{
    m_bColumnResizeable = bResizeable;
    if (m_pSplitBox != nullptr) {
        m_pSplitBox->SetEnabled(IsColumnResizeable() ? true : false);
    }
}

bool ListCtrlHeaderItem::IsColumnResizeable() const
{
    return m_bColumnResizeable;
}

void ListCtrlHeaderItem::SetColumnWidth(int32_t nWidth, bool bNeedDpiScale)
{
    if (nWidth < 0) {
        nWidth = 0;
    }
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleInt(nWidth);
    }
    m_nColumnWidth = nWidth;
    CheckColumnWidth();
}

int32_t ListCtrlHeaderItem::GetColumnWidth() const
{
    return m_nColumnWidth;
}

void ListCtrlHeaderItem::CheckColumnWidth()
{
    int32_t nSplitWidth = 0;
    if (m_pSplitBox != nullptr) {
        ASSERT(m_pSplitBox->GetFixedWidth().IsInt32());
        nSplitWidth = m_pSplitBox->GetFixedWidth().GetInt32();
    }
    int32_t nWidth = GetFixedWidth().GetInt32();
    if ((nWidth + nSplitWidth) != GetColumnWidth()) {
        nWidth = GetColumnWidth() - nSplitWidth;
        if (nWidth < 0) {
            nWidth = 0;
        }
        SetFixedWidth(UiFixedInt(nWidth), true, false);
    }
}

void ListCtrlHeaderItem::SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale)
{
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleInt(nIconSpacing);
    }
    m_nIconSpacing = nIconSpacing;
    if (m_nIconSpacing < 0) {
        m_nIconSpacing = 0;
    }
    Invalidate();
}

int32_t ListCtrlHeaderItem::GetIconSpacing() const
{
    return m_nIconSpacing;
}

void ListCtrlHeaderItem::SetShowIconAtTop(bool bShowIconAtTop)
{
    m_bShowIconAtTop = bShowIconAtTop;
    Invalidate();
}

bool ListCtrlHeaderItem::IsShowIconAtTop() const
{
    return m_bShowIconAtTop;
}

void ListCtrlHeaderItem::SetTextHorAlign(HorAlignType alignType)
{
    uint32_t textStyle = GetTextStyle();
    if (alignType == HorAlignType::kHorAlignCenter) {
        //�ı������ж���
        textStyle &= ~(TEXT_LEFT | TEXT_RIGHT);
        textStyle |= TEXT_CENTER;
    }
    else if (alignType == HorAlignType::kHorAlignRight) {
        //�ı����Ҷ���
        textStyle &= ~(TEXT_LEFT | TEXT_CENTER);
        textStyle |= TEXT_RIGHT;
    }
    else {
        //�ı��������
        textStyle &= ~(TEXT_CENTER | TEXT_RIGHT);
        textStyle |= TEXT_LEFT;
    }
    SetTextStyle(textStyle, true);
}

HorAlignType ListCtrlHeaderItem::GetTextHorAlign() const
{
    HorAlignType alignType = HorAlignType::kHorAlignLeft;//�ı��������
    uint32_t textStyle = GetTextStyle();
    if (textStyle & TEXT_CENTER) {
        //�ı������ж���
        alignType = HorAlignType::kHorAlignCenter;
    }
    else if (textStyle & TEXT_RIGHT) {
        //�ı����Ҷ���
        alignType = HorAlignType::kHorAlignRight;
    }
    return alignType;
}

bool ListCtrlHeaderItem::SetCheckBoxVisible(bool bVisible)
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            pCheckBox->SetVisible(bVisible);
            return true;
        }
    }
    return false;
}

bool ListCtrlHeaderItem::IsCheckBoxVisible() const
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            return pCheckBox->IsVisible();
        }
    }
    return false;
}

bool ListCtrlHeaderItem::HasCheckBox() const
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            return true;
        }
    }
    return false;
}

bool ListCtrlHeaderItem::SetCheckBoxSelect(bool bSelected, bool bPartSelect)
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            pCheckBox->SetSelected(bSelected);
            if (bSelected) {
                pCheckBox->SetPartSelected(bPartSelect);
            }
            pCheckBox->Invalidate();
            return true;
        }
    }
    return false;
}

void ListCtrlHeaderItem::SetColumnVisible(bool bColumnVisible)
{
    m_bColumnVisible = bColumnVisible;
    SetVisible(bColumnVisible);
    if (m_pSplitBox != nullptr) {
        m_pSplitBox->SetVisible(bColumnVisible);
    }
    ListCtrlHeader* pHeader = dynamic_cast<ListCtrlHeader*>(GetParent());
    ASSERT(pHeader != nullptr);
    if (pHeader != nullptr) {
        pHeader->OnHeaderColumnVisibleChanged();
    }
}

bool ListCtrlHeaderItem::IsColumnVisible() const
{
    //�б���IsVisible(), ����ͷ���ص�ʱ��IsVisible()Ҳ�᷵��false
    return m_bColumnVisible;
}

bool ListCtrlHeaderItem::ButtonDown(const EventArgs& msg)
{
    bool bRet = __super::ButtonDown(msg);
    ListCtrlHeader* pParentBox = dynamic_cast<ListCtrlHeader*>(GetParent());
    ASSERT(pParentBox != nullptr);
    if (pParentBox == nullptr) {
        return bRet;
    }
    if (!pParentBox->IsEnableHeaderDragOrder()) {
        //��֧���϶�����˳��
        return bRet;
    }
    UiPoint pt(msg.ptMouse);
    pt.Offset(GetScrollOffsetInScrollBox());

    m_bMouseDown = true;
    m_ptMouseDown = pt;
    m_rcMouseDown = GetRect();
    
    m_rcItemList.clear();
    size_t nItemCount = pParentBox->GetItemCount();
    for (size_t index = 0; index < nItemCount; ++index) {
        ItemStatus itemStatus;
        itemStatus.m_index = index;
        itemStatus.m_pItem = pParentBox->GetItemAt(index);
        if (itemStatus.m_pItem != nullptr) {
            itemStatus.m_rcPos = itemStatus.m_pItem->GetRect();
            m_rcItemList.push_back(itemStatus);
        }
        if (itemStatus.m_pItem == this) {
            ASSERT(itemStatus.m_rcPos.ContainsPt(m_ptMouseDown));
        }
    }
    return bRet;
}

bool ListCtrlHeaderItem::ButtonUp(const EventArgs& msg)
{
    bool bRet = __super::ButtonUp(msg);
    Box* pParentBox = dynamic_cast<Box*>(GetParent());
    if (pParentBox == nullptr) {
        ClearDragStatus();
        return bRet;
    }

    UiPoint pt(msg.ptMouse);
    pt.Offset(GetScrollOffsetInScrollBox());

    bool bOrderChanged = false;
    const size_t itemCount = pParentBox->GetItemCount();
    size_t nMouseItemIndex = Box::InvalidIndex;
    size_t nCurrentItemIndex = Box::InvalidIndex;
    for (const ItemStatus& itemStatus : m_rcItemList) {
        if (itemStatus.m_rcPos.ContainsPt(pt)) {
            nMouseItemIndex = itemStatus.m_index;
        }
        if ((itemStatus.m_pItem == this) && !itemStatus.m_rcPos.ContainsPt(pt)){
            nCurrentItemIndex = itemStatus.m_index;
        }
    }
    if ((nMouseItemIndex != Box::InvalidIndex) && 
        (nCurrentItemIndex != Box::InvalidIndex) &&
        (nMouseItemIndex < itemCount) &&
        (nCurrentItemIndex < itemCount)) {
        //�����ؼ���λ��
        if (nMouseItemIndex < nCurrentItemIndex) {
            //����ཻ��
            pParentBox->SetItemIndex(this, nMouseItemIndex);
            if (m_pSplitBox != nullptr) {
                size_t nNewIndex = pParentBox->GetItemIndex(this);
                ASSERT(nNewIndex < itemCount);
                ASSERT((nNewIndex + 1) < itemCount);
                if ((nNewIndex + 1) < itemCount) {
                    pParentBox->SetItemIndex(m_pSplitBox, nNewIndex + 1);
                }
            }
        }
        else {
            //���Ҳཻ��
            nMouseItemIndex += 1;
            ASSERT(nMouseItemIndex < itemCount);
            if (nMouseItemIndex < itemCount) {
                pParentBox->SetItemIndex(this, nMouseItemIndex);
                if (m_pSplitBox != nullptr) {
                    size_t nNewIndex = pParentBox->GetItemIndex(this);
                    ASSERT(nNewIndex < itemCount);
                    pParentBox->SetItemIndex(m_pSplitBox, nNewIndex);
                }
            }
        }
        bOrderChanged = true;
        ASSERT(pParentBox->GetItemIndex(this) == (pParentBox->GetItemIndex(m_pSplitBox) - 1));

        //�����󣬶����е������У��
        for (size_t index = 0; index < itemCount; index += 2) {
            ASSERT(dynamic_cast<ListCtrlHeaderItem*>(pParentBox->GetItemAt(index)) != nullptr);
            ASSERT((index + 1) < itemCount);
            if ((index + 1) >= itemCount) {
                break;
            }
            ASSERT(dynamic_cast<SplitBox*>(pParentBox->GetItemAt(index + 1)) != nullptr);
            ASSERT(dynamic_cast<SplitBox*>(pParentBox->GetItemAt(index + 1)) == 
                   dynamic_cast<ListCtrlHeaderItem*>(pParentBox->GetItemAt(index))->m_pSplitBox);
        }
    }
    ClearDragStatus();

    if (bOrderChanged) {
        //�����н����¼�
        ListCtrlHeader* pHeader = dynamic_cast<ListCtrlHeader*>(GetParent());
        ASSERT(pHeader != nullptr);
        if (pHeader != nullptr) {
            pHeader->OnHeaderColumnOrderChanged();
        }
    }
    return bRet;
}

bool ListCtrlHeaderItem::MouseMove(const EventArgs& msg)
{
    bool bRet = __super::MouseMove(msg);
    if (!m_bMouseDown) {
        return bRet;
    }
    Control* pParent = GetParent();
    if (pParent == nullptr) {
        return bRet;
    }
    UiPoint pt(msg.ptMouse);
    pt.Offset(GetScrollOffsetInScrollBox());
    int32_t xOffset = pt.x - m_ptMouseDown.x;
    if (std::abs(xOffset) < GlobalManager::Instance().Dpi().GetScaleInt(2)) {
        return bRet;
    }

    UiRect boxRect = pParent->GetRect();
    if ((pt.x >= boxRect.left) && (pt.x < boxRect.right)) {
        UiRect rect = m_rcMouseDown;
        rect.left += xOffset;
        rect.right += xOffset;
        SetPos(rect);

        if (!m_bInDragging) {
            m_bInDragging = true;
            m_nOldAlpha = (uint8_t)GetAlpha();
            //����Ϊ��͸����Ч��
            SetAlpha(216);
        }

        AdjustHeaderItemPos(pt);
    }
    return bRet;
}

bool ListCtrlHeaderItem::OnWindowKillFocus(const EventArgs& msg)
{
    bool bRet = __super::OnWindowKillFocus(msg);
    ClearDragStatus();
    return bRet;
}

void ListCtrlHeaderItem::AdjustHeaderItemPos(const UiPoint& mousePt)
{
    Control* pMouseItem = nullptr;
    size_t nMouseItemIndex = Box::InvalidIndex;
    size_t nMouseDownItemIndex = Box::InvalidIndex;
    for (const ItemStatus& itemStatus : m_rcItemList) {
        if (itemStatus.m_rcPos.ContainsPt(mousePt)) {
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
    if (dynamic_cast<ListCtrlHeaderItem*>(pMouseItem) == nullptr) {
        //��겻�ڱ�ͷ�ؼ���
        return;
    }

    const size_t itemCount = m_rcItemList.size();
    int32_t xOffset = mousePt.x - m_ptMouseDown.x;
    if (pMouseItem == this) {
        //��ǰ���λ�ã���������λ�ã��ָ������ؼ���ʵ��λ��
        for (ItemStatus& item : m_rcItemList) {
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
            ItemStatus& item = m_rcItemList[index];
            if (item.m_pItem == this) {
                //�ָ�������Split�ؼ�λ��
                if ((index + 1) < itemCount) {
                    const ItemStatus& nextItem = m_rcItemList[index + 1];
                    if ((nextItem.m_pItem->GetRect() != nextItem.m_rcPos)) {
                        nextItem.m_pItem->SetPos(nextItem.m_rcPos);
                    }
                }
                continue;
            }
            else if ((item.m_index >= nMouseItemIndex) && (item.m_index < nMouseDownItemIndex)) {
                //���Ҳ��ƶ�
                if ((index + 2) < itemCount) {
                    const ItemStatus& nextItem = m_rcItemList[index + 2];
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
            ItemStatus& item = m_rcItemList[index];
            if (item.m_pItem == this) {
                //�ָ�������Split�ؼ�λ��
                if ((index + 1) < itemCount) {
                    const ItemStatus& nextItem = m_rcItemList[index + 1];
                    if ((nextItem.m_pItem->GetRect() != nextItem.m_rcPos)) {
                        nextItem.m_pItem->SetPos(nextItem.m_rcPos);
                    }
                }
                continue;
            }
            else if ((item.m_index > nMouseDownItemIndex) && (item.m_index <= nMouseItemIndex)) {
                //������ƶ�
                if ((index - 2) < itemCount) {
                    const ItemStatus& nextItem = m_rcItemList[index - 2];
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

void ListCtrlHeaderItem::ClearDragStatus()
{
    if (m_bInDragging) {
        SetAlpha(m_nOldAlpha);
        m_nOldAlpha = 255;
        m_bInDragging = false;
    }
    m_bMouseDown = false;
    if (!m_rcItemList.empty()) {
        m_rcItemList.clear();
        if (GetParent() != nullptr) {
            GetParent()->Invalidate();
            GetParent()->SetPos(GetParent()->GetPos());
        }
    }
}

}//namespace ui
