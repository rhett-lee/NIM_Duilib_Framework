#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Box/HBox.h"
#include "duilib/Box/VBox.h"
#include "duilib/Render/IRender.h"
#include "duilib/Control/RichEdit.h"
#include "duilib/Control/Button.h"
#include <atomic>

namespace nim_comp {

class PopoverArrow;
class PopoverHeader;
class PopoverBody;
class PopoverFooter;
class PopoverRoot;
class Popover;
class PopoverHolderLayer;
class PopoverLayer;


/**
* @brief ������λ�úͷ���Ĭ��ָ��ؼ����ĵ������㣻
*        kPlaceInner �� kPlaceOuter ��ʾ�ڿؼ��ڻ��ǿؼ��⣬
*        һ��popover��tooltip�ǿؼ��⣬alert��notification�ǿؼ��ڣ�
*        kPlaceLeftTop�ȱ�ʾ��������
*        Left��ʾ��ê����࣬Top��ʾ��ͷ�ڵ���ƫ����ָ��ê�㡣
*/
enum PopoverPlacement {
    kPlaceInner = 1,
    kPlaceOuter = 1 << 1,
    kPlaceLeftTop = 1 << 2,
    kPlaceLeft = 1 << 3,
    kPlaceLeftBottom = 1 << 4,
    kPlaceTopLeft = 1 << 5,
    kPlaceTop = 1 << 6,
    kPlaceTopRight = 1 << 7,
    kPlaceRightTop = 1 << 8,
    kPlaceRight = 1 << 9,
    kPlaceRightBottom = 1 << 10,
    kPlaceBottomLeft = 1 << 11,
    kPlaceBottom = 1 << 12,
    kPlaceBottomRight = 1 << 13,
    kPlaceCenter = 1 << 14
};

/* ����������ʽ */
enum PopoverTriggerType {
    /* �û��Լ����� */
    kTriggerNone = 0,
    /* ê���ȡ���� */
    kTriggerSetFocus = 1,
    /* ê��ʧȥ���� */
    kTriggerKillFocus = 1 << 1,
    /* ����¼� */
    kTriggerClick = 1 << 2,
    /* ��ʱ */
    kTriggerTimeout = 1 << 3,
    /* ����رա�ȡ����ȷ�ϵȰ�ť */
    kTriggerConfirm = 1 << 4,
    /* ������ */
    kTriggerEnter = 1 << 5,
    /* ���ͣ�� */
    kTriggerHover = 1 << 6,
    /* ����뿪 */
    kTriggerLeave = 1 << 7,
    /* ������ǵ������� */
    kTriggerClickLayer = 1 << 8,
    /* ����չʾ */
    kTriggerImmediately = 1 << 9,
    /* ê��visible���Է����仯ʱ */
    kTriggerVisible = 1 << 10
};

/* ����ͼ�� */
enum PopoverIconType {
    /* ����ʾͼ�� */
    kIconNone,
    /* ��Ϣ */
    kIconInfo,
    /* ���� */
    kIconWarning,
    /* ���� */
    kIconError
};

/* Ĭ�ϰ�ť */
enum PopoverButtonType {
    kButtonNone = 0,
    /* ����ͷ�еĹرհ�ť */
    kButtonClose = 1,
    /* ����β��ȷ�ϰ�ť */
    kButtonOk = 1 << 1,
    /* ����β��ȡ����ť */
    kButtonCancel = 1 << 2
};

/* Ĭ�ϵ���������� */
enum PopoverResultType {
    /* �޲������Զ��رյ��� */
    kResultNone,
    /* ȷ�� */
    kResultOk,
    /* ȡ�� */
    kResultCancel
};

/* �����ر�ʱ�ص������������� */
struct PopoverResult {
    PopoverResultType type;
};

/* �����ر�ʱ�ص����� */
typedef std::function<bool(const PopoverResult&)> PopoverCallback;

class PopoverCallbackSource : public std::vector<PopoverCallback>
{
public:
    PopoverCallbackSource& operator += (const PopoverCallback& callback)
    {
        push_back(callback);
        return *this;
    }

