#ifndef NOTES_CONSTANTS_H
#define NOTES_CONSTANTS_H

#include <cstddef> // std::size_t
#include <string_view>

namespace constants
{
	constexpr std::size_t maxKeySize{ static_cast<std::size_t>(16) };
	/* How many notes to display in one page on screen */
	constexpr std::size_t maxPageLength{ static_cast<std::size_t>(10) };
	/* How many chars can key be before two tabs is too much */
	constexpr std::size_t keyHalfSize{ static_cast<std::size_t>(7) };
	constexpr std::string_view flagClear{ "-c" };
	constexpr std::string_view flagDelete{ "-d" };
	constexpr std::string_view flagHelp{ "-h" };
	constexpr std::string_view flagPrintKeys{ "-k" };
	constexpr std::string_view flagPrintAll{ "-p" };
	constexpr std::string_view flagRecall{ "-r" };
	constexpr std::string_view flagWrite{ "-w" };
	constexpr std::string_view noteFilename{ "/data/data/com.termux/files/home/.notes.txt" };
}

#endif
