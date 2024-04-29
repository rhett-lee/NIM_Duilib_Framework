 #include "BitmapAlpha.h"

namespace ui
{

BitmapAlpha::BitmapAlpha(uint8_t* pPiexl, int32_t nWidth, int32_t nHeight, int32_t nChannels):
	m_pPiexl(pPiexl),
	m_nWidth(nWidth),
	m_nHeight(nHeight),
	m_nChannels(nChannels)
{
	ASSERT(nChannels == 4);
	ASSERT(nWidth > 0);
	ASSERT(nHeight > 0);
	ASSERT(pPiexl != nullptr);
}

BitmapAlpha::~BitmapAlpha()
{
}

void BitmapAlpha::ClearAlpha(const UiRect& rcDirty, uint8_t alpha) const
{
	ASSERT((m_pPiexl != nullptr) && (m_nChannels == 4) && (m_nWidth > 0) && (m_nHeight > 0));
	if ((m_pPiexl == nullptr) || (m_nChannels != 4) || (m_nWidth <= 0) ||(m_nHeight <= 0)){
		return;
	}

	unsigned int * pBmpBits = (unsigned int *)m_pPiexl;
	int nTop = std::max((int)rcDirty.top, 0);
	int nBottom = std::min((int)rcDirty.bottom, (int)m_nHeight);
	int nLeft = std::max((int)rcDirty.left, 0);
	int nRight = std::min((int)rcDirty.right, (int)m_nWidth);
	if (nRight > nLeft)	{
		for (int i = nTop; i < nBottom; ++i) {
			::memset(pBmpBits + i * m_nWidth + nLeft, alpha, (nRight - nLeft) * 4);
		}
	}
}

void BitmapAlpha::RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding, uint8_t alpha) const
{
	// �˺���������GDI��API��Ⱦλͼ�����¶�ʧalphaͨ������������԰�alphaͨ��������
	// ������Ⱦλͼʱ������GDI+��AlphaBlend��API��λͼ�����˰�͸����alphaͨ��ʱ�����ܵ���û����ȷ������alphaͨ��
	ASSERT((m_pPiexl != nullptr) && (m_nChannels == 4) && (m_nWidth > 0) && (m_nHeight > 0));
	if ((m_pPiexl == nullptr) || (m_nChannels != 4) || (m_nWidth <= 0) || (m_nHeight <= 0)) {
		return;
	}

	unsigned int * pBmpBits = (unsigned int *)m_pPiexl;
	int nTop = std::max((int)rcDirty.top, 0);
	int nBottom = std::min((int)rcDirty.bottom, (int)m_nHeight);
	int nLeft = std::max((int)rcDirty.left, 0);
	int nRight = std::min((int)rcDirty.right, (int)m_nWidth);

	for (int i = nTop; i < nBottom; i++) {
		for (int j = nLeft; j < nRight; j++) {
			uint8_t* a = (uint8_t*)(pBmpBits + i * m_nWidth + j) + 3;

			if (((j >= rcShadowPadding.left && j < m_nWidth - rcShadowPadding.right)
				|| (i >= rcShadowPadding.top && i < m_nHeight - rcShadowPadding.bottom))) {

				// ClearAlphaʱ����alphaͨ������Ϊĳ��ֵ
				// �����ֵû�б仯����֤������û�л����κ����ݣ���alpha��Ϊ0
				if (alpha != 0 && *a == alpha) {
					*a = 0;
				}
				// �����ֵ��Ϊ0����֤�����汻����DrawText��GDI�������ƹ�����alpha����Ϊ0����ʱalpha��Ϊ255
				else if (*a == 0) {
					*a = 255;
				}
			}
		}
	}
}

void BitmapAlpha::RestoreAlpha(const UiRect& rcDirty, const UiPadding& rcShadowPadding) const
{
	// ����ʲô��������Ѵ������alphaͨ������Ϊ255
	ASSERT((m_pPiexl != nullptr) && (m_nChannels == 4) && (m_nWidth > 0) && (m_nHeight > 0));
	if ((m_pPiexl == nullptr) || (m_nChannels != 4) || (m_nWidth <= 0) || (m_nHeight <= 0)) {
		return;
	}

	unsigned int * pBmpBits = (unsigned int *)m_pPiexl;
	int nTop = std::max((int)rcDirty.top, 0);
	int nBottom = std::min((int)rcDirty.bottom, (int)m_nHeight);
	int nLeft = std::max((int)rcDirty.left, 0);
	int nRight = std::min((int)rcDirty.right, (int)m_nWidth);

	for (int i = nTop; i < nBottom; i++) {
		for (int j = nLeft; j < nRight; j++) {
			uint8_t* a = (uint8_t*)(pBmpBits + i * m_nWidth + j) + 3;

			if (((j >= rcShadowPadding.left && j < m_nWidth - rcShadowPadding.right)
				|| (i >= rcShadowPadding.top && i < m_nHeight - rcShadowPadding.bottom))) {
					*a = 255;
			}
		}
	}
}

}