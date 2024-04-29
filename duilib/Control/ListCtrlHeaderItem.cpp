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
    m_bShowIconAtTop(true),
    m_bColumnVisible(true),
    m_imageId(-1),
    m_pHeaderCtrl(nullptr)
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
    //��Ҫ���Ƶ����ݰ�����ͼ�ꡢ���֡�����ͼ��
    if (pRender == nullptr) {
        return;
    }
    //�ı�ǰ��ͼ��
    ImagePtr pItemImage;
    UiSize itemImageSize;
    if ((m_imageId >= 0) && (m_pHeaderCtrl != nullptr)) {
        ListCtrl* pListCtrl = m_pHeaderCtrl->GetListCtrl();
        if (pListCtrl != nullptr) {
            ImageList* pImageList = pListCtrl->GetImageList(ListCtrlType::Report);
            if (pImageList != nullptr) {
                itemImageSize = pImageList->GetImageSize();
                pItemImage = pImageList->GetImageData(m_imageId);
                ASSERT(pItemImage != nullptr);
            }
        }
    }
    if ((pItemImage != nullptr) && (pItemImage->GetImageCache() == nullptr)) {
        LoadImageData(*pItemImage);
        if (pItemImage->GetImageCache() == nullptr) {
            pItemImage = nullptr;
        }
        else {
            if ((pItemImage->GetImageCache()->GetWidth() <= 0) ||
                (pItemImage->GetImageCache()->GetHeight() <= 0)) {
                pItemImage = nullptr;
            }
        }
    }

    //����ͼ��
    Image* pSortImage = nullptr;
    if (m_sortMode == SortMode::kUp) {
        //����
        pSortImage = m_pSortedUpImage;
    }
    else if (m_sortMode == SortMode::kDown) {
        //����
        pSortImage = m_pSortedDownImage;
    }
    if ((pSortImage != nullptr) && (pSortImage->GetImageCache() == nullptr)) {
        LoadImageData(*pSortImage);
        if (pSortImage->GetImageCache() == nullptr) {
            pSortImage = nullptr;
        }
        else {
            if ((pSortImage->GetImageCache()->GetWidth() <= 0) ||
                (pSortImage->GetImageCache()->GetHeight() <= 0)) {
                pSortImage = nullptr;
            }
        }
    }

    if ((pSortImage != nullptr) && IsShowIconAtTop()) {
        //ͼ����ʾ�����ֵ��Ϸ���������ʾ
        UiRect rc = GetRect();
        rc.Deflate(GetControlPadding());
        int32_t nImageWidth = pSortImage->GetImageCache()->GetWidth();
        int32_t nImageHeight = pSortImage->GetImageCache()->GetHeight();
        rc.left = rc.CenterX() - nImageWidth / 2;
        rc.right = rc.left + nImageWidth;
        if (!(GetTextStyle() & TEXT_VCENTER) && !(GetTextStyle() & TEXT_BOTTOM)) {
            rc.top = rc.bottom - nImageHeight;
        }
        else {
            rc.bottom = rc.top + nImageHeight;
        }

        //��������ͼ��
        PaintImage(pRender, pSortImage, L"", -1, nullptr, &rc, nullptr);
        pSortImage = nullptr;
    }

    if ((pSortImage == nullptr) && (pItemImage == nullptr)) {
        __super::PaintText(pRender);
        return;
    }

    if (pItemImage != nullptr) {
        if (itemImageSize.cx <= 0) {
            itemImageSize.cx = pItemImage->GetImageCache()->GetWidth();
        }
        if (itemImageSize.cy <= 0) {
            itemImageSize.cy = pItemImage->GetImageCache()->GetHeight();
        }
    }

    UiSize sortImageSize;
    if (pSortImage != nullptr) {
        sortImageSize.cx = pSortImage->GetImageCache()->GetWidth();
        sortImageSize.cy = pSortImage->GetImageCache()->GetHeight();
    }

    int32_t nIconTextSpacing = GetIconSpacing();
    //CheckBox�Ŀ�ȣ���Ҫ������
    int32_t nCheckBoxWidth = 0;
    ListCtrlCheckBox* pCheckBox = nullptr;
    if (GetItemCount() > 0) {
        pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
    }
    if ((pCheckBox != nullptr) && pCheckBox->IsVisible()) {
        UiSize sz = pCheckBox->GetStateImageSize(kStateImageBk, kControlStateNormal);
        nCheckBoxWidth += sz.cx;
        nCheckBoxWidth += nIconTextSpacing;
    }

    uint32_t textStyle = GetTextStyle();
    UiRect measureRect = pRender->MeasureString(GetText(), GetFontId(), textStyle);
    UiRect rcItemRect = GetRect();
    rcItemRect.Deflate(GetControlPadding());
    if (nCheckBoxWidth > 0) {
        rcItemRect.left += nCheckBoxWidth;
        rcItemRect.Validate();
    }
    
    if ((sortImageSize.cx + itemImageSize.cx + measureRect.Width()) > rcItemRect.Width()) {
        //����Ŀռ䲻�㣬����������
        nIconTextSpacing = 0;
        textStyle = TEXT_LEFT;
    }
    
    UiRect rc = GetRect();
    rc.Deflate(GetControlPadding());
    if (nCheckBoxWidth > 0) {
        rc.left += nCheckBoxWidth;
        rc.Validate();
    }
    if (textStyle & TEXT_CENTER) {
        //���ж���
        UiRect textRect = GetRect();
        textRect.Deflate(GetControlPadding());
        textRect.Deflate(GetTextPadding());
        if (pItemImage != nullptr) {
            UiRect itemRect = rc;
            itemRect.left = textRect.CenterX() - measureRect.Width() / 2;
            itemRect.left -= nIconTextSpacing;
            itemRect.left -= itemImageSize.cx;
            itemRect.left = std::max(itemRect.left, rc.left);
            itemRect.Validate();
            itemRect.right = itemRect.left + itemImageSize.cx;
            VAlignRect(itemRect, GetTextStyle(), itemImageSize.cy);
            PaintImage(pRender, pItemImage.get(), L"", -1, nullptr, &itemRect, nullptr);
        }
        if (pSortImage != nullptr) {
            UiRect sortRect = rc;
            sortRect.left = textRect.CenterX() + measureRect.Width() / 2;
            sortRect.left += nIconTextSpacing;
            sortRect.right = sortRect.left + sortImageSize.cx;
            sortRect.Validate();
            VAlignRect(sortRect, GetTextStyle(), sortImageSize.cy);
            PaintImage(pRender, pSortImage, L"", -1, nullptr, &sortRect, nullptr);
        }

        DoPaintText(textRect, pRender);
    }
    else if (textStyle & TEXT_RIGHT) {
        //���Ҷ���
        if (pSortImage != nullptr) {
            UiRect sortRect = rc;
            sortRect.left = sortRect.right - sortImageSize.cx;
            sortRect.Validate();
            VAlignRect(sortRect, GetTextStyle(), sortImageSize.cy);
            PaintImage(pRender, pSortImage, L"", -1, nullptr, &sortRect, nullptr);
            rc.right = sortRect.left;
            rc.right -= nIconTextSpacing;
            rc.Validate();
        }

        UiRect textRect = GetRect();
        textRect.Deflate(GetControlPadding());
        textRect.Deflate(GetTextPadding());
        textRect.right = std::min(rc.right, textRect.right);
        if (textRect.Width() > measureRect.Width()) {
            textRect.left = textRect.right - measureRect.Width();
        }
        DoPaintText(textRect, pRender);

        if (pItemImage != nullptr) {
            rc.right = textRect.left;
            rc.right -= nIconTextSpacing;
            rc.Validate();

            if (rc.Width() > itemImageSize.cx) {
                rc.left = rc.right - itemImageSize.cx;
                rc.Validate();
            }
            UiRect itemRect = rc;
            VAlignRect(itemRect, GetTextStyle(), itemImageSize.cy);
            PaintImage(pRender, pItemImage.get(), L"", -1, nullptr, &itemRect, nullptr);
        }
    }
    else {
        //������룺ͼ�ꡢ���֡�����ͼ�����λ���
        if (pItemImage != nullptr) {
            UiRect itemRect = rc;
            itemRect.right = itemRect.left + itemImageSize.cx;
            VAlignRect(itemRect, GetTextStyle(), itemImageSize.cy);
            PaintImage(pRender, pItemImage.get(), L"", -1, nullptr, &itemRect, nullptr);
            rc.left += itemImageSize.cx;
            rc.left += nIconTextSpacing;
        }

        UiRect textRect = GetRect();
        textRect.Deflate(GetControlPadding());
        textRect.Deflate(GetTextPadding());
        if (pItemImage != nullptr) {
            textRect.left = std::max(textRect.left, rc.left);
        }
        DoPaintText(textRect, pRender);

        rc.left = textRect.left;
        rc.left += measureRect.Width();
        rc.left += nIconTextSpacing;

        if (pSortImage != nullptr) {
            UiRect sortRect = rc;
            VAlignRect(sortRect, GetTextStyle(), sortImageSize.cy);
            PaintImage(pRender, pSortImage, L"", -1, nullptr, &sortRect, nullptr);
        }
    }
}

