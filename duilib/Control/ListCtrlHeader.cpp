#include "ListCtrlHeader.h"
#include "duilib/Control/ListCtrl.h"

namespace ui
{

ListCtrlHeader::ListCtrlHeader() :
    m_pListCtrl(nullptr),
    m_nCheckBoxPadding(0),
    m_nPaddingLeftValue(0),
    m_bEnableCheckChangeEvent(true)
{
    m_nIconSpacing = GlobalManager::Instance().Dpi().GetScaleInt(4);
}

ListCtrlHeader::~ListCtrlHeader()
{
}

std::wstring ListCtrlHeader::GetType() const { return L"ListCtrlHeader"; }

void ListCtrlHeader::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"icon_spacing") {
        SetIconSpacing(_wtoi(strValue.c_str()), true);
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

void ListCtrlHeader::SetIconSpacing(int32_t nIconSpacing, bool bNeedDpiScale)
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

int32_t ListCtrlHeader::GetIconSpacing() const
{
    return m_nIconSpacing;
}

bool ListCtrlHeader::IsSelectableType() const
{
    return false;
}

ListCtrlHeaderItem* ListCtrlHeader::InsertColumn(int32_t columnIndex, const ListCtrlColumn& columnInfo)
{
    int32_t nColumnWidth = columnInfo.nColumnWidth;
    ASSERT(m_pListCtrl != nullptr);
    if (m_pListCtrl == nullptr) {
        return nullptr;
    }
    if (columnInfo.bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleInt(nColumnWidth);
    }
    if (nColumnWidth < 0) {
        nColumnWidth = 0;
    }

    ListCtrlHeaderItem* pHeaderItem = new ListCtrlHeaderItem;
    pHeaderItem->SetHeaderCtrl(this);
    SplitBox* pHeaderSplit = new SplitBox;
    size_t nColumnCount = GetColumnCount();
    if ((size_t)columnIndex >= nColumnCount) {
        //�������
        AddItem(pHeaderItem);
        AddItem(pHeaderSplit);
    }
    else {
        //�������м�λ��        
        AddItemAt(pHeaderSplit, columnIndex);
        AddItemAt(pHeaderItem, columnIndex);
    }

    //��������
    if (!m_pListCtrl->GetHeaderSplitBoxClass().empty()) {
        pHeaderSplit->SetClass(m_pListCtrl->GetHeaderSplitBoxClass());
    }

    Control* pSplitCtrl = new Control;
    pSplitCtrl->SetMouseEnabled(false);
    pSplitCtrl->SetMouseFocused(false);
    pSplitCtrl->SetNoFocus();
    if (!m_pListCtrl->GetHeaderSplitControlClass().empty()) {
        pSplitCtrl->SetClass(m_pListCtrl->GetHeaderSplitControlClass());
    }
    pHeaderSplit->AddItem(pSplitCtrl);

    if (!m_pListCtrl->GetHeaderItemClass().empty()) {
        pHeaderItem->SetClass(m_pListCtrl->GetHeaderItemClass());
    }
    pHeaderItem->SetText(columnInfo.text);

    //���������Split�ؼ��ӿ�
    pHeaderItem->SetSplitBox(pHeaderSplit);
    pHeaderItem->SetColumnWidth(nColumnWidth, false);
    if (columnInfo.nColumnWidthMin > 0) {
        //�п���Сֵ
        pHeaderItem->SetMinWidth(columnInfo.nColumnWidthMin, columnInfo.bNeedDpiScale);
    }
    if (columnInfo.nColumnWidthMax > 0) {
        //�п����ֵ
        pHeaderItem->SetMaxWidth(columnInfo.nColumnWidthMax, columnInfo.bNeedDpiScale);
    }

    if (columnInfo.bSortable) {
        pHeaderItem->SetSortMode(ListCtrlHeaderItem::SortMode::kUp);
    }
    else {
        pHeaderItem->SetSortMode(ListCtrlHeaderItem::SortMode::kNone);
    }
    pHeaderItem->SetColumnResizeable(columnInfo.bResizeable);

    if (columnInfo.nTextFormat >= 0) {
        uint32_t textStyle = columnInfo.nTextFormat;
        //ˮƽ����
        if (columnInfo.nTextFormat & TEXT_CENTER) {
            //�ı������ж���
            textStyle &= ~(TEXT_LEFT | TEXT_RIGHT);
            textStyle |= TEXT_CENTER;            
        }
        else if (columnInfo.nTextFormat & TEXT_RIGHT) {
            //�ı����Ҷ���
            textStyle &= ~(TEXT_LEFT | TEXT_CENTER);
            textStyle |= TEXT_RIGHT;
        }
        else {
            //�ı��������
            textStyle &= ~(TEXT_CENTER | TEXT_RIGHT);
            textStyle |= TEXT_LEFT;
        }

        //��ֱ����
        if (columnInfo.nTextFormat & TEXT_VCENTER) {
            //�ı������ж���
            textStyle &= ~(TEXT_TOP | TEXT_BOTTOM);
            textStyle |= TEXT_VCENTER;
        }
        else if (columnInfo.nTextFormat & TEXT_BOTTOM) {
            //�ı����ײ�����
            textStyle &= ~(TEXT_TOP | TEXT_VCENTER);
            textStyle |= TEXT_BOTTOM;
        }
        else {
            //�ı�����������
            textStyle &= ~(TEXT_BOTTOM | TEXT_VCENTER);
            textStyle |= TEXT_TOP;
        }
        pHeaderItem->SetTextStyle(textStyle, true);
    }

    //����ͼ��
    pHeaderItem->SetImageId(columnInfo.nImageId);

    //CheckBox����
    pHeaderItem->SetCheckBoxVisible(columnInfo.bShowCheckBox);

    //�����϶���Ӧ�¼�
    pHeaderSplit->AttachSplitDraged([this](const EventArgs& args) {
        OnHeaderColumnResized((Control*)args.wParam, (Control*)args.lParam);
        return true;
        });

    //�����Ҽ�����¼�������ת��
    pHeaderItem->AttachRClick([this, pHeaderItem](const EventArgs& args) {
        EventArgs msg(args);
        msg.pSender = this;
        msg.wParam = (WPARAM)pHeaderItem;
        SendEvent(msg);
        return true;
        });
    pHeaderSplit->AttachRClick([this, pHeaderItem](const EventArgs& args) {
        EventArgs msg(args);
        msg.pSender = this;
        msg.wParam = (WPARAM)pHeaderItem;
        SendEvent(msg);
        return true;
        });

    //�������˫���¼�
    pHeaderSplit->AttachDoubleClick([this, pHeaderItem](const EventArgs& /*args*/) {
        OnHeaderColumnSplitDoubleClick(pHeaderItem);
        return true;
        });

    m_pListCtrl->OnHeaderColumnAdded(pHeaderItem->GetColomnId());
    return pHeaderItem;
}

size_t ListCtrlHeader::GetColumnCount() const
{
    size_t nItemCount = GetItemCount();
    if (nItemCount == 0) {
        return 0;
    }
    ASSERT((nItemCount % 2) == 0);
    if ((nItemCount % 2) != 0) {
        return 0;
    }
    const size_t nColumnCount = nItemCount / 2;
#ifdef _DEBUG
    //У��ṹ�Ƿ����Ԥ��    
    for (size_t index = 0; index < nColumnCount; ++index) {
        ASSERT(dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(index * 2)) != nullptr);
        ASSERT(dynamic_cast<SplitBox*>(GetItemAt(index * 2 + 1)) != nullptr);
    }
#endif // _DEBUG  
    
    return nColumnCount;
}

