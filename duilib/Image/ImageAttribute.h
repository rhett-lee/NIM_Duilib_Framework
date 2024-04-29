#ifndef UI_IMAGE_IMAGE_ATTRIBUTE_H_
#define UI_IMAGE_IMAGE_ATTRIBUTE_H_

#pragma once

#include "duilib/Core/UiTypes.h"

namespace ui 
{
/** ͼƬ����
*/
class UILIB_API ImageAttribute
{
public:
	ImageAttribute();
	~ImageAttribute();
	ImageAttribute(const ImageAttribute&);
	ImageAttribute& operator=(const ImageAttribute&);

	/** �����ݳ�Ա���г�ʼ��
	*/
	void Init();

	/** ����ͼƬ�������г�ʼ��(�ȵ���Init��ʼ����Ա�������ٰ��մ���������и��²�������)
	* @param [in] strImageString ͼƬ�����ַ���
	*/
	void InitByImageString(const std::wstring& strImageString);

	/** ����ͼƬ�����޸�����ֵ�������������õ�ͼƬ����, δ���������Բ����и��£�
	* @param [in] strImageString ͼƬ�����ַ���
	*/
	void ModifyAttribute(const std::wstring& strImageString);

public:
	/** �ж�rcDest�����Ƿ�����Чֵ
	* @param [in] rcDest ��Ҫ�жϵ�����
	*/
	static bool HasValidImageRect(const UiRect& rcDest);

	/** ��ͼƬ��Դ����Ŀ������Բ�Ǵ�С����У��������DPI����Ӧ
	* @param [in] imageWidth ͼƬ�Ŀ��
	* @param [in] imageHeight ͼƬ�ĸ߶�
	* @param [in] bImageDpiScaled ͼƬ�Ƿ�����DPI����Ӧ����
	* @param [out] rcDestCorners ����Ŀ�������Բ����Ϣ�������������ڲ�����rcImageCorners�����ã�Ȼ�󴫳�
	* @param [in/out] rcSource ͼƬ����
	* @param [in/out] rcSourceCorners ͼƬ�����Բ����Ϣ
	*/
	static void ScaleImageRect(uint32_t imageWidth, uint32_t imageHeight, bool bImageDpiScaled,
		                       UiRect& rcDestCorners,
		                       UiRect& rcSource, UiRect& rcSourceCorners);

public:
	/** ��ȡrcSource
	*/
	UiRect GetSourceRect() const;

	/** ��ȡrcDest
	*/
	UiRect GetDestRect() const;

	/** rcPadding;
	*/
	UiPadding GetPadding() const;

	/** ��ȡrcCorner;
	*/
	UiRect GetCorner() const;

	/** ����ͼƬ���Ե��ڱ߾�(�ڲ�����DPI����Ӧ)
	*/
	void SetPadding(const UiPadding& newPadding);

public:
	//ͼƬ�ļ������ַ���
	UiString sImageString;

	//ͼƬ�ļ��ļ����������·��������������
	UiString sImagePath;

	//����ͼƬ��ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������300������30%
	UiString srcWidth;

	//����ͼƬ�߶ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������200������30%
	UiString srcHeight;

	//����ͼƬʱ��DPI����Ӧ���ԣ�������DPI����ͼƬ��С
	bool srcDpiScale;

	//����ͼƬʱ���Ƿ�������DPI����Ӧ����
	bool bHasSrcDpiScale;

	//�ڻ���Ŀ�������к�����뷽ʽ(���ָ����rcDestֵ�����ѡ����Ч)
	UiString hAlign;

	//�ڻ���Ŀ��������������뷽ʽ(���ָ����rcDestֵ�����ѡ����Ч)
	UiString vAlign;

	//͸���ȣ�0 - 255��
	uint8_t bFade;

	//����ƽ��
	bool bTiledX;

	//������ȫƽ�̣�����bTiledXΪtrueʱ��Ч
	bool bFullTiledX;

	//����ƽ��
	bool bTiledY;

	//������ȫƽ�̣�����bTiledYΪtrueʱ��Ч
	bool bFullTiledY;

	//ƽ��ʱ�ı߾ࣨ����bTiledXΪtrue����bTiledYΪtrueʱ��Ч��
	int32_t nTiledMargin;

	//�����GIF�ȶ���ͼƬ������ָ�����Ŵ��� -1 ��һֱ���ţ�ȱʡֵ��
	int32_t nPlayCount;	

	//�����ICO�ļ�������ָ����Ҫ���ص�ICOͼƬ�Ĵ�С
	//(ICO�ļ��а����ܶ����ͬ��С��ͼƬ����������256��48��32��16������ÿ����С����32λ��ʡ�256ɫ��16ɫ֮�֣�
	//ĿǰICO�ļ��ڼ���ʱ��ֻ��ѡ��һ����С��ICOͼƬ���м��أ����غ�Ϊ����ͼƬ
	uint32_t iconSize;

	//�ɻ��Ʊ�־��true��ʾ������ƣ�false��ʾ��ֹ����
	bool bPaintEnabled;

private:
	//����Ŀ������λ�úʹ�С������ڿؼ������λ�ã�
	UiRect* rcDest;

	//�ڻ���Ŀ�������е��ڱ߾�(���ָ����rcDestֵ�����ѡ����Ч)
	UiPadding16* rcPadding;

	//ͼƬԴ����λ�úʹ�С
	UiRect* rcSource;

	//Բ������
	UiRect* rcCorner;
};

} // namespace ui

#endif // UI_IMAGE_IMAGE_ATTRIBUTE_H_
