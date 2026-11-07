/*
 * words.c - the word list and the words.txt file
 * Part 3 of the Hangman program (Word List)
 * Owner: ____________________ (Documentation Lead)
 */

#include "hangman.h"

/* loadWords: reads words.txt into the words array and returns how
   many words it loaded (0 if the file is missing).
   KEY IDEA: words[][WORD_SIZE] is a 2-D char array: each row holds
   one word. fopen returns NULL when a file can't be opened. */
int loadWords(char words[][WORD_SIZE]) {
    FILE *file;
    int count = 0;

    file = fopen(WORDS_FILE, "r");
    if (file == NULL) {
        printf("Could not open %s. Add words with option 2.\n", WORDS_FILE);
        return 0;
    }

    /* fscanf returns 1 each time it reads a word, and stops at the end of the file */
    while (count < MAX_WORDS && fscanf(file, "%20s", words[count]) == 1) {
        if (strlen(words[count]) >= MIN_LETTERS && isAllLetters(words[count])) {
            toLowerWord(words[count]);
            count++;                    /* keep this word */
        } else {
            printf("  Skipping \"%s\" in %s (needs %d-20 letters).\n",
                   words[count], WORDS_FILE, MIN_LETTERS);
        }
    }

    fclose(file);
    printf("Words loaded from %s: %d\n", WORDS_FILE, count);
    return count;
}

/* saveWords: writes the word list to words.txt, one word per line.
   KEY IDEA: "w" mode creates the file, or erases it if it exists.
   fprintf works like printf but writes into the file. */
void saveWords(char words[][WORD_SIZE], int wordCount) {
    FILE *file;
    int i;

    file = fopen(WORDS_FILE, "w");
    if (file == NULL) {
        printf("Error: could not save %s.\n", WORDS_FILE);
        return;
    }
    for (i = 0; i < wordCount; i++) {
        fprintf(file, "%s\n", words[i]);
    }
    fclose(file);
    printf("Words saved to %s: %d\n", WORDS_FILE, wordCount);
}

/* addWord: asks for a new word and adds it to the end of the list.
   KEY IDEA (pass-by-reference): wordCount points to main's counter,
   so (*wordCount)++ adds 1 to main's variable, not to a copy. */
void addWord(char words[][WORD_SIZE], int *wordCount) {
    char newWord[WORD_SIZE];

    if (*wordCount == MAX_WORDS) {
        printf("The word list is full (%d words).\n", MAX_WORDS);
        return;
    }

    readWord("New word: ", newWord);
    toLowerWord(newWord);

    if (strlen(newWord) < MIN_LETTERS) {
        printf("  Rejected: words need at least %d letters.\n", MIN_LETTERS);
    } else if (wordExists(words, *wordCount, newWord)) {
        printf("  Rejected: \"%s\" is already in the list.\n", newWord);
    } else {
        strcpy(words[*wordCount], newWord);     /* copy into the next empty row */
        (*wordCount)++;
        printf("  Added \"%s\". Words in list: %d\n", newWord, *wordCount);
    }
}

/* showWords: prints the word list, four words per line. */
void showWords(char words[][WORD_SIZE], int wordCount) {
    int i;

    if (wordCount == 0) {
        printf("The word list is empty.\n");
        return;
    }

    printf("\nWords in list: %d\n", wordCount);
    for (i = 0; i < wordCount; i++) {
        printf("  %-14s", words[i]);    /* %-14s: left-aligned in 14 spaces */
        if ((i + 1) % 4 == 0) {
            printf("\n");
        }
    }
    if (wordCount % 4 != 0) {
        printf("\n");
    }
}

/* wordExists: returns 1 if word is already in the list, 0 if not.
   strcmp returns 0 when two strings match exactly. */
int wordExists(char words[][WORD_SIZE], int wordCount, char word[]) {
    int i;

    for (i = 0; i < wordCount; i++) {
        if (strcmp(words[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}
