#include "stdafx.h"
#include "richlist_form.h"
#include "item.h"

const std::wstring RichlistForm::kClassName = L"Basic";

RichlistForm::RichlistForm():
	m_pListBox(nullptr)
{
}


RichlistForm::~RichlistForm()
{
}

std::wstring RichlistForm::GetSkinFolder()
{
	return L"list_box";
}

std::wstring RichlistForm::GetSkinFile()
{
	return L"list_box.xml";
}

std::wstring RichlistForm::GetWindowClassName() const
{
	return kClassName;
}

void RichlistForm::OnInitWindow()
{
	m_pListBox = dynamic_cast<ui::ListBox*>(FindControl(L"list"));
	ASSERT(m_pListBox != nullptr);
	if (m_pListBox == nullptr) {
		return;
	}
	bool bHListBox = dynamic_cast<ui::HListBox*>(m_pListBox) != nullptr;
	bool bVListBox = dynamic_cast<ui::VListBox*>(m_pListBox) != nullptr;
	bool bHTileListBox = dynamic_cast<ui::HTileListBox*>(m_pListBox) != nullptr;
	bool bVTileListBox = dynamic_cast<ui::VTileListBox*>(m_pListBox) != nullptr;

	for (auto i = 0; i < 300; i++) {
		Item* item = new Item;
		item->SetWindow(this);//����item.xml������Window��������Class���ԣ�������Ҫ����
		ui::GlobalManager::Instance().FillBoxWithCache(item, L"list_box/item.xml");

		if (bHListBox || bHTileListBox || bVTileListBox) {
			item->SetFixedWidth(ui::UiFixedInt(200), true, true);
		}

		std::wstring img = L"icon.png";
		std::wstring title = nbase::StringPrintf(L"���� [%02d]", i);

		item->InitSubControls(img, title);
		m_pListBox->AddItem(item);
	}

	m_pListBox->SetFocus();
	// �����б��е��ѡ��������¼�
	m_pListBox->AttachSelect(nbase::Bind(&RichlistForm::OnSelected, this, std::placeholders::_1));
}


bool RichlistForm::OnSelected(const ui::EventArgs& args)
{
	int current = static_cast<int>(args.wParam);
	int old = static_cast<int>(args.lParam);

	/*auto message = nbase::StringPrintf(L"��ѡ��������Ϊ %d �������һ��ѡ����������Ϊ %d\n", current, old);
	::OutputDebugStringW(message.c_str());

	ui::ListBoxVerVisible vVisibleType = ui::ListBoxVerVisible::kVisible;
	ui::ListBoxHorVisible hVisibleType = ui::ListBoxHorVisible::kVisible;
	if (m_pListBox != nullptr) {
		if (current == 20) {
			m_pListBox->EnsureVisible(200, vVisibleType, hVisibleType);
		}
		else if (current == 210) {
			m_pListBox->EnsureVisible(21, vVisibleType, hVisibleType);
		}
	}*/
	//nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), message, false, L"��ʾ", false);

	return true;
}

LRESULT RichlistForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
