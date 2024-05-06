#ifndef UI_UTILS_DPIMANAGER_H_
#define UI_UTILS_DPIMANAGER_H_

#pragma once

#include "duilib/Core/UiTypes.h"

namespace ui
{
/** @class DpiManager
  * @brief DPI���������
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2016/10/10
  */
class UILIB_API DpiManager
{
public:
	DpiManager();
	~DpiManager();
	DpiManager(const DpiManager&) = delete;
	DpiManager& operator = (const DpiManager&) = delete;

public:
	/** �����Ƿ�֧��DPI����Ӧ��������Ĭ�����ű�
	* @param [in] bAdaptDPI true��ʾ֧��DPI����Ӧ��false��ʾ��֧��DPI����Ӧ
	*/
	bool SetAdaptDPI(bool bAdaptDPI);

	/** �Ƿ�֧������DPI����Ч��(Ĭ�ϲ�֧�֣���Ҫ����SetAdaptDPI���ò���֧��)
	*/
	bool IsAdaptDPI() const;

	/** ��ȡ��ǰ�������űȣ�100���������ţ�
	* @return ���ű�
	*/
	uint32_t GetScale() const;

	/** ��ǰ�����Ƿ���DPI����
	* @return �����ǰ�������ű�Ϊ100����false�����򷵻�true
	*/
	bool IsScaled() const;

	/** ����DPIֵ���ý������űȣ�ֻ��IsAdaptDPI()Ϊtrue��ʱ����Ч��
	* @param[in] uDPI DPIֵ
	*/
	bool SetScale(uint32_t uDPI);

	/** ���ݽ������ű�����������
	* @param[in] iValue ����
	* @return int ���ź��ֵ
	*/
	int32_t ScaleInt(int32_t& iValue);
	int32_t GetScaleInt(int32_t iValue);
	uint32_t GetScaleInt(uint32_t iValue);

	/** ���ݽ������ű�������SIZE
	* @param[in] size ��Ҫ���ŵ�Size����
	*/
	void ScaleSize(SIZE& size);
	void ScaleSize(UiSize& size);

	/** ���ݽ������ű�������POINT
	* @param[in] point ��Ҫ���ŵ�point����
	*/
	void ScalePoint(POINT& point);
	void ScalePoint(UiPoint& point);

	/** ���ݽ������ű�������RECT
	* @param[in] rect ��Ҫ���ŵ�rect����
	* @return void	�޷���ֵ
	*/
	void ScaleRect(RECT& rect);
	void ScaleRect(UiRect& rect);
	void ScalePadding(UiPadding& padding);
	void ScaleMargin(UiMargin& margin);

private:
	/** ��ȡĳ����ʾ����DPI������DPI��֪����Ч
	* @param[in] HMONITOR���
	* @return ���� DPIֵ
	*/
	uint32_t GetMonitorDPI(HMONITOR hMonitor);

	/** ��ȡ����ʾ��DPI������DPI��֪����Ч
	* @return ���� DPIֵ
	*/
	uint32_t GetMainMonitorDPI();

	/** MulDiv ������װ
	*/
	int32_t MulDiv(int32_t nNumber, int32_t nNumerator, int32_t nDenominator);

private:
	//DPI�������ӣ�100��ʾ������
	uint32_t m_nScaleFactor;

	//�Ƿ���DPI����Ӧ
	bool m_bAdaptDPI;
};
}
#endif //UI_UTILS_DPIMANAGER_H_