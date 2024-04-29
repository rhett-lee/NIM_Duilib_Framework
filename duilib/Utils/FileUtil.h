#ifndef UI_UTILS_FILEUTIL_H_
#define UI_UTILS_FILEUTIL_H_

#include "duilib/duilib_defs.h"
#include <string>
#include <vector>

namespace ui
{

class UILIB_API FileUtil
{
public:
	/** ��ȡ�ļ�����
	* @param [in] filePath �����ļ�·��
	* @param [out] fileData �ļ����ݣ������������ݶ�ȡ
	*/
	static bool ReadFileData(const std::wstring& filePath, std::vector<uint8_t>& fileData);
};

}

#endif // UI_UTILS_FILEUTIL_H_
