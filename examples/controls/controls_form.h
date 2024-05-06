#pragma once

enum ThreadId
{
	kThreadUI,
	kThreadGlobalMisc
};

class ControlForm : public ui::WindowImplBase
{
public:
	ControlForm();
	~ControlForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void OnInitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

	/**
	 * ��ʶ���� class name
	 */
	static const std::wstring kClassName;

private:

	/** ��ʾ�˵�
	* @param [in] point ��ʾλ�����꣬��Ļ����
	*/
	void ShowPopupMenu(const ui::UiPoint& point);

	/**
	 * ��Ͷ�ݵ������̶߳�ȡ xml ���ݵ�������
	 */
	void LoadRichEditData();

	/**
	 * �����������̶߳�ȡ xml ��ɺ���� UI ���ݵĽӿ�
	 */
	void OnResourceFileLoaded(const std::wstring& xml);

	/**
	 * ��̬���½������ӿ�
	 */
	void OnProgressValueChagned(float value);

	/** ��ʾʰɫ������
	*/
	void ShowColorPicker();

private:
	/** ���ռ��̰���������Ϣ(WM_HOTKEY)ʱ������
	* @param [in] uMsg ��Ϣ����
	* @param [in] wParam ��Ϣ���Ӳ���
	* @param [in] lParam ��Ϣ���Ӳ���
	* @param [out] bHandled ���� false ������ɷ�����Ϣ���������ɷ�����Ϣ
	* @return ������Ϣ������
	*/
	virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;
};

