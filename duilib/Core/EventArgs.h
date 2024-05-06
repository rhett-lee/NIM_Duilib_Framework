#ifndef UI_CORE_EVENTARGS_H_
#define UI_CORE_EVENTARGS_H_

#pragma once

#include "duilib/Core/UiPoint.h"
#include <string>

namespace ui
{
class Control;

/** �¼�֪ͨ�Ĳ���
*/
struct EventArgs
{
    EventArgs() :
        Type(kEventNone),
        pSender(nullptr),
        dwTimestamp(0),
        chKey(0),
        wParam(0),
        lParam(0)
    {
        ptMouse.x = 0;
        ptMouse.y = 0;
    }

    /** �¼�����
    */
    EventType Type;

    /** �����¼��Ŀؼ�
    */
    Control* pSender;

    /** �����¼�ʱ��ʱ���
    */
    size_t dwTimestamp;

    /** �����¼�ʱ�������������
    */
    UiPoint ptMouse;

    /** �����¼�ʱ�İ���
    */
    wchar_t chKey;

    /** �����¼�ʱ�Ĳ���
    */
    WPARAM wParam;

    /** �����¼�ʱ�Ĳ���
    */
    LPARAM lParam;
};

/** ���ַ���ת��Ϊ�¼�����
*/
EventType StringToEventType(const std::wstring& messageType);

/** ���¼�����ת��Ϊ�ַ���
*/
std::wstring EventTypeToString(EventType eventType);

}// namespace ui

#endif // UI_CORE_EVENTARGS_H_