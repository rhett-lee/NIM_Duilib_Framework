#ifndef UI_CONTROL_COLORPICKER_STANDARD_GRAY_H_
#define UI_CONTROL_COLORPICKER_STANDARD_GRAY_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Render/IRender.h"

namespace ui
{
/** ��ɫѡ��������׼��ɫ����ɫ
*/
class ColorPickerStatardGray : public Control
{
public:
	ColorPickerStatardGray();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

	/** ѡ��һ����ɫ
	*/
	void SelectColor(const UiColor& color);

	/**
	* @brief ���ƿؼ�����ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void Paint(IRender* pRender, const UiRect& rcPaint);

	/** ����ؼ���С(��͸�)
		���������ͼƬ������ width �� height ����һ��Ϊ auto��������ͼƬ��С���ı���С���������մ�С
	 *  @param [in] szAvailable ���ô�С����������߾�
	 *  @return �ؼ��Ĺ����С�������ڱ߾�(Box)����������߾�
	 */
	virtual UiEstSize EstimateSize(UiSize szAvailable) override;

	/** ��һ�������ڻ�����������ƴ�ӵ���ɫ��ͼ, ����������������
	*/
	void DrawColorMap(IRender* pRender, const UiRect& rect);

	/** ����һ����������(���ö���ζ���ķ�ʽ����·�����)
	* @param [in] pRender ��Ⱦ�ӿ�
	* @param [in] centerPt �������ε����ĵ�����
	* @param [in] radius �������εİ뾶�����ĵ���붥��ľ��루ͬʱҲ�Ǳ߳���
	* @param [in] penColor ���ʵ���ɫ�����Ϊ0���򲻻��Ʊ߿�
	* @param [in] penWidth ���ʵĿ�ȣ����Ϊ0���򲻻��Ʊ߿�
	* @param [in] brushColor ��ˢ����ɫ�����Ϊ0���������ɫ
	*/
	bool DrawRegularHexagon(IRender* pRender, const UiPointF& centerPt, int32_t radius,
		                    const UiColor& penColor, int32_t penWidth, const UiColor& brushColor);

	/** ����ƶ�
	*/
	virtual bool MouseMove(const EventArgs& msg) override;

	/** ����������
	*/
	virtual bool ButtonDown(const EventArgs& msg) override;

	/** ��ȡ��ǰ������ڵ����ɫ��Ϣ
	*/
	bool GetColorInfo(const UiPoint& ptMouse, UiColor& ptColor) const;

	/** ��������֮��ľ���
	*/
	float GetPointsDistance(const UiPointF& pt1, const UiPointF& pt2) const;

	/** ��ʼ����ɫ��
	*/
	void InitColorMap();

	/** ����ѡ����ɫ���¼�
	* @param[in] callback ѡ����ɫ�仯ʱ�Ļص�����
	*            ����˵��:
						wParam: ��ǰ��ѡ�����ɫֵ��������UiColor((uint32_t)wParam)������ɫ
						lParam: ԭ����ѡ�����ɫֵ��������UiColor((uint32_t)lParam)������ɫ
	*/
	void AttachSelectColor(const EventCallback& callback) { AttachEvent(kEventSelectColor, callback); }

private:
	/** ��ɫ��
	*/
	struct ColorInfo
	{
		//��ɫֵ
		UiColor color;

		//����ɫ�������������ĵ�����
		UiPointF centerPt;

		/** �������εİ뾶
		*/
		int32_t m_radius;
	};
	std::vector<ColorInfo> m_colorMap;

	/** ��ǰѡ����������ɫ
	*/
	UiColor m_selectedColor;
};

}//namespace ui

#endif //UI_CONTROL_COLORPICKER_STANDARD_GRAY_H_