    bool operator() (const PopoverResult& result) const
    {
        for (auto it = this->begin(); it != this->end(); it++) {
            if (!(*it)(result)) return false;
        }
        return true;
    }
};

/* ������ͷ */
class PopoverArrow :public ui::Control
{
public:
    explicit PopoverArrow(int nPlaceMent);
    virtual ~PopoverArrow();

    virtual std::wstring GetType() const override;
    virtual void OnInit() override;

    void SetArrowArea(ui::UiRect rcArea);

    static const int kWidth;
    static const int kHeight;
    static const int kMargin;
private:
    ui::HorAlignType GetHorAlignType();
    ui::VerAlignType GetVerAlignType();

protected:
    ui::UiMargin GetMarginByPlacement();

    virtual void CalcTrianglePoints();
    virtual void PaintBkColor(ui::IRender* pRender) override;
protected:
    int m_nPlacement;
    ui::UiRect m_rcArea;
    ui::UiPoint m_ptTriangle[3];
    std::unique_ptr<ui::IPath> m_pPath;
    std::unique_ptr<ui::IPen> m_pPen;
    std::unique_ptr<ui::IBrush> m_pBrush;
};

/* ����ͷ */
class PopoverHeader :public ui::HBox
{
public:
    explicit PopoverHeader(const std::wstring& strTitle,
        bool bShowClose = false,
        PopoverIconType nIconType = kIconNone);
    virtual ~PopoverHeader();

    // ���ظ���
    virtual std::wstring GetType() const override;
    virtual ui::UiEstSize EstimateSize(ui::UiSize szAvailable) override;

    // ��������
    virtual void UpdateTitle(const std::wstring& strTitle);

    // �����رհ�ť����¼�
    void AttachCloseClicked(const ui::EventCallback& callback) { OnClose += callback; }

protected:


protected:
    bool m_bUseMaxSize;
    ui::CEventSource OnClose;
    std::wstring m_strTitle;
    bool m_bShowClose;
    PopoverIconType m_nIconType;

    ui::Control* m_pControlIcon;
    ui::RichEdit* m_pRichEditTitle;
    ui::Button* m_pButtonClose;
};

/* ������ */
class PopoverBody :public ui::HBox
{
public:
    explicit PopoverBody(const std::wstring& content, const std::wstring& colorId = L"");
    virtual ~PopoverBody();

    virtual std::wstring GetType() const override;
    virtual ui::UiEstSize EstimateSize(ui::UiSize szAvailable) override;
 
    virtual void UpdateContent(const std::wstring& strContent);
protected:
    bool m_bUseMaxSize;
    ui::RichEdit* m_pRichEditContent;
};

/* ����β */
class PopoverFooter :public ui::HBox
{
public:
    PopoverFooter(const std::wstring& strOk, const std::wstring& strCancel);
    virtual ~PopoverFooter();

    virtual std::wstring GetType() const override;
    virtual ui::UiEstSize EstimateSize(ui::UiSize szAvailable) override;
    virtual void OnInit() override;

    void AttachCancelClicked(const ui::EventCallback& callback) { OnCancel += callback; }
    void AttachOkClicked(const ui::EventCallback& callback) { OnOk += callback; }

protected:
    bool m_bUseMaxSize;
    std::wstring m_strOk;
    std::wstring m_strCancel;
    ui::CEventSource OnCancel;
    ui::CEventSource OnOk;
    ui::Button* m_pButtonOk;
    ui::Button* m_pButtonCancel;
};

class PopoverRoot :public ui::VBox
{
public:
    PopoverRoot() {
        // DO NOT DELAY DESTROY
        SetDelayedDestroy(false);
    }

    virtual ~PopoverRoot() = default;

