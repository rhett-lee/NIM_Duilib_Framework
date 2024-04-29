#ifndef UI_CORE_UICOLOR_H_
#define UI_CORE_UICOLOR_H_

#pragma once

#include "duilib/Core/UiColors.h"

namespace ui 
{

/** ��ɫֵ�ķ�װ(ARGB��ʽ)
*/
class UILIB_API UiColor
{
public:

    //��ɫֵ����
    typedef uint32_t ARGB;

    UiColor():
        Argb(0)
    {
    }

    UiColor(uint8_t r, uint8_t g, uint8_t b)
    {
        Argb = MakeARGB(255, r, g, b);
    }

    UiColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
    {
        Argb = MakeARGB(a, r, g, b);
    }

    explicit UiColor(ARGB argb)
    {
        Argb = argb;
    }

    explicit UiColor(int32_t argb)
    {
        Argb = (ARGB)argb;
    }

    /** ��ȡ��ɫ��Alphaֵ
    */
    uint8_t GetAlpha() const { return (uint8_t)(Argb >> AlphaShift); }

    /** ��ȡ��ɫ��Alphaֵ
    */
    uint8_t GetA() const { return (uint8_t)(Argb >> AlphaShift); }

    /** ��ȡ��ɫ��Redֵ
    */
    uint8_t GetRed() const { return (uint8_t)(Argb >> RedShift); }

    /** ��ȡ��ɫ��Redֵ
    */
    uint8_t GetR() const { return (uint8_t)(Argb >> RedShift); }

    /** ��ȡ��ɫ��Greenֵ
    */
    uint8_t GetGreen() const { return (uint8_t)(Argb >> GreenShift); }

    /** ��ȡ��ɫ��Greenֵ
    */
    uint8_t GetG() const { return (uint8_t)(Argb >> GreenShift); }

    /** ��ȡ��ɫ��Blueֵ
    */
    uint8_t GetBlue() const { return (uint8_t)(Argb >> BlueShift); }

    /** ��ȡ��ɫ��Blueֵ
    */
    uint8_t GetB() const { return (uint8_t)(Argb >> BlueShift); }

    /** ��ȡ��ɫ��ARGBֵ
    */
    ARGB GetARGB() const { return Argb; }

    /** ��ɫֵ�Ƿ�Ϊ��ֵ
    */
    bool IsEmpty() const { return Argb == 0; }

    /** ������ɫ��ARGBֵ
    */
    void SetARGB(ARGB argb) { Argb = argb; }

    /** ��COLORREF��ɫֵ������ɫ��COLORREF������RGBֵ������Aֵ��
    */
    void SetFromCOLORREF(uint32_t rgb)
    {
        Argb = MakeARGB(255, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
    }

    /** ��ARGB��ɫת��ΪCOLORREF��ɫֵ��COLORREF������RGBֵ������Aֵ��
    */
    uint32_t ToCOLORREF() const
    {
        return RGB(GetRed(), GetGreen(), GetBlue());
    }

    /** �ж��Ƿ�������һ������ͬ
    */
    bool Equals(const UiColor& dst) const
    {
        return Argb == dst.Argb;
    }

    /** �ж�����ֵ�Ƿ����
    */
    friend bool operator == (const UiColor& a, const UiColor& b)
    {
        return a.Equals(b);
    }

    /** �ж�����ֵ�Ƿ����
    */
    friend bool operator != (const UiColor& a, const UiColor& b)
    {
        return !a.Equals(b);
    }

    // Shift count and bit mask for A, R, G, B components
    enum
    {
        AlphaShift = 24,
        RedShift   = 16,
        GreenShift = 8,
        BlueShift  = 0
    };

    enum
    {
        AlphaMask = 0xff000000,
        RedMask   = 0x00ff0000,
        GreenMask = 0x0000ff00,
        BlueMask  = 0x000000ff
    };

    // Assemble A, R, G, B values into a 32-bit integer
    static ARGB MakeARGB(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
    {
        return (((ARGB)(b) << BlueShift)  |
                ((ARGB)(g) << GreenShift) |
                ((ARGB)(r) << RedShift)   |
                ((ARGB)(a) << AlphaShift));
    }

private:
    //��ɫֵ
    ARGB Argb;
};

} // namespace ui

#endif // UI_CORE_UICOLOR_H_
