#ifndef NOTES_TEXTINTERFACE_H
#define NOTES_TEXTINTERFACE_H

#include "constants.h"
#include "FstreamHandler.h"
#include <string>
#include <string_view>
#include <tuple> // TextInterface::noteType_t
#include <optional>
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
	/* Holds a reference to every note. */
	using noteReferenceArray_t = std::vector<std::reference_wrapper<noteType_t>>;
	using noteConstReferenceArray_t = std::vector<std::reference_wrapper<const noteType_t>>;
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
	/* Returns array of references to all matching notes. The array will be
	* empty if there are no matching notes. */
	noteReferenceArray_t findNotes(std::string_view key);
	noteConstReferenceArray_t findNotes(std::string_view key) const;
	/* Get a note from m_noteFile. */
	noteType_t getNote();
	/* Load m_noteArray with notes from m_noteFile. */
	void loadNoteArray();
	/* Print notes to standard output for viewing by the user. Returns false if
	* writing failed or noteArray is empty. */
	bool printNotes(const noteConstReferenceArray_t noteArray) const;
	/* Write a note to an output device. Returns false on failure. */
	bool write(const noteType_t& note, std::ostream& out) const;
	/* Write all notes from noteArray to noteFile. */
	bool writeFile();
};

#endif
