#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

class TextInterface final
{
private:
	using keyArray_t = std::vector<std::string>;
	std::fstream noteFile;

public:
	TextInterface();

	/* Add a note. Returns false if out of memory. */
	bool add(std::string_view key, std::string_view noteString);
	/* Prints every key. */
	void printKeys();
	/* Prints every key, note, and the dates they were taken. */
	void printAll();
	/* Print a note. Returns false if key doesn't exist. */
	bool recall(std::string_view key);
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);
	/* Check the status of file. Returns false if file cannot be accessed. */
	bool status() const { return static_cast<bool>(noteFile); }

private:
	std::string extractKey();
	keyArray_t getKeys();
};

#endif
