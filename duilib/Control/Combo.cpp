#include "Combo.h"
#include "duilib/Core/Window.h"
#include "duilib/Utils/Macros.h"
#include "duilib/Box/ListBox.h"
#include "duilib/Box/HBox.h"

namespace ui
{

/** �����б���
*/
class CComboWnd: public Window
{
public:
    void InitComboWnd(Combo* pOwner, bool bActivated);
	void UpdateComboWnd();
    virtual std::wstring GetWindowClassName() const override;
	virtual void OnFinalMessage(HWND hWnd) override;
	virtual LRESULT OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/** �ر�������
	* @param [in] bCanceled true��ʾȡ���������ʾ�����ر�
	* @param [in] needUpdateSelItem true��ʾ��Ҫ����ѡ���������Ҫ����ѡ����
	*/
	void CloseComboWnd(bool bCanceled, bool needUpdateSelItem);

	/** ��ǰ�Ƿ�Ϊ���㴰��
	*/
	bool IsFocusWindow() const;

private:
	//������Combo�ӿ�
    Combo* m_pOwner = nullptr;

	//ԭ����ѡ��������
    size_t m_iOldSel = Box::InvalidIndex;

	//ԭ��Edit�ؼ����ı�����
	UiString m_editText;

	//�Ƿ��Ѿ��ر�
	bool m_bIsClosed = false;
};

void CComboWnd::InitComboWnd(Combo* pOwner, bool bActivated)
{
	ASSERT(pOwner != nullptr);
	if (pOwner == nullptr) {
		return;
	}
    m_pOwner = pOwner;
    m_iOldSel = m_pOwner->GetCurSel();
	m_editText = m_pOwner->GetText();
	m_bIsClosed = false;
    CreateWnd(pOwner->GetWindow()->GetHWND(), L"", WS_POPUP, WS_EX_TOOLWINDOW);
	UpdateComboWnd();
	if (bActivated) {
		HWND hWndParent = GetHWND();
		while (::GetParent(hWndParent) != NULL) {
			hWndParent = ::GetParent(hWndParent);
		}
		::ShowWindow(GetHWND(), SW_SHOW);
		::SetForegroundWindow(GetHWND());
		::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
		pOwner->GetTreeView()->SetFocus();
		pOwner->SetState(kControlStateHot);
	}
	else {
		::ShowWindow(GetHWND(), SW_SHOWNOACTIVATE);
	}
	if (Box::IsValidItemIndex(m_iOldSel)) {
		//չ����ʱ��ȷ��ѡ��ɼ�
		::UpdateWindow(GetHWND());
		UiRect rc = pOwner->GetTreeView()->GetPos();
		pOwner->GetTreeView()->EnsureVisible(m_iOldSel, ListBoxVerVisible::kVisibleAtCenter);
	}
}

void CComboWnd::UpdateComboWnd()
{
	Combo* pOwner = m_pOwner;
	if (pOwner == nullptr) {
		return;
	}
	// Position the popup window in absolute space
	UiSize szDrop = pOwner->GetDropBoxSize();
	UiRect rcOwner = pOwner->GetPos();
	UiPoint scrollBoxOffset = pOwner->GetScrollOffsetInScrollBox();
	rcOwner.Offset(-scrollBoxOffset.x, -scrollBoxOffset.y);

	UiRect rc = rcOwner;
	rc.top = rc.bottom + 1;		    // ������left��bottomλ����Ϊ�����������
	rc.bottom = rc.top + szDrop.cy;	// ���㵯�����ڸ߶�
	if (szDrop.cx > 0) {
		rc.right = rc.left + szDrop.cx;	// ���㵯�����ڿ��
	}

	int32_t cyFixed = 0;
	if (pOwner->GetTreeView()->GetItemCount() > 0) {
		UiSize szAvailable(rc.Width(), rc.Height());
		UiFixedInt oldFixedHeight = pOwner->GetTreeView()->GetFixedHeight();
		pOwner->GetTreeView()->SetFixedHeight(UiFixedInt::MakeAuto(), false, false);
		UiEstSize estSize = pOwner->GetTreeView()->EstimateSize(szAvailable);
		pOwner->GetTreeView()->SetFixedHeight(oldFixedHeight, false, false);
		cyFixed = estSize.cy.GetInt32();
	}
	if (cyFixed == 0) {
		cyFixed = szDrop.cy;
	}
	rc.bottom = rc.top + std::min(cyFixed, szDrop.cy);

	pOwner->GetWindow()->MapWindowRect(rc);

	UiRect rcWork;
	GetMonitorWorkRect(rcWork);
	if (rc.bottom > rcWork.bottom || m_pOwner->IsPopupTop()) {
		rc.left = rcOwner.left;
		rc.right = rcOwner.right;
		if (szDrop.cx > 0) {
			rc.right = rc.left + szDrop.cx;
		}
		rc.top = rcOwner.top - std::min(cyFixed, szDrop.cy);
		rc.bottom = rcOwner.top;
		pOwner->GetWindow()->MapWindowRect(rc);
	}
	SetWindowPos(nullptr, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
}

std::wstring CComboWnd::GetWindowClassName() const
{
    return L"ComboWnd";
}

void CComboWnd::OnFinalMessage(HWND hWnd)
{
	if (m_pOwner != nullptr) {
		if (m_pOwner->GetTreeView()->GetWindow() == this) {
			m_pOwner->GetTreeView()->SetWindow(nullptr);
			m_pOwner->GetTreeView()->SetParent(nullptr);
		}
		if (m_pOwner->m_pWindow == this) {			
			m_pOwner->m_pWindow = nullptr;
			m_pOwner->SetState(kControlStateNormal);
			m_pOwner->Invalidate();
		}
	}
	__super::OnFinalMessage(hWnd);
    delete this;
}

void CComboWnd::CloseComboWnd(bool bCanceled, bool needUpdateSelItem)
{
	if (m_bIsClosed) {
		return;
	}
	m_bIsClosed = true;
	Box* pRootBox = GetRoot();
	if ((pRootBox != nullptr) && (pRootBox->GetItemCount() > 0)) {
		m_pOwner->GetTreeView()->SetWindow(nullptr);
		m_pOwner->GetTreeView()->SetParent(nullptr);
		pRootBox->RemoveAllItems();
	}
	//�Ƚ�ǰ�˴����л�Ϊ�����ڣ�����ǰ�˴��ڹرպ��л�����������
	HWND hWnd = GetHWND();
	HWND hParentWnd = ::GetParent(hWnd);
	HWND hForeWnd = ::GetForegroundWindow();
	if ((hForeWnd == hWnd) || hForeWnd == hParentWnd) {
		if (hParentWnd != nullptr) {
			::SetForegroundWindow(hParentWnd);
		}		
	}
	CloseWnd();
	if (m_pOwner != nullptr) {
		if (bCanceled) {
			m_pOwner->GetTreeView()->SelectItem(m_iOldSel, false, false);
		}
		m_pOwner->OnComboWndClosed(bCanceled, needUpdateSelItem, m_editText.c_str());
	}
}

bool CComboWnd::IsFocusWindow() const
{
	return ::GetFocus() == GetHWND();
}

LRESULT CComboWnd::OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	bHandled = false;
    if( uMsg == WM_CREATE ) {
		InitWnd(GetHWND());
		Box* pRoot = new Box;
		pRoot->SetAutoDestroyChild(false);
		pRoot->AddItem(m_pOwner->GetTreeView());
		AttachBox(pRoot);
		SetResourcePath(m_pOwner->GetWindow()->GetResourcePath());
		SetShadowAttached(false);
		SetRenderTransparent(true);
		bHandled = true;
    }
    else if( uMsg == WM_CLOSE ) {
		Box* pRootBox = GetRoot();
		if ((pRootBox != nullptr) && (pRootBox->GetItemCount() > 0)) {
			m_pOwner->GetTreeView()->SetWindow(nullptr);
			m_pOwner->GetTreeView()->SetParent(nullptr);
			pRootBox->RemoveAllItems();
		}
        m_pOwner->SetPos(m_pOwner->GetPos());
        m_pOwner->SetFocus();
    }
	LRESULT lResult = 0;
	if (!bHandled) {
		lResult = __super::OnWindowMessage(uMsg, wParam, lParam, bHandled);
	}
	if (uMsg == WM_KILLFOCUS) {
		//ʧȥ���㣬�رմ��ڣ������ر�
		if (GetHWND() != (HWND)wParam) {
			CloseComboWnd(false, false);
		}
	}
	else if (uMsg == WM_KEYDOWN && wParam == VK_ESCAPE) {
		//��סESC����ȡ��
		CloseComboWnd(true, false);
	}
	else if (uMsg == WM_KEYDOWN && wParam == VK_RETURN) {
		//���س������رմ��ڣ������ر�
		CloseComboWnd(false, true);
	}
	return lResult;
}

////////////////////////////////////////////////////////

Combo::Combo() :
    m_pWindow(nullptr),
	m_bPopupTop(false),
	m_iCurSel(Box::InvalidIndex),
	m_pIconControl(nullptr),
	m_pEditControl(nullptr),
	m_pButtonControl(nullptr),
	m_comboType(kCombo_DropDown),
	m_bDropListShown(false)
{
	//��Ҫ�������ú������ڲ���DPI����Ӧ���߼�������С
	SetDropBoxSize({ 0, 150 }, true);
	m_treeView.SetSelectNextWhenActiveRemoved(false);
    m_treeView.AttachSelect(nbase::Bind(&Combo::OnSelectItem, this, std::placeholders::_1));
}

Combo::~Combo()
{
	if (!IsInited()) {
		if (m_pIconControl != nullptr) {
			delete m_pIconControl;
			m_pIconControl = nullptr;
		}
		if (m_pEditControl != nullptr) {
			delete m_pEditControl;
			m_pEditControl = nullptr;
		}
		if (m_pButtonControl != nullptr) {
			delete m_pButtonControl;
			m_pButtonControl = nullptr;
		}
	}
}

std::wstring Combo::GetType() const { return DUI_CTR_COMBO; }

void Combo::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == L"combo_type") {
		if (strValue == L"drop_list") {
			SetComboType(kCombo_DropList);
		}
		else if (strValue == L"drop_down") {
			SetComboType(kCombo_DropDown);
		}
	}
	else if ((strName == L"dropbox_size") || (strName == L"dropboxsize") ) {
		//���������б�Ĵ�С����Ⱥ͸߶ȣ�
		UiSize szDropBoxSize;
		AttributeUtil::ParseSizeValue(strValue.c_str(), szDropBoxSize);
		SetDropBoxSize(szDropBoxSize, true);
	}
	else if ((strName == L"popup_top") || (strName == L"popuptop")) {
		//�����б��Ƿ����ϵ���
		SetPopupTop(strValue == L"true");
	}
	else if (strName == L"combo_tree_view_class") {
		SetComboTreeClass(strValue);
	}
	else if (strName == L"combo_tree_node_class") {
		SetComboTreeNodeClass(strValue);
	}
	else if (strName == L"combo_icon_class") {
		SetIconControlClass(strValue);
	}
	else if (strName == L"combo_edit_class") {
		SetEditControlClass(strValue);
	}
	else if (strName == L"combo_button_class") {
		SetButtonControlClass(strValue);
	}
	else {
		__super::SetAttribute(strName, strValue);
	}
}

