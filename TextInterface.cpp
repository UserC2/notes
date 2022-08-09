#include "TextInterface.h"
#include "date.h"
#include <algorithm> // std::find
#include <fstream>
#include <iostream>
#include <limits> // std::numeric_limits
#include <optional>
#include <ostream>
#include <tuple>
#include <string>
#include <string_view>
#include <vector>

TextInterface::TextInterface()
	: noteFile{ constants::noteFilename, std::ios::app | std::ios::in }
{
}

bool TextInterface::add(std::string_view key, std::string_view noteString)
{
	std::string time{ date::currentDate() };
	noteType_t note{ time, key, noteString };
	noteFile.seekp(0, std::ios::end);
	if (write(note, noteFile))
	{
		std::cout << "Wrote \"" << noteString << "\" with key \"" << key
		<< "\" on " << time << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

void TextInterface::printKeys()
{
	//keyArray_t keys{ getKeys() };
	//for (std::string_view e : keys)
	//{
	//	std::cout << e << '\n';
	//}
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
// get note corresponding to key
// if multiple entries, print all
// if no entries, return false
	return false;
}

bool TextInterface::remove(std::string_view key)
{
// get note corresponding to ey
// if multiple notes, print all
// if no entries, return false
	return false;
// if one note, delete immediately
// if multiple entries, ask which to delete (number 1-amntOfEntries)
// print message: "Deleted note:"
//	std::cout << "Deleted \"" << noteString << "\" with key \"" << key
//	<< "\" created on " << time << '\n';
//	return true;
}
// return false if key doesn't exist
// if multiple entries, ask which to delete? or ask y/n and delete all?
// print message: "Deleted note: "notetxt"

TextInterface::noteKey_t TextInterface::extractKey()
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
		return {}; // no valid key
	}
}

TextInterface::keyArray_t TextInterface::getKeys()
{
	noteFile.seekg(0, std::ios::beg);
	keyArray_t keys;
	while (true)
	{
		keys.push_back(extractKey());
		if (!keys.back()) // doesn't contain a string
		{
			keys.pop_back();
			break; // we've reached EOF
		}
	}
	return keys;
}
/*
TextInterface::noteKey_t TextInterface::findKey(std::string key)
{
	keyArray_t keys{ getKeys() };
	noteKey_t found{ std::find(keys.begin(), keys.end(), key) };
	if (found == keys.end())
		return std::nullopt_t{}
	else
		return found;
}
*/

bool TextInterface::write(const noteType_t& note, std::ostream& out)
{
	//noteFile.seekp(0, std::ios::end);
	const auto&[time, key, noteString]{ note };
    std::string tabs{ key.length() < constants::tabSize ? "\t\t" : "\t" };
    std::string line{ '(' + time + ")\t" + key + ':' + tabs + noteString
		+ '\n' };
    out << line;
    try
    {
        out.flush();
    }
    catch (std::ios_base::failure)
    {
        return false;
    }
    return true;
}
