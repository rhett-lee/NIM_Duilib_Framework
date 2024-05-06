#ifndef UI_CONTROL_CHECKBOX_H_
#define UI_CONTROL_CHECKBOX_H_

#pragma once

#include "duilib/Control/Button.h"

namespace ui {

template<typename InheritType = Control>
class UILIB_API CheckBoxTemplate : public ButtonTemplate<InheritType>
{
public:
    CheckBoxTemplate();
    CheckBoxTemplate(const CheckBoxTemplate& r) = delete;
    CheckBoxTemplate& operator=(const CheckBoxTemplate& r) = delete;
    virtual ~CheckBoxTemplate();

    /// ��д���෽�����ṩ���Ի����ܣ���ο���������
    virtual std::wstring GetType() const override;
    virtual void Activate() override;
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
    virtual void PaintStateColors(IRender* pRender) override;
    virtual void PaintStateImages(IRender* pRender) override;
    virtual void PaintText(IRender* pRender) override;
    virtual bool HasHotState() override;
    virtual std::wstring GetBorderColor(ControlStateType stateType) const override;

    /** �ر�CheckBox���ܣ����CheckBox������ͼƬ����(�������ڵ㣬CheckBox�����ǿ���ͨ�����ؿ������߹رյ�)
    */
    void ClearStateImages();

    /**
     * @brief ѡ��״̬�£�û�����ñ���ɫ�򱳾�ͼʱ���Ƿ��÷�ѡ��״̬�Ķ�Ӧ����������
     * @return ���� true Ϊѡ��״̬������Ϊ false
     */
    bool IsPaintNormalFirst() const { return m_bPaintNormalFirst; }

    /**
     * @brief ���ÿؼ�ѡ��״̬�£�û�����ñ���ɫ�򱳾�ͼʱ���÷�ѡ��״̬�Ķ�Ӧ����������
     * @param[in] bFirst Ϊ true ���Ʒ�ѡ��״̬���ԣ�false ������
     * @return ��
     */
    void SetPaintNormalFirst(bool bFirst) { m_bPaintNormalFirst = bFirst; }

    /**
     * @brief �жϵ�ǰ�Ƿ���ѡ��״̬
     * @return ���� true Ϊѡ��״̬������Ϊ false
     */
    bool IsSelected() const { return m_bSelected; }

    /** ����ѡ��״̬�����������¼��������½���
    * @param [in] bSelected trueΪѡ��״̬��falseΪ��ѡ��״̬
    */
    virtual void SetSelected(bool bSelected);

    /** ���ÿؼ��Ƿ�ѡ��״̬
     * @param [in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
     * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��Ĭ��Ϊ false
     */
    virtual void Selected(bool bSelected, bool bTriggerEvent = false);

    /** ��ȡ��ѡ��ʱ��ͼƬ
     * @param [in] stateType Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
     * @return ����ͼƬ·��������
     */
    std::wstring GetSelectedStateImage(ControlStateType stateType) const;

    /** ���ñ�ѡ��ʱ��ͼƬ
     * @param [in] stateType Ҫ��������״̬�µ�ͼƬ
     * @param [in] strImage ͼƬ·��������
     */
    void SetSelectedStateImage(ControlStateType stateType, const std::wstring& strImage);

    /** ��ȡ��ѡ��ʱ��ǰ��ͼƬ
     * @param[in] stateType Ҫ��ȡ����״̬�µ�ǰ��ͼƬ
     */
    std::wstring GetSelectedForeStateImage(ControlStateType stateType) const;

    /** ���ñ�ѡ��ʱ��ǰ��ͼƬ
     * @param[in] stateType Ҫ���ú���״̬�µ�ǰ��ͼƬ
     * @param[in] strImage ͼƬλ��
     */
    void SetSelectedForeStateImage(ControlStateType stateType, const std::wstring& strImage);

    /** ��ȡ��ѡ��ʱ���ı���ɫ
     */
    std::wstring GetSelectedTextColor() const;

