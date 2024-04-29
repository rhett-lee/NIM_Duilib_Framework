#include "ListBox.h"
#include "duilib/Core/ScrollBar.h"

namespace ui 
{

//��ѡ��ʱ���Ƿ���ʾѡ�񱳾�ɫ: 0 - Ĭ�Ϲ���; 1 - ��ʾ����ɫ; 2: ����ʾ����ɫ
enum ePaintSelectedColors
{
	PAINT_SELECTED_COLORS_DEFAULT = 0,
	PAINT_SELECTED_COLORS_YES = 1,
	PAINT_SELECTED_COLORS_NO = 2
};

ListBox::ListBox(Layout* pLayout) :
	ScrollBox(pLayout),
	m_bScrollSelect(false),
	m_bMultiSelect(false),
	m_uPaintSelectedColors(PAINT_SELECTED_COLORS_DEFAULT),
	m_bSelectNextWhenActiveRemoved(false),
	m_iCurSel(Box::InvalidIndex),
	m_pCompareFunc(nullptr),
	m_pCompareContext(nullptr)
{
}

std::wstring ListBox::GetType() const { return L"ListBox"; }

void ListBox::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == L"multi_select") {
		SetMultiSelect(strValue == L"true");
	}
	else if (strName == L"paint_selected_colors") {
		if (strValue == L"true") {
			m_uPaintSelectedColors = PAINT_SELECTED_COLORS_YES;
		}
		else {
			m_uPaintSelectedColors = PAINT_SELECTED_COLORS_NO;
		}
	}
	else if ((strName == L"scroll_select") || (strName == L"scrollselect")) {
		SetScrollSelect(strValue == L"true");
	}
	else if (strName == L"select_next_when_active_removed") {
		SetSelectNextWhenActiveRemoved(strValue == L"true");
	}
	else {
		ScrollBox::SetAttribute(strName, strValue);
	}
}

void ListBox::HandleEvent(const EventArgs& msg)
{
	if (IsDisabledEvents(msg)) {
		//�������������Ϣ�����ҿؼ���Disabled�ģ�ת�����ϲ�ؼ�
		Box* pParent = GetParent();
		if (pParent != nullptr) {
			pParent->SendEvent(msg);
		}
		else {
			__super::HandleEvent(msg);
		}
		return;
	}
	bool bHandled = false;
	if (msg.Type == kEventKeyDown) {
		bHandled = OnListBoxKeyDown(msg);
	}
	else if (msg.Type == kEventMouseWheel) {
		bHandled = OnListBoxMouseWheel(msg);
	}	
	if(!bHandled) {
		__super::HandleEvent(msg);
	}
}

bool ListBox::OnListBoxKeyDown(const EventArgs& msg)
{
	ASSERT(msg.Type == kEventKeyDown);
	bool bHandled = false;
	bool bArrowKeyDown = (msg.Type == kEventKeyDown) &&
						  ((msg.chKey == VK_UP) || (msg.chKey == VK_DOWN) ||
						  (msg.chKey == VK_LEFT) || (msg.chKey == VK_RIGHT) ||
						  (msg.chKey == VK_PRIOR) || (msg.chKey == VK_NEXT) ||
						  (msg.chKey == VK_HOME) || (msg.chKey == VK_END));
	if (!bArrowKeyDown) {
		return bHandled;
	}

	bool bHasSelectItem = GetCurSel() < GetItemCount(); //�Ƿ��е�ѡ��ѡ����
	if (!IsMultiSelect() && (GetItemCount() > 0) && !bHasSelectItem) {
		//��ǰ��������ѡ�����Ҫ��ѯ���ࣨ���ʵ�֣����Ƿ���ѡ����
		size_t nDestItemIndex = Box::InvalidIndex;
		if (OnFindSelectable(GetCurSel(), SelectableMode::kSelect, 1, nDestItemIndex)) {
			bHasSelectItem = true;
			ASSERT(GetCurSel() == nDestItemIndex);
		}
	}
	if (IsMultiSelect() || (GetItemCount() == 0) || !bHasSelectItem) {
		//�������ݡ�֧�ֶ�ѡ����ѡ���������£���֧�ֵ�ѡ��ݼ��߼�����֧��HOME��END������Ӧ(����)
		if (msg.chKey == VK_HOME) {
			if (IsHorizontalScrollBar()) {
				HomeLeft();
			}
			else {
				HomeUp();
			}
			bHandled = true;
		}
		else if (msg.chKey == VK_END) {
			if (IsHorizontalScrollBar()) {
				EndRight();
			}
			else {
				EndDown(false, false);
			}
			bHandled = true;
		}
		return bHandled;
	}

	//��ѡ�������ݡ���ѡ��������
	bHandled = true;
	switch (msg.chKey) {
	case VK_UP:
		if (IsHorizontalScrollBar()) {
			//���������������1��
			SelectItemPrevious(true, true);
		}
		else {
			//���Ǻ��������������1��
			size_t nColumns = 0;
			size_t nRows = 0;
			GetDisplayItemCount(false, nColumns, nRows);
			if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel) &&
				(GetItemCountBefore(m_iCurSel) >= nColumns)) {
				//�������Ϲ���1��
				SelectItemCountN(true, true, false, nColumns);
			}
		}		
		break;
	case VK_DOWN:
		if (IsHorizontalScrollBar()) {
			//���������������1��
			SelectItemNext(true, true);
		}
		else {
			//���Ǻ��������������1��
			size_t nColumns = 0;
			size_t nRows = 0;
			GetDisplayItemCount(false, nColumns, nRows);
			if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel) &&
				(GetItemCountAfter(m_iCurSel) >= nColumns)) {
				SelectItemCountN(true, true, true, nColumns);
			}
			else {
				PageDown();
				SelectItem(m_iCurSel, true, false);
			}
		}
		break;
	case VK_LEFT:
		if (IsHorizontalScrollBar()) {
			//���������������1��
			size_t nColumns = 0;
			size_t nRows = 0;
			GetDisplayItemCount(false, nColumns, nRows);
			if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel) &&
				(GetItemCountBefore(m_iCurSel) >= nRows)) {
				SelectItemCountN(true, true, false, nRows);
			}
		}
		else {
			//���Ǻ��������������1��
			SelectItemPrevious(true, true);
		}
		break;
	case VK_RIGHT:
		if (IsHorizontalScrollBar()) {
			//���������������1��
			size_t nColumns = 0;
			size_t nRows = 0;
			GetDisplayItemCount(false, nColumns, nRows);
			if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel) &&
				(GetItemCountAfter(m_iCurSel) >= nRows)) {
				SelectItemCountN(true, true, true, nRows);
			}
			else {
				PageRight();
				SelectItem(m_iCurSel, true, false);
			}
		}
		else {
			//���Ǻ��������������1��
			SelectItemNext(true, true);
		}
		break;
	case VK_PRIOR:
		SelectItemPage(true, true, false, 0);
		break;
	case VK_NEXT:
		SelectItemPage(true, true, true, 0);
		break;
	case VK_HOME:
		SelectItemHome(true, true);
		break;
	case VK_END:
		SelectItemEnd(true, true);
		break;
	default:
		bHandled = false;
		break;
	}
	return bHandled;
}

