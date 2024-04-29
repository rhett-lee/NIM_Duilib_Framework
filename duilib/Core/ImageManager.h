#ifndef UI_CORE_IMAGEMANAGER_H_
#define UI_CORE_IMAGEMANAGER_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace ui 
{
class ImageInfo;
class ImageLoadAttribute;

/** ͼƬ������
 */
class UILIB_API ImageManager
{
public:
	ImageManager();
	~ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator = (const ImageManager&) = delete;

public:
	/** ���ָ��ͼƬ�Ƿ��Ѿ�������
	 * @param[in] loadAtrribute ͼƬ�ļ������ԣ�����ͼƬ·������Ϣ
	 * @return ����Ѿ������棬�򷵻� ImageInfo ������ָ�����
	 */
	std::shared_ptr<ImageInfo> GetCachedImage(const ImageLoadAttribute& loadAtrribute);

	/** ����ͼƬ ImageInfo ����
	 * @param[in] loadAtrribute ͼƬ�ļ������ԣ�����ͼƬ·������Ϣ
	 * @return ����ͼƬ ImageInfo ���������ָ��
	 */
	std::shared_ptr<ImageInfo> GetImage(const ImageLoadAttribute& loadAtrribute);

	/** �ӻ�����ɾ������ͼƬ
	 */
	void RemoveAllImages();

	/** �����Ƿ�Ĭ�϶�����ͼƬ�ڼ���ʱ����DPI�������ţ������ȫ�����ԣ�Ĭ��Ϊtrue��Ӧ��������ͼƬ
	   ������Ϊtrue��Ҳ����ͨ����xml�У�ʹ��"dpiscale='false'"���Թر�ĳ��ͼƬ��DPI�Զ����ţ�
	*/
	void SetDpiScaleAllImages(bool bEnable);

	/** �ж��Ƿ�Ĭ�϶�����ͼƬ�ڼ���ʱ����DPI��������
	*/
	bool IsDpiScaleAllImages();

private:
	/** ͼƬ�����ٵĻص������������ͷ�ͼƬ��Դ
	 * @param[in] pImageInfo ͼƬ��Ӧ�� ImageInfo ����
	 */
	static void OnImageInfoDestroy(ImageInfo* pImageInfo);

	/** ���Ҷ�ӦDPI�µ�ͼƬ������ÿ��DPI����һ��ͼƬ������߲�ͬDPI�µ�ͼƬ����
	*/
	std::wstring GetDpiImageFullPath(const std::wstring& strImageFullPath, bool bIsUseZip) const;

	/** ���ļ�����һ��ͼƬ
	*/
	void LoadImageData(const ImageLoadAttribute& loadAtrribute,
		               bool& isDpiScaledImageFile,
		               std::unique_ptr<ImageInfo>& imageInfo) const;

#ifdef UILIB_IMPL_WINSDK
	/** ��HICON�������һ��ͼƬ
	*/
	void LoadIconData(const ImageLoadAttribute& loadAtrribute,
		              std::unique_ptr<ImageInfo>& imageInfo) const;
#endif

private:
	/** �����Ƿ�Ĭ�϶�����ͼƬ�ڼ���ʱ����DPI�������ţ������ȫ�����ԣ�Ĭ��Ϊtrue��Ӧ��������ͼƬ
	   ������Ϊtrue��Ҳ����ͨ����xml�У�ʹ��"dpiscale='false'"���Թر�ĳ��ͼƬ��DPI�Զ����ţ�
	*/
	bool m_bDpiScaleAllImages;

	/** ͼƬ��Դӳ���
	*/
	std::unordered_map<std::wstring, std::weak_ptr<ImageInfo>> m_imageMap;
};

}
#endif //UI_CORE_IMAGEMANAGER_H_
