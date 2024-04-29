#include "ColorPickerRegular.h"

namespace ui
{
/** ��ɫѡ������������ɫ
*/
class ColorPickerRegularProvider : public ui::VirtualListBoxElement
{
public:
    ColorPickerRegularProvider();

    /** ������ɫ����
    * @param [in] uiColors �ⲿ�ṩ����ɫ���ݣ���һ������ɫ���ƣ��ڶ�������ɫֵ
    */
    void SetColors(const std::vector<std::pair<std::wstring, int32_t>>& uiColors);

    /** ����һ��������
    * @return ���ش������������ָ��
    */
    virtual Control* CreateElement() override;

    /** ���ָ��������
    * @param [in] pControl ������ؼ�ָ��
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    */
    virtual bool FillElement(ui::Control* pControl, size_t nElementIndex) override;

    /** ��ȡ����������
    * @return ��������������
    */
    virtual size_t GetElementCount() const override;

    /** ����ѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @param [in] bSelected true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual void SetElementSelected(size_t nElementIndex, bool bSelected) override;

    /** ��ȡѡ��״̬
    * @param [in] nElementIndex ����Ԫ�ص�����ID����Χ��[0, GetElementCount())
    * @return true��ʾѡ��״̬��false��ʾ��ѡ��״̬
    */
    virtual bool IsElementSelected(size_t nElementIndex) const override;

    /** ��ȡѡ���Ԫ���б�
    * @param [in] selectedIndexs ���ص�ǰѡ���Ԫ���б���Ч��Χ��[0, GetElementCount())
    */
    virtual void GetSelectedElements(std::vector<size_t>& selectedIndexs) const override;

    /** �Ƿ�֧�ֶ�ѡ
    */
    virtual bool IsMultiSelect() const override;

    /** �����Ƿ�֧�ֶ�ѡ���ɽ������ã����������ؼ�һ��
    * @return bMultiSelect true��ʾ֧�ֶ�ѡ��false��ʾ��֧�ֶ�ѡ
    */
    virtual void SetMultiSelect(bool bMultiSelect) override;

    /** ѡ��һ����ɫ
    */
    size_t SelectColor(const UiColor& color);

    /** ��ȡ��ǰѡ�����ɫ
    */
    UiColor GetSelectedColor() const;

public:
    /** ������ɫֵ����Ӧ���ַ�������
    */
    void GetDefaultColors(std::vector<std::pair<std::wstring, int32_t>>& uiColors);

    /** ������ɫֵ����Ӧ���ַ�������
    */
    void GetBasicColors(std::vector<std::pair<std::wstring, int32_t>>& uiColors);

private:
    /** ��ɫ�ṹ
    */
    struct RegularColor
    {
        //��ɫ����ʾ����
        UiString colorName;
        //��ɫֵ
        UiColor colorValue;
        //�Ƿ�ѡ��
        bool m_bSelected;

        //�ȽϺ���
        bool operator < (const RegularColor& r)
        {
            //������ɫ�ĻҶ�ֵ����
            double v1 = colorValue.GetR() * 0.299 + colorValue.GetG() * 0.587 + colorValue.GetB() * 0.114;
            double v2 = r.colorValue.GetR() * 0.299 + r.colorValue.GetG() * 0.587 + r.colorValue.GetB() * 0.114;
            return v1 < v2;
        }
    };

