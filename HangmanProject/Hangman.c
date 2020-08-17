#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

/* MAX VARIABLE SIZES */

#define MAX_ARRAY_SIZE 1000
#define MAX_WORDS 70000
#define WORD_LENGTH 35

/* Function definitions */

int checker(char *word);
int wordcheck(char *word, char *tempword);
void wordtype(char *word1);
int spaces(char *word);
int InitialiseWordList(void);
void clear(void);
void display(char *blocks, char *word, int*misscount, char* misses, int*count);
void guesses(char *blocks, char *word, int *misscount, char *misses, char guess);
void hanger (int misscount);
void endgame(void);
void hooray(void);

/* 	GLOBAL VARIABLES */
char wordarray[MAX_WORDS][WORD_LENGTH];
int numWords;

/*Hangman Project 2019*/

int main(void)
{
    char response[WORD_LENGTH];
    char word[WORD_LENGTH], word1[WORD_LENGTH], word2[WORD_LENGTH];
    int randindex;

    //Displaying the Hangman logo.
	printf("\n");
    printf("dP     dP\n");
    printf("88     88\n");
    printf("88aaaaa88a .d8888b. 88d888b. .d8888b. 88d8b.d8b. .d8888b. 88d888b. \n");
    printf("88     88  88'  `88 88'  `88 88'  `88 88'`88'`88 88'  `88 88'  `88 \n");
    printf("88     88  88.  .88 88    88 88.  .88 88  88  88 88.  .88 88    88 \n");
    printf("dP     dP  `88888P8 dP    dP `8888P88 dP  dP  dP `88888P8 dP    dP \n");
    printf("                                  .88\n");
    printf("                              d8888P\n");

    printf("\n\nWould you like to enter your own word(s)? (y or n): ");
    //Using gets to get the response.
    gets(response);
    //if the first letter isnt a y or n then repeat the question.
    while (response[0] != 'y' && response[0] != 'Y' && response[0] != 'n' && response[0] != 'N'){

    	printf("\nWould you like to enter your own word(s)? (y or n): ");
    	gets(response);
    }

    //if entering own words, get the word and check if it is one word or two.
    if (response[0] == 'y' || response[0] == 'Y') 
    {
    	printf("\nEnter your word(s): (max 2)\n");
    	gets(word);

    	int length = strlen(word);
    	int index = spaces(word);
    	
    	//checks if the word is in the dictionary file using the checker function.
    	if (index == -1) {
    		if (checker(word) != 1){
    			wordtype(word);
    		}
    		printf("\nYour word(s) is: %s\n", &word);	
    	}
    	//if two words, splits them into two seperate strings.
    	if (index > 0) {
    		for(int j = 0; j<index; j++) {
    			word1[j] = word[j];
    		}
    		for(int j = index+1; j<length; j++) {
    			word2[(j-index-1)] = word[j];
    		}
    		

    		word1[index] = '\0';
    		word2[length-(index+1)] = '\0';
    		//checks that both words are legit. if not asks to enter a new word(separately).
    		if(checker(word1)==1 && checker(word2)==1) {
    			printf("Your word(s) is: %s", word);
    		}else {
    			wordtype(word1);
    			printf("\nYour first word is: %s\n", word1);
    			wordtype(word2);
    			printf("\nYour second word is: %s\n", word2);
    			strcat(word1, " ");
    			strcat(word1, word2);
    			strcpy(word, word1);
    			printf("\nYour word(s) is: %s\n", word);
    		}
    	}
    }
    //if answer is no, then a computer generated word is produced.
    if (response[0] == 'n' || response[0] == 'N'){

    	printf("\nYour word will be randomly generated.\n\n");

    	numWords = InitialiseWordList();
    	//A random number is produced using time strand to improve unpredictability.
    	srand((unsigned int)time(NULL));
    	randindex = rand() % (numWords);

    	strcpy(word, wordarray[randindex]);
    } 
    
    //make blocks string for missing letters.
    int lastlength = strlen(word);
    char blocks[WORD_LENGTH] = {0};
    blocks[lastlength] = '\0';
    int h = 0;

    while (word[h] != '\0'){
    	if (word[h] == ' '){
    		blocks[h] = ' ';
    	}else{
    		blocks[h] = '_';
    	}
    	h++;
    }

    printf("\n\nPress the ENTER key to start the game:\n");
    getchar();
    clear();

    char misses[26] = {0};
    int misscount = 6;
    int count = 1;

    //while not solved and still have lives, continue game.
    while (strcmp(blocks,word) !=0 && misscount >0) {
    	display(blocks, word, &misscount, misses, &count);
    }

    printf("\n\nTHE WORD WAS: %s\n", word);

    Sleep(2000);

    int k=0;

    for (k = 0; k<50; k++){
		printf("\n");
	}
	//end screens.
    if(misscount == 0){
    	printf("\n\nYOU ARE OUT OF GUESSES!\n\n...SORRY BUT YOU DIE...\n");
    	endgame();
    }else{
    	printf("\n\nYOU WIN :)!\n\n...GOOD JOB...\n\n");
    	printf("YOU HAD %i MORE MISSES LEFT\n", misscount);
    	hooray();
    }
    return 0;
}
 
