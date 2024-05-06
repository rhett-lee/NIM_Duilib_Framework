#ifndef UI_RENDER_IRENDER_H_
#define UI_RENDER_IRENDER_H_

#pragma once

#include "base/callback/callback.h"
#include "duilib/Core/UiTypes.h"

namespace ui 
{
/** ����ӿ�
*/
class UILIB_API IFont: public virtual nbase::SupportWeakCallback
{
public:
	/** ��ʼ������(�ڲ�δ�������С��DPI����Ӧ)
 	*/
	virtual bool InitFont(const UiFont& fontInfo) = 0;

	/** ��ȡ������
	*/
	virtual const wchar_t* FontName() const = 0;

	/** ��ȡ�����С(����߶�)
	*/
	virtual int FontSize() const = 0;

	/** �Ƿ�Ϊ����
	*/
	virtual bool IsBold() const = 0;

	/** �����»���״̬
	*/
	virtual bool IsUnderline() const = 0;

	/** �����б��״̬
	*/
	virtual bool IsItalic() const = 0;

	/** �����ɾ����״̬
	*/
	virtual bool IsStrikeOut() const = 0;
};

/** Skia������Ҫ����Alpha����
*/
enum UILIB_API BitmapAlphaType: int
{
	kUnknown_SkAlphaType,	//!< uninitialized
	kOpaque_SkAlphaType,	//!< pixel is opaque
	kPremul_SkAlphaType,	//!< pixel components are premultiplied by alpha
	kUnpremul_SkAlphaType	//!< pixel components are independent of alpha
};

/** λͼ�ӿ�
*/
class UILIB_API IBitmap : public virtual nbase::SupportWeakCallback
{
public:
	/** �����ݳ�ʼ����ARGB��ʽ��
	@param [in] nWidth ���
	@param [in] nHeight �߶�
	@param [in] flipHeight �Ƿ�תλͼ�����Ϊtrue������λͼ��ʱ�������Ͻ�ΪԲ�㣬ͼ�����Ǵ��ϵ��µģ�
	                       ���Ϊfalse���������½�ΪԲ�㣬ͼ�����Ǵ��µ��ϡ�
	@param [in] pPixelBits λͼ����, ���Ϊnullptr��ʾ���ڿ�λͼ�������Ϊnullptr�������ݳ���Ϊ��nWidth*4*nHeight
	@param [in] alphaType λͼ��Alpha���ͣ�ֻ��Skia������Ҫ�˲���
	*/
	virtual bool Init(uint32_t nWidth, uint32_t nHeight, bool flipHeight, 
					  const void* pPixelBits, BitmapAlphaType alphaType = kPremul_SkAlphaType) = 0;

	/** ��ȡͼƬ���
	*/
	virtual uint32_t GetWidth() const = 0;

	/** ��ȡͼƬ�߶�
	*/
	virtual uint32_t GetHeight() const = 0;

	/** ��ȡͼƬ��С
	@return ͼƬ��С
	*/
	virtual UiSize GetSize() const = 0;

	/** ����λͼ���ݣ����ݳ��� = GetWidth() * GetHeight() * 4
	*/
	virtual void* LockPixelBits() = 0;

	/** �ͷ�λͼ����
	*/
	virtual void UnLockPixelBits() = 0;

	/** ��λͼ�Ƿ���͸������(��͸��ͨ���У����в���255������)
	*/
	virtual bool IsAlphaBitmap() const = 0;

	/** ��¡�����µĵ�λͼ
	*@return ���������ɵ�λͼ�ӿڣ��ɵ��÷��ͷ���Դ
	*/
	virtual IBitmap* Clone() = 0;
};

/** ���ʽӿ�
*/
class UILIB_API IPen : public virtual nbase::SupportWeakCallback
{
public:
	/** ���û��ʿ��
	*/
	virtual void SetWidth(int width) = 0;

	/** ��ȡ���ʿ��
	*/
	virtual int GetWidth() const = 0;

	/** ���û�����ɫ
	*/
	virtual void SetColor(UiColor color) = 0;

	/** ��ȡ������ɫ
	*/
	virtual UiColor GetColor() const = 0;

	/** ��ñ��ʽ
	*/
	enum LineCap
	{
		kButt_Cap   = 0,	//ƽ��ñ��Ĭ�ϣ�
		kRound_Cap  = 1,	//Բ��ñ
		kSquare_Cap = 2		//����ñ
	};

	/** �����߶���ʼ�ı�ñ��ʽ
	*/
	virtual void SetStartCap(LineCap cap) = 0;

