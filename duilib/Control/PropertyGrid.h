#ifndef UI_CONTROL_PROPERTY_GRID_H_
#define UI_CONTROL_PROPERTY_GRID_H_

#pragma once

#include "duilib/Box/VBox.h"
#include "duilib/Control/Split.h"
#include "duilib/Control/Label.h"
#include "duilib/Control/RichText.h"
#include "duilib/Control/RichEdit.h"
#include "duilib/Control/TreeView.h"
#include "duilib/Control/Combo.h"
#include "duilib/Control/ComboButton.h"
#include "duilib/Control/DateTime.h"
#include "duilib/Control/IPAddress.h"
#include "duilib/Control/HotKey.h"
#include "duilib/Utils/FileDialog.h"

namespace ui
{
/** ���Ա�ؼ���֧�ֵ�����
*/
class PropertyGridGroup;
class PropertyGridProperty;
class PropertyGridTextProperty;		//�ı�������
class PropertyGridComboProperty;	//������
class PropertyGridFontProperty;		//��������
class PropertyGridFontSizeProperty;	//�����С
class PropertyGridColorProperty;	//��ɫ
class PropertyGridDateTimeProperty; //����ʱ��
class PropertyGridIPAddressProperty;//IP��ַ
class PropertyGridHotKeyProperty;	//�ȼ�
class PropertyGridFileProperty;		//�ļ�·��
class PropertyGridDirectoryProperty;//�ļ���

/** ���Ա�ؼ�
*/
class PropertyGrid : public VBox
{
public:
	PropertyGrid();

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
	/** �����Ƿ���ʾ��ͷ
	*/
	void SetEnableHeaderCtrl(bool bEnable,
							 const std::wstring& sLeftColumn = L"", 
							 const std::wstring& sRightColumn = L"");
	/** �жϵ�ǰ�Ƿ���ʾ��ͷ
	*/
	bool IsEnableHeaderCtrl() const { return m_bHeaderCtrl; }

	/** ��ȡHeader�ӿ�
	*/
	Control* GetHeaderCtrl() const { return m_pHeaderCtrl; }

	/** ��ȡHeader�е����һ��
	*/
	Label* GetHeaderLeft() const { return m_pHeaderLeft; }

	/** ��ȡHeader�е��Ҳ�һ��
	*/
	Label* GetHeaderRight() const { return m_pHeaderRight; }

	/** ��ȡHeader�еķָ���
	*/
	Split* GetHeaderSplit() const { return m_pHeaderSplit; }

public:
	/** ����һ������
	* @param [in] groupName ���������
	* @param [in] description �����������Ϣ
	* @param [in] nGroupData �û��Զ�������
	* @return ���ظ÷���Ľӿڣ��������������
	*/
	PropertyGridGroup* AddGroup(const std::wstring& groupName, 
							    const std::wstring& description = L"",
								size_t nGroupData = 0);

	/** ��ȡ���еķ���
	* @param [out] groups ���ص�ǰ���еķ����б�
	*/
	void GetGroups(std::vector<PropertyGridGroup*>& groups) const;

	/** ɾ������
	* @param [in] pGroup ��ɾ���ķ���
	*/
	bool RemoveGroup(PropertyGridGroup* pGroup);

	/** ɾ�����з���
	*/
	void RemoveAllGroups();

	/** ���һ������(�ɵ��÷���������)
	* @param [in] pGroup �����������ķ���
	* @param [in] pProperty ���Խӿ�
	*/
	bool AddProperty(PropertyGridGroup* pGroup, PropertyGridProperty* pProperty);

