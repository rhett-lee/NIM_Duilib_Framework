/** @file cef_control.h
 * @brief ��װCef���������Ϊduilib�ؼ�
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2016/7/19
 */
#pragma once
#include "cef_control_base.h"

namespace nim_comp {

class CefNativeControl : public CefControlBase
{
public:
	CefNativeControl(void);
	~CefNativeControl(void);	

	virtual void Init() override;
	virtual void SetPos(ui::UiRect rc) override;
	virtual void HandleEvent(const ui::EventArgs& msg) override;
	virtual void SetVisible(bool bVisible) override;
	virtual void SetWindow(ui::Window* pManager) override;

	/**
	* @brief �򿪿����߹���
	* @param[in] view һ�� CefControl �ؼ�ʵ��(����CefControl������Ҫ����)
	* @return �ɹ����� true��ʧ�ܷ��� false
	*/
	virtual bool AttachDevTools(ui::Control* view) override;

protected:
	virtual void ReCreateBrowser() override;
};
}