void Combo::SetComboTreeClass(const std::wstring& classValue)
{
	SetAttributeList(&m_treeView, classValue);
}

void Combo::SetComboTreeNodeClass(const std::wstring& classValue)
{
	m_treeNodeClass = classValue;
}

void Combo::SetIconControlClass(const std::wstring& classValue)
{
	if (classValue.empty()) {
		RemoveControl(m_pIconControl);
		if (m_pIconControl != nullptr) {
			delete m_pIconControl;
			m_pIconControl = nullptr;
		}
	}
	else {
		if (m_pIconControl == nullptr) {
			m_pIconControl = new Control;
		}
		SetAttributeList(m_pIconControl, classValue);
	}
}

void Combo::SetEditControlClass(const std::wstring& classValue)
{
	if (classValue.empty()) {
		RemoveControl(m_pEditControl);
		if (m_pEditControl != nullptr) {
			delete m_pEditControl;
			m_pEditControl = nullptr;
		}
	}
	else {
		if (m_pEditControl == nullptr) {
			m_pEditControl = new RichEdit;
		}
		SetAttributeList(m_pEditControl, classValue);
	}	
}

void Combo::SetButtonControlClass(const std::wstring& classValue)
{
	if (classValue.empty()) {
		RemoveControl(m_pButtonControl);
		if (m_pButtonControl != nullptr) {
			delete m_pButtonControl;
			m_pButtonControl = nullptr;
		}
	}
	else {
		if (m_pButtonControl == nullptr) {
			m_pButtonControl = new Button;
		}
		SetAttributeList(m_pButtonControl, classValue);
	}
}

