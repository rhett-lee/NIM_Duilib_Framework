#ifndef UI_CONTROL_FILTERCOMBO_H_
#define UI_CONTROL_FILTERCOMBO_H_

#pragma once

#include "duilib/Control/Combo.h"

namespace ui 
{

/** ���й��˹��ܵ���Ͽ�
*/
class UILIB_API FilterCombo : public Combo
{
public:
	FilterCombo();
	FilterCombo(const FilterCombo& r) = delete;
	Combo& operator=(const FilterCombo& r) = delete;
	virtual ~FilterCombo();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

protected:
	virtual void OnInit() override;
	
protected:
	/** �����Edit���水�°�ť
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnEditButtonDown(const EventArgs& args);

	/** �����Edit���浯��ť
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnEditButtonUp(const EventArgs& args);

	/** Edit���ı����ݷ����仯
	 * @param[in] args �����б�
	 * @return ʼ�շ��� true
	 */
	virtual bool OnEditTextChanged(const ui::EventArgs& args);

private:

	/** ���������б���������ݽ��й���
	*/
	void FilterComboList(const std::wstring& filterText);

	/** �ж��ı��Ƿ������������
	*/
	bool IsFilterText(const std::wstring& filterText, const std::wstring& itemText) const;
};

} // namespace ui

#endif // UI_CONTROL_FILTERCOMBO_H_
