
#include <stdio.h>
#include "ConfigurationParser.h"
#include <stdlib.h>

int main()
{
	SetConfigurationFile("myConfig.cfg");
	char *ip;
	int port;
	double myNumber;

	ReadString("MyIP", &ip);
	printf("IP: %s\n", ip);

	ReadInteger("MyPort", &port);
	printf("Port: %d\n", port);	

	ReadDouble("MyNumber", &myNumber);
	printf("Number: %f\n", myNumber);	
	

	free(ip);

	return 0;
}
