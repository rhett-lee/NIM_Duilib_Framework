#ifndef UI_IMAGE_IMAGE_H_
#define UI_IMAGE_IMAGE_H_

#pragma once

#include "duilib/Image/ImageInfo.h"
#include "duilib/Image/ImageAttribute.h"
#include "duilib/Image/ImageLoadAttribute.h"
#include "duilib/Image/StateImageMap.h"
#include "duilib/Utils/Delegate.h"
#include <memory>

namespace ui 
{
class Control;
class ImageGif;

/** ͼƬ��ط�װ��֧�ֵ��ļ���ʽ��SVG/PNG/GIF/JPG/BMP/APNG/WEBP/ICO
*/
class UILIB_API Image
{
public:
	Image();
	Image(const Image&) = delete;
	Image& operator=(const Image&) = delete;

public:
	/** @name ͼƬ����
	* @{
	*/
	/** ��ʼ��ͼƬ����
	*/
	void InitImageAttribute();

	/** ���ò���ʼ��ͼƬ����
	*@param [in] strImageString ͼƬ�����ַ���
	*/
	void SetImageString(const std::wstring& strImageString);

	/** ��ȡͼƬ���ԣ����ļ�������ͼƬ�������Եȣ�
	*/
	std::wstring GetImageString() const;

	/** �ж�ͼƬ�����Ƿ����
	*/
	bool EqualToImageString(const std::wstring& imageString) const;

	/** ��ȡͼƬ�ļ����������·��������ͼƬ���ԣ�
	*/
	std::wstring GetImagePath() const;

	/** ����ͼƬ���Ե��ڱ߾�
	*/
	void SetImagePadding(const UiPadding& newPadding);

	/** ��ȡͼƬ���Ե��ڱ߾�
	*/
	UiPadding GetImagePadding() const;

	/** �ж��Ƿ����ͼƬ����
	*/
	bool IsImagePaintEnabled() const;

	/** �����Ƿ��ֹ����ͼƬ����
	*/
	void SetImagePaintEnabled(bool bEnable);

	/** ����ͼƬ���ԣ����Ŵ�����������֡ͼƬʱ��
	*/
	void SetImagePlayCount(int32_t nPlayCount);

	/** ����ͼƬ���ԣ�͸���ȣ�������֡ͼƬʱ��
	*/
	void SetImageFade(uint8_t nFade);

	/** ��ȡͼƬ���ԣ�ֻ����
	*/
	const ImageAttribute& GetImageAttribute() const;

	/** ��ȡͼƬ��������
	*/
	ImageLoadAttribute GetImageLoadAttribute() const;

	/** @} */

public:
	/** @name ͼƬ���ݣ����ⲿ����ͼƬ���ݣ�
	* @{
	*/
	/** ��ȡͼƬ��Ϣ�ӿ�
	*/
	const std::shared_ptr<ImageInfo>& GetImageCache() const;

	/** ����ͼƬ��Ϣ�ӿ�
	*/
	void SetImageCache(const std::shared_ptr<ImageInfo>& imageInfo);

	/** ���ͼƬ��Ϣ��������, �ͷ���Դ
	*/
	void ClearImageCache();

	/** ���õ�ǰͼƬ֡��������֡ͼƬʱ��
	*/
	void SetCurrentFrame(uint32_t nCurrentFrame);

	/** ��ȡ��ǰͼƬ֡������������֡ͼƬʱ��
	*/
	uint32_t GetCurrentFrame() const;

	/** ��ȡͼƬ��֡��
	*/
	uint32_t GetFrameCount() const;

	/** �Ƿ�λ��֡ͼƬ(����GIF��)
	*/
	bool IsMultiFrameImage() const;

	/** ��ȡ��ǰͼƬ֡��ͼƬ����
	*/
	IBitmap* GetCurrentBitmap() const;

	/** @} */

public:
	/** @name ͼƬ����ʾ
	* @{
	*/
	/** ���ù����Ŀؼ��ӿ�
	*/
	void SetControl(Control* pControl);

	/** ���� GIF/WebP/APNG ����
	* @param [in] rcImageRect ����ͼƬ����ʾ����
	*/
	bool CheckStartGifPlay(const UiRect& rcImageRect);

	/** ֹͣ���� GIF/WebP/APNG ����
	 */
	void CheckStopGifPlay();

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

	/** @} */

private:

	/** ��ǰ���ڲ��ŵ�ͼƬ֡��������֡ͼƬʱ��
	*/
	uint32_t m_nCurrentFrame;

	/** �����Ŀؼ��ӿ�
	*/
	Control* m_pControl;

	/** ��֡ͼƬ����ʵ�ֽӿ�
	*/
	ImageGif* m_pImageGif;

	/** ͼƬ����
	*/
	ImageAttribute m_imageAttribute;

	/** ͼƬ��Ϣ
	*/
	std::shared_ptr<ImageInfo> m_imageCache;
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_H_
