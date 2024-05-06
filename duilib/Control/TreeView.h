#ifndef UI_CONTROL_TREEVIEW_H_
#define UI_CONTROL_TREEVIEW_H_

#pragma once

#include "duilib/Box/ListBox.h"
#include <map>

namespace ui
{

/** �ڵ㹴ѡ״̬
*/
enum class TreeNodeCheck
{
	UnCheck,	 //û�д�
	CheckedAll,	 //ȫ����
	CheckedPart  //���ִ�
};

class TreeView;
class UILIB_API TreeNode : public ListBoxItem
{
	friend class TreeView;
public:
	TreeNode();
	TreeNode(const TreeNode& r) = delete;
	TreeNode& operator=(const TreeNode& r) = delete;
	virtual ~TreeNode();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual bool IsVisible() const override;
	virtual bool SupportCheckedMode() const override;

private:
	virtual void PaintStateImages(IRender* pRender) override;
	virtual bool ButtonDown(const EventArgs& msg) override;
	virtual bool OnDoubleClickItem(const EventArgs& args);

public:
	/** ��������������������
	 * @param[in] pTreeView ����ָ��
	 */
	void SetTreeView(TreeView* pTreeView);

	/** ��ȡ����������������
	 */
	TreeView* GetTreeView() const;

	/** ��ȡ���ڵ�ָ��
	 * @return ���ظ��ڵ�ָ��
	 */
	TreeNode* GetParentNode() const;

	/** ���ø��ڵ�
	 * @param[in] pParentTreeNode ���ڵ�ָ��
	 */
	void SetParentNode(TreeNode* pParentTreeNode);

	/** ����������һ���µ��ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool AddChildNode(TreeNode* pTreeNode);

	/** ��ָ��λ������ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @param[in] iIndex Ҫ�����ĸ�λ��֮��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool AddChildNodeAt(TreeNode* pTreeNode, const size_t iIndex);

	/** ��ָ��λ���Ƴ�һ���ӽڵ�
	 * @param[in] iIndex Ҫ�Ƴ����ӽڵ�����
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveChildNodeAt(size_t iIndex);

	/** �����ӽڵ�ָ���Ƴ�һ���ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveChildNode(TreeNode* pTreeNode);

	/** �Ƴ������ӽڵ�
	 */
	void RemoveAllChildNodes();

	/** �ݹ��ȡ�����ӽڵ����
	 * @return ���������ӽڵ����
	 */
	size_t GetDescendantNodeCount() const;

	/** ��ȡ��һ���ӽڵ����
	 * @return �����ӽڵ����
	 */
	size_t GetChildNodeCount() const;

	/** ��ȡһ���ӽڵ�ָ��
	 * @param[in] iIndex Ҫ��ȡ���ӽڵ�����
	 * @return �����ӽڵ�ָ��
	 */
	TreeNode* GetChildNode(size_t iIndex) const;

	/** �����ӽڵ�ָ���ȡ�ӽڵ�λ������
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return ����λ������
	 */
	size_t GetChildNodeIndex(TreeNode* pTreeNode) const;

	/** �ж��Ƿ�չ��״̬
	 * @return ���� true Ϊչ��״̬������Ϊ false
	 */
	bool IsExpand() const; 

	/** �����Ƿ�չ����ʾ�ӽڵ�
	 * @param[in] bExpand Ϊ true ʱչ����Ϊ false �ǲ�չ��
	 */
	void SetExpand(bool bExpand, bool bTriggerEvent = false);

	/** ��ȡ����㼶
	 * @return ���ص�ǰ�㼶, ���ڵ�Ĳ㼶Ϊ0�����ڵ���һ������ڵ㣬һ���ڵ���ʵ�ڵ㣬�㼶��1
	 *         ���ڵ�������ǣ�
	 *         int32_t indent = 0;
	 *         if(GetDepth() > 0) {
	 *				indent = (GetDepth() - 1) * TreeView::GetIndent();
	 *		   }
	 */
	uint16_t GetDepth() const;

#ifdef UILIB_IMPL_WINSDK

	/** ���ñ���ͼƬ(HICON���)
	 * @param [in] hIcon Ҫ���õ�ͼ���������ú���ui::GlobalManager::Instance().Icon()������Դ����������
	               ���hIconΪnullptr, ��ɾ���ڵ��ͼ�꣬�������ui::GlobalManager::Instance().Icon()�Ƴ�ԭ��������ͼ����
	 */
	void SetBkIcon(HICON hIcon);

#endif

