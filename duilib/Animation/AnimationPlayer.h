#ifndef UI_ANIMATION_ANIMATIONPLAYER_H_
#define UI_ANIMATION_ANIMATIONPLAYER_H_

#pragma once

#include "duilib/duilib_defs.h"
#include "base/callback/callback.h"
#include <functional>
#include <chrono>

namespace ui 
{

typedef std::function<void (int64_t)> PlayCallback;		//���Żص�����
typedef std::function<void (void)> CompleteCallback;	//������ɻص�����

/** �����������Ļ���ӿ�
*/
class UILIB_API AnimationPlayerBase : public virtual nbase::SupportWeakCallback
{
public:
	AnimationPlayerBase();
	virtual ~AnimationPlayerBase() = default;

	AnimationPlayerBase(const AnimationPlayerBase& r) = delete;
	AnimationPlayerBase& operator=(const AnimationPlayerBase& r) = delete;

public:
	/** ���ö�������
	*/
	void SetAnimationType(AnimationType type) { m_animationType = type; };

	/** ��ȡ��������
	*/
	AnimationType GetAnimationType() const { return m_animationType; };
	
	/** ���ò�����ʼֵ
	*/
	void SetStartValue(int64_t startValue) { m_startValue = startValue; }

	/** ��ȡ������ʼֵ
	*/
	int64_t GetStartValue() const { return m_startValue; }

	/** ���ò��Ž���ֵ
	*/
	void SetEndValue(int64_t endValue) { m_endValue = endValue; }

	/** ��ȡ���Ž���ֵ
	*/
	int64_t GetEndValue() const { return m_endValue; }

	/** �����ܵĲ���ʱ�䣨���룩
	*/
	void SetTotalMillSeconds(int64_t totalMillSeconds) { m_totalMillSeconds = totalMillSeconds; }

	/** ��ȡ�ܵĲ���ʱ�䣨���룩
	*/
	int64_t GetTotalMillSeconds() const { return m_totalMillSeconds; }

	/** ���ò��Żص�����
	*/
	void SetCallback(const PlayCallback& callback) { m_playCallback = callback; }

	/** ���ò�����ɻص�����
	*/
	void SetCompleteCallback(const CompleteCallback& callback) { m_completeCallback = callback; }

	/** ֹͣ��������Դ
	*/
	void Clear();

	/** ����״̬
	*/
	void Reset();

	/** �Ƿ����ڲ�����
	*/
	bool IsPlaying() const { return m_bPlaying; }

	/** �Ƿ��һ�β���
	*/
	bool IsFirstRun() const { return m_bFirstRun; }

	/** ��ʼ��
	*/
	virtual void Init();

	/** ������ʼ
	*/
	virtual void Start();

	/** ��������
	*/
	virtual void Stop();

	/** ��������������ʼֵ �� ����ֵ��
	*/
	virtual void Continue();

	/** ��������������ӽ���ֵ �� ��ʼֵ�����򶯻���
	*/
	virtual void ReverseContinue();

	/** ����������ʱ��
	*/
	virtual void StartTimer();

	/** ��ȡ������ǰֵ
	*/
	virtual int64_t GetCurrentValue() const = 0;

private:
	/** ����һ�ζ������ڶ�ʱ���д������ã�
	*/
	void Play();

	/** ������ʼֵ�ͽ���ֵ
	*/
	void ReverseAllValue();

	/** ��ɲ��Ŷ�����������������ɻص�����
	*/
	void Complete();

protected:
	/** ��������
	*/
	AnimationType m_animationType;

	/** ��ʼֵ
	*/
	int64_t m_startValue;

	/** ����ֵ
	*/
	int64_t m_endValue;

	/** ��ǰֵ
	*/
	int64_t m_currentValue;

	/** �����ܵ�ʱ�䣨���룩
	*/
	int64_t m_totalMillSeconds;

	/** �����Ѿ����ŵ�ʱ�䣨���룩
	*/
	int64_t m_palyedMillSeconds;

	/** �������ŵ�ʱ����������ʱ���Ĵ���ʱ���������룩
	*/
	int64_t m_elapseMillSeconds;

	/** �Ƿ��һ�β���
	*/
	bool m_bFirstRun;

	/** �Ƿ����ڲ�����
	*/
	bool m_bPlaying;

	/** �Ƿ����ڷ��򲥷�
	*/
	bool m_reverseStart;

	/** ���Żص�����
	*/
	PlayCallback m_playCallback;

	/** ������ɻص�����
	*/
	CompleteCallback m_completeCallback;
	
	/** ���ŵĿ�ʼʱ���
	*/
	std::chrono::steady_clock::time_point m_startTime;
	
	/** ��ʱ����ֹ��־
	*/
	nbase::WeakCallbackFlag m_weakFlagOwner;
};


class UILIB_API AnimationPlayer : 
	public AnimationPlayerBase
{
public:
	AnimationPlayer();
	virtual ~AnimationPlayer() = default;
	AnimationPlayer(const AnimationPlayer& r) = delete;
	AnimationPlayer& operator=(const AnimationPlayer& r) = delete;

public:
	/** ��ʼ��
	*/
	virtual void Init() override;

	/** ����������ʱ��
	*/
	virtual void StartTimer() override;

	/** ��ȡ������ǰֵ
	*/
	virtual int64_t GetCurrentValue() const override;

	/** ���ü�������A
	*/
	virtual void SetSpeedUpfactorA(double factorA) { m_speedUpfactorA = factorA; }

	/** ���ü�������A
	*/
	virtual void SetSpeedDownfactorA(double factorA) { m_speedDownfactorA = factorA; }

	/** ������󲥷�ʱ�䣨���룩
	*/
	void SetMaxTotalMillSeconds(int64_t maxTotalMillSeconds) { m_maxTotalMillSeconds = maxTotalMillSeconds; }

	/** ���������ٶȣ�ֵ/���룩
	*/
	void SetLinearSpeed(double linearSpeed) { m_linearSpeed = linearSpeed; }

	/** ���ü��ٱ���
	*/
	void SetSpeedUpRatio(double speedUpRatio) { m_speedUpRatio = speedUpRatio; }

	/** ���ü��ٱ���
	*/
	void SetSpeedDownRatio(double speedDownRatio) { m_speedDownRatio = speedDownRatio; }

private:
	/** ��ʼ��������������
	*/
	void InitFactor();

private:
	/** ���ٱ���
	*/
	double m_speedUpRatio;

	/** ���ٶ�����ʱ�䣨���룩
	*/
	double m_speedUpMillSeconds;

	/** ���ٱ���
	*/
	double m_speedDownRatio;

	/** ���ٶ�����ʱ�䣨���룩
	*/
	double m_speedDownMillSeconds;

	/** �����ٶȣ�ֵ/���룩
	*/
	double m_linearSpeed;

	/** ���Լ��ٶ�����ʱ�䣨���룩
	*/
	double m_linerMillSeconds;
	
	/** ��������A
	*/
	double m_speedUpfactorA;

	/** ��������A
	*/
	double m_speedDownfactorA;

	/** ��������B
	*/
	double m_speedDownfactorB;

	/** ��󲥷�ʱ�䣨���룩
	*/
	int64_t m_maxTotalMillSeconds;
};

} // namespace ui

#endif // UI_ANIMATION_ANIMATIONPLAYER_H_
