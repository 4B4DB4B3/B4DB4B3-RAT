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
#pragma once
#pragma warning(disable : 4996)

#ifndef COMMON_H
#define COMMON_H

#include <Windows.h>

#include <WinInet.h>
#pragma comment(lib, "WinInet.lib")

#include <fstream>
#include <nlohmann/json.hpp>
#include <random>
#include <time.h>

#include <TlHelp32.h>

#include <algorithm>
#include <vector>
#include <sstream>

#include <psapi.h>

#include <gdiplus.h>
#pragma comment(lib, "GdiPlus.lib")

#pragma comment(lib, "Urlmon.lib")

#endif