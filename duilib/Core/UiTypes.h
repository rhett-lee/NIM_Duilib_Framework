#ifndef UI_CORE_UITYPES_H_
#define UI_CORE_UITYPES_H_

#pragma once

#include "duilib/Core/UiSize.h"
#include "duilib/Core/UiSize64.h"
#include "duilib/Core/UiPoint.h"
#include "duilib/Core/UiPointF.h"
#include "duilib/Core/UiRect.h"
#include "duilib/Core/UiColor.h"
#include "duilib/Core/UiFont.h"
#include "duilib/Core/UiPadding.h"
#include "duilib/Core/UiMargin.h"
#include "duilib/Core/UiFixedInt.h"
#include "duilib/Core/UiEstInt.h"
#include "duilib/Core/UiString.h"

namespace ui
{
    /** ���õĿؼ���С
    */
    class UILIB_API UiFixedSize
    {
    public:
        /** ���
        */
        UiFixedInt cx;

        /** �߶�
        */
        UiFixedInt cy;
    };

    /** ����Ŀؼ���С�����UiFixedSize��û��Auto���ͣ�
    */
    class UILIB_API UiEstSize
    {
    public:
        /** ���
        */
        UiEstInt cx;

        /** �߶�
        */
        UiEstInt cy;
    };

    /** ����ؼ���С�Ľ��
    */
    class UILIB_API UiEstResult
    {
    public:
        /** �Ƿ���Ҫ����������С
        */
        bool m_bReEstimateSize = true;

        /** ���ι���ʱ�Ŀ��þ��δ�С(�������Ӱ��������)
        */
        UiSize m_szAvailable;

        /** �ؼ����ѹ����С�����ȺͿ�ȣ����൱�ڹ����Ļ���ֵ
        */
        UiEstSize m_szEstimateSize;
    };

    /** ��UiFixedInt����UiEstInt
    */
    inline UiEstInt MakeEstInt(const UiFixedInt& fixedInt)
    {
        UiEstInt estInt;
        if (fixedInt.IsStretch()) {
            estInt.SetStretch(fixedInt.GetStretchPercentValue());
        }
        else if (fixedInt.IsInt32()) {
            estInt.SetInt32(fixedInt.GetInt32());
        }
        else {
            estInt.SetInt32(0);
        }
        return estInt;
    }

    /** �����������͵ĳ���ֵ
    */
    inline int32_t CalcStretchValue(const UiEstInt& estInt, int32_t nAvailable)
    {
        if (estInt.IsStretch()) {
            int32_t nStretchValue = estInt.GetStretchPercentValue(); //����ٷֱ�ֵ��ȡֵ��ΧΪ��(0, 100]
            if ((nStretchValue > 0) && (nStretchValue < 100)) {
                //���ذ��ٷֱȼ����ֵ, ��������
                return static_cast<int32_t>(nAvailable * nStretchValue / 100.0f + 0.5f);
            }
            else {
                //����ԭֵ
                return nAvailable;
            }
        }
        //�������������ԭֵ(�ݴ�)
        return nAvailable;
    }

    /** �����������͵ĳ���ֵ
    */
    inline int32_t CalcStretchValue(const UiFixedInt& fixedInt, int32_t nAvailable)
    {
        if (fixedInt.IsStretch()) {
            int32_t nStretchValue = fixedInt.GetStretchPercentValue(); //����ٷֱ�ֵ��ȡֵ��ΧΪ��(0, 100]
            if ((nStretchValue > 0) && (nStretchValue < 100)) {
                //���ذ��ٷֱȼ����ֵ, ��������
                return static_cast<int32_t>(nAvailable * nStretchValue / 100.0f + 0.5f);
            }
            else {
                //����ԭֵ
                return nAvailable;
            }
        }
        //�������������ԭֵ(�ݴ�)
        return nAvailable;
    }

    /** ��UiFixedSize����UiEstSize
    */
    inline UiEstSize MakeEstSize(const UiFixedSize& fixedSize)
    {
        UiEstSize estSize;
        estSize.cx = MakeEstInt(fixedSize.cx);
        estSize.cy = MakeEstInt(fixedSize.cy);
        return estSize;
    }

    /** ��UiSize����UiEstSize
    */
    inline UiEstSize MakeEstSize(const UiSize& size)
    {
        UiEstSize estSize;
        estSize.cx = UiEstInt(size.cx);
        estSize.cy = UiEstInt(size.cy);
        return estSize;
    }

    /** ��UiSize����UiEstSize
    */
    inline UiSize MakeSize(const UiEstSize& estSize)
    {
        ASSERT(estSize.cx.IsInt32() && estSize.cy.IsInt32());
        UiSize size(estSize.cx.GetInt32(), estSize.cy.GetInt32());
        return size;
    }

    /** ��64λ����ֵת��λ32λ����ֵ
    */
    inline int32_t TruncateToInt32(int64_t x)
    {
        ASSERT((x >= INT32_MIN) && (x <= INT32_MAX) );
        x = x < INT32_MAX ? x : INT32_MAX;
        x = x > INT32_MIN ? x : INT32_MIN;
        return static_cast<int32_t>(x);
    }

    /** ��32λy�з�������ֵת��λ16λ�޷�������ֵ
    */
    inline uint16_t TruncateToUInt16(uint32_t x)
    {
        ASSERT(x <= UINT16_MAX);
        x = x < UINT16_MAX ? x : UINT16_MAX;
        return static_cast<uint16_t>(x);
    }

    /** ��32λ�޷�������ֵת��λ16λ�޷�������ֵ
    */
    inline uint16_t TruncateToUInt16(int32_t x)
    {
        ASSERT((x >= 0) && (x <= UINT16_MAX));
        x = x > 0 ? x : 0;
        x = x < UINT16_MAX ? x : UINT16_MAX;
        return static_cast<uint16_t>(x);
    }

    /** ��32λ����ֵת��λ8λ����ֵ
    */
    inline int8_t TruncateToInt8(int32_t x)
    {
        ASSERT((x >= INT8_MIN) && (x <= INT8_MAX));
        x = x < INT8_MAX ? x : INT8_MAX;
        x = x > INT8_MIN ? x : INT8_MIN;
        return static_cast<int8_t>(x);
    }

    /** ��32λ����ֵת��λ8λ����ֵ
    */
    inline uint8_t TruncateToUInt8(int32_t x)
    {
        ASSERT((x >= 0) && (x <= UINT8_MAX));
        x = x > 0 ? x : 0;
        x = x < UINT8_MAX ? x : UINT8_MAX;
        return static_cast<uint8_t>(x);
    }

}//namespace ui

#endif // UI_CORE_UITYPES_H_
