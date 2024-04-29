#ifndef UI_BOX_VTILE_LAYOUT_H_
#define UI_BOX_VTILE_LAYOUT_H_

#pragma once

#include "duilib/Box/Layout.h"

namespace ui 
{

/** ��Ƭ����
*/
class UILIB_API VTileLayout : public Layout
{
public:
	VTileLayout();

	/** ��������
	*/
	virtual LayoutType GetLayoutType() const override { return LayoutType::VTileLayout; }

	/** �����ڲ����пؼ���λ����Ϣ
	 * @param[in] items �ؼ��б�
	 * @param[in] rc ��ǰ����λ����Ϣ, �����ڱ߾࣬����������߾�
	 * @return �������к����պ��ӵĿ�Ⱥ͸߶���Ϣ
	 */
	virtual UiSize64 ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;

	/** �����ڲ��ӿؼ���С�������������С���������͵��ӿؼ������ԣ��������С����
	 * @param[in] items �ӿؼ��б�
	 * @param [in] szAvailable ���ô�С������������ÿؼ����ڱ߾࣬��������������ؼ�����߾�
	 * @return �������к����ղ��ֵĴ�С��Ϣ����Ⱥ͸߶ȣ���
			   ����items���ӿؼ�����߾࣬����items���ӿؼ����ڱ߾ࣻ
			   ����Box�ؼ�������ڱ߾ࣻ
			   ������Box�ؼ��������߾ࣻ
			   ����ֵ�в������������͵��ӿؼ���С��
	 */
	virtual UiSize EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable);
	
	/** ���ò�������
	 * @param[in] strName Ҫ���õ�������
	 * @param[in] strValue Ҫ���õ�����ֵ
	 * @return true ���óɹ���false ���Բ�����
	 */
	virtual bool SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
	/** ��ȡ�����С���ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
	 */
	const UiSize& GetItemSize() const;

	/** ���������С
	 * @param[in] szItem �����С���ݣ��ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
	 */
	void SetItemSize(UiSize szItem, bool bNeedDpiScale = true);

	/** ��ȡ������
	 */
	int32_t GetColumns() const;

	/** ������ʾ��������
	 * @param[in] nCols Ҫ������ʾ���е���ֵ
	 */
	void SetColumns(int32_t nCols);

	/** �����Ƿ��Զ���������
	 */
	void SetAutoCalcColumns(bool bAutoCalcColumns);

	/** �ж��Ƿ��Զ���������
	 */
	bool IsAutoCalcColumns() const;

	/** ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������
	*/
	void SetScaleDown(bool bScaleDown);

	/** �жϳ����߽��ʱ���Ƿ񰴱�����С
	*/
	bool IsScaleDown() const;

	/** ��ǰ�Ƿ�Ϊ���ɲ���
	*/
	bool IsFreeLayout() const;

private:
	/** δ������ӿؼ��ӿں�������Ϣ
	*/
	struct ItemSizeInfo
	{
		Control* pControl = nullptr; //�ӿؼ��ӿ�
		int32_t cx = 0;				 //�ӿؼ��Ŀ��
		int32_t cy = 0;			     //�ӿؼ��ĸ߶�
	};

	/** ��ȡ�����Сʱ�Ŀ��ÿ��
	* @param [in] pControl �ռ�ӿ�
	* @param [in] szItem ÿ����Ƭ�ؼ��Ŀ�Ⱥ͸߶�(����ֵ)
	* @param [in] rc ��Ƭ�ؼ����������Ŀ����������
	* @return ���ظÿռ�Ĺ����С����͸ߣ�
	*/
	static UiSize CalcEstimateSize(Control* pControl, const UiSize& szItem, UiRect rc);

	/** ��ȡ������������Ƭ������
	* @param [in] normalItems �ӿؼ��б�
	* @param [in] rc ��Ƭ�ؼ����������ľ���
	* @param [in] tileWidth ÿ����Ƭ�ؼ��Ŀ��(����ֵ)
	* @param [in] childMarginX �ӿؼ���X����
	* @param [in] childMarginY �ӿؼ���Y����	
	* @param [out] nColumns ����������
	*/
	static void CalcTileColumns(const std::vector<ItemSizeInfo>& normalItems, const UiRect& rc,
		                        int32_t tileWidth, int32_t childMarginX, int32_t childMarginY,
		                        int32_t& nColumns);

	/** ���㸡���ؼ��Ĵ�С
	*/
	static UiSize64 EstimateFloatSize(Control* pControl, UiRect rc);

