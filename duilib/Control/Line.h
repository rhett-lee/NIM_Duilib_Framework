#ifndef UI_CONTROL_LINE_H_
#define UI_CONTROL_LINE_H_

#pragma once

#include "duilib/Core/Control.h"

namespace ui
{
/** ���߿ؼ�
*/
class Line: public Control
{
public:
	Line();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

protected:
	/** ���ƿؼ�����ں���
	* @param [in] pRender ָ����������
	* @param [in] rcPaint ָ����������
	*/
	virtual void Paint(IRender* pRender, const UiRect& rcPaint) override;

private:
	/** ˮƽ���Ǵ�ֱ(true��ʾ��ֱ)
	*/
	bool m_bLineVertical;

	/** ������ɫ
	*/
	UiColor m_lineColor;

	/** �������
	*/
	int32_t m_lineWidth;

	/** ��������
	*/
	int32_t m_dashStyle;
};

}//namespace ui

#endif //UI_CONTROL_LINE_H_
