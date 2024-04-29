#ifndef UI_RENDER_GDIPLUS_RENDER_H_
#define UI_RENDER_GDIPLUS_RENDER_H_

#pragma once

#include "duilib/Render/IRender.h"

namespace ui 
{

class UILIB_API Render_GdiPlus : public IRender
{
public:
	Render_GdiPlus();
	virtual ~Render_GdiPlus();

	/** ��ȡRenderʵ������
	*/
	virtual RenderType GetRenderType() const override;

	virtual bool Resize(int width, int height) override;
	virtual void Clear() override;
	virtual std::unique_ptr<IRender> Clone() override;

	/** ����λͼ
	*@return ����λͼ�ӿڣ����غ��ɵ��÷�������Դ�������ͷ���Դ�ȣ�
	*/
	virtual IBitmap* DetachBitmap();

	virtual int	GetWidth() override;
	virtual int GetHeight() override;
	virtual void ClearAlpha(const UiRect& rcDirty, uint8_t alpha = 0) override;
	virtual void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding, uint8_t alpha) override;
	virtual void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding = UiPadding()) override;

	virtual bool IsRenderTransparent() const override;
	virtual bool SetRenderTransparent(bool bTransparent) override;

	virtual UiPoint OffsetWindowOrg(UiPoint ptOffset) override;
	virtual UiPoint SetWindowOrg(UiPoint ptOffset) override;
	virtual UiPoint GetWindowOrg() const override;

	virtual void SaveClip(int& nState) override;
	virtual void RestoreClip(int nState) override;
	virtual void SetClip(const UiRect& rc, bool bIntersect = true) override;
	virtual void SetRoundClip(const UiRect& rc, int width, int height, bool bIntersect = true) override;
	virtual void ClearClip() override;

	virtual bool BitBlt(int x, int y, int cx, int cy, IBitmap* pSrcBitmap, int xSrc, int ySrc, RopMode rop) override;
	virtual bool BitBlt(int x, int y, int cx, int cy, IRender* pSrcRender, int xSrc, int ySrc, RopMode rop) override;
	virtual bool StretchBlt(int xDest, int yDest, int widthDest, int heightDest, IRender* pSrcRender, int xSrc, int ySrc, int widthSrc, int heightSrc, RopMode rop) override;
	virtual bool AlphaBlend(int xDest, int yDest, int widthDest, int heightDest, IRender* pSrcRender, int xSrc, int ySrc, int widthSrc, int heightSrc, uint8_t alpha = 255) override;

	virtual void DrawImage(const UiRect& rcPaint, IBitmap* pBitmap, 
						   const UiRect& rcDest, const UiRect& rcDestCorners,
						   const UiRect& rcSource, const UiRect& rcSourceCorners,
						   uint8_t uFade = 255, bool xtiled = false, bool ytiled = false, 
						   bool fullxtiled = true,  bool fullytiled = true, int nTiledMargin = 0) override;
	virtual void DrawImage(const UiRect& rcPaint, IBitmap* pBitmap, 
						   const UiRect& rcDest,  const UiRect& rcSource, 
						   uint8_t uFade = 255, bool xtiled = false, bool ytiled = false, 
						   bool fullxtiled = true, bool fullytiled = true, int nTiledMargin = 0) override;
	virtual void DrawImageRect(const UiRect& rcPaint, IBitmap* pBitmap,
						       const UiRect& rcDest, const UiRect& rcSource,
						       uint8_t uFade = 255, IMatrix* pMatrix = nullptr);

	virtual void DrawLine(const UiPoint& pt1, const UiPoint& pt2, UiColor penColor, int32_t nWidth) override;
	virtual void DrawLine(const UiPointF& pt1, const UiPointF& pt2, UiColor penColor, float fWidth) override;
	virtual void DrawLine(const UiPoint& pt1, const UiPoint& pt2, IPen* pen) override;

	virtual void DrawRect(const UiRect& rc, UiColor penColor, int32_t nWidth, bool bLineInRect = false) override;
	virtual void FillRect(const UiRect& rc, UiColor dwColor, uint8_t uFade = 255) override;

	virtual void DrawRoundRect(const UiRect& rc, const UiSize& roundSize, UiColor penColor, int nWidth) override;
	virtual void FillRoundRect(const UiRect& rc, const UiSize& roundSize, UiColor dwColor, uint8_t uFade = 255) override;

	virtual void DrawCircle(const UiPoint& centerPt, int32_t radius, UiColor penColor, int nWidth) override;
	virtual void FillCircle(const UiPoint& centerPt, int32_t radius, UiColor dwColor, uint8_t uFade = 255) override;

	virtual void DrawArc(const UiRect& rc, float startAngle, float sweepAngle, bool useCenter, 
						 const IPen* pen, 
		                 UiColor* gradientColor = nullptr, const UiRect* gradientRect = nullptr) override;

	virtual void DrawPath(const IPath* path, const IPen* pen) override;
	virtual void FillPath(const IPath* path, const IBrush* brush) override;

	virtual UiRect MeasureString(const std::wstring& strText,
		                         const std::wstring& strFontId, 
								 uint32_t uFormat, int width = DUI_NOSET_VALUE) override;


	virtual void DrawString(const UiRect& rc, const std::wstring& strText,
		                    UiColor dwTextColor, const std::wstring& strFontId, 
							uint32_t uFormat, uint8_t uFade = 255) override;


	virtual void DrawRichText(const UiRect& rc,
		                      std::vector<RichTextData>& richTextData,
		                      uint32_t uFormat = 0,
		                      bool bMeasureOnly = false,
		                      uint8_t uFade = 255) override;

	//�������Gdiplus�汾��ʵ�ֲ�̫�ԣ��Ƽ�ʹ��Skia�汾�ġ�
	void DrawBoxShadow(const UiRect& rc, const UiSize& roundSize, const UiPoint& cpOffset, int nBlurRadius, int nSpreadRadius, UiColor dwColor) override;

#ifdef UILIB_IMPL_WINSDK
	/** ��ȡDC���������ʹ�ú���Ҫ����ReleaseDC�ӿ��ͷ���Դ
	*/
	virtual HDC GetDC() override;

	/** �ͷ�DC��Դ
	* @param [in] hdc ��Ҫ�ͷŵ�DC���
	*/
	virtual void ReleaseDC(HDC hdc) override;
#endif

private:
	/** ��ȡGDI�Ĺ�դ��������
	*/
	DWORD GetRopMode(RopMode rop) const;

private:
	/** DC���
	*/
	HDC m_hDC;

	/** �����DC��״̬
	*/
	int m_saveDC;

	/** �Ƿ�ָ��Ϊ֧��͸��
	*/
	bool m_bTransparent;

	/** DCԭ��������λͼ���
	*/
	HBITMAP m_hOldBitmap;

	/** Render���õ�λͼ
	*/
	HBITMAP	m_hBitmap;

	/** Render���õ�λͼ����
	*/
	BYTE* m_pPiexl;

	/** Render���õ�λͼ���
	*/
	int m_nWidth;

	/** Render���õ�λͼ�߶�
	*/
	int m_nHeight;
};

} // namespace ui

#endif // UI_RENDER_GDIPLUS_RENDER_H_
