/*
4B4DB4B3 (c) 2020
15.10.2020
*/
#pragma once
#include "Requests.h"

class Telegram
{
private:
	char* botapi;
	std::string before_message = "";
public:
	Telegram(char* api) {
		this->botapi = api;
	}
	void SendTextMessage(const char* chatid, const char* message);
	std::string GetLastMessageText(int chatid);
};

