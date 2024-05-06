#ifndef UI_CONTROL_IPADDRESS_H_
#define UI_CONTROL_IPADDRESS_H_

#pragma once

#include "duilib/Box/HBox.h"

namespace ui
{
/** IP��ַ�ؼ�
*/
class RichEdit;
class IPAddress: public HBox
{
public:
	IPAddress();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/** �ÿؼ���ȡ����
	 */
	virtual void SetFocus() override;

	/** ����IP��ַ
	*/
	void SetIPAddress(const std::wstring& ipAddress);

	/** ��ȡIP��ַ
	*/
	std::wstring GetIPAddress() const;

protected:

	/** ��ʼ���ӿ�
	*/
	virtual void OnInit() override;

	/** @brief �ؼ�ͳһ����Ϣ������ڣ�����ͳ Windows ��Ϣת��Ϊ�Զ����ʽ����Ϣ
	 * @param[in] eventType	��Ϣ����
	 * @param[in] wParam	��Ϣ��������
	 * @param[in] lParam	��Ϣ��������
	 * @param[in] tChar		������Ϣ
	 * @param[in] mousePos	�����Ϣ
	 */
	virtual void SendEvent(EventType eventType,
			        	   WPARAM wParam = 0, 
						   LPARAM lParam = 0, 
						   TCHAR tChar = 0, 
						   const UiPoint& mousePos = UiPoint()) override;

	/** @brief ��ת�������Ϣ�ɷ�����Ϣ������
	 * @param[in] msg ��Ϣ����
	 */
    virtual void SendEvent(const EventArgs& msg) override;

	/** �༭��Ľ���ת��ʱ��
	*/
	void OnKillFocusEvent(RichEdit* pRichEdit, Control* pNewFocus);

private:
	/** �༭���б�
	*/
	std::vector<RichEdit*> m_editList;

	/** �ϴν������ĸ��ؼ���
	*/
	RichEdit* m_pLastFocus;

	/** IP��ַ
	*/
	UiString m_ipAddress;
};

}//namespace ui

#endif //UI_CONTROL_IPADDRESS_H_