int32_t ListCtrlHeader::GetColumnWidth(size_t columnIndex) const
{
    int32_t nColumnWidth = 0;
    size_t nColumnCount = GetColumnCount();
    ASSERT(columnIndex < nColumnCount);
    if (columnIndex >= nColumnCount) {
        return nColumnWidth;
    }
    ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(columnIndex * 2));
    ASSERT(pHeaderItem != nullptr);
    if (pHeaderItem != nullptr) {
        nColumnWidth = pHeaderItem->GetColumnWidth();
    }
    return nColumnWidth;
}

bool ListCtrlHeader::SetColumnWidth(size_t columnIndex, int32_t nWidth, bool bNeedDpiScale)
{
    bool bRet = false;
    ListCtrlHeaderItem* pHeaderItem = GetColumn(columnIndex);
    ASSERT(pHeaderItem != nullptr);
    if (pHeaderItem != nullptr) {
        pHeaderItem->SetColumnWidth(nWidth, bNeedDpiScale);
        bRet = true;
    }
    return bRet;
}

ListCtrlHeaderItem* ListCtrlHeader::GetColumn(size_t columnIndex) const
{
    size_t nColumnCount = GetColumnCount();
    ASSERT(columnIndex < nColumnCount);
    if (columnIndex >= nColumnCount) {
        return nullptr;
    }
    ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(columnIndex * 2));
    ASSERT(pHeaderItem != nullptr);
    return pHeaderItem;
}

