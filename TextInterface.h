#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include "FstreamHandler.h"
#include <fstream>
#include <string>
#include <string_view>
#include <tuple> // TextInterface::noteType_t
#include <optional>
#include <ostream> // TextInterface::write()
#include <vector>

class TextInterface final
{
private:
	/* Holds the time, key, and note string of a note. */
	using noteType_t = std::tuple<std::string, std::string, std::string>;
	using noteArray_t = std::vector<noteType_t>;
	using noteKey_t = std::optional<std::string>;
	using keyArray_t = std::vector<noteKey_t>;
	FstreamHandler m_noteFile;
	noteArray_t m_noteArray;

public:
	/* Can throw std::runtime_error on failure. */
	TextInterface();

	/* Add a note. Returns false on failure. */
	bool add(std::string_view key, std::string_view noteString);
	/* Prints every key. */
	void printKeys();
	/* Prints every key, note, and the dates they were taken. */
	void printAll();
	/* Print a note. Returns false if key doesn't exist. */
	bool recall(std::string_view key);
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);
	//  this is bad, should be fixed. also textInterface constructor needs to load array
	/* Check the status of file. Returns false if file cannot be accessed. */
	// bool status() { return static_cast<bool>(noteFile.stream()); }

private:
	/* Extract a key out of the file, starting at the current file pointer. */
	std::optional<std::string> extractKey();
	/* Extract an array of all keys. */
	keyArray_t getKeys();
	/* Find 'key', if it exists. */
//	noteKey_t findKey(std::string key);
	/* Get a note from m_noteFile. */
	noteType_t getNote();
	/* Load m_noteArray with notes from m_noteFile. */
	void loadNoteArray();
	/* Write a note to an output device. Returns false on failutre. */
	bool write(const noteType_t& note, std::ostream& out);
	/* Write all notes from noteArray to noteFile. */
	bool writeFile();
};

#endif
