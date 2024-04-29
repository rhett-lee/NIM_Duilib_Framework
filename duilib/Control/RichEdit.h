#ifndef UI_CONTROL_RICHEDIT_H_
#define UI_CONTROL_RICHEDIT_H_

#pragma once

#include "duilib/Box/ScrollBox.h"
#include "duilib/Image/Image.h"
#include "duilib/Control/RichEditCtrl.h"

namespace ui 
{

class RichEditHost;
class ControlDropTarget;
class VBox;
class UILIB_API RichEdit : public ScrollBox
{
public:
	typedef std::function<bool(LONG, LONG, UiSize&)> FunGetNaturalSize;
public:
	RichEdit();
	RichEdit(const RichEdit& r) = delete;
	RichEdit& operator=(const RichEdit& r) = delete;
    virtual ~RichEdit();

public:
	/** �ж��Ƿ���� TAB ������Ϣ
	 * @return ���� true ��ʾ���ܣ�false ��ʾ������
	 */
	virtual bool IsWantTab() const override;

	/** �ж��Ƿ���� TAB ������Ϣ
	 * @param[in] bWantTab Ϊ true ����ܸ���Ϣ��false Ϊ������
	 */
    void SetWantTab(bool bWantTab = true);

	/** �ж��Ƿ���� RETURN ������Ϣ
	 * @return ���� true ��ʾ���ܣ�false ��ʾ������
	 */
    bool IsNeedReturnMsg();

	/** �����Ƿ���� RETURN ������Ϣ
	 * @param[in] bNeedReturnMsg Ϊ true ����ܸ���Ϣ��false Ϊ������
	 */
    void SetNeedReturnMsg(bool bNeedReturnMsg = true);

	/** �ж��Ƿ����CTRL+RETURN ��ϼ���Ϣ
	 * @return ���� true ��ʾ���ܣ�false ��ʾ������
	 */
    bool IsReturnMsgWantCtrl();

	/** �����Ƿ����CTRL+RETUREN ��ϼ���Ϣ
	 * @param[in] bReturnMsgWantCtrl Ϊ true ����ܸ���Ϣ��false Ϊ������
	 */
    void SetReturnMsgWantCtrl(bool bReturnMsgWantCtrl = true);

	/** �Ƿ��Ǹ��ı�ģʽ
	 * @return ���� true Ϊ���ı�ģʽ��֧�ַḻ���ı���ʽ��֧��RTF��ʽ
	           ���� false Ϊ���ı�ģʽ�����ı��ؼ��е��ı�ֻ����һ�ָ�ʽ
	 */
    bool IsRichText();

	/** ���ÿؼ�Ϊ���ı�ģʽ
	 * @param[in] bRichText ���� true Ϊ���ı�ģʽ��false Ϊ���ı�ģʽ
	 */
    void SetRichText(bool bRichText = true);

	/** �Ƿ���ֻ��״̬
	 * @return ���� true Ϊֻ��״̬������Ϊ false
	 */
    bool IsReadOnly();

	/** ���ÿؼ�Ϊֻ��״̬
	 * @param[in] bReadOnly ���� true �ÿؼ���Ϊֻ��״̬��false Ϊ��д��״̬
	 */
    void SetReadOnly(bool bReadOnly = true);

	/** �Ƿ�������״̬�ؼ�
	 * @return ���� true ��ʾ������ؼ�������Ϊ false
	 */
	bool IsPassword();

	/** ���ÿؼ�Ϊ����ؼ�����ʾ ***��
	 * @param[in] bPassword ����Ϊ true �ÿؼ���ʾ����Ϊ ***��false Ϊ��ʾ��������
	 */
	void SetPassword(bool bPassword);

	/** �����Ƿ���ʾ����
	*/
	void SetShowPassword(bool bShow);

	/** �Ƿ���ʾ����
	*/
	bool IsShowPassword() const;

	/** ���������ַ�
	*/
	void SetPasswordChar(wchar_t ch);

	/** �����Ƿ��������ַ�������ʾ�����أ�����IsShowPassword()Ϊtrue��������ģʽ��ʱ����Ч��
	*/
	void SetFlashPasswordChar(bool bFlash);

	/** ��ȡ�Ƿ��������ַ�������ʾ������
	*/
	bool GetFlashPasswordChar() const;

	/** �Ƿ�ֻ������������
	*/
	bool IsNumberOnly() const;

	/** �����Ƿ�ֻ������������
	*/
	void SetNumberOnly(bool bNumberOnly);

	/** ����������������(����IsNumberOnly()Ϊtrue��ʱ����Ч)
	*/
	void SetMaxNumber(int32_t maxNumber);

	/** ��ȡ������������
	*/
	int32_t GetMaxNumber() const;

	/** �����������С����(����IsNumberOnly()Ϊtrue��ʱ����Ч)
	*/
	void SetMinNumber(int32_t minNumber);

	/** ��ȡ�������С����
	*/
	int32_t GetMinNumber() const;

	/** ��ȡ��������������ı���ʾ��ʽ
	 * @return ���� true ʱ�����ڶ���ģʽ�����ݱ�������ʾ��false ���ʾ�ض���ʾ
	 */
    bool GetWordWrap();

