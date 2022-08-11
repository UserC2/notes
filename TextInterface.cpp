#include "TextInterface.h"
#include "date.h" // date::currentDate()
#include "FstreamHandler.h"
#include "input.h" // askToContinue()
#include <algorithm> // std::count_if
#include <exception> // std::runtime_exception
#include <fstream>
#include <iostream>
#include <limits> // std::numeric_limits
#include <ostream> // TextInterface::write()
#include <tuple> // std::get()
#include <string>
#include <string_view>
#include <vector> // noteArray_t and indexArray_t

// public functions

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
	m_noteFile.stream().seekp(0, std::ios::end);
	if (write(note, m_noteFile.stream()))
	{
		std::cout << "Wrote \"" << noteString << "\" with key \"" << key
		<< "\" on " << time << ".\n";
		return true;
	}
	else
	{
		return false;
	}
}

void TextInterface::printKeys() const
{
	for (const noteType_t& note : m_noteArray)
	{
		std::cout << std::get<static_cast<size_t>(NoteType::key)>(note)
			<< '\n';
	}
	// make printKeys function similar to printNotes except for keys
	// it should accept same parameters as printNotes?
	// maybe another function to find all unique keys
	// see idea in .notes.txt as well
}

void TextInterface::printAll() const
{
	printNotes(findAllNotes());
}

bool TextInterface::recall(std::string_view key) const
{
	return printNotes(findNotes(key));
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

// private functions

TextInterface::indexArray_t TextInterface::findAllNotes() const
{
	indexArray_t indexArray;
	indexArray.reserve(m_noteArray.size());
	for (std::size_t index{ 0 }; index < m_noteArray.size(); index++)
	{
		indexArray.push_back(index);
	}
	return indexArray;
}

TextInterface::indexArray_t TextInterface::findNotes(std::string_view key) const
{
    auto matchesKey{ [&](const noteType_t& note) -> bool {
        return std::get<static_cast<std::size_t>(NoteType::key)>(note) == key;
    }};
	indexArray_t indexArray;
	indexArray.reserve(std::count_if(std::begin(m_noteArray)
		, std::end(m_noteArray), matchesKey));
	for (std::size_t index{ 0 }; index < m_noteArray.size(); index++)
	{
		if (matchesKey(m_noteArray.at(index)))
			indexArray.push_back(index);
	}
	return indexArray;
}

TextInterface::noteType_t TextInterface::getNote()
{
    m_noteFile.stream().ignore(std::numeric_limits<std::streamsize>::max()
		, '(');
	// TODO: this should extract an entire line into a stringstream
	// after that, operate as normal below:
	// this will prevent errors that should have been caught, such as accepting
	// practically anything as a key so long as it is between () and : (even if
	// it is seperated by several newlines and other garbage).
	// mostly this will eliminate newlines between notes.
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
		m_noteFile.stream().clear();
		/* Reset any flags caused by a failed call to getNote(). This is done
		* at the start of the loop iteration to avoid resetting eofbit. */
		try
		{
			m_noteArray.push_back(getNote());
		}
		catch (const std::runtime_error& ex)
		{
			continue;
			/* Since the invalid note is never loaded into the array, it is
			* deleted when the array is written to disk. This eliminates errors
			* in the text file. */
		}
	}
	m_noteFile.stream().seekg(0, std::ios::beg);
	m_noteFile.stream().clear(); // clear eofbit so file can be used
}

bool TextInterface::printNotes(const indexArray_t& indexArray) const
{
	if (indexArray.size() == 0)
		return false;
	int i{ 0 };
	for (std::size_t index : indexArray)
	{
		if (i == constants::maxPageLength)
		{
			i = 0;
			if (!input::askToContinue(":", "q"))
				break;
		}
		if (!write(m_noteArray.at(index), std::cout))
			return false;
		i++;
	}
	return true;
}

bool TextInterface::write(const noteType_t& note, std::ostream& out) const
{
	const auto&[time, key, noteString]{ note };
	std::string tabs{ key.length() < constants::keyHalfSize ? "\t\t" : "\t" };
	std::string line{ '(' + time + ")\t" + key + ':' + tabs + noteString
		+ '\n' };
	out << line;
	try
	{
	    out.flush();
	}
	catch (std::ios_base::failure)
	{
		out.clear();
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
