#ifndef UI_CONTROL_COMBO_BUTTON_H_
#define UI_CONTROL_COMBO_BUTTON_H_

#pragma once

#include "duilib/Core/Box.h"
#include "duilib/Box/VBox.h"
#include "duilib/Control/TreeView.h"
#include "duilib/Control/RichEdit.h"

namespace ui 
{
typedef ButtonTemplate<VBox> ButtonVBox;

/** ����������Ͽ�İ�ť
*/
class UILIB_API ComboButton : public Box
{
    friend class ComboButtonWnd;
public:
	ComboButton();
	ComboButton(const ComboButton& r) = delete;
	ComboButton& operator=(const ComboButton& r) = delete;
	virtual ~ComboButton();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual bool CanPlaceCaptionBar() const override;
	virtual std::wstring GetBorderColor(ControlStateType stateType) const override;

public:

	/** ��ȡ�������б��С(��Ⱥ͸߶�)
	*/
	UiSize GetDropBoxSize() const;

	/** �����������б��С(��Ⱥ͸߶�)
	 * @param [in] szDropBox Ҫ���õĴ�С��Ϣ
	 * @param [in] bNeedScaleDpi �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetDropBoxSize(UiSize szDropBox, bool bNeedScaleDpi);

	/** ���� Combobox �Ƿ����ϵ���
	 * @param[in] top Ϊ true �����ϵ�����false ΪĬ�����µ���
	 */
	void SetPopupTop(bool top) { m_bPopupTop = top; }

	/** �ж� Combobox ����ģʽ�Ƿ������ϵ���
	 * @return ���� true ��ʾ���ϵ���������Ϊ false
	 */
	bool IsPopupTop() const { return m_bPopupTop; }

	/** ������ఴť�ؼ���Class����
	*/
	void SetLeftButtonClass(const std::wstring& classValue);

	/** ������ఴť�ϲ��Label�ؼ���Class����
	*/
	void SetLeftButtonTopLabelClass(const std::wstring& classValue);

	/** ������ఴť�²��Label�ؼ���Class����
	*/
	void SetLeftButtonBottomLabelClass(const std::wstring& classValue);

	/** �����Ҳఴť�ؼ���Class����
	*/
	void SetRightButtonClass(const std::wstring& classValue);

	/** ���������б�������Class����
	*/
	void SetComboBoxClass(const std::wstring& classValue);

public:
	/** ��ȡ�����б�������ӿ�
	*/
	Box* GetComboBox() const;

	/** ��ȡ��ť�ؼ�
	*/
	ButtonVBox* GetLeftButtonBox() const;

	/** ��ȡ��ť�ؼ��ϲ���ı��ؼ�
	*/
	Label* GetLabelTop() const;

	/** ��ȡ��ť�ؼ��²���ı��ؼ�
	*/
	Label* GetLabelBottom() const;

	/** ��ť�ؼ�
	*/
	Button* GetRightButton() const;

	/** ���������б��ڵ�λ��
	*/
	void UpdateComboWndPos();

public:
	/** �������ť����¼������İ�ť�������
	 * @param[in] callback �����Ļص�����
	 */
	void AttachClick(const EventCallback& callback) { AttachEvent(kEventClick, callback);}

	/** �����������ر��¼�
	 * @param[in] callback �������رպ󴥷��Ļص�������WPARAM Ϊ1��ʾȡ����Ϊ0��ʾ�����ر�
	 */
	void AttachWindowClose(const EventCallback& callback) { AttachEvent(kEventWindowClose, callback); }

protected:
	/** ��ʾ�����б�
	*/
	virtual void ShowComboList();

	/** �ر������б�
	*/
	virtual void HideComboList();

	/** ���������б�
	*/
	virtual void UpdateComboList();

	/** �����򴰿ڹر�
	* @param [in] bCanceled true��ʾȡ���������ʾ�����ر�
	*/
	virtual void OnComboWndClosed(bool bCanceled);

	/** ��ఴť����¼�
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnLeftButtonClicked(const EventArgs& args);

	/** �Ҳఴť��갴���¼�
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnRightButtonDown(const EventArgs& args);

	/** �Ҳఴť����¼�
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnRightButtonClicked(const EventArgs& args);

	/** ����ʧȥ����
	* @param[in] args �����б�
	* @return ʼ�շ��� true
	*/
	virtual bool OnWindowKillFocus(const EventArgs& args);

	/** �����ƶ�
	* @param[in] args �����б�
	* @return ʼ�շ��� true
	*/
	virtual bool OnWindowMove(const EventArgs& args);

protected:
	/** ��ʼ������
	*/
	virtual void OnInit() override;

private:
	/** ���������б�
	*/
	void ParseAttributeList(const std::wstring& strList,
							std::vector<std::pair<std::wstring, std::wstring>>& attributeList) const;

	/** ���ÿؼ��������б�
	*/
	void SetAttributeList(Control* pControl, const std::wstring& classValue);

	/** �Ƴ��ؼ�
	*/
	void RemoveControl(Control* pControl);

	/** ��ť��״̬�����仯��ͬ��״̬
	* @param[in] args �����б�
	* @return ʼ�շ��� true
	*/
	bool OnButtonStateChanged(const EventArgs& args);

private:
	/** �����б�Ĵ��ڽӿ�
	*/
	ComboButtonWnd* m_pWindow;

	/** �����б�Ĵ�С����Ⱥ͸߶ȣ�
	*/
	UiSize m_szDropBox;

	/** �����б��Ƿ����ϵ���
	*/
	bool m_bPopupTop;

private:
	/** �����б������
	*/
	Box* m_pComboBox;

	/** ��ť�����ؼ�ButtonVBox
	*/
	ButtonVBox* m_pLeftButton;

	/** ��ť�������ϲ���ı��ؼ�(λ��ButtonVBox����)
	*/
	Label* m_pLabelTop;

	/** ��ť�������²���ı��ؼ�(λ��ButtonVBox����)
	*/
	Label* m_pLabelBottom;

	/** ��ť�ؼ����Ҳ�������ť��
	*/
	Button* m_pRightButton;

	/** ��갴�µ�ʱ���Ƿ�������ʾ�����б�
	*/
	bool m_bDropListShown;
};

} // namespace ui

#endif // UI_CONTROL_COMBO_BUTTON_H_
