/*
 *
 Test 5.

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

#define FALSE 0
#define TRUE 1

typedef struct employee
{
	char* pFirstName, * pMiddleName, * pLastName;
	int Brutto, TaxCoefficient, Netto;
} EMPLOYEE;




/*  The input string format: “<first_name> <middle_name> <last_name> <brutto_income>;”
**  for example:   John James Smith 15000;
*/
EMPLOYEE* Exam(char* pInput)
{
	int ii;

	EMPLOYEE* pOutStruc;
	char* pItem[4];
	char* pTmp;
	char BuffBrutto[16];
	int nNumberOfSegments;
	int nItemLen[4];
	int nBruttoIncome;
	int nNettoIncome;
	int nTaxCoefficient;
	int bEndOfSearch;

	nNumberOfSegments = 0;

	if (pInput == NULL)
	{
		pOutStruc = NULL;
	}
	else
	{
		pOutStruc = NULL;

		pTmp = pInput;
		bEndOfSearch = FALSE;
		ii = 0;

		while (!bEndOfSearch)
		{
			nItemLen[ii] = 0;

			/* Skip leading spaces */
			while (TRUE)
			{
				/* End of the input string */
				if (*pTmp == '\0')
				{
					bEndOfSearch = TRUE;

					break;
				}
				else
				{
					if (*pTmp != ' ' && *pTmp != ';')
					{
						/* The first character of the input string item */
						pItem[ii] = pTmp;
						nItemLen[ii]++;
						pTmp++;

						break;
					}
				}
			}

			if (!bEndOfSearch)
			{
				/* Input string item */
				while (*pTmp != ' ' && *pTmp != ';')
				{
					nItemLen[ii]++;
					pTmp++;
				}

				ii++;

				if (*pTmp == ';')
				{
					/* Number of items */
					nNumberOfSegments = ii;

					bEndOfSearch = TRUE;
				}
				else
				{
					/* Skip spaces between name and quantity */
					while (*pTmp == ' ') pTmp++;
				}
			}
		}


		if (nNumberOfSegments > 0)
		{
			switch (nNumberOfSegments)
			{
			case 3:
				/* Pointer to the output structure */
				pOutStruc = (EMPLOYEEP)malloc(sizeof(EMPLOYEE) + nItemLen[0] + nItemLen[1] + 2);
				pTmp = (char*)pOutStruc + sizeof(EMPLOYEE);

				/* First name */
				pOutStruc->pFirstName = pTmp;
				strncpy(pTmp, pItem[0], nItemLen[0]);
				pTmp += nItemLen[0];
				*pTmp++ = '\0';

				/* Midle name */
				pOutStruc->pMiddleName = NULL;

				/* Last name */
				pOutStruc->pLastName = pTmp;
				strncpy(pTmp, pItem[1], nItemLen[1]);
				pTmp += nItemLen[1];
				*pTmp++ = '\0';

				/* Brutto income */
				strncpy((char*)&BuffBrutto, pItem[2], nItemLen[2]);

				break;
			case 4:
				/* Pointer to the output structure */
				pOutStruc = (EMPLOYEEP)malloc(sizeof(EMPLOYEE) + nItemLen[0] + nItemLen[1] + nItemLen[2] + 3);
				pTmp = (char*)pOutStruc + sizeof(EMPLOYEE);

				/* First name */
				pOutStruc->pFirstName = pTmp;
				strncpy(pTmp, pItem[0], nItemLen[0]);
				pTmp += nItemLen[0];
				*pTmp++ = '\0';

				/* Midle name */
				pOutStruc->pMiddleName = pTmp;
				strncpy(pTmp, pItem[1], nItemLen[1]);
				pTmp += nItemLen[1];
				*pTmp++ = '\0';

				/* Last name */
				pOutStruc->pLastName = pTmp;
				strncpy(pTmp, pItem[2], nItemLen[2]);
				pTmp += nItemLen[2];
				*pTmp++ = '\0';

				/* Brutto income */
				strncpy((char*)&BuffBrutto, pItem[3], nItemLen[3]);

				break;
			default:
				break;
			}

			nBruttoIncome = atoi((char*)&BuffBrutto);
			pOutStruc->Brutto = nBruttoIncome;
			if (nBruttoIncome > 10000)
			{
				nTaxCoefficient = 25;
			}
			else if (nBruttoIncome > 7500)
			{
				nTaxCoefficient = 20;
			}
			else if (nBruttoIncome > 5000)
			{
				nTaxCoefficient = 15;
			}
			else
			{
				nTaxCoefficient = 0;
			}

			nNettoIncome = nBruttoIncome / nTaxCoefficient;
			pOutStruc->TaxCoefficient = nTaxCoefficient;
			pOutStruc->Netto = nNettoIncome;
		}
	}

	return pOutStruc;
}

void main(int argc, char** argv[])
{
	char sInpStr1[] = { "John James Smith 15000;" };
	char sInpStr2[] = { "John Smith 8000;" };
	char sInpStr3[] = { "Benedek Matveev 1000000;" };
	EMPLOYEEP pEmployee;

	pEmployee = Exam((char*)&sInpStr1);
	if (pEmployee == NULL)
	{
		printf("Error\n");
	}
	else
	{
		printf("First Name: %s, ", pEmployee->pFirstName);
		if (pEmployee->pMiddleName == NULL)
		{
			printf("Middle Name: - ");
		}
		else
		{
			printf("Middle Name: %s, ", pEmployee->pMiddleName);
		}
		printf("Last Name: %s, ", pEmployee->pLastName);
		printf("Brutto: %d, ", pEmployee->Brutto);
		printf("Tax coefficient: %d, ", pEmployee->TaxCoefficient);
		printf("Netto: %d\n", pEmployee->Netto);

		free(pEmployee);
	}

	pEmployee = Exam((char*)&sInpStr2);
	if (pEmployee == NULL)
	{
		printf("Error\n");
	}
	else
	{
		printf("First Name: %s, ", pEmployee->pFirstName);
		if (pEmployee->pMiddleName == NULL)
		{
			printf("Middle Name: -, ");
		}
		else
		{
			printf("Middle Name: %s, ", pEmployee->pMiddleName);
		}
		printf("Last Name: %s, ", pEmployee->pLastName);
		printf("Brutto: %d, ", pEmployee->Brutto);
		printf("Tax coefficient: %d, ", pEmployee->TaxCoefficient);
		printf("Netto: %d\n", pEmployee->Netto);

		free(pEmployee);
	}

	pEmployee = Exam((char*)&sInpStr3);
	if (pEmployee == NULL)
	{
		printf("Error\n");
	}
	else
	{
		printf("First Name: %s, ", pEmployee->pFirstName);
		if (pEmployee->pMiddleName == NULL)
		{
			printf("Middle Name: -, ");
		}
		else
		{
			printf("Middle Name: %s, ", pEmployee->pMiddleName);
		}
		printf("Last Name: %s, ", pEmployee->pLastName);
		printf("Brutto: %d, ", pEmployee->Brutto);
		printf("Tax coefficient: %d, ", pEmployee->TaxCoefficient);
		printf("Netto: %d\n", pEmployee->Netto);

		free(pEmployee);
	}
}