## �˵�
�˵���ʵ���ǻ��ڴ���([WindowImplBase](../duilib/Utils/WinImplBase.h))ʵ�ֵģ���Ҫ��[CMenuWnd](../duilib/Control/Menu.h)��[CMenuElementUI](../duilib/Control/Menu.h)��������ɡ�
1. �˵���Ч��Ԥ��
���Ԥ����`examples/controls`ʾ�������еĲ˵���
<img src="./Images/Menu.png"/>
2. �˵���ʵ�ְ�����ϵͳ�˵��еĻ������ܣ�֧��ͼ�ꡢ��ѡ�򡢶༶�˵����˵���ָ�������̬�޸Ĳ˵���˵��в���ǲ˵��ؼ��ȡ�
3. `settings_menu.xml`�е���Ҫ���ݣ�
```xml
<?xml version="1.0" encoding="utf-8"?>
<Window>
    <VListBox class="menu">
        <!-- һ���˵� -->
        <MenuElement class="menu_element" name="first" width="180">
          <Button name="button_01" width="auto" height="auto" bkimage="menu_settings.png" valign="center" mouse="false"/>
          <Label class="menu_text" text="һ���˵��� 1" margin="30,0,0,0"/>
        </MenuElement>
    
        <MenuElement class="menu_element" name="second" width="180">
          <Button name="button_02" width="auto" height="auto" bkimage="menu_proxy.png" valign="center" mouse="false"/>
          <Label class="menu_text" text="һ���˵��� 2" margin="30,0,0,0"/>
        </MenuElement>
        
        <!-- �ڲ˵��в�����ͨ�ؼ���ʵ���ض����� -->
        <HBox class="menu_split_box" height="36">
            <Label class="menu_text" text="����" textpadding="0,0,6,0"/>
            <Control width="auto" height="auto" bkimage="menu_speaker.png" valign="center"/>
            <Slider class="slider_green" value="70" tooltiptext="ui::Slider"/>        
        </HBox>
        
        <!-- �˵���֮��ķָ��� -->
        <Box class="menu_split_box">
            <Control class="menu_split_line" />
        </Box>
        
        <MenuElement class="menu_element" name="third" width="180">
            <Button name="button_03" width="auto" height="auto" bkimage="menu_logs.png" valign="center" mouse="false"/>
            <Label class="menu_text" text="һ���˵��� 3" margin="30,0,0,0"/>
        </MenuElement>
        
        <MenuElement class="menu_element" name="fourth" width="180">
            <Button name="button_04" width="auto" height="auto" bkimage="menu_tree.png" valign="center" mouse="false"/>
            <Label class="menu_text" text="�����˵�" margin="30,0,0,0"/>
            <!-- �����˵�����һ��֧�ֵ���ʽ�����־ɰ汾�ļ����ԣ� -->
            <MenuElement class="menu_element" name="sub_menu0" width="180">
                <Button name="button_44" width="auto" height="auto" bkimage="menu_tree.png" valign="center" mouse="false"/>
                <Label class="menu_text" text="�����˵��� 0" margin="30,0,0,0"/>
            </MenuElement>
            <!-- �����˵����ڶ���֧�ֵ���ʽ��������ʽ���������Ӳ˵������ͨ�ÿؼ��� -->
            <SubMenu>
                <MenuElement class="menu_element" name="sub_menu1" width="180">
                    <Label class="menu_text" text="�����˵��� 1" margin="30,0,0,0"/>
                </MenuElement>
                <MenuElement class="menu_element" name="sub_menu2" width="180">
                    <Label class="menu_text" text="�����˵��� 2" margin="30,0,0,0"/>
                </MenuElement>
                <MenuElement class="menu_element" name="sub_menu3" width="180">
                    <Label class="menu_text" text="�����˵��� 3" margin="30,0,0,0"/>
                </MenuElement>
                <MenuElement class="menu_element" name="sub_menu4" width="180">
                    <Button name="button_05" width="auto" height="auto" bkimage="menu_tree.png" valign="center" mouse="false"/>
                    <Label class="menu_text" text="�����˵�" margin="30,0,0,0"/>
                    <!-- �����˵� -->
                    <MenuElement class="menu_element" name="sub_sub_menu1" width="180">
                        <Label class="menu_text" text="�����˵��� 1"/>
                    </MenuElement>
                    <MenuElement class="menu_element" name="sub_sub_menu2" width="180">
                        <Label class="menu_text" text="�����˵��� 2"/>
                    </MenuElement>
                </MenuElement>
            </SubMenu>
        </MenuElement>
        
        <!-- �˵���֮��ķָ��� -->
        <Box class="menu_split_box">
            <Control class="menu_split_line" />
        </Box>
        
        <!-- ����ѡ��Ĳ˵��� -->
        <MenuElement class="menu_element" name="menu_check_01" width="180">
            <CheckBox class="menu_checkbox" name="menu_checkbox_01" text="����ʽ������" margin="0,5,0,10" selected="true" tooltiptext="ui::Checkbox"/>
        </MenuElement>
        <MenuElement class="menu_element" name="menu_check_02" width="180">
            <CheckBox class="menu_checkbox" name="menu_checkbox_02" text="����ʽ���ݼ�" margin="0,5,0,10" selected="false" tooltiptext="ui::Checkbox"/>
        </MenuElement>
        
        <!-- �˵���֮��ķָ��� -->
        <Box class="menu_split_box">
            <Control class="menu_split_line" />
        </Box>
    
        <MenuElement class="menu_element" name="about" width="180">
            <Button name="button_06" width="auto" height="auto" bkimage="menu_about.png" valign="center" mouse="false"/>
            <Label class="menu_text" text="����" margin="30,0,0,0"/>
        </MenuElement>
  </VListBox>
</Window>
```

