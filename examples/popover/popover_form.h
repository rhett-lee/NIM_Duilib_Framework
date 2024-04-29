#pragma once

class PopoverForm : public ui::WindowImplBase
{
public:
  PopoverForm();
  ~PopoverForm();

  /**
   * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
   * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
   * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
   * GetWindowClassName	�ӿ����ô���Ψһ��������
   */
  virtual std::wstring GetSkinFolder() override;
  virtual std::wstring GetSkinFile() override;
  virtual std::wstring GetWindowClassName() const override;
  virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;

  /**
   * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
   */
  virtual void OnInitWindow() override;

  /**
   * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
   */
  virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) override;

  static const std::wstring kClassName;

private:
  void TestAllPlacement();
  void TestOthers();

private:
  nim_comp::PopoverLayer* m_pPopoverLayer;

  ui::Button* btn_updatetitle;
  ui::Button* btn_updatecontent;
  ui::Button* btn_tl;
  ui::Button* btn_top;
  ui::Button* btn_tr;
  ui::Button* btn_lt;
  ui::Button* btn_rt;
  ui::Button* btn_left;
  ui::Button* btn_right;
  ui::Button* btn_lb;
  ui::Button* btn_rb;
  ui::Button* btn_bl;
  ui::Button* btn_bottom;
  ui::Button* btn_br;
};

