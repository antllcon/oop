#include "HttpUrl.h"
#include <cstdint>
#include <iostream>

int main()
{
	std::string line;
	while (std::getline(std::cin, line))
	{
		try
		{
			HttpUrl url(line);

			std::cout << url << std::endl;
			std::cout << "Protocol: " << url.GetProtocol().ToString() << std::endl;
			std::cout << "Domain: " << url.GetDomain() << std::endl;
			std::cout << "Port: " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument() << std::endl;
		}
		catch (const std::exception& exceptionMessage)
		{
			std::cout << "Error: " << exceptionMessage.what() << std::endl;
		}
	}
}
