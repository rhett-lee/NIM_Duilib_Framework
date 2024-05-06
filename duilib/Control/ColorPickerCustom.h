#ifndef UI_CONTROL_COLORPICKER_CUSTOM_H_
#define UI_CONTROL_COLORPICKER_CUSTOM_H_

#pragma once

#include "duilib/Core/Box.h"
#include "duilib/Control/ColorControl.h"
#include "duilib/Control/ColorSlider.h"
#include "duilib/Control/RichEdit.h"

namespace ui
{
/** ��ɫѡ�������Զ�����ɫ
*/
class ColorPickerRegular;
class ColorPickerCustom : public Box
{
public:
	ColorPickerCustom();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

	/** ѡ��һ����ɫ
	*/
	void SelectColor(const UiColor& color);

	/** ���ÿؼ�λ��
	*/
	virtual void SetPos(UiRect rc) override;

	/** ����ѡ����ɫ���¼�
	* @param[in] callback ѡ����ɫ�仯ʱ�Ļص�����
	*            ����˵��:
						wParam: ��ǰ��ѡ�����ɫֵ��������UiColor((uint32_t)wParam)������ɫ
						lParam: ԭ����ѡ�����ɫֵ��������UiColor((uint32_t)lParam)������ɫ
	*/
	void AttachSelectColor(const EventCallback& callback) { AttachEvent(kEventSelectColor, callback); }

private:
	/** ��ɫ�仯��ԭ��
	*/
	enum class ChangeReason
	{
		ColorUpdate,	//��ɫֵ������ҳ�����
		ColorSpectrum,	//��ɫ����ͼ
		ColorRegular,	//��׼��ɫ��
		NewColorEdit,	//����ɫ�Ŀɱ༭��

		ColorARGB_A,	//ARGB��ɫ�仯
		ColorARGB_R,	//ARGB��ɫ�仯
		ColorARGB_G,	//ARGB��ɫ�仯
		ColorARGB_B,	//ARGB��ɫ�仯

		ColorHSV_H,		//HSV��ɫ�仯
		ColorHSV_S,		//HSV��ɫ�仯
		ColorHSV_V,		//HSV��ɫ�仯

		ColorHSL_H,		//HSL��ɫ�仯
		ColorHSL_S,		//HSL��ɫ�仯
		ColorHSL_L,		//HSL��ɫ�仯
	};

	/** ��ʼ��
	*/
	void InitPicker();

	/** ��ɫ�����仯
	*/
	void OnColorChanged(WPARAM wParam, LPARAM lParam, ChangeReason reason);

	/** �ж������Ƿ�Ϊ�Ϸ�����ɫ�ַ�������ʽ��"#FF123456"
	*/
	bool IsValidColorString(const std::wstring& colorText) const;

private:
	/** һ����ɫͨ���Ľ���ؼ�
	*/
	struct ColorUI
	{
		//��ɫֵ��ʾ�ؼ�
		RichEdit* m_pColorEdit = nullptr;

		//��ɫֵ�����ؼ�
		ColorSlider* m_pColorSlider = nullptr;
	};

	/** ��ʼ��һ��RGBͨ��
	*/
	void InitRGB(const ColorUI& colorUI, ChangeReason reason);

	/** ��ʼ��һ��HSVͨ��
	*/
	void InitHSV(const ColorUI& colorUI, int32_t maxValue, ChangeReason reason);

	/** ��ʼ��һ��HSLͨ��
	*/
	void InitHSL(const ColorUI& colorUI, int32_t maxValue, ChangeReason reason);

	/** ����RGB
	* @param [in] flag: 0 - A, 1 - R, 2 - G, 3 - B
	*/
	void UpdateRGB(const ColorUI& colorUI, const UiColor& color, int32_t flag);

	/** ����HSV
	*/
	void UpdateHSV(const ColorUI& colorUIH, const ColorUI& colorUIS, const ColorUI& colorUIV, const UiColor& color, ChangeReason reason);

	/** ����HSL
	*/
	void UpdateHSL(const ColorUI& colorUIH, const ColorUI& colorUIS, const ColorUI& colorUIL, const UiColor& color, ChangeReason reason);

	/** RGB��ɫ�����仯
	*/
	void OnRGBChanged(ChangeReason reason);

	/** HSV��ɫ�����仯
	*/
	void OnHSVChanged(ChangeReason reason);

	/** HSL��ɫ�����仯
	*/
	void OnHSLChanged(ChangeReason reason);

private:
	/** �Ƿ��Ѿ���ɳ�ʼ��
	*/
	bool m_bPickerInited;

	/** �ɵ���ɫ
	*/
	UiColor m_oldColor;

	/** ��׼��ɫ�ؼ��ӿ�
	*/
	ColorPickerRegular* m_pRegularPicker;

	/** ɫ�׿ؼ�
	*/
	ColorControl* m_pSpectrumControl;

	/** ��ѡ�����ɫ�ؼ��ı���ӿ�
	*/
	RichEdit* m_pNewColorEdit;

private:
	/** RGB��ɫ�����ؼ�
	*/
	ColorUI m_rgbA;
	ColorUI m_rgbR;
	ColorUI m_rgbG;
	ColorUI m_rgbB;

	/** HSV��ɫ�����ؼ�
	*/
	ColorUI m_hsvH;
	ColorUI m_hsvS;
	ColorUI m_hsvV;

	/** HSL��ɫ�����ؼ�
	*/
	ColorUI m_hslH;
	ColorUI m_hslS;
	ColorUI m_hslL;
};

}//namespace ui

#endif //UI_CONTROL_COLORPICKER_CUSTOM_H_