	/** ��ȡ�߶���ʼ�ı�ñ��ʽ
	*/
	virtual LineCap GetStartCap() const = 0;

	/** �����߶ν����ı�ñ��ʽ
	*/
	virtual void SetEndCap(LineCap cap) = 0;

	/** ��ȡ�߶ν����ı�ñ��ʽ
	*/
	virtual LineCap GetEndCap() const = 0;

	/** ���ö̻��߱�ñ����ʽ
	*/
	virtual void SetDashCap(LineCap cap) = 0;

	/** ��ȡ�̻��߱�ñ����ʽ
	*/
	virtual LineCap GetDashCap() const = 0;

	/** �߶�ĩβʹ�õ�������ʽ�����߶�����һ���߶�����
	*/
	enum LineJoin
	{
		kMiter_Join = 0,	//��ǣ�Ĭ�ϣ�
		kBevel_Join = 1,	//ƽ��
		kRound_Join = 2		//Բ��		
	};

	/** �����߶�ĩβʹ�õ�������ʽ
	*/
	virtual void SetLineJoin(LineJoin join) = 0;

	/** ��ȡ�߶�ĩβʹ�õ�������ʽ
	*/
	virtual LineJoin GetLineJoin() const = 0;

	/** �ʻ��Ƶ�������������ʽ
	*/
	enum DashStyle
	{
		kDashStyleSolid			= 0,	//ʵ�ߣ�Ĭ�ϣ�
		kDashStyleDash			= 1,	//����
		kDashStyleDot			= 2,	//����
		kDashStyleDashDot		= 3,	//��������
		kDashStyleDashDotDot	= 4		//����̻��ߵ����
	};

	/** ���û��Ƶ�������ʽ
	*/
	virtual void SetDashStyle(DashStyle style) = 0;

	/** ��ȡ���Ƶ�������ʽ
	*/
	virtual DashStyle GetDashStyle() const = 0;

	/** ����Pen����
	*/
	virtual IPen* Clone() const = 0;
};

/** ��ˢ�ӿ�
*/
//Ŀǰֻ֧��һ��SolidBrush
class UILIB_API IBrush : public virtual nbase::SupportWeakCallback
{
public:
	virtual IBrush* Clone() = 0;
	virtual UiColor GetColor() const = 0;
};

/** ·���ӿ�
*/
class IMatrix;
class UILIB_API IPath : public virtual nbase::SupportWeakCallback
{
public:	
	/** ������ͣ���·���������ཻʱ�������γɵ�����
	*/
	enum class FillType 
	{
		/** Specifies that "inside" is computed by an odd number of edge crossings
		*/
		kEvenOdd		= 0, //FillModeAlternate

		/** Specifies that "inside" is computed by a non-zero sum of signed edge crossings 
		*/
		kWinding		= 1, //FillModeWinding

		/** Same as EvenOdd, but draws outside of the path, rather than inside 
		*/
		kInverseEvenOdd	= 2,

		/** Same as Winding, but draws outside of the path, rather than inside 
		*/
		kInverseWinding	= 3
	};

	/** �����������
	*/
	virtual void SetFillType(FillType mode) = 0;

	/** ��ȡ�������
	*/
	virtual FillType GetFillType() = 0;

	/** ��һ����ӵ���·���ĵ�ǰͼ��
	* @param [in] x1 �������� x ����
	* @param [in] y1 �������� y ����
	* @param [in] x2 �����յ�� x ����
	* @param [in] y2 �����յ�� y ����
	*/
	virtual void AddLine(int x1, int y1, int x2, int y2) = 0;

	/** ���·���ĵ�ǰͼ���һϵ��������
	* @param [in] points ���������յ�ĵ�����, �����еĵ�һ�����ǵ�һ�е���㣬
	                     �����е����һ���������һ�е��յ㡣 
						 ����ÿ���㶼����һ�е��յ㣬��һ�е���㡣
	* @param [in] count �������е�Ԫ����
	*/
	virtual void AddLines(const UiPoint* points, int count) = 0;

	/** ��������(B��zier)����������ӵ���·���ĵ�ǰͼ��
	*    ���������ɻ���������һ�����ĸ���ָ�������ߣ�
	*    �����˵㣨p1[x1,y1] �� p2[x4,y4]�����������Ƶ㣨c1[x2,y2] �� c2[x3,y3]���� 
	*	 ���ߴ� p1 ��ʼ���� p2 ��β�� 
	*	 ���߲�ͨ�����Ƶ㣬�����Ƶ�䵱����������������ĳ�����򣬲�Ӱ�����ߵ�������ʽ��
	* @param [in] x1 ���� x ����
	* @param [in] y1 ���� y ����
	* @param [in] x2 ��һ�����Ƶ�� x ����
	* @param [in] y2 ��һ�����Ƶ�� y ����
	* @param [in] x3 �ڶ������Ƶ�� x ����
	* @param [in] y3 �ڶ������Ƶ�� y ����
	* @param [in] x4 �յ�� x ����
	* @param [in] y4 �յ�� y ����
	*
	*/
	virtual void AddBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) = 0;

