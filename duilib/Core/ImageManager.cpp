#include "ImageManager.h"
#include "duilib/Image/Image.h"
#include "duilib/Image/ImageDecoder.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Utils/StringUtil.h"
#include "duilib/Utils/FileUtil.h"

namespace ui 
{

ImageManager::ImageManager():
	m_bDpiScaleAllImages(true)
{
}

ImageManager::~ImageManager()
{
}

std::shared_ptr<ImageInfo> ImageManager::GetCachedImage(const ImageLoadAttribute& loadAtrribute)
{
	std::wstring cacheKey = loadAtrribute.GetCacheKey();
	std::shared_ptr<ImageInfo> sharedImage;
	auto it = m_imageMap.find(cacheKey);
	if (it != m_imageMap.end()) {
		sharedImage = it->second.lock();
	}
	return sharedImage;
}

std::shared_ptr<ImageInfo> ImageManager::GetImage(const ImageLoadAttribute& loadAtrribute)
{
	std::wstring imageCacheKey = loadAtrribute.GetCacheKey();
	auto it = m_imageMap.find(imageCacheKey);
	if (it != m_imageMap.end()) {
		std::shared_ptr<ImageInfo> sharedImage = it->second.lock();
		if (sharedImage) {
			//�ӻ����У��ҵ���ЧͼƬ��Դ��ֱ�ӷ���
			return sharedImage;
		}
	}

	//���¼�����Դ
	bool isUseZip = GlobalManager::Instance().Zip().IsUseZip();
	std::wstring imageFullPath = GetDpiImageFullPath(loadAtrribute.GetImageFullPath(), isUseZip);
	//���DPI����ӦͼƬ���ԣ����·����ͬ��˵���Ѿ�ѡ���˶�ӦDPI�µ��ļ�
	bool isDpiScaledImageFile = imageFullPath != loadAtrribute.GetImageFullPath();

	std::vector<uint8_t> fileData;
	if (isUseZip) {
		GlobalManager::Instance().Zip().GetZipData(imageFullPath, fileData);
	}
	else {
		FileUtil::ReadFileData(imageFullPath, fileData);
	}
	ASSERT(!fileData.empty());

	std::unique_ptr<ImageInfo> imageInfo;
	if (!fileData.empty()) {
		ImageDecoder imageDecoder;
		ImageLoadAttribute imageLoadAtrribute(loadAtrribute);
		if (isDpiScaledImageFile) {
			imageLoadAtrribute.SetNeedDpiScale(false);
		}
		imageInfo = imageDecoder.LoadImageData(fileData, imageLoadAtrribute);
	}
	std::shared_ptr<ImageInfo> sharedImage;
	if (imageInfo != nullptr) {
		sharedImage.reset(imageInfo.release(), &OnImageInfoDestroy);
		sharedImage->SetCacheKey(imageCacheKey);
		if (isDpiScaledImageFile) {
			//ʹ����DPI����Ӧ��ͼƬ�������
			sharedImage->SetBitmapSizeDpiScaled(true);
		}
		m_imageMap[imageCacheKey] = sharedImage;
	}
	return sharedImage;
}

void ImageManager::OnImageInfoDestroy(ImageInfo* pImageInfo)
{
	ASSERT(pImageInfo != nullptr);
	ImageManager& imageManager = GlobalManager::Instance().Image();
	if (pImageInfo != nullptr) {
		std::wstring imageCacheKey = pImageInfo->GetCacheKey();
		if (!imageCacheKey.empty()) {
			auto it = imageManager.m_imageMap.find(imageCacheKey);
			if (it != imageManager.m_imageMap.end()) {
				imageManager.m_imageMap.erase(it);
			}
		}
		delete pImageInfo;
	}	
}

void ImageManager::RemoveAllImages()
{
	m_imageMap.clear();
}

void ImageManager::SetDpiScaleAllImages(bool bEnable)
{
	m_bDpiScaleAllImages = bEnable;
}

bool ImageManager::IsDpiScaleAllImages()
{
	return m_bDpiScaleAllImages;
}

std::wstring ImageManager::GetDpiImageFullPath(const std::wstring& strImageFullPath, bool bIsUseZip)
{
	UINT dpi = GlobalManager::Instance().Dpi().GetScale();
	if (dpi == 100) {
		//��ǰDPI��������
		return strImageFullPath;
	}

	std::wstring strPathDir;
	std::wstring strPathFileName;
	std::list<std::wstring> strPathList = StringHelper::Split(strImageFullPath, L"\\");
	for (auto it = strPathList.begin(); it != strPathList.end(); ++it) {
		auto itTemp = it;
		if (++itTemp == strPathList.end()) {
			strPathFileName = *it;
		}
		else {
			strPathDir += *it + L"\\";
		}
	}

	size_t iPointPos = strPathFileName.rfind('.');
	ASSERT(iPointPos != std::wstring::npos);
	if (iPointPos == std::wstring::npos)
	{
		return std::wstring();
	}
	std::wstring strFileExtension = strPathFileName.substr(iPointPos, strPathFileName.length() - iPointPos);
	std::wstring strFile = strPathFileName.substr(0, iPointPos);
	//����ָ��DPI�µ�ͼƬ������DPIΪ120��ͼƬ��"image.png" ��Ӧ�� "image@120.png"
	strPathFileName = StringHelper::Printf(L"%s%s%d%s", strFile.c_str(), L"@", dpi, strFileExtension.c_str());
	std::wstring strNewFilePath = strPathDir + strPathFileName;
	if (bIsUseZip) {
		bool hasData = GlobalManager::Instance().Zip().IsZipResExist(strNewFilePath);
		return hasData ? strNewFilePath : strImageFullPath;
	}
	else {
		return StringHelper::IsExistsPath(strNewFilePath) ? strNewFilePath : strImageFullPath;
	}
}

}