	/** ����һ������(�ı�����������)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridTextProperty* AddTextProperty(PropertyGridGroup* pGroup,
									          const std::wstring& propertyName, 
									          const std::wstring& propertyValue,
									          const std::wstring& description = L"",
									          size_t nPropertyData = 0);

	/** ����һ������(������)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridComboProperty* AddComboProperty(PropertyGridGroup* pGroup,
									            const std::wstring& propertyName, 
									            const std::wstring& propertyValue,
									            const std::wstring& description = L"",
									            size_t nPropertyData = 0);

	/** ����һ������(��������)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ���������ƣ�
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridFontProperty* AddFontProperty(PropertyGridGroup* pGroup,
									          const std::wstring& propertyName, 
									          const std::wstring& propertyValue,
									          const std::wstring& description = L"",
									          size_t nPropertyData = 0);

	/** ����һ������(�����С)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ�������С��
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridFontSizeProperty* AddFontSizeProperty(PropertyGridGroup* pGroup,
									                  const std::wstring& propertyName, 
									                  const std::wstring& propertyValue,
									                  const std::wstring& description = L"",
									                  size_t nPropertyData = 0);

	/** ����һ������(��ɫ)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ�������С��
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridColorProperty* AddColorProperty(PropertyGridGroup* pGroup,
									            const std::wstring& propertyName, 
									            const std::wstring& propertyValue,
									            const std::wstring& description = L"",
									            size_t nPropertyData = 0);

	/** ����һ������(����ʱ��)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] dateTimeValue ���Ե�ֵ������ʱ��ֵ��
	* @param [in] editFormat ���ڵı༭��ʽ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridDateTimeProperty* AddDateTimeProperty(PropertyGridGroup* pGroup,
									                  const std::wstring& propertyName, 
									                  const std::wstring& dateTimeValue,												      
									                  const std::wstring& description = L"",
									                  size_t nPropertyData = 0,
													  DateTime::EditFormat editFormat = DateTime::EditFormat::kDateCalendar);
	
	/** ����һ������(IP��ַ)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridIPAddressProperty* AddIPAddressProperty(PropertyGridGroup* pGroup,
														const std::wstring& propertyName, 
														const std::wstring& propertyValue,
														const std::wstring& description = L"",
														size_t nPropertyData = 0);

	/** ����һ������(�ȼ�)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridHotKeyProperty* AddHotKeyProperty(PropertyGridGroup* pGroup,
												  const std::wstring& propertyName, 
												  const std::wstring& propertyValue,
												  const std::wstring& description = L"",
												  size_t nPropertyData = 0);

	/** ����һ������(�ļ�·��)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(�ļ�·��)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @param [in] bOpenFileDialog true��ʾ���ļ���false��ʾ�����ļ�
	* @param [in] fileTypes �Ի�����Դ򿪻򱣴���ļ�����
	* @param [in] nFileTypeIndex ѡ����ļ����ͣ���Ч��Χ��[0, fileTypes.size())
	* @param [in] defaultExt Ĭ�ϵ��ļ�����, ������"doc;docx"
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridFileProperty* AddFileProperty(PropertyGridGroup* pGroup,
										      const std::wstring& propertyName, 
										      const std::wstring& propertyValue,											  
											  const std::wstring& description = L"",
											  size_t nPropertyData = 0,
											  bool bOpenFileDialog = true,
											  const std::vector<FileDialog::FileType>& fileTypes = std::vector<FileDialog::FileType>(),
											  int32_t nFileTypeIndex = -1,
											  const std::wstring& defaultExt = L"");

	/** ����һ������(�ļ���)
	* @param [in] pGroup �����������ķ���
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @return ���ظ����ԵĽӿ�
	*/
	PropertyGridDirectoryProperty* AddDirectoryProperty(PropertyGridGroup* pGroup,
													    const std::wstring& propertyName, 
													    const std::wstring& propertyValue,
													    const std::wstring& description = L"",
													    size_t nPropertyData = 0);

	/** �������һ�еĿ��
	* @param [in] nLeftColumnWidth ���һ�еĿ��
    * @param [in] bNeedDpiScale �Ƿ���Ҫ���п�ֵ����DPI����Ӧ
	*/
	void SetLeftColumnWidth(int32_t nLeftColumnWidth, bool bNeedDpiScale);

	/** ��ȡ���һ�еĿ��ֵ
	*/
	int32_t GetLeftColumnWidth() const;

public:
	/** �����Ƿ���ʾ��������
	*/
	void SetEnableDescriptionArea(bool bEnable);

	/** �ж��Ƿ���ʾ��������
	*/
	bool IsEnableDescriptionArea() const { return m_bDescriptionArea; }

	/** ������������ĸ߶�ֵ
	* @param [in] nHeight �߶�ֵ
    * @param [in] bNeedDpiScale �Ƿ���Ҫ���п�ֵ����DPI����Ӧ
	*/
	void SetDescriptionAreaHeight(int32_t nHeight, bool bNeedDpiScale);