bool ListBox::OnListBoxMouseWheel(const EventArgs& msg)
{
	ASSERT(msg.Type == kEventMouseWheel);
	bool bHandled = false;
	if (m_bScrollSelect && (msg.Type == kEventMouseWheel)) {
		int32_t deltaValue = GET_WHEEL_DELTA_WPARAM(msg.wParam);
		if (deltaValue != 0) {
			bool bForward = deltaValue > 0 ? false : true;
			SelectItemPage(true, true, bForward, std::abs(deltaValue));
			bHandled = true;
		}
	}
	return bHandled;
}

bool ListBox::SelectItem(size_t iIndex)
{
	return SelectItem(iIndex, true, true);
}

size_t ListBox::SelectItemPrevious(bool bTakeFocus, bool bTriggerEvent)
{
	return SelectItemCountN(bTakeFocus, bTriggerEvent, false, 1);
}

size_t ListBox::SelectItemNext(bool bTakeFocus, bool bTriggerEvent)
{
	return SelectItemCountN(bTakeFocus, bTriggerEvent, true, 1);
}

size_t ListBox::SelectItemPageUp(bool bTakeFocus, bool bTriggerEvent)
{
	return SelectItemPage(bTakeFocus, bTriggerEvent, false, 0);
}

size_t ListBox::SelectItemPageDown(bool bTakeFocus, bool bTriggerEvent)
{
	return SelectItemPage(bTakeFocus, bTriggerEvent, true, 0);
}

size_t ListBox::SelectItemHome(bool bTakeFocus, bool bTriggerEvent)
{
	if (GetItemCount() == 0) {
		return Box::InvalidIndex;
	}
	size_t iIndex = 0;
	size_t nDestItemIndex = Box::InvalidIndex;
	if (OnFindSelectable(m_iCurSel, SelectableMode::kHome, 1, nDestItemIndex)) {
		iIndex = nDestItemIndex;
	}
	size_t itemIndex = FindSelectable(iIndex, true);
	if (Box::IsValidItemIndex(itemIndex)) {		
		SelectItem(itemIndex, false, false);
		itemIndex = SelectEnsureVisible(itemIndex, bTakeFocus);
		if (bTriggerEvent) {
			SendEvent(kEventSelect, itemIndex, Box::InvalidIndex);
		}
	}
	return itemIndex;
}

size_t ListBox::SelectItemEnd(bool bTakeFocus, bool bTriggerEvent)
{
	if (GetItemCount() == 0) {
		return Box::InvalidIndex;
	}
	size_t iIndex = GetItemCount() - 1;
	size_t nDestItemIndex = Box::InvalidIndex;
	if (OnFindSelectable(m_iCurSel, SelectableMode::kEnd, 1, nDestItemIndex)) {
		iIndex = nDestItemIndex;
	}
	size_t itemIndex = FindSelectable(iIndex, false);
	if (Box::IsValidItemIndex(itemIndex)) {
		SelectItem(itemIndex, false, false);
		itemIndex = SelectEnsureVisible(itemIndex, bTakeFocus);
		if (bTriggerEvent) {
			SendEvent(kEventSelect, itemIndex, Box::InvalidIndex);
		}
	}
	return itemIndex;
}

size_t ListBox::SelectItemPage(bool bTakeFocus, bool bTriggerEvent, bool bForward, int32_t nDeltaValue)
{
	//Page Up / Page Down ���ķ�ҳ�߼�
	size_t itemIndex = Box::InvalidIndex;
	const size_t itemCount = GetItemCount();
	if (itemCount == 0) {
		return itemIndex;
	}

	bool bIsHorizontal = IsHorizontalScrollBar(); //�Ƿ�Ϊ���������
	if (nDeltaValue == 0) {
		//����nDeltaValueֵ
		nDeltaValue = bIsHorizontal ? GetRect().Width() : GetRect().Height();
	}
	if (nDeltaValue == 0) {
		if (m_iCurSel < itemCount) {
			EnsureVisible(m_iCurSel);
		}
		return itemIndex;
	}
	size_t nCountPerPage = 1;
	size_t nColumns = 0;
	size_t nRows = 0;
	size_t nTotalDisplayCount = GetDisplayItemCount(bIsHorizontal, nColumns, nRows);
	if (nTotalDisplayCount < 1) {
		nTotalDisplayCount = 1;
	}
	if (bIsHorizontal) {
		//ֻ�к������������������
		nCountPerPage = nTotalDisplayCount * std::abs(nDeltaValue) / GetRect().Width();
		if (nCountPerPage > nRows) {
			nCountPerPage -= nRows; //����1��
		}
		if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel)) {
			//����޷����㷭ҳ����ôͣ�������һ��
			while (nCountPerPage > nRows) {
				if (bForward) {
					if (GetItemCountAfter(m_iCurSel) >= nCountPerPage) {
						break;
					}
				}
				else {
					if (GetItemCountBefore(m_iCurSel) >= nCountPerPage) {
						break;
					}
				}
				if (nCountPerPage > nRows) {
					nCountPerPage -= nRows;
				}
				else {
					break;
				}
			}
		}
	}
	else {
		//����������������������
		nCountPerPage = nTotalDisplayCount * std::abs(nDeltaValue) / GetRect().Height();
		if (nCountPerPage > nColumns) {
			nCountPerPage -= nColumns; //����1��
		}
		if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel)) {
			//����޷����㷭ҳ����ôͣ�������һ��
			while (nCountPerPage > nColumns) {
				if (bForward) {
					if (GetItemCountAfter(m_iCurSel) >= nCountPerPage) {
						break;
					}
				}
				else {
					if (GetItemCountBefore(m_iCurSel) >= nCountPerPage) {
						break;
					}
				}
				if (nCountPerPage > nColumns) {
					nCountPerPage -= nColumns;
				}
				else {
					break;
				}
			}
		}
	}
	if (nCountPerPage < 1) {
		nCountPerPage = 1;
	}
	
	itemIndex = Box::InvalidIndex;
	if ((m_iCurSel < GetItemCount()) && IsSelectableItem(m_iCurSel)) {
		if (bForward) {
			if (GetItemCountAfter(m_iCurSel) >= nCountPerPage) {
				itemIndex = SelectItemCountN(bTakeFocus, bTriggerEvent, bForward, nCountPerPage);
			}
		}
		else {
			if (GetItemCountBefore(m_iCurSel) >= nCountPerPage) {
				itemIndex = SelectItemCountN(bTakeFocus, bTriggerEvent, bForward, nCountPerPage);
			}
		}
	}
	if (itemIndex == Box::InvalidIndex) {
		if (IsHorizontalScrollBar()) {
			if (bForward) {
				PageRight();
			}
			else {
				PageLeft();
			}			
		}
		else {
			if (bForward) {
				PageDown();
			}
			else {
				PageUp();
			}
		}
		SelectItem(m_iCurSel, true, false);
	}
	return itemIndex;
}

