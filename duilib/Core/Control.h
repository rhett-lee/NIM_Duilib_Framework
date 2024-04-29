#ifndef UI_CORE_CONTROL_H_
#define UI_CORE_CONTROL_H_

#pragma once

#include "duilib/Core/PlaceHolder.h"
#include "duilib/Core/BoxShadow.h"
#include "duilib/Utils/Delegate.h"
#include <map>
#include <memory>

namespace ui 
{
	class Control;
	class ControlLoading;
	class Image;
	class IMatrix;
	class StateColorMap;
	class StateImageMap;
	class AnimationManager;
	class IRender;
	class IPath;

	typedef Control* (CALLBACK* FINDCONTROLPROC)(Control*, LPVOID);

class UILIB_API Control : 
	public PlaceHolder
{
public:
	Control();
	Control(const Control& r) = delete;
	Control& operator=(const Control& r) = delete;
    virtual ~Control();

    /** ��ȡ�ؼ�����
	*/
	virtual std::wstring GetType() const override;

    /// ͼ�����
	/**@brief ��ȡ������ɫ
	 * @return ���ر�����ɫ���ַ�������ֵ�� global.xml �ж���
	 */
	std::wstring GetBkColor() const { return m_strBkColor.c_str(); }

	/** ���ñ�����ɫ
	 * @param [in] strColor Ҫ���õı�����ɫֵ����ֵ������ global.xml �д���
	 */
	void SetBkColor(const std::wstring& strColor);

	/** ���ñ�����ɫ
	 * @param [in] color Ҫ���õı�����ɫֵ
	 */
	void SetBkColor(const UiColor& color);

	/**
	 * @brief ��ȡĳ��״̬�µĿؼ���ɫ
	 * @param[in] stateType Ҫ��ȡ����״̬�µ���ɫֵ���ο� ControlStateType ö��
	 * @return ָ��״̬���趨����ɫ�ַ�������Ӧ global.xml ��ָ��ɫֵ
	 */
	std::wstring GetStateColor(ControlStateType stateType) const;

	/**
	 * @brief ����ĳ��״̬�µĿؼ���ɫ
	 * @param[in] stateType Ҫ���ú���״̬�µ���ɫֵ���ο� ControlStateType ö��
	 * @param[in] strColor Ҫ���õ���ɫֵ����ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetStateColor(ControlStateType stateType, const std::wstring& strColor);

	/**
	 * @brief ��ȡ����ͼƬλ��
	 * @return ����ͼƬλ��  
	 */
    std::wstring GetBkImage() const;

	/**
	 * @brief ��ȡ UTF8 ��ʽ�ı���ͼƬλ��
	 * @return ����ͼƬλ��
	 */
	std::string GetUTF8BkImage() const;

	/**
	 * @brief ���ñ���ͼƬ
	 * @param[in] strImage Ҫ���õ�ͼƬ·��
	 * @return ��
	 */
	void SetBkImage(const std::wstring& strImage);

	/**
	 * @brief ���ñ���ͼƬ��UTF8 ��ʽ�ַ�����
	 * @param[in] strImage Ҫ���õ�ͼƬ·��
	 * @return ��
	 */
	void SetUTF8BkImage(const std::string& strImage);

public:
    /** ����loadingͼƬ
    * @param[in] strImage Ҫ���õ�ͼƬ·��������
    */
    void SetLoadingImage(const std::wstring& strImage);

    /** ����loading����ɫ
    * @param[in] strColor ����ɫ
    */
    void SetLoadingBkColor(const std::wstring& strColor);

	/** ����loading״̬
	* @param[in] start_angle loadingͼƬ��ת�ĽǶ�
	*/
	void StartLoading(int32_t fStartAngle = -1);

	/** �ر�loading״̬
	* @param[in] frame �������ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	*/
	void StopLoading(GifFrameType frame = kGifFrameFirst);

public:
	/**
	 * @brief ��ȡָ��״̬�µ�ͼƬλ��
	 * @param[in] Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @return ָ��״̬�µ�ͼƬλ��
	 */
	std::wstring GetStateImage(ControlStateType stateType) const;

	/**
	 * @brief ����ĳ��״̬�µ�ͼƬ
	 * @param[in] stateType Ҫ���ú���״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @param[in] strImage Ҫ���õ�ͼƬ·��
	 * @return ��
	 */
	void SetStateImage(ControlStateType stateType, const std::wstring& strImage);

	/**
	 * @brief ��ȡָ��״̬�µ�ǰ��ͼƬ
	 * @param[in] Ҫ��ȡ����״̬�µ�ͼƬ���ο� `ControlStateType` ö��
	 * @return ָ��״̬��ǰ��ͼƬλ��
	 */
	std::wstring GetForeStateImage(ControlStateType stateType) const;

	/**
	 * @brief ����ĳ��״̬��ǰ��ͼƬ
	 * @param[in] stateType Ҫ���ú���״̬�µ�ͼƬ���ο� `ControlStateType` ö��
	 * @param[in] strImage Ҫ���õ�ǰ��ͼƬ·��
	 * @return ��
	 */
	void SetForeStateImage(ControlStateType stateType, const std::wstring& strImage);

	/**@brief ��ȡ�ؼ�״̬
	 * @return �ؼ���״̬����ο� `ControlStateType` ö��
	 */
	ControlStateType GetState() const;

	/**@brief ���ÿؼ�״̬
	 * @param[in] controlState Ҫ���õĿؼ�״̬����ο� `ControlStateType` ö��
	 */
	void SetState(ControlStateType controlState);

	/** ��ǰ�Ƿ�ΪHot״̬(���״̬�£�ҵ���߼��϶�)
	*/
	bool IsHotState() const;

	/** ��ȡ���ڹ���ؼ���С����͸ߣ�ͼƬ�ӿ�
	 */
	virtual Image* GetEstimateImage();

	/// �߿����
	/** ��ȡָ��״̬�µı߿���ɫ
	 * @param [in] stateType �ؼ�״̬
	 * @return �߿����ɫ�ַ�������Ӧ global.xml �еľ�����ɫֵ
	 */
	virtual std::wstring GetBorderColor(ControlStateType stateType) const;

	/** ���ñ߿���ɫ��Ӧ��������״̬
	 * @param [in] strBorderColor ���ñ߿����ɫ�ַ���ֵ����ֵ������ global.xml �д���
	 */
	void SetBorderColor(const std::wstring& strBorderColor);

	/** ����ָ��״̬�µı߿���ɫ
	 * @param [in] stateType �ؼ�״̬
	 * @param [in] strBorderColor ���ñ߿����ɫ�ַ���ֵ����ֵ������ global.xml �д���
	 */
	void SetBorderColor(ControlStateType stateType, const std::wstring& strBorderColor);

	/** ���ý���״̬�µı߿���ɫ
	*/
	void SetFocusBorderColor(const std::wstring& strBorderColor);

	/** ��ȡ����״̬�µı߿���ɫ
	*/
	std::wstring GetFocusBorderColor() const;

	/** ���ñ߿�Ĵ�С(left��top��right��bottom�ֱ��Ӧ��߿��С���ϱ߿��С���ұ߿��С���±߿��С)
	 * @param [in] rc һ�� `UiRect` �ṹ�ı߿��С����
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetBorderSize(UiRect rc, bool bNeedDpiScale = true);

	/** ��ȡ���߿��С
	 * @return ���߿�Ĵ�С  
	 */
	int32_t GetLeftBorderSize() const;

	/** �������߿��С
	 * @param [in] nSize Ҫ���õ����߿��С
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetLeftBorderSize(int32_t nSize, bool bNeedDpiScale = true);

	/** ��ȡ�����߿��С
	 */
	int32_t GetTopBorderSize() const;

	/** ���ö����߿��С
	 * @param [in] nSize Ҫ���õ��Ϸ��߿��С
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetTopBorderSize(int32_t nSize, bool bNeedDpiScale = true);

	/** ��ȡ�Ҳ�߿��С
	 * @return �Ҳ�ı߿��С
	 */
	int32_t GetRightBorderSize() const;

	/** �����Ҳ�߿��С
	 * @param [in] nSize Ҫ���õ��Ҳ�߿��С
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetRightBorderSize(int32_t nSize, bool bNeedDpiScale = true);

	/** ��ȡ�·��߿��С
	 * @return �·��߿��С
	 */
	int32_t GetBottomBorderSize() const;

	/** �����·��߿��С
	 * @param [in] nSize Ҫ���õ��·��߿��С
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetBottomBorderSize(int32_t nSize, bool bNeedDpiScale = true);

	/** ��ȡԲ�Ǵ�С
	 */
	const UiSize& GetBorderRound() const;

	/** ���ñ߿��С
	 * @param [in] cxyRound һ�� UiSize �ṹ��ʾԲ�Ǵ�С
	 */
	void SetBorderRound(UiSize cxyRound);

	/** ���ñ߿���Ӱ
	 * @param[in] Ҫ���õ���Ӱ����
	 */
	void SetBoxShadow(const std::wstring& strShadow);

    /// ������
	/**
	 * @brief ��ȡ���ָ������
	 */
	virtual CursorType GetCursorType() const;

	/**@brief ���õ�ǰ���ָ������
	 * @param[in] cursorType Ҫ���õ�������ͣ��ο� CursorType ö��
	 */
	void SetCursorType(CursorType cursorType);

	/**
	 * @brief ��ȡ�ؼ����������״̬�µ���ʾ�ı�
	 * @return ���ص�ǰ�������״̬��ʾ���ı�
	 */
    virtual std::wstring GetToolTipText() const;

	/**
	 * @brief ��ȡ�ؼ����������״̬�µ���ʾ�ı���UTF8 ��ʽ��
	 * @return ���ص�ǰ�������״̬��ʾ���ı�
	 */
	virtual std::string GetUTF8ToolTipText() const;

	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı�
	 * @param[in] strText Ҫ���õ��ı�
	 * @return ��
	 */
	virtual void SetToolTipText(const std::wstring& strText);

	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı���UTF8 ��ʽ��
	 * @param[in] strText Ҫ���õ��ı�
	 * @return ��
	 */
	virtual void SetUTF8ToolTipText(const std::string& strText);

	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı��������ļ��ж�Ӧ������
	 * @param[in] strTextId �������ļ��ж�Ӧ����ʾ���� ID
	 * @return ��
	 */
	virtual void SetToolTipTextId(const std::wstring& strTextId);

	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı��������ļ��ж�Ӧ�����֣�UTF8 ��ʽ��
	 * @param[in] strTextId �������ļ��ж�Ӧ����ʾ���� ID
	 * @return ��
	 */
	virtual void SetUTF8ToolTipTextId(const std::string& strTextId);

	/**
	 * @brief ��������������ؼ�����ʾ���ı����������
	 * @param[in] nWidth Ҫ���õĿ��ֵ
	 * @return ��
	 */
	virtual void SetToolTipWidth(int32_t nWidth);

	/**
	 * @brief ��ȡ����������ؼ�����ʾ���ı����������
	 * @return ��ǰ��ʾ�ı������
	 */
	virtual int32_t GetToolTipWidth(void) const;

    /// �˵�
	/**
	 * @brief �ؼ��Ƿ���Ӧ�����Ĳ˵���Ϣ
	 * @return ���ؽ����ʾ���Ƿ���Ӧ�����Ĳ˵���Ϣ��true ��Ӧ�����Ĳ˵���Ϣ��false ����Ӧ�����Ĳ˵���Ϣ
	 */
	virtual bool IsContextMenuUsed() const { return m_bContextMenuUsed; };

	/**
	 * @brief ���ÿؼ���Ӧ�����Ĳ˵���Ϣ
	 * @param[in] bMenuUsed �Ƿ���Ӧ�����Ĳ˵���Ϣ��true Ϊ�ǣ�false Ϊ��
	 * @return ��
	 */
    virtual void SetContextMenuUsed(bool bMenuUsed);

    /// �û����ݣ��������������û�ʹ��

	/** ��ȡ�û��󶨵��ؼ��������ַ���
	 * @return ���ؾ��������ַ���
	 */
	std::wstring GetDataID() const;

	/** ��ȡ�û��󶨵��ؼ��������ַ�����UTF8 ��ʽ��
	 * @return ���ؾ��������ַ���
	 */
	std::string GetUTF8DataID() const;

	/** ��һ���ַ������ݵ��ؼ�
	 * @param[in] strText Ҫ�󶨵��ַ�������
	 */
	void SetDataID(const std::wstring& strText);

	/** ��һ���ַ������ݵ��ؼ���UTF8 ��ʽ��
	 * @param[in] strText Ҫ�󶨵��ַ�������
	 */
	void SetUTF8DataID(const std::string& strText);

	/** ��һ������ֵ���ݵ��ؼ�
	 * @param[in] dataID Ҫ�󶨵���������
	 */
	void SetUserDataID(size_t dataID);

	/** ��ȡ�ؼ��󶨵�����ֵ����
	*/
	size_t GetUserDataID() const;

    /// һЩ��Ҫ������
	/**
	 * @brief �Ե��뵭���ȶ�����ʽ���ÿؼ��Ƿ�ɼ�, ���õĽ����SetVisible��ͬ��ֻ�ǹ��̰����˶���Ч����
	          ����SetFadeVisible�Ժ󣬲���Ҫ�ٵ���SetVisible�����޸Ŀɼ����ԡ�
			  �ú����ڲ������SetVisible����麯����
	 * @param[in] bVisible Ϊ true ʱ�ؼ��ɼ���Ϊ false ʱ�ؼ�������
	 * @return ��
	 */
    virtual void SetFadeVisible(bool bVisible);

	/** ���ÿؼ��Ƿ�ɼ�
	 * @param[in] @param[in] bVisible Ϊ true ʱ�ؼ��ɼ���Ϊ false ʱ�ؼ�������
	 */
	virtual void SetVisible(bool bVisible) override;

	/**
	 * @brief ���ؼ��Ƿ����
	 * @return �ؼ�����״̬������ true �ؼ����ã�����Ϊ false
	 */
	virtual bool IsEnabled() const { return m_bEnabled; };

	/**
	 * @brief ���ÿؼ�����״̬
	 * @param[in] bEnable Ϊ true ʱ�ؼ����ã�Ϊ false ʱ�ؼ�Ϊ����״̬�򲻿���
	 * @return ��
	 */
    virtual void SetEnabled(bool bEnable = true);

	/**
	 * @brief ���ؼ��Ƿ���Ӧ����¼�
	 * @return ���ؿؼ��Ƿ���Ӧ����¼������� true ��Ӧ����¼���false Ϊ����Ӧ
	 */
	virtual bool IsMouseEnabled() const { return m_bMouseEnabled; };

	/**
	 * @brief ���ÿؼ��Ƿ���Ӧ����¼�
	 * @param[in] bEnable Ϊ true ��Ӧ����¼���Ϊ false ʱ����Ӧ����¼�
	 * @return ��
	 */
    virtual void SetMouseEnabled(bool bEnable);

	/**
	 * @brief ���ؼ��Ƿ���Ӧ�����¼�
	 * @return ���ؿؼ��Ƿ���Ӧ�����¼������� true ��Ӧ�����¼���false ����Ӧ�����¼�
	 */
	virtual bool IsKeyboardEnabled() const { return m_bKeyboardEnabled; };

	/**
	 * @brief ���ÿؼ��Ƿ���Ӧ�����¼�
	 * @param[in] bEnable Ϊ true ��Ӧ�����¼���Ϊ false ʱ����Ӧ�����¼�
	 * @return ��
	 */
    virtual void SetKeyboardEnabled(bool bEnable);

	/** ���ؼ��Ƿ���н���
	 * @return ���ؿؼ��Ƿ���м�㣬Ϊ true ʱ�ǵ�ǰ���н��㣬Ϊ false ʱ�ؼ�û�н���
	 */
    virtual bool IsFocused() const;

	/** �ÿؼ���ȡ����
	 */
    virtual void SetFocus();

	/** ���ؿؼ��ı�ʶ�������ж��Ƿ������Ӧ TAB �л��¼�
	 * @return ���ؿؼ��ı�ʶ����
	 */
	virtual uint32_t GetControlFlags() const;

	/** �ÿؼ�������Զ��ȡ��������
	 */
	void SetNoFocus(); // �ؼ���Զ��Ҫ���㣬��KillFocus��һ��

	/** �ÿؼ��Ƿ񲻻�ȡ����
	*/
	bool IsNoFocus() const { return m_bNoFocus; }

	/** �����Ƿ���ʾ����״̬(һ�����߹��ɵľ���)
	*/
	void SetShowFocusRect(bool bShowFocusRect);

	/** �����Ƿ���ʾ����״̬(һ�����߹��ɵľ���)
	*/
	bool IsShowFocusRect() const;

	/** ���ý���״̬���߾��ε���ɫ(��������ɫ)
	*/
	void SetFocusRectColor(const std::wstring& focusRectColor);

	/** ��ȡ����״̬���߾��ε���ɫ(��������ɫ)
	*/
	std::wstring GetFocusRectColor() const;

	/** �жϵ�ǰ��꽹���Ƿ��ڿؼ���
	 * @return ������꽹���Ƿ��ڿؼ��ϣ�true ��꽹���ڿؼ��ϣ�false ��꽹�㲻�ڿؼ���
	 */
	virtual bool IsMouseFocused() const { return m_bMouseFocused;}

	/**
	 * @brief �����Ƿ���꽹�㵽�ؼ���
	 * @param[in] bMouseFocused Ϊ true ʱ������꽹�㵽�ؼ��ϣ�Ϊ false ʱ�ÿؼ�ʧȥ��꽹��
	 * @return ��
	 */
	virtual void SetMouseFocused(bool bMouseFocused) { m_bMouseFocused = bMouseFocused; }

	/**
	 * @brief �жϿؼ���ǰ�Ƿ��ǿɼ���״̬
	 * @return ���ؿؼ�״̬��true �ؼ���ǰ�ǿɼ���״̬���ɼ������ã�false �ؼ���ǰ�ǿɼ���״̬�����ܲ��ɼ��򱻽���
	 */
	virtual bool IsActivatable() const;

	/**
	 * @brief ����ؼ���������ѡ�С�չ���Ȳ���
	 * @param[in] ������
	 * @return ������
	 */
	virtual void Activate();

	/** �����������ָ���ؼ�
	 * @param [in] Proc ���ҵ�ƥ�亯��
	 * @param [in] pProcData ���Һ������Զ�������
	 * @param [in] ptMouse ������ڵ�����, ��������UIFIND_HITTESTʱ��Ч
	 * @param [in] uFlags ���ұ�־�����磺UIFIND_ENABLED ��
	 * @param [in] scrollPos �������Ĺ���λ��
	 * @return ���ؿؼ���ָ��
	 */
    virtual Control* FindControl(FINDCONTROLPROC Proc, LPVOID pProcData, uint32_t uFlags,								 
								 const UiPoint& ptMouse = UiPoint(),
								 const UiPoint& scrollPos = UiPoint());

	/// λ�����
	/** ��ȡ�ؼ�λ�ã�����ɸı���Ϊ��
	* @return ���ؿؼ��ľ������򣬰����ڱ߾࣬��������߾�
	 */
	virtual	UiRect GetPos() const override;

	/** ���ÿؼ�λ�ã�����ɸı���Ϊ��
	 * @param [in] rc Ҫ���õľ���������Ϣ�������ڱ߾࣬��������߾�
	 */
	virtual void SetPos(UiRect rc) override;

	/** ����ؼ���С(��͸�)
	    ���������ͼƬ������ width �� height ����һ��Ϊ auto��������ͼƬ��С���ı���С���������մ�С
	 *  @param [in] szAvailable ���ô�С����������߾�
	 *  @return �ؼ��Ĺ����С�������ڱ߾�(Box)����������߾�
	 */
	virtual UiEstSize EstimateSize(UiSize szAvailable);

	/** �����ı������С����͸ߣ�
	 *  @param [in] szAvailable ���ô�С���������ڱ߾࣬��������߾�
	 *  @return �ؼ����ı������С�������ڱ߾�(Box)����������߾�
	 */
	virtual UiSize EstimateText(UiSize szAvailable);

	/**
	 * @brief ���ָ�������Ƿ��ڹ�������ǰ����λ�õķ�Χ��
	 * @param[in] point ��������
	 * @return �����Ƿ��ڷ�Χ�ڣ�true �ڹ�������ǰ����λ�÷�Χ�ڣ�false ���ڹ�������ǰ����λ�÷�Χ��
	 */
	virtual bool IsPointInWithScrollOffset(const UiPoint& point) const;

	// ��Ϣ����
	/** @brief �ؼ�ͳһ����Ϣ������ڣ�����ͳ Windows ��Ϣת��Ϊ�Զ����ʽ����Ϣ
	 * @param[in] eventType	��Ϣ����
	 * @param[in] wParam	��Ϣ��������
	 * @param[in] lParam	��Ϣ��������
	 * @param[in] tChar		������Ϣ
	 * @param[in] mousePos	�����Ϣ
	 */
	virtual void SendEvent(EventType eventType,
			        	   WPARAM wParam = 0, 
						   LPARAM lParam = 0, 
						   TCHAR tChar = 0, 
						   const UiPoint& mousePos = UiPoint());

	/** @brief ��ת�������Ϣ�ɷ�����Ϣ������
	 * @param[in] msg ��Ϣ����
	 */
    virtual void SendEvent(const EventArgs& msg);

	/**
	 * @brief �жϿؼ��Ƿ��� HOT ״̬
	 * @return ���� true �� HOT ״̬�� ����Ϊ false
	 */
	virtual bool HasHotState();

	// ��������
	/**
	 * @brief ���ÿؼ�ָ������
	 * @param[in] strName Ҫ���õ��������ƣ��� width��
	 * @param[in] strValue Ҫ���õ�����ֵ���� 100��
	 * @return ��
	 */
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue);

