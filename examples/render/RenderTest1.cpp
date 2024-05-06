#include "RenderTest1.h"
#include "duilib/RenderGdiPlus/BitmapHelper.h"

namespace ui {

RenderTest1::RenderTest1()
{

}

RenderTest1::~RenderTest1()
{

}

void RenderTest1::AlphaPaint(IRender* pRender, const UiRect& rcPaint)
{
    __super::AlphaPaint(pRender, rcPaint);
}

void RenderTest1::Paint(IRender* pRender, const UiRect& rcPaint)
{
    __super::Paint(pRender, rcPaint);
    int marginLeft = 8;
    int marginTop = 4;
    GlobalManager::Instance().Dpi().ScaleInt(marginLeft);
    GlobalManager::Instance().Dpi().ScaleInt(marginTop);

    UiRect rect = GetRect();
    UiRect textRect = rect;
    rect.left += marginLeft;
    rect.top += marginTop;

    int nSize = 110;
    int nTextLineHeight = 40;
    GlobalManager::Instance().Dpi().ScaleInt(nSize);
    GlobalManager::Instance().Dpi().ScaleInt(nTextLineHeight);

    rect.right = rect.left + nSize;
    rect.bottom = rect.top + nSize;
    int currentBottom = rect.bottom;//��¼��ǰ��bottomֵ
    
    //��ͼ��ͬ�ӿ�
    Image image;
    image.SetImageString(L"autumn.png");
    LoadImageData(image);
    rect.right = rect.left + image.GetImageCache()->GetWidth();
    rect.bottom = rect.top + image.GetImageCache()->GetHeight();

    UiRect rcImageSource(0, 0, image.GetImageCache()->GetWidth(), image.GetImageCache()->GetHeight());
    pRender->DrawImage(rcPaint, image.GetCurrentBitmap(), rect, UiRect(), rcImageSource, UiRect());

    //��͸������ͼƬ
    rect.left = rect.right + marginLeft;
    rect.right = rect.left + image.GetImageCache()->GetWidth();
    pRender->DrawImage(rcPaint, image.GetCurrentBitmap(), rect, UiRect(), rcImageSource, UiRect(), 100);

    //��С����
    rect.left = rect.right + marginLeft;
    rect.right = rect.left + image.GetImageCache()->GetWidth() / 2;
    rect.bottom = rect.top + image.GetImageCache()->GetHeight() / 2;
    pRender->DrawImage(rcPaint, image.GetCurrentBitmap(), rect, UiRect(), rcImageSource, UiRect());

    //BitBlt/StretchBlt/AlphaBlend�������ƺ���
    IRender* pSrcRender = BitmapHelper::CreateRenderObject(image.GetCurrentBitmap());
    ASSERT(pSrcRender != nullptr);

    rect.left = rect.right + marginLeft;
    rect.right = rect.left + image.GetImageCache()->GetWidth();
    rect.bottom = rect.top + image.GetImageCache()->GetHeight();
    pRender->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), pSrcRender, 0, 0, RopMode::kSrcCopy);

    rect.left = rect.right + marginLeft;
    rect.right = rect.left + image.GetImageCache()->GetWidth() / 2;
    rect.bottom = rect.top + image.GetImageCache()->GetHeight() / 2;
    pRender->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(), pSrcRender, 0, 0, pSrcRender->GetWidth(), pSrcRender->GetHeight(), RopMode::kSrcCopy);

    rect.left = rect.right + marginLeft;
    rect.right = rect.left + image.GetImageCache()->GetWidth() ;
    rect.bottom = rect.top + image.GetImageCache()->GetHeight() ;
    pRender->AlphaBlend(rect.left, rect.top, rect.Width() , rect.Height() , pSrcRender, 0, 0, pSrcRender->GetWidth(), pSrcRender->GetHeight(), 96);

    delete pSrcRender;
    pSrcRender = nullptr;

    currentBottom = rect.bottom;//��¼��ǰ��bottomֵ

    //����
    rect = GetRect();
    rect.left += marginLeft;
    rect.top = currentBottom + marginTop;

    //ƽ�̻���
    rect.right = rcPaint.right;
    rect.bottom = rcPaint.bottom;

    bool xtiled = true;
    bool ytiled = true;
    bool fullxtiled = false;
    bool fullytiled = false;//����ƽ�̣�����ؼ�������������ͼƬ���Ͳ�����ơ����Ϊfalse����ֻҪ�пռ�ͻ��ƣ�����ʱͼƬֻ�ǻ���һ���ֵġ�
    int nTiledMargin = 0;
    UiRect rcCorners(48, 48, 48, 48);
    pRender->DrawImage(rcPaint, image.GetCurrentBitmap(), rect, rcCorners, rcImageSource, rcCorners, 255, xtiled, ytiled, fullxtiled, fullytiled, nTiledMargin);
}

void RenderTest1::PaintChild(IRender* pRender, const UiRect& rcPaint)
{
    __super::PaintChild(pRender, rcPaint);
}

} //end of namespace ui