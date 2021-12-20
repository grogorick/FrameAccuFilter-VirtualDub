#include <windows.h>
#include <commctrl.h>
#include <resource.h>
#include <vd2/VDXFrame/VideoFilterDialog.h>
#include <vd2/VDXFrame/VideoFilter.h>
#include <FrameCacheFilterConfig.h>

#ifndef FILTER_VD_FRAME_CACHE_DIALOG
#define FILTER_VD_FRAME_CACHE_DIALOG

class FrameCacheFilterDialog : public VDXVideoFilterDialog {
public:
	FrameCacheFilterDialog(FrameCacheFilterConfig& config, IVDXFilterPreview *ifp);
	bool Show(HWND parent);
	virtual INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	IVDXFilterPreview *const mifp;

	void OnInit();
	bool OnCommand(int cmd);

	void LoadFromConfig();
	void SaveToConfig();

	FrameCacheFilterConfig& mConfigNew;
	FrameCacheFilterConfig mConfigOld;
};

#endif 