    /** ���ñ�ѡ��ʱ���ı���ɫ
     * @param[in] dwTextColor Ҫ���õ���ɫ�ַ���������ɫ������ global.xml �д���
     */
    void SetSelectedTextColor(const std::wstring& dwTextColor);

    /** ��ȡ��ѡ��ʱָ��״̬�µ��ı���ɫ
     * @param[in] stateType Ҫ��ȡ����״̬�µ���ɫ
     * @return ������ɫ�ַ�������ֵ�� global.xml �ж���
     */
    std::wstring GetSelectedStateTextColor(ControlStateType stateType) const;

    /** ���ñ�ѡ��ʱָ��״̬�µ��ı���ɫ
     * @param[in] stateType Ҫ���ú���״̬�µ���ɫ
     * @param[in] stateColor Ҫ���õ���ɫ
     */
    void SetSelectedStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor);

    /** ��ȡ��ѡ��ʱָ��״̬�µ�ʵ�ʱ���Ⱦ�ı���ɫ
     * @param [in] buttonStateType Ҫ��ȡ����״̬�µ���ɫ
     * @param [out] stateType ʵ�ʱ���Ⱦ��״̬
     * @return ������ɫ�ַ�������ֵ�� global.xml �ж���
     */
    std::wstring GetPaintSelectedStateTextColor(ControlStateType buttonStateType, ControlStateType& stateType) const;

    /** ��ȡ��ѡ��ʱ�Ŀؼ���ɫ
     * @param [in] stateType Ҫ��ȡ����״̬�µ���ɫ
     * @return ������ɫ�ַ�������ֵ�� global.xml �ж���
     */
    std::wstring GetSelectStateColor(ControlStateType stateType) const;

    /** ���ñ�ѡ��ʱ�Ŀؼ���ɫ
     * @param[in] stateType Ҫ���ú���״̬�µ���ɫ
     * @param[in] stateColor Ҫ���õ���ɫ
     */
    void SetSelectedStateColor(ControlStateType stateType, const std::wstring& stateColor);

    /** ������ѡ��ʱ���¼�
     * @param [in] callback ��ѡ��ʱ�����Ļص�����
     */
    void AttachSelect(const EventCallback& callback) { this->AttachEvent(kEventSelect, callback); }

    /** ����ȡ��ѡ��ʱ���¼�
     * @param [in] callback ȡ��ѡ��ʱ�����Ļص�����
     */
    void AttachUnSelect(const EventCallback& callback) { this->AttachEvent(kEventUnSelect, callback); }

public: //����̬ѡ��[ȫ��ѡ�񡢲���ѡ��δѡ��]/��ѡģʽ���ֹ��ܵĺ�����

    /** ��갴�������¼��������ж��Ƿ�����CheckBoxͼƬ��
    */
    virtual bool ButtonUp(const EventArgs& msg) override;

    /** �Ƿ����ѡ��״̬�µı���ɫ���ṩ�麯����Ϊ��ѡ��
   ������ListBox/TreeView�ڵ��ڶ�ѡʱ�������й�ѡ�������Ҫ����ѡ��״̬�ı���ɫ��
    */
    virtual bool CanPaintSelectedColors() const { return true; }

    /** �Ƿ�֧�ֹ�ѡģʽ��Ŀǰ��TreeView/ListCtrl��ʹ�����ģʽ��
        ��ѡģʽ��ָ��
        ��1��ֻ�е����CheckBoxͼƬ�ϵ�ʱ�򣬹�ѡ��ͼƬ����ѡ��״̬���ǹ�ѡģʽ�£��ǵ���ڿؼ������ھ�ѡ��
        ��2����ѡ״̬��ѡ��״̬���룬��������ͬ��״̬
    */
    virtual bool SupportCheckedMode() const { return false; }

    /** �����Ƿ��Զ���ѡѡ���������(������Header��ÿ��)
    */
    void SetAutoCheckSelect(bool bAutoCheckSelect) { m_bAutoCheckSelect = bAutoCheckSelect; }

