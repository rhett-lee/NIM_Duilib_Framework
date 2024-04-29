#ifndef UI_CORE_DRAG_WINDOW_H_
#define UI_CORE_DRAG_WINDOW_H_

#pragma once

#include "duilib/Core/Control.h"
#include "duilib/Core/Box.h"
#include "duilib/Utils/WinImplBase.h"
#include "duilib/Render/IRender.h"

namespace ui
{
/** �϶���������ʾ�Ĵ���
*/
class DragWindow : public WindowImplBase
{
public:
    DragWindow();

protected:
    //���������������ⲿ���ã�����OnFinalMessage�����У���delete this����
    virtual ~DragWindow();

public:
    /**  ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ��Ŀ¼
    * @return ������ʵ�ֲ����ش���Ƥ��Ŀ¼
    */
    virtual std::wstring GetSkinFolder() override;

    /**  ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ƥ�� XML �����ļ�
    * @return ������ʵ�ֲ����ش���Ƥ�� XML �����ļ�
    *         ���ص����ݣ�������XML�ļ����ݣ����ַ�'<'Ϊ��ʼ���ַ�������
    *         �������ļ�·����������'<'�ַ���ʼ���ַ��������ļ�Ҫ��GetSkinFolder()·�����ܹ��ҵ�
    */
    virtual std::wstring GetSkinFile() override;

    /** ��������ʱ�����ã�������ʵ�����Ի�ȡ����Ψһ��������
    * @return ������ʵ�ֲ����ش���Ψһ��������
    */
    virtual std::wstring GetWindowClassName() const override;

    /** �ڴ����յ� WM_NCDESTROY ��Ϣʱ�ᱻ����
    * @param [in] hWnd Ҫ���ٵĴ��ھ��
    */
    virtual void OnFinalMessage(HWND hWnd) override;

public:
    /** ������ʾ��ͼƬ
    * @param [in] pBitmap ͼƬ��Դ�Ľӿ�
    */
    virtual void SetDragImage(const std::shared_ptr<IBitmap>& pBitmap);

    /** ��������λ�ã��������
    */
    virtual void AdjustPos();

public:
    /** �������ü���
    */
    void AddRef();

    /** �������ü���
    */
    void Release();

private:
    /** ���ü���
    */
    int32_t m_nRefCount;
};
}

#endif // UI_CORE_DRAG_WINDOW_H_