#ifndef UI_CONTROL_HOTKEY_H_
#define UI_CONTROL_HOTKEY_H_

#pragma once

#include "duilib/Box/HBox.h"

namespace ui
{
class HotKeyRichEdit;

/** �ȼ��ؼ�
*/
class HotKey: public HBox
{
public:
	HotKey();
    virtual ~HotKey();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

    /** ��������
    */
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

    /** �ÿؼ���ȡ����
     */
    virtual void SetFocus() override;

public:
    /** �����ȼ�
    * @param [in] wVirtualKeyCode ��������룬���磺VK_DOWN�ȣ��ɲο���https://learn.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
    * @param [in] wModifiers �ȼ���ϼ���־λ���μ�HotKeyModifiersö�����͵�ֵ
    */
    void SetHotKey(uint8_t wVirtualKeyCode, uint8_t wModifiers);

    /** ��ȡ�ȼ�
    * @param [out] wVirtualKeyCode ��������룬���磺VK_DOWN��
    * @param [out] wModifiers �ȼ���ϼ���־λ���μ�HotKeyModifiersö�����͵�ֵ
    */
    void GetHotKey(uint8_t& wVirtualKeyCode, uint8_t& wModifiers) const;

    /** �����ȼ���ֵ[��MAKEWORD(wVirtualKeyCode, wModifiers)����]
    * @param [in] dwHotKey ��8λΪwModifiers����8λΪwVirtualKeyCode
    */
    void SetHotKey(uint16_t dwHotKey);

    /** ��ȡ�ȼ���ֵ[��MAKEWORD(wVirtualKeyCode, wModifiers)����]
    * @return �ȼ���ֵ����8λΪwModifiers����8λΪwVirtualKeyCode
    */
    uint16_t GetHotKey() const;

    /** ��ȡ�ȼ���ʾ���ƣ�����"Ctrl + C"��
    */
    std::wstring GetHotKeyName() const;

    /** ������ʾ���������ȼ�
    * @param [in] hotKeyName �ȼ����ƣ�����"Ctrl + C"��
    */
    bool SetHotKeyName(const std::wstring& hotKeyName);

public:
    /** ��ȡ������ʾ����
    * @param [in] wVirtualKeyCode ��������룬���磺VK_DOWN��
    * @param [in] fExtended ����������������չ��Կ����Ϊ true������Ϊ false��
    */
    static std::wstring GetKeyName(uint8_t wVirtualKeyCode, bool fExtended);

protected:

	//��ʼ��
	virtual void OnInit() override;

private:
	/** Ĭ����ʾ������
    */
	UiString m_defaultText;

    /** �༭��ؼ��Ľӿ�
    */
    HotKeyRichEdit* m_pRichEdit;
};

}//namespace ui

#endif //UI_CONTROL_HOTKEY_H_
