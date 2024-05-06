#ifndef UI_CORE_UICOLORS_H_
#define UI_CORE_UICOLORS_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <vector>
#include <string>

namespace ui 
{
namespace UiColors
{
    /** ������ɫֵ����(ARGB��ʽ)
    */
    enum
    {
        AliceBlue = 0xFFF0F8FF,     //����˿��,�ӽ�ǳ����ɫ�����ɫ
        AntiqueWhite = 0xFFFAEBD7,  //�Ŷ���
        Aqua = 0xFF00FFFF,          //ǳ��ɫ
        Aquamarine = 0xFF7FFFD4,    //������ʯɫ������ɫ��������ɫ����ɫ֮��
        Azure = 0xFFF0FFFF,         //ε��ɫ��
        Beige = 0xFFF5F5DC,         //��ɫ
        Bisque = 0xFFFFE4C4,        //�ۻ�ɫ
        Black = 0xFF000000,         //��ɫ
        BlanchedAlmond = 0xFFFFEBCD,//����ɫ
        Blue = 0xFF0000FF,          //��ɫ
        BlueViolet = 0xFF8A2BE2,    //��������ɫ
        Brown = 0xFFA52A2A,         //��ɫ����ɫ
        BurlyWood = 0xFFDEB887,     //ʵľɫ
        CadetBlue = 0xFF5F9EA0,     //����ɫ
        Chartreuse = 0xFF7FFF00,    //����ɫ
        Chocolate = 0xFFD2691E,     //�ɿ���ɫ
        Coral = 0xFFFF7F50,         //ɺ��ɫ
        CornflowerBlue = 0xFF6495ED,//����ɫ
        Cornsilk = 0xFFFFF8DC,      //�׳�ɫ
        Crimson = 0xFFDC143C,       //����ɫ��
        Cyan = 0xFF00FFFF,          //��ɫ
        DarkBlue = 0xFF00008B,      //����ɫ
        DarkCyan = 0xFF008B8B,      //����ɫ
        DarkGoldenrod = 0xFFB8860B, //���ƻ�
        DarkGray = 0xFFA9A9A9,      //���ɫ
        DarkGreen = 0xFF006400,     //����ɫ
        DarkKhaki = 0xFFBDB76B,     //������ɫ����ƺ�ɫ
        DarkMagenta = 0xFF8B008B,   //��Ʒ��ɫ�������
        DarkOliveGreen = 0xFF556B2F,//�������
        DarkOrange = 0xFFFF8C00,    //���ɫ
        DarkOrchid = 0xFF9932CC,    //����ɫ
        DarkRed = 0xFF8B0000,       //���ɫ
        DarkSalmon = 0xFFE9967A,    //����ɫ
        DarkSeaGreen = 0xFF8FBC8B,  //���ɫ
        DarkSlateBlue = 0xFF483D8B, //�����ɫ
        DarkSlateGray = 0xFF2F4F4F, //����ɫ
        DarkTurquoise = 0xFF00CED1, //����ʯ��ɫ
        DarkViolet = 0xFF9400D3,    //��������ɫ
        DeepPink = 0xFFFF1493,      //��ۺ�ɫ
        DeepSkyBlue = 0xFF00BFFF,   //������ɫ
        DimGray = 0xFF696969,       //����ɫ
        DodgerBlue = 0xFF1E90FF,    //����ɫ
        Firebrick = 0xFFB22222,     //��שɫ
        FloralWhite = 0xFFFFFAF0,   //����ɫ
        ForestGreen = 0xFF228B22,   //ɭ����
        Fuchsia = 0xFFFF00FF,       //�Ϻ�ɫ
        Gainsboro = 0xFFDCDCDC,     //����ɫ
        GhostWhite = 0xFFF8F8FF,    //�����ɫ
        Gold = 0xFFFFD700,          //��ɫ
        Goldenrod = 0xFFDAA520,     //������ɫ
        Gray = 0xFF808080,          //��ɫ
        Green = 0xFF008000,         //��ɫ
        GreenYellow = 0xFFADFF2F,   //����ɫ
        Honeydew = 0xFFF0FFF0,      //��ɫ
        HotPink = 0xFFFF69B4,       //�ȷۺ�ɫ
        IndianRed = 0xFFCD5C5C,     //ӡ�ڰ���
        Indigo = 0xFF4B0082,        //����ɫ
        Ivory = 0xFFFFFFF0,         //����ɫ
        Khaki = 0xFFF0E68C,         //�ƺ�ɫ
        Lavender = 0xFFE6E6FA,      //޹�²�ɫ������ɫ
        LavenderBlush = 0xFFFFF0F5, //���Ϻ�ɫ
        LawnGreen = 0xFF7CFC00,     //����ɫ
        LemonChiffon = 0xFFFFFACD,  //���ʳ�ɫ
        LightBlue = 0xFFADD8E6,     //����ɫ
        LightCoral = 0xFFF08080,    //��ɺ��ɫ
        LightCyan = 0xFFE0FFFF,     //����ɫ
        LightGoldenrodYellow = 0xFFFAFAD2,  //���ջ�
        LightGray = 0xFFD3D3D3,     //ǳ��ɫ
        LightGreen = 0xFF90EE90,    //����ɫ
        LightPink = 0xFFFFB6C1,     //ǳ�ۺ�
        LightSalmon = 0xFFFFA07A,   //����ɫ
        LightSeaGreen = 0xFF20B2AA, //ǳ����ɫ
        LightSkyBlue = 0xFF87CEFA,  //������ɫ
        LightSlateGray = 0xFF778899,//������
        LightSteelBlue = 0xFFB0C4DE,//������ɫ
        LightYellow = 0xFFFFFFE0,   //ǳ��ɫ
        Lime = 0xFF00FF00,          //ʯ��ɫ
        LimeGreen = 0xFF32CD32,     //�����ɫ
        Linen = 0xFFFAF0E6,         //����ɫ
        Magenta = 0xFFFF00FF,       //���ɫ
        Maroon = 0xFF800000,        //�Ϻ�ɫ
        MediumAquamarine = 0xFF66CDAA,  //�б���ɫ
        MediumBlue = 0xFF0000CD,    //����ɫ
        MediumOrchid = 0xFFBA55D3,  //��������
        MediumPurple = 0xFF9370DB,  //����ɫ
        MediumSeaGreen = 0xFF3CB371,    //�к�����
        MediumSlateBlue = 0xFF7B68EE,   //�а�����
        MediumSpringGreen = 0xFF00FA9A, //�д���ɫ
        MediumTurquoise = 0xFF48D1CC,   //���̱�ʯɫ
        MediumVioletRed = 0xFFC71585,   //��������ɫ
        MidnightBlue = 0xFF191970,      //��ҹ��
        MintCream = 0xFFF5FFFA,         //����ɫ
        MistyRose = 0xFFFFE4E1,         //����õ��ɫ
        Moccasin = 0xFFFFE4B5,          //¹Ƥɫ
        NavajoWhite = 0xFFFFDEAD,       //���߰�
        Navy = 0xFF000080,              //������
        OldLace = 0xFFFDF5E6,           //ǳ��ɫ
        Olive = 0xFF808000,             //���ɫ
        OliveDrab = 0xFF6B8E23,         //���̺�ɫ
        Orange = 0xFFFFA500,            //��ɫ
        OrangeRed = 0xFFFF4500,         //�Ⱥ�ɫ
        Orchid = 0xFFDA70D6,            //������ɫ
        PaleGoldenrod = 0xFFEEE8AA,     //����ɫ
        PaleGreen = 0xFF98FB98,         //����ɫ
        PaleTurquoise = 0xFFAFEEEE,     //����ɫ
        PaleVioletRed = 0xFFDB7093,     //ǳ��������
        PapayaWhip = 0xFFFFEFD5,        //��ľɫ
        PeachPuff = 0xFFFFDAB9,         //��ɫ
        Peru = 0xFFCD853F,              //��³ɫ
        Pink = 0xFFFFC0CB,              //�ۺ�ɫ
        Plum = 0xFFDDA0DD,              //����ɫ
        PowderBlue = 0xFFB0E0E6,        //����ɫ
        Purple = 0xFF800080,            //��ɫ
        Red = 0xFFFF0000,               //��ɫ
        RosyBrown = 0xFFBC8F8F,     //õ����ɫ
        RoyalBlue = 0xFF4169E1,     //�ʼ���ɫ
        SaddleBrown = 0xFF8B4513,   //�غ�ɫ
        Salmon = 0xFFFA8072,        //����ɫ��������ɫ
        SandyBrown = 0xFFF4A460,    //ɳ��ɫ
        SeaGreen = 0xFF2E8B57,      //����ɫ
        SeaShell = 0xFFFFF5EE,      //����ɫ
        Sienna = 0xFFA0522D,        //������ɫ
        Silver = 0xFFC0C0C0,        //��ɫ
        SkyBlue = 0xFF87CEEB,       //����ɫ
        SlateBlue = 0xFF6A5ACD,     //ʯ����ɫ
        SlateGray = 0xFF708090,     //ʯ���ɫ
        Snow = 0xFFFFFAFA,          //ѩ��ɫ
        SpringGreen = 0xFF00FF7F,   //����ɫ
        SteelBlue = 0xFF4682B4,     //����ɫ
        Tan = 0xFFD2B48C,           //�غ�ɫ
        Teal = 0xFF008080,          //��ɫ
        Thistle = 0xFFD8BFD8,       //��ɫ����һ����ɫ
        Tomato = 0xFFFF6347,        //����ɫ
        Transparent = 0x00FFFFFF,   //͸����
        Turquoise = 0xFF40E0D0,     //����ɫ
        Violet = 0xFFEE82EE,        //������ɫ
        Wheat = 0xFFF5DEB3,         //С��ɫ, ����ɫ
        White = 0xFFFFFFFF,         //��ɫ
        WhiteSmoke = 0xFFF5F5F5,    //����ɫ
        Yellow = 0xFFFFFF00,        //��ɫ
        YellowGreen = 0xFF9ACD32    //����ɫ
    };

    /** ������ɫֵ����Ӧ���ַ�������
    */
    void GetUiColorsString(std::vector<std::pair<std::wstring, int32_t>>& uiColors);

}// namespace UiColors
} // namespace ui

#endif // UI_CORE_UICOLORS_H_