	/** �����ӵ� B��zier ����������ӵ���·���ĵ�ǰͼ��
	* @param [in] points ָ�����ӵ���������ʼ�㡢������Ϳ��Ƶ������ָ�롣 
	*                   ��һ�������ӵ�һ���㵽����ĵ��ĸ��㹹�죬��ʹ�õڶ��͵���������Ϊ���Ƶ㡣 
	*					�����е�ÿ����������ֻ��Ҫ���������㣺
	*					ǰһ���������յ�������㣬�����е����������ǿ��Ƶ㣬�����������յ㡣
	* @param [in] count �����е�Ԫ����
	*/
	virtual void AddBeziers(const UiPoint* points, int count) = 0;

	/** ��������ӵ���·��
	* @param [in] rect ��������
	*/
	virtual void AddRect(const UiRect& rect) = 0;

	/** ����Բ��ӵ���·��
	* @param [in] ��Բ�ľ������� 
	*             left ��Բ�߿����Ͻǵ� x ����
	*             top  ��Բ�߿����Ͻǵ� y ����
	*             right left + ��Բ�߽���εĿ��
	*             bottom top + ��Բ�߽���εĸ߶�
	*/
	virtual void AddEllipse(const UiRect& rect) = 0;

	/** ����Բ����ӵ���·��
	* @param [in] ��Բ�ľ������� 
	* @param [in] startAngle ��Բˮƽ���뻡�����֮���˳ʱ��Ƕȣ��Զ�Ϊ��λ��
	* @param [in] sweepAngle ��� (startAngle) �ͻ����յ�֮���˳ʱ��Ƕȣ��Զ�Ϊ��λ��
	*/
	virtual void AddArc(const UiRect& rect, float startAngle, float sweepAngle) = 0;

	/** ���������ӵ���·��
	* @param [in] points ָ������ζ���ĵ�����
	* @param [in] count �����е�Ԫ����
	*/
	virtual void AddPolygon(const UiPoint* points, int count) = 0;
	virtual void AddPolygon(const UiPointF* points, int count) = 0;

	/** ��·�����о���任�����Խ�����ת�Ȳ���
	* @param [in] pMatrix ����ӿ�
	*/
	virtual void Transform(IMatrix* pMatrix) = 0;

	/** ��ȡ��·���ı߽����
	* @param [in] pen ������Pen���󣬿���Ϊnullptr
	*/
	virtual UiRect GetBounds(const IPen* pen) = 0;

	/** �رյ�ǰ��ͼ
	*/
	virtual void Close() = 0;

	/** ����Path����
	*/
	virtual void Reset() = 0;

	/** ����Path����
	*/
	virtual IPath* Clone() = 0;
};

/** 3x3 ����ӿ�
*/
class UILIB_API IMatrix : public nbase::SupportWeakCallback
{
public:
	/** ƽ�Ʋ���
	* @param [in] offsetX X�᷽��ƽ�Ƶ�ƫ����
	* @param [in] offsetY Y�᷽��ƽ�Ƶ�ƫ����
	*/
	virtual void Translate(int offsetX, int offsetY) = 0;

	/** ���Ų���
	* @param [in] scaleX X�᷽�����ű���
	* @param [in] scaleY Y�᷽�����ű���
	*/
	virtual void Scale(float scaleX, float scaleY) = 0;

	/** ��ת��������Դ������(0,0)Ϊ���ĵ�����ת����
	* @param [in] angle ��ת�ĽǶȣ�����Ϊ˳ʱ�����������Ϊ��ʱ�����
	*/
	virtual void Rotate(float angle) = 0;

	/** ��ת������������(center)Ϊ���ĵ�����ת����
	* @param [in] angle ��ת�ĽǶȣ�����Ϊ˳ʱ�����������Ϊ��ʱ�����
	* @param [in] center ��ת�����ĵ�����ֵ
	*/
	virtual void RotateAt(float angle, const UiPoint& center) = 0;
};

/** ��դ��������
*/
enum class UILIB_API RopMode
{
	kSrcCopy,	//��Ӧ�� SRCCOPY
	kDstInvert, //��Ӧ�� DSTINVERT
	kSrcInvert, //��Ӧ�� SRCINVERT
	kSrcAnd     //��Ӧ�� SRCAND
};

