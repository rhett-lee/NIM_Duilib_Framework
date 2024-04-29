#ifndef UI_CORE_UIRECT_H_
#define UI_CORE_UIRECT_H_

#pragma once

#include "duilib/Core/UiPoint.h"
#include "duilib/Core/UiSize.h"
#include "duilib/Core/UiPadding.h"
#include "duilib/Core/UiMargin.h"
#include <algorithm>

namespace ui 
{
/** ��������ķ�װ
*/
class UILIB_API UiRect
{
public:
	UiRect()
	{
		left = top = right = bottom = 0;
	}

	UiRect(int32_t nLeft, int32_t nTop, int32_t nRight, int32_t nBottom)
	{
		left = nLeft;
		top = nTop;
		right = nRight;
		bottom = nBottom;
	}

	/** ��ȡleftֵ
	*/
	constexpr int32_t Left() const { return left; }

	/** ��ȡrightֵ
	*/
	constexpr int32_t Right() const { return right; }

	/** ��ȡtopֵ
	*/
	constexpr int32_t Top() const { return top; }

	/** ��ȡbottomֵ
	*/
	constexpr int32_t Bottom() const { return bottom; }

	/** ��ȡ���
	*/
	int32_t Width() const { return right - left; }

	/** ��ȡ�߶�
	*/
	int32_t Height() const { return bottom - top; }

	/** ��ȡ���ĵ��X������ֵ
	*/
	int32_t CenterX() const { return (left + right) / 2; }

	/** ��ȡ���ĵ��Y������ֵ
	*/
	int32_t CenterY() const { return (top + bottom) / 2; }

	/** ��ȡ�������ĵ����꣨X�������Y�����꣩
	*/
	UiPoint Center() const { return { CenterX(), CenterY() }; }

	/** ����
	*/
	void Clear()
	{
		left = top = right = bottom = 0;
	}

	/** �ж��Ƿ�ȫΪ��
	*/
	bool IsZero() const
	{
		return (left == 0) && (right == 0) && (top == 0) && (bottom == 0);
	}

	/** �ж��Ƿ�Ϊ�յľ��Σ���͸߲�����Чֵ��
	*/
	bool IsEmpty() const
	{
		int32_t w = Width();
		int32_t h = Height();
		return (w <= 0 || h <= 0);
	}

	/** ����Ⱥ͸߶�ֵ�Ƿ�Ϊ��Чֵ��������
	*/
	void Validate()
	{
		if (right < left) {
			right = left;
		}
		if (bottom < top) {
			bottom = top;
		}
	}

	/** ƫ�Ʋ���
	*/
	void Offset(int32_t cx, int32_t cy)
	{
		left += cx;
		right += cx;
		top += cy;
		bottom += cy;
	}

	/** ƫ�Ʋ���
	*/
	void Offset(const UiPoint& offset)
	{
		left += offset.X();
		right += offset.X();
		top += offset.Y();
		bottom += offset.Y();
	}

	/** ʹ�����������󣨿������2*dx���߶�����2*dy��
	*/
	void Inflate(int32_t dx, int32_t dy)
	{
		left -= dx;
		right += dx;
		top -= dy;
		bottom += dy;
	}

	/** ʹ������������
	* @param [in] margin ��߾���ı߲���
	*/
	void Inflate(const UiMargin& margin)
	{
		left -= margin.left;
		right += margin.right;
		top -= margin.top;
		bottom += margin.bottom;
	}

	/** ʹ������������
	* @param [in] padding �ڱ߾���ı߲���
	*/
	void Inflate(const UiPadding& padding)
	{
		left -= padding.left;
		right += padding.right;
		top -= padding.top;
		bottom += padding.bottom;
	}

	/** ʹ������������
	* @param nLeft left����ֵ
	* @param nTop top����ֵ
	* @param nRight right����ֵ
	* @param nBottom bottom����ֵ
	*/
	void Inflate(int32_t nLeft, int32_t nTop, int32_t nRight, int32_t nBottom)
	{
		left -= nLeft;
		right += nRight;
		top -= nTop;
		bottom += nBottom;
	}

	/** ʹ����������С����ȼ���2*dx���߶ȼ���2*dy��
	*/
	void Deflate(int32_t dx, int32_t dy)
	{
		left += dx;
		right -= dx;
		top += dy;
		bottom -= dy;
	}