	/** ���ó�������������ı���ʾ��ʽ
	 * @param[in] bWordWrap Ϊ true ʱ�����ڶ���ģʽ�����ݱ�������ʾ��false ���ʾ�ض���ʾ
	 */
    void SetWordWrap(bool bWordWrap = true);

	/** �Ƿ�Ϊ�����ı�
	*/
	bool GetMultiLine() const ;

	/** �����Ƿ�Ϊ�����ı�
	*/
	void SetMultiLine(bool bMultiLine);

	/** ��ȡ��ǰ���õ���������
	 * @return ����������������Ӧ global.xml �������˳��
	 */
	std::wstring GetFontId() const;

	/** ������������
	 * @param[in] index Ҫ���õ�������������Ӧ global.xml �������˳��
	 */
	void SetFontId(const std::wstring& strFontId);

	/** ���������ı���ɫ
	 * @param[in] dwTextColor Ҫ���õ��ı���ɫ������ɫ���� global.xml �д���
	 */
	void SetTextColor(const std::wstring& dwTextColor);

	/** ��ȡ�����ı���ɫ
	 */
	std::wstring GetTextColor() const;

	/** ����Disabled״̬���ı���ɫ
	 * @param[in] dwTextColor Ҫ���õ��ı���ɫ������ɫ���� global.xml �д���
	 */
	void SetDisabledTextColor(const std::wstring& dwTextColor);

	/** ��ȡDisabled״̬���ı���ɫ
	 */
	std::wstring GetDisabledTextColor() const;

	/** ��ȡ�����ַ�����
	 * @return ���������ַ�����
	 */
    int32_t GetLimitText() const;

	/** ���������ַ�����
	 * @param [in] iChars Ҫ���Ƶ��ַ�����
	 */
    void SetLimitText(int32_t iChars);

	/** ��ȡ����������Щ�ַ�
	*/
	std::wstring GetLimitChars() const;

	/** ��������������Щ�ַ���������ɫֵ�������ã�limit_chars="#0123456789ABCDEFabcdef"
	* @param [in] limitChars ����������ַ��б�
	*/
	void SetLimitChars(const std::wstring& limitChars);

	/** �Ƿ�������Beep����
	*/
	bool GetAllowBeep() const;

	/** �����Ƿ�������Beep����
	*/
	void SetAllowBeep(bool bAllowBeep);

	/** ��ȡ���ݵĳ���(Unicode���룬�ַ�����)
	 * @return �������ݳ���
	 */
    int32_t GetTextLength() const;

	/** ��ȡ�ؼ��е��ı�
	 * @return ���ؿؼ��е��ı�����
	 */
    std::wstring GetText() const;

	/** ��ȡ�ؼ��е��ı�
	 * @return ���ؿؼ��е��ı����� UTF8 ��ʽ
	 */
	virtual std::string GetUTF8Text() const;

	/** ���ÿؼ����ı�, �ᴥ���ı��仯�¼�
	 * @param [in] strText Ҫ���õ��ı�����
	 */
    void SetText(const std::wstring& strText);

	/** ���ÿؼ����ı����������ı��仯�¼�
	 * @param [in] strText Ҫ���õ��ı�����
	 */
	void SetTextNoEvent(const std::wstring& strText);

	/** ���ÿؼ����ı���Ӧ ID
	 * @param[in] strTextId Ҫ���õ� ID���� ID �����ڼ��ص������ļ��д���
	 */
	void SetTextId(const std::wstring& strTextId);

	/** ���ÿؼ����ı���Ӧ ID
	 * @param[in] strTextId Ҫ���õ� UTF8 ��ʽ ID���� ID �����ڼ��ص������ļ��д���
	 */
	virtual void SetUTF8Text(const std::string& strText);

	/** ��ȡ�޸ı�־
	 * @return ���� true Ϊ�������޸ı�־������Ϊ false
	 */
    bool GetModify() const;

	/** �����޸ı�־
	 * @param[in] bModified ����Ϊ true ��ʾ�ı��Ѿ����޸ģ�false Ϊδ�޸ģ�Ĭ��Ϊ true
	 */
    void SetModify(bool bModified = true);

	/** ��ȡ��ѡ�ı�����ʼλ�úͽ���λ��
	 * @param[out] cr ������ʼλ�úͽ���λ��
	 */
    void GetSel(CHARRANGE &cr) const;

	/** ��ȡ��ѡ�ı�����ʼλ�úͽ���λ��
	 * @param[in] nStartChar ������ʼλ��
	 * @param[in] nEndChar ���ؽ���λ��
	 */
    void GetSel(long& nStartChar, long& nEndChar) const;

	/** ѡ��һ��������
	 * @param[in] cr Ҫѡ���������ʼλ�úͽ���λ��
	 * @return ����ѡ�����������
	 */
    int SetSel(CHARRANGE &cr);

	/** ѡ��һ��������
	 * @param[in] nStartChar Ҫѡ�����ʼλ��
	 * @param[in] nEndChar Ҫѡ��Ľ���λ��
	 * @return ����ѡ�����������
	 */
    int SetSel(long nStartChar, long nEndChar);

	/** �滻��ѡ����
	 * @param[in] lpszNewText Ҫ�滻������
	 * @param[in] bCanUndo �Ƿ���Գ�����true Ϊ���ԣ�����Ϊ false
	 */
    void ReplaceSel(const std::wstring& lpszNewText, bool bCanUndo);

