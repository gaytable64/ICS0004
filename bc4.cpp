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

and the input string consists of segments <item_name>, <quantity>, <price>;
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


#include<stdio.h>
#include<string.h>
#include<stdlib.h>



typedef struct item
{
    char* pName;
    int Quantity, Price, Total;
}ITEM;

ITEM* Exam(char* pInput, int* pnItems);

ITEM* Exam(char* pInput, int* pnItems)
{
    ITEM* pItems;
    pItems = (ITEM*)malloc(*pnItems * sizeof(ITEM));

    char* charFind;
    char* segmFind;
    int i = 0; //counter



    //set flag at the beginning of the input string
    charFind = pInput;
    for (i = 0; i < *pnItems; i++) 
    {
        //pName
        segmFind = strstr(charFind, ",");
        *(segmFind) = '\0';
        pItems[i].pName = (char*)malloc(strlen(charFind));
        strcpy(pItems[i].pName, charFind);
        *(segmFind) = ',';

        //Quantity
        charFind = segmFind + 1;
        segmFind = strchr(charFind, ',');
        pItems[i].Quantity = atoi(charFind);

        //Price
        charFind = segmFind + 1;
        segmFind = strchr(charFind, ';');
        pItems[i].Price = atoi(charFind);

        //Total
        pItems[i].Total = pItems[i].Quantity * pItems[i].Price;

        int j = 1;
        while (*(segmFind + j) == ' ') 
        {
            j++;
        }
        charFind = segmFind + j;

    }
    return pItems;
}

int counter(char* pInput)
{
    pInput = strchr(pInput, ';');
    int i = 0;
    if (pInput)
    {
        i++;
    }
    while (pInput)
    {
        pInput = strchr(pInput + 1, ';');
        if (pInput)
        {
            i++;
        }
    }
    return i;
}

int main()
{

    char sInput[] = "Shirt, 100, 15;   Jacket, 250, 120;     Coat, 10, 20;   ";
    int nItems = counter(sInput);
    ITEM* pItem;

    pItem = Exam((char*)&sInput, (int*)&nItems);

    int i;
    for (i = 0; i < nItems; i++) 
    {
        printf("Item Name:%s, Quantity:%d, Price:%d, Total:%d;\n", pItem[i].pName, pItem[i].Quantity, pItem[i].Price, pItem[i].Total);
    }
    free(pItem);
}