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

#include "simple_translator/data_management.h"

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
has_entry(Translation *translation, EntryList *entries)
{
    int entry_idx;
    Entry *entry;
    bool is_containing_translation;
    int translation_idx;
    Translation *entry_translation;
    int entry_cnt = 0;

    for (entry_idx = 0; entry_idx < entries->length; entry_idx++)
    {
        entry = &entries->values[entry_idx];
        is_containing_translation = false;
        translation_idx = 0;

        while (!is_containing_translation && translation_idx < entry->translations_amount)
        {
            entry_translation = &entry->translations[translation_idx];

            if ((strlen(translation->language) == 0 && strcmp(entry_translation->word, translation->word) == 0) ||
                (strlen(translation->language) > 0 && strcmp(entry_translation->language, translation->language) == 0 &&
                 strcmp(entry_translation->word, translation->word) == 0))
            {
                is_containing_translation = true;
                entry_cnt++;
            }
            else
            {
                translation_idx++;
            }
        }
    }

    return entry_cnt;
}

/**
 * @brief Gets the index of the nth entry containing the translation.
 * @param[in] translation The translation to get the index of the entry of. If the language of the translation is empty,
 * the language will be ignored.
 * @param[in] entries The entries to get from.
 * @param nth The position in the sequence of indexes to get.
 * @return The index of the translation, or `-1` if it doesn’t exist.
 */
int
get_entry_index(Translation *translation, EntryList *entries, int nth)
{
    bool is_existing_entry = false;
    int entry_idx = 0;
    Entry *entry;
    bool is_containing_translation;
    int translation_idx;
    Translation *entry_translation;
    int entry_cnt = 0;

    while (!is_existing_entry && entry_idx < entries->length)
    {
        entry = &entries->values[entry_idx];
        is_containing_translation = false;
        translation_idx = 0;

        while (!is_containing_translation && translation_idx < entry->translations_amount)
        {
            entry_translation = &entry->translations[translation_idx];

            if ((strlen(translation->language) == 0 && strcmp(entry_translation->word, translation->word) == 0) ||
                (strlen(translation->language) > 0 && strcmp(entry_translation->language, translation->language) == 0 &&
                 strcmp(entry_translation->word, translation->word) == 0))
            {
                is_containing_translation = true;
                entry_cnt++;
            }
            else
            {
                translation_idx++;
            }
        }

        if (entry_cnt == nth)
        {
            is_existing_entry = true;
        }
        else
        {
            entry_idx++;
        }
    }

    if (!is_existing_entry)
    {
        return -1;
    }

    return entry_idx;
}

/**
 * @brief Gets the index of the translation in the specific language.
 * @param lang The language of the translation to get the index of.
 * @param entry The entry to get from.
 * @return The index of the translation, or `-1` if it doesn’t exist.
 */
int
get_translation_index(String20 lang, Entry *entry)
{
    bool is_containing_lang = false;
    int idx = 0;

    while (!is_containing_lang && idx < entry->translations_amount)
    {
        if (strcmp(entry->translations[idx].language, lang) == 0)
        {
            is_containing_lang = true;
        }
        else
        {
            idx++;
        }
    }

    if (!is_containing_lang)
    {
        return -1;
    }

    return idx;
}

/**
 * @brief Sorts the entries by alphabetical order based on their English translation.
 * @param[in,out] entries The entries to sort.
 */
