#include "multi_browser_manager.h"
#include "multi_browser_form.h"
#include "browser_box.h"
#include "dragdrop/drag_form.h"
#include "dragdrop/drag_drop.h"

namespace
{
	const int kSplitFormXOffset = 20;	//�Զ������������ں��´��ڵ�xƫ������
	const int kSplitFormYOffset = 20;	//�Զ������������ں��´��ڵ�yƫ������
	const int kDragFormXOffset = -100;	//��ק������������ں���������xƫ������
	const int kDragFormYOffset = -20;	//��ק������������ں���������yƫ������
}

BrowserBox* MultiBrowserManager::CreateBorwserBox(MultiBrowserForm *browser_form, const std::string &id, const std::wstring &url)
{
	BrowserBox *browser_box = NULL;
	// ��������˴��ںϲ����ܣ��Ͱ�����������Ӷ����д�����ĳһ�������������
	// ����ÿ����������Ӷ�����һ�����������
	if (enable_merge_) {
		if (!browser_form) {
			browser_form = new MultiBrowserForm;
			if (!browser_form->CreateWnd(NULL, L"MultiBrowser", UI_WNDSTYLE_FRAME, 0)) {
				browser_form = nullptr;
				return nullptr;
			}
			browser_form->CenterWindow();
		}
		browser_box = browser_form->CreateBox(id, url);
		if (nullptr == browser_box) {
			return nullptr;
		}
	}
	else {
		browser_form = new MultiBrowserForm;
		if (!browser_form->CreateWnd(NULL, L"MultiBrowser", UI_WNDSTYLE_FRAME, 0)) {
			return nullptr;
		}
		browser_box = browser_form->CreateBox(id, url);
		if (nullptr == browser_box) {
			return nullptr;
		}
		browser_form->CenterWindow();
	}

	box_map_[id] = browser_box;
	return browser_box;
}

MultiBrowserManager::MultiBrowserManager()
{
	enable_merge_ = true;
	use_custom_drag_image_ = true;
}

MultiBrowserManager::~MultiBrowserManager()
{

}

bool MultiBrowserManager::IsBorwserBoxActive(const std::string& id)
{
	BrowserBox *browser_box = FindBorwserBox(id);
	if (NULL != browser_box)
	{
		MultiBrowserForm *parent_form = browser_box->GetBrowserForm();
		return parent_form->IsActiveBox(browser_box);
	}

	return false;
}

BrowserBox* MultiBrowserManager::FindBorwserBox( const std::string &id )
{
	std::map<std::string, BrowserBox*>::const_iterator i = box_map_.find(id);
	if (i == box_map_.end())
		return NULL;
	else
		return i->second;
}

void MultiBrowserManager::RemoveBorwserBox( std::string id, const BrowserBox* box /*=NULL*/)
{
	auto it_box = box_map_.find(id);
	if (it_box == box_map_.end())
	{
		assert(0);
	}
	else
	{
		if (NULL == box || box == it_box->second)
		{
			box_map_.erase(it_box);
		}
		else
		{
			assert(0);
		}
	}

	if (box_map_.empty())
		nim_comp::CefManager::GetInstance()->PostQuitMessage(0);
}

