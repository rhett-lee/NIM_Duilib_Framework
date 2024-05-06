## Control�������ؼ���������

`Control` �ؼ�Ϊ���п��ÿؼ��Ļ��࣬�����˿ؼ����õ����ԣ����ȡ��߶ȡ��߾�����ԡ�һ������²���Ϊ������ÿؼ�ʹ�ã���������һЩռλ������ο�ʾ����
`Control` �����пؼ��Ļ��࣬���������пؼ��Ŀ���ͨ�����ԡ�

```xml
<!-- һ�����ݸ���������Զ������ Control �ؼ���һ��������Ϊռλ��ʹ�� -->
<Control width="stretch"/>
```

| �������� | Ĭ��ֵ | �������� |����[Control.h](../duilib/Core/Control.h)�еĺ���| ��; |
| :--- | :--- | :--- | :---| :--- |
| class |  | string | SetClass|�ؼ���ʽ,����ʽ���������ֵ�����ñ��ؼ�������,��(btn_default),����ͬʱָ�������ʽ,������ʽ֮���ÿո�ָ�,��Ҫд�ڵ�һ������λ�� |
| name |  | string | SetName|�ؼ�����,ͬһ�����ڱ���Ψһ,��(testbtn) |
| width | stretch | int / string | SetFixedWidth|��������int��string���͵�ֵ.��ֵΪint�������ÿؼ��Ŀ��ֵ,��(100);��ֵΪstringʱ,stretch�����ɸ���������ؼ����,auto���������������Զ�������,���Ϊ�ٷֱ�ֵ"50%"������ÿؼ��Ŀ������ֵΪ���ؼ���ȵ�50% |
| height | stretch | int / string | SetFixedHeight|��������int��string���͵�ֵ.��ֵΪint�������ÿؼ��ĸ߶�ֵ,��(100);��ֵΪstringʱ,stretch�����ɸ���������ؼ��߶�,auto���������������Զ�����߶�,���Ϊ�ٷֱ�ֵ"30%"������ÿؼ��Ŀ������ֵΪ���ؼ��߶ȵ�30%  |
| min_width | -1 | int | SetMinWidth|�ؼ�����С���,��(30) |
| min_height | -1 | int | SetMinHeight|�ؼ�����С�߶�,��(30) |
| max_width | INT32_MAX | int / string | SetMaxWidth|�ؼ��������,����ͬwidth |
| max_height | INT32_MAX | int / string | SetMaxHeight|�ؼ������߶�,����ͬheight |
| margin | 0,0,0,0 | rect | SetMargin|��߾�,��(2,2,2,2) |
| padding | 0,0,0,0 | rect | SetPadding|�ڱ߾�,��(2,2,2,2) |
| control_padding | true | bool | SetEnableControlPadding|�Ƿ�����ؼ����������ڱ߾� |
| halign | left | string | SetHorAlignType|�ؼ��ĺ���λ��,��(center),֧��left��center��right����λ�� |
| valign | top | string | SetVerAlignType|�ؼ�������λ��,��(center),֧��top��center��bottom����λ�� |
| float | false | bool | SetFloat|�Ƿ�ʹ�þ��Զ�λ,��(true) |
| bkcolor |  | string | SetBkColor|������ɫ�ַ�������,��(white) |
| normal_color |  | string | SetStateColor|��ͨ״̬��ɫ,��(white) |
| hot_color |  | string | SetStateColor|����״̬��ɫ,��(white) |
| pushed_color |  | string | SetStateColor|����״̬��ɫ,��(white) |
| disabled_color |  | string | SetStateColor|����״̬��ɫ,��(white) |
| border_color |  | string | SetBorderColor|��������״̬�µı߿���ɫ,��(blue) |
| normal_border_color |  | string | SetBorderColor|����״̬�ı߿���ɫ,��(blue) |
| hot_border_color |  | string | SetBorderColor|����״̬�ı߿���ɫ,��(blue) |
| pushed_border_color |  | string | SetBorderColor|����״̬�ı߿���ɫ,��(blue) |
| disabled_border_color |  | string | SetBorderColor|��ֹ״̬�ı߿���ɫ,��(blue) |
| focus_border_color |  | string | SetFocusBorderColor|����״̬�ı߿���ɫ,��(blue) |
| border_size | 0 | int / rect | SetBorderSize|��������int��rect���͵�ֵ����ֵΪintʱ�����ϡ��ҡ��¶��ø�ֵ��Ϊ��ֵΪrect����ʱ��ֱ��������ϡ��ҡ��µı߿� |
| left_border_size | 0 | int | SetLeftBorderSize|��߱߿��С,��(1),���ø�ֵ����0,�򽫺���border_size���Ե����� |
| top_border_size | 0 | int | SetTopBorderSize|�����߿��С,��(1),���ø�ֵ����0,�򽫺���border_size���Ե����� |
| right_border_size | 0 | int | SetRightBorderSize|�ұ߱߿��С,��(1),���ø�ֵ����0,�򽫺���border_size���Ե����� |
| bottom_border_size | 0 | int | SetBottomBorderSize|�ײ��߿��С,��(1),���ø�ֵ����0,�򽫺���border_size���Ե����� |
| border_round | 0,0 | size | SetBorderRound|�߿�Բ�ǰ뾶,��(2,2) |
| bkimage |  | string | SetBkImage|����ͼƬ,��(bk.bmp��file='aaa.jpg' res='' dest='0,0,0,0' source='0,0,0,0' corner='0,0,0,0' fade='255' xtiled='false' ytiled='false') |
| normal_image |  | string | SetStateImage|��ͨ״̬ͼƬ |
| hot_image |  | string | SetStateImage|���������״̬ͼƬ |
| pushed_image |  | string | SetStateImage|��갴�µ�״̬ͼƬ |
| disabled_image |  | string | SetStateImage|���õ�״̬ͼƬ |
| fore_normal_image |  | string | SetForeStateImage|��ͨ״̬ǰ��ͼƬ |
| fore_hot_image |  | string | SetForeStateImage |���������״̬ǰ��ͼƬ |
| fore_pushed_image |  | string | SetForeStateImage|��갴�µ�״̬ǰ��ͼƬ |
| fore_disabled_image |  | string | SetForeStateImage|���õ�״̬ǰ��ͼƬ |
| tooltip_text |  | string | SetToolTipText|���������ʾ,��(�������������������) |
| tooltip_textid |  | string | SetToolTipTextId|���������ʾ,ָ��������ģ���ID,��tooltiptextΪ��ʱ����ʾ������,��(TOOL_TIP_ID) |
| dataid |  | string | SetDataID|�Զ����ַ�������,�������������û�ʹ�� |
| user_dataid |  | size_t | SetUserDataID|�Զ�����������, ���û�ʹ�� |
| enabled | true | bool | SetEnabled|�Ƿ������Ӧ�û�����,��(true) |
| mouse_enabled | true | bool | SetMouseEnabled|���ؼ��Ƿ������Ӧ������,��(true) |
| keyboard_enabled | true | bool | SetKeyboardEnabled|��CButtonUI����Ը�ֵ,Ϊfalseʱ��֧��TAB_STOP,�Ҹö��󲻴��������Ϣ |
| receivepointer | true | bool | |�Ƿ���Ӧ������Ϣ,��(true) |
| visible | true | bool | SetVisible|�Ƿ�ɼ�,��(true) |
| fade_visible | true | bool | SetFadeVisible|�Ƿ�ɼ�,��(true),�����Իᴥ���ؼ�����Ч�� |
| menu | false | bool | |�Ƿ���Ҫ�Ҽ��˵�,��(true) |
| nofocus | false | bool | SetNoFocus|�Ƿ���Ի�ȡ����,��(true) |
| tab_stop | true | bool | SetTabStop| �Ƿ�����ͨ����TAB���л����˿ؼ� |
| show_focus_rect | false| bool | SetLoadingBkColor| �Ƿ���ʾ����״̬(һ�����߹��ɵľ���) |
| focus_rect_color | | string | SetFocusRectColor| ����״̬���ε���ɫ |
| alpha | 255 | int | SetAlpha|�ؼ�������͸����,��(128)����ЧֵΪ 0-255 |
| state | normal | string | SetState|�ؼ��ĵ�ǰ״̬: ֧��normal��hot��pushed��disabled״̬ |
| cursor_type | arrow | string | SetCursorType|����ƶ����ؼ���ʱ�������: arrow(��ͷ)��hand(����)��ibeam(��I����״)��sizewe(�����϶�)��sizens(�����϶�)|
| render_offset | 0,0 | size | SetRenderOffset|�ؼ�����ʱ��ƫ����,��(10,10),һ�����ڻ��ƶ��� |
| fade_alpha | false | bool | GetAnimationManager(). SetFadeAlpha|�Ƿ����ÿؼ�͸�����䶯��,��(true) |
| fade_hot | false | bool |GetAnimationManager(). SetFadeHot |�Ƿ����ÿؼ�����״̬�� ��͸�����䶯��,��(true) |
| fade_width | false | bool | GetAnimationManager(). SetFadeWidth|�Ƿ����ÿؼ���Ƚ��䶯��,��(true) |
| fade_height | false | bool | GetAnimationManager(). SetFadeHeight|�Ƿ����ÿؼ��߶Ƚ��䶯��,��(true) |
| fade_in_out_x_from_left | false | bool | GetAnimationManager(). SetFadeInOutX|�Ƿ����ÿؼ������ҵĶ���,��(true) |
| fade_in_out_x_from_right | false | bool | GetAnimationManager(). SetFadeInOutX|�Ƿ����ÿؼ����ҵ���Ķ���,��(true) | 
| fade_in_out_y_from_top | false | bool | GetAnimationManager().  SetFadeInOutY|�Ƿ����ÿؼ����ϵ��µĶ���,��(true) | 
| fade_in_out_y_from_bottom | false | bool | GetAnimationManager().  SetFadeInOutY|�Ƿ����ÿؼ����µ��ϵĶ���,��(true) |
| loading_image | | string | SetLoadingImage| ������״̬��ͼƬ |
| loading_bkcolor | | string | SetLoadingBkColor| ������״̬�ı���ɫ |
| paint_order | | string | SetPaintOrder| ���û���˳��0 ��ʾ������ƣ���0��ʾָ������˳��ֵԽ���ʾԽ����� |
| start_gif_play | | int | StartGifPlay| ���Ŷ�����������ʾ����ѭ������ |
| stop_gif_play | | int | StopGifPlay| ֹͣ������������ʾֹͣ����һ֡ |
| box_shadow | | string | SetBoxShadow|���ÿؼ�����Ӱ���ԣ�������boxshadow="color='red' offset='0,0' blurradius='8' spreadradius='8' |
| cache | false | bool |SetUseCache |�Ƿ����ÿؼ����ƻ���,��(true) |

