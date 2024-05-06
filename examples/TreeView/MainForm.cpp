#include "MainForm.h"
#include "MainThread.h"
#include "DiskUtils.h"
#include <ShellApi.h>

const std::wstring MainForm::kClassName = L"MainForm";

MainForm::MainForm():
    m_fileList(this),
    m_pTree(nullptr),
    m_pListBox(nullptr),
    m_hShell32Dll(nullptr)
{
}

MainForm::~MainForm()
{
    for (auto p : m_folderList) {
        ui::GlobalManager::Instance().Icon().RemoveIcon(p->hIcon);
        ::DestroyIcon(p->hIcon);
        delete p;
    }
    if (m_hShell32Dll != nullptr) {
        ::FreeLibrary(m_hShell32Dll);
        m_hShell32Dll = nullptr;
    }
}

std::wstring MainForm::GetSkinFolder()
{
	return L"tree_view";
}

std::wstring MainForm::GetSkinFile()
{
	return L"tree_view.xml";
}

std::wstring MainForm::GetWindowClassName() const
{
	return kClassName;
}

void MainForm::OnInitWindow()
{
	m_pTree = dynamic_cast<ui::TreeView*>(FindControl(L"tree"));
    ASSERT(m_pTree != nullptr);
    m_pListBox = dynamic_cast<ui::VirtualListBox*>(FindControl(L"list"));
    ASSERT(m_pListBox != nullptr);
    if (m_pListBox != nullptr) {
        m_pListBox->SetDataProvider(&m_fileList);
    }
    //���ÿ������ڵ��CheckBox����
    m_pTree->SetCheckBoxClass(L"tree_node_checkbox");
    //���ÿ������ڵ��[չ��/����]ͼ�깦��
    m_pTree->SetExpandImageClass(L"tree_node_expand");
    //�����Ƿ�֧�ֶ�ѡ
    m_pTree->SetMultiSelect(true);
	
    //��ʾ����·��
    ShowVirtualDirectoryNode(CSIDL_DESKTOP, FOLDERID_Desktop, L"����");
    ShowVirtualDirectoryNode(CSIDL_PERSONAL, FOLDERID_Documents, L"�ĵ�");
    ShowVirtualDirectoryNode(CSIDL_MYPICTURES, FOLDERID_Pictures, L"ͼƬ");
    ShowVirtualDirectoryNode(CSIDL_MYMUSIC, FOLDERID_Music, L"����");
    ShowVirtualDirectoryNode(CSIDL_MYVIDEO, FOLDERID_Videos, L"��Ƶ");
    ShowVirtualDirectoryNode(-1, FOLDERID_Downloads, L"����"); 

    //��ʾ����
    ui::TreeNode* pFirstDiskNode = ShowAllDiskNode();

    //�ڴ���ǰ�棬��һ�����߷ָ���
    if (pFirstDiskNode != nullptr) {
        ui::Control* pLineControl = new ui::Control;
        pLineControl->SetClass(L"splitline_hor_level1");
        pLineControl->SetMargin(ui::UiMargin(12, 8, 12, 8), true);
        m_pTree->InsertControlBeforeNode(pFirstDiskNode, pLineControl);
    }

   // ShowAllDiskNode();
}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void MainForm::InsertTreeNodes(ui::TreeNode* pTreeNode,
                               const std::wstring& path,
                               const std::vector<FolderStatus>& fileList,
                               bool isFolder)
{
    //У��pTreeNode�Ƿ���ڣ����ھ������̣߳�
    if (pTreeNode == nullptr) {
        return;
    }
    size_t itemIndex = m_pTree->GetItemIndex(pTreeNode);
    if (!ui::Box::IsValidItemIndex(itemIndex)) {
        //�ڵ��Ѿ��������ˣ�����
        return;
    }
    
    std::wstring folderPath;
    for (const FolderStatus& folder : fileList) {
        folderPath = ui::StringHelper::JoinFilePath(path, folder.path);
        InsertTreeNode(pTreeNode, folder.path, folderPath, isFolder, folder.hIcon);
    }
}

