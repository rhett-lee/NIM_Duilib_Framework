#include "TreeView.h"
#include "duilib/Core/ScrollBar.h"

namespace ui
{

TreeNode::TreeNode() :
	m_bExpand(true),
	m_pTreeView(nullptr),
	m_pParentTreeNode(nullptr),
	m_uDepth(0),
	m_expandCheckBoxPadding(0),
	m_expandIconPadding(0),
	m_expandTextPadding(0),
	m_checkBoxIconPadding(0),
	m_checkBoxTextPadding(0),
	m_iconTextPadding(0),
	m_pExpandImageRect(nullptr),
	m_pCollapseImageRect(nullptr)
{
	m_expandIndent = (uint16_t)ui::GlobalManager::Instance().Dpi().GetScaleInt(4);
	m_checkBoxIndent = (uint16_t)ui::GlobalManager::Instance().Dpi().GetScaleInt(6);
	m_iconIndent = (uint16_t)ui::GlobalManager::Instance().Dpi().GetScaleInt(4);
}

TreeNode::~TreeNode()
{
	if (m_pExpandImageRect != nullptr) {
		delete m_pExpandImageRect;
		m_pExpandImageRect = nullptr;
	}
	if (m_pCollapseImageRect != nullptr) {
		delete m_pCollapseImageRect;
		m_pCollapseImageRect = nullptr;
	}
}

std::wstring TreeNode::GetType() const { return DUI_CTR_TREENODE; }

void TreeNode::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == L"expand_normal_image") {
		SetExpandStateImage(kControlStateNormal, strValue);
	}
	else if (strName == L"expand_hot_image") {
		SetExpandStateImage(kControlStateHot, strValue);
	}
	else if (strName == L"expand_pushed_image") {
		SetExpandStateImage(kControlStatePushed, strValue);
	}
	else if (strName == L"expand_disabled_image") {
		SetExpandStateImage(kControlStateDisabled, strValue);
	}
	else if (strName == L"collapse_normal_image") {
		SetCollapseStateImage(kControlStateNormal, strValue);
	}
	else if (strName == L"collapse_hot_image") {
		SetCollapseStateImage(kControlStateHot, strValue);
	}
	else if (strName == L"collapse_pushed_image") {
		SetCollapseStateImage(kControlStatePushed, strValue);
	}
	else if (strName == L"collapse_disabled_image") {
		SetCollapseStateImage(kControlStateDisabled, strValue);
	}
	else if (strName == L"expand_image_right_space") {
		int32_t iValue = wcstol(strValue.c_str(), nullptr, 10);
		ui::GlobalManager::Instance().Dpi().ScaleInt(iValue);
		m_expandIndent = ui::TruncateToUInt16(iValue);
	}
	else if (strName == L"check_box_image_right_space") {
		int32_t iValue = wcstol(strValue.c_str(), nullptr, 10);
		ui::GlobalManager::Instance().Dpi().ScaleInt(iValue);
		m_checkBoxIndent = ui::TruncateToUInt16(iValue);
	}
	else if (strName == L"icon_image_right_space") {
		int32_t iValue = wcstol(strValue.c_str(), nullptr, 10);
		ui::GlobalManager::Instance().Dpi().ScaleInt(iValue);
		m_iconIndent = ui::TruncateToUInt16(iValue);
	}
	else {
		__super::SetAttribute(strName, strValue);
	}
}

std::wstring TreeNode::GetExpandStateImage(ControlStateType stateType)
{
	Image* pImage = nullptr;
	if (m_expandImage != nullptr) {
		pImage = m_expandImage->GetStateImage(stateType);
	}
	if (pImage != nullptr) {
		return pImage->GetImageString();
	}
	return std::wstring();
}

void TreeNode::SetExpandStateImage(ControlStateType stateType, const std::wstring& strImage)
{
	if (m_expandImage == nullptr) {
		m_expandImage.reset(new StateImage);
		m_expandImage->SetControl(this);
	}
	m_expandImage->SetImageString(stateType, strImage);
}

std::wstring TreeNode::GetCollapseStateImage(ControlStateType stateType)
{
	Image* pImage = nullptr;
	if (m_collapseImage != nullptr) {
		pImage = m_collapseImage->GetStateImage(stateType);
	}
	if (pImage != nullptr) {
		return pImage->GetImageString();
	}
	return std::wstring();
}

void TreeNode::SetCollapseStateImage(ControlStateType stateType, const std::wstring& strImage)
{
	if (m_collapseImage == nullptr) {
		m_collapseImage.reset(new StateImage);
		m_collapseImage->SetControl(this);
	}
	m_collapseImage->SetImageString(stateType, strImage);
}

void TreeNode::PaintStateImages(IRender* pRender)
{
	__super::PaintStateImages(pRender);	
	if (IsExpand()) {
		//����չ��״̬ͼ�꣬���û���ӽڵ㣬����ֻ���ͼ��
		if ((m_expandImage != nullptr) && !m_aTreeNodes.empty()){
			if (m_pExpandImageRect == nullptr) {
				m_pExpandImageRect = new UiRect;
			}
			m_expandImage->PaintStateImage(pRender, GetState(), L"", m_pExpandImageRect);
		}
	}
	else {
		//����δչ��״̬ͼ��
		if (m_collapseImage != nullptr) {
			if (m_pCollapseImageRect == nullptr) {
				m_pCollapseImageRect = new UiRect;
			}
			m_collapseImage->PaintStateImage(pRender, GetState(), L"", m_pCollapseImageRect);
		}
	}
}

