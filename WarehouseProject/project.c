/* ENGGEN131 Project - C Project - 2019 */
/* The Warehouse */

/* << Name: Jacob Eyles, Username: jeyl534, ID: 992957383 >> */

#include "project.h"

/*
This function calculates the difference between the time when a worker has clocked in and out.
The inputs for the function is the time measured in minutes and seconds for times A and B. 
The output is the positive difference between these two times (timeA and timeB), measured in seconds.
*/
int TimeWorked(int minuteA, int secondA, int minuteB, int secondB)
{
	int timeA, timeB, diff;
	
	timeA = 60*minuteA + secondA;
	timeB = 60*minuteB + secondB;
	
	diff = timeA - timeB;
	
	if (diff<0) {
		diff = diff*(-1);
	}
	
	return diff;
	
}

/*
This function calculates the largest prime number, given an upper bound.
Each number from 0 to the set upper bound (which is the input 'maximum') 
is divided by a number 'j' from 2 to the currentAddress or current number 
which is being sorted through in the set. If there is a remainder of 0, 
this is not a prime and is not added to variable 'prime'. Eventually, the 
maximum bound is reached and the largest prime of the set is stored in 
the variable 'prime'. This is the required ouput.
*/
int WarehouseAddress(int maximum)
{
	int currentAddress,j,prime;
	prime = 0;
	
	for (currentAddress = 0; currentAddress<maximum ; currentAddress++) {
		j = 2;
		while ((j<currentAddress) && (currentAddress % j != 0)) {
			j++;
			}
			if (j==currentAddress) {
				prime = currentAddress;
			}
	}
	
	return prime;
			
}

/*
This function shifts the characters in an input string 'words'
to the left by one postion. The array at index 0 is shifted to
the furthest index on the right.
*/
void Advertise(char *words)
{
	int i, strlen;
	char temp;
	
	i = 0;
	
	while(words[i] != '\0') {
		i++;
	}
	
	strlen = i;
	temp = words[0];
	
	for(i=0; i<(strlen-1); i++) {
		words[i] = words[i+1];
	}

	words[strlen-1] = temp;
}

/*
This function finds the lowest unique bid from an auction.
The algorithm compares every element in the bid values to
every other bid. If any are the same, this is value is 
ignored. From the unique values, the lowest bid is set as 
the variable 'bid'. If there is no lowest unique bid, -1 is
returned.
*/
int WinningBid(int *values, int length)
{
	int i, duplicate, j, bid;
	bid = 0;
	
	for (i=0; i<length; i++) {
		
		duplicate = 0;
		for(j = 0; j<length ;j++) {
			
			if(j!=i && (values[j] == values[i])) {
				duplicate = 1;
			}
		}
		
		if (duplicate == 0 && bid == 0) {
			bid = values[i];
		} if (duplicate==0 && values[i]<bid) {
			bid = values[i];
		}
	}
	
	if (bid == 0) {
		return -1;
	}
	
	return bid;

}

/*
This function manipulates a string to simulate the outline of a
box. The outline of the box is created with asterisks and the rest 
is filled with spaces. This middle section of the box outline is 
filled with 'X's. 
*/
void BoxDesign(char *design, int width, int height)
{
	int i;
	int strlen = (width+1)*height;
	int index = ((height-1)/2*(width+1))+((width-1)/2);
	
	for (i=0; i<strlen; i++) {
		
		if(i<width || (i>=(strlen-width) && (i<strlen-1))) {
			design[i] = '*';
		}
		else if(i%(width+1) == width) {
			design[i] = '\n';
		}
		else if(i%(width+1) == 0 || i%(width+1) == width-1) {
			design[i] = '*';
		}
		else{
			design[i] = 32;
		}
	}
	
	if(width >= 3 && height >= 3) {
		
		if(width%2 == 1 && height%2 == 1) {
			design[index] = 88;
		}
		if(width%2 == 0 && height%2 == 1) {
			design[index+1] = 88;
			design[index] = 88;
		}
		if(width%2 == 1 && height%2 == 0) {
			design[index+(width+1)] = 88;
			design[index] = 88;
		}
		if((width%2 == 0 && height%2 == 0)) {
			design[index+1] = 88;
			design[index+(width+1)] = 88;
			design[index+(width+2)] = 88;
			design[index] = 88;
		}
	}
}