    /** ��ɫ�б�
    */
    std::vector<RegularColor> m_colors;
};

ColorPickerRegular::ColorPickerRegular()
{
    m_regularColors = std::make_unique<ColorPickerRegularProvider>();
    SetDataProvider(m_regularColors.get());
    AttachSelect([this](const ui::EventArgs& args) {
        Control* pControl = GetItemAt(args.wParam);
        if (pControl != nullptr) {
            std::wstring colorString = pControl->GetBkColor();
            if (!colorString.empty()) {
                UiColor newColor = pControl->GetUiColor(colorString);
                SendEvent(kEventSelectColor, newColor.GetARGB());
            }
        }
        return true;
        });
}

std::wstring ColorPickerRegular::GetType() const { return DUI_CTR_COLOR_PICKER_REGULAR; }

void ColorPickerRegular::SelectColor(const UiColor& color)
{
    size_t nCurSel = m_regularColors->SelectColor(color);
    size_t nOldSel = GetCurSel();
    if (nCurSel != nOldSel) {
        Control* pControl = GetItemAt(nOldSel);
        if (pControl != nullptr) {
            ListBoxItem* pListItem = dynamic_cast<ListBoxItem*>(pControl);
            if ((pListItem != nullptr) && (pListItem->IsSelected())) {
                pListItem->SetSelected(false);
            }
        }
        if (nCurSel < GetItemCount()) {
            SetCurSel(nCurSel);
        }        
    }
    Refresh();
    Invalidate();
}

UiColor ColorPickerRegular::GetSelectedColor() const
{
    return m_regularColors->GetSelectedColor();
}

void ColorPickerRegular::SetPos(UiRect rc)
{
    UiRect rect = rc;
    rect.Deflate(GetPadding());
    //�Զ�����ÿ����ɫ��Ĵ�С����Ӧ����
    int32_t elementCount = 0;
    VirtualListBoxElement* pListBoxElement = GetDataProvider();
    if (pListBoxElement != nullptr) {
        elementCount = (int32_t)pListBoxElement->GetElementCount();
    }
    VirtualVTileLayout* pVirtualLayout = dynamic_cast<VirtualVTileLayout*>(GetLayout());
    if ((pVirtualLayout != nullptr) && (elementCount > 0)) {
        if ((m_szItem.cx == 0) && (m_szItem.cy == 0)) {
            m_szItem = pVirtualLayout->GetItemSize();
        }
        int32_t columns = pVirtualLayout->GetColumns();
        if (columns > 0) {
            int32_t rows = elementCount / columns;
            if ((elementCount % columns) != 0) {
                rows += 1;
            }
            if (rows <= 0) {
                rows += 1;
            }
            //�Զ�����Item��С            
            int32_t childMarginX = pVirtualLayout->GetChildMarginX();
            int32_t childMarginY = pVirtualLayout->GetChildMarginY();
            UiSize szItem;
            szItem.cx = (rect.Width() - childMarginX * (columns - 1)) / columns;
            szItem.cy = (rect.Height() - childMarginY * (rows - 1)) / rows;
            if ((szItem.cx > 0) && (szItem.cy > 0)) {
                pVirtualLayout->SetItemSize(szItem, false);
            }
            else if ((m_szItem.cx > 0) && (m_szItem.cy > 0)) {
                pVirtualLayout->SetItemSize(m_szItem, false);
            }
        }
    }
    __super::SetPos(rc);
}

void ColorPickerRegular::SetColumns(int32_t nColumns)
{
    ASSERT(nColumns > 0);
    if (nColumns <= 0) {
        return;
    }
    VirtualVTileLayout* pVirtualLayout = dynamic_cast<VirtualVTileLayout*>(GetLayout());
    if (pVirtualLayout != nullptr) {
        pVirtualLayout->SetColumns(nColumns);
    }
}

void ColorPickerRegular::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
    if (strName == L"color_type") {
        if (strValue == L"basic") {
            //ʹ�û�����ɫ
            std::vector<std::pair<std::wstring, int32_t>> uiColors;
            m_regularColors->GetBasicColors(uiColors);
            m_regularColors->SetColors(uiColors);
        }
        else {
            //ʹ��Ĭ����ɫ
            std::vector<std::pair<std::wstring, int32_t>> uiColors;
            m_regularColors->GetDefaultColors(uiColors);
            m_regularColors->SetColors(uiColors);
        }
    }
    else {
        __super::SetAttribute(strName, strValue);
    }
}

////////////////////////////////////////////////////////////
//
ColorPickerRegularProvider::ColorPickerRegularProvider()
{
    std::vector<std::pair<std::wstring, int32_t>> uiColors;
    GetDefaultColors(uiColors);
    SetColors(uiColors);
}

