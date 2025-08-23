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

#include "data_management.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Checks if a translation already has an entry containing it.
 * @param[in] translation The translation to check. If the language of the translation is empty, the language will be
 * ignored.
 * @param[in] entries The entries to check against.
 * @return The amount entries containing the translation.
 */
int
has_entry(Translation* translation, EntryList* entries)
{
  int entry_index;
  Entry* entry;
  bool is_containing_translation;
  int translation_index;
  Translation* entry_translation;
  int entry_count = 0;

  for (entry_index = 0; entry_index < entries->length; entry_index++)
  {
    entry = &entries->values[entry_index];
    is_containing_translation = false;
    translation_index = 0;

    while (!is_containing_translation && translation_index < entry->translations_amount)
    {
      entry_translation = &entry->translations[translation_index];

      if ((strlen(translation->language) == 0 && strcmp(entry_translation->word, translation->word) == 0) ||
          (strlen(translation->language) > 0 && strcmp(entry_translation->language, translation->language) == 0 &&
           strcmp(entry_translation->word, translation->word) == 0))
      {
        is_containing_translation = true;
        entry_count++;
      }
      else
      {
        translation_index++;
      }
    }
  }

  return entry_count;
}

/**
 * @brief Gets the index of the nth entry containing the translation.
 * @param[in] translation The translation to get the index of the entry of. If the language of the translation is empty,
 * the language will be ignored.
 * @param[in] entries The entries to get from.
 * @param nth The position in the sequence of indexes to get.
 * @return The index of the translation, or `-1` if it does not exist.
 */
int
get_entry_index(Translation* translation, EntryList* entries, int nth)
{
  bool is_existing_entry = false;
  int entry_index = 0;
  Entry* entry;
  bool is_containing_translation;
  int translation_index;
  Translation* entry_translation;
  int entry_count = 0;

  while (!is_existing_entry && entry_index < entries->length)
  {
    entry = &entries->values[entry_index];
    is_containing_translation = false;
    translation_index = 0;

    while (!is_containing_translation && translation_index < entry->translations_amount)
    {
      entry_translation = &entry->translations[translation_index];

      if ((strlen(translation->language) == 0 && strcmp(entry_translation->word, translation->word) == 0) ||
          (strlen(translation->language) > 0 && strcmp(entry_translation->language, translation->language) == 0 &&
           strcmp(entry_translation->word, translation->word) == 0))
      {
        is_containing_translation = true;
        entry_count++;
      }
      else
      {
        translation_index++;
      }
    }

    if (entry_count == nth)
    {
      is_existing_entry = true;
    }
    else
    {
      entry_index++;
    }
  }

  if (!is_existing_entry)
  {
    return -1;
  }

  return entry_index;
}

/**
 * @brief Gets the index of the translation in the specific language.
 * @param lang The language of the translation to get the index of.
 * @param entry The entry to get from.
 * @return The index of the translation, or `-1` if it does not exist.
 */
int
get_translation_index(String20 lang, Entry* entry)
{
  bool is_containing_language = false;
  int index = 0;

  while (!is_containing_language && index < entry->translations_amount)
  {
    if (strcmp(entry->translations[index].language, lang) == 0)
    {
      is_containing_language = true;
    }
    else
    {
      index++;
    }
  }

  if (!is_containing_language)
  {
    return -1;
  }

  return index;
}

/**
 * @brief Sorts the entries by alphabetical order based on their English translation.
 * @param[in,out] entries The entries to sort.
 */
void
sort_entries(EntryList* entries)
{
  int entry_index;
  int other_entry_index;
  Entry entry;
  String20 sorting_language = "English";
  int entry_english_index;
  Entry other_entry;
  int other_entry_english_index;
  Entry temporary;

  for (entry_index = 0; entry_index < entries->length - 1; entry_index++)
  {
    for (other_entry_index = entry_index + 1; other_entry_index < entries->length; other_entry_index++)
    {
      entry = entries->values[entry_index];
      entry_english_index = get_translation_index(sorting_language, &entry);
      other_entry = entries->values[other_entry_index];
      other_entry_english_index = get_translation_index(sorting_language, &other_entry);

      if ((entry_english_index >= 0 && other_entry_english_index >= 0 &&
           strcmp(entry.translations[entry_english_index].word,
                  other_entry.translations[other_entry_english_index].word) > 0) ||
          (entry_english_index == -1 && other_entry_english_index >= 0))
      {
        temporary = entry;
        entries->values[entry_index] = other_entry;
        entries->values[other_entry_index] = temporary;
      }
    }
  }
}

