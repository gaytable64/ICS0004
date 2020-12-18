/*
 * Test 5.

Write a function with prototype:
EMPLOYEE *Exam(char *pInput);

Here:
typedef struct employee
{
char *pFirstName, *pMiddleName, *pLastName;
int Brutto, TaxCoefficient, Netto;
} EMPLOYEE;

and the input string format is “<first_name> <middle_name> <last_name> <brutto_income>;”
for example:   John James Smith 15000;
The middle name is optional, i.e. the input string may be also like:   John Smith 15000;
The brutto income is an integer. There is only one space between components.

The tax coefficient is 25% if the brutto income exceeds 10000,
20% if the brutto income is between 7500 and 10000,
15% if the brutto income is between 5000 and 7500,
0% if the brutto income is less that 5000.

The function must allocate memory for output struct and, extracting the needed information from the input string, fill its fields.
If middle name is not present, the pointer to it must be zero.
The function returns the pointer to the created struct.

You may suppose that the input string is absolutely correct, i.e. its checking is not needed.

Write also main to test the code.

 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct employee {
    char* pFirstName, * pMiddleName, * pLastName;
    int Brutto, TaxCoefficient, Netto;
}EMPLOYEE;

EMPLOYEE* Exam(char* pInput);
void BruttoCalc(EMPLOYEE* pEmployee);


EMPLOYEE* Exam(char* pInput) {
    EMPLOYEE* Employee = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));

    int spaces = 0;
    int i = 0;
    while (pInput[i] != '\0') {
        if (pInput[i] == ' ')spaces++;
        i++;
    }
    int isMiddle = 0;
    if (spaces == 3)isMiddle = 1;

    char* flag;
    //set the flag at the beginning of the input
    flag = pInput;
    i = 0;
    int process = 0;
    while (pInput[i] != '\0') {
        if (pInput[i] == ' ') {
            pInput[i] = '\0';

            if (process == 0) {
                //First Name
                Employee->pFirstName = (char*)malloc(sizeof(char) * strlen(flag) + 1);
                strcpy(Employee->pFirstName, flag);
            }
            if (process == 1 && isMiddle == 1) {
                //Middle Name if it exsits
                Employee->pMiddleName = (char*)malloc(sizeof(char) * strlen(flag) + 1);
                strcpy(Employee->pMiddleName, flag);
            }
            if (process == 1 && isMiddle == 0) {
                //Middle Name if it does not exist
                Employee->pMiddleName = NULL;
            }
            if ((process == 2 && isMiddle == 1) || (process == 1 && isMiddle == 0)) {
                //Last Name
                Employee->pLastName = (char*)malloc(sizeof(char) * strlen(flag) + 1);
                strcpy(Employee->pLastName, flag);

                //Brutto
                flag = pInput + i + 1;
                Employee->Brutto = atoi(flag);
            }

            pInput[i] = ' ';
            flag = pInput + i + 1;
            process++;
        }
        i++;
    }
    BruttoCalc(Employee);

    return Employee;
}

void BruttoCalc(EMPLOYEE* pEmployee) {
    //10000<= Brutto
    if (pEmployee->Brutto >= 10000) {
        pEmployee->TaxCoefficient = 25;
        pEmployee->Netto = pEmployee->Brutto * 75 / 100;
    }
    //7500<= Brutto < 10000
    if (pEmployee->Brutto >= 7500 && pEmployee->Brutto < 10000) {
        pEmployee->TaxCoefficient = 20;
        pEmployee->Netto = pEmployee->Brutto * 80 / 100;
    }
    //5000<= Brutto < 7500
    if (pEmployee->Brutto >= 5000 && pEmployee->Brutto < 7500) {
        pEmployee->TaxCoefficient = 15;
        pEmployee->Netto = pEmployee->Brutto * 85 / 100;
    }
    //Brutto < 5000
    if (pEmployee->Brutto < 5000) {
        pEmployee->TaxCoefficient = 0;
        pEmployee->Netto = pEmployee->Brutto;
    }
}


int main() {
    //char Input[]="John James Smith 15000;";
    char Input[] = "John Smith 5000;";
    EMPLOYEE* result;

    result = Exam(Input);
    printf("FirstName:%s\nMiddleName:%s\nLastName:%s\n", result->pFirstName,
        result->pMiddleName,
        result->pLastName);
    printf("Brutto:%d\nTaxCoefficient:%d\nNetto:%d\n", result->Brutto,
        result->TaxCoefficient,
        result->Netto);

    return 0;
}