ui::TreeNode* MainForm::InsertTreeNode(ui::TreeNode* pTreeNode,
                                       const std::wstring& displayName,
                                       const std::wstring& path,
                                       bool isFolder,
                                       HICON hIcon)
{
    if (m_pTree == nullptr) {
        return nullptr;
    }

    ui::TreeNode* node = new ui::TreeNode;
    node->SetWindow(this);
    node->SetClass(L"tree_node");//��"global.xml"�ж���
    node->SetText(displayName);
        
    FolderStatus* pFolder = new FolderStatus;
    pFolder->path = path;
    pFolder->hIcon = hIcon;
    pFolder->pTreeNode = node;
    m_folderList.push_back(pFolder);
    ui::GlobalManager::Instance().Icon().AddIcon(hIcon);
    node->SetUserDataID((size_t)pFolder);

    node->SetBkIcon(hIcon);//�������ڵ�Ĺ���ͼ��
    node->AttachExpand(nbase::Bind(&MainForm::OnTreeNodeExpand, this, std::placeholders::_1));
    node->AttachClick(nbase::Bind(&MainForm::OnTreeNodeClick, this, std::placeholders::_1));
    node->AttachSelect(nbase::Bind(&MainForm::OnTreeNodeSelect, this, std::placeholders::_1));

    if (isFolder) {
        pFolder->bShow = false;
        node->SetExpand(false, false);
    }
    else {
        pFolder->bShow = true;
        node->SetExpand(true, false);
    }

    if (pTreeNode == nullptr) {
        pTreeNode = m_pTree->GetRootNode();
    }
    if (pTreeNode != nullptr) {
        pTreeNode->AddChildNode(node);
    }
    return node;
}

void MainForm::ShowVirtualDirectoryNode(int csidl, REFKNOWNFOLDERID rfid, const std::wstring& name)
{
    if (m_hShell32Dll == nullptr) {
        m_hShell32Dll = ::LoadLibraryW(L"Shell32.dll");
    }

    typedef HRESULT (*PFN_SHGetKnownFolderPath)( REFKNOWNFOLDERID rfid,
                                                 DWORD            dwFlags,
                                                 HANDLE           hToken,
                                                 PWSTR * ppszPath );
    typedef HRESULT (*PFN_SHGetKnownFolderIDList)( REFKNOWNFOLDERID rfid,
                                                   DWORD            dwFlags,
                                                   HANDLE           hToken,
                                                   PIDLIST_ABSOLUTE * ppidl );

    PFN_SHGetKnownFolderPath pfnSHGetKnownFolderPath = (PFN_SHGetKnownFolderPath)::GetProcAddress(m_hShell32Dll, "SHGetKnownFolderPath");
    PFN_SHGetKnownFolderIDList pfnSHGetKnownFolderIDList = (PFN_SHGetKnownFolderIDList)::GetProcAddress(m_hShell32Dll, "SHGetKnownFolderIDList");

    TCHAR folder[MAX_PATH] = { 0 };
    LPITEMIDLIST lpPidl = nullptr;

    if (pfnSHGetKnownFolderPath != nullptr) {
        PWSTR ppszPath = nullptr;
        pfnSHGetKnownFolderPath(rfid, 0, nullptr, &ppszPath);
        wcscpy_s(folder, ppszPath);
        if (ppszPath != nullptr) {
            ::CoTaskMemFree(ppszPath);
        }
    }

    if (pfnSHGetKnownFolderIDList != nullptr) {
        pfnSHGetKnownFolderIDList(rfid, 0, nullptr, &lpPidl);
    }

    if (folder[0] == L'\0') {
        if (csidl < 0) {
            return;
        }
        if (!::SHGetSpecialFolderPath(nullptr, folder, csidl, FALSE)) {
            return;
        }
    }

    if (lpPidl == nullptr) {
        if (csidl < 0) {
            return;
        }
        HRESULT hr = ::SHGetSpecialFolderLocation(GetHWND(), csidl, &lpPidl);
        if ((hr != S_OK) || (lpPidl == nullptr)) {
            return;
        }
    }

    SHFILEINFO shFileInfo = { 0 };
    if (::SHGetFileInfo((LPCTSTR)lpPidl,
        0,
        &shFileInfo,
        sizeof(SHFILEINFO),
        SHGFI_PIDL | SHGFI_DISPLAYNAME | SHGFI_ICON | SHGFI_SMALLICON)) {
        std::wstring displayName = shFileInfo.szDisplayName;
        if (displayName.empty()) {
            displayName = name;
        }
        InsertTreeNode(nullptr, displayName, folder, true, shFileInfo.hIcon);
    }

    if (lpPidl != nullptr) {
        ::CoTaskMemFree(lpPidl);
    }
}

