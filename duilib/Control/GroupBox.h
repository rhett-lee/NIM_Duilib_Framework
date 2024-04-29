#ifndef UI_CONTROL_GROUPBOX_H_
#define UI_CONTROL_GROUPBOX_H_

#pragma once

#include "duilib/Control/Label.h"
#include "duilib/Box/HBox.h"
#include "duilib/Box/VBox.h"

namespace ui
{

/** ��������
*/
template<typename InheritType>
class UILIB_API GroupBoxTemplate : public LabelTemplate<InheritType>
{
public:
    GroupBoxTemplate();
	virtual ~GroupBoxTemplate();
		
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
    virtual void PaintText(IRender* pRender) override;

    /** ����Բ�Ǵ�С
     */
    void SetCornerSize(UiSize cxyRound, bool bNeedDpiScale);

    /** �����������
    */
    void SetLineWidth(int32_t nLineWidth, bool bNeedDpiScale);

    /** ����������ɫ
    */
    void SetLineColor(const std::wstring& lineColor);

private:
    /** ��ȡһ��͸���ȵ���ɫ
    */
    UiColor GetFadeColor(UiColor color, uint8_t nFade) const;

private:
    //�������
    int32_t m_nLineWidth;

    //Բ�Ǵ�С��Ĭ��Ϊֱ��, ��Բ�ǣ�
    UiSize m_cornerSize;

    //������ɫ
    UiString m_lineColor;
};

template<typename InheritType>
GroupBoxTemplate<InheritType>::GroupBoxTemplate(): m_nLineWidth(0)
{
    SetAttribute(L"text_align", L"top,left");
    SetAttribute(L"text_padding", L"8,0,0,0");
}

template<typename InheritType>
GroupBoxTemplate<InheritType>::~GroupBoxTemplate()
{
}

template<typename InheritType>
inline std::wstring GroupBoxTemplate<InheritType>::GetType() const { return L"GroupBoxTemplate"; }

template<>
inline std::wstring GroupBoxTemplate<Box>::GetType() const { return DUI_CTR_GROUP_BOX; }

template<>
inline std::wstring GroupBoxTemplate<HBox>::GetType() const { return DUI_CTR_GROUP_HBOX; }

template<>
inline std::wstring GroupBoxTemplate<VBox>::GetType() const { return DUI_CTR_GROUP_VBOX; }

template<typename InheritType>
void GroupBoxTemplate<InheritType>::SetCornerSize(UiSize cxyRound, bool bNeedDpiScale)
{
    int32_t cx = cxyRound.cx;
    int32_t cy = cxyRound.cy;
    ASSERT(cx >= 0);
    ASSERT(cy >= 0);
    if ((cx < 0) || (cy < 0)) {
        return;
    }
    //��������Ҫôͬʱ����0��Ҫôͬʱ����0�����������Ч
    ASSERT(((cx > 0) && (cy > 0)) || ((cx == 0) && (cy == 0)));
    if (cx == 0) {
        if (cy != 0) {
            return;
        }
    }
    else {
        if (cy == 0) {
            return;
        }
    }
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleSize(cxyRound);
    }
    if (m_cornerSize != cxyRound) {
        m_cornerSize = cxyRound;
        this->Invalidate();
    }
}

template<typename InheritType>
void GroupBoxTemplate<InheritType>::SetLineWidth(int32_t nLineWidth, bool bNeedDpiScale)
{
    if (nLineWidth < 0) {
        nLineWidth = 0;
    }
    if (bNeedDpiScale) {
        GlobalManager::Instance().Dpi().ScaleInt(nLineWidth);
    }
    if (m_nLineWidth != nLineWidth) {
        m_nLineWidth = nLineWidth;
        this->Invalidate();
    }
}

template<typename InheritType>
void GroupBoxTemplate<InheritType>::SetLineColor(const std::wstring& lineColor)
{
    if (m_lineColor != lineColor) {
        m_lineColor = lineColor;
        this->Invalidate();
    }
}

template<typename InheritType>
UiColor GroupBoxTemplate<InheritType>::GetFadeColor(UiColor color, uint8_t nFade) const
{
    color = UiColor(nFade, color.GetR() * nFade / 255, color.GetG() * nFade / 255, color.GetB() * nFade / 255);
    return color;
}

