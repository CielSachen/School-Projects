/*
 * Simple Translator creates and uses translation dictionaries to translate words.
 * Copyright (C) 2025  Raphael Panaligan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef IO_H_
#define IO_H_

#include <stdbool.h>

/** @brief The maximum length of a file's name. */
#define MAXIMUM_FILENAME_LENGTH 31

/** @brief The accepted import and export file extension. */
#define FILE_EXTENSION ".txt"

/** @brief The ANSI code to reset the text print color. */
#define PRINT_COLOR_RESET "\033[0m"

/** @brief The ANSI code for a red text print color. */
#define PRINT_COLOR_RED "\033[0;31m"
/** @brief The ANSI code for a green text print color. */
#define PRINT_COLOR_GREEN "\033[0;32m"
/** @brief The ANSI code for a yellow text print color. */
#define PRINT_COLOR_YELLOW "\033[0;33m"
/** @brief The ANSI code for a blue text print color. */
#define PRINT_COLOR_BLUE "\033[0;34m"

/** @brief The ANSI code for a red print background color. */
#define PRINT_BACKGROUND_COLOR_RED "\033[41m"
/** @brief The ANSI code for a green print background color. */
#define PRINT_BACKGROUND_COLOR_GREEN "\033[42m"
/** @brief The ANSI code for a yellow print background color. */
#define PRINT_BACKGROUND_COLOR_YELLOW "\033[43m"
/** @brief The ANSI code for a blue print background color. */
#define PRINT_BACKGROUND_COLOR_BLUE "\033[44m"

/** @brief A string with a maximum length of 20 characters. */
typedef char String20[21];
/** @brief A string with a maximum length of 30 characters. */
typedef char String30[31];
/** @brief A string with a maximum length of 150 characters. */
typedef char String150[151];

/**
 * @brief Clears the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) by
 * reading every succeeding excess character.
 * @remarks Characters will be read until an escape character (`\n`) or the end of the file (`EOF`) is reached.
 */
void clear_input_buffer(void);

/**
 * @brief Gets a character from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted character.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
char get_character_input(void);

/**
 * @brief Gets an integer from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted integer.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
char get_integer_input(void);

/**
 * @brief Gets a boolean from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted boolean.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 * @remarks An input of `'Y'` is treated as `true`, while anything else is `false`.
 */
bool get_boolean_input(void);

/**
 * @brief Gets a string from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @param[out] string_input The string to store the input in.
 * @param max_length The length of the string.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
void get_string_input(char* string_input, int max_length);

/** @brief The warning situation IDs. */
enum WarningId
{
  /** @brief The number of entries has reached the maximum. */
  MAXED_ENTRIES,
  /** @brief The number of translations in an entry has reached the maximum. */
  MAXED_TRANSLATIONS,
  /** @brief No entries contain a specific translation. */
  NO_ENTRIES_WITH_TRANSLATION,
  /** @brief No entries contain a specific word. */
  NO_ENTRIES_WITH_WORD,
};

/**
 * @brief Prints the warning message corresponding to the situation encountered.
 * @param situation_id The ID of the situation encountered.
 */
void print_warning_message(enum WarningId situation_id);

/** @brief The error status codes. */
enum ErrorCode
{
  /** @brief The user gave an unknown ID input. */
  INVALID_ACTION_ID,
  /** @brief The file cannot be created or overwritten. */
  FILE_CREATION_FAILED,
  /** @brief The file cannot be opened and read. */
  FILE_READING_FAILED,
  /** @brief The entry list is empty. */
  NO_ENTRIES_PRESENT,
};

/**
 * @brief Prints the error message corresponding to the type of error encountered.
 * @param error_type The type of the error encountered.
 */
void print_error_message(enum ErrorCode error_type);

#endif  // IO_H_