size_t ListBox::SelectItemCountN(bool bTakeFocus, bool bTriggerEvent, bool bForward, size_t nCount)
{
	if (m_iCurSel >= GetItemCount()) {
		//��ǰ����Ч��ѡ����޷�����
		return Box::InvalidIndex;
	}
	if (!IsSelectableItem(m_iCurSel)) {
		//�����ǰѡ����Ϊ����ѡ����޷�����
		return Box::InvalidIndex;
	}
	if ((nCount == 0) || (nCount == Box::InvalidIndex)){
		nCount = 1;
	}
	bool bExceedFirst = false; //�Ѿ������1��
	size_t iIndex = Box::InvalidIndex;
	if (!bForward) {
		//Page Up
		if (m_iCurSel > nCount) {
			iIndex = m_iCurSel - nCount;
		}
		else {
			bExceedFirst = true;
		}
	}
	else {
		//Page Down
		iIndex = m_iCurSel + nCount;
	}
	if (IsSelectableItem(iIndex)) {
		//Ŀ��������ڣ�ֱ�ӷ���
		size_t itemIndex = iIndex;
		if (itemIndex < GetItemCount()) {
			SelectItem(itemIndex, false, false);
			itemIndex = SelectEnsureVisible(itemIndex, bTakeFocus);
			if (bTriggerEvent) {
				SendEvent(kEventSelect, itemIndex, Box::InvalidIndex);
			}
		}
		return itemIndex;
	}

	//������ҪԤ�������ݣ������Ԥ������Ϊ��m_iCurSel��ֵ���ܷ����仯
	size_t nDestItemIndex = Box::InvalidIndex;
	SelectableMode mode = bForward ? SelectableMode::kForward : SelectableMode::kBackward;
	if (OnFindSelectable(m_iCurSel, mode, nCount, nDestItemIndex)) {
		iIndex = nDestItemIndex;
		ASSERT(iIndex < GetItemCount());
		if (iIndex >= GetItemCount()) {
			return Box::InvalidIndex;
		}
	}
	else {
		if (bExceedFirst) {
			iIndex = 0;
		}
	}
	const size_t itemCount = GetItemCount();
	if (iIndex >= itemCount) {
		iIndex = itemCount - 1;
	}	
	size_t itemIndex = FindSelectable(iIndex, bForward);
	if (itemIndex < itemCount) {		
		SelectItem(itemIndex, false, false);
		itemIndex = SelectEnsureVisible(itemIndex, bTakeFocus);
		if (bTriggerEvent) {
			SendEvent(kEventSelect, itemIndex, Box::InvalidIndex);
		}
	}
	return itemIndex;
}

size_t ListBox::SelectEnsureVisible(size_t itemIndex, bool bTakeFocus)
{
	itemIndex = EnsureVisible(itemIndex);
	if (bTakeFocus) {
		Control* pSelectedControl = GetItemAt(itemIndex);
		if ((pSelectedControl != nullptr) && pSelectedControl->IsVisible()) {
			pSelectedControl->SetFocus();
		}
		ASSERT(pSelectedControl != nullptr);
		ASSERT(pSelectedControl->IsVisible());
		ASSERT(GetWindow()->GetFocus() == pSelectedControl);
	}
	return itemIndex;
}

bool ListBox::IsSelectableItem(size_t itemIndex) const
{
	bool bSelectable = false;
	Control* pControl = GetItemAt(itemIndex);
	if ((pControl != nullptr) &&
		pControl->IsSelectableType() &&
		pControl->IsVisible() &&
		pControl->IsEnabled()) {
		bSelectable = true;
	}
	return bSelectable;
}

size_t ListBox::GetDisplayItemCount(bool bIsHorizontal, size_t& nColumns, size_t& nRows) const
{
	nColumns = 1;
	nRows = 1;
	size_t nCount = 1;
	bool bRet = false;
	HTileLayout* pHTileLayout = dynamic_cast<HTileLayout*>(GetLayout());
	if ((pHTileLayout != nullptr) && pHTileLayout->IsFreeLayout()) {
		pHTileLayout = nullptr;
	}
	VTileLayout* pVTileLayout = dynamic_cast<VTileLayout*>(GetLayout());
	if ((pVTileLayout != nullptr) && pVTileLayout->IsFreeLayout()) {
		pVTileLayout = nullptr;
	}
	if (pHTileLayout != nullptr) {
		nRows = CalcHTileRows(pHTileLayout);
		nColumns = CalcHTileColumns(pHTileLayout);
		nCount = nColumns * nRows;
		bRet = true;
	}
	else if (pVTileLayout != nullptr) {		
		nRows = CalcVTileRows(pVTileLayout);
		nColumns = CalcVTileColumns(pVTileLayout);
		nCount = nColumns * nRows;
		bRet = true;
	}
	if(!bRet) {
		std::map<int32_t, int32_t> rows;
		std::map<int32_t, int32_t> columns;		
		UiRect boxRect = GetRect();
		const size_t nItemCount = GetItemCount();
		for (size_t nItemIndex = 0; nItemIndex < nItemCount; ++nItemIndex) {
			Control* pControl = GetItemAt(nItemIndex);
			if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
				continue;
			}

			bool bDisplayItem = false;
			const UiRect& rc = pControl->GetRect();
			if (bIsHorizontal) {
				if ((rc.left >= boxRect.left) &&
					(rc.right <= boxRect.right)) {
					if ((rc.top >= boxRect.top) && (rc.top < boxRect.bottom)) {
						bDisplayItem = true;
					}
					else if ((rc.bottom >= boxRect.top) && (rc.top < boxRect.bottom)) {
						bDisplayItem = true;
					}
				}
			}
			else {
				if ((rc.top >= boxRect.top) &&
					(rc.bottom <= boxRect.bottom)) {
					if ((rc.left >= boxRect.left) && (rc.left < boxRect.right)) {
						bDisplayItem = true;
					}
					else if ((rc.right >= boxRect.left) && (rc.right < boxRect.right)) {
						bDisplayItem = true;
					}
				}
			}
			if (bDisplayItem) {
				rows[pControl->GetRect().top] = 0;
				columns[pControl->GetRect().left] = 0;
				++nCount;
			}
		}
		nColumns = columns.size();
		nRows = rows.size();
		if (nCount >= (nRows * nColumns)) {
			nCount = nRows * nColumns;
		}
	}
	return nCount;
}