void MultiBrowserManager::SetEnableMerge(bool enable)
{
	if (enable_merge_ == enable)
		return;

	enable_merge_ = enable;

	if (enable_merge_)
	{
		// �����ǰֻ��һ����������ڻ�����������ӣ��Ͳ���Ҫ���кϲ�����
		if (box_map_.size() <= 1)
			return;

		// ѡ���һ����������������Ĵ�����Ϊ�ϲ�����
		MultiBrowserForm *merge_form = box_map_.begin()->second->GetBrowserForm();

		// ����������������ӣ�����ԭ��������ڣ��ٸ��ӵ��ϲ�������
		for (auto it_box : box_map_)
		{
			ASSERT(NULL != it_box.second);
			MultiBrowserForm *parent_form = it_box.second->GetBrowserForm();
			if (merge_form != parent_form)
			{
				if (parent_form->DetachBox(it_box.second))
				{
					merge_form->AttachBox(it_box.second);
				}
			}
		}
	}
	else
	{
		// �����ǰֻ��һ����������ӣ��Ͳ���Ҫ���в�ֲ���
		if (box_map_.size() <= 1)
			return;

		// ���²�ֵĴ�����������
		bool first_sort = true;
		ui::UiRect rect_old_form;
		MultiBrowserForm *sort_form = NULL;

		// ����������������ӣ�����ԭ��������ڣ������µ���������ڲ��������������
		for (auto it_box : box_map_)
		{
			ASSERT(NULL != it_box.second);
			MultiBrowserForm *parent_form = it_box.second->GetBrowserForm();
			if (1 == parent_form->GetBoxCount())
			{
				sort_form = parent_form;
			}
			else if (parent_form->DetachBox(it_box.second))
			{
				MultiBrowserForm *browser_form = new MultiBrowserForm;
				if (!browser_form->CreateWnd(NULL, L"MultiBrowser", UI_WNDSTYLE_FRAME, 0)) {
					ASSERT(0);
					continue;
				}
				if (!browser_form->AttachBox(it_box.second)) {
					ASSERT(0);
					continue;
				}
				sort_form = browser_form;
			}

			if (NULL != sort_form)
			{
				if (first_sort)
				{
					first_sort = false;
					sort_form->CenterWindow();
					rect_old_form = sort_form->GetWindowPos(true);
				}
				else
				{
					rect_old_form.left += kSplitFormXOffset;
					rect_old_form.top += kSplitFormXOffset;
					sort_form->SetWindowPos(rect_old_form, true, SWP_NOSIZE, NULL, true);
				}
			}
		}
	}
}

bool MultiBrowserManager::IsEnableMerge() const
{
	return enable_merge_;
}

void MultiBrowserManager::SetUseCustomDragImage(bool use)
{
	use_custom_drag_image_ = use;
}

bool MultiBrowserManager::IsUseCustomDragImage() const
{
	return use_custom_drag_image_;
}

bool MultiBrowserManager::IsDragingBorwserBox() const
{
	return enable_merge_ && NULL != draging_box_;
}

void MultiBrowserManager::SetDropForm(MultiBrowserForm *browser_form)
{
	if (NULL == browser_form)
		return;

	drop_browser_form_ = browser_form;
}

bool MultiBrowserManager::DoDragBorwserBox(BrowserBox *browser_box, HBITMAP bitmap, POINT pt_offset)
{
	if (!enable_merge_)
		return false;

	SdkDropSource* drop_src = new SdkDropSource;
	if (drop_src == NULL)
		return false;

	SdkDataObject* data_object = CreateDragDataObject(bitmap, pt_offset);
	if (data_object == NULL)
		return false;

	// ����ʲôʱ������קʱ�����ʾΪ��ͷ
	drop_src->SetFeedbackCursor(::LoadCursor(NULL, IDC_ARROW));

	OnBeforeDragBorwserBox(browser_box, bitmap, pt_offset);

	// �˺���������ֱ����ק���
	DWORD dwEffect;
	HRESULT hr = ::DoDragDrop(data_object, drop_src, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);

	OnAfterDragBorwserBox();

	// ����λͼ
	DeleteObject(bitmap);
	drop_src->Release();
	data_object->Release();
	return true;
}

SdkDataObject* MultiBrowserManager::CreateDragDataObject(HBITMAP bitmap, POINT pt_offset)
{
	SdkDataObject* data_object = new SdkDataObject;
	if (data_object == NULL)
		return NULL;

	if (use_custom_drag_image_)
	{
		FORMATETC fmtetc = { 0 };
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.cfFormat = CF_HDROP;
		fmtetc.tymed = TYMED_NULL;

		STGMEDIUM medium = { 0 };
		medium.tymed = TYMED_NULL;
		data_object->SetData(&fmtetc, &medium, FALSE);
	}
	else
	{
		FORMATETC fmtetc = { 0 };
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.cfFormat = CF_BITMAP;
		fmtetc.tymed = TYMED_GDI;

		STGMEDIUM medium = { 0 };
		medium.tymed = TYMED_GDI;
		HBITMAP hBitmap = (HBITMAP)OleDuplicateData(bitmap, fmtetc.cfFormat, NULL);
		medium.hBitmap = hBitmap;
		data_object->SetData(&fmtetc, &medium, FALSE);

		BITMAP bitmap_info;
		GetObject(hBitmap, sizeof(BITMAP), &bitmap_info);
		SIZE bitmap_size = { bitmap_info.bmWidth, bitmap_info.bmHeight };
		SdkDragSourceHelper dragSrcHelper;
		dragSrcHelper.InitializeFromBitmap(hBitmap, pt_offset, bitmap_size, data_object, RGB(255, 0, 255));
	}

	return data_object;
}

