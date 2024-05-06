#ifndef UI_CORE_SCROLLBAR_H_
#define UI_CORE_SCROLLBAR_H_

#pragma once

#include "duilib/Core/Control.h"
#include "base/callback/callback.h"

namespace ui
{
	class ScrollBox;
	class StateImage;

/** �������ؼ�
*/
class UILIB_API ScrollBar: 
	public Control
{
public:
	ScrollBar();
	ScrollBar(const ScrollBar& r) = delete;
	ScrollBar& operator=(const ScrollBar& r) = delete;

	ScrollBox* GetOwner() const;
	void SetOwner(ScrollBox* pOwner);

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual void SetEnabled(bool bEnable = true) override;
	virtual void SetFocus() override;
	virtual void SetVisible(bool bVisible) override;
	virtual bool ButtonUp(const EventArgs& msg) override;
	virtual bool HasHotState() override;
	virtual bool MouseEnter(const EventArgs& msg) override;
	virtual bool MouseLeave(const EventArgs& msg) override;

	virtual void SetPos(UiRect rc) override;
	virtual void HandleEvent(const EventArgs& msg) override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void Paint(IRender* pRender, const UiRect& rcPaint) override;
	virtual void ClearImageCache() override;

	/**
	 * @brief �Ƿ���ˮƽ������
	 * @return ���� true ������ˮƽ������������Ϊ false �����Ǵ�ֱ������
	 */
	bool IsHorizontal();

	/**
	 * @brief ���ù���������
	 * @param[in] ���� true ������ˮƽ������������ false �����Ǵ�ֱ��������Ĭ��Ϊ true
	 * @return ��
	 */
	void SetHorizontal(bool bHorizontal);

	/**
	 * @brief ��ȡ������Χ����Ӧ XML �� range ����
	 * @return ���ع�����Χ
	 */
	int64_t GetScrollRange() const;

	/**
	 * @brief �����ù�����Χ
	 * @param[in] nRange Ҫ���õĹ�����Χ
	 * @return ��
	 */
	void SetScrollRange(int64_t nRange);

	/**
	 * @brief �ж��Ƿ���Ч
	 * @return true Ϊ��Ч������Ϊ false
	 */
	bool IsValid() { return GetScrollRange() != 0; }

	/**
	 * @brief ��ȡ������λ��
	 * @return ���ع�����λ��
	 */
	int64_t GetScrollPos() const;

	/**
	 * @brief ���ù�����λ��
	 * @param[in] nPos Ҫ���õ�λ����Ϣ
	 * @return ��
	 */
	void SetScrollPos(int64_t nPos);

	/**
	 * @brief ��ȡ����һ�еĴ�С
	 * @return ���ع���һ�еĴ�С
	 */
	int GetLineSize() const;

	/**
	 * @brief ���ù���һ�еĴ�С
	 * @param[in] nSize Ҫ���õĴ�С��ֵ
	 * @return ��
	 */
	void SetLineSize(int nSize);

	/**
	 * @brief ��ȡ�������С����
	 * @return ���ػ������С����
	 */
	int GetThumbMinLength() const;

	/**
	 * @brief ���û������С����
	 * @param[in] nThumbMinLength Ҫ���õ���С����
	 * @return ��
	 */
	void SetThumbMinLength(int nThumbMinLength);

	/**
	 * @brief �Ƿ���ʾ����ϰ�ť
	 * @return ���� true Ϊ��ʾ��false Ϊ����ʾ
	 */
	bool IsShowButton1();

	/**
	 * @brief �����Ƿ���ʾ����ϰ�ť
	 * @param[in] bShow ���� true Ϊ��ʾ��false Ϊ����ʾ
	 * @return ��
	 */
	void SetShowButton1(bool bShow);

	/**
	 * @brief ��ȡָ��״̬�µ���������ϰ�ťͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetButton1StateImage(ControlStateType stateType);

	/**
	 * @brief ����ָ��״̬�µ���������ϰ�ťͼƬ
	 * @param[in] stateType Ҫ��������״̬�µ�ͼƬ
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetButton1StateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief �Ƿ���ʾ�һ��°�ť
	 * @return ���� true Ϊ��ʾ��false Ϊ����ʾ
	 */
	bool IsShowButton2();

	/**
	 * @brief �����Ƿ���ʾ�һ��°�ť
	 * @param[in] bShow ���� true Ϊ��ʾ��false Ϊ����ʾ
	 * @return ��
	 */
	void SetShowButton2(bool bShow);

	/**
	 * @brief ��ȡָ��״̬�µ����һ����°�ťͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetButton2StateImage(ControlStateType stateType);

	/**
	 * @brief ����ָ��״̬�µ����һ����°�ťͼƬ
	 * @param[in] stateType Ҫ��������״̬�µ�ͼƬ
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetButton2StateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief ��ȡ����ָ��״̬�µ�ͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬��ʶ���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetThumbStateImage(ControlStateType stateType);

	/**
	 * @brief ���û���ָ��״̬�µ�ͼƬ
	 * @param[in] stateType Ҫ���õ�״̬��ʶ���ο� ControlStateType ö��
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetThumbStateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief ��ȡָ��״̬�»����м��ʶͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬��ʶ���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetRailStateImage(ControlStateType stateType);

	/**
	 * @brief ����ָ��״̬�»����м��ʶͼƬ
	 * @param[in] stateType Ҫ���õ�״̬��ʶ���ο� ControlStateType ö��
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetRailStateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief ��ȡָ��״̬�µı���ͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬��ʶ���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetBkStateImage(ControlStateType stateType);

	/**
	 * @brief ����ָ��״̬�µı���ͼƬ
	 * @param[in] stateType Ҫ���õ�״̬��ʶ���ο� ControlStateType ö��
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetBkStateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief �Ƿ��Զ����ع�����
	 * @return ���� true Ϊ�ǣ�����Ϊ false
	 */
	bool IsAutoHideScroll(){return m_bAutoHide;}

	/**
	 * @brief �����Ƿ��Զ����ع�����
	 * @param[in] hide ����Ϊ true Ϊ�Զ����أ�false Ϊ���Զ�����
	 * @return ��
	 */
	void SetAutoHideScroll(bool hide);

	/**
	 * @brief ��ȡ����״̬
	 * @return ���ػ���״̬���ο� ControlStateType ö��
	 */
	ControlStateType GetThumbState() { return m_uThumbState; }

private:
	void ScrollTimeHandle();

	/// ������غ���
	void PaintBk(IRender* pRender);
	void PaintButton1(IRender* pRender);
	void PaintButton2(IRender* pRender);
	void PaintThumb(IRender* pRender);
	void PaintRail(IRender* pRender);

	/** ��ȡһ�ο��ٹ�����ƫ����
	*/
	int64_t CalcFastScrollOffset(int32_t posOffset) const;

private:
	enum
	{ 
		DEFAULT_SCROLLBAR_SIZE = 16,
	};

	//�Ƿ�Ϊˮƽ��������true��ʾˮƽ��������false��ʾ��ֱ������
	bool m_bHorizontal;

	//�Ƿ���ʾ����ϰ�ť
	bool m_bShowButton1;

	//�Ƿ���ʾ�һ��°�ť
	bool m_bShowButton2;

	//�Ƿ��Զ����ع�����
	bool m_bAutoHide;

	//������Χ
	int64_t m_nRange;

	//������λ��
	int64_t m_nScrollPos;

	//����һ�еĴ�С
	int m_nLineSize;

	//�������������С����
	int m_nThumbMinLength;

	//�ϴεĹ�����λ��
	int64_t m_nLastScrollPos;

	//�ϴι�����λ��ƫ��
	int64_t m_nLastScrollOffset;

	//�ӳٹ����ظ�����
	int m_nScrollRepeatDelay;
	
	//�ϴ��������λ��
	UiPoint m_ptLastMouse;

	//����ϰ�ť��λ�úʹ�С
	UiRect m_rcButton1;

	//�һ��°�ť��λ�úʹ�С
	UiRect m_rcButton2;

	//�����λ�úʹ�С
	UiRect m_rcThumb;

	//����ϰ�ť��״̬
	ControlStateType m_uButton1State;

	//�һ��°�ť��״̬
	ControlStateType m_uButton2State;

	//�����״̬
	ControlStateType m_uThumbState;

	//ͼƬ��Ŀ�����򣬻�����
	std::wstring m_sImageModify;

	//��������״̬��ͼƬ
	std::unique_ptr<StateImage> m_bkStateImage;

	//����ϰ�ť��״̬ͼƬ
	std::unique_ptr<StateImage> m_button1StateImage;

	//�һ��°�ť��״̬ͼƬ
	std::unique_ptr<StateImage> m_button2StateImage;

	//�����״̬ͼƬ
	std::unique_ptr<StateImage> m_thumbStateImage;

	//ָ��״̬�»����м��ʶͼƬ
	std::unique_ptr<StateImage> m_railStateImage;

	//�ӳٹ�����ȡ������
	nbase::WeakCallbackFlag m_weakFlagOwner;

	//֧�ֹ������������ӿ�
	ScrollBox* m_pOwner;
};

}//namespace ui

#endif // UI_CORE_SCROLLBAR_H_