int32_t ListBox::CalcHTileRows(HTileLayout* pHTileLayout) const
{
	int32_t nRows = 1;
	if (pHTileLayout == nullptr) {
		return nRows;
	}
	UiSize szItem = pHTileLayout->GetItemSize();
	if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
		return nRows;
	}
	int32_t childMarginY = pHTileLayout->GetChildMarginY();
	if (childMarginY < 0) {
		childMarginY = 0;
	}
	nRows = pHTileLayout->GetRows();
	bool bAutoRows = pHTileLayout->IsAutoCalcRows();
	if (bAutoRows) {
		nRows = 0;
	}
	if (nRows <= 0) {
		UiRect rc = GetRect();
		rc.Deflate(GetControlPadding());
		int32_t totalHeight = rc.Height();
		while (totalHeight > 0) {
			totalHeight -= szItem.cy;
			if (nRows != 0) {
				totalHeight -= childMarginY;
			}
			if (totalHeight >= 0) {
				++nRows;
			}
		}
	}
	if (nRows <= 0) {
		nRows = 1;
	}
	return nRows;
}

int32_t ListBox::CalcHTileColumns(HTileLayout* pHTileLayout) const
{
	int32_t nColumns = 1;
	if (pHTileLayout == nullptr) {
		return nColumns;
	}
	UiSize szItem = pHTileLayout->GetItemSize();
	if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
		return nColumns;
	}
	int32_t childMarginX = pHTileLayout->GetChildMarginX();
	if (childMarginX < 0) {
		childMarginX = 0;
	}
	nColumns = 0;
	UiRect rc = GetRect();
	rc.Deflate(GetControlPadding());
	int32_t totalWidth = rc.Width();
	while (totalWidth > 0) {
		totalWidth -= szItem.cx;
		if (nColumns != 0) {
			totalWidth -= childMarginX;
		}
		if (totalWidth >= 0) {
			++nColumns;
		}
	}
	if (nColumns <= 0) {
		nColumns = 1;
	}
	return nColumns;
}

int32_t ListBox::CalcVTileColumns(VTileLayout* pVTileLayout) const
{
	int32_t nColumns = 1;
	if (pVTileLayout == nullptr) {
		return nColumns;
	}
	UiSize szItem = pVTileLayout->GetItemSize();
	if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
		return nColumns;
	}
	int32_t childMarginX = pVTileLayout->GetChildMarginX();
	if (childMarginX < 0) {
		childMarginX = 0;
	}

	nColumns = pVTileLayout->GetColumns();
	bool bAutoColumns = pVTileLayout->IsAutoCalcColumns();
	if (bAutoColumns) {
		nColumns = 0;
	}
	if (nColumns <= 0) {
		UiRect rc = GetRect();
		rc.Deflate(GetControlPadding());
		int32_t totalWidth = rc.Width();
		while (totalWidth > 0) {
			totalWidth -= szItem.cx;
			if (nColumns != 0) {
				totalWidth -= childMarginX;
			}
			if (totalWidth >= 0) {
				++nColumns;
			}
		}
	}
	if (nColumns <= 0) {
		nColumns = 1;
	}
	return nColumns;
}

int32_t ListBox::CalcVTileRows(VTileLayout* pVTileLayout) const
{
	int32_t nRows = 1;
	if (pVTileLayout == nullptr) {
		return nRows;
	}
	UiSize szItem = pVTileLayout->GetItemSize();
	if ((szItem.cx <= 0) || (szItem.cy <= 0)) {
		return nRows;
	}
	int32_t childMarginY = pVTileLayout->GetChildMarginY();
	if (childMarginY < 0) {
		childMarginY = 0;
	}
	nRows = 0;
	UiRect rc = GetRect();
	rc.Deflate(GetControlPadding());
	int32_t totalHeight = rc.Height();
	while (totalHeight > 0) {
		totalHeight -= szItem.cy;
		if (nRows != 0) {
			totalHeight -= childMarginY;
		}
		if (totalHeight >= 0) {
			++nRows;
		}
	}
	if (nRows <= 0) {
		nRows = 1;
	}
	return nRows;
}

void ListBox::SendEvent(EventType eventType, WPARAM wParam, LPARAM lParam, TCHAR tChar, const UiPoint& mousePos)
{
	ScrollBox::SendEvent(eventType, wParam, lParam, tChar, mousePos);
}

void ListBox::SendEvent(const EventArgs& event)
{
	ScrollBox::SendEvent(event);
}

size_t ListBox::GetCurSel() const
{
	return m_iCurSel;
}

void ListBox::SetCurSel(size_t iIndex)
{
	if (Box::IsValidItemIndex(iIndex)) {
		ASSERT(iIndex < GetItemCount());
		if (iIndex > GetItemCount()) {
			return;
		}
	}	
	m_iCurSel = iIndex;
}

bool ListBox::IsScrollSelect() const
{
	return m_bScrollSelect;
}

void ListBox::SetScrollSelect(bool bScrollSelect)
{
	m_bScrollSelect = bScrollSelect;
}

bool ListBox::IsSelectNextWhenActiveRemoved() const
{
	return m_bSelectNextWhenActiveRemoved;
}

