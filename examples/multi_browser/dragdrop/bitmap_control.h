#pragma once

/** @class BitmapControl
  * @brief ��HBITMAP��Ϊ�����Ŀؼ�,�ؼ�����������HBITMAP
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class BitmapControl : public ui::Control
{
public:
	BitmapControl();

	/**
	* ��д���ؼ����ƺ���
	* @param[in] hDC Ŀ��DC
	* @param[in] rcPaint �ɻ�������
	* @return void	�޷���ֵ
	*/
	virtual void Paint(ui::IRender* pRender, const ui::UiRect& rcPaint) override;

	/**
	* ������ʾ�ڱ�����HBITMAP����
	* @param[in] bitmap λͼ����
	* @return void	�޷���ֵ
	*/
	void SetBitmapImage(HBITMAP bitmap);

private:
	HBITMAP bitmap_;
};