//libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "wordsDRAFT1.c"
#include "wordsSTRUCTURESdraft1.c"
#include "wordsFUNCTIONS.c" 

int main()
{

//load words
loadWords();

//print elements of hangman array

for (int i = 0; i < 8; i++)
{
    printf("Word %i is: %s.\n",i+1, hangman_words[i]);
}

return 0;


}