	/** �������ӿؼ���������δ������ӿؼ��б�
	* @param [in] items �ӿؼ��б�
	* @param [in] rect �ⲿ���þ��δ�С
	* @param [in] szItem ÿ����Ƭ�ؼ��Ŀ�Ⱥ͸߶�(����ֵ)
	* @param [in] isCalcOnly ���Ϊtrue��ʾ���������򣬶Կؼ�λ�ò������������Ϊfalse����ʾ�Կؼ�λ����������
	* @param [out] normalItems ����δ������ӿؼ��б������С��Ϣ
	* @return ���ظ����ؼ���ռ�������Ⱥ͸߶�
	*/
	static UiSize64 ArrangeFloatChild(const std::vector<Control*>& items,
							          UiRect rc,
		                              const UiSize& szItem,
		                              bool isCalcOnly, 
		                              std::vector<ItemSizeInfo>& normalItems);

	/** ��ȡ������������Ƭ�߶ȣ��������й����У���ÿ�п�ʼʱ�����㱾�еĸ߶�
	* @param [in] normalItems �ӿؼ��б�
	* @param [in] iterBegin �ӿؼ���ʼ�ĵ�����
	* @param [in] nColumns ������
	* @param [in] szItem ��Ƭ�ؼ���Ⱥ͸߶ȣ�����ֵ��
	* @return ���ظ߶�ֵ����������߾�Margin.top + Margin.bottomֵ
	*/
	static int32_t CalcTileRowHeight(const std::vector<ItemSizeInfo>& normalItems,
									 const std::vector<ItemSizeInfo>::const_iterator iterBegin,
								 	 int32_t nColumns,
								     const UiSize& szItem);

	/** ������Ƭ�ؼ�����ʾ����ʹ�С
	* @param [in] itemSizeInfo ��Ƭ�ؼ��Ľӿ�, ���ؼ��Ĵ�С��Ϣ
	* @param [in] tileWidth ���õ���Ƭ�ؼ����
	* @param [in] tileHeight ���õ���Ƭ�ؼ��߶ȣ�ȡ�иߣ�
	* @param [in] ptTile ��ǰ��Ƭ�ؼ����Ͻǵ�����
	* @param [in] bScaleDown ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������
	* @param [out] szTilePos ��Ƭ�ؼ�����ʾ���ꡢ��Ⱥ͸߶�
	* @return ������Ƭ�ؼ�Ŀ������Ĵ�С����͸ߣ�����Ⱥ͸߶Ȱ����˿ؼ�����߾�
	*/
	static UiSize CalcTilePosition(const ItemSizeInfo& itemSizeInfo,
								   int32_t tileWidth,
								   int32_t tileHeight,
								   const UiPoint& ptTile,
		                           bool bScaleDown, 
								   UiRect& szTilePos);

private:
	/** ���ӿؼ����ֵ��ڲ�ʵ�ֺ���
	* @param [in] items �ӿؼ��б�
	* @param [in] rect ���þ��δ�С������������ÿؼ����ڱ߾࣬��������������ؼ�����߾�
	* @param [in] isCalcOnly ���Ϊtrue��ʾ���������򣬶Կؼ�λ�ò������������Ϊfalse����ʾ�Կؼ�λ����������
	* @param [in] inColumnWidths ÿ�еĿ��ֵ������Ϊ��
	* @param [out] outColumnWidths ���β��֣�ʹ�õ�ÿ�п��ֵ
	* @return ��������Ŀ�Ⱥ͸߶�
	*/
	UiSize64 ArrangeChildNormal(const std::vector<Control*>& items, 
								UiRect rect,
							    bool isCalcOnly,
		                        const std::vector<int32_t>& inColumnWidths,
		                        std::vector<int32_t>& outColumnWidths) const;

	/** ʹ�����ɲ������пؼ�(�޹̶������������������չʾ�ռ䣬��ʾ�����ܶ������)
	* @param [in] items �ӿؼ��б�
	* @param [in] rect ���þ��δ�С������������ÿؼ����ڱ߾࣬��������������ؼ�����߾�
	* @param [in] isCalcOnly ���Ϊtrue��ʾ���������򣬶Կؼ�λ�ò������������Ϊfalse����ʾ�Կؼ�λ����������
	* @return ��������Ŀ�Ⱥ͸߶�
	*/
	UiSize64 ArrangeChildFreeLayout(const std::vector<Control*>& items, 
									UiRect rect, 
									bool isCalcOnly) const;

private:

	//��ʾ��������
	int32_t m_nColumns;

	//�����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
	UiSize m_szItem;

	//�Զ���������
	bool m_bAutoCalcColumns;

	//���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������
	bool m_bScaleDown;
};

} // namespace ui

#endif // UI_BOX_VTILE_LAYOUT_H_
