#include "TimerManager.h"
#include "duilib/Core/GlobalManager.h"
#include <Mmsystem.h>

namespace ui 
{

#define WM_USER_DEFINED_TIMER	(WM_USER + 9999)

/** ϵͳ��ʱ������ʱ��������λΪ����
*/
#define TIMER_INTERVAL	16

/** ��ʱ���������ȣ���λΪ����
*/
#define TIMER_PRECISION	1

/** ��ʱ��������
*/
class TimerInfo
{
public:
	TimerInfo(): 
		timerCallback(nullptr),
		uPerformanceCount(0),
		uRepeatTime(0)
	{
		dwEndPerformanceCounter.QuadPart = 0;
	}

	bool operator < (const TimerInfo& timerInfo) const {
		//�������������ȴ���������ǰ��
		return dwEndPerformanceCounter.QuadPart > timerInfo.dwEndPerformanceCounter.QuadPart;
	}

	//��ʱ���ص�����
	TimerCallback timerCallback;

	//��ʱ�����������λ�����ܼ������ĵδ������
	LONGLONG uPerformanceCount;

	//�ظ�����: -1 ��ʾ��ͣ�ظ�
	uint32_t uRepeatTime;

	//��ʱ������ʱ��: ���ܼ�����������ֵ
	LARGE_INTEGER dwEndPerformanceCounter;

	//ȡ����ʱ��ͬ������
	std::weak_ptr<nbase::WeakFlag> weakFlag;
};

TimerManager::TimerManager() : 
	m_hMessageWnd(nullptr),
	m_aTimers(),
	m_bMinInterval(true),
	m_nTimerId(0)
{
	::QueryPerformanceFrequency(&m_timeFrequency); 
	auto hinst = ::GetModuleHandle(NULL);
	WNDCLASSEXW wc = {0};
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WndProcThunk;
	wc.hInstance = hinst;
	wc.lpszClassName = L"UI_ANIMATION_TIMERMANAGER_H_";
	::RegisterClassExW(&wc);
	m_hMessageWnd = ::CreateWindowW(L"UI_ANIMATION_TIMERMANAGER_H_", 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, hinst, 0);
}

TimerManager::~TimerManager()
{
	if (m_hMessageWnd != nullptr) {
		::DestroyWindow(m_hMessageWnd);
		m_hMessageWnd = nullptr;
	}
}

LRESULT TimerManager::WndProcThunk(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_USER_DEFINED_TIMER) {
		//�Ƴ������ж������Ϣ������������д������õ��ظ���Ϣ�������޷�������������Ϣ
		size_t msgCount = 0;
		MSG msg;
		while (::PeekMessage(&msg, hwnd, WM_USER_DEFINED_TIMER, WM_USER_DEFINED_TIMER, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				//��⵽�˳���Ϣ�����·ŵ���Ϣ�����У���������˲���
				::PostQuitMessage(static_cast<int>(msg.wParam));
				return ::DefWindowProcW(hwnd, message, wparam, lparam);
			}
			ASSERT(msg.message == WM_USER_DEFINED_TIMER);
			++msgCount;
		}
//#ifdef _DEBUG
//		if (msgCount > 0) {
//			char str[256] = { 0 };
//			sprintf_s(str, "TimerManager::WndProcThunk eat msgs: %d\n", (int)msgCount);
//			::OutputDebugStringA(str);
//		}
//#endif
		GlobalManager::Instance().Timer().Poll();
		return 1;
	}
	return ::DefWindowProcW(hwnd, message, wparam, lparam);
}

void TimerManager::TimeCallback(UINT /*uTimerID*/, UINT /*uMsg*/, DWORD_PTR /*dwUser*/, DWORD_PTR /*dw1*/, DWORD_PTR /*dw2*/)
{
	HWND hWnd = GlobalManager::Instance().Timer().m_hMessageWnd;
	::PostMessage(hWnd, WM_USER_DEFINED_TIMER, 0, 0);
}