## ScrollBar������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| button1_normal_image |  | string | ����ϰ�ť��ͨ״̬ͼƬ |
| button1_hot_image |  | string | ����ϰ�ť�������״̬ͼƬ |
| button1_pushed_image |  | string | ����ϰ�ť��갴��״̬ͼƬ |
| button1_disabled_image |  | string | ����ϰ�ť����״̬ͼƬ |
| button2_normal_image |  | string | �һ��°�ť��ͨ״̬ͼƬ |
| button2_hot_image |  | string | �һ��°�ť�������״̬ͼƬ |
| button2_pushed_image |  | string | �һ��°�ť��갴��״̬ͼƬ |
| button2_disabled_image |  | string | �һ��°�ť����״̬ͼƬ |
| thumb_normal_image |  | string | ������ͨ״̬ͼƬ |
| thumb_hot_image |  | string | �����������״̬ͼƬ |
| thumb_pushed_image |  | string | ������갴��״̬ͼƬ |
| thumb_disabled_image |  | string | �������״̬ͼƬ |
| rail_normal_image |  | string | �����м��ʶ��ͨ״̬ͼƬ |
| rail_hot_image |  | string | �����м��ʶ�������״̬ͼƬ |
| rail_pushed_image |  | string | �����м��ʶ��갴��״̬ͼƬ |
| rail_disabled_image |  | string | �����м��ʶ����״̬ͼƬ |
| bk_normal_image |  | string | ������ͨ״̬ͼƬ |
| bk_hot_image |  | string | �����������״̬ͼƬ |
| bk_pushed_image |  | string | ������갴��״̬ͼƬ |
| bk_disabled_image |  | string | ��������״̬ͼƬ |
| horizontal | false | bool | ˮƽ��ֱ,��(true) |
| line_size | 8 | int | ����һ�еĴ�С,��(8) |
| thumb_min_length | 30 | int | �������С���� |
| range | 100 | int | ������Χ,��(100) |
| value | 0 | int | ����λ��,��(0) |
| show_button1 | true | bool | �Ƿ���ʾ����ϰ�ť,��(true) |
| show_button2 | true | bool | �Ƿ���ʾ�һ��°�ť,��(true) |
| auto_hide_scroll | true | bool | �Ƿ��Զ����ع�����,��(true) |

