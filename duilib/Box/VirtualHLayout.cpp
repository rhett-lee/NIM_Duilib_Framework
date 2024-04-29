#include "VirtualHLayout.h"
#include "duilib/Box/VirtualListBox.h"

namespace ui 
{
VirtualHLayout::VirtualHLayout()
{
}

VirtualListBox* VirtualHLayout::GetOwnerBox() const
{
    VirtualListBox* pList = dynamic_cast<VirtualListBox*>(GetOwner());
    ASSERT(pList != nullptr);
    return pList;
}

UiSize64 VirtualHLayout::ArrangeChild(const std::vector<ui::Control*>& items, ui::UiRect rc)
{
    VirtualListBox* pList = dynamic_cast<VirtualListBox*>(GetOwner());
    if ((pList == nullptr) || !pList->HasDataProvider()) {
        //���δ�������ݽӿڣ�����ݻ���Ĺ���
        return __super::ArrangeChild(items, rc);
    }
    DeflatePadding(rc);
    int64_t nTotalWidth = GetElementsWidth(rc, Box::InvalidIndex);
    UiSize64 sz(rc.Width(), rc.Height());
    sz.cx = std::max(nTotalWidth, sz.cx);
    LazyArrangeChild(rc);
    return sz;
}

UiSize VirtualHLayout::EstimateSizeByChild(const std::vector<Control*>& items, ui::UiSize szAvailable)
{
    VirtualListBox* pList = dynamic_cast<VirtualListBox*>(GetOwner());
    if ((pList == nullptr) || !pList->HasDataProvider()) {
        //���δ�������ݽӿڣ�����ݻ���Ĺ���
        return __super::EstimateSizeByChild(items, szAvailable);
    }
    szAvailable.Validate();
    UiEstSize estSize;
    if (GetOwner() != nullptr) {
        estSize = GetOwner()->Control::EstimateSize(szAvailable);
    }
    UiSize size(estSize.cx.GetInt32(), estSize.cy.GetInt32());
    if (estSize.cx.IsStretch()) {
        size.cx = CalcStretchValue(estSize.cx, szAvailable.cx);
    }
    if (estSize.cy.IsStretch()) {
        size.cy = CalcStretchValue(estSize.cy, szAvailable.cy);
    }
    if ((size.cx == 0) || (size.cy == 0)) {
        UiPadding rcPadding;
        if (GetOwner() != nullptr) {
            rcPadding = GetOwner()->GetPadding();
        }
        UiSize szItem = GetItemSize();
        szItem.cx += (rcPadding.left + rcPadding.right);
        szItem.cy += (rcPadding.top + rcPadding.bottom);

        if (size.cx == 0) {
            size.cx = szItem.cx;
        }
        if (size.cy == 0) {
            size.cy = szItem.cy;
        }
    }
    size.Validate();
    return size;
}

bool VirtualHLayout::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    bool hasAttribute = true;
    if ((strName == L"item_size") || (strName == L"itemsize")) {
        UiSize szItem;
        AttributeUtil::ParseSizeValue(strValue.c_str(), szItem);
        SetItemSize(szItem);
    }
    else {
        hasAttribute = HLayout::SetAttribute(strName, strValue);
    }
    return hasAttribute;
}

void VirtualHLayout::SetItemSize(UiSize szItem, bool bNeedDpiScale)
{
    szItem.cx = std::max(szItem.cx, 0);
    szItem.cy = std::max(szItem.cy, 0);
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleSize(szItem);
    }
    ASSERT((szItem.cx > 0) && (szItem.cy > 0));
    if ((m_szItem.cx != szItem.cx) || (m_szItem.cy != szItem.cy)) {
        m_szItem = szItem;
        if (GetOwner() != nullptr) {
            GetOwner()->Arrange();
        }
    }
}

const UiSize& VirtualHLayout::GetItemSize() const
{
    return m_szItem;
}

int64_t VirtualHLayout::GetElementsWidth(UiRect /*rc*/, size_t nCount) const
{
    UiSize szItem = GetItemSize();
    ASSERT((szItem.cx > 0) || (szItem.cy > 0));
    if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
        return 0;
    }
    if (nCount <= 1) {
        return szItem.cx + GetChildMarginX();
    }
    if (!Box::IsValidItemIndex(nCount)) {
        VirtualListBox* pList = GetOwnerBox();
        ASSERT(pList != nullptr);
        if (pList != nullptr) {
            nCount = pList->GetElementCount();
        }
    }
    if (!Box::IsValidItemIndex(nCount)) {
        ASSERT(FALSE);
        return szItem.cx + GetChildMarginX();
    }

    int64_t cols = nCount;
    int64_t iChildMargin = 0;
    if (GetChildMarginX() > 0) {
        iChildMargin = GetChildMarginX();
    }
    int64_t childMarginTotal = ((int64_t)nCount - 1) * iChildMargin;
    return szItem.cx * cols + childMarginTotal;
}

