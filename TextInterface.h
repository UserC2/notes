#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include <fstream>
#include <string_view>

class TextInterface final
{
private:
	std::fstream noteFile;

public:
	TextInterface();

	/* Add a note. Returns false if out of memory. */
	bool add(std::string_view key, std::string_view noteString);
	/* Prints every key. */
	void printKeys() const;
	/* Prints every key, note, and the dates they were taken. */
	void printAll() const;
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);
	/* Check the status of file. Returns false if file cannot be accessed. */
	bool status() const { return static_cast<bool>(noteFile); }
};

#endif
