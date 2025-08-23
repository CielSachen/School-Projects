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

#include "io.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Clears the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) by
 * reading every succeeding excess character.
 * @remarks Characters will be read until an escape character (`\n`) or the end of the file (`EOF`) is reached.
 */
void
clear_input_buffer(void)
{
  int excess_character;

  while ((excess_character = getchar()) != '\n' && excess_character != EOF);
}

/**
 * @brief Gets a character from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted character.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
char
get_character_input(void)
{
  char input_character;

  fflush(stdout);

  scanf(" %c", &input_character);

  clear_input_buffer();

  return input_character;
}

/**
 * @brief Gets an integer from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted integer.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
char
get_integer_input(void)
{
  int input_integer;

  fflush(stdout);

  scanf(" %d", &input_integer);

  clear_input_buffer();

  return input_integer;
}

/**
 * @brief Gets a boolean from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @return The inputted boolean.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 * @remarks An input of `'Y'` is treated as `true`, while anything else is `false`.
 */
bool
get_boolean_input(void)
{
  if (toupper(get_character_input()) == 'Y')
  {
    return true;
  }

  return false;
}

/**
 * @brief Gets a string from the user through
 * [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)).
 * @param[out] string_input The string to store the input.
 * @param max_length The length of the string.
 * @note This will flush output buffer
 * [`stdout`](https://en.wikipedia.org/wiki/Standard_streams#Standard_output_(stdout)) before getting the input and
 * clear the input buffer [`stdin`](https://en.wikipedia.org/wiki/Standard_streams#Standard_input_(stdin)) after.
 */
void
get_string_input(char* string_input, int max_length)
{
  int last_index;

  fflush(stdout);

  fgets(string_input, max_length, stdin);

  last_index = strlen(string_input) - 1;

  if (string_input[last_index] == '\n')
  {
    string_input[last_index] = '\0';
  }
  else
  {
    clear_input_buffer();
  }
}

/**
 * @brief Prints the warning message corresponding to the situation encountered.
 * @param situation_id The ID of the situation encountered.
 */
void
print_warning_message(enum WarningId situation_id)
{
  switch (situation_id)
  {
    case MAXED_ENTRIES:
      printf(PRINT_COLOR_YELLOW "You have reached the maximum number of entries." PRINT_COLOR_RESET "\n");

      break;
    case MAXED_TRANSLATIONS:
      printf(PRINT_COLOR_YELLOW "You have reached the maximum number of translations." PRINT_COLOR_RESET "\n");

      break;
    case NO_ENTRIES_WITH_TRANSLATION:
      printf(PRINT_COLOR_YELLOW "There's no entry containing the translation you provided." PRINT_COLOR_RESET "\n");

      printf("\n");

      printf(PRINT_BACKGROUND_COLOR_GREEN
             "TIP:" PRINT_COLOR_RESET " " PRINT_COLOR_GREEN
             "Use the \"Add Entry\" action to add an entry containing the translation." PRINT_COLOR_RESET "\n");

      break;
    case NO_ENTRIES_WITH_WORD:
      printf(PRINT_COLOR_YELLOW "There's no entry containing the word you provided." PRINT_COLOR_RESET "\n");

      printf("\n");

      printf(PRINT_BACKGROUND_COLOR_GREEN
             "TIP:" PRINT_COLOR_RESET " " PRINT_COLOR_GREEN
             "Use the \"Add Entry\" action to add an entry containing the word." PRINT_COLOR_RESET "\n");

      break;
  }
}

/**
 * @brief Prints the error message corresponding to the type of error encountered.
 * @param error_type The type of the error encountered.
 */
void
print_error_message(enum ErrorCode error_type)
{
  printf(PRINT_BACKGROUND_COLOR_RED "ERROR:" PRINT_COLOR_RESET " " PRINT_COLOR_RED);

  switch (error_type)
  {
    case INVALID_ACTION_ID:
      printf("Unknown ID, please pick from the provided options.");

      break;
    case FILE_CREATION_FAILED:
      printf("The program could not create or overwrite the file.");

      break;
    case FILE_READING_FAILED:
      printf("The program could not open and read the file.");

      break;
    case NO_ENTRIES_PRESENT:
      printf("No entries are present at the moment.");

      break;
    default:
      printf("The program encountered an unknown error.");

      break;
  }

  printf(PRINT_COLOR_RESET "\n");
}
