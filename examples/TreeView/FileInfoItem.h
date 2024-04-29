#pragma once

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

struct FileInfo;
class FileInfoItem : public ui::ListBoxItem
{
public:
    FileInfoItem();
    virtual ~FileInfoItem();
    void InitSubControls(const FileInfo& fileInfo, size_t nElementIndex);

private:
    /** �Ƿ�ΪͼƬ�ļ�
    */
    bool IsImageFile(const std::wstring& filePath) const;

private:
    //Ԫ�ص�������
    size_t m_nElementIndex;

    //ͼ��ؼ�
    ui::Control* m_pIconControl;

    //���ֿؼ�
    ui::Label* m_pTextControl;
};

