#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include "FstreamHandler.h"
#include <string>
#include <string_view>
#include <tuple> // TextInterface::noteType_t
#include <ostream> // TextInterface::write()
#include <vector> // TextInterface::noteArray_t and indexArray_t

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
	/* Holds indices of notes. After removing a note (std::vector::erase()),
	* all indices >= the removed once are invalid. */
	using indexArray_t = std::vector<std::size_t>;
	FstreamHandler m_noteFile;
	noteArray_t m_noteArray;

public:
	/* Can throw std::runtime_error on failure. */
	TextInterface();

	/* Add a note. Returns false on failure. */
	bool add(std::string_view key, std::string_view noteString);
	/* Prints every key. */
	void printKeys() const;
	/* Prints every key, note, and the dates they were taken. */
	void printAll() const;
	/* Print a note. Returns false if key doesn't exist. */
	bool recall(std::string_view key) const;
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);

private:
	/* Returns an array of indices of all notes. */
	indexArray_t findAllNotes() const;
	/* Returns an array of indices of all matching notes. The array will be
	* empty if there are no matching notes. */
	indexArray_t findNotes(std::string_view key) const;
	/* Get a note from m_noteFile. */
	noteType_t getNote();
	/* Load m_noteArray with notes from m_noteFile. */
	void loadNoteArray();
	/* Print notes to standard output for viewing by the user. Returns false if
	* writing failed or indexArray is empty. */
	bool printNotes(const indexArray_t& indexArray) const;
	/* Write a note to an output device. Returns false on failure. */
	bool write(const noteType_t& note, std::ostream& out) const;
	/* Write all notes from noteArray to noteFile. */
	bool writeFile();
};

#endif
