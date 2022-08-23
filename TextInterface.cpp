#include "TextInterface.h"
#include "date.h" // date::currentDate()
#include "FstreamHandler.h"
#include "input.h" // askToContinue(), chooseYorN()
#include <algorithm> // std::count_if
#include <cassert>
#include <exception> // std::runtime_exception
#include <filesystem>
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

bool TextInterface::clear(std::string_view key)
{
	const indexArray_t notes{ findNotes(key) };
	if (notes.size() == 0)
	{
		std::cout << "Key does not exist." << '\n';
		return false;
	}
	printNotes(notes);
	if (input::chooseYOrN("Clear ALL NOTES with key "
		+ static_cast<std::string>(key) + " (Y/N)? "))
	{
		// the index of 'notes', *NOT* m_noteArray!
		// need signed type (long) so that index doesn't rollover at 0
		for (auto index{ static_cast<long>(notes.size() - 1) }; index >= 0; index--)
		{
			removeNote(notes[index]);
			/* By deleting the notes backwards, none of the indices in 'notes'
			* are invalidated by std::vector::erase(), which guarantees that
			* any iterators at or after the erased element will be invalid. */
		}
	}
	if (writeFile())
	{
		std::cout << "Deleted all notes with key " << key << ".\n";
		return true;
	}
	else
	{
		std::cout << "Writing failed.\n";
		return false;
	}
}

bool TextInterface::clearAll()
{
	if (!input::chooseYOrN("CLEAR ALL NOTES (Y/N)? "))
		return false;
	else if (!input::chooseYOrN("ARE YOU SURE (Y/N)? "))
		return false;
	else
	{
		m_noteArray.clear();
		if (writeFile())
		{
			std::cout << "Deleted all notes.\n";
			return true;
		}
		else
		{
			std::cout << "Writing failed.\n";
			return false;
		}
	}
}

void TextInterface::printAllKeys() const
{
	printKeys(findUniqueKeys());
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
	indexArray_t indexArray{ findNotes(key) };
	noteType_t note;
	if (indexArray.size() == 0)
	{
		std::cout << "No matching notes.\n";
		return false;
	}
	else if (indexArray.size() == 1)
	{
		note = m_noteArray.at(indexArray[0]);
	}
	else
	{
		printNumberedNotes(indexArray);
		size_t index{ selectANote(indexArray) };
		if (index == indexArray.size())
			return false;
		note = m_noteArray.at(indexArray[index]);
	}
	removeNote(note);
	if (writeFile())
	{
		const auto&[time, key, noteString]{ note };
		std::cout << "Deleted \"" << noteString << "\" with key \"" << key
			<< "\" created on " << time << '\n';
		return true;
	}
	else
	{
		std::cout << "Writing failed.\n";
		return false;
	}
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
        return getKey(note) == key;
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

TextInterface::keyArray_t TextInterface::findUniqueKeys() const
{
	keyArray_t keys;
	keys.reserve(m_noteArray.size());
	for (const noteType_t& note : m_noteArray)
	{
		auto matchesKey{ [&](std::string_view key) -> bool {
			return key == getKey(note);
		}};
		if (std::count_if(std::begin(keys), std::end(keys), matchesKey) == 0)
			keys.push_back(getKey(note));
	}
	return keys;
}

std::string_view TextInterface::getKey(const noteType_t& note) const
{
	return std::get<static_cast<size_t>(NoteType::key)>(note);
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

void TextInterface::printKeys(const keyArray_t& keyArray) const
{
	for (std::string_view key : keyArray)
	{
		std::cout << key << '\n';
	}
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

bool TextInterface::printNumberedNotes(const indexArray_t& indexArray) const
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
		std::cout << i << ' ';
		if (!write(m_noteArray.at(index), std::cout))
			return false;
		i++;
	}
	return true;
}

void TextInterface::removeNote(std::size_t index)
{
	try
	{
		m_noteArray.erase(std::begin(m_noteArray) + index);
	}
	catch (std::out_of_range& ex)
	{
		assert(false && "removeNote() called with invalid index.");
	}
}

void TextInterface::removeNote(const noteType_t& note)
{
	const auto iterator{
		std::find(std::begin(m_noteArray), std::end(m_noteArray), note)
	};
	assert((iterator == std::end(m_noteArray))
		&& "removeNote() called with invalid note. Note not found.");
	m_noteArray.erase(iterator);
}

std::size_t TextInterface::selectANote(const indexArray_t& indexArray) const
{
	std::cout << "Enter the number corresponding a note.\n";
	std::cout << "Enter any negative number to cancel.\n";
	while (true)
	{
		int input{ input::getInput<int>(": ") };
		if (input < 0)
		{
			std::cout << "Operation cancelled.\n";
			return indexArray.size();
		}
		else if (input >= indexArray.size())
			continue; // if index is too high, try again
		else
			return static_cast<std::size_t>(input);
	}
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
	try
	{
		m_noteFile.stream().close();
		m_noteFile.stream().open(m_noteFile.filename(), std::ios::out
			| std::ios::trunc);
	}
	catch (const std::runtime_error& ex)
	{
		std::cerr << "TextInterface::writeFile(): " << ex.what() << '\n';
		return false;
	}
	for (const noteType_t& note : m_noteArray)
	{
		if (!write(note, m_noteFile.stream()))
			return false;
	}
	return true;
}
