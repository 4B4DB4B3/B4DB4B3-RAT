/*
4B4DB4B3 (c) 2020
15.10.2020
*/
#include "Requests.h"

std::string GetRequest(const char* url, const char* useragent, const char* path, const char* ContentType) {
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

				return std::string(resultRss);
			}
			InternetCloseHandle(hRequest);
		}
		InternetCloseHandle(hConnection);
	}
	InternetCloseHandle(hSocket);
	return "";
}