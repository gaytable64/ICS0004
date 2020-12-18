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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee
{
	char* pFirstName, * pMiddleName, * pLastName;
	int Brutto, TaxCoefficient, Netto;
} EMPLOYEE;
int NameCounter(char* pInput)
{
	int cc = 0;
	pInput = strpbrk(pInput, "ABCDEFGHIJKLMNOPQRSTUVXYZ");
	pInput = strchr(pInput, ' ');
	if (pInput)
	{
		cc++;
		while (pInput)
		{
			pInput = strchr(pInput + 1, ' ');
			if (pInput)
			{
				cc++;
			}
		}
	}
	return cc;
}
EMPLOYEE* Salary(char* pInput)
{
	int n = NameCounter(pInput);
	EMPLOYEE* salary = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
	char* token;

	pInput = strpbrk(pInput, "ABCDEFGHIJKLMNOPQRSTUVXYZ");
	token = strtok(pInput, " ;");
	salary[0].pFirstName = (char*)malloc(strlen(token) + 1);
	strcpy(salary[0].pFirstName, token);

	token = strtok(NULL, " ;");
	if (n == 3)
	{
		salary[0].pMiddleName = (char*)malloc(strlen(token) + 1);
		strcpy(salary[0].pMiddleName, token);
		token = strtok(NULL, " ;");
	}
	else if (n == 2)
		salary[0].pMiddleName = NULL;

	salary[0].pLastName = (char*)malloc(strlen(token) + 1);
	strcpy(salary[0].pLastName, token);

	token = strtok(NULL, " ;");
	salary[0].Brutto = atoi(token);

	if (salary[0].Brutto >= 10000)
	{
		salary[0].TaxCoefficient = 25;
	}
	else if ((7500 <= salary[0].Brutto) && (salary[0].Brutto < 10000))
	{
		salary[0].TaxCoefficient = 20;
	}
	else if ((5000 <= salary[0].Brutto) && (salary[0].Brutto < 7500))
	{
		salary[0].TaxCoefficient = 15;
	}
	else if (salary[0].Brutto < 5000)
	{
		salary[0].TaxCoefficient = 0;
	}
	double temp = (100 - salary[0].TaxCoefficient) * 0.01;
	salary[0].Netto = salary[0].Brutto * temp; //EHHEZ KELLETT A MATEK 4-es HE!

	return salary;
}

int main()
{
	char pInput[] = { ":   John James Bertold 7500;" };
	EMPLOYEE* final = Salary(pInput);
	printf("FirstName: %s\nMiddleName: %s\nLastName: %s\nBruttoSalary: %d\nNettoSalary: %d\nTaxCoefficent: %d\n", final[0].pFirstName, final[0].pMiddleName, final[0].pLastName, final[0].Brutto, final[0].Netto, final[0].TaxCoefficient);
	return 0;
}