	/** �����Ƿ���ʾͼ��
	*/
	void SetEnableIcon(bool bEnable);

	/** ��������չ���¼�
	 * @param[in] callback ����չ��ʱ�����Ļص�����
	 */
	void AttachExpand(const EventCallback& callback) { AttachEvent(kEventExpand, callback); }

	/** �������������¼�
	 * @param[in] callback ��������ʱ�����Ļص�����
	 */
	void AttachCollapse(const EventCallback& callback) { AttachEvent(kEventCollapse, callback); }

private:
	/** ����[δչ��/չ��]��־ͼƬ������Class�������Ϊ�ձ�ʾ����չ����־���ܣ�Ϊ����ر�չ����־����
	*   Ӧ�÷�Χ���ýڵ㱾��
	* @param [in] expandClass չ����־ͼƬ��Class����
	*/
	void SetExpandImageClass(const std::wstring& expandClass);

	/** ����CheckBox������Class�������Ϊ�ձ�ʾ����CheckBox���ܣ�Ϊ����ر�CheckBox����
	*   Ӧ�÷�Χ���ýڵ㱾��
	* @param [in] checkBoxClass ui::CheckBox��Class���ԣ�һ�����õ���Ҫ�����У�
				  normal_image������״̬��ͼƬ����ѡ����(������ʱ��ͼƬ)
				  selected_normal_image��ѡ��ʱ������״̬��ͼƬ����ѡ����(����ʱ��ͼƬ)
	*/
	bool SetCheckBoxClass(const std::wstring& checkBoxClass);

	/** ���������ӽڵ�Ĺ�ѡ״̬����������ѡ��仯�¼�
	* @param [in] bChecked ��ѡ״̬���򹴻��߲��򹴣�
	*/
	void SetChildrenCheckStatus(bool bChecked);

	/** �����Լ������и��׽ڵ�Ĺ�ѡ״̬���򹴻��߲��򹴣�����������ѡ��仯�¼�
	*   ���ڵ�Ĺ�ѡ״̬�����仯/�ӽڵ�����/ɾ��ʱ����Ҫ���ô˺������½ڵ�Ĺ�ѡ״̬
	* @param [in] bUpdateSelf �Ƿ���Ҫ�����Լ���ѡ��״̬
	*/
	void UpdateParentCheckStatus(bool bUpdateSelf);

	/** ���µ�ǰ�ڵ�Ĺ�ѡ״̬(��̬ѡ��״̬)
	*/
	void UpdateSelfCheckStatus();

	/** ��ȡ��ǰ�ڵ�Ĺ�ѡ״̬(������ӽڵ�)
	*/
	TreeNodeCheck GetCheckStatus(void) const;

	/** ��ȡ��ǰ�ڵ���ӽڵ㹴ѡ״̬(����������ֻ�����ӽڵ�)
	*/
	TreeNodeCheck GetChildrenCheckStatus(void) const;

	/** ��ȡչ��״̬��ͼƬ
	 * @param [in] stateType Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @return ����ͼƬ·��������
	 */
	std::wstring GetExpandStateImage(ControlStateType stateType);

	/** ����չ��״̬��ͼƬ
	 * @param [in] stateType Ҫ��������״̬�µ�ͼƬ
	 * @param [in] strImage ͼƬ·��������
	 */
	void SetExpandStateImage(ControlStateType stateType, const std::wstring& strImage);

	/** ��ȡδչ��״̬��ͼƬ
	 * @param [in] stateType Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @return ����ͼƬ·��������
	 */
	std::wstring GetCollapseStateImage(ControlStateType stateType);

	/** ����δչ��״̬��ͼƬ
	 * @param [in] stateType Ҫ��������״̬�µ�ͼƬ
	 * @param [in] strImage ͼƬ·��������
	 */
	void SetCollapseStateImage(ControlStateType stateType, const std::wstring& strImage);

private:
	/** ɾ������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveSelf();

	/** ��ָ��λ���Ƴ�һ���ӽڵ�
	 * @param [in] iIndex Ҫ�Ƴ����ӽڵ�����
	 * @param [in] bUpdateCheckStatus �Ƿ���¹�ѡ״̬
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveChildNodeAt(size_t iIndex, bool bUpdateCheckStatus);

	/** ���ݵ�ǰ�����ã�����չ����־�������ڱ߾�(�����뺯������ε����޸�����)
	*/
	void AdjustExpandImagePadding();

	/** ���ݵ�ǰ�����ã�����CheckBox�������ڱ߾�(�����뺯������ε����޸�����)
	*/
	void AdjustCheckBoxPadding();

