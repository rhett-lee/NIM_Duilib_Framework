#pragma once

#include "popover.h"

namespace nim_comp {

class NotificationHeader :public PopoverHeader
{
public:
    NotificationHeader(const std::wstring& strTitle,
        bool bShowClose,
        PopoverIconType nIconType);

    virtual ~NotificationHeader();
};

class NotificationBody :public PopoverBody
{
public:
    explicit NotificationBody(const std::wstring& strContent);

    virtual ~NotificationBody();
};

class Notification :public Popover
{
public:
    Notification(ui::Control* pAnchor,
        int nPlacement,
        int nShowType,
        int nDisappearType,
        bool bRemoveOnClose,
        int nShowTimeouts,
        int nDisappearTimeouts,
        PopoverHeader* header,
        PopoverBody* body);

    virtual ~Notification();

    // ���ظ���
    void SetPos(ui::UiRect rc) override;

protected:
    // ��ʼ��λ�ã�����ê���¼�
    void InitializePosition() override;
};
}