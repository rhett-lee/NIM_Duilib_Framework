#ifndef UI_CONTROL_COLOR_CONTROL_H_
#define UI_CONTROL_COLOR_CONTROL_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Render/IRender.h"

namespace ui
{
/** �Զ�����ɫ�ؼ�
*/
class ColorControl: public Control
{
public:
	ColorControl();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

	/** ѡ����ɫ
	*/
	void SelectColor(const UiColor& selColor);

	/** ����ѡ����ɫ���¼�
	* @param[in] callback ѡ����ɫ�仯ʱ�Ļص�����
	*            ����˵��:
						wParam: ��ǰ��ѡ�����ɫֵ��������UiColor((uint32_t)wParam)������ɫ
						lParam: ԭ����ѡ�����ɫֵ��������UiColor((uint32_t)lParam)������ɫ
	*/
	void AttachSelectColor(const EventCallback& callback) { AttachEvent(kEventSelectColor, callback); }

protected:
	/** ���Ʊ���ͼƬ����ں���
	* @param[in] pRender ָ����������
	*/
	virtual void PaintBkImage(IRender* pRender) override;

	/** ����������
	*/
	virtual bool ButtonDown(const EventArgs& msg) override;

	/** ����ƶ�
	*/
	virtual bool MouseMove(const EventArgs& msg) override;

	/** ����������
	*/
	virtual bool ButtonUp(const EventArgs& msg) override;

private:
	/** ��ȡ���Ƶ���ɫλͼ�ӿ�
	* @param [in] rect ��ʾ�����С��Ϣ
	*/
	IBitmap* GetColorBitmap(const UiRect& rect);

	/** ѡ��λ�÷����仯
	*/
	void OnSelectPosChanged(const UiRect& rect, const UiPoint& pt);

	/** ������겶��
	*/
	void SetMouseCapture(bool bCapture);

private:
	/** ��ɫλͼ
	*/
	std::unique_ptr<IBitmap> m_spBitmap;

	/** �����λ��
	*/
	UiPoint m_lastPt;

	/** ����Ƿ���
	*/
	bool m_bMouseDown;
};

}//namespace ui

#endif //UI_CONTROL_COLOR_CONTROL_H_