void Combo::ParseAttributeList(const std::wstring& strList,
							   std::vector<std::pair<std::wstring, std::wstring>>& attributeList) const
{
	if (strList.empty()) {
		return;
	}
	std::wstring strValue = strList;
	//������ֹ�д������ԣ��Ի�����{}����˫���ţ���д��ʱ��Ͳ���Ҫת���ַ��ˣ�
	StringHelper::ReplaceAll(L"{", L"\"", strValue);
	StringHelper::ReplaceAll(L"}", L"\"", strValue);
	if (strValue.find(L"\"") != std::wstring::npos) {
		AttributeUtil::ParseAttributeList(strValue, L'\"', attributeList);
	}
	else if (strValue.find(L"\'") != std::wstring::npos) {
		AttributeUtil::ParseAttributeList(strValue, L'\'', attributeList);
	}
}

void Combo::SetAttributeList(Control* pControl, const std::wstring& classValue)
{
	std::vector<std::pair<std::wstring, std::wstring>> attributeList;
	ParseAttributeList(classValue, attributeList);
	if (!attributeList.empty()) {
		//�������б�����
		for (const auto& attribute : attributeList) {
			pControl->SetAttribute(attribute.first, attribute.second);
		}
	}
	else if(!classValue.empty()) {
		//��Class��������
		pControl->SetClass(classValue);
	}
}

