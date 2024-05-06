#ifndef UI_RENDER_GDIPLUS_BITMAP_HELPER_H_
#define UI_RENDER_GDIPLUS_BITMAP_HELPER_H_

#pragma once

#include "duilib/Render/IRender.h"

namespace ui 
{
    namespace BitmapHelper 
    {
#ifdef UILIB_IMPL_WINSDK

        /** ����һ��Render���󣬲�����HDC�ϵ����ݵ�Render
        * @return ���ص�Render�����ɵ����߸����ͷ���Դ
        */
        IRender* CreateRenderObject(int srcRenderWidth, int srcRenderHeight, HDC hSrcDc, int srcDcWidth, int srcDcHeight);

        /** ����һ��Render���󣬲�����Bitmap�ϵ����ݵ�Render
        * @return ���ص�Render�����ɵ����߸����ͷ���Դ
        */
        IRender* CreateRenderObject(IBitmap* pBitmap);

        /** ����һ��Bitmap���󣬲�����HDC�ϵ����ݵ�λͼ
        * @return ���ص�IBitmap�����ɵ����߸����ͷ���Դ
        */
        IBitmap* CreateBitmapObject(int srcRenderWidth, int srcRenderHeight, HDC hSrcDc, int srcDcWidth, int srcDcHeight);

        /** ��һ��GDI Bitmap���󣬻�ȡһ��HBITMAP���
        * @return ����HBITMAP������ⲿ��������Ҫ�ͷ���Դ���Ա�����Դй¶
        */
        HBITMAP CreateGDIBitmap(IBitmap* pBitmap);

        /** ����һ���豸�޹ص�λͼ
	    *@return ����λͼ������ɵ��÷��ͷ�λͼ��Դ
	    */
	    HBITMAP CreateGDIBitmap(int32_t nWidth, int32_t nHeight, bool flipHeight, LPVOID* pBits);
#endif
    }
}

#endif //UI_RENDER_GDIPLUS_BITMAP_HELPER_H_

