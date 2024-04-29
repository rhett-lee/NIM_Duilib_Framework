#ifndef UI_CONTROL_LABEL_H_
#define UI_CONTROL_LABEL_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Core/Box.h"
#include "duilib/Core/Window.h"
#include "duilib/Core/StateColorMap.h"
#include "duilib/Image/Image.h"
#include "duilib/Utils/StringUtil.h"
#include "duilib/Utils/AttributeUtil.h"
#include "duilib/Render/IRender.h"
#include "duilib/Animation/AnimationManager.h"
#include "duilib/Animation/AnimationPlayer.h"

namespace ui
{

/** ��ǩ�ؼ���ģ�壩��������ʾ�ı�
*/
template<typename InheritType = Control>
class UILIB_API LabelTemplate : public InheritType
{
public:
	LabelTemplate();
    virtual ~LabelTemplate();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual std::wstring GetText() const;
	virtual std::string GetUTF8Text() const;
	virtual void SetText(const std::wstring& strText);
	virtual void SetUTF8Text(const std::string& strText);
	virtual void SetTextId(const std::wstring& strTextId);
	virtual void SetUTF8TextId(const std::string& strTextId);
	virtual bool HasHotState() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void PaintText(IRender* pRender) override;
	virtual void SetPos(UiRect rc) override;
    virtual std::wstring GetToolTipText() const override;

    /** �����ı������С����͸ߣ�
     *  @param [in] szAvailable ���ô�С���������ڱ߾࣬��������߾�
     *  @return �ؼ����ı������С�������ڱ߾�(Box)����������߾�
     */
    virtual UiSize EstimateText(UiSize szAvailable) override;

    /** �ָ�Ĭ�ϵ��ı���ʽ
    */
    void SetDefaultTextStyle(bool bRedraw);

    /**
     * @brief �����ı���ʽ
     * @param[in] uStyle Ҫ���õ���ʽ
     * @return ��
     */
	void SetTextStyle(UINT uStyle, bool bRedraw);

	/**
     * @brief ��ȡ�ı���ʽ
     * @return �����ı���ʽ
     */
	UINT GetTextStyle() const;

	/**
     * @brief ��ȡָ��״̬�µ��ı���ɫ
     * @param[in] stateType Ҫ��ȡ��״̬��־
     * @return ����ָ��״̬�µ��ı���ɫ
     */
	std::wstring GetStateTextColor(ControlStateType stateType) const;

	/**
     * @brief ����ָ��״̬�µ��ı���ɫ
     * @param[in] stateType Ҫ���õ�״̬��־
     * @param[in] dwTextColor Ҫ���õ�״̬��ɫ�ַ�������ֵ������ global.xml �д���
     * @return ��
     */
	void SetStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor);

    /**
     * @brief ��ȡָ��״̬�µ�ʵ�ʱ���Ⱦ�ı���ɫ
     * @param[in] buttonStateType Ҫ��ȡ����״̬�µ���ɫ
     * @param[out] stateType ʵ�ʱ���Ⱦ��״̬
     * @return ������ɫ�ַ�������ֵ�� global.xml �ж���
     */
	std::wstring GetPaintStateTextColor(ControlStateType buttonStateType, ControlStateType& stateType);

    /** ��ȡ��ǰ����ID
     * @return ��������ID��������ID�� global.xml �б�ʶ
     */
	std::wstring GetFontId() const;

    /** ���õ�ǰ����ID
     * @param[in] strFontId Ҫ���õ�����ID��������ID������ global.xml �д���
     */
	void SetFontId(const std::wstring& strFontId);

    /**
     * @brief ��ȡ�����ڱ߾�
     * @return �������ֵ��ڱ߾���Ϣ
     */
	UiPadding GetTextPadding() const;

    /**
     * @brief ���������ڱ߾���Ϣ
     * @param[in] padding �ڱ߾���Ϣ
     * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
     */
	void SetTextPadding(UiPadding padding, bool bNeedDpiScale = true);

    /**
     * @brief �ж��Ƿ��ǵ���ģʽ
     * @return ���� true ��ʾ����ģʽ������Ϊ false
     */
	bool IsSingleLine() const;

    /**
     * @brief ����Ϊ��������ģʽ
     * @param[in] bSingleLine Ϊ true ʱΪ����ģʽ������Ϊ false
     * @return ��
     */
	void SetSingleLine(bool bSingleLine);