void ListCtrlHeaderItem::VAlignRect(UiRect& rc, uint32_t textStyle, int32_t nImageHeight)
{
    if ((nImageHeight <= 0) || (nImageHeight >= rc.Height())){
        return;
    }
    if (textStyle & TEXT_VCENTER) {
        //���ж���
        rc.top = rc.CenterY() - nImageHeight / 2;
        rc.bottom = rc.top + nImageHeight;
    }
    else if (textStyle & TEXT_BOTTOM) {
        //�ײ�����
        rc.top = rc.bottom - nImageHeight;
    }
    else {
        //��������
        rc.bottom = rc.top + nImageHeight;
    }
}

void ListCtrlHeaderItem::Activate()
{
    if (IsInDraggingOrder() || IsInDraggingOut()) {
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
        ListCtrlHeader* pHeader = GetHeaderCtrl();
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
            ListCtrlHeader* pHeader = GetHeaderCtrl();
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
    if (m_nIconSpacing != nIconSpacing) {
        m_nIconSpacing = nIconSpacing;
        if (m_nIconSpacing < 0) {
            m_nIconSpacing = 0;
        }
        Invalidate();
    }    
}

int32_t ListCtrlHeaderItem::GetIconSpacing() const
{
    return m_nIconSpacing;
}

void ListCtrlHeaderItem::SetShowIconAtTop(bool bShowIconAtTop)
{
    if (m_bShowIconAtTop != bShowIconAtTop) {
        m_bShowIconAtTop = bShowIconAtTop;
        Invalidate();
    }    
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

void ListCtrlHeaderItem::SetImageId(int32_t imageId)
{
    if (m_imageId != imageId) {
        m_imageId = imageId;
        Invalidate();
    }    
}

int32_t ListCtrlHeaderItem::GetImageId() const
{
    return m_imageId;
}

bool ListCtrlHeaderItem::IsEnableDragOrder() const
{
    ListCtrlHeader* pHeader = GetHeaderCtrl();
    if (pHeader != nullptr) {
        if (!pHeader->IsEnableHeaderDragOrder()) {
            //��֧���϶�����˳��
            return false;
        }
    }
    return __super::IsEnableDragOrder();
}

bool ListCtrlHeaderItem::SetCheckBoxVisible(bool bVisible)
{
    bool bRet = false;
    if (bVisible) {
        ListCtrlHeader* pHeader = GetHeaderCtrl();
        if (pHeader == nullptr) {
            return false;
        }
        ListCtrl* pListCtrl = pHeader->GetListCtrl();
        ListCtrlCheckBox* pCheckBox = nullptr;
        if (GetItemCount() > 0) {
            pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
        }
        if (pCheckBox == nullptr) {
            pCheckBox = new ListCtrlCheckBox; 
            AddItem(pCheckBox);
            std::wstring checkBoxClass;
            if (pListCtrl != nullptr) {
                checkBoxClass = pListCtrl->GetCheckBoxClass();
            }
            ASSERT(!checkBoxClass.empty());
            pCheckBox->SetClass(checkBoxClass);
        }

        //�����ڱ߾࣬�����������ص�
        UiPadding textPadding = GetTextPadding();
        int32_t nCheckBoxWidth = pCheckBox->GetCheckBoxWidth();
        if ((nCheckBoxWidth > 0) && (textPadding.left < nCheckBoxWidth)) {
            textPadding.left = nCheckBoxWidth;
            SetTextPadding(textPadding, false);
        }
        pCheckBox->SetVisible(true);

        //����CheckBox���¼�����
        pCheckBox->DetachEvent(kEventSelect);
        pCheckBox->DetachEvent(kEventUnSelect);
        //ͬ������
        if (pListCtrl != nullptr) {
            pListCtrl->UpdateHeaderColumnCheckBox(GetColomnId());
        }
        pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            pCheckBox->AttachSelect([this, pHeader](const EventArgs& /*args*/) {
                pHeader->OnHeaderColumnCheckStateChanged(this, true);
                return true;
                });
            pCheckBox->AttachUnSelect([this, pHeader](const EventArgs& /*args*/) {
                pHeader->OnHeaderColumnCheckStateChanged(this, false);
                return true;
                });
        }        
        bRet = true;
    }
    else if(GetItemCount() > 0) {
        ListCtrlCheckBox* pCheckBox = dynamic_cast<ListCtrlCheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            UiPadding textPadding = GetTextPadding();
            int32_t nCheckBoxWidth = pCheckBox->GetCheckBoxWidth();
            if ((nCheckBoxWidth > 0) && (textPadding.left >= nCheckBoxWidth)) {
                textPadding.left -= nCheckBoxWidth;
                SetTextPadding(textPadding, false);
            }
            RemoveItemAt(0);
            bRet = true;
        }
    }
    return bRet;
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

bool ListCtrlHeaderItem::SetCheckBoxCheck(bool bChecked, bool bPartChecked)
{
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            bool bChanged = pCheckBox->IsSelected() != bChecked;
            pCheckBox->SetSelected(bChecked);
            if (bChecked) {
                if (pCheckBox->IsPartSelected() != bPartChecked) {
                    pCheckBox->SetPartSelected(bPartChecked);
                    bChanged = true;
                }
            }
            if (bChanged) {
                pCheckBox->Invalidate();
            }            
            return true;
        }
    }
    return false;
}