void ColorPickerRegularProvider::SetColors(const std::vector<std::pair<std::wstring, int32_t>>& uiColors)
{
    m_colors.clear();
    RegularColor regularColor;
    regularColor.m_bSelected = false;
    for (const auto& color : uiColors) {
        regularColor.colorValue = UiColor(color.second);
        std::wstring colorString = ui::StringHelper::Printf(L"#%02X%02X%02X%02X",
            regularColor.colorValue.GetA(),
            regularColor.colorValue.GetR(),
            regularColor.colorValue.GetG(),
            regularColor.colorValue.GetB());
        std::wstring colorName = color.first;
        StringHelper::ReplaceAll(L",", L", ", colorName);
        colorName = colorString + L", " + colorName;
        regularColor.colorName = colorName;
        if (regularColor.colorValue.GetARGB() != UiColors::Transparent) {
            m_colors.push_back(regularColor);
        }
    }
    std::sort(m_colors.begin(), m_colors.end());
}

Control* ColorPickerRegularProvider::CreateElement()
{
    ListBoxItem* pControl = new ListBoxItem;
    UiRect borderSize(1, 1, 1, 1);
    pControl->SetBorderSize(borderSize);
    pControl->SetBorderColor(kControlStatePushed, L"blue");
    return pControl;
}

bool ColorPickerRegularProvider::FillElement(ui::Control* pControl, size_t nElementIndex)
{
    if ((pControl != nullptr) && (nElementIndex < m_colors.size())) {
        const RegularColor& regularColor = m_colors[nElementIndex];
        pControl->SetBkColor(regularColor.colorValue);
        pControl->SetToolTipText(regularColor.colorName.c_str());
        pControl->SetUserDataID(nElementIndex);
        return true;
    }
    return false;
}

size_t ColorPickerRegularProvider::GetElementCount() const
{
    return m_colors.size();
}

void ColorPickerRegularProvider::SetElementSelected(size_t nElementIndex, bool bSelected)
{
    if (nElementIndex < m_colors.size()) {
        RegularColor& regularColor = m_colors[nElementIndex];
        regularColor.m_bSelected = bSelected;
    }
}

bool ColorPickerRegularProvider::IsElementSelected(size_t nElementIndex) const
{
    if (nElementIndex < m_colors.size()) {
        const RegularColor& regularColor = m_colors[nElementIndex];
        return regularColor.m_bSelected;
    }
    return false;
}

void ColorPickerRegularProvider::GetSelectedElements(std::vector<size_t>& selectedIndexs) const
{
    selectedIndexs.clear();
    size_t nCount = m_colors.size();
    for (size_t nElementIndex = 0; nElementIndex < nCount; ++nElementIndex) {
        const RegularColor& regularColor = m_colors[nElementIndex];
        if (regularColor.m_bSelected) {
            selectedIndexs.push_back(nElementIndex);
        }
    }
}

bool ColorPickerRegularProvider::IsMultiSelect() const
{
    return false;
}

void ColorPickerRegularProvider::SetMultiSelect(bool /*bMultiSelect*/)
{
}

size_t ColorPickerRegularProvider::SelectColor(const UiColor& color)
{
    size_t selectIndex = Box::InvalidIndex;
    for (size_t index = 0; index < m_colors.size(); ++index) {
        RegularColor& regularColor = m_colors[index];
        if (regularColor.colorValue == color) {
            regularColor.m_bSelected = true;
            selectIndex = index;
        }
        else {
            regularColor.m_bSelected = false;
        }
    }
    return selectIndex;
}

UiColor ColorPickerRegularProvider::GetSelectedColor() const
{
    for (const RegularColor& regularColor : m_colors) {
        if (regularColor.m_bSelected) {
            return regularColor.colorValue;
        }
    }
    return UiColor();
}