bool TreeNode::ButtonDown(const EventArgs& msg)
{
	bool bRet = __super::ButtonDown(msg);
	if (!IsEnabled()) {
		return bRet;
	}
	UiRect pos = GetPos();
	UiPoint pt(msg.ptMouse);
	pt.Offset(GetScrollOffsetInScrollBox());
	if (!pos.ContainsPt(pt)) {
		return bRet;
	}
	if (IsExpand()) {
		//չ��״̬
		if ((m_expandImage != nullptr) && !m_aTreeNodes.empty()) {
			//��������չ��ͼ���ϣ�������
			if ((m_pExpandImageRect != nullptr) && 
				m_pExpandImageRect->ContainsPt(pt)) {
				SetExpand(false, true);
			}
		}
	}
	else {
		//δչ��״̬
		if (m_collapseImage != nullptr) {
			//��������չ��ͼ���ϣ���չ��
			if ((m_pCollapseImageRect != nullptr) && 
				m_pCollapseImageRect->ContainsPt(pt)) {
				SetExpand(true, true);
			}
		}
	}
	return bRet;
}

int32_t TreeNode::GetExpandImagePadding(void) const
{
	int32_t imageWidth = 0;
	Image* pImage = nullptr;
	if (m_collapseImage != nullptr) {
		pImage = m_collapseImage->GetStateImage(kControlStateNormal);
	}
	if(pImage == nullptr){
		if (m_expandImage != nullptr) {
			pImage = m_expandImage->GetStateImage(kControlStateNormal);
		}
	}
	if (pImage != nullptr) {
		if (pImage->GetImageCache() == nullptr) {
			LoadImageData(*pImage);
		}
		if (pImage->GetImageCache() != nullptr) {
			imageWidth = pImage->GetImageCache()->GetWidth();
		}
	}
	if (imageWidth > 0) {
		imageWidth += m_expandIndent;
	}
	return imageWidth;
}

void TreeNode::SetTreeView(TreeView* pTreeView)
{
    m_pTreeView = pTreeView;
}

TreeView* TreeNode::GetTreeView() const
{
	return m_pTreeView;
}

bool TreeNode::OnDoubleClickItem(const EventArgs& args)
{
    TreeNode* pItem = dynamic_cast<TreeNode*>(args.pSender);
	ASSERT(pItem != nullptr);
	if (pItem != nullptr) {
		pItem->SetExpand(!pItem->IsExpand(), true);
	}
    return true;
}

bool TreeNode::OnNodeCheckStatusChanged(const EventArgs& args)
{
	TreeNode* pItem = dynamic_cast<TreeNode*>(args.pSender);
	ASSERT(pItem != nullptr);
	if ((pItem != nullptr) && (m_pTreeView != nullptr)) {
		m_pTreeView->OnNodeCheckStatusChanged(pItem);
	}
	return true;
}

bool TreeNode::IsVisible() const
{
	if (!ListBoxItem::IsVisible()) {
		return false;
	}
	if (m_pParentTreeNode != nullptr) {
		//������ڵ�δչ�������߸��ڵ㲻�ɼ�������ӽڵ�Ҳ���ɼ�
		if (!m_pParentTreeNode->IsExpand() || !m_pParentTreeNode->IsVisible()) {
			return false;
		}
	}
	return true;
}

bool TreeNode::SupportCheckedMode() const
{
	bool bHasStateImages = HasStateImages();
	if (!bHasStateImages || (m_pTreeView == nullptr)) {
		//���û��״̬ͼƬ(CheckBox�򹴵�ͼƬ)������Ĭ��ֵ
		return __super::SupportCheckedMode();
	}
	//��ѡ��ʱ��֧��; ��ѡ��ʱ�򣬲�֧��
	return m_pTreeView->IsMultiCheckMode();
}

TreeNode* TreeNode::GetParentNode() const
{
	return m_pParentTreeNode;
}

void TreeNode::SetParentNode(TreeNode* pParentTreeNode)
{
	m_pParentTreeNode = pParentTreeNode;
}

bool TreeNode::AddChildNode(TreeNode* pTreeNode)
{
	return AddChildNodeAt(pTreeNode, GetChildNodeCount());
}

