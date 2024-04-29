#ifndef UI_CORE_COLOR_MANAGER_H_
#define UI_CORE_COLOR_MANAGER_H_

#pragma once

#include "duilib/Core/UiColor.h"
#include <unordered_map>
#include <string>

namespace ui 
{
/** ��ɫֵ�Ĺ�������
*/
class UILIB_API ColorMap
{
public:
    /** ���һ����ɫֵ
    * @param[in] strName ��ɫ���ƣ��� white��
    * @param[in] strValue ��ɫ������ֵ���� #FFFFFFFF��
    */
    void AddColor(const std::wstring& strName, const std::wstring& strValue);

    /** ���һ����ɫֵ
    * @param[in] strName ��ɫ���ƣ��� white��
    * @param[in] argb ��ɫ������ֵ, ��ARGB��ʽ��ʾ
    */
    void AddColor(const std::wstring& strName, UiColor argb);

    /** �������ƻ�ȡһ����ɫ�ľ�����ֵ
    * @param[in] strName Ҫ��ȡ����ɫ����
    * @return ���� ARGB ��ʽ����ɫ����ֵ
    */
    UiColor GetColor(const std::wstring& strName) const;

    /** ɾ��������ɫ����
    */
    void RemoveAllColors();

private:
    /** ��ɫ��������ɫֵ��ӳ���ϵ
    */
    std::unordered_map<std::wstring, UiColor> m_colorMap;
};

/** ��ɫֵ�Ĺ�����
*/
class UILIB_API ColorManager
{
public:
    ColorManager();

    /** ����ɫ��ֵ�ַ���ת��ΪARGB��ɫ��
     * @param[in] strColor ֧��������ɫֵ��
                  (1) ��ɫ������ֵ���� #FFFFFFFF��
                  (2) ���õı�׼��ɫֵ������"blue"���μ�ui::UiColors::UiColorConsts�����еĶ���
     */
    static UiColor ConvertToUiColor(const std::wstring& strColor);

public:
    /** ���һ��ȫ����ɫֵ
     * @param[in] strName ��ɫ���ƣ��� white��
     * @param[in] strValue ��ɫ������ֵ���� #FFFFFFFF��
     */
    void AddColor(const std::wstring& strName, const std::wstring& strValue);

    /** ���һ��ȫ����ɫֵ
     * @param[in] strName ��ɫ���ƣ��� white��
     * @param[in] argb ��ɫ������ֵ, ��ARGB��ʽ��ʾ
     */
    void AddColor(const std::wstring& strName, UiColor argb);

    /** �������ƻ�ȡһ����ɫ�ľ�����ֵ
     * @param[in] strName Ҫ��ȡ����ɫ����
     * @return ���� ARGB ��ʽ����ɫ����ֵ
     */
    UiColor GetColor(const std::wstring& strName) const;

    /** �������ƻ�ȡһ����׼��ɫ�ľ�����ֵ
     * @param[in] strName Ҫ��ȡ����ɫ���ƣ�����"blue"����ϸ�б�μ���ui::UiColors::UiColorConsts�����еĶ���
     * @return ���� ARGB ��ʽ����ɫ����ֵ
     */
    UiColor GetStandardColor(const std::wstring& strName) const;

    /** ɾ��������ɫ����
     */
    void RemoveAllColors();

    /** ɾ��������ɫ���ԵȻ���
     */
    void Clear();

public:
	/** ��ȡĬ�Ͻ���״̬��������ɫ
	 * @return Ĭ�Ͻ���״̬��ɫ���ַ�����ʾ����Ӧ global.xml ��ָ����ɫֵ
	 */
	const std::wstring& GetDefaultDisabledTextColor();

	/** ����Ĭ�Ͻ���״̬�µ�������ɫ
	 */
	void SetDefaultDisabledTextColor(const std::wstring& strColor);

	/** ��ȡĬ��������ɫ
	 */
    const std::wstring& GetDefaultTextColor();

	/** ����Ĭ��������ɫ
	 */
	void SetDefaultTextColor(const std::wstring& strColor);

private:
    /** ��ɫ��������ɫֵ��ӳ���ϵ
    */
    ColorMap m_colorMap;

    /** ��׼��ɫֵӳ���, �μ���UiColors::GetUiColorsString�����е��б�
    */
    ColorMap m_standardColorMap;

    /** Ĭ�Ͻ���״̬�µ�������ɫ
    */
    std::wstring m_defaultDisabledTextColor;

    /** Ĭ������״̬��������ɫ
    */
    std::wstring m_defaultTextColor;
};

} // namespace ui

#endif // UI_CORE_COLOR_MANAGER_H_
