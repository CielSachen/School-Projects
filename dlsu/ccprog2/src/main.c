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

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "data_management.h"
#include "io.h"
#include "translation.h"

int
main(void)
{
  EntryList translation_entries;
  bool is_exiting_program = false;
  char chosen_menu_id;
  char chosen_action_id;
  bool is_exiting_menu;

  while (!is_exiting_program)
  {
    translation_entries.length = 0;

    printf("\n");

    printf(" __ _                 _        " PRINT_COLOR_BLUE
           "_____                     _       _             " PRINT_COLOR_RESET
           "\n"
           "/ _(_)_ __ ___  _ __ | | ___  " PRINT_COLOR_BLUE
           "/__   \\_ __ __ _ _ __  ___| | __ _| |_ ___  _ __ " PRINT_COLOR_RESET
           "\n"
           "\\ \\| | '_ ` _ \\| '_ \\| |/ _ \\   " PRINT_COLOR_BLUE
           "/ /\\/ '__/ _` | '_ \\/ __| |/ _` | __/ _ \\| '__|" PRINT_COLOR_RESET
           "\n"
           "_\\ \\ | | | | | | |_) | |  __/  " PRINT_COLOR_BLUE
           "/ /  | | | (_| | | | \\__ \\ | (_| | || (_) | |   " PRINT_COLOR_RESET
           "\n"
           "\\__/_|_| |_| |_| .__/|_|\\___|  " PRINT_COLOR_BLUE
           "\\/   |_|  \\__,_|_| |_|___/_|\\__,_|\\__\\___/|_|   " PRINT_COLOR_RESET
           "\n"
           "               |_|                                                             \n");

    printf("\n");

    printf(
      "  [M] Manage Data\n"
      "  [T] Translate\n"
      "\n" PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
      "\n"
      " > ");

    chosen_menu_id = toupper(get_character_input());

    if (chosen_menu_id != 'X')
    {
      printf("\n");
    }

    switch (chosen_menu_id)
    {
      case 'M':
        is_exiting_menu = false;

        while (!is_exiting_menu)
        {
          printf(
            "What would you like to do?\n"
            "  [1] Add Entry\n"
            "  [2] Add Translations\n"
            "  [3] Delete Entry\n"
            "  [4] Delete Translations\n"
            "  [5] Display All Entries\n"
            "  [6] Search Word\n"
            "  [7] Search Translations\n"
            "  [8] Export\n"
            "  [9] Import\n"
            "\n" PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
            "\n"
            " > ");

          chosen_action_id = toupper(get_character_input());

          printf("\n");

          switch (chosen_action_id)
          {
            case '1':
              add_entries(&translation_entries);

              break;
            case '2':
              add_translations(&translation_entries);

              break;
            case '3':
              delete_entry(&translation_entries);

              break;
            case '4':
              delete_translations(&translation_entries);

              break;
            case '5':
              display_entries(&translation_entries);

              break;
            case '6':
              search_word(&translation_entries);

              break;
            case '7':
              search_translation(&translation_entries);

              break;
            case '8':
              export_entries(&translation_entries);

              break;
            case '9':
              import_entries(&translation_entries, true);

              break;
            case 'X':
              is_exiting_menu = true;

              break;
            default:
              print_error_message(INVALID_ACTION_ID);

              break;
          }

          if (chosen_action_id != 'X')
          {
            printf("\n");
          }
        }

        break;
      case 'T':
        import_entries(&translation_entries, false);

        if (translation_entries.length > 0)
        {
          is_exiting_menu = false;
        }
        else
        {
          is_exiting_menu = true;
        }

        printf("\n");

        while (!is_exiting_menu)
        {
          printf(
            "What would you like to do?\n"
            "  [1] Translate Text Input\n"
            "  [2] Translate Text File\n"
            "\n" PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
            "\n"
            " > ");

          chosen_action_id = toupper(get_character_input());

          printf("\n");

          switch (chosen_action_id)
          {
            case '1':
              translate_input(&translation_entries);

              break;
            case '2':
              translate_text_file(&translation_entries);

              break;
            case 'X':
              is_exiting_menu = true;

              break;
            default:
              print_error_message(INVALID_ACTION_ID);

              break;
          }

          if (chosen_action_id != 'X')
          {
            printf("\n");
          }
        }

        break;
      case 'X':
        is_exiting_program = true;

        break;
      default:
        print_error_message(INVALID_ACTION_ID);

        break;
    }
  }
}
