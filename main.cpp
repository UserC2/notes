#include "constants.h"
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
	if (argc <= 1)
		fail();
	if (argv[1] == constants::flag_delete)
	{
		if (!argv[2])
			fail("Key cannot be empty.");
		// delete it (check if it exists and fail if it doesn't)
		// print message: "Deleted note: "notetxt"
	}
	else if (argv[1] == constants::flag_help)
	{
		printHelp();
	}
	else if (argv[1] == constants::flag_printkeys)
	{
		// print all keys
	}
	else if (argv[1] == constants::flag_printall)
	{
		// print all lines of txt file. format will already be correct
	}
	else if (argv[1] == constants::flag_write)
	{
		if (!argv[2])
			fail("Key cannot be empty.");
		else if (!argv[3])
			fail("Note cannot be empty.");
		// add line to txt file:
		// date: dd/mm/yyyy
		// (Date)\tkey:<tabs>note
		// tabs calculation: if (str.length() < 8) tabs == 2
		// if (str.length < 16) tabs = 1
		// else fail("Key too long.")
	}
	else
	{
		fail("Invalid flag.");
	}
	return EXIT_SUCCESS;
}