	/** ��ȡ��ǰ��������ĸ߶�ֵ
	*/
	int32_t GetDescriptionAreaHeight() const;

	/** ��ȡ�����ؼ��Ľӿ�
	*/
	RichText* GetDescriptionArea() const { return m_pDescriptionArea; }

	/** �����ؼ��ķָ����ӿ�
	*/
	Split* GetDescriptionAreaSplit() const { return m_pDescriptionAreaSplit; }

public:
	/** ��ȡ���Ա�����ؼ��ӿڣ����ڹ������ݣ�
	*/
	TreeView* GetTreeView() const { return m_pTreeView; }

	/** ���������ߵĿ��
	* @param [in] nLineWidth �����ߵĿ�ȣ����Ϊ0��ʾ����ʾ����������
	* @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
	*/
	void SetRowGridLineWidth(int32_t nLineWidth, bool bNeedDpiScale);
	int32_t GetRowGridLineWidth() const;

	/** ���������ߵ���ɫ
	* @param [in] color ���������ߵ���ɫ
	*/
	void SetRowGridLineColor(const std::wstring& color);
	std::wstring GetRowGridLineColor() const;

	/** ���������ߵĿ��
	* @param [in] nLineWidth �����ߵĿ�ȣ����Ϊ0��ʾ����ʾ����������
	* @param [in] bNeedDpiScale ���Ϊtrue��ʾ��Ҫ�Կ�Ƚ���DPI����Ӧ
	*/
	void SetColumnGridLineWidth(int32_t nLineWidth, bool bNeedDpiScale);
	int32_t GetColumnGridLineWidth() const;

	/** ���������ߵ���ɫ
	* @param [in] color ���������ߵ���ɫ
	*/
	void SetColumnGridLineColor(const std::wstring& color);
	std::wstring GetColumnGridLineColor() const;

	/** ��ͷ��Class
	*/
	void SetHeaderClass(const std::wstring& headerClass);
	std::wstring GetHeaderClass() const;

	/** �����Class
	*/
	void SetGroupClass(const std::wstring& groupClass);
	std::wstring GetGroupClass() const;

	/** ���Ե�Class
	*/
	void SetPropertyClass(const std::wstring& propertyClass);
	std::wstring GetPropertyClass() const;

protected:
	/** ��ʼ������
	 */
	virtual void OnInit() override;

	/** �����ӿؼ�
	*/
	virtual void PaintChild(IRender* pRender, const UiRect& rcPaint) override;

	/** ����������
	*/
	void PaintGridLines(IRender* pRender);

	/** �϶��б�ͷ�ı��п���¼���Ӧ����
	*/
	void OnHeaderColumnResized();

	/** ����һ�����Խڵ���п�
	*/
	void ResizePropertyColumn(TreeNode* pPropertyNode, int32_t nLeftColumnWidth);

private:
	/** ����XML�ļ�
	*/
	UiString m_configXml;

private:
	/** �Ƿ���ʾHeader
	*/
	bool m_bHeaderCtrl;

	/** Header�ӿ�
	*/
	Control* m_pHeaderCtrl;

	/** Header�е����һ��
	*/
	Label* m_pHeaderLeft;

	/** Header�е��Ҳ�һ��
	*/
	Label* m_pHeaderRight;

	/** Header�еķָ���
	*/
	Split* m_pHeaderSplit;

	/** ���һ�еĿ��
	*/
	int32_t m_nLeftColumnWidth;

private:
	/** �����ؼ��ķָ���
	*/
	Split* m_pDescriptionAreaSplit;

	/** �����ؼ�
	*/
	RichText* m_pDescriptionArea;

	/** �Ƿ���ʾ��������
	*/
	bool m_bDescriptionArea;

private:
	/** ���Ա�����ؼ��ӿ�
	*/
	TreeView* m_pTreeView;

	/** ��ͷ��Class
	*/
	UiString m_headerClass;

	/** �����Class
	*/
	UiString m_groupClass;

	/** ���Ե�Class
	*/
	UiString m_propertyClass;

private:
	/** ���������ߵĿ��
	*/
	int32_t m_nRowGridLineWidth;

	/** ���������ߵ���ɫ
	*/
	UiString m_rowGridLineColor;

