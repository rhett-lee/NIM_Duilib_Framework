#pragma once

#include "resource.h"

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

class MainForm;
class FindForm : public ui::WindowImplBase
{
public:
	explicit FindForm(MainForm* pMainForm);
	~FindForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void OnInitWindow() override;

	/**
	 * ��ʶ���� class name
	 */
	static const LPCTSTR kClassName;

private:
	//������һ��
	void OnFindNext();

private:
	//���ҽӿ�
	MainForm* m_pMainForm;

	//��������ѡ��
	ui::Option* m_pDirectionOption;

	//�Ƿ����ִ�Сд
	ui::CheckBox* m_pCaseSensitive;

	//�Ƿ�ȫ��ƥ��
	ui::CheckBox* m_pMatchWholeWord;

	//��������
	ui::RichEdit* m_pFindText;
};

