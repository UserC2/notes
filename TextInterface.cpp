#include "TextInterface.h"
#include "date.h"
#include <fstream>
#include <iostream>
#include <limits> // std::numeric_limits
#include <string>
#include <string_view>
#include <vector>

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
	noteFile.seekg(0, std::ios::beg);
	keyArray_t keys{ getKeys() };
	for (std::string_view e : keys)
	{
		std::cout << e << '\n';
	}
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

std::string TextInterface::extractKey()
{
    noteFile.ignore(std::numeric_limits<std::streamsize>::max(), '\t');
    std::string key;
    if (std::getline(noteFile >> std::ws, key, ':')) // ignore second tab
	{
	    noteFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		// ignore the rest of the note
	   	return key;
	}
	else
	{
		return constants::stringExtractionFailed;
	}
}

TextInterface::keyArray_t TextInterface::getKeys()
{
	keyArray_t keys;
	while (true)
	{
		keys.push_back(extractKey());
		if (keys.back() == constants::stringExtractionFailed)
		{
			keys.pop_back();
			break;
		}
	}
	return keys;
}
