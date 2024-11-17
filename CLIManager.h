#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "ApiManager.h"
#include <cctype>

class CLIManager {
public:
	void run() {
		int choise;
		std::string choise1;
		while (true) {
			std::cout << "1 - Search author by name\n2 - Search author by key\n3 - Search book by name\nElse - Exit\n";
			std::cin >> choise;
			if (choise == 1) {
				std::cout << "Enter the name of author: "; 
				std::cin.ignore();
				std::string author;
				std::getline(std::cin, author);
				get_author_by_name(author);
			}
			else if (choise == 2) {
				std::cout << "Enter the key of author: ";
				std::cin >> choise1;
				get_author_by_key(choise1);
			}
			else if (choise == 3) {
				std::cin.ignore();
				std::string bookTitle;
				std::getline(std::cin, bookTitle);
				get_book_by_title(bookTitle);
			}
			else {
				break;
			}
		}
	}
	void get_author_by_name(std::string request) {
		for (int i = 0;i < int(authors["numFound"]);i++) {
			if (authors["docs"][i]["name"] == request) {
				std::cout << "Name: " << authors["docs"][i]["name"] << std::endl
					<< "Key: " << authors["docs"][i]["key"] << std::endl
					<< "Birth date: " << authors["docs"][i]["birth_date"] << std::endl
					<< "Deth date: " << authors["docs"][i]["deth_date"] << std::endl
					<< "Work count: " << authors["docs"][i]["work_count"] << std::endl
					<< "Rating average: " << authors["docs"][i]["ratings_average"] << std::endl;
			}
		}
	}

	void get_author_by_key(std::string request) {
		for (int i = 0;i < int(authors["numFound"]);i++) {
			if (authors["docs"][i]["key"] == request) {
				std::cout << "Name: " << authors["docs"][i]["name"] << std::endl
					<< "Key: " << authors["docs"][i]["key"] << std::endl
					<< "Birth date: " << authors["docs"][i]["birth_date"] << std::endl
					<< "Deth date: " << authors["docs"][i]["deth_date"] << std::endl
					<< "Work count: " << authors["docs"][i]["work_count"] << std::endl
					<< "Rating average: " << authors["docs"][i]["ratings_average"] << std::endl;
			}
		}
	}

	void get_book_by_title(std::string request) {
		std::string request1 = request;
		request1 = toLower(request1);
		for (int i = 0; i < request1.length(); i++) {
			if (request1[i] == ' ') {
				request1[i] = '+';
			}
		}
		nlohmann::json books = a_manager->get_response("https://openlibrary.org/search.json?title=" + request1);
		for (int i = 0;i < int(books["numFound"]);i++) {
			if (books["docs"][i]["title"] == request) {
				std::cout << "Title: " << books["docs"][i]["title"] << std::endl
					<< "Authors: " << books["docs"][i]["author_name"] << std::endl
					<< "Authors keys: " << books["docs"][i]["author_key"] << std::endl;
			}
		}
	}

	std::string toLower(std::string str) {
		std::string lower_str;
		lower_str.reserve(str.size());

		for (char c : str) {
			lower_str += std::tolower(static_cast<unsigned char>(c));
		}

		return lower_str;
	}
private:
	std::shared_ptr<ApiManager> a_manager = std::make_shared<ApiManager>();

	nlohmann::json authors = a_manager->get_response("https://openlibrary.org/search/authors.json?q=twain");
};