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

#include "PrntSc.h"

// Copyright (c) 2020 4B4DB4B3
std::string PrntSc::UploadImage(const char* useragent, const char* file) {
    const char* headers = "Content-Type: multipart/form-data; boundary=----B4DB4B3";

    std::string data = "------B4DB4B3\r\n"
        "Content-Disposition: form-data; name=\"image\"; filename=\"" + std::string(file) + "\"\r\n"
        "Content-Type: application/octet-stream\r\n"
        "Content-Transfer-Encoding: binary\r\n\r\n";

    const char* dataEnd = "\r\n------B4DB4B3--\r\n";

    char header[512] = { 0 };

    HINTERNET hSession, hConnect, hRequest;
    DWORD     dwFileSize, dwBytesRead, dwContentLength;

    hSession = InternetOpenA(useragent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

    if (hSession) {
        hConnect = InternetConnectA(hSession, "prntscr.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

        if (hConnect) {
            hRequest = HttpOpenRequestA(hConnect, "POST", "upload.php", NULL, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_SECURE, 1);

            if (hRequest) {
                HANDLE hFile = CreateFile(file, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

                if (hFile != INVALID_HANDLE_VALUE) {
                    dwFileSize = GetFileSize(hFile, NULL);

                    wsprintf(header, data.c_str());

                    dwContentLength = lstrlen(header) + dwFileSize + lstrlen(dataEnd);
                    LPBYTE pBuf = (LPBYTE)malloc(dwContentLength);
                    
                    CopyMemory(&pBuf[0], header, lstrlen(header));

                    ReadFile(hFile, &pBuf[lstrlen(header)], dwFileSize, &dwBytesRead, NULL);

                    CopyMemory(&pBuf[lstrlen(header) + dwFileSize], dataEnd, lstrlen(dataEnd));
                    
                    HttpSendRequest(hRequest, headers, lstrlen(headers), pBuf, dwContentLength);
                    CloseHandle(hFile);
                    free(pBuf);

                    std::string resultRss;
                    BYTE _DATA_RECIEVED[1024];
                    DWORD NO_BYTES_READ = 0;
                    while (InternetReadFile(hRequest, _DATA_RECIEVED, 1024, &NO_BYTES_READ) && NO_BYTES_READ > 0) {
                        resultRss.append((char*)_DATA_RECIEVED, NO_BYTES_READ);
                    }

                    std::string url;
                    nlohmann::json resultParse;
                    try {
                        resultParse = nlohmann::json::parse(resultRss);
                        url = resultParse["data"];
                    }
                    catch (std::exception) {
                        url = "";
                    }

                    return url;
                }
            }

            InternetCloseHandle(hRequest);
        }

        InternetCloseHandle(hConnect);
    }

    InternetCloseHandle(hSession);

    return "";
}