ListCtrlHeaderItem* ListCtrlHeader::GetColumnById(size_t columnId) const
{
    ListCtrlHeaderItem* pFoundHeaderItem = nullptr;
    size_t nColumnCount = GetColumnCount();
    for (size_t index = 0; index < nColumnCount; ++index) {
        ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(index * 2));
        ASSERT(pHeaderItem != nullptr);
        if (pHeaderItem != nullptr) {
            if (pHeaderItem->GetColomnId() == columnId) {
                pFoundHeaderItem = pHeaderItem;
                break;
            }
        }
    }
    return pFoundHeaderItem;
}

bool ListCtrlHeader::GetColumnInfo(size_t columnId, size_t& columnIndex, int32_t& nColumnWidth) const
{
    bool bRet = false;
    columnIndex = Box::InvalidIndex;
    nColumnWidth = -1;
    size_t nColumnCount = GetColumnCount();
    for (size_t index = 0; index < nColumnCount; ++index) {
        ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(index * 2));
        ASSERT(pHeaderItem != nullptr);
        if (pHeaderItem != nullptr) {
            if (pHeaderItem->GetColomnId() == columnId) {
                nColumnWidth = pHeaderItem->GetColumnWidth();
                columnIndex = index;
                bRet = true;
                break;
            }
        }
    }
    return bRet;
}

size_t ListCtrlHeader::GetColumnIndex(size_t columnId) const
{
    size_t columnIndex = Box::InvalidIndex;
    int32_t nColumnWidth = -1;
    GetColumnInfo(columnId, columnIndex, nColumnWidth);
    return columnIndex;
}

size_t ListCtrlHeader::GetColumnId(size_t columnIndex) const
{
    size_t columnId = Box::InvalidIndex;
    ListCtrlHeaderItem* pHeaderItem = GetColumn(columnIndex);
    if (pHeaderItem != nullptr) {
        columnId = pHeaderItem->GetColomnId();
    }
    return columnId;
}

bool ListCtrlHeader::DeleteColumn(size_t columnIndex)
{
    bool bRet = false;
    size_t columnId = Box::InvalidIndex;
    size_t nColumnCount = GetColumnCount();
    if (columnIndex < nColumnCount) {
        ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(GetItemAt(columnIndex * 2));
        ASSERT(pHeaderItem != nullptr);
        if (pHeaderItem != nullptr) {
            columnId = pHeaderItem->GetColomnId();
            if (pHeaderItem->GetSplitBox() != nullptr) {
                ASSERT(dynamic_cast<SplitBox*>(GetItemAt(columnIndex * 2 + 1)) == pHeaderItem->GetSplitBox());
                RemoveItem(pHeaderItem->GetSplitBox());
            }
            RemoveItem(pHeaderItem);
            bRet = true;
        }
    }
    if (bRet && (m_pListCtrl != nullptr)) {
        m_pListCtrl->OnHeaderColumnRemoved(columnId);
    }
    return bRet;
}

