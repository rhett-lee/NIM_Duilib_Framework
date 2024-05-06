#include "FontManager.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Utils/VersionHelpers.h"
#include "duilib/Render/IRender.h"
#include "duilib/Utils/StringUtil.h"

namespace ui 
{

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	RemoveAllFonts();
	RemoveAllFontFiles();
}

bool FontManager::AddFont(const std::wstring& strFontId,
						  const UiFont& fontInfo,
						  bool bDefault)
{
	ASSERT(!strFontId.empty());
	if (strFontId.empty()) {
		return false;
	}

	auto iter = m_fontMap.find(strFontId);
	ASSERT(iter == m_fontMap.end());
	if (iter != m_fontMap.end()) {
		return false;
	}

	static bool bOsOverXp = IsWindowsVistaOrGreater();
	std::wstring fontName = fontInfo.m_fontName;
	if (fontName.empty() || (fontName == L"system")) {
		//����ʹ��Ӣ�����ƣ����ּ�����
		fontName = bOsOverXp ? L"Microsoft YaHei" : L"SimSun";
	}

	IFont* pFont = nullptr;
	IRenderFactory* pRenderFactory = GlobalManager::Instance().GetRenderFactory();
	if (pRenderFactory != nullptr) {
		pFont = pRenderFactory->CreateIFont();
	}
	ASSERT(pFont != nullptr);
	if (pFont == nullptr) {
		return false;
	}
	UiFont fontInfoNew = fontInfo;
	fontInfoNew.m_fontName = fontName;
	bool isInitOk = pFont->InitFont(fontInfoNew);
	ASSERT(isInitOk);
	if (!isInitOk) {
		delete pFont;
		pFont = nullptr;
		return false;
	}
	m_fontMap.insert(std::make_pair(strFontId, pFont));
	if (bDefault) {
		m_defaultFontId = strFontId;
	}
	return true;
}

IFont* FontManager::GetIFont(const std::wstring& strFontId)
{
	auto iter = m_fontMap.find(strFontId);
	if (iter == m_fontMap.end()) {
		//����Ҳ���������Ĭ������
		if (!m_defaultFontId.empty()) {
			iter = m_fontMap.find(m_defaultFontId);
		}		
	}
	IFont* pFont = nullptr;
	if (iter != m_fontMap.end()) {
		pFont = iter->second;
	}
	return pFont;
}

void FontManager::RemoveAllFonts()
{
	for (auto fontInfo : m_fontMap) {
		IFont* pFont = fontInfo.second;
		if (pFont != nullptr) {
			delete pFont;
		}
	}
	m_fontMap.clear();
	m_defaultFontId.clear();
}

void FontManager::AddFontFile(const std::wstring& strFontFile, const std::wstring& strFontName)
{
	FontFileInfo fontFileInfo;
	std::wstring path = GlobalManager::Instance().GetResFullPath(L"", L"font\\" + strFontFile);
	bool res = false;
	if (GlobalManager::Instance().Zip().IsUseZip()) {
		std::vector<unsigned char> file_data;
		if (GlobalManager::Instance().Zip().GetZipData(path, file_data)) {
			DWORD dwFonts = 0;
			fontFileInfo.m_hFontFile = ::AddFontMemResourceEx(file_data.data(), static_cast<DWORD>(file_data.size()), NULL, &dwFonts);
			res = fontFileInfo.m_hFontFile != nullptr;
		}
	}
	else {
		res = ::AddFontResourceEx(path.c_str(), FR_PRIVATE, 0) != 0;
	}
	ASSERT(res);
	if (res) {
		fontFileInfo.m_fontFilePath = path;
		fontFileInfo.m_fontName = strFontName;
		m_fontFileInfo.push_back(fontFileInfo);
	}
}

void FontManager::RemoveAllFontFiles()
{
	for (const auto& it : m_fontFileInfo) {
		if (it.m_hFontFile != nullptr) {
			::RemoveFontMemResourceEx(it.m_hFontFile);
		}
		else if(!it.m_fontFilePath.empty()){
			::RemoveFontResourceEx(it.m_fontFilePath.c_str(), FR_PRIVATE, 0);
		}
	}
	m_fontFileInfo.clear();
}

//�������Ӣ������ӳ���
static void GetFontNameList(std::vector<std::pair<std::wstring, std::wstring>>& fontNameList)
{
	//ϵͳ����
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����", L"SimSun"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����", L"SimHei"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"΢���ź�", L"Microsoft YaHei"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"΢��������", L"Microsoft JhengHei"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����", L"KaiTi"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"������", L"NSimSun"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����", L"FangSong"));
	
	//Office����
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��Բ", L"YouYuan"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����", L"LiSu"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����ϸ��", L"STXiHei"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"���Ŀ���", L"STKaiTi"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��������", L"STSong"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"���ķ���", L"STFangSong"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��������", L"STZhongSong"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"���Ĳ���", L"STCaiYun"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��������", L"STHuPo"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"������κ", L"STXinWei"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��������", L"STLiTi"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"�����п�", L"STXingKai"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"��������", L"FZShuTi"));
	fontNameList.push_back(std::make_pair<std::wstring, std::wstring>(L"����Ҧ��", L"FZYaoTi"));
}

std::wstring FontManager::GetFontEnglishName(const std::wstring& fontName)
{
	std::vector<std::pair<std::wstring, std::wstring>> fontNameList;
	GetFontNameList(fontNameList);
	for (const auto& pair : fontNameList) {
		if (fontName == pair.first) {
			return pair.second;
		}
	}
	return fontName;
}

std::wstring FontManager::GetFontSystemName(const std::wstring& fontName)
{
	std::vector<std::pair<std::wstring, std::wstring>> fontNameList;
	GetFontNameList(fontNameList);
	for (const auto& pair : fontNameList) {
		if (ui::StringHelper::IsEqualNoCase(fontName, pair.second)) {
			return pair.first;
		}
	}
	return fontName;
}

}