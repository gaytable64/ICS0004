/*
*
Test 3.

Write a function with prototype:
Student *Exam(char *pInput,  char *pItemName);

Here:
typedef struct item
{
char *pName;
int quantity, write_off; //write_off: 0, if not expired yet, 1 if expired
} ITEM;

and the input string consists of segments enclosed into brackets.

The segments contain 3 components: “ Name: <string>   Quantity: <integer>   Expires: <integer>-<integer>   ”
The order of components may be any. Example:
[ Name: Mackerel   Quantity: 1000   Expires: 10–2018   ]   [ Quantity: 500   Name: Sardine   Expires: 12–2017   ]   [ Expires: 1–2020   Quantity: 10000    Name: Tuna   ]

The number of spaces in components and between segments is any except zero (as many as you want) but after colon (:) only one.
There are also spaces before ] and after [ .
The item name does not contain spaces.

The function must create a struct ITEM for item whos name is specified by the pointer pItemName and, extracting the needed information from the input string, fill its fields. The function returns the pointer to the created struct.

You may suppose that the input string is absolutely correct, i.e. its checking is not needed.
However, the item with the specified name may be not present in the input string. In that case the function must return 0.
To know whether the item must be write off, compare the date of expire with January 2019.

Write also main to test the code.

*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define KEYWORD_NAME "Name:"
#define KEYWORD_QUANTITY "Quantity:"
#define KEYWORD_EXPIRES "Expires:"

typedef struct item
{
	char* pName;
	int quantity, write_off; //write_off: 0, if not expired yet, 1 if expired
} ITEM;


/*  The segments contain 3 components: “ Name: <string>   Quantity: <integer>   Expires: <integer>-<integer>   ”
*/
ITEM* Exam(char* pInput, char* pItemName); //prototype



ITEM* Exam(char* pInput, char* pItemName) //pItemName will be pName, pInput will be q and wr
{
	ITEM* pItem;
	pItem = (ITEM*)malloc(sizeof(ITEM)); //the input will be dynamic

	//Find segments
	char* charFind;
	char* segmFind = 0;
	int count = 0;

	//Expires
	int month = 0;
	int year = 0;


	/* FIND SEGMENTS*/
	charFind = strstr(pInput, pItemName); //finds a character in a string
	if (charFind == NULL)
	{
		printf("Item not found - %s\n", pItemName);
		exit(1);
	}
	else
	{
		do 
		{
			if (*(charFind - count) == '[') //count is increasing, charFind is all length, - count length == [ start of the segment
			{
				segmFind = charFind - count; //segmFind sets the start of the segment to 
				break;
			}
			count++;
			
			//printf("%d\n", count); //test count //writes the output to the right char place.
			//printf("%s\n", charFind); //test charFind //writes the whole table till the [ and one segment less until the next [ to every places //input format, cuts down the [ and the spaces
			//printf("%s\n", segmFind); //test segmFind //writes nulls and the actual output to the starting places


		} while (*charFind != '\0'); //counts until find the last char
		//this

	}


	
	//pName
	pItem->pName = (char*)malloc(strlen(pItemName)); //function->struct name = dynamically allocates the size of pItemName string length // sizeof did not work
	strcpy(pItem->pName, pItemName);//copies the string from pItemName to function->struct name. //strcpy ignores the spaces

	//printf("%s\n\n", pItemName); finds and prints only the name, skip [ and spaces

	
	//Quantity
	charFind = strstr(segmFind, KEYWORD_QUANTITY); //sets the character find value equals to segmentfind from Quantity
	pItem->quantity = atoi(charFind + strlen(KEYWORD_QUANTITY)); // charFind + the Keyword length translated to integer 

	//printf("%s\n\n", charFind); //prints from the first quantity
	//printf("%s\n\n", segmFind); // prints the input array
	//printf("%s\n", charFind); //test charFind //writes the whole table till the [ and one segment less until the next [ to every places //input format, cuts down the [ and the spaces
	//printf("%s\n", segmFind); //test segmFind //writes nulls and the actual output to the starting places


	/*EXPIRES*/
	charFind = strstr(segmFind, KEYWORD_EXPIRES); // sets the character find value equals to segmentfind from Expires
	month = atoi(charFind + strlen(KEYWORD_EXPIRES)); // charFind + the Keyword length translated to integer
	//printf("%s\n\n", charFind); //prints from the first expires
	//printf("%s\n\n", segmFind); // prints the input array

	
	charFind = strstr(segmFind, "-"); //sets the character find value equals to segmentfind from -
	year = atoi(charFind + 1); // charFind + the rest translated to integer
	//printf("%s\n\n", charFind); //prints from the first quantity
	//printf("%s\n\n", segmFind); // prints the input array

	
	if (year < 2019 || (month <= 1 && year == 2019)) {
		pItem->write_off = 1;
		printf("%s %d-%d: Expired - ",KEYWORD_EXPIRES, month, year);
	}
	else {
		pItem->write_off = 0;
		printf("%s %d-%d: Not expired - ",KEYWORD_EXPIRES, month, year);
	}

	return pItem;
}

int main() {

	char sInput[] = "[ Name: Mackerel   Quantity: 1000   Expires: 10-2018   ]   [ Quantity: 500   Name: Sardine   Expires: 12-2017   ]   [ Expires: 1-2020   Quantity: 10000    Name: Tuna   ]";
	char sItemName1[] = "Mackerel";
	char sItemName2[] = "Sardine";
	char sItemName3[] = "Tuna";
	char sItemName4[] = "Whale";
	ITEM* Output;
	printf("Expire Date: January 2019\nExpires: if not expired: 0, if expired: 1\n\n");

	
	Output = Exam(sInput, sItemName1);
	printf("Name: %s, Quantity: %d, Expires: %d\n", Output->pName, Output->quantity, Output->write_off);
    free(Output);

	Output = Exam(sInput, sItemName2);
	printf("Name: %s, Quantity: %d, Expires: %d\n", Output->pName, Output->quantity, Output->write_off);
	free(Output);

	Output = Exam(sInput, sItemName3);
	printf("Name: %s, Quantity: %d, Expires: %d\n", Output->pName, Output->quantity, Output->write_off);
	free(Output);
	Output = Exam(sInput, sItemName4);
	printf("Name: %s, Quantity: %d, Expires: %d\n", Output->pName, Output->quantity, Output->write_off);
	free(Output);

	printf("\n\n\n");

    return 0;

}
