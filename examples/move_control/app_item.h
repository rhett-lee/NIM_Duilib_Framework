#pragma once

#define APP_HEIGHT 90
#define APP_WIDTH  90
#define EACH_LINE  6

#include <string>

//app�ľ�����Ϣ������ٶ���id��name��_icon,_isFrequent������չ
struct AppItem
{
	std::string m_id;
	std::wstring m_name;
	std::wstring m_icon;
	bool m_isFrequent=false;
};

//App UI��
class AppItemUi : public ui::ControlDragableT<ui::VBox>
{
public:
	static AppItemUi* Create(const AppItem& item);
	virtual void OnInit() override;
	void SetAppdata(const AppItem& item,bool refresh);
	inline const AppItem& getAppData() const { return m_app_data; }

	/** ���ÿؼ�������
	*/
	void SetFrequentBox(ui::Box* pFrequentBox);

private:
	/** Ŀ��λ��ָʾ�ؼ�
	* @param [in] pTargetBox ���������Ŀ��Box�ؼ��ӿ�
	*/
	virtual Control* CreateDestControl(Box* pTargetBox) override;

	/** �ؼ����������϶�����¼�����ͬһ������/���߲�ͬ�����ڣ�
    * @param [in] pOldBox �ؼ�ԭ�������������ӿ�
    * @param [in] nOldItemIndex ԭ��������������
    * @param [in] pNewBox �ؼ����������������ӿ�
    * @param [in] nNewItemIndex ���µ�����������
    */
    virtual void OnItemBoxChanged(Box* pOldBox, size_t nOldItemIndex, 
                                  Box* pNewBox, size_t nNewItemIndex) override;

private:
	AppItem m_app_data;
	ui::Control* m_app_icon = nullptr;
	ui::Label* m_app_name = nullptr;

	/** ���ÿؼ�������
	*/
	Box* m_pFrequentBox = nullptr;
};
