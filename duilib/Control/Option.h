#ifndef UI_CONTROL_OPTION_H_
#define UI_CONTROL_OPTION_H_

#pragma once

#include "duilib/Control/CheckBox.h"

namespace ui
{

/** ��ѡ��ť�ؼ�
*/
template<typename InheritType = Control>
class UILIB_API OptionTemplate : public CheckBoxTemplate<InheritType>
{
public:
	OptionTemplate();
	~OptionTemplate();
		
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
    virtual void SetWindow(Window* pManager) override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void Selected(bool bSelected, bool bTriggerEvent = false) override;
	virtual void Activate() override;

	/**
	 * @brief ��ȡ����������
	 * @return ����������
	 */
	virtual std::wstring GetGroup() const;

	/**
	 * @brief ����������
	 * @param[in] strGroupName ������
	 * @return ��
	 */
	virtual void SetGroup(const std::wstring& strGroupName);

private:

    //����������(ͬһ�����ڵĿؼ������е�ѡ״̬����)
	UiString m_sGroupName;
};

template<typename InheritType>
OptionTemplate<InheritType>::OptionTemplate() :
    m_sGroupName()
{
}

template<typename InheritType>
OptionTemplate<InheritType>::~OptionTemplate()
{
    if (!m_sGroupName.empty() && this->GetWindow()) {
        this->GetWindow()->RemoveOptionGroup(m_sGroupName.c_str(), this);
    }
}

template<typename InheritType>
inline std::wstring OptionTemplate<InheritType>::GetType() const { return DUI_CTR_OPTION; }

template<>
inline std::wstring OptionTemplate<Box>::GetType() const { return DUI_CTR_OPTIONBOX; }

template<typename InheritType>
void OptionTemplate<InheritType>::SetWindow(Window* pManager)
{
    __super::SetWindow(pManager);
    if (!m_sGroupName.empty()) {
        if (this->GetWindow()) {
            this->GetWindow()->AddOptionGroup(m_sGroupName.c_str(), this);
        }
    }
}

template<typename InheritType>
void OptionTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"group") {
        SetGroup(strValue);
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

template<typename InheritType>
void OptionTemplate<InheritType>::Selected(bool bSelected, bool bTriggerEvent)
{
    bool isChanged = this->IsSelected() != bSelected;
    this->SetSelected(bSelected);

    if (this->GetWindow() != nullptr) {
        if (this->IsSelected()) {
            if (!m_sGroupName.empty()) {
                std::vector<Control*>* aOptionGroup = this->GetWindow()->GetOptionGroup(m_sGroupName.c_str());
                ASSERT(aOptionGroup);
                if (aOptionGroup) {
                    for (auto it = aOptionGroup->begin(); it != aOptionGroup->end(); ++it) {
                        auto pControl = static_cast<OptionTemplate<InheritType>*>(*it);
                        if ((pControl != nullptr) && pControl != this) {
                            pControl->Selected(false, bTriggerEvent);
                        }
                    }
                }
            }

            if (isChanged && bTriggerEvent) {
                this->SendEvent(kEventSelect);
            }
        }
        else {
            if (isChanged && bTriggerEvent) {
                this->SendEvent(kEventUnSelect);
            }
        }
    }

    this->Invalidate();
}

template<typename InheritType>
void OptionTemplate<InheritType>::Activate()
{
    if (!this->IsActivatable()) {
        return;
    }
    Selected(true, true);
    ButtonTemplate<InheritType>::Activate();
}

template<typename InheritType>
std::wstring OptionTemplate<InheritType>::GetGroup() const
{
    return m_sGroupName.c_str();
}

template<typename InheritType>
void OptionTemplate<InheritType>::SetGroup(const std::wstring& strGroupName)
{
    if (strGroupName.empty()) {
        if (m_sGroupName.empty()) {
            return;
        }
        if (this->GetWindow()) {
            this->GetWindow()->RemoveOptionGroup(m_sGroupName.c_str(), this);
        }
        m_sGroupName.clear();
    }
    else {
        if (m_sGroupName == strGroupName) {
            return;
        }
        if (!m_sGroupName.empty() && this->GetWindow()) {
            this->GetWindow()->RemoveOptionGroup(m_sGroupName.c_str(), this);
        }
        m_sGroupName = strGroupName;
        if (this->GetWindow()) {
            this->GetWindow()->AddOptionGroup(m_sGroupName.c_str(), this);
        }
    }

    Selected(this->IsSelected(), true);
}

typedef OptionTemplate<Control> Option;
typedef OptionTemplate<Box> OptionBox;

}

#endif // UI_CONTROL_OPTION_H_