void VirtualHLayout::LazyArrangeChild(UiRect rc) const
{
    UiSize szItem = GetItemSize();
    ASSERT((szItem.cx > 0) || (szItem.cy > 0));
    if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
        return;
    }
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return;
    }
    if (!pOwnerBox->HasDataProvider()) {
        return;
    }

    //X�������ƫ�ƣ���Ҫ���֣��������λ�ñ䶯������ˢ�½������ƫ��
    int32_t xOffset = 0;
    int64_t itemWidth = GetElementsWidth(rc, 1);
    if (itemWidth > 0) {
        xOffset = TruncateToInt32(pOwnerBox->GetScrollPos().cx % itemWidth);
    }

    //����������ʼλ�� 
    int32_t iPosLeft = rc.left - xOffset;

    //����Ķ�����ʼλ��
    int32_t iPosTop = rc.top;

    //��������ƫ�ƣ������������ϴ�ʱ��rc���32λ�ľ��εĸ߶Ȼ�Խ�磬��Ҫ64λ���Ͳ�������
    pOwnerBox->SetScrollVirtualOffsetX(pOwnerBox->GetScrollPos().cx);

    //�ؼ������Ͻ�����ֵ
    ui::UiPoint ptTile(iPosLeft, iPosTop);

    VirtualListBox::RefreshDataList refreshDataList;
    VirtualListBox::RefreshData refreshData;
    // ����index
    size_t nTopIndex = GetTopElementIndex(rc);
    size_t iCount = 0;
    size_t nItemCount = pOwnerBox->m_items.size();
    for (size_t nItemIndex = 0; nItemIndex < nItemCount; ++nItemIndex) {
        Control* pControl = pOwnerBox->m_items[nItemIndex];
        if (pControl == nullptr) {
            continue;
        }
        // Determine size
        ui::UiRect rcTile(ptTile.x, ptTile.y, ptTile.x + szItem.cx, ptTile.y + szItem.cy);
        pControl->SetPos(rcTile);

        // �������
        size_t nElementIndex = nTopIndex + iCount;
        if (nElementIndex < pOwnerBox->GetElementCount()) {
            if (!pControl->IsVisible()) {
                pControl->SetVisible(true);
            }
            pOwnerBox->FillElement(pControl, nElementIndex);
            refreshData.nItemIndex = nItemIndex;
            refreshData.pControl = pControl;
            refreshData.nElementIndex = nElementIndex;
            refreshDataList.push_back(refreshData);
        }
        else {
            if (pControl->IsVisible()) {
                pControl->SetVisible(false);
            }
        }
        ++iCount;

        //����
        ptTile.y = iPosTop;
        ptTile.x += szItem.cx + GetChildMarginX();
    }
    if (!refreshDataList.empty()) {
        pOwnerBox->OnRefreshElements(refreshDataList);
    }
}

size_t VirtualHLayout::AjustMaxItem(UiRect rc) const
{
    UiSize szItem = GetItemSize();
    ASSERT((szItem.cx > 0) || (szItem.cy > 0));
    if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
        return 0;
    }
    if (rc.IsEmpty()) {
        return 0;
    }
    int32_t nColumns = rc.Width() / (szItem.cx + GetChildMarginX() / 2);
    //��֤������
    if (nColumns > 1) {
        int32_t calcWidth = nColumns * szItem.cx + (nColumns - 1) * GetChildMarginX();
        if (calcWidth < rc.Width()) {
            nColumns += 1;
        }
    }
    //��������1�У�ȷ����ʵ�ؼ��������������ʾ����
    nColumns += 1;
    return nColumns;
}

size_t VirtualHLayout::GetTopElementIndex(UiRect rc) const
{
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return 0;
    }
    int64_t nPos = pOwnerBox->GetScrollPos().cx;
    if (nPos < 0) {
        nPos = 0;
    }
    int64_t nWidth = GetElementsWidth(rc, 1);
    ASSERT(nWidth >= 0);
    if (nWidth <= 0) {
        return 0;
    }
    int64_t iIndex = nPos / nWidth;
    return static_cast<size_t>(iIndex);
}

