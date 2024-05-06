#ifndef UI_CORE_WINDOW_DROP_TARGET_H_
#define UI_CORE_WINDOW_DROP_TARGET_H_

#pragma once

#include "duilib/Core/UiTypes.h"

namespace ui 
{

class ControlDropTarget;
class Window;

/** ���ڵ��Ϸ�֧��
*/
class WindowDropTarget
{
public:
	WindowDropTarget();
	WindowDropTarget(const WindowDropTarget& r) = delete;
	WindowDropTarget& operator=(const WindowDropTarget& r) = delete;
	~WindowDropTarget();

public:
	/** ����������������
	 * @param [in] pWindow ����ָ��
	 */
	void SetWindow(Window* pWindow);

	/** ע��һ���ϷŽӿ�
	*/
	bool RegisterDragDrop(ControlDropTarget* pDropTarget);

	/** ע��һ���ϷŽӿ�
	*/
	bool UnregisterDragDrop(ControlDropTarget* pDropTarget);

	/** �����ϷŲ�������Դ, ע�����ڵ��ϷŲ����ӿ�
	*/
	void Clear();

private:
	/** ����ָ��
	*/
	Window* m_pWindow;

	/** ע��Ŀؼ��б�
	*/
	std::vector<ControlDropTarget*> m_dropTargets;

	/** DropTarget ��ʵ�ֽӿ�
	*/
	friend class WindowDropTargetImpl;
	WindowDropTargetImpl* m_pDropTargetImpl;
};

} // namespace ui

#endif // UI_CORE_WINDOW_DROP_TARGET_H_
