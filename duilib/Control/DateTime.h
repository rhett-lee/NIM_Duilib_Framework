#ifndef _UI_CONTROL_DATETIME_H_
#define _UI_CONTROL_DATETIME_H_
#pragma once
#include "duilib/Control/Label.h"

namespace ui
{
/** ����ʱ��ѡ��ؼ�
*/
class DateTimeWnd;
class UILIB_API DateTime : public Label
{
    friend class DateTimeWnd;
public:
    DateTime();
    DateTime(const DateTime& r) = delete;
    DateTime& operator=(const DateTime& r) = delete;
    virtual ~DateTime();

public:
    /** �Ա���ʱ���ʼ��
    */
    void InitLocalTime();

    /** �������ʱ��ֵ
    */
    void ClearTime();

    /** ��ȡ����ʱ��ֵ
    */
    const std::tm& GetDateTime() const;

    /** ��������ʱ��ֵ
    */
    void SetDateTime(const std::tm& dateTime);

    /** ��ǰ����ʱ��ֵ�Ƿ�Ϊ��Ч������ʱ��
    */
    bool IsValidDateTime() const;

    /** ��ȡ����ʱ���ַ���, ���ڵĸ�ʽ����ͨ��SetStringFormat()��������
    */
    std::wstring GetDateTimeString() const;

    /** ��������ʱ���ַ���, ����GetStringFormat()ָ���ĸ�ʽ, ��������ʱ��ֵ
    */
    bool SetDateTimeString(const std::wstring& dateTime);

    /** ��ȡ���ڵ��ַ�����ʽ
    */
    std::wstring GetStringFormat() const;
    
    /** �������ڸ�ʽ��Ĭ��ֵȡ����EditFormat��ֵ
    * @param [in] sFormat ���ڵĸ�ʽ������ɲο���std::put_time ������˵����
        %a ���ڼ��ļ�д
        %A ���ڼ���ȫ��
        %b �·ֵļ�д
        %B �·ݵ�ȫ��
        %c ��׼�����ڵ�ʱ�䴮
        %C ��ݵĺ���λ����
        %d ʮ���Ʊ�ʾ��ÿ�µĵڼ���
        %D ��/��/��
        %e �����ַ����У�ʮ���Ʊ�ʾ��ÿ�µĵڼ���
        %F ��-��-��
        %g ��ݵĺ���λ���֣�ʹ�û����ܵ���
        %G ��֣�ʹ�û����ܵ���
        %h ��д���·���
        %H 24Сʱ�Ƶ�Сʱ
        %I 12Сʱ�Ƶ�Сʱ
        %j ʮ���Ʊ�ʾ��ÿ��ĵڼ���
        %m ʮ���Ʊ�ʾ���·�
        %M ʮʱ�Ʊ�ʾ�ķ�����
        %n ���з�
        %p ���ص�AM��PM�ĵȼ���ʾ
        %r 12Сʱ��ʱ��
        %R ��ʾСʱ�ͷ��ӣ�hh:mm
        %S ʮ���Ƶ�����
        %t ˮƽ�Ʊ��
        %T ��ʾʱ���룺hh:mm:ss
        %u ÿ�ܵĵڼ��죬����һΪ��һ�� ��ֵ��0��6������һΪ0��
        %U ����ĵڼ��ܣ�����������Ϊ��һ�죨ֵ��0��53��
        %V ÿ��ĵڼ��ܣ�ʹ�û����ܵ���
        %w ʮ���Ʊ�ʾ�����ڼ���ֵ��0��6��������Ϊ0��
        %W ÿ��ĵڼ��ܣ�������һ��Ϊ��һ�죨ֵ��0��53��
        %x ��׼�����ڴ�
        %X ��׼��ʱ�䴮
        %y �������͵�ʮ������ݣ�ֵ��0��99��
        %Y �����Ͳ��ֵ�ʮ�������
        %z��%Z ʱ�����ƣ�������ܵõ�ʱ�������򷵻ؿ��ַ���
        %% �ٷֺ�
    */
    void SetStringFormat(const std::wstring& sFormat);

    /** ����ʱ��ı༭��ʽ
    */
    enum class EditFormat
    {
        kDateCalendar,      //�༭ʱ��ʾ����-��-�գ�ͨ��������չʾ�������ķ�ʽ���޸����ڣ���֧��ѡ��ʱ��
        kDateUpDown,        //�༭ʱ��ʾ����-��-�գ�ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸����ڣ���֧��ѡ��ʱ��
        kDateTimeUpDown,    //�༭ʱ��ʾ����-��-�� ʱ:��:�룬ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸����ں�ʱ��
        kDateMinuteUpDown,  //�༭ʱ��ʾ����-��-�� ʱ:�֣�ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸����ں�ʱ��
        kTimeUpDown,        //�༭ʱ��ʾ��ʱ:��:�룬ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸�ʱ�䣬��֧���޸�����
        kMinuteUpDown,      //�༭ʱ��ʾ��ʱ:�֣�ͨ���ؼ����Ҳ����һ������-���µĿؼ����޸�ʱ�䣬��֧���޸�����
    };

    /** ���ñ༭��ʽ
    */
    void SetEditFormat(EditFormat editFormat);

    /** ��ȡ�༭ģʽ
    */
    EditFormat GetEditFormat() const;

    /** �����±༭���ڵ�λ��
    */
    void UpdateEditWndPos();

    /** �������ʱ��ֵ�仯�����¼�
    */
    void AttachTimeChange(const EventCallback& callback) { AttachEvent(kEventValueChange, callback); }

public:
    //������麯��
    virtual std::wstring GetType() const override;
    virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
    virtual void HandleEvent(const EventArgs& msg) override;

    //���ڳ�ʼ��xml����
    virtual void OnInit() override;

private:
    /** �Ƚ�����ʱ���Ƿ���ͬ
    */
    bool IsEqual(const std::tm& a, const std::tm& b) const;

private:
    /** ��ǰ������ʱ��ֵ
    */
    std::tm m_dateTime;

    /* ����ʱ����ʾ��ʽ
    */
    UiString m_sFormat;

    /** ����ʱ��ı༭��ʽ
    */
    EditFormat m_editFormat;

    /** �����յķָ���
    */
    wchar_t m_dateSeparator;

    /** �������ڿؼ����ڽӿ�
    */
    DateTimeWnd* m_pDateWindow;
};

}//namespace ui

#endif // _UI_CONTROL_DATETIME_H_
