#ifndef UI_UTILS_BOXSHADOW_H_
#define UI_UTILS_BOXSHADOW_H_

#pragma once

#include "duilib/Core/UiPoint.h"
#include <string>

namespace ui {

/** �ؼ���Ӱ������
*/
class UILIB_API BoxShadow
{
public:
	BoxShadow();

	/**
	 * @brief ������Ӱ����
	 * @param[in] strBoxShadow Ҫ���õ�����,�� "color='black' offset='1,1' blur_radius='2' spread_radius='2'"
	 * @return ��
	 */
	void SetBoxShadowString(const std::wstring& strBoxShadow);

	/**
	 * @brief �Ƿ�����Ӱ
	 * @return �ǻ��
	 */
	bool HasShadow() const;

	// ��Ӱ����
	// ��ʱ����֧�� color offset blurSize
	// https://codersblock.com/blog/creating-glow-effects-with-css/

	/** ��Ӱ����ɫֵ
	*/
	std::wstring m_strColor;

	/** ������Ӱƫ������offset-x �� offset-y��
	 *                 <offset-x> ����ˮƽƫ����������Ǹ�ֵ����Ӱλ�ھ�����ߡ� 
	 *                 <offset-y> ���ô�ֱƫ����������Ǹ�ֵ����Ӱλ�ھ������档
	 */
	UiPoint m_cpOffset;

	/** ģ���뾶��ֵԽ��ģ�����Խ����Ӱ��Խ��Խ��, ���Ϊ0����ʱ��Ӱ��Ե��������ģ��Ч��������Ϊ��ֵ��
	 */
	int m_nBlurRadius;

	/** ��չ�뾶����ģ���������rc���α�Ե���ٸ����ء�ȡ��ֵʱ����Ӱ����ȡ��ֵʱ����Ӱ������
	 */
	int m_nSpreadRadius;
};

} // namespace ui

#endif // !UI_UTILS_BOXSHADOW_H_

