#include "AttributeUtil.h"
#include "duilib/Utils/StringUtil.h"
#include "duilib/Core/Window.h"
#include "duilib/Core/GlobalManager.h"

namespace ui
{

void AttributeUtil::SkipSepChar(wchar_t*& pPtr)
{
	if ((pPtr != nullptr) && (*pPtr != L'\0')) {
		//�����ָ��ַ�������������β0����ֹ�ַ���Խ��
		pPtr++;
	}
}

void AttributeUtil::ParseSizeValue(const wchar_t* strValue, UiSize& size)
{
	size.Clear();
	if ((strValue == nullptr) || (*strValue == L'\0')) {
		return;
	}
	wchar_t* pstr = nullptr;
	int32_t cx = wcstol(strValue, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	int32_t cy = wcstol(pstr, &pstr, 10);
	size.cx = cx;
	size.cy = cy;
}

void AttributeUtil::ParsePointValue(const wchar_t* strValue, UiPoint& pt)
{
	UiSize size;
	AttributeUtil::ParseSizeValue(strValue, size);
	pt.x = size.cx;
	pt.y = size.cy;
}

void AttributeUtil::ParsePaddingValue(const wchar_t* strValue, UiPadding& padding)
{
	padding.Clear();
	if ((strValue == nullptr) || (*strValue == L'\0')) {
		return;
	}
	wchar_t* pstr = nullptr;
	padding.left = wcstol(strValue, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	padding.top = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	padding.right = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	padding.bottom = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	ASSERT((padding.left >= 0) && (padding.top >= 0) && (padding.right >= 0) && (padding.bottom >= 0));
	padding.Validate();
}

void AttributeUtil::ParseMarginValue(const wchar_t* strValue, UiMargin& margin)
{
	margin.Clear();
	if ((strValue == nullptr) || (*strValue == L'\0')) {
		return;
	}
	wchar_t* pstr = nullptr;
	margin.left = wcstol(strValue, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	margin.top = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	margin.right = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	margin.bottom = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	ASSERT((margin.left >= 0) && (margin.top >= 0) && (margin.right >= 0) && (margin.bottom >= 0));
	margin.Validate();
}

void AttributeUtil::ParseRectValue(const wchar_t* strValue, UiRect& rect)
{
	rect.Clear();
	if ((strValue == nullptr) || (*strValue == L'\0')) {
		return;
	}
	wchar_t* pstr = nullptr;
	rect.left = wcstol(strValue, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	rect.top = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	rect.right = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	SkipSepChar(pstr);
	rect.bottom = wcstol(pstr, &pstr, 10); ASSERT(pstr);
	ASSERT((rect.Width() >= 0) && (rect.Height() >= 0));
}

void AttributeUtil::ParseAttributeList(const std::wstring& strList,
									   wchar_t seperateChar,
	                                   std::vector<std::pair<std::wstring, std::wstring>>& attributeList)
{
	std::wstring sName;
	std::wstring sValue;
	const wchar_t* pstrList = strList.c_str();
	while (*pstrList != L'\0') {
		sName.clear();
		sValue.clear();
		//��ȡ�Ⱥ�ǰ������ݣ���ΪName
		while (*pstrList != L'\0' && *pstrList != L'=') {
			const wchar_t* pstrTemp = ::CharNext(pstrList);
			while (pstrList < pstrTemp) {
				sName += *pstrList++;
			}
		}
		//��ǰ�ַ�Ӧ���Ǹ��Ⱥ�
		ASSERT(*pstrList == L'=');
		if (*pstrList != L'=') {
			return;
		}
		//�����Ⱥ��ַ�������ַ�������ַ�Ӧ���Ǹ��ָ��ַ�
		pstrList++;
		ASSERT(*pstrList == seperateChar);
		if (*pstrList != seperateChar) {
			return;
		}

		//������һ���ָ��ַ�������ַ�����ȡ����ֵ
		pstrList++;
		while (*pstrList != L'\0' && *pstrList != seperateChar) {
			LPTSTR pstrTemp = ::CharNext(pstrList);
			while (pstrList < pstrTemp) {
				sValue += *pstrList++;
			}
		}
		ASSERT(*pstrList == seperateChar);
		if (*pstrList != seperateChar) {
			return;
		}

		//������һ�����ԣ���ӵ��б���(�������Ʋ������пո�)
		sName = StringHelper::Trim(sName);
		attributeList.push_back(std::make_pair(sName, sValue));

		//�����ָ��ַ�������ַ�������ַ�Ӧ���ǿո�������ǿո���Ϊ�Ѿ�����
		pstrList++;
		if (*pstrList != L' ') {
			return;
		}

		//�����ո������ַ�
		pstrList++;
	}
}

std::tuple<int32_t, float> AttributeUtil::ParseString(const wchar_t* strValue, wchar_t** pEndPtr)
{
	wchar_t* pstr = nullptr;
	if ((strValue == nullptr) || (*strValue == L'\0')) {
		if (pEndPtr != nullptr) {
			*pEndPtr = pstr;
		}
		return std::tuple<int32_t, float>(0, 0.0f);
	}
	int32_t xValue = 0;
	float xPercent = wcstof(strValue, &pstr);
	ASSERT(pstr != nullptr);
	if ((pstr != nullptr) && (*pstr == L'%')) {
		//��ֵ�ǰٷֱȣ�����'%'�ַ�
		pstr++;
	}
	else {
		//���ǰٷֱ�, ��������ֵ
		xPercent = 0.0f;
		xValue = wcstol(strValue, &pstr, 10);
		ASSERT(pstr != nullptr);
	}
	if (pEndPtr != nullptr) {
		*pEndPtr = pstr;
	}
	return std::tuple<int32_t, float>(xValue, xPercent);
}

void AttributeUtil::ParseWindowSize(Window* pWindow, const wchar_t* strValue, UiSize& size)
{
	//֧�ֵĸ�ʽ��size="1200,800",����size="50%,50%",����size="1200,50%",size="50%,800"
	//�ٷֱ���ָ��Ļ��Ȼ��߸߶ȵİٷֱ�
	ASSERT(pWindow != nullptr);
	UiRect rcWork;
	if (pWindow != nullptr) {
		pWindow->GetMonitorWorkRect(rcWork);
	}
	wchar_t* pstr = nullptr;
	std::tuple<int32_t, float> x = ParseString(strValue, &pstr);
	AttributeUtil::SkipSepChar(pstr);
	std::tuple<int32_t, float> y = ParseString(pstr, &pstr);

	//��ȡ��Ч�İٷֱ�ֵ
	auto GetValidPercent = [](const std::tuple<int32_t, float>& xy) -> float {
		float fPercent = std::get<1>(xy);
		fPercent /= 100.0f;
		ASSERT((fPercent >= 0.0001f) && (fPercent < 1.0001f));
		if ((fPercent < 0.0001f) || (fPercent > 1.0001f)) {
			//���������Ч�ٷֱȣ���Ĭ������Ϊ���ڴ�С��75%
			fPercent = 0.75f;
		}
		return fPercent;
	};

	bool needScaleCX = true;
	bool needScaleCY = true;
	int cx = std::get<0>(x);
	if (cx <= 0) {
		float fPercent = GetValidPercent(x);
		cx = (int)(rcWork.Width() * fPercent);
		needScaleCX = false;
	}
	int cy = std::get<0>(y);
	if (cy <= 0) {
		float fPercent = GetValidPercent(y);
		cy = (int)(rcWork.Height() * fPercent);
		needScaleCY = false;
	}

	ASSERT((cx > 0) && (cy > 0));
	if (cx < 0) {
		cx = 0;
	}
	if (cy < 0) {
		cy = 0;
	}
	if (needScaleCX) {
		GlobalManager::Instance().Dpi().ScaleInt(cx);
	}
	if (needScaleCY) {
		GlobalManager::Instance().Dpi().ScaleInt(cy);
	}
	if (cx > rcWork.Width()) {
		cx = rcWork.Width();
	}
	if (cy > rcWork.Width()) {
		cy = rcWork.Height();
	}
	size.cx = cx;
	size.cy = cy;
}

}//namespace ui
