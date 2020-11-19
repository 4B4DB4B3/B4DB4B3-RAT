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
#include "Telegram.h"
#include "common.h"

void Telegram::SendTextMessage(const char* chatid, const char* message) {
	std::string path = "bot" + std::string(botapi) + "/sendMessage?text=" + message + "&chat_id=" + chatid;
	Requests::GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());
}

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
OUT OF OR IN CONN
*/

std::string Telegram::GetLastMessageText(int chatid) {
	std::string path = "bot" + std::string(botapi) + "/getUpdates";
	std::string messages = Requests::GetRequest("api.telegram.org", "4B4DB4B3", path.c_str());

	nlohmann::json list_messages = nlohmann::json::parse(messages);
	

	std::string text;
	for (size_t i = 0; i < list_messages["result"].size(); i++) {
		try {
			if (list_messages["result"][i]["message"]["from"]["id"] == chatid) {
				text = list_messages["result"][i]["message"]["text"];
			}
		}
		catch (std::exception) {
			text = "";
			break;
		}
	}
	
	if (text != previous_message) {
		previous_message = text;
		return text;
	}
	else {
		return "";
	}
}