    /**
    * @brief ��������������ؼ���ʾ����ʾ�ı��Ƿ�ʡ�Ժų���ʱ����ʾ
    * @param[in] bAutoShow true ʡ�Ժų��ֲ���ʾ false �����κο���
    * @return ��
    */
	void SetAutoToolTip(bool bAutoShow);

protected:
    /** ����Ƿ���Ҫ�Զ���ʾToolTip
    */
	void CheckShowToolTip();

    /** �������ֵ�ʵ�ֺ���
    * @param [in] rc ʵ�ʻ������򣬲������ڱ߾ࣨ���ɵ��÷���ȥ�ڱ߾ࣩ
    * @param [in] pRender ��Ⱦ�ӿ�
    */
    void DoPaintText(const UiRect& rc, IRender* pRender);

private:
	UiString m_sFontId;
    UiString m_sAutoShowTooltipCache;
	UINT	m_uTextStyle;
	bool    m_bSingleLine;
	bool    m_bAutoShowToolTip;
	UiPadding16	m_rcTextPadding;
    UiString m_sText;
	UiString m_sTextId;
	StateColorMap* m_pTextColorMap;
};

template<typename InheritType>
LabelTemplate<InheritType>::LabelTemplate() :
    m_sFontId(),
    m_uTextStyle(TEXT_LEFT | TEXT_VCENTER | TEXT_END_ELLIPSIS | TEXT_NOCLIP | TEXT_SINGLELINE),
    m_bSingleLine(true),
    m_bAutoShowToolTip(false),
    m_rcTextPadding(),
    m_sText(),
    m_sTextId(),
    m_pTextColorMap(nullptr)
{
    if (dynamic_cast<Box*>(this)) {
        this->SetFixedWidth(UiFixedInt::MakeStretch(), false, false);
        this->SetFixedHeight(UiFixedInt::MakeStretch(), false, false);
    }
    else {
        this->SetFixedWidth(UiFixedInt::MakeAuto(), false, false);
        this->SetFixedHeight(UiFixedInt::MakeAuto(), false, false);
    }
}

template<typename InheritType>
LabelTemplate<InheritType>::~LabelTemplate()
{
    if (m_pTextColorMap != nullptr) {
        delete m_pTextColorMap;
        m_pTextColorMap = nullptr;
    }
}

template<typename InheritType>
inline std::wstring LabelTemplate<InheritType>::GetType() const { return DUI_CTR_LABEL; }

template<>
inline std::wstring LabelTemplate<Box>::GetType() const { return DUI_CTR_LABELBOX; }

