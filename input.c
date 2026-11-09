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
//FUNCTION PROTOTYPES:
#include "hangman.h"

void clearInput(){
    int c;

    do{
	    c = getchar();
    } while (c != '\n' && c != EOF);
//EOF is End of File.
//If the user decides to quit the game while the game is not over
//this will let the computer know to shut down instead of looping infinitely 
    if ( c == EOF){
        printf("\nNo more input! Goodbye!\n");
	exit(0);
    }
}

//readNumber function will be used in main.c 
//It will prompt the user to enter a number
//Read the number (throwing away newlines) 
//Keep the number between the appropriate range 

int readNumber(char prompt[], int min, int max){
    int number;
    int valid = 0;

    do{
	    printf("%s", prompt);
//If user tries to input anything that is not an integer scanf will return false and hence we notify the user to input a whole number
	    if (scanf("%d", &number) != 1){
		    printf("Please input a whole number\n");
	    } else if ( number < min || number > max ){
		    printf("Please enter a number between the range given:%d to %d\n", min, max);
	    } else {
//If user entered a whole number within the range, then the while loop is valid and is allowed to exit		    
		    valid = 1;
	    }

	    clearInput();
    
    }while(valid == 0);

    return number; 
}

//readLEtter function will work similarly to readNumber
//First part will prompt the user to enter one letter
//Second part will evaluate whether the user entered a letter 


char readLetter(char prompt[]){
    char letter;
    int valid = 0;

    do{
	    printf("%s", prompt);
//scanf will not allow user to add spaces to our program
//However scanf does automatically add '/n' when the user hits "Enter" for a char (NOT STRING) 
//so if the user adds more letters getchar can check that the next letter is not '\n' 
//If the user typed in too many letters this function will clear the input and ask the user to try again  
	    scanf("%c", &letter);
	    if (getchar() != '\n'){
		    printf("Please do not type more than one letter or a space!!\n");
	            clearInput();
//Using ASCII values we can make sure our inputs are indeed a letter 		    
	    } else if ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z')){
		    printf("Please enter a letter, %c is not a letter\n", letter);
	    } else{
		    valid = 1;
	    }

    }while(valid == 0);

//Now we will take any uppercase letters and make them lowercase 

    if( letter >= 'A' && letter <= 'Z'){
//Adding 32 or 'a'-'A' moves an upper case letter to its lowercase counterpart
	    letter = letter + ('a' - 'A');
    }

    return letter; 

}


//Whenever there is a decision for the user to make that is a simple yes or no
//This function will make sure that the user can only type 'y' for yes  and 'n' for no 
//For yes the function will return 1
//For no the function will return 0 ( doing nothing)

int askYesNo(char prompt[]){
    char answer; 
//We wil use our readLetter function to prompt the user to type in a letter
//We can then accept answers that are only either 'y' or 'n' 
    do{
	    answer = readLetter(prompt);
	    if ( answer != 'y' && answer != 'n'){
		    printf("Please answer Yes (y) or No (n)\n");
	    }
    }while ( answer != 'y' && answer != 'n');

    if ( answer == 'y'){
	    return 1;
    }

    return 0;
}

//readWord function will make sure a words contains ONLY letters, up to 20 will be allowed ( feel free to change this parameter) 
//I will use isAllLetters function to make sure that the first condition of only letters is met

void readWord(char prompt[], char word[]){
    int valid = 0;

    do{
	    printf("%s", prompt);
//Fgets is less efficient in this case than scanf since we are only reading one word!
//Whenever reading a string, scanf does NOT add '\n' like fgets would, so there is no need
//To remove the trailing newline ( less code to write!) 	    
	    scanf("%20s", word);
	    if ( getchar() != '\n'){
		    printf("Please do not type a word more than 20 letters!\n");
		    clearInput();
	    }else if (!isAllLetters(word)){
		    printf("Please use only letters!\n");
	    } else{
		    valid = 1;
	    }
    }while (valid == 0);
}

//AllLetters will check through a for-loop whether a char array (word) is actually all letters 
//In which case it will return 1

int isAllLetters(char text[]){

//We loop until we reach '\n' meaning our array(word) has reached the end	
//If we do not have a letter, then we return 0
	for( int i = 0; text[i] != '\0'; i++){
		if( (text[i] < 'a' || text[i] > 'z') && (text[i] < 'A' || text[i] > 'Z')){
			return 0;
		}
	}
	return 1;
}

//LowerWord function will make all letters lowercase. Unlike our readLetter function
//This function will take a whole word instead of just one letter
//We will make use of a for-loop as in the previous function to go through all letters
//and use the same arithmetic as in readLetter to change each letter in the word to lowercase

void toLowerWord( char word[]){
	
	for( int i = 0; word[i] != '\0';i++){ /* CHANGELOG '\0' */
		if(word[i] >= 'A' && word[i] <= 'Z'){
			word[i] = word[i] + ('a' - 'A');
		}
	}
}