bool TreeNode::AddChildNodeAt(TreeNode* pTreeNode, const size_t iIndex)
{
	ASSERT(pTreeNode != nullptr);
	if (pTreeNode == nullptr) {
		return false;
	}
	ASSERT(m_pTreeView != nullptr);
	if (m_pTreeView == nullptr) {
		return false;
	}
	ASSERT(iIndex <= m_aTreeNodes.size());
	if (iIndex > m_aTreeNodes.size()) {
		return false;
	}
	ASSERT(std::find(m_aTreeNodes.begin(), m_aTreeNodes.end(), pTreeNode) == m_aTreeNodes.end());
	if (std::find(m_aTreeNodes.begin(), m_aTreeNodes.end(), pTreeNode) != m_aTreeNodes.end()) {
		return false;
	}
	
	ASSERT(m_uDepth <= UINT16_MAX);//���Ϊ65535���㼶
	/*if (m_uDepth >= UINT16_MAX) {
		return false;
	}*/

	pTreeNode->m_uDepth = m_uDepth + 1;
	pTreeNode->SetParentNode(this);
	pTreeNode->SetTreeView(m_pTreeView);
	pTreeNode->SetWindow(GetWindow());

	//����˫���¼�������չ���ӽڵ�
	pTreeNode->AttachEvent(kEventMouseDoubleClick, nbase::Bind(&TreeNode::OnDoubleClickItem, this, std::placeholders::_1));
	
	//������ѡ�¼������ڶ�ѡʱͬ����ѡ�ӽڵ��ͬ�����ڵ����̬ѡ��״̬
	pTreeNode->AttachChecked(nbase::Bind(&TreeNode::OnNodeCheckStatusChanged, this, std::placeholders::_1));
	pTreeNode->AttachUnCheck(nbase::Bind(&TreeNode::OnNodeCheckStatusChanged, this, std::placeholders::_1));

	UiPadding padding = GetPadding();
	
	if (m_uDepth != 0) {
		//�����ǰ���Ǹ��ڵ㣨���ڵ��m_uDepth��0������Ҫ���һ������
		padding.left += m_pTreeView->GetIndent();
	}
	pTreeNode->SetPadding(padding, false);

	//[δչ��/չ��]ͼƬ��־
	std::wstring expandImageClass = m_pTreeView->GetExpandImageClass();
	pTreeNode->SetExpandImageClass(expandImageClass);

	//CheckBoxѡ��
	std::wstring checkBoxClass = m_pTreeView->GetCheckBoxClass();
	pTreeNode->SetCheckBoxClass(checkBoxClass);

	//�Ƿ���ʾͼ��
	pTreeNode->SetEnableIcon(m_pTreeView->IsEnableIcon());

	//��ӵ�ListBox������
	size_t nInsertIndex = GetDescendantNodeMaxListBoxIndex();
	if (!Box::IsValidItemIndex(nInsertIndex)) {
		//��һ���ڵ�
		nInsertIndex = 0;
	}
	else {
		//���ǵ�һ���ڵ�ʱ������λ����Ҫ������������ڵ�ĺ���
		nInsertIndex += 1;
	}
	ASSERT(nInsertIndex <= m_pTreeView->ListBox::GetItemCount());
	m_aTreeNodes.insert(m_aTreeNodes.begin() + iIndex, pTreeNode);
	bool bAdded = m_pTreeView->ListBox::AddItemAt(pTreeNode, nInsertIndex);
	if (bAdded) {
		if (SupportCheckedMode()) {
			//����ӵĽڵ�״̬�����游�ڵ�
			pTreeNode->SetChecked(IsChecked());
			//���½ڵ�Ĺ�ѡ״̬
			UpdateSelfCheckStatus();
			UpdateParentCheckStatus(false);
		}
	}
	else {
		//���ʧ�ܵĻ����Ƴ�
		auto iter = std::find(m_aTreeNodes.begin(), m_aTreeNodes.end(), pTreeNode);
		if (iter != m_aTreeNodes.end()) {
			m_aTreeNodes.erase(iter);
		}
	}
	return bAdded;
}

#ifdef UILIB_IMPL_WINSDK

void TreeNode::SetBkIcon(HICON hIcon)
{
	GlobalManager::Instance().Icon().AddIcon(hIcon);
	std::wstring iconString = GlobalManager::Instance().Icon().GetIconString(hIcon);
	std::wstring oldIconString = GetBkImagePath();
	if (iconString == oldIconString) {
		//û�б仯��ֱ�ӷ���
		return;
	}
	//�ɵ�ͼ���С
	HICON hOldIcon = GlobalManager::Instance().Icon().GetIcon(oldIconString);
	UiSize oldIconSize = GlobalManager::Instance().Icon().GetIconSize(hOldIcon);

	//�µ�ͼ���С
	UiSize newIconSize = GlobalManager::Instance().Icon().GetIconSize(hIcon);

	bool bAdjustIconPadding = true;
	if (!oldIconString.empty()) {
		if (newIconSize.cx != oldIconSize.cx) {
			//��ͼ����ڣ�����ͼ���С��ͬ���������ԭ����ͼ��
			SetBkImage(L"");
			AdjustIconPadding();
		}
		else {
			//�¾�ͼ���С��ͬ������Ҫ����ͼ���ڱ߾�
			bAdjustIconPadding = false;
		}
	}

	if (!iconString.empty()) {
		iconString = StringHelper::Printf(L"file='%s' halign='left' valign='center'", iconString.c_str());
		SetBkImage(iconString);
	}
	else {
		SetBkImage(L"");
	}

	if (bAdjustIconPadding) {
		AdjustIconPadding();
	}

	//�����޸��Ƿ���ʾͼ���־
	if (m_pTreeView != nullptr) {
		SetEnableIcon(m_pTreeView->IsEnableIcon());
	}
}

#endif //UILIB_IMPL_WINSDK

void TreeNode::SetExpandImageClass(const std::wstring& expandClass)
{
	if (!expandClass.empty()) {
		//����չ����־����
		SetClass(expandClass);
	}
	else {
		//�ر�չ����־����
		m_expandImage.reset();
		m_collapseImage.reset();
		if (m_pExpandImageRect != nullptr) {
			delete m_pExpandImageRect;
			m_pExpandImageRect = nullptr;
		}
		if (m_pCollapseImageRect != nullptr) {
			delete m_pCollapseImageRect;
			m_pCollapseImageRect = nullptr;
		}
	}
	AdjustExpandImagePadding();
}

bool TreeNode::SetCheckBoxClass(const std::wstring& checkBoxClass)
{
	bool bSetOk = true;
	if (!checkBoxClass.empty()) {
		//����CheckBox����
		SetClass(checkBoxClass);
		if (!HasStateImage(kStateImageBk) && !HasStateImage(kStateImageSelectedBk)) {
			ASSERT(!"TreeNode::SetCheckBoxClass failed!");
			bSetOk = false;
		}
	}
	else {
		//�ر�CheckBox����
		ClearStateImages();
	}
	AdjustCheckBoxPadding();
	return bSetOk;
}

