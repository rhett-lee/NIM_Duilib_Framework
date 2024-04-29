#ifndef UI_CORE_PLACE_HOLDER_H_
#define UI_CORE_PLACE_HOLDER_H_

#pragma once

#include "base/callback/callback.h"
#include "duilib/Core/UiTypes.h"
#include <string>
#include <memory>

namespace ui 
{
	class Box;
	class Window;

/** �ؼ���λ�á���С�������״�Ļ�����װ
*/
class UILIB_API PlaceHolder : public virtual nbase::SupportWeakCallback
{
public:
	PlaceHolder();
	PlaceHolder(const PlaceHolder& r) = delete;
	PlaceHolder& operator=(const PlaceHolder& r) = delete;
	virtual ~PlaceHolder();

	/** �ؼ�����
	*/
	virtual std::wstring GetType() const;

	/** ��ȡ�ؼ����ƣ���Ӧ xml �� name ����
	 */
	std::wstring GetName() const;

	/** ��ȡ�ؼ����ƣ���Ӧ xml �� name ����
	 * @return ���ؿؼ����ƣ�UTF8 ���룩
	 */
	std::string GetUTF8Name() const;

	/** ���ÿؼ����ƣ��ڴ������ò���д�� xml ��
	 * @param [in] strName Ҫ���õ�����
	 */
	void SetName(const std::wstring& strName);

	/** ���ÿؼ����ƣ��ڴ������ò���д�� xml �У�UTF8 ���룩
	 * @param[in] strName Ҫ���õ�����
	 */
	void SetUTF8Name(const std::string& strName);

	/** �жϿؼ������Ƿ����
	*/
	bool IsNameEquals(const std::wstring& name) const;

	/** �������ƻ�ȡ��������ָ��
	* @param [in] strName Ҫ��ȡ��������������
	*/
	Box* GetAncestor(const std::wstring& strName);

	/** ����������������
	 * @param [in] pParent ������ָ��
	 */
	virtual void SetParent(Box* pParent);

	/** ����������������
	 * @param [in] pManager ����ָ��
	 */
	virtual void SetWindow(Window* pManager);

	/** ��ȡ������ָ��
	*/
	Box* GetParent() const { return m_pParent; }

	/** ��ȡ�����Ĵ���ָ��
	 * @return ���ع������ڵ�ָ��
	 */
	Window* GetWindow() const { return m_pWindow; }

	/** ��ʼ������(���ÿؼ�����ӵ����ؼ���ʱ�򣬵��ø�Init����)
	 */
	virtual void Init();

	/** �Ƿ��Ѿ���ʼ��
	*/
	bool IsInited() const;

	/**@brief ���øÿؼ��Ƿ�ɼ�
	 */
	virtual void SetVisible(bool bVisible);

	/**@brief �ж��Ƿ�ɼ�
	 */
	virtual bool IsVisible() const { return m_bVisible; }

	/**@brief �жϿؼ��Ƿ񸡶�״̬����Ӧ xml �� float ����
	 */
	bool IsFloat() const { return m_bFloat; }

	/**@brief ���ÿؼ��Ƿ񸡶�
	 * @param[in] bFloat ����Ϊ true Ϊ������false Ϊ������
	 */
	void SetFloat(bool bFloat);

public:
	/** ��ȡ�ؼ����õĿ�Ⱥ͸߶ȣ���߾������ڱ߾࣬������������߾�
	*/
	const UiFixedSize& GetFixedSize() const;

	/** ��ȡ���õĿ�ȣ������ڱ߾࣬��������߾ࣩ����Ӧ xml �� width ����; ���δ���ã�Ĭ��ֵ������
	 */
	const UiFixedInt& GetFixedWidth() const;

	/** ��ȡ�̶��߶ȣ������ڱ߾࣬��������߾ࣩ����Ӧ xml �� height ����; ���δ���ã�Ĭ��ֵ������
	 */
	const UiFixedInt& GetFixedHeight() const;

	/**@brief ���ÿؼ��Ŀ��
	 * @param[in] cx Ҫ���õĿ�ȣ������ڱ߾࣬��������߾ࣩ
	 * @param[in] bArrange �Ƿ��������У�Ĭ��Ϊ true
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 */
	void SetFixedWidth(UiFixedInt cx, bool bArrange, bool bNeedDpiScale);

