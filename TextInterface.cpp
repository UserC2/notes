#include "TextInterface.h"
#include "date.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

TextInterface::TextInterface()
	: noteFile{ constants::noteFilename, std::ios::app | std::ios::in }
{
}

bool TextInterface::add(std::string_view key, std::string_view noteString)
{
	noteFile.seekp(0, std::ios::end);
	std::string time{ date::currentDate() };
	std::string tabs{ key.length() < constants::tabSize ? "\t\t" : "\t" };
	std::string line{ '(' + time + ")\t" + static_cast<std::string>(key) + ':'
		+ tabs + static_cast<std::string>(noteString) + '\n' };
	noteFile << line;
	try
	{
		noteFile.flush();
	}
	catch (std::ios_base::failure)
	{
		return false;
	}
	std::cout << "Wrote \"" << noteString << "\" with key \"" << key
	<< "\" on " << time << '\n';
	return true;
}

void TextInterface::printKeys()
{
}

void TextInterface::printAll()
{
	noteFile.seekg(0, std::ios::beg);
	while (true)
	{
		std::string str;
		if (!std::getline(noteFile >> std::ws, str)) break;
		std::cout << str << '\n';
	}
}

bool TextInterface::recall(std::string_view key)
{
	return false;
// if multiple entries, print all
// if no entries, return false
}

bool TextInterface::remove(std::string_view key)
{
	return false;
}
// return false if key doesn't exist
// if multiple entries, ask which to delete? or ask y/n and delete all?
// print message: "Deleted note: "notetxt"
