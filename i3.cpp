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


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct item {
    char* pName;
    int quantity, write_off;
}ITEM;

ITEM* Exam(char* pInput, char* pItemName);


ITEM* Exam(char* pInput, char* pItemName) {

    char* find;
    find = strstr(pInput, pItemName);

    if (find == NULL) {
        printf("No existance\n");
        exit(1);
    }

    char* start = 0;
    int i = 0;
    while (*(find + i) != '\0') {
        if (*(find + i) == '[') {
            start = find + i;
            break;
        }
        i--;
    }

    ITEM* Item;
    Item = (ITEM*)malloc(sizeof(ITEM));

    //pName
    Item->pName = (char*)malloc(sizeof(char) * strlen(pItemName));
    strcpy(Item->pName, pItemName);

    //Quantity
    find = strstr(start, "Quantity: ");
    Item->quantity = atoi(find + strlen("Quantity: "));

    //Expires
    int month = 0;
    int year = 0;

    find = strstr(start, "Expires: ");
    month = atoi(find + strlen("Expires: "));

    find = strstr(start, "-");
    year = atoi(find + 1);

    if (year < 2019 || (month <= 1 && year == 2019)) {
        Item->write_off = 1;
    }
    else {
        Item->write_off = 0;
    }

    return Item;
}

int main() {

    char Input[] = "[ Name: Mackerel   Quantity: 1000   Expires: 10-2018   ]   [ Quantity: 500   Name: Sardine   Expires: 12-2017   ]   [ Expires: 1-2020   Quantity: 10000    Name: Tuna   ]";

    char ItemName[] = "Sardine";

    ITEM* result;
    result = Exam(Input, ItemName);

    printf("%s\n%d\n%d\n", result->pName,
        result->quantity,
        result->write_off);

    free(result->pName);
    free(result);
    return 0;

}