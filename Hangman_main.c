#include "hangman.h"
void printMenu(void){
	printf("\nWELCOME TO HANGMAN\n");
	printf(" 1. Play Hangman\n");
	printf(" 2. Add a word\n");
	printf(" 3. Show word list\n");
	printf(" 4. Score History\n");
	printf(" 5. Show stats\n");
	printf(" 6. Save words and scores\n");
	printf(" 0. Quit hanging that poor man\n");
}

void playGame(char words[][WORD_SIZE], int wordCount, GameRecord history[], int *gameCount){
	char player[WORD_SIZE];   // current player's name
	char secret[WORD_SIZE];   // the word being guessed this round
	int length;               // number of letters in the secret word
	int wrong;                // wrong guesses made this round
	int won;                  // 1 = player won, 0 = player lost
	int slot;                 // index in history where this game gets saved
	
	// Can't play with an empty word list, so bail out early
	if(wordCount == 0){
		printf("No words to play with, please add one using option 2\n");
		return;
	}
	
	// Ask for the player's name once, before the game loop starts
	// Comes from input.c file
	read_word("Player name: ", player);
	
	do{
		// Stop if history is full so we never write past the end of the array
		if(*gameCount == MAX_GAMES) {
			printf("Reached the max amount of games that can be saved (%d)\n", MAX_GAMES);
			return;
		}
		// picks a random word from the array of words and copies it into the secret variable using strcpy which came from string.h
		// pickRandomWord F-n comes from game.c as well as the decloration of 'secret'
		strcpy(secret, words[pickRandomWord(wordCount)]); 
		
		// strlen comes from the string.h header and is reading how many letters are in the string in secret
		length = strlen(secret);
		printf("\n%s started a new game, the chosen word has %d letters", player, length);
		
		// playRound F-n comes from game.c file
		// Plays one full round and returns how many guesses were wrong
		wrong = playRound(secret);
		
		// Fewer wrong guesses than the limit means the player won
		 if (wrong < MAX_WRONG) {
            won = 1;
            printf("You saved the man to be hung! The word was %s!\n", secret);
        } else {
            // Hit the wrong-guess limit, so the player lost
            won = 0;
            printf("\nYou took too many guesses and the poor man was hung! The word was %s!\n", secret);
        }
		
		 // store this game in the next empty slot of history
        
        // The number of games saved so far is also the index of the next free slot
        // (e.g., 3 games saved -> indexes 0,1,2 used -> slot 3 is free)
        slot = *gameCount;
        
        // Strings can't be assigned with =, so strcpy copies the characters
        // into this record's player and word fields
        strcpy(history[slot].player, player);
        strcpy(history[slot].word, secret);
        
        // Plain numbers can be assigned directly: win flag and wrong guess count
        history[slot].won = won;
        history[slot].wrong = wrong;
        
        // Score is calculated from the word length, wrong guesses, and win/loss
        history[slot].score = computeScore(length, wrong, won);
        
        // Increase the game count through the pointer so the caller's variable
        // updates and the next game goes in the next slot.
        // The parentheses matter: *gameCount++ would move the pointer instead.
        (*gameCount)++;
		
		printf("Score this game %d\n", history[slot].score);
	}
	//yes_or_no f-n comes from inputs.c 
	//User input is getting read with readletter f-n also located in the input.c file. It is a f-n within a function it's used in the yes_or_no f-n
	while (yes_or_no("Play Again (y/n)?: "));
}

int main(void){
	 char words[MAX_WORDS][WORD_SIZE];   /* the word list: one word per row */
    GameRecord history[MAX_GAMES];      /* every finished game */
    int wordCount;
    int gameCount;
    int choice;
	
	//This line make the program pick a different random word each time the program runs
	// srand() sets the starting point (the seed) that rand() uses to pick numbers.
	//The seed is the starting point of the algorithm that srand runs to pick a a randome number 
	// time(NULL) returns the current clock time in seconds, which is different on every run,
	// so the seed changes each time and pickRandomWord chooses different words.
	// In playGame, this line chooses the word: strcpy(secret, words[pickRandomWord(wordCount)]);
	// pickRandomWord(wordCount) returns a random index from 0 to wordCount - 1,
	// and words[...] turns that index into an actual word.
	// For that index to be random, pickRandomWord calls rand()
	// rand() repeats the same sequence unless it's seeded, and srand(time(NULL)) is what seeds it.
	//Talk to Ceasr about Ean's pickrandom f-n and wether or not it uses rand() % pickrandomWord() logic.
	srand(time(NULL));      
	 
	printf("Welcome to Hangman\n");
	wordCount = loadWords(words);
	gamecount = loadScores(history);
	
	do{ 
	printmenu();
	//Inputs are read using the read_number F-n from inputs.c and then checked
	//against a switch case to see what the user chose, functions from our different .c
	//files are then called accordingly
	choice = read_number("Choose an option: ", 0, 6); 
	
	        switch (choice) {
            case 1:
				//Comes from the games.c file
                playGame(words, wordCount, history, &gameCount);
                break;
            case 2:
				//Comes from words.c
                addWord(words, &wordCount);
                break;
            case 3:
				//Comes from words.c
                showWords(words, wordCount);
                break;
            case 4:
				//Comes from scores.c
                showScores(history, gameCount);
                break;
            case 5:
				//Comes from scores.c
                showStatistics(history, gameCount);
                break;
            case 6:
				//saveWords comes from words.c and saveScores comes from scores.c 
                saveWords(words, wordCount);
                saveScores(history, gameCount);
                break;
            case 0:
				//Uses yes_or_no from input.c to check wether or not user wants to save
				//if yes, loop uses saveWords from words.c and saveScores.c from scores.c
				//Futher testing is required to see if this line will work the yes_or_no function in it's current state
                if (yes_or_no("Save before quitting? (y/n): ")) {
                    saveWords(words, wordCount);
                    saveScores(history, gameCount);
                }
                printf("Goodbye!\n");
                break;
        }
		// Go back to the top while choice is not 0; picking 0 makes this false and ends the loop.
    } while (choice != 0);

    return 0;
}

	
	
