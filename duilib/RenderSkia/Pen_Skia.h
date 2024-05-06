#ifndef UI_RENDER_SKIA_PEN_H_
#define UI_RENDER_SKIA_PEN_H_

#pragma once

#include "duilib/Render/IRender.h"

namespace ui 
{

class UILIB_API Pen_Skia : public IPen
{
public:
	explicit Pen_Skia(UiColor color, int width = 1);
	Pen_Skia(const Pen_Skia& r);
	Pen_Skia& operator=(const Pen_Skia& r) = delete;

	/** ���û��ʿ��
	*/
	virtual void SetWidth(int width) override;

	/** ��ȡ���ʿ��
	*/
	virtual int GetWidth() const override;

	/** ���û�����ɫ
	*/
	virtual void SetColor(UiColor color) override;

	/** ��ȡ������ɫ
	*/
	virtual UiColor GetColor() const override;

	/** �����߶���ʼ�ı�ñ��ʽ
	*/
	virtual void SetStartCap(LineCap cap) override;

	/** ��ȡ�߶���ʼ�ı�ñ��ʽ
	*/
	virtual LineCap GetStartCap() const override;

	/** �����߶ν����ı�ñ��ʽ
	*/
	virtual void SetEndCap(LineCap cap) override;

	/** ��ȡ�߶ν����ı�ñ��ʽ
	*/
	virtual LineCap GetEndCap() const override;

	/** ���ö̻��߱�ñ����ʽ
	*/
	virtual void SetDashCap(LineCap cap) override;

	/** ��ȡ�̻��߱�ñ����ʽ
	*/
	virtual LineCap GetDashCap() const override;

	/** �����߶�ĩβʹ�õ�������ʽ
	*/
	virtual void SetLineJoin(LineJoin join) override;

	/** ��ȡ�߶�ĩβʹ�õ�������ʽ
	*/
	virtual LineJoin GetLineJoin() const override;

	/** ���û��Ƶ�������ʽ
	*/
	virtual void SetDashStyle(DashStyle style) override;

	/** ��ȡ���Ƶ�������ʽ
	*/
	virtual DashStyle GetDashStyle() const override;

	/** ����Pen����
	*/
	virtual IPen* Clone() const override;

private:
	/** ������ɫ
	*/
	UiColor m_color;

	/** ���ʿ��
	*/
	int m_width;

	/** �߶���ʼ��ñ��״
	*/
	LineCap m_startCap;

	/** �̻��߱�ñ��״
	*/
	LineCap m_dashCap;

	/** �߶ν�����ñ��״
	*/
	LineCap m_endCap;

	/** �߶�ĩβʹ�õ�������ʽ�����߶�����һ���߶�����
	*/
	LineJoin m_lineJoin;

	/** �̻�����ʽ
	*/
	DashStyle m_dashStyle;
};

} // namespace ui

#endif // UI_RENDER_SKIA_PEN_H_
