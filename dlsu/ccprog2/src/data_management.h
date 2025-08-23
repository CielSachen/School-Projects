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

#ifndef DATA_MANAGEMENT_H_
#define DATA_MANAGEMENT_H_

#include <stdbool.h>

#include "io.h"

/** @brief The maximum accepted length of a language's name. */
#define MAXIMUM_LANGUAGE_LENGTH 21
/** @brief The maximum accepted length of a word. */
#define MAXIMUM_WORD_LENGTH 21

/** @brief The maximum number of entries. */
#define MAXIMUM_ENTRIES_LENGTH 150
/** @brief The maximum number of translations an entry can have. */
#define MAXIMUM_ENTRY_TRANSLATIONS 10

/** @brief A word translation. */
typedef struct Translation
{
  /** @brief The language of the translation. */
  String20 language;
  /** @brief The translated word. */
  String20 word;
} Translation;
/** @brief A translation entry. */
typedef struct Entry
{
  /** @brief The word translations. */
  Translation translations[MAXIMUM_ENTRY_TRANSLATIONS];
  /** @brief The actual length of `translations`. */
  int translations_amount;
} Entry;
/** @brief An array of entries with an integer member tracking the actual length. */
typedef struct EntryList
{
  /** @brief The entries. */
  Entry values[MAXIMUM_ENTRIES_LENGTH];
  /** @brief The actual length of `values`. */
  int length;
} EntryList;

/**
 * @brief Checks if a translation already has an entry containing it.
 * @param[in] translation The translation to check. If the language of the translation is empty, the language will be
 * ignored.
 * @param[in] entries The entries to check against.
 * @return The amount entries containing the translation.
 */
int has_entry(Translation* translation, EntryList* entries);

/**
 * @brief Gets the index of the nth entry containing the translation.
 * @param[in] translation The translation to get the index of the entry of. If the language of the translation is empty,
 * the language will be ignored.
 * @param[in] entries The entries to get from.
 * @param nth The position in the sequence of indexes to get.
 * @return The index of the translation, or `-1` if it does not exist.
 */
int get_entry_index(Translation* translation, EntryList* entries, int nth);

/**
 * @brief Gets the index of the translation in the specific language.
 * @param language The language of the translation to get the index of.
 * @param entry The entry to get from.
 * @return The index of the translation, or `-1` if it does not exist.
 */
int get_translation_index(String20 language, Entry* entry);

/**
 * @brief Adds an entry or multiple entries by asking the user to input their first translations.
 * @param[in,out] entries The entries to add to.
 */
void add_entries(EntryList* entries);

/**
 * @brief Adds a translation or multiple translations to an entry or multiple entries.
 * @param[in,out] entries The entries to add translations to.
 * @remarks The user will be asked to input a translation from the entry to add to.
 */
void add_translations(EntryList* entries);

/**
 * @brief Deletes an entry by moving it at the end of the list and decreasing the length.
 * @param[in,out] entries The entries to delete one of.
 */
void delete_entry(EntryList* entries);

/**
 * @brief Deletes translations from entries by moving them at the end of the lists and decreasing their lengths. Entries
 * with zero translations will be deleted.
 * @param[in,out] entries The entries to delete translations from.
 */
void delete_translations(EntryList* entries);

/**
 * @brief Displays the entries by printing them entry-per-entry to `stdout`.
 * @param[in] entries The entries to display.
 */
void display_entries(EntryList* entries);

/**
 * @brief Searches for the entries containing a specific word and displays them.
 * @param[in] entries The entries to search through.
 */
void search_word(EntryList* entries);

/**
 * @brief Searches for the entries containing a specific translation and displays them.
 * @param[in] entries The entries to search through.
 */
void search_translation(EntryList* entries);

/**
 * @brief Exports the stored entries into a new or overwritten text file.
 * @param[in] entries The entries to export.
 * @remarks The user will be asked to input the name of the text file.
 */
void export_entries(EntryList* entries);

/**
 * @brief Imports the entries stored in a text file into the stored entries list.
 * @param[in,out] entries The entries to import into.
 * @param is_data_management Whether this function is called from the data management menu.
 * @remarks The user will be asked to input the name of the text file.
 */
void import_entries(EntryList* entries, bool is_data_management);

#endif  // DATA_MANAGEMENT_H_