void ListCtrlHeader::SetListCtrl(ListCtrl* pListCtrl)
{
    m_pListCtrl = pListCtrl;
}

ListCtrl* ListCtrlHeader::GetListCtrl() const
{
    ASSERT(m_pListCtrl != nullptr);
    return m_pListCtrl;
}

bool ListCtrlHeader::IsEnableHeaderDragOrder() const
{
    if (m_pListCtrl != nullptr) {
        return m_pListCtrl->IsEnableHeaderDragOrder();
    }
    return false;
}

void ListCtrlHeader::OnHeaderColumnResized(Control* pLeftHeaderItem, Control* pRightHeaderItem)
{
    size_t nColumnId1 = Box::InvalidIndex;
    size_t nColumnId2 = Box::InvalidIndex;
    ListCtrlHeaderItem* pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(pLeftHeaderItem);
    if (pHeaderItem != nullptr) {
        int32_t nSplitWidth = 0;
        if (pHeaderItem->GetSplitBox() != nullptr) {
            nSplitWidth = pHeaderItem->GetSplitBox()->GetFixedWidth().GetInt32();
        }
        int32_t nItemWidth = pHeaderItem->GetFixedWidth().GetInt32();
        int32_t nColumnWidth = nItemWidth + nSplitWidth;
        pHeaderItem->SetColumnWidth(nColumnWidth, false);
        nColumnId1 = pHeaderItem->GetColomnId();
    }
    pHeaderItem = dynamic_cast<ListCtrlHeaderItem*>(pRightHeaderItem);
    if (pHeaderItem != nullptr) {
        int32_t nSplitWidth = 0;
        if (pHeaderItem->GetSplitBox() != nullptr) {
            nSplitWidth = pHeaderItem->GetSplitBox()->GetFixedWidth().GetInt32();
        }
        int32_t nItemWidth = pHeaderItem->GetFixedWidth().GetInt32();
        int32_t nColumnWidth = nItemWidth + nSplitWidth;
        pHeaderItem->SetColumnWidth(nColumnWidth, false);
        nColumnId2 = pHeaderItem->GetColomnId();
    } 

    if ((nColumnId1 != Box::InvalidIndex) || (nColumnId2 != Box::InvalidIndex)) {
        if (m_pListCtrl != nullptr) {
            m_pListCtrl->OnColumnWidthChanged(nColumnId1, nColumnId2);
        }
    }
}

void ListCtrlHeader::OnHeaderColumnSorted(ListCtrlHeaderItem* pHeaderItem)
{
    if (pHeaderItem == nullptr) {
        return;
    }
    size_t nColumnId = pHeaderItem->GetColomnId();
    ListCtrlHeaderItem::SortMode sortMode = pHeaderItem->GetSortMode();
    ASSERT(sortMode != ListCtrlHeaderItem::SortMode::kNone);
    if (sortMode == ListCtrlHeaderItem::SortMode::kNone) {
        return;
    }
    if (m_pListCtrl != nullptr) {
        bool bSortedUp = (sortMode == ListCtrlHeaderItem::SortMode::kUp) ? true : false;
        m_pListCtrl->OnColumnSorted(nColumnId, bSortedUp);
    }
}

void ListCtrlHeader::OnHeaderColumnOrderChanged()
{
    if (m_pListCtrl != nullptr) {
        m_pListCtrl->OnHeaderColumnOrderChanged();
    }
}

