#include "stdafx.h"
#include "app_db.h"

CAppDb::CAppDb()
{
	//������Դ�db��һЩ���� 
}


CAppDb::~CAppDb()
{
	//������Թر�db��һЩ����
}

bool CAppDb::LoadFromDb(std::vector<AppItem>& app_list)
{
	app_list.clear();
	//select from....
	//Ŀǰд��
	{
		AppItem item;
		item.m_id = "1";
		item.m_icon = L"1.png";
		item.m_isFrequent = false;
		item.m_name = L"���з���";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "2";
		item.m_icon = L"2.png";
		item.m_isFrequent = false;
		item.m_name = L"����Ԥ��";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "3";
		item.m_icon = L"3.png";
		item.m_isFrequent = true;
		item.m_name = L"����";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "4";
		item.m_icon = L"4.png";
		item.m_isFrequent = true;
		item.m_name = L"���ʵ�";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "5";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����5";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "6";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����6";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "7";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����7";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "8";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����8";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "9";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����9";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "10";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����10";
		app_list.emplace_back(item);
	}
	{
		AppItem item;
		item.m_id = "11";
		item.m_icon = L"5.png";
		item.m_isFrequent = false;
		item.m_name = L"����11";
		app_list.emplace_back(item);
	}
	
	return true;
}

bool CAppDb::SaveToDb(const AppItem& item)
{
	// insert or replace into ....
	return true;
}
