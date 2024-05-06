#ifndef UI_IMAGE_STATE_IMAGE_H_
#define UI_IMAGE_STATE_IMAGE_H_

#pragma once

#include "duilib/Core/UiTypes.h"
#include <map>

namespace ui 
{
/** �ؼ�״̬��ͼƬ��ӳ��
*/
class Control;
class Image;
class IRender;
class UILIB_API StateImage
{
public:
	StateImage();
	~StateImage();

	/** ���ù����Ŀؼ��ӿ�
	*/
	void SetControl(Control* pControl);

	/** ����ͼƬ����
	*@param [in] stateType ͼƬ����
	*@param [in] strImageString ͼƬ�����ַ���
	*/
	void SetImageString(ControlStateType stateType, const std::wstring& strImageString);

	/** ��ȡͼƬ����
	*@param [in] stateType ͼƬ����
	*/
	std::wstring GetImageString(ControlStateType stateType) const;

	/** ��ȡͼƬ�ļ���
	*@param [in] stateType ͼƬ����
	*/
	std::wstring GetImagePath(ControlStateType stateType) const;

	/** ��ȡͼƬ��Դ�����С
	*@param [in] stateType ͼƬ����
	*/
	UiRect GetImageSourceRect(ControlStateType stateType) const;

	/** ��ȡͼƬ��͸����
	*@param [in] stateType ͼƬ����
	*/
	int32_t GetImageFade(ControlStateType stateType) const;

	/** ��ȡͼƬ�ӿ�(�ɶ�����д)
	*/
	Image* GetStateImage(ControlStateType stateType) const;

public:
	/** �Ƿ����Hot״̬��ͼƬ
	*/
	bool HasHotImage() const;

	/** �Ƿ����״̬ͼƬ
	*/
	bool HasImage() const;

	/** ����ָ��״̬��ͼƬ
	* @param [in] pRender ���ƽӿ�
	* @param [in] stateType �ؼ�״̬������ѡ������ĸ�ͼƬ
	* @param [in] sImageModify ͼƬ�ĸ�������
	* @param [out] pDestRect ����ͼƬ���Ƶ�����Ŀ���������
	* @return ���Ƴɹ�����true, ���򷵻�false
	*/
	bool PaintStateImage(IRender* pRender, ControlStateType stateType, 
					     const std::wstring& sImageModify = L"",
		                 UiRect* pDestRect = nullptr);

	/** ��ȡ���ڹ���Control�ؼ���С����͸ߣ���ͼƬ�ӿ�
	*/
	Image* GetEstimateImage() const;

	/** ��ȡ����ͼƬ�ӿ�
	*/
	void GetAllImages(std::vector<Image*>& allImages) const;

	/** ���ͼƬ���棬�ͷ���Դ
	*/
	void ClearImageCache();

	/** ֹͣ����ͼƬ�Ķ���
	*/
	void StopGifPlay();

private:
	//�����Ŀؼ��ӿ�
	Control* m_pControl;

	//ÿ��״̬��ͼƬ�ӿ�
	std::map<ControlStateType, Image*> m_stateImageMap;
};

} // namespace ui

#endif // UI_IMAGE_STATE_IMAGE_H_
