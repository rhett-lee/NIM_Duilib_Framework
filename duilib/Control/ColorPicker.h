#ifndef UI_CONTROL_COLORPICKER_H_
#define UI_CONTROL_COLORPICKER_H_

#pragma once

#include "duilib/Utils/WinImplBase.h"
#include "duilib/Control/Label.h"

namespace ui
{

/** ʰɫ������������
*/
class Control;
class ColorPickerRegular;
class ColorPickerStatard;
class ColorPickerStatardGray;
class ColorPickerCustom;
class ColorPicker : public WindowImplBase
{
public:
	ColorPicker();
	virtual ~ColorPicker();

	/** ���������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/** ��������
	*/
	static const std::wstring kClassName;

public:
	/** ������ѡ��ɫ
	*/
	void SetSelectedColor(const UiColor& color);

	/** ��ȡ���ڹر�ʱ����ѡ�����ɫ
	*/
	UiColor GetSelectedColor() const;

	/** ����ѡ����ɫ���¼�
	* @param[in] callback ѡ����ɫ�仯ʱ�Ļص�����
	*            ����˵��:
						wParam: ��ǰ��ѡ�����ɫֵ��������UiColor((uint32_t)wParam)������ɫ
						lParam: ԭ����ѡ�����ɫֵ��������UiColor((uint32_t)lParam)������ɫ
	*/
	void AttachSelectColor(const EventCallback& callback);

	/** �������ڹر��¼�
	 * @param[in] callback ָ���رպ�Ļص�����, ������ص��У����Ե���GetSelectedColor()������ȡѡ�����ɫֵ
	                       ������wParam�����ڹرյĴ��������
	 *                     0 - ��ʾ "ȷ��" �رձ�����
						   1 - ��ʾ������ڵ� "�ر�" ��ť�رձ�����(Ĭ��ֵ)
				           2 - ��ʾ "ȡ��" �رձ�����
	 */
	void AttachWindowClose(const EventCallback& callback);

private:
	/** �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	*/
	virtual void OnInitWindow() override;

	/** �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/** �ڲ�ѡ��������ɫ
	*/
	void OnSelectColor(const UiColor& newColor);

	/** ��Ļȡɫ
	*/
	void OnPickColorFromScreen();

private:
	/** ��ѡ�����ɫ�ؼ��ӿ�
	*/
	Label* m_pNewColor;

	/** ԭ������ɫ�ؼ��ӿ�
	*/
	Label* m_pOldColor;

	/** ������ɫ�ؼ��ӿ�
	*/
	ColorPickerRegular* m_pRegularPicker;

	/** ��׼��ɫ�ؼ��ӿ�
	*/
	ColorPickerStatard* m_pStatardPicker;

	/** ��׼��ɫ�ؼ��ӿ�(��ɫ)
	*/
	ColorPickerStatardGray* m_pStatardGrayPicker;

	/** �Զ�����ɫ�ؼ��ӿ�
	*/
	ColorPickerCustom* m_pCustomPicker;

	/** ѡ�����ɫ
	*/
	UiColor m_selectedColor;

	/** ѡ����ɫ�ļ����¼�
	*/
	EventCallback m_colorCallback;
};

} // namespace ui

#endif //UI_CONTROL_COLORPICKER_H_