/** �����ı�ʱ�ĸ�ʽ
*/
enum UILIB_API DrawStringFormat
{
	TEXT_SINGLELINE		= DT_SINGLELINE,
	TEXT_LEFT			= DT_LEFT,
	TEXT_CENTER			= DT_CENTER,
	TEXT_RIGHT			= DT_RIGHT,
	TEXT_TOP			= DT_TOP,
	TEXT_VCENTER		= DT_VCENTER,
	TEXT_BOTTOM			= DT_BOTTOM,
	TEXT_END_ELLIPSIS	= DT_END_ELLIPSIS,
	TEXT_PATH_ELLIPSIS  = DT_PATH_ELLIPSIS,
	TEXT_NOCLIP			= DT_NOCLIP,
};

/** Render����
*/
enum class RenderType
{
	kRenderType_Skia = 0,
	kRenderType_GdiPlus = 1
};

/** ��ʽ�ı�����
*/
class RichTextData
{
public:
	/** ��������
	*/
	UiString m_text;

	/** ������ɫ
	*/
	UiColor m_textColor;

	/** ������ɫ
	*/
	UiColor m_bgColor;

	/** ������Ϣ
	*/
	UiFont m_fontInfo;

	/** �м��
	*/
	float m_fRowSpacingMul = 1.0f;

	/** �����������(�������)
	*/
	std::vector<UiRect> m_textRects;
};

/** ��Ⱦ�ӿ�
*/
class UILIB_API IRender : public virtual nbase::SupportWeakCallback
{
public:
	/** ��ȡRenderʵ������
	*/
	virtual RenderType GetRenderType() const = 0;

	/** ��ȡ�������
	*/
	virtual int	GetWidth() = 0;

	/** ��ȡ�����߶�
	*/
	virtual int GetHeight() = 0;

	/** ����������С
	*/
	virtual bool Resize(int width, int height) = 0;

	/** �жϻ����Ƿ�֧��͸��
	*/
	virtual bool IsRenderTransparent() const = 0;

	/** ���û����Ƿ�֧��͸��
	*/
	virtual bool SetRenderTransparent(bool bTransparent) = 0;

	/** ���ô�������ԭ������ƫ�ƣ�
	 *  ��ԭ����ԭ��xֵ����ptOffset.x����Ϊ�µ�����ԭ��x;
	 *  ��ԭ����ԭ��yֵ����ptOffset.y����Ϊ�µ�����ԭ��y;
	 * @param [in] ptOffset ����ԭ������ƫ����
	 *@return ����ԭ��������ԭ������(x,y)
	 */
	virtual UiPoint OffsetWindowOrg(UiPoint ptOffset) = 0;

	/** ����(pt.x, pt.y)ӳ�䵽����ԭ�� (0, 0)
	 *@return ����ԭ��������ԭ������(x,y)
	 */
	virtual UiPoint SetWindowOrg(UiPoint pt) = 0;

	/** ��ȡ����ԭ������(x,y)
	 * @return ���ص�ǰ������ԭ������(x,y)
	 */
	virtual UiPoint GetWindowOrg() const = 0;
	
	/** ����ָ���豸�����ĵĵ�ǰ״̬
	* @param [out] ���ر�����豸�����ı�־����RestoreClip��ʱ����Ϊ��������
	*/
	virtual void SaveClip(int& nState) = 0;

	/** ���豸�����Ļ�ԭ�����һ�α����״̬
	* @param [in] ������豸�����ı�־����SaveClip���أ�
	*/
	virtual void RestoreClip(int nState) = 0;

	/** ���þ��μ������򣬲����浱ǰ�豸�����ĵ�״̬
	* @param [in] rc���������뵱ǰ������ȡ������Ϊ�µļ�������
	* @param [in] bIntersect ClipOp������־��true��ʾkIntersect������false��ʾkDifference����
	*/
	virtual void SetClip(const UiRect& rc, bool bIntersect = true) = 0;

	/** ����Բ�Ǿ��μ������򣬲����浱ǰ�豸�����ĵ�״̬
	* @param [in] rcItem ���������뵱ǰ������ȡ������Ϊ�µļ�������
	* @param [in] width Բ�ǵĿ��
	* @param [in] height Բ�ǵĵĶ�
	* @param [in] bIntersect ClipOp������־��true��ʾkIntersect������false��ʾkDifference����
	*/
	virtual void SetRoundClip(const UiRect& rcItem, int width, int height, bool bIntersect = true) = 0;

