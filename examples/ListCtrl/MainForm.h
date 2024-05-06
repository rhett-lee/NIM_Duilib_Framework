#pragma once

#include "resource.h"

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

class MainForm : public ui::WindowImplBase
{
public:
	MainForm();
	~MainForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/** �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/** �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void OnInitWindow() override;

	/** ��������
	*/
	static const std::wstring kClassName;

private:
	/** �������
	*/
	void InsertItemData(int32_t nRows, int32_t nColumns, int32_t nImageId);

	/** ִ��һЩ���ܲ���
	*/
	void RunListCtrlTest();

	/** ���Ƹ���
	*/
	void OnColumnChanged(size_t nColumnId);
};


