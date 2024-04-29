#include "ImageAttribute.h"
#include "duilib/Core/GlobalManager.h"
#include "duilib/Utils/AttributeUtil.h"

namespace ui 
{
ImageAttribute::ImageAttribute():
	rcDest(nullptr),
	rcPadding(nullptr),
	rcSource(nullptr),
	rcCorner(nullptr)
{
	Init();
}

ImageAttribute::ImageAttribute(const ImageAttribute& r) :
	rcDest(nullptr),
	rcPadding(nullptr),
	rcSource(nullptr),
	rcCorner(nullptr)
{
	Init();
	*this = r;
}

ImageAttribute& ImageAttribute::operator=(const ImageAttribute& r)
{
	if (&r == this) {
		return *this;
	}

	sImageString = r.sImageString;
	sImagePath = r.sImagePath;
	srcWidth = r.srcWidth;
	srcHeight = r.srcHeight;

	srcDpiScale = r.srcDpiScale;
	bHasSrcDpiScale = r.bHasSrcDpiScale;
	hAlign = r.hAlign;
	vAlign = r.vAlign;

	bFade = r.bFade;
	bTiledX = r.bTiledX;
	bFullTiledX = r.bFullTiledX;
	bTiledY = r.bTiledY;
	bFullTiledY = r.bFullTiledY;
	nTiledMargin = r.nTiledMargin;
	nPlayCount = r.nPlayCount;
	iconSize = r.iconSize;
	bPaintEnabled = r.bPaintEnabled;

	if (r.rcDest != nullptr) {
		if (rcDest == nullptr) {
			rcDest = new UiRect;
		}
		*rcDest = *r.rcDest;
	}
	else {
		if (rcDest != nullptr) {
			delete rcDest;
			rcDest = nullptr;
		}
	}

	if (r.rcPadding != nullptr) {
		if (rcPadding == nullptr) {
			rcPadding = new UiPadding16;
		}
		*rcPadding = *r.rcPadding;
	}
	else {
		if (rcPadding != nullptr) {
			delete rcPadding;
			rcPadding = nullptr;
		}
	}

	if (r.rcSource != nullptr) {
		if (rcSource == nullptr) {
			rcSource = new UiRect;
		}
		*rcSource = *r.rcSource;
	}
	else {
		if (rcSource != nullptr) {
			delete rcSource;
			rcSource = nullptr;
		}
	}

	if (r.rcCorner != nullptr) {
		if (rcCorner == nullptr) {
			rcCorner = new UiRect;
		}
		*rcCorner = *r.rcCorner;
	}
	else {
		if (rcCorner != nullptr) {
			delete rcCorner;
			rcCorner = nullptr;
		}
	}

	return *this;
}

void ImageAttribute::Init()
{
	sImageString.clear();
	sImagePath.clear(); 
	srcWidth.clear();
	srcHeight.clear();

	srcDpiScale = false;
	bHasSrcDpiScale = false;
	hAlign.clear();
	vAlign.clear();

	bFade = 0xFF;
	bTiledX = false;
	bFullTiledX = true;
	bTiledY = false;
	bFullTiledY = true;
	nTiledMargin = 0;
	nPlayCount = -1;
	iconSize = 0;
	bPaintEnabled = true;

	if (rcDest != nullptr) {
		delete rcDest;
		rcDest = nullptr;
	}
	if (rcSource != nullptr) {
		delete rcSource;
		rcSource = nullptr;
	}
	if (rcPadding != nullptr) {
		delete rcPadding;
		rcPadding = nullptr;
	}
	if (rcCorner != nullptr) {
		delete rcCorner;
		rcCorner = nullptr;
	}
}

ImageAttribute::~ImageAttribute()
{
	if (rcDest != nullptr) {
		delete rcDest;
		rcDest = nullptr;
	}
	if (rcSource != nullptr) {
		delete rcSource;
		rcSource = nullptr;
	}
	if (rcPadding != nullptr) {
		delete rcPadding;
		rcPadding = nullptr;
	}
	if (rcCorner != nullptr) {
		delete rcCorner;
		rcCorner = nullptr;
	}
}

void ImageAttribute::InitByImageString(const std::wstring& strImageString)
{
	Init();
	sImageString = strImageString;
	sImagePath = strImageString;
	ModifyAttribute(strImageString);
}

void ImageAttribute::ModifyAttribute(const std::wstring& strImageString)
{
	if (strImageString.find(L'=') == std::wstring::npos) {
		//�����еȺţ�˵��û�����ԣ�ֱ�ӷ���
		return;
	}
	std::vector<std::pair<std::wstring, std::wstring>> attributeList;
	AttributeUtil::ParseAttributeList(strImageString, L'\'', attributeList);

	ImageAttribute& imageAttribute = *this;
	bool bDisalbeScaleDest = false;
	bool bHasDest = false;
	bHasSrcDpiScale = false;
	for (const auto& attribute : attributeList) {
		const std::wstring& name = attribute.first;
		const std::wstring& value = attribute.second;
		if (name.empty() || value.empty()) {
			continue;
		}
		if (name == L"file" || name == L"res") {
			//ͼƬ��Դ�ļ��������ݴ�����ȥ����ͼƬ��Դ
			imageAttribute.sImagePath = value;
		}
		else if (name == L"width") {
			//����ͼƬ��ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������300������30%
			imageAttribute.srcWidth = value;
		}
		else if (name == L"height") {
			//����ͼƬ�߶ȣ����ԷŴ����Сͼ��pixels���߰ٷֱ�%������200������30%
			imageAttribute.srcHeight = value;
		}
		else if (name == L"source") {
			//ͼƬԴ�������ã��������ڽ�����ԴͼƬ�Ĳ���ͼƬ���ݣ�����ͨ���˻��ƣ�����ť�ĸ���״̬ͼƬ���ϵ�һ�Ŵ�ͼƬ�ϣ��������ͼƬ��Դ��
			if (imageAttribute.rcSource == nullptr) {
				imageAttribute.rcSource = new UiRect;
			}
			AttributeUtil::ParseRectValue(value.c_str(), *imageAttribute.rcSource);
		}
		else if (name == L"corner") {
			//ͼƬ��Բ�����ԣ�������ô����ԣ�����ͼƬ��ʱ�򣬲��þŹ�����Ʒ�ʽ����ͼƬ��
			//    �ĸ��ǲ�����ͼƬ���ĸ��߲������죬�м䲿�ֿ���������߸���xtiled��ytiled������ƽ�̻���
			if (imageAttribute.rcCorner == nullptr) {
				imageAttribute.rcCorner = new UiRect;
			}
			AttributeUtil::ParseRectValue(value.c_str(), *imageAttribute.rcCorner);
		}
		else if ((name == L"dpi_scale") || (name == L"dpiscale")) {
			//����ͼƬʱ������DPI����ͼƬ��С����Ӱ��width���ԡ�height���ԡ�sources���ԡ�corner���ԣ�
			imageAttribute.srcDpiScale = (value == L"true");
			bHasSrcDpiScale = true;
		}
		else if (name == L"dest") {
			//����Ŀ�����򣬸�������ָ����������ؼ���Rect����
			if (imageAttribute.rcDest == nullptr) {
				imageAttribute.rcDest = new UiRect;
			}
			AttributeUtil::ParseRectValue(value.c_str(), *imageAttribute.rcDest);
			bHasDest = true;
		}
		else if ((name == L"dest_scale") || (name == L"destscale")) {
			//����ʱ����dest���԰���DPI����ͼƬ������������dest����ʱ��Ч����Ӱ��dest���ԣ�
			//����ʱ���ڲ�ʹ�ã��������Ƿ��dest���Խ���DPI����
			bDisalbeScaleDest = (value == L"false");
		}
		else if (name == L"padding") {
			//��Ŀ�������������ڱ߾�
			UiPadding padding;
			AttributeUtil::ParsePaddingValue(value.c_str(), padding);
			GlobalManager::Instance().Dpi().ScalePadding(padding);
			imageAttribute.SetPadding(padding);
		}
		else if (name == L"halign") {
			//��Ŀ�����������ú�����뷽ʽ			
			ASSERT((value == L"left") || (value == L"center") || (value == L"right"));
			if ((value == L"left") || (value == L"center") || (value == L"right")) {
				imageAttribute.hAlign = value;
			}
		}
		else if (name == L"valign") {
			//��Ŀ������������������뷽ʽ
			ASSERT((value == L"top") || (value == L"center") || (value == L"bottom"));
			if ((value == L"top") || (value == L"center") || (value == L"bottom")) {
				imageAttribute.vAlign = value;
			}
		}
		else if (name == L"fade") {
			//ͼƬ��͸����
			imageAttribute.bFade = (uint8_t)wcstoul(value.c_str(), nullptr, 10);
		}
		else if (name == L"xtiled") {
			//����ƽ��
			imageAttribute.bTiledX = (value == L"true");
		}
		else if ((name == L"full_xtiled") || (name == L"fullxtiled")) {
			//����ƽ��ʱ����֤����ͼƬ����
			imageAttribute.bFullTiledX = (value == L"true");
		}
		else if (name == L"ytiled") {
			//����ƽ��
			imageAttribute.bTiledY = (value == L"true");
		}
		else if ((name == L"full_ytiled") || (name == L"fullytiled")) {
			//����ƽ��ʱ����֤����ͼƬ����
			imageAttribute.bFullTiledY = (value == L"true");
		}
		else if ((name == L"tiled_margin") || (name == L"tiledmargin")) {
			//ƽ�̻���ʱ����ƽ��ͼƬ֮��ļ������������ƽ�̺�����ƽ��
			imageAttribute.nTiledMargin = wcstol(value.c_str(), nullptr, 10);
		}
		else if ((name == L"icon_size") || (name == L"iconsize")) {
			//ָ������ICO�ļ���ͼƬ��С(����ͼƬ�ļ���ICO�ļ�ʱ��Ч)
			imageAttribute.iconSize = (uint32_t)wcstol(value.c_str(), nullptr, 10);
		}
		else if ((name == L"play_count") || (name == L"playcount")) {
			//�����GIF��APNG��WEBP�ȶ���ͼƬ������ָ�����Ŵ��� -1 ��һֱ���ţ�ȱʡֵ��
			imageAttribute.nPlayCount = wcstol(value.c_str(), nullptr, 10);
			if (imageAttribute.nPlayCount < 0) {
				imageAttribute.nPlayCount = -1;
			}
		}
		else {
			ASSERT(!"ImageAttribute::ModifyAttribute: fount unknown attribute!");
		}
	}
	if (bHasDest && !bDisalbeScaleDest) {
		//���û������"destscale" ���� destscale="true"�����������Ҫ��rcDest����DPI����Ӧ
		//ֻ��������destscale="false"��ʱ�򣬲Ž�ֹ��rcDest����DPI����Ӧ
		if (imageAttribute.rcDest != nullptr) {
			GlobalManager::Instance().Dpi().ScaleRect(*imageAttribute.rcDest);
		}		
	}
}

bool ImageAttribute::HasValidImageRect(const UiRect& rcDest)
{
	if (rcDest.IsZero() || rcDest.IsEmpty()) {
		return false;
	}
	if ((rcDest.left >= 0) && (rcDest.top >= 0) && 
		(rcDest.Width() > 0) && (rcDest.Height() > 0)){
		return true;
	}
	return false;
}

void ImageAttribute::ScaleImageRect(uint32_t imageWidth, uint32_t imageHeight, bool bImageDpiScaled,
					                UiRect& rcDestCorners,
					                UiRect& rcSource, UiRect& rcSourceCorners)
{
	ASSERT((imageWidth > 0) && (imageHeight > 0));
	if ((imageWidth == 0) || (imageHeight == 0)) {
		return;
	}
	//��rcImageSourceCorners���д����Ա߽�ֵ�����ݴ����ĸ��ߴ���߾࣬�������������
	//��XML�������ص�ʱ��δ��DPI����Ӧ��
	//�ڻ��Ƶ�ʱ�����ͼƬ����DPI����Ӧ��ҲҪ��DPI����Ӧ�����ͼƬδ��DPI����Ӧ��Ҳ����Ҫ����	
	if ((rcSourceCorners.left < 0) || (rcSourceCorners.top < 0) ||
		(rcSourceCorners.right < 0)|| (rcSourceCorners.bottom < 0)) {
		rcSourceCorners.Clear();
	}
	else if (bImageDpiScaled) {
		GlobalManager::Instance().Dpi().ScaleRect(rcSourceCorners);
	}

	//��rcDestCorners���д�����rcSourceCorners��ֵ���߽Ǳ���һ�£��������ͼƬ��ʱ���ĸ����б��Σ�
	//���þŹ�����Ƶ�ʱ���ĸ��ǵĴ��ڣ���Ϊ�˱�����Ƶ�ʱ���ĸ��ǳ��ֱ���
	rcDestCorners = rcSourceCorners;
	if (!bImageDpiScaled) {
		//rcDestCorners������DPI����Ӧ��rcSourceCorners���ܲ���DPI����Ӧ����������ָ��������ͼƬ��
		GlobalManager::Instance().Dpi().ScaleRect(rcDestCorners);
	}

	// ���Դλͼ�Ѿ�����DPI���Ź�����ô��Ӧ��rcImageSourceҲ��Ҫ����
	if ((rcSource.left < 0) || (rcSource.top < 0) ||
		(rcSource.right < 0) || (rcSource.bottom < 0) ||
		(rcSource.Width() <= 0) || (rcSource.Height() <= 0)) {
		//�������Чֵ��������Ϊ����ͼƬ��С
		rcSource.left = 0;
		rcSource.top = 0;
		rcSource.right = (int32_t)imageWidth;
		rcSource.bottom = (int32_t)imageHeight;
	}
	else if (bImageDpiScaled) {
		//����ⲿ���ô�ֵ����DPI����Ӧ����
		GlobalManager::Instance().Dpi().ScaleRect(rcSource);
	}

	//ͼƬԴ�ݴ���
	if (rcSource.right > (int32_t)imageWidth) {
		rcSource.right = (int32_t)imageWidth;
	}
	if (rcSource.bottom > (int32_t)imageHeight) {
		rcSource.bottom = (int32_t)imageHeight;
	}
}

UiRect ImageAttribute::GetSourceRect() const
{
	UiRect rc;
	if (rcSource != nullptr) {
		rc = *rcSource;
	}
	return rc;
}

UiRect ImageAttribute::GetDestRect() const
{
	UiRect rc;
	if (rcDest != nullptr) {
		rc = *rcDest;
	}
	return rc;
}

UiPadding ImageAttribute::GetPadding() const
{
	UiPadding rc;
	if (rcPadding != nullptr) {
		rc = UiPadding(rcPadding->left, rcPadding->top, rcPadding->right, rcPadding->bottom);
	}
	return rc;
}

void ImageAttribute::SetPadding(const UiPadding& newPadding)
{
	if (rcPadding == nullptr) {
		rcPadding = new UiPadding16;
	}
	rcPadding->left = TruncateToUInt16(newPadding.left);
	rcPadding->top = TruncateToUInt16(newPadding.top);
	rcPadding->right = TruncateToUInt16(newPadding.right);
	rcPadding->bottom = TruncateToUInt16(newPadding.bottom);
}

UiRect ImageAttribute::GetCorner() const
{
	UiRect rc;
	if (rcCorner != nullptr) {
		rc = *rcCorner;
	}
	return rc;
}

}