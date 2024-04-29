#pragma once
#include "browser_box.h"

enum ThreadId
{
	kThreadUI
};

/** @class MultiBrowserManager
  * @brief ���ǩ����������࣬����ͳһ������ǩ������򿪡��ϲ�����֡���ק����
  * @date 2019/3/20
  */
class SdkDataObject;
class MultiBrowserManager : public virtual nbase::SupportWeakCallback
{
public:
	SINGLETON_DEFINE(MultiBrowserManager);
public:
	MultiBrowserManager();
	~MultiBrowserManager();

	/**
	* ����һ�����������
	* @param[in] browser_form ��������ڣ����ΪNULL�򴴽�һ���µĴ��ڣ�����������������½����������
	* @param[in] id ĳ����������ӵ�Ψһ��ʶ
	* @param[in] url ��ʼ��URL
	* @return BorwserBox*	���������ָ��
	*/
	BrowserBox* CreateBorwserBox(MultiBrowserForm *browser_form, const std::string &id, const std::wstring &url);

	/**
	* �ж�ĳ������������Ƿ��ڼ���״̬
	* @param[in] id ĳ����������ӵ�Ψһ��ʶ
	* @return bool true ���false �Ǽ���
	*/
	bool IsBorwserBoxActive(const std::string& id);

	/**
	* ���ݻỰid���һ����������
	* @param[in] id ĳ����������ӵ�Ψһ��ʶ
	* @return BorwserBox* ������������ӵ�ָ��
	*/
	BrowserBox* FindBorwserBox(const std::string &id);

	/**
	* ���ݻỰid���Ƴ������������������Ϣ
	* @param[in] id ĳ����������ӵ�Ψһ��ʶ
	* @param[in] box id��Ӧ�����������ָ��
	* @return void �޷���ֵ
	*/
	void RemoveBorwserBox(std::string id, const BrowserBox* box = NULL);

public:
	/**
	* �����Ƿ�����ǩ�ϲ�����
	* @param[in] enable true:�����ϲ�����,�Զ��ϲ���ǰ�������������
	*					false:�رպϲ�����,�Զ���ֵ�ǰ�������������
	* @return �޷���ֵ
	*/
	void SetEnableMerge(bool enable);

	/**
	* �Ƿ�����ǩ�ϲ�����
	* @return bool true �ǣ�false ��
	*/
	bool IsEnableMerge() const;

	/**
	* �����Ƿ�ʹ���Զ������ק����ͼ
	* @param[in] use true:ʹ���Զ�����ק����ͼ����ʹ�õͼ����̹��ӣ�һЩ��ȫ���������
	*				 false:ʹ��ϵͳ����ק����ͼ��Ч���ϲ����Զ���ĺ�
	* @return �޷���ֵ
	*/
	void SetUseCustomDragImage(bool use);

	/**
	* �Ƿ�ʹ���Զ������ק����ͼ
	* @return bool true �ǣ�false ��
	*/
	bool IsUseCustomDragImage() const;

	/**
	* ��ǰ�Ƿ�������ק���������
	* @return bool true �ǣ�false ��
	*/
	bool IsDragingBorwserBox() const;

	/**
	* ���ñ�������������ӵ����������
	* @param[in] browser_form ���������
	* @return void	�޷���ֵ
	*/
	void SetDropForm(MultiBrowserForm *browser_form);

	/**
	* ִ����ק��������ӵĲ���
	* @param[in] browser_box ���������
	* @param[in] bitmap ������������ɵ�λͼ
	* @param[in] pt_offset ��קͼ�����������ƫ��
	* @return bool true �ɹ���false ʧ��
	*/
	bool DoDragBorwserBox(BrowserBox *browser_box, HBITMAP bitmap, POINT pt_offset);

private:

	/**
	* ����һ��������ק��IDataObject����
	* @param[in] bitmap ����������קЧ����λͼ
	* @param[in] pt_offset ��קͼ�����������ƫ��
	* @return SdkDataObject* IDataObject����
	*/
	SdkDataObject* CreateDragDataObject(HBITMAP bitmap, POINT pt_offset);

	/**
	* ִ����ק����ǰ������
	* @return void	�޷���ֵ
	*/
	void OnBeforeDragBorwserBox(BrowserBox *browser_box, HBITMAP bitmap, POINT pt_offset);

	/**
	* ִ����ק�����󱻵���
	* @return void	�޷���ֵ
	*/
	void OnAfterDragBorwserBox();

private:
	bool				enable_merge_;
	bool				use_custom_drag_image_;
	BrowserBox			*draging_box_;	// �������ڱ���ק�����������
	MultiBrowserForm	*drop_browser_form_;	// ������������ӵ���������ڣ����ڸ�����ק�������������

	std::map<std::string, BrowserBox*>	box_map_;
};