	/** ������μ������򣬲��ָ��豸�����ĵ����һ�α����״̬
	*/
	virtual void ClearClip() = 0;

	/** ����ִ�����ָ��Դ�豸�����ĵ�Ŀ���豸�������е����ؾ��ζ�Ӧ����ɫ���ݵ�λ�鴫��
	* @param [in] x Ŀ��������Ͻǵ� x ����
	* @param [in] y Ŀ��������Ͻǵ� y ����
	* @param [in] cx Դ���κ�Ŀ����εĿ��
	* @param [in] cy Դ��Ŀ����εĸ߶�
	* @param [in] pSrcBitmap ԴͼƬ�ӿ�
	* @param [in] pSrcRender ԴRender����
	* @param [in] xSrc Դ�������Ͻǵ� x ����
	* @param [in] ySrc Դ�������Ͻǵ� y ����
	* @param [in] rop ��դ��������
	*/
	virtual bool BitBlt(int x, int y, int cx, int cy, 
		                IBitmap* pSrcBitmap, int xSrc, int ySrc,
		                RopMode rop) = 0;
	virtual bool BitBlt(int x, int y, int cx, int cy, 
		                IRender* pSrcRender, int xSrc, int ySrc,
		                RopMode rop) = 0;

	/** ������һ��λͼ��Դ���θ��Ƶ�Ŀ������У��������ѹ��λͼ����ӦĿ����εĳߴ磨���б�Ҫ���� 
	    ϵͳ���ݵ�ǰ��Ŀ���豸�����������õ�����ģʽ�����ѹ��λͼ��
	* @param [in] xDest Ŀ��������Ͻǵ� x ����
	* @param [in] yDest Ŀ��������Ͻǵ� y ����
	* @param [in] widthDest Ŀ����εĿ��
	* @param [in] heightDest Ŀ����εĸ߶�
	* @param [in] pSrcRender ԴRender����
	* @param [in] xSrc Դ�������Ͻǵ� x ����
	* @param [in] ySrc Դ�������Ͻǵ� y ����
	* @param [in] widthSrc Դ���εĿ��
	* @param [in] heightSrc Դ���εĸ߶�
	* @param [in] rop ��դ��������
	*/
	virtual bool StretchBlt(int xDest, int yDest, int widthDest, int heightDest,
		                    IRender* pSrcRender, int xSrc, int ySrc, int widthSrc, int heightSrc,
		                    RopMode rop) = 0;


	/** ��ʾ����͸�����͸�����ص�λͼ�����Դ���κ�Ŀ����εĴ�С����ͬ���������Դλͼ��ƥ��Ŀ����Ρ�
	* @param [in] xDest Ŀ��������Ͻǵ� x ����
	* @param [in] yDest Ŀ��������Ͻǵ� y ����
	* @param [in] widthDest Ŀ����εĿ��
	* @param [in] heightDest Ŀ����εĸ߶�
	* @param [in] pSrcRender ԴRender����
	* @param [in] xSrc Դ�������Ͻǵ� x ����
	* @param [in] ySrc Դ�������Ͻǵ� y ����
	* @param [in] widthSrc Դ���εĿ��
	* @param [in] heightSrc Դ���εĸ߶�
	* @param [in] alpha ͸���� alpha ֵ��0 - 255��
	*/
	virtual bool AlphaBlend(int xDest, int yDest, int widthDest, int heightDest,
		                    IRender* pSrcRender, int xSrc, int ySrc, int widthSrc, int heightSrc,
		                    uint8_t alpha = 255) = 0;