void ColorPickerRegularProvider::GetDefaultColors(std::vector<std::pair<std::wstring, int32_t>>& uiColors)
{
    uiColors = {
                {L"AliceBlue,����˿��",UiColors::AliceBlue},
                {L"AntiqueWhite,�Ŷ���",UiColors::AntiqueWhite},
                {L"Aqua,ǳ��ɫ",UiColors::Aqua},
                {L"Aquamarine,������ʯɫ",UiColors::Aquamarine},
                {L"Azure,ε��ɫ��",UiColors::Azure},
                {L"Beige,��ɫ",UiColors::Beige},
                {L"Bisque,�ۻ�ɫ",UiColors::Bisque},
                {L"Black,��ɫ",UiColors::Black},
                {L"BlanchedAlmond,����ɫ",UiColors::BlanchedAlmond},
                {L"Blue,��ɫ",UiColors::Blue},
                {L"BlueViolet,��������ɫ",UiColors::BlueViolet},
                {L"Brown,��ɫ����ɫ",UiColors::Brown},
                {L"BurlyWood,ʵľɫ",UiColors::BurlyWood},
                {L"CadetBlue,����ɫ",UiColors::CadetBlue},
                {L"Chartreuse,����ɫ",UiColors::Chartreuse},
                {L"Chocolate,�ɿ���ɫ",UiColors::Chocolate},
                {L"Coral,ɺ��ɫ",UiColors::Coral},
                {L"CornflowerBlue,����ɫ",UiColors::CornflowerBlue},
                {L"Cornsilk,�׳�ɫ",UiColors::Cornsilk},
                {L"Crimson,����ɫ��",UiColors::Crimson},
                {L"Cyan,��ɫ",UiColors::Cyan},
                {L"DarkBlue,����ɫ",UiColors::DarkBlue},
                {L"DarkCyan,����ɫ",UiColors::DarkCyan},
                {L"DarkGoldenrod,���ƻ�",UiColors::DarkGoldenrod},
                {L"DarkGray,���ɫ",UiColors::DarkGray},
                {L"DarkGreen,����ɫ",UiColors::DarkGreen},
                {L"DarkKhaki,������ɫ����ƺ�ɫ",UiColors::DarkKhaki},
                {L"DarkMagenta,��Ʒ��ɫ�������",UiColors::DarkMagenta},
                {L"DarkOliveGreen,�������",UiColors::DarkOliveGreen},
                {L"DarkOrange,���ɫ",UiColors::DarkOrange},
                {L"DarkOrchid,����ɫ",UiColors::DarkOrchid},
                {L"DarkRed,���ɫ",UiColors::DarkRed},
                {L"DarkSalmon,����ɫ",UiColors::DarkSalmon},
                {L"DarkSeaGreen,���ɫ",UiColors::DarkSeaGreen},
                {L"DarkSlateBlue,�����ɫ",UiColors::DarkSlateBlue},
                {L"DarkSlateGray,����ɫ",UiColors::DarkSlateGray},
                {L"DarkTurquoise,����ʯ��ɫ",UiColors::DarkTurquoise},
                {L"DarkViolet,��������ɫ",UiColors::DarkViolet},
                {L"DeepPink,��ۺ�ɫ",UiColors::DeepPink},
                {L"DeepSkyBlue,������ɫ",UiColors::DeepSkyBlue},
                {L"DimGray,����ɫ",UiColors::DimGray},
                {L"DodgerBlue,����ɫ",UiColors::DodgerBlue},
                {L"Firebrick,��שɫ",UiColors::Firebrick},
                {L"FloralWhite,����ɫ",UiColors::FloralWhite},
                {L"ForestGreen,ɭ����",UiColors::ForestGreen},
                {L"Fuchsia,�Ϻ�ɫ",UiColors::Fuchsia},
                {L"Gainsboro,����ɫ",UiColors::Gainsboro},
                {L"GhostWhite,�����ɫ",UiColors::GhostWhite},
                {L"Gold,��ɫ",UiColors::Gold},
                {L"Goldenrod,������ɫ",UiColors::Goldenrod},
                {L"Gray,��ɫ",UiColors::Gray},
                {L"Green,��ɫ",UiColors::Green},
                {L"GreenYellow,����ɫ",UiColors::GreenYellow},
                {L"Honeydew,��ɫ",UiColors::Honeydew},
                {L"HotPink,�ȷۺ�ɫ",UiColors::HotPink},
                {L"IndianRed,ӡ�ڰ���",UiColors::IndianRed},
                {L"Indigo,����ɫ",UiColors::Indigo},
                {L"Ivory,����ɫ",UiColors::Ivory},
                {L"Khaki,�ƺ�ɫ",UiColors::Khaki},
                {L"Lavender,޹�²�ɫ������ɫ",UiColors::Lavender},
                {L"LavenderBlush,���Ϻ�ɫ",UiColors::LavenderBlush},
                {L"LawnGreen,����ɫ",UiColors::LawnGreen},
                {L"LemonChiffon,���ʳ�ɫ",UiColors::LemonChiffon},
                {L"LightBlue,����ɫ",UiColors::LightBlue},
                {L"LightCoral,��ɺ��ɫ",UiColors::LightCoral},
                {L"LightCyan,����ɫ",UiColors::LightCyan},
                {L"LightGoldenrodYellow,���ջ�",UiColors::LightGoldenrodYellow},
                {L"LightGray,ǳ��ɫ",UiColors::LightGray},
                {L"LightGreen,����ɫ",UiColors::LightGreen},
                {L"LightPink,ǳ�ۺ�",UiColors::LightPink},
                {L"LightSalmon,����ɫ",UiColors::LightSalmon},
                {L"LightSeaGreen,ǳ����ɫ",UiColors::LightSeaGreen},
                {L"LightSkyBlue,������ɫ",UiColors::LightSkyBlue},
                {L"LightSlateGray,������",UiColors::LightSlateGray},
                {L"LightSteelBlue,������ɫ",UiColors::LightSteelBlue},
                {L"LightYellow,ǳ��ɫ",UiColors::LightYellow},
                {L"Lime,ʯ��ɫ",UiColors::Lime},
                {L"LimeGreen,�����ɫ",UiColors::LimeGreen},
                {L"Linen,����ɫ",UiColors::Linen},
                {L"Magenta,���ɫ",UiColors::Magenta},
                {L"Maroon,�Ϻ�ɫ",UiColors::Maroon},
                {L"MediumAquamarine,�б���ɫ",UiColors::MediumAquamarine},
                {L"MediumBlue,����ɫ",UiColors::MediumBlue},
                {L"MediumOrchid,��������",UiColors::MediumOrchid},
                {L"MediumPurple,����ɫ",UiColors::MediumPurple},
                {L"MediumSeaGreen,�к�����",UiColors::MediumSeaGreen},
                {L"MediumSlateBlue,�а�����",UiColors::MediumSlateBlue},
                {L"MediumSpringGreen,�д���ɫ",UiColors::MediumSpringGreen},
                {L"MediumTurquoise,���̱�ʯɫ",UiColors::MediumTurquoise},
                {L"MediumVioletRed,��������ɫ",UiColors::MediumVioletRed},
                {L"MidnightBlue,��ҹ��",UiColors::MidnightBlue},
                {L"MintCream,����ɫ",UiColors::MintCream},
                {L"MistyRose,����õ��ɫ",UiColors::MistyRose},
                {L"Moccasin,¹Ƥɫ",UiColors::Moccasin},
                {L"NavajoWhite,���߰�",UiColors::NavajoWhite},
                {L"Navy,������",UiColors::Navy},
                {L"OldLace,ǳ��ɫ",UiColors::OldLace},
                {L"Olive,���ɫ",UiColors::Olive},
                {L"OliveDrab,���̺�ɫ",UiColors::OliveDrab},
                {L"Orange,��ɫ",UiColors::Orange},
                {L"OrangeRed,�Ⱥ�ɫ",UiColors::OrangeRed},
                {L"Orchid,������ɫ",UiColors::Orchid},
                {L"PaleGoldenrod,����ɫ",UiColors::PaleGoldenrod},
                {L"PaleGreen,����ɫ",UiColors::PaleGreen},
                {L"PaleTurquoise,����ɫ",UiColors::PaleTurquoise},
                {L"PaleVioletRed,ǳ��������",UiColors::PaleVioletRed},
                {L"PapayaWhip,��ľɫ",UiColors::PapayaWhip},
                {L"PeachPuff,��ɫ",UiColors::PeachPuff},
                {L"Peru,��³ɫ",UiColors::Peru},
                {L"Pink,�ۺ�ɫ",UiColors::Pink},
                {L"Plum,����ɫ",UiColors::Plum},
                {L"PowderBlue,����ɫ",UiColors::PowderBlue},
                {L"Purple,��ɫ",UiColors::Purple},
                {L"Red,��ɫ",UiColors::Red},
                {L"RosyBrown,õ����ɫ",UiColors::RosyBrown},
                {L"RoyalBlue,�ʼ���ɫ",UiColors::RoyalBlue},
                {L"SaddleBrown,�غ�ɫ",UiColors::SaddleBrown},
                {L"Salmon,����ɫ��������ɫ",UiColors::Salmon},
                {L"SandyBrown,ɳ��ɫ",UiColors::SandyBrown},
                {L"SeaGreen,����ɫ",UiColors::SeaGreen},
                {L"SeaShell,����ɫ",UiColors::SeaShell},
                {L"Sienna,������ɫ",UiColors::Sienna},
                {L"Silver,��ɫ",UiColors::Silver},
                {L"SkyBlue,����ɫ",UiColors::SkyBlue},
                {L"SlateBlue,ʯ����ɫ",UiColors::SlateBlue},
                {L"SlateGray,ʯ���ɫ",UiColors::SlateGray},
                {L"Snow,ѩ��ɫ",UiColors::Snow},
                {L"SpringGreen,����ɫ",UiColors::SpringGreen},
                {L"SteelBlue,����ɫ",UiColors::SteelBlue},
                {L"Tan,�غ�ɫ",UiColors::Tan},
                {L"Teal,��ɫ",UiColors::Teal},
                {L"Thistle,��ɫ����һ����ɫ",UiColors::Thistle},
                {L"Tomato,����ɫ",UiColors::Tomato},
                {L"Transparent,͸����",UiColors::Transparent},
                {L"Turquoise,����ɫ",UiColors::Turquoise},
                {L"Violet,������ɫ",UiColors::Violet},
                {L"Wheat,С��ɫ, ����ɫ",UiColors::Wheat},
                {L"White,��ɫ",UiColors::White},
                {L"WhiteSmoke,����ɫ",UiColors::WhiteSmoke},
                {L"Yellow,��ɫ",UiColors::Yellow},
                {L"YellowGreen,����ɫ",UiColors::YellowGreen}
    };
}

