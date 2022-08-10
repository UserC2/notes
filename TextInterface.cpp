#include "TextInterface.h"
#include "date.h" // TextInterface::add()
#include "FstreamHandler.h"
#include <algorithm> // std::find
#include <exception>
#include <fstream>
#include <iostream>
#include <limits> // std::numeric_limits
#include <optional>
#include <ostream> // TextInterface::write()
#include <tuple>
#include <string>
#include <string_view>
#include <vector>

TextInterface::TextInterface()
	: m_noteFile{ constants::noteFilename }
{
	m_noteArray.reserve(m_noteFile.maxLines());
	loadNoteArray();
}

bool TextInterface::add(std::string_view key, std::string_view noteString)
{
	std::string time{ date::currentDate() };
	noteType_t note{ time, key, noteString };
	m_noteFile.write();
	if (write(note, m_noteFile.stream()))
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
}

void TextInterface::printAll()
{
	for (noteType_t note : m_noteArray)
	{
		write(note, std::cout);
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
// get note corresponding to key
// if multiple notes, print all
// if no entries, return false
	return false;
// if one note, delete immediately
// if multiple entries, ask which to delete (number 1-amntOfEntries)
//	remove from array, then writeFile();
//	std::cout << "Deleted \"" << noteString << "\" with key \"" << key
//	<< "\" created on " << time << '\n';
//	return true;
}
// return false if key doesn't exist
// if multiple entries, ask which to delete? or ask y/n and delete all?
// print message: "Deleted note: "notetxt"

TextInterface::noteKey_t TextInterface::extractKey()
{
    m_noteFile.stream().ignore(std::numeric_limits<std::streamsize>::max()
		, '\t');
    std::string key;
    if (std::getline(m_noteFile.stream() >> std::ws, key, ':'))
	// ignores second tab
	{
	    m_noteFile.stream().ignore(std::numeric_limits<std::streamsize>::max()
			, '\n');
		// ignores the rest of the note
	   	return key;
	}
	else
	{
		return {}; // no valid key
	}
}

TextInterface::keyArray_t TextInterface::getKeys()
{
	m_noteFile.read();
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

TextInterface::noteType_t TextInterface::getNote()
{
    m_noteFile.stream().ignore(std::numeric_limits<std::streamsize>::max()
		, '(');
	std::string date;
	if (!std::getline(m_noteFile.stream() >> std::ws, date, ')'))
		throw std::runtime_error("Failed to extract date from note.");
	std::string key;
	if (!std::getline(m_noteFile.stream() >> std::ws, key, ':'))
		throw std::runtime_error("Failed to extract key from note.");
	std::string note;
	if (!std::getline(m_noteFile.stream() >> std::ws, note, '\n'))
		throw std::runtime_error("Failed to extract note string from note.");
	return { date, key, note };
}

void TextInterface::loadNoteArray()
{
	m_noteFile.stream().seekg(0, std::ios::beg);
	while (!m_noteFile.stream().eof())
	{
		try
		{
			m_noteArray.push_back(getNote());
		}
		catch (const std::runtime_error& ex)
		{
			continue;
			/* Since the invalid note is never loaded into the array, it is
			* deleted when the program is run! This eliminates errors in the
			*  text file. */
		}
	}
	m_noteFile.stream().seekg(0, std::ios::beg);
}

bool TextInterface::write(const noteType_t& note, std::ostream& out)
{
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

bool TextInterface::writeFile()
{
	for (const noteType_t& note : m_noteArray)
	{
		if (!write(note, m_noteFile.stream()))
			return false;
	}
	return true;
}
