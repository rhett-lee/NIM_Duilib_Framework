#include "HLayout.h"
#include "duilib/Core/Box.h"
#include <map>

namespace ui 
{

HLayout::HLayout()
{
}

UiSize64 HLayout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
{
	DeflatePadding(rc);
	const UiSize szAvailable(rc.Width(), rc.Height());
	
	//���Ϊstretch�Ŀؼ���
	int32_t stretchCount = 0;
	//�̶���ȵĿؼ����ܵĸ߶�
	int32_t cxFixedTotal = 0;
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
		//������
		if(estSize.cx.IsStretch()) {
			stretchCount++;
			cxFixedTotal += (rcMargin.left + rcMargin.right);
		}
		else {
			if (sz.cx < pControl->GetMinWidth()) {
				sz.cx = pControl->GetMinWidth();
			}
			if (sz.cx > pControl->GetMaxWidth()) {
				sz.cx = pControl->GetMaxWidth();
			}
			if (sz.cx < 0) {
				sz.cx = 0;
			}
			cxFixedTotal += (sz.cx + rcMargin.left + rcMargin.right);
		}
		
		//����߶�
		if (estSize.cy.IsStretch()) {
			sz.cy = (CalcStretchValue(estSize.cy, szAvailable.cy) - rcMargin.top - rcMargin.bottom);
			sz.cy = std::max(sz.cy, 0);
		}
		if (sz.cy < pControl->GetMinHeight()) {
			sz.cy = pControl->GetMinHeight();
		}
		if (sz.cy > pControl->GetMaxHeight()) {
			sz.cy = pControl->GetMaxHeight();
		}
		if (sz.cy < 0) {
			sz.cy = 0;
		}
		if (!estSize.cx.IsStretch()) {
			estSize.cx.SetInt32(sz.cx);
		}
		estSize.cy.SetInt32(sz.cy);//cy���Ѿ�����õ�ȷ����ֵ��������������Զ�����ֵ
		itemsMap[pControl] = estSize;
	}
	if (!itemsMap.empty()) {
		cxFixedTotal += ((int32_t)itemsMap.size() - 1) * GetChildMarginX();
	}

	float fStretchValue = 0;	//ÿ������ؼ���������Ϊ100%ʱ��Ӧ�÷���ĸ߶�ֵ
	float fTotalStretch = 0;	//������Ϊ100%ʱΪһ���ؼ���λ���ܹ��ж��ٸ��ؼ���λ
	if (stretchCount > 0) {
		for (auto iter : itemsMap) {
			const UiEstSize& itemEstSize = iter.second;
			if (itemEstSize.cx.IsStretch()) {
				fTotalStretch += itemEstSize.cx.GetStretchPercentValue() / 100.0f;
			}
		}
		ASSERT(fTotalStretch > 0);
		if (fTotalStretch > 0) {
			fStretchValue = std::max(0, (szAvailable.cx - cxFixedTotal)) / fTotalStretch;
		}
	}

	//��һ��Ԥ����ȥ����Ҫʹ��minwidth/maxwidth�Ŀؼ��������¼���ƽ���߶�
	bool bStretchCountChanged = false;
	if ((fStretchValue > 0) && !itemsMap.empty()) {
		for (auto iter = itemsMap.begin(); iter != itemsMap.end(); ++iter) {
			Control* pControl = iter->first;
			UiEstSize estSize = iter->second;
			UiSize sz(estSize.cx.GetInt32(), estSize.cy.GetInt32());
			if (estSize.cx.IsStretch()) {
				int32_t cxStretch = static_cast<int32_t>(fStretchValue * estSize.cx.GetStretchPercentValue() / 100.0f);
				sz.cx = cxStretch;
				if (sz.cx < pControl->GetMinWidth()) {
					sz.cx = pControl->GetMinWidth();
				}
				if (sz.cx > pControl->GetMaxWidth()) {
					sz.cx = pControl->GetMaxWidth();
				}
				if (sz.cx != cxStretch) {
					//����ؼ���Ҫʹ��min����max��ȣ���ƽ��ֵ���Ƴ�������Fixed�ؼ���
					estSize.cx.SetInt32(sz.cx);
					iter->second = estSize;
					--stretchCount;
					cxFixedTotal += sz.cx; //Margin�Ѿ��ۼӹ�������Ҫ�����ۼ�
					bStretchCountChanged = true;
				}
			}
		}
	}
	//���¼���Stretch�ؼ��Ŀ�ȣ���������μ����Ϊ׼��
	//��������ܿռ䲻�㣬��ԭ��������ƽ���߶ȣ����ȱ�֤ǰ��Ŀؼ�����������ʾ
	if (bStretchCountChanged && (stretchCount > 0) && (szAvailable.cx > cxFixedTotal)) {
		fTotalStretch = 0;
		for (auto iter : itemsMap) {
			const UiEstSize& itemEstSize = iter.second;
			if (itemEstSize.cx.IsStretch()) {
				fTotalStretch += itemEstSize.cx.GetStretchPercentValue() / 100.0f;
			}
		}
		ASSERT(fTotalStretch > 0);
		if (fTotalStretch > 0) {
			fStretchValue = std::max(0, (szAvailable.cx - cxFixedTotal)) / fTotalStretch;
		}
	}