	/** ���������ߵĿ��
	*/
	int32_t m_nColumnGridLineWidth;

	/** ���������ߵ���ɫ
	*/
	UiString m_columnGridLineColor;
};

/** ���Ա�ķ���, �����ṹ
*   <PropertyGridGroup>
*		<HBox>
*			<LabelBox/>
*		</HBox>
*   </PropertyGridGroup>
*/
class PropertyGridGroup : public TreeNode
{
public:
	/** ����һ����
	* @param [in] groupName �������
	* @param [in] description ���������Ϣ
	* @param [in] nGroupData �û��Զ�������
	*/
	explicit PropertyGridGroup(const std::wstring& groupName, 
							   const std::wstring& description = L"",
		                       size_t nGroupData = 0);

public:
	/** ��ȡ��������
	*/
	std::wstring GetGroupName() const { return m_groupName.c_str(); }

	/** ��ȡ���������Ϣ
	*/
	std::wstring GetDescriptiion() const { return m_description.c_str(); }

	/** ��ȡ�û��Զ�������
	*/
	size_t GetGroupData() const { return m_nGroupData; }

	/** �����û��Զ�������
	*/
	void SetGroupData(size_t nGroupData) { m_nGroupData = nGroupData; }

	/** ��ȡ�������Ƶ���ʾ�ؼ�
	*/
	LabelBox* GetLabelBox() const { return m_pLabelBox; }

	/** ��ȡ�����µ���������
	* @param [out] properties ���ص�ǰ���еķ����б�
	*/
	void GetProperties(std::vector<PropertyGridProperty*>& properties) const;

	/** ɾ���÷����µ�����
	* @param [in] pProperty ��Ҫɾ�������Խӿ�
	*/
	bool RemoveProperty(PropertyGridProperty* pProperty);

	/** ɾ���÷����µ���������
	*/
	void RemoveAllProperties();

protected:
	/** ��ʼ������
	 */
	virtual void OnInit() override;

private:
	/** ���������
	*/
	UiString m_groupName;

	/** ���������Ϣ
	*/
	UiString m_description;

	/** �û��Զ�������
	*/
	size_t m_nGroupData;

	/** �������Ƶ���ʾ�ؼ�
	*/
	LabelBox* m_pLabelBox;
};

/** ���Ե�����
*/
enum class PropertyGridPropertyType
{
	kNone,		//�޾������ͣ�����
	kText,		//��ͨ�ı�
	kCombo,		//������
	kFont,		//��������
	kFontSize,  //�����С
	kColor,		//��ɫ
	kDateTime,	//����ʱ��
	kIPAddress,	//IP��ַ
	kHotKey,	//�ȼ�
	kFile,		//�ļ�·��
	kDirectory,	//�ļ���
	kCustom		//�û��Զ�������ͣ������Լ�ʵ��һ������
};

/** ���Ա������, �����ṹ
*   <PropertyGridProperty>
*		<HBox>
*			<LabelBox/>
*			<LabelBox/>
*		</HBox>
*   </PropertyGridProperty>
*/
class PropertyGridProperty: public TreeNode
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridProperty(const std::wstring& propertyName, 
					     const std::wstring& propertyValue,
					     const std::wstring& description = L"",
					     size_t nPropertyData = 0);

public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const 
	{ 
		return PropertyGridPropertyType::kNone; 
	}

	/** ��ȡ��������
	*/
	std::wstring GetPropertyName() const { return m_propertyName.c_str(); }

	/** ��ȡ����ֵ(ԭֵ)
	*/
	std::wstring GetPropertyValue() const { return m_propertyValue.c_str(); }

	/** ��ȡ���Ե�������Ϣ
	*/
	std::wstring GetDescriptiion() const { return m_description.c_str(); }

	/** ��ȡ�û��Զ�������
	*/
	size_t GetPropertyData() const { return m_nPropertyData; }

	/** �����û��Զ�������
	*/
	void SetPropertyData(size_t nPropertyData) { m_nPropertyData = nPropertyData; }

	/** ��ȡ�������ƺ�����ֵ���������ؼ������������ñ���ɫ��
	*/
	HBox* GetHBox() const {	return m_pHBox;	}

	/** ��ȡ�������Ƶ���ʾ�ؼ�, ���ؼ���GetHBox()
	*/
	LabelBox* GetLabelBoxLeft() const { return m_pLabelBoxLeft; }

