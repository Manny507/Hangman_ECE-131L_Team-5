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

/* CHANGELOG #4 and CHANGELOG #5 */ 
int loadWords(char (**words)[WORD_SIZE]) 
{
    FILE *file = fopen(WORDS_FILE, "r"); //CHANGELOG #6
    //CHANGELOG #7
    if (file == NULL)
    {
        printf("Could not open %s. Add words with option 2.\n", WORDS_FILE);
        return 0;
    }

    //CHANGELOG #8
    int wordCount = 0;
    char tempWord[WORD_SIZE];

    while (fgets(tempWord, WORD_SIZE, file) != NULL)
    {
        wordCount ++;
    }

    //CHANGELOG #9
    rewind(file);

    if (wordCount == 0)
    {
        fclose(file);
        return 0;
    }
   
    *words = calloc(wordCount, sizeof(**words));
 
    if (*words == NULL)
    {
        printf("Error: Memory Allocation Failed.\n");
        fclose(file);
        return 0;
    }

    //CHANGELOG #10
    int loadedCount = 0;

    while (fgets(tempWord, WORD_SIZE, file) != NULL)
    {
        int length = strlen(tempWord);
        
        if (length > 0 && tempWord[length - 1] == '\n')
        {
            tempWord[length - 1] = '\0';
        }
    
        if (strlen(tempWord) >= MIN_LETTERS && isAllLetters(tempWord))
        {
            toLowerWord(tempWord); //CHANGELOG #21
            strcpy((*words)[loadedCount], tempWord);
            loadedCount++;
        }
    }

    fclose(file);
    printf("Words loaded from %s: %d\n", WORDS_FILE, loadedCount);
    return loadedCount;
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
//CHANGELOG #12
void addWord(char (**words)[WORD_SIZE], int *wordCount) {
    char newWord[WORD_SIZE];

    //CHANGELOG #16 REMOVED fixed MAXED WORDS RESTRICTION

    readWord("New word: ", newWord);
    toLowerWord(newWord);

    if (strlen(newWord) < MIN_LETTERS) {
        printf("  Rejected: words need at least %d letters.\n", MIN_LETTERS);
    } else if (wordExists(*words, *wordCount, newWord)) { //CHANGELOG #13
        printf("  Rejected: \"%s\" is already in the list.\n", newWord);
    } else
      {
          //CHANGELOG #15
          char (*temp)[WORD_SIZE] = realloc(*words, (*wordCount + 1) * sizeof(**words));
          if (temp == NULL)
          {
              printf("Error: Memory Allocation Failed.\n");
              return;
          }
          *words = temp;

          strcpy((*words)[*wordCount], newWord);  //CHANGELOG #14
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
