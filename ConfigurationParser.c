
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

// This is the file descriptor of the configuration file
FILE *configFile = NULL;

/** @brief Set the Configuration path. Return -1 if there is a problem */
int SetConfigurationFile(char *path)
{
	configFile = fopen(path, "r");

	if(configFile == NULL) 
		return -1;

	return 0;
}

/** 
@brief Replace needle in haystack with \0 character

Searches for the needle character in haystack. If it's present, then
it replaces the character with \0, and returns the pointer to the next
element in the haystack. N.B. That this behaves similar to strtok()

*/
static char *ReplaceCharacterWithZero(char *haystack, char needle)
{
	char *charToZero  = strchr(haystack, needle);
	if(charToZero == NULL)
		return NULL;

	*charToZero = '\0';	
	return ++charToZero;

}

static int GetPointerToString(char *needle, char **toWrite)
{
	int nBytes;
	char *line = NULL;
	size_t len = 0;

	// Start the search from the beginning of the file
	fseek(configFile, 0, SEEK_SET);

	// Load the next line from the configFile Buffer
	while(getline(&line, &len, configFile) != -1) 
	{
		//Remove the carriage return
		ReplaceCharacterWithZero(line, '\n');

		//Remove anything to the right of the first # sign
		ReplaceCharacterWithZero(line, '#');

		// Now we search the beginning of the string for a "=" sign
		// We set the leftHandSide to be whatever there is before the =
		// and the rightHandSide to be whatever there is after the =
		char *leftHandSide   = line;
		char *rightHandSide  = ReplaceCharacterWithZero(line, '=');

		// Do we have a match for the leftHandSide? 
		// And is there an = sign?
		if(strstr(leftHandSide, needle) != NULL && rightHandSide != NULL)
		{
			// Skip to the first character that is not blank: " " or \t
			for(; isblank(*rightHandSide); rightHandSide++);

			// Allocate memory for the new string and then copy
			// it to the toWrite variable
			*toWrite =  malloc(strlen(rightHandSide));
			strcpy(*toWrite, rightHandSide);

			return 0;

		}
	}
	return -1;
}

int ReadString(char *needle, char **toWrite)
{
	return GetPointerToString(needle, toWrite);
}


int ReadInteger(char *needle, int *toWrite)
{
	char *toInput;
	if(GetPointerToString(needle, &toInput) < 0)
		return -1;

	*toWrite = atoi(toInput); 
	free(toInput);

	return 0;	
}

int ReadDouble(char *needle, double *toWrite)
{
	char *toInput;
	if(GetPointerToString(needle, &toInput) < 0)
		return -1;

	*toWrite = atof(toInput); 
	free(toInput);
	return 0;	
}