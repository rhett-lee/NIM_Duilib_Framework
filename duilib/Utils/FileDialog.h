#ifndef UI_UTILS_FILE_DIALOG_H_
#define UI_UTILS_FILE_DIALOG_H_

#include "duilib/duilib_defs.h"
#include <string>
#include <vector>

namespace ui
{

/** �ļ�����Ŀ¼ѡ��Ի���֧�ֶ�ѡ
*/
class Window;
class UILIB_API FileDialog
{
public:
    /** ѡ���ļ��У���ѡ��
    * @param [in] pWindow ������
    * @param [out] folderPath ����ѡ����ļ���·��
    */
    bool BrowseForFolder(Window* pWindow, std::wstring& folderPath);

    /** ѡ���ļ��У���ѡ��
    * @param [in] pWindow ������
    * @param [out] folderPaths ����ѡ����ļ���·��
    */
    bool BrowseForFolders(Window* pWindow, std::vector<std::wstring>& folderPaths);

public:
    /** �ļ�����ɸѡ��
    */
    struct FileType
    {
        std::wstring szName; //�ļ�����ɸѡ������ʾ����, ����: "Text files"
        std::wstring szExt;  //�ļ�����ɸѡ��, ������"*.txt"
    };

    /** ѡ���ļ�����ѡ��
    * @param [in] pWindow ������
    * @param [in] bOpenFileDialog true��ʾ���ļ���false��ʾ�����ļ�
    * @param [in] fileTypes �Ի�����Դ򿪻򱣴���ļ�����
    * @param [in] nFileTypeIndex ѡ����ļ����ͣ���Ч��Χ��[0, fileTypes.size())
    * @param [in] defaultExt Ĭ�ϵ��ļ�����, ������"doc;docx"
    * @param [out] filePath ����ѡ����ļ�·��
    */
    bool BrowseForFile(Window* pWindow, 
                       std::wstring& filePath,                       
                       bool bOpenFileDialog, 
                       const std::vector<FileType>& fileTypes = std::vector<FileType>(),
                       int32_t nFileTypeIndex = -1,
                       const std::wstring& defaultExt = L"");

    /** ѡ���ļ�����ѡ��
    * @param [in] pWindow ������
    * @param [in] fileTypes �Ի�����Դ򿪻򱣴���ļ�����
    * @param [in] nFileTypeIndex ѡ����ļ����ͣ���Ч��Χ��[0, fileTypes.size())
    * @param [in] defaultExt Ĭ�ϵ��ļ�����, ������"doc;docx"
    * @param [out] filePaths ����ѡ����ļ�·��
    */
    bool BrowseForFiles(Window* pWindow, 
                        std::vector<std::wstring>& filePaths,                        
                        const std::vector<FileType>& fileTypes = std::vector<FileType>(),
                        int32_t nFileTypeIndex = -1,
                        const std::wstring& defaultExt = L"");

};

}

#endif // UI_UTILS_FILE_DIALOG_H_
