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


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct item {
    char* pName;
    int Quantity, Price, Total;
}ITEM;

ITEM* Exam(char* pInput, int* pnItems);

ITEM* Exam(char* pInput, int* pnItems) {
    ITEM* Items;
    Items = (ITEM*)malloc(*pnItems * sizeof(ITEM));

    char* start_flag;
    char* end_flag;

    //set flag at the beginning of the input string
    start_flag = pInput;

    int i = 0;
    for (i = 0; i < *pnItems; i++) {
        //pName
        end_flag = strstr(start_flag, ",");
        *(end_flag) = '\0';
        Items[i].pName = (char*)malloc(sizeof(char) * strlen(start_flag) + 1);
        strcpy(Items[i].pName, start_flag);
        *(end_flag) = ',';

        //Quantity
        start_flag = end_flag + 1;
        end_flag = strchr(start_flag, ',');
        Items[i].Quantity = atoi(start_flag);

        //Price
        start_flag = end_flag + 1;
        end_flag = strchr(start_flag, ';');
        Items[i].Price = atoi(start_flag);

        //Total
        Items[i].Total = Items[i].Quantity * Items[i].Price;

        int j = 1;
        while (*(end_flag + j) == ' ') {
            j++;
        }
        start_flag = end_flag + j;

    }
    return Items;
}

int main() {
    char Input[] = "Shirt, 100, 15;   Jacket, 250, 120;     Coat, 10, 20;   ";
    int nItems = 3;
    ITEM* pItem;

    pItem = Exam(Input, &nItems);

    int i;
    for (i = 0; i < nItems; i++) {
        printf("Item No.%d\nItem Name:%s\nQuantity:%d\nPrice:%d\nTotal:%d\n",
            i + 1,
            pItem[i].pName,
            pItem[i].Quantity,
            pItem[i].Price,
            pItem[i].Total);
        free(pItem[i].pName);
    }
    free(pItem);
}