	/** ���ݵ�ǰ�����ã�����ͼ��������ڱ߾�(�����뺯������ε����޸�����)
	*/
	void AdjustIconPadding();

	/** ���ѡ״̬�仯ʱ����
	 * @param[in] args ��Ϣ��
	 * @return ʼ�շ��� true
	 */
	bool OnNodeCheckStatusChanged(const EventArgs& args);

	/** ��ȡչ��״̬ͼ��ռ�õ��ڱ߾���
	*/
	int32_t GetExpandImagePadding(void) const;

	/** ��ȡ�����Լ����Լ�������ڵ��У�ListBox���������ֵ�����ڼ�������ӽڵ�Ĳ���λ��
	*   ���û����ЧԪ�أ��򷵻� Box::InvalidIndex
	*/
	size_t GetDescendantNodeMaxListBoxIndex() const;
	
private:
	//����㼶
	uint16_t m_uDepth;

	//�Ƿ�չ����ʾ�ӽڵ�
	bool m_bExpand;

	//����������������
	TreeView* m_pTreeView;

	//���ڵ�
	TreeNode* m_pParentTreeNode;

	//�ӽڵ��б�
	std::vector<TreeNode*> m_aTreeNodes;

	//ͼƬ/����Ԫ��֮��Ĺ̶����
	uint16_t m_expandIndent;	//[չ��/����]��ť����ļ��
	uint16_t m_checkBoxIndent;	//CheckBox ����ļ��
	uint16_t m_iconIndent;		//icon ͼ�����ļ��

	//Expandͼ�������ͼ��/�����ڱ߾ࣺ3��
	uint16_t m_expandCheckBoxPadding;
	uint16_t m_expandIconPadding;
	uint16_t m_expandTextPadding;

	//CheckBox������ͼ��/�����ڱ߾ࣺ2��
	uint16_t m_checkBoxIconPadding;
	uint16_t m_checkBoxTextPadding;

	//ͼ������������ڱ߾ࣺ1��
	uint16_t m_iconTextPadding;

	/** �ؼ�չ��״̬��ͼƬ������״̬ͼƬ��MAP, ���Ƶ�Ŀ�����
	*/
	std::unique_ptr<StateImage> m_expandImage;
	UiRect* m_pExpandImageRect;

	/** �ؼ�δչ��״̬��ͼƬ������״̬ͼƬ��MAP, ���Ƶ�Ŀ�����
	*/
	std::unique_ptr<StateImage> m_collapseImage;
	UiRect* m_pCollapseImageRect;
};

class UILIB_API TreeView : public ListBox
{
	friend class TreeNode;
public:
	TreeView();
	virtual ~TreeView();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void SetParent(Box* pParent) override;
	virtual void SetWindow(Window* pManager) override;

	/** ��ȡ���ڵ�
	 * @return ���ظ��ڵ�ָ��
	 */
	TreeNode* GetRootNode()	const{ return m_rootNode.get(); }

	/** ��ȡ�ӽڵ�����ֵ
	 * @return �����ӽڵ�����ֵ
	 */
	int32_t GetIndent() const { return m_iIndent;	}

	/** �����ӽڵ�����ֵ
	 * @param [in] indent Ҫ���õ�����ֵ, ��λΪ����
	 * @param [in] bNeedDpiScale �Ƿ���ҪDPI����
	 */
	void SetIndent(int32_t indent, bool bNeedDpiScale);

	/** ����[δչ��/չ��]��־ͼƬ������Class�������Ϊ�ձ�ʾ����չ����־���ܣ�Ϊ����ر�չ����־����
	*   Ӧ�÷�Χ�����������нڵ�
	* @param [in] className չ����־ͼƬ��Class����
	*/
	void SetExpandImageClass(const std::wstring& className);

	/** ��ȡ[δչ��/չ��]��־ͼƬ������Class
	*/
	std::wstring GetExpandImageClass() const;

	/** ����CheckBox������Class�������Ϊ�ձ�ʾ����CheckBox���ܣ�Ϊ����ر�CheckBox����
	*   Ӧ�÷�Χ�����������нڵ�
	* @param [in] className ui::CheckBox��Class���ԣ�һ�����õ���Ҫ�����У�
				  normal_image������״̬��ͼƬ����ѡ����(������ʱ��ͼƬ)
				  selected_normal_image��ѡ��ʱ������״̬��ͼƬ����ѡ����(����ʱ��ͼƬ)
	*/
	void SetCheckBoxClass(const std::wstring& className);

