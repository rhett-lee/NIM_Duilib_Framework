#ifndef UI_RENDER_SKIA_FONT_GDI_H_
#define UI_RENDER_SKIA_FONT_GDI_H_

#pragma once

#include "duilib/Render/IRender.h"

class SkFont;

namespace ui 
{

/** Skia����ӿڵ�ʵ��
*/
class UILIB_API Font_Skia: public IFont
{
public:
    explicit Font_Skia(IRenderFactory* pRenderFactory);
    Font_Skia(const Font_Skia&) = delete;
    Font_Skia& operator=(const Font_Skia&) = delete;
    virtual ~Font_Skia();

    /** ��ʼ������(�ڲ�δ�������С��DPI����Ӧ)
    */
    virtual bool InitFont(const UiFont& fontInfo) override;

    /**@brief ��ȡ������
     */
    virtual const wchar_t* FontName() const override { return m_uiFont.m_fontName.c_str(); }

    /**@brief ��ȡ�����С
     */
    virtual int FontSize() const override { return m_uiFont.m_fontSize; }

    /**@brief �Ƿ�Ϊ����
     */
    virtual bool IsBold() const override { return m_uiFont.m_bBold; }

    /**@brief �����»���״̬
     */
    virtual bool IsUnderline() const override { return m_uiFont.m_bUnderline; }

    /**@brief �����б��״̬
     */
    virtual bool IsItalic() const override { return m_uiFont.m_bItalic; }

    /**@brief �����ɾ����״̬
     */
    virtual bool IsStrikeOut() const override { return m_uiFont.m_bStrikeOut; }

public:
    /** ��ȡ������
    */
    const SkFont* GetFontHandle();

private:
    //������Ϣ
    UiFont m_uiFont;

    //������
    SkFont* m_skFont;

    //��Ⱦ�ӿ�
    IRenderFactory* m_pRenderFactory;
};

} // namespace ui

#endif // UI_RENDER_GDIPLUS_FONT_GDI_H_