template<typename InheritType>
void GroupBoxTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"corner_size") {
        //Բ�Ǵ�С
        UiSize cxyRound;
        AttributeUtil::ParseSizeValue(strValue.c_str(), cxyRound);
        this->SetCornerSize(cxyRound, true);
    }
    else if (strName == L"line_width") {
        //�������
        ASSERT(_wtoi(strValue.c_str()) >= 0);
        this->SetLineWidth(_wtoi(strValue.c_str()), true);
    }
    else if (strName == L"line_color") {
        //������ɫ
        this->SetLineColor(strValue);
    }
    else if (strName == L"text") {
        //�����ı�����
        __super::SetAttribute(strName, strValue);
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

template<typename InheritType>
void GroupBoxTemplate<InheritType>::PaintText(IRender* pRender)
{
    //�Ȼ�������
    __super::PaintText(pRender);

    if (pRender == nullptr) {
        return;
    }

    UiPadding rcPadding = this->GetControlPadding();
    std::wstring textValue = this->GetText();//�ı�����
    UiRect drawTextRect;//�ı��Ļ�������
    bool hasClip = false;
    if (!textValue.empty()) {
        UiRect textRect = pRender->MeasureString(textValue, this->GetFontId(), 0, 0);
        drawTextRect = this->GetRect();
        drawTextRect.Deflate(rcPadding);
        drawTextRect.Deflate(this->GetTextPadding());
        drawTextRect.right = drawTextRect.left + textRect.Width();
        drawTextRect.bottom = drawTextRect.top + textRect.Height();

        //���ü������򣬱��������������
        pRender->SetClip(drawTextRect, false);
        hasClip = true;
    }

    //�����ֵײ����Ʊ߿�
    int32_t nLineWidth = m_nLineWidth;
    if (nLineWidth <= 0) {
        nLineWidth = GlobalManager::Instance().Dpi().GetScaleInt(1);
    }
    UiSize cornerSize = m_cornerSize;
    UiColor lineColor;
    if (!m_lineColor.empty()) {
        lineColor = this->GetUiColor(m_lineColor.c_str());
    }
    if (lineColor.GetARGB() == 0) {
        lineColor = GetFadeColor(UiColor(UiColors::Gray), 96);
    }

    int32_t nShadowOffset = 1;//��Ӱƫ��
    UiRect rc = this->GetRect();
    rc.Deflate(rcPadding);
    rc.Deflate(nLineWidth / 2 + nShadowOffset, nLineWidth/2 + nShadowOffset);

    if (drawTextRect.Height() > 0) {
        //���������ı��м�
        rc.top += (drawTextRect.Height() / 2 - nLineWidth / 2);
    }

    if ((cornerSize.cx > 0) && (cornerSize.cy > 0)) {
        //�Ȼ��Ƹ���ӰЧ��
        if (nShadowOffset > 0) {
            UiColor fadeColor = GetFadeColor(lineColor, 24);
            UiRect fadeRect = rc;
            fadeRect.Inflate(nShadowOffset, nShadowOffset);
            pRender->DrawRoundRect(fadeRect, cornerSize, fadeColor, nLineWidth);
        }
        //����Բ�Ǿ��α߿�
        pRender->DrawRoundRect(rc, cornerSize, lineColor, nLineWidth);
    }
    else {
        //�Ȼ��Ƹ���ӰЧ��
        if (nShadowOffset > 0) {
            UiColor fadeColor = GetFadeColor(lineColor, 24);
            UiRect fadeRect = rc;
            fadeRect.Inflate(nShadowOffset, nShadowOffset);
            pRender->DrawRect(fadeRect, fadeColor, nLineWidth);
        }
        //���ƾ��α߿�
        pRender->DrawRect(rc, lineColor, nLineWidth);
    }

    if (hasClip) {
        //�ָ���������
        pRender->ClearClip();
    }    
}

/** ��������/��ֱ��������/ˮƽ��������
*/
typedef GroupBoxTemplate<Box>  GroupBox;
typedef GroupBoxTemplate<HBox> GroupHBox;
typedef GroupBoxTemplate<VBox> GroupVBox;

}

#endif // UI_CONTROL_GROUPBOX_H_
