
#include "duilib/Control/Slider.h"

#ifndef UI_CONTROL_COLOR_SLIDER_H_
#define UI_CONTROL_COLOR_SLIDER_H_

#pragma once

namespace ui
{
/** ��ɫ����
*/
enum class ColorMode
{
	kMode_ARGB,	//ARGB	
	kMode_HSV,	//HSV
	kMode_HSL	//HSL
};

/** ��ɫ������ʽ
*/
enum class ColorAdjustMode
{
	kMode_ARGB_A, //ARGBģʽ������A
	kMode_ARGB_R, //ARGBģʽ������R
	kMode_ARGB_G, //ARGBģʽ������G
	kMode_ARGB_B, //ARGBģʽ������B
	kMode_HSV_H,  //HSVģʽ������H
	kMode_HSV_S,  //HSVģʽ������S
	kMode_HSV_V,  //HSVģʽ������V
	kMode_HSL_H,  //HSLģʽ������H
	kMode_HSL_S,  //HSLģʽ������S
	kMode_HSL_L   //HSLģʽ������L
};

/** HSV��ɫ
*/
class ColorHSV
{
public:
	uint16_t H = 0; //��Χ: [0, 359)
	uint8_t  S = 0; //��Χ: [0, 100]
	uint8_t  V = 0; //��Χ: [0, 100]
};

/** HSL��ɫ
*/
class ColorHSL
{
public:
	uint16_t H = 0; //��Χ: [0, 359)
	uint8_t  S = 0; //��Χ: [0, 100]
	uint8_t  L = 0; //��Χ: [0, 100]
};

/** �Զ�����ɫ������Slider�ؼ�
*/
class ColorSlider: public Slider
{
public:
	ColorSlider();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

	/** ������ɫ��Ϣ(ARGB��ʽ����ɫ)
	*/
	void SetColorInfo(const UiColor& color, ColorAdjustMode adjustMode);

	/** ������ɫ��Ϣ(HSV��ʽ����ɫ)
	*/
	void SetColorInfo(const ColorHSV& color, ColorAdjustMode adjustMode);

	/** ������ɫ��Ϣ(HSL��ʽ����ɫ)
	*/
	void SetColorInfo(const ColorHSL& color, ColorAdjustMode adjustMode);

	/** ���Ʊ���ͼƬ����ں���
	* @param[in] pRender ָ����������
	*/
	virtual void PaintBkImage(IRender* pRender) override;

private:

	/** ��ȡ���Ƶ���ɫλͼ�ӿ�
	* @param [in] rect ��ʾ�����С��Ϣ
	*/
	IBitmap* GetColorBitmap(const UiRect& rect);

	/** ��ȡARGB��ʽ�Ľ�����ɫ
	*/
	void GetARGB(uint32_t* buffer, int32_t samples,
				 const UiColor& start,
				 const UiColor& end) const;

private:
	/** ��ɫλͼ
	*/
	std::unique_ptr<IBitmap> m_spBitmap;

	/** ��ɫģʽ
	*/
	ColorMode m_colorMode;

	/** ARGB��ɫֵ
	*/
	UiColor m_argbColor;

	/** HSV��ɫֵ
	*/
	ColorHSV m_hsvColor;

	/** HSL��ɫֵ
	*/
	ColorHSL m_hslColor;

	/** ��ɫ����ģʽ
	*/
	ColorAdjustMode m_adjustMode;
};

}//namespace ui

#endif //UI_CONTROL_COLOR_SLIDER_H_
