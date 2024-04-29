#include "VLayout.h"
#include "duilib/Core/Box.h"
#include <map>

namespace ui 
{

VLayout::VLayout()
{
}

UiSize64 VLayout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
{
	DeflatePadding(rc);
	const UiSize szAvailable(rc.Width(), rc.Height());

	//�߶�Ϊstretch�Ŀؼ���
	int32_t stretchCount = 0;
	//�̶��߶ȵĿؼ����ܵĸ߶�
	int32_t cyFixedTotal = 0;
	//��Ҫ���в��ִ�������пؼ�(KEY�ǿؼ���VALUE�ǿ�Ⱥ͸߶�)
	std::map<Control*, UiEstSize> itemsMap;

	//����ÿ���ؼ��Ŀ�Ⱥ͸߶ȣ�����¼��Map��
	for(auto pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
			continue;
		}

		UiEstSize estSize = pControl->EstimateSize(szAvailable);
		UiSize sz = UiSize(estSize.cx.GetInt32(), estSize.cy.GetInt32());
		UiMargin rcMargin = pControl->GetMargin();
		//����߶�
		if(estSize.cy.IsStretch()) {
			stretchCount++;
			cyFixedTotal += (rcMargin.top + rcMargin.bottom);
		}
		else {
			if (sz.cy < pControl->GetMinHeight()) {
				sz.cy = pControl->GetMinHeight();
			}
			if (sz.cy > pControl->GetMaxHeight()) {
				sz.cy = pControl->GetMaxHeight();
			}
			if (sz.cy < 0) {
				sz.cy = 0;
			}
			cyFixedTotal += (sz.cy + rcMargin.top + rcMargin.bottom);
		}

		//������
		if (estSize.cx.IsStretch()) {
			sz.cx = CalcStretchValue(estSize.cx, szAvailable.cx) - rcMargin.left - rcMargin.right;
			sz.cx = std::max(sz.cx, 0);
		}
		if (sz.cx < pControl->GetMinWidth()) {
			sz.cx = pControl->GetMinWidth();
		}
		if (sz.cx > pControl->GetMaxWidth()) {
			sz.cx = pControl->GetMaxWidth();
		}
		if (sz.cx < 0) {
			sz.cx = 0;
		}
		if (!estSize.cy.IsStretch()) {
			estSize.cy.SetInt32(sz.cy);
		}
		estSize.cx.SetInt32(sz.cx);//cx���Ѿ�����õ�ȷ����ֵ��������������Զ�����ֵ
		itemsMap[pControl] = estSize;
	}
	if (!itemsMap.empty()) {
		cyFixedTotal += ((int32_t)itemsMap.size() - 1) * GetChildMarginY();
	}
	
	float fStretchValue = 0;	//ÿ������ؼ���������Ϊ100%ʱ��Ӧ�÷���ĸ߶�ֵ
	float fTotalStretch = 0;	//������Ϊ100%ʱΪһ���ؼ���λ���ܹ��ж��ٸ��ؼ���λ
	if (stretchCount > 0) {		
		for (auto iter : itemsMap) {
			const UiEstSize& itemEstSize = iter.second;
			if (itemEstSize.cy.IsStretch()) {
				fTotalStretch += itemEstSize.cy.GetStretchPercentValue() / 100.0f;
			}
		}
		ASSERT(fTotalStretch > 0);
		if (fTotalStretch > 0) {
			fStretchValue = std::max(0, (szAvailable.cy - cyFixedTotal)) / fTotalStretch;
		}
	}

	//��һ��Ԥ����ȥ����Ҫʹ��minheight/maxheight�Ŀؼ��������¼���ƽ���߶�
	bool bStretchCountChanged = false;
	if ((fStretchValue > 0) && !itemsMap.empty()) {
		for (auto iter = itemsMap.begin(); iter != itemsMap.end(); ++iter) {
			Control* pControl = iter->first;
			UiEstSize estSize = iter->second;
			UiSize sz(estSize.cx.GetInt32(), estSize.cy.GetInt32());
			if (estSize.cy.IsStretch()) {
				int32_t cyStretch = static_cast<int32_t>(fStretchValue * estSize.cy.GetStretchPercentValue() / 100.0f);
				sz.cy = cyStretch;
				if (sz.cy < pControl->GetMinHeight()) {
					sz.cy = pControl->GetMinHeight();
				}
				if (sz.cy > pControl->GetMaxHeight()) {
					sz.cy = pControl->GetMaxHeight();
				}
				if (sz.cy != cyStretch) {
					//����ؼ���Ҫʹ��min����max�߶ȣ���ƽ��ֵ���Ƴ�������Fixed�ؼ���
					estSize.cy.SetInt32(sz.cy);
					iter->second = estSize;
					--stretchCount;
					cyFixedTotal += sz.cy; //Margin�Ѿ��ۼӹ�������Ҫ�����ۼ�
					bStretchCountChanged = true;
				}
			}
		}
	}

	//���¼���Stretch�ؼ��ĸ߶ȣ���������μ����Ϊ׼��
	//��������ܿռ䲻�㣬��ԭ��������ƽ���߶ȣ����ȱ�֤ǰ��Ŀؼ�����������ʾ
	if (bStretchCountChanged && (stretchCount > 0) && (szAvailable.cy > cyFixedTotal)) {
		fTotalStretch = 0;
		for (auto iter : itemsMap) {
			const UiEstSize& itemEstSize = iter.second;
			if (itemEstSize.cy.IsStretch()) {
				fTotalStretch += itemEstSize.cy.GetStretchPercentValue() / 100.0f;
			}
		}
		ASSERT(fTotalStretch > 0);
		if (fTotalStretch > 0) {
			fStretchValue = std::max(0, (szAvailable.cy - cyFixedTotal)) / fTotalStretch;
		}
	}

