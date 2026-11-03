/* Scores.c keeps the history of games played, generates/updates our scores.txt file,  
*  and generates a stats report. 
*  Written by: Cesar Marquez Garcia
*/
#include "hangman.h"

/* 
typedef struct {
    char player[WORD_SIZE]; // Player's name
    char word[WORD_SIZE]; // The word to guess
    int won; // 1 if the player won, 0 if they lost
    int wrong; // Number of wrong guesses made
    int score;  
} GameRecord;
 */

// loadScores reads scores.txt into the history[] array with GameRecord data. If no history exists...
// ... then load scores will load 0 games. Returns how many games were loaded, so main.c can set gameCount.
int loadScores(GameRecord history[]){
    FILE *scoreFile;
    scoreFile = fopen(SCORES_FILE, "r");

    int count = 0;

    //Checking if the file score.txt exists
    if (scoreFile == NULL) {                 
        printf("No score history yet, starting new score history.\n");
        return 0;
    }
    
    // Reads one line per game into the next slot of history, until history is full or the file ends.
    // the "== 5" condition ensures that incomplete games aren't counted.
    while (count < MAX_GAMES &&
        fscanf(scoreFile, "%20s %20s %d %d %d", 
            history[count].player, history[count].word, 
            &history[count].won, &history[count].wrong, &history[count].score) == 5) {
            count++;
            }
    
    fclose(scoreFile);
    return count;
}

// saveScores writes data from history to scores.txt 
// and creates scores.txt if it didn't already exist.
void saveScores(GameRecord history[], int gameCount){
    FILE *scoreFile;
    scoreFile = fopen(SCORES_FILE, "w");
    int i;

    // In case scores.txt can't be accessed.
    if (scoreFile == NULL) {
        printf("Error: could not save into scores.txt.\n");
        return;
    }

    // Writes the GameRecord into scores.txt
    for(i=0; i<gameCount; i++){
        fprintf(scoreFile, "%s %s %d %d %d\n",
        history[i].player, history[i].word, 
        history[i].won, history[i].wrong, history[i].score);   
    }

    // fclose prevents our data from being lost & our game crashing.
    fclose(scoreFile);
}

void showScores(GameRecord history[], int gameCount){

}

void showStatistics(GameRecord history[], int gameCount){

}

