#ifndef UI_CORE_TIMER_MANAGER_H_
#define UI_CORE_TIMER_MANAGER_H_

#pragma once

#include "duilib/duilib_defs.h"
#include "base/callback/callback.h"
#include <queue>

namespace ui 
{

/** ��ʱ���ص�����ԭ�ͣ�void FunctionName();
*/
typedef std::function<void()> TimerCallback;
class TimerInfo;

/** ��ʱ��������
*/
class TimerManager
{
public:
	TimerManager();
	~TimerManager();
	TimerManager(const TimerManager&) = delete;
	TimerManager& operator = (const TimerManager&) = delete;

public:
	const static int REPEAT_FOREVER = -1;

	/** ���һ����ȡ���Ķ�ʱ��
	* @param [in] weakFlag ��ʱ��ȡ�����ƣ����weakFlag.expired()Ϊtrue��ʾ��ʱ���Ѿ�ȡ���������ڼ����ɷ���ʱ���ص�
	* @param [in] callback ��ʱ���ص�����
	* @param [in] uElapse ��ʱ������ʱ��������λΪ����
	* @param [in] iRepeatTime ��ʱ���ص��������ƣ����Ϊ -1 ��ʾ��ͣ�ظ��ص�
	*/
	bool AddCancelableTimer(const std::weak_ptr<nbase::WeakFlag>& weakFlag,
		                    const TimerCallback& callback,
		                    uint32_t uElapse, 
		                    int32_t iRepeatTime);

	/** �رն�ʱ�����������ͷ���Դ
	 */
	void Clear();

private:
	/** ��Ϣ���ں���
	*/
	static LRESULT CALLBACK WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	/** ��ʱ���ص�����
	*/
	static void CALLBACK TimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

	/** ��ʱ�����������ж�ʱ���¼��ص��ɷ�
	*/
	void Poll();

	/** ֹͣ��ʱ��
	*/
	void KillTimerEvent();

private:
	/** ��Ϣ���ھ����������UI�߳����ɷ���ʱ���¼�
	*/
	HWND m_hMessageWnd;

	/** ����ע��Ķ�ʱ��
	*/
	std::priority_queue<TimerInfo> m_aTimers;

	/** ���ܼ�����Ƶ��(ÿ���ʱ�ӵδ���)
	*/
	LARGE_INTEGER m_timeFrequency;

	/** ��ǰϵͳ��ʱ���ļ���Ƿ�Ϊ��С���
	*/
	bool m_bMinInterval;

	/** ��ʱ��ID
	*/
	uint32_t m_nTimerId;
};

} // namespace ui

#endif // UI_CORE_TIMER_MANAGER_H_
