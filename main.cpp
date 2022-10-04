#include "constants.h"
#include "TextInterface.h"
#include <cstdlib> // std::exit
#include <exception>
#include <iostream>

void printHelp()
{
	std::cout << "Usage: notes <flag> key note\n";
	std::cout << "Flag\tName\tUsage\t\tExplanation\n";
	std::cout << "-c\tclear\t-c\t\tDelete **ALL** notes\n";
	std::cout << "-c\tclear\t-c key\t\tDelete **ALL** notes corresponding to `key`\n";
	std::cout << "-d\tdelete\t-d key\t\tDelete the note(s) corresponding to `key`\n";
	std::cout << "-h\thelp\t-h\t\tDisplay this help prompt\n";
	std::cout << "-k\tkeys\t-k\t\tPrint a list of every key\n";
	std::cout << "-p\tprint\t-p\t\tPrint a list of every key, note, and the date each note was taken\n";
	std::cout << "-p\tprint\t-p key\t\tEquivalent to `-r key`\n";
	std::cout << "-s\tsort\t-s date\t\tSort notes from oldest to newest, and alphabetically when dates are the same\n";
	std::cout << "-s\tsort\t-s key\t\tSort notes alphabetically according to key, and from oldest to newest when keys are the same\n";
	std::cout << "-r\trecall\t-r key\t\tPrint the note(s) corresponding to `key`\n";
	std::cout << "-w\twrite\t-w key note\tAdd a note (`note`) accessible through `key`\n";
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
			else if (!notes.remove(argv[2]))
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
    	    else if (!notes.recall(argv[2]))
   	    		fail("Key does not exist.");
		}
		else if (argv[1] == constants::flagRecall)
		{
			if (!argv[2])
        		fail("Key cannot be empty.");
    	    else if (!notes.recall(argv[2]))
   	    		fail("Key does not exist.");
		}
		else if (argv[1] == constants::flagSort)
		{
			if (!argv[2])
				fail("Invalid flag option.");
			else if (argv[2] == constants::optionSortDate)
			{
				if (!notes.sortByDate())
					fail("Notes not sorted.");
			}
			else if (argv[2] == constants::optionSortKey)
			{
				if (!notes.sortByKey())
					fail("Notes not sorted.");
			}
			else
				fail("Invalid flag option.");
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