	/** ��ȡ��ѡ��������
	 * @return ������ѡ��������
	 */
    std::wstring GetSelText() const;

	/** ȫѡ
	 * @return ����ѡ�����������
	 */
    int SetSelAll();

	/** ��ѡ���κ�����
	 * @return ʼ�շ��� 0 
	 */
    int SetSelNone();

	/** ��ȡ�ؼ���ѡ������
	 * @return ���ؿؼ���ѡ�����ͣ��ο���https://docs.microsoft.com/en-us/windows/desktop/controls/em-selectiontype
		SEL_TEXT: Text.
		SEL_OBJECT: At least one COM object.
		SEL_MULTICHAR: More than one character of text.
		SEL_MULTIOBJECT: More than one COM object.
	 */
    WORD GetSelectionType() const;

	/** �����ı�
	*/
	LONG FindRichText(DWORD dwFlags, FINDTEXT& ft) const;

	/** �����ı�
	*/
	LONG FindRichText(DWORD dwFlags, FINDTEXTEX& ft) const;

	/** ��ȡ��ǰ���űȣ� �����ű�������/��ĸ��ʾ�����ţ�1/64 < (wParam / lParam) < 64
	 * @param[out] nNum ���ű��ʷ���
	 * @param[out] nDen ���ű��ʷ�ĸ
	 * @return �����������Ϣ�򷵻� TRUE
	 */
    bool GetZoom(int& nNum, int& nDen) const;

	/** �������ű�
	 * @param[in] nNum ���ű��ʷ��ӣ�ȡֵ��Χ��[0, 64]
	 * @param[in] nDen ���ű��ʷ�ĸ��ȡֵ��Χ��[0, 64]
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool SetZoom(int nNum, int nDen);

	/** �ָ����ŵ���ʼ״̬
	 * @return �ɹ����� true�����򷵻� false
	 */
    bool SetZoomOff();

	/** ��ȡ�Ƿ������Զ� URL ���(��RichEditHost��ȡ)
	 * @return ���� true ��ʾ�������Զ���⣬����Ϊ false
	 */
    bool GetAutoURLDetect() const;

	/** �����Ƿ��� URL �Զ����
	 * @param[in] bAutoDetect ����Ϊ true ��ʾ��� URL��false Ϊ����⣬Ĭ��Ϊ true
	 * @return ���� true Ϊ���óɹ���false Ϊʧ��
	 */
    bool SetAutoURLDetect(bool bAutoDetect = true);

	/** ��ȡ�ؼ����¼�����
	 * @return �����¼�����
	 */
    DWORD GetEventMask() const;

	/** ���ÿؼ����¼�����
	 * @param[in] dwEventMask Ҫ���õ��¼�����ֵ
	 * @return ��������֮ǰ���¼�����ֵ
	 */
    DWORD SetEventMask(DWORD dwEventMask);

	/** ��ȡָ����Χ������
	 * @param[in] nStartChar ��ʼλ��
	 * @param[in] nEndChar ����Ϊֹ
	 * @return �������õ�ָ��λ�õ�����
	 */
    std::wstring GetTextRange(long nStartChar, long nEndChar) const;

	/** �����Ƿ����ػ���ʾѡ���ֵ
	 * @param[in] bHide �Ƿ���ʾ��true Ϊ��ʾ��false Ϊ����ʾ
	 * @param[in] bChangeStyle �Ƿ��޸���ʽ��true Ϊ�޸ģ�false Ϊ���޸�
	 */
    void HideSelection(bool bHide = true, bool bChangeStyle = false);

	/** ���ù�굽�ɼ�λ��
	 */
    void ScrollCaret();

	/** ��������
	 * @param[in] nInsertAfterChar Ҫ�����λ��
	 * @param[in] lpstrText Ҫ������ı�
	 * @param[in] bCanUndo �Ƿ���Գ�����true Ϊ���ԣ�����Ϊ false��Ĭ��Ϊ false
	 * @return ���ز������ı�λ��
	 */
    int InsertText(long nInsertAfterChar, LPCTSTR lpstrText, bool bCanUndo = false);

	/** ׷������
	 * @param[in] strText Ҫ׷�ӵ�����
	 * @param[in] bCanUndo �Ƿ���Գ�����true Ϊ���ԣ�����Ϊ false��Ĭ��Ϊ false
	 * @return ����׷�Ӻ������λ��
	 */
    int AppendText(const std::wstring& strText, bool bCanUndo = false);

	/** ��ȡ�ַ���ʽ
	 * @param[out] cf ���ػ�ȡ���ַ���ʽ
	 * @return ���ز��� cf �� dwMask ��ֵ
	 */
    DWORD GetDefaultCharFormat(CHARFORMAT2 &cf) const;

	/** ����Ĭ�ϵ��ַ���ʽ
	 * @param[in] cf Ҫ�����ַ���ʽ
	 * @return ���� true ��ʾ�ɹ���false Ϊʧ��
	 */
    bool SetDefaultCharFormat(CHARFORMAT2 &cf);

	/** ��ȡ��ѡ����ַ���ʽ
	 * @param[out] cf ���ػ�ȡ���ַ���ʽ
	 * @return ���ز��� cf �� dwMask ��ֵ
	 */
    DWORD GetSelectionCharFormat(CHARFORMAT2 &cf) const;

