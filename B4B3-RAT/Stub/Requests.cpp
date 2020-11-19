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

#include "Requests.h"

std::string Requests::GetRequest(const char* url, const char* useragent, const char* path, const char* ContentType) {
	InternetSetOption(0, 42, NULL, 0);

	HINTERNET hSocket = InternetOpenA(useragent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
	
    if (hSocket != NULL) {
		HINTERNET hConnection = InternetConnectA(hSocket, url, INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
		
        if (hConnection != NULL) {
			HINTERNET hRequest;

			if (path == "") {
				hRequest = HttpOpenRequestA(hConnection, "GET", NULL, NULL, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 1);
			}
			else {
				hRequest = HttpOpenRequestA(hConnection, "GET", path, NULL, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 1);
			}

			if (hRequest != NULL) {
				if (ContentType == "") {
					HttpSendRequestA(hRequest, NULL, 0, NULL, 0);
				}
				else {
					HttpSendRequestA(hRequest, ContentType, sizeof(ContentType), NULL, NULL);
				}

				std::string resultRss;
				BYTE _DATA_RECIEVED[1024];
				DWORD NO_BYTES_READ = 0;
				while (InternetReadFile(hRequest, _DATA_RECIEVED, 1024, &NO_BYTES_READ) && NO_BYTES_READ > 0) {
					resultRss.append((char*)_DATA_RECIEVED, NO_BYTES_READ);
				}

				return resultRss;
			}
			InternetCloseHandle(hRequest);
		}
		InternetCloseHandle(hConnection);
	}
	InternetCloseHandle(hSocket);

	return "";
}