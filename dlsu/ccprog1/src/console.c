/*
 * Tides of Manila is a turn-based trading game set in Manila.
 * Copyright (C) 2024  Raphael Panaligan
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

#include "console.h"

#include <stdio.h>

/** @brief Resets the color of text output in the console using an ANSI escape sequence. */
void resetConsoleColor(void) { printf(COLOR_DEFAULT); }

/** @brief Sets the color of text output in the console to red using an ANSI escape sequence. */
void setConsoleColorToRed(void) { printf(COLOR_RED); }

/** @brief Sets the color of text output in the console to green using an ANSI escape sequence. */
void setConsoleColorToGreen(void) { printf(COLOR_GREEN); }

/** @brief Sets the color of text output in the console to yellow using an ANSI escape sequence. */
void setConsoleColorToYellow(void) { printf(COLOR_YELLOW); }

/** @brief Sets the color of text output in the console to blue using an ANSI escape sequence. */
void setConsoleColorToBlue(void) { printf(COLOR_BLUE); }

/** @brief Sets the color of text output in the console to purple using an ANSI escape sequence. */
void setConsoleColorToPurple(void) { printf(COLOR_PURPLE); }

/** @brief Sets the color of text output in the console to cyan using an ANSI escape sequence. */
void setConsoleColorToCyan(void) { printf(COLOR_CYAN); }

/**
 * @brief Prompts the player to input an integer into the console.
 * @param nConsoleLeftPaddingSize The number of spaces to move the console cursor to the right.
 * @return The first integer value inputted into the console..
 */
int getIntegerInput(int nConsoleLeftPaddingSize) {
  int nGivenInteger;

  printf("\n");

  printf("%*c%% ", nConsoleLeftPaddingSize, ' ');

  scanf(" %d", &nGivenInteger);

  return nGivenInteger;
}

/**
 * @brief Prompts the player to input a character into the console.
 * @param nConsoleLeftPaddingSize The number of spaces to move the console cursor to the right.
 * @return The first character value inputted into the console.
 */
char getCharacterInput(int nConsoleLeftPaddingSize) {
  char cGivenCharacter;

  printf("\n");

  printf("%*c%% ", nConsoleLeftPaddingSize, ' ');

  scanf(" %c", &cGivenCharacter);

  return cGivenCharacter;
}
