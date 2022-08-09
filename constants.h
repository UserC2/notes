#ifndef NOTES_CONSTANTS_H
#define NOTES_CONSTANTS_H

#include <cstddef> // std::size_t
#include <string>
#include <string_view>

namespace constants
{
	const std::string stringExtractionFailed{ "```extraction_failed```" };
	constexpr std::size_t maxKeySize{ static_cast<std::size_t>(16) };
	constexpr std::size_t tabSize{ static_cast<std::size_t>(8) };
	constexpr std::string_view flagDelete{ "-d" };
	constexpr std::string_view flagHelp{ "-h" };
	constexpr std::string_view flagPrintKeys{ "-k" };
	constexpr std::string_view flagPrintAll{ "-p" };
	constexpr std::string_view flagRecall{ "-r" };
	constexpr std::string_view flagWrite{ "-w" };
	constexpr std::string_view noteFilename{ ".notes.txt" };
}

#endif