	/** ʹ����������С
	* @param padding �ڱ߾���ı߲���
	*/
	void Deflate(const UiPadding& padding)
	{
		left += padding.left;
		right -= padding.right;
		top += padding.top;
		bottom -= padding.bottom;
	}

	/** ʹ����������С
	* @param margin ��߾���ı߲���
	*/
	void Deflate(const UiMargin& margin)
	{
		left += margin.left;
		right -= margin.right;
		top += margin.top;
		bottom -= margin.bottom;
	}

	/** ʹ����������С
	* @param nLeft left��Сֵ
	* @param nTop top��Сֵ
	* @param nRight right��Сֵ
	* @param nBottom bottom��Сֵ
	*/
	void Deflate(int32_t nLeft, int32_t nTop, int32_t nRight, int32_t nBottom)
	{
		left += nLeft;
		right -= nRight;
		top += nTop;
		bottom -= nBottom;
	}

	/** ȡ�������εĲ���
	* @param [in] r ����һ������
	* @return ����������ǿվ��Σ�����true����������ǿվ����򷵻�false
	*/
	bool Union(const UiRect& r)
	{
		if (r.left >= r.right || r.top >= r.bottom) {
			//r�ǿվ���
			return !IsEmpty();
		}
		if (left >= right || top >= bottom) {
			//�Լ��ǿվ���
			*this = r;
		}
		else {
			//���������ǿվ���
			left   = (std::min)(left, r.left);
			top    = (std::min)(top, r.top);
			right  = (std::max)(right, r.right);
			bottom = (std::max)(bottom, r.bottom);
		}
		return !IsEmpty();
	}

	/** ȡ�������εĽ���
	* @param [in] r ����һ������
	* @return ����������ǿվ��Σ�����true����������ǿվ����򷵻�false
	*/
	bool Intersect(const UiRect& r)
	{
		left = (std::max)(left, r.Left());
		top = (std::max)(top, r.Top());
		right = (std::min)(right, r.Right());
		bottom = (std::min)(bottom, r.Bottom());
		return !IsEmpty();
	}

	/** ȡ��������(a,b)�Ľ���, ����������һ���µľ���c
	* @return �������c���ǿվ��Σ�����true���������c�ǿվ����򷵻�false
	*/
	static bool Intersect(UiRect& c,const UiRect& a, const UiRect& b)
	{
		c.left = (std::max)(a.Left(), b.Left());
		c.top = (std::max)(a.Top(), b.Top());
		c.right = (std::min)(a.Right(), b.Right());
		c.bottom = (std::min)(a.Bottom(), b.Bottom());
		return !c.IsEmpty();
	}

	/** �ж�һ�����Ƿ��ھ�������
	*/
	bool ContainsPt(const UiPoint& pt) const
	{
		return pt.X() >= left && pt.X() < right && pt.Y() >= top && pt.Y() < bottom;
	}

	/** �ж�һ�����Ƿ��ھ�������
	*/
	bool ContainsPt(int32_t x, int32_t y) const
	{
		return x >= left && x < right && y >= top && y < bottom;
	}

	/** �ж��Ƿ��������һ������
	*/
	bool ContainsRect(const UiRect& r) const
	{
		return  !r.IsEmpty() && !this->IsEmpty() &&
			    left <= r.left && top <= r.top   &&
			    right >= r.right && bottom >= r.bottom;
	}

	/** �ж�������һ�������Ƿ���ͬ
	*/
	bool Equals(const UiRect& r) const
	{
		return left == r.left && top == r.top &&
			   right == r.right && bottom == r.bottom;
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator == (const UiRect& a, const UiRect& b)
	{
		return a.Equals(b);
	}

	/** �ж�����ֵ�Ƿ����
	*/
	friend bool operator != (const UiRect& a, const UiRect& b)
	{
		return !a.Equals(b);
	}

public:
	/** ���Ͻ�X�������
	*/
	int32_t left;

	/** ���Ͻ�Y�������
	*/
	int32_t top;

	/** ���½�X�������
	*/
	int32_t right;

	/** ���½�Y�������
	*/
	int32_t bottom;
};

} // namespace ui

#endif // UI_CORE_UIPOINT_H_
