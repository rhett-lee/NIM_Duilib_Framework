#include "HTileLayout.h"
#include "duilib/Core/Box.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Utils/AttributeUtil.h"
#include <numeric>

namespace ui 
{
HTileLayout::HTileLayout():
	m_nRows(0), 
	m_szItem(0, 0),
	m_bAutoCalcRows(false),
	m_bScaleDown(true)
{
}

UiSize HTileLayout::CalcEstimateSize(Control* pControl, const UiSize& szItem, UiRect rc)
{
	if ((pControl == nullptr) || !pControl->IsVisible()) {
		return UiSize();
	}
	
	//����Ŀ�������ʼ��ʹ��������
	UiMargin rcMargin = pControl->GetMargin();
	int32_t width = rc.Width() - rcMargin.left - rcMargin.right;
	int32_t height = rc.Height() - rcMargin.top - rcMargin.bottom;
	UiSize szAvailable(width, height);
	szAvailable.Validate();
	UiEstSize estSize = pControl->EstimateSize(szAvailable);
	UiSize childSize(estSize.cx.GetInt32(), estSize.cy.GetInt32());
	if (estSize.cy.IsStretch()) {
		childSize.cy = szItem.cy;
	}
	if (childSize.cy < pControl->GetMinHeight()) {
		childSize.cy = pControl->GetMinHeight();
	}
	if (childSize.cy > pControl->GetMaxHeight()) {
		childSize.cy = pControl->GetMaxHeight();
	}

	if (estSize.cx.IsStretch()) {
		childSize.cx = szItem.cx;
	}
	if (childSize.cx < pControl->GetMinWidth()) {
		childSize.cx = pControl->GetMinWidth();
	}
	if (childSize.cx > pControl->GetMaxWidth()) {
		childSize.cx = pControl->GetMaxWidth();
	}
	return childSize;
}

void HTileLayout::CalcTileRows(const std::vector<ItemSizeInfo>& normalItems, const UiRect& rc,
								 int32_t tileHeight, int32_t childMarginX, int32_t childMarginY,
	                             int32_t& nRows)
{
	nRows = 0;
	if (tileHeight <= 0) {
		//��Ҫ�ȼ�����Ƭ�ؼ��߶ȣ�Ȼ����ݿ�ȼ�������
		int32_t maxHeight = 0;
		int64_t areaTotal = 0;
		const int64_t maxArea = (int64_t)rc.Width() * rc.Height();
		for (const ItemSizeInfo& itemSizeInfo : normalItems) {
			UiMargin rcMargin = itemSizeInfo.pControl->GetMargin();
			UiSize childSize(itemSizeInfo.cx, itemSizeInfo.cy);
			if (childSize.cy > 0) {
				maxHeight = std::max(maxHeight, childSize.cy + rcMargin.top + rcMargin.bottom);
			}
			int32_t childWidth = childSize.cx;
			int32_t childHeight = childSize.cy;
			if (childWidth > 0) {
				childWidth += childMarginX;
			}			
			if (childHeight > 0) {
				childHeight += childMarginY;
			}
			areaTotal += ((int64_t)childWidth * childHeight);
			if (areaTotal > maxArea) {
				//����ǰ������չʾ���������
				break;
			}
		}
		//ȡ�������ؼ��߶����ֵ����Ϊÿ��Item�ĸ߶�
		tileHeight = maxHeight;
	}
	if (tileHeight > 0) {
		//ʹ�����õĸ߶���Ϊ��Ƭ�ؼ��Ŀ�ȣ���ͨ�����õĸ߶ȣ���������
		int32_t totalHeight = rc.Height();
		while (totalHeight > 0) {
			totalHeight -= tileHeight;
			if (nRows != 0) {
				totalHeight -= childMarginX;
			}
			if (totalHeight >= 0) {
				++nRows;
			}
		}
	}
}

UiSize64 HTileLayout::EstimateFloatSize(Control* pControl, UiRect rc)
{
	ASSERT(pControl != nullptr);
	if ((pControl == nullptr) || !pControl->IsVisible()) {
		return UiSize64();
	}
	UiMargin margin = pControl->GetMargin();
	UiSize childSize = CalcEstimateSize(pControl, UiSize(0, 0), rc);
	if (childSize.cx > 0) {
		childSize.cx += (margin.left + margin.right);
	}
	if (childSize.cy > 0) {
		childSize.cy += (margin.top + margin.bottom);
	}	
	return UiSize64(childSize.cx, childSize.cy);
}

UiSize64 HTileLayout::ArrangeFloatChild(const std::vector<Control*>& items,
									   UiRect rc,
									   const UiSize& szItem,
									   bool isCalcOnly,
									   std::vector<ItemSizeInfo>& normalItems)
{
	int64_t cxNeededFloat = 0;	//�����ؼ���Ҫ���ܿ��
	int64_t cyNeededFloat = 0;	//�����ؼ���Ҫ���ܸ߶�
	for (Control* pControl : items) {
		if ((pControl == nullptr) || !pControl->IsVisible()) {
			continue;
		}
		if (pControl->IsFloat()) {
			//�����ؼ�
			UiSize64 floatSize;
			if (!isCalcOnly) {
				//���ø����ؼ���λ��
				floatSize = SetFloatPos(pControl, rc);
			}
			else {
				//����Float�ؼ��Ĵ�С
				floatSize = EstimateFloatSize(pControl, rc);
			}
			if (cxNeededFloat < floatSize.cx) {
				cxNeededFloat = floatSize.cx;
			}
			if (cyNeededFloat < floatSize.cy) {
				cyNeededFloat = floatSize.cy;
			}
		}
		else {
			//��ͨ�ؼ�
			UiSize childSize = CalcEstimateSize(pControl, szItem, rc);
			if ((childSize.cx <= 0) || (childSize.cy <= 0)) {
				//��СΪ0�ģ�������ʾ�ؼ�(����������ؼ�)
				if (!isCalcOnly) {
					UiRect rcPos(rc);
					rcPos.right = rcPos.left;
					rcPos.bottom = rcPos.top;
					pControl->SetPos(rcPos);
				}
			}
			else {
				ItemSizeInfo info;
				info.pControl = pControl;
				info.cx = childSize.cx;
				info.cy = childSize.cy;
				normalItems.push_back(info);
			}
		}
	}
	return UiSize64(cxNeededFloat, cyNeededFloat);
}

int32_t HTileLayout::CalcTileColumnWidth(const std::vector<ItemSizeInfo>& normalItems,
									     const std::vector<ItemSizeInfo>::const_iterator iterBegin,
									     int32_t nRows,
									     const UiSize& szItem)
{
	//szItem�Ŀ�Ⱥ͸߶�ֵ���ǰ����˿ؼ�����߾���ڱ߾��
	ASSERT(nRows > 0);
	int32_t cyWidth = szItem.cx;
	if (cyWidth > 0) {
		//��������˿�ȣ�������ʹ�����õĿ��ֵ
		return cyWidth;
	}
	if (nRows <= 0) {
		return 0;
	}

	int32_t iIndex = 0;
	for (auto it = iterBegin; it != normalItems.end(); ++it) {
		const ItemSizeInfo& itemSizeInfo = *it;
		UiMargin rcMargin = itemSizeInfo.pControl->GetMargin();
		UiSize szTile(itemSizeInfo.cx, itemSizeInfo.cy);

		//�����߶����ֵ
		if (szTile.cx > 0) {
			cyWidth = std::max(cyWidth, szTile.cx + rcMargin.left + rcMargin.right);
		}

		++iIndex;
		if ((iIndex % nRows) == 0) {
			//���У��˳�
			break;
		}
	}
	return cyWidth;
}

UiSize HTileLayout::CalcTilePosition(const ItemSizeInfo& itemSizeInfo,
	                                int32_t tileWidth, int32_t tileHeight,
	                                const UiPoint& ptTile, bool bScaleDown, UiRect& szTilePos)
{
	szTilePos.Clear();
	//Ŀ�������С����͸ߣ�
	UiSize szItem(tileWidth, tileHeight);
	szItem.Validate();

	//��Ƭ�ؼ���С(��͸�), ������߾�
	UiMargin rcMargin = itemSizeInfo.pControl->GetMargin();
	UiSize childSize(itemSizeInfo.cx + rcMargin.left + rcMargin.right, 
		             itemSizeInfo.cy + rcMargin.top + rcMargin.bottom);
	childSize.Validate();

	if ((szItem.cx == 0) && (childSize.cx > 0)) {
		szItem.cx = childSize.cx;
	}
	if ((childSize.cx == 0) && (szItem.cx > 0)) {
		childSize.cx = szItem.cx;
	}

	if ((szItem.cy == 0) && (childSize.cy > 0)) {
		szItem.cy = childSize.cy;
	}
	if ((childSize.cy == 0) && (szItem.cy > 0)) {
		childSize.cy = szItem.cy;
	}
	
	int32_t cxWidth = szItem.cx;	//ÿ���ؼ�����Ƭ���Ŀ�ȣ���̬����ֵ��
	int32_t cyHeight = szItem.cy;	//ÿ���ؼ�����Ƭ���ĸ߶ȣ���̬����ֵ��

	//Ŀ������أ����Ͻ����꣬��͸ߣ�
	UiRect rcTile(ptTile.x, ptTile.y, ptTile.x + cxWidth, ptTile.y + cyHeight);

	//�Կؼ����еȱ�������(���ŵ�ʱ����Ҫȥ����߾�)
	UiRect rcRealTile = rcTile;
	rcRealTile.Deflate(rcMargin);
	UiSize realSize(childSize.cx - rcMargin.left - rcMargin.right,
				    childSize.cy - rcMargin.top - rcMargin.bottom);
	if (bScaleDown && 
		(rcRealTile.Width() > 0) && (rcRealTile.Height() > 0) &&
		(realSize.cx > 0) && (realSize.cy > 0) ) {
		if ((realSize.cx > rcRealTile.Width()) || (realSize.cy > rcRealTile.Height())) {
			//�����������������еȱ�����
			UiSize oldSize = realSize;
			double cx = realSize.cx;
			double cy = realSize.cy;
			double cxRatio = cx / rcRealTile.Width();
			double cyRatio = cy / rcRealTile.Height();
			if (cxRatio > cyRatio) {
				ASSERT(realSize.cx > rcRealTile.Width());
				double ratio = cx / realSize.cy;
				realSize.cx = rcRealTile.Width();
				realSize.cy = static_cast<int32_t>(realSize.cx / ratio + 0.5);
			}
			else {
				ASSERT(realSize.cy > rcRealTile.Height());
				double ratio = cy / realSize.cx;
				realSize.cy = rcRealTile.Height();
				realSize.cx = static_cast<int32_t>(realSize.cy / ratio + 0.5);
			}
		}
	}

	//rcTile������߾࣬realSize��������߾�
	szTilePos = GetFloatPos(itemSizeInfo.pControl, rcTile, realSize);
	if (szTilePos.left < ptTile.x) {
		//����ؼ��ϴ󣬳����߽磬�������
		int32_t width = szTilePos.Width();
		szTilePos.left = ptTile.x;
		szTilePos.right = ptTile.x + width;
	}
	if (szTilePos.top < ptTile.y) {
		//����ؼ��ϴ󣬳����߽磬���϶���
		int32_t height = szTilePos.Height();
		szTilePos.top = ptTile.y;
		szTilePos.bottom = ptTile.y + height;
	}
	return UiSize(cxWidth, cyHeight);
}

UiSize64 HTileLayout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
{
	//���岼�ֲ��ԣ�
	// (1) �������������߽磨�������׵ĵ�һ��Ԫ�ش�С��rc����������º���ᳬ���߽磩��
	//     ������ܻ���ֳ����߽硣
	// (2) ��Ƭ�Ŀ�߱ȣ�Ĭ�ϱ��ֿ�߱Ƚ�����С������ӦĿ����ʾ��(����m_bScaleDown���ƴ���Ϊ)��
	//     �����Ȼ��߸߶ȳ��������ţ���Ҫ���ֿ�߱ȣ�������ֱ��Σ�
	//     �����ṩһ��ѡ��SetScaleDown()�������ֿ�߱ȣ���������£����г����߽������
	// (3) ���ڲ�������ģʽ����������m_bAutoCalcColumnsΪtrue����m_nColumns������
	//���ֵļ�������:
	// (1) !m_bAutoCalcRows && (m_nRows == 0) && (m_szItem.cx == 0)
	//     ���ֲ��ԣ�	1�����������ɲ��֣������У�ÿ����Ҫ������߽磬�ͻ��У�ÿ�е��������ܶ���ͬ����
	//				2����Ƭ�ؼ��Ŀ�ȣ�����ʵ�ʿ��չʾ��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (2) (m_nRows == 0) && (m_szItem.cx > 0)
	//     ���ֲ��ԣ�	1������������ rc.Width() �� m_szItem.cx ������Ӧ�÷ּ��У������̶���
	//				2����Ƭ�ؼ��Ŀ�ȣ��̶�Ϊ m_szItem.cx��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (3) (m_nRows > 0) && (m_szItem.cx == 0)
	//     ���ֲ��ԣ�	1�������������̶�Ϊm_nColumns��
	//				2����Ƭ�ؼ��Ŀ�ȣ�����ʵ�ʿ��չʾ��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (4) (m_nRows > 0) && (m_szItem.cx > 0)
	//     ���ֲ��ԣ�	1�������������̶�Ϊm_nColumns��
	//				2����Ƭ�ؼ��Ŀ�ȣ��̶�Ϊ m_szItem.cx��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��

	if (IsFreeLayout()) {
		//ʹ�����ɲ������пؼ�(�޹̶������������������չʾ�ռ䣬��ʾ�����ܶ������)
		return ArrangeChildFreeLayout(items, rc, false);
	}
	else {
		std::vector<int32_t> inRowHeights;
		std::vector<int32_t> outRowHeights;
		ArrangeChildNormal(items, rc, true, inRowHeights, outRowHeights);
		inRowHeights.swap(outRowHeights);
		return ArrangeChildNormal(items, rc, false, inRowHeights, outRowHeights);
	}
}

bool HTileLayout::IsFreeLayout() const
{
	return (!m_bAutoCalcRows && (m_nRows == 0) && (m_szItem.cx == 0) && m_szItem.cy == 0);
}

UiSize64 HTileLayout::ArrangeChildNormal(const std::vector<Control*>& items,
										UiRect rect,
										bool isCalcOnly,
										const std::vector<int32_t>& inRowHeights,
										std::vector<int32_t>& outRowHeights) const
{
	ASSERT(!IsFreeLayout());
	DeflatePadding(rect); //��ȥ�ڱ߾࣬ʣ�µ��ǿ�������
	const UiRect& rc = rect;

	//���������ؼ����������ؿؼ���������ʾ�ؼ���
	//�������͵��ӿؼ������(m_szItem.cx > 0) && (m_szItem.cy > 0) Ϊtrue���������ʾ������ᱻ���˵�
	std::vector<ItemSizeInfo> normalItems;
	ArrangeFloatChild(items, rc, m_szItem, isCalcOnly, normalItems); //�����ؼ���Ҫ���ܿ�Ⱥ͸߶�

	int32_t nRows = m_nRows;  //����������ֵ��
	if (m_bAutoCalcRows) {
		//����Զ����������������¼�������
		nRows = 0;
	}
	if (nRows <= 0) {
		CalcTileRows(normalItems, rc, m_szItem.cy, GetChildMarginX(), GetChildMarginY(), nRows);
	}
	if (nRows < 1) {
		//�޷���ȷ����ʱ��Ĭ��ֵ����Ϊ1
		nRows = 1;
	}

	//�п�����, �̶�ֵ
	std::vector<int32_t> fixedRowHeights = inRowHeights;
	if (m_szItem.cy > 0) {
		fixedRowHeights.clear();
		fixedRowHeights.resize(nRows, m_szItem.cy);
	}

	int32_t cxColumnWidth = 0;         //ÿ�пؼ�����Ƭ���Ŀ�ȣ���̬����ֵ��

	std::vector<int32_t> rowHeights;   //ÿ�еĸ߶�ֵ������ֵ
	std::vector<int32_t> columnWidths; //ÿ�еĿ��ֵ������ֵ
	rowHeights.resize(nRows);
	columnWidths.resize(1);

	int32_t nColumnTileCount = 0;      //�������ɵ���Ƭ�ؼ�����
	int32_t nColumnIndex = 0;          //��ǰ���к�

	int32_t yPosTop = rc.top;
	//�ؼ���ʾ���ݵ��ϲ�����ֵ(����������ж���)
	if (!isCalcOnly && !fixedRowHeights.empty()) {
		int32_t cyTotal = std::accumulate(fixedRowHeights.begin(), fixedRowHeights.end(), 0);
		if (fixedRowHeights.size() > 1) {
			cyTotal += ((int32_t)fixedRowHeights.size() - 1) * GetChildMarginX();
		}
		if (cyTotal < rc.Height()) {
			yPosTop = rc.CenterY() - cyTotal / 2;
		}
	}

	UiPoint ptTile(rc.left, yPosTop);	//ÿ���ؼ�����Ƭ���Ķ�������	
	for( auto it = normalItems.begin(); it != normalItems.end(); ++it ) {
		const ItemSizeInfo& itemSizeInfo = *it;
		Control* pControl = itemSizeInfo.pControl;
		if (nColumnTileCount == 0) {
			//һ�еĿ�ʼ��������һ�еĸ߶�
			nColumnTileCount = nRows;
			cxColumnWidth = CalcTileColumnWidth(normalItems, it, nRows, m_szItem);
			ASSERT(cxColumnWidth > 0);//����������
		}
		
		const int32_t rowIndex = nRows - nColumnTileCount;//��ǰ���±�[0, nRows)
		int32_t fixedRowHeight = 0; //��ǰ������и߿��, �̶�ֵ
		if (((int32_t)fixedRowHeights.size() == nRows) &&
			(rowIndex < fixedRowHeights.size())) {
			fixedRowHeight = fixedRowHeights[rowIndex];
		}

		//���㵱ǰ��Ƭ�ؼ���λ�����ꡢ���(cxWidth)�͸߶�(cyHeight)		
		UiRect rcTilePos;

		UiPoint posLeftTop = ptTile;         //�ÿؼ������Ͻ�����ֵ
		int32_t posWidth = cxColumnWidth;    //�ÿؼ��������ÿ��
		int32_t posHeight = fixedRowHeight;  //�ÿؼ��������ø߶�
		UiSize szTileSize = CalcTilePosition(itemSizeInfo, posWidth, posHeight,
			                                 posLeftTop, m_bScaleDown, rcTilePos);//����ֵ�����˿ؼ�����߾�
		
		if (!isCalcOnly) {
			pControl->SetPos(rcTilePos);
		}

		int32_t cyHeight = szTileSize.cy;
		if (fixedRowHeight > 0) {
			cyHeight = fixedRowHeight;
		}

		//���㱾�п�����ֵ�����ֵ��Ҫ������߾�
		int32_t tileWidth = (m_szItem.cx > 0) ? m_szItem.cx : szTileSize.cx;
		columnWidths[nColumnIndex] = std::max(tileWidth, columnWidths[nColumnIndex]);

		--nColumnTileCount;
		if(nColumnTileCount == 0 ) {
			//����
			columnWidths.push_back(0);
			nColumnIndex = (int32_t)columnWidths.size() - 1;
			
			//��������X�����Y�����λ��(����)
			ptTile.x += cxColumnWidth + GetChildMarginX();
			//Y�������л�����һ�У����и��л�
			ptTile.y = yPosTop;
		}
		else {
			//ͬһ�У������л����꣬����ǰ��Ƭ�ؼ��Ŀ���л�
			ptTile.y += cyHeight + GetChildMarginY();
		}		
		//��¼ÿ�еĸ߶ȣ�ȡ��һ���У��ؼ��߶ȵ����ֵ�������˿ؼ�����߾ࣩ
		if (rowIndex < rowHeights.size()) {
			int32_t tileHeight = (m_szItem.cy > 0) ? m_szItem.cy : cyHeight;	
			rowHeights[rowIndex] = std::max(tileHeight, rowHeights[rowIndex]);
		}
	}

	//�����ڱ߾��Ѿ������������Ⱥ͸߶ȵ�ʱ����Ҫ�����ڱ߾�
	UiPadding rcPadding;
	if (GetOwner() != nullptr) {
		rcPadding = GetOwner()->GetPadding();
	}
	//����������
	int64_t cxNeeded = std::accumulate(columnWidths.begin(), columnWidths.end(), 0);
	if (columnWidths.size() > 1) {
		cxNeeded += (columnWidths.size() - 1) * GetChildMarginX();
	}
	cxNeeded += (rcPadding.left + rcPadding.right);

	//��������߶�
	int64_t cyNeeded = std::accumulate(rowHeights.begin(), rowHeights.end(), 0);
	if (rowHeights.size() > 1) {
		cyNeeded += (rowHeights.size() - 1) * GetChildMarginY();
	}
	cyNeeded += (rcPadding.top + rcPadding.bottom);

	outRowHeights.swap(rowHeights);
	UiSize64 size(cxNeeded, cyNeeded);
	return size;
}

UiSize64 HTileLayout::ArrangeChildFreeLayout(const std::vector<Control*>& items,
											UiRect rect, bool isCalcOnly) const
{
	DeflatePadding(rect); //��ȥ�ڱ߾࣬ʣ�µ��ǿ�������
	const UiRect& rc = rect;

	//���������ؼ����������ؿؼ���������ʾ�ؼ���
	//�������͵��ӿؼ������(m_szItem.cx > 0) && (m_szItem.cy > 0) Ϊtrue���������ʾ������ᱻ���˵�
	std::vector<ItemSizeInfo> normalItems;
	ArrangeFloatChild(items, rc, m_szItem, isCalcOnly, normalItems); //�����ؼ���Ҫ���ܿ�Ⱥ͸߶�

	int64_t cxNeeded = 0;		//�Ǹ����ؼ���Ҫ���ܿ��	
	int64_t cyNeeded = 0;		//�Ǹ����ؼ���Ҫ���ܸ߶�

	int32_t cxColumnWidth = 0;   //ÿ�пؼ�����Ƭ���Ŀ�ȣ���̬����ֵ��

	const int32_t yPosTop = rc.top;         //�ؼ���ʾ���ݵ��ϲ�����ֵ��ʼ�ղ�ȡ�϶���
	UiPoint ptTile(rc.left, yPosTop); //ÿ���ؼ�����Ƭ���Ķ�������
	const size_t itemCount = normalItems.size();
	for (size_t index = 0; index < itemCount; ++index) {
		const ItemSizeInfo& itemSizeInfo = normalItems[index];
		Control* pControl = itemSizeInfo.pControl;

		//���㵱ǰ��Ƭ�ؼ���λ�����ꡢ��Ⱥ͸߶�
		UiRect rcTilePos;
		UiSize szTileSize = CalcTilePosition(itemSizeInfo, 0, 0,
											 ptTile, m_bScaleDown, rcTilePos);
		if (rcTilePos.bottom >= rc.bottom) {
			//�²��Ѿ������߽�, ������ǿ������ϲ࣬���Ȼ��У�����ʾ
			if (ptTile.y != yPosTop) {
				//�Ȼ���, Ȼ������ʾ
				ptTile.y = yPosTop;
				ptTile.x += cxColumnWidth + GetChildMarginX();//��һ��			
				cxColumnWidth = 0;

				szTileSize = CalcTilePosition(itemSizeInfo, 0, 0,
											  ptTile, m_bScaleDown, rcTilePos);				
			}
		}
		if (!isCalcOnly) {
			pControl->SetPos(rcTilePos);
		}

		UiMargin rcMargin = pControl->GetMargin();
		cxNeeded = std::max((int64_t)rcTilePos.right + rcMargin.right, cxNeeded);
		cyNeeded = std::max((int64_t)rcTilePos.bottom + rcMargin.bottom, cyNeeded);

		//���¿ؼ����ֵ���и�ֵ
		int32_t cyHeight = rcTilePos.Height() + rcMargin.top + rcMargin.bottom;
		cxColumnWidth = std::max(rcTilePos.Width() + rcMargin.left + rcMargin.right, cxColumnWidth);

		if (rcTilePos.bottom >= rc.bottom) {
			//��ǰ�ؼ��Ѿ������߽磬��Ҫ����
			ptTile.y = yPosTop;
			ptTile.x += cxColumnWidth + GetChildMarginX();//��һ��		
			cxColumnWidth = 0;
		}
		else {
			//�����У�����л�������
			ptTile.y += cyHeight + GetChildMarginY();
		}
	}

	//�����ڱ߾��Ѿ������������Ⱥ͸߶ȵ�ʱ����Ҫ�����ڱ߾�
	//(ֻ��Ҫ�����Ҳ�͵ײ����ڱ߾࣬��Ϊ�����ʱ���ǰ���.rigth��.bottom�����)
	UiPadding rcPadding;
	if (GetOwner() != nullptr) {
		rcPadding = GetOwner()->GetPadding();
	}
	cxNeeded += rcPadding.right;
	cyNeeded += rcPadding.bottom;

	if (isCalcOnly) {
		//���صĿ�ȣ���󲻳�����������Ŀռ䣬��Ϊ�˷���ֵ���Ϊ�������յĿ��ֵ
		if (cyNeeded > (rect.Height())) {
			cyNeeded = rect.Height();
		}
	}
	UiSize64 size(cxNeeded, cyNeeded);
	return size;
}

UiSize HTileLayout::EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable)
{
	szAvailable.Validate();
	UiRect rc(0, 0, szAvailable.Width(), szAvailable.Height());
	UiSize64 requiredSize;
	if (IsFreeLayout()) {
		requiredSize = ArrangeChildFreeLayout(items, rc, true);
	}
	else {
		std::vector<int32_t> inRowHeights;
		std::vector<int32_t> outRowHeights;
		requiredSize = ArrangeChildNormal(items, rc, true, inRowHeights, outRowHeights);
	}
	UiSize size(TruncateToInt32(requiredSize.cx), TruncateToInt32(requiredSize.cy));
	return size;
}