    /** ��ȡ�Ƿ��Զ���ѡѡ���������
    */
    bool IsAutoCheckSelect() const { return m_bAutoCheckSelect; }

    /** �Ƿ��ڹ�ѡ״̬, ���� SupportCheckedMode() ����Ϊtrue��ʱ��������
    */
    bool IsChecked() const { return m_bChecked; }

    /** ����Check״̬
    * @param [in] bChecked �Ƿ�����ΪCheck״̬
    * @param [in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��Ĭ��Ϊ false
    */
    void SetChecked(bool bChecked, bool bTriggerEvent = false);

    /** ���ò���ѡ���־��֧����̬ѡ���־��ȫ��ѡ��/����ѡ��/δѡ��
    */
    void SetPartSelected(bool bPartSelected);

    /** ��ǰ�Ƿ�Ϊ����ѡ��
    */
    bool IsPartSelected() const;

    /** ��ȡ����ѡ��ʱ��ͼƬ
     * @param [in] stateType Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
     * @return ����ͼƬ·��������
     */
    std::wstring GetPartSelectedStateImage(ControlStateType stateType);

    /** ���ò���ѡ��ʱ��ͼƬ
     * @param [in] stateType Ҫ��������״̬�µ�ͼƬ
     * @param [in] strImage ͼƬ·��������
     */
    void SetPartSelectedStateImage(ControlStateType stateType, const std::wstring& strImage);

    /** ��ȡ����ѡ��ʱ��ǰ��ͼƬ
     * @param[in] stateType Ҫ��ȡ����״̬�µ�ǰ��ͼƬ
     */
    std::wstring GetPartSelectedForeStateImage(ControlStateType stateType);

    /** ���ò���ѡ��ʱ��ǰ��ͼƬ
     * @param[in] stateType Ҫ���ú���״̬�µ�ǰ��ͼƬ
     * @param[in] strImage ͼƬλ��
     */
    void SetPartSelectedForeStateImage(ControlStateType stateType, const std::wstring& strImage);

    /** ��������ѡʱ���¼������� SupportCheckedMode() ����Ϊtrue��ʱ�򣬻�������¼���
     * @param [in] callback ��ѡ��ʱ�����Ļص�����
     */
    void AttachChecked(const EventCallback& callback) { this->AttachEvent(kEventChecked, callback); }

    /** ����ȡ����ѡʱ���¼������� SupportCheckedMode() ����Ϊtrue��ʱ�򣬻�������¼���
     * @param [in] callback ȡ��ѡ��ʱ�����Ļص�����
     */
    void AttachUnCheck(const EventCallback& callback) { this->AttachEvent(kEventUnCheck, callback); }

protected:
    /** �ڲ�����ѡ��״̬
    */
    void PrivateSetSelected(bool bSelected);

    /** �ڲ����ù�ѡ״̬
    */
    void PrivateSetChecked(bool bChecked);

    /** ѡ��״̬�仯�¼�(m_bSelected���������仯)
    */
    virtual void OnPrivateSetSelected() {}

    /** ��ѡ״̬�仯�¼�(m_bChecked���������仯)
    */
    virtual void OnPrivateSetChecked() {}

private:
    //ѡ��״̬
    bool m_bSelected;

    //�Ƿ����Ȼ���Normal״̬
    bool m_bPaintNormalFirst;

    //ѡ��״̬���ı���ɫ
    UiString m_dwSelectedTextColor;

    //ѡ��״̬���ı���ɫ
    StateColorMap* m_pSelectedTextColorMap;

    //ѡ��״̬�ı�����ɫ
    StateColorMap* m_pSelectedColorMap;

private: //����̬ѡ��[ȫ��ѡ�񡢲���ѡ��δѡ��]/��ѡģʽ���ֹ��ܵı�����

    //�Ƿ�Ϊ����ѡ��ֻӰ��ѡ��״̬�»����ĸ�ͼƬ����ҵ����Ӱ�죩
    bool m_bPartSelected;

