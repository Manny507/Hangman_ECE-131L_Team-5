/* Scores.c keeps the history of games played, generates/updates our scores.txt file,  
*  and generates a stats report. 
*  Written by: Cesar Marquez Garcia
*/
#include "hangman.h"

// loadScores reads scores.txt into the history[] array with GameRecord data. If no history exists...
// ... then load scores will load 0 games. Returns how many games were loaded, so main.c can set gameCount.
int loadScores(GameRecord history[]){
    FILE *scoreFile;
    scoreFile = fopen(SCORES_FILE, "r"); //allows us to read scores.txt

    int count = 0;

    //Checking if the file scores.txt exists
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
    printf("Games loaded: %d\n", count);
    return count;
}

// saveScores writes data from history to scores.txt 
// and creates scores.txt if it didn't already exist.
void saveScores(GameRecord history[], int gameCount){
    FILE *scoreFile;
    scoreFile = fopen(SCORES_FILE, "w"); //allows us to write into scores.txt
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

    // fclose finishes writing everything to scores.txt and releases the file.
    fclose(scoreFile);
    printf("Games saved into scores.txt: %d\n", gameCount);
}

// showScores prints data from our GameRecord array
void showScores(GameRecord history[], int gameCount){
    
    // Checks if there's any data to display.
    if (gameCount == 0){
        printf("No score data to show.\n");
        return;
    }

    // prints a header row 
    printf("%-11s %-11s %5s %5s %5s\n", "Player", "Word", "Won", "Wrong", "Score");
    // prints out score data
    for(int i=0; i<gameCount; i++){
        printf("%-11s %-11s %5d %5d %5d\n", history[i].player, history[i].word, history[i].won, history[i].wrong, history[i].score);
    }
}

// showStatistics compiles the GameRecord data to show statistics.
void showStatistics(GameRecord history[], int gameCount){
    int wins = 0;
    int totalScore = 0;
    int totalWrong = 0;
    double avgScore;
    double winRate;
    double avgWrong;
    int best = 0;

    // checks if any games have been played
    if (gameCount == 0){
        printf("No games played yet\n");
        return;
    }

    // Gathers totals for wins, score, and wrong guesses
    for (int i = 0; i < gameCount; i++){
        if (history[i].won == 1){
        wins++;
       } 
    totalScore = totalScore + history[i].score;
    totalWrong = totalWrong + history[i].wrong;
    }

    // calculates total losses, average score, and win rate.
    int losses = gameCount - wins;
    avgScore = (double)totalScore/gameCount;
    winRate = (double)wins/gameCount * 100.0;
    avgWrong = (double)totalWrong/gameCount;

    // prints stats
    printf("Games played:   %d\n", gameCount);
    printf("Wins:           %d\n", wins);
    printf("Losses:         %d\n", losses);
    printf("Win rate:       %.1f%%\n", winRate);
    printf("Average score:  %.1f\n", avgScore);
    printf("Average Wrong:  %.1f\n", avgWrong);

    //Calculates your best game
    for (int i = 0; i<gameCount; i++){
    if (history[i].score > history[best].score){
        best = i;
        }
    }

    printf("Best game:      %d points by %s\n", history[best].score, history[best].player);
}

