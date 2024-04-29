#ifndef UI_RENDER_BITMAP_ALPHA_H_
#define UI_RENDER_BITMAP_ALPHA_H_

#pragma once

#include "duilib/Core/UiRect.h"

namespace ui
{

/** ��λͼ���ݵ�Alphaֵ���б���ͻָ�
*/
class BitmapAlpha
{
public:
	BitmapAlpha(uint8_t* pPiexl, int32_t nWidth, int32_t nHeight, int32_t nChannels);
	~BitmapAlpha();

public:
	void ClearAlpha(const UiRect& rcDirty, uint8_t alpha) const;
	void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding, uint8_t alpha) const;
	void RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding) const;

private:
	/** ͼ������
	*/
	uint8_t* m_pPiexl;

	/** ͼ����
	*/
	int32_t m_nWidth;

	/** ͼ��߶�
	*/
	int32_t m_nHeight;

	/** ͨ������Ŀǰֻ֧��4��ARGB��
	*/
	int32_t m_nChannels;
};
} // namespace ui

#endif // UI_RENDER_BITMAP_ALPHA_H_