	/** ����ͼƬ�����þŹ���ʽ����ͼƬ��
	* @param [in] rcPaint ��ǰȫ���ɻ����������ڱ���ǿɻ�������Ļ��ƣ�����߻������ܣ�
	* @param [in] pBitmap ���ڻ��Ƶ�λͼ�ӿ�
	* @param [in] rcDest ���Ƶ�Ŀ������
	* @param [in] rcDestCorners ���Ƶ�Ŀ������ı߽���Ϣ�����ھŹ������
	* @param [in] rcSource ���Ƶ�ԴͼƬ����
	* @param [in] rcSourceCorners ����ԴͼƬ�ı߽���Ϣ�����ھŹ������
	* @param [in] uFade ͸���ȣ�0 - 255��
	* @param [in] xtiled ����ƽ��
	* @param [in] ytiled ����ƽ��
	* @param [in] fullxtiled ���Ϊtrue������ƽ�̻���ʱ��ȷ������������ͼƬ���ò�������xtiledΪtrueʱ��Ч
	* @param [in] fullytiled ���Ϊtrue������ƽ�̻���ʱ��ȷ������������ͼƬ���ò�������ytiledΪtrueʱ��Ч
	* @param [in] nTiledMargin ƽ�̻���ʱ��ͼƬ�ĺ������������ò�������xtiledΪtrue����ytiledΪtrueʱ��Ч
	*/
	virtual void DrawImage(const UiRect& rcPaint, IBitmap* pBitmap, 
						   const UiRect& rcDest, const UiRect& rcDestCorners,
						   const UiRect& rcSource, const UiRect& rcSourceCorners,
						   uint8_t uFade = 255, bool xtiled = false, bool ytiled = false, 
						   bool fullxtiled = true, bool fullytiled = true, int nTiledMargin = 0) = 0;
	/** ����ͼƬ�����þŹ���ʽ����ͼƬ��, ��Բ�ǲ���
	*/
	virtual void DrawImage(const UiRect& rcPaint, IBitmap* pBitmap, 
						   const UiRect& rcDest,  const UiRect& rcSource, 
						   uint8_t uFade = 255, bool xtiled = false, bool ytiled = false, 
						   bool fullxtiled = true, bool fullytiled = true, int nTiledMargin = 0) = 0;

	/** ����ͼƬ
	* @param [in] rcPaint ��ǰȫ���ɻ����������ڱ���ǿɻ�������Ļ��ƣ�����߻������ܣ�
	* @param [in] pBitmap ���ڻ��Ƶ�λͼ�ӿ�
	* @param [in] rcDest ���Ƶ�Ŀ������
	* @param [in] rcSource ���Ƶ�ԴͼƬ����
	* @param [in] uFade ͸���ȣ�0 - 255��
	* @param [in] pMatrix ����ʱ�ı任����ӿ�
	*/
	virtual void DrawImageRect(const UiRect& rcPaint, IBitmap* pBitmap,
						       const UiRect& rcDest, const UiRect& rcSource,
						       uint8_t uFade = 255, IMatrix* pMatrix = nullptr) = 0;

	/** ����ֱ��
	* @param [in] pt1 ��ʼ������
	* @param [in] pt2 ��ֹ������
	* @param [in] penColor ���ʵ���ɫֵ
	* @param [in] nWidth ���ʵĿ��
	*/
	virtual void DrawLine(const UiPoint& pt1, const UiPoint& pt2, UiColor penColor, int32_t nWidth) = 0;

	/** ����ֱ��
	* @param [in] pt1 ��ʼ������
	* @param [in] pt2 ��ֹ������
	* @param [in] penColor ���ʵ���ɫֵ
	* @param [in] nWidth ���ʵĿ��
	*/
	virtual void DrawLine(const UiPointF& pt1, const UiPointF& pt2, UiColor penColor, float fWidth) = 0;

	/** ����ֱ�ߣ�֧�ָ�������
	* @param [in] pt1 ��ʼ������
	* @param [in] pt2 ��ֹ������
	* @param [in] pen ���ʵĽӿ�
	*/
	virtual void DrawLine(const UiPoint& pt1, const UiPoint& pt2, IPen* pen) = 0;

	/** ���ƾ���
	* @param [in] rc ��������
	* @param [in] penColor ���ʵ���ɫֵ
	* @param [in] nWidth ���ʵĿ��
	* @param [in] bLineInRect ���Ϊtrue����ʾȷ�������������ϸ�������rc�����ڲ��������ߵ����ĵ�����rc���߶���ģ��������в��ֳ���rc���η�Χ
	*/
	virtual void DrawRect(const UiRect& rc, UiColor penColor, int32_t nWidth, bool bLineInRect = false) = 0;

	/** ����ɫ������
	* @param [in] rc Ŀ���������
	* @param [in] dwColor ��ɫֵ
	* @param [in] uFade ͸���ȣ�0 - 255��
	*/
	virtual void FillRect(const UiRect& rc, UiColor dwColor, uint8_t uFade = 255) = 0;

	/** ����Բ�Ǿ���
	* @param [in] rc ��������
	* @param [in] roundSize Բ�ǵĿ�͸�
	* @param [in] penColor ���ʵ���ɫֵ
	* @param [in] nWidth ���ʵĿ��
	*/
	virtual void DrawRoundRect(const UiRect& rc, const UiSize& roundSize, UiColor penColor, int nWidth) = 0;

