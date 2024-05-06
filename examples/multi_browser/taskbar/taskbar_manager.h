#pragma once

interface ITaskbarList4;

/** @class TaskbarTabItem
  * @brief �����������ӵ�ĳ��������ʾ��һ������������ͼTab(ֻ��Win7������ϵͳ��)
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class TaskbarManager;
class TaskbarTabItem final : public ui::Window
{
public:
	/**
	* @param[in] bind_control ��TaskbarTabItem����һ����ṩ����ͼ��Ԥ��ͼ�Ŀؼ���ָ��
	* ���캯��
	*/
	TaskbarTabItem(ui::Control *bind_control);

	/**
	* ��ȡ��TaskbarTabItem����һ��Ŀؼ�ָ��
	* @return ui::Control* �ؼ�ָ��
	*/
	ui::Control* GetBindControl();

	/**
	* ��ȡ����ͼTab��Ψһid
	* @return std::string& id
	*/
	std::string& GetId();

	/**
	* ��ʼ��������TaskbarTabItem��new����������
	* @param[in] taskbar_title ������������ͼ����ʾ�ı���
	* @param[in] id ����ͼTab��Ψһid
	* @return void	�޷���ֵ
	*/
	void Init(const std::wstring &taskbar_title, const std::string &id);

	/**
	* ����ʼ������
	* @return void	�޷���ֵ
	*/
	void UnInit();

	/**
	* ���ñ�Tab����ͼ�ı���
	* @param[in] title ����
	* @return void	�޷���ֵ
	*/
	void SetTaskbarTitle(const std::wstring &title);

	/**
	* ���ñ�Tab�����Ĵ����Ӧ��TaskbarManager
	* @param[in] taskbar_manager TaskbarManagerָ��
	* @return void	�޷���ֵ
	*/
	void SetTaskbarManager(TaskbarManager *taskbar_manager);

	/**
	* ��ȡ��Tab�����Ĵ����Ӧ��TaskbarManager
	* @return TaskbarManager* TaskbarManagerָ��
	*/
	TaskbarManager* GetTaskbarManager();

	/**
	* ��TaskbarTabItem��������������ͼ��Ϊ��Ч״̬�������ػ�����ͼ
	* @return bool true �ɹ���false ʧ��
	*/
	bool InvalidateTab();

private:
	/**
	* ���ر����ڵĴ�������
	* @return std::wstring ��������
	*/
	virtual std::wstring GetWindowClassName() const override;

	/**
	* ���ز�����ײ㴰����Ϣ
	* @param[in] uMsg ��Ϣ����
	* @param[in] wParam ���Ӳ���
	* @param[in] lParam ���Ӳ���
	* @param[in out] bHandled �Ƿ�������Ϣ����������˲�����������Ϣ
	* @return LRESULT ������
	*/
	virtual LRESULT OnWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/**
	* ������������Ϣ
	* @return void	�޷���ֵ
	*/
	virtual void OnFinalMessage(HWND hWnd) override;

	/**
	* ��ӦWM_DWMSENDICONICTHUMBNAIL��Ϣ
	* @param[in] width ��Ҫ��λͼ���
	* @param[in] height ��Ҫ��λͼ�߶�
	* @return void	�޷���ֵ
	*/
	void OnSendThumbnail(int width, int height);

	/**
	* ��ӦWM_DWMSENDICONICLIVEPREVIEWBITMAP��Ϣ
	* @return void	�޷���ֵ
	*/
	void OnSendPreview();

private:
	bool			is_win7_or_greater_;
	ui::Control		*bind_control_;
	std::string		id_;
	TaskbarManager	*taskbar_manager_;
};