    ui::UiEstSize EstimateSize(ui::UiSize szAvailable) override;

public:
    std::wstring GetType() const override {
        return L"PopoverRoot";
    }
};

/* ���� */
class Popover :public ui::VBox
{
public:
    /*
    * @brief �������๹�캯��
    * @param[in] pAnchor ê��ؼ�,Ϊ�ձ�ʾ�����������ʾ;
    *                    ��Ϊ��ʱ������nShowType�Զ����ô�����������ê��ؼ�������ʱ�Զ��رյ���
    */
    Popover(ui::Control* pAnchor,
        int nPlacement,
        int nShowType,
        int nDisappearType,
        bool bRemoveOnClose,
        int nShowTimeouts,
        int nDisappearTimeouts,
        PopoverHeader* header,
        PopoverBody* body,
        PopoverFooter* footer,
        PopoverArrow* arrow);

    virtual ~Popover();

    // ���ظ���
    virtual std::wstring GetType() const override;
    virtual ui::UiEstSize EstimateSize(ui::UiSize szAvailable) override;
    virtual void OnInit() override;
    virtual void SetPos(ui::UiRect rc) override;

    ui::Control* GetAnchor() const { return m_pAnchor; }
    PopoverHeader* GetHeader() const { return m_pPopoverHeader; }
    PopoverBody* GetBody() const { return m_pPopoverBody; }
    PopoverFooter* GetFooter() const { return m_pPopoverFooter; }
    PopoverRoot* GetRoot() const { return m_pPopoverRoot; }

    // ����Tag���Ա�ʶͬ���͵���
    void SetTag(const std::wstring& strTag) { m_strTag = strTag; }
    const std::wstring GetTag() const { return m_strTag; }

    // ���µ�������
    virtual void Update(PopoverHeader* header, PopoverBody* body, PopoverFooter* footer);
    virtual void UpdateContent(const std::wstring& content);
    virtual void UpdateNotification(const std::wstring& strTitle,
        const std::wstring& strContent = L"");
    virtual void UpdateTooltip(const std::wstring& tooltip);
    virtual void UpdateShowType(int nType, int nTimeouts = 0);
    virtual void UpdateDisappearType(int nType, int nTimeouts = 0);

    // ��������ص�
    void BindResultCallback(const PopoverCallback& callback) { m_cbResult += callback; }

    // �����رջص�
    void BindCloseCallback(const PopoverCallback& callback) { m_cbClose += callback; }

protected:
    ui::HorAlignType GetHorAlignType();
    ui::VerAlignType GetVerAlignType();
    virtual ui::UiRect ReCalcByAnchorPos(ui::UiRect rc);

protected:
    // ��ʼ��Ԫ��
    virtual void InitializeElements();

    // ��ʼ��λ�ã�����ê���¼�
    virtual void InitializePosition();

    // ��ʼ��չʾ�͹رմ�����
    bool HasTrigger(int nType, PopoverTriggerType nTrigger) { return nType & nTrigger; }
    virtual void InitializeShowTriggers(int nOldType, int nNewType, int nTimeouts = 0);
    virtual void InitializeDisappearTriggers(int nOldType, int nNewType, int nTimeouts = 0);
    virtual void OnShowTriggerTimeout(int index);
    virtual void OnDisappearTriggerTimeout(int index);

    // �����رյ���
    virtual void TriggerResult(const PopoverResult& result, bool bForceClose = false);
    virtual void TriggerClose();

    // ê���¼�
    virtual bool OnAnchorResize(const ui::EventArgs& args);
    virtual bool OnAnchorSetFocus(const ui::EventArgs& args);
    virtual bool OnAnchorKillFocus(const ui::EventArgs& args);
    virtual bool OnAnchorMouseClick(const ui::EventArgs& args);
    virtual bool OnAnchorMouseEnter(const ui::EventArgs& args);
    virtual bool OnAnchorMouseHover(const ui::EventArgs& args);
    virtual bool OnAnchorMouseLeave(const ui::EventArgs& args);
    virtual bool OnAnchorLastEvent(const ui::EventArgs& args);
    virtual bool OnAnchorVisibleChange(const ui::EventArgs& args);

