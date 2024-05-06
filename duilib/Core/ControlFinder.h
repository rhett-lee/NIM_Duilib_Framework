#ifndef UI_CORE_CONTROL_FINDER_H_
#define UI_CORE_CONTROL_FINDER_H_

#pragma once

#include "duilib/Core/UiPoint.h"
#include <string>
#include <vector>
#include <map>

namespace ui 
{
// Flags for Control::GetControlFlags()
#define UIFLAG_DEFAULT       0x00000000		// Ĭ��״̬
#define UIFLAG_TABSTOP       0x00000001		// ��ʶ�ؼ��Ƿ����յ� TAB �л�����ʱ�������ý���

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_DRAG_DROP     0x00000010
#define UIFIND_ME_FIRST      0x80000000

class Control;
class Box;

typedef struct tagFINDTABINFO
{
	Control* pFocus;
	Control* pLast;
	bool bForward;
	bool bNextIsIt;
} FINDTABINFO;

/** Window��������Control��ع��ܵķ�װ
*/
class UILIB_API ControlFinder
{
public:
    ControlFinder();
	~ControlFinder();
	
public:
	/** ����Box���ڵ�
	*/
	void SetRoot(Box* pRoot);

	/**
	 * @brief �����������ָ���ؼ�
	 * @param[in] pt ָ������
	 * @return ���ؿؼ�ָ��
	 */
	Control* FindControl(const UiPoint& pt) const;

	/**
	 * @brief ����������ҿ�����ӦWM_CONTEXTMENU�Ŀؼ�
	 * @param[in] pt ָ������
	 * @return ���ؿؼ�ָ��
	 */
	Control* FindContextMenuControl(const UiPoint* pt) const;

	/** ���ҿ���֧���Ϸŵ�Box����
	* @param [in] pt ָ������
	* @param [in] nDropInId �Ϸŵ�IDֵ��ÿ���ؼ���������һ��ID���������Ϸ�, 0��ʾ���������룬��0��ʾ�������룩
	*/
	Box* FindDroppableBox(const UiPoint& pt, uint8_t nDropInId) const;

	/**
	 * @brief ���ݿؼ����Ʋ��ҿؼ�
	 * @param[in] strName �ؼ�����
	 * @return ���ؿؼ�ָ��
	 */
	Control* FindControl2(const std::wstring& strName) const;

	/**
	 * @brief ������������ӿؼ�
	 * @param[in] pParent Ҫ�����Ŀؼ�
	 * @param[in] pt Ҫ���ҵ�����
	 * @return ���ؿؼ�ָ��
	 */
	Control* FindSubControlByPoint(Control* pParent, const UiPoint& pt) const;

	/**
	 * @brief �������ֲ����ӿؼ�
	 * @param[in] pParent Ҫ�����Ŀؼ�
	 * @param[in] strName Ҫ���ҵ�����
	 * @return ���ؿؼ�ָ��
	 */
	Control* FindSubControlByName(Control* pParent, const std::wstring& strName) const;

	/** ���һ���ؼ����Կؼ�����������
	*/
	void AddControl(Control* pControl);

	/**@brief ���տؼ���ͨ��AddControl������ӵĿؼ���
	 * @param[in] pControl �ؼ�ָ��
	 */
	void RemoveControl(Control* pControl);

public:
	static Control* CALLBACK __FindControlFromPoint(Control* pThis, LPVOID pData);
	static Control* CALLBACK __FindControlFromTab(Control* pThis, LPVOID pData);
	static Control* CALLBACK __FindControlFromUpdate(Control* pThis, LPVOID pData);
	static Control* CALLBACK __FindControlFromName(Control* pThis, LPVOID pData);
	static Control* CALLBACK __FindContextMenuControl(Control* pThis, LPVOID pData);
	static Control* CALLBACK __FindControlFromDroppableBox(Control* pThis, LPVOID pData);

private:
    /** ���ڵ�
	*/
	Box* m_pRoot;

	/** �ؼ���name��ӿ�֮���ӳ��
	*/
	std::map<std::wstring, Control*> m_mNameHash;
};

} // namespace ui

#endif // UI_CORE_CONTROL_FINDER_H_
