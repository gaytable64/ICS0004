/*
 * Test 4.

Write a function with prototype:
ITEM *Exam(char *pInput,  int *pnItems);

Here:
typedef struct item
{
char *pName;
int Quantity, Price, Total;
} ITEM;

and the input string consists of segments “<item_name>, <quantity>, <price>;”
for example:   Shirt, 100, 15;   Jacket, 250, 120;

The number of segments is not restricted.
There is only one space between the components of segments (i.e. after comma).
But there may be any numbers (except 0 pieces) of spaces between segments (i.e. after semicolon)
The item name stats with Uppercase letter, and do not contain spaces.
The semicolon is after each segment.

The function must create an array of ITEM structs and, extracting the needed information from the input string, fill its fields for each item.
The function returns the pointer to the created array.
The number of created items must be stored into field pointed by parameter pnItems.
You may suppose that the input string is absolutely correct, i.e. its checking is not needed.

To get Total, multiply Quantity and Price -> Total = Quantity*Price

Write also main to test the code.

 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif



#include <stdio.h>
#include "stdlib.h"
#include <string.h>


typedef struct item
{
	char* pName;
	int Quantity, Price, Total;
} ITEM;

int ItemCounter(char* pInput)
{
	pInput = strchr(pInput, ';');
	int cc = 0;
	if (pInput)
	{
		cc++;
	}
	while (pInput)
	{
		pInput = strchr(pInput + 1, ';');
		if (pInput)
		{
			cc++;
		}
	}
	return cc;
}

ITEM* Price(char* pInput, int* pnItems)
{
	ITEM* to_fill = (ITEM*)malloc(sizeof(ITEM) * (*pnItems));
	char* coma;
	for (int i = 0; i < *pnItems; i++)
	{
		//Put the pInput to the correct starting point and fill the name
		pInput = strpbrk(pInput, "ABCDEFGHIJKLMNOPQRSTUVXYZ");
		coma = strchr(pInput, ',');
		*coma = 0;
		to_fill[i].pName = (char*)malloc(strlen(pInput) + 1);
		strcpy(to_fill[i].pName, pInput);
		*coma = ',';

		//Put the pInput to the correct quantity then fill it
		pInput = strpbrk(pInput, "0123456789");
		to_fill[i].Quantity = atoi(pInput);

		//Put the pInput to the correct price then fill it
		pInput = strchr(pInput, ',');
		pInput = strpbrk(pInput, "0123456789");
		to_fill[i].Price = atoi(pInput);

		to_fill[i].Total = to_fill[i].Quantity * to_fill[i].Price;
	}
	return to_fill;
}

int main()
{
	char pInput[] = { "    Shirt, 100, 50;       Jacket, 250, 120;     Pullover, 1, 1000; Plasticdick, 4, 14000;" };
	int pnItems = ItemCounter(pInput);
	ITEM* total_price = Price(pInput, &pnItems);
	int sum = 0;
	for (int i = 0; i < pnItems; i++)
	{
		printf("Name: %s, Quantity: %d, Price: %d Total: %d\n", total_price[i].pName, total_price[i].Quantity, total_price[i].Price, total_price[i].Total);
		free(total_price[i].pName);
		sum += total_price[i].Total;

	}
	printf("The total sum is: %d", sum);
	free(total_price);
	return 0;
}