/** @class TaskbarManager
  * @brief ����ĳ���Ự��������������ʾ��Ԥ��Ч��(ֻ��Win7������ϵͳ��),���а������TaskbarItem
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class SessionForm;
class TaskbarManager final : public virtual nbase::SupportWeakCallback
{
public:
	/** @class ITaskbarDelegate
	  * @brief TaskbarManager���¼�ί���ֻ࣬�м̳и���������ʹ��TaskbarManager����
	  * @date 2019/3/20
	  */
	class ITaskbarDelegate
	{
	public:
		/**
		* ��ȡ������
		* @return HWND	������
		*/
		virtual HWND GetHandle() const = 0;

		/**
		* ��ȡ��Ⱦ�ӿ�
		* @return ��Ⱦ�ӿ�
		*/
		virtual ui::IRender* GetTaskbarRender() const = 0;

		/**
		* �ر�һ����������
		* @param[in] id ��������id
		* @return void	�޷���ֵ
		*/
		virtual void CloseTaskbarItem(const std::string &id) = 0;

		/**
		* ����л���һ����������
		* @param[in] id ��������id
		* @return void �޷���ֵ
		*/
		virtual void SetActiveTaskbarItem(const std::string &id) = 0;
	};

	/**
	* ���캯��
	*/
	TaskbarManager();

	/**
	* ��ʼ��ITaskbarList4�ӿ�
	* @param[in] taskbar_delegate ��Ϊ����������ͼ������
	* @return void	�޷���ֵ
	*/
	void Init(ITaskbarDelegate *taskbar_delegate);

	/**
	* ��һ��TaskbarTabItemע��Ϊ�����ڵ�һ��Tabҳ
	* @param[in] tab_item TaskbarItem����
	* @return bool true �ɹ���false ʧ��
	*/
	bool RegisterTab(TaskbarTabItem &tab_item);

	/**
	* ��һ��TaskbarTabItem���������з�ע��Ϊ
	* @param[in] tab_item TaskbarItem����
	* @return bool true �ɹ���false ʧ��
	*/
	bool UnregisterTab(TaskbarTabItem &tab_item);

	/**
	* ��һ��TaskbarTabItem�������ڵ�����ͼ�е���ʾ˳�����õ���һ��TaskbarTabItemǰ��
	* @param[in] tab_item ������˳���TaskbarItem����
	* @param[in] tab_item_insert_before �������TaskbarItem����
	* @return bool true �ɹ���false ʧ��
	*/
	bool SetTabOrder(const TaskbarTabItem &tab_item, const TaskbarTabItem &tab_item_insert_before);

	/**
	* ��һ��TaskbarTabItem������������Ϊ����״̬
	* @param[in] tab_item TaskbarItem����
	* @return bool true �ɹ���false ʧ��
	*/
	bool SetTabActive(const TaskbarTabItem &tab_item);

	/**
	* ����ĳ���ؼ���Ӧ��λͼ������λͼ�������ڣ��ҳߴ�Ϊ���ڴ�С��
	* @param[in] control �ؼ�ָ��
	* @return HBITMAP	���ɵ�λͼ
	*/
	ui::IBitmap* GenerateBindControlBitmapWithForm(ui::Control *control);

	/**
	* ����ĳ���ؼ���Ӧ��λͼ
	* @param[in] control �ؼ�ָ��
	* @param[in] dest_width Ŀ����
	* @param[in] dest_height Ŀ��߶�
	* @return HBITMAP	���ɵ�λͼ
	*/
	ui::IBitmap* GenerateBindControlBitmap(ui::Control *control, const int dest_width, const int dest_height);

	/**
	* ����һ���ڴ�λͼ
	* @param[in] dest_width Ŀ����
	* @param[in] dest_height Ŀ��߶�
	* @param[in] pSrcRender ԴRender�ӿ�
	* @param[in] src_x Դ������
	* @param[in] src_y Դ������
	* @param[in] src_width Դ���
	* @param[in] src_height Դ�߶�
	* @return HBITMAP	���ɵ�λͼ
	*/
	ui::IBitmap* ResizeBitmap(int dest_width, int dest_height, ui::IRender* pSrcRender, int src_x, int src_y, int src_width, int src_height);

	/**
	* ����������Tab������ͼ��WM_CLOSE��Ϣ
	* @param[in] tab_item ������Ϣ��Tab
	* @return void	�޷���ֵ
	*/
	void OnTabItemClose(TaskbarTabItem &tab_item);

	/**
	* ����������Tab������ͼ��WM_ACTIVATE��Ϣ
	* @param[in] tab_item ������Ϣ��Tab
	* @return void	�޷���ֵ
	*/
	void OnTabItemClicked(TaskbarTabItem &tab_item);
private:
	ITaskbarDelegate	*taskbar_delegate_;
	ITaskbarList4		*taskbar_list_;
};