	/**
	 * @brief ���ÿؼ��� class ȫ������
	 * @param[in] strClass Ҫ���õ� class ���ƣ������Ʊ����� global.xml �д���
	 * @return ��
	 */
	void SetClass(const std::wstring& strClass);

	/**
	 * @brief Ӧ��һ�������б�
	 * @param[in] strList �����б���ַ�����ʾ���� `width="100" height="30"`
	 * @return ��
	 */
    void ApplyAttributeList(const std::wstring& strList);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	bool OnApplyAttributeList(const std::wstring& strReceiver, const std::wstring& strList, const EventArgs& eventArgs);

	/// ���Ʋ���
	/**
	 * @brief ����ͼƬ
	 * @param [in] pRender ����������
	 * @param [in] pImage ͼƬ����Ľӿ�
	 * @param [in] isLoadingImage true��ʾLoading Image������ʱ����ת��ͼƬ;false��ʾ����ͼƬ
	 * @param [in] strModify ͼƬ�ĸ�������
	 * @param [in] nFade �ؼ���͸���ȣ�������ö���Ч����ֵ�ڻ���ʱ�ǲ��ϱ仯��
	 * @param [in] pMatrix ����ͼƬʱʹ�õı任����
	 * @param [in] pInRect �ⲿ�����ͼƬ���Ƶ�Ŀ���������Ϊnullptr�����ڲ�ʹ��GetRect()���ص�����
	 * @param [out] pPaintedRect ����ͼƬ���Ƶ�����Ŀ���������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool PaintImage(IRender* pRender, Image* pImage,
				    const std::wstring& strModify = L"",
		            int32_t nFade = DUI_NOSET_VALUE,
		            IMatrix* pMatrix = nullptr,
		            UiRect* pInRect = nullptr,
		            UiRect* pPaintedRect = nullptr) const;

	/**
	* @brief ��ȡ���������Ķ���
	* @return ���ػ��������Ķ���
	*/
	IRender* GetRender();