    // ��ʱ��

protected:
    std::wstring m_strTag;
    ui::Control* m_pAnchor;
    int m_nPlacement;
    int m_nShowType;
    int m_nDisappearType;
    bool m_bRemoveOnClose;

    int m_nShowTimeouts;
    int m_nDisappearTimeouts;

    std::atomic<int> m_nShowTriggerIndex;
    std::atomic<int> m_nDisappearTriggerIndex;

    PopoverRoot* m_pPopoverRoot;
    PopoverHeader* m_pPopoverHeader;
    PopoverBody* m_pPopoverBody;
    PopoverFooter* m_pPopoverFooter;
    PopoverArrow* m_pPopoverArrow;

    PopoverCallbackSource m_cbResult;
    PopoverCallbackSource m_cbClose;

    friend class PopoverLayer;
};

/*
* ����������
* Popover �� Alert ������ͨBox����
* Notification ������Ҫ�д�ֱ���ֻ��������Ⲽ��
*/
class PopoverHolderLayer :public ui::Box
{
public:
    explicit PopoverHolderLayer(const std::wstring& type,
        ui::Layout* pLayout = new ui::Layout()) :ui::Box(pLayout),
        m_strType(type)
    {
        SetMouseEnabled(false);
        SetKeyboardEnabled(false);

        // DO NOT DELAY DESTROY
        SetDelayedDestroy(false);
    }

    virtual ~PopoverHolderLayer()
    {

    }

public:
    static const std::wstring kHolderTypeNotification;
    static const std::wstring kHolderTypePopover;
    static const std::wstring kHolderTypeAlert;

public:
    std::wstring GetType() const override {
        return m_strType;
    }

private:
    std::wstring m_strType;
};



class NotificationHolderLayer :public PopoverHolderLayer
{
public:
    explicit NotificationHolderLayer(ui::Control* pAnchor) :
        PopoverHolderLayer(PopoverHolderLayer::kHolderTypeNotification, new ui::VLayout()),
        m_pAnchor(pAnchor)
    {
    }

    ~NotificationHolderLayer()
    {

    }

    bool OnAnchorResize(const ui::EventArgs& /*args*/) {
        ui::UiRect rc = m_pAnchor->GetPos();

        SetFixedWidth(ui::UiFixedInt(rc.Width()), true, true);
        SetFixedHeight(ui::UiFixedInt(rc.Height()), true, true);

        SetPos(rc);

        return true;
    }

    virtual void SetPos(ui::UiRect rc) override {
        rc = m_pAnchor->GetPos();

        SetFixedWidth(ui::UiFixedInt(rc.Width()), true, true);
        SetFixedHeight(ui::UiFixedInt(rc.Height()), true, true);

        ui::Control::SetPos(rc);

        ui::UiSize64 requiredSize;
        if (m_items.size() == 0) {
            requiredSize.cx = 0;
            requiredSize.cy = 0;
        }
        else {
            requiredSize = GetLayout()->ArrangeChild(m_items, rc);
        }
    }

    virtual void OnInit() override {

        if (IsInited()) {
            return;
        }
        __super::OnInit();
        ASSERT(m_pAnchor);

        m_pAnchor->AttachResize(nbase::Bind(&NotificationHolderLayer::OnAnchorResize, this, std::placeholders::_1));
    }

private:
    ui::Control* m_pAnchor;
};

/**
* ������
* ��Ҫȷ���������ܹ����յ��������¼�
* ʹ��ʱ��Ҫ����������ص�root�ڵ㣬�ұ�֤�㼶Ϊ���ϲ�
*/
class PopoverLayer :public ui::IUIMessageFilter, public ui::Box {
public:
    PopoverLayer();
    ~PopoverLayer();

