#include "Layout.h"
#include "duilib/Utils/AttributeUtil.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Core/Control.h"
#include "duilib/Core/Box.h"

namespace ui 
{
Layout::Layout() :
	m_iChildMarginX(0),
	m_iChildMarginY(0),
	m_pOwner(nullptr)
{
}

void Layout::SetOwner(Box* pOwner)
{
	m_pOwner = pOwner;
}

UiSize64 Layout::SetFloatPos(Control* pControl, const UiRect& rcContainer)
{
	ASSERT(pControl != nullptr);
	if ((pControl == nullptr) || (!pControl->IsVisible())) {
		return UiSize64();
	}
	UiRect rc = rcContainer;
	rc.Deflate(pControl->GetMargin());
	UiSize szAvailable(rc.Width(), rc.Height());
	szAvailable.Validate();

	UiEstSize estSize = pControl->EstimateSize(szAvailable);
	UiSize childSize(estSize.cx.GetInt32(), estSize.cy.GetInt32());
	if (estSize.cx.IsStretch()) {
		childSize.cx = CalcStretchValue(estSize.cx, szAvailable.cx);
	}
	if (estSize.cy.IsStretch()) {
		childSize.cy = CalcStretchValue(estSize.cy, szAvailable.cy);
	}
	childSize.cx = std::max(childSize.cx, 0);
	childSize.cy = std::max(childSize.cy, 0);
	
	if (childSize.cx < pControl->GetMinWidth()) {
		childSize.cx = pControl->GetMinWidth();
	}
	if (childSize.cx > pControl->GetMaxWidth()) {
		childSize.cx = pControl->GetMaxWidth();
	}
	
	if (childSize.cy < pControl->GetMinHeight()) {
		childSize.cy = pControl->GetMinHeight();
	}
	if (childSize.cy > pControl->GetMaxHeight()) {
		childSize.cy = pControl->GetMaxHeight();
	}

	UiRect childPos = GetFloatPos(pControl, rcContainer, childSize);
	pControl->SetPos(childPos);
	//TODO: 64λ�����Լ��
	return UiSize64(childPos.Width(), childPos.Height());
}

UiRect Layout::GetFloatPos(Control* pControl, UiRect rcContainer, UiSize childSize)
{
	rcContainer.Validate();
	UiMargin rcMargin = pControl->GetMargin();
	int32_t iPosLeft = rcContainer.left + rcMargin.left;
	int32_t iPosRight = rcContainer.right - rcMargin.right;
	int32_t iPosTop = rcContainer.top + rcMargin.top;
	int32_t iPosBottom = rcContainer.bottom - rcMargin.bottom;
	//����ռ䲻�㣬��������Ϊ�㣨���������õ�����С����������Ƶ�����֣�
	if (iPosRight < iPosLeft) {
		iPosRight = iPosLeft;
	}
	if (iPosBottom < iPosTop) {
		iPosBottom = iPosTop;
	}
	
	childSize.cx = std::max(childSize.cx, 0);
	childSize.cy = std::max(childSize.cy, 0);

	int32_t childWidth = childSize.cx;
	int32_t childHeight = childSize.cy;

	//�����ӿؼ�ָ���ĺ�����뷽ʽ��������뷽ʽ�����пؼ�
	HorAlignType horAlignType = pControl->GetHorAlignType();
	VerAlignType verAlignType = pControl->GetVerAlignType();

	int32_t childLeft = 0;
	int32_t childRight = 0;
	int32_t childTop = 0;
	int32_t childBottm = 0;

	if (horAlignType == kHorAlignLeft) {
		childLeft = iPosLeft;
		childRight = childLeft + childWidth;
	}
	else if (horAlignType == kHorAlignRight) {
		childRight = iPosRight;
		childLeft = childRight - childWidth;
	}
	else if (horAlignType == kHorAlignCenter) {
		childLeft = iPosLeft + (iPosRight - iPosLeft - childWidth) / 2;
		childRight = childLeft + childWidth;
	}

	if (verAlignType == kVerAlignTop) {
		childTop = iPosTop;
		childBottm = childTop + childHeight;
	}
	else if (verAlignType == kVerAlignBottom) {
		childBottm = iPosBottom;
		childTop = childBottm - childHeight;
	}
	else if (verAlignType == kVerAlignCenter) {
		childTop = iPosTop + (iPosBottom - iPosTop - childHeight) / 2;
		childBottm = childTop + childHeight;
	}

	UiRect childPos(childLeft, childTop, childRight, childBottm);
	return childPos;
}

bool Layout::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	bool hasAttribute = true;
	if ((strName == L"child_margin") || (strName == L"childmargin")) {
		int32_t iMargin = _wtoi(strValue.c_str());
		SetChildMargin(iMargin);
	}
	else if ((strName == L"child_margin_x") || (strName == L"childmarginx")) {
		int32_t iMargin = _wtoi(strValue.c_str());
		SetChildMarginX(iMargin);
	}
	else if ((strName == L"child_margin_y") || (strName == L"childmarginy")) {
		int32_t iMargin = _wtoi(strValue.c_str());
		SetChildMarginY(iMargin);
	}
	else {
		hasAttribute = false;
	}
	return hasAttribute;
}

