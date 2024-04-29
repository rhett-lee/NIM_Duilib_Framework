#pragma once

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

class RichEditFindReplace
{
public:
    RichEditFindReplace();

public:
	//���ù�����RichEdit�ؼ�
	void SetRichEdit(ui::RichEdit* pRichEdit);

public:
	//����
	bool FindRichText(const std::wstring& findText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);

	//������һ��
	bool FindNext();

	//�滻
	bool ReplaceRichText(const std::wstring& findText, const std::wstring& replaceText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);
	
	//ȫ���滻
	bool ReplaceAllRichText(const std::wstring& findText, const std::wstring& replaceText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);

protected:
	//û�ҵ����ص�����
	virtual void OnTextNotFound(const std::wstring& findText);

	//��ʼȫ���滻
	virtual void OnReplaceAllCoreBegin();

	//���ȫ���滻
	virtual void OnReplaceAllCoreEnd(int replaceCount);

private:
	//���Һ���ʵ��
	bool FindTextSimple(const std::wstring& findText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord);

	//���Ҳ�ѡ��
	long FindAndSelect(DWORD dwFlags, FINDTEXTEX& ft);

	//�Ƚϵ�ǰѡ�����ı��Ƿ�ƥ��
	bool SameAsSelected(const std::wstring& replaceText, BOOL bMatchCase);

	//û�ҵ����ص�����
	void TextNotFound(const std::wstring& findText);

	//���������滻���ڵ�λ��
	void AdjustDialogPosition(HWND hWndDialog);

private:
    //RichEdit�ؼ��ӿ�
    ui::RichEdit* m_pRichEdit;

	//��������
	std::wstring m_sFindNext;

	//�滻����
	std::wstring m_sReplaceWith;

	//��������ѡ��
	bool m_bFindDown;

	//�Ƿ����ִ�Сд
	bool m_bMatchCase;

	//�Ƿ�ȫ��ƥ��
	bool m_bMatchWholeWord;

private:
	//����״̬: �Ƿ�Ϊ��һ������
	bool m_bFirstSearch;

	//��ʼ������λ��
	long m_nInitialSearchPos;

	//�ɵĹ��
	HCURSOR m_hOldCursor;
};