	/**
	* @brief ������������Ķ���
	* @return ��
	*/
	void ClearRender();

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual void AlphaPaint(IRender* pRender, const UiRect& rcPaint);
	
	/**
	* @brief ���ƿؼ�����ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void Paint(IRender* pRender, const UiRect& rcPaint);

	/**
	* @brief ���ƿؼ�������ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void PaintChild(IRender* pRender, const UiRect& rcPaint) { (void)pRender; (void)rcPaint; };

	/**
	* @brief �����Ƿ�Ի��Ʒ�Χ����������
	* @param[in] clip ���� true Ϊ��Ҫ������Ϊ����Ҫ�������ƺ���
	* @return ��
	*/
	void SetClip(bool clip) { m_bClip = clip; };

	/**
	* @brief �ж��Ƿ�Ի��Ʒ�Χ����������
	* @return ���� true Ϊ��Ҫ��false Ϊ����Ҫ
	*/
	bool IsClip() const { return m_bClip; }

	/**
	 * @brief ���ÿؼ�͸����
	 * @param[in] alpha 0 ~ 255 ��͸����ֵ��255 Ϊ��͸��
	 * @return ��
	 */
	void SetAlpha(int64_t alpha);

	/**
	 * @brief ��ȡ�ؼ�͸����
	 * @return ���ؿؼ���͸����
	 */
	int32_t GetAlpha() const { return m_nAlpha;	}

