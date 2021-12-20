#include <FrameDelayFilterDialog.h>
#include <sstream>

FrameDelayFilterDialog::FrameDelayFilterDialog(FrameDelayFilterConfig& config, IVDXFilterPreview *ifp):mifp(ifp), mConfigNew(config){
}

bool FrameDelayFilterDialog::Show(HWND parent) {
	return 0 != VDXVideoFilterDialog::Show(NULL, MAKEINTRESOURCE(IDD_DIALOG_FRAME_DELAY_SETTINGS), parent);
};

INT_PTR FrameDelayFilterDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG:
		OnInit();
		return TRUE;

	case WM_COMMAND:
		if (OnCommand(LOWORD(wParam)))
			return TRUE;
		break;
	}

	return FALSE;
}

void FrameDelayFilterDialog::OnInit() {
	mConfigOld = mConfigNew;

	LoadFromConfig();

	// gain focus to first control
	HWND hwndFirst = GetDlgItem(mhdlg, IDC_EDIT_FRAMES);
	if (hwndFirst)
		SendMessage(mhdlg, WM_NEXTDLGCTL, (WPARAM)hwndFirst, TRUE);
}

bool FrameDelayFilterDialog::OnCommand(int cmd) {
	switch (cmd) {
		case ID_DIALOG_BUTTON_OK:
			EndDialog(mhdlg, true);
			return true;

		case ID_DIALOG_BUTTON_CANCEL:
			mConfigNew = mConfigOld;
			EndDialog(mhdlg, false);
			return true;

		case IDC_EDIT_FRAMES:
			SaveToConfig();
			return true;
	}
	return false;
}

void FrameDelayFilterDialog::LoadFromConfig() {
	//{
	//	wchar_t buffer[256];
	//	wsprintfW(buffer, L"%d", 123);
	//	MessageBox(mhdlg, buffer, L"Titel", 0);
	//}

	wchar_t buffer[8];
	wsprintfW(buffer, L"%d", mConfigNew.mNumFrames);
	SendDlgItemMessage(mhdlg, IDC_EDIT_FRAMES, WM_SETTEXT, 0, (LPARAM)buffer);
}

void FrameDelayFilterDialog::SaveToConfig() {
	wchar_t buffer[8];
	size_t len = SendDlgItemMessage(mhdlg, IDC_EDIT_FRAMES, WM_GETTEXT, sizeof(buffer) / sizeof(wchar_t), (LPARAM)buffer);
	long numFrames = wcstol(buffer, nullptr, 10);

	mConfigNew.mNumFrames = (uint8)max(1, min(255, numFrames));
	if (mConfigNew.mNumFrames != numFrames) {
		wsprintfW(buffer, L"%d", mConfigNew.mNumFrames);
		SendDlgItemMessage(mhdlg, IDC_EDIT_FRAMES, WM_SETTEXT, 0, (LPARAM)buffer);
	}
}