#ifndef UI_CONTROL_COLORPICKER_REGULAR_H_
#define UI_CONTROL_COLORPICKER_REGULAR_H_

#pragma once

#include "duilib/Box/VirtualListBox.h"

namespace ui
{
/** ��ɫѡ������������ɫ
*/
class ColorPickerRegularProvider;
class ColorPickerRegular : public VirtualVTileListBox
{
public:
    ColorPickerRegular();

    /** ��ȡ�ؼ�����
    */
    virtual std::wstring GetType() const override;

    /** ѡ��һ����ɫ
    */
    void SelectColor(const UiColor& color);

    /** ��ȡ��ǰѡ�����ɫ
    */
    UiColor GetSelectedColor() const;

    /** ����ѡ����ɫ���¼�
    * @param[in] callback ѡ����ɫ�仯ʱ�Ļص�����
    *            ����˵��:
                        wParam: ��ǰ��ѡ�����ɫֵ��������UiColor((uint32_t)wParam)������ɫ
                        lParam: ԭ����ѡ�����ɫֵ��������UiColor((uint32_t)lParam)������ɫ
    */
    void AttachSelectColor(const EventCallback& callback) { AttachEvent(kEventSelectColor, callback); }

    /** ���ÿؼ�λ��
    */
    virtual void SetPos(UiRect rc) override;

    /** ������ʾ����
    */
    void SetColumns(int32_t nColumns);

    /** ��������
    */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

private:
    /** ������ɫ�����ṩ��
    */
    std::unique_ptr<ColorPickerRegularProvider> m_regularColors;

    /** ԭ�����õ�Ԫ�ؿؼ���С
    */
    UiSize m_szItem;
};

}//namespace ui

#endif //UI_CONTROL_COLORPICKER_REGULAR_H_
