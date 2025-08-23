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

#include "translation.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "io.h"

/**
 * @brief Translates a sentence using the imported translation entries.
 * @param[in] sentence The sentence to translate.
 * @param[in] input_language The language to translate from.
 * @param[out] translated_sentence The string to store the translated sentence in.
 * @param[in] output_language The language to translate to.
 * @param[in] translation_entries The imported translation entries to use.
 */
void
translate_sentence(String150 sentence, String20 input_language, String150 translated_sentence, String20 output_language,
                   EntryList* translation_entries)
{
  char* token = strtok(sentence, " ,.!?");
  String20 words[MAXIMUM_SENTENCE_LENGTH - 1];
  int word_index = 0;
  int words_amount = 0;
  Translation temporary;
  int entries_amount;
  int entry_count;
  Entry* translation_entry;
  int translation_index;

  while (token != NULL)
  {
    strcpy(words[word_index++], token);

    words_amount++;
    token = strtok(NULL, " ,.!?");
  }

  strcpy(translated_sentence, "");

  for (word_index = 0; word_index < words_amount; word_index++)
  {
    strcpy(temporary.language, input_language);
    strcpy(temporary.word, words[word_index]);

    if ((entries_amount = has_entry(&temporary, translation_entries)))
    {
      entry_count = 1;

      do
      {
        translation_entry =
          &translation_entries->values[get_entry_index(&temporary, translation_entries, entry_count++)];
        translation_index = get_translation_index(output_language, translation_entry);
      } while (translation_index == -1 && entry_count <= entries_amount);

      if (translation_index >= 0)
      {
        strcat(translated_sentence, translation_entry->translations[translation_index].word);
      }
      else
      {
        strcat(translated_sentence, temporary.word);
      }
    }
    else
    {
      strcat(translated_sentence, temporary.word);
    }

    if (word_index < words_amount - 1)
    {
      strcat(translated_sentence, " ");
    }
  }
}

/**
 * @brief Translates a sentence inputted by the user using the imported translation entries.
 * @param[in] translation_entries The imported translation entries to use.
 */
void
translate_input(EntryList* translation_entries)
{
  String20 input_language;
  String150 input_sentence;
  String20 output_language;
  String150 translated_sentence;
  bool is_translating_more;

  printf("Input the language to translate from " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
         ": ");

  get_string_input(input_language, MAXIMUM_LANGUAGE_LENGTH);

  printf("Input the language to translate into " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
         ": ");

  get_string_input(output_language, MAXIMUM_LANGUAGE_LENGTH);

  do
  {
    printf("Input the sentence to translate " PRINT_COLOR_YELLOW "(maximum of 150 characters)" PRINT_COLOR_RESET ": ");

    get_string_input(input_sentence, MAXIMUM_SENTENCE_LENGTH);

    printf("\n");

    printf(
      "|- Original Text ----------------------------------------------------------------------------------------------------------------------------------------|\n"
      "|                                                                                                                                                        |\n"
      "| %-150s |\n"
      "|                                                                                                                                                        |\n"
      "|--------------------------------------------------------------------------------------------------------------------------------------------------------|\n",
      input_sentence);

    translate_sentence(input_sentence, input_language, translated_sentence, output_language, translation_entries);

    printf("\n");

    printf(
      "|- Translated Text --------------------------------------------------------------------------------------------------------------------------------------|\n"
      "|                                                                                                                                                        |\n"
      "| %-150s |\n"
      "|                                                                                                                                                        |\n"
      "|--------------------------------------------------------------------------------------------------------------------------------------------------------|\n",
      translated_sentence);

    printf("\n");

    printf("Translate another sentence? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET ": ");

    is_translating_more = get_boolean_input();
  } while (!is_translating_more);
}

/**
 * @brief Translates all sentences in a text file using the imported translation entries and exports them into a new or
 * overwritten text file.
 * @param[in] translation_entries The imported translation entries to use.
 * @remarks The user will be asked to input the name of the input and output text file.
 */
void
translate_text_file(EntryList* translation_entries)
{
  String20 input_language;
  String20 output_language;
  String30 filename;
  FILE* input_file;
  int character;
  int sentences_amount = 0;
  int character_index = 0;
  String150 sentences[MAXIMUM_SENTENCES];
  int sentence_index = 0;
  String150 temporary;
  FILE* output_file;

  printf("Input the language to translate from " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
         ": ");

  get_string_input(input_language, MAXIMUM_LANGUAGE_LENGTH);

  printf("Input the language to translate into " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
         ": ");

  get_string_input(output_language, MAXIMUM_LANGUAGE_LENGTH);

  printf("Input the name of the file containing the sentences " PRINT_COLOR_YELLOW
         "(maximum of 30 characters)" PRINT_COLOR_RESET ": ");

  get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

  input_file = fopen(strcat(filename, FILE_EXTENSION), "r");

  if (input_file != NULL)
  {
    while ((character = fgetc(input_file)) != EOF && sentences_amount < MAXIMUM_SENTENCES)
    {
      if (character != '.' && character != '?' && character != '!')
      {
        if (character_index > 0 || (character_index == 0 && character != ' ' && character != '\n' && character != '\r'))
        {
          sentences[sentence_index][character_index++] = character;
        }
      }
      else
      {
        sentences[sentence_index][character_index] = '\0';
        sentences_amount++;
        sentence_index++;
        character_index = 0;
      }
    }

    fclose(input_file);

    printf("\n");

    printf(
      "|- Original Text ----------------------------------------------------------------------------------------------------------------------------------------|\n");

    for (sentence_index = 0; sentence_index < sentences_amount; sentence_index++)
    {
      printf(
        "|                                                                                                                                                        |\n"
        "| %-150s |\n",
        sentences[sentence_index]);
    }

    printf(
      "|                                                                                                                                                        |\n"
      "|--------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

    for (sentence_index = 0; sentence_index < sentences_amount; sentence_index++)
    {
      strcpy(temporary, sentences[sentence_index]);

      translate_sentence(temporary, input_language, sentences[sentence_index], output_language, translation_entries);
    }

    printf("\n");

    printf(
      "|- Translated Text --------------------------------------------------------------------------------------------------------------------------------------|\n");

    for (sentence_index = 0; sentence_index < sentences_amount; sentence_index++)
    {
      printf(
        "|                                                                                                                                                        |\n"
        "| %-150s |\n",
        sentences[sentence_index]);
    }

    printf(
      "|                                                                                                                                                        |\n"
      "|--------------------------------------------------------------------------------------------------------------------------------------------------------|\n");

    printf("\n");

    printf("Input the name of the file containing the sentences " PRINT_COLOR_YELLOW
           "(maximum of 30 characters)" PRINT_COLOR_RESET ": ");

    get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

    output_file = fopen(strcat(filename, FILE_EXTENSION), "w");

    printf("\n");

    if (output_file != NULL)
    {
      for (sentence_index = 0; sentence_index < sentences_amount; sentence_index++)
      {
        fprintf(output_file, "%s\n", sentences[sentence_index]);
      }

      fclose(output_file);

      printf(PRINT_COLOR_GREEN "Exported the translated sentences into the file `%s`!" PRINT_COLOR_RESET "\n",
             filename);
    }
    else
    {
      printf("\n");

      print_error_message(FILE_READING_FAILED);
    }
  }
  else
  {
    printf("\n");

    print_error_message(FILE_READING_FAILED);
  }
}
