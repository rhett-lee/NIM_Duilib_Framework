#ifndef UI_CORE_UIPOINTF_H_
#define UI_CORE_UIPOINTF_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui 
{

/** ��ķ�װ
*/
class UILIB_API UiPointF
{
public:
	UiPointF()
	{
		x = y = 0;
	}

	UiPointF(float xValue, float yValue)
	{
		x = xValue;
		y = yValue;
	}

	/** �����µ�X��Yֵ
	*/
	void SetXY(float xValue, float yValue)
	{
		x = xValue;
		y = yValue;
	}

	/** �����µ�Xֵ
	*/
	void SetX(float xValue) { x = xValue; }

	/** �����µ�Yֵ
	*/
	void SetY(float yValue) { y = yValue;	}

	/** ƫ�Ʋ���
	*/
	void Offset(float offsetX, float offsetY)
	{
		x += offsetX;
		y += offsetY;
	}

	/** ƫ�Ʋ���
	*/
	void Offset(const UiPointF& offsetPoint)
	{
		x += offsetPoint.x;
		y += offsetPoint.y;
	}

	/** ����xֵ
	*/
	constexpr float X() const { return x; }

	/** ����yֵ
	*/
	constexpr float Y() const { return y; }

	/** ���x��y����0������true
	*/
	bool IsZero() const 
	{ 
		return x == 0 && y == 0; 
	}

	/** �ж��Ƿ�������һ������ͬ
	*/
	bool Equals(float xValue, float yValue) const
	{
		return x == xValue && y == yValue;
	}

	/** �ж��Ƿ�������һ������ͬ
	*/
	bool Equals(const UiPointF& dst) const
	{
		return x == dst.x && y == dst.y;
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator == (const UiPointF& a, const UiPointF& b)
	{
		return a.Equals(b);
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator != (const UiPointF& a, const UiPointF& b)
	{
		return !a.Equals(b);
	}

public:
	/** X������
	*/
	float x;

	/** Y������
	*/
	float y;
};

} // namespace ui

#endif // UI_CORE_UIPOINTF_H_
