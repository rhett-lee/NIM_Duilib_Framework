#ifndef UI_UTILS_STRINGUTIL_H_
#define UI_UTILS_STRINGUTIL_H_

#include "duilib/duilib_defs.h"
#include <string>
#include <list>

namespace ui
{

class UILIB_API StringHelper
{
public:
	//��·���еķָ���/�㣨"/\\."���ַ����й淶������, ȷ��Ŀ¼�Էָ�������(������Ŀ¼)
	static std::wstring NormalizeDirPath(const std::wstring& strFilePath);

	//��·���еķָ���/�㣨"/\\."���ַ����й淶������, ���������ļ���
	static std::wstring NormalizeFilePath(const std::wstring& strFilePath);

	//��������·��������һ���µ�·��������·��ƴ��
	static std::wstring JoinFilePath(const std::wstring& path1, const std::wstring& path2);

	//�ж�·��ָ����ļ��Ƿ����
	static bool IsExistsPath(const std::wstring& strFilePath);

	//�ж�·���Ƿ�Ϊ���·��
	static bool IsRelativePath(const std::wstring& strFilePath);

	//�ж�·���Ƿ�Ϊ����·��
	static bool IsAbsolutePath(const std::wstring& strFilePath);

public:
	// format a string
	static std::wstring Printf(const wchar_t *format, ...);

	// replace all 'find' with 'replace' in the string
	static size_t ReplaceAll(const std::wstring& find, const std::wstring& replace, std::wstring& output);
	static size_t ReplaceAll(const std::string& find, const std::string& replace, std::string& output);

	static std::wstring MakeLowerString(const std::wstring &str);
	static std::wstring MakeUpperString(const std::wstring &str);

	static bool MBCSToUnicode(const char *input, std::wstring& output, int code_page = CP_ACP);
	static bool MBCSToUnicode(const std::string &input, std::wstring& output, int code_page = CP_ACP);
	static bool UnicodeToMBCS(const wchar_t *input, std::string &output, int code_page = CP_ACP);
	static bool UnicodeToMBCS(const std::wstring& input, std::string &output, int code_page = CP_ACP);

	// trimming, removing extra spaces
	static std::string TrimLeft(const char *input);
	static std::string TrimRight(const char *input);
	static std::string Trim(const char *input); /* both left and right */
	static std::string& TrimLeft(std::string &input);
	static std::string& TrimRight(std::string &input);
	static std::string& Trim(std::string &input); /* both left and right */
	static std::wstring TrimLeft(const wchar_t *input);
	static std::wstring TrimRight(const wchar_t *input);
	static std::wstring Trim(const wchar_t *input); /* both left and right */
	static std::wstring& TrimLeft(std::wstring &input);
	static std::wstring& TrimRight(std::wstring &input);
	static std::wstring& Trim(std::wstring &input); /* both left and right */

	// find all tokens splitted by one of the characters in 'delimitor'
	static std::list<std::string> Split(const std::string& input, const std::string& delimitor);
	static std::list<std::wstring> Split(const std::wstring& input, const std::wstring& delimitor);

	//�Ƚ��ַ����Ƿ���ȣ��Ƚ�ʱ���Դ�Сд
	static bool IsEqualNoCase(const std::wstring& lhs, const std::wstring& rhs);
	static bool IsEqualNoCase(const wchar_t* lhs, const std::wstring& rhs);
	static bool IsEqualNoCase(const std::wstring& lhs, const wchar_t* rhs);
	static bool IsEqualNoCase(const wchar_t* lhs, const wchar_t* rhs);

	//������ת��Ϊ�ַ���
	static std::wstring UInt64ToString(uint64_t value);
	static std::wstring UInt32ToString(uint32_t value);
};

}

#endif // UI_UTILS_STRINGUTIL_H_