/**
 * @brief Sorts the translations of the entries by alphabetical order based on their language.
 * @param[in,out] entries The entries to sort the translations of.
 */
void
sort_translations(EntryList* entries)
{
  int entry_index;
  Entry* entry;
  int translation_index;
  int other_translation_index;
  Translation translation;
  Translation other_translation;
  Translation temporary;

  for (entry_index = 0; entry_index < entries->length; entry_index++)
  {
    entry = &entries->values[entry_index];

    if (entry->translations_amount > 1)
    {
      for (translation_index = 0; translation_index < entry->translations_amount - 1; translation_index++)
      {
        for (other_translation_index = translation_index + 1; other_translation_index < entry->translations_amount;
             other_translation_index++)
        {
          translation = entry->translations[translation_index];
          other_translation = entry->translations[other_translation_index];

          if (strcmp(translation.language, other_translation.language) > 0)
          {
            temporary = translation;
            entry->translations[translation_index] = other_translation;
            entry->translations[other_translation_index] = temporary;
          }
        }
      }
    }
  }
}

/**
 * @brief Prints an entry to `stdout`.
 * @param[in] entry The entry to print.
 */
void
print_entry(Entry* entry)
{
  int index;

  printf(
    "|--------------------------------------------------|\n"
    "| ID |       Language       |     Translation      |\n"
    "|--------------------------------------------------|\n");

  for (index = 0; index < entry->translations_amount; index++)
  {
    printf("| %-2d | %-20s | %-20s |\n", index + 1, entry->translations[index].language,
           entry->translations[index].word);
  }

  printf("|--------------------------------------------------|\n");
}

/**
 * @brief Adds an entry or multiple entries by asking the user to input their first translations.
 * @param[in,out] entries The entries to add to.
 */
