#include <FrameAccuFilterDialog.h>

FrameAccuFilterDialog::FrameAccuFilterDialog(FrameAccuFilterConfig& config, IVDXFilterPreview *ifp):mifp(ifp), mConfigNew(config){
}

bool FrameAccuFilterDialog::Show(HWND parent) {
	return 0 != VDXVideoFilterDialog::Show(NULL, MAKEINTRESOURCE(IDD_DIALOG_FRAME_ACCU_SETTINGS), parent);
};

INT_PTR FrameAccuFilterDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		return !OnInit();

	case WM_DESTROY:
		OnDestroy();
		break;

	case WM_COMMAND:
		if (OnCommand(LOWORD(wParam)))
			return TRUE;
		break;

	case WM_HSCROLL:
		if (mifp && SaveToConfig())
			mifp->RedoFrame();
		return TRUE;
	}

	return FALSE;
}

bool FrameAccuFilterDialog::OnInit() {
	mConfigOld = mConfigNew;
	// init preview button
	HWND hwndPreview = GetDlgItem(mhdlg, ID_DIALOG_BUTTON_PREVIEW);
	if (hwndPreview && mifp) {
		EnableWindow(hwndPreview, TRUE);
		mifp->InitButton((VDXHWND)hwndPreview);
	}
	return false;
}

void FrameAccuFilterDialog::OnDestroy() {
	if (mifp)
		mifp->InitButton(NULL);
}

bool FrameAccuFilterDialog::OnCommand(int cmd) {
	switch (cmd) {
		case ID_DIALOG_BUTTON_OK:
			SaveToConfig();
			EndDialog(mhdlg, true);
			return true;
		case ID_DIALOG_BUTTON_CANCEL:
			mConfigNew = mConfigOld;
			EndDialog(mhdlg, false);
			return true;
		case ID_DIALOG_BUTTON_PREVIEW:
			if (mifp)
				mifp->Toggle((VDXHWND)mhdlg);
			return true;
	}
	return false;
}

void FrameAccuFilterDialog::LoadFromConfig() {
}

bool FrameAccuFilterDialog::SaveToConfig() {
	return false;
}