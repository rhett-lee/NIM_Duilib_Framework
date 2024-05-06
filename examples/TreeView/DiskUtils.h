#ifndef __DiskUtils_h_
#define __DiskUtils_h_

#include "duilib/duilib_config.h"
#include <string>
#include <vector>

/** ���̷�����Ϣ������
*/
class DiskUtils
{
public:

    /** ���̷�������ϸ��Ϣ
    */
    struct DiskInfo
    { 
        /** �������
        */
        std::wstring m_volumeName;
        
        /** ��������
        */
        std::wstring m_volumeType;
        
        /** �������ͣ���NTFS��
        */
        std::wstring m_fileSystem;
        
        /** �ش�С
        */
        uint32_t m_clusterBytes;
        
        /** �ܴ�С
        */
        uint64_t m_totalBytes;
        
        /** ���ÿռ��С
        */
        uint64_t m_freeBytes;
        
        /** �Ƿ����ļ�ϵͳ
        */
        bool m_hasFileSystem;
    };
    
public:
    
    /** ��ȡ���ش����б�
    @param [out] ���ر��ش��̵��б����̸�ʽ�磺"C:\\"��
    @return �ɹ�����true�����򷵻�false
    */
    static bool GetLogicalDriveList(std::vector<std::wstring>& driveList);
    
    /** ��ȡ������Ϣ
    @param [in] driveString ���������ƣ���ʽ�磺"C:\\"
    @param [out] diskInfo ���ش��̶�Ӧ��Ϣ
    @return �ɹ�����true�����򷵻�false
    */
    static bool GetLogicalDriveInfo(const std::wstring& driveString, DiskInfo& diskInfo);

    /** ����·���õ���ǰ���̷�
    @param [in] path ��ǰ·��
    @return �̷�����
    */
    static std::wstring GetDriveFromDirectoryPath(std::wstring path);

    /** ��ȡʣ��ռ����ı��ش��̵��̷�
    @return ���ش��̵��̷��� ����: "C:\\"
    */
    static std::wstring GetMaxFreeSpaceLocalDisk();

    /** ��ȡָ��Ŀ¼��ʣ����̿ռ�
    @param[in] fullDirectory �ļ�Ŀ¼
    @return ʣ����̿ռ��С(BYTE)
    */
    static uint64_t GetFreeDiskSpace(const std::wstring& fullDirectory);
};

#endif //__DiskUtils_h_