void TreeNode::AdjustExpandImagePadding()
{
	uint16_t expandPadding = ui::TruncateToUInt8(GetExpandImagePadding());
	if (expandPadding != 0) {
		//��ʾ[չ��/����]��־
		if (m_expandCheckBoxPadding == 0) {
			int32_t leftOffset = (int32_t)expandPadding;
			if (AdjustStateImagesPaddingLeft(leftOffset, false)) {
				m_expandCheckBoxPadding = expandPadding;
			}
		}
		else if (!HasStateImage(kStateImageBk)) {
			//CheckBoxͼ���Ѿ�����
			m_expandCheckBoxPadding = 0;
		}

		if (m_expandIconPadding == 0) {
			//��CheckBox״̬ͼƬ, ��Ҫ���ñ���ͼƬ���ڱ߾࣬��������ͼƬ�ص�
			UiPadding rcBkPadding = GetBkImagePadding();
			rcBkPadding.left += expandPadding;
			if (SetBkImagePadding(rcBkPadding, false)) {
				m_expandIconPadding = expandPadding;
			}
		}

		if (m_expandTextPadding == 0) {
			//�������ֵ��ڱ߾�
			UiPadding rcTextPadding = GetTextPadding();
			rcTextPadding.left += expandPadding;
			SetTextPadding(rcTextPadding, false);
			m_expandTextPadding = expandPadding;
		}
	}
	else {
		//����ʾ[չ��/����]��־
		if (m_expandCheckBoxPadding > 0) {
			int32_t leftOffset = -(int32_t)m_expandCheckBoxPadding;
			AdjustStateImagesPaddingLeft(leftOffset, false);
			m_expandCheckBoxPadding = 0;
		}

		if (m_expandIconPadding > 0) {
			UiPadding rcBkPadding = GetBkImagePadding();
			rcBkPadding.left -= (int32_t)m_expandIconPadding;
			if (rcBkPadding.left >= 0) {
				SetBkImagePadding(rcBkPadding, false);
			}
			m_expandIconPadding = 0;
		}
		if (m_expandTextPadding > 0) {
			UiPadding rcTextPadding = GetTextPadding();
			rcTextPadding.left -= (int32_t)m_expandTextPadding;
			if (rcTextPadding.left >= 0) {
				SetTextPadding(rcTextPadding, false);
			}
			m_expandTextPadding = 0;
		}		
	}
	Invalidate();
}

void TreeNode::AdjustCheckBoxPadding()
{
	if (HasStateImage(kStateImageBk)) {
		//��ʾCheckBox
		uint16_t extraPadding = m_checkBoxIndent;
		UiSize imageSize = GetStateImageSize(kStateImageBk, kControlStateNormal);
		uint16_t checkBoxPadding = TruncateToUInt16(imageSize.cx);
		if (checkBoxPadding > 0) {
			checkBoxPadding += extraPadding;
		}
		
		if ((checkBoxPadding > 0) && (m_checkBoxIconPadding == 0)){
			//��CheckBox״̬ͼƬ, ��Ҫ���ñ���ͼƬ���ڱ߾࣬��������ͼƬ�ص�
			UiPadding rcBkPadding = GetBkImagePadding();
			rcBkPadding.left += checkBoxPadding;
			if (SetBkImagePadding(rcBkPadding, false)) {
				m_checkBoxIconPadding = checkBoxPadding;
			}			
		}

		if ((checkBoxPadding > 0) && (m_checkBoxTextPadding == 0)) {
			//�������ֵ��ڱ߾�
			UiPadding rcTextPadding = GetTextPadding();
			rcTextPadding.left += checkBoxPadding;
			SetTextPadding(rcTextPadding, false);
			m_checkBoxTextPadding = checkBoxPadding;
		}
	}
	else {
		//����CheckBox
		if (m_checkBoxIconPadding > 0) {
			UiPadding rcBkPadding = GetBkImagePadding();
			rcBkPadding.left -= (int32_t)m_checkBoxIconPadding;
			if (rcBkPadding.left >= 0) {
				SetBkImagePadding(rcBkPadding, false);
			}
			m_checkBoxIconPadding = 0;
		}
		if (m_checkBoxTextPadding > 0) {
			UiPadding rcTextPadding = GetTextPadding();
			rcTextPadding.left -= (int32_t)m_checkBoxTextPadding;
			if (rcTextPadding.left >= 0) {
				SetTextPadding(rcTextPadding, false);
			}
			m_checkBoxTextPadding = 0;
		}
	}
	AdjustExpandImagePadding();
}

void TreeNode::AdjustIconPadding()
{
	std::wstring iconString = GetBkImagePath();
	if (!IsBkImagePaintEnabled()) {
		//��ֹ����ͼ��
		iconString.clear();
	}
	if (!iconString.empty()) {
		//��ʾͼ��
		if (m_iconTextPadding == 0) {
			const uint16_t extraPadding = m_iconIndent;
			UiSize imageSize = GetBkImageSize();
			uint16_t iconTextPadding = TruncateToUInt16(imageSize.cx);
			if (iconTextPadding > 0) {
				iconTextPadding += extraPadding;
			}
			if (iconTextPadding > 0) {
				//�������ֵ��ڱ߾�
				UiPadding rcTextPadding = GetTextPadding();
				rcTextPadding.left += iconTextPadding;
				SetTextPadding(rcTextPadding, false);
				m_iconTextPadding = iconTextPadding;
			}
		}
	}
	else {
		//����ͼ��
		if (m_iconTextPadding > 0) {
			UiPadding rcTextPadding = GetTextPadding();
			rcTextPadding.left -= (int32_t)m_iconTextPadding;
			if (rcTextPadding.left >= 0) {
				SetTextPadding(rcTextPadding, false);
			}
			m_iconTextPadding = 0;
		}
	}
	AdjustCheckBoxPadding();
}

void TreeNode::SetEnableIcon(bool bEnable)
{
	if (IsBkImagePaintEnabled() != bEnable) {
		SetBkImagePaintEnabled(bEnable);
		AdjustIconPadding();
	}
}

void TreeNode::SetChildrenCheckStatus(bool bChecked)
{
	if (!SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox������
		return;
	}
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode) {
			pTreeNode->SetChecked(bChecked, false);
			pTreeNode->SetChildrenCheckStatus(bChecked);
		}
	}
}

void TreeNode::UpdateParentCheckStatus(bool bUpdateSelf)
{
	if (!SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox������
		return;
	}
	if (bUpdateSelf) {
		UpdateSelfCheckStatus();
	}
	if (m_pParentTreeNode != nullptr) {
		m_pParentTreeNode->UpdateParentCheckStatus(true);
	}
}