int wordcheck(char *word, char *tempword)
{
	//checking if words are the same.
	int i = 0, count = 0;

	if (strlen(word) != strlen(tempword)) {
		return 0;
	}

	while (word[i] != '\0') {

		if(word[i] != tempword[i]) {
			count++;
		}
		i++;
	}
	if (count == 0) {
		return 1;
	}
	return 0;
}

int checker(char *word)
{
	//opens dictionary file. if too small, return 2. if
	//it matches a word in file return 1. if not return 0.
	char tempword[100];

	FILE *list;
    list = fopen("wordlist.txt", "r");
    int length = strlen(word);

	if (length < 3) {
		return 2;
	}

	while (fscanf(list, "%s", tempword) != EOF) {

		if (strcmp(word,tempword) == 0){
    		return 1;
		}
    } 

    return 0;
}

void wordtype(char *word1)
{
	//messages associated with the returns from checker function.
	int check;

	while (checker(word1) == 0 || checker(word1) == 2){

    		check = checker(word1);
    		if (check == 2){
    			printf("Your word (%s) is too short (below 3 letters), please add a different word: ", word1);
    			gets(word1);
    		}if (check == 0){
    			printf("This is not a word (%s), please add a different word: ", word1);
    			gets(word1);
    		}if (check == 1){
    			return;
    		}
    	}
}

int spaces(char *word) {

	//checks if a ' ' space exists in the word.
	int length = strlen(word);
    int space = -1;
    int i =0;

    for(i = 0; i<length; i++){
   		if(word[i] == ' '){
   			space = i;
   		}
   	}
   	return space;
}

int InitialiseWordList(void)
{
	FILE *list;
	char tempword[WORD_LENGTH];

	list = fopen("wordlist.txt", "r");
	numWords = 0;

	if(list == NULL) {
		printf("Could not open file.");
		exit(EXIT_FAILURE);
	}
	//while the file can still can to tempword( until EOF),
	//if word is large enough, make the wordarray of all legit 
	//words to use for the computed generated word.
	while (fscanf(list, "%s", tempword) != EOF) {
		if ((int)strlen(tempword) >= 3) {
			strcpy(wordarray[numWords], tempword);
			numWords++;
		}
	}
	//wordarray is actually a global variable.
	return numWords;
}

void clear(void)
{
	int i = 0;

	Sleep(700);
	printf("\n\nThe game will begin in ...");
    printf("\n...3");
    Sleep(500);
    printf("\n...2");
    Sleep(500);
    printf("\n...1");
    Sleep(500);
    printf("\nGO!!!");

	for (i = 0; i<100; i++){
		printf("\n");
	}
}

