#define _CRT_SECURE_NO_WARNINGS

/* ENGGEN131 - 2019 - Lab 11 */
/* Word Chain */
/* A word game where each player must substitute one letter in a word to generate a new word */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* The dictionary we are using has fewer than 70000 words */
#define MAX_WORDS 70000
#define WORD_LENGTH 35

char wordList[MAX_WORDS][WORD_LENGTH];
int numWords;

void guesses(char *blocks, char *word, int *misscount, char *misses, char guess);

int main(void)
{
	char blocks[WORD_LENGTH] = "_____";
	char word[WORD_LENGTH] = "jelly";
	char misses[52] = {0};
	int misscount = 6;


	printf("Enter guess: ");

	char guess;
	guess = getchar();

	guesses(blocks,word,&misscount,misses,guess);

	printf("%i\n", misscount);
	printf("%s\n", misses);



}

void guesses(char *blocks, char *word, int *misscount, char *misses, char guess)
{
	int i=0;
	int positive = 0; 
	int index = strlen(misses);

	
	while (word[i] != '\0') {


		if (word[i] == guess) {
			positive = 1;
			blocks[i] = word[i];
		}
		i++;
	}

	printf("%i\n", positive);
	printf("%s\n", blocks);

	int dupe = 0;

	for (i=0;i<index;i++){
		if (guess == misses[i]){
			dupe = 1;
		}
	}


	if (positive == 0 && dupe == 0) {
		*misscount = *misscount - 1;
		misses[index] = guess;
		misses[index+1] = ',';
	}
}