4. `submenu.xml`�е���Ҫ���ݣ�
```xml
<?xml version="1.0" encoding="utf-8"?>
<Window>
  <VListBox class="menu" name="submenu">
   
  </VListBox>
</Window>
```
`submenu.xml`���Ӳ˵��������ļ�������ͨ��`CMenuWnd::SetSubMenuXml`�ӿ��޸ģ�
```cpp
/** ���ö༶�Ӳ˵���XMLģ���ļ�������
@param [in] submenuXml �Ӳ˵���XMLģ���ļ��������û���ã��ڲ�Ĭ��Ϊ "submenu.xml"
@param [in] submenuNodeName �Ӳ˵�XML�ļ��У��Ӳ˵������λ�õĽڵ����ƣ����û���ã��ڲ�Ĭ��Ϊ "submenu"
*/
void SetSubMenuXml(const std::wstring& submenuXml, const std::wstring& submenuNodeName);
```
5. `examples/controls`ʾ����������ʾ�˵��Ĵ���Ƭ��    
��ʾ�˵��������ڶ����˵��У�����Ӳ˵��
```cpp
void ControlForm::ShowPopupMenu(const ui::UiPoint& point)
{
    ui::CMenuWnd* menu = new ui::CMenuWnd(GetHWND());//��Ҫ���ø����ڣ����ڲ˵�������ʱ�򣬳���״̬����̷Ǽ���״̬
    std::wstring xml(L"settings_menu.xml");
    menu->ShowMenu(xml, point);

    //�ڶ����˵��У�����Ӳ˵���
    ui::CMenuElementUI* menu_fourth = static_cast<ui::CMenuElementUI*>(menu->FindControl(L"fourth"));
	if (menu_fourth != nullptr) {
		ui::CMenuElementUI* menu_item = new ui::CMenuElementUI;
		menu_item->SetText(L"Dynamically created");
		menu_item->SetClass(L"menu_element");
		menu_item->SetFixedWidth(ui::UiFixedInt(180), true, true);
		menu_item->SetFontId(L"system_14");
		menu_item->SetTextPadding({ 20, 0, 20, 0 });
		menu_fourth->AddSubMenuItemAt(menu_item, 1);//��Ӻ���Դ�ɲ˵�ͳһ����
	}
```

��Ӳ˵���Ĺ�����Ӧ������
```cpp
    /* About menu */
    ui::CMenuElementUI* menu_about = static_cast<ui::CMenuElementUI*>(menu->FindControl(L"about"));
    if (menu_about != nullptr) {
    	menu_about->AttachClick([this](const ui::EventArgs& args) {
    		AboutForm* about_form = new AboutForm();
    		about_form->CreateWnd(GetHWND(), AboutForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, WS_EX_LAYERED);
    		about_form->CenterWindow();
    		about_form->ShowModalFake(GetHWND());
    		return true;
    		});
}
```