	/** ��ȡ����ֵ����ʾ�ؼ�, ���ؼ���GetHBox()
	*/
	LabelBox* GetLabelBoxRight() const { return m_pLabelBoxRight; }

	/** ����ֻ��ģʽ
	*/
	void SetReadOnly(bool bReadOnly);

	/** �Ƿ�Ϊֻ��ģʽ
	*/
	bool IsReadOnly() const { return m_bReadOnly; }

	/** ��ȡ�µ�����ֵ���޸ĺ������ֵ, ������޸��򷵻�ԭֵ��
	*/
	virtual std::wstring GetPropertyNewValue() const;

protected:
	/** ��ʼ������
	 */
	virtual void OnInit() override;

	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool /*bEnable*/) {}

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	* @return ���ر༭�ؼ��Ľӿ�
	*/
	virtual Control* ShowEditControl(bool /*bShow*/) { return nullptr; }

	/** �����������˹���(���ڴ�����ʽ�Ӵ��ڵ�λ������)
	*/
	virtual void OnScrollPosChanged() {}

	/** ��ȡ�༭�ؼ���Margin.right������������ڵ��༭�ؼ���
	*/
	int32_t GetEditControlMarginRight() const;

protected:
	/** ��������ֵ���ı�(��ʾ�ؼ�)
	* @param [in] text �ı�����
	* @param [in] bChanged �Ƿ���Ϊ�仯
	*/
	void SetPropertyText(const std::wstring& text, bool bChanged);

	/** ��ȡ����ֵ�ı�(��ʾ�ؼ�)
	*/
	std::wstring GetPropertyText() const;

	/** ��������ֵ��������ɫ(��ʾ�ؼ�)
	* @param [in] text �ı�����
	*/
	void SetPropertyTextColor(const std::wstring& textColor);

	/** ���������õ�����ֵ�ı���ʾ�ؼ�
	*/
	void SetPropertyFocus();

	/** ������ֵ��LabelBox����ӿؼ�
	*/
	bool AddPropertySubItem(Control* pControl);

	/** ������ֵ��LabelBox���Ƴ��ؼ�
	*/
	bool RemovePropertySubItem(Control* pControl);

	/** �ж�����ֵ��LabelBox���Ƿ�����ؼ�
	*/
	bool HasPropertySubItem(Control* pControl) const;

private:
	/** ���Ե�����
	*/
	UiString m_propertyName;

	/** ���Ե�ֵ
	*/
	UiString m_propertyValue;

	/** ���Ե�������Ϣ
	*/
	UiString m_description;

	/** �û��Զ�������
	*/
	size_t m_nPropertyData;

	/** �������ƺ�����ֵ���������ؼ�
	*/
	HBox* m_pHBox;

	/** �������Ƶ���ʾ�ؼ�
	*/
	LabelBox* m_pLabelBoxLeft;

	/** ����ֵ����ʾ�ؼ�
	*/
	LabelBox* m_pLabelBoxRight;

	/** ֻ��ģʽ
	*/
	bool m_bReadOnly;
};

/** �ı����͵����ԣ�ʹ��RichEdit�༭
*/
class PropertyGridTextProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridTextProperty(const std::wstring& propertyName,
					         const std::wstring& propertyValue,
					         const std::wstring& description = L"",
					         size_t nPropertyData = 0);

public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kText;
	}

	/** ��ȡ�µ�����ֵ���޸ĺ������ֵ, ������޸��򷵻�ԭֵ��
	*/
	virtual std::wstring GetPropertyNewValue() const override;

	/** ��ȡ�༭��ؼ�
	*/
	RichEdit* GetRichEdit() const { return m_pRichEdit; }

	/** ��������ģʽ����ʾ ***��
	 * @param[in] bPassword ����Ϊ true �ÿؼ���ʾ����Ϊ ***��false Ϊ��ʾ��������
	 */
	void SetPassword(bool bPassword);

	/** �Ƿ�Ϊ����ģʽ
	*/
	bool IsPassword() const { return m_bPassword; }

	/** �����Ƿ�֧��Spin�ؼ�
	* @param [in] bEnable true��ʾ֧��Spin�ؼ���false��ʾ��֧��Spin�ؼ�
	* @param [in] nMin ��ʾ�������ֵ���Сֵ
	* @param [in] nMax ��ʾ�������ֵ����ֵ����� nMin��nMaxͬʱΪ0, ��ʾ���������ֵ���Сֵ�����ֵ
	*/
	void SetEnableSpin(bool bEnable, int32_t nMin = 0, int32_t nMax = 0);

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

