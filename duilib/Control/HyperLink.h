#ifndef UI_CONTROL_HYPER_LINK_H_
#define UI_CONTROL_HYPER_LINK_H_

#pragma once

#include "duilib/Control/Label.h"

namespace ui {

/** ���г������ӵ�����, ���URLΪ�յĻ������Ե�����ͨ�����ְ�ťʹ��
*/
class HyperLink : public Label
{
public:
    /// ��д���෽�����ṩ���Ի����ܣ���ο���������
    virtual std::wstring GetType() const override { return DUI_CTR_HYPER_LINK; }
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override
    {
        if (strName == L"url") {
            m_url = strValue;
        }
        else {
            __super::SetAttribute(strName, strValue);
        }
    }

    virtual void Activate() override
    {
        if (!IsActivatable()) {
            return;
        }
        std::wstring url = m_url.c_str();
        SendEvent(kEventLinkClick, (WPARAM)url.c_str());
    }

public:
    /** �����������ӱ�����¼�
     * @param[in] callback �������ӱ������Ļص�����
     */
    void AttachLinkClick(const EventCallback& callback) { AttachEvent(kEventLinkClick, callback); }

private:
    /** URL
    */
    UiString m_url;
};

}	// namespace ui

#endif // UI_CONTROL_HYPER_LINK_H_