bool ListCtrlHeaderItem::GetCheckBoxCheck(bool& bChecked, bool& bPartChecked) const
{
    bChecked = false;
    bPartChecked = false;
    if (GetItemCount() > 0) {
        CheckBox* pCheckBox = dynamic_cast<CheckBox*>(GetItemAt(0));
        if (pCheckBox != nullptr) {
            bChecked = pCheckBox->IsSelected();
            if (bChecked) {
                bPartChecked = pCheckBox->IsPartSelected();
            }
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
    ListCtrlHeader* pHeader = GetHeaderCtrl();
    if (pHeader != nullptr) {
        pHeader->OnHeaderColumnVisibleChanged();
    }
}

bool ListCtrlHeaderItem::IsColumnVisible() const
{
    //�б���IsVisible(), ����ͷ���ص�ʱ��IsVisible()Ҳ�᷵��false
    return m_bColumnVisible;
}

void ListCtrlHeaderItem::SetHeaderCtrl(ListCtrlHeader* pHeaderCtrl)
{
    m_pHeaderCtrl = pHeaderCtrl;
}

ListCtrlHeader* ListCtrlHeaderItem::GetHeaderCtrl() const
{
    ASSERT(m_pHeaderCtrl != nullptr);
    return m_pHeaderCtrl;
}

void ListCtrlHeaderItem::AdjustItemPos(const UiPoint& pt, const UiPoint& ptMouseDown,
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
    ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(pMouseItem);
    if (pHeaderItem == nullptr) {
        //��겻�ڱ�ͷ�ؼ���
        return;
    }
    if (!pHeaderItem->IsEnableDragOrder()) {
        //��ǰ��Ϊ�̶��У����������˳��
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
            if (item.m_pItem == this) {
                //�ָ�������Split�ؼ�λ��
                if ((index + 1) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index + 1];
                    if ((nextItem.m_pItem->GetRect() != nextItem.m_rcPos)) {
                        nextItem.m_pItem->SetPos(nextItem.m_rcPos);
                    }
                }
                continue;
            }
            else if ((item.m_index >= nMouseItemIndex) && (item.m_index < nMouseDownItemIndex)) {
                //���Ҳ��ƶ�
                if ((index + 2) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index + 2];
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
            if (item.m_pItem == this) {
                //�ָ�������Split�ؼ�λ��
                if ((index + 1) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index + 1];
                    if ((nextItem.m_pItem->GetRect() != nextItem.m_rcPos)) {
                        nextItem.m_pItem->SetPos(nextItem.m_rcPos);
                    }
                }
                continue;
            }
            else if ((item.m_index > nMouseDownItemIndex) && (item.m_index <= nMouseItemIndex)) {
                //������ƶ�
                if ((index - 2) < itemCount) {
                    const ItemStatus& nextItem = rcItemList[index - 2];
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

bool ListCtrlHeaderItem::AdjustItemOrders(const UiPoint& pt,
                                          const std::vector<ItemStatus>& rcItemList,
                                          size_t& nOldItemIndex,
                                          size_t& nNewItemIndex)
{
    nOldItemIndex = Box::InvalidIndex;
    nNewItemIndex = Box::InvalidIndex;
    Box* pHeader = GetParent();
    if (pHeader == nullptr) {
        return false;
    }
    bool bOrderChanged = false;
    const size_t itemCount = pHeader->GetItemCount();
    size_t nMouseItemIndex = Box::InvalidIndex;
    size_t nCurrentItemIndex = Box::InvalidIndex;
    for (const ItemStatus& itemStatus : rcItemList) {
        if (itemStatus.m_rcPos.ContainsPt(pt)) {
            nMouseItemIndex = itemStatus.m_index;
            ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(itemStatus.m_pItem);
            if ((pHeaderItem != nullptr) && !pHeaderItem->IsEnableDragOrder()) {
                //��ǰ��Ϊ�̶��У����������˳��
                nMouseItemIndex = Box::InvalidIndex;
            }
        }
        if ((itemStatus.m_pItem == this) && !itemStatus.m_rcPos.ContainsPt(pt)) {
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
            pHeader->SetItemIndex(this, nMouseItemIndex);
            if (m_pSplitBox != nullptr) {
                size_t nNewIndex = pHeader->GetItemIndex(this);
                ASSERT(nNewIndex < itemCount);
                ASSERT((nNewIndex + 1) < itemCount);
                if ((nNewIndex + 1) < itemCount) {
                    pHeader->SetItemIndex(m_pSplitBox, nNewIndex + 1);
                }
            }
        }
        else {
            //���Ҳཻ��
            nMouseItemIndex += 1;
            ASSERT(nMouseItemIndex < itemCount);
            if (nMouseItemIndex < itemCount) {
                pHeader->SetItemIndex(this, nMouseItemIndex);
                if (m_pSplitBox != nullptr) {
                    size_t nNewIndex = pHeader->GetItemIndex(this);
                    ASSERT(nNewIndex < itemCount);
                    pHeader->SetItemIndex(m_pSplitBox, nNewIndex);
                }
            }
        }
        nOldItemIndex = nCurrentItemIndex;
        nNewItemIndex = nMouseItemIndex;
        bOrderChanged = true;
        ASSERT(pHeader->GetItemIndex(this) == (pHeader->GetItemIndex(m_pSplitBox) - 1));

        //�����󣬶����е������У��
        for (size_t index = 0; index < itemCount; index += 2) {
            ASSERT(dynamic_cast<ListCtrlHeaderItem*>(pHeader->GetItemAt(index)) != nullptr);
            ASSERT((index + 1) < itemCount);
            if ((index + 1) >= itemCount) {
                break;
            }
            ASSERT(dynamic_cast<SplitBox*>(pHeader->GetItemAt(index + 1)) != nullptr);
            ASSERT(dynamic_cast<SplitBox*>(pHeader->GetItemAt(index + 1)) ==
                   dynamic_cast<ListCtrlHeaderItem*>(pHeader->GetItemAt(index))->m_pSplitBox);
        }
    }

    return bOrderChanged;
}

void ListCtrlHeaderItem::OnItemOrdersChanged(size_t /*nOldItemIndex*/, size_t /*nNewItemIndex*/)
{
    ListCtrlHeader* pHeader = GetHeaderCtrl();
    if (pHeader != nullptr) {
        pHeader->OnHeaderColumnOrderChanged();
    }
}

}//namespace ui