void TreeNode::UpdateSelfCheckStatus()
{
	if (!SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox������
		return;
	}
	bool bChecked = IsChecked();
	TreeNodeCheck nodeCheck = GetChildrenCheckStatus();//�����ӽڵ��ѡ��״̬���޸ĵ�ǰ�ڵ��ѡ��״̬
	if (nodeCheck == TreeNodeCheck::UnCheck) {
		if (!bChecked) {
			return;
		}
		else {
			//����Ϊ��TreeNodeCheck::UnCheck
			SetChecked(false);
			SetPartSelected(false);
			Invalidate();
		}
	}
	else if (nodeCheck == TreeNodeCheck::CheckedAll) {
		//����Ϊ��TreeNodeCheck::CheckedAll
		if (bChecked) {
			if (IsPartSelected()) {
				SetPartSelected(false);
				Invalidate();
			}
		}
		else {			
			SetChecked(true);
			SetPartSelected(false);
			Invalidate();
		}
	}
	else if (nodeCheck == TreeNodeCheck::CheckedPart) {
		//����Ϊ��TreeNodeCheck::CheckedPart
		SetChecked(true);
		SetPartSelected(true);
		Invalidate();
	}
}

TreeNodeCheck TreeNode::GetCheckStatus(void) const
{
	if (!SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox��ֻ����ǰ�ڵ�״̬�жϽ��
		return IsSelected() ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
	}

	//��ѡ
	bool bChecked = IsChecked();
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode == nullptr) {
			continue;
		}
		if (bChecked != pTreeNode->IsChecked()) {
			return TreeNodeCheck::CheckedPart;
		}
	}

	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode == nullptr) {
			continue;
		}
		TreeNodeCheck childCheck = pTreeNode->GetCheckStatus();
		if (bChecked) {
			if (childCheck == TreeNodeCheck::UnCheck) {
				return TreeNodeCheck::CheckedPart;
			}
			else if (childCheck == TreeNodeCheck::CheckedPart) {
				return TreeNodeCheck::CheckedPart;
			}
		}
		else {
			if (childCheck == TreeNodeCheck::CheckedAll) {
				return TreeNodeCheck::CheckedPart;
			}
			else if (childCheck == TreeNodeCheck::CheckedPart) {
				return TreeNodeCheck::CheckedPart;
			}
		}
	}
	return bChecked ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
}

TreeNodeCheck TreeNode::GetChildrenCheckStatus(void) const
{
	if (!SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox��ֻ����ǰ�ڵ�״̬�жϽ��
		return IsSelected() ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
	}

	if (m_aTreeNodes.empty()) {
		//û���ӽڵ㣺���ص�ǰ�ڵ��״̬
		return IsChecked() ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
	}
	//��ѡ: ��ɨ��һ���ӽڵ�
	bool bLastChecked = false;
	bool bSetLastChecked = false;
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode == nullptr) {
			continue;
		}
		bool bChildChecked = pTreeNode->IsChecked();
		if (!bSetLastChecked) {
			bLastChecked = bChildChecked;
			bSetLastChecked = true;
		}
		else {
			if (bLastChecked != bChildChecked) {
				return TreeNodeCheck::CheckedPart;
			}
		}		
	}

	//��ɨ��༶�ӽڵ�
	TreeNodeCheck lastChildCheck = TreeNodeCheck::UnCheck;
	bool bSetLastChildCheck = false;
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode == nullptr){
			continue;
		}
		TreeNodeCheck childSelect = pTreeNode->GetCheckStatus();//��ȡ��������/�ӽڵ�Ĺ�ѡ״̬
		if (childSelect == TreeNodeCheck::CheckedPart) {
			return TreeNodeCheck::CheckedPart;
		}
		if (!bSetLastChildCheck) {
			lastChildCheck = childSelect;
			bSetLastChildCheck = true;
		}
		else {
			if (childSelect != lastChildCheck) {
				return TreeNodeCheck::CheckedPart;
			}
		}
	}

	//���״̬��һ�������ص�һ���ӽڵ��״̬
	TreeNode* pTreeNode = m_aTreeNodes.front();
	if (pTreeNode != nullptr) {
		return pTreeNode->IsChecked() ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
	}
	else {
		return IsChecked() ? TreeNodeCheck::CheckedAll : TreeNodeCheck::UnCheck;
	}
}

bool TreeNode::RemoveChildNodeAt(size_t iIndex, bool bUpdateCheckStatus)
{
	ASSERT(iIndex < m_aTreeNodes.size());
	if (iIndex >= m_aTreeNodes.size()) {
		return false;
	}

	bool bRemoved = false;
	TreeNode* pTreeNode = ((TreeNode*)m_aTreeNodes[iIndex]);
	m_aTreeNodes.erase(m_aTreeNodes.begin() + iIndex);
	if (pTreeNode != nullptr) {
		bRemoved = pTreeNode->RemoveSelf();
	}
	if (bUpdateCheckStatus && SupportCheckedMode()) {
		//���½ڵ�Ĺ�ѡ״̬
		UpdateSelfCheckStatus();
		UpdateParentCheckStatus(false);
	}
	return bRemoved;
}

bool TreeNode::RemoveChildNodeAt(size_t iIndex)
{
	return RemoveChildNodeAt(iIndex, true);
}

bool TreeNode::RemoveChildNode(TreeNode* pTreeNode)
{
	auto it = std::find(m_aTreeNodes.begin(), m_aTreeNodes.end(), pTreeNode);
	if (it == m_aTreeNodes.end()) {
		return false;
	}		
	size_t iIndex = it - m_aTreeNodes.begin();
	return RemoveChildNodeAt(iIndex, true);
}
	