    /*
    * λ�ڵ��������
    */
    void ShowAlert(Popover* popover);

    /*
    * λ�ڵ������м��
    */
    void ShowPopover(Popover* popover);

    /*
    * λ�ڵ������м��
    */
    void ShowTooltip(Popover* popover);

    /*
    * λ�ڵ�������ײ�
    */
    void ShowNotification(Popover* popover);

    /**
    * @brief ��Ĭ����ʽ�����������ݣ�Ĭ����Ӱ�׵׺���, �Ҵ��м�ͷ
    * @param[in] pAnchor ê��ؼ�,Ϊ�ձ�ʾ�����������ʾ
    * @param[in] strTitle ���⣬����Ҫ��Ϊ��
    * @param[in] strOk ȷ�ϰ�ť���֣�Ĭ��ʹ�� STRING_OK
    * @param[in] strCancel ȡ����ť���֣�Ĭ��ʹ�� STRING_CANCEL
    * @param[in] strContent ���ݣ�����Ҫ��Ϊ��
    * @param[in] nPlacement ��������Ĭ��Ϊê��ؼ����ê��ؼ���
    * @param[in] nButtons ��ť������ϣ�kButtonOk | kButtonCancel ��ʾ��ʾȷ�Ϻ�ȡ����ť
    * @param[in] nShowType �Զ���ʾ�Ĵ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] nDisappearType �Զ��رյĴ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] bRemoveOnClose �رպ��Ƿ�ɾ��
    * @param[in] pCustomHeader �Զ���PopoverHeader
    * @param[in] pCustomBody �Զ���PopoverBody
    * @param[in] pCustomFooter �Զ���PopoverFooter
    */
    static Popover* CreatePopover(ui::Control* pAnchor,
        const std::wstring& strTitle,
        const std::wstring& strContent,
        const std::wstring& strOk = L"",
        const std::wstring& strCancel = L"",
        int nPlacement = kPlaceOuter | kPlaceTop,
        int nButtons = kButtonOk | kButtonCancel,
        int nShowType = kTriggerClick,
        int nDisappearType = kTriggerConfirm | kTriggerClickLayer | kTriggerKillFocus,
        bool bShowArrow = true,
        bool bRemoveOnClose = false,
        int nShowTimeouts = 0,
        int nDisappearTimeouts = 0,
        PopoverHeader* pCustomHeader = nullptr,
        PopoverBody* pCustomBody = nullptr,
        PopoverFooter* pCustomFooter = nullptr,
        PopoverArrow* pCustomArrow = nullptr);

    /**
    * @brief ��Ĭ����ʽ�����������ݣ�Ĭ����Ӱ�׵׺���, �Ҵ��м�ͷ
    * @param[in] pAnchor ê��ؼ�,Ϊ�ձ�ʾ�����������ʾ
    * @param[in] strTitle ���⣬����Ҫ��Ϊ��
    * @param[in] strOk ȷ�ϰ�ť���֣�Ĭ��ʹ�� STRING_OK
    * @param[in] strCancel ȡ����ť���֣�Ĭ��ʹ�� STRING_CANCEL
    * @param[in] strContent ���ݣ�����Ҫ��Ϊ��
    * @param[in] nPlacement ��������Ĭ��Ϊê��ؼ����ê��ؼ���
    * @param[in] nButtons ��ť������ϣ�kButtonOk | kButtonClose ��ʾ��ʾȷ�Ϻ͹رհ�ť
    * @param[in] nShowType �Զ���ʾ�Ĵ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] nDisappearType �Զ��رյĴ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] bRemoveOnClose �رպ��Ƿ�ɾ��
    * @param[in] pCustomHeader �Զ���PopoverHeader
    * @param[in] pCustomBody �Զ���PopoverBody
    * @param[in] pCustomFooter �Զ���PopoverFooter
    */
    static Popover* CreateAlert(ui::Control* pAnchor,
        const std::wstring& strTitle,
        const std::wstring& strContent,
        const std::wstring& strOk = L"",
        const std::wstring& strCancel = L"",
        int nPlacement = kPlaceInner | kPlaceCenter,
        int nButtons = kButtonOk | kButtonClose,
        int nShowType = kTriggerImmediately,
        int nDisappearType = kTriggerConfirm,
        bool bRemoveOnClose = true,
        PopoverHeader* pCustomHeader = nullptr,
        PopoverBody* pCustomBody = nullptr,
        PopoverFooter* pCustomFooter = nullptr);

