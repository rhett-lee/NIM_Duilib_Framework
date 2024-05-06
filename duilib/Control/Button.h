#ifndef UI_CONTROL_BUTTON_H_
#define UI_CONTROL_BUTTON_H_

#pragma once

#include "duilib/Control/Label.h"

namespace ui {

template<typename InheritType = Control>
class UILIB_API ButtonTemplate : public LabelTemplate<InheritType>
{
public:
    ButtonTemplate();

    /// ��д���෽�����ṩ���Ի����ܣ���ο���������
    virtual std::wstring GetType() const override;
    virtual void Activate() override;
    virtual void HandleEvent(const EventArgs& msg) override;
    virtual uint32_t GetControlFlags() const override;

    /** �ÿؼ��Ƿ���Է����ڱ������ϣ������ڴ���NC��Ϣ��Ӧ��
     * @return ���� true ��ʾ���ԣ�false ��ʾ�����ԣ� Ĭ�Ϸ���false
     */
    virtual bool CanPlaceCaptionBar() const override;
};

template<typename InheritType>
inline std::wstring ButtonTemplate<InheritType>::GetType() const { return DUI_CTR_BUTTON; }

template<>
inline std::wstring ButtonTemplate<Box>::GetType() const { return DUI_CTR_BUTTONBOX; }

template<typename InheritType>
uint32_t ui::ButtonTemplate<InheritType>::GetControlFlags() const
{
    return this->IsKeyboardEnabled() && this->IsEnabled() && this->IsAllowTabStop() ? UIFLAG_TABSTOP : UIFLAG_DEFAULT;
}

template<typename InheritType>
ButtonTemplate<InheritType>::ButtonTemplate()
{
    this->SetTextStyle(TEXT_VCENTER | TEXT_CENTER | TEXT_END_ELLIPSIS | TEXT_NOCLIP | TEXT_SINGLELINE, false);
}

template<typename InheritType>
void ButtonTemplate<InheritType>::HandleEvent(const EventArgs& msg)
{
    if (msg.Type == kEventKeyDown) {
        if (this->IsEnabled() && this->IsKeyboardEnabled()) {
            //���»س������߿ո����ʱ�򣬴�����ť��Ӧ����
            if (msg.chKey == VK_SPACE || msg.chKey == VK_RETURN) {
                Activate();
                return;
            }
        }
    }
    __super::HandleEvent(msg);
}

template<typename InheritType>
void ButtonTemplate<InheritType>::Activate()
{
    if (!this->IsActivatable()) {
        return;
    }
    this->SendEvent(kEventClick);
}

template<typename InheritType>
bool ButtonTemplate<InheritType>::CanPlaceCaptionBar() const
{
    return true;
}

typedef ButtonTemplate<Control> Button;
typedef ButtonTemplate<Box> ButtonBox;

}	// namespace ui

#endif // UI_CONTROL_BUTTON_H_