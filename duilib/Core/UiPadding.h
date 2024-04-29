#ifndef UI_CORE_UIPADDING_H_
#define UI_CORE_UIPADDING_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui 
{
/** �ڱ߾�����ݽṹ��װ�����Ǿ��Σ�û�п�ߵĸ��
*   �ڱ߾ࣺPadding�ǰ����ؼ��ľ��������ڵ�;
    �ڱ߾������ǲ���(Layout)���ԣ�ֻ��Box�����������в������Ե��������ڱ߾����ԣ�Control����û���ڱ߾�����
*/
class UILIB_API UiPadding
{
public:
	UiPadding()
	{
		left = top = right = bottom = 0;
	}
	UiPadding(int32_t nLeft, int32_t nTop, int32_t nRight, int32_t nBottom)
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
	bool Equals(const UiPadding& r) const
	{
		return left == r.left && top == r.top &&
			   right == r.right && bottom == r.bottom;
	}

public:
	/** ���������ڱ߾�
	*/
	int32_t left;

	/** ����������ڱ߾�
	*/
	int32_t top;

	/** �����Ҳ���ڱ߾�
	*/
	int32_t right;

	/** ����������ڱ߾�
	*/
	int32_t bottom;
};

/** 16λ�޷��ŵİ汾�����ڴ洢����Լ�ռ�
*/
class UILIB_API UiPadding16
{
public:
	UiPadding16()
	{
		left = top = right = bottom = 0;
	}
	UiPadding16(uint16_t nLeft, uint16_t nTop, uint16_t nRight, uint16_t nBottom)
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

#endif // UI_CORE_UIPADDING_H_
