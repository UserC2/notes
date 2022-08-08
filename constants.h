#ifndef NOTES_CONSTANTS_H
#define NOTES_CONSTANTS_H

#include <string_view>

namespace constants
{
	constexpr std::string_view flagDelete{ "-d" };
	constexpr std::string_view flagHelp{ "-h" };
	constexpr std::string_view flagPrintKeys{ "-k" };
	constexpr std::string_view flagPrintAll{ "-p" };
	constexpr std::string_view flagWrite{ "-w" };
	constexpr std::string_view noteFilename{ ".notes.txt" };
}

#endif