	/** ���ñ�ѡ����ַ���ʽ
	 * @param[in] cf Ҫ���õ��ַ���ʽ
	 * @return ���� true ��ʾ�ɹ���false Ϊʧ��
	 */
    bool SetSelectionCharFormat(CHARFORMAT2 &cf);

	/** ���õ�ǰ�����ĵ��ʸ�ʽ
	 * @param[in] cf Ҫ���õĵ��ʸ�ʽ
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool SetWordCharFormat(CHARFORMAT2 &cf);

	/** ��ȡ��ǰ�����ʽ
	 * @param[out] pf ���ص�ǰ�����ʽ
	 * @return ���� pf ������ dwMask ��Ա
	 */
    DWORD GetParaFormat(PARAFORMAT2 &pf) const;

	/** ���õ�ǰ�����ʽ
	 * @param[in] pf Ҫ���õĶ����ʽ��ʽ
	 * @return �ɹ����� true�����򷵻� false
	 */
    bool SetParaFormat(PARAFORMAT2 &pf);

	/** �Ƿ����Redo
	*/
	bool CanRedo() const;

	/** ��������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool Redo();

	/** �Ƿ�ɳ���
	*/
	bool CanUndo() const;

	/** ��������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool Undo();

	/** ���
	 */
    void Clear();

	/** ������ѡ����
	 */
    void Copy();

	/** ������ѡ����
	 */
    void Cut();

	/** ճ��
	 */
	void Paste();

	/** ����Ƿ����ճ��ָ�����а��ʽ
	 * @param[in] nFormat Ҫ���ĸ�ʽ
	 * @return ���Է��� true�����򷵻� false
	 */
	BOOL CanPaste(UINT nFormat = 0);

	/** �ڿؼ���ճ���ض��ļ������ʽ
	 * @param[in] uClipFormat ָ�����а��ʽ
	 * @param[in] dwAspect ָ��չʾ��ʽ
	 * @param[in] hMF ��� dwAspect Ϊ DVASPECT_ICON���ú���Ӧ�ð���ͼ����
	 */
	void PasteSpecial(UINT uClipFormat, DWORD dwAspect = 0, HMETAFILE hMF = 0);

	/** ��ȡ������
	 * @return ����������
	 */
    int GetLineCount() const;

	/** ��ȡһ������
	 * @param[in] nIndex Ҫ��ȡ������
	 * @param[in] nMaxLength Ҫ��ȡ��ǰ���������ݳ���
	 * @return ���ػ�ȡ��һ������
	 */
    std::wstring GetLine(int nIndex, int nMaxLength) const;

	/** ��ȡָ���еĵ�һ���ַ�����
	 * @param[in] nLine Ҫ��ȡ�ڼ������ݣ�Ĭ��Ϊ -1
	 * @return ����ָ���еĵ�һ���ַ�����
	 */
    int LineIndex(int nLine = -1) const;

	/** ��ȡָ���е����ݳ���
	 * @param[in] nLine Ҫ��ȡ�ڼ������ݣ�Ĭ��Ϊ -1
	 * @return ����ָ���е����ݳ���
	 */
    int LineLength(int nLine = -1) const;

	/** �����ı�
	 * @param[in] nLines ָ����ֱ��������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool LineScroll(int nLines);

	/** ��ȡָ���ַ���������
	 * @param[in] nIndex �ַ�������λ��
	 * @return ���ص�ǰ�ַ����ڵ�����
	 */
    long LineFromChar(long nIndex) const;

	/** ��ȡָ��λ���ַ��Ŀͻ�������
	 * @param[in] nChar �ַ�����λ��
	 * @return ���ؿͻ�������
	 */
    UiPoint PosFromChar(long nChar) const;

	/** �������귵��ָ���ַ�����
	 * @param[in] pt ������Ϣ
	 * @return ������ӽ����� pt ��ָ��������λ��
	 */
	int CharFromPos(UiPoint pt) const;

	/** ��ճ����б�
	 */
    void EmptyUndoBuffer();

	/** ���ó����б����ɵ���������
	 * @param[in] nLimit
	 * @return �������ú�ĳ����б��������������
	 */
    UINT SetUndoLimit(UINT nLimit);

	/** ����һ���ص����ڿ�����������
	 * @param[in] nFormat ָ�����ݸ�ʽ���滻ѡ�����https://docs.microsoft.com/en-us/windows/desktop/controls/em-streamin
	 * @param[in] es �����Զ���ص��Ľṹ��
	 * @return ���ض��������������ݴ�С
	 */
    long StreamIn(UINT nFormat, EDITSTREAM &es);

	/** ָ��һ���ص����ڿ����������
	 * @param[in] nFormat ָ�����ݸ�ʽ���滻ѡ�����https://docs.microsoft.com/en-us/windows/desktop/controls/em-streamin
	 * @param[in] es �����Զ���ص��Ľṹ��
	 * @return ����д�������������ݴ�С
	 */
    long StreamOut(UINT nFormat, EDITSTREAM &es);

	/** ���ù�����λ��
	 * @param[in] szPos Ҫ���õĹ�����λ����Ϣ
	 */
    virtual void SetScrollPos(UiSize64 szPos) override;