void
sort_entries(EntryList *entries)
{
    int entry_idx;
    int other_entry_idx;
    Entry entry;
    String20 sorting_lang = "English";
    int entry_english_idx;
    Entry other_entry;
    int other_entry_english_idx;
    Entry temp;

    for (entry_idx = 0; entry_idx < entries->length - 1; entry_idx++)
    {
        for (other_entry_idx = entry_idx + 1; other_entry_idx < entries->length; other_entry_idx++)
        {
            entry = entries->values[entry_idx];
            entry_english_idx = get_translation_index(sorting_lang, &entry);
            other_entry = entries->values[other_entry_idx];
            other_entry_english_idx = get_translation_index(sorting_lang, &other_entry);

            if ((entry_english_idx >= 0 && other_entry_english_idx >= 0 &&
                 strcmp(entry.translations[entry_english_idx].word,
                        other_entry.translations[other_entry_english_idx].word) > 0) ||
                (entry_english_idx == -1 && other_entry_english_idx >= 0))
            {
                temp = entry;
                entries->values[entry_idx] = other_entry;
                entries->values[other_entry_idx] = temp;
            }
        }
    }
}

/**
 * @brief Sorts the translations of the entries by alphabetical order based on their language.
 * @param[in,out] entries The entries to sort the translations of.
 */