ScrollBar �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������

## Label������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| text |  | string | ��ʾ�ı� |
| textid |  | string | �����Թ��ܵ��ı�ID |
| text_align | left | string | �ı��Ķ��䷽ʽ, ֧������ȡֵ��left��hcenter��right��top��vcenter��bottom |
| text_padding | 0,0,0,0 | rect | ������ʾ�ı߾�, ��(2,2,2,2) |
| font | | string | ����ID��������ID������ global.xml �д��� |
| end_ellipsis | false | bool | ��ĩ��ʾ�������Ƿ�ʹ��...���� |
| path_ellipsis | false | bool | ����·������ʾ������ʱ�Ƿ�ʹ��...�����м�·�� |
| normal_text_color |  | string | ��ͨ������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| hot_text_color |  | string | �������������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| pushed_text_color |  | string | ��갴��������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| disabled_text_color |  | string | disabled������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| single_line | true | bool | �Ƿ���������� |
| multi_line | false | bool | �Ƿ����������֣���single_line���Ի��� |
| auto_tooltip | false | bool | ����������ؼ���ʾ����ʾ�ı��Ƿ�ʡ�Ժų���ʱ����ʾ|

Label �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������

## LabelBox������
LabelBox��Label�ǻ�����ͬģ����࣬��ο� `Label`������    
LabelBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## Button������
Button �ؼ��̳��� `Label` ���ԣ��������������ο�`Label`������

