#include <windows.h>
#include <commctrl.h>
#include <resource.h>
#include <vd2/VDXFrame/VideoFilterDialog.h>
#include <vd2/VDXFrame/VideoFilter.h>
#include <FrameDelayFilterConfig.h>

#ifndef FILTER_VD_FRAME_DELAY_DIALOG
#define FILTER_VD_FRAME_DELAY_DIALOG

class FrameDelayFilterDialog : public VDXVideoFilterDialog {
public:
	FrameDelayFilterDialog(FrameDelayFilterConfig& config, IVDXFilterPreview *ifp);
	bool Show(HWND parent);
	virtual INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	IVDXFilterPreview *const mifp;

	void OnInit();
	bool OnCommand(int cmd);

	void LoadFromConfig();
	void SaveToConfig();

	FrameDelayFilterConfig& mConfigNew;
	FrameDelayFilterConfig mConfigOld;
};

#endif 