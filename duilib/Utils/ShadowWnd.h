#ifndef UI_UTILS_SHADOW_WND_H__
#define UI_UTILS_SHADOW_WND_H__

#pragma once

#include "duilib/Utils/WinImplBase.h"

namespace ui {

/** ʹ�ø�����Ӱ���ڵĻ��࣬ʵ���˴������ڲ����ӵĹ��ܣ��ṩû�� WS_EX_LAYERED ���ԵĴ��ڼ̳�
 * ����ʵ�֣���װ��3�ִ���ģʽ��
 * ��1������ģʽ����������Ӱ�Ĵ��ڣ�����ͨ��XML�����ļ�<Window>�������ã���������
 *             shadow_attached="false" layered_window="false" ������Ҫ����alpha���ԣ���֧��alpha����;
 * ��2��������Ӱ����ģʽ����Ҫʹ�ò㴰��(����WS_EX_LAYERED����)������ͨ��XML�����ļ�<Window>�������ã���������
 *             shadow_attached="true" layered_window="true" ��alphaΪ��ѡ���ã����ô���͸���ȣ���������ã�Ĭ��Ϊ255��
 * ��3��������Ӱ����ģʽ������Ҫʹ�ò㴰��(������WS_EX_LAYERED����)������ͨ��XML�����ļ�<Window>�������ã���������
 *             shadow_attached="true" layered_window="false" ������Ҫ����alpha���ԣ���֧��alpha����;
 *             �������õ�ͬ�ڣ�layered_window="false"��������shadow_attached���ԡ�
 */
class ShadowWndBase;
class ShadowWnd: public ui::WindowImplBase
{
public:
	ShadowWnd();

	/**@brief ��������
	 * @param[in] hwndParent �����ھ��
	 * @param[in] windowName ��������
	 * @param[in] dwStyle ������ʽ
	 * @param[in] dwExStyle ������չ��ʽ, �������ò㴰�ڣ�WS_EX_LAYERED��������
	 * @param[in] rc ���ڴ�С
	 */
	virtual bool CreateWnd(HWND hwndParent,
						   const wchar_t* windowName,
						   uint32_t dwStyle,
						   uint32_t dwExStyle,
						   const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

private:
	/** ���Ӵ�����Ӱ
	*/
	virtual Box* AttachShadow(Box* pRoot) override;

private:
	/** �ж��Ƿ���Ҫ����͸�����ڵĸ�����Ӱ
	*/
	bool NeedCreateShadowWnd() const;

private:
	//��Ӱ���ڣ�͸����
	ShadowWndBase* m_pShadowWnd;
};
} // namespace ui

#endif // UI_UTILS_SHADOW_WND_H__