	/** ����ɫ���Բ�Ǿ���
	* @param [in] rc ��������
	* @param [in] roundSize Բ�ǵĿ�͸�
	* @param [in] dwColor ��ɫֵ
	* @param [in] uFade ͸���ȣ�0 - 255��
	*/
	virtual void FillRoundRect(const UiRect& rc, const UiSize& roundSize, UiColor dwColor, uint8_t uFade = 255) = 0;

	/** �������ߣ���Բ��һ���֣�
	* @param [in] rc ����Բ������Բ�ľ��α߽�����
	* @param [in] startAngle  x���뻡���֮��ĽǶ�
	* @param [in] sweepAngle  Բ�������յ�֮��ĽǶȣ�������˳ʱ�뷽�򣬸�������ʱ�뷽��
	* @param [in] useCenter ���Ϊtrue���������Բ�����ĵ㣨��Skia����ʹ�ã�
	* @param [in] pen ���ʵĽӿڣ����û�����ɫ�ͻ��ʿ��
	* @param [in] gradientColor ��ѡ������������ɫ
	* @param [in] gradientRect ��ѡ������������ɫ�ľ����������ã�����gradientColor��Ϊnullptrʱ��Ч
	*/
	virtual void DrawArc(const UiRect& rc, float startAngle, float sweepAngle, bool useCenter, 
						 const IPen* pen, 
		                 UiColor* gradientColor = nullptr, const UiRect* gradientRect = nullptr) = 0;

	/** ����Բ��
	* @param [in] centerPt Բ�������
	* @param [in] radius Բ�İ뾶
	* @param [in] penColor ���ʵ���ɫֵ
	* @param [in] nWidth ���ʵĿ��
	*/
	virtual void DrawCircle(const UiPoint& centerPt, int32_t radius, UiColor penColor, int nWidth) = 0;

	/** ���Բ��
	* @param [in] centerPt Բ�������
	* @param [in] radius Բ�İ뾶
	* @param [in] dwColor ��ɫֵ
	* @param [in] uFade ͸���ȣ�0 - 255��
	*/
	virtual void FillCircle(const UiPoint& centerPt, int32_t radius, UiColor dwColor, uint8_t uFade = 255) = 0;

	/** ����·��
	* @param [in] path ·���Ľӿ�
	* @param [in] pen ����·��ʹ�õĻ���
	*/
	virtual void DrawPath(const IPath* path, const IPen* pen) = 0;

	/** ���·��
	* @param [in] path ·���Ľӿ�
	* @param [in] brush ���·��ʹ�õĻ�ˢ
	*/
	virtual void FillPath(const IPath* path, const IBrush* brush) = 0;

	/** ����ָ���ı��ַ����Ŀ�Ⱥ͸߶�
	* @param [in] strText ��������
	* @param [in] strFontId ���ֵ�����ID������������ȫ������������
	* @param [in] uFormat ���ֵĸ�ʽ���μ� enum DrawStringFormat ���Ͷ���
	* @param [in] width ��ǰ��������ƿ��
	* @return �����ı��ַ����Ŀ�Ⱥ͸߶ȣ��Ծ��α�ʾ���
	*/
	virtual UiRect MeasureString(const std::wstring& strText, 
		                         const std::wstring& strFontId, 
		                         uint32_t uFormat,
		                         int width = DUI_NOSET_VALUE) = 0;
	/** ��������
	* @param [in] ��������
	* @param [in] strText ��������
	* @param [in] dwTextColor ������ɫֵ
	* @param [in] strFontId ���ֵ�����ID������������ȫ������������
	* @param [in] uFormat ���ֵĸ�ʽ���μ� enum DrawStringFormat ���Ͷ���
	* @param [in] uFade ͸���ȣ�0 - 255��
	*/
	virtual void DrawString(const UiRect& rc,
		                    const std::wstring& strText,
		                    UiColor dwTextColor,
		                    const std::wstring& strFontId, 
		                    uint32_t uFormat,
		                    uint8_t uFade = 255) = 0;

	/** ���Ƹ�ʽ�ı�
	* @param [in] ��������
	* @param [in,out] richTextData ��ʽ���������ݣ��������ֻ��Ƶ�����
	* @param [in] uFormat ���ֵĸ�ʽ���μ� enum DrawStringFormat ���Ͷ���
	* @param [in] bMeasureOnly ���Ϊtrue�����������������������򣬲�ִ�����ֻ���
	* @param [in] uFade ͸���ȣ�0 - 255��
	*/
	virtual void DrawRichText(const UiRect& rc,
		                      std::vector<RichTextData>& richTextData,
		                      uint32_t uFormat = 0,
		                      bool bMeasureOnly = false,
		                      uint8_t uFade = 255) = 0;