    //�Ƿ��Ѿ�����Check״̬������ SupportCheckedMode() ����Ϊtrue��ʱ�������壩
    bool m_bChecked;

    //CheckBoxͼ�����ڵľ��Σ����� SupportCheckedMode() ����Ϊtrue��ʱ�������壩
    UiRect* m_pCheckBoxImageRect;

    /** ��ѡ���ʱ���Ƿ��Զ���ѡ�����ǵ�m_bSelected�仯��ʱ��ͬ���޸�m_bChecked������ֵ��ͬ
    *   ����m_bChecked�仯��ʱ�򣬲���ͬ����m_bSelected
    */
    bool m_bAutoCheckSelect;
};

template<typename InheritType>
CheckBoxTemplate<InheritType>::CheckBoxTemplate() : 
    m_bSelected(false), 
    m_bPaintNormalFirst(false), 
    m_dwSelectedTextColor(), 
    m_pSelectedTextColorMap(nullptr),
    m_pSelectedColorMap(nullptr),
    m_bPartSelected(false),
    m_bChecked(false),
    m_pCheckBoxImageRect(nullptr),
    m_bAutoCheckSelect(false)
{
}

template<typename InheritType>
CheckBoxTemplate<InheritType>::~CheckBoxTemplate()
{
    if (m_pSelectedTextColorMap != nullptr) {
        delete m_pSelectedTextColorMap;
        m_pSelectedTextColorMap = nullptr;
    }
    if (m_pSelectedColorMap != nullptr) {
        delete m_pSelectedColorMap;
        m_pSelectedColorMap = nullptr;
    }
    if (m_pCheckBoxImageRect != nullptr) {
        delete m_pCheckBoxImageRect;
        m_pCheckBoxImageRect = nullptr;
    }
}

template<typename InheritType>
inline std::wstring CheckBoxTemplate<InheritType>::GetType() const { return DUI_CTR_CHECKBOX; }