bool VirtualHLayout::IsElementDisplay(UiRect rc, size_t iIndex) const
{
    if (!Box::IsValidItemIndex(iIndex)) {
        return false;
    }
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return false;
    }

    int64_t nScrollPos = pOwnerBox->GetScrollPos().cx;
    int64_t nElementPos = GetElementsWidth(rc, iIndex + 1);
    int64_t nElementWidth = GetElementsWidth(rc, 1);
    if ((nElementPos - nElementWidth) > nScrollPos) { //���ε�leftλ��
        int64_t nBoxWidth = pOwnerBox->GetWidth();
        if (nElementPos <= (nScrollPos + nBoxWidth)) {//���ε�rightλ��
            return true;
        }
    }
    return false;
}

bool VirtualHLayout::NeedReArrange() const
{
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return false;
    }
    if (!pOwnerBox->HasDataProvider()) {
        return false;
    }
    size_t nCount = pOwnerBox->GetItemCount();
    if (nCount == 0) {
        return false;
    }

    if (pOwnerBox->GetElementCount() <= nCount) {
        return false;
    }

    ui::UiRect rcThis = pOwnerBox->GetPos();
    if (rcThis.IsEmpty()) {
        return false;
    }

    int64_t nScrollPosX = pOwnerBox->GetScrollPos().cx;
    int64_t nVirtualOffsetX = pOwnerBox->GetScrollVirtualOffset().cx;
    return nVirtualOffsetX != nScrollPosX;
}

void VirtualHLayout::GetDisplayElements(UiRect rc, std::vector<size_t>& collection) const
{
    collection.clear();
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return;
    }

    if (pOwnerBox->GetItemCount() == 0) {
        return;
    }

    size_t nEleWidth = GetElementsWidth(rc, 1);
    if (nEleWidth == 0) {
        return;
    }

    size_t min = ((size_t)pOwnerBox->GetScrollPos().cx / nEleWidth);
    size_t max = min + ((size_t)rc.Width() / nEleWidth);

    size_t nCount = pOwnerBox->GetElementCount();
    if (nCount > 0) {
        if (max >= nCount) {
            max = nCount - 1;
        }
    }
    else {
        return;
    }

    for (size_t i = min; i <= max; ++i) {
        collection.push_back(i);
    }
}

void VirtualHLayout::EnsureVisible(UiRect rc, size_t iIndex, bool bToTop) const
{
    VirtualListBox* pOwnerBox = GetOwnerBox();
    if (pOwnerBox == nullptr) {
        return;
    }
    if (!Box::IsValidItemIndex(iIndex) || iIndex >= pOwnerBox->GetElementCount()) {
        return;
    }
    if (pOwnerBox->m_pVScrollBar == nullptr) {
        return;
    }
    int64_t nPos = pOwnerBox->GetScrollPos().cx;
    int64_t elementWidth = GetElementsWidth(rc, 1);
    if (elementWidth <= 0) {
        return;
    }
    int64_t nTopIndex = 0;
    if (elementWidth > 0) {
        nTopIndex = (nPos / elementWidth);
    }
    int64_t nNewPos = 0;

    if (bToTop) {
        nNewPos = GetElementsWidth(rc, iIndex);
        if (nNewPos >= elementWidth) {
            nNewPos -= elementWidth;
        }
    }
    else {
        if (IsElementDisplay(rc, iIndex)) {
            return;
        }

        if ((int64_t)iIndex > nTopIndex) {
            // ����
            int64_t nWidth = GetElementsWidth(rc, iIndex + 1);
            nNewPos = nWidth - pOwnerBox->GetRect().Width();
        }
        else {
            // ����
            nNewPos = GetElementsWidth(rc, iIndex + 1);
            if (nNewPos >= elementWidth) {
                nNewPos -= elementWidth;
            }
        }
    }
    if (nNewPos < 0) {
        nNewPos = 0;
    }
    if (nNewPos > pOwnerBox->m_pHScrollBar->GetScrollRange()) {
        nNewPos = pOwnerBox->m_pHScrollBar->GetScrollRange();
    }
    ui::UiSize64 sz(nNewPos, 0);
    pOwnerBox->SetScrollPos(sz);
}
} // namespace ui