ui::TreeNode* MainForm::ShowAllDiskNode()
{
    ui::TreeNode* pFirstNode = nullptr;
    std::vector<std::wstring> driveList;
    DiskUtils::GetLogicalDriveList(driveList);
    for (auto iter = driveList.begin(); iter != driveList.end(); ++iter) {
        std::wstring driverName = *iter;
        // ����A:�̺�B:��
        if (ui::StringHelper::IsEqualNoCase(driverName, L"A:\\") ||
            ui::StringHelper::IsEqualNoCase(driverName, L"B:\\")) {
            continue;
        }

        uint32_t type = ::GetDriveType(driverName.c_str());
        if ((type != DRIVE_FIXED) && (type != DRIVE_REMOVABLE)) {
            continue;
        }

        if (!ui::StringHelper::IsExistsPath(driverName)) {
            continue;
        }

        std::wstring name;
        int32_t imageIndex = 0;

        SHFILEINFO shFileInfo;
        ZeroMemory(&shFileInfo, sizeof(SHFILEINFO));
        if (::SHGetFileInfo(driverName.c_str(), 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON | SHGFI_DISPLAYNAME)) {      
            ui::TreeNode* pNewNode = InsertTreeNode(nullptr, shFileInfo.szDisplayName, driverName, true, shFileInfo.hIcon);
            if (pFirstNode == nullptr) {
                pFirstNode = pNewNode;
            }
        }
    }
    return pFirstNode;
}

bool MainForm::OnTreeNodeExpand(const ui::EventArgs& args)
{
    ui::TreeNode* pTreeNode = dynamic_cast<ui::TreeNode*>(args.pSender);
    ASSERT(pTreeNode != nullptr);
    if (pTreeNode != nullptr) {
        FolderStatus* pFolder = (FolderStatus*)pTreeNode->GetUserDataID();
        auto iter = std::find(m_folderList.begin(), m_folderList.end(), pFolder);
        if (iter != m_folderList.end()) {
            //������Ŀ¼�б�
            if (!pFolder->bShow) {
                pFolder->bShow = true;
                ShowSubFolders(pTreeNode, pFolder->path);                
            }
        }
    }
    return true;
}

void MainForm::CheckExpandTreeNode(ui::TreeNode* pTreeNode, const std::wstring& filePath)
{
    if (pTreeNode == nullptr) {
        return;
    }
    FolderStatus* pFolder = (FolderStatus*)pTreeNode->GetUserDataID();
    auto iter = std::find(m_folderList.begin(), m_folderList.end(), pFolder);
    if (iter == m_folderList.end()) {
        return;
    }

    if (!pFolder->bShow) {
        //������Ŀ¼�б�
        pFolder->bShow = true;
        ShowSubFolders(pTreeNode, pFolder->path);
    }
    else {
        //չ����Ŀ¼
        if (!pTreeNode->IsExpand()) {
            pTreeNode->SetExpand(true, true);
        }
    }
    if (filePath.empty()) {
        return;
    }
    //����ShowSubFolders�������߳���ִ�еģ���������ҲҪ�ȷ������̣߳���ת��UI�̣߳���֤ʱ����ȷ
    nbase::ThreadManager::PostTask(kThreadWorker, ToWeakCallback([this, pTreeNode, filePath]() {
        //��δ����ڹ����߳���ִ�У�ö��Ŀ¼������ɺ�Ȼ�󷢸�UI�߳���ӵ����ڵ���
        nbase::ThreadManager::PostTask(kThreadUI, ToWeakCallback([this, pTreeNode, filePath]() {
            //��δ�����UI�߳���ִ��
            for (const FolderStatus* folder : m_folderList) {
                if (folder->path == filePath) {
                    ui::TreeNode* pSubTreeNode = folder->pTreeNode;
                    if (pSubTreeNode != nullptr) {
                        pSubTreeNode->Activate();
                    }
                }
            }
        }));
    }));
}

