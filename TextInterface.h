#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include "FstreamHandler.h"
#include <string>
#include <string_view>
#include <tuple> // TextInterface::noteType_t
#include <ostream> // TextInterface::write()
#include <vector>

class TextInterface final
{
private:
	enum class NoteType
	{
		date,
		key,
		noteString,
	};
	/* Holds the time, key, and note string of a note. */
	using noteType_t = std::tuple<std::string, std::string, std::string>;
	/* Array of every note. */
	using noteArray_t = std::vector<noteType_t>;
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

private:
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