void TreeNode::RemoveAllChildNodes()
{
	while (m_aTreeNodes.size() > 0) {
		RemoveChildNodeAt(0, false);
	}
}

bool TreeNode::RemoveSelf()
{
	for(TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode != nullptr) {
			pTreeNode->RemoveSelf();
		}
	}
	m_aTreeNodes.clear();

	//��ListBox���Ƴ�Ԫ��
	bool bRemoved = false;
	size_t nListBoxIndex = GetListBoxIndex();
	if (Box::IsValidItemIndex(nListBoxIndex)) {
		ASSERT(m_pTreeView->ListBox::GetItemAt(nListBoxIndex) == this);
		bRemoved = m_pTreeView->ListBox::RemoveItemAt(nListBoxIndex);
	}
	return bRemoved;
}

size_t TreeNode::GetDescendantNodeCount() const
{
	size_t nodeCount = GetChildNodeCount();
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode != nullptr) {
			nodeCount += pTreeNode->GetDescendantNodeCount();
		}
	}
	return nodeCount;
}

size_t TreeNode::GetChildNodeCount() const
{
	return m_aTreeNodes.size();
}

size_t TreeNode::GetDescendantNodeMaxListBoxIndex() const
{
	size_t maxListBoxIndex = GetListBoxIndex();
	if (!Box::IsValidItemIndex(maxListBoxIndex)) {
		if (m_aTreeNodes.empty()) {
			return maxListBoxIndex;
		}
		maxListBoxIndex = 0;
	}
	for (TreeNode* pTreeNode : m_aTreeNodes) {
		if (pTreeNode != nullptr) {
			maxListBoxIndex = std::max(pTreeNode->GetDescendantNodeMaxListBoxIndex(), maxListBoxIndex);
		}
	}
	return maxListBoxIndex;
}
	
TreeNode* TreeNode::GetChildNode(size_t iIndex) const
{
	if (iIndex >= m_aTreeNodes.size()) {
		return nullptr;
	}
	return m_aTreeNodes[iIndex];
}
	
size_t TreeNode::GetChildNodeIndex(TreeNode* pTreeNode) const
{
	auto it = std::find(m_aTreeNodes.begin(), m_aTreeNodes.end(), pTreeNode);
	if (it == m_aTreeNodes.end()) {
		return Box::InvalidIndex;
	}
	return it - m_aTreeNodes.begin();
}

bool TreeNode::IsExpand() const
{
	return m_bExpand;
}

void TreeNode::SetExpand(bool bExpand, bool bTriggerEvent)
{
	if(m_bExpand == bExpand) {
		return;
	}
	m_bExpand = bExpand;

	if (bTriggerEvent) {
		SendEvent(m_bExpand ? kEventExpand : kEventCollapse);
	}
	if (m_pTreeView != nullptr) {
		m_pTreeView->Arrange();
	}	
}

uint16_t TreeNode::GetDepth() const
{
	return m_uDepth;
}

TreeView::TreeView() :
	ListBox(new VLayout),
	m_iIndent(0),
	m_rootNode(),
	m_bEnableIcon(true)
{
	m_bMultiCheckMode = __super::IsMultiSelect();
	m_rootNode.reset(new TreeNode());
	m_rootNode->SetTreeView(this);
	//����Ĭ������Ϊ20������
	SetIndent(20, true);
}

TreeView::~TreeView()
{
	m_rootNode->RemoveSelf();
	m_rootNode.reset();
}

std::wstring TreeView::GetType() const { return DUI_CTR_TREEVIEW; }

void TreeView::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	//֧�ֵ������б�: ����ʵ�ֵ�ֱ��ת��
	if (strName == L"indent") {
		//���ڵ��������ÿ��ڵ�����һ��indent��λ��
		SetIndent(_wtoi(strValue.c_str()), true);
	}
	else if (strName == L"multi_select") {
		//��ѡ��Ĭ���ǵ�ѡ���ڻ���ʵ��
		SetMultiSelect(strValue == L"true");
	}
	else if (strName == L"check_box_class") {
		//�Ƿ���ʾCheckBox
		SetCheckBoxClass(strValue);
	}
	else if (strName == L"expand_image_class") {
		//�Ƿ���ʾ[չ��/����]ͼ��
		SetExpandImageClass(strValue);
	}
	else if (strName == L"show_icon") {
		//�Ƿ���ʾͼ��
		SetEnableIcon(strValue == L"true");
	}
	else {
		ListBox::SetAttribute(strName, strValue);
	}
}

bool TreeView::IsMultiSelect() const
{
	if (!m_checkBoxClass.empty()) {
		//�����ʾCheckBox����CheckģʽΪ׼, ��������ѡ��״̬������ѡ����
		if (IsMultiCheckMode()) {
			return false;
		}		
	}
	return __super::IsMultiSelect();
}

void TreeView::SetMultiSelect(bool bMultiSelect)
{
	bool bSelectChanged = (bMultiSelect != __super::IsMultiSelect()) ||
						  (m_bMultiCheckMode != bMultiSelect);
	if (!bSelectChanged) {
		return;
	}
	bool bOldCheckMode = IsMultiCheckMode();
	m_bMultiCheckMode = bMultiSelect;
	__super::SetMultiSelect(bMultiSelect);

	bool isChanged = false;
	if (IsMultiCheckMode()) {
		//�л�����Checkģʽ����CheckBox��ʾ�������
		if (OnCheckBoxShown()) {
			isChanged = true;
		}
	}
	else if (IsMultiSelect()) {
		//�л�����ѡģʽ����CheckBox�����ص������
		if (OnCheckBoxHided()) {
			isChanged = true;
		}
	}
	else {
		//�л�����ѡģʽ
		if (bOldCheckMode) {
			//��Checkģʽ�л�����ѡ����Ҫ��ͬ����ǰѡ�����������л���ѡ���һ�����⣨û�й�ѡ�ģ�����˵�ǰѡ���
			if (UpdateCurSelItemCheckStatus()) {
				isChanged = true;
			}
		}
		//�л�Ϊ��ѡģʽ��ȷ��ListBox����������ǵ�ѡ��
		if (OnSwitchToSingleSelect()) {
			isChanged = true;
		}
	}
	if (isChanged) {
		Invalidate();
	}
}