void Combo::RemoveControl(Control* pControl)
{
	if (IsInited() && (GetItemCount() > 0)) {
		HBox* pBox = dynamic_cast<HBox*>(GetItemAt(0));
		if (pBox != nullptr) {
			pBox->RemoveItem(pControl);
		}
	}
}

bool Combo::CanPlaceCaptionBar() const
{
	return true;
}

std::wstring Combo::GetBorderColor(ControlStateType stateType) const
{
	std::wstring borderColor;
	if (m_pIconControl != nullptr) {
		if (m_pIconControl->IsFocused() || m_pIconControl->IsMouseFocused()) {
			borderColor = __super::GetBorderColor(kControlStateHot);
		}
	}
	if (borderColor.empty() && (m_pEditControl != nullptr)) {
		if (m_pEditControl->IsFocused() || m_pEditControl->IsMouseFocused()) {
			borderColor = __super::GetBorderColor(kControlStateHot);
		}
	}
	if (borderColor.empty() && (m_pButtonControl != nullptr)) {
		if (m_pButtonControl->IsFocused() || m_pButtonControl->IsMouseFocused()) {
			borderColor = __super::GetBorderColor(kControlStateHot);
		}
	}
	if (borderColor.empty() && (m_pWindow != nullptr) && !m_pWindow->IsClosingWnd()) {
		borderColor = __super::GetBorderColor(kControlStateHot);
	}
	if (borderColor.empty()) {
		borderColor = __super::GetBorderColor(stateType);
	}
	return borderColor;
}

void Combo::OnInit()
{
	if (IsInited()) {
		return;
	}
	__super::OnInit();

	HBox* pBox = new HBox;	
	AddItem(pBox);
	pBox->SetNoFocus();
	AttachMouseEvents(pBox);

	if (m_pIconControl != nullptr) {		
		pBox->AddItem(m_pIconControl);
		AttachMouseEvents(m_pIconControl);
	}
	if (m_pEditControl != nullptr) {
		pBox->AddItem(m_pEditControl);
	}
	if (m_pButtonControl != nullptr) {
		pBox->AddItem(m_pButtonControl);
		AttachMouseEvents(m_pButtonControl);
	}

	if (m_pIconControl != nullptr) {
		m_pIconControl->SetNoFocus();
	}
	if (m_pButtonControl != nullptr) {
		m_pButtonControl->SetNoFocus();		
		m_pButtonControl->AttachButtonDown(nbase::Bind(&Combo::OnButtonDown, this, std::placeholders::_1));
		m_pButtonControl->AttachClick(nbase::Bind(&Combo::OnButtonClicked, this, std::placeholders::_1));
	}
	if (m_pEditControl != nullptr) {
		m_pEditControl->SetNeedReturnMsg(true);
		m_pEditControl->AttachButtonDown(nbase::Bind(&Combo::OnEditButtonDown, this, std::placeholders::_1));
		m_pEditControl->AttachButtonUp(nbase::Bind(&Combo::OnEditButtonUp, this, std::placeholders::_1));
		m_pEditControl->AttachEvent(kEventKeyDown, nbase::Bind(&Combo::OnEditKeyDown, this, std::placeholders::_1));
		m_pEditControl->AttachSetFocus(nbase::Bind(&Combo::OnEditSetFocus, this, std::placeholders::_1));
		m_pEditControl->AttachKillFocus(nbase::Bind(&Combo::OnEditKillFocus, this, std::placeholders::_1));
		m_pEditControl->AttachEvent(kEventWindowKillFocus, nbase::Bind(&Combo::OnWindowKillFocus, this, std::placeholders::_1));
		m_pEditControl->AttachEvent(kEventWindowMove, nbase::Bind(&Combo::OnWindowMove, this, std::placeholders::_1));
		m_pEditControl->AttachTextChange(nbase::Bind(&Combo::OnEditTextChanged, this, std::placeholders::_1));
	}
	SetNoFocus();
	SetComboType(GetComboType());
}