	/** ����һ��
	 */
    void LineUp();

	/** ����һ��
	 */
    void LineDown();

	/** ���Ϸ�ҳ
	 */
    virtual void PageUp() override;

	/** ���·�ҳ
	 */
    virtual void PageDown() override;

	/** ���ص�����
	 */
    virtual void HomeUp() override;

	/** ���ص��ײ�
	 */
    void EndDown();

	/** ˮƽ�������
	 */
    void LineLeft();

	/** ˮƽ���ҹ���
	 */
    void LineRight();

	/** ˮƽ����ҳ
	 */
    virtual void PageLeft() override;

	/** ˮƽ���ҷ�ҳ
	 */
    virtual void PageRight() override;

	/** ���ص������
	 */
    virtual void HomeLeft() override;

	/** ���ص�����
	 */
    virtual void EndRight() override;

	/** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;
	
	/** ���ÿؼ�����״̬
	 * @param[in] bEnable Ϊ true ʱ�ؼ����ã�Ϊ false ʱ�ؼ�Ϊ����״̬�򲻿���
	 */
	virtual void SetEnabled(bool bEnable = true) override;
	
	/** ��������
	*/
	virtual void SetAttribute(const std::wstring& pstrName, const std::wstring& pstrValue) override;

	/** ���ù�������
	*/
	virtual void SetWindow(Window* pManager) override;

	/** ���ÿؼ�λ�ã�����ɸı���Ϊ��
	 * @param [in] rc Ҫ���õľ���������Ϣ�������ڱ߾࣬��������߾�
	 */
	virtual void SetPos(UiRect rc) override;

	/** ����ؼ���С(��͸�)
		���������ͼƬ������ width �� height ����һ��Ϊ auto��������ͼƬ��С���ı���С���������մ�С
	 *  @param [in] szAvailable ���ô�С����������߾�
	 *  @return �ؼ��Ĺ����С�������ڱ߾�(Box)����������߾�
	 */
	virtual UiEstSize EstimateSize(UiSize szAvailable) override;

	/** �����ı������С����͸ߣ�
	 *  @param [in] szAvailable ���ô�С���������ڱ߾࣬��������߾�
	 *  @return �ؼ����ı������С�������ڱ߾�(Box)����������߾�
	 */
	virtual UiSize EstimateText(UiSize szAvailable);

	/** �������
	 * @param[in] xWidth �����
	 * @param[in] yHeight ���߶�
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	BOOL CreateCaret(INT xWidth, INT yHeight);

	/** �����Ƿ���ʾ���
	 * @param[in] fShow ���� true Ϊ��ʾ��false Ϊ����ʾ
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	BOOL ShowCaret(BOOL fShow);

	/** ���ù����ɫ
	 * @param[in] dwColor Ҫ���õ���ɫֵ����ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetCaretColor(const std::wstring& dwColor);

	/** ��ȡ�����ɫ
	 * @return ���ع����ɫ
	 */
	std::wstring GetCaretColor();

	/** ��ȡ������λ��
	 * @return ���ع�����λ��
	 */
	RECT GetCaretRect();

	/** ���ù��λ��
	 * @param[in] x X ������
	 * @param[in] y Y ������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	BOOL SetCaretPos(INT x, INT y);

	/** �л�����Ƿ���ʾ
	 */
	void ChangeCaretVisiable();

	/** ���ƹ��
	 * @param[in] pRender ��������
	 * @param[in] rcPaint ����λ��
	 */
	void PaintCaret(IRender* pRender, const UiRect& rcPaint);

	/** �����Ƿ���ʾ��ʾ����
	 * @param[in] bPrompt ����Ϊ true Ϊ��ʾ��false Ϊ����ʾ
	 */
	void SetPromptMode(bool bPrompt);

	/** ��ȡ��ʾ����
	 */
	std::wstring GetPromptText() const;

	/** ��ȡ��ʾ����
	 * @return ���� UTF8 ��ʽ����ʾ����
	 */
	std::string GetUTF8PromptText() const;

	/** ������ʾ����
	 * @param[in] strText Ҫ���õ���ʾ����
	 */
	void SetPromptText(const std::wstring& strText);

	/** ������ʾ����
	 * @param[in] strText Ҫ���õ� UTF8 ��ʽ��ʾ����
	 */
	void SetUTF8PromptText(const std::string& strText);

	/** ������ʾ���� ID
	 * @param[in] strText Ҫ���õ���ʾ���� ID���� ID �����ڼ��ص������ļ��д���
	 */
	void SetPromptTextId(const std::wstring& strTextId);

	/** ������ʾ���� ID
	 * @param[in] strText Ҫ���õ� UTF8 ��ʽ��ʾ���� ID���� ID �����ڼ��ص������ļ��д���
	 */
	void SetUTF8PromptTextId(const std::string& strTextId);

	/** ������ʾ����
	 * @param[in] pRender ��������
	 */
	void PaintPromptText(IRender* pRender);

	/** ��ȡ����״̬�µ�ͼƬ
	 * @return ���ؽ���״̬�µ�ͼƬ
	 */
	std::wstring GetFocusedImage();

	/** ���ý���״̬�µ�ͼƬ
	 * @param[in] strImage Ҫ���õ�ͼƬλ��
	 */
	void SetFocusedImage(const std::wstring& strImage);

