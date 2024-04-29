#ifndef UI_CORE_UIPOINT_H_
#define UI_CORE_UIPOINT_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui 
{

/** ��ķ�װ
*/
class UILIB_API UiPoint
{
public:
	UiPoint()
	{
		x = y = 0;
	}

	UiPoint(int32_t xValue, int32_t yValue)
	{
		x = xValue;
		y = yValue;
	}

	/** �����µ�X��Yֵ
	*/
	void SetXY(int32_t xValue, int32_t yValue)
	{
		x = xValue;
		y = yValue;
	}

	/** �����µ�Xֵ
	*/
	void SetX(int32_t xValue) { x = xValue; }

	/** �����µ�Yֵ
	*/
	void SetY(int32_t yValue) { y = yValue;	}

	/** ƫ�Ʋ���
	*/
	void Offset(int32_t offsetX, int32_t offsetY)
	{
		x += offsetX;
		y += offsetY;
	}

	/** ƫ�Ʋ���
	*/
	void Offset(const UiPoint& offsetPoint)
	{
		x += offsetPoint.x;
		y += offsetPoint.y;
	}

	/** ����xֵ
	*/
	constexpr int32_t X() const { return x; }

	/** ����yֵ
	*/
	constexpr int32_t Y() const { return y; }

	/** ���x��y����0������true
	*/
	bool IsZero() const 
	{ 
		return x == 0 && y == 0; 
	}

	/** �ж��Ƿ�������һ������ͬ
	*/
	bool Equals(int32_t xValue, int32_t yValue) const 
	{
		return x == xValue && y == yValue;
	}

	/** �ж��Ƿ�������һ������ͬ
	*/
	bool Equals(const UiPoint& dst) const
	{
		return x == dst.x && y == dst.y;
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator == (const UiPoint& a, const UiPoint& b)
	{
		return a.Equals(b);
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator != (const UiPoint& a, const UiPoint& b)
	{
		return !a.Equals(b);
	}

public:
	/** X������
	*/
	int32_t x;

	/** Y������
	*/
	int32_t y;
};

} // namespace ui

#endif // UI_CORE_UIPOINT_H_
