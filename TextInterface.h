#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include "FstreamHandler.h"
#include <string>
#include <string_view>
#include <tuple> // TextInterface::noteType_t
#include <ostream> // TextInterface::write()
#include <vector> // TextInterface::indexArray_t, keyArray_t, and noteArray_t

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
	/* Holds a string_view of keys. */
	using keyArray_t = std::vector<std::string_view>;
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
	/* Remove EVERY NOTE corresponding to 'key'. Prints all notes corresponding
	* to specified key and prompts user to confirm decision. Returns false if
	* writing failed or user cancelled operation. */
	bool clear(std::string_view key);
	/* Remove EVERY NOTE from the note file. Prompts user before deleting all
	* notes. Returns false if writing failed or user cancelled operation. */
	bool clearAll();
	/* Prints every key. */
	void printAllKeys() const;
	/* Prints every key, note, and the dates they were taken. */
	void printAll() const;
	/* Print a note. Returns false if key doesn't exist. */
	bool recall(std::string_view key) const;
	/* Delete a note. Returns false if key doesn't exist. */
	bool remove(std::string_view key);
	/* Sorts notes in order of oldest to newest according to their date, and
	* then alphabetically according to their key within the same date. Returns
	* false if writing failed. */
	bool sortByDate();
	/* Sorts notes alphabetically according to their key. Returns false if
	* writing failed. */
	bool sortByKey();

private:
	/* Returns an array of indices of all notes. */
	indexArray_t findAllNotes() const;
	/* Returns an array of indices of all matching notes. The array will be
	* empty if there are no matching notes. */
	indexArray_t findNotes(std::string_view key) const;
	/* Returns array of all unique keys. */
	keyArray_t findUniqueKeys() const;
	/* Get a formatted date in a string from a noteType_t. */
	std::string_view getDate(const noteType_t& note) const;
	/* Get a key from a noteType_t. */
	std::string_view getKey(const noteType_t& note) const;
	/* Get a note from m_noteFile. */
	noteType_t getNote();
	/* Load m_noteArray with notes from m_noteFile. */
	void loadNoteArray();
	/* Print keys to standard output. */
	void printKeys(const keyArray_t& keyArray) const;
	/* Print notes to standard output for viewing by the user. Returns false if
	* writing failed or indexArray is empty. */
	bool printNotes(const indexArray_t& indexArray) const;
	/* Print notes to standard output for viewing by the user. Each note is
	* prefixed with a number corresponding to its index in 'indexArray'.
	* Returns false if writing failed or indexArray is empty. Numbered notes
	* start at '0' (like the array indices). */
	bool printNumberedNotes(const indexArray_t& indexArray) const;
	/* Delete the specified note from m_noteArray. */
	void removeNote(std::size_t index);
	void removeNote(const noteType_t& note);
	/* Ask a user to select a note out of an indexArray_t. Loops until user
	* enters a valid number, or enters a negative number to cancel. Returns an
	index one larger than the maximum index of the array on failure. */
	std::size_t selectANote(const indexArray_t& indexArray) const;
	/* Write a note to an output device. Returns false on failure. */
	bool write(const noteType_t& note, std::ostream& out) const;
	/* Write all notes from noteArray to noteFile. */
	bool writeFile();
};

#endif
