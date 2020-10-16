/*
* github.com/4B4DB4B3
			4B4DB4B3 (c)
					15.10.2020
*/

#include "Telegram.h"

void Telegram::SendTextMessage(const char* chatid, const char* message) {
	std::string path = "bot" + std::string(botapi) + "/sendMessage?text=" + message + "&chat_id=" + chatid;
	GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());
}

/*
* github.com/4B4DB4B3
			4B4DB4B3 (c)
					15.10.2020
*/
std::string Telegram::GetLastMessageText(int chatid) {
	std::string path = "bot" + std::string(botapi) + "/getUpdates";
	std::string messages = GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());

	nlohmann::json list_messages = nlohmann::json::parse(messages);
	
	std::string text;
	for (int i = 0; i < list_messages["result"].size(); i++) {
		try {
			if (list_messages["result"][i]["message"]["from"]["id"] == chatid) {
				text = list_messages["result"][i]["message"]["text"];
			}
		}
		catch (std::exception& e) {
			text = "";
			break;
		}
	}
	
	if (text != before_message) {
		before_message = text;
		return text;
	}
	else {
		return "";
	}
}