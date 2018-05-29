/**
@brief A small tool for parsing text files
@file 

ConfigurationParser is a quick-and-dirty tool for reading plain text files
and parsing the information for use. It's not very smart so you should be
a bit careful about using it!

The logic for the parser is as follows:

	1. Load configuration file
		1a. If cannot load file, return -1
	2. Load each line from the configuration file
	3. Disregard anything that comes after a #
	4. Search for an '=' character
	5. Search if anything left of '=' character matches the variable
		5a. Skip this line if there is no '=' character
	6. Search for anything right of '=' up to the end of the line
	7. Assign the contents of the right hand side to the toWrite variable

Further notes:

	1. All white spaces on left hand side are ignored unles they're part
		of the needle

	2. All white spaces before the first alphanumeric character on the 
		right hand side are ignored.

	3. All white spaces after the last alphanumeric character on the 
		right hand side are incorporated as part of toWrite

	4. Careful not to declare a variable that is contained with another:
		ABCDE = 456
		BCD = 123

		This is bad! The poor little ConfigurationParser won't get to BCD 

Example: myConfig.cfg
```
# This line will be ignored
Radial2015_IP 	= 192.168.1.10 #This comment will be ignored
Radial2015_PORT = 5000
```

Example: Test.c
```
#include "ConfigurationParser.h"
#include <stdio.h> //printf()
#include <stdlib.h> // free()

int main()
{
	SetConfigurationFile("myConfig.cfg");
	char *ip;
	int port;
	double angle;

	ReadString("Radial2015_IP", &ip);
	printf("Radial2015 IP: %s\n", ip);

	ReadInteger("Radial2015_PORT", &port);
	printf("Radial2015 PORT: %d\n", port);	

	free(ip); // Needed since this is a char
	// No free() is required for the integer

	return 0;
}
```

@authors David Brandman
*/

/**
@brief Set the file to read

Returns 0 if the file was read successfully, and -1 if there was a problem
*/
int SetConfigurationFile(char *path);

/**
@brief Find needle from the configuration file, and then assign pointer to toWrite

Note here that the ReadString() function as a malloc() call. This means that
*you* are responsible for setting *toWrite free

*/
int ReadString(char *needle, char **toWrite);

/** @brief Find needle from configuration file and assign integer to toWrite */
int ReadInteger(char *needle, int *toWrite);

/** @brief Find needle from configuration file and assign double to toWrite */
int ReadDouble(char *needle, double *toWrite);
