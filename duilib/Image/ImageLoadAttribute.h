#ifndef UI_IMAGE_IMAGE_LOAD_ATTRIBUTE_H_
#define UI_IMAGE_IMAGE_LOAD_ATTRIBUTE_H_

#pragma once

#include "duilib/Core/UiTypes.h"

namespace ui 
{
class Control;

/** ͼƬ�������ԣ����ڼ���һ��ͼƬ
*/
class UILIB_API ImageLoadAttribute
{
public:
	ImageLoadAttribute(std::wstring srcWidth,
					   std::wstring srcHeight,
		               bool srcDpiScale,
		               bool bHasSrcDpiScale,
		               uint32_t iconSize);

	/** ����ͼƬ·�������ؾ���·������ѹ�����ڵ����·����
	*/
	void SetImageFullPath(const std::wstring& imageFullPath);

	/** ��ȡͼƬ·�������ؾ���·������ѹ�����ڵ����·����
	*/
	std::wstring GetImageFullPath() const;

	/** ��ȡ����ͼƬ�Ļ���KEY
	*/
	std::wstring GetCacheKey() const;

	/** ���ü���ͼƬʱ���Ƿ���Ҫ����DPI����ͼƬ��С
	*/
	void SetNeedDpiScale(bool bNeedDpiScale);

	/** ��ȡ����ͼƬʱ���Ƿ���Ҫ����DPI����ͼƬ��С
	*/
	bool NeedDpiScale() const;

	/** ��ȡ����ͼƬʱ���Ƿ�������DPI����Ӧ���ԣ�����XML�ļ��У�����ͨ�����ã�"file='test.png' dpiscale='false'"��
	*/
	bool HasSrcDpiScale() const;

	/** ��ȡͼƬ���غ�Ӧ�����ŵĿ�Ⱥ͸߶�
	* @param [in,out] nImageWidth ����ԭʼͼƬ�Ŀ�ȣ����ؼ����Ŀ��
	* @param [in,out] nImageHeight ԭʼͼƬ�ĸ߶ȣ����ؼ����ĸ߶�
	* @return ����true��ʾͼƬ��С�����ţ�����false��ʾͼƬ��С������
	*/
	bool CalcImageLoadSize(uint32_t& nImageWidth, uint32_t& nImageHeight) const;

	/** �����ICO�ļ�������ָ����Ҫ���ص�ICOͼƬ�Ĵ�С
	*/
	uint32_t GetIconSize() const;

private:
	/** ��ȡ���õ����ź�Ĵ�С
	*/
	uint32_t GetScacledSize(const std::wstring& srcSize, uint32_t nImageSize) const;

private:
	//���ؾ���·������ѹ�����ڵ����·��������������
	UiString m_srcImageFullPath;

	//����ͼƬ��ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������300������30%
	UiString m_srcWidth;

	//����ͼƬ�߶ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������200������30%
	UiString m_srcHeight;

	//����ͼƬʱ������DPI����ͼƬ��С
	bool m_srcDpiScale;

	//����ͼƬʱ���Ƿ�������DPI����Ӧ����
	bool m_bHasSrcDpiScale;

	//�����ICO�ļ�������ָ����Ҫ���ص�ICOͼƬ�Ĵ�С
	//(ICO�ļ��а����ܶ����ͬ��С��ͼƬ����������256��48��32��16������ÿ����С����32λ��ʡ�256ɫ��16ɫ֮�֣�
	//ĿǰICO�ļ��ڼ���ʱ��ֻ��ѡ��һ����С��ICOͼƬ���м��أ����غ�Ϊ����ͼƬ
	uint32_t m_iconSize;
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_LOAD_ATTRIBUTE_H_
