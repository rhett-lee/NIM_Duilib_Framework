#include "render_form.h"
#include "RenderTest1.h"
#include "RenderTest2.h"
#include "RenderTest3.h"

const std::wstring RenderForm::kClassName = L"render";

RenderForm::RenderForm()
{
}


RenderForm::~RenderForm()
{
}

std::wstring RenderForm::GetSkinFolder()
{
	return L"render";
}

std::wstring RenderForm::GetSkinFile()
{
	return L"render.xml";
}

std::wstring RenderForm::GetWindowClassName() const
{
	return kClassName;
}

void RenderForm::OnInitWindow()
{
	TestPropertyGrid();
}

LRESULT RenderForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	CheckPropertyGridResult();
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

ui::Control* RenderForm::CreateControl(const std::wstring& strClass)
{
	if (strClass == L"RenderTest1") {
		return new ui::RenderTest1;
	}
	else if (strClass == L"RenderTest2") {
		return new ui::RenderTest2;
	}
	if (strClass == L"RenderTest3") {
		return new ui::RenderTest3;
	}
	return nullptr;
}

void RenderForm::TestPropertyGrid()
{
	ui::PropertyGrid* pPropertyGrid = dynamic_cast<ui::PropertyGrid*>(FindControl(L"property_grid_test"));
	if (pPropertyGrid == nullptr) {
		return;
	}
	pPropertyGrid->SetEnableHeaderCtrl(true, L"Property", L"Value");
	pPropertyGrid->SetEnableDescriptionArea(true);

	ui::PropertyGridGroup* pGroup = nullptr;
	
	pGroup = pPropertyGrid->AddGroup(L"����һ", L"������Ϣһ", (size_t)this);
	ASSERT(pGroup->GetGroupData() == (size_t)this);
	auto p = pPropertyGrid->AddTextProperty(pGroup, L"����1", L"ֵ1", L"����1��������Ϣ", (size_t)this);
	ASSERT(p->GetPropertyData() == (size_t)this);
	auto p00 = pPropertyGrid->AddTextProperty(pGroup, L"����2", L"ֵ2", L"����2��������Ϣ��Disable");
	p00->SetEnabled(false);

	pGroup = pPropertyGrid->AddGroup(L"�����", L"������Ϣ��");
	pPropertyGrid->AddTextProperty(pGroup, L"����2", L"ֵ2", L"����2��������Ϣ");

	pGroup = pPropertyGrid->AddGroup(L"������", L"������Ϣ��");
	auto p0 = pPropertyGrid->AddTextProperty(pGroup, L"����3-0(�ı�)", L"�ı�ֵ3-0", L"����3��������Ϣ");
	auto p1 = pPropertyGrid->AddTextProperty(pGroup, L"����3-1(����)", L"3", L"����3��������Ϣ������Spin�ؼ�������");
	p1->SetEnableSpin(true, -10, 10);

	auto p2 = pPropertyGrid->AddTextProperty(pGroup, L"����3-2(ֻ��)", L"ֵ3-2", L"����3��������Ϣ");
	p2->SetReadOnly(true);

	auto p3 = pPropertyGrid->AddTextProperty(pGroup, L"����3-3(����)", L"ֵ3-3", L"����3��������Ϣ");
	p3->SetPassword(true);

	pGroup = pPropertyGrid->AddGroup(L"������", L"������Ϣ��");
	auto p10 = pPropertyGrid->AddComboProperty(pGroup, L"����4-1(������)", L"�ı�ֵ4", L"����4��������Ϣ");
	p10->AddOption(L"ȡֵ1");
	p10->AddOption(L"ȡֵ2");
	p10->AddOption(L"ȡֵ3");
	p10->SetComboListMode(true);

	auto p11 = pPropertyGrid->AddComboProperty(pGroup, L"����4-1(������)", L"�ı�ֵ4", L"����4��������Ϣ");
	p11->AddOption(L"ȡֵ1");
	p11->AddOption(L"ȡֵ2");
	p11->AddOption(L"ȡֵ3");
	p11->SetComboListMode(false);//Ĭ��

	pGroup = pPropertyGrid->AddGroup(L"������", L"������Ϣ�壺����");
	auto p20 = pPropertyGrid->AddFontProperty(pGroup, L"����", L"����", L"������Ϣ��������������");
	auto p21 = pPropertyGrid->AddFontSizeProperty(pGroup, L"�ֺ�", L"���", L"������Ϣ�����������С");

	auto s000 = p21->GetPropertyNewValue();
	auto s001 = p21->GetFontSize();
	auto s002 = p21->GetDpiFontSize();
	auto s003 = p21->GetFontSize(L"����");
	auto s004 = p21->GetDpiFontSize(L"����");

	auto p22 = pPropertyGrid->AddColorProperty(pGroup, L"��ɫ", L"Blue", L"������Ϣ������������ɫ");

	pGroup = pPropertyGrid->AddGroup(L"������", L"������Ϣ��������ʱ��");
	pPropertyGrid->AddDateTimeProperty(pGroup, L"����", L"2023-12-07", L"������Ϣ����������");
	pPropertyGrid->AddDateTimeProperty(pGroup, L"����", L"2023/12/07", L"������Ϣ����������");
	pPropertyGrid->AddDateTimeProperty(pGroup, L"����", L"2023-12-07", L"������Ϣ����������", 0,
										ui::DateTime::EditFormat::kDateUpDown);
	pPropertyGrid->AddDateTimeProperty(pGroup, L"����ʱ��", L"2023-12-07 17:30:02", L"������Ϣ����������ʱ��", 0, 
										ui::DateTime::EditFormat::kDateTimeUpDown);
	pPropertyGrid->AddDateTimeProperty(pGroup, L"����ʱ��", L"2023-12-07 17:30", L"������Ϣ����������ʱ��", 0,
										ui::DateTime::EditFormat::kDateMinuteUpDown);
	pPropertyGrid->AddDateTimeProperty(pGroup, L"ʱ��", L"17:30:02", L"������Ϣ������ʱ��", 0,
										ui::DateTime::EditFormat::kTimeUpDown);
	pPropertyGrid->AddDateTimeProperty(pGroup, L"ʱ��", L"17:30", L"������Ϣ������ʱ��", 0,
										ui::DateTime::EditFormat::kMinuteUpDown);

	pGroup = pPropertyGrid->AddGroup(L"������", L"������Ϣ��");
	pPropertyGrid->AddIPAddressProperty(pGroup, L"IP��ַ", L"192.168.0.1", L"������Ϣ��IP��ַ");
	pPropertyGrid->AddHotKeyProperty(pGroup, L"�ȼ�1", L"Ctrl+C", L"������Ϣ���ȼ� HotKey�ؼ�1");
	pPropertyGrid->AddHotKeyProperty(pGroup, L"�ȼ�2", L"Ctrl+Shift+C", L"������Ϣ���ȼ� HotKey�ؼ�2");
	pPropertyGrid->AddHotKeyProperty(pGroup, L"�ȼ�3", L"Ctrl+Shift+Alt+C", L"������Ϣ���ȼ� HotKey�ؼ�3");
	pPropertyGrid->AddHotKeyProperty(pGroup, L"�ȼ�4", L"Ctrl+Shift", L"������Ϣ���ȼ� HotKey�ؼ�4");

	pGroup = pPropertyGrid->AddGroup(L"�����", L"������Ϣ��");
	auto p80 = pPropertyGrid->AddFileProperty(pGroup, L"�ļ�·��", L"C:\\Test-Save.txt", L"������Ϣ���ļ�·��", 0,
		                                      false, 
											  { 
												  {L"Text�ļ�", L"*.txt"},
												  {L"CSV�ļ�", L"*.csv"},
												  {L"INI�ļ�", L"*.ini"},
												  {L"�����ļ�", L"*.*"}
		                                      }, 
											  0, L"txt");
	auto p81 = pPropertyGrid->AddFileProperty(pGroup, L"�ļ�·��", L"C:\\Test-Open.txt", L"������Ϣ���ļ�·��", 0,
											  true, 
											  { 
												  {L"Text�ļ�", L"*.txt"},
												  {L"CSV�ļ�", L"*.csv"},
												  {L"INI�ļ�", L"*.ini"},
												  {L"�����ļ�", L"*.*"}
		                                      }, 
											  0, L"txt");

	auto p82 = pPropertyGrid->AddDirectoryProperty(pGroup, L"�ļ���", L"C:\\Test\\", L"������Ϣ���ļ���");

	return;
}

void RenderForm::CheckPropertyGridResult()
{
	ui::PropertyGrid* pPropertyGrid = dynamic_cast<ui::PropertyGrid*>(FindControl(L"property_grid_test"));
	if (pPropertyGrid == nullptr) {
		return;
	}

	struct PropertyData
	{
		std::wstring name;
		std::wstring oldValue;
		std::wstring newValue;
	};
	typedef std::vector<PropertyData> PropertyDataList;
	std::map<std::wstring, PropertyDataList> propertyMap;

	std::vector<ui::PropertyGridProperty*> properties;
	std::vector<ui::PropertyGridGroup*> groups;
	pPropertyGrid->GetGroups(groups);
	for (auto pGroup : groups) {
		if (pGroup != nullptr) {
			PropertyDataList& dataList = propertyMap[pGroup->GetGroupName()];
			pGroup->GetProperties(properties);
			for (auto pProperty : properties) {
				if (pProperty != nullptr) {
					PropertyData data;
					data.name = pProperty->GetPropertyName();
					data.oldValue = pProperty->GetPropertyValue();
					data.newValue = pProperty->GetPropertyNewValue();
					dataList.push_back(data);
				}
			}
		}
	}
	propertyMap.clear();
}