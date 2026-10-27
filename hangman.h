/* hangman.h is our header file that contains:
 * Function prototypes, structs declarations, shared definitions, and C libraries.
 * Written by: Cesar Marquez-Garcia 
*/

// Libraries
#include <stdio.h> // printf, scanf, etc.
#include <stdlib.h> // rand, srand, etc.
#include <string.h> // strcpy
#include <time.h> //time 

// Game limits and global definitions
#define MAX_WORDS 50   // Max number of words the list can hold.
#define WORD_SIZE 21   // 20 letters max plus 1 for the invisible '\0'
#define MIN_LETTERS 3  // Least amount of letters allowed for a word
#define MAX_GAMES 100  // Most games we want our history to hold
#define MAX_WRONG 6    // Max wrong guesses allowed before losing
#define WORDS_FILE "words.txt" // Name for word list file
#define SCORES_FILE "scores.txt" // Name for the score history file

// Structs
typedef struct {
    char player[WORD_SIZE]; // Player's name
    char word[WORD_SIZE]; // The word to guess
    int won; // 1 if the player won, 0 if they lost
    int wrong; // Number of wrong guesses made
    int score;  
} GameRecord;

