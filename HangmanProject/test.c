#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 70000
#define WORD_LENGTH 35

int wordcheck(char *word, char *tempword);

char wordList[MAX_WORDS][WORD_LENGTH];
int numWords;

int main(void)
{
	char word[100];
	int numWords = 0;
	char wordarray[70000][35] = {0};
   	
   	FILE *inputFile;

	inputFile = fopen("wordlist.txt", "r");
	numWords = 0;

	if(inputFile == NULL) {
		printf("Could not open file.");
		exit(EXIT_FAILURE);
	}else{
		printf("Success");
	}

	fscanf(inputFile, "%s", word);

	//while (fscanf(inputFile, "%s", word) != EOF) {
	//	if ((int)strlen(word) >= 3) {
	//		strcpy(wordarray[numWords], word);
	//		numWords++;
	//		printf("%i\n", numWords);
	//	}
	//}
	strcpy(wordarray[numWords], word);
	//printf("%s\n", wordarray[0]);
	//strcpy(wordarray[0], word);
	printf("%s\n", wordarray[numWords]);



    return 0;
}
