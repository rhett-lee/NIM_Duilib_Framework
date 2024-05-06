#pragma once

// �� ui::ListBoxItem �м̳����п��ù���
class Item : public ui::ListBoxItem
{
public:
	Item();
	~Item();

	// �ṩ�ⲿ��������ʼ�� item ����
	void InitSubControls(const std::wstring& img, const std::wstring& title, size_t nDataIndex);
private:
	bool OnRemove(const ui::EventArgs& args);

private:
	ui::ListBox*	list_box_;

	ui::Control*	control_img_;
	ui::Label*		label_title_;
	ui::Progress*	progress_;
	ui::Button*		btn_del_;
	int64_t         t_time;
	size_t m_nDataIndex;
};

