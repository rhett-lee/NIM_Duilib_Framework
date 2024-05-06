#ifndef UI_RENDER_SKIA_PATH_H_
#define UI_RENDER_SKIA_PATH_H_

#pragma once

#include "duilib/Render/IRender.h"

class SkPath;

namespace ui 
{

class UILIB_API Path_Skia : public IPath
{
public:
	Path_Skia();
	Path_Skia(const Path_Skia& r);
	Path_Skia& operator=(const Path_Skia& r) = delete;

	virtual IPath* Clone() override;
	virtual void Reset() override;

	/** �رյ�ǰ��ͼ
	*/
	virtual void Close() override;

	virtual void SetFillType(FillType mode) override;
	virtual FillType GetFillType() override;

	virtual void AddLine(int x1, int y1, int x2, int y2) override;
	virtual void AddLines(const UiPoint* points, int count) override;
	virtual void AddBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
	virtual void AddBeziers(const UiPoint* points, int count) override;
	virtual void AddRect(const UiRect& rect) override;
	virtual void AddEllipse(const UiRect& rect) override;
	virtual void AddArc(const UiRect& rect, float startAngle, float sweepAngle) override;
	virtual void AddPolygon(const UiPoint* points, int count) override;
	virtual void AddPolygon(const UiPointF* points, int count) override;
	virtual void Transform(IMatrix* pMatrix) override;

	virtual UiRect GetBounds(const IPen* pen) override;

public:
	/** ��ȡSkia Path
	*/
	SkPath* GetSkPath() const;

private:
	/** ����������ƶ���ָ���ĵ�(x1,y1)
	*/
	void MoveToPoint(int x1, int y1);

private:
	/** Skia Path
	*/
	std::unique_ptr<SkPath> m_skPath;
};

} // namespace ui

#endif // UI_RENDER_SKIA_PATH_H_
