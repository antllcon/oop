#include "decoder.h"
#include <iostream>

// Программа, выполняющая построчное декодирование html-сущностей текста, поступающих со
// стандартного потока ввода, и выводящих результат в стандартный поток вывода.
int main()
{
	try
	{
		CopyStreamWithHtmlDecode(std::cin, std::cout);
	}
	catch (const std::exception& errorMessage)
	{
		std::cout << errorMessage.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}