	/** ���ÿؼ��Ŀ�ȣ������ڱ߾࣬��������߾ࣩ��������ʹ�õĽӿ�
	*/
	void SetFixedWidth64(int64_t cx64);

	/**@brief ���ÿؼ��ĸ߶�
	 * @param[in] cy Ҫ���õĹ̶��߶ȣ������ڱ߾࣬��������߾ࣩ
	 * @param[in] bArrange �Ƿ��������У�Ĭ��Ϊ true
	 * @param[in] bNeedDpiScale ���� DPI ���ţ�Ĭ��Ϊ true
	 */
	void SetFixedHeight(UiFixedInt cy, bool bArrange, bool bNeedDpiScale);

	/** ���ÿؼ��ĸ߶ȣ������ڱ߾࣬��������߾ࣩ��������ʹ�õĽӿ�
	*/
	void SetFixedHeight64(int64_t cy64);

public:
	/** �ж��Ƿ���Ҫ����������С
	* @param [in] szAvailable ����ʱ��������δ�С
	*/
	bool IsReEstimateSize(const UiSize& szAvailable) const;

	/** �����Ƿ���Ҫ����������С
	* @param [in] bReEstimateSize �Ƿ���Ҫ���¹���
	*/
	void SetReEstimateSize(bool bReEstimateSize);

	/** ��ȡ�ؼ����ѹ����С�����ȺͿ�ȣ����൱��EstimateSize���������Ļ���ֵ
	*/
	const UiEstSize& GetEstimateSize() const;

	/**@brief ���ÿؼ����ѹ����С�����ȺͿ�ȣ����൱��EstimateSize���������Ļ���ֵ
	*@param [in] szEstimateSize ����Ľ������Ϊ���汣������
	*@param [in] szAvailable szAvailable ����ʱ��������δ�С
	*/
	void SetEstimateSize(const UiEstSize& szEstimateSize, const UiSize& szAvailable);

public:
	/** ��ȡ��С���
	* @return ������С��ȣ������ڱ߾࣬��������߾ࣩ������ֵ >= 0��
	*/
	int32_t GetMinWidth() const;

	/**@brief ������С���
	 * @param [in] cx Ҫ���õ���С��ȣ������ڱ߾࣬��������߾ࣩ��ֵ >= 0��
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetMinWidth(int32_t cx, bool bNeedDpiScale = true);

	/** ��ȡ�����
	* @return ��������ȣ������ڱ߾࣬��������߾ࣩ������ֵ >= 0��
	*/
	int32_t GetMaxWidth() const;

	/** ���������
	 * @param [in] cx Ҫ���õ�����ȣ������ڱ߾࣬��������߾ࣩ��ֵ >= 0��
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetMaxWidth(int32_t cx, bool bNeedDpiScale = true);

	/** ��ȡ��С�߶�
	* @return ������С�߶ȣ������ڱ߾࣬��������߾ࣩ������ֵ >= 0��
	*/
	int32_t GetMinHeight() const;

	/** ������С�߶�
	 * @param [in] cy Ҫ���õ���С�߶ȣ������ڱ߾࣬��������߾ࣩ��ֵ >= 0��
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetMinHeight(int32_t cy, bool bNeedDpiScale = true);

	/** ��ȡ���߶�
	* @return �������߶ȣ������ڱ߾࣬��������߾ࣩ������ֵ >= 0��
	*/
	int32_t GetMaxHeight() const;

	/** �������߶�
	 * @param[in] cy Ҫ���õ����߶ȣ������ڱ߾࣬��������߾ࣩ��ֵ >= 0��
	 * @param [in] bNeedDpiScale �Ƿ���Ҫ��DPI����Ӧ
	 */
	void SetMaxHeight(int32_t cy, bool bNeedDpiScale = true);

	/** ��ȡʵ�ʿ�ȣ������ڱ߾࣬��������߾ࣩ
	 */
	int32_t GetWidth() const { return m_uiRect.Width(); }

	/** ��ȡʵ�ʸ߶ȣ������ڱ߾࣬��������߾ࣩ
	 */
	int32_t GetHeight() const { return m_uiRect.Height(); }

	/**@brief ��ȡˮƽ���뷽ʽ�� �ο� HorAlignType ö��
	 */
	HorAlignType GetHorAlignType() const;