	int32_t iPosLeft = rc.left;
	int32_t iPosRight = rc.right;
	int32_t iPosY = rc.top;

	// Place elements
	int64_t cyNeeded = 0;//��Ҫ���ܸ߶�
	int64_t cxNeeded = 0;//��Ҫ���ܿ�ȣ�ȡ�����ӿؼ��Ŀ�����ֵ��
	int32_t assignedStretch = 0; //�Ѿ����������ռ��С

	for(auto pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible()) {
			continue;
		}
		if( pControl->IsFloat() ) {
			SetFloatPos(pControl, rc);
			continue;
		}

		UiMargin rcMargin = pControl->GetMargin();
		ASSERT(itemsMap.find(pControl) != itemsMap.end());
		UiEstSize estSize = itemsMap[pControl];
		UiSize sz(estSize.cx.GetInt32(), estSize.cy.GetInt32());

		//����߶�
		if(estSize.cy.IsStretch()) {
			int32_t cyStretch = static_cast<int32_t>(fStretchValue * estSize.cy.GetStretchPercentValue() / 100.0f);
			sz.cy = cyStretch;
			if (sz.cy < pControl->GetMinHeight()) {
				sz.cy = pControl->GetMinHeight();
			}
			if (sz.cy > pControl->GetMaxHeight()) {
				sz.cy = pControl->GetMaxHeight();
			}
			assignedStretch += sz.cy;
			--stretchCount;
			if (stretchCount == 0) {
				//�����һ������ؼ��ϣ���������ƫ��
				int32_t deviation = szAvailable.cy - cyFixedTotal - assignedStretch;
				if (deviation > 0) {
					sz.cy += deviation;
				}
			}
		}
				
		//����������뷽ʽ��ȷ��X������
		int32_t childLeft = 0;
		int32_t childRight = 0;
		HorAlignType horAlignType = pControl->GetHorAlignType();
		if (horAlignType == kHorAlignLeft) {
			childLeft = iPosLeft + rcMargin.left;
			childRight = childLeft + sz.cx;
		}
		else if (horAlignType == kHorAlignRight) {
			childRight = iPosRight - rcMargin.right;
			childLeft = childRight - sz.cx;
		}
		else if (horAlignType == kHorAlignCenter) {
			childLeft = iPosLeft + (iPosRight - iPosLeft + rcMargin.left - rcMargin.right - sz.cx) / 2;
			childRight = childLeft + sz.cx;
		}

		//���ÿؼ���λ��
		UiRect controlRect(childLeft, iPosY + rcMargin.top, childRight, iPosY + rcMargin.top + sz.cy);		
		pControl->SetPos(controlRect);
		cxNeeded = std::max(cxNeeded, (int64_t)controlRect.Width() + rcMargin.left + rcMargin.right);

		//������ǰY������ֵ
		iPosY += (sz.cy + rcMargin.top + rcMargin.bottom + GetChildMarginY());
		cyNeeded += (sz.cy + rcMargin.top + rcMargin.bottom);
	}
	if (!itemsMap.empty()) {
		cyNeeded += ((int64_t)itemsMap.size() - 1) * GetChildMarginY();
	}

	UiSize64 size(cxNeeded, cyNeeded);
	UiPadding rcPadding;
	if (GetOwner() != nullptr) {
		rcPadding = GetOwner()->GetPadding();
	}
	if (size.cx > 0) {
		size.cx += (rcPadding.left + rcPadding.right);
	}
	if (size.cy > 0) {
		size.cy += (rcPadding.top + rcPadding.bottom);
	}
	return size;
}

UiSize VLayout::EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable)
{
	//��ȣ�ȡ�����ӿؼ���ȵ����ֵ������Margin��Padding�ȣ������������͵��ӿؼ�
	//�߶ȣ������ӿؼ��߶�֮�ͣ�����Margin��Padding�ȣ������������͵��ӿؼ�
	UiSize totalSize;
	UiSize itemSize;
	int32_t estimateCount = 0;
	for (Control* pControl : items)	{
		if ((pControl == nullptr) || !pControl->IsVisible() || pControl->IsFloat()) {
			continue;
		}

		estimateCount++;
		UiMargin rcMargin = pControl->GetMargin();
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
		
		if (itemSize.cx > 0) {
			totalSize.cx = std::max(itemSize.cx + rcMargin.left + rcMargin.right, totalSize.cx);
		}
		if (itemSize.cy > 0) {
			totalSize.cy += (itemSize.cy + rcMargin.top + rcMargin.bottom);
		}		
	}

	if ((totalSize.cy > 0) && ((estimateCount - 1) > 0)) {
		totalSize.cy += (estimateCount - 1) * GetChildMarginY();
	}
	UiPadding rcPadding;
	if (GetOwner() != nullptr) {
		rcPadding = GetOwner()->GetPadding();
	}
	if (totalSize.cx > 0) {
		totalSize.cx += (rcPadding.left + rcPadding.right);
	}
	if (totalSize.cy > 0) {
		totalSize.cy += (rcPadding.top + rcPadding.bottom);
	}
	if ((totalSize.cx == 0) || (totalSize.cy == 0)) {
		CheckConfig(items);
	}
	return totalSize;
}

} // namespace ui
