#include "TextInterface.h"
#include <exception>
#include <fstream>
#include <string_view>

bool TextInterface::add(std::string_view key, std::string_view noteString)
{
	return false;
	// return false if key is too long
	// add line to txt file:                                               // date: dd/mm/yyyy
    // (Date)\tkey:<tabs>note
    // tabs calculation: if (str.length() < 8) tabs == 2
    // if (str.length < 16) tabs = 1
    // else fail("Key too long.")
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

void TextInterface::status() const
{
	if (!noteFile)
	{
		throw std::runtime_error(
			static_cast<std::string>(constants::noteFilename)
			+ " not found or inaccessable.\n");
	}
}