template<>
inline std::wstring CheckBoxTemplate<Box>::GetType() const { return DUI_CTR_CHECKBOXBOX; }

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"selected") {
        Selected(strValue == L"true", true);
    }
    else if ((strName == L"normal_first") || (strName == L"normalfirst")) {
        SetPaintNormalFirst(strValue == L"true");
    }
    else if ((strName == L"selected_normal_image") || (strName == L"selectednormalimage")) {
        SetSelectedStateImage(kControlStateNormal, strValue);
    }
    else if ((strName == L"selected_hot_image") || (strName == L"selectedhotimage")) {
        SetSelectedStateImage(kControlStateHot, strValue);
    }
    else if ((strName == L"selected_pushed_image") || (strName == L"selectedpushedimage")) {
        SetSelectedStateImage(kControlStatePushed, strValue);
    }
    else if ((strName == L"selected_disabled_image") || (strName == L"selecteddisabledimage")) {
        SetSelectedStateImage(kControlStateDisabled, strValue);
    }
    else if ((strName == L"selected_fore_normal_image") || (strName == L"selectedforenormalimage")) {
        SetSelectedForeStateImage(kControlStateNormal, strValue);
    }
    else if ((strName == L"selected_fore_hot_image") || (strName == L"selectedforehotimage")) {
        SetSelectedForeStateImage(kControlStateHot, strValue);
    }
    else if ((strName == L"selected_fore_pushed_image") || (strName == L"selectedforepushedimage")) {
        SetSelectedForeStateImage(kControlStatePushed, strValue);
    }
    else if ((strName == L"selected_fore_disabled_image") || (strName == L"selectedforedisabledimage")) {
        SetSelectedForeStateImage(kControlStateDisabled, strValue);
    }
    else if (strName == L"part_selected_normal_image") {
        SetPartSelectedStateImage(kControlStateNormal, strValue);
    }
    else if (strName == L"part_selected_hot_image") {
        SetPartSelectedStateImage(kControlStateHot, strValue);
    }
    else if (strName == L"part_selected_pushed_image") {
        SetPartSelectedStateImage(kControlStatePushed, strValue);
    }
    else if (strName == L"part_selected_disabled_image") {
        SetPartSelectedStateImage(kControlStateDisabled, strValue);
    }
    else if (strName == L"part_selected_fore_normal_image") {
        SetPartSelectedForeStateImage(kControlStateNormal, strValue);
    }
    else if (strName == L"part_selected_fore_hot_image") {
        SetPartSelectedForeStateImage(kControlStateHot, strValue);
    }
    else if (strName == L"part_selected_fore_pushed_image") {
        SetPartSelectedForeStateImage(kControlStatePushed, strValue);
    }
    else if (strName == L"part_selected_fore_disabled_image") {
        SetPartSelectedForeStateImage(kControlStateDisabled, strValue);
    }
    else if ((strName == L"selected_text_color") || (strName == L"selectedtextcolor")) {
        SetSelectedTextColor(strValue);
    }
    else if ((strName == L"selected_normal_text_color") || (strName == L"selectednormaltextcolor")) {
        SetSelectedStateTextColor(kControlStateNormal, strValue);
    }
    else if ((strName == L"selected_hot_text_color") || (strName == L"selectedhottextcolor")) {
        SetSelectedStateTextColor(kControlStateHot, strValue);
    }
    else if ((strName == L"selected_pushed_text_color") || (strName == L"selectedpushedtextcolor")) {
        SetSelectedStateTextColor(kControlStatePushed, strValue);
    }
    else if ((strName == L"selected_disabled_text_color") || (strName == L"selecteddisabledtextcolor")) {
        SetSelectedStateTextColor(kControlStateDisabled, strValue);
    }
    else if ((strName == L"selected_normal_color") || (strName == L"selectednormalcolor")) {
        SetSelectedStateColor(kControlStateNormal, strValue);
    }
    else if ((strName == L"selected_hot_color") || (strName == L"selectedhotcolor")) {
        SetSelectedStateColor(kControlStateHot, strValue);
    }
    else if ((strName == L"selected_pushed_color") || (strName == L"selectedpushedcolor")) {
        SetSelectedStateColor(kControlStatePushed, strValue);
    }
    else if ((strName == L"selected_disabled_color") || (strName == L"selecteddisabledcolor")) {
        SetSelectedStateColor(kControlStateDisabled, strValue);
    }
    else if ((strName == L"switch_select") || (strName == L"switchselect")) {
        Selected(!IsSelected());
    }
    else if (strName == L"auto_check_select") {
        SetAutoCheckSelect(strValue == L"true");
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

template<typename InheritType>
bool CheckBoxTemplate<InheritType>::ButtonUp(const EventArgs& msg)
{
    bool bRet = __super::ButtonUp(msg);
    bool bCheckedMode = SupportCheckedMode();
    if (bCheckedMode && (m_pCheckBoxImageRect != nullptr)) {
        if (!this->IsEnabled()) {
            return bRet;
        }
        UiRect pos = this->GetPos();
        UiPoint pt(msg.ptMouse);
        pt.Offset(this->GetScrollOffsetInScrollBox());
        if (!pos.ContainsPt(pt) || !m_pCheckBoxImageRect->ContainsPt(pt)) {
            return bRet;
        }

        //ȷ�ϵ����CheckBoxͼ�����棬�ı乴ѡ״̬(��������)
        SetChecked(!IsChecked(), true);
    }
    return bRet;
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetChecked(bool bChecked, bool bTriggerEvent)
{
    if (m_bChecked == bChecked) {
        return;
    }
    PrivateSetChecked(bChecked);
    if (bTriggerEvent) {
        if (bChecked) {
            this->SendEvent(kEventChecked);
        }
        else {
            this->SendEvent(kEventUnCheck);
        }
    }
    this->Invalidate();    
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::Activate()
{
    if (!this->IsActivatable()) {
        return;
    }
    Selected(!m_bSelected, true);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PrivateSetSelected(bool bSelected)
{
    bool bChanged = m_bSelected != bSelected;
    if (bChanged) {
        m_bSelected = bSelected;
    }
    if (!bSelected && m_bPartSelected) {
        //��ѡ��״̬ʱ���Բ���ѡ���Ǹ�λ
        m_bPartSelected = false;
    }
    if (bChanged) {
        OnPrivateSetSelected();
    }
    if (IsAutoCheckSelect()) {
        //�Զ�ͬ����Check����
        PrivateSetChecked(m_bSelected);
    }
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PrivateSetChecked(bool bChecked)
{
    bool bChanged = m_bChecked != bChecked;
    if (bChanged) {
        m_bChecked = bChecked;
        OnPrivateSetChecked();
    }
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelected(bool bSelected)
{ 
    PrivateSetSelected(bSelected);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::Selected(bool bSelected, bool bTriggerEvent)
{
    if (m_bSelected == bSelected) {
        return;
    }
    PrivateSetSelected(bSelected);
    if (bTriggerEvent) {
        if (bSelected) {
            this->SendEvent(kEventSelect);
        }
        else {
            this->SendEvent(kEventUnSelect);
        }
    }
    this->Invalidate();
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetPartSelected(bool bPartSelected)
{ 
    if (m_bPartSelected != bPartSelected) {
        m_bPartSelected = bPartSelected;
        this->Invalidate();
    }
}

template<typename InheritType>
bool CheckBoxTemplate<InheritType>::IsPartSelected() const
{
    return m_bPartSelected;
}

template<typename InheritType>
bool CheckBoxTemplate<InheritType>::HasHotState()
{
    if (__super::HasHotState()) {
        return true;
    }
    if ((m_pSelectedColorMap != nullptr) && m_pSelectedColorMap->HasHotColor()) {
        return true;
    }
    if ((m_pSelectedTextColorMap != nullptr) && m_pSelectedTextColorMap->HasHotColor()) {
        return true;
    }
    return false;
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetBorderColor(ControlStateType stateType) const
{
    if (this->IsSelected()) {
        std::wstring borderColor = __super::GetBorderColor(kControlStatePushed);
        if (!borderColor.empty()) {
            return borderColor;
        }
    }
    return __super::GetBorderColor(stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::ClearStateImages()
{
    if (m_pCheckBoxImageRect != nullptr) {
        delete m_pCheckBoxImageRect;
        m_pCheckBoxImageRect = nullptr;
    }
    __super::ClearStateImages();
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintStateColors(IRender* pRender)
{
    if (!IsSelected() || !CanPaintSelectedColors()) {
        __super::PaintStateColors(pRender);
        return;
    }

    if (m_pSelectedColorMap == nullptr) {
        if (IsPaintNormalFirst()) {
            this->PaintStateColor(pRender, this->GetPaintRect(), this->GetState());
        }
    }
    else {
        if (IsPaintNormalFirst() && !m_pSelectedColorMap->HasStateColors()) {
            this->PaintStateColor(pRender, this->GetPaintRect(), this->GetState());
        }
        else {
            m_pSelectedColorMap->PaintStateColor(pRender, this->GetPaintRect(), this->GetState());
        }
    }
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintStateImages(IRender* pRender)
{
    bool bCheckedMode = SupportCheckedMode();
    if (bCheckedMode && (m_pCheckBoxImageRect == nullptr)) {
        m_pCheckBoxImageRect = new UiRect;
    }

    bool isSelectNone = false;
    if (bCheckedMode) {
        //���SupportCheckedMode()Ϊtrue����IsChecked()�ж��Ƿ���ʾѡ��״̬��ͼƬ
        if (!IsChecked()) {
            isSelectNone = true;
        }
    }
    else {
        //���SupportCheckedMode()Ϊfalse����IsSelected()�ж��Ƿ���ʾѡ��״̬��ͼƬ
        if (!IsSelected()) {
            isSelectNone = true;
        }
    }

    if (isSelectNone) {
        //δѡ��״̬
        this->PaintStateImage(pRender, kStateImageBk, this->GetState(), L"", m_pCheckBoxImageRect);
        this->PaintStateImage(pRender, kStateImageFore, this->GetState(), L"", m_pCheckBoxImageRect);
        return;
    }

    if (this->IsPartSelected()) {
        //����ѡ��״̬
        bool bPainted = false;
        if (this->HasStateImage(kStateImagePartSelectedBk)) {
            this->PaintStateImage(pRender, kStateImagePartSelectedBk, this->GetState(), L"", m_pCheckBoxImageRect);
            bPainted = true;
        }
        if (this->HasStateImage(kStateImagePartSelectedFore)) {
            this->PaintStateImage(pRender, kStateImagePartSelectedFore, this->GetState(), L"", m_pCheckBoxImageRect);
            bPainted = true;
        }
        if (bPainted) {
            //����Ѿ������˲���ѡ��״̬������
            return;
        }
    }

    //ȫ��ѡ��״̬
    if (IsPaintNormalFirst() && !this->HasStateImage(kStateImageSelectedBk)) {
        this->PaintStateImage(pRender, kStateImageBk, this->GetState(), L"", m_pCheckBoxImageRect);
    }
    else {
        this->PaintStateImage(pRender, kStateImageSelectedBk, this->GetState(), L"", m_pCheckBoxImageRect);
    }

    if (IsPaintNormalFirst() && !this->HasStateImage(kStateImageSelectedFore)) {
        this->PaintStateImage(pRender, kStateImageFore, this->GetState(), L"", m_pCheckBoxImageRect);
    }
    else {
        this->PaintStateImage(pRender, kStateImageSelectedFore, this->GetState(), L"", m_pCheckBoxImageRect);
    }
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintText(IRender* pRender)
{
    if (!IsSelected()) {
        __super::PaintText(pRender);
        return;
    }
    std::wstring textValue = this->GetText();
    if (textValue.empty() || (pRender == nullptr)) {
        return;
    }
    UiRect rc = this->GetRect();
    UiPadding rcPadding = this->GetControlPadding();
    rc.Deflate(rcPadding);
    rc.Deflate(this->GetTextPadding());

    auto stateType = this->GetState();
    std::wstring clrColor = GetPaintSelectedStateTextColor(this->GetState(), stateType);
    if (clrColor.empty()) {
        clrColor = m_dwSelectedTextColor.empty() ? this->GetPaintStateTextColor(this->GetState(), stateType) : m_dwSelectedTextColor.c_str();
    }
    UiColor dwClrColor = this->GetUiColor(clrColor);

    uint32_t uTextStyle = this->GetTextStyle();
    if (this->IsSingleLine()) {        
        uTextStyle |= TEXT_SINGLELINE;        
    }
    else {
        uTextStyle &= ~TEXT_SINGLELINE;
    }
    this->SetTextStyle(uTextStyle, false);

    if (this->GetAnimationManager().GetAnimationPlayer(AnimationType::kAnimationHot)) {
        if ((stateType == kControlStateNormal || stateType == kControlStateHot)
            && !GetSelectedStateTextColor(kControlStateHot).empty()) {
            std::wstring clrStateColor = GetSelectedStateTextColor(kControlStateNormal);
            if (!clrStateColor.empty()) {
                UiColor dwWinColor = this->GetUiColor(clrStateColor);
                pRender->DrawString(rc, textValue, dwWinColor, this->GetFontId(), this->GetTextStyle());
            }

            if (this->GetHotAlpha() > 0) {
                std::wstring textColor = GetSelectedStateTextColor(kControlStateHot);
                if (!textColor.empty()) {
                    UiColor dwTextColor = this->GetUiColor(textColor);
                    pRender->DrawString(rc, textValue, dwTextColor, this->GetFontId(), this->GetTextStyle(), (BYTE)this->GetHotAlpha());
                }
            }

            return;
        }
    }

    pRender->DrawString(rc, textValue, dwClrColor, this->GetFontId(), this->GetTextStyle());
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedStateImage(ControlStateType stateType) const
{
    return this->GetStateImage(kStateImageSelectedBk, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedStateImage(ControlStateType stateType, const std::wstring& strImage)
{
    this->SetStateImage(kStateImageSelectedBk, stateType, strImage);
    this->RelayoutOrRedraw();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedForeStateImage(ControlStateType stateType) const
{
    return this->GetStateImage(kStateImageSelectedFore, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedForeStateImage(ControlStateType stateType, const std::wstring& strImage)
{
    this->SetStateImage(kStateImageSelectedFore, stateType, strImage);
    this->RelayoutOrRedraw();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetPartSelectedStateImage(ControlStateType stateType)
{
    return this->GetStateImage(kStateImagePartSelectedBk, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetPartSelectedStateImage(ControlStateType stateType, const std::wstring& strImage)
{
    this->SetStateImage(kStateImagePartSelectedBk, stateType, strImage);
    this->RelayoutOrRedraw();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetPartSelectedForeStateImage(ControlStateType stateType)
{
    return this->GetStateImage(kStateImagePartSelectedFore, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetPartSelectedForeStateImage(ControlStateType stateType, const std::wstring& strImage)
{
    this->SetStateImage(kStateImagePartSelectedFore, stateType, strImage);
    this->RelayoutOrRedraw();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedTextColor() const
{
    return m_dwSelectedTextColor.c_str();
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedTextColor(const std::wstring& dwTextColor)
{
    m_dwSelectedTextColor = dwTextColor;
    this->Invalidate();
}

template<typename InheritType /*= Control*/>
std::wstring ui::CheckBoxTemplate<InheritType>::GetSelectedStateTextColor(ControlStateType stateType) const
{
    if (m_pSelectedTextColorMap != nullptr) {
        return m_pSelectedTextColorMap->GetStateColor(stateType);
    }
    return std::wstring();
}

template<typename InheritType /*= Control*/>
void ui::CheckBoxTemplate<InheritType>::SetSelectedStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor)
{
    if (m_pSelectedTextColorMap == nullptr) {
        m_pSelectedTextColorMap = new StateColorMap;
        m_pSelectedTextColorMap->SetControl(this);
    }
    m_pSelectedTextColorMap->SetStateColor(stateType, dwTextColor);
    this->Invalidate();
}

template<typename InheritType /*= Control*/>
std::wstring ui::CheckBoxTemplate<InheritType>::GetPaintSelectedStateTextColor(ControlStateType buttonStateType, ControlStateType& stateType) const
{
    stateType = buttonStateType;
    if (stateType == kControlStatePushed && GetSelectedStateTextColor(kControlStatePushed).empty()) {
        stateType = kControlStateHot;
    }
    if (stateType == kControlStateHot && GetSelectedStateTextColor(kControlStateHot).empty()) {
        stateType = kControlStateNormal;
    }
    if (stateType == kControlStateDisabled && GetSelectedStateTextColor(kControlStateDisabled).empty()) {
        stateType = kControlStateNormal;
    }
    return GetSelectedStateTextColor(stateType);
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectStateColor(ControlStateType stateType) const
{
    if (m_pSelectedColorMap != nullptr) {
        return m_pSelectedColorMap->GetStateColor(stateType);
    }
    return std::wstring();
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedStateColor(ControlStateType stateType, const std::wstring& stateColor)
{
    if (m_pSelectedColorMap == nullptr) {
        m_pSelectedColorMap = new StateColorMap;
        m_pSelectedColorMap->SetControl(this);
    }
    m_pSelectedColorMap->SetStateColor(stateType, stateColor);
    this->Invalidate();
}

typedef CheckBoxTemplate<Control> CheckBox;
typedef CheckBoxTemplate<Box> CheckBoxBox;

} // namespace ui

#endif // UI_CONTROL_CHECKBOX_H_