bool TreeView::IsMultiCheckMode() const
{
	if (!m_checkBoxClass.empty()) {
		ASSERT(m_bMultiCheckMode == __super::IsMultiSelect());
		return m_bMultiCheckMode;
	}
	return false;
}

bool TreeView::CanPaintSelectedColors(bool bHasStateImages) const
{
	if (bHasStateImages && IsMultiCheckMode()) {
		//�����CheckBox��Checkģʽ��ʱ��Ĭ�ϲ���ʾѡ�񱳾�ɫ
		return false;
	}
	return __super::CanPaintSelectedColors(bHasStateImages);
}

bool TreeView::OnSwitchToSingleSelect()
{
	ASSERT(!IsMultiSelect());
	bool bChanged = __super::OnSwitchToSingleSelect();
	if (IsMultiCheckMode()) {
		return bChanged;
	}
	//�Ѿ��л�Ϊ��ѡ
	TreeNode* pItem = nullptr;
	const size_t itemCount = m_items.size();
	for (size_t i = 0; i < itemCount; ++i) {
		pItem = dynamic_cast<TreeNode*>(m_items[i]);
		if ((pItem != nullptr) && pItem->IsChecked()) {
			if (GetCurSel() != i) {
				//��Ϊ��ѡ��������ǵ�ǰѡ���Checked��־ȫ����Ϊfalse
				pItem->SetChecked(false, false);
				pItem->Invalidate();
				bChanged = true;
			}
		}
	}
	return bChanged;
}

bool TreeView::UpdateCurSelItemCheckStatus()
{
	//��Check��ѡ��Ϊ׼�����õ�ǰѡ����
	bool bChanged = false;
	size_t curSelIndex = GetCurSel();
	if (Box::IsValidItemIndex(curSelIndex)) {
		TreeNode* pItem = dynamic_cast<TreeNode*>(GetItemAt(curSelIndex));
		if (pItem != nullptr) {
			if (!pItem->IsChecked()) {
				SetCurSel(Box::InvalidIndex);
				pItem->SetSelected(false);
				pItem->Invalidate();
				bChanged = true;
			}
			else {
				pItem->SetSelected(true);
				pItem->Invalidate();
			}
		}
	}
	return bChanged;
}

bool TreeView::OnCheckBoxHided()
{
	ASSERT(IsMultiSelect() && !IsMultiCheckMode());
	//ͬ������: Check -> Select
	if (m_items.empty()) {
		return false;
	}
	bool isChaned = false;
	TreeNode* pItem = nullptr;
	const size_t itemCount = m_items.size();
	for (size_t i = 0; i < itemCount; ++i) {
		pItem = dynamic_cast<TreeNode*>(m_items[i]);
		if (pItem == nullptr) {
			continue;
		}
		//ͬ��Check��Select��־
		if (pItem->IsSelected() != pItem->IsChecked()) {
			pItem->SetSelected(pItem->IsChecked());
			pItem->Invalidate();
			isChaned = true;
		}
		if (pItem->IsChecked()) {
			//Checkȫ����Ϊfalse
			pItem->SetChecked(false);
			pItem->Invalidate();
			isChaned = true;
		}		
	}
	//ͬ����ǰѡ����
	if (UpdateCurSelItemSelectStatus()) {
		isChaned = true;
	}
	return isChaned;
}

bool TreeView::OnCheckBoxShown()
{
	ASSERT(IsMultiCheckMode());
	//ͬ������: Select -> Check
	if (m_items.empty()) {
		return false;
	}
	bool isChanged = false;
	const size_t curSelIndex = GetCurSel();
	TreeNode* pItem = nullptr;
	const size_t itemCount = m_items.size();
	for (size_t i = 0; i < itemCount; ++i) {
		pItem = dynamic_cast<TreeNode*>(m_items[i]);
		if (pItem == nullptr) {
			continue;
		}
		//ͬ��Select��Check��־
		if (pItem->IsChecked() != pItem->IsSelected()) {
			pItem->SetChecked(pItem->IsSelected());
			pItem->Invalidate();
			isChanged = true;
		}
		if (curSelIndex != i) {
			//��ѡ�����״̬ȥ������ΪCheckģʽ�£�ListBox����Ϊ�ǵ�ѡ��Ϊ
			if (pItem->IsSelected()) {
				pItem->SetSelected(false);
				pItem->Invalidate();
				isChanged = true;
			}
		}
	}
	//ͬ����ǰѡ����	
	if (Box::IsValidItemIndex(curSelIndex)) {
		bool bSelectItem = false;
		pItem = dynamic_cast<TreeNode*>(GetItemAt(curSelIndex));
		if (pItem != nullptr) {
			bSelectItem = pItem->IsSelected();
		}
		if (!bSelectItem) {
			SetCurSel(Box::InvalidIndex);
			isChanged = true;
		}
		else if(pItem->IsChecked()){
			//ͬ����ѡ״̬
			pItem->UpdateParentCheckStatus(true);
		}
	}
	return isChanged;
}

void TreeView::SetIndent(int32_t indent, bool bNeedDpiScale)
{
	ASSERT(indent >= 0);
	if (bNeedDpiScale) {
		GlobalManager::Instance().Dpi().ScaleInt(indent);
	}
	if (indent >= 0) {
		m_iIndent = indent;
	}	
}

