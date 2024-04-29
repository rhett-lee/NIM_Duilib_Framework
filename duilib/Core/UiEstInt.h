#ifndef UI_CORE_UIESTINT_H_
#define UI_CORE_UIESTINT_H_

#pragma once

#include "duilib/duilib_defs.h"
#include <cstdint>

namespace ui
{

/** �ؼ����㳤�ȣ����ȣ���ֵ
*/
class UILIB_API UiEstInt
{
public:
    //��ֵ���Ͷ���
    enum class Type
    {
        Int32   = 0,    //����32λ����ֵ���̶���ֵ
        Stretch = 1     //���죨���ⲿ�������������þ�����ֵ��
    };

    //��ֵ����
    Type type;

    //������ֵ:
    // �� type Ϊ Int32 ʱ, ����Ϊ�̶���ֵ
    // �� type Ϊ Stretch, ȡֵ��Χ�� (0,100]�������ɸ���������ռ�ٷֱȷ���
    int32_t value;

public:
    /** ����һ���������͵�ֵ
    */
    static UiEstInt MakeStretch()
    {
        UiEstInt estInt;
        estInt.SetStretch();
        return estInt;
    }

    /** ����һ���������͵�ֵ, ��ָ��ֵ
    */
    static UiEstInt MakeStretch(int32_t iValue)
    {
        UiEstInt estInt;
        estInt.SetStretch(iValue);
        return estInt;
    }

public:
    /** ���캯��, Ĭ��Ϊ����ֵ0
    */
    UiEstInt(): type(Type::Int32), value(0)
    { }

    /** ���캯��, ����Ϊ����ֵ
    */
    explicit UiEstInt(int32_t iValue) : type(Type::Int32), value(iValue)
    { }

    /** �ж��Ƿ�Ϊ��������
    */
    bool IsStretch() const { return type == Type::Stretch;}

    /** �ж��Ƿ�Ϊ32λ����ֵ����
    */
    bool IsInt32() const { return type == Type::Int32; }

    /** �Ƿ�Ϊ��Чֵ����ֵ���ͣ������ȣ�������ڵ����㣩
    */
    bool IsValid() const
    {
        if (type == Type::Int32) {
            return value >= 0;
        }
        return true;
    }

    /** ��ֵΪ32λ����ֵ
    */
    void SetInt32(int32_t iValue)
    {
        ASSERT(iValue >= 0);
        type = Type::Int32;
        value = iValue >= 0 ? iValue : 0;
    }

    /** ��ȡ32λ����ֵ
    */
    int32_t GetInt32() const
    {
        if (type != Type::Int32) {
            return 0;
        }
        return value >= 0 ? value : 0;
    }

    /** ��ȡ��������ֵ����Чֵ(0, 100], ����ٷ�֮��
    */
    int32_t GetStretchPercentValue() const
    {
        if (type != Type::Stretch) {
            return 0;
        }
        if ((value > 0) && (value <= 100)) {
            return value;
        }
        return 100;
    }

    /** ��ֵΪ��������
    */
    void SetStretch() 
    { 
        type = Type::Stretch; 
        value = 100;
    }

    /** ��ֵΪ�������ͣ���ָ��ֵ
    */
    void SetStretch(int32_t iValue)
    {
        type = Type::Stretch;
        if ((iValue > 0) && (iValue <= 100)) {
            value = iValue;
        }
        else {
            value = 100;
        }
    }

    /** �ж��Ƿ�������һ��Size��ͬ
    */
    bool Equals(const UiEstInt& dst) const
    {
        if (IsStretch() && dst.IsStretch()) {
            return value == dst.value;
        }
        else if (IsInt32() && dst.IsInt32()) {
            return value == dst.value;
        }
        return false;
    }

    /** �ж�����ֵ�Ƿ����
    */
    friend bool operator == (const UiEstInt& a, const UiEstInt& b)
    {
        return a.Equals(b);
    }

    /** �ж�����ֵ�Ƿ����
    */
    friend bool operator != (const UiEstInt& a, const UiEstInt& b)
    {
        return !a.Equals(b);
    }
};

}//namespace ui

#endif // UI_CORE_UIESTINT_H_