void ListBox::SetSelectNextWhenActiveRemoved(bool bSelectNextItem)
{
	m_bSelectNextWhenActiveRemoved = bSelectNextItem;
}

void ListBox::GetSelectedItems(std::vector<size_t>& selectedIndexs) const
{
	selectedIndexs.clear();
	const size_t itemCount = GetItemCount();
	for (size_t iIndex = 0; iIndex < itemCount; ++iIndex) {
		Control* pControl = m_items[iIndex];
		if ((pControl == nullptr) || !pControl->IsVisible() || !pControl->IsEnabled()) {
			continue;
		}
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
		if (pListItem != nullptr) {
			if (pListItem->IsSelected()) {
				selectedIndexs.push_back(iIndex);
			}
		}
	}
}

size_t ListBox::FindSelectable(size_t iIndex, bool bForward) const
{
	return __super::FindSelectable(iIndex, bForward);
}

bool ListBox::OnFindSelectable(size_t /*nCurSel*/, SelectableMode /*mode*/,
							   size_t /*nCount*/, size_t& /*nDestItemIndex*/)
{
	return false;
}

size_t ListBox::GetItemCountBefore(size_t nCurSel)
{
	if (nCurSel < GetItemCount()) {
		return nCurSel;
	}
	else {
		return 0;
	}
}

size_t ListBox::GetItemCountAfter(size_t nCurSel)
{
	size_t nCount = 0;
	if (nCurSel < GetItemCount()) {
		nCount = GetItemCount() - nCurSel - 1;
	}
	return nCount;
}

bool ListBox::SelectItem(size_t iIndex, bool bTakeFocus, bool bTriggerEvent, uint64_t /*vkFlag*/)
{
	if (IsMultiSelect()) {
		//��ѡ
		return SelectItemMulti(iIndex, bTakeFocus, bTriggerEvent);
	}
	else {
		//��ѡ
		return SelectItemSingle(iIndex, bTakeFocus, bTriggerEvent);
	}
}

bool ListBox::UnSelectItem(size_t iIndex, bool bTriggerEvent)
{
	bool bHasEvent = false;
	Control* pControl = GetItemAt(iIndex);
	if (pControl != nullptr) {
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
		if ((pListItem != nullptr) && pListItem->IsSelected()) {
			pListItem->OptionSelected(false, bTriggerEvent);
			bHasEvent = true;			
			//����״̬�仯ʱ�ػ�
			Invalidate();
		}
	}
	if (iIndex == m_iCurSel) {
		m_iCurSel = Box::InvalidIndex;
	}
	if (bTriggerEvent && bHasEvent) {
		//�¼���������Ҫ���ں�������֮ǰ�����ܷ��ڴ����м�
		SendEvent(kEventUnSelect, iIndex, Box::InvalidIndex);
	}
	return true;
}

void ListBox::OnItemSelectedChanged(size_t /*iIndex*/, IListBoxItem* /*pListBoxItem*/)
{
}

void ListBox::OnItemCheckedChanged(size_t /*iIndex*/, IListBoxItem* /*pListBoxItem*/)
{
}

bool ListBox::SelectItemSingle(size_t iIndex, bool bTakeFocus, bool bTriggerEvent)
{
	//��ѡ
	if (iIndex == m_iCurSel) {
		Control* pControl = GetItemAt(iIndex);
		if (pControl == nullptr) {
			m_iCurSel = Box::InvalidIndex;
			return false;
		}		
		//ȷ���ɼ���Ȼ�󷵻�		
		if (bTakeFocus) {
			pControl->SetFocus();
		}
		bool bChanged = false;
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
		if ((pListItem != nullptr) && !pListItem->IsSelected()) {
			bChanged = true;
			pListItem->OptionSelected(true, bTriggerEvent);
		}
		Invalidate();
		if (bChanged && bTriggerEvent) {
			SendEvent(kEventSelect, m_iCurSel, Box::InvalidIndex);
		}
		return true;
	}
	bool hasUnSelectEvent = false;
	const size_t iOldSel = m_iCurSel;
	if (Box::IsValidItemIndex(iOldSel)) {
		//ȡ����ѡ�����ѡ��״̬
		Control* pControl = GetItemAt(iOldSel);
		if (pControl != nullptr) {
			IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
			if ((pListItem != nullptr) && pListItem->IsSelected()) {
				pListItem->OptionSelected(false, bTriggerEvent);
				hasUnSelectEvent = true;				
			}
		}
		m_iCurSel = Box::InvalidIndex;
	}
	if (!Box::IsValidItemIndex(iIndex)) {
		Invalidate();
		if (hasUnSelectEvent && bTriggerEvent) {
			SendEvent(kEventUnSelect, iOldSel, Box::InvalidIndex);
		}
		return false;
	}

	Control* pControl = GetItemAt(iIndex);
	if ((pControl == nullptr) || !pControl->IsVisible() || !pControl->IsEnabled()) {
		Invalidate();
		if (hasUnSelectEvent && bTriggerEvent) {
			SendEvent(kEventUnSelect, iOldSel, Box::InvalidIndex);
		}
		return false;
	}
	IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
	if (pListItem == nullptr) {
		Invalidate();
		if (hasUnSelectEvent && bTriggerEvent) {
			SendEvent(kEventUnSelect, iOldSel, Box::InvalidIndex);
		}
		return false;
	}
	m_iCurSel = iIndex;
	//����ѡ��״̬
	pListItem->OptionSelected(true, bTriggerEvent);
	pControl = GetItemAt(m_iCurSel);
	if (pControl != nullptr) {		
		if (bTakeFocus) {
			pControl->SetFocus();
		}
	}

	Invalidate();
	if (hasUnSelectEvent && bTriggerEvent) {
		SendEvent(kEventUnSelect, iOldSel, Box::InvalidIndex);
	}
	if (bTriggerEvent) {
		SendEvent(kEventSelect, m_iCurSel, iOldSel);
	}	
	return true;
}

