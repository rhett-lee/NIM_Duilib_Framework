#ifndef UI_CORE_TABBOX_H_
#define UI_CORE_TABBOX_H_

#pragma once

#include "duilib/Core/Box.h"

namespace ui
{

class UILIB_API TabBox : public Box
{
public:
	explicit TabBox(Layout* pLayout = new Layout());

	// ���ڳ�ʼ��xml����
	virtual void OnInit() override;

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual bool AddItem(Control* pControl) override;
	virtual bool AddItemAt(Control* pControl, size_t iIndex) override;
	virtual bool RemoveItem(Control* pControl) override;
	virtual bool RemoveItemAt(size_t iIndex) override;
	virtual void RemoveAllItems() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/**
	 * @brief ��ȡ��ǰѡ����
	 * @return ���ص�ǰѡ��������(�������Ч�������򷵻�Box::InvalidIndex)
	 */
	size_t GetCurSel() const;

	/**
	 * @brief ���ݿؼ�����ѡ��һ������
	 * @param[in] iIndex Ҫѡ�����������
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(size_t iIndex);

	/**
	 * @brief ���ݿؼ�ָ��ѡ��һ������
	 * @param[in] pControl Ҫѡ�������ָ��
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(Control* pControl);

	/**
	 * @brief ���ݿؼ�����ѡ��һ������
	 * @param[in] pControlName Ҫѡ��Ŀؼ�����
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SelectItem(const std::wstring& pControlName);

	/**
	 * @brief �����Ƿ���ʾ����Ч��
	 * @param[in] bFadeSwitch ����Ϊ true ����ʾ��false Ϊ����ʾ����
	 * @return ��
	 */
	void SetFadeSwitch(bool bFadeSwitch);

	/**
	 * @brief �ж��Ƿ���Ҫ��ʾ����Ч��
	 * @return ���� true ��ʾ������false Ϊ����ʾ����Ч��
	 */
	bool IsFadeSwitch() const { return m_bFadeSwith; }
	
	/** @brief ����Tabҳ��ѡ���¼�
	  * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	  * @return ��
	  */
	void AttachTabSelect(const EventCallback& callback) { AttachEvent(kEventTabSelect, callback); }

protected:
	/**
	 * @brief ��ʾһ�� TAB ��ʱ������һЩ����
	 * @param[in] it TAB ������
	 * @return ��
	 */
	void OnShowTabItem(size_t index);

	/**
	 * @brief ����һ�� TAB ��ʱ������һЩ����
	 * @param[in] it TAB ������
	 * @return ��
	 */
	void OnHideTabItem(size_t index);

	/** �������Ž���
	*@param[in] it TAB ������
	*/
	void OnAnimationComplete(size_t index);

private:
	//��ǰѡ���Item�±�
	size_t m_iCurSel;

	//��ʼ��ʱ��Ҫѡ���Item�±�
	size_t m_iInitSel;

	//�Ƿ���Ҫ�л�����
	bool m_bFadeSwith;
};

}
#endif // UI_CORE_TABBOX_H_
