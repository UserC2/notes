#ifndef NOTES_CONSTANTS_H
#define NOTES_CONSTANTS_H

#include <string_view>

namespace constants
{
	constexpr std::string_view flag_delete{ "-d" };
	constexpr std::string_view flag_help{ "-h" };
	constexpr std::string_view flag_printkeys{ "-k" };
	constexpr std::string_view flag_printall{ "-p" };
	constexpr std::string_view flag_write{ "-w" };
}

#endif
