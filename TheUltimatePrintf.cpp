#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <string.h>


int main()
{

	char s[100];

	printf("Want pizza? yes or no\n");
	scanf("%s", s);

	if (strcmp(s, "yes") == 0)
	{
		printf("Get pizza");
	}
	else if (strcmp(s, "no") == 0)
	{
		printf("get out");
	}
	else
	{
		printf("What?");
	}
	return 0;
}