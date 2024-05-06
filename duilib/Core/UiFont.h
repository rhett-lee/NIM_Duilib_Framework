#ifndef UI_CORE_UIFONT_H_
#define UI_CORE_UIFONT_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>
#include <string>

namespace ui
{

/** ����ӿڵĻ������ݽṹ
*/
class UILIB_API UiFont
{
public:
    UiFont() :
        m_fontSize(0),
        m_bBold(false),
        m_bUnderline(false),
        m_bItalic(false),
        m_bStrikeOut(false)
    {}

    /** ��������
    */
    std::wstring m_fontName;

    /** �����С����λ�����أ�
    */
    int32_t m_fontSize;

    /** �Ƿ�Ϊ����
        */
    bool m_bBold;

    /** �����»���״̬
    */
    bool m_bUnderline;

    /** �����б��״̬
    */
    bool m_bItalic;

    /** �����ɾ����״̬
    */
    bool m_bStrikeOut;
};

} // namespace ui

#endif // UI_CORE_UIFONT_H_
