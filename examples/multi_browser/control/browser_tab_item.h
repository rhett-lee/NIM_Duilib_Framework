#pragma once

/** @class BrowserTabItem
  * @brief ���ǩ��������ڶ�����ǩ�ؼ�
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class BrowserTabItem : public ui::ListBoxItem
{
public:
	BrowserTabItem();

	/** 
	* ��ʼ���ؼ��ڲ�ָ��	
	* @param[in] browser_id �����id
	* @return void �޷���ֵ
	*/
	void InitControl(std::string browser_id);

	/**
	* ������ʾ�����������
	* @param[in] name ����
	* @return void	�޷���ֵ
	*/
	void SetTitle(std::wstring name);

	/**
	* ������ʾ�������ͷ��
	* @param[in] icon ͷ��·��
	* @return void	�޷���ֵ
	*/
	void SetIcon(std::wstring icon);

private:

	/**
	* �������������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMouseEnter(const ui::EventArgs& msg);

	/**
	* ��������Ƴ���Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnMouseLeave(const ui::EventArgs& msg);

	/**
	* ����ؼ��Ĳ˵���Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnItemMenu(const ui::EventArgs& msg);

	/**
	* �����˵�
	* @param[in] point ��������
	* @return void	�޷���ֵ
	*/
	void PopupItemMenu(POINT point);

	/**
	* ����˵����������Ϣ
	* @param[in] msg ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool MergeItemMenuItemClick(const ui::EventArgs& msg);

private:
	ui::Control		*icon_;
	ui::Label		*name_;
	ui::Button		*button_close_;

	std::wstring	session_id_;
};