	/** ��ָ��������Χ������Ӱ����˹ģ��, ֻ֧���ⲿ��Ӱ����֧���ڲ���Ӱ��
	* @param [in] rc ��������
	* @param [in] roundSize ��Ӱ��Բ�ǿ�Ⱥ͸߶�
	* @param [in] cpOffset ������Ӱƫ������offset-x �� offset-y��
	*                      <offset-x> ����ˮƽƫ����������Ǹ�ֵ����Ӱλ�ھ�����ߡ� 
	*                      <offset-y> ���ô�ֱƫ����������Ǹ�ֵ����Ӱλ�ھ������档
	* @param [in] nBlurRadius ģ���뾶��ֵԽ��ģ�����Խ����Ӱ��Խ��Խ��, ���Ϊ0����ʱ��Ӱ��Ե��������ģ��Ч��������Ϊ��ֵ��
	* @param [in] nSpreadRadius ��չ�뾶����ģ���������rc���α�Ե���ٸ����ء�
	*                           ȡ��ֵʱ����Ӱ����ȡ��ֵʱ����Ӱ������
	* @param [in] dwColor ��Ӱ����ɫֵ
	*/
	virtual void DrawBoxShadow(const UiRect& rc, 
		                       const UiSize& roundSize, 
		                       const UiPoint& cpOffset, 
		                       int nBlurRadius, 
		                       int nSpreadRadius,
		                       UiColor dwColor) = 0;


	/** ����λͼ
	*@return ����λͼ�ӿڣ����غ��ɵ��÷�������Դ�������ͷ���Դ�ȣ�
	*/
	virtual IBitmap* DetachBitmap() = 0;

	/** �����������ڵ�ͼ��Alpha�趨Ϊָ��ֵalpha(0 - 255)
	* @param [in] rcDirty ��������
	* @param [in] alpha ��Ҫ�趨��Aplpaֵ
	*/
	virtual void ClearAlpha(const UiRect& rcDirty, uint8_t alpha = 0) = 0;

	/** �ָ����������ڵ�ͼ��AlphaֵΪalpha(0 - 255)
	* @param [in] rcDirty ��������
	* @param [in] rcShadowPadding ��Ӱ�߾ࣨ�ֱ��Ӧ���ε���/��/��/�±߾��Paddingֵ��
	* @param [in] alpha ��Ҫ�ָ���Alphaֵ����Ҫ��ClearAlphaʱ�����alphaֵ��ͬ��
	*/
	virtual void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding, uint8_t alpha) = 0;

	/** �ָ����������ڵ�ͼ��AlphaֵΪ255
	* @param [in] rcDirty ��������
	* @param [in] rcShadowPadding ��Ӱ�߾ࣨ�ֱ��Ӧ���ε���/��/��/�±߾��Paddingֵ��
	*/
	virtual void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding = UiPadding()) = 0;

#ifdef UILIB_IMPL_WINSDK
	/** ��ȡDC���������ʹ�ú���Ҫ����ReleaseDC�ӿ��ͷ���Դ
	*/
	virtual HDC GetDC() = 0;

	/** �ͷ�DC��Դ
	* @param [in] hdc ��Ҫ�ͷŵ�DC���
	*/
	virtual void ReleaseDC(HDC hdc) = 0;
#endif

public:

	/** ���λͼ���ݣ�ʹ����ȫ͸��λͼ��λͼ����ȫ�����㣩
	*/
	virtual void Clear() = 0;

	/** ��¡һ���µĶ���
	*/
	virtual std::unique_ptr<IRender> Clone() = 0;
};

/** ��Ⱦ�ӿڹ������ڴ���Font��Pen��Brush��Path��Matrix��Bitmap��Render����Ⱦʵ�ֶ���
*/
class UILIB_API IRenderFactory
{
public:
	virtual ~IRenderFactory() = default;

	/** ����һ��Font����
	*/
	virtual IFont* CreateIFont() = 0;

	/** ����һ��Pen����
	*/
	virtual IPen* CreatePen(UiColor color, int width = 1) = 0;

	/** ����һ��Brush����
	*/
	virtual IBrush* CreateBrush(UiColor corlor) = 0;

	/** ����һ��Path����
	*/
	virtual IPath* CreatePath() = 0;

	/** ����һ��Matrix����
	*/
	virtual IMatrix* CreateMatrix() = 0;

	/** ����һ��Bitmap����
	*/
	virtual IBitmap* CreateBitmap() = 0;

	/** ����һ��Render����
	*/
	virtual IRender* CreateRender() = 0;
};

} // namespace ui

#endif // UI_RENDER_IRENDER_H_
