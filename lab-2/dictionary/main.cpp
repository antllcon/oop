#include "dictionary.h"

// Программа-словарь, осуществляющая перевод слов и словосочетаний,
// поступающих со стандартного потока ввода, с английского языка на русский
// с использованием заданного файла словаря и выводящая результат перевода в
// стандартный поток вывода.
int main(int argc, char* argv[])
{
	std::locale::global(std::locale("ru_RU.utf8"));
	try
	{
		std::string fileName = GetFileName(argc, argv);
		Dictionary dictionary = GetDictionary(fileName);
		ProcessDialog(dictionary, fileName);
	}
	catch (const std::exception& errorMessage)
	{
		std::cerr << errorMessage.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}