void
sort_translations(EntryList *entries)
{
    int entry_idx;
    Entry *entry;
    int translation_idx;
    int other_translation_idx;
    Translation translation;
    Translation other_translation;
    Translation temp;

    for (entry_idx = 0; entry_idx < entries->length; entry_idx++)
    {
        entry = &entries->values[entry_idx];

        if (entry->translations_amount > 1)
        {
            for (translation_idx = 0; translation_idx < entry->translations_amount - 1; translation_idx++)
            {
                for (other_translation_idx = translation_idx + 1; other_translation_idx < entry->translations_amount;
                     other_translation_idx++)
                {
                    translation = entry->translations[translation_idx];
                    other_translation = entry->translations[other_translation_idx];

                    if (strcmp(translation.language, other_translation.language) > 0)
                    {
                        temp = translation;
                        entry->translations[translation_idx] = other_translation;
                        entry->translations[other_translation_idx] = temp;
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
print_entry(Entry *entry)
{
    int idx;

    printf(
        "|--------------------------------------------------|\n"
        "| ID |       Language       |     Translation      |\n"
        "|--------------------------------------------------|\n");

    for (idx = 0; idx < entry->translations_amount; idx++)
    {
        printf("| %-2d | %-20s | %-20s |\n", idx + 1, entry->translations[idx].language, entry->translations[idx].word);
    }

    printf("|--------------------------------------------------|\n");
}

/**
 * @brief Adds an entry or multiple entries by asking the user to input their first translations.
 * @param[in,out] entries The entries to add to.
 */
void
add_entries(EntryList *entries)
{
    bool is_exiting = false;
    Entry entry;
    entry.translations_amount = 1;
    int entries_amt;
    bool has_confirmed;
    int entry_idx;
    int entry_cnt;
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

            if ((entries_amt = has_entry(&entry.translations[0], entries)))
            {
                printf("\n");

                entry_cnt = 1;

                do
                {
                    entry_idx = get_entry_index(&entry.translations[0], entries, entry_cnt);

                    printf(" Entry ID: %d\n", entry_idx + 1);

                    print_entry(&entries->values[entry_idx]);

                    do
                    {
                        printf("\n");

                        if (entry_cnt > 1)
                        {
                            printf("  [P] <-- Previous\n");
                        }

                        if (entry_cnt < entries_amt)
                        {
                            printf("  [N] --> Next\n");
                        }

                        printf(PRINT_COLOR_GREEN "  [Y] A New Entry\n" PRINT_COLOR_RED
                                                 "  [X] Not a New Entry\n" PRINT_COLOR_RESET
                                                 "\n"
                                                 " > ");

                        chosen_action_id = get_character_input();

                        if (toupper(chosen_action_id) == 'P' && entry_cnt > 1)
                        {
                            is_valid_action_id = true;
                            entry_cnt--;
                            has_confirmed = false;
                        }
                        else if (toupper(chosen_action_id) == 'N' && entry_cnt < entries_amt)
                        {
                            is_valid_action_id = true;
                            entry_cnt++;
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
add_translations(EntryList *entries)
{
    bool is_exiting = false;
    bool is_different_entry = true;
    Translation translation;
    int entries_amt;
    bool has_picked_entry;
    int entry_idx;
    int entry_cnt = 1;
    bool is_valid_action_id;
    char chosen_action_id[4];
    int chosen_entry_id;
    Entry *entry;
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

        if ((entries_amt = has_entry(&translation, entries)))
        {
            if (entries_amt > 1)
            {
                do
                {
                    entry_idx = get_entry_index(&translation, entries, entry_cnt);

                    printf(" Entry ID: %d\n", entry_idx + 1);

                    print_entry(&entries->values[entry_idx]);

                    do
                    {
                        printf("\n");

                        if (entry_cnt > 1)
                        {
                            printf("  [P] <-- Previous\n");
                        }

                        if (entry_cnt < entries_amt)
                        {
                            printf("  [N] --> Next\n");
                        }

                        printf(
                            "  [%d] Add to This Entry\n"
                            "\n"
                            " > ",
                            entry_idx);

                        get_string_input(chosen_action_id, sizeof chosen_action_id);

                        printf("\n");

                        if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_cnt > 1)
                        {
                            is_valid_action_id = true;
                            entry_cnt--;
                            has_picked_entry = false;
                        }
                        else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                                 entry_cnt < entries_amt)
                        {
                            is_valid_action_id = true;
                            entry_cnt++;
                            has_picked_entry = false;
                        }
                        else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_idx)
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
                entry_idx = get_entry_index(&translation, entries, 1);
            }

            entry = &entries->values[entry_idx];

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
                        printf("Add to the same entry? " PRINT_COLOR_YELLOW "([y]es / [ANY] no)" PRINT_COLOR_RESET
                               ": ");

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
delete_entry(EntryList *entries)
{
    bool is_exiting = false;
    int entry_idx = 0;
    bool is_valid_action_id;
    char chosen_action_id[4];
    int chosen_entry_id;
    bool is_deleting = false;

    if (entries->length > 0)
    {
        while (!is_exiting)
        {
            printf(" Entry ID: %d\n", entry_idx + 1);

            print_entry(&entries->values[entry_idx]);

            do
            {
                printf("\n");

                if (entry_idx > 0)
                {
                    printf("  [P] <-- Previous\n");
                }

                if (entry_idx < entries->length - 1)
                {
                    printf("  [N] --> Next\n");
                }

                if (entry_idx > 0 || entry_idx < entries->length - 1)
                {
                    printf("\n");
                }

                printf(PRINT_COLOR_RED
                       "  [%d] Delete This Entry\n"
                       "\n"
                       "  [X] Exit\n" PRINT_COLOR_RESET
                       "\n"
                       " > ",
                       entry_idx + 1);

                get_string_input(chosen_action_id, sizeof chosen_action_id);

                printf("\n");

                if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_idx > 0)
                {
                    is_valid_action_id = true;
                    entry_idx--;
                }
                else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                         entry_idx < entries->length - 1)
                {
                    is_valid_action_id = true;
                    entry_idx++;
                }
                else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'X')
                {
                    is_valid_action_id = true;
                    is_exiting = true;
                }
                else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_idx + 1)
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
            entries->values[entry_idx] = entries->values[--entries->length];

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
delete_translations(EntryList *entries)
{
    bool is_exiting = false;
    int entry_idx = 0;
    char chosen_action_id[4];
    bool is_valid_action_id;
    int chosen_entry_id;
    bool is_deleting = false;
    Entry *entry;
    int translation_idx;
    int chosen_translation_id;

    if (entries->length > 0)
    {
        while (!is_exiting)
        {
            printf(" Entry ID: %d\n", entry_idx + 1);

            print_entry(&entries->values[entry_idx]);

            do
            {
                printf("\n");

                if (entry_idx > 0)
                {
                    printf("  [P] <-- Previous\n");
                }

                if (entry_idx < entries->length - 1)
                {
                    printf("  [N] --> Next\n");
                }

                if (entry_idx > 0 || entry_idx < entries->length - 1)
                {
                    printf("\n");
                }

                printf(PRINT_COLOR_RED
                       "  [%d] Delete from This Entry\n"
                       "\n"
                       "  [X] Exit\n" PRINT_COLOR_RESET
                       "\n"
                       " > ",
                       entry_idx + 1);

                get_string_input(chosen_action_id, sizeof chosen_action_id);

                printf("\n");

                if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'P' && entry_idx > 0)
                {
                    is_valid_action_id = true;
                    entry_idx--;
                }
                else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'N' &&
                         entry_idx < entries->length - 1)
                {
                    is_valid_action_id = true;
                    entry_idx++;
                }
                else if (strlen(chosen_action_id) == 1 && toupper(chosen_action_id[0]) == 'X')
                {
                    is_valid_action_id = true;
                    is_exiting = true;
                }
                else if (sscanf(chosen_action_id, "%d", &chosen_entry_id) == 1 && chosen_entry_id == entry_idx + 1)
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
            entry = &entries->values[entry_idx];

            do
            {
                print_entry(entry);

                do
                {
                    printf("\n");

                    printf(PRINT_COLOR_RED);

                    for (translation_idx = 0; translation_idx < entry->translations_amount; translation_idx++)
                    {
                        printf("  [%d] Delete This Translation\n", translation_idx + 1);
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
                        translation_idx = chosen_translation_id - 1;
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
                        entry->translations[translation_idx] = entry->translations[--entry->translations_amount];

                        sort_entries(entries);
                        sort_translations(entries);

                        printf(PRINT_COLOR_RED "Deleted the translation from the entry!" PRINT_COLOR_RESET "\n");

                        printf("\n");
                    }
                    else
                    {
                        entries->values[entry_idx] = entries->values[--entries->length];

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
display_entries(EntryList *entries)
{
    bool is_exiting = false;
    bool is_valid_action_id;
    int idx = 0;
    char chosen_action_id;

    if (entries->length > 0)
    {
        while (!is_exiting)
        {
            printf(" Entry ID: %d\n", idx + 1);

            print_entry(&entries->values[idx]);

            do
            {
                printf("\n");

                if (idx > 0)
                {
                    printf("  [P] <-- Previous\n");
                }

                if (idx < entries->length - 1)
                {
                    printf("  [N] --> Next\n");
                }

                if (idx > 0 || idx < entries->length - 1)
                {
                    printf("\n");
                }

                printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                                       "\n"
                                       " > ");

                chosen_action_id = toupper(get_character_input());

                printf("\n");

                if (chosen_action_id == 'P' && idx > 0)
                {
                    is_valid_action_id = true;
                    idx--;
                }
                else if (chosen_action_id == 'N' && idx < entries->length - 1)
                {
                    is_valid_action_id = true;
                    idx++;
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
search_word(EntryList *entries)
{
    Translation translation;
    int entries_amt;
    bool is_exiting = false;
    int entry_idx;
    int entry_cnt = 1;
    char chosen_action_id;
    bool is_valid_action_id;

    strcpy(translation.language, "");

    if (entries->length > 0)
    {
        printf("Input the word to search entries for " PRINT_COLOR_YELLOW "(maximum of 20 characters)" PRINT_COLOR_RESET
               ": ");

        get_string_input(translation.word, MAXIMUM_WORD_LENGTH);

        printf("\n");

        if ((entries_amt = has_entry(&translation, entries)))
        {
            while (!is_exiting)
            {
                entry_idx = get_entry_index(&translation, entries, entry_cnt);

                printf(" Entry ID: %d\n", entry_idx + 1);

                print_entry(&entries->values[entry_idx]);

                do
                {
                    printf("\n");

                    if (entry_cnt > 1)
                    {
                        printf("  [P] <-- Previous\n");
                    }

                    if (entry_cnt < entries_amt)
                    {
                        printf("  [N] --> Next\n");
                    }

                    if (entry_cnt > 1 || entry_cnt < entries_amt)
                    {
                        printf("\n");
                    }

                    printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                                           "\n"
                                           " > ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    if (chosen_action_id == 'P' && entry_cnt > 1)
                    {
                        is_valid_action_id = true;
                        entry_cnt--;
                    }
                    else if (chosen_action_id == 'N' && entry_cnt < entries_amt)
                    {
                        is_valid_action_id = true;
                        entry_cnt++;
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
search_translation(EntryList *entries)
{
    Translation translation;
    int entries_amt;
    bool is_exiting = false;
    int entry_idx;
    int entry_cnt = 1;
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

        if ((entries_amt = has_entry(&translation, entries)))
        {
            while (!is_exiting)
            {
                entry_idx = get_entry_index(&translation, entries, entry_cnt);

                printf(" Entry ID: %d\n", entry_idx + 1);

                print_entry(&entries->values[entry_idx]);

                do
                {
                    printf("\n");

                    if (entry_cnt > 1)
                    {
                        printf("  [P] <-- Previous\n");
                    }

                    if (entry_cnt < entries_amt)
                    {
                        printf("  [N] --> Next\n");
                    }

                    if (entry_cnt > 1 || entry_cnt < entries_amt)
                    {
                        printf("\n");
                    }

                    printf(PRINT_COLOR_RED "  [X] Exit\n" PRINT_COLOR_RESET
                                           "\n"
                                           " > ");

                    chosen_action_id = toupper(get_character_input());

                    printf("\n");

                    if (chosen_action_id == 'P' && entry_cnt > 1)
                    {
                        is_valid_action_id = true;
                        entry_cnt--;
                    }
                    else if (chosen_action_id == 'N' && entry_cnt < entries_amt)
                    {
                        is_valid_action_id = true;
                        entry_cnt++;
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
export_entries(EntryList *entries)
{
    String30 filename;
    FILE *out_file;
    int entry_idx;
    int translation_idx;
    Translation *translation;

    if (entries->length > 0)
    {
        printf("Input your preferred name for the output file " PRINT_COLOR_YELLOW
               "(maximum of 30 characters)" PRINT_COLOR_RESET ": ");

        get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

        out_file = fopen(strcat(filename, FILE_EXTENSION), "w");

        printf("\n");

        if (out_file != NULL)
        {
            for (entry_idx = 0; entry_idx < entries->length; entry_idx++)
            {
                for (translation_idx = 0; translation_idx < entries->values[entry_idx].translations_amount;
                     translation_idx++)
                {
                    translation = &entries->values[entry_idx].translations[translation_idx];

                    fprintf(out_file, "%s: %s\n", translation->language, translation->word);
                }

                fprintf(out_file, "\n");
            }

            fclose(out_file);

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
 * @param in_data_management Whether this function is called from the data management menu.
 * @remarks The user will be asked to input the name of the text file.
 */
void
import_entries(EntryList *entries, bool in_data_management)
{
    String30 filename;
    FILE *in_file;
    Entry entry;
    bool is_finished_reading;
    char in_buff[43];
    Translation translation;
    bool is_originally_empty_list = entries->length == 0;
    bool should_add_entry;

    printf("%s" PRINT_COLOR_YELLOW "(maximum of 30 characters)" PRINT_COLOR_RESET ": ",
           in_data_management ? "Input the name of the file containing the entries "
                              : "Input the name of the file containing the translation data ");

    get_string_input(filename, MAXIMUM_FILENAME_LENGTH);

    in_file = fopen(strcat(filename, FILE_EXTENSION), "r");

    if (in_file != NULL)
    {
        do
        {
            entry.translations_amount = 0;

            while (!(is_finished_reading = fgets(in_buff, sizeof in_buff, in_file) == NULL) &&
                   strcmp(in_buff, "\n") != 0 && strcmp(in_buff, "\r\n") != 0)
            {
                sscanf(in_buff, "%20s %20s", translation.language, translation.word);

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

        fclose(in_file);

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