void display(char *blocks, char *word, int*misscount, char* misses, int*count)
{
	//simple display of the game screen.
	printf("----------------------------------------------\n");
	printf("|                H_NGM_N G_ME                |\n");
	printf("|                                            |\n");
	printf("|              -----------------             |\n");
	hanger(*misscount);
	printf("|        ______|___________________          |\n");
	printf("|       /      |\\                 /|         |\n");
	printf("|      /_________________________/ |         |\n");
	printf("|      |                         | /         |\n");
	printf("|      |_________________________|/          |\n");
	printf("|                                            |\n");
	printf("|             MISSES LEFT: %i                 |\n",*misscount);
	printf("|                                            |\n");

	int length = strlen(blocks);
	int start = 22 - (int)length/2;
	char missing[45] = {0};
	missing[44] = '\0';

	//creates a new string line where the blocks array is in the middle.
	for (int i =0;i<44;i++) {

		if (i < (start+length) && i >= start){
			int index = i-start;
			missing[i] = blocks[index];
		}
		else {
			missing[i]= ' ';
		}
	}

	printf("%c",124);
	printf("%s",missing);
	printf("%c\n",124);

	printf("|                                            |\n");
	printf("----------------------------------------------\n");
	printf(" \n");
	printf("Attempt number: %i\n",*count);
	printf("Characters guessed:\n");
	int misslength = strlen(misses);

	for (int g = 0; g<misslength;g++){
		printf("%c",misses[g]);
	}
	printf("\nEnter guess: ");

	char guess = (char)getchar();
	getchar();
	
	//increases the count of turns used.
	printf("\n\n\n\n\n");
	*count = *count + 1;

	guesses(blocks,word,&*misscount,misses,guess); // calls the guesses function using a &*for a subcall of a pointer.
	//weird but it works.

}

void guesses(char *blocks, char *word, int *misscount, char *misses, char guess)
{
	//if the guess is a letter of the word then change the blocks array.
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


	int dupe = 0;
	// if guess has already been guessed, dupe = 1.
	for (i=0;i<index;i++){
		if (guess == misses[i]){
			dupe = 1;
		}
	}

	//if not a dupe and not a letter, decrease misscount and add to the misses list with a comma follwoing it.
	if (positive == 0 && dupe == 0) {
		*misscount = *misscount - 1;
		misses[index] = guess;
		misses[index+1] = ',';
	}
}

void hanger (int misscount) 
{
	if (misscount == 6){
	printf("|              |/              |             |\n");
	printf("|              |                             |\n");
	printf("|              |                             |\n");
	printf("|              |                             |\n");
	}if (misscount == 5){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |                             |\n");
	printf("|              |                             |\n");
	}if (misscount == 4){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |               |             |\n");
	printf("|              |                             |\n");
	}if (misscount == 3){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |              /|             |\n");
	printf("|              |                             |\n");
	}if (misscount == 2){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |              /|\\            |\n");
	printf("|              |                             |\n");
	}if (misscount == 1){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |              /|\\            |\n");
	printf("|              |                \\            |\n");
	}if (misscount == 0){
	printf("|              |/              |             |\n");
	printf("|              |               O             |\n");
	printf("|              |              /|\\            |\n");
	printf("|              |              / \\            |\n");
	}
}

void endgame(void) 
{
	printf("                uuuuuuu\n");
    printf("           uu$$$$$$$$$$$uu\n");
    printf("        uu$$$$$$$$$$$$$$$$$uu\n");
    printf("       u$$$$$$$$$$$$$$$$$$$$$u\n");
    printf("      u$$$$$$$$$$$$$$$$$$$$$$$u\n");
    printf("     u$$$$$$$$$$$$$$$$$$$$$$$$$u\n");
    printf("     u$$$$$$$$$$$$$$$$$$$$$$$$$u\n");
    printf("     u$$$$$$\"   \"$$$\"    \"$$$$$$u\n");
    printf("     \"$$$$\"      u$u      \"$$$$\"\n");
    printf("      $$$u       u$u       u$$$\n");
    printf("      $$$u      u$$$u     u$$$\n");
    printf("       \"$$$$uu$$$   $$$uu$$$$\"\n");
    printf("        \"$$$$$$$\"   \"$$$$$$$\"\n");
    printf("          u$$$$$$$u$$$$$$$u\n");
    printf("           u$\"$\"$\"$\"$\"$\"$u\n");
    printf("uuu        $$u$ $ $ $ $u$$       uuu\n");
    printf("u$$$$       $$$$$u$u$u$$$        u$$$$\n");
    printf("$$$$$uu      \"$$$$$$$$$\"     uu$$$$$$\n");
	printf("u$$$$$$$$$$$uu  \"\"\"\"\"      uuuu$$$$$$$$$$\n");
	printf("$$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\"\n");
	printf(" \"\"\"      \"\"$$$$$$$$$$$uu \"\"$\"\"\"\n");
    printf("       uuuu \"\"$$$$$$$$$$uuu\n");
    printf("u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$\n");
    printf("$$$$$$$$$$\"\"\"\"           \"\"$$$$$$$$$$$\"\n");
    printf(" \"$$$$$\"                      \"\"$$$$\"\"\n");
    printf("  $$$\"                         $$$$\"");
}