	/**
	 * @brief ���ؼ��Ƿ���͸������
	 * @return ���ؿؼ��Ƿ�͸����true �ؼ���ǰ��͸�����ԣ�false �ؼ�û��͸������
	 */
	bool IsAlpha() const { return m_nAlpha != 255; }

	/**
	 * @brief ���ý���״̬͸����
	 * @param[in] alpha 0 ~ 255 ��͸����ֵ��255 Ϊ��͸��
	 * @return ��
	 */
	void SetHotAlpha(int64_t nHotAlpha);

	/**
	 * @brief �����Ƿ����TAB���л�����
	 * @param[in] enable
	 * @return ��
	 */
	void SetTabStop(bool enable);

	/**
	 * @brief ����Ƿ����TAB���л�����
	 * @return ���ؿؼ��Ƿ����TAB���л�����
	 */
	bool IsAllowTabStop() const { return m_bAllowTabstop; }

	/**
	 * @brief ��ȡ����״̬͸����
	 * @return ���ؿؼ�����״̬��͸����
	 */
	int32_t GetHotAlpha() const { return m_nHotAlpha; }

	/**
	 * @brief ��ȡ�ؼ�����ƫ����
	 * @return ���ص�ǰ�ؼ��Ļ���ƫ����
	 */
	UiPoint GetRenderOffset() const { return m_renderOffset;	}

