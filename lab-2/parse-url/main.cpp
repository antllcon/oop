#include "ParseUrl.h"

#include <iostream>

int main()
{
	std::string url;
	parse_url::UrlData data;

	while (std::getline(std::cin, url))
	{
		if (!parse_url::ParseURL(url, data))
		{
			std::cout << "Error" << std::endl;
			return EXIT_FAILURE;
		}

		auto& [protocol, host, port, document] = data;

		std::cout << url << std::endl;
		std::cout << "Host: " << host << std::endl;
		std::cout << "Port: " << port << std::endl;
		std::cout << "Doc: " << document << std::endl;
	}

	return EXIT_SUCCESS;
}
