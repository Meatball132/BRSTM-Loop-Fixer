#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum Errors
{
	WRONG_ARG_COUNT,
	WRONG_ARG_TYPE,
	WRONG_ARG_ORDER
};

bool checkIfInt(char *arg);
void error(enum Errors type);

char *exeName; // listen. this is a global. that is ok. don't worry about it.

int main(int argc, char *argv[])
{
	exeName = argv[0];
	
	// Make sure there are precisely two arguments
	if (argc != 3)
		error(WRONG_ARG_COUNT);
	
	// Make sure both args are integer values
	for (int i = 1; i < 3; i++)
	{
		if (checkIfInt(argv[i]) == 0)
			error(WRONG_ARG_TYPE);
	}
	
	// OK, now that we know it's safe, convert arguments to ints
	long loopStart = atoi(argv[1]);
	long loopEnd = atoi(argv[2]);
	
	// Make sure loopStart is smaller than loopEnd
	if (loopStart > loopEnd)
		error(WRONG_ARG_ORDER);
	
	const long FRAME_SIZE = 14336; // 1024 * 14
	
	// Adjust start point to be a multiple of the frame size
	// Calculating the ceiling (not floor) to avoid including part of the intro in the loop
	long newLoopStart = ((loopStart + FRAME_SIZE - 1) / FRAME_SIZE) * FRAME_SIZE;
	
	// Shift loop end in accordance with loop start shift
	long newLoopEnd = newLoopStart + (loopEnd - loopStart); 
	
	// Print results
	printf("Adjusted loop points:\n");
	printf("Loop Start  =  %ld\n", newLoopStart);
	printf("Loop End    =  %ld\n", newLoopEnd);
	
	return 0;
}

bool checkIfInt(char *arg)
{
	while (*arg)
	{
		if (!isdigit(*arg))
			return false;
		arg++;
	}
	return true;
}

void error(enum Errors type)
{
	switch (type)
	{
		case WRONG_ARG_COUNT:
			printf("Wrong number of arguments!\n");
			break;
		case WRONG_ARG_TYPE:
			printf("Arguments must be integers!\n");
			break;
		case WRONG_ARG_ORDER:
			printf("End loop point must be larger than start loop point!\n");
			break;
		default:
			printf("Something went wrong! Sorry!\n");
			break;
	}
	printf("Usage: \"%s Loop_Start Loop_End\"\n", exeName);
	exit(1);
}