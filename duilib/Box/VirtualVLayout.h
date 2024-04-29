#ifndef UI_BOX_VIRTUAL_VLAYOUT_H_
#define UI_BOX_VIRTUAL_VLAYOUT_H_

#pragma once

#include "duilib/Box/VLayout.h"
#include "duilib/Box/VirtualLayout.h"

namespace ui 
{
/** ���ʵ�ֵ���Ƭ����
*/
class VirtualListBox;
class UILIB_API VirtualVLayout : public VLayout, public VirtualLayout
{
public:
    VirtualVLayout();

    /** ��������
    */
    virtual LayoutType GetLayoutType() const override { return LayoutType::VirtualVLayout; }

    /** �����ڲ����пؼ���λ����Ϣ
        * @param [in] items �ؼ��б�
        * @param[in] rc ��ǰ����λ����Ϣ, �����ڱ߾࣬����������߾�
        * @return �������к����պ��ӵĿ�Ⱥ͸߶���Ϣ
        */
    virtual UiSize64 ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;

    /** �����ڲ��ӿؼ���С�������������С���������͵��ӿؼ������ԣ��������С����
        * @param[in] items �ӿؼ��б�
        * @param [in] szAvailable ���ô�С������������ÿؼ����ڱ߾࣬��������������ؼ�����߾�
        * @return �������к����ղ��ֵĴ�С��Ϣ����Ⱥ͸߶ȣ���
                ����items���ӿؼ�����߾࣬����items���ӿؼ����ڱ߾ࣻ
                ����Box�ؼ�������ڱ߾ࣻ
                ������Box�ؼ��������߾ࣻ
                ����ֵ�в������������͵��ӿؼ���С��
        */
    virtual UiSize EstimateSizeByChild(const std::vector<Control*>& items, UiSize szAvailable) override;

    /** ���ò�������
     * @param[in] strName Ҫ���õ�������
     * @param[in] strValue Ҫ���õ�����ֵ
     * @return true ���óɹ���false ���Բ�����
     */
    virtual bool SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

public:
    /** �ӳټ���չʾ����
    * @param [in] rc ��ǰ������С��Ϣ, �ⲿ����ʱ����Ҫ�ȼ�ȥ�ڱ߾�
    */
    virtual void LazyArrangeChild(UiRect rc) const override;

    /** ��ȡ��Ҫչʾ����ʵ������������������Control�����Ӧ����ʵ�����
    * @param [in] rc ��ǰ������С��Ϣ, �ⲿ����ʱ����Ҫ�ȼ�ȥ�ڱ߾�
    */
    virtual size_t AjustMaxItem(UiRect rc) const override;

    /** �õ��ɼ���Χ�ڵ�һ��Ԫ�ص�ǰһ��Ԫ������
    * @param [in] rc ��ǰ��ʾ����ľ��Σ��������ڱ߾�
    * @return ����Ԫ�ص�����
    */
    virtual size_t GetTopElementIndex(UiRect rc) const override;

    /** �ж�ĳ��Ԫ���Ƿ��ڿɼ���Χ��
    * @param[in] iIndex Ԫ������
    * @param [in] rc ��ǰ��ʾ����ľ��Σ��������ڱ߾�
    * @return ���� true ��ʾ�ɼ�������Ϊ���ɼ�
    */
    virtual bool IsElementDisplay(UiRect rc, size_t iIndex) const override;

    /** �ж��Ƿ�Ҫ���²���
    */
    virtual bool NeedReArrange() const override;

    /** ��ȡ��ǰ���пɼ��ؼ�������Ԫ������
    * @param [in] rc ��ǰ��ʾ����ľ��Σ��������ڱ߾�
    * @param[out] collection �����б���Χ�ǣ�[0, GetElementCount())
    */
    virtual void GetDisplayElements(UiRect rc, std::vector<size_t>& collection) const override;

    /** �ÿؼ��ڿɼ���Χ��
    * @param [in] rc ��ǰ��ʾ����ľ��Σ��������ڱ߾�
    * @param[in] iIndex Ԫ�������ţ���Χ�ǣ�[0, GetElementCount())
    * @param[in] bToTop �Ƿ������Ϸ�
    */
    virtual void EnsureVisible(UiRect rc, size_t iIndex, bool bToTop) const override;

private:
    /** ��ȡ������ĸ߶�
    * @param [in] nCount ��������������ΪBox::InvalidIndex�����ȡ����������ĸ߶��ܺ�
    * @param [in] rc ��ǰ������С��Ϣ, �ⲿ����ʱ����Ҫ�ȼ�ȥ�ڱ߾�
    * @return ���� nCount ��������ĸ߶��ܺ�
    */
    int64_t GetElementsHeight(UiRect rc, size_t nCount) const;

private:
    /** ��ȡ������Box�ӿ�
    */
    VirtualListBox* GetOwnerBox() const;

    /** ���������С
     * @param[in] szItem �����С���ݣ��ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
     */
    void SetItemSize(UiSize szItem, bool bNeedDpiScale = true);

    /** ��ȡ�����С���ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
     */
    const UiSize& GetItemSize() const;

private:
    //�����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾��
    UiSize m_szItem;
};
} // namespace ui

#endif // UI_BOX_VIRTUAL_VLAYOUT_H_
