#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include <fstream>
#include <string_view>

class TextInterface final
{
private:
	std::fstream noteFile{ constants::noteFilename,
		std::ios::app | std::ios::out };

public:
	TextInterface() = default;

	/* Add a note. Returns false if key is too long. */
	bool add(std::string_view key, std::string_view noteString);
	/* Prints every key. */
	void printKeys() const;
	/* Prints every key, note, and the dates they were taken. */
	void printAll() const;
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);
	void status() const;
};

#endif
