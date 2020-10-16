/*
4B4DB4B3 (c) 2020
15.10.2020
*/
#include "common.h"
#include "DlgProc.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	return DialogBoxA(hInst, MAKEINTRESOURCEA(IDD_DIALOGBAR), 0, (DLGPROC)DlgMain);
}