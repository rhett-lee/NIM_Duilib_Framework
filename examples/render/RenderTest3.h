#pragma once

// duilib
#include "duilib/duilib.h"

namespace ui {

class RenderTest3 : public ui::Control
{
public:
	RenderTest3();
	virtual ~RenderTest3();

public:
	/**
	* @brief ������
	* @param[in] ������
	* @return ������
	*/
	virtual void AlphaPaint(IRender* pRender, const UiRect& rcPaint);

	/**
	* @brief ���ƿؼ�����ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void Paint(IRender* pRender, const UiRect& rcPaint);

	/**
	* @brief ���ƿؼ�������ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void PaintChild(IRender* pRender, const UiRect& rcPaint);

private:
	/** ������ֵ����DPI����Ӧ
	*/
	int DpiScaledInt(int iValue);

	/** ��һ�������ڻ�����������ƴ�ӵ���ɫ��ͼ, ����������������
	*/
	void DrawColorMap(IRender* pRender, const UiRect& rect);

	/** ����һ����������(���ö���ζ���ķ�ʽ����·�����)
	* @param [in] pRender ��Ⱦ�ӿ�
	* @param [in] centerPt �������ε����ĵ�����
	* @param [in] radius �������εİ뾶�����ĵ���붥��ľ��루ͬʱҲ�Ǳ߳���
	* @param [in] penColor ���ʵ���ɫ�����Ϊ0���򲻻��Ʊ߿�
	* @param [in] penWidth ���ʵĿ�ȣ����Ϊ0���򲻻��Ʊ߿�
	* @param [in] brushColor ��ˢ����ɫ�����Ϊ0���������ɫ
	*/
	bool DrawRegularHexagon(IRender* pRender, const UiPointF& centerPt, int32_t radius, 
						    const UiColor& penColor, int32_t penWidth, const UiColor& brushColor);

	/** ����һ����������(������������ת�ķ�ʽ����)
	* @param [in] pRender ��Ⱦ�ӿ�
	* @param [in] centerPt �������ε����ĵ�����
	* @param [in] radius �������εİ뾶�����ĵ���붥��ľ��루ͬʱҲ�Ǳ߳���
	* @param [in] penColor ���ʵ���ɫ�����Ϊ0���򲻻��Ʊ߿�
	* @param [in] penWidth ���ʵĿ�ȣ����Ϊ0���򲻻��Ʊ߿�
	* @param [in] brushColor ��ˢ����ɫ�����Ϊ0���������ɫ
	*/
	bool DrawRegularHexagon3(IRender* pRender, const UiPoint& centerPt, int32_t radius, 
						     const UiColor& penColor, int32_t penWidth, const UiColor& brushColor);

};

} //end of namespace ui
