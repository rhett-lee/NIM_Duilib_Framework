#ifndef UI_RENDER_GDIPLUS_FONT_GDI_H_
#define UI_RENDER_GDIPLUS_FONT_GDI_H_

#pragma once

#include "duilib/Render/IRender.h"

namespace ui 
{

/** GDI����ӿڵ�ʵ��
*/
class UILIB_API Font_GDI: public IFont
{
public:
    Font_GDI();
    Font_GDI(const Font_GDI&) = delete;
    Font_GDI& operator=(const Font_GDI&) = delete;
    virtual ~Font_GDI();

    /** ��ʼ������(�ڲ�δ�������С��DPI����Ӧ)
    */
    virtual bool InitFont(const UiFont& fontInfo) override;

    /**@brief ��ȡ������
     */
    virtual const wchar_t* FontName() const override { return m_logFont.lfFaceName; }

    /**@brief ��ȡ�����С
     */
    virtual int FontSize() const override { return -m_logFont.lfHeight; }

    /**@brief �Ƿ�Ϊ����
     */
    virtual bool IsBold() const override { return m_logFont.lfWeight >= FW_BOLD; }

    /**@brief �����»���״̬
     */
    virtual bool IsUnderline() const override { return m_logFont.lfUnderline; }

    /**@brief �����б��״̬
     */
    virtual bool IsItalic() const override { return m_logFont.lfItalic; }

    /**@brief �����ɾ����״̬
     */
    virtual bool IsStrikeOut() const override { return m_logFont.lfStrikeOut; }

public:
    /** ��ȡ������
    */
    HFONT GetFontHandle();

private:
    //������Ϣ
    LOGFONT m_logFont;

    //������
    HFONT m_hFont;
};

} // namespace ui

#endif // UI_RENDER_GDIPLUS_FONT_GDI_H_