	/**@brief ����ˮƽ���뷽ʽ
	 * @param[in] horAlignType Ҫ���õĶ��뷽ʽ���ο� HorAlignType ö��
	 */
	void SetHorAlignType(HorAlignType horAlignType);

	/**@brief ��ȡ��ֱ���뷽ʽ���μ� VerAlignType ö��
	 */
	VerAlignType GetVerAlignType() const;

	/**@brief ���ô�ֱ���뷽ʽ
	 * @param[in] vorAlignType Ҫ���õĶ��뷽ʽ���ο� VerAlignType ö��
	 */
	void SetVerAlignType(VerAlignType verAlignType);

	/** ��ȡ�ؼ�����߾�
	 */
	UiMargin GetMargin() const;

	/** ���ÿؼ�����߾�
	 * @param[in] rcMargin �ؼ�����߾���Ϣ
	 * @param[in] bNeedDpiScale �Ƿ�����߾���� DPI ���䣬false ������ DPI
	 */
	void SetMargin(UiMargin rcMargin, bool bNeedDpiScale);

	/** ��ȡ�ڱ߾�
	 * @return �����ڱ߾��ıߵĴ�С��Rect���ĸ������ֱ�����ĸ��ߵ��ڱ߾ࣩ
	 */
	UiPadding GetPadding() const;

	/** �����ڱ߾�
	 * @param[in] rcPadding �ڱ߾�����
	 * @param[in] bNeedDpiScale �Ƿ���� DPI ����Ӧ��Ĭ��Ϊ true
	 */
	void SetPadding(UiPadding rcPadding, bool bNeedDpiScale);

	/** �Ƿ�����ؼ����������ڱ߾�
	* @param [in] bEnable true��ʾ�ؼ�����Ҳ�����ڱ߾ࣨBox��Control����
						  false��ʾ�ؼ����������ڱ߾࣬�ڱ߾�����ڲ����ӿؼ���Box�������
	*/
	void SetEnableControlPadding(bool bEnable);

	/** �жϿؼ������Ƿ����������ڱ߾�
	* @return true��ʾ�ؼ�����Ҳ�����ڱ߾ࣨBox��Control����
		      false��ʾ�ؼ����������ڱ߾࣬�ڱ߾�����ڲ����ӿؼ���Box�������
	*/
	bool IsEnableControlPadding() const;

	/** ��ȡ�ؼ�������ڱ߾ࣨ�������Ϊ��ֹ�����ڱ߾࣬�򷵻ؿգ�
	* @return �����ڱ߾��ıߵĴ�С��Rect���ĸ������ֱ�����ĸ��ߵ��ڱ߾ࣩ
	*/
	UiPadding GetControlPadding() const;

	/** ��ȡ�ؼ�λ�ã�����ɸı���Ϊ��
	* @return ���ؿؼ��ľ������򣬰����ڱ߾࣬��������߾�
	 */
	virtual	UiRect GetPos() const { return m_uiRect; }

	/** ���ÿؼ�λ�ã�����ɸı���Ϊ��
	 * @param [in] rc Ҫ���õľ���������Ϣ�������ڱ߾࣬��������߾�
	 */
	virtual void SetPos(UiRect rc);

	/** ��ȡ�ؼ���������(��������m_uiRectֵ)�������ڱ߾࣬��������߾�
	*/
	const UiRect& GetRect() const { return m_uiRect; }

	/** ���ÿؼ���������(��������m_uiRectֵ)�������ڱ߾࣬��������߾�
	*/
	void SetRect(const UiRect& rc);

	/** �ػ�ؼ�
	*/
	virtual void Invalidate();

	/** �ػ�ؼ��Ĳ�������
	* @param [in] rc ��Ҫ�ػ������
	*/
	virtual void InvalidateRect(const UiRect& rc);

	/** �ؼ���������
	 */
	virtual void Arrange();

	/** �ø��������в�������
	 */
	virtual void ArrangeAncestor();

	/** ���ݿؼ����ԣ��ж���Ҫ���Ų��ֻ���ֻ���ػ�
	*/
	void RelayoutOrRedraw();

	/** �ж��Ƿ��Ѿ����й�
	 */
	bool IsArranged() const { return m_bIsArranged; }

