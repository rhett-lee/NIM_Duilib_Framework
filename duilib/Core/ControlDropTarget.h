#ifndef UI_CORE_CONTROL_DROP_TARGET_H_
#define UI_CORE_CONTROL_DROP_TARGET_H_

#pragma once

#include "duilib/Core/UiTypes.h"

namespace ui 
{
class Control;

/** �ؼ����Ϸ�֧��
*/
class ControlDropTarget
{
public:
	ControlDropTarget();
	ControlDropTarget(const ControlDropTarget& r) = delete;
	ControlDropTarget& operator=(const ControlDropTarget& r) = delete;
	virtual ~ControlDropTarget();

public:
	/** ���ù����Ŀؼ��ӿ�
	 * @param [in] pControl �ؼ��ӿ�
	 */
	void SetControl(Control* pControl);

	/** ��ȡ�ؼ��ӿ�
	*/
	Control* GetControl() const;

	/** �жϵ������Ƿ�����ڸÿؼ���
	* @param [in] screenPt ��Ļ�����
	*/
	bool ContainsPt(const UiPoint& screenPt) const;

public:

    //IDropTarget::DragEnter
    virtual int32_t DragEnter(void* pDataObj, uint32_t grfKeyState, const UiPoint& pt, uint32_t* pdwEffect);

    //IDropTarget::DragOver
    virtual int32_t DragOver(uint32_t grfKeyState, const UiPoint& pt, uint32_t* pdwEffect);

    //IDropTarget::DragLeave
    virtual int32_t DragLeave(void);

    //IDropTarget::Drop
    virtual int32_t Drop(void* pDataObj, uint32_t grfKeyState, const UiPoint& pt, uint32_t* pdwEffect);

private:
	/** �����Ŀؼ��ӿ�
	*/
	Control* m_pControl;
};

} // namespace ui

#endif // UI_CORE_CONTROL_DROP_TARGET_H_
