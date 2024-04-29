#ifndef UI_IMAGE_IMAGE_INFO_H_
#define UI_IMAGE_IMAGE_INFO_H_

#pragma once

#include "duilib/Render/IRender.h"
#include "duilib/Core/UiTypes.h"

namespace ui 
{
	class IRender;
	class Control;

/** ͼƬ��Ϣ
*/
class UILIB_API ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

	ImageInfo(const ImageInfo&) = delete;
	ImageInfo& operator = (const ImageInfo&) = delete;

public:
	/** ����ͼƬ·��
	*/
	void SetImageFullPath(const std::wstring& path);

	/** ��ȡͼƬ·��
	*/
	std::wstring GetImageFullPath() const;

	/** ���ø�ͼƬ�Ĵ�С�Ƿ��Ѿ�������ӦDPI����
	*/
	void SetBitmapSizeDpiScaled(bool isDpiScaled) { m_bDpiScaled = isDpiScaled; }

	/** �жϸ�ͼƬ�Ĵ�С�Ƿ��Ѿ�������ӦDPI����
	*/
	bool IsBitmapSizeDpiScaled() const { return m_bDpiScaled; }

	/** ����ͼƬ�Ŀ�͸�
	*/
	void SetImageSize(int32_t nWidth, int32_t nHeight);

	/** ��ȡͼƬ���
	*/
	int32_t GetWidth() const { return m_nWidth; }

	/** ��ȡͼƬ�߶�
	*/
	int32_t GetHeight() const { return m_nHeight; }

	/** ���һ��ͼƬ֡����, ��Ӻ����Դ�ɸ����ڲ��й�
	*/
	void SetFrameBitmap(const std::vector<IBitmap*>& frameBitmaps);

	/** ��ȡһ��ͼƬ֡����
	*/
	IBitmap* GetBitmap(uint32_t nIndex) const;

	/** ����ͼƬ�Ķ�֡�����¼����������Ϊ��λ ��
	*/
	void SetFrameInterval(const std::vector<int32_t>& frameIntervals);

	/** ��ȡͼƬ֡��Ӧ�Ĳ���ʱ����������Ϊ��λ ��
	*/
	int32_t GetFrameInterval(uint32_t nIndex) const;

	/** ��ȡͼƬ��֡��
	*/
	uint32_t GetFrameCount() const;

	/** �Ƿ�λ��֡ͼƬ(����GIF��)
	*/
	bool IsMultiFrameImage() const;

	/** ����ѭ�����Ŵ���(���ڵ���0���������0����ʾ������ѭ�����ŵ�, APNG��ʽ֧������ѭ�����Ŵ���)
	*/
	void SetPlayCount(int32_t nPlayCount);

	/** ��ȡѭ�����Ŵ���
	*@return ����ֵ��-1 ��ʾδ����
	*               0  ��ʾ������һ��ѭ�����ŵ�
	*              > 0 ��ʾ����ѭ�����ŵľ������
	*/
	int32_t GetPlayCount() const;

	/** ����ͼƬ�Ļ���KEY, ����ͼƬ���������ڹ���
	*/
	void SetCacheKey(const std::wstring& cacheKey);

	/** ��ȡͼƬ�Ļ���KEY
	*/
	std::wstring GetCacheKey() const;

private:
	//ͼƬ������·��
	UiString m_imageFullPath;

	//��ͼƬ�Ĵ�С�Ƿ��Ѿ�������ӦDPI����
	bool m_bDpiScaled;

	//ͼƬ�Ŀ��
	int32_t m_nWidth;
	
	//ͼƬ�ĸ߶�
	int32_t m_nHeight;

	//ͼƬ֡��Ӧ�Ĳ���ʱ����������Ϊ��λ ��
	std::vector<int32_t>* m_pFrameIntervals;

	//ͼƬ֡����
	IBitmap** m_pFrameBitmaps;

	//ͼƬ֡����
	uint32_t m_nFrameCount;

	//ѭ�����Ŵ���(���ڵ���0���������0����ʾ������ѭ�����ŵ�, APNG��ʽ֧������ѭ�����Ŵ���)
	int32_t m_nPlayCount;

	/** ͼƬ�Ļ���KEY, ����ͼƬ���������ڹ���
	*/
	UiString m_cacheKey;
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_INFO_H_
