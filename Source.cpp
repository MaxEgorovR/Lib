#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "ApiManager.h"
#include "CLIManager.h"

//https://openlibrary.org/developers/api

int main() {
	std::shared_ptr<CLIManager> manager = std::make_shared<CLIManager>();
	manager->run();
}