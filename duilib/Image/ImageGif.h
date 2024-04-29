#ifndef UI_IMAGE_IMAGE_GIF_H_
#define UI_IMAGE_IMAGE_GIF_H_

#pragma once

#include "duilib/Core/UiTypes.h"
#include "duilib/Utils/Delegate.h"
#include "base/callback/callback.h"
#include <memory>
#include <map>

namespace ui 
{
class Image;
class Control;
typedef std::map<int32_t, CEventSource> GifEventMap;

/** �ؼ�������̬���Ŷ������߼���װ��֧��GIF/WebP/APNG������
*/
class ImageGif: public nbase::SupportWeakCallback
{
public:
	ImageGif();
	virtual ~ImageGif();
	ImageGif(const ImageGif&) = delete;
	ImageGif& operator = (const ImageGif&) = delete;

public:
	/** ���ù����Ŀؼ��ӿ�
	*/
	void SetControl(Control* pControl);

	/** ���ù�����ͼƬ�ӿ�
	*/
	void SetImage(Image* pImage);

	/** ���ö�������ʾ����
	*/
	void SetImageRect(const UiRect& rcImageRect);

	/** ���� GIF/WebP/APNG ����
	 */
	bool StartGifPlay();

	/** ֹͣ���� GIF/WebP/APNG ����
	 */
	void StopGifPlay();

	/** ���� GIF/WebP/APNG ����
	 * @param [in] nStartFrame ����һ֡��ʼ���ţ������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	 * @param [in] nPlayCount ָ�����Ŵ���, �����-1��ʾһֱ����
	 */
	bool StartGifPlay(GifFrameType nStartFrame, int32_t nPlayCount);

	/** ֹͣ���� GIF/WebP/APNG ����
	 * @param [in] bTriggerEvent �Ƿ�ֹͣ�¼�֪ͨ�������ߣ��ο� AttachGifPlayStop ����
	 * @param [in] nStopFrame ���Ž���ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifFrameType ö��
	 */
	void StopGifPlay(bool bTriggerEvent, GifFrameType nStopFrame);

	/** �Ƿ����ڲ��Ŷ���
	*/
	bool IsPlayingGif() const;

	/** ���� GIF �������֪ͨ
	 * @param[in] callback Ҫ���� GIF ֹͣ���ŵĻص�����
	 */
	void AttachGifPlayStop(const EventCallback& callback) { m_OnGifEvent[m_nVirtualEventGifStop] += callback; };

private:
	/** ������߷��Ͳ���ֹͣ�¼�
	*/
	void BroadcastGifEvent(int32_t nVirtualEvent) const;

	/** ��ȡGIF֡��
	*/
	uint32_t GetGifFrameIndex(GifFrameType frame) const;

	/** ��ʱ������GIF�Ļص�����
	*/
	bool PlayGif();

	/** �ػ�ͼƬ
	*/
	void RedrawImage();

	/** �Ƿ�λ��֡ͼƬ(����GIF��)
	*/
	bool IsMultiFrameImage() const;

private:
	/** GIF����ͼƬ���ŵ�ȡ������
	*/
	nbase::WeakCallbackFlag m_gifWeakFlag;

	/** GIF�����¼��Ļص�ע���������(Ŀǰֻ�в������һ���¼�)
	*/
	GifEventMap m_OnGifEvent;

	/** ������Control����
	*/
	Control* m_pControl;

	/** ͼƬ�ӿ�
	*/
	Image* m_pImage;

	/** ��������ʾ����
	*/
	UiRect m_rcImageRect;

	/** �Ƿ����ڲ��Ŷ���ͼƬ
	*/
	bool m_bPlayingGif;

	/** �Ƿ��Զ���ʼ����
	*/
	bool m_bAutoPlay;

	/** �Ѳ��Ŵ���
	*/
	int32_t m_nCycledCount;

	/** ��󲥷Ŵ���
	*/
	int32_t m_nMaxPlayCount;

	/** GIF����ͼƬ��������¼���ID
	*/
	static const int32_t m_nVirtualEventGifStop = 1;
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_GIF_H_
