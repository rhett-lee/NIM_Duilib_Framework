#ifndef UI_CORE_UISIZE64_H_
#define UI_CORE_UISIZE64_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui 
{

/** Size64�ķ�װ
*/
class UILIB_API UiSize64
{
public:
	UiSize64()
	{
		cx = cy = 0;
	}

	UiSize64(const UiSize64& src)
	{
		cx = src.cx;
		cy = src.cy;
	}

	UiSize64(int64_t cxValue, int64_t cyValue)
	{
		cx = cxValue;
		cy = cyValue;
	}

	/** �����µĿ�Ⱥ͸߶�
	*/
	void SetWidthHeight(int64_t cxValue, int64_t cyValue)
	{
		cx = cxValue;
		cy = cyValue;
	}

	/** �����µĿ��
	*/
	void SetWidth(int64_t cxValue) { cx = cxValue; }

	/** �����µĸ߶�
	*/
	void SetHeight(int64_t cyValue) { cy = cyValue; }

	/** ���ؿ��
	*/
	constexpr int64_t Width() const { return cx; }

	/** ���ظ߶�
	*/
	constexpr int64_t Height() const { return cy; }

	/** ���cx��cy����0������true
	*/
	bool IsEmpty() const { return cx == 0 && cy == 0; }

	/** cx��cy������Ϊ0
	*/
	void Clear()
	{
		cx = 0;
		cy = 0;
	}

	/** �ж��Ƿ�������һ��Size��ͬ
	*/
	bool Equals(int64_t cxValue, int64_t cyValue) const
	{
		return cx == cxValue && cy == cyValue;
	}

	/** �ж��Ƿ�������һ��Size��ͬ
	*/
	bool Equals(const UiSize64& dst) const
	{
		return cx == dst.cx && cy == dst.cy;
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator == (const UiSize64& a, const UiSize64& b)
	{
		return a.Equals(b);
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator != (const UiSize64& a, const UiSize64& b)
	{
		return !a.Equals(b);
	}

public:
	/** ���
	*/
	int64_t cx;

	/** �߶�
	*/
	int64_t cy;
};

} // namespace ui

#endif // UI_CORE_UISIZE_H_