void MainForm::ShowSubFolders(ui::TreeNode* pTreeNode, const std::wstring& path)
{
    nbase::ThreadManager::PostTask(kThreadWorker, ToWeakCallback([this, path, pTreeNode]() {
        //��δ����ڹ����߳���ִ�У�ö��Ŀ¼������ɺ�Ȼ�󷢸�UI�߳���ӵ����ڵ���
        std::wstring findPath = ui::StringHelper::JoinFilePath(path, L"*.*");
        WIN32_FIND_DATA findData;
        HANDLE hFile = ::FindFirstFile(findPath.c_str(), &findData);
        if (hFile == INVALID_HANDLE_VALUE) {
            return;
        }

        std::vector<FolderStatus> folderList;
        std::vector<FolderStatus> fileList;

        do {
            if ((findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
                continue;
            }

            if (ui::StringHelper::IsEqualNoCase(findData.cFileName, L".") ||
                ui::StringHelper::IsEqualNoCase(findData.cFileName, L"..")) {
                continue;
            }

            std::wstring folderPath = ui::StringHelper::JoinFilePath(path, findData.cFileName);

            SHFILEINFO shFileInfo;
            ZeroMemory(&shFileInfo, sizeof(SHFILEINFO));
            if (::SHGetFileInfo(folderPath.c_str(), 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON)) {
#ifdef _DEBUG
                //������hIcon�����Ч�������ԭ��δ֪����ʱ���˵�                
                if (shFileInfo.hIcon != nullptr) {
                    ICONINFO iconInfo = { 0, };
                    if (!::GetIconInfo(shFileInfo.hIcon, &iconInfo)) {
                        ::DestroyIcon(shFileInfo.hIcon);
                        shFileInfo.hIcon = nullptr;
                    }
                    else {
                        if (iconInfo.hbmColor != nullptr) {
                            ::DeleteObject(iconInfo.hbmColor);
                        }
                        if (iconInfo.hbmMask != nullptr) {
                            ::DeleteObject(iconInfo.hbmMask);
                        }
                    }
                }
#endif
                if (IsDirectory(folderPath)) {
                    //Ŀ¼
                    folderList.push_back({ findData.cFileName, false, shFileInfo.hIcon });
                }
                else {
                    //�ļ�
                    fileList.push_back({ findData.cFileName, false, shFileInfo.hIcon });
                }
            }
        } while (::FindNextFile(hFile, &findData));
        ::FindClose(hFile);
        hFile = INVALID_HANDLE_VALUE;

        nbase::ThreadManager::PostTask(kThreadUI, ToWeakCallback([this, path, pTreeNode, folderList]() {
            //��δ�����UI�߳���ִ��
            InsertTreeNodes(pTreeNode, path, folderList, true);
            if (!pTreeNode->IsExpand()) {
                pTreeNode->SetExpand(true, true);
            }
        }));
    }));
}

bool MainForm::OnTreeNodeClick(const ui::EventArgs& args)
{
    ui::TreeNode* pTreeNode = dynamic_cast<ui::TreeNode*>(args.pSender);
    ASSERT(pTreeNode != nullptr);
    if (pTreeNode != nullptr) {
        FolderStatus* pFolder = (FolderStatus*)pTreeNode->GetUserDataID();
        auto iter = std::find(m_folderList.begin(), m_folderList.end(), pFolder);
        if (iter != m_folderList.end()) {
            //������Ŀ¼�б��Ҳ�����
            ShowFolderContents(pTreeNode, pFolder->path);
        }
    }
    return true;
}

bool MainForm::OnTreeNodeSelect(const ui::EventArgs& args)
{
    if ((m_pTree != nullptr) && m_pTree->IsMultiSelect()) {
        //��ѡ��ʱ�򣬲���Ӧѡ���¼�
        return true;
    }
    return OnTreeNodeClick(args);
}

bool MainForm::IsDirectory(const std::wstring& filePath) const
{
    DWORD dwAttr = ::GetFileAttributes(filePath.c_str());
    if (dwAttr != INVALID_FILE_ATTRIBUTES) {
        return dwAttr & FILE_ATTRIBUTE_DIRECTORY;
    }
    return false;
}

void MainForm::ShowFolderContents(ui::TreeNode* pTreeNode, const std::wstring& path)
{
    nbase::ThreadManager::PostTask(kThreadWorker, ToWeakCallback([this, pTreeNode, path]() {
        //��δ����ڹ����߳���ִ�У�ö��Ŀ¼������ɺ�Ȼ�󷢸�UI�߳���ӵ����ڵ���
        std::wstring findPath = ui::StringHelper::JoinFilePath(path, L"*.*");
        WIN32_FIND_DATA findData;
        HANDLE hFile = ::FindFirstFile(findPath.c_str(), &findData);
        if (hFile == INVALID_HANDLE_VALUE) {
            return;
        }

        std::vector<FolderStatus> folderList;
        std::vector<FolderStatus> fileList;

        do {
            if ((findData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) &&
                (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)) {
                continue;
            }

            if (ui::StringHelper::IsEqualNoCase(findData.cFileName, L".") ||
                ui::StringHelper::IsEqualNoCase(findData.cFileName, L"..")) {
                continue;
            }

            std::wstring folderPath = ui::StringHelper::JoinFilePath(path, findData.cFileName);

            SHFILEINFO shFileInfo;
            ZeroMemory(&shFileInfo, sizeof(SHFILEINFO));
            if (::SHGetFileInfo(folderPath.c_str(), 0, &shFileInfo, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_LARGEICON)) {
                if (IsDirectory(folderPath)) {
                    //Ŀ¼
                    folderList.push_back({ findData.cFileName, false, shFileInfo.hIcon });
                }
                else {
                    //�ļ�
                    fileList.push_back({ findData.cFileName, false, shFileInfo.hIcon });
                }
            }
        } while (::FindNextFile(hFile, &findData));
        ::FindClose(hFile);
        hFile = INVALID_HANDLE_VALUE;

        std::vector<FileInfo> pathList;
        std::wstring folderPath;
        for (const FolderStatus& folder : folderList) {
            folderPath = ui::StringHelper::JoinFilePath(path, folder.path);
            pathList.push_back({ folder.path, folderPath, true, folder.hIcon });
        }
        for (const FolderStatus& folder : fileList) {
            folderPath = ui::StringHelper::JoinFilePath(path, folder.path);
            pathList.push_back({ folder.path, folderPath, false, folder.hIcon });
        }

        //����UI�߳�
        nbase::ThreadManager::PostTask(kThreadUI, ToWeakCallback([this, pTreeNode, path, pathList]() {
            //��δ�����UI�߳���ִ��
            if (m_pTree != nullptr) {
                if (!m_pTree->IsMultiSelect()) {
                    //��ѡ������У��
                    if (pTreeNode->IsSelected()) {
                        m_fileList.SetFileList(pTreeNode, pathList);
                    }
                }
                else {
                    //��ѡ����У��
                    m_fileList.SetFileList(pTreeNode, pathList);
                }
            }            
        }));
    }));
}