void TreeView::SetCheckBoxClass(const std::wstring& className)
{
	if (m_checkBoxClass == className) {
		return;
	}
	std::wstring oldCheckBoxClass = m_checkBoxClass.c_str();
	m_checkBoxClass = className;
	bool bSetOk = true;
	bool hasSetOk = false;
	for (Control* pControl : m_items) {
		TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
		if (pTreeNode != nullptr) {
			if (!pTreeNode->SetCheckBoxClass(className)) {
				bSetOk = false;
			}
			else {
				hasSetOk = true;
			}
		}
	}

	if (!bSetOk && !hasSetOk) {
		//��Ч������
		ASSERT(!"TreeView::SetCheckBoxClass failed!");
		m_checkBoxClass.clear();
		if (oldCheckBoxClass == m_checkBoxClass) {
			return;
		}
	}

	bool isChanged = false;
	if (m_checkBoxClass.empty()) {
		//����ʾCheckBox������CheckBox��������ģʽ��Ҫ������ѡģʽ����ѡģʽ��
		//��Ҫ��ͬ����ǰѡ�����������л���ѡ���һ�����⣨û�й�ѡ�ģ�����˵�ǰѡ���
		if (UpdateCurSelItemCheckStatus()) {
			isChanged = true;
		}
		if (IsMultiSelect()) {
			//�л�Ϊ��ѡģʽ
			if (OnCheckBoxHided()) {
				isChanged = true;
			}
		}
		else {
			//�л�Ϊ��ѡģʽ��ȷ��ListBox����������ǵ�ѡ��
			if (OnSwitchToSingleSelect()) {
				isChanged = true;
			}
		}
	}
	else {
		//������CheckBox�л�Ϊ��ʾCheckBox��������ģʽ��Ҫ����Checkģʽ����ѡģʽ��
		if (IsMultiCheckMode()) {
			//Checkģʽ����CheckBox��ʾ�������
			isChanged = OnCheckBoxShown();
		}
		else if(!IsMultiSelect()) {
			//��ѡģʽ��ȷ��ListBox����������ǵ�ѡ��
			if (OnSwitchToSingleSelect()) {
				isChanged = true;
			}
		}
		else {
			//������������
			ASSERT(!"ERROR!");
		}
	}
	if (isChanged) {
		Invalidate();
	}
}

std::wstring TreeView::GetCheckBoxClass() const
{
	return m_checkBoxClass.c_str();
}

void TreeView::SetExpandImageClass(const std::wstring& className)
{
	bool isChanged = m_expandImageClass != className;
	m_expandImageClass = className;
	if (isChanged) {
		for (Control* pControl : m_items) {
			TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
			if (pTreeNode != nullptr) {
				pTreeNode->SetExpandImageClass(className);
			}
		}
	}
}

std::wstring TreeView::GetExpandImageClass() const
{
	return m_expandImageClass.c_str();
}

void TreeView::SetEnableIcon(bool bEnable)
{
	bool isChanged = m_bEnableIcon != bEnable;
	m_bEnableIcon = bEnable;
	if (isChanged) {
		for (Control* pControl : m_items) {
			TreeNode* pTreeNode = dynamic_cast<TreeNode*>(pControl);
			if (pTreeNode != nullptr) {
				pTreeNode->SetEnableIcon(bEnable);
			}
		}
	}
}

bool TreeView::IsEnableIcon() const
{
	return m_bEnableIcon;
}

bool TreeView::InsertControlBeforeNode(TreeNode* pTreeNode, Control* pControl)
{
	if ((pTreeNode == nullptr) || (pControl == nullptr)) {
		return false;
	}
	bool bAdded = false;
	if (dynamic_cast<TreeNode*>(pControl) != nullptr) {
		//������ͨ���ýӿ�������ڵ�
		return false;
	}
	size_t iIndex = pTreeNode->GetListBoxIndex();
	if (Box::IsValidItemIndex(iIndex)) {
		bAdded = ListBox::AddItemAt(pControl, iIndex);
	}
	return bAdded;
}

bool TreeView::RemoveControl(Control* pControl)
{
	if (pControl == nullptr) {
		return false;
	}
	bool bRemoved = false;
	if (dynamic_cast<TreeNode*>(pControl) != nullptr) {
		//������ͨ���ýӿ��Ƴ����ڵ�
		return false;
	}
	bRemoved = ListBox::RemoveItem(pControl);
	return bRemoved;
}

bool TreeView::AddItem(Control* /*pControl*/)
{
	ASSERT(FALSE);
	return false;
}

bool TreeView::AddItemAt(Control* /*pControl*/, size_t /*iIndex*/)
{
	ASSERT(FALSE);
	return false;
}

bool TreeView::RemoveItem(Control* /*pControl*/)
{
	ASSERT(FALSE);
	return false;
}

bool TreeView::RemoveItemAt(size_t /*iIndex*/)
{
	ASSERT(FALSE);
	return false;
}

void TreeView::RemoveAllItems()
{
	ASSERT(FALSE);
}

void TreeView::SetParent(Box* pParent)
{
	ListBox::SetParent(pParent);
	m_rootNode->SetParent(pParent);
}

void TreeView::SetWindow(Window* pManager)
{
	__super::SetWindow(pManager);
	m_rootNode->SetWindow(pManager);
}

void TreeView::OnNodeCheckStatusChanged(TreeNode* pTreeNode)
{
	if (pTreeNode == nullptr) {
		return;
	}
	if (!pTreeNode->SupportCheckedMode()) {
		//��ѡ���߲���ʾCheckBox��ֱ�ӷ���
		return;
	}

	//��ѡ
	bool isChecked = pTreeNode->IsChecked();
	//ͬ���ӽڵ�Ĺ�ѡ״̬�����浱ǰ�ڵ�
	pTreeNode->SetChildrenCheckStatus(isChecked);

	//ͬ�����ڵ�Ĺ�ѡ״̬
	pTreeNode->UpdateParentCheckStatus(false);
}

}