bool TimerManager::AddCancelableTimer(const std::weak_ptr<nbase::WeakFlag>& weakFlag, 
									  const TimerCallback& callback, 
									  uint32_t uElapse, 
								      int32_t iRepeatTime)
{
	ASSERT(uElapse > 0);

	TimerInfo pTimer;
	pTimer.timerCallback = callback;
	//�������Ҫ�δ���ٴ�
	pTimer.uPerformanceCount = uElapse * m_timeFrequency.QuadPart / 1000;
	::QueryPerformanceCounter(&pTimer.dwEndPerformanceCounter);
	//������´δ���ʱ��ʱ�ӵδ���
	pTimer.dwEndPerformanceCounter.QuadPart += pTimer.uPerformanceCount;
	pTimer.uRepeatTime = static_cast<uint32_t>(iRepeatTime);
	pTimer.weakFlag = weakFlag;
	m_aTimers.push(pTimer);
	
	if ((m_nTimerId == 0) || !m_bMinInterval) {
		KillTimerEvent();
		m_nTimerId = ::timeSetEvent(TIMER_INTERVAL, TIMER_PRECISION, &TimerManager::TimeCallback, NULL, TIME_PERIODIC);
		ASSERT(m_nTimerId != 0);
		m_bMinInterval = true;
	}

	return true;
}

void TimerManager::Poll()
{
	LARGE_INTEGER currentTime;
	::QueryPerformanceCounter(&currentTime);

	while (!m_aTimers.empty()) {
		//����ɾ���Ѿ�ȡ���Ķ�ʱ��
		if (m_aTimers.top().weakFlag.expired()) {
			m_aTimers.pop();
			continue;
		}
		LONGLONG detaTime = m_aTimers.top().dwEndPerformanceCounter.QuadPart - currentTime.QuadPart;
		if (detaTime <= 0) {
			//���ж��Ķ�ʱ�����Ѿ��ﵽ��ʱ����������
			TimerInfo it = m_aTimers.top();
			m_aTimers.pop();

			if (!it.weakFlag.expired()) {
				it.timerCallback();
				bool rePush = false;
				if (it.uRepeatTime > 0) {
					it.uRepeatTime--;
					if (it.uRepeatTime > 0) {
						rePush = true;
					}
				}
				if (rePush) {
					//���δ�ﵽ�����������ƣ����������´δ����ĵδ���
					TimerInfo rePushTimerInfo = it;
					rePushTimerInfo.dwEndPerformanceCounter.QuadPart = currentTime.QuadPart + it.uPerformanceCount;
					m_aTimers.push(rePushTimerInfo);
				}
			}
		}
		else if ((detaTime > 0) && (detaTime < m_timeFrequency.QuadPart)) {
			//���ж��Ķ�ʱ������ʱ����1������, ʹ����С����ľ�ȷ��ʱ��
			if (!m_bMinInterval) {
				KillTimerEvent();
				m_nTimerId = ::timeSetEvent(TIMER_INTERVAL, TIMER_PRECISION, &TimerManager::TimeCallback, NULL, TIME_PERIODIC);
				ASSERT(m_nTimerId != 0);
				m_bMinInterval = true;
			}
			break;
		}
		else {
			//���ж��Ķ�ʱ������ʱ�������Ժ󣬷Ŵ�ʱ���Ĵ������ʱ�䣬��������ʱ���������2���루�Ż����ܣ�����ϵͳ��ʱ��Ƶ��������
			double newDetaTime = double(detaTime) * 1000 / m_timeFrequency.QuadPart;
			KillTimerEvent();
			m_nTimerId = ::timeSetEvent(int(newDetaTime + 2 * TIMER_PRECISION), TIMER_PRECISION, &TimerManager::TimeCallback, NULL, TIME_PERIODIC);
			ASSERT(m_nTimerId != 0);
			m_bMinInterval = false;
			break;
		}
	}

	if (m_aTimers.empty()) {
		KillTimerEvent();
	}
}

void TimerManager::KillTimerEvent()
{
	if (m_nTimerId != 0) {
		::timeKillEvent(m_nTimerId);
		m_nTimerId = 0;
	}
}

void TimerManager::Clear()
{
	KillTimerEvent();
	if (m_hMessageWnd != nullptr) {
		::DestroyWindow(m_hMessageWnd);
		m_hMessageWnd = nullptr;
	}	
	while (!m_aTimers.empty()) {
		m_aTimers.pop();
	}
	m_bMinInterval = true;
}

}