	/**
	 * @brief ���ÿؼ�����ƫ����
	 * @param[in] renderOffset �ؼ�ƫ������
	 * @return ��
	 */
	void SetRenderOffset(UiPoint renderOffset);

	/**
	 * @brief ���ÿؼ�ƫ�Ƶ� X ����
	 * @param[in] renderOffsetX X ����ֵ
	 * @return ��
	 */
	void SetRenderOffsetX(int64_t renderOffsetX);

	/**
	 * @brief ���ÿؼ�ƫ�Ƶ� Y ����
	 * @param[in] renderOffsetY Y ����ֵ
	 * @return ��
	 */
	void SetRenderOffsetY(int64_t renderOffsetY);

	/// ����ͼƬ
	/** ���� GIF/WebP/APNG ����
	 * @param [in] nStartFrame ����һ֡��ʼ���ţ������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	 * @param [in] nPlayCount ָ�����Ŵ���, �����-1��ʾһֱ����
	 */
	bool StartGifPlay(GifFrameType nStartFrame = kGifFrameFirst, int32_t nPlayCount = -1);

	/** ֹͣ���� GIF/WebP/APNG ����
	 * @param [in] bTriggerEvent �Ƿ�ֹͣ�¼�֪ͨ�������ߣ��ο� AttachGifPlayStop ����
	 * @param [in] nStopFrame ���Ž���ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	 */
	void StopGifPlay(bool bTriggerEvent = false, GifFrameType nStopFrame = kGifFrameCurrent);

	/** ���� GIF �������֪ͨ
	 * @param[in] callback Ҫ���� GIF ֹͣ���ŵĻص�����
	 */
	void AttachGifPlayStop(const EventCallback& callback);

	/** @brief ��ȡ�����������ӿ�
	 */
	AnimationManager& GetAnimationManager();

	/// ͼƬ����
	/**@brief ����ͼƬ·��, ����ͼƬ��Ϣ�������С�
	 *        ���ز��ԣ����ͼƬû�м�����ִ�м���ͼƬ�����ͼƬ·�������仯�������¼��ظ�ͼƬ��
	 * @param[in��out] duiImage ����ʱ��עͼƬ��·����Ϣ������ɹ���Ỻ��ͼƬ����¼���ò����ĳ�Ա��
	 */
	bool LoadImageData(Image& duiImage) const;

	/**@brief ����ͼƬ����
	 */
	virtual void ClearImageCache();

	/** ��Ļ����ת��Ϊ�ͻ�������
	*/
	virtual bool ScreenToClient(UiPoint& pt);

	/** �ͻ�������ת��Ϊ��Ļ����
	*/
	virtual bool ClientToScreen(UiPoint& pt);

public:
	/** �����ؼ������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachAllEvents(const EventCallback& callback)	{ AttachEvent(kEventAll, callback); }

	/** �����������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachMouseEnter(const EventCallback& callback) { AttachEvent(kEventMouseEnter, callback); }

	/** ��������뿪�¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachMouseLeave(const EventCallback& callback) { AttachEvent(kEventMouseLeave, callback); }

	/** ������������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachMouseHover(const EventCallback& callback) { AttachEvent(kEventMouseHover, callback); }

	/** ��������ƶ��¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachMouseMove(const EventCallback& callback) { AttachEvent(kEventMouseMove, callback); }

	/** ������갴���¼�(���)
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachButtonDown(const EventCallback& callback) { AttachEvent(kEventMouseButtonDown, callback); }

	/** ������굯���¼�(���)
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachButtonUp(const EventCallback& callback) { AttachEvent(kEventMouseButtonUp, callback); }

	/** ������갴���¼�(�Ҽ�)
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachRButtonDown(const EventCallback& callback) { AttachEvent(kEventMouseRButtonDown, callback); }

	/** ������굯���¼�(�Ҽ�)
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachRButtonUp(const EventCallback& callback) { AttachEvent(kEventMouseRButtonUp, callback); }

	/** ������ý����¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachSetFocus(const EventCallback& callback) { AttachEvent(kEventSetFocus, callback); }

	/** ����ʧȥ�����¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachKillFocus(const EventCallback& callback) { AttachEvent(kEventKillFocus, callback); }

	/** ��������ʧȥ�����¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachWindowKillFocus(const EventCallback& callback) { AttachEvent(kEventWindowKillFocus, callback); }

	/** �����Ҽ��˵��¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachMenu(const EventCallback& callback) { AttachEvent(kEventMouseMenu, callback); }

	/** �����ؼ���С�ı��¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachResize(const EventCallback& callback) { AttachEvent(kEventResize, callback); }

	/** ����˫���¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachDoubleClick(const EventCallback& callback) { AttachEvent(kEventMouseDoubleClick, callback); }

	/** �������������
	* @param[in] callback Ҫ�󶨵Ļص�����
	*/
	void AttachClick(const EventCallback& callback) { AttachEvent(kEventClick, callback); }

	/** ������Ҽ����������
	* @param[in] callback Ҫ�󶨵Ļص�����
	*/
	void AttachRClick(const EventCallback& callback) { AttachEvent(kEventRClick, callback); }

	/** �����ؼ���ʾ�������¼�
	* @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	*/
	void AttachVisibleChange(const EventCallback& callback) { AttachEvent(kEventVisibleChange, callback); }

	/** �����ؼ�״̬�仯�¼�
	* @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	*/
	void AttachStateChange(const EventCallback& callback) { AttachEvent(kEventStateChange, callback); }

	/** �����ؼ��ر�ǰ���һ����Ϣ
	* @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	*/
	void AttachLastEvent(const EventCallback& callback) { AttachEvent(kEventLast, callback); }

public:
	/** �ж���ɫ�����Ƿ���Ч
	* @param [in] colorName ��ɫ�����ƣ���Ч����ɫ���ƿ��������¶��壨����ȡ���ȼ�˳�򣩣�
	*           (1) ���ȼ�1����'#'�ַ���ͷ��ֱ��ָ����ɫֵ��������#FFFFFFFF       
	*		    (2) ���ȼ�2��������XML�е�<Window>�ڵ��ж����ӽڵ㣬������<TextColor name="wnd_darkcolor" value="#FF00BB96"/>
	*           (3) ���ȼ�3����global.xml�е�<Global>�ڵ��ж����ӽڵ㣬������<TextColor name="white" value="#FFFFFFFF"/>                    
	*           (4) ���ȼ�4���μ�ui::UiColors::UiColorConsts�����еĶ���
	*/
	bool HasUiColor(const std::wstring& colorName) const;