## ButtonBox������
ButtonBox��Button�ǻ�����ͬģ����࣬��ο� `Button`������    
ButtonBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## CheckBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| selected | false | bool | �Ƿ�ѡ�� |
| selected_normal_image |  | string | ѡ��״̬ʱ����ͨ״̬ͼƬ |
| selected_hot_image |  | string | ѡ��״̬ʱ�����������״̬ͼƬ |
| selected_pushed_image |  | string | ѡ��״̬ʱ����갴�µ�״̬ͼƬ |
| selected_disabled_image |  | string | ѡ��״̬ʱ�����õ�״̬ͼƬ |
| selected_fore_normal_image |  | string | ѡ��״̬ʱ��ǰ��ͼƬ |
| selected_fore_hot_image |  | string | ѡ��״̬ʱ���������״̬��ͼƬ |
| selected_fore_pushed_image |  | string | ѡ��״̬ʱ����갴��״̬��ǰ��ͼƬ |
| selected_fore_disabled_image |  | string | ѡ��״̬ʱ������״̬��ǰ��ͼƬ |
| part_selected_normal_image |  | string | ����ѡ��ʱ����ͨ״̬ͼƬ |
| part_selected_hot_image |  | string | ����ѡ��ʱ�����������״̬ͼƬ |
| part_selected_pushed_image |  | string | ����ѡ��ʱ����갴�µ�״̬ͼƬ |
| part_selected_disabled_image |  | string | ����ѡ��ʱ�����õ�״̬ͼƬ |
| part_selected_fore_normal_image |  | string | ����ѡ��ʱ��ǰ��ͼƬ |
| part_selected_fore_hot_image |  | string | ����ѡ��ʱ���������״̬��ͼƬ |
| part_selected_fore_pushed_image |  | string | ����ѡ��ʱ����갴��״̬��ǰ��ͼƬ |
| part_selected_fore_disabled_image |  | string | ����ѡ��ʱ������״̬��ǰ��ͼƬ |
| selected_text_color |  | string | ѡ��״̬��������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| selected_normal_text_color |  | string | ѡ��״̬����ͨ״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| selected_hot_text_color |  | string | ѡ��״̬���������״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| selected_pushed_text_color |  | string | ѡ��״̬����갴��״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| selected_disabled_text_color |  | string | ѡ��״̬�Ľ���״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| normal_first | false | bool | �ؼ���ѡ��״̬�£�û�����ñ���ɫ�򱳾�ͼʱ���÷�ѡ��״̬�Ķ�Ӧ���������� |

CheckBox �ؼ��̳��� `Button` ���ԣ��������������ο�`Button`������

## CheckBoxBox������
CheckBoxBox��CheckBox�ǻ�����ͬģ����࣬��ο� `CheckBox`������    
CheckBoxBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## Option������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| group |  | string | ����������ƣ�����ͬ���������£����ֵ�ѡ |

Option �ؼ��̳��� `CheckBox` ���ԣ��������������ο�`CheckBox`������

## OptionBox������
OptionBoxBox��OptionBox�ǻ�����ͬģ����࣬��ο� `OptionBox`������    
OptionBoxBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## GroupBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| corner_size | "0,0" | size | Բ�Ǵ�С |
| line_width | 0 | int | ������� |
| line_color | | string | ������ɫ |
| text | | string | �ı����� |

GroupBox �ؼ��̳��� `Label` ���ԣ��������������ο�`Label`������

## GroupVBox������
GroupVBox �� GroupBox ����ͬģ��ʵ�֣�����������ο�`GroupBox`������    
GroupVBox �ؼ��̳��� `VBox` ���ԣ��������������ο�`VBox`������

## GroupHBox������
GroupHBox �� GroupBox ����ͬģ��ʵ�֣�����������ο�`GroupBox`������    
GroupHBox �ؼ��̳��� `HBox` ���ԣ��������������ο�`HBox`������

## Combo������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| combo_type | "drop_down" | string | ��Ͽ�����ͣ�"drop_list" ��ʾΪ���ɱ༭�б�"drop_down" ��ʾΪ�ɱ༭�б�|
| dropbox_size | | string | �����б�Ĵ�С����Ⱥ͸߶ȣ�|
| popup_top | false | bool | �����б��Ƿ����ϵ��� |
| combo_tree_view_class | | string | ������TreeView��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| combo_tree_node_class | | string | ������TreeView�Ľڵ��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| combo_icon_class | | string | ��ʾͼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| combo_edit_class | | string | �༭�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| combo_button_class | | string | ��ť�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|

