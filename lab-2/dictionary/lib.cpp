#ifndef LIB_H
#define LIB_H
#include "lib.h"

std::string getUserMessage(void)
{
	std::string message;
	std::cin >> message;

	if (!std::cin)
	{
		throw std::runtime_error("Icorrect stream");
	}
	return message;
}

#endif