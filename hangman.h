/* hangman.h is our header file that contains:
 * Function prototypes, struct declarations, shared definitions, and C libraries.
 * Written by: Cesar Marquez-Garcia 
*/ 

// Libraries
#include <stdio.h> // printf, scanf, etc.
#include <stdlib.h> // rand, srand, etc.
#include <string.h> // strcpy
#include <time.h> // time 

// Game limits and global definitions
#define MAX_WORDS 50;   // Max number of words the list can hold.
#define WORD_SIZE 20   // 24 letters max plus 1 for '\0'
#define MIN_LETTERS 3  // Least amount of letters allowed for a word
#define MAX_GAMES 100  // Most games we want our history to hold
#define MAX_WRONG 6    // Max wrong guesses allowed before losing
#define WORDS_FILE "words.txt" // Name for word list file
#define SCORES_FILE "scores.txt" // Name for the score history file

// Player game record struct.
typedef struct {
    char player[WORD_SIZE]; // Player's name
    char word[WORD_SIZE]; // The word to guess
    int won; // 1 if the player won, 0 if they lost
    int wrong; // Number of wrong guesses made
    int score;  
} GameRecord;

// Function prototypes for all the functions in the game, grouped by the file where 
// they are defined.

    // Input checks (input.c)
void clearInput(void);
int  readNumber(char prompt[], int min, int max);
char readLetter(char prompt[]);
int  askYesNo(char prompt[]);
void readWord(char prompt[], char word[]);
int  isAllLetters(char text[]);
void toLowerWord(char word[]);

    // Words list management (words.c)
int loadWords(char words[][WORD_SIZE]);
void saveWords(char words[][WORD_SIZE], int wordCount);
void addWord(char words[][WORD_SIZE], int *wordCount);
int wordExists(char words[][WORD_SIZE], int wordCount, char word[]);
void showWords(char words[][WORD_SIZE], int wordCount);

    // Game rules (game.c)
int pickRandomWord(int wordCount);
void drawHangman(int wrong);
void showBoard(char revealed[], char guessed[], int wrong);
int alreadyGuessed(char guessed[], char letter);
int revealLetter(char secret[], char revealed[], char letter);
int computeScore(int wordLength, int wrong, int won);
int playRound(char secret[]);

    // Scores and reports (scores.c)
int loadScores(GameRecord history[]);                     
void saveScores(GameRecord history[], int gameCount);
void showScores(GameRecord history[], int gameCount);
void showStatistics(GameRecord history[], int gameCount);

    // Menu and game flow (main.c)
void printMenu(void);
void playGame(char words[][WORD_SIZE], int wordCount, GameRecord history[], int *gamecount);