private:
	/** �༭��ؼ�(�����޸�����)
	*/
	RichEdit* m_pRichEdit;

	/** ����ģʽ
	*/
	bool m_bPassword;
};

/** ���������͵����ԣ�ʹ��Combo�༭
*/
class PropertyGridComboProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridComboProperty(const std::wstring& propertyName,
							  const std::wstring& propertyValue,
							  const std::wstring& description = L"",
							  size_t nPropertyData = 0);

public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kCombo;
	}

	/** ��ȡ�µ�����ֵ���޸ĺ������ֵ, ������޸��򷵻�ԭֵ��
	*/
	virtual std::wstring GetPropertyNewValue() const override;

	/** ����һ��������ѡ��
	* @param [in] optionText �������б��������
	* @return ���ظ�������±�ֵ
	*/
	size_t AddOption(const std::wstring& optionText);

	/** ��ȡ������ѡ��ĸ�ʽ
	*/
	size_t GetOptionCount() const;

	/** ��ȡ������������ı�
	* @param [in] nIndex ������±�ֵ����Ч��Χ��[0, GetOptionCount())
	*/
	std::wstring GetOption(size_t nIndex) const;

	/** �����������������
	* @param [in] nIndex ������±�ֵ����Ч��Χ��[0, GetOptionCount())
	* @param [in] nOptionData ��������
	*/
	void SetOptionData(size_t nIndex, size_t nOptionData);

	/** ��ȡ�������������
	* @param [in] nIndex ������±�ֵ����Ч��Χ��[0, GetOptionCount())
	*/
	size_t GetOptionData(size_t nIndex) const;

	/** ɾ��ָ��������
	* @param [in] nIndex ������±�ֵ����Ч��Χ��[0, GetOptionCount())
	*/
	bool RemoveOption(size_t nIndex);

	/** ɾ����������
	*/
	void RemoveAllOptions();

	/** ��ȡ��ǰѡ��������
	 * @return ���ص�ǰѡ��������, (�������Ч�������򷵻�Box::InvalidIndex)
	 */
	size_t GetCurSel() const;

	/** ѡ��һ������, ������ѡ���¼�
	 * @param[in] nIndex Ҫѡ���������������Ч��Χ��[0, GetOptionCount())
	 * @return ���� true ��ʾ�ɹ�������Ϊ false
	 */
	bool SetCurSel(size_t nIndex);

	/** ����Ϊ�б�ģʽ
	* @param [in] bListMode true��ʾ��֧�ֱ༭�ı���ֻ�ܴ���������ѡ��false��ʾ����༭������ѡ��
	*/
	void SetComboListMode(bool bListMode);

	/** ��ȡ������ӿ�
	*/
	Combo* GetCombo() const { return m_pCombo; }

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

	/** �����������˹���(���ڴ�����ʽ�Ӵ��ڵ�λ������)
	*/
	virtual void OnScrollPosChanged() override;

private:
	/** ������ӿ�
	*/
	Combo* m_pCombo;
};

/** �����������Ƶ�����
*/
class PropertyGridFontProperty : public PropertyGridComboProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(ԭ��������)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridFontProperty(const std::wstring& propertyName,
							 const std::wstring& propertyValue,
							 const std::wstring& description = L"",
						     size_t nPropertyData = 0);

public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kFont;
	}

	/** ��ȡ�µ�����ֵ���޸ĺ������ֵ, ������޸��򷵻�ԭֵ��
	*/
	virtual std::wstring GetPropertyNewValue() const override;

protected:

	/** ��ʼ������
	 */
	virtual void OnInit() override;

private:
	/** ��ȡϵͳ�����б�
	*/
	void GetSystemFontList(std::vector<std::wstring>& fontList) const;
};

/** ���������С������
*/
class PropertyGridFontSizeProperty : public PropertyGridComboProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(ԭ��������)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridFontSizeProperty(const std::wstring& propertyName,
								 const std::wstring& propertyValue,
								 const std::wstring& description = L"",
								 size_t nPropertyData = 0);