void ColorPickerRegularProvider::GetBasicColors(std::vector<std::pair<std::wstring, int32_t>>& uiColors)
{
    uiColors = {
        {L"õ���",0xFFF08784},
        {L"õ���",0xFFEB3324},
        {L"��ɫ",0xFF774342},
        {L"��ɫ",0xFF8E403A},
        {L"���ɫ",0xFF3A0603},
        {L"����",0xFF9FFCFD},
        {L"����",0xFF73FBFD},
        {L"��ɫ",0xFF3282F6},
        {L"��ɫ",0xFF0023F5},
        {L"����",0xFF00129A},
        {L"����",0xFF16417C},
        {L"����",0xFF000C7B},

        {L"ǳ��ɫ",0xFFFFFE91},
        {L"��ɫ",0xFFFFFD55},
        {L"��ɫ",0xFFF09B59},
        {L"��ɫ",0xFFF08650},
        {L"��ɫ",0xFF784315},
        {L"���ɫ",0xFF817F26},
        {L"ǳ��ɫ",0xFF7E84F7},
        {L"��ɫ",0xFF732BF5},
        {L"��ɫ",0xFF3580BB},
        {L"����",0xFF00023D},
        {L"����ɫ",0xFF58135E},
        {L"����ɫ",0xFF3A083E},

        {L"ǳ��",0xFFA1FB8E},
        {L"��ɫ",0xFFA1FA4F},
        {L"��ɫ",0xFF75F94D},
        {L"ǳ��",0xFF75FA61},
        {L"ǳ��",0xFF75FA8D},
        {L"��ɫ",0xFF818049},
        {L"��ɫ",0xFFEF88BE},
        {L"ǳ��ɫ",0xFFEE8AF8},
        {L"����ɫ",0xFFEA3FF7},
        {L"��ɫ",0xFFEA3680},
        {L"����ɫ",0xFF7F82BB},
        {L"�Ϻ�ɫ",0xFF75163F},

        {L"ǳ��ɫ",0xFF377D22},
        {L"����ɫ",0xFF377E47},
        {L"����ɫ",0xFF367E7F},
        {L"��ɫ",0xFF507F80},
        {L"����ɫ",0xFF183E0C},
        {L"����ɫ",0xFF173F3F},
        {L"����ɫ",0xFF741B7C},
        {L"����ɫ",0xFF39107B},
        {L"��ɫ",0xFF000000},
        {L"��ɫ",0xFF808080},
        {L"ǳ��",0xFFC0C0C0},
        {L"��ɫ",0xFFFFFFFF}
    };
}

}//namespace ui
