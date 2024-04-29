#pragma once

#include "resource.h"

// base header
#include "base/base.h"

// duilib
#include "duilib/duilib.h"

#include "RichEditFindReplace.h"

class FindForm;
class ReplaceForm;
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

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void OnInitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;
	virtual LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;
	virtual LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	static const std::wstring kClassName;

	//����/�滻�ӿ�
	void FindRichText(const std::wstring& findText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);
	void ReplaceRichText(const std::wstring& findText, const std::wstring& replaceText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);
	void ReplaceAllRichText(const std::wstring& findText, const std::wstring& replaceText, bool bFindDown, bool bMatchCase, bool bMatchWholeWord, HWND hWndDialog);

	//��ȡRichEdit�ӿ�
	ui::RichEdit* GetRichEdit() const;

private:
	//����Ĭ�ϵ��ı�����
	void LoadRichEditData();

	//���ļ��������ļ������Ϊ�ļ�
	void OnOpenFile();
	void OnSaveFile();
	void OnSaveAsFile();

	bool LoadFile(const std::wstring& filePath);
	bool SaveFile(const std::wstring& filePath);

	//�ж�һ���ļ���չ���Ƿ�ΪRTF�ļ�
	bool IsRtfFile(const std::wstring& filePath) const;

	static DWORD CALLBACK StreamReadCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR* pcb);
	static DWORD CALLBACK StreamWriteCallback(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR* pcb);

	//���±���״̬
	void UpdateSaveStatus();

private:
	//����/�滻
	void OnFindText();
	void OnFindNext();
	void OnReplaceText();

private://�����������
	struct FontInfo
	{
		LOGFONT lf;
		DWORD fontType;
	};

	struct FontSizeInfo
	{
		std::wstring fontSizeName;
		float fFontSize;	//��λ�����أ�δ��DPI����Ӧ
		int32_t fontSize;   //��λ�����أ�����DPI����Ӧ
	};

	//��ȡ����ṹ
	bool GetRichEditLogFont(LOGFONT& lf) const;

	//��ʼ��������Ϣ
	void InitCharFormat(const LOGFONT& lf, CHARFORMAT2& charFormat) const;

	//����ϵͳĬ�϶Ի�����������
	void OnSetFont();

	//��ȡϵͳ�����б�
	void GetSystemFontList(std::vector<FontInfo>& fontList) const;

	//��ȡ�����Сӳ���
	void GetFontSizeList(std::vector<FontSizeInfo>& fontSizeList) const;

	//�������尴ť��״̬
	void UpdateFontStatus();

	//���������С��״̬
	void UpdateFontSizeStatus();

	//������������
	void SetFontName(const std::wstring& fontName);

	//���������С
	void SetFontSize(const std::wstring& fontSize);

	//���������С: bIncreaseFontSize Ϊtrue��ʾ���������С��Ϊfalse��ʾ��С�����С
	void AdjustFontSize(bool bIncreaseFontSize);

	//����������ʽ�����壩
	void SetFontBold(bool bBold);

	//����������ʽ��б�壩
	void SetFontItalic(bool bItalic);

	//����������ʽ���»��ߣ�
	void SetFontUnderline(bool bUnderline);

	//����������ʽ��ɾ���ߣ�
	void SetFontStrikeOut(bool bStrikeOut);

	/** �����ı���ɫ
	*/
	void SetTextColor(const std::wstring& newColor);

	//ö������ص�����
	static int CALLBACK EnumFontFamExProc(const LOGFONT* lpelfe, const TEXTMETRIC* lpntme, DWORD fontType, LPARAM lParam);

	//�������Сת����Rich Edit�ؼ�������߶�
	int32_t ConvertToFontHeight(int32_t fontSize) const;

	/** ��ȡRichEdit�ؼ����ַ���ʽ
	*/
	void GetCharFormat(CHARFORMAT2& charFormat) const;

	/** ����RichEdit�ؼ����ַ���ʽ
	*/
	void SetCharFormat(CHARFORMAT2& charFormat);

private:
	//�������ű���
	void UpdateZoomValue();

	//��ʼ��������ɫ��Combo��ť
	void InitColorCombo();

	//��ʾʰɫ������
	void ShowColorPicker();

private:

	//RichEdit�ؼ��ӿ�
	ui::RichEdit* m_pRichEdit;

	//��ǰ�򿪵��ļ�
	std::wstring m_filePath;

	//���水ť������
	std::wstring m_saveBtnText;

	//����
	FindForm* m_pFindForm;

	//�滻
	ReplaceForm* m_pReplaceForm;

	//�����滻ʵ��
	RichEditFindReplace m_findReplace;

private:
	//���������б�
	std::vector<FontInfo> m_fontList;

	//�����С�б�
	std::vector<FontSizeInfo> m_fontSizeList;
};


