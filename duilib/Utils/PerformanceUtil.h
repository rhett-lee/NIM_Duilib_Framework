#ifndef UI_UTILS_PERFORMANCE_UTIL_H_
#define UI_UTILS_PERFORMANCE_UTIL_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <string>
#include <map>
#include <chrono>

namespace ui 
{

/** ����ִ�����ܷ�������
*/
class UILIB_API PerformanceUtil
{
public:
	PerformanceUtil();
	~PerformanceUtil();

	/** ��������
	*/
	static PerformanceUtil& Instance();

	/** ���뿪ʼִ�У���ʼ��ʱ
	* @param [in] name ͳ���������
	*/
	void BeginStat(const std::wstring& name);

	/** �������ִ�У�ͳ��ִ������
	* @param [in] name ͳ���������
	*/
	void EndStat(const std::wstring& name);
	
private:
	/** ��¼ÿ��ͳ�ƵĽ��
	*/
	struct TStat
	{
		//�Ƿ��п�ʼ����
		bool hasStarted = false;

		//��ʼʱ��
		std::chrono::steady_clock::time_point startTime;

		//����ʱ��
		std::chrono::steady_clock::time_point endTime;

		//����ִ����ʱ�䣺΢��(ǧ��֮һ����)
		std::chrono::microseconds totalTimes = std::chrono::microseconds::zero();

		//ͳ���ܴ���
		uint32_t totalCount = 0;

		/** ������󣺣�΢��(ǧ��֮һ����)
		*/
		std::chrono::microseconds maxTime = std::chrono::microseconds::zero();
	};

	std::map<std::wstring, TStat> m_stat;
};

class PerformanceStat
{
public:
	PerformanceStat(const std::wstring& statName):
		m_statName(statName)
	{
		PerformanceUtil::Instance().BeginStat(m_statName);
	}
	~PerformanceStat()
	{
		PerformanceUtil::Instance().EndStat(m_statName);
	}
private:
	std::wstring m_statName;
};

}

#endif // UI_UTILS_PERFORMANCE_UTIL_H_