## ���ֵ�����
| ������ | �������� |����ͷ�ļ�| ��; |
| :--- | :--- |:--- | :--- |
| Layout | |[duilib/Box/Layout.h](../duilib/Box/Layout.h) | ���ɲ��֣��������֣�|
| HLayout |Layout |[duilib/Box/HLayout.h](../duilib/Box/HLayout.h) | ˮƽ����|
| VLayout |Layout |[duilib/Box/VLayout.h](../duilib/Box/VLayout.h) | ��ֱ����|
| HTileLayout |Layout| [duilib/Box/HTileLayout.h](../duilib/Box/HTileLayout.h) | ˮƽ��Ƭ����|
| VTileLayout |Layout| [duilib/Box/VTileLayout.h](../duilib/Box/VTileLayout.h) | ��ֱ��Ƭ����|
| VirtualHLayout |HLayout| [duilib/Box/VirtualHLayout.h](../duilib/Box/VirtualHLayout.h) | ���ˮƽ����|
| VirtualVLayout |VLayout| [duilib/Box/VirtualVLayout.h](../duilib/Box/VirtualVLayout.h) | ���ֱ����|
| VirtualHTileLayout |HTileLayout| [duilib/Box/VirtualHTileLayout.h](../duilib/Box/VirtualHTileLayout.h) | ���ˮƽ��Ƭ����|
| VirtualVTileLayout |VTileLayout| [duilib/Box/VirtualVTileLayout.h](../duilib/Box/VirtualVTileLayout.h) | ���ֱ��Ƭ����|

1. ���ɲ��֣�Layout���������֣�
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| child_margin | 0 | int | �ӿؼ�֮��Ķ���߾�: X �᷽�� �� Y �᷽��ͬʱ����Ϊ��ֵͬ|
| child_margin_x | 0 | int | �ӿؼ�֮��Ķ���߾�: X �᷽�� |
| child_margin_y | 0 | int | �ӿؼ�֮��Ķ���߾�: Y �᷽��|
2. ˮƽ���֣�HLayout�����������Լ̳����ɲ��ֵ�����
3. ��ֱ���֣�VLayout�����������Լ̳����ɲ��ֵ�����
4. ˮƽ��Ƭ���֣�HTileLayout�����������Լ̳����ɲ��ֵ�����
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| rows | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|
5. ��ֱ��Ƭ���֣�VTileLayout�����������Լ̳����ɲ��ֵ�����
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| columns | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|
6. ���ˮƽ���֣�VirtualHLayout�����������Լ̳�ˮƽ���ֵ�����
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
7. ���ֱ���֣�VirtualVLayout�����������Լ̳д�ֱ���ֵ�����
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
8. ���ˮƽ��Ƭ���֣�VirtualHLayout�����������Լ̳�ˮƽ��Ƭ���ֵ�����
9. ���ֱ��Ƭ���֣�VirtualVLayout�����������Լ̳д�ֱ��Ƭ���ֵ�����

## Box������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| child_margin | 0 | int | �ӿؼ�֮��Ķ���߾�: X �᷽�� �� Y �᷽��ͬʱ����Ϊ��ֵͬ|
| child_margin_x | 0 | int | �ӿؼ�֮��Ķ���߾�: X �᷽�� |
| child_margin_y | 0 | int | �ӿؼ�֮��Ķ���߾�: Y �᷽��|
| margin | 0,0,0,0 | rect | ��߾�,��(2,2,2,2) |
| padding | 0,0,0,0 | rect | �ڱ߾�,��(2,2,2,2) |
| mouse_child | true | bool | ���ؼ����ӿؼ��Ƿ������Ӧ�û�����, true ���� false|
| drag_out_id |  | int | �����Ƿ�֧����ק�ϳ������������������0��֧���ϳ�������֧���ϳ����ϳ���drop_in_id==drag_out_id��������|
| drop_in_id |  | int | �����Ƿ�֧����קͶ�Ž��������: ���������0��֧�����룬����֧������(��drag_out_id==drop_in_id���������뵽������)|

Box �ؼ��̳��� `Control` ���ԣ��������������ο�������[Control(�����ؼ�)������](./Control.md)

## VBox������
VBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## HBox������
HBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## TabBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| fade_switch | false | bool | ���л�ҳ��ʱ�Ƿ�ʹ�ö���Ч��, ��(false) |
| selected_id | 0 | int | Ĭ��ѡ�е�ҳ��id, ��(0) |

TabBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## VTileBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| columns | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

VTileBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## HTileBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| rows | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

HTileBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## ScrollBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| vscrollbar | false | bool | �Ƿ�ʹ�����������,��(true) |
| hscrollbar | false | bool | �Ƿ�ʹ�ú��������,��(true) |
| vscrollbar_style |  | string | ���ñ��������������������ʽ |
| hscrollbar_style |  | string | ���ñ������ĺ������������ʽ |
| scrollbar_padding | 0,0,0,0 | rect | ����������߾�,�����ù�������ռ������,��(2,2,2,2) |
| vscroll_unit | 30 | int | �����Ĵ�ֱ��������������, 0����ʹ��Ĭ�ϲ��� |
| hscroll_unit | 30 | int | ������ˮƽ��������������, 0����ʹ��Ĭ�ϲ��� |
| scrollbar_float | true | bool | �����Ĺ������Ƿ��������ӿؼ�����,��(true) |
| vscrollbar_left | false | bool | �����Ĺ������Ƿ��������ʾ |
| hold_end | false | bool | �Ƿ�һֱ������ʾĩβλ��,��(true) |

ScrollBox �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## VScrollBox������
VScrollBox �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## HScrollBox������
HScrollBox �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## VTileScrollBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| columns | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

VTileScrollBox �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## HTileScrollBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| rows | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

HTileScrollBox �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## ListBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| multi_select | false | bool | �Ƿ�֧�ֶ�ѡ |
| paint_selected_colors | Ĭ�Ϲ��� | bool | ��ѡ��ʱ���Ƿ���ʾѡ�񱳾�ɫ |
| scroll_select | false | bool | �Ƿ��������ֵĹ����ı�ѡ��������(��ѡ�����ѡ��Ч) |
| select_next_when_active_removed | | bool | ���Ƴ�һ�������, ������Ƴ�����ѡ����Ƿ��Զ�ѡ����һ��(��ѡ�����ѡ��Ч) |

ListBox �ؼ��̳��� `ScrollBox` ���ԣ��������������ο�`ScrollBox`������

## VListBox������
VListBox �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## HListBox������
HListBox �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## VTileListBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| columns | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

VTileListBox �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## HTileListBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| rows | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

HTileListBox �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## VirtualListBox������
VirtualListBox �ؼ��̳��� `ListBox` ���ԣ��������������ο�`ListBox`������

## VirtualVListBox������
VirtualVListBox �ؼ��̳��� `VirtualListBox` ���ԣ��������������ο�`VirtualListBox`������

## VirtualHListBox������
VirtualHListBox �ؼ��̳��� `VirtualListBox` ���ԣ��������������ο�`VirtualListBox`������

## VirtualVTileListBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| columns | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

VirtualVTileListBox �ؼ��̳��� `VirtualListBox` ���ԣ��������������ο�`VirtualListBox`������

## VirtualHTileListBox������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| item_size | 0,0 | size | �����С, �ÿ�Ⱥ͸߶ȣ��ǰ����˿ؼ�����߾���ڱ߾�ģ�����"100,40"|
| rows | 0 | int | �������Ϊ"auto"����ʾ�Զ��������������Ϊ��ֵ����ʾ����Ϊ�̶�����|
| scale_down | true | bool | ���ؼ����ݳ����߽�ʱ����������С����ʹ�ؼ�������ȫ��ʾ����Ƭ������|

VirtualHTileListBox �ؼ��̳��� `VirtualListBox` ���ԣ��������������ο�`VirtualListBox`������

## BoxDragable������
| �������� | Ĭ��ֵ | �������� | ��; |
| :--- | :--- | :--- | :--- |
| drag_order | true | bool | �Ƿ�֧���϶�����˳����ͬһ�������ڣ� |
| drag_alpha | 216 | int | �����϶�˳��ʱ���ؼ���͸���ȣ�0 - 255�� |
| drag_out | true | bool | �Ƿ�֧���ϳ����ݣ�����ͬ���ڵĲ�ͬ�����ڣ� |

BoxDragable �ؼ��̳��� `Box` ���ԣ��������������ο�`Box`������

## HBoxDragable������
HBoxDragable �� BoxDragable��һ��ģ����ʵ�ֵģ�������ο�`BoxDragable`������    
HBoxDragable �ؼ��̳��� `HBox` ���ԣ��������������ο�`HBox`������

## VBoxDragable������
VBoxDragable �� BoxDragable��һ��ģ����ʵ�ֵģ�������ο�`BoxDragable`������    
VBoxDragable �ؼ��̳��� `VBox` ���ԣ��������������ο�`VBox`������

