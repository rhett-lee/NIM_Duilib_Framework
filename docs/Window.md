## ���ڵ�����
| �������� | Ĭ��ֵ | �������� | ����[Window.h](../duilib/Core/Window.h)�еĺ���| ��; |
| :--- | :--- | :--- | :--- |:--- |
| size | 0,0 | size | SetInitSize|���ڵĳ�ʼ����С, ֧�ֵĸ�ʽ��size="1200,800", ����size="50%,50%", ����size="1200,50%", size="50%,800"���ٷֱ���ָ��Ļ��Ȼ��߸߶ȵİٷֱ� |
| mininfo | 0,0 | size | SetMinInfo|������С��С, ��(320,240) |
| maxinfo | 0,0 | size | SetMaxInfo|��������С, ��(1600,1200) |
| sizebox | 0,0,0,0 | rect | SetSizeBox|���ڿ��϶��ı䴰�ڴ�С�ı߾�, ��(4,4,6,6) |
| caption | 0,0,0,0 | rect | SetCaptionRect|���ڿ��϶��ı�������С�ı߾�, ���һ��������ָ���ϱ߿�ľ���,��(0,0,0,28) |
| use_system_caption | false | bool | SetUseSystemCaption|�����Ƿ�ʹ��ϵͳ������ |
| text |  | string | SetText|��������ַ���|
| textid |  | string | SetTextId|��������ַ�����ID, ID�ڶ������ļ���ָ��, ��(STRID_MIANWINDOW_TITLE) |
| round_corner | 0,0 | size | SetRoundCorner|����Բ�Ǵ�С, ��(4,4) |
| shadow_attached | true | bool | SetShadowAttached|�����Ƿ񸽼���ӰЧ��,��(true) |
| shadow_image |  | string | SetShadowImage|ʹ���Զ������Ӱ�ز�ȥ����Ĭ�ϵ���ӰЧ�������õ�·��Ҫע�����·���Լ��Ź������ԣ���(file='../public/bk/bk_shadow.png' corner='30,30,30,30') |
| shadow_corner | 0,0,0,0 | rect | SetShadowCorner|������shadowimage���Ժ����ô�������ָ����Ӱ�زĵľŹ����������������һ��Ҫд��size����ǰ�� |
| alpha_fix_corner | 14,14,14,14 | rect | SetAlphaFixCorner|͸��ͨ���޲���Χ�ĵľŹ������� |
| render_transparent | false | bool | SetRenderTransparent|���Ϊtrue����ʾ������ȾΪ͸��ͼ�� |
| layered_window | false | bool | SetLayeredWindow|�����Ƿ�Ϊ�㴰�� |
| alpha | 255 | int | SetWindowAlpha|���ô��ڵ�͸���ȣ�0 - 255��������ʹ�ò㴰��ʱ��Ч |

��ע���������ԵĽ��������μ���[WindowBuilder::Create����](../duilib/Core/WindowBuilder.cpp)    
��ע��������XML�еı�ǩ�����ǣ�"Window"     
ʹ��ʾ����    
```xml
<Window size="75%,90%" mininfo="80,50" use_system_caption="false" caption="0,0,0,36"
        shadowattached="true" layered_window="true" alpha="255" sizebox="4,4,4,4">
</Window>
```