UiSize64 Layout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
{
	DeflatePadding(rc);
	UiSize64 size;
	for (Control* pControl : items) {
		if ((pControl == nullptr) || (!pControl->IsVisible())) {
			continue;
		}
		UiSize64 controlSize = SetFloatPos(pControl, rc);
		size.cx = std::max(size.cx, controlSize.cx);
		size.cy = std::max(size.cy, controlSize.cy);
	}
	UiPadding rcPadding;
	if (m_pOwner != nullptr) {
		rcPadding = m_pOwner->GetPadding();
	}
	if (size.cx > 0) {
		size.cx += (rcPadding.left + rcPadding.right);
	}
	if (size.cy > 0) {
		size.cy += (rcPadding.top + rcPadding.bottom);
	}
	return size;
}

UiSize Layout::EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable)
{
	//��ȣ�ȡ�����ӿؼ���ȵ����ֵ������Margin��Padding�ȣ������������͵��ӿؼ�
	//�߶ȣ�ȡ�����ӿؼ��߶ȵ����ֵ������Margin��Padding�ȣ������������͵��ӿؼ�
	szAvailable.Validate();
	UiSize maxSize;
	UiSize itemSize;
	for (Control* pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
			continue;
		}
		UiEstSize estSize = pControl->EstimateSize(szAvailable);
		itemSize = UiSize(estSize.cx.GetInt32(), estSize.cy.GetInt32());
		if (estSize.cx.IsStretch()) {
			//�������͵��ӿؼ���������
			itemSize.cx = 0;
		}
		else {
			if (itemSize.cx < pControl->GetMinWidth()) {
				itemSize.cx = pControl->GetMinWidth();
			}
			if (itemSize.cx > pControl->GetMaxWidth()) {
				itemSize.cx = pControl->GetMaxWidth();
			}
		}
		if (estSize.cy.IsStretch()) {
			//�������͵��ӿؼ���������
			itemSize.cy = 0;
		}
		else {
			if (itemSize.cy < pControl->GetMinHeight()) {
				itemSize.cy = pControl->GetMinHeight();
			}
			if (itemSize.cy > pControl->GetMaxHeight()) {
				itemSize.cy = pControl->GetMaxHeight();
			}
		}
		UiMargin rcMargin = pControl->GetMargin();
		if (itemSize.cx > 0) {
			maxSize.cx = std::max(itemSize.cx + rcMargin.left + rcMargin.right, maxSize.cx);
		}
		if (itemSize.cy > 0) {
			maxSize.cy = std::max(itemSize.cy + rcMargin.top + rcMargin.bottom, maxSize.cy);
		}
	}
	UiPadding rcPadding;
	if (m_pOwner != nullptr) {
		rcPadding = m_pOwner->GetPadding();
	}
	if (maxSize.cx > 0) {
		maxSize.cx += rcPadding.left + rcPadding.right;
	}
	if (maxSize.cy > 0) {
		maxSize.cy += rcPadding.top + rcPadding.bottom;
	}
	if ((maxSize.cx == 0) || (maxSize.cy == 0)){
		CheckConfig(items);
	}
	return maxSize;
}

