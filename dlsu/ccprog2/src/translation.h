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

#ifndef TRANSLATION_H_
#define TRANSLATION_H_

#include "data_management.h"

/** @brief The maximum accepted length of a sentence. */
#define MAXIMUM_SENTENCE_LENGTH 151

/** @brief The maximum accepted number of sentences. */
#define MAXIMUM_SENTENCES 100

/**
 * @brief Translates a sentence inputted by the user using the imported translation entries.
 * @param[in] translation_entries The imported translation entries to use.
 */
void translate_input(EntryList* entries);

/**
 * @brief Translates all sentences in a text file using the imported translation entries and exports them into a new or
 * overwritten text file.
 * @param[in] translation_entries The imported translation entries to use.
 * @remarks The user will be asked to input the name of the input and output text file.
 */
void translate_text_file(EntryList* entries);

#endif  // TRANSLATION_H_