public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kFontSize;
	}

	/** ��ȡ�µ������Сֵ, ��ʾֵ���޸ĺ������ֵ, ������޸��򷵻�ԭֵ��
	*/
	virtual std::wstring GetPropertyNewValue() const override;

	/** ��ȡ�����Сֵ����������δ��DPI����Ӧֵ
	* @return ������б���ѡ�񣬷���ֵΪ�ǿգ����δ�ܴ��б���ѡ���򷵻ؿ�
	*/
	std::wstring GetFontSize() const;

	/** ��ȡ�����Сֵ��������������DPI����Ӧֵ
	* @return ������б���ѡ�񣬷���ֵΪ�ǿգ����δ�ܴ��б���ѡ���򷵻ؿ�
	*/
	std::wstring GetDpiFontSize() const;

	/** ��ȡ�����С��ʾ���ƶ�Ӧ�������Сֵ����������δ��DPI����Ӧֵ
	* @param [in] fontSizeName ���磺"���"
	*/
	std::wstring GetFontSize(const std::wstring& fontSizeName) const;

	/** ��ȡ�����С��ʾ���ƶ�Ӧ�������Сֵ��������������DPI����Ӧֵ
	* @param [in] fontSizeName ���磺"���"
	*/
	std::wstring GetDpiFontSize(const std::wstring& fontSizeName) const;

protected:

	/** ��ʼ������
	 */
	virtual void OnInit() override;

private:
	struct FontSizeInfo
	{
		std::wstring fontSizeName; //�����С����ʾ���ƣ�����"���"
		float fFontSize;		   //��λ�����أ�δ��DPI����Ӧ
		float fDpiFontSize;		   //��λ�����أ�����DPI����Ӧ
	};

	/** ��ȡϵͳ�����С�б�
	*/
	void GetSystemFontSizeList(std::vector<FontSizeInfo>& fontSizeList) const;

private:
	/** �����С
	*/
	std::vector<FontSizeInfo> m_fontSizeList;
};

/** ������ɫ������
*/
class PropertyGridColorProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(ԭ��������)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridColorProperty(const std::wstring& propertyName,
							  const std::wstring& propertyValue,
							  const std::wstring& description = L"",
							  size_t nPropertyData = 0);


public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kColor;
	}

	/** ��ȡ��ɫѡ��ؼ��ӿ�
	*/
	ComboButton* GetComboButton() const { return m_pComboButton; }

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

	/** �����������˹���(���ڴ�����ʽ�Ӵ��ڵ�λ������)
	*/
	virtual void OnScrollPosChanged() override;

private:
	/** ��ʼ��������ɫ��Combo��ť
	*/
	void InitColorCombo();

	/** ��ʾʰɫ������
	*/
	void ShowColorPicker();

	/** ����ѡ����ɫ
	*/
	void OnSelectColor(const std::wstring& color);

private:
	/** ��ɫѡ��ؼ�
	*/
	ComboButton* m_pComboButton;
};

/** ��������ʱ�������
*/
class PropertyGridDateTimeProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] dateTimeValue ����ʱ���ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @param [in] editFormat ����ʱ��ĸ�ʽ
	*/
	PropertyGridDateTimeProperty(const std::wstring& propertyName,
								 const std::wstring& dateTimeValue,
								 const std::wstring& description = L"",
								 size_t nPropertyData = 0,
								 DateTime::EditFormat editFormat = DateTime::EditFormat::kDateCalendar);


public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kDateTime;
	}

	/** ��ȡ����ʱ��ؼ��ӿ�
	*/
	DateTime* GetDateTime() const { return m_pDateTime; }

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

	/** �����������˹���(���ڴ�����ʽ�Ӵ��ڵ�λ������)
	*/
	virtual void OnScrollPosChanged() override;

private:
	/** ����ʱ��ؼ��ӿ�
	*/
	DateTime* m_pDateTime;

	/** ����ʱ��ĸ�ʽ
	*/
	DateTime::EditFormat m_editFormat;
};

/** ����IP��ַ������
*/
class PropertyGridIPAddressProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridIPAddressProperty(const std::wstring& propertyName,
							      const std::wstring& propertyValue,
								  const std::wstring& description = L"",
								  size_t nPropertyData = 0);