/*
Your comment should go here – it should describe the purpose of the function and a
brief summary of the algorithm you have used to solve the task (this comment must
be written in your own words
*/
void WorkerRoute(int warehouse[10][10])
{
	int i,j;
	int Wrow = 0,Wcol = 0;
	int Brow = 0,Bcol = 0;
	
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			
			if (warehouse[i][j] == 1) {
				Wrow = i;
				Wcol = j;
			}
			if (warehouse[i][j] == 2) {
				Brow = i;
				Bcol = j;
			}
		}
	}
	
	int coldiff;
	
	if (Bcol > Wcol) {
		coldiff = Bcol - Wcol;
		
		for (i=1;i<=coldiff;i++) {
			if(warehouse[Wrow][Wcol+i] == 0){
				warehouse[Wrow][Wcol+i] = 3;
			}
		}
	}
	
	if (Bcol < Wcol) {
		coldiff = Wcol - Bcol;
		
		for (i=1;i<=coldiff;i++) {
			if(warehouse[Wrow][Wcol-i] == 0){
				warehouse[Wrow][Wcol-i] = 3;
			}
		}
	}
	
	int rowdiff;
	
	if (Brow > Wrow) {
		rowdiff = Brow - Wrow;
		
		for (i=1;i<rowdiff;i++) {
			warehouse[Wrow+i][Bcol] = 3;
		}
	}
	if (Brow < Wrow) {
		rowdiff = Wrow - Brow;
		
		for (i=1;i<rowdiff;i++) {
			warehouse[Wrow-i][Bcol] = 3;
		}
	}
}

