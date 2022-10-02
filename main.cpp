#include "constants.h"
#include "TextInterface.h"
#include <cstdlib> // std::exit
#include <exception>
#include <iostream>

void printHelp()
{
	std::cout << "Usage: notes <flag> key note\n";
	std::cout << "Flag\tName\tUsage\n";
	std::cout << "-c\tclear\t-c or -c key\n";
	std::cout << "-d\tdelete\t-d key\n";
	std::cout << "-h\thelp\t-h\n";
	std::cout << "-k\tkeys\t-k\n";
	std::cout << "-p\tprint\t-p or -p key\n";
	std::cout << "-r\trecall\t-r key\n";
	std::cout << "-w\twrite\t-w key note\n";
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
	try
	{
		TextInterface notes{};
		if (argc <= 1)
			fail();
		if (argv[1] == constants::flagClear)
		{
			if (!argv[2])
			{
				if (!notes.clearAll())
					fail("Notes not deleted.");
			}
			else
			{
				if (!notes.clear(argv[2]))
					fail("Notes not deleted.");
			}
		}
		else if (argv[1] == constants::flagDelete)
		{
			if (!argv[2])
				fail("Key cannot be empty.");
			if (!notes.remove(argv[2]))
				fail("Note not deleted.");
		}
		else if (argv[1] == constants::flagHelp)
		{
			printHelp();
		}
		else if (argv[1] == constants::flagPrintKeys)
		{
			notes.printAllKeys();
		}
		else if (argv[1] == constants::flagPrintAll)
		{
			if (!argv[2])
        		notes.printAll();
    	    if (!notes.recall(argv[2]))
   	    		fail("Key does not exist.");
		}
		else if (argv[1] == constants::flagRecall)
		{
			if (!argv[2])
        		fail("Key cannot be empty.");
    	    if (!notes.recall(argv[2]))
   	    		fail("Key does not exist.");
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
				fail("File output failure. Out of memory? Your notes may have been lost!");
				// TODO: this is not an ideal failure.
				// maybe keep the program running and ask user to try again?
				// do this in TextInterface
			}
		}
		else
		{
			fail("Invalid flag.");
		}
		return EXIT_SUCCESS;
	}
	catch (std::runtime_error& ex)
	{
		fail(ex.what());
	}
}
