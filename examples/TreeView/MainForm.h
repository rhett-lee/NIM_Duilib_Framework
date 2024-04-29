#pragma once

#include "resource.h"

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

#include "FileInfoList.h"
#include <Shlobj.h>

class MainForm : public ui::WindowImplBase
{
public:
	MainForm();
	~MainForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void OnInitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	static const std::wstring kClassName;

	/** �������ڵ����¼�
	 */
	void CheckExpandTreeNode(ui::TreeNode* pTreeNode, const std::wstring& filePath);

private:
	//Ŀ¼�б����ݽṹ
	struct FolderStatus
	{
		std::wstring path;
		bool bShow = false;
		HICON hIcon = nullptr;
		ui::TreeNode* pTreeNode = nullptr;
	};

	//��ʾ����Ŀ¼�ڵ㣨�������桢�ҵ��ĵ��ȣ�
	void ShowVirtualDirectoryNode(int csidl, REFKNOWNFOLDERID rfid, const std::wstring& name);

	//��ʾ���̽ڵ�, ���ص�һ���½ڵ�ӿ�
	ui::TreeNode* ShowAllDiskNode();

	//��ʾָ��Ŀ¼����Ŀ¼
	void ShowSubFolders(ui::TreeNode* pTreeNode, const std::wstring& path);

	//���������һ���ڵ�, ��������ӵĽڵ�ӿ�
	ui::TreeNode* InsertTreeNode(ui::TreeNode* pTreeNode,
		                         const std::wstring& displayName,
								 const std::wstring& path,
								 bool isFolder,
								 HICON hIcon);

	//���������в���һ���ڵ�
	void InsertTreeNodes(ui::TreeNode* pTreeNode, 
		                const std::wstring& path,
						const std::vector<FolderStatus>& fileList,
		                bool isFolder);

	//��ʾָ��Ŀ¼������
	void ShowFolderContents(ui::TreeNode* pTreeNode, const std::wstring& path);

	/** ���ڵ�չ���¼�
	 * @param[in] args ��Ϣ��
	 * @return ʼ�շ��� true
	 */
	bool OnTreeNodeExpand(const ui::EventArgs& args);

	/** ���ڵ����¼�
	 * @param[in] args ��Ϣ��
	 * @return ʼ�շ��� true
	 */
	bool OnTreeNodeClick(const ui::EventArgs& args);

	/** ���ڵ�ѡ���¼�
	 * @param[in] args ��Ϣ��
	 * @return ʼ�շ��� true
	 */
	bool OnTreeNodeSelect(const ui::EventArgs& args);

	/** �ж�һ��·���Ƿ�ΪĿ¼
	*/
	bool IsDirectory(const std::wstring& filePath) const;

private:
	//���ڵ�Ľӿ�
	ui::TreeView* m_pTree;

	//Ŀ¼�б��������ʾ��
	std::vector<FolderStatus*> m_folderList;

	/** �ļ��б��Ҳ������ʾ��
	*/
	FileInfoList m_fileList;

	//�ļ��б�Ľӿ�
	ui::VirtualListBox* m_pListBox;

	/** L"Shell32.dll" ���
	*/
	HMODULE m_hShell32Dll;
};