bool ListBox::SelectItemMulti(size_t iIndex, bool bTakeFocus, bool bTriggerEvent)
{
	//��ѡ: m_iCurSel ʼ��ִ�����һ��ѡ����
	size_t iOldSel = m_iCurSel;
	m_iCurSel = Box::InvalidIndex;
	if (!Box::IsValidItemIndex(iIndex)) {
		Invalidate();
		return false;
	}
	Control* pControl = GetItemAt(iIndex);
	if ((pControl == nullptr) || !pControl->IsVisible() || !pControl->IsEnabled()){
		Invalidate();
		return false;
	}
	IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
	if (pListItem == nullptr) {
		Invalidate();
		return false;
	}
	
	if (pListItem->IsSelected()) {
		//��ѡʱ���ٴ�ѡ��ʱ����ȡ��ѡ����
		pListItem->OptionSelected(false, false);
		Invalidate();
		if (bTriggerEvent) {
			SendEvent(kEventUnSelect, iIndex, Box::InvalidIndex);
		}
	}
	else {
		//���ԭ���Ƿ�ѡ��״̬������Ϊѡ��״̬
		m_iCurSel = iIndex;
		pListItem->OptionSelected(true, false);		
		if (bTakeFocus) {			
			pControl->SetFocus();
		}
		Invalidate();
		if (bTriggerEvent) {
			SendEvent(kEventSelect, iIndex, iOldSel);
		}
	}	
	return true;
}

void ListBox::EnsureVisible(const UiRect& rcItem,
							ListBoxVerVisible vVisibleType,
							ListBoxHorVisible hVisibleType)
{
	UiRect rcNewItem = rcItem;
	UiSize scrollOffset = GetScrollOffset();
	rcNewItem.Offset(-scrollOffset.cx, -scrollOffset.cy);
	UiRect rcList = GetPos();
	rcList.Deflate(GetPadding());

	ScrollBar* pVScrollBar = GetVScrollBar();
	if (pVScrollBar && pVScrollBar->IsValid()) {
		if (IsVScrollBarAtLeft()) {
			ASSERT(pVScrollBar->GetFixedWidth().GetInt32() > 0);
			rcList.left += pVScrollBar->GetFixedWidth().GetInt32();
		}
		else {
			ASSERT(m_pVScrollBar->GetFixedWidth().GetInt32() > 0);
			rcList.right -= pVScrollBar->GetFixedWidth().GetInt32();
		}
	}

	ScrollBar* pHScrollBar = GetHScrollBar();
	if (pHScrollBar && pHScrollBar->IsValid()) {
		ASSERT(pHScrollBar->GetFixedHeight().GetInt32() > 0);
		rcList.bottom -= pHScrollBar->GetFixedHeight().GetInt32();
	}

	if ((rcNewItem.left >= rcList.left) && (rcNewItem.top >= rcList.top) && 
		(rcNewItem.right <= rcList.right) && (rcNewItem.bottom <= rcList.bottom)) {
		IListBoxItem* listBoxElement = dynamic_cast<IListBoxItem*>(GetParent());
		IListBoxOwner* lisBoxOwner = nullptr;
		if (listBoxElement != nullptr) {
			lisBoxOwner = listBoxElement->GetOwner();
		}
		if (lisBoxOwner != nullptr) {
			lisBoxOwner->EnsureVisible(rcNewItem, vVisibleType, hVisibleType);
		}		
		return;
	}
	//ˮƽ������
	int32_t dx = 0;
	if (hVisibleType == ListBoxHorVisible::kVisibleAtCenter) {
		//������ʾ
		if (rcNewItem.left < rcList.CenterX()) {
			dx = rcNewItem.left - rcList.CenterX();
		}
		if (rcNewItem.right > rcList.CenterX()) {
			dx = rcNewItem.right - rcList.CenterX();
		}
	}
	else if (hVisibleType == ListBoxHorVisible::kVisibleAtLeft) {
		//������ʾ
		dx = rcNewItem.left - rcList.left;
	}
	else if (hVisibleType == ListBoxHorVisible::kVisibleAtRight) {
		//������ʾ
		dx = rcNewItem.right - rcList.right;
	}
	else {
		if (rcNewItem.left < rcList.left) {
			dx = rcNewItem.left - rcList.left;
		}
		if (rcNewItem.right > rcList.right) {
			dx = rcNewItem.right - rcList.right;
		}
		UiRect rcNewList = rcList;
		rcNewList.top = rcNewItem.top;
		rcNewList.bottom = rcNewItem.bottom;
		if (rcNewItem.ContainsRect(rcNewList)) {
			//����������Ѿ��ڿɼ����򣬲���������������������һζ�
			dx = 0;
		}
	}
	//��ֱ������
	int32_t dy = 0;
	if (vVisibleType == ListBoxVerVisible::kVisibleAtCenter) {
		//������ʾ
		if (rcNewItem.top < rcList.CenterY()) {
			dy = rcNewItem.top - rcList.CenterY();
		}
		if (rcNewItem.bottom > rcList.CenterY()) {
			dy = rcNewItem.bottom - rcList.CenterY();
		}
	}
	else if (vVisibleType == ListBoxVerVisible::kVisibleAtTop) {
		//��������
		dy = rcNewItem.top - rcList.top;
	}
	else if (vVisibleType == ListBoxVerVisible::kVisibleAtBottom) {
		//�ײ�����
		dy = rcNewItem.bottom - rcList.bottom;
	}
	else {
		//ֻҪ�ɼ�����
		if (rcNewItem.top < rcList.top) {
			dy = rcNewItem.top - rcList.top;
		}
		if (rcNewItem.bottom > rcList.bottom) {
			dy = rcNewItem.bottom - rcList.bottom;
		}
		UiRect rcNewList = rcList;
		rcNewList.left = rcNewItem.left;
		rcNewList.right = rcNewItem.right;
		if (rcNewItem.ContainsRect(rcNewList)) {
			//����������Ѿ��ڿɼ����򣬲���������������������»ζ�
			dy = 0;
		}
	}
	if ((dx != 0) || (dy != 0)) {
		UiSize64 sz = GetScrollPos();
		SetScrollPos(UiSize64(sz.cx + dx, sz.cy + dy));
		Invalidate();
	}
}

void ListBox::StopScroll()
{
	StopScrollAnimation();
}

bool ListBox::CanPaintSelectedColors(bool bHasStateImages) const
{
	if (m_uPaintSelectedColors == PAINT_SELECTED_COLORS_YES) {
		return true;
	}
	else if (m_uPaintSelectedColors == PAINT_SELECTED_COLORS_NO) {
		return false;
	}
	if (bHasStateImages && IsMultiSelect()) {
		//�����CheckBox����ѡ��ʱ��Ĭ�ϲ���ʾѡ�񱳾�ɫ
		return false;
	}
	return true;
}

bool ListBox::ButtonDown(const EventArgs& msg)
{
	bool ret = __super::ButtonDown(msg);
	StopScroll();
	return ret;
}

bool ListBox::IsHorizontalLayout() const
{
	LayoutType type = GetLayout()->GetLayoutType();
	bool bHorizontal = false;
	if ((type == LayoutType::HLayout) ||
		(type == LayoutType::HTileLayout) ||
		(type == LayoutType::VirtualHLayout) ||
		(type == LayoutType::VirtualHTileLayout)) {
		bHorizontal = true;
	}
	return bHorizontal;
}

bool ListBox::IsHorizontalScrollBar() const
{
	bool bHasVScrollBar = false;
	ScrollBar* pVScrollBar = GetVScrollBar();
	if (pVScrollBar && pVScrollBar->IsValid()) {
		bHasVScrollBar = true;
	}

	bool bHasHScrollBar = false;
	ScrollBar* pHScrollBar = GetHScrollBar();
	if (pHScrollBar && pHScrollBar->IsValid()) {
		bHasHScrollBar = true;
	}

	bool bIsHorizontal = (bHasHScrollBar && !bHasVScrollBar) ? true : false;
	if (GetLayout()->IsHLayout()) {
		//ȷ���Ǻ��򲼾�
		bIsHorizontal = true;
	}
	else if (GetLayout()->IsVLayout()) {
		bIsHorizontal = false;
	}
	return bIsHorizontal;
}

bool ListBox::ScrollItemToTop(size_t iIndex)
{
	Control* pControl = GetItemAt(iIndex);
	if ((pControl == nullptr) || !pControl->IsVisible()) {
		return false;
	}
	if (IsHorizontalLayout()) {
		//���򲼾�
		if (GetScrollRange().cx != 0) {
			UiSize64 scrollPos = GetScrollPos();
			scrollPos.cx = pControl->GetPos().left - GetPosWithoutPadding().left;
			if (scrollPos.cx >= 0) {
				SetScrollPos(scrollPos);
				return true;
			}
		}
	}
	else {
		//���򲼾�
		if (GetScrollRange().cy != 0) {
			UiSize64 scrollPos = GetScrollPos();
			scrollPos.cy = pControl->GetPos().top - GetPosWithoutPadding().top;
			if (scrollPos.cy >= 0) {
				SetScrollPos(scrollPos);
				return true;
			}
		}
	}
	return false;
}

bool ListBox::ScrollItemToTop(const std::wstring& itemName)
{
	const size_t itemCount = m_items.size();
	for (size_t iIndex = 0; iIndex < itemCount; ++iIndex) {
		Control* pControl = m_items[iIndex];
		if ((pControl == nullptr) || !pControl->IsVisible()) {
			continue;
		}
		if (pControl->IsNameEquals(itemName)) {
			return ScrollItemToTop(iIndex);
		}
	}
	return false;
}

Control* ListBox::GetTopItem() const
{
	if (IsHorizontalLayout()) {
		//���򲼾�
		int32_t listLeft = GetPos().left + GetPadding().left + GetScrollOffset().cx;
		for (Control* pControl : m_items) {
			ASSERT(pControl != nullptr);
			if (pControl->IsVisible() && !pControl->IsFloat() && pControl->GetPos().right >= listLeft) {
				return pControl;
			}
		}
	}
	else {
		//���򲼾�
		int32_t listTop = GetPos().top + GetPadding().top + GetScrollOffset().cy;
		for (Control* pControl : m_items) {
			ASSERT(pControl != nullptr);
			if (pControl->IsVisible() && !pControl->IsFloat() && pControl->GetPos().bottom >= listTop) {
				return pControl;
			}
		}
	}
	return nullptr;
}

bool ListBox::SetItemIndex(Control* pControl, size_t iIndex)
{
	size_t iOrginIndex = GetItemIndex(pControl);
	if (!Box::IsValidItemIndex(iOrginIndex)) {
		return false;
	}
	if (iOrginIndex == iIndex) {
		return true;
	}

	IListBoxItem* pSelectedListItem = nullptr;
	if (Box::IsValidItemIndex(m_iCurSel)) {
		pSelectedListItem = dynamic_cast<IListBoxItem*>(GetItemAt(m_iCurSel));
	}
	if (!ScrollBox::SetItemIndex(pControl, iIndex)) {
		return false;
	}
	size_t iMinIndex = std::min(iOrginIndex, iIndex);
	size_t iMaxIndex = std::max(iOrginIndex, iIndex);
	for(size_t i = iMinIndex; i < iMaxIndex + 1; ++i) {
		Control* pItemControl = GetItemAt(i);
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pItemControl);
		if( pListItem != NULL ) {
			pListItem->SetListBoxIndex(i);
		}
	}
	if (Box::IsValidItemIndex(m_iCurSel) && pSelectedListItem != nullptr) {
		m_iCurSel = pSelectedListItem->GetListBoxIndex();
	}
	return true;
}

size_t ListBox::EnsureVisible(size_t iIndex, ListBoxVerVisible vVisibleType, ListBoxHorVisible hVisibleType)
{
	Control* pControl = GetItemAt(iIndex);
	ASSERT(pControl != nullptr);
	if (pControl != nullptr) {
		UiRect rcItem = pControl->GetPos();
		EnsureVisible(rcItem, vVisibleType, hVisibleType);
		ASSERT(GetItemAt(iIndex) == pControl);
	}
	return iIndex;
}

bool ListBox::AddItem(Control* pControl)
{
	// Override the AddItem() method so we can add items specifically to
	// the intended widgets. Headers are assumed to be
	// answer the correct interface so we can add multiple list headers.
	// The list items should know about us
	IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
	if( pListItem != nullptr) {
		pListItem->SetOwner(this);
		pListItem->SetListBoxIndex(GetItemCount());
		if (!IsMultiSelect()) {
			pListItem->OptionSelected(false, false);
		}
	}
	return ScrollBox::AddItem(pControl);
}

bool ListBox::AddItemAt(Control* pControl, size_t iIndex)
{
	// Override the AddItemAt() method so we can add items specifically to
	// the intended widgets. Headers and are assumed to be
	// answer the correct interface so we can add multiple list headers.

	if (!ScrollBox::AddItemAt(pControl, iIndex)) {
		return false;
	}

	// The list items should know about us
	IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(pControl);
	if( pListItem != nullptr ) {
		pListItem->SetOwner(this);
		pListItem->SetListBoxIndex(iIndex);
		if (!IsMultiSelect()) {
			pListItem->OptionSelected(false, false);
		}
	}

	const size_t itemCount = GetItemCount();
	for(size_t i = iIndex + 1; i < itemCount; ++i) {
		Control* p = GetItemAt(i);
		pListItem = dynamic_cast<IListBoxItem*>(p);
		if( pListItem != nullptr ) {
			pListItem->SetListBoxIndex(i);
		}
	}
	if (Box::IsValidItemIndex(m_iCurSel) && (m_iCurSel >= iIndex)) {
		m_iCurSel += 1;
	}
	return true;
}

bool ListBox::RemoveItem(Control* pControl)
{
	size_t iIndex = GetItemIndex(pControl);
	if (!Box::IsValidItemIndex(iIndex)) {
		return false;
	}
	return RemoveItemAt(iIndex);
}

bool ListBox::RemoveItemAt(size_t iIndex)
{
	if (!IsAutoDestroyChild()) {
		Control* p = GetItemAt(iIndex);
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(p);
		if (pListItem != nullptr) {
			pListItem->SetOwner(nullptr);
		}
	}
	if (!ScrollBox::RemoveItemAt(iIndex)) {
		return false;
	}
	const size_t itemCount = GetItemCount();
	for(size_t i = iIndex; i < itemCount; ++i) {
		Control* p = GetItemAt(i);
		IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(p);
		if (pListItem != nullptr) {
			pListItem->SetListBoxIndex(i);
		}
	}

	if (Box::IsValidItemIndex(m_iCurSel)) {
		if (iIndex == m_iCurSel) {
			if (!IsMultiSelect() && m_bSelectNextWhenActiveRemoved) {
				SelectItem(FindSelectable(m_iCurSel--, false));
			}
			else {
				m_iCurSel = Box::InvalidIndex;
			}
		}
		else if (iIndex < m_iCurSel) {
			m_iCurSel -= 1;
		}
	}
	return true;
}

void ListBox::RemoveAllItems()
{
	if (!IsAutoDestroyChild()) {
		const size_t itemCount = GetItemCount();
		for (size_t i = 0; i < itemCount; ++i) {
			Control* p = GetItemAt(i);
			IListBoxItem* pListItem = dynamic_cast<IListBoxItem*>(p);
			if (pListItem != nullptr) {
				pListItem->SetOwner(nullptr);
			}
		}
	}
	m_iCurSel = Box::InvalidIndex;
	ScrollBox::RemoveAllItems();
}

bool ListBox::SortItems(PFNCompareFunc pfnCompare, void* pCompareContext)
{
	if (pfnCompare == nullptr) {
		return false;
	}		
	if (m_items.empty()) {
		return true;
	}

	m_pCompareFunc = pfnCompare;
	m_pCompareContext = pCompareContext;
	qsort_s(&(*m_items.begin()), m_items.size(), sizeof(Control*), ListBox::ItemComareFunc, this);	
	IListBoxItem* pItem = nullptr;
	const size_t itemCount = m_items.size();
	for (size_t i = 0; i < itemCount; ++i) {
		pItem = dynamic_cast<IListBoxItem*>(m_items[i]);
		if (pItem != nullptr) {
			pItem->SetListBoxIndex(i);
			//ȡ�����������е�ѡ����
			pItem->OptionSelected(false, false);
		}
	}
	SelectItem(Box::InvalidIndex);
	SetPos(GetPos());
	Invalidate();
	return true;
}

int __cdecl ListBox::ItemComareFunc(void *pvlocale, const void *item1, const void *item2)
{
	ListBox *pThis = (ListBox*)pvlocale;
	if (!pThis || !item1 || !item2) {
		return 0;
	}
	return pThis->ItemComareFunc(item1, item2);
}

int __cdecl ListBox::ItemComareFunc(const void *item1, const void *item2)
{
	Control *pControl1 = *(Control**)item1;
	Control *pControl2 = *(Control**)item2;
	return m_pCompareFunc(pControl1, pControl2, m_pCompareContext);
}

bool ListBox::IsMultiSelect() const
{
	return m_bMultiSelect;
}

void ListBox::SetMultiSelect(bool bMultiSelect)
{
	m_bMultiSelect = bMultiSelect;
	if (!bMultiSelect) {
		//ֻҪbMultiSelectΪfalse����ִ��ȡ�����ж�ѡ���߼�
		//�˴������ж���ԭֵ�Ƿ�仯�������Ƿ�ִ������Ĵ��룬������ܻ�Ӱ�����ࣨTreeView���߼���
		if (OnSwitchToSingleSelect()) {
			Invalidate();
		}
	}
}

void ListBox::EnsureSingleSelection()
{
	if (!IsMultiSelect()) {
		OnSwitchToSingleSelect();
	}	
}

bool ListBox::OnSwitchToSingleSelect()
{
	bool bChanged = false;
	IListBoxItem* pItem = nullptr;
	const size_t itemCount = m_items.size();
	if (m_iCurSel > itemCount) { 
		//�����ѡ״̬��ͬ����ʹ�õ�һ��ѡ�����Ϊ���յ�ѡ��ѡ����
		for (size_t i = 0; i < itemCount; ++i) {
			pItem = dynamic_cast<IListBoxItem*>(m_items[i]);
			if ((pItem != nullptr) && pItem->IsSelected()) {
				m_iCurSel = i;
				break;
			}
		}
	}
	for (size_t i = 0; i < itemCount; ++i) {
		pItem = dynamic_cast<IListBoxItem*>(m_items[i]);
		if ((pItem != nullptr) && pItem->IsSelected()) {
			if (m_iCurSel != i) {
				pItem->OptionSelected(false, false); //������Select�¼�
				bChanged = true;
			}
		}
	}
	if (UpdateCurSelItemSelectStatus()) {
		bChanged = true;
	}
	return bChanged;
}

bool ListBox::UpdateCurSelItemSelectStatus()
{
	//ͬ����ǰѡ�����״̬
	bool bChanged = false;
	size_t curSelIndex = GetCurSel();
	if (Box::IsValidItemIndex(curSelIndex)) {
		bool bSelectItem = false;
		IListBoxItem* pItem = dynamic_cast<IListBoxItem*>(GetItemAt(curSelIndex));
		if (pItem != nullptr) {
			bSelectItem = pItem->IsSelected();
		}
		if (!bSelectItem) {
			SetCurSel(Box::InvalidIndex);
			bChanged = true;
		}
	}
	return bChanged;
}

} // namespace ui