void
add_entries(EntryList* entries)
{
  bool is_exiting = false;
  Entry entry;
  entry.translations_amount = 1;
  int entries_amount;
  bool has_confirmed;
  int entry_index;
  int entry_count;
  bool is_valid_action_id;
  char chosen_action_id;
  bool is_adding;
  bool is_adding_more_translations;
  Translation translation;
  bool is_adding_more;

  if (entries->length < MAXIMUM_ENTRIES_LENGTH)
  {
    while (!is_exiting)
    {
      printf("Input the language of the first translation in the entry " PRINT_COLOR_YELLOW
             "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

      get_string_input(entry.translations[0].language, MAXIMUM_LANGUAGE_LENGTH);

      printf("Input the first translation in the entry " PRINT_COLOR_YELLOW
             "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

      get_string_input(entry.translations[0].word, MAXIMUM_WORD_LENGTH);

      if ((entries_amount = has_entry(&entry.translations[0], entries)))
      {
        printf("\n");

        entry_count = 1;

        do
        {
          entry_index = get_entry_index(&entry.translations[0], entries, entry_count);

          printf(" Entry ID: %d\n", entry_index + 1);

          print_entry(&entries->values[entry_index]);

          do
          {
            printf("\n");

            if (entry_count > 1)
            {
              printf("  [P] <-- Previous\n");
            }

            if (entry_count < entries_amount)
            {
              printf("  [N] --> Next\n");
            }

            printf(PRINT_COLOR_GREEN "  [Y] A New Entry\n" PRINT_COLOR_RED "  [X] Not a New Entry\n" PRINT_COLOR_RESET
                                     "\n"
                                     " > ");

            chosen_action_id = get_character_input();

            if (toupper(chosen_action_id) == 'P' && entry_count > 1)
            {
              is_valid_action_id = true;
              entry_count--;
              has_confirmed = false;
            }
            else if (toupper(chosen_action_id) == 'N' && entry_count < entries_amount)
            {
              is_valid_action_id = true;
              entry_count++;
              has_confirmed = false;
            }
            else if (toupper(chosen_action_id) == 'Y')
            {
              is_valid_action_id = true;
              is_adding = true;
              has_confirmed = true;
            }
            else if (toupper(chosen_action_id) == 'X')
            {
              is_valid_action_id = true;
              is_adding = false;
              has_confirmed = true;
            }
            else
            {
              is_valid_action_id = false;

              printf("\n");

              print_error_message(INVALID_ACTION_ID);
            }
          } while (!is_valid_action_id);
        } while (!has_confirmed);
      }
      else
      {
        is_adding = true;
      }

      if (is_adding)
      {
        do
        {
          printf("\n");

          printf("Add another translation? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

          is_adding_more_translations = get_boolean_input();

          if (is_adding_more_translations)
          {
            printf("\n");

            printf("Input the language of the new translation in the entry " PRINT_COLOR_YELLOW
                   "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

            get_string_input(translation.language, MAXIMUM_LANGUAGE_LENGTH);

            printf("Input the new translation in the entry " PRINT_COLOR_YELLOW
                   "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

            get_string_input(translation.word, MAXIMUM_WORD_LENGTH);

            strcpy(entry.translations[entry.translations_amount].language, translation.language);
            strcpy(entry.translations[entry.translations_amount].word, translation.word);

            entry.translations_amount++;

            printf("\n");

            printf(PRINT_COLOR_GREEN "Added the translation into the entry!" PRINT_COLOR_RESET "\n");
          }
        } while (is_adding_more_translations);

        entries->values[entries->length++] = entry;

        printf("\n");

        printf(PRINT_COLOR_GREEN "Added the entry into the stored list!" PRINT_COLOR_RESET "\n");
      }

      printf("\n");

      if (entries->length < MAXIMUM_ENTRIES_LENGTH)
      {
        printf("Add another entry? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

        is_adding_more = get_boolean_input();

        if (is_adding_more)
        {
          printf("\n");
        }
        else
        {
          is_exiting = true;
        }
      }
      else
      {
        print_warning_message(MAXED_ENTRIES);

        is_exiting = true;
      }
    }

    sort_entries(entries);
    sort_translations(entries);
  }
  else
  {
    print_warning_message(MAXED_ENTRIES);
  }
}

/**
 * @brief Adds a translation or multiple translations to an entry or multiple entries.
 * @param[in,out] entries The entries to add translations to.
 * @remarks The user will be asked to input a translation from the entry to add to.
 */
void
add_translations(EntryList* entries)
{
  bool is_exiting = false;
  bool is_different_entry = true;
  Translation translation;
  int entries_amount;
  bool has_picked_entry;
  int entry_index;
  int entry_count = 1;
  bool is_valid_action_id;
  char chosen_action_id[4];
  int chosen_entry_id;
  Entry* entry;
  Translation new_translation;
  bool is_adding_more;

  while (!is_exiting)
  {
    if (is_different_entry)
    {
      printf("Input the language of a translation in the entry " PRINT_COLOR_YELLOW
             "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

      get_string_input(translation.language, MAXIMUM_LANGUAGE_LENGTH);

      printf("Input a translation in the entry " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
             ": ");

      get_string_input(translation.word, MAXIMUM_WORD_LENGTH);

      printf("\n");
    }

    if ((entries_amount = has_entry(&translation, entries)))
    {
      if (entries_amount > 1)
      {
        do
        {
          entry_index = get_entry_index(&translation, entries, entry_count);

          printf(" Entry ID: %d\n", entry_index + 1);

          print_entry(&entries->values[entry_index]);

          do
          {
            printf("\n");

            if (entry_count > 1)
            {
              printf("  [P] <-- Previous\n");
            }

            if (entry_count < entries_amount)
            {
              printf("  [N] --> Next\n");
            }

            printf(
              "  [%d] Add to This Entry\n"
              "\n"
              " > ",
              entry_index);

            get_string_input(chosen_action_id, sizeof chosen_action_id);

            printf("\n");

            if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_count > 1)
            {
              is_valid_action_id = true;
              entry_count--;
              has_picked_entry = false;
            }
            else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                     entry_count < entries_amount)
            {
              is_valid_action_id = true;
              entry_count++;
              has_picked_entry = false;
            }
            else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_index)
            {
              is_valid_action_id = true;
              has_picked_entry = true;
            }
            else
            {
              is_valid_action_id = false;

              print_error_message(INVALID_ACTION_ID);
            }
          } while (!is_valid_action_id);
        } while (!has_picked_entry);
      }
      else
      {
        entry_index = get_entry_index(&translation, entries, 1);
      }

      entry = &entries->values[entry_index];

      if (entry->translations_amount < MAXIMUM_ENTRY_TRANSLATIONS)
      {
        printf("Input the language of the new translation in the entry " PRINT_COLOR_YELLOW
               "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

        get_string_input(new_translation.language, MAXIMUM_LANGUAGE_LENGTH);

        printf("Input the new translation in the entry " PRINT_COLOR_YELLOW
               "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

        get_string_input(new_translation.word, MAXIMUM_WORD_LENGTH);

        strcpy(entry->translations[entry->translations_amount].language, new_translation.language);
        strcpy(entry->translations[entry->translations_amount].word, new_translation.word);

        entry->translations_amount++;

        printf("\n");

        printf(PRINT_COLOR_GREEN "Added the translation into the entry!" PRINT_COLOR_RESET "\n");

        printf("\n");

        if (entry->translations_amount < MAXIMUM_ENTRY_TRANSLATIONS)
        {
          printf("Add another translation? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

          is_adding_more = get_boolean_input();

          if (is_adding_more)
          {
            printf("Add to the same entry? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

            is_different_entry = tolower(get_character_input());

            printf("\n");
          }
          else
          {
            is_exiting = true;
          }
        }
        else
        {
          print_warning_message(MAXED_TRANSLATIONS);

          is_exiting = true;
        }
      }
      else
      {
        print_warning_message(MAXED_TRANSLATIONS);

        is_exiting = true;
      }
    }
    else
    {
      print_warning_message(NO_ENTRIES_WITH_TRANSLATION);

      is_exiting = true;
    }
  }

  sort_translations(entries);
}

/**
 * @brief Deletes an entry by moving it at the end of the list and decreasing the length.
 * @param[in,out] entries The entries to delete one of.
 */
void
delete_entry(EntryList* entries)
{
  bool is_exiting = false;
  int entry_index = 0;
  bool is_valid_action_id;
  char chosen_action_id[4];
  int chosen_entry_id;
  bool is_deleting = false;

  if (entries->length > 0)
  {
    while (!is_exiting)
    {
      printf(" Entry ID: %d\n", entry_index + 1);

      print_entry(&entries->values[entry_index]);

      do
      {
        printf("\n");

        if (entry_index > 0)
        {
          printf("  [P] <-- Previous\n");
        }

        if (entry_index < entries->length - 1)
        {
          printf("  [N] --> Next\n");
        }

        if (entry_index > 0 || entry_index < entries->length - 1)
        {
          printf("\n");
        }

        printf(PRINT_COLOR_RED
               "  [%d] Delete This Entry\n"
               "\n"
               "  [X] Exit\n" PRINT_COLOR_RESET
               "\n"
               " > ",
               entry_index + 1);

        get_string_input(chosen_action_id, sizeof chosen_action_id);

        printf("\n");

        if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_index > 0)
        {
          is_valid_action_id = true;
          entry_index--;
        }
        else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                 entry_index < entries->length - 1)
        {
          is_valid_action_id = true;
          entry_index++;
        }
        else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'X')
        {
          is_valid_action_id = true;
          is_exiting = true;
        }
        else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_index + 1)
        {
          is_valid_action_id = true;
          is_deleting = true;
          is_exiting = true;
        }
        else
        {
          is_valid_action_id = false;

          print_error_message(INVALID_ACTION_ID);
        }
      } while (!is_valid_action_id);
    }

    if (is_deleting)
    {
      entries->values[entry_index] = entries->values[--entries->length];

      sort_entries(entries);

      printf(PRINT_COLOR_RED "Deleted the entry from the stored list!" PRINT_COLOR_RESET "\n");
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Deletes translations from entries by moving them at the end of the lists and decreasing their lengths. Entries
 * with zero translations will be deleted.
 * @param[in,out] entries The entries to delete translations from.
 */
void
delete_translations(EntryList* entries)
{
  bool is_exiting = false;
  int entry_index = 0;
  char chosen_action_id[4];
  bool is_valid_action_id;
  int chosen_entry_id;
  bool is_deleting = false;
  Entry* entry;
  int translation_index;
  int chosen_translation_id;

  if (entries->length > 0)
  {
    while (!is_exiting)
    {
      printf(" Entry ID: %d\n", entry_index + 1);

      print_entry(&entries->values[entry_index]);

      do
      {
        printf("\n");

        if (entry_index > 0)
        {
          printf("  [P] <-- Previous\n");
        }

        if (entry_index < entries->length - 1)
        {
          printf("  [N] --> Next\n");
        }

        if (entry_index > 0 || entry_index < entries->length - 1)
        {
          printf("\n");
        }

        printf(PRINT_COLOR_RED
               "  [%d] Delete from This Entry\n"
               "\n"
               "  [X] Exit\n" PRINT_COLOR_RESET
               "\n"
               " > ",
               entry_index + 1);

        get_string_input(chosen_action_id, sizeof chosen_action_id);

        printf("\n");

        if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_index > 0)
        {
          is_valid_action_id = true;
          entry_index--;
        }
        else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                 entry_index < entries->length - 1)
        {
          is_valid_action_id = true;
          entry_index++;
        }
        else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'X')
        {
          is_valid_action_id = true;
          is_exiting = true;
        }
        else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_index + 1)
        {
          is_valid_action_id = true;
          is_deleting = true;
          is_exiting = true;
        }
        else
        {
          is_valid_action_id = false;

          print_error_message(INVALID_ACTION_ID);
        }
      } while (!is_valid_action_id);
    }

    printf("%d\n", is_deleting);

    if (is_deleting)
    {
      entry = &entries->values[entry_index];

      do
      {
        print_entry(entry);

        do
        {
          printf("\n");

          printf(PRINT_COLOR_RED);

          for (translation_index = 0; translation_index < entry->translations_amount; translation_index++)
          {
            printf("  [%d] Delete This Translation\n", translation_index + 1);
          }

          printf(
            "\n"
            "  [X] Exit\n" PRINT_COLOR_RESET
            "\n"
            " > ");

          get_string_input(chosen_action_id, sizeof chosen_action_id);

          printf("\n");

          if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'X')
          {
            is_valid_action_id = true;
            is_deleting = false;
            is_exiting = true;
          }
          else if (sscanf(chosen_action_id, "%d", &chosen_translation_id) == 1 && chosen_translation_id > 0 &&
                   chosen_translation_id <= entry->translations_amount)
          {
            is_valid_action_id = true;
            is_deleting = true;
            translation_index = chosen_translation_id - 1;
            is_exiting = false;
          }
          else
          {
            is_valid_action_id = false;

            print_error_message(INVALID_ACTION_ID);
          }
        } while (!is_valid_action_id);

        if (is_deleting)
        {
          if (entry->translations_amount > 1)
          {
            entry->translations[translation_index] = entry->translations[--entry->translations_amount];

            sort_entries(entries);
            sort_translations(entries);

            printf(PRINT_COLOR_RED "Deleted the translation from the entry!" PRINT_COLOR_RESET "\n");

            printf("\n");
          }
          else
          {
            entries->values[entry_index] = entries->values[--entries->length];

            sort_entries(entries);

            printf(PRINT_COLOR_RED "Deleted the entry from the stored list!" PRINT_COLOR_RESET "\n");

            is_exiting = true;
          }
        }
      } while (!is_exiting);
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Displays the entries by printing them entry-per-entry to `stdout.
 * @param[in] entries The entries to display.
 */
void
display_entries(EntryList* entries)
{
  bool is_exiting = false;
  bool is_valid_action_id;
  int index = 0;
  char chosen_action_id;

  if (entries->length > 0)
  {
    while (!is_exiting)
    {
      printf(" Entry ID: %d\n", index + 1);

      print_entry(&entries->values[index]);

      do
      {
        printf("\n");

        if (index > 0)
        {
          printf("  [P] <-- Previous\n");
        }

        if (index < entries->length - 1)
        {
          printf("  [N] --> Next\n");
        }

        if (index > 0 || index < entries->length - 1)
        {
          printf("\n");
        }

        printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                               "\n"
                               " > ");

        chosen_action_id = toupper(get_character_input());

        printf("\n");

        if (chosen_action_id == 'P' && index > 0)
        {
          is_valid_action_id = true;
          index--;
        }
        else if (chosen_action_id == 'N' && index < entries->length - 1)
        {
          is_valid_action_id = true;
          index++;
        }
        else if (chosen_action_id == 'X')
        {
          is_valid_action_id = true;
          is_exiting = true;
        }
        else
        {
          is_valid_action_id = false;

          print_error_message(INVALID_ACTION_ID);
        }
      } while (!is_valid_action_id);
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Searches for the entries containing a specific word and displays them.
 * @param[in] entries The entries to search through.
 */
void
search_word(EntryList* entries)
{
  Translation translation;
  int entries_amount;
  bool is_exiting = false;
  int entry_index;
  int entry_count = 1;
  char chosen_action_id;
  bool is_valid_action_id;

  strcpy(translation.language, "");

  if (entries->length > 0)
  {
    printf("Input the word to search entries for " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
           ": ");

    get_string_input(translation.word, MAXIMUM_WORD_LENGTH);

    printf("\n");

    if ((entries_amount = has_entry(&translation, entries)))
    {
      while (!is_exiting)
      {
        entry_index = get_entry_index(&translation, entries, entry_count);

        printf(" Entry ID: %d\n", entry_index + 1);

        print_entry(&entries->values[entry_index]);

        do
        {
          printf("\n");

          if (entry_count > 1)
          {
            printf("  [P] <-- Previous\n");
          }

          if (entry_count < entries_amount)
          {
            printf("  [N] --> Next\n");
          }

          if (entry_count > 1 || entry_count < entries_amount)
          {
            printf("\n");
          }

          printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                                 "\n"
                                 " > ");

          chosen_action_id = toupper(get_character_input());

          printf("\n");

          if (chosen_action_id == 'P' && entry_count > 1)
          {
            is_valid_action_id = true;
            entry_count--;
          }
          else if (chosen_action_id == 'N' && entry_count < entries_amount)
          {
            is_valid_action_id = true;
            entry_count++;
          }
          else if (chosen_action_id == 'X')
          {
            is_valid_action_id = true;
            is_exiting = true;
          }
          else
          {
            is_valid_action_id = false;

            print_error_message(INVALID_ACTION_ID);
          }
        } while (!is_valid_action_id);
      }
    }
    else
    {
      print_warning_message(NO_ENTRIES_WITH_WORD);
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Searches for the entries containing a specific translation and displays them.
 * @param[in] entries The entries to search through.
 */
void
search_translation(EntryList* entries)
{
  Translation translation;
  int entries_amount;
  bool is_exiting = false;
  int entry_index;
  int entry_count = 1;
  char chosen_action_id = 1;
  bool is_valid_action_id;

  if (entries->length > 0)
  {
    printf("Input the language of the translation to search entries for " PRINT_COLOR_YELLOW
           "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

    get_string_input(translation.language, MAXIMUM_LANGUAGE_LENGTH);

    printf("Input the translation to search entries for " PRINT_COLOR_YELLOW
           "(maximum of 20 characters)" PRINT_COLOR_RESET ": ");

    get_string_input(translation.word, MAXIMUM_WORD_LENGTH);

    printf("\n");

    if ((entries_amount = has_entry(&translation, entries)))
    {
      while (!is_exiting)
      {
        entry_index = get_entry_index(&translation, entries, entry_count);

        printf(" Entry ID: %d\n", entry_index + 1);

        print_entry(&entries->values[entry_index]);

        do
        {
          printf("\n");

          if (entry_count > 1)
          {
            printf("  [P] <-- Previous\n");
          }

          if (entry_count < entries_amount)
          {
            printf("  [N] --> Next\n");
          }

          if (entry_count > 1 || entry_count < entries_amount)
          {
            printf("\n");
          }

          printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                                 "\n"
                                 " > ");

          chosen_action_id = toupper(get_character_input());

          printf("\n");

          if (chosen_action_id == 'P' && entry_count > 1)
          {
            is_valid_action_id = true;
            entry_count--;
          }
          else if (chosen_action_id == 'N' && entry_count < entries_amount)
          {
            is_valid_action_id = true;
            entry_count++;
          }
          else if (chosen_action_id == 'X')
          {
            is_valid_action_id = true;
            is_exiting = true;
          }
          else
          {
            is_valid_action_id = false;

            print_error_message(INVALID_ACTION_ID);
          }
        } while (!is_valid_action_id);
      }
    }
    else
    {
      print_warning_message(NO_ENTRIES_WITH_TRANSLATION);
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Exports the stored entries into a new or overwritten text file.
 * @param[in] entries The entries to export.
 * @remarks The user will be asked to input the name of the text file.
 */
void
export_entries(EntryList* entries)
{
  String30 filename;
  FILE* output_file;
  int entry_index;
  int translation_index;
  Translation* translation;

  if (entries->length > 0)
  {
    printf("Input your preferred name for the output file " PRINT_COLOR_YELLOW
           "(maximum of 30 characters)" PRINT_COLOR_RESET ": ");

    get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

    output_file = fopen(strcat(filename, FILE_EXTENSION), "w");

    printf("\n");

    if (output_file != NULL)
    {
      for (entry_index = 0; entry_index < entries->length; entry_index++)
      {
        for (translation_index = 0; translation_index < entries->values[entry_index].translations_amount;
             translation_index++)
        {
          translation = &entries->values[entry_index].translations[translation_index];

          fprintf(output_file, "%s: %s\n", translation->language, translation->word);
        }

        fprintf(output_file, "\n");
      }

      fclose(output_file);

      printf(PRINT_COLOR_GREEN "Exported the entries into the file `%s`!" PRINT_COLOR_RESET "\n", filename);
    }
    else
    {
      print_error_message(FILE_CREATION_FAILED);
    }
  }
  else
  {
    print_error_message(NO_ENTRIES_PRESENT);
  }
}

/**
 * @brief Imports the entries stored in a text file into the stored entries list.
 * @param[in,out] entries The entries to import into.
 * @param is_data_management Whether this function is called from the data management menu.
 * @remarks The user will be asked to input the name of the text file.
 */
void
import_entries(EntryList* entries, bool is_data_management)
{
  String30 filename;
  FILE* input_file;
  Entry entry;
  bool is_finished_reading;
  char input_buff[43];
  Translation translation;
  bool is_originally_empty_list = entries->length == 0;
  bool should_add_entry;

  printf("%s" PRINT_COLOR_YELLOW "(maximum of 30 characters)" PRINT_COLOR_RESET ": ",
         is_data_management ? "Input the name of the file containing the entries "
                            : "Input the name of the file containing the translation data ");

  get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

  input_file = fopen(strcat(filename, FILE_EXTENSION), "r");

  if (input_file != NULL)
  {
    do
    {
      entry.translations_amount = 0;

      while (!(is_finished_reading = fgets(input_buff, sizeof input_buff, input_file) == NULL) &&
             strcmp(input_buff, "\n") != 0 && strcmp(input_buff, "\r\n") != 0)
      {
        sscanf(input_buff, "%20s %20s", translation.language, translation.word);

        if (translation.language[strlen(translation.language) - 1] == ':')
        {
          translation.language[strlen(translation.language) - 1] = '\0';
        }

        entry.translations[entry.translations_amount] = translation;
        entry.translations_amount++;
      }

      if (!is_finished_reading)
      {
        if (!is_originally_empty_list)
        {
          printf("\n");

          print_entry(&entry);

          printf("\n");

          printf("Add this entry? " PRINT_COLOR_YELLOW "([Y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

          should_add_entry = get_boolean_input();
        }
        else
        {
          should_add_entry = true;
        }

        if (should_add_entry)
        {
          entries->values[entries->length++] = entry;

          if (!is_originally_empty_list)
          {
            printf("\n");

            printf(PRINT_COLOR_GREEN "Added the entry into the stored list!" PRINT_COLOR_RESET "\n");
          }
        }
      }
    } while (!is_finished_reading);

    fclose(input_file);

    if (is_originally_empty_list)
    {
      printf("\n");

      printf(PRINT_COLOR_GREEN "Added the entries into the stored list!" PRINT_COLOR_RESET "\n");
    }

    sort_entries(entries);
    sort_translations(entries);
  }
  else
  {
    printf("\n");

    print_error_message(FILE_READING_FAILED);
  }
}
