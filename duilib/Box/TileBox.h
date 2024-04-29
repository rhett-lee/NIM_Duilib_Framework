#ifndef UI_BOX_TILEBOX_H_
#define UI_BOX_TILEBOX_H_

#pragma once
#include "duilib/Core/Box.h"
#include "duilib/Box/VTileLayout.h"
#include "duilib/Box/HTileLayout.h"

namespace ui
{

/** ��Ƭ���ֵ�Box(���򲼾�)
*/
class UILIB_API VTileBox : public Box
{
public:
	VTileBox() :
		Box(new VTileLayout())
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_VTILE_BOX; }
};

/** ��Ƭ���ֵ�Box(ˮƽ����)
*/
class UILIB_API HTileBox : public Box
{
public:
	HTileBox() :
		Box(new HTileLayout())
	{
	}

	virtual std::wstring GetType() const override { return DUI_CTR_HTILE_BOX; }
};

}
#endif // UI_BOX_TILEBOX_H_
