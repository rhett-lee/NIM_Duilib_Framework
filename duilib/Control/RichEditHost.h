#ifndef UI_CONTROL_RICHEDIT_HOST_H_
#define UI_CONTROL_RICHEDIT_HOST_H_

#pragma once

#include "duilib/Core/UiTypes.h"
//ʹ��Windows��ITextHostʵ��
#include <Richedit.h>
#include <TextServ.h>
#include <RichOle.h>

namespace ui
{

class RichEdit;
class UILIB_API RichEditHost : public ITextHost
{
public:
	/** ���캯������������ü���Ϊ1���ⲿ����ͨ��AddRef��Release���ƶ������������
	*/
	explicit RichEditHost(RichEdit* pRichEdit);
	RichEditHost(const RichEditHost& r) = delete;
	RichEditHost& operator=(const RichEditHost& r) = delete;

private:
	virtual ~RichEditHost();

public:
	/** ��ȡITextServices�ӿ�
	*/
	ITextServices* GetTextServices(void) const;

	/** �ͷ���Դ
	*/
	void Clear();

    void SetClientRect(const UiRect& rc);
	void GetControlRect(UiRect* prc);

	//�Ƿ��Զ����У����ڵ����ı�ģʽ����Ч�������ı�ģʽʱ��Ч��
    void SetWordWrap(bool bWordWrap);
	bool IsWordWrap() const;

	//�Ƿ��Զ�ѡ�񵥴�
	void SetEnableAutoWordSel(bool bEnableAutoWordSel);

	//�Ƿ�ֻ��
    void SetReadOnly(bool fReadOnly);
	bool IsReadOnly() const;

	//���������ַ�������Ϊ��Ч���ַ�����������'\0'
	void SetPasswordChar(WCHAR chPasswordChar);
    void SetPassword(bool bPassword);
	bool IsPassword() const;
	void SetShowPassword(bool bShow); //�����Ƿ���ʾ����
	bool IsShowPassword() const;//�Ƿ���ʾ����
	void SetFlashPasswordChar(bool bFlash);
	bool IsFlashPasswordChar() const;

	//�Ƿ�ֻ�������������ַ�
	bool IsNumberOnly() const;
	void SetNumberOnly(bool bNumberOnly);

	//�Ƿ�֧�ֶ���
	bool IsMultiLine() const;
	void SetMultiLine(bool bMultiLine);

	//�ı������������뷽ʽ
	void SetHAlignType(HorAlignType alignType);
	void SetVAlignType(VerAlignType alignType);

	//������������������
	void SetVScrollBar(bool bEnable);
	void SetHScrollBar(bool bEnable);	

	//���û������һ�а� ENTER ʱ���Զ����ı����Ϲ���һҳ��
	void SetAutoVScroll(bool bEnable);

	//���û�����β����һ���ַ�ʱ���Զ����ı����ҹ��� 10 ���ַ���
	//���û��� Enter ʱ���ؼ��Ὣ�����ı���������λ�á�
	void SetAutoHScroll(bool bEnable);

	// ��������
    void SetFontId(const std::wstring& fontId);
	//�����ı���ɫ
    void SetTextColor(COLORREF dwColor);
	//��ȡ�ı���ɫ
	COLORREF GetTextColor() const;

    void SetExtent(SIZEL sizelExtent);
    void SetAllowBeep(bool bAllowBeep);
	bool IsAllowBeep() const;
	bool IsRichText() const;
    void SetRichText(bool fNew);
    bool SetSaveSelection(bool fSaveSelection);
	void SetHideSelection(bool fHideSelection);
    bool SetCursor(const UiRect* prc, const UiPoint* pt);
    void SetTransparent(bool fTransparent);    
    void SetDisabled(bool fOn);
    void SetSelBarWidth(LONG lSelBarWidth);

    void SetCharFormat(const CHARFORMAT2W& c);
    void SetParaFormat(const PARAFORMAT2& p);

