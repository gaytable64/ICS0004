#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



#include <stdio.h>
#include <string.h>

int main()
{
	printf("What is your name ?: ");
	char name[100]; // '\0'
	scanf("%s", name);

	int letter = 0;
	while (name[letter] != '\0')
	{
		letter++;
	}

	//check name size
	printf("Size of name: %lu\n", strlen(name));

	//compare input without array
	if (strcmp(name, "Ben ") == 0 || strcmp(name, "ben ")) // oly prints good if gives extra space
	{
		printf("Access \n");
	}
	else
	{
		printf("No access \n");
	}

	// copy name to an other variable
	char copy[100];
	strcpy(copy, name); // copies from name to copy
	printf("Copy of name: %s\n", copy);


	// add other string to input
	char lastName[] = { " Matveev" };
	strcat(copy, lastName); //adds lastname to copy make it one var
	printf("Full name: %s\n", copy);



	return  0;
}
