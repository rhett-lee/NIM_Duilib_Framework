#include "Shadow.h"
#include "duilib/Core/Box.h"
#include "duilib/Core/Window.h"
#include "duilib/Render/IRender.h"
#include "duilib/Core/GlobalManager.h"

namespace ui 
{

class ShadowBox : public Box
{
public:
	ShadowBox()
	{
		//�رտؼ�������ڱ߾࣬������Ӱ���Ʋ�����
		SetEnableControlPadding(false);
	}
	virtual std::wstring GetType() const override { return L"ShadowBox"; }

	virtual void Paint(IRender* pRender, const UiRect& rcPaint) override
	{
		if (pRender == nullptr) {
			return;
		}		
		UiRect rcPos = GetPosWithoutPadding();
		if (rcPaint.left >= rcPos.left && rcPaint.top >= rcPos.top && rcPaint.right <= rcPos.right && rcPaint.bottom <= rcPos.bottom) {
			//��Ϊ��Ӱ���м䲿���ǿյģ�����Ҫ�����ػ�, ֻ���Բ�ǿ�϶
			FillRoundRect(pRender, rcPos);
			return;
		}
		else {
			__super::Paint(pRender, rcPaint);
			FillRoundRect(pRender, rcPos);
		}
	};

	/** ��Box��Բ�ǵ�ʱ���ĸ��ǲ������ɫ���Ʊ�����������ֺ�ɫ����
	*/
	void FillRoundRect(IRender* pRender, const UiRect& rcPos)
	{
		Control* pChildBox = GetItemAt(0);
		if (pChildBox == nullptr) {
			return;
		}
		if (!pChildBox->IsVisible() || !pChildBox->ShouldBeRoundRectFill()) {
			//�������Բ�ǵģ����߲��ɼ��ģ�����Ҫ�����
			return;
		}
		UiSize borderRound = pChildBox->GetBorderRound();
		const int nRectSize = std::max(borderRound.cx, borderRound.cy);
		if (nRectSize <= 0) {
			return;
		}

		uint8_t uFade = 0xFF;
		Window* pWindow = GetWindow();
		if ((pWindow != nullptr) && (pWindow->IsLayeredWindow())) {
			uFade = pWindow->GetWindowAlpha();
		}

		if (pChildBox->GetAlpha() != 0xFF) {
			uFade = static_cast<uint8_t>((int32_t)uFade * pChildBox->GetAlpha() / 0xFF);
		}
		
		UiRect fillRect;
		//���Ͻ�
		fillRect = UiRect(rcPos.left, rcPos.top, rcPos.left + nRectSize, rcPos.top + nRectSize);
		pRender->FillRect(fillRect, m_bkColor, uFade);

		//���Ͻ�
		fillRect = UiRect(rcPos.right - nRectSize, rcPos.top, rcPos.right, rcPos.top + nRectSize);
		pRender->FillRect(fillRect, m_bkColor, uFade);

		//���½�
		fillRect = UiRect(rcPos.left, rcPos.bottom - nRectSize, rcPos.left + nRectSize, rcPos.bottom);
		pRender->FillRect(fillRect, m_bkColor, uFade);

		//���½�
		fillRect = UiRect(rcPos.right - nRectSize, rcPos.bottom - nRectSize, rcPos.right, rcPos.bottom);
		pRender->FillRect(fillRect, m_bkColor, uFade);
	}

private:
	/** ����ɫ
	*/
	UiColor m_bkColor = UiColor(UiColors::LightGray);
};

UiSize Shadow::GetChildBoxBorderRound()
{
	return { 3, 3 };
}

Shadow::Shadow():
	m_bShadowAttached(true),
	m_bUseDefaultShadowAttached(true),
	m_pRoot(nullptr)
{
	ResetDefaultShadow();
}

void Shadow::SetShadowAttached(bool bShadowAttached)
{
	m_bShadowAttached = bShadowAttached; 
	//�ⲿ���ú󣬼�����Ϊ��Ĭ��ֵ
	m_bUseDefaultShadowAttached = false;
}

bool Shadow::IsShadowAttached() const
{ 
	return m_bShadowAttached;
}

bool Shadow::IsUseDefaultShadowAttached() const
{
	return m_bUseDefaultShadowAttached;
}

void Shadow::SetUseDefaultShadowAttached(bool isDefault)
{
	m_bUseDefaultShadowAttached = isDefault;
}

void Shadow::SetShadowImage(const std::wstring &image)
{
	m_strImage = image;
	m_bUseDefaultImage = false;
}

const std::wstring& Shadow::GetShadowImage() const
{
	return m_strImage;
}

void Shadow::SetShadowCorner(const UiPadding& padding, bool bNeedDpiScale)
{
	ASSERT((padding.left >= 0) && (padding.top >= 0) && (padding.right >= 0) && (padding.bottom >= 0));
	if ((padding.left >= 0) && (padding.top >= 0) && (padding.right >= 0) && (padding.bottom >= 0)) {
		m_rcShadowCorner = padding;
		if (bNeedDpiScale) {
			GlobalManager::Instance().Dpi().ScalePadding(m_rcShadowCorner);
		}
		m_rcShadowCornerBackup = m_rcShadowCorner;
	}	
}

UiPadding Shadow::GetShadowCorner() const
{
	if (m_bShadowAttached) {
		return m_rcShadowCorner;
	}
	else {
		return UiPadding(0, 0, 0, 0);
	}
}

void Shadow::ResetDefaultShadow()
{
	m_bUseDefaultImage = true;
	m_strImage = L"file='public/shadow/bk_shadow.png' corner='30,30,30,30'";

	m_rcShadowCorner = { 14, 14, 14, 14 };
	GlobalManager::Instance().Dpi().ScalePadding(m_rcShadowCorner);
	m_rcShadowCornerBackup = m_rcShadowCorner;
}

Box* Shadow::AttachShadow(Box* pRoot)
{
	if (!m_bShadowAttached) {
		return pRoot;
	}
	ASSERT(m_pRoot == nullptr);
	if (m_pRoot != nullptr) {
		return pRoot;
	}

	if (pRoot == nullptr) {
		return nullptr;
	}

	m_pRoot = new ShadowBox();
	m_pRoot->SetPadding(m_rcShadowCorner, false);

	if (pRoot->GetFixedWidth().IsInt32()) {
		int32_t rootWidth = pRoot->GetFixedWidth().GetInt32();
		rootWidth += m_rcShadowCorner.left + m_rcShadowCorner.right;
		m_pRoot->SetFixedWidth(UiFixedInt(rootWidth), true, false);
	}
	else {
		m_pRoot->SetFixedWidth(pRoot->GetFixedWidth(), true, false);
	}
	if (pRoot->GetFixedHeight().IsInt32()) {
		int32_t rootHeight = pRoot->GetFixedHeight().GetInt32();
		rootHeight += m_rcShadowCorner.top + m_rcShadowCorner.bottom;
		m_pRoot->SetFixedHeight(UiFixedInt(rootHeight), true, false);
	}
	else {
		m_pRoot->SetFixedHeight(pRoot->GetFixedHeight(), true, false);
	}

	if (m_bUseDefaultImage)	{
		pRoot->SetBorderRound(Shadow::GetChildBoxBorderRound());
	}

	m_pRoot->AddItem(pRoot);
	m_pRoot->SetBkImage(m_strImage);

	return m_pRoot;
}

void Shadow::MaximizedOrRestored(bool isMaximized)
{
	if (!m_bShadowAttached) {
		return;
	}

	if (isMaximized && m_pRoot) {
		m_rcShadowCorner = UiPadding(0, 0, 0, 0);
		m_pRoot->SetPadding(m_rcShadowCorner, false);
	}
	else if (!isMaximized && m_pRoot) {
		m_rcShadowCorner = m_rcShadowCornerBackup;
		m_pRoot->SetPadding(m_rcShadowCorner, false);
	}
}

ui::Control* Shadow::GetRoot()
{
	return m_pRoot;
}

void Shadow::ClearImageCache()
{
	if (m_pRoot) {
		m_pRoot->ClearImageCache();
	}	
}

}