TreeView* Combo::GetTreeView()
{
	return &m_treeView;
}

Control* Combo::GetIconControl() const
{
	return m_pIconControl;
}

RichEdit* Combo::GetEditControl() const
{
	return m_pEditControl;
}

Button* Combo::GetButtonContrl() const
{
	return m_pButtonControl;
}

void Combo::SetComboType(ComboType comboType)
{
	if (comboType == kCombo_DropList) {
		m_comboType = kCombo_DropList;
		if (m_pEditControl != nullptr) {
			//����Ϊֻ��������ʾ���
			m_pEditControl->SetReadOnly(true);
			m_pEditControl->SetNoCaretReadonly();
			m_pEditControl->SetCursorType(kCursorArrow);
			m_pEditControl->SetUseControlCursor(true);
		}
	}
	else if (comboType == kCombo_DropDown) {
		m_comboType = kCombo_DropDown;
		if (m_pEditControl != nullptr) {
			m_pEditControl->SetReadOnly(false);
			m_pEditControl->SetUseControlCursor(false);
		}
	}
}

Combo::ComboType Combo::GetComboType() const
{
	if (m_comboType == kCombo_DropList) {
		return kCombo_DropList;
	}
	else if (m_comboType == kCombo_DropDown) {
		return kCombo_DropDown;
	}
	return kCombo_DropList;
}

UiSize Combo::GetDropBoxSize() const
{
    return m_szDropBox;
}

void Combo::SetDropBoxSize(UiSize szDropBox, bool bNeedScaleDpi)
{
	ASSERT(szDropBox.cy > 0);
	if (szDropBox.cy <= 0) {
		return;
	}
	szDropBox.Validate();
	if (bNeedScaleDpi) {
		GlobalManager::Instance().Dpi().ScaleSize(szDropBox);
	}
    m_szDropBox = szDropBox;
}

size_t Combo::GetCount() const
{
	return m_treeView.GetRootNode()->GetDescendantNodeCount();
}

size_t Combo::GetCurSel() const
{ 
	return m_treeView.GetCurSel();
}

bool Combo::SetCurSel(size_t iIndex)
{
	size_t iOldSel = m_iCurSel;
	bool bRet = m_treeView.SelectItem(iIndex, false, false);
	m_iCurSel = m_treeView.GetCurSel();
	OnSelectedItemChanged();
	if (m_iCurSel != iOldSel) {
		Invalidate();
	}
	return bRet;
}

size_t Combo::GetItemData(size_t iIndex) const
{
	Control* pControl = m_treeView.GetItemAt(iIndex);
	if (pControl != nullptr) {
		ASSERT(dynamic_cast<TreeNode*>(pControl) != nullptr);
		return pControl->GetUserDataID();
	}
	return 0;
}

bool Combo::SetItemData(size_t iIndex, size_t itemData)
{
	Control* pControl = m_treeView.GetItemAt(iIndex);
	if (pControl != nullptr) {
		ASSERT(dynamic_cast<TreeNode*>(pControl) != nullptr);
		pControl->SetUserDataID(itemData);
		return true;
	}
	return false;
}

std::wstring Combo::GetItemText(size_t iIndex) const
{
	Control* pControl = m_treeView.GetItemAt(iIndex);
	if (pControl != nullptr) {
		TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
		ASSERT(pTreeNode != nullptr);
		if (pTreeNode != nullptr) {
			return pTreeNode->GetText();
		}		
	}
	return std::wstring();
}

bool Combo::SetItemText(size_t iIndex, const std::wstring& itemText)
{
	Control* pControl = m_treeView.GetItemAt(iIndex);
	if (pControl != nullptr) {
		TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
		ASSERT(pTreeNode != nullptr);
		if (pTreeNode != nullptr) {
			pTreeNode->SetText(itemText);
			return true;
		}
	}
	return false;
}