	/** ��ȡĳ����ɫ��Ӧ��ֵ
	* @param [in] colorName ��ɫ�����ƣ���Ч����ɫ���ƿ��������¶��壨����ȡ���ȼ�˳�򣩣�
	*           (1) ���ȼ�1����'#'�ַ���ͷ��ֱ��ָ����ɫֵ��������#FFFFFFFF
	*		    (2) ���ȼ�2��������XML�е�<Window>�ڵ��ж����ӽڵ㣬������<TextColor name="wnd_darkcolor" value="#FF00BB96"/>
	*           (3) ���ȼ�3����global.xml�е�<Global>�ڵ��ж����ӽڵ㣬������<TextColor name="white" value="#FFFFFFFF"/>                    
	*           (4) ���ȼ�4��ֱ��ָ��Ԥ�������ɫ�������μ�ui::UiColors::UiColorConsts�����еĶ���
	* @return ARGB��ɫֵ
	*/
    UiColor GetUiColor(const std::wstring& colorName) const;

	/** ��ȡ��ɫֵ��Ӧ���ַ���, ���ظ���ɫ��Ӧ���ַ���
	* @param [in] color ��ɫֵ
	* @return ������ɫֵ��Ӧ���ַ���������"#FF123456"
	*/
	std::wstring GetColorString(const UiColor& color) const;

	/** �жϿؼ������Ƿ�Ϊ��ѡ���
	 * @return Ĭ�Ϸ���false
	 */
	virtual bool IsSelectableType() const;

	/** �ж��Ƿ���� TAB ������Ϣ
	 * @return ���� true ��ʾ���ܣ�false ��ʾ�����ܣ� Ĭ�Ϸ���false
	 */
	virtual bool IsWantTab() const;

	/** �ÿؼ��Ƿ���Է����ڱ������ϣ������ڴ���NC��Ϣ��Ӧ��
	 * @return ���� true ��ʾ���ԣ�false ��ʾ�����ԣ� Ĭ�Ϸ���false
	 */
	virtual bool CanPlaceCaptionBar() const;

	/** ��ǰ�ؼ��Լ������������Ƿ�ɼ����ӵ�ǰ�ؼ�����㸸�ؼ���ֻҪ��һ��VisibleΪfalse���򷵻�false��
	* @return true ��ʾ��ǰ�ؼ��Լ����и��ؼ������ǿɼ�״̬
	*         false ��ʾ��ǰ�ؼ��������и��ؼ��У��зǿɼ�״̬�Ŀؼ�
	 */
	bool CheckVisibleAncestor(void) const;

public:
	/**@name �¼�������ؽӿ�
	* @{
	*/

	/**@brief (m_pOnEvent)����ָ���¼�
	 * @param[in] type �¼����ͣ��� EventType ö��
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachEvent(EventType type, const EventCallback& callback);

	/**@brief (m_pOnEvent)ȡ������ָ���¼�
	 * @param[in] type �¼����ͣ��� EventType ö��
	 */
	void DetachEvent(EventType type);

	/**@brief (m_pOnXmlEvent)ͨ��XML�У�����<Event��ǩ��ӵ���Ӧ�¼���������Control::OnApplyAttributeList������Ӧ�������
	 * @param[in] type �¼����ͣ��� EventType ö��
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 */
	void AttachXmlEvent(EventType eventType, const EventCallback& callback);

	/**@brief (m_pOnXmlEvent)ȡ������ָ���¼�
	 * @param[in] type �¼����ͣ��� EventType ö��
	 */
	void DetachXmlEvent(EventType type);

	/**@brief (m_pOnBubbledEvent)���¼�������
	 * @param[in] eventType �¼�����
	 * @param[in] callback ָ���ص�����
	 */
	void AttachBubbledEvent(EventType eventType, const EventCallback& callback);

	/**@brief (m_pOnBubbledEvent)����¼�������
	 * @param[in] eventType �¼�����
	 */
	void DetachBubbledEvent(EventType eventType);

	/** @brief �� XML �б�д�� Event �� BubbleEvent �¼��Ĵ�����
	 * @param[in] eventType �¼�����
	 * @param[in] callback ָ���ص�����
	 */
	void AttachXmlBubbledEvent(EventType eventType, const EventCallback& callback);

	/** @brief ���XML�¼�������
	 * @param[in] eventType �¼�����
	 */
	void DetachXmlBubbledEvent(EventType eventType);

	/** �����¼��������������ļ����߷����¼���m_pOnEvent��m_pOnXmlEvent��m_pOnBubbledEvent�� m_pOnXmlBubbledEvent��
	* @param [in] msg ��Ϣ����
	* @return ������м����߻ص���������true����ú�������true�����򷵻�false
	*/
	bool FireAllEvents(const EventArgs& msg);

	/** @} */

protected:

	//��������ؼ���������߼� 
	void EnsureNoFocus();

	/** �ж���Ϣ�Ƿ�ΪӦ���˵�����Ϣ, ��������
	*   �����ǰ�ؼ��� !IsEnabled() || !IsMouseEnabled() || !IsKeyboardEnabled() ״̬��
	    ������Ϣ����ꡢ������Ϣ������true�����򷵻�false
	*/
	bool IsDisabledEvents(const EventArgs& msg) const;

	//��Ϣ����ı�����Ա�������������ⲿֱ�ӵ���

	/** ��Ϣ������
	* @param [in] msg ��Ϣ����
	*/
	virtual void HandleEvent(const EventArgs& msg);

	//�����Ϣ������true����ʾ��Ϣ�Ѵ�������false�����ʾ��Ϣδ������ת�������ؼ���
	virtual bool MouseEnter(const EventArgs& msg);
	virtual bool MouseLeave(const EventArgs& msg);
	virtual bool ButtonDown(const EventArgs& msg);
	virtual bool ButtonUp(const EventArgs& msg);
	virtual bool ButtonDoubleClick(const EventArgs& msg);
	virtual bool RButtonDown(const EventArgs& msg);
	virtual bool RButtonUp(const EventArgs& msg);
	virtual bool RButtonDoubleClick(const EventArgs& msg);
	virtual bool MouseMove(const EventArgs& msg);
	virtual bool MouseHover(const EventArgs& msg);
	virtual bool MouseWheel(const EventArgs& msg);
	virtual bool MouseMenu(const EventArgs& msg);

