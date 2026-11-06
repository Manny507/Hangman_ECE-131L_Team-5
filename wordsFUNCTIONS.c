//This file contains functions applicable to the words.c implementation
#define SIZE 25

//This function reads words into the word database
void addWord(int database_index, char hangman_words[][WORD_COUNT])
{
    printf("Enter a word to add: ");
    
    if (fgets(hangman_words[database_index], WORD_COUNT, stdin) == NULL)
    {
        hangman_words[database_index][0] = '\0';
        return;
    }


    int length = strlen(hangman_words[database_index]);
    if (length > 0 && hangman_words[database_index][length-1] == '\n')
    {
        hangman_words[database_index][length - 1] = '\0';
    }
}

//This function loads the initial 8 words present in the array

void loadWords(void)
{
    FILE *word_file = fopen("wordsDRAFT.txt", "r");
    if (word_file == NULL)
    {
        printf("Error: Could not open word database.\n");
        return;
    }



    hangman_words = calloc(MAX_WORDS, sizeof(*hangman_words));
    
    for (int i = 0; i < MAX_WORDS; i++)
    {

        if (fgets(hangman_words[i], WORD_COUNT, word_file) == NULL)
        {
            break;
        }  
    
        int length = strlen(hangman_words[i]);
        if (length > 0 &&hangman_words[i][length - 1] == '\n')
        {
            hangman_words[i][length - 1] = '\0';
        }

    }

    fclose(word_file);
}

