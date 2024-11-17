#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<nlohmann/json.hpp>
#include <cpr/cpr.h>

class ApiManager {
public:
	nlohmann::json get_response(std::string request) {
		try {
			response = cpr::Get(cpr::Url{ request });
			if (response.status_code == 200) {
				json_response = nlohmann::json::parse(response.text);
				return json_response;
			}
			else {
				std::cout << response.error.message << std::endl;
				return nullptr;
			}
		}
		catch (const std::exception ex) {
			std::cout << ex.what() << std::endl;
		}
	}
private:
	nlohmann::json json_response;

	cpr::Response response;
};