template<typename InheritType>
void LabelTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if ((strName == L"text_align") || (strName == L"align")) {
        if (strValue.find(L"left") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_CENTER | TEXT_RIGHT);
            m_uTextStyle |= TEXT_LEFT;
        }
        //center������������壬�����Ա��ּ����ԣ��µ�������"hcenter"
        size_t centerPos = strValue.find(L"center");
        if (centerPos != std::wstring::npos) {
            bool isCenter = true;
            size_t vCenterPos = strValue.find(L"vcenter");
            if (vCenterPos != std::wstring::npos) {
                if ((vCenterPos + 1) == centerPos) {
                    isCenter = false;
                }
            }
            if (isCenter) {
                m_uTextStyle &= ~(TEXT_LEFT | TEXT_RIGHT);
                m_uTextStyle |= TEXT_CENTER;
            }
        }
        if (strValue.find(L"hcenter") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_LEFT | TEXT_RIGHT);
            m_uTextStyle |= TEXT_CENTER;
        }
        if (strValue.find(L"right") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_LEFT | TEXT_CENTER);
            m_uTextStyle |= TEXT_RIGHT;
        }
        if (strValue.find(L"top") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_BOTTOM | TEXT_VCENTER);
            m_uTextStyle |= TEXT_TOP;
        }
        if (strValue.find(L"vcenter") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_TOP | TEXT_BOTTOM);
            m_uTextStyle |= TEXT_VCENTER;
        }
        if (strValue.find(L"bottom") != std::wstring::npos) {
            m_uTextStyle &= ~(TEXT_TOP | TEXT_VCENTER);
            m_uTextStyle |= TEXT_BOTTOM;
        }
    }
    else if ((strName == L"end_ellipsis") || (strName == L"endellipsis")) {
        if (strValue == L"true") {
            m_uTextStyle |= TEXT_END_ELLIPSIS;
        }
        else {
            m_uTextStyle &= ~TEXT_END_ELLIPSIS;
        }
    }
    else if ((strName == L"path_ellipsis") || (strName == L"pathellipsis")) {
        if (strValue == L"true") {
            m_uTextStyle |= TEXT_PATH_ELLIPSIS;
        }
        else {
            m_uTextStyle &= ~TEXT_PATH_ELLIPSIS;
        }
    }
    else if ((strName == L"single_line") || (strName == L"singleline")) {
        SetSingleLine(strValue == L"true");
    }
    else if ((strName == L"multi_line") || (strName == L"multiline")) {
        SetSingleLine(strValue != L"true");
    }
    else if (strName == L"text") {
        SetText(strValue);
    }
    else if (strName == L"textid") {
        SetTextId(strValue);
    }
    else if ((strName == L"auto_tooltip") || (strName == L"autotooltip")) {
        SetAutoToolTip(strValue == L"true");
    }
    else if (strName == L"font") {
        SetFontId(strValue);
    }
    else if ((strName == L"normal_text_color") || (strName == L"normaltextcolor")) {
        SetStateTextColor(kControlStateNormal, strValue);
    }
    else if ((strName == L"hot_text_color") || (strName == L"hottextcolor")) {
        SetStateTextColor(kControlStateHot, strValue);
    }
    else if ((strName == L"pushed_text_color") || (strName == L"pushedtextcolor")) {
        SetStateTextColor(kControlStatePushed, strValue);
    }
    else if ((strName == L"disabled_text_color") || (strName == L"disabledtextcolor")) {
        SetStateTextColor(kControlStateDisabled, strValue);
    }
    else if ((strName == L"text_padding") || (strName == L"textpadding")) {
        UiPadding rcTextPadding;
        AttributeUtil::ParsePaddingValue(strValue.c_str(), rcTextPadding);
        SetTextPadding(rcTextPadding);
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetText() const
{
    std::wstring strText = m_sText.c_str();
    if (strText.empty() && !m_sTextId.empty()) {
        strText = GlobalManager::Instance().Lang().GetStringViaID(m_sTextId.c_str());
    }

    return strText;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetAutoToolTip(bool bAutoShow)
{
	m_bAutoShowToolTip = bAutoShow;
	CheckShowToolTip();
}

template<typename InheritType /*= Control*/>
void ui::LabelTemplate<InheritType>::SetPos(UiRect rc)
{
	__super::SetPos(rc);
	CheckShowToolTip();
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetToolTipText() const
{
	std::wstring toolTip = __super::GetToolTipText();
    if (!toolTip.empty()) {
        return toolTip;
    }
    else if (m_bAutoShowToolTip) {
        toolTip = m_sAutoShowTooltipCache.c_str();
    }
	return toolTip;
}

template<typename InheritType>
void LabelTemplate<InheritType>::CheckShowToolTip()
{
    m_sAutoShowTooltipCache.clear();
    if (!m_bAutoShowToolTip || (this->GetWindow() == nullptr)) {
        return;
    }
    auto pRender = this->GetWindow()->GetRender();
    if (pRender == nullptr) {
        return;
    }    
    std::wstring sText = this->GetText();
    if (sText.empty()) {
        return;
    }
    UiRect rc = this->GetRect();
    if (rc.IsEmpty()) {
        return;
    }
    UiPadding rcPadding = this->GetControlPadding();
    rc.Deflate(rcPadding);
    rc.Deflate(this->GetTextPadding());

    if (m_bSingleLine) {
        m_uTextStyle |= TEXT_SINGLELINE;
    }
    else {
        m_uTextStyle &= ~TEXT_SINGLELINE;
    }
    int width = this->GetFixedWidth().GetInt32();
    if (this->GetFixedWidth().IsStretch()) {
        width = 0;
    }
    if (width < 0) {
        width = 0;
    }
    if (!m_bSingleLine && (width == 0)) {
        //�����ı�������ߵ�ʱ�򣬱���ָ�����
        width = rc.Width();
    }

    UiRect rcMessure = pRender->MeasureString(sText, GetFontId(), m_uTextStyle, width);
    if (rc.Width() < rcMessure.Width() || rc.Height() < rcMessure.Height()) {
        m_sAutoShowTooltipCache = sText;
    }
}

template<typename InheritType>
std::string LabelTemplate<InheritType>::GetUTF8Text() const
{
    std::wstring strIn = GetText();
    std::string strOut;
    StringHelper::UnicodeToMBCS(strIn, strOut, CP_UTF8);
    return strOut;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetText(const std::wstring& strText)
{
    if (m_sText == strText) {
        return;
    }
    m_sText = strText;
    this->RelayoutOrRedraw();
	CheckShowToolTip();
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetUTF8Text(const std::string& strText)
{
    std::wstring strOut;
    StringHelper::MBCSToUnicode(strText, strOut, CP_UTF8);
    SetText(strOut);
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextId(const std::wstring& strTextId)
{
    if (m_sTextId == strTextId) {
        return;
    }
    m_sTextId = strTextId;
    this->RelayoutOrRedraw();
    CheckShowToolTip();
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetUTF8TextId(const std::string& strTextId)
{
    std::wstring strOut;
    StringHelper::MBCSToUnicode(strTextId, strOut, CP_UTF8);
    SetTextId(strOut);
}

template<typename InheritType>
bool LabelTemplate<InheritType>::HasHotState()
{
    if (__super::HasHotState()) {
        return true;
    }
    if (m_pTextColorMap != nullptr) {
        return m_pTextColorMap->HasHotColor();
    }
    return false;
}

template<typename InheritType>
UiSize LabelTemplate<InheritType>::EstimateText(UiSize szAvailable)
{
    if (m_bSingleLine) {
        m_uTextStyle |= TEXT_SINGLELINE;
    }
    else {
        m_uTextStyle &= ~TEXT_SINGLELINE;
    }

    int32_t width = szAvailable.cx;
    if (this->GetFixedWidth().IsStretch()) {
        //������������ͣ�ʹ���ⲿ���
        width = CalcStretchValue(this->GetFixedWidth(), szAvailable.cx);
    }
    else if (this->GetFixedWidth().IsInt32()) {
        width = this->GetFixedWidth().GetInt32();
    }
    UiPadding rcTextPadding = this->GetTextPadding();
    UiPadding rcPadding = this->GetControlPadding();
    width -= (rcPadding.left + rcPadding.right);
    width -= (rcTextPadding.left + rcTextPadding.right);
    if (width < 0) {
        width = 0;
    }
    UiSize fixedSize;
    std::wstring textValue = GetText();
    if (!textValue.empty() && (this->GetWindow() != nullptr)) {
        auto pRender = this->GetWindow()->GetRender();
        if (pRender != nullptr) {
            UiRect rect = pRender->MeasureString(textValue, GetFontId(), m_uTextStyle, width);            
            if (this->GetFixedWidth().IsAuto()) {
                fixedSize.cx = rect.Width() + rcTextPadding.left + rcTextPadding.right;
                fixedSize.cx += (rcPadding.left + rcPadding.right);
            }
            if (this->GetFixedHeight().IsAuto()) {
                fixedSize.cy = rect.Height() + rcTextPadding.top + rcTextPadding.bottom;
                fixedSize.cy += (rcPadding.top + rcPadding.bottom);
            }
        }        
    }
    return fixedSize;
}

template<typename InheritType>
void LabelTemplate<InheritType>::PaintText(IRender* pRender)
{
    UiRect rc = this->GetRect();
    rc.Deflate(this->GetControlPadding());
    rc.Deflate(this->GetTextPadding());
    DoPaintText(rc, pRender);
}

template<typename InheritType>
void LabelTemplate<InheritType>::DoPaintText(const UiRect & rc, IRender * pRender)
{
    std::wstring textValue = this->GetText();
    if (textValue.empty() || (pRender == nullptr)) {
        return;
    }

    ControlStateType stateType = this->GetState();
    UiColor dwClrColor = this->GetUiColor(GetPaintStateTextColor(this->GetState(), stateType));

    if (m_bSingleLine) {
        m_uTextStyle |= TEXT_SINGLELINE;
    }
    else {
        m_uTextStyle &= ~TEXT_SINGLELINE;
    }
    std::wstring fontId = GetFontId();
    if (this->GetAnimationManager().GetAnimationPlayer(AnimationType::kAnimationHot)) {
        if ((stateType == kControlStateNormal || stateType == kControlStateHot) && 
            !GetStateTextColor(kControlStateHot).empty()) {
            std::wstring clrColor = GetStateTextColor(kControlStateNormal);
            if (!clrColor.empty()) {
                UiColor dwTextColor = this->GetUiColor(clrColor);
                pRender->DrawString(rc, textValue, dwTextColor, fontId, m_uTextStyle);
            }

            if (this->GetHotAlpha() > 0) {
                std::wstring textColor = GetStateTextColor(kControlStateHot);
                if (!textColor.empty()) {
                    UiColor dwTextColor = this->GetUiColor(textColor);
                    pRender->DrawString(rc, textValue, dwTextColor, fontId, m_uTextStyle, (BYTE)this->GetHotAlpha());
                }
            }

            return;
        }
    }

    pRender->DrawString(rc, textValue, dwClrColor, fontId, m_uTextStyle);
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextStyle(UINT uStyle, bool bRedraw)
{
    m_uTextStyle = uStyle;
    if (m_uTextStyle & TEXT_SINGLELINE) {
        m_bSingleLine = true;
    }
    else {
        m_bSingleLine = false;
    }
    if (bRedraw) {
        this->Invalidate();
    }    
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetDefaultTextStyle(bool bRedraw)
{
    SetTextStyle(TEXT_LEFT | TEXT_VCENTER | TEXT_END_ELLIPSIS | TEXT_NOCLIP | TEXT_SINGLELINE, bRedraw);
}

template<typename InheritType>
UINT LabelTemplate<InheritType>::GetTextStyle() const
{
    return m_uTextStyle;
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetStateTextColor(ControlStateType stateType) const
{
    std::wstring stateColor;
    if (m_pTextColorMap != nullptr) {
        stateColor = m_pTextColorMap->GetStateColor(stateType);
    }
    if (stateColor.empty() && (stateType == kControlStateNormal)) {
        stateColor = GlobalManager::Instance().Color().GetDefaultTextColor();
    }
    if (stateColor.empty() && (stateType == kControlStateDisabled)) {
        stateColor = GlobalManager::Instance().Color().GetDefaultDisabledTextColor();
    }
    return stateColor;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor)
{
    if (stateType == kControlStateHot) {
        this->GetAnimationManager().SetFadeHot(true);
    }
    if (m_pTextColorMap == nullptr) {
        m_pTextColorMap = new StateColorMap;
        m_pTextColorMap->SetControl(this);
    }
    m_pTextColorMap->SetStateColor(stateType, dwTextColor);
    this->Invalidate();
}

template<typename InheritType /*= Control*/>
std::wstring ui::LabelTemplate<InheritType>::GetPaintStateTextColor(ControlStateType buttonStateType, ControlStateType& stateType)
{
    stateType = buttonStateType;
    if (stateType == kControlStatePushed && GetStateTextColor(kControlStatePushed).empty()) {
        stateType = kControlStateHot;
    }
    if (stateType == kControlStateHot && GetStateTextColor(kControlStateHot).empty()) {
        stateType = kControlStateNormal;
    }
    if (stateType == kControlStateDisabled && GetStateTextColor(kControlStateDisabled).empty()) {
        stateType = kControlStateNormal;
    }
    return GetStateTextColor(stateType);
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetFontId() const
{
    return m_sFontId.c_str();
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetFontId(const std::wstring& strFontId)
{
    m_sFontId = strFontId;
    this->Invalidate();
}

template<typename InheritType>
UiPadding LabelTemplate<InheritType>::GetTextPadding() const
{
    return UiPadding(m_rcTextPadding.left, m_rcTextPadding.top, m_rcTextPadding.right, m_rcTextPadding.bottom);
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextPadding(UiPadding padding, bool bNeedDpiScale)
{
    ASSERT((padding.left >= 0) && (padding.top >= 0) && (padding.right >= 0) && (padding.bottom >= 0));
    if ((padding.left < 0) || (padding.top < 0) ||
        (padding.right < 0) || (padding.bottom < 0)) {
        return;
    }
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScalePadding(padding);
    }    
    if (!this->GetTextPadding().Equals(padding)) {
        m_rcTextPadding.left = TruncateToUInt16(padding.left);
        m_rcTextPadding.top = TruncateToUInt16(padding.top);
        m_rcTextPadding.right = TruncateToUInt16(padding.right);
        m_rcTextPadding.bottom = TruncateToUInt16(padding.bottom);
        this->RelayoutOrRedraw();
    }    
}

template<typename InheritType>
bool LabelTemplate<InheritType>::IsSingleLine() const
{
    return m_bSingleLine;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetSingleLine(bool bSingleLine)
{
    if (m_bSingleLine == bSingleLine) {
        return;
    }
    m_bSingleLine = bSingleLine;
    this->Invalidate();
}

typedef LabelTemplate<Control> Label;
typedef LabelTemplate<Box> LabelBox;

}

#endif // UI_CONTROL_LABEL_H_