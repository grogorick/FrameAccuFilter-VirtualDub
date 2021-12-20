#include <FrameAccuFilterDialog.h>
#include <sstream>

FrameAccuFilterDialog::FrameAccuFilterDialog(FrameAccuFilterConfig& config, IVDXFilterPreview *ifp):mifp(ifp), mConfigNew(config){
}

bool FrameAccuFilterDialog::Show(HWND parent) {
	return 0 != VDXVideoFilterDialog::Show(NULL, MAKEINTRESOURCE(IDD_DIALOG_FRAME_ACCU_SETTINGS), parent);
};

INT_PTR FrameAccuFilterDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) {
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

void FrameAccuFilterDialog::OnInit() {
	mConfigOld = mConfigNew;

	const wchar_t *operations[] = { L"Max", L"Add", L"Multiply" };
	for (int i = 0; i < 3; ++i) SendDlgItemMessage(mhdlg, IDC_COMBO_OPERATION, CB_ADDSTRING, 0, (LPARAM)operations[i]);

	LoadFromConfig();

	// gain focus to first control
	HWND hwndFirst = GetDlgItem(mhdlg, IDC_COMBO_OPERATION);
	if (hwndFirst)
		SendMessage(mhdlg, WM_NEXTDLGCTL, (WPARAM)hwndFirst, TRUE);
}

bool FrameAccuFilterDialog::OnCommand(int cmd) {
	switch (cmd) {
		case ID_DIALOG_BUTTON_OK:
			EndDialog(mhdlg, true);
			return true;

		case ID_DIALOG_BUTTON_CANCEL:
			mConfigNew = mConfigOld;
			EndDialog(mhdlg, false);
			return true;

		case IDC_COMBO_OPERATION:
			SaveToConfig();
			return true;
	}
	return false;
}

void FrameAccuFilterDialog::LoadFromConfig() {
	//wchar_t buffer[256];
	//wsprintfW(buffer, L"%d", (int)mConfigNew.mOperation);
	//MessageBox(mhdlg, buffer, L"Titel", 0);

	SendDlgItemMessage(mhdlg, IDC_COMBO_OPERATION, CB_SETCURSEL, (int) mConfigNew.mOperation, 0);
}

void FrameAccuFilterDialog::SaveToConfig() {
	mConfigNew.mOperation = (FrameAccuFilterConfig::Operation) SendDlgItemMessage(mhdlg, IDC_COMBO_OPERATION, CB_GETCURSEL, 0, 0);
}