	HRESULT OnTxInPlaceDeactivate();
	HRESULT OnTxInPlaceActivate(LPCRECT prcClient);

public:

    static void GetLogFont(const std::wstring& fontId, LOGFONT& lf);

public:
    // -----------------------------
    //	IUnknown interface
    // -----------------------------
    virtual HRESULT _stdcall QueryInterface(REFIID riid, void** ppvObject) override;
    virtual ULONG _stdcall AddRef(void) override;
    virtual ULONG _stdcall Release(void) override;

    // -----------------------------
    //	ITextHost interface
    // -----------------------------
	//@cmember Get the DC for the host
	virtual HDC TxGetDC() override;

	//@cmember Release the DC gotten from the host
	virtual INT TxReleaseDC(HDC hdc) override;

	//@cmember Show the scroll bar
	virtual BOOL TxShowScrollBar(INT fnBar, BOOL fShow) override;

	//@cmember Enable the scroll bar
	virtual BOOL TxEnableScrollBar(INT fuSBFlags, INT fuArrowflags) override;

	//@cmember Set the scroll range
	virtual BOOL TxSetScrollRange( INT fnBar,
								   LONG nMinPos,
								   INT nMaxPos,
								   BOOL fRedraw) override;

	//@cmember Set the scroll position
	virtual BOOL TxSetScrollPos(INT fnBar, INT nPos, BOOL fRedraw) override;

	//@cmember InvalidateRect
	virtual void TxInvalidateRect(LPCRECT prc, BOOL fMode) override;

	//@cmember Send a WM_PAINT to the window
	virtual void TxViewChange(BOOL fUpdate) override;

	//@cmember Create the caret
	virtual BOOL TxCreateCaret(HBITMAP hbmp, INT xWidth, INT yHeight) override;

	//@cmember Show the caret
	virtual BOOL TxShowCaret(BOOL fShow) override;

	//@cmember Set the caret position
	virtual BOOL TxSetCaretPos(INT x, INT y) override;

	//@cmember Create a timer with the specified timeout
	virtual BOOL TxSetTimer(UINT idTimer, UINT uTimeout) override;

	//@cmember Destroy a timer
	virtual void TxKillTimer(UINT idTimer) override;

	//@cmember Scroll the content of the specified window's client area
	virtual void TxScrollWindowEx( INT dx,
								   INT dy,
								   LPCRECT lprcScroll,
								   LPCRECT lprcClip,
								   HRGN hrgnUpdate,
								   LPRECT lprcUpdate,
								   UINT fuScroll) override;

	//@cmember Get mouse capture
	virtual void TxSetCapture(BOOL fCapture) override;

	//@cmember Set the focus to the text window
	virtual void TxSetFocus() override;

	//@cmember Establish a new cursor shape
	virtual void TxSetCursor(HCURSOR hcur, BOOL fText) override;

	//@cmember Converts screen coordinates of a specified point to the client coordinates 
	virtual BOOL TxScreenToClient(LPPOINT lppt) override;

	//@cmember Converts the client coordinates of a specified point to screen coordinates
	virtual BOOL TxClientToScreen(LPPOINT lppt) override;

	//@cmember Request host to activate text services
	virtual HRESULT TxActivate(LONG* plOldState) override;

	//@cmember Request host to deactivate text services
	virtual HRESULT TxDeactivate(LONG lNewState) override;

	//@cmember Retrieves the coordinates of a window's client area
	virtual HRESULT TxGetClientRect(LPRECT prc) override;

	//@cmember Get the view rectangle relative to the inset
	virtual HRESULT TxGetViewInset(LPRECT prc) override;

	//@cmember Get the default character format for the text
	virtual HRESULT TxGetCharFormat(const CHARFORMATW** ppCF) override;

	//@cmember Get the default paragraph format for the text
	virtual HRESULT TxGetParaFormat(const PARAFORMAT** ppPF) override;