void hooray(void)
{
printf("	                                  ......\n");                               
printf("                                        ..~+===+I.\n");                              
printf("                                        .I+======?.\n");                             
printf("   .I?++                           .???..+========?.                  :II?.\n");     
printf("  .I+++++++.                     ?+++==+II+=====+++I.              .?+++=++I..\n");  
printf("  :?+++====++.                  .+======+I++++++++++I            .?++=====++$.\n");  
printf("  .?++======+?.           ....  ?+=======+$+++++++++I..          7++======++7.\n");  
printf("  .$++=======++?        .=++=+++++=======+?++++++++++7.         7++=======+?+.\n");  
printf("   .I?+=======+++..    .+======+7++====++++I+++++++++I.        .?++=====++?Z\n");    
printf("     7?+=====+++++?.   .+======++I++++++++++7+++?????I7.      .7++=====++?$.\n");    
printf("     .$?++++++==++++.  .+=====+++?++++++++++?+???IIIII7.      ~?++====++?$.\n");     
printf("      .7????+====++++=..++++++++++7++++++++++IIIII77777.      7?++===++?7.\n");      
printf("       .=???+====+++++?.I++++++++++?++++++????777777777O.    $?+++=+++?7..\n");      
printf("        . I?++===++++++??++++++++++I?????IIIII77777777$O?7..$?+++=+++?I+\n");        
printf("          .$??++++++++++7I+++++++???7IIIIII77777$777$ZO$????++++++++?I$\n");         
printf("           .II???+++++++?$?++????IIII7I77777777$OZZZOOOII?+++++++++?IZ.\n");         
printf("            .,I???+++++++?7???IIIIII777777777$$O7Z888ZII?+++++++++?IZ.\n");          
printf("               I????++++++I7I777777777$$$$$$$ZOOIIIIII?++++++++++?I$.\n");           
printf("               .7?????+++++I777777777$7IOOOOO88ZII????++++++++++?I$\n");             
printf("                .7?????+++++I777777$ZO7II$O88O$I????++++++++++??I$.\n");             
printf("                 .7????+++++?IOZZZZO8ZIIIIII??????++++++=+++++?I$.\n");              
printf("                 ..I???+++++???7O8D8$I???????????+++++====+++??I:.\n");              
printf("                   :I???+++??????II????????????++++++====+++??I$.\n");               
printf("                   .7I???++??????????????????+++++=======+++?I7.\n");                
printf("                    .7II???????????????????+++++========+++?I7Z.\n");                
printf("                    .$II????????++++++++++++++=========+++?II$..\n");                
printf("                     .$III????++++++++++++++==========+++??I7~\n");                  
printf("                       $7II????++++++++++++======+++++++??I7Z\n");                   
printf("                       .77II????++++++++++++++++++++????III$.\n");                   
printf("                        .$7II?????++++++++++++????????III7$.\n");                    
printf("                          .$7II????????????????????IIII7$\n");                       
printf("                            $7III?????????????IIIIII77$.\n");                        
printf("                             ..$IIIIIIIIIIIIII77777$..\n");                          
printf("                                ..=$777777777$$:...\n");                             
printf("                                   ...........\n");                                                                                                                
}