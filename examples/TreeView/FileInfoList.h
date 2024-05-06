#pragma once

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

/** �ļ���Ϣ
*/
struct FileInfo
{
    //�ļ���, ����·��
    std::wstring m_fileName;
    //�ļ�����·����
    std::wstring m_filePath;
    //�Ƿ�Ϊ�ļ���
    bool m_isFolder = false;
    //������ͼ��(��Դ���������ڸ����ڲ�����)
    HICON m_hIcon = nullptr;
};

class MainForm;
class FileInfoList: public ui::VirtualListBoxElement
{
public:
    explicit FileInfoList(MainForm* pMainForm);
    virtual ~FileInfoList();

    /** ����һ��������
    * @return ���ش������������ָ��
    */
    virtual ui::Control* CreateElement() override;

    /** ���ָ��������
    * @param [in] pControl ������ؼ�ָ��
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    */
    virtual bool FillElement(ui::Control* pControl, size_t nElementIndex) override;

    /** ��ȡ����������
    * @return ��������������
    */
    virtual size_t GetElementCount() const override;

    /** ����ѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] bSelected true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual void SetElementSelected(size_t nElementIndex, bool bSelected) override;

    /** ��ȡѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @return true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual bool IsElementSelected(size_t nElementIndex) const override;

    /** ��ȡѡ���Ԫ���б�
    * @param [in] selectedIndexs ���ص�ǰѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    */
    virtual void GetSelectedElements(std::vector<size_t>& selectedIndexs) const override;

    /** �Ƿ�֧�ֶ�ѡ
    */
    virtual bool IsMultiSelect() const override;

    /** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
    * @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
    */
    virtual void SetMultiSelect(bool bMultiSelect) override;

public:
    /** ���µ��ļ��б��滻ԭ�����б�
    */
    void SetFileList(ui::TreeNode* pTreeNode, const std::vector<FileInfo>& pathList);

    /** ����ļ��б�
    */
    void ClearFileList();

private:
    /** ���˫��ʱ����
     * @param[in] args ��Ϣ��
     * @return ʼ�շ��� true
     */
    bool OnDoubleClickItem(const ui::EventArgs& args);

private:
    /** ������MainForm
    */
    MainForm* m_pMainForm;

    /** ���������ڵ�
    */
    ui::TreeNode* m_pTreeNode;

    //�ļ��б�
    std::vector<FileInfo> m_pathList;
};

