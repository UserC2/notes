#include "constants.h"
#include "TextInterface.h"
#include <cstdlib> // std::exit
#include <iostream>

void printHelp()
{
	std::cout << "Usage: notes <flag> key note_string\n";
	std::cout << "Flags:\n-d\tdelete\n-h\thelp\n-k\tkeys\n-p\tprint\n-w\twrite\n";
}

void fail()
{
	printHelp();
	std::exit(EXIT_FAILURE);
}

void fail(std::string_view message)
{
	std::cout << message << '\n';
	std::exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
	TextInterface notes{};
	if (!notes.status())
		fail("Notes file not found or inaccessable.");
	if (argc <= 1)
		fail();
	if (argv[1] == constants::flagDelete)
	{
		if (!argv[2])
			fail("Key cannot be empty.");
		if (!notes.remove(argv[2]))
			fail("Key does not exist.");
	}
	else if (argv[1] == constants::flagHelp)
	{
		printHelp();
	}
	else if (argv[1] == constants::flagPrintKeys)
	{
		notes.printKeys();
	}
	else if (argv[1] == constants::flagPrintAll)
	{
		notes.printAll();
	}
	else if (argv[1] == constants::flagWrite)
	{
		if (!argv[2])
			fail("Key cannot be empty.");
		else if (!argv[3])
			fail("Note cannot be empty.");
		else if (std::strlen(argv[2]) > constants::maxKeySize)
			fail("Key too long.");
		if (!notes.add(argv[2], argv[3]))
		{
			fail("Out of memory.");
		}
	}
	else
	{
		fail("Invalid flag.");
	}
	return EXIT_SUCCESS;
}
