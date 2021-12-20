#include <FrameCacheFilterDialog.h>
#include <sstream>

FrameCacheFilterDialog::FrameCacheFilterDialog(FrameCacheFilterConfig& config, IVDXFilterPreview *ifp) :mifp(ifp), mConfigNew(config) {
}

bool FrameCacheFilterDialog::Show(HWND parent) {
	return 0 != VDXVideoFilterDialog::Show(NULL, MAKEINTRESOURCE(IDD_DIALOG_FRAME_CACHE_SETTINGS), parent);
};

INT_PTR FrameCacheFilterDialog::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) {
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

void FrameCacheFilterDialog::OnInit() {
	mConfigOld = mConfigNew;

	const wchar_t *operations[] = { L"Load", L"Save" };
	for (int i = 0; i < 2; ++i) SendDlgItemMessage(mhdlg, IDC_COMBO_MODE, CB_ADDSTRING, 0, (LPARAM)operations[i]);

	LoadFromConfig();

	// gain focus to first control
	HWND hwndFirst = GetDlgItem(mhdlg, IDC_COMBO_MODE);
	if (hwndFirst)
		SendMessage(mhdlg, WM_NEXTDLGCTL, (WPARAM)hwndFirst, TRUE);
}

bool FrameCacheFilterDialog::OnCommand(int cmd) {
	switch (cmd) {
	case ID_DIALOG_BUTTON_OK:
		EndDialog(mhdlg, true);
		return true;

	case ID_DIALOG_BUTTON_CANCEL:
		mConfigNew = mConfigOld;
		EndDialog(mhdlg, false);
		return true;

	case IDC_COMBO_MODE:
		SaveToConfig();
		return true;
	}
	return false;
}

void FrameCacheFilterDialog::LoadFromConfig() {
	//wchar_t buffer[256];
	//wsprintfW(buffer, L"%d", (int)mConfigNew.mMode);
	//MessageBox(mhdlg, buffer, L"Titel", 0);

	SendDlgItemMessage(mhdlg, IDC_COMBO_MODE, CB_SETCURSEL, (int)mConfigNew.mMode, 0);
}

void FrameCacheFilterDialog::SaveToConfig() {
	mConfigNew.mMode = (FrameCacheFilterConfig::Mode) SendDlgItemMessage(mhdlg, IDC_COMBO_MODE, CB_GETCURSEL, 0, 0);
}