	/** ��ȡCheckBox������Class
	*/
	std::wstring GetCheckBoxClass() const;

	/** �����Ƿ���ʾͼ��
	*/
	void SetEnableIcon(bool bEnable);

	/** �ж��Ƿ���ʾͼ��
	*/
	bool IsEnableIcon() const;

	/** ��ĳ�����ڵ�ǰ�����ͨ�ؼ�����ʵ��һЩЧ�������粻ͬ���ͽڵ��ķָ�����
	* @param [in] pTreeNode ���Ľڵ�ӿڣ�������Ϊ��
	* @param [in] pControl ��Ҫ��ӵ���ͨ�ؼ��ӿڣ�������Ϊ��
	*/
	bool InsertControlBeforeNode(TreeNode* pTreeNode, Control* pControl);

	/** ɾ�����ڵ��е���ͨ�ؼ�
	* @param [in] pControl ��Ҫɾ������ͨ�ؼ��ӿڣ�������Ϊ��
	*/
	bool RemoveControl(Control* pControl);

	/** �Ƿ������ѡ
	*/
	virtual bool IsMultiSelect() const override;

	/** �����Ƿ������ѡ
	*/
	virtual void SetMultiSelect(bool bMultiSelect) override;

	/** �Ƿ�Ϊ��ѡ�Ĺ�ѡģʽ�����������Ϊtrue��ģʽ�£�ҵ���߼�˵����
	*   (1) �����������ListBox������Ϊ��ѡ�߼���
	*   (2) �������ڵ��ϵ�CheckBox��ѡ���߼�����IsSelected()����߼���δʹ�ã�
	        ʹ�õ���Check�߼�����IsChecked()����߼�����Check�߼��ǿ��Զ๴ѡ�ġ�
	*/
	bool IsMultiCheckMode() const;

private:
	/** ���ڵ㹴ѡ״̬�仯
	 * @param [in] pTreeNode ���ڵ�ӿ�
	 */
	void OnNodeCheckStatusChanged(TreeNode* pTreeNode);

	/** �Ƿ����ѡ��״̬�µı���ɫ���ṩ�麯����Ϊ��ѡ��
	   ������ListBox/TreeView�ڵ��ڶ�ѡʱ�������й�ѡ�������Ҫ����ѡ��״̬�ı���ɫ��
	   @param [in] bHasStateImages ��ǰ�б����Ƿ���CheckBox��ѡ��
	*/
	virtual bool CanPaintSelectedColors(bool bHasStateImages) const override;

private:
	//���º�������˽�л���������ֹʹ�ã�Ӧ��ʹ��TreeNode�е���غ���
	bool AddItem(Control* pControl) override;
	bool AddItemAt(Control* pControl, size_t iIndex) override;
	bool RemoveItem(Control* pControl) override;
	bool RemoveItemAt(size_t iIndex) override;
	void RemoveAllItems() override;

	/** ���Ӷ�ѡ�л�Ϊ��ѡģʽ��ʱ����Ҫȷ���б���ֻ��һ��ѡ����
	* @return ����б仯����true�����򷵻�false
	*/
	virtual bool OnSwitchToSingleSelect() override;

	/** ͬ����ǰѡ����Ĺ�ѡ״̬
	* @return ����б仯����true�����򷵻�false
	*/
	bool UpdateCurSelItemCheckStatus();

	/** ��CheckBox����ʾ�л������غ�ͬ��Check��Select
	    ��1����Checked�ģ���ΪSelected��
		��2��������Checked��־��Ϊfalse
	   @return ����true��ʾ��Ҫ�ػ棬������Ҫ�ػ�
	*/
	bool OnCheckBoxHided();

	/** ��CheckBox�������л�����ʾ��ͬ��Select��Check
		��1����Selected�ģ���ΪChecked��
		��2��Selected״̬���ı�
	  @return ����true��ʾ��Ҫ�ػ棬������Ҫ�ػ�
	*/
	bool OnCheckBoxShown();

private:
	//�ӽڵ������ֵ����λΪ����
	int32_t m_iIndent;

	//չ����־ͼƬ��Class
	UiString m_expandImageClass;

	//CheckBox��Class
	UiString m_checkBoxClass;

	//�Ƿ���ʾͼ��
	bool m_bEnableIcon;

	//���ĸ��ڵ�
	std::unique_ptr<TreeNode> m_rootNode;

	//�Ƿ������ѡ(��ѡģʽ)
	bool m_bMultiCheckMode;
};

}

#endif // UI_CONTROL_TREEVIEW_H_
