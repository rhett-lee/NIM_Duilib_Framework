#pragma once

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

class RenderForm : public ui::WindowImplBase
{
public:
	RenderForm();
	~RenderForm();

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
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/**@brief ��Ҫ�����Ŀؼ����Ǳ�׼�Ŀؼ�����ʱ����øú���
	 * @param[in] strClass �ؼ�����
	 * @return ����һ���Զ���ؼ�ָ�룬һ������¸��� strClass ���������Զ���Ŀؼ�
	 */
	virtual ui::Control* CreateControl(const std::wstring& strClass) override;

	/** ��������
	*/
	static const std::wstring kClassName;

private:
	//����PropertyGrid�ؼ�
	void TestPropertyGrid();

	//��ȡPropertyGrid�ؼ��Ľ��
	void CheckPropertyGridResult();
};

