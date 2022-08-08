#include "constants.h"
#include "TextInterface.h"
#include <cstdlib>
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
	try
	{
		notes.status();
	}
	catch (const std::runtime_error& ex)
	{
		fail(ex.what());
	}
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
		if (!notes.add(argv[2], argv[3]))
			fail("Key too long.");
	}
	else
	{
		fail("Invalid flag.");
	}
	return EXIT_SUCCESS;
}