size_t Combo::AddTextItem(const std::wstring& itemText)
{
	return InsertTextItem(GetCount(), itemText);
}

size_t Combo::InsertTextItem(size_t iIndex, const std::wstring& itemText)
{
	ASSERT(iIndex <= GetCount());
	if (iIndex > GetCount()) {
		return Box::InvalidIndex;
	}
	size_t newIndex = Box::InvalidIndex;
	if (iIndex == GetCount()) {
		//�����������µĽڵ�
		TreeNode* pNewNode = CreateTreeNode(itemText);
		m_treeView.GetRootNode()->AddChildNode(pNewNode);
		newIndex = m_treeView.GetItemIndex(pNewNode);
	}
	else {
		//��ָ��λ�ò����µĽڵ�
		Control* pControl = m_treeView.GetItemAt(iIndex);
		if (pControl != nullptr) {
			TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
			ASSERT(pTreeNode != nullptr);
			if (pTreeNode != nullptr) {
				TreeNode* pParentNode = pTreeNode->GetParentNode();
				ASSERT(pParentNode != nullptr);
				if (pParentNode != nullptr) {
					size_t iChildIndex = pParentNode->GetChildNodeIndex(pTreeNode);
					TreeNode* pNewNode = CreateTreeNode(itemText);
					pParentNode->AddChildNodeAt(pNewNode, iChildIndex);
					newIndex = m_treeView.GetItemIndex(pNewNode);
				}
			}
		}
	}
	ASSERT(newIndex != Box::InvalidIndex);
	return newIndex;
}

bool Combo::DeleteItem(size_t iIndex)
{
	bool bRemoved = false;
	Control* pControl = m_treeView.GetItemAt(iIndex);
	if (pControl != nullptr) {
		TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
		ASSERT(pTreeNode != nullptr);
		if (pTreeNode != nullptr) {
			TreeNode* pParentNode = pTreeNode->GetParentNode();
			ASSERT(pParentNode != nullptr);
			if (pParentNode != nullptr) {
				bRemoved = pParentNode->RemoveChildNode(pTreeNode);
			}
		}
	}
	return bRemoved;
}

void Combo::DeleteAllItems()
{
	m_treeView.GetRootNode()->RemoveAllChildNodes();
}

size_t Combo::SelectTextItem(const std::wstring& itemText, bool bTriggerEvent)
{
	size_t nSelIndex = Box::InvalidIndex;
	size_t itemCount = m_treeView.GetItemCount();
	for (size_t nIndex = 0; nIndex < itemCount; ++nIndex) {
		Control* pControl = m_treeView.GetItemAt(nIndex);
		if (pControl != nullptr) {
			TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
			ASSERT(pTreeNode != nullptr);
			if (pTreeNode != nullptr) {
				if (pTreeNode->GetText() == itemText) {
					nSelIndex = nIndex;
					break;
				}
			}
		}
	}
	if (Box::IsValidItemIndex(nSelIndex)) {
		m_treeView.SelectItem(nSelIndex, false, bTriggerEvent);
	}
	return nSelIndex;
}

TreeNode* Combo::CreateTreeNode(const std::wstring& itemText)
{
	TreeNode* pNewNode = new TreeNode;
	if (!m_treeNodeClass.empty()) {
		SetAttributeList(pNewNode, m_treeNodeClass.c_str());
	}
	pNewNode->SetText(itemText);
	return pNewNode;
}

std::wstring Combo::GetText() const
{
	if (m_pEditControl != nullptr) {
		return m_pEditControl->GetText();
	}
	return std::wstring();
}

void Combo::SetText(const std::wstring& text)
{
	if (m_pEditControl != nullptr) {
		m_pEditControl->SetText(text);
	}
}

bool Combo::OnSelectItem(const EventArgs& /*args*/)
{
	size_t iOldSel = m_iCurSel;
	m_iCurSel = m_treeView.GetCurSel();
	OnSelectedItemChanged();
	if (m_iCurSel != iOldSel) {
		SendEvent(kEventSelect, m_iCurSel, iOldSel);
		Invalidate();
	}
	if (Box::IsValidItemIndex(m_iCurSel) && (m_pWindow != nullptr) && !m_pWindow->IsClosingWnd()) {
		const Control* pControl = m_treeView.GetItemAt(m_iCurSel);
		if ((pControl != nullptr) && (m_pWindow->GetEventClick() == pControl)) {
			//��������������ѡ����ô�ر������б�
			if (m_pWindow != nullptr) {
				m_pWindow->CloseComboWnd(false, false);
			}
		}
	}
	return true;
}