	/** �����Ƿ��Ѿ����й�
	 */
	void SetArranged(bool bArranged);

	/** �����Ƿ�ʹ�û���
	 */
	void SetUseCache(bool cache);

	/** �ж��Ƿ�ʹ�û���
	 */
	bool IsUseCache() { return m_bUseCache; }

	/** ���û������־λ
	 */
	void SetCacheDirty(bool dirty);

	/** �жϻ������־λֵ
	 */
	bool IsCacheDirty() { return m_bCacheDirty; }

	/** ��ȡ������ƫ��
	 */
	UiPoint GetScrollOffsetInScrollBox() const;

	/** �ж������ؼ��Ƿ���ڸ���/�����ϵ
	 */
	bool IsChild(PlaceHolder* pAncestor, PlaceHolder* pChild) const;

protected:
	/** ���Լ�����
	 */
	virtual void ArrangeSelf();

	/** ִ�г�ʼ���������¼���ÿ���ؼ��ڳ�ʼ��ʱ������øú���������ֻ����һ�Σ�
	 *  �ú���ִ��ʱ��IsInited()��ֵΪfalse�����IsInited()Ϊtrue����ʾOnInit()�����ظ�ִ���ˡ�
	 */
	virtual void OnInit();

private:
	//�ؼ����ƣ����ڲ��ҿؼ��Ȳ���
	UiString m_sName;

	//�����Ĵ��ڶ���
	Window* m_pWindow;

	//���ؼ�����
	Box* m_pParent;

	//�ؼ�λ�����С
	UiRect m_uiRect;

	//�ⲿ���õĿؼ���С
	UiFixedSize m_cxyFixed;

	//����ؼ���С�Ľ��
	UiEstResult m_estResult;

	//�ؼ���С��Сֵ
	UiSize m_cxyMin;

	//�ؼ���С���ֵ
	UiSize m_cxyMax;

	//�ؼ�ˮƽ���뷽ʽ(HorAlignType)
	int8_t m_horAlignType;

	//�ؼ���ֱ���뷽ʽ(VerAlignType)
	int8_t m_verAlignType;

	//�ؼ�����߾����ԣ��ϣ��£����ұ߾ࣩ����߾���m_uiRect����Ŀռ䣬��������m_uiRect����
	UiMargin16 m_rcMargin;

	//�ڱ߾��ıߵĴ�С���ϣ��£����ұ߾ࣩ���ڱ߾��ǿؼ��������ڵĿռ䣬�ǰ����ڿؼ��������ڵ�
	UiPadding16 m_rcPadding;

	//�Ƿ�����ؼ����������ڱ߾�
	//(ԭ�����߼���Control�������ڱ߾࣬Box��Layout���ڱ߾࣬����Box����ı���ͼƬ���ǲ�Ӧ���ڱ߾�ģ�ֻ���ӿؼ�Ӧ���ڱ߾�)
	//�˿���Ĭ��Ϊtrue���ṩ�ر�ѡ����Ϊ�˼���ԭ�����߼���������Ӱ��ʵ�֣��Ͳ��ܿ����ڱ߾࣬������Ӱ�����쳣
	bool m_bEnableControlPadding;

	//�ؼ��Ƿ�Ϊ��������
	bool m_bFloat;

	//�Ƿ���Ҫ��������
	bool m_bIsArranged;

	//�Ƿ�ʹ�û��ƻ���
	// ���Ϊtrue��ÿ���ؼ��Լ�����һ�ݻ��ƻ��棬��ռ�ý϶��ڴ棬�����ϻ������������ܣ���ʵ��δ���Գ�Ч����
	// ���Ϊfalse����ʾ�޻��ƻ��棬�ڴ�ռ�ñȽ��١�
	// TODO: ���ģʽ���ڴ�ռ���ʺܸߣ��Ի����������������ԣ�δ�����ܻ�ɾ��������߼����Լ򻯴��롣
	bool m_bUseCache;

	//�����Ƿ�������־ֵ
	bool m_bCacheDirty;

	//�Ƿ�ɼ�
	bool m_bVisible;

	//�Ƿ��Ѿ���ɳ�ʼ��
	bool m_bInited;
};

} // namespace ui

#endif // UI_CORE_PLACE_HOLDER_H_
