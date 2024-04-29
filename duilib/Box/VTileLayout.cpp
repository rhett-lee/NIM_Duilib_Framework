#include "VTileLayout.h"
#include "duilib/Core/Box.h"
#include "duilib/Utils/AttributeUtil.h"
#include "duilib/Core/GlobalManager.h"
#include <numeric>

namespace ui 
{
VTileLayout::VTileLayout(): 
	m_nColumns(0), 
	m_szItem(0, 0),
	m_bAutoCalcColumns(false),
	m_bScaleDown(true)
{
}

UiSize VTileLayout::CalcEstimateSize(Control* pControl, const UiSize& szItem, UiRect rc)
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

void VTileLayout::CalcTileColumns(const std::vector<ItemSizeInfo>& normalItems, const UiRect& rc,
								 int32_t tileWidth, int32_t childMarginX, int32_t childMarginY,
	                             int32_t& nColumns)
{
	nColumns = 0;
	if (tileWidth <= 0) {
		//��Ҫ�ȼ�����Ƭ�ؼ���ȣ�Ȼ����ݿ�ȼ�������
		int32_t maxWidth = 0;
		int64_t areaTotal = 0;
		const int64_t maxArea = (int64_t)rc.Width() * rc.Height();
		for (const ItemSizeInfo& itemSizeInfo : normalItems) {
			UiMargin rcMargin = itemSizeInfo.pControl->GetMargin();
			UiSize childSize(itemSizeInfo.cx, itemSizeInfo.cy);
			if (childSize.cx > 0) {
				maxWidth = std::max(maxWidth, childSize.cx + rcMargin.left + rcMargin.right);
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
		//ȡ�������ؼ�������ֵ����Ϊÿ��Item�Ŀ��
		tileWidth = maxWidth;
	}
	if (tileWidth > 0) {
		//ʹ�����õĿ����Ϊ��Ƭ�ؼ��Ŀ�ȣ���ͨ�����õĿ�ȣ���������
		int32_t totalWidth = rc.Width();
		while (totalWidth > 0) {
			totalWidth -= tileWidth;
			if (nColumns != 0) {
				totalWidth -= childMarginX;
			}
			if (totalWidth >= 0) {
				++nColumns;
			}
		}
	}
}

UiSize64 VTileLayout::EstimateFloatSize(Control* pControl, UiRect rc)
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

UiSize64 VTileLayout::ArrangeFloatChild(const std::vector<Control*>& items,
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

int32_t VTileLayout::CalcTileRowHeight(const std::vector<ItemSizeInfo>& normalItems,
									  const std::vector<ItemSizeInfo>::const_iterator iterBegin,
									  int32_t nColumns,
									  const UiSize& szItem)
{
	//szItem�Ŀ�Ⱥ͸߶�ֵ���ǰ����˿ؼ�����߾���ڱ߾��
	ASSERT(nColumns > 0);
	int32_t cyHeight = szItem.cy;
	if (cyHeight > 0) {
		//��������˸߶ȣ�������ʹ�����õĸ߶�ֵ
		return cyHeight;
	}
	if (nColumns <= 0) {
		return 0;
	}

	int32_t iIndex = 0;
	for (auto it = iterBegin; it != normalItems.end(); ++it) {
		const ItemSizeInfo& itemSizeInfo = *it;
		UiMargin rcMargin = itemSizeInfo.pControl->GetMargin();
		UiSize szTile(itemSizeInfo.cx, itemSizeInfo.cy);

		//�����߶����ֵ
		if (szTile.cy > 0) {
			cyHeight = std::max(cyHeight, szTile.cy + rcMargin.top + rcMargin.bottom);
		}

		++iIndex;
		if ((iIndex % nColumns) == 0) {
			//���У��˳�
			break;
		}
	}
	return cyHeight;
}

UiSize VTileLayout::CalcTilePosition(const ItemSizeInfo& itemSizeInfo,
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

UiSize64 VTileLayout::ArrangeChild(const std::vector<Control*>& items, UiRect rc)
{
	//���岼�ֲ��ԣ�
	// (1) �������������߽磨�������׵ĵ�һ��Ԫ�ش�С��rc����������º���ᳬ���߽磩��
	//     ������ܻ���ֳ����߽硣
	// (2) ��Ƭ�Ŀ�߱ȣ�Ĭ�ϱ��ֿ�߱Ƚ�����С������ӦĿ����ʾ��(����m_bScaleDown���ƴ���Ϊ)��
	//     �����Ȼ��߸߶ȳ��������ţ���Ҫ���ֿ�߱ȣ�������ֱ��Σ�
	//     �����ṩһ��ѡ��SetScaleDown()�������ֿ�߱ȣ���������£����г����߽������
	// (3) ���ڲ�������ģʽ����������m_bAutoCalcColumnsΪtrue����m_nColumns������
	//���ֵļ�������:
	// (1) !m_bAutoCalcColumns && (m_nColumns == 0) && (m_szItem.cx == 0)
	//     ���ֲ��ԣ�	1�����������ɲ��֣������У�ÿ����Ҫ������߽磬�ͻ��У�ÿ�е��������ܶ���ͬ����
	//				2����Ƭ�ؼ��Ŀ�ȣ�����ʵ�ʿ��չʾ��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (2) (m_nColumns == 0) && (m_szItem.cx > 0)
	//     ���ֲ��ԣ�	1������������ rc.Width() �� m_szItem.cx ������Ӧ�÷ּ��У������̶���
	//				2����Ƭ�ؼ��Ŀ�ȣ��̶�Ϊ m_szItem.cx��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (3) (m_nColumns > 0) && (m_szItem.cx == 0)
	//     ���ֲ��ԣ�	1�������������̶�Ϊm_nColumns��
	//				2����Ƭ�ؼ��Ŀ�ȣ�����ʵ�ʿ��չʾ��
	//              3����Ƭ�ؼ��ĸ߶ȣ�
	//                ��1�����m_szItem.cy > 0������Ϊ�̶�m_szItem.cy
	//                ��2�����m_szItem.cy == 0: ����ʵ�ʸ߶�չʾ��
	// (4) (m_nColumns > 0) && (m_szItem.cx > 0)
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
		std::vector<int32_t> inColumnWidths;
		std::vector<int32_t> outColumnWidths;
		ArrangeChildNormal(items, rc, true, inColumnWidths, outColumnWidths);
		inColumnWidths.swap(outColumnWidths);
		return ArrangeChildNormal(items, rc, false, inColumnWidths, outColumnWidths);
	}
}

bool VTileLayout::IsFreeLayout() const
{
	return (!m_bAutoCalcColumns && (m_nColumns == 0) && (m_szItem.cx == 0) && m_szItem.cy == 0);
}

UiSize64 VTileLayout::ArrangeChildNormal(const std::vector<Control*>& items,
										UiRect rect,
										bool isCalcOnly,
										const std::vector<int32_t>& inColumnWidths,
										std::vector<int32_t>& outColumnWidths) const
{
	ASSERT(!IsFreeLayout());
	DeflatePadding(rect); //��ȥ�ڱ߾࣬ʣ�µ��ǿ�������
	const UiRect& rc = rect;

	//���������ؼ����������ؿؼ���������ʾ�ؼ���
	//�������͵��ӿؼ������(m_szItem.cx > 0) && (m_szItem.cy > 0) Ϊtrue���������ʾ������ᱻ���˵�
	std::vector<ItemSizeInfo> normalItems;
	ArrangeFloatChild(items, rc, m_szItem, isCalcOnly, normalItems); //�����ؼ���Ҫ���ܿ�Ⱥ͸߶�

	int32_t nColumns = m_nColumns;  //����������ֵ��
	if (m_bAutoCalcColumns) {
		//����Զ����������������¼�������
		nColumns = 0;
	}
	if (nColumns <= 0) {
		CalcTileColumns(normalItems, rc, m_szItem.cx, GetChildMarginX(), GetChildMarginY(), nColumns);
	}
	if (nColumns < 1) {
		//�޷���ȷ����ʱ��Ĭ��ֵ����Ϊ1
		nColumns = 1;
	}

	//�п�����, �̶�ֵ
	std::vector<int32_t> fixedColumnWidths = inColumnWidths;
	if (m_szItem.cx > 0) {
		fixedColumnWidths.clear();
		fixedColumnWidths.resize(nColumns, m_szItem.cx);
	}

	int32_t cyRowHeight = 0;   //ÿ�пؼ�����Ƭ���ĸ߶ȣ���̬����ֵ��

	std::vector<int32_t> rowHeights;   //ÿ�еĸ߶�ֵ������ֵ
	std::vector<int32_t> columnWidths; //ÿ�еĿ��ֵ������ֵ
	columnWidths.resize(nColumns);
	rowHeights.resize(1);

	int32_t nRowTileCount = 0;  //�������ɵ���Ƭ�ؼ�����
	int32_t nRowIndex = 0;      //��ǰ���к�

	int32_t xPosLeft = rc.left; 
	//�ؼ���ʾ���ݵ��������ֵ(����������ж���)
	if (!isCalcOnly && !fixedColumnWidths.empty()) {
		int32_t cxTotal = std::accumulate(fixedColumnWidths.begin(), fixedColumnWidths.end(), 0);
		if (fixedColumnWidths.size() > 1) {
			cxTotal += ((int32_t)fixedColumnWidths.size() - 1) * GetChildMarginX();
		}
		if (cxTotal < rc.Width()) {
			xPosLeft = rc.CenterX() - cxTotal / 2;
		}
	}

	UiPoint ptTile(xPosLeft, rc.top);	//ÿ���ؼ�����Ƭ���Ķ�������	
	for( auto it = normalItems.begin(); it != normalItems.end(); ++it ) {
		const ItemSizeInfo& itemSizeInfo = *it;
		Control* pControl = itemSizeInfo.pControl;
		if (nRowTileCount == 0) {
			//һ�еĿ�ʼ��������һ�еĸ߶�
			nRowTileCount = nColumns;
			cyRowHeight = CalcTileRowHeight(normalItems, it, nColumns, m_szItem);
			ASSERT(cyRowHeight > 0);//����������
		}
		
		const int32_t colIndex = nColumns - nRowTileCount;//��ǰ���±�[0, nColumns)
		int32_t fixedColumnWidth = 0; //��ǰ������п��, �̶�ֵ
		if (((int32_t)fixedColumnWidths.size() == nColumns) &&
			(colIndex < fixedColumnWidths.size())) {
			fixedColumnWidth = fixedColumnWidths[colIndex];
		}

		//���㵱ǰ��Ƭ�ؼ���λ�����ꡢ���(cxWidth)�͸߶�(cyHeight)		
		UiRect rcTilePos;

		UiPoint posLeftTop = ptTile;         //�ÿؼ������Ͻ�����ֵ
		int32_t posWidth = fixedColumnWidth; //�ÿؼ��������ÿ��
		int32_t posHeight = cyRowHeight;     //�ÿؼ��������ø߶�
		UiSize szTileSize = CalcTilePosition(itemSizeInfo, posWidth, posHeight,
			                                 posLeftTop, m_bScaleDown, rcTilePos);//����ֵ�����˿ؼ�����߾�
		
		if (!isCalcOnly) {
			pControl->SetPos(rcTilePos);
		}

		int32_t cxWidth = szTileSize.cx;
		if (fixedColumnWidth > 0) {
			cxWidth = fixedColumnWidth;
		}

		//���㱾�и߶����ֵ���߶�ֵ��Ҫ������߾�
		int32_t tileHeight = (m_szItem.cy > 0) ? m_szItem.cy : szTileSize.cy;
		rowHeights[nRowIndex] = std::max(tileHeight, rowHeights[nRowIndex]);

		--nRowTileCount;
		if(nRowTileCount == 0 ) {
			//����
			rowHeights.push_back(0);
			nRowIndex = (int32_t)rowHeights.size() - 1;			
			
			//��������X�����Y�����λ��(����)
			ptTile.x = xPosLeft;
			//Y�������л�����һ�У����и��л�
			ptTile.y += cyRowHeight + GetChildMarginY();
		}
		else {
			//ͬһ�У������л����꣬����ǰ��Ƭ�ؼ��Ŀ���л�
			ptTile.x += cxWidth + GetChildMarginX();
		}		
		//��¼ÿ�еĿ�ȣ�ȡ��һ���У��ؼ���ȵ����ֵ�������˿ؼ�����߾ࣩ
		if (colIndex < columnWidths.size()) {
			int32_t tileWidth = (m_szItem.cx > 0) ? m_szItem.cx : cxWidth;	
			columnWidths[colIndex] = std::max(tileWidth, columnWidths[colIndex]);
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

	outColumnWidths.swap(columnWidths);
	UiSize64 size(cxNeeded, cyNeeded);
	return size;
}

UiSize64 VTileLayout::ArrangeChildFreeLayout(const std::vector<Control*>& items, 
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

	int32_t cyRowHeight = 0;    //ÿ�пؼ�����Ƭ���ĸ߶ȣ���̬����ֵ��

	const int32_t xPosLeft = rc.left;         //�ؼ���ʾ���ݵ��������ֵ��ʼ�ղ�ȡ�����
	UiPoint ptTile(xPosLeft, rc.top);	//ÿ���ؼ�����Ƭ���Ķ�������
	const size_t itemCount = normalItems.size();
	for (size_t index = 0; index < itemCount; ++index) {
		const ItemSizeInfo& itemSizeInfo = normalItems[index];
		Control* pControl = itemSizeInfo.pControl;

		//���㵱ǰ��Ƭ�ؼ���λ�����ꡢ��Ⱥ͸߶�
		UiRect rcTilePos;
		UiSize szTileSize = CalcTilePosition(itemSizeInfo, 0, 0,
											 ptTile, m_bScaleDown, rcTilePos);
		if (rcTilePos.right >= rc.right) {
			//�Ҳ��Ѿ������߽�, ������ǿ�������࣬���Ȼ��У�����ʾ
			if (ptTile.x != xPosLeft) {
				//�Ȼ���, Ȼ������ʾ
				ptTile.x = xPosLeft;
				ptTile.y += cyRowHeight + GetChildMarginY();//��һ��
				cyRowHeight = 0;

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
		int32_t cxWidth = rcTilePos.Width() + rcMargin.left + rcMargin.right;
		cyRowHeight = std::max(rcTilePos.Height() + rcMargin.top + rcMargin.bottom, cyRowHeight);

		if (rcTilePos.right >= rc.right) {
			//��ǰ�ؼ��Ѿ������߽磬��Ҫ����
			ptTile.x = xPosLeft;
			ptTile.y += cyRowHeight + GetChildMarginY();//��һ��
			cyRowHeight = 0;
		}
		else {
			//�����У�����л�������
			ptTile.x += cxWidth + GetChildMarginX();
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
		if (cxNeeded > (rect.Width())) {
			cxNeeded = rect.Width();
		}
	}
	UiSize64 size(cxNeeded, cyNeeded);
	return size;
}

UiSize VTileLayout::EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable)
{
	szAvailable.Validate();
	UiRect rc(0, 0, szAvailable.Width(), szAvailable.Height());
	UiSize64 requiredSize;
	if (IsFreeLayout()) {
		requiredSize = ArrangeChildFreeLayout(items, rc, true);
	}
	else {
		std::vector<int32_t> inColumnWidths;
		std::vector<int32_t> outColumnWidths;
		requiredSize = ArrangeChildNormal(items, rc, true, inColumnWidths, outColumnWidths);
	}
	UiSize size(TruncateToInt32(requiredSize.cx), TruncateToInt32(requiredSize.cy));
	return size;
}

bool VTileLayout::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	bool hasAttribute = true;
	if((strName == L"item_size") || (strName == L"itemsize")){
		UiSize szItem;
		AttributeUtil::ParseSizeValue(strValue.c_str(), szItem);
		SetItemSize(szItem);
	}
	else if( (strName == L"columns") || (strName == L"rows")) {
		if (strValue == L"auto") {
			//�Զ���������
			SetAutoCalcColumns(true);
		}
		else {
			SetAutoCalcColumns(false);
			SetColumns(_wtoi(strValue.c_str()));
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

const UiSize& VTileLayout::GetItemSize() const
{
	return m_szItem;
}

void VTileLayout::SetItemSize(UiSize szItem, bool bNeedDpiScale)
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

int32_t VTileLayout::GetColumns() const
{
	return m_nColumns;
}

void VTileLayout::SetColumns(int32_t nCols)
{
	nCols = std::max(nCols, 0);
	if (m_nColumns != nCols) {
		m_nColumns = nCols;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}	
}

void VTileLayout::SetAutoCalcColumns(bool bAutoCalcColumns)
{
	if (m_bAutoCalcColumns != bAutoCalcColumns) {
		m_bAutoCalcColumns = bAutoCalcColumns;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}
}

bool VTileLayout::IsAutoCalcColumns() const
{
	return m_bAutoCalcColumns;
}

void VTileLayout::SetScaleDown(bool bScaleDown)
{
	if (m_bScaleDown != bScaleDown) {
		m_bScaleDown = bScaleDown;
		if (GetOwner() != nullptr) {
			GetOwner()->Arrange();
		}
	}
}

bool VTileLayout::IsScaleDown() const
{
	return m_bScaleDown;
}

} // namespace ui