public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kIPAddress;
	}

	/** ��ȡIP��ַ�ؼ��ӿ�
	*/
	IPAddress* GetIPAddress() const { return m_pIPAddress; }

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

private:
	/** IP��ַ�ؼ�
	*/
	IPAddress* m_pIPAddress;
};

/** �����ȼ�������
*/
class PropertyGridHotKeyProperty : public PropertyGridProperty
{
public:
	/** ����һ������
	@param [in] propertyName ���Ե�����
	@param [in] propertyValue ���Ե�ֵ
	@param [in] description ���Ե�������Ϣ
	@param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridHotKeyProperty(const std::wstring& propertyName,
							   const std::wstring& propertyValue,
						       const std::wstring& description = L"",
							   size_t nPropertyData = 0);


public:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kHotKey;
	}

	/** ��ȡ�ȼ��ؼ��ӿ�
	*/
	HotKey* GetHotKey() const { return m_pHotKey; }

protected:
	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ��ʾ�������ر༭��ؼ�
	* @param [in] bShow ��ʾ��ʾ�༭�ؼ���false��ʾ���ر༭�ؼ�
	*/
	virtual Control* ShowEditControl(bool bShow) override;

private:
	/** �ȼ��ؼ�
	*/
	HotKey* m_pHotKey;
};

/** �����ļ�·������
*/
class PropertyGridFileProperty : public PropertyGridTextProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(�ļ���·��)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	* @param [in] bOpenFileDialog true��ʾ���ļ���false��ʾ�����ļ�
	* @param [in] fileTypes �Ի�����Դ򿪻򱣴���ļ�����
	* @param [in] nFileTypeIndex ѡ����ļ����ͣ���Ч��Χ��[0, fileTypes.size())
	* @param [in] defaultExt Ĭ�ϵ��ļ�����, ������"doc;docx"
	*/
	PropertyGridFileProperty(const std::wstring& propertyName,
							 const std::wstring& propertyValue,
							 const std::wstring& description = L"",
							 size_t nPropertyData = 0,
							 bool bOpenFileDialog = true,
							 const std::vector<FileDialog::FileType>& fileTypes = std::vector<FileDialog::FileType>(),
							 int32_t nFileTypeIndex = -1,
							 const std::wstring& defaultExt = L"");


protected:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kFile;
	}

	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ����������ť
	*/
	virtual void OnBrowseButtonClicked();

private:
	/** �����ť
	*/
	Button* m_pBrowseBtn;

	/** true��ʾ���ļ���false��ʾ�����ļ�
	*/
	bool m_bOpenFileDialog;

	/** �ļ����͹�����
	*/
	std::vector<FileDialog::FileType> m_fileTypes;

	/** ѡ����ļ������±�ֵ
	*/
	int32_t m_nFileTypeIndex;

	/** Ĭ�ϵ��ļ�����
	*/
	std::wstring m_defaultExt;
};

/** �����ļ�������
*/
class PropertyGridDirectoryProperty : public PropertyGridTextProperty
{
public:
	/** ����һ������
	* @param [in] propertyName ���Ե�����
	* @param [in] propertyValue ���Ե�ֵ(�ļ���·��)
	* @param [in] description ���Ե�������Ϣ
	* @param [in] nPropertyData �û��Զ�������
	*/
	PropertyGridDirectoryProperty(const std::wstring& propertyName,
							      const std::wstring& propertyValue,
							      const std::wstring& description = L"",
							      size_t nPropertyData = 0);


protected:
	/** ��ȡ��������
	*/
	virtual PropertyGridPropertyType GetPropertyType() const
	{
		return PropertyGridPropertyType::kDirectory;
	}

	/** �����Ƿ�������ڱ༭��ؼ�
	* @param [in] bEnable true��ʾ������ڱ༭��ؼ���false��ʾ��������ڱ༭��ؼ�
	*/
	virtual void EnableEditControl(bool bEnable) override;

	/** ����������ť
	*/
	virtual void OnBrowseButtonClicked();

private:
	/** �����ť
	*/
	Button* m_pBrowseBtn;
};

}//namespace ui

#endif //UI_CONTROL_PROPERTY_GRID_H_
