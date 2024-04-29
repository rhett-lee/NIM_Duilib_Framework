#ifndef UI_CORE_CONTROL_LOADING_H_
#define UI_CORE_CONTROL_LOADING_H_

#pragma once

#include "duilib/Core/UiTypes.h"
#include "base/callback/callback.h"
#include <memory>

namespace ui 
{

/** �ؼ�������״̬���߼���װ
*/
class Image;
class Control;
class IRender;
class ControlLoading: public nbase::SupportWeakCallback
{
public:
	explicit ControlLoading(Control* pControl);
	~ControlLoading();
	ControlLoading(const ControlLoading&) = delete;
	ControlLoading& operator = (const ControlLoading&) = delete;

public:
	/** ����"������"ͼƬ��·����������Ϣ
	* @return ����仯����true�����򷵻�false
	*/
	bool SetLoadingImage(const std::wstring& strImage);

	/** ����loading����ɫ
	* @param[in] strColor ����ɫ
	* @return ����仯����true�����򷵻�false
	*/
	bool SetLoadingBkColor(const std::wstring& strColor);

	/** ����"������"ͼƬ
	*/
	void PaintLoading(IRender* pRender);

	/** ����loading״̬
	* @param[in] start_angle loadingͼƬ��ת�ĽǶ�
	*/
	bool StartLoading(int32_t fStartAngle = -1);

	/** �ر�loading״̬
	* @param[in] frame �������ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	*/
	void StopLoading(GifFrameType frame = kGifFrameFirst);

	/** �Ƿ�����loading
	* @return ��loading����true, ��֮����false
	*/
	bool IsLoading() const;

private:
	/** ����loadingͼƬ����ת�Ƕ�, ��תͼƬ
	*/
	void Loading();

private:
	//�Ƿ��ڼ����е�״̬
	bool m_bIsLoading;

	//������ͼƬ��ת�ĽǶȣ�0-360��
	int32_t m_fCurrrentAngele;

	//������״̬ʱ��ʾ��ͼƬ
	std::unique_ptr<Image> m_pLoadingImage;

	//������״̬ʱ�ı�����ɫ
	UiString m_strLoadingBkColor;

	//������״̬ͼƬ(m_pLoadingImage)���������ڹ���ȡ������
	nbase::WeakCallbackFlag m_loadingImageFlag;

	//������Control����
	Control* m_pControl;
};

} // namespace ui

#endif // UI_CORE_CONTROL_LOADING_H_