void Combo::OnComboWndClosed(bool bCanceled, bool needUpdateSelItem, const std::wstring& oldEditText)
{
	if (bCanceled) {
		size_t iOldSel = m_iCurSel;
		m_iCurSel = m_treeView.GetCurSel();
		if (m_iCurSel != iOldSel) {
			SendEvent(kEventSelect, m_iCurSel, iOldSel);
			Invalidate();
		}
		SetText(oldEditText);
	}
	if (needUpdateSelItem) {
		OnSelectedItemChanged();
	}
	SendEvent(kEventWindowClose);
	Invalidate();
}

bool Combo::OnButtonDown(const EventArgs& /*args*/)
{
	m_bDropListShown = (m_pWindow != nullptr) ? true : false;
	if (m_pWindow != nullptr) {
		//�������������ʾ״̬�����ٴε����ʱ�򣬹ر�
		HideComboList();
	}
	return true;
}

bool Combo::OnButtonClicked(const EventArgs& /*args*/)
{
	//�����갴�µ�ʱ��������ʾ�б���ô�������ʾ�����б�
	if (!m_bDropListShown) {		
		ShowComboList();
	}
	if (m_comboType == kCombo_DropDown) {
		if (m_pEditControl != nullptr) {
			m_pEditControl->SetFocus();
		}
	}
	return true;
}

bool Combo::OnEditButtonDown(const EventArgs& /*args*/)
{
	if (m_comboType == kCombo_DropList) {
		m_bDropListShown = (m_pWindow != nullptr) ? true : false;
	}
	return true;
}

bool Combo::OnEditButtonUp(const EventArgs& /*args*/)
{
	if (m_comboType == kCombo_DropList) {
		if (m_bDropListShown) {
			//�����갴�µ�ʱ��������ʾ�б���ô�������ʾ�����б�
			return true;
		}
		//��ʾ�����б�
		ShowComboList();
	}
	return true;
}

bool Combo::OnEditKeyDown(const EventArgs& args)
{
	if (m_comboType == kCombo_DropList) {
		return true;
	}
	if (args.wParam == VK_DOWN) {
		if ((m_pWindow == nullptr) || m_pWindow->IsClosingWnd()) {
			//�����¼�ͷ��ʱ��: ��������б�δ��ʾ������ʾ�����б�
			ShowComboList();
		}
		else {
			//�����¼�ͷ��ʱ��: ����Ѿ���ʾ�������ѡ���л�
			const size_t itemCount = GetCount();
			const size_t nCurSel = m_treeView.GetCurSel();
			if (!Box::IsValidItemIndex(nCurSel)) {
				//���δѡ����ʼѡ���һ��
				if (itemCount > 0) {
					m_treeView.SelectItem(0, false, true);
				}
			}
			else {				
				if ((itemCount > 0) && (nCurSel < itemCount)) {
					if (nCurSel == (itemCount - 1)) {
						//����Ѿ������һ���ȡ��ѡ��
						m_treeView.SelectItem(Box::InvalidIndex, false, true);
					}
					else {
						//����������һ���ѡ����һ��
						m_treeView.SelectItem(nCurSel + 1, false, true);
					}
				}
			}
		}
	}
	else if (args.wParam == VK_UP) {
		//�����ϼ�ͷ
		if ((m_pWindow != nullptr) && !m_pWindow->IsClosingWnd()) {
			const size_t itemCount = GetCount();
			const size_t nCurSel = m_treeView.GetCurSel();
			if (Box::IsValidItemIndex(nCurSel)) {
				if (nCurSel == 0) {
					//�Ѿ��ǵ�һ�ȡ��ѡ��
					m_treeView.SelectItem(Box::InvalidIndex, false, true);
				}
				else {
					//���ǵ�һ�ѡ��ǰ��һ��
					m_treeView.SelectItem(nCurSel - 1, false, true);
				}
			}
			else {
				//���δѡ����ѡ�����һ��
				m_treeView.SelectItem(itemCount - 1, false, true);
			}
		}
	}
	else if (args.wParam == VK_ESCAPE) {
		//��סESC����ȡ��
		if (m_pWindow != nullptr) {
			m_pWindow->CloseComboWnd(true, false);
		}
	}
	else if (args.wParam == VK_RETURN) {
		//���س������رմ��ڣ������ر�
		if (m_pWindow != nullptr) {
			m_pWindow->CloseComboWnd(false, false);
		}
	}
	return true;
}

