#ifndef UI_IMAGE_STATE_IMAGE_MAP_H_
#define UI_IMAGE_STATE_IMAGE_MAP_H_

#pragma once

#include "duilib/Image/StateImage.h"

namespace ui 
{
/** �ؼ�ͼƬ������״̬ͼƬ��ӳ��
*/
class UILIB_API StateImageMap
{
public:
	StateImageMap();

	/** ���ù����Ŀؼ��ӿ�
	*/
	void SetControl(Control* pControl);

	/** ����ͼƬ����
	*@param [in] stateImageType ͼƬ���ͣ���������״̬ǰ��ͼƬ������ͼƬ��ѡ��״̬��ǰ��ͼƬ������ͼƬ��
	*@param [in] stateType ͼƬ״̬���������������㡢���¡�����״̬��
	*@param [in] strImagePath ͼƬ�����ַ���
	*/
	void SetImageString(StateImageType stateImageType, ControlStateType stateType, const std::wstring& strImagePath);

	/** ��ȡͼƬ����
	*@param [in] stateImageType ͼƬ���ͣ���������״̬ǰ��ͼƬ������ͼƬ��ѡ��״̬��ǰ��ͼƬ������ͼƬ��
	*@param [in] stateType ͼƬ״̬���������������㡢���¡�����״̬��
	*/
	std::wstring GetImageString(StateImageType stateImageType, ControlStateType stateType) const;

	/** �Ƿ���Hot״̬��ͼƬ
	*/
	bool HasHotImage() const;

	/** �Ƿ�״̬ͼƬ
	*/
	bool HasStateImages(void) const;

	/** �Ƿ���ָ�����͵�ͼƬ
	*/
	bool HasStateImage(StateImageType stateImageType) const;

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
	
	/** ��ȡ���ڹ���Control�ؼ���С����͸ߣ���ͼƬ�ӿ�
	*/
	Image* GetEstimateImage(StateImageType stateImageType) const;

	/** ��ȡָ��ͼƬ���ͺ�״̬��ͼƬ�ӿ�
	*/
	Image* GetStateImage(StateImageType stateImageType, ControlStateType stateType) const;

	/** ��ȡ����ͼƬ�ӿ�
	*/
	void GetAllImages(std::vector<Image*>& allImages) const;

	/** �������ͼƬ���͵Ļ��棬�ͷ���Դ
	*/
	void ClearImageCache();

	/** ֹͣ����ͼƬ�Ķ���
	*/
	void StopGifPlay();

private:
	//�����Ŀؼ��ӿ�
	Control* m_pControl;

	//ÿ��ͼƬ���͵�״̬ͼƬ(����״̬ǰ��ͼƬ������ͼƬ��ѡ��״̬��ǰ��ͼƬ������ͼƬ)
	std::map<StateImageType, StateImage> m_stateImageMap;
};

} // namespace ui

#endif // UI_IMAGE_STATE_IMAGE_MAP_H_