    //������Ϣ������true����ʾ��Ϣ�Ѵ�������false�����ʾ��Ϣδ������ת�������ؼ���
	virtual bool OnChar(const EventArgs& msg);
	virtual bool OnKeyDown(const EventArgs& msg);
	virtual bool OnKeyUp(const EventArgs& msg);
	virtual bool OnSysKeyDown(const EventArgs& msg);
	virtual bool OnSysKeyUp(const EventArgs& msg);

    //����뽹�������Ϣ������true����ʾ��Ϣ�Ѵ�������false�����ʾ��Ϣδ������ת�������ؼ���
	virtual bool OnSetCursor(const EventArgs& msg);
	virtual bool OnSetFocus(const EventArgs& msg);
	virtual bool OnKillFocus(const EventArgs& msg); //�ؼ�ʧȥ����
	virtual bool OnWindowKillFocus(const EventArgs& msg);//�ؼ������Ĵ���ʧȥ����
	virtual bool OnImeStartComposition(const EventArgs& msg);
	virtual bool OnImeEndComposition(const EventArgs& msg);

	/// ������ر�����Ա�������������ⲿֱ�ӵ���
	virtual void PaintShadow(IRender* pRender);
	virtual void PaintBkColor(IRender* pRender);
	virtual void PaintBkImage(IRender* pRender);
	virtual void PaintStateColors(IRender* pRender);
	virtual void PaintStateImages(IRender* pRender);
	virtual void PaintText(IRender* pRender);
	virtual void PaintBorder(IRender* pRender);
	virtual void PaintFocusRect(IRender* pRender);
	virtual void PaintLoading(IRender* pRender);

protected:
	/** �Ƿ�״̬ͼƬ, ֻҪ��������״̬ͼƬ��������true
	*/
	bool HasStateImages(void) const;

	/** �Ƿ���ָ�����͵�ͼƬ
	*/
	bool HasStateImage(StateImageType stateImageType) const;

	/** ��ȡָ��״̬�µ�ͼƬλ��
	 */
	std::wstring GetStateImage(StateImageType imageType, ControlStateType stateType) const;

	/** ����ĳ��״̬�µ�ͼƬ
	 */
	void SetStateImage(StateImageType imageType, ControlStateType stateType, const std::wstring& strImage);

	/** ����ָ�����͡�ָ��״̬��ͼƬ
	* @param [in] pRender ���ƽӿ�
	* @param [in] stateImageType ͼƬ����
	* @param [in] stateType �ؼ�״̬������ѡ������ĸ�ͼƬ
	* @param [in] sImageModify ͼƬ�ĸ�������
	* @param [out] pDestRect ����ͼƬ���Ƶ�����Ŀ���������
	* @return ���Ƴɹ�����true, ���򷵻�false
	*/
	bool PaintStateImage(IRender* pRender, 
						 StateImageType stateImageType, 
					     ControlStateType stateType, 
						 const std::wstring& sImageModify = L"",
		                 UiRect* pDestRect = nullptr);

	/** �������״̬ͼƬ����
	*/
	void ClearStateImages();

	/** ����״̬ͼƬ���ڱ߾�leftֵ(����״̬ͼƬ���ڱ߾�һ�����)
	* @param [in] leftOffset Ҫ���õ�ͼƬ�ڱ߾�ƫ������������ʾ���ӣ�������ʾ����
	* @param [in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	* @return �ɹ�����true��ʧ�ܷ���false
	*/
	bool AdjustStateImagesPaddingLeft(int32_t leftOffset, bool bNeedDpiScale = true);

	/** ��ȡ����ͼƬ���ڱ߾�
	 */
	UiPadding GetBkImagePadding() const;

	/** ���ñ���ͼƬ���ڱ߾�
	 * @param[in] rcPadding Ҫ���õ�ͼƬ�ڱ߾�
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 */
	bool SetBkImagePadding(UiPadding rcPadding, bool bNeedDpiScale = true);

	/** �ж��Ƿ���ñ���ͼƬ����
	*/
	bool IsBkImagePaintEnabled() const;
 
	/** �����Ƿ��ֹ����ͼƬ����
	*/
	void SetBkImagePaintEnabled(bool bEnable);

	/** ��ȡ����ͼƬ·�����������ԣ�
	*/
	std::wstring GetBkImagePath() const;

	/** ��ȡ����ͼƬ��С(�������ͼƬ)
	*/
	UiSize GetBkImageSize() const;

protected:
	/** ����ָ��״̬����ɫ
	*/
	void PaintStateColor(IRender* pRender, const UiRect& rcPaint, ControlStateType stateType) const;

	/** @brief ��ȡ�ؼ��Ļ�������
	*/
	const UiRect& GetPaintRect() const { return m_rcPaint; }

	/** @brief ���ÿؼ��Ļ�������
	*/
	void SetPaintRect(const UiRect& rect);

	/** ���ƽ���״̬�ľ��Σ�������ɵľ��Σ�
	*/
	void DoPaintFocusRect(IRender* pRender);

	/** ֹͣ����GIF����(����ͼƬ�Ķ�����)
	*/
	void CheckStopGifPlay();

private:
	/** ���Ʊ߿򣺸��������жϻ���Բ�Ǿ��α߿�����ͨ���α߿�
	*/
	void PaintBorders(IRender* pRender, UiRect rcDraw, 
		              int32_t nBorderSize, UiColor dwBorderColor) const;

    /** ����Բ�Ǿ���
	*/
	void DrawRoundRect(IRender* pRender, const UiRect& rc, const UiSize& roundSize, UiColor dwBorderColor, int32_t nBorderSize) const;

	/** ���Բ�Ǿ���
	*/
	void FillRoundRect(IRender* pRender, const UiRect& rc, const UiSize& roundSize, UiColor dwColor) const;
  
    /** ���·��, �γ�Բ�Ǿ���
	*/
	void AddRoundRectPath(IPath* path, const UiRect& rc, UiSize roundSize) const;

	/** ��ǰ�ؼ��Ƿ�Ϊ���ڵ�Root�ڵ�
	*/
	bool IsRootBox() const;

	/** ��ǰWindow�Ƿ�ΪԲ�ǵ�(����ȷ���Ƿ������Windowsһ����Բ�ǻ��Ʒ�ʽ)
	*/
	bool IsWindowRoundRect() const;

