/*
 * Test 3.

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



typedef struct item
{
	char* pName;
	int quantity, write_off; //write_off: 0, if not expired yet, 1 if expired ez mennyire buzis már
} ITEM;

ITEM* product(char* pInput, char* pItemName)
{
	ITEM* prod = (ITEM*)malloc(sizeof(ITEM));
	/*	char* lookup = strstr(pInput, pItemName);
		if (lookup == nullptr)
			return 0;
		if (strncmp(pInput,pItemName,strlen(pItemName)) == 0)
		prod[0].pName = (char*)malloc(strlen(pItemName) + 1);
		strcpy(prod[0].pName, pItemName);

		lookup = strpbrk(lookup, "0123456789");
		prod[0].quantity = atoi(lookup);

		lookup = strchr(lookup, '-');
		lookup = strpbrk(lookup, "0123456789");
		int temp_writeoff = atoi(lookup);
		if (temp_writeoff )
		{

		}
	*/
	char* lookup; //To jump
	char* token; //To split
	int cc = 0;
	token = strtok(pInput, "]");
	while (cc != 3)
	{
		cc = 0;
		//		printf("%s", token);

		//Go trough each ]
		char* lookup = strstr(token, pItemName);
		if (lookup == nullptr)
			token = strtok(NULL, "]");
		//			return 0;
		//Check if strstr exist
		else
		{
			prod[0].pName = (char*)malloc(strlen(pItemName) + 1);
			strcpy(prod[0].pName, pItemName);
			cc++;
		}
		//if exist fill the itemname

		lookup = strstr(token, "Quantity");
		//Put he lookup to quantity
		lookup = strpbrk(lookup, "0123456789");
		prod[0].quantity = atoi(lookup);
		cc++;
		//Fill the quantity
		lookup = strchr(token, '-');
		lookup = (lookup + 1);
		//Go to the unique "-" and then jump from it to the correct date
		int temp_writeoff = atoi(lookup);
		if (temp_writeoff >= 2019)
		{
			prod[0].write_off = 0;
			cc++;
		}
		else
		{
			prod[0].write_off = 1;
			cc++;
		}
	}
	return prod;
}

int main()
{
	//Ha usertol akarod bekerni
	/*char line[201];
	printf("Give me the input: \n");
	gets_s(line);
	char* pInput = (char *)malloc(strlen(line) + 1);
	strcpy(pInput, line);
	printf("Give me the item name: \n");
	gets_s(line);
	char* pItemName = (char*)malloc(strlen(line) + 1);
	strcpy(pItemName, line);
	*/
	//Ha kell teszteléshez
	char pInput[] = "[Name: Mackerel   Quantity: 150000   Expires: 10-2019   ]   [ Quantity: 500   Name: Sardinen   Expires: 12-2017   ]   [ Expires: 1-2020   Quantity: 10000    Name: Tuna   ]";
	char pItemName[] = "Mackerel";
	//A product strucot belerakom a finalba
	ITEM* final = product(pInput, pItemName);
	//printelem a final osszes elemet egyesevel
	printf("Date of expire: before January 2019. 0 if not expired, 1 if expired.\n");
	printf("Name:%s, Quantity:%d, Expired:%d\n\n\n", final[0].pName, final[0].quantity, final[0].write_off);
	//felszabaditok memoria teruletet
	free(final);
	return 0;
}