bool HTileLayout::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	bool hasAttribute = true;
	if((strName == L"item_size") || (strName == L"itemsize")){
		UiSize szItem;
		AttributeUtil::ParseSizeValue(strValue.c_str(), szItem);
		SetItemSize(szItem);
	}
	else if ((strName == L"columns") || (strName == L"rows")) {
		if (strValue == L"auto") {
			//�Զ���������
			SetAutoCalcRows(true);
		}
		else {
			SetAutoCalcRows(false);
			SetRows(_wtoi(strValue.c_str()));
		}
	}
	else if ((strName == L"scale_down") || (strName == L"scaledown")) {
		SetScaleDown(strValue == L"true");
	}
	else {
		hasAttribute = Layout::SetAttribute(strName, strValue);
	}
	return hasAttribute;
}

const UiSize& HTileLayout::GetItemSize() const
{
	return m_szItem;
}

void HTileLayout::SetItemSize(UiSize szItem, bool bNeedDpiScale)
{
	szItem.cx = std::max(szItem.cx, 0);
	szItem.cy = std::max(szItem.cy, 0);
	if (bNeedDpiScale) {
		GlobalManager::Instance().Dpi().ScaleSize(szItem);
	}

	if( (m_szItem.cx != szItem.cx) || (m_szItem.cy != szItem.cy) ) {
		m_szItem = szItem;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}		
	}
}

int32_t HTileLayout::GetRows() const
{
	return m_nRows;
}

void HTileLayout::SetRows(int32_t nRows)
{
	nRows = std::max(nRows, 0);
	if (m_nRows != nRows) {
		m_nRows = nRows;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}	
}

void HTileLayout::SetAutoCalcRows(bool bAutoCalcRows)
{
	if (m_bAutoCalcRows != bAutoCalcRows) {
		m_bAutoCalcRows = bAutoCalcRows;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}
}

bool HTileLayout::IsAutoCalcRows() const
{
	return m_bAutoCalcRows;
}

void HTileLayout::SetScaleDown(bool bScaleDown)
{
	if (m_bScaleDown != bScaleDown) {
		m_bScaleDown = bScaleDown;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}
}

bool HTileLayout::IsScaleDown() const
{
	return m_bScaleDown;
}

} // namespace ui