	/** �ж��Ƿ���Ҫ����Բ�Ǿ��λ��Ʊ߿�
	*/
	bool ShouldBeRoundRectBorders() const;

public:
	/** �ж��Ƿ���Ҫ����Բ�Ǿ�����䱳��ɫ
	*/
	bool ShouldBeRoundRectFill() const;

	/** ��ȡָ��״̬�µ�ͼƬ��С(�������ͼƬ)
	*/
	UiSize GetStateImageSize(StateImageType imageType, ControlStateType stateType);

	/** ���ù��
	* @param [in] cursorType �������
	*/
	void SetCursor(CursorType cursorType);

	/** ���û���˳��
	* @param [in] nPaintOrder 0 ��ʾ������ƣ���0��ʾָ������˳��ֵԽ���ʾԽ�����
	*/
	void SetPaintOrder(uint8_t nPaintOrder);

	/** ��ȡ����˳��
	*/
	uint8_t GetPaintOrder() const;

private:

	/** ��ȡ��ɫ���ƶ�Ӧ����ɫֵ
	*/
	UiColor GetUiColorByName(const std::wstring& colorName) const;

	/** �Ƿ���BoxShadow
	*/
	bool HasBoxShadow() const;

	/** ���ÿؼ�״̬��ֵ��������״̬�仯�¼�
	 * @param[in] controlState Ҫ���õĿؼ�״̬����ο� `ControlStateType` ö��
	 */
	void PrivateSetState(ControlStateType controlState);

private:
	/** �߿�Բ�Ǵ�С(��m_rcBorderSize����Ӧ��)������Ӱ��Բ�Ǵ�С(��m_boxShadow����Ӧ��)
	    ���� m_rcBorderSize �ĸ��߿�ֵ����Ч, ���Ҷ���ͬʱ
	*/
	UiSize m_cxyBorderRound;

	//�ؼ���Ӱ����Բ�Ǵ�Сͨ��m_cxyBorderRound��������
	BoxShadow* m_pBoxShadow;

	/** ����״̬�µı߿���ɫ
	*/
	UiString m_focusBorderColor;

	/** �߿���ɫ, ÿ��״̬����ָ����ͬ�ı߿���ɫ
	*/
	std::unique_ptr<StateColorMap> m_pBorderColorMap;

	//�ؼ��ıߵı߿��С���ɷֱ�����top/bottom/left/right�ĸ��ߵ�ֵ��
	UiRect m_rcBorderSize;

private:
	//�ؼ��ı�����ɫ
	UiString m_strBkColor;

	//�ؼ��ı���ͼƬ
	std::shared_ptr<Image> m_pBkImage;

private:
	/** �ؼ�״̬(ControlStateType)
	*/
	int8_t m_controlState;

	/** ״̬����ɫֵMAP��ÿ��״̬����ָ����ͬ����ɫ
	*/
	std::unique_ptr<StateColorMap> m_pColorMap;

	/** �ؼ�ͼƬ������״̬ͼƬ��MAP
	*/
	std::unique_ptr<StateImageMap> m_pImageMap;

private:
	/** �ؼ�"������"�߼���ʵ�ֽӿ�
	*/
	ControlLoading* m_pLoading;

private:
	//�ؼ��������Ź�����
	std::unique_ptr<AnimationManager> m_animationManager;

	//�ؼ����Ŷ���ʱ����Ⱦƫ��(X����ƫ�ƺ�Y����ƫ��)
	UiPoint m_renderOffset;
	
	//�ؼ���͸���ȣ�0 - 255��0Ϊ��ȫ͸����255Ϊ��͸����
	uint8_t m_nAlpha;

	//�ؼ�ΪHot״̬ʱ��͸���ȣ�0 - 255��0Ϊ��ȫ͸����255Ϊ��͸����
	uint8_t m_nHotAlpha;

	//�Ƿ�Ի��Ʒ�Χ����������
	bool m_bClip;

	//�ؼ��Ļ�������
	UiRect m_rcPaint;

	//������Ⱦ����ӿ�
	std::unique_ptr<IRender> m_render;

	//box-shadow�Ƿ��Ѿ����ƣ�����box-shadow���ƻᳬ��GetRect()��Χ��������Ҫ���⴦��
	bool m_isBoxShadowPainted;

private:
	//ToolTip�Ŀ��
	uint16_t m_nTooltipWidth;

	//ToolTip���ı�����
	UiString m_sToolTipText;

	//ToolTip���ı�ID
	UiString m_sToolTipTextId;

private:
	
	//�û�����ID(�ַ���)
	UiString m_sUserDataID;

	//�û�����ID(����ֵ)
	size_t m_uUserDataID;

private:
	//ͨ��AttachXXX�ӿڣ���ӵļ����¼�
	EventMap* m_pOnEvent;

	//ͨ��XML�У�����<Event��ǩ��ӵ���Ӧ�¼���������Control::OnApplyAttributeList������Ӧ�������
	EventMap* m_pOnXmlEvent;

	//ͨ��AttachBubbledEvent�ӿ���ӵ��¼�
	EventMap* m_pOnBubbledEvent;

	//ͨ��XML�У�����<BubbledEvent��ǩ��ӵ���Ӧ�¼���������Control::OnApplyAttributeList������Ӧ�������
	EventMap* m_pOnXmlBubbledEvent;

private:
	//�ؼ���Enable״̬����Ϊfalse��ʱ�򣬲���Ӧ��ꡢ���̵�������Ϣ��
	bool m_bEnabled;

	//�����Ϣ��Enable״̬����Ϊfalse��ʱ�򣬲���Ӧ�����Ϣ��
	bool m_bMouseEnabled;

	//������Ϣ��Enable״̬����Ϊfalse��ʱ�򣬲���Ӧ������Ϣ��
	bool m_bKeyboardEnabled;

	//��꽹���Ƿ��ڿؼ���
	bool m_bMouseFocused;

	//�ؼ��Ƿ���Ӧ�����Ĳ˵�
	bool m_bContextMenuUsed;

	//�ؼ�����Ҫ���㣨���Ϊtrue����ؼ������ý��㣩
	bool m_bNoFocus;

	//�Ƿ�����TAB�л�����
	bool m_bAllowTabstop;

	//�ؼ��Ĺ������(CursorType)
	int8_t m_cursorType;

	//�Ƿ���ʾ����״̬(һ�����߹��ɵľ���)
	bool m_bShowFocusRect;

	//����״̬���߾��ε���ɫ
	UiString m_focusRectColor;

	//����˳��: 0 ��ʾ������ƣ���0��ʾָ������˳��ֵԽ���ʾ����Խ�����
	uint8_t m_nPaintOrder;
};

} // namespace ui

#endif // UI_CORE_CONTROL_H_
