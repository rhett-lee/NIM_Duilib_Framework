#ifndef UI_CORE_STATE_COLOR_MAP_H_
#define UI_CORE_STATE_COLOR_MAP_H_

#pragma once

#include "duilib/Render/IRender.h"
#include "duilib/Core/UiTypes.h"
#include <map>

namespace ui 
{
/** �ؼ�״̬����ɫֵ��ӳ��
*/
class Control;
class IRender;
class UILIB_API StateColorMap
{
public:
	StateColorMap();

	/** ���ù���Ŀؼ��ӿ�
	*/
	void SetControl(Control* control);

	/** ��ȡ��ɫֵ���������������ɫ���򷵻ؿ�
	*/
	std::wstring GetStateColor(ControlStateType stateType) const;

	/** ������ɫֵ
	*/
	void SetStateColor(ControlStateType stateType, const std::wstring& color);

	/** �Ƿ����Hot״̬����ɫ
	*/
	bool HasHotColor() const;

	/** �Ƿ���ָ����ɫֵ
	*/
	bool HasStateColor(ControlStateType stateType) const;

	/** �Ƿ�����ɫֵ
	*/
	bool HasStateColors() const;

	/** ����ָ��״̬����ɫ
	*/
	void PaintStateColor(IRender* pRender, UiRect rcPaint, ControlStateType stateType) const;

private:
	/** �����Ŀؼ��ӿ�
	*/
	Control* m_pControl;

	/** ״̬����ɫֵ��ӳ���
	*/
	std::map<ControlStateType, UiString> m_stateColorMap;
};

} // namespace ui

#endif // UI_CORE_STATE_COLOR_MAP_H_
