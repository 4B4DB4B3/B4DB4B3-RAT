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

#include "ScreenTool.h"

bool GDIScreen(std::string path) {
	IStream* istream;
	HRESULT res = CreateStreamOnHGlobal(NULL, true, &istream);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::Status status;
	ULONG_PTR gdiplusToken;

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	{
		HDC scrdc, memdc;
		HBITMAP membit;
		scrdc = ::GetDC(0);
		int Height = GetSystemMetrics(SM_CYSCREEN);
		int Width = GetSystemMetrics(SM_CXSCREEN);
		memdc = CreateCompatibleDC(scrdc);
		membit = CreateCompatibleBitmap(scrdc, Width, Height);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, membit);
		BitBlt(memdc, 0, 0, Width, Height, scrdc, 0, 0, SRCCOPY);

		Gdiplus::Bitmap bitmap(membit, NULL);
		CLSID clsid;
		GetEncoderClsid(L"image/jpeg", &clsid);
		
		std::wstring wsPath(path.begin(), path.end());
		status = bitmap.Save(wsPath.c_str(), &clsid, NULL);
		
		// Create a bitmap from the stream and save it to make sure the stream has the image
//		Gdiplus::Bitmap bmp(istream, NULL);
//		bmp.Save(L"t1est.jpeg", &clsid, NULL);             
		// END

		delete& clsid;
		DeleteObject(memdc);
		DeleteObject(membit);
		::ReleaseDC(0, scrdc);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return status == Gdiplus::Status::Ok ? true : false;
}

int GetEncoderClsid(const WCHAR* format, CLSID* clsID) {
	using namespace Gdiplus;
	UINT  num = 0;
	UINT  size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*clsID = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return 0;
}