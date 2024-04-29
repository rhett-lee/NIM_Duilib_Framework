#ifndef UI_IMAGE_IMAGE_DECODER_H_
#define UI_IMAGE_IMAGE_DECODER_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <memory>
#include <vector>
#include <string>

namespace ui 
{
class ImageInfo;
class ImageLoadAttribute;

/** ͼƬ��ʽ������
*/
class UILIB_API ImageDecoder
{
public:
    /** ���ڴ��ļ������м���ͼƬ������ͼƬ����, ��͸����Կ���ֻ����һ��������һ��������Ĭ�ϰ�ԴͼƬ�ȱȼ���ó�
    * @param [in] fileData ͼƬ�ļ������ݣ����ָ�ʽ���ع������ڲ�������β0��д����
    * @param [in] imageLoadAttribute ͼƬ��������, ����ͼƬ·����
    */
	std::unique_ptr<ImageInfo> LoadImageData(std::vector<uint8_t>& fileData,
                                             const ImageLoadAttribute& imageLoadAttribute);

public:
    /** ���غ��ͼƬ����
    */
    struct ImageData
    {
        /** λͼ���ݣ�ÿ֡ͼƬ�����ݳ��ȹ̶�Ϊ��ͼ�����ݳ���Ϊ (m_imageHeight*m_imageWidth*4)
        *   ÿ���������ݹ̶�ռ4���ֽڣ���ʽΪARGB��ʽ��λ��˳��Ӹ�λ����λ�ֱ�Ϊ[��3λ:A����2λ:R����1λ:G,��0λ:B]
        */
        std::vector<uint8_t> m_bitmapData;

        /** ͼ����
        */
        uint32_t m_imageWidth = 0;

        /** ͼ��߶�
        */
        uint32_t m_imageHeight = 0;

        /** ��������ʱ���ӳ�ʱ�䣬��λΪ����
        */
        uint32_t m_frameInterval = 0;

        /** ����λͼ��ʱ���Ƿ���Ҫ��ת�߶ȣ���ͬ�������棬�����Կ��ܲ�ͬ��
        */
        bool bFlipHeight = true;
    };

private:
    /** ��ͼƬ���ݽ��н��룬����λͼ����
    * @param [in] fileData ԭʼͼƬ����
    * @param [in] imageFormat ԭʼͼƬ���ݵ�ͼƬ��ʽ
    * @param [out] imageData ���سɹ���ͼƬ���ݣ�ÿ��ͼƬ֡һ��Ԫ��
    * @param [out] playCount �������ŵ�ѭ������(-1��ʾ��Чֵ�����ڵ���0ʱ��ʾֵ��Ч���������0����ʾ������ѭ�����ŵ�, APNG��ʽ֧������ѭ�����Ŵ���)
    * @param [out] bDpiScaled ͼƬ���ص�ʱ��ͼƬ��С�Ƿ������DPI����Ӧ����
    */
    bool DecodeImageData(std::vector<uint8_t>& fileData, 
                         const ImageLoadAttribute& imageLoadAttribute,
                         std::vector<ImageData>& imageData,
                         int32_t& playCount,
                         bool& bDpiScaled);

    /** ��ͼƬ���ݽ��д�С����
    * @param [in] imageData ��Ҫ���ŵ�ͼƬ����
    * @param [in] nNewWidth �µĿ��
    * @param [in] nNewHeight �µĸ߶�
    */
    bool ResizeImageData(std::vector<ImageData>& imageData, 
                         uint32_t nNewWidth,
                         uint32_t nNewHeight);

    /** ֧�ֵ�ͼƬ�ļ���ʽ
    */
    enum class ImageFormat {
        kUnknown,
        kPNG,
        kSVG,
        kGIF,
        kWEBP,
        kJPEG,
        kBMP,
        kICO
    };

    /** ����ͼƬ�ļ�����չ����ȡͼƬ��ʽ
    */
    static ImageFormat GetImageFormat(const std::wstring& path);
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_DECODER_H_