	//@cmember Get the background color for the window
	virtual COLORREF TxGetSysColor(int nIndex) override;

	//@cmember Get the background (either opaque or transparent)
	virtual HRESULT TxGetBackStyle(TXTBACKSTYLE* pstyle) override;

	//@cmember Get the maximum length for the text
	virtual HRESULT TxGetMaxLength(DWORD* plength) override;

	//@cmember Get the bits representing requested scroll bars for the window
	virtual HRESULT TxGetScrollBars(DWORD* pdwScrollBar) override;

	//@cmember Get the character to display for password input
	virtual HRESULT TxGetPasswordChar(_Out_ TCHAR* pch) override;

	//@cmember Get the accelerator character
	virtual HRESULT TxGetAcceleratorPos(LONG* pcp) override;

	//@cmember Get the native size
	virtual HRESULT TxGetExtent(LPSIZEL lpExtent) override;

	//@cmember Notify host that default character format has changed
	virtual HRESULT OnTxCharFormatChange(const CHARFORMATW* pCF) override;

	//@cmember Notify host that default paragraph format has changed
	virtual HRESULT OnTxParaFormatChange(const PARAFORMAT* pPF) override;

	//@cmember Bulk access to bit properties
	virtual HRESULT TxGetPropertyBits(DWORD dwMask, DWORD* pdwBits) override;

	//@cmember Notify host of events
	virtual HRESULT TxNotify(DWORD iNotify, void* pv) override;

	// East Asia Methods for getting the Input Context
	virtual HIMC TxImmGetContext() override;
	virtual void TxImmReleaseContext(HIMC himc) override;

	//@cmember Returns HIMETRIC size of the control bar.
	virtual HRESULT TxGetSelectionBarWidth(LONG* lSelBarWidth) override;

private:
	/** ֪ͨOnTxPropertyBitsChange�ӿ�
	*/
	void OnTxPropertyBitsChange(DWORD dwMask, DWORD dwBits);

	//�����ĳ�ʼ��
	void Init();

	//��ʼ��������Ϣ
	void InitCharFormat(const LOGFONT& lf);

	//ת�����θ�ʽ
	UiRect MakeUiRect(const RECT& rc);

	// Convert Pixels on the X axis to Himetric
	LONG DXtoHimetricX(LONG dx, LONG xPerInch);

	// Convert Pixels on the Y axis to Himetric
	LONG DYtoHimetricY(LONG dy, LONG yPerInch);

private:
	//���ü���
	ULONG m_cRefs;

	//RichEdit�ؼ���UI��ӿ�
    RichEdit* m_pRichEdit;

	// pointer to Text Services object
	ITextServices* m_pTextServices;

    uint16_t m_dwStyle;			// style bits
    bool m_fEnableAutoWordSel;	// enable Word style auto word selection?
    bool m_fWordWrap;			// Whether control should word wrap
	bool m_fAllowBeep;			// Whether beep is allowed
    bool m_fRichText;			// Whether control is rich text
    bool m_fSaveSelection;		// Whether to save the selection when inactive
    bool m_fInplaceActive;		// Whether control is inplace active
    bool m_fTransparent;		// Whether control is transparent

    LONG m_lSelBarWidth;		// Width of the selection bar
    UiRect m_rcClient;			// Client Rect for this control
    SIZEL m_sizelExtent;		// Extent array
	
    CHARFORMAT2 m_charFormat;  //���ֵ�����
    PARAFORMAT2	m_paraFormat;	//�����ʽ
    WCHAR m_chPasswordChar;		// Password character
	bool m_bShowPassword;       //�Ƿ���ʾ����
	bool m_bFlashPasswordChar;  //���ݵ���ʾ�����ַ���Ȼ��������
};


}//name space ui

#endif // UI_CONTROL_RICHEDIT_HOST_H_
