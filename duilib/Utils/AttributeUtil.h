#ifndef UI_UTILS_ATTRIBUTUTIL_H_
#define UI_UTILS_ATTRIBUTUTIL_H_

#include "duilib/Core/UiTypes.h"
#include <string>
#include <vector>
#include <tuple>

namespace ui
{
class Window;
class UILIB_API AttributeUtil
{
public:
	/** �����ַ�������������һ���ָ���
	*/
	static void SkipSepChar(wchar_t*& pPtr);

	/** �������н���һ��Size�ṹ�������ʽ�磺"800,500"
	*/
	static void ParseSizeValue(const wchar_t* strValue, UiSize& size);

	/** �������н���һ��Point�ṹ�������ʽ�磺"800,500"
	*/
	static void ParsePointValue(const wchar_t* strValue, UiPoint& size);

	/** �������н���һ��Rect�ṹ�������ʽ�磺"80,50,60,70"
	*/
	static void ParseRectValue(const wchar_t* strValue, UiRect& rect);
	static void ParsePaddingValue(const wchar_t* strValue, UiPadding& padding);
	static void ParseMarginValue(const wchar_t* strValue, UiMargin& margin);

	/** ���������б���ʽ��	: font="system_bold_14" normaltextcolor="white" bkcolor="red"
	*                 ����	: color='black' offset='1,1' blur_radius='2' spread_radius='2'
	*   �ָ���������˫���Ż��ߵ����ţ��ɲ�������
	* @param [in] seperateChar �ַ����ָ����������� L'\"' ���� L'\''
	*/
	static void ParseAttributeList(const std::wstring& strList,
		                           wchar_t seperateChar,
		                           std::vector<std::pair<std::wstring, std::wstring>>& attributeList);

	/** ����һ���ַ�������ʽΪ��"500,"����"50%,"�����ſ��п��ޣ�Ҳ�����������ַ������õ�����ֵ���߸�����
    * @param [in] strValue ���������ַ�����ַ
    * @param [out] pEndPtr ������ɺ��ַ���������ַ�����ڼ����������������
    * @return ��������ֵ���߰ٷֱȣ�����ֵ�У�0 ���� 0.0f ��ʾ��Чֵ
    */
	static std::tuple<int32_t, float> ParseString(const wchar_t* strValue, wchar_t** pEndPtr);

    /** ��ȡ�����еĴ��ڴ�С
    */
	static void ParseWindowSize(Window* pWindow, const wchar_t* strValue, UiSize& size);
};

} //namespace ui

#endif // UI_UTILS_ATTRIBUTUTIL_H_
