#ifndef UI_CORE_TOOLTIP_H_
#define UI_CORE_TOOLTIP_H_

#pragma once

#include "duilib/Core/UiPoint.h"
#include "duilib/Core/UiRect.h"
#include <string>
#include <CommCtrl.h>

namespace ui 
{
/** ToolTip��ʵ��
*/
class UILIB_API ToolTip
{
public:
    ToolTip();
	~ToolTip();
	
public:
	/**@brief ����������״̬
	*/
	void SetMouseTracking(HWND hParentWnd, bool bTracking);

	/**@brief ��ʾToolTip��Ϣ
	* @param [in] hParentWnd �����ھ��
	* @param [in] hModule ���ڹ�������Դ���
	* @param [in] rect Tooltip��ʾ����
	* @param [in] maxWidth Tooltip��ʾ�����
	* @param [in] trackPos ���ٵ�λ��
    * @param [in] text Tooltip��ʾ����
	*/
	void ShowToolTip(HWND hParentWnd, 
					 HMODULE hModule, 
					 const UiRect& rect, 
					 uint32_t maxWidth,
					 const UiPoint& trackPos,
					 const std::wstring& text);

	/**@brief ����ToolTip��Ϣ
	*/
	void HideToolTip();

	/**@brief ���������״̬
	*/
	void ClearMouseTracking();

private:
    //������״̬
	bool m_bMouseTracking;
	
	//Tooltip��Ϣ
	TOOLINFO m_ToolTip;
	
	//Tooltip����
	HWND m_hwndTooltip;
	
	//������
	HWND m_hParentWnd;
};

} // namespace ui

#endif // UI_CORE_TOOLTIP_H_
