//MyDuilibForm.cpp
#include "MyDuilibForm.h"

const std::wstring MyDuilibForm::kClassName = L"MyDuilibForm";

MyDuilibForm::MyDuilibForm()
{
}


MyDuilibForm::~MyDuilibForm()
{
}

std::wstring MyDuilibForm::GetSkinFolder()
{
	return L"my_duilib_app";
}

std::wstring MyDuilibForm::GetSkinFile()
{
	return L"MyDuilibForm.xml";
}

std::wstring MyDuilibForm::GetWindowClassName() const
{
	return kClassName;
}

void MyDuilibForm::OnInitWindow()
{
	//���ڳ�ʼ����ɣ����Խ��б�Form�ĳ�ʼ��

}

LRESULT MyDuilibForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	//���ڹر�ʱ����ֹ���̵߳���Ϣѭ�����Ӷ��˳�����
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