void MultiBrowserManager::OnBeforeDragBorwserBox(BrowserBox *browser_box, HBITMAP bitmap, POINT pt_offset)
{
	// ��ȡ��ǰ����ק��������������������������
	draging_box_ = browser_box;
	MultiBrowserForm *drag_browser_form = draging_box_->GetBrowserForm();
	ASSERT(NULL != drag_browser_form);

	// ��ȡ����ק�������������������ӵ�����
	int box_count = drag_browser_form->GetBoxCount();
	ASSERT(box_count > 0);
	drop_browser_form_ = NULL;

	drag_browser_form->OnBeforeDragBoxCallback(nbase::UTF8ToUTF16(draging_box_->GetId()));

	if (use_custom_drag_image_)
		DragForm::CreateCustomDragImage(bitmap, pt_offset);
}

void MultiBrowserManager::OnAfterDragBorwserBox()
{
	if (use_custom_drag_image_)
		DragForm::CloseCustomDragImage();

	if (NULL == draging_box_)
		return;

	// ��ȡ��ǰ����ק��������������������������
	MultiBrowserForm *drag_browser_form = draging_box_->GetBrowserForm();
	ASSERT(NULL != drag_browser_form);

	// ��ȡ����ק�������������������ӵ�����
	int box_count = drag_browser_form->GetBoxCount();
	ASSERT(box_count > 0);

	// �������ק����������ӷ��뵽һ�������������
	if (NULL != drop_browser_form_)
	{
		if (drag_browser_form == drop_browser_form_)
		{
			drag_browser_form->OnAfterDragBoxCallback(false);
		}
		else
		{
			drag_browser_form->OnAfterDragBoxCallback(true);
			if (drag_browser_form->DetachBox(draging_box_))
			{
				drop_browser_form_->AttachBox(draging_box_);
			}
		}

		// �������ק����������ڰ��������������ӣ���Ͷ��һ��WM_LBUTTONUP��Ϣ������
		// (��Ϊ���ڱ���קʱ������ButtonDown��ButtonMove��Ϣ���������յ�ButtonUp��Ϣ�ᱻ���ԣ����ﲹ��)
		// ���ֻ��һ����������ӣ�������������������������ʱ����������ھͻ�رգ�����ҪͶ��
		if (box_count > 1)
			drag_browser_form->PostMsg(WM_LBUTTONUP, 0, 0);
	}
	// ���û�б���ק����һ�������������
	else
	{
		// �������ק�������������ֻ��һ�����������,����קʧ��
		if (1 == box_count)
		{
			drag_browser_form->OnAfterDragBoxCallback(false);
		}
		// ����ж�����������, �Ͱ��������������ԭ��������ڣ����ӵ��µ���������ڣ���ק�ɹ�
		else
		{
			drag_browser_form->OnAfterDragBoxCallback(true);

			if (drag_browser_form->DetachBox(draging_box_))
			{
				MultiBrowserForm *browser_form = new MultiBrowserForm;
				if (browser_form->CreateWnd(NULL, L"MultiBrowser", UI_WNDSTYLE_FRAME, 0)) {
					if (browser_form->AttachBox(draging_box_)) {
						// ������������������ڵ�λ�ã����õ�ƫ���������100,20��λ��
						POINT pt_mouse;
						::GetCursorPos(&pt_mouse);
						ui::UiRect rect(pt_mouse.x + kDragFormXOffset, pt_mouse.y + kDragFormYOffset, 0, 0);
						browser_form->SetWindowPos(rect, false, SWP_NOSIZE);
					}
				}
			}
		}

		// ���û�б���ק����һ��������������ʱ��������������ڱ��رգ�����ֱ��Ͷ��ButtonUp��Ϣ
		drag_browser_form->PostMsg(WM_LBUTTONUP, 0, 0);
	}

	draging_box_ = NULL;
	drop_browser_form_ = NULL;
}