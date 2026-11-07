#include "Hangman.h"

int pickRandomWord(int wordCount){ //funcction name is pickRandomWorld & wordCount is the words we have available 
    return rand() % wordCount; //rand generates a random number w/ % wordCOunt makes the random number correlates to a position in that array
}

void drawHangman(int wrong) { //void doesnt return a value & int wrong tracks those wrong guesses
    printf("  _____\n"); //starts to print out the frame of the hangman 
    printf("  |   |\n");
    if(wrong >=1) {//Each numnber from 1-6 represents a wrong guess and that correlates to the body of the stickman as you progress
        printf("  O |\n");
    } else {
        printf("    |\n");
    }

    if (wrong >= 4) {
        printf("/|\   |\n");
    } else if (wrong >= 3) {
        printf(" /|   |\n)");
    } else if (wrong >= 2) {
        printf("  |   |\n");
    } else {
        printf("    |\n");
    }
    if (wrong>= 6) {
        printf("/\\  |\n");
    } else if (wrong >= 5) {
        printf(" /   |\n");
    } else {
        printf("     |\n");
    }

}

void showBoard(char revealed[], char guessed[], int wrong) {
    int i;

    printf("/n");
    drawHangman(wrong);

    printf("Word:  ");
    for (i = 0; revealed[i] != '\0'; i++) {
        printf("%c ", revealed[i]);
    }
    printf("\n");
    printf("Guessed: %s\n", guessed);
    printf("Lives: %d\n", MAX_WRONG - wrong);
}

int revealLetter(char secret[], char revealed[], char letter) {
    int i;
    int found = 0;

    for (i = 0; secret[i] != '\0'; i++) {
        if (secret[i] == letter) {
            revealed[i] = letter;
            found++;
        }
    }
    return found;
}

int computeScore(int wordLength, int wrong, int won) {
    if (won == 0){
        return 0;
    }
    return 10 * wordLength + 20 * (MAX_WRONG - wrong);
}

int playRound(char secret[]) {
    char revealed[WORD_SIZE];
    char guessed[27]= "";
    int wrong = 0;
    int length = strlen(secret);
    char letter;
    int i;
    int triedCount = 0;

    for (i=0; i<length; i++) {
        revealed[i] = '_';
    }
    revealed[length] = '\0';

    while (wrong < MAX_WRONG && strcmp(revealed, secret) !=0) {
        showBoard(revealed, guessed, wrong);
        letter = readLetter("Guess a letter");

        if (alreadyGuessed(guessed, letter)){
            printf("You already guessed '%c', No penalty.\n", letter);
    } else {
        guessed[triedCount] = letter;
        triedCount++;
        guessed[triedCount] = '\0';

        if (revealLetter(secret, revealed, letter)>0){
            printf(" Good Job! '%c' is in the word.\n", letter);
        } else {
            printf(" Sorry, '%c' is not in the word.\n", letter);
            wrong++;
        }
        
    }

    showBoard(revealed, guessed, wrong);

    return wrong;
}