    /**
    * @brief ��Ĭ����ʽ�����������ݣ�Ĭ����Ӱ�׵׺���, �Ҵ��м�ͷ
    * @param[in] pAnchor ê��ؼ�,Ϊ�ձ�ʾ�����������ʾ
    * @param[in] strContent ���⣬����Ҫ��Ϊ��
    * @param[in] nPlacement ��������Ĭ��Ϊê��ؼ����ê��ؼ���
    * @param[in] nButtons ��ť������ϣ���֧�� kButtonClose �� kButtonNone
    * @param[in] nShowType �Զ���ʾ�Ĵ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] nDisappearType �Զ��رյĴ�����ʽ��kTriggerNone��ʾ���Զ�����
    * @param[in] bRemoveOnClose �رպ��Ƿ�ɾ��
    * @param[in] pCustomHeader �Զ���PopoverHeader
    * @param[in] pCustomBody �Զ���PopoverBody
    */
    static Popover* CreateNotification(ui::Control* pAnchor,
        const std::wstring& strTitle,
        const std::wstring& strContent,
        PopoverIconType nIconType = kIconInfo,
        int nPlacement = kPlaceInner | kPlaceTopRight,
        int nButtons = kButtonNone,
        int nShowType = kTriggerImmediately,
        int nDisappearType = kTriggerConfirm,
        bool bRemoveOnClose = true,
        int nShowTimeouts = 0,
        int nDisappearTimeouts = 0,
        PopoverHeader* pCustomHeader = nullptr,
        PopoverBody* pCustomBody = nullptr);

    /**
    * @brief ��Ĭ����ʽ�����������ݣ�Ĭ����Ӱ�׵׺���, �Ҵ��м�ͷ
    * @param[in] pAnchor ê��ؼ�,Ϊ�ձ�ʾ�����������ʾ
    * @param[in] strContent ���ݣ�����Ҫ��Ϊ��
    * @param[in] nPlacement ��������Ĭ��Ϊê��ؼ����ê��ؼ���
    * @param[in] pCustomBody �Զ���PopoverBody
    */
    static Popover* CreateToolltip(ui::Control* pAnchor,
        const std::wstring& strContent,
        int nPlacement = kPlaceOuter | kPlaceTop,
        int nShowType = kTriggerHover,
        int nDisappearType = kTriggerLeave,
        PopoverBody* pCustomBody = nullptr);

public:
    // ����
    bool RemoveItem(Control* pControl) override;

    // ������е�������������Holder
    void ClearAll();

private:
    // ����
    std::wstring GetType() const;
    virtual void OnInit() override;
    virtual LRESULT FilterMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

    /**
    * �����Ƿ���ʾ��͸������
    */
    void SetShowMask(bool show);

    /**
    * �Ƿ���ʾ��͸������
    */
    bool IsShowMask() const { return m_bShowMask; }

    /*
    * @brief ���������������¼�����ر�����nDisappearType
                        ΪkTriggerClickLayer�ĵ���
    * @param[in] pt ���������
    */
    void OnMouseEventButtonDown(ui::UiPoint pt);

private:
    bool m_bShowMask;
    bool m_bDisableWindow;
    int alert_count;

    // should be base of VBox
    std::map<ui::Control*, NotificationHolderLayer*> m_NotifyLayerMap;
    PopoverHolderLayer* m_pPopoverLayer;
    PopoverHolderLayer* m_pAlertLayer;
};
}