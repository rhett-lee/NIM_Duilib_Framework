#ifndef UI_CORE_UIMARGIN_H_
#define UI_CORE_UIMARGIN_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui 
{
/** ��߾�����ݽṹ��װ�����Ǿ��Σ�û�п�ߵĸ��
*   ��߾ࣺMargin�ǲ������ؼ��ľ��������ڵġ�
*/
class UILIB_API UiMargin
{
public:
	UiMargin()
	{
		left = top = right = bottom = 0;
	}
	UiMargin(int32_t nLeft, int32_t nTop, int32_t nRight, int32_t nBottom)
	{
		left = nLeft;
		top = nTop;
		right = nRight;
		bottom = nBottom;
	}
	/** ����
	*/
	void Clear()
	{
		left = top = right = bottom = 0;
	}
	/** �ж��Ƿ�Ϊ��
	*/
	bool IsEmpty() const
	{
		return (left == 0) && (top == 0) && (right == 0) && (bottom == 0);
	}

	/** ������ֵ��Ϊ��Чֵ������ֵ������Ϊ��ֵ����������
	*/
	void Validate()
	{
		if (left < 0) {
			left = 0;
		}
		if (top < 0) {
			top = 0;
		}
		if (right < 0) {
			right = 0;
		}
		if (bottom < 0) {
			bottom = 0;
		}
	}

	/** �ж�������һ���Ƿ���ͬ
	*/
	bool Equals(const UiMargin& r) const
	{
		return left == r.left && top == r.top &&
			   right == r.right && bottom == r.bottom;
	}

public:
	/** ����������߾�
	*/
	int32_t left;

	/** �����������߾�
	*/
	int32_t top;

	/** �����Ҳ����߾�
	*/
	int32_t right;

	/** �����������߾�
	*/
	int32_t bottom;
};

/** 16λ�޷��ŵİ汾�����ڴ洢����Լ�ռ�
*/
class UILIB_API UiMargin16
{
public:
	UiMargin16()
	{
		left = top = right = bottom = 0;
	}
	UiMargin16(uint16_t nLeft, uint16_t nTop, uint16_t nRight, uint16_t nBottom)
	{
		left = nLeft;
		top = nTop;
		right = nRight;
		bottom = nBottom;
	}
public:
	/** ����������߾�
	*/
	uint16_t left;

	/** �����������߾�
	*/
	uint16_t top;

	/** �����Ҳ����߾�
	*/
	uint16_t right;

	/** �����������߾�
	*/
	uint16_t bottom;
};

} // namespace ui

#endif // UI_CORE_UIMARGIN_H_
