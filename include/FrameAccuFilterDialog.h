#include <windows.h>
#include <commctrl.h>
#include <resource.h>
#include <vd2/VDXFrame/VideoFilterDialog.h>
#include <vd2/VDXFrame/VideoFilter.h>
#include <FrameAccuFilterConfig.h>

#ifndef FILTER_VD_FRAME_ACCU_DIALOG
#define FILTER_VD_FRAME_ACCU_DIALOG

class FrameAccuFilterDialog : public VDXVideoFilterDialog {
public:
	FrameAccuFilterDialog(FrameAccuFilterConfig& config, IVDXFilterPreview *ifp);
	bool Show(HWND parent);
	virtual INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	IVDXFilterPreview *const mifp;

	void OnInit();
	bool OnCommand(int cmd);

	void LoadFromConfig();
	void SaveToConfig();

	FrameAccuFilterConfig& mConfigNew;
	FrameAccuFilterConfig mConfigOld;
};

#endif 