#include "TextInterface.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>

TextInterface::TextInterface()
	: noteFile{ constants::noteFilename, std::ios::app | std::ios::out }
{
	noteFile.exceptions(std::ios_base::failbit | std::ios_base::badbit);
}

bool TextInterface::add(std::string_view key, std::string_view noteString)
{
	std::string date{ "dd/mm/yyyy" }; // placeholder
	std::string tabs{ key.length() < constants::tabSize ? "\t\t" : "\t" };
	std::string line{ '(' + date + ")\t" + static_cast<std::string>(key) + ':'
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
	<< "\" on " << date << '\n';
	return true;
}

void TextInterface::printKeys() const
{
}

void TextInterface::printAll() const
{
}

bool TextInterface::remove(std::string_view key)
{
	return false;
}
// return false if key doesn't exist
// print message: "Deleted note: "notetxt"
