#ifndef UI_ANIMATION_ANIMATIONMANAGER_H_
#define UI_ANIMATION_ANIMATIONMANAGER_H_

#pragma once

#include "duilib/Animation/AnimationPlayer.h"
#include <map>
#include <memory>

namespace ui 
{
class Control;

/** �ؼ��Ķ������Ź�����
*/
class UILIB_API AnimationManager
{
public:
	AnimationManager();
	AnimationManager(const AnimationManager& r) = delete;
	AnimationManager& operator=(const AnimationManager& r) = delete;

	/** ��ʼ��
	* @param [in] pControl ���������ؼ��Ľӿ�
	*/
	void Init(Control* pControl)	{ m_pControl = pControl;	}

	/** ��ȡָ���������͵Ĳ��Žӿ�
	* @param [in] animationType ��������
	* @return ���ظ����͵Ķ������Žӿڣ����ƥ�䲻��������nullptr
	*/
	AnimationPlayer* GetAnimationPlayer(AnimationType animationType) const;

	/** ���û�������Ŷ�������Ӧ��������Ϊ��kAnimationAlpha
	* @param [in] bFadeHot true��ʾ���ö�����false��ʾ�������
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeHot(bool bFadeHot);

	/** ���û�������Ŷ�������Ӧ��������Ϊ��kAnimationHot
	* @param [in] bFadeVisible true��ʾ���ö�����false��ʾ�������
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeAlpha(bool bFadeVisible);

	/** ���û�������Ŷ�������Ӧ��������Ϊ��kAnimationWidth
	* @param [in] bFadeWidth true��ʾ���ö�����false��ʾ�������
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeWidth(bool bFadeWidth);

	/** ���û�������Ŷ�������Ӧ��������Ϊ��kAnimationHeight
	* @param [in] bFadeHeight true��ʾ���ö�����false��ʾ�������
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeHeight(bool bFadeHeight);

	/** ���û�������Ŷ���
	* @param [in] bFade true��ʾ���ö�����false��ʾ�������
	* @param [in] bIsFromRight true��ʾ���Ҳද����kAnimationInoutXFromRight����false��ʾ����ද����kAnimationInoutXFromLeft��
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeInOutX(bool bFade, bool bIsFromRight);

	/** ���û�������Ŷ���
	* @param [in] bFade true��ʾ���ö�����false��ʾ�������
	* @param [in] bIsFromBottom true��ʾ���²ද����kAnimationInoutYFromBottom����false��ʾ���ϲද����kAnimationInoutYFromTop��
	* @return ����ʱ���ض������Žӿڣ����ʱ����nullptr
	*/
	AnimationPlayer* SetFadeInOutY(bool bFade, bool bIsFromBottom);

	/** �����õĶ�������ʾ�ؼ�
	*/
	void Appear();

	/** �����õĶ��������ؿؼ�
	*/
	void Disappear();

	/** �������ʱ��������ִ�ж���
	*/
	void MouseEnter();

	/** ����Ƴ�ʱ��������ִ�ж���
	*/
	void MouseLeave();

	/** �������ж�����Դ
	*/
	void Clear(Control* control);

private:
	/** ���������ؼ��Ľӿ�
	*/
	Control* m_pControl;

	/** ÿ�����������µĶ������Žӿ�
	*/
	std::map<AnimationType, std::unique_ptr<AnimationPlayer>> m_animationMap;
};

} // namespace ui

#endif // UI_ANIMATION_ANIMATIONMANAGER_H_