void Layout::CheckConfig(const std::vector<Control*>& items)
{
	//���m_pOwner�Ŀ�߶���auto�������ӿؼ��Ŀ�߶���stretch����ô�õ��Ľ�����㣬���Ӹ�����
	if (m_pOwner == nullptr) {
		return;
	}
	if (!m_pOwner->GetFixedWidth().IsAuto() && !m_pOwner->GetFixedHeight().IsAuto()) {
		return;
	}

	bool isAllWidthStretch = true;
	bool isAllHeightStretch = true;
	size_t childCount = 0;
	for (Control* pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
			continue;
		}
		if (!pControl->GetFixedWidth().IsStretch()) {
			isAllWidthStretch = false;
		}
		if (!pControl->GetFixedHeight().IsStretch()) {
			isAllHeightStretch = false;
		}
		++childCount;
	}
	if ((childCount > 0) && m_pOwner->GetFixedWidth().IsAuto() && isAllWidthStretch) {
		ASSERT(!"���ô��󣺵�ǰ�����Ŀ���auto���ӿؼ��Ŀ���stretch��������Ϊ�㣡");
	}
	if ((childCount > 0) && m_pOwner->GetFixedHeight().IsAuto() && isAllHeightStretch) {
		ASSERT(!"���ô��󣺵�ǰ�����ĸ���auto���ӿؼ��ĸ߶���stretch������߶�Ϊ�㣡");
	}
}

void Layout::SetChildMargin(int32_t iMargin)
{
	ASSERT(iMargin >= 0);
	iMargin = std::max(iMargin, 0);
	GlobalManager::Instance().Dpi().ScaleInt(iMargin);
	bool isChanged = ((int32_t)m_iChildMarginX != iMargin) || ((int32_t)m_iChildMarginY != iMargin);
	m_iChildMarginX = TruncateToUInt16((uint32_t)iMargin);
	m_iChildMarginY = TruncateToUInt16((uint32_t)iMargin);
	ASSERT(m_pOwner != nullptr);
	if (isChanged && (m_pOwner != nullptr)) {
		m_pOwner->Arrange();
	}
}

void Layout::SetChildMarginX(int32_t iMarginX)
{
	ASSERT(iMarginX >= 0);
	iMarginX = std::max(iMarginX, 0);
	GlobalManager::Instance().Dpi().ScaleInt(iMarginX);
	bool isChanged = ((int32_t)m_iChildMarginX != iMarginX);
	m_iChildMarginX = TruncateToUInt16((uint32_t)iMarginX);
	ASSERT(m_pOwner != nullptr);
	if (isChanged && (m_pOwner != nullptr)) {
		m_pOwner->Arrange();
	}
}

void Layout::SetChildMarginY(int32_t iMarginY)
{
	ASSERT(iMarginY >= 0);
	iMarginY = std::max(iMarginY, 0);
	GlobalManager::Instance().Dpi().ScaleInt(iMarginY);
	bool isChanged = ((int32_t)m_iChildMarginY != iMarginY);
	m_iChildMarginY = TruncateToUInt16((uint32_t)iMarginY);
	ASSERT(m_pOwner != nullptr);
	if (isChanged && (m_pOwner != nullptr)) {
		m_pOwner->Arrange();
	}
}

void Layout::DeflatePadding(UiRect& rc) const
{
	ASSERT(m_pOwner != nullptr);
	if (m_pOwner != nullptr) {
		rc.Deflate(m_pOwner->GetPadding());
		rc.Validate();
	}
}

} // namespace ui