	int32_t iPosTop = rc.top;
	int32_t iPosBottom = rc.bottom;
	int32_t iPosX = rc.left;

	// Place elements
	int64_t cyNeeded = 0;//��Ҫ���ܸ߶ȣ�ȡ�����ӿؼ��ĸ߶����ֵ��
	int64_t cxNeeded = 0;//��Ҫ���ܿ��
	int32_t assignedStretch = 0; //�Ѿ����������ռ��С

	for(auto pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible()) {
			continue;
		}
		if (pControl->IsFloat()) {
			SetFloatPos(pControl, rc);
			continue;
		}

		UiMargin rcMargin = pControl->GetMargin();
		ASSERT(itemsMap.find(pControl) != itemsMap.end());
		UiEstSize estSize = itemsMap[pControl];
		UiSize sz(estSize.cx.GetInt32(), estSize.cy.GetInt32());

		//������
		if(estSize.cx.IsStretch()) {
			int32_t cxStretch = static_cast<int32_t>(fStretchValue * estSize.cx.GetStretchPercentValue() / 100.0f);
			sz.cx = cxStretch;
			if (sz.cx < pControl->GetMinWidth()) {
				sz.cx = pControl->GetMinWidth();
			}
			if (sz.cx > pControl->GetMaxWidth()) {
				sz.cx = pControl->GetMaxWidth();
			}
			assignedStretch += sz.cx;
			--stretchCount;
			if (stretchCount == 0) {
				//�����һ������ؼ��ϣ���������ƫ��
				int32_t deviation = szAvailable.cx - cxFixedTotal - assignedStretch;
				if (deviation > 0) {
					sz.cx += deviation;
				}
			}
		}

		//����������뷽ʽ��ȷ��Y������
		int32_t childTop = 0;
		int32_t childBottm = 0;
		VerAlignType verAlignType = pControl->GetVerAlignType();
		if (verAlignType == kVerAlignTop) {
			childTop = iPosTop + rcMargin.top;
			childBottm = childTop + sz.cy;
		}
		else if (verAlignType == kVerAlignBottom) {
			childBottm = iPosBottom - rcMargin.bottom;
			childTop = childBottm - sz.cy;
		}
		else if (verAlignType == kVerAlignCenter) {
			childTop = iPosTop + (iPosBottom - iPosTop + rcMargin.top - rcMargin.bottom - sz.cy) / 2;
			childBottm = childTop + sz.cy;
		}

		//���ÿؼ���λ��
		UiRect rcChildPos(iPosX + rcMargin.left, childTop, iPosX + rcMargin.left + sz.cx, childBottm);
		pControl->SetPos(rcChildPos);
		cyNeeded = std::max(cyNeeded, (int64_t)rcChildPos.Height() + rcMargin.top + rcMargin.bottom);

		//������ǰY������ֵ
		iPosX += (sz.cx + rcMargin.left + GetChildMarginX() + rcMargin.right);
		cxNeeded += (sz.cx + rcMargin.left + rcMargin.right);
	}
	if (!itemsMap.empty()) {
		cxNeeded += ((int64_t)itemsMap.size() - 1) * GetChildMarginX();
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

UiSize HLayout::EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable)
{
	//��ȣ������ӿؼ����֮�ͣ�����Margin��Padding�ȣ������������͵��ӿؼ�
	//�߶ȣ�ȡ�����ӿؼ��߶ȵ����ֵ������Margin��Padding�ȣ������������͵��ӿؼ�
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
		
		if (itemSize.cy > 0) {
			totalSize.cy = std::max(itemSize.cy + rcMargin.top + rcMargin.bottom, totalSize.cy);
		}
		if (itemSize.cx > 0) {
			totalSize.cx += (itemSize.cx + rcMargin.left + rcMargin.right);
		}		
	}

	if ((totalSize.cx > 0) && ((estimateCount - 1) > 0)) {
		totalSize.cx += (estimateCount - 1) * GetChildMarginX();
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
