/*This file will give the functions to check the inputs given by the user throughout the game.
 * Checks and fixes:  
 * That the user types in a valid number that corresponds to the game menu.
 * That the user cannot enter more than one letter per guess (and that the input is indeed a letter)
 * ... (Revisit YesorNo function)
 * That the user types in name and word with less than 20 characters
 * That every string is a letter ( no special characters)
 * That every letter is lowercase.*/

//Include the general library: #include <hangman.c> 

//Begin with clear input function that will be used throughout the input functions
//This is an important function to avoid keeping newlines and other 'garbage' input out of the input buffer
//For example, when the user guesses 'a' and hit 'Enter' they are adding '/n' which would get pushed into the next guess
//Putting these inputs into a variable will avoid any undefined behavior in the program.

void clear_input(){
    int c;

    do{
	    c = getchar();
    } while (c != '\n' && c != EOF);
//EOF is End of File.
//If the user decides to quit the game while the game is not over
//this will let the computer know to shut down instead of looping infinitely 
    if ( c == EOF){
        printf("\nNo more input! Goodbye!");
	exit(0);
    }
}

//readNumber function will be used in main.c 
//It will prompt the user to enter a number
//Read the number (throwing away newlines) 
//Keep the number between the appropriate range 

int read_number(char prompt[], int min, int max){
    int number;
    int valid = 0;

    do{
	    printf("%s", prompt);
//If user tries to input anything that is not an integer scanf will return false and hence we notify the user to input a whole number
	    if (scanf("%d", &number) != 1){
		    printf("Please input a whole number");
	    } else if ( number < min || number > max ){
		    printf("Please enter a number between the range given:%d to %d", min, max);
	    } else {
//If user entered a whole number within the range, then the while loop is valid and is allowed to exit		    
		    valid = 1;
	    }

	    clear_input();
    
    }while(valid == 0);

    return number; 
}

//readLEtter function will work similarly to readNumber
//First part will prompt the user to enter one letter
//Second part will evaluate whether the user entered a letter 
//

char readLetter(char prompt[]){
    char letter;
    int valid = 0;

    do{
	    printf("%s", prompt);
//scanf will not allow user to add spaces to our program
//However scanf does automatically add '/n' so if the user adds more letters getchar can check that the next letter is not '\n' 
//If the user typed in too many letters this function will clear the input and ask the user to try again  
	    if scanf("%c", &letter);
	    if (getchar() != '\n'){
	        
	    }
}