/*
Your comment should go here – it should describe the purpose of the function and a
brief summary of the algorithm you have used to solve the task (this comment must
be written in your own words
*/
int MakeMove(int warehouse[10][10], char move)
{
	int i,j,Wrow=0,Wcol=0;
	
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			if (warehouse[i][j] == 5 || warehouse[i][j] == 6) {
				Wrow = i;
				Wcol = j;
			}
		}
	}
	
	if(move == 'w') {
		if(warehouse[Wrow][Wcol] == 5) {
			if(warehouse[Wrow-1][Wcol] == 0) {
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow-1][Wcol] == 2) {
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow-1][Wcol] == 3 && warehouse[Wrow-2][Wcol] == 2) {
				warehouse[Wrow-2][Wcol] = 4;
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow-1][Wcol] == 3 && warehouse[Wrow-2][Wcol] == 0) {
				warehouse[Wrow-2][Wcol] = 3;
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow-1][Wcol] == 4 && warehouse[Wrow-2][Wcol] == 0) {
				warehouse[Wrow-2][Wcol] = 3;
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow-1][Wcol] == 4 && warehouse[Wrow-2][Wcol] == 2) {
				warehouse[Wrow-2][Wcol] = 4;
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}
		}
		if(warehouse[Wrow][Wcol] == 6) {
			if(warehouse[Wrow-1][Wcol] == 0) {
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow-1][Wcol] == 2) {
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow-1][Wcol] == 3 && warehouse[Wrow-2][Wcol] == 2) {
				warehouse[Wrow-2][Wcol] = 4;
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow-1][Wcol] == 3 && warehouse[Wrow-2][Wcol] == 0) {
				warehouse[Wrow-2][Wcol] = 3;
				warehouse[Wrow-1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow-1][Wcol] == 4 && warehouse[Wrow-2][Wcol] == 0) {
				warehouse[Wrow-2][Wcol] = 3;
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow-1][Wcol] == 4 && warehouse[Wrow-2][Wcol] == 2) {
				warehouse[Wrow-2][Wcol] = 4;
				warehouse[Wrow-1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}
		}
	}
	
	if(move == 'a') {
		if(warehouse[Wrow][Wcol] == 5) {
			if(warehouse[Wrow][Wcol-1] == 0) {
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol-1] == 2) {
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol-1] == 3 && warehouse[Wrow][Wcol-2] == 2) {
				warehouse[Wrow][Wcol-2] = 4;
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol-1] == 3 && warehouse[Wrow][Wcol-2] == 0) {
				warehouse[Wrow][Wcol-2] = 3;
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol-1] == 4 && warehouse[Wrow][Wcol-2] == 0) {
				warehouse[Wrow][Wcol-2] = 3;
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol-1] == 4 && warehouse[Wrow][Wcol-2] == 2) {
				warehouse[Wrow][Wcol-2] = 4;
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}
		}
		if(warehouse[Wrow][Wcol] == 6) {
			if(warehouse[Wrow][Wcol-1] == 0) {
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol-1] == 2) {
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol-1] == 3 && warehouse[Wrow][Wcol-2] == 2) {
				warehouse[Wrow][Wcol-2] = 4;
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol-1] == 3 && warehouse[Wrow][Wcol-2] == 0) {
				warehouse[Wrow][Wcol-2] = 3;
				warehouse[Wrow][Wcol-1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol-1] == 4 && warehouse[Wrow][Wcol-2] == 0) {
				warehouse[Wrow][Wcol-2] = 3;
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol-1] == 4 && warehouse[Wrow][Wcol-2] == 2) {
				warehouse[Wrow][Wcol-2] = 4;
				warehouse[Wrow][Wcol-1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}
		}

	}
	
	if(move == 's') {
		if(warehouse[Wrow][Wcol] == 5) {
			if(warehouse[Wrow+1][Wcol] == 0) {
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow+1][Wcol] == 2) {
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow+1][Wcol] == 3 && warehouse[Wrow+2][Wcol] == 2) {
				warehouse[Wrow+2][Wcol] = 4;
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow+1][Wcol] == 3 && warehouse[Wrow+2][Wcol] == 0) {
				warehouse[Wrow+2][Wcol] = 3;
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow+1][Wcol] == 4 && warehouse[Wrow+2][Wcol] == 0) {
				warehouse[Wrow+2][Wcol] = 3;
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow+1][Wcol] == 4 && warehouse[Wrow+2][Wcol] == 2) {
				warehouse[Wrow+2][Wcol] = 4;
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 0;
				}
		}
		if(warehouse[Wrow][Wcol] == 6) {
			if(warehouse[Wrow+1][Wcol] == 0) {
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow+1][Wcol] == 2) {
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow+1][Wcol] == 3 && warehouse[Wrow+2][Wcol] == 2) {
				warehouse[Wrow+2][Wcol] = 4;
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow+1][Wcol] == 3 && warehouse[Wrow+2][Wcol] == 0) {
				warehouse[Wrow+2][Wcol] = 3;
				warehouse[Wrow+1][Wcol] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow+1][Wcol] == 4 && warehouse[Wrow+2][Wcol] == 0) {
				warehouse[Wrow+2][Wcol] = 3;
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow+1][Wcol] == 4 && warehouse[Wrow+2][Wcol] == 2) {
				warehouse[Wrow+2][Wcol] = 4;
				warehouse[Wrow+1][Wcol] = 6;
				warehouse[Wrow][Wcol] = 2;
				}
		}
	
	}
	if(move == 'd') {
		if(warehouse[Wrow][Wcol] == 5) {
			if(warehouse[Wrow][Wcol+1] == 0) {
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol+1] == 2) {
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol+1] == 3 && warehouse[Wrow][Wcol+2] == 2) {
				warehouse[Wrow][Wcol+2] = 4;
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol+1] == 3 && warehouse[Wrow][Wcol+2] == 0) {
				warehouse[Wrow][Wcol+2] = 3;
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol+1] == 4 && warehouse[Wrow][Wcol+2] == 0) {
				warehouse[Wrow][Wcol+2] = 3;
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}if(warehouse[Wrow][Wcol+1] == 4 && warehouse[Wrow][Wcol+2] == 2) {
				warehouse[Wrow][Wcol+2] = 4;
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 0;
				}
		}
		if(warehouse[Wrow][Wcol] == 6) {
			if(warehouse[Wrow][Wcol+1] == 0) {
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol+1] == 2) {
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol+1] == 3 && warehouse[Wrow][Wcol+2] == 2) {
				warehouse[Wrow][Wcol+2] = 4;
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol+1] == 3 && warehouse[Wrow][Wcol+2] == 0) {
				warehouse[Wrow][Wcol+2] = 3;
				warehouse[Wrow][Wcol+1] = 5;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol+1] == 4 && warehouse[Wrow][Wcol+2] == 0) {
				warehouse[Wrow][Wcol+2] = 3;
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}if(warehouse[Wrow][Wcol+1] == 4 && warehouse[Wrow][Wcol+2] == 2) {
				warehouse[Wrow][Wcol+2] = 4;
				warehouse[Wrow][Wcol+1] = 6;
				warehouse[Wrow][Wcol] = 2;
				}
		}
	}
	
	int counted = 0,count = 0;
	
	for (i=0;i<10;i++) {
		for (j=0;j<10;j++) {
			if (warehouse[i][j] == 2 || warehouse[i][j] == 6 || warehouse[i][j] == 4 ) {
				counted++;
			}if (warehouse[i][j] == 5 || warehouse[i][j] == 3) {
				count++;
			}
		}
	}
	
	if (counted == 0) {
		return 0;
	}
	if(count == 0) {
		return 1;
	}
	return 0;
	
}