	/** ����ָ��״̬�µ�ͼƬ
	 * @param[in] pRender ��������
	 */
	virtual void PaintStateImages(IRender* pRender) override;

	/** ����ʧȥ������Ƿ�ȡ��ѡ����
	 * @param[in] bOnSel ����Ϊ true ��ʾȡ��ѡ���false Ϊ��ȡ��
	 */
	void SetNoSelOnKillFocus(bool bOnSel);

	/** ���û�ȡ������Ƿ�ѡ����������
	 * @param[in] bSelAll ���� true ��ʾ�ڻ�ȡ����ʱѡ���������ݣ�false Ϊ��ѡ��
	 */
	void SetSelAllOnFocus(bool bSelAll);

	/** ����ֻ��ģʽ����ʾ���
	 */
	void SetNoCaretReadonly();

	/** �����Ƿ񱣴���ѡ���ݵı߽�
	 */
	void SetSaveSelection(bool fSaveSelection);

	/** �����Ƿ�����ѡ����
	 */
	void SetHideSelection(bool fHideSelection);

	/** ��Ӵ���ɫ���ı�
	 * @param[in] str �ı�����
	 * @param[in] color ��ɫֵ����ֵ������ global.xml �д���
	 */
	void AddColorText(const std::wstring &str, const std::wstring &color);

	/** ���һ������������ɫ�ĳ�����
	 * @param[in] str ��������
	 * @param[in] color ������ɫ
	 * @param[in] linkInfo ���ӵ�ַ
	 */
	void AddLinkColorText(const std::wstring &str, const std::wstring &color, const std::wstring &linkInfo = L"");

	/** ���һ��ָ���������������ɫ�ĳ�����
	 * @param[in] str ��������
	 * @param[in] color ������ɫ
	 * @param[in] linkInfo ���ӵ�ַ
	 * @param[in] font ��������
	 */
	void AddLinkColorTextEx(const std::wstring& str, const std::wstring &color, const std::wstring &linkInfo = L"", const std::wstring& strFontId = L"");

	/** ���һ����Χ���� hittest �ж��Ƿ���������Ϣ
	 * @param[in] cr ��Χ����ʼλ�úͽ���λ��
	 * @param[in] linkInfo �Զ��� link ����
	 */
	void AddLinkInfo(const CHARRANGE cr, const std::wstring &linkInfo);

	/** ���һ����Χ���� hittest �ж��Ƿ���������Ϣ,�����÷�Χ��������ʽ��Ϊϵͳ������ʽ
	 * @param[in] str ��������
	 * @param[in] cr ��Χ����ʼλ�úͽ���λ��
	 * @param[in] linkInfo �Զ��� link ����
	 */
	void AddLinkInfoEx(const CHARRANGE cr, const std::wstring& linkInfo);

	/** ����point��hittest�Զ���link������
	 * @param[in] pt λ����Ϣ
	 * @param[in] info ��ʾ link ���Զ�������
	 * @return ���� true ��ʾ�� link ��
	 */
	bool HittestCustomLink(UiPoint pt, std::wstring& info);

	/** ����ͼƬ����
	 */
	virtual void ClearImageCache() override;

	/** ���������ڱ߾���Ϣ
	 * @param[in] padding �ڱ߾���Ϣ
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 */
	void SetTextPadding(UiPadding padding, bool bNeedDpiScale = true);

	/** ��ȡ�����ڱ߾�
	 */
	UiPadding GetTextPadding() const;

	/** �����Ƿ�ʹ��Control�Ĺ��
	*/
	void SetUseControlCursor(bool bUseControlCursor);

	/** �����Ƿ�����ͨ��Ctrl + �������������ű���
	*/
	void SetEnableWheelZoom(bool bEnable);

	/** ��ȡ�Ƿ�����ͨ��Ctrl + �������������ű���
	*/
	bool IsEnableWheelZoom(void) const;

	/** �Ƿ�����ʹ��Ĭ�ϵ��Ҽ��˵�
	*/
	void SetEnableDefaultContextMenu(bool bEnable);

	/** �Ƿ�����ʹ��Ĭ�ϵ��Ҽ��˵�
	*/
	bool IsEnableDefaultContextMenu() const;

	/** �����Ƿ������ϷŹ���
	*/
	void SetEnableDragDrop(bool bEnable);

	/** �ж��Ƿ��Ѿ������ϷŹ���
	*/
	bool IsEnableDragDrop() const;

	/** �����Ƿ�֧��Spin�ؼ�
	* @param [in] bEnable true��ʾ֧��Spin�ؼ���false��ʾ��֧��Spin�ؼ�
	* @param [in] spinClass Spin�ؼ���Class���ԣ��ַ�����Ҫ����3��ֵ���������òμ���global.xml�����rich_edit_spin����
	*             ȡֵ������rich_edit_spin_box,rich_edit_spin_btn_up,rich_edit_spin_btn_down
	* @param [in] nMin ��ʾ�������ֵ���Сֵ
	* @param [in] nMax ��ʾ�������ֵ����ֵ����� nMin��nMaxͬʱΪ0, ��ʾ���������ֵ���Сֵ�����ֵ
	*/
	bool SetEnableSpin(bool bEnable, const std::wstring& spinClass, int32_t nMin = 0, int32_t nMax = 0);

public:
	/** �����س����������¼�
	 * @param[in] callback �س������µ��Զ���ص�����
	 */
	void AttachReturn(const EventCallback& callback) { AttachEvent(kEventReturn, callback); }

	/** ���� TAB ���������¼�
	 * @param[in] callback TAB �����µ��Զ���ص�����
	 */
	void AttachTab(const EventCallback& callback) { AttachEvent(kEventTab, callback); }

	/* �������ű����仯�¼�
	 * @param[in] callback �ı����޸ĺ���Զ���ص�����
	 */
	void AttachZoom(const EventCallback& callback) { AttachEvent(kEventZoom, callback); }

	/* �����ı����޸��¼�
	 * @param[in] callback �ı����޸ĺ���Զ���ص�����
	 */
	void AttachTextChange(const EventCallback& callback) { AttachEvent(kEventTextChange, callback); }

	/* �����ı�ѡ��仯�¼�
	 * @param[in] callback �ı�ѡ��仯����Զ���ص�����
	 */
	void AttachSelChange(const EventCallback& callback);

	/** �����������ӱ�����¼�
	 * @param[in] callback �������ӱ������Ļص�����
	 */
	void AttachLinkClick(const EventCallback& callback)	{ AttachEvent(kEventLinkClick, callback); }

	/** ������С�仯�¼�
	 * @param[in] callback ��С���ı����Զ���ص�����
	 */
	void AttachGetNaturalSize(const FunGetNaturalSize& callback) { m_cbGetNaturalSize = callback; };

public:

	virtual void HandleEvent(const EventArgs& msg) override;

public:

	void OnTxNotify(DWORD iNotify, void* pv);

	HWND GetWindowHandle();
	HDC GetWindowDC();
	UiSize GetNaturalSize(LONG width, LONG height);
	void SetImmStatus(BOOL bOpen);
	void SetTimer(UINT idTimer, UINT uTimeout);
	void KillTimer(UINT idTimer);

	/** ��Ļ����ת��Ϊ�ͻ�������
	*/
	virtual bool ScreenToClient(UiPoint& pt) override;

	/** �ͻ�������ת��Ϊ��Ļ����
	*/
	virtual bool ClientToScreen(UiPoint& pt) override;

protected:

	//һЩ������麯��
	virtual bool CanPlaceCaptionBar() const override;
	virtual void OnInit() override;
	virtual uint32_t GetControlFlags() const override;

	//��Ϣ������
	virtual bool OnSetCursor(const EventArgs& msg) override;
	virtual bool OnSetFocus(const EventArgs& msg) override;
	virtual bool OnKillFocus(const EventArgs& msg) override;
	virtual bool OnChar(const EventArgs& msg) override;
	virtual bool OnKeyDown(const EventArgs& msg) override;
	virtual bool OnImeStartComposition(const EventArgs& msg) override;
	virtual bool OnImeEndComposition(const EventArgs& msg) override;

	void OnMouseMessage(UINT uMsg, const EventArgs& msg);

	virtual void Paint(IRender* pRender, const UiRect& rcPaint) override;
	virtual void PaintChild(IRender* pRender, const UiRect& rcPaint) override;

	/** �����ڲ������ӿؼ���λ����Ϣ
	 * @param[in] items �ؼ��б�
	 */
	virtual void ArrangeChild(const std::vector<Control*>& items) const;

private:
	/** ��ʾRichEdit�ϵĲ˵�
	* @param [in] point �ͻ���������
	*/
	void ShowPopupMenu(const ui::UiPoint& point);

	/** ע���ϷŽӿ��봰�ڵĹ�����ϵ
	*/
	void RegisterDragDrop();

	/** ע���ϷŽӿ��봰�ڵĹ�����ϵ
	*/
	void UnregisterDragDrop();

	/** �ж�һ���ַ����Ƿ��������ַ��б���
	*/
	bool IsInLimitChars(wchar_t charValue) const;

	/** �ж��Ƿ���Խ���ճ������(�ж��Ƿ����ַ����ơ���������)
	* @return �������true, ��ʾ�����ý���ճ������
	*/
	bool IsPasteLimited() const;

private:
	/** �����ı��仯�¼�
	*/
	void OnTextChanged();

	/** ����Spin���ܵ�Class����
	*/
	bool SetSpinClass(const std::wstring& spinClass);

	/** ��ȡ�ı����ݣ���ת��Ϊ����
	*/
	int64_t GetTextNumber() const;

	/** ������ת��Ϊ�ı��������ı�����
	*/
	void SetTextNumber(int64_t nValue);

	/** �����ı�����ֵ
	*/
	void AdjustTextNumber(int32_t nDelta);

	/** ��ʼ���������ı�����ֵ�Ķ�ʱ��
	*/
	void StartAutoAdjustTextNumberTimer(int32_t nDelta);

	/** ��ʼ�Զ������ı�����ֵ
	*/
	void StartAutoAdjustTextNumber(int32_t nDelta);

	/** �����Զ������ı�����ֵ
	*/
	void StopAutoAdjustTextNumber();

private:
	/** ���������ť���ܵ�Class����
	*/
	void SetClearBtnClass(const std::wstring& btnClass);

	/** ������ʾ���밴ť���ܵ�Class����
	*/
	void SetShowPasswordBtnClass(const std::wstring& btnClass);

private:
	//�ж��Ƿ����ֽڣ� �ɴ�ӡ�ַ���0x20-0x7e��
	static bool IsAsciiChar(const wchar_t ch);

	//��ȡ�ַ������ֽ���
	static int GetAsciiCharNumber(const std::wstring& str);

	//ɾ���ַ����г���limit�ֽڸ���֮����ַ�
	static void LimitAsciiNumber(std::wstring& src, int limit);

	//��ȡճ�����ַ���
	static void GetClipboardText(std::wstring& out);

	//����ճ�����ַ���
	static void SetClipBoardText(const std::wstring& str);

protected:
	//RichEdit���Ƹ���������
	RichEditCtrl m_richCtrl;

	//RichEdit Host��
	RichEditHost* m_pRichHost;

    bool m_bVScrollBarFixing; //������������־
    bool m_bWantTab;		  //�Ƿ����TAB�������Ϊtrue��ʱ��TAB���ᵱ���ı����룬������˵�TAB��
    bool m_bNeedReturnMsg;    //�Ƿ���ջس��������Ϊtrue��ʱ�򣬻س����ᵱ���ı����룬������˵��س���
    bool m_bReturnMsgWantCtrl;//�Ƿ����Ctrl + �س��������Ϊtrue��ʱ�򣬻س����ᵱ���ı����룬������˵��س���
	 
	bool m_bSelAllEver;			//ֻ�ڻ�ȡ�����ĵ�һ����굯��ȫѡ

	bool m_bNoSelOnKillFocus;	//ʧȥ�����ʱ��ȡ���ı�ѡ����� m_bEnabled && IsReadOnly()��
	bool m_bSelAllOnFocus;		//��ȡ�����ʱ��ȫѡ�ı������ m_bEnabled && !IsReadOnly()��

	bool m_bIsComposition;   //���뷨�ϳɴ����Ƿ�ɼ�
	
	/** ��С���ı����Զ���ص�����
	*/
	FunGetNaturalSize m_cbGetNaturalSize;

protected:
	struct LinkInfo
	{
		CHARRANGE cr;
		UiString info;
	};
	std::map<UINT, nbase::WeakCallbackFlag> m_timeFlagMap;
	std::vector<LinkInfo> m_linkInfo;

private:
	bool m_bNoCaretReadonly;	 //ֻ��ģʽ�£�����ʾ���
	bool m_bIsCaretVisiable;	 //����Ƿ�ɼ�
	int32_t	 m_iCaretPosX;		 //���X����
	int32_t  m_iCaretPosY;		 //���Y����
	int32_t  m_iCaretWidth;		 //�����
	int32_t  m_iCaretHeight;	 //���߶�
	UiString m_sCaretColor;		 //�����ɫ

	nbase::WeakCallbackFlag m_drawCaretFlag; //���ƹ��Ķ�ʱ����������

private:
	UiString m_sFontId;				 //����ID
	UiString m_sTextColor;			 //�����ı���ɫ
	UiString m_sDisabledTextColor;	 //Disabled״̬���ı���ɫ

	bool m_bAllowPrompt;			 //�Ƿ�֧����ʾ����
	UiString m_sPromptColor;		 //��ʾ������ɫ
	UiString m_sPromptText;			 //��ʾ�ı����ݣ�ֻ�б༭��Ϊ�յ�ʱ����ʾ��
	UiString m_sPromptTextId;		 //��ʾ����ID

private:
	/** ��ȡ����ʱ����ʾ��ͼƬ
	*/
	Image* m_pFocusedImage;

	/** �ı��ڱ߾�
	*/
	UiPadding16	m_rcTextPadding;

	/** �Ƿ�ʹ��Control���õĹ��
	*/
	bool m_bUseControlCursor;

	/** �Ƿ�����ͨ��Ctrl + �������������ű���
	*/
	bool m_bEnableWheelZoom;

	/** �Ƿ�����ʹ��Ĭ�ϵ��Ҽ��˵�
	*/
	bool m_bEnableDefaultContextMenu;

	/** �ϷŹ��ܵ�ʵ�ֽӿ�, �����Ϊ�ձ�ʾ�����Ѿ�����
	*/
	ControlDropTarget* m_pControlDropTarget;

	/** ����������ַ��б�
	*/
	UiString m_limitChars;

	/** �Ƿ��ֹ�����ı��仯�¼�
	*/
	bool m_bDisableTextChangeEvent;

	/** ����������������(����IsNumberOnly()Ϊtrue��ʱ����Ч)
	*/
	int32_t m_maxNumber;

	/** �����������С����(����IsNumberOnly()Ϊtrue��ʱ����Ч)
	*/
	int32_t m_minNumber;

	/** Spin���ܵ�����
	*/
	VBox* m_pSpinBox;

    /** �Զ������ı�����ֵ�Ķ�ʱ���������ڹ���
	*/
	nbase::WeakCallbackFlag m_flagAdjustTextNumber;

	/** ������ܵİ�ť(������ֻ��ģʽ��Ч)
	*/
	Control* m_pClearButton;

	/** ��ʾ/�������밴ť(��������ģʽ��Ч)
	*/
	Control* m_pShowPasswordButton;
};

} // namespace ui

#endif // UI_CONTROL_RICHEDIT_H_