bool Combo::OnEditSetFocus(const EventArgs& /*args*/)
{
	//��RichEdit�ؼ��Ľ���״̬����ΪCombo�Ľ���״̬
	SendEvent(kEventSetFocus);
	return true;
}

bool Combo::OnEditKillFocus(const EventArgs& /*args*/)
{
	if (m_pWindow != nullptr) {
		if (m_pWindow->IsFocusWindow()) {
			return true;
		}
	}
	HideComboList();
	Invalidate();
	//��RichEdit�ؼ��Ľ���״̬����ΪCombo�Ľ���״̬
	SendEvent(kEventKillFocus);
	return true;
}

bool Combo::OnWindowKillFocus(const EventArgs& /*args*/)
{
	if (m_pWindow != nullptr) {
		if (m_pWindow->IsFocusWindow()) {
			return true;
		}
	}
	HideComboList();
	return true;
}

bool Combo::OnWindowMove(const EventArgs& /*args*/)
{
	UpdateComboList();
	return true;
}

void Combo::OnSelectedItemChanged()
{
	if (m_pEditControl != nullptr) {
		size_t nSelIndex = GetCurSel();
		if (Box::IsValidItemIndex(nSelIndex)) {
			m_pEditControl->SetText(GetItemText(nSelIndex));
		}		
	}
}

bool Combo::OnEditTextChanged(const ui::EventArgs& /*args*/)
{
	if ((m_pWindow != nullptr) && !m_pWindow->IsClosingWnd()) {
		std::wstring editText = GetText();
		//ת����Сд���Ƚϵ�ʱ�򣬲����ִ�Сд
		editText = StringHelper::MakeLowerString(editText);
		size_t itemCount = m_treeView.GetItemCount();
		for (size_t iIndex = 0; iIndex < itemCount; ++iIndex) {
			Control* pControl = m_treeView.GetItemAt(iIndex);
			if (pControl != nullptr) {
				TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
				ASSERT(pTreeNode != nullptr);
				if (pTreeNode != nullptr) {
					pTreeNode->SetExpand(true, false);
					std::wstring nodeText = StringHelper::MakeLowerString(pTreeNode->GetText());
					if (nodeText.find(editText) != std::wstring::npos) {
						m_treeView.EnsureVisible(iIndex, ListBoxVerVisible::kVisibleAtCenter);
						break;
					}
				}
			}
		}
	}
	return true;
}

void Combo::ShowComboList()
{
	//��ʾ�����б�
	if ((m_pWindow == nullptr) || m_pWindow->IsClosingWnd()) {
		m_pWindow = new CComboWnd();
		if (m_comboType == kCombo_DropList) {
			m_pWindow->InitComboWnd(this, true);
		}
		else {
			m_pWindow->InitComboWnd(this, false);
		}		
	}
}

void Combo::HideComboList()
{
	if(m_pWindow != nullptr) {
		m_pWindow->CloseComboWnd(false, false);
	}
}

void Combo::UpdateComboList()
{
	if (m_pWindow != nullptr) {
		m_pWindow->UpdateComboWnd();
	}
}

void Combo::UpdateComboWndPos()
{
	if (m_pWindow != nullptr) {
		m_pWindow->UpdateComboWnd();
	}
}

void Combo::AttachMouseEvents(Control* pControl)
{
	if (pControl == nullptr) {
		return;
	}
	auto SetRichEditFocus = [this]() {
		if ((m_pEditControl != nullptr) && m_pEditControl->IsVisible()) {
			if (!m_pEditControl->IsFocused()) {
				m_pEditControl->SetFocus();
			}
		}
		};
	pControl->AttachButtonDown([SetRichEditFocus](const EventArgs&) {
		SetRichEditFocus();
		return true;
		});
	pControl->AttachRButtonDown([SetRichEditFocus](const EventArgs&) {
		SetRichEditFocus();
		return true;
		});
}

void Combo::SetFocus()
{
	//������������Edit�ؼ���
	if (IsNoFocus()) {
		if ((m_pEditControl != nullptr) && m_pEditControl->IsVisible()) {
			if (!m_pEditControl->IsFocused()) {
				m_pEditControl->SetFocus();
			}
		}
	}
	else {
		__super::SetFocus();
	}
}

} // namespace ui