Combo �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## FilterCombo������
FilterCombo �ؼ���֧��"combo_type"����    
FilterCombo �ؼ��̳��� `Combo` ���ԣ��������������ο�`Combo`������

## ComboButton������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| dropbox_size | | string | �����б�Ĵ�С����Ⱥ͸߶ȣ�|
| popup_top | false | bool | �����б��Ƿ����ϵ��� |
| combo_box_class | | string | ��������Ͽ��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| left_button_class | | string | ��ఴť�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| left_button_top_label_class | | string | ��ఴť�ϲ��Label�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| left_button_bottom_label_class | | string | ��ఴť�²��Label�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|
| left_button_top_label_text | | string | ��ఴť�ϲ��Label�ؼ����ı�|
| left_button_bottom_label_text | | string | ��ఴť�²��Label�ؼ����ı�|
| left_button_top_label_bkcolor | | string | ��ఴť�ϲ��Label�ؼ��ı���ɫ|
| left_button_bottom_label_bkcolor | | string | ��ఴť�²��Label�ؼ��ı���ɫ|
| right_button_class | | string | �Ҳఴť�ؼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ����|

ComboButton �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## CheckCombo������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| dropbox | | string | �������������Ϣ���������÷����ɲ���ʾ������|
| dropbox_size | | string | �����б�Ĵ�С����Ⱥ͸߶ȣ�|
| popup_top | false | bool | �����б��Ƿ����ϵ��� |
| dropbox_item_class | | string | �����б���ÿһ���б�������ԣ��������÷����ɲ���ʾ������|
| selected_item_class | | string | ѡ������ÿһ����������ԣ��������÷����ɲ���ʾ������|

CheckCombo �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## DateTime������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| format | | string | ���ڵĸ�ʽ������ɲο���`DateTime.h`�к�����˵�� |
| edit_format | | string | �༭״̬ʱ�����ڵı༭��ʽ����ѡֵ��"date_calendar"����-��-�գ�ͨ��������չʾ�������ķ�ʽ���޸����ڣ�"date_up_down"�� �༭ʱ��ʾ����-��-�գ�ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸����ڣ�"date_time_up_down"���༭ʱ��ʾ����-��-�� ʱ:��:�룻"date_minute_up_down"���༭ʱ��ʾ����-��-�� ʱ:�֣�"time_up_down"���༭ʱ��ʾ��ʱ:��:�룻"minute_up_down"���༭ʱ��ʾ��ʱ:��|

DateTime �ؼ��̳��� `Label` ���ԣ��������������ο�`Label`������

## HotKey������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| default_text | | string | Ĭ����ʾ������ |

HotKey �ؼ��̳��� `HBox` ���ԣ��������������ο�`HBox`������

## HyperLink������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| url | | string | URL |

HyperLink �ؼ��̳��� `Label` ���ԣ��������������ο�`Label`������

## IPAddress������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| ip | | string | IP��ַ�����磺"192.168.0.0" |

HotKey �ؼ��̳��� `HBox` ���ԣ��������������ο�`HBox`������

## Line������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| vertical | false | bool | �Ƿ�Ϊ��ֱ���� |
| line_color | | string | �ߵ���ɫ |
| line_width | | int | �ߵĿ�� |
| dash_style | | string | �ߵ���״����ѡֵ��"solid"��ʵ�ߣ�"dash"���̻��߹��ɵ����ߣ�"dot"���㹹�ɵ����ߣ�"dash_dot"������̻��ߵ��ߣ�"dash_dot_dot"������̻��ߵ����|

Line �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������

## CMenuWnd������
CMenuWnd��һ�����ڣ������÷���ο�ʾ�������еĲ˵�    
CMenuWnd �ؼ��̳��� `Window` ���ԣ��������������ο�`Window`������

## Progress������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| horizontal | true | bool | �Ƿ�ˮƽ�ģ�true��ʾˮƽ��false��ʾ��ֱ |
| min | 0 | int | ������Сֵ,��(0) |
| max | 100 | int | �������ֵ,��(100) |
| value | 0 | int | ����ֵ,��(50) |
| progress_image |  | string | ������ǰ��ͼƬ |
| stretch_fore_image | true | bool | ָ��������ǰ��ͼƬ�Ƿ�������ʾ |
| progress_color |  | string | ������ǰ����ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| marquee | true | bool | �Ƿ������ʾ |
| marquee_width | | int | �����Ŀ�� |
| marquee_step | | int | �����Ĳ��� |
| reverse | false | bool | ����ֵ�Ƿ��������ȴ�100 �� 0�� |

Progress �ؼ��̳��� `Label` ���ԣ��������������ο�`Label`������

## Slider������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| thumb_normal_image |  | string | �϶�������ͨ״̬ͼƬ |
| thumb_hot_image |  | string | �϶������������״̬ͼƬ |
| thumb_pushed_image |  | string | �϶�������갴��״̬ͼƬ |
| thumb_disabled_image |  | string | �϶�����������״̬ͼƬ |
| thumb_size | 10,10 | size | �϶������С,��(10,10) |
| step | 1 | int | ���Ȳ���,��(1) |
| progress_bar_padding | 0,0,0,0 | rect | ����������ʱ��С���ڱ߾� |

Slider �ؼ��̳��� `Progress` ���ԣ��������������ο�`Progress`������

## CircleProgress������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| circular | true | bool | ���ܿ��أ��Ƿ�Ϊ���ν����� |
| circle_width | 1 | int | ���ν������Ŀ�ȣ���(10) |
| indicator |  | string | ���ý���ָʾ�ƶ�ͼ�� |
| clockwise | true | bool |���õ������� |
| bgcolor |  | string | ���ý�����������ɫ |
| fgcolor |  | string | ���ý�������ǰ��ɫ |
| gradient_color |  | string | ���ý�����ǰ��������ɫ���� fgcolor ͬʱʹ�ã����Բ��������޽���Ч�� |

CircleProgress �ؼ��̳��� `Progress` ���ԣ��������������ο�`Progress`������

## RichEdit������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| vscrollbar | false | bool | �Ƿ�ʹ�����������,��(true) |
| hscrollbar | false | bool | �Ƿ�ʹ�ú��������,��(true) |
| auto_vscroll | false | bool | �Ƿ��������������,��(true) |
| auto_hscroll | false | bool | �Ƿ�������������,��(true) |
| want_tab | true | bool | �Ƿ����tab������Ϣ,��(true) |
| want_return_msg | true | bool | �Ƿ����return������Ϣ,��(true) |
| return_msg_want_ctrl | true | bool | �Ƿ����ctrl+return������Ϣ,��(true) |
| rich_text | true | bool | �Ƿ�ʹ�ø���ʽ,��(true) |
| single_line | true | bool | �Ƿ�ʹ�õ���,��(true) |
| multi_line | true | bool | �Ƿ�ʹ�ö���,��������single_line����,��(true) |
| readonly | false | bool | �Ƿ�ֻ��,��(false) |
| password | false | bool | �Ƿ�Ϊ����ģʽ,��(true) |
| show_password | false | bool | �Ƿ���ʾ�����,��(true) |
| password_char | | string | ���������ַ���Ĭ��Ϊ " * " �ַ�������ͨ��������Ըı�|
| flash_password_char | false | bool | ����ʾ�ַ���Ȼ������ʾ�����ַ�|
| number_only | false | bool | �Ƿ�ֻ������������,��(false) |
| max_number | INT_MAX | int | ������������(����number_onlyΪtrue��ʱ����Ч) |
| min_number | INT_MIN | int | �������С����(����number_onlyΪtrue��ʱ����Ч |
| text_align | left,top | string | ���ֶ��뷽ʽ, ȡֵ: left��right��hcenter��top��vcenter��bottom, ��(right,bottom) |
| text_padding |  | rect | �ı��ڱ߾࣬�磺"2,2,2,2" |
| text |  | string | ��ʾ�ı�,��(�����ı�) |
| textid |  | string | ��ʾ�ı��Ķ����Թ���ID |
| font | | string | ����ID |
| normal_text_color |  | string | ��ͨ״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| disabled_text_color |  | string | ����״̬������ɫ,��ָ����ʹ��Ĭ����ɫ,��(blue) |
| caret_color |  | string | ������ɫ |
| prompt_mode | false | bool | �Ƿ���ʾ��ʾ����,��(true) |
| prompt_text |  | string | �ı�������ʾ����,���ı���textΪ��ʱ��ʾ |
| prompt_textid |  | string | �����Թ��ܵ�ID,��(TEXT_OUT) |
| prompt_color |  | string | �ı�������ʾ���ֵ���ɫ |
| focused_image |  | string | ����״̬�µ�ͼƬ |
| auto_detect_url | false | bool | �Ƿ��Զ����URL�������URL����ʾΪ������ |
| limit_text | | int | ��������ַ��� |
| limit_chars | | string | ��������������Щ�ַ�������"abc"��ʾֻ��������a��b��c�ַ������������������ַ� |
| allow_beep | | bool | �Ƿ�������Beep���� |
| word_wrap | | bool | �Ƿ��Զ����� |
| no_caret_readonly | | bool | ֻ��ģʽ������ʾ��� |
| save_selection | | bool | ��� Ϊ true���򵱿ؼ����ڷǻ״̬ʱ��Ӧ������ѡ���ݵı߽� |
| hide_selection | | bool | �Ƿ�����ѡ������ |
| zoom | | size | �������ű������� wParam�����ű����ķ��ӣ�lParam�����ű����ķ�ĸ��"wParam,lParam" ��ʾ�����ű�������/��ĸ��ʾ�����ţ�ȡֵ��Χ��1/64 < (wParam / lParam) < 64����������"0,0"��ʾ�ر����Ź��ܣ�"2,1"��ʾ�Ŵ�200%��"1,2"��ʾ��С��50% |
| wheel_zoom | | bool | �Ƿ�����Ctrl + �������������ű��� |
| default_context_menu | | bool | �Ƿ�ʹ��Ĭ�ϵ��Ҽ��˵� |
| enable_drag_drop | | bool | �Ƿ������ϷŲ��� |
| spin_class | | string | ����Spin���ܵ�Class���ƣ������Ϊ������ʾSpin��ť����ϸ�÷��μ�ʾ������|
| clear_btn_class | | string | ���������ť���ܵ�Class���ƣ������Ϊ������ʾ�����ť����ϸ�÷��μ�ʾ������ |
| show_passowrd_btn_class | | string |������ʾ���밴ť���ܵ�Class���ƣ������Ϊ������ʾ��ʾ���밴ť ����ϸ�÷��μ�ʾ������ |

RichEdit �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## RichText������
RichText�Ǵ��и�ʽ���ı������ʽ������HTML��ǩ����ʽ�ı���`<RichText>`��ͷ����`</RichText>`��β��    
������`<RichText>��ʽ�ı���ʾ��<a href="URL">�ı�</a></RichText>`    
֧�ֵı�ǩ�б�    
```cpp
   // ֧�ֵı�ǩ�б�(����HTML�ı�ǩ):
   // �������ӣ�   <a href="URL">�ı�</a>
   // ������:      <b> </b>
   // б����:      <i> </i>
   // ɾ����:      <s> </s> �� <del> </del> ���� <strike> </strike>
   // �»�����:    <u> </u>
   // ���ñ���ɫ:  <bgcolor color="#000000"> </bgcolor>
   // ��������:    <font face="����" size="12" color="#000000">
   // ���б�ǩ��   <br/>
```
�����÷�Ҳ���òο�ʾ������

| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| text_align | left,top | string | ���ֶ��뷽ʽ, ȡֵ: left��right��hcenter��top��vcenter��bottom, ��(right,bottom) |
| text_padding |  | rect | �ı��ڱ߾࣬�磺"2,2,2,2" |
| font | | string | ����ID |
| text_color | | string | Ĭ���ı���ɫ |
| default_link_font_color | | string | �������ӣ������ı���ɫֵ |
| hover_link_font_color | | string | �������ӣ�Hover״̬�ı���ɫֵ |
| mouse_down_link_font_color | | string | �������ӣ���갴��״̬�ı���ɫֵ |
| link_font_underline | | string | �������ӣ��Ƿ�ʹ�ô��»��ߵ����� |
| row_spacing_mul | | float | �м�౶��, ����1.5����1.5���м�� |

RichText �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������

## Split������
�ָ����ؼ�������ͨ���϶��ָ����ı����һ������������ؼ��Ŀ�Ȼ��߸߶ȣ�Ӧ�÷���:     
������ں��򲼾֣�HLayout���У��������϶�    
����������򲼾֣�VLayout���У��������϶�    
ע�������������ؼ�������Ϊ�������͵ģ���ָ����޷�����������

| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| enable_split_single | false | bool | ��ֻ��һ���ؼ���ʱ���Ƿ������������ |

Split �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������

## SplitBox������
SplitBox �� Split ����ͬģ��ʵ�֣�����������ο�`Split`������    
SplitBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## TabCtrl������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| selected_id | | int | Ĭ��ѡ������� |
| tab_box_name | | string | �󶨵�TabBox�ؼ����ƣ��󶨺�TabCtrl��ѡ����仯ʱ��TabBox��ѡ��������仯 |

TabCtrl �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## TreeView������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| indent | | int | ���ڵ��������ÿ��ڵ�����һ��indent��λ�� |
| multi_select | false | bool | �Ƿ�֧�ֶ�ѡ |
| check_box_class | | string | ��ʾCheckBox��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| expand_image_class | | string | ��ʾչ��/����ͼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| show_icon | | string | ��ʾͼ���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|

TreeView �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## TreeNode������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| expand_normal_image | | string | չ��ʱ������״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| expand_hot_image | | string | չ��ʱ����ͣ״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| expand_pushed_image | | string | չ��ʱ������״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| expand_disabled_image | | string | չ��ʱ����ֹ״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| collapse_normal_image | | string | ����ʱ������״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| collapse_hot_image | | string | ����ʱ����ͣ״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| collapse_pushed_image | | string | ����ʱ������״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| collapse_disabled_image | | string | ����ʱ����ֹ״̬��ͼƬ�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| expand_image_right_space | | int | չ��ͼƬ�Ҳ�Ŀ�϶ |
| check_box_image_right_space | | int | CheckBoxͼƬ�Ҳ�Ŀ�϶ |
| icon_image_right_space | | int | ͼ���Ҳ�Ŀ�϶ |

TreeNode �ؼ��̳��� `ListBoxItem` ���ԣ��������������ο�`ListBoxItem`������

## ListCtrl������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| type | "report" | string | ���ͣ���ѡֵ��"report"��"icon"��"list" |
| header_class | | string | ListCtrlHeader��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| header_item_class | | string | ListCtrlHeaderItem��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| header_split_box_class | | string | ListCtrlHeader/SplitBox��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| header_split_control_class | | string | ListCtrlHeader/SplitBox/Control��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| enable_header_drag_order | true | bool | �Ƿ�֧���б�ͷ�϶��ı��е�˳��|
| check_box_class | | string | CheckBox��Class����(Ӧ����Header��ListCtrl����)�����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| data_item_class | | string | ListCtrlItem��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| data_sub_item_class | | string | ListCtrlItem/ListCtrlSubItem��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| row_grid_line_width | | int | ���������ߵĿ��|
| row_grid_line_color | | int | ���������ߵ���ɫ|
| column_grid_line_width | | int | ���������ߵĿ��|
| column_grid_line_color | | int | ���������ߵ���ɫ|
| report_view_class | | string | ����Report��ͼ�е�ListBox��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| header_height | | int | ��ͷ�ؼ��ĸ߶�|
| data_item_height | | int | �������Ĭ�ϸ߶�(�и�)|
| show_header | true | bool | �Ƿ���ʾ��ͷ�ؼ�|
| multi_select | true | bool | �Ƿ�֧�ֶ�ѡ|
| enable_column_width_auto | true | bool | �Ƿ�֧��˫��Header�ķָ����Զ������п�|
| auto_check_select | false | bool | �Ƿ��Զ���ѡѡ���������(������Header��ÿ��)|
| show_header_checkbox | false | bool | �Ƿ��ڱ�ͷ�������ʾCheckBox|
| show_data_item_checkbox | false | bool | �Ƿ���ÿ��������ʾCheckBox|
| icon_view_class | | string | ����Icon��ͼ�е�ListBox��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| icon_view_item_image_class | | string | ����Icon��ͼ�е�ListBox��������ͼƬ��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| icon_view_item_label_class | | string | ����Icon��ͼ�е�ListBox��������Label��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| list_view_class | | string | ����List��ͼ�е�ListBox��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| list_view_item_class | | string | ����List��ͼ�е�ListBox������Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| list_view_item_image_class | | string | ����List��ͼ�е�ListBox�������ͼƬ��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| list_view_item_label_class | | string | ����List��ͼ�е�ListBox�������Label��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| enable_item_edit | true | bool | �Ƿ�֧������༭|
| list_ctrl_richedit_class | | string | �༭���Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|

ListCtrl �ؼ��̳��� `VBox` ���ԣ��������������ο�`VBox`������

## PropertyGrid������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| property_grid_xml | | string | �����ļ�XML�����Ϊ�գ�Ĭ��Ϊ��"public/property_grid/property_grid.xml" |
| row_grid_line_width | | int | ���������ߵĿ��|
| row_grid_line_color | | int | ���������ߵ���ɫ|
| column_grid_line_width | | int | ���������ߵĿ��|
| column_grid_line_color | | int | ���������ߵ���ɫ|
| header_class | | string | ��ͷ��Class���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| group_class | | string | �����ClassClass���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| propterty_class | | string | ���Ե�ClassClass���ԣ����巽����ο�`global.xml` �еĶ�Ӧ���ݺ�ʾ������|
| left_column_width | | int | ���һ�еĿ��|

PropertyGrid �ؼ��̳��� `VBox` ���ԣ��������������ο�`VBox`������

## ColorPicker������
ColorPicker��һ�����ڣ������÷���ο�ʾ�������еĲ˵�    
ColorPicker �ؼ��̳��� `Window` ���ԣ��������������ο�`Window`������

## ControlDragable������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| drag_order | true | bool | �Ƿ�֧���϶�����˳����ͬһ�������ڣ� |
| drag_alpha | 216 | int | �����϶�˳��ʱ���ؼ���͸���ȣ�0 - 255�� |
| drag_out | true | bool | �Ƿ�֧���ϳ����ݣ�����ͬ���ڵĲ�ͬ�����ڣ� |

ControlDragable �ؼ��̳��� `Control` ���ԣ��������������ο�`Control`������
