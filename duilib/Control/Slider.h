#ifndef UI_CONTROL_SLIDER_H_
#define UI_CONTROL_SLIDER_H_

#pragma once

#include "duilib/Control/Progress.h"
#include <string>

namespace ui
{

/** ����ؼ�
*/
class UILIB_API Slider : public Progress
{
public:
	Slider();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetType() const override;
	virtual UiRect GetProgressPos() override;
	virtual void HandleEvent(const EventArgs& msg) override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void PaintStateImages(IRender* pRender) override;
	virtual void PaintBkColor(IRender* pRender) override;
	virtual void ClearImageCache() override;

	/**
	 * @brief ��ȡ��������
	 * @return ���ز�������
	 */
	int GetChangeStep();

	/**
	 * @brief ���ò�������
	 * @param[in] step Ҫ���õĲ���
	 * @return ��
	 */
	void SetChangeStep(int step);

	/**
	 * @brief ���öද����Ĵ�С
	 * @param[in] szXY Ҫ���õĴ�С
	 * @return ��
	 */
	void SetThumbSize(UiSize szXY);

	/**
	 * @brief ��ȡ����ľ�����Ϣ
	 * @return ���ػ���ľ�����Ϣ
	 */
	UiRect GetThumbRect() const;

	/**
	 * @brief ��ȡָ��״̬�»����ͼƬ
	 * @param[in] stateType Ҫ��ȡ��״̬��ʶ���ο� ControlStateType ö��
	 * @return ����ͼƬ·��
	 */
	std::wstring GetThumbStateImage(ControlStateType stateType) const;

	/**
	 * @brief ����ָ��״̬�»����ͼƬ
	 * @param[in] stateType Ҫ���õ�״̬��ʶ���ο� ControlStateType ö��
	 * @param[in] pStrImage Ҫ���õ�ͼƬλ��
	 * @return ��
	 */
	void SetThumbStateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/** ��ȡ�������ڱ߾�
	 */
	const UiPadding& GetProgressBarPadding() const;

	/** ���ý������ڱ߾�
	 * @param[in] padding Ҫ���õ��ڱ߾���Ϣ
	 */
	void SetProgressBarPadding(UiPadding padding);

	/**
	 * @brief �������������ȸı��¼�
	 * @param[in] callback ���������ȸı����õĻص�����
	 * @return ��
	 */
	void AttachValueChange(const EventCallback& callback) { AttachEvent(kEventValueChange, callback);	}

protected:
	int m_nStep;
	UiSize m_szThumb;
	StateImage m_thumbStateImage;
	UiPadding m_rcProgressBarPadding;
	UiString m_sImageModify;
};

}

#endif // UI_CONTROL_SLIDER_H_