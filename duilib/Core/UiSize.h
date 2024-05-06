#ifndef UI_CORE_UISIZE_H_
#define UI_CORE_UISIZE_H_

#pragma once

#include "duilib/Core/UiSize64.h"

namespace ui 
{

/** Size�ķ�װ
*/
class UILIB_API UiSize
{
public:
	UiSize()
	{
		cx = cy = 0;
	}

	UiSize(const UiSize& src)
	{
		cx = src.cx;
		cy = src.cy;
	}

	UiSize(int32_t cxValue, int32_t cyValue)
	{
		cx = cxValue;
		cy = cyValue;
	}

	/** �����µĿ�Ⱥ͸߶�
	*/
	void SetWidthHeight(int32_t cxValue, int32_t cyValue)
	{
		cx = cxValue;
		cy = cyValue;
	}

	/** �����µĿ��
	*/
	void SetWidth(int32_t cxValue) { cx = cxValue; }

	/** �����µĸ߶�
	*/
	void SetHeight(int32_t cyValue) { cy = cyValue; }

	/** ���ؿ��
	*/
	constexpr int32_t Width() const { return cx; }

	/** ���ظ߶�
	*/
	constexpr int32_t Height() const { return cy; }

	/** ����Ⱥ͸߶�ֵ�Ƿ�Ϊ��Чֵ��������
	*/
	void Validate()
	{
		if (cx < 0) {
			cx = 0;
		}
		if (cy < 0) {
			cy = 0;
		}
	}

	/** �߶ȺͿ���Ƿ�Ϊ��Чֵ
	*/
	bool IsValid() const { return cx >= 0 && cy >= 0; }

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
	bool Equals(int32_t cxValue, int32_t cyValue) const
	{
		return cx == cxValue && cy == cyValue;
	}

	/** �ж��Ƿ�������һ��Size��ͬ
	*/
	bool Equals(const UiSize& dst) const
	{
		return cx == dst.cx && cy == dst.cy;
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator == (const UiSize& a, const UiSize& b)
	{
		return a.Equals(b);
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator != (const UiSize& a, const UiSize& b)
	{
		return !a.Equals(b);
	}

public:
    /** ���
    */
    int32_t cx;

    /** �߶�
    */
    int32_t cy;
};

} // namespace ui

#endif // UI_CORE_UISIZE_H_