void ListCtrlHeader::OnHeaderColumnCheckStateChanged(ListCtrlHeaderItem* pHeaderItem, bool bChecked)
{
    if (pHeaderItem == nullptr) {
        return;
    }
    size_t nColumnId = pHeaderItem->GetColomnId();
    if (m_pListCtrl != nullptr) {
        m_pListCtrl->OnHeaderColumnCheckStateChanged(nColumnId, bChecked);
    }
}

void ListCtrlHeader::OnHeaderColumnVisibleChanged()
{
    if (m_pListCtrl != nullptr) {
        m_pListCtrl->OnHeaderColumnVisibleChanged();
    }
}

void ListCtrlHeader::OnHeaderColumnSplitDoubleClick(ListCtrlHeaderItem* pHeaderItem)
{
    if (m_pListCtrl != nullptr) {
        m_pListCtrl->OnHeaderColumnSplitDoubleClick(pHeaderItem);
    }
}

bool ListCtrlHeader::SupportCheckedMode() const
{
    return true;
}

void ListCtrlHeader::OnPrivateSetChecked()
{
    if (!m_bEnableCheckChangeEvent) {
        return;
    }
    bool bChecked = IsChecked();
    if (m_pListCtrl != nullptr) {
        m_pListCtrl->OnHeaderCheckStateChanged(bChecked);
    }
}

bool ListCtrlHeader::SetShowCheckBox(bool bShow)
{
    bool bOldShow = IsShowCheckBox();
    if (bOldShow == bShow) {
        return true;
    }
    bool bRet = false;
    if (bShow) {
        ListCtrl* pListCtrl = GetListCtrl();
        if (pListCtrl != nullptr) {
            std::wstring checkBoxClass = pListCtrl->GetCheckBoxClass();
            if (!checkBoxClass.empty()) {
                SetClass(checkBoxClass);
                bRet = IsShowCheckBox();
            }
        }
    }
    else {
        //���CheckBoxͼƬ��Դ���Ͳ���ʾ��
        ClearStateImages();
        ASSERT(!IsShowCheckBox());
        bRet = true;
    }
    if (IsShowCheckBox() != bOldShow) {
        UpdatePaddingLeft();
    }    
    return bRet;
}


void ListCtrlHeader::SetPaddingLeftValue(int32_t nPaddingLeft)
{
    if (nPaddingLeft < 0) {
        nPaddingLeft = 0;
    }
    if (m_nPaddingLeftValue != nPaddingLeft) {
        m_nPaddingLeftValue = nPaddingLeft;
        UpdatePaddingLeft();
    }    
}

void ListCtrlHeader::UpdatePaddingLeft()
{
    UiPadding rcPadding = GetPadding();
    UiPadding rcOldPadding = rcPadding;
    int32_t nCheckBoxWidth = GetCheckBoxImageWidth();
    if (nCheckBoxWidth > 0) {
        nCheckBoxWidth += m_nIconSpacing;
    }
    rcPadding.left = std::max(nCheckBoxWidth, m_nPaddingLeftValue);
    if (rcPadding.left != rcOldPadding.left) {
        SetPadding(rcPadding, false);
        //��ֹ�����Padding��ʹ��Paddingֻ�������ӿؼ�������Ҫ�ָ�
        SetEnableControlPadding(false);
    }
}

bool ListCtrlHeader::IsShowCheckBox() const
{
    //�����CheckBoxͼƬ��Դ������Ϊ��ʾ��CheckBox
    return !GetStateImage(kControlStateNormal).empty() && !GetSelectedStateImage(kControlStateNormal).empty();
}

int32_t ListCtrlHeader::GetCheckBoxImageWidth()
{
    if (GetWindow() == nullptr) {
        return 0;
    }
    UiSize sz = GetStateImageSize(kStateImageBk, kControlStateNormal);
    return sz.cx;
}

bool ListCtrlHeader::SetEnableCheckChangeEvent(bool bEnable)
{
    bool bOldValue = m_bEnableCheckChangeEvent;
    m_bEnableCheckChangeEvent = bEnable;
    return bOldValue;
}

}//namespace ui
