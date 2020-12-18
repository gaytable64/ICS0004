#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define TEST1_LAST_NAME_NDX 0
#define TEST1_FIRST_NAME_NDX 1
#define TEST1_BIRSTDAY_DAY_NDX 3
#define TEST1_BIRSTDAY_MONTH_NDX 4
#define TEST1_BIRSTDAY_YEAR_NDX 5
#define TEST1_NATIONALITY_NDX 7

typedef struct
{
	int day;
	char month[4];
	int year;
} DATE;

typedef struct
{
	const char* pFirstName, * pLastName, * pNationality;
	DATE Birthdate;
} STUDENT;

typedef char* PATTERNELEMENTP;

int Exam(STUDENT* pStudents, int nStudents, const char* pPattern);

/* The pattern is a string formatted as “<last-name>, <first-name> born <day> <month-in-English> <year> from <country>” */
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern)
{
	int ii;
	int nFirstNameLen, nLastNameLen, nNationalityLen;
	PATTERNELEMENTP pPatternElement[8];
	char nPatternElement[8];
	char TmpBuff[8];
	char* pTmp;
	int nLen;
	int bFoundFlag;

	if (pStudents == NULL || pPattern == NULL)
	{
		bFoundFlag = FALSE;
	}
	else
	{
		pPatternElement[0] = (char*)pPattern;
		pTmp = (char*)pPattern;
		nLen = 0;
		ii = 0;

		while (*pTmp)
		{
			if (*pTmp == ' ')
			{
				nPatternElement[ii++] = nLen;
				pTmp++;
				nLen = 0;
				pPatternElement[ii] = pTmp;
			}
			else
			{
				pTmp++;
				nLen++;
			}
		}

		nPatternElement[ii] = nLen;
		nLen = 0;
		nPatternElement[0] = nPatternElement[0] - 1;

		for (int ii = 0; ii < nStudents; ii++)
		{
			bFoundFlag = TRUE;

			nFirstNameLen = strlen(pStudents[ii].pFirstName);
			nLastNameLen = strlen(pStudents[ii].pLastName);
			nNationalityLen = strlen(pStudents[ii].pNationality);

			if (bFoundFlag)
			{
				if (nPatternElement[TEST1_FIRST_NAME_NDX] == nFirstNameLen)
				{
					if (strncmp(pPatternElement[TEST1_FIRST_NAME_NDX], pStudents[ii].pFirstName, nFirstNameLen) != 0)
					{
						bFoundFlag = FALSE;
					}
				}
				else
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag)
			{
				if (nPatternElement[TEST1_LAST_NAME_NDX] == nLastNameLen)
				{
					if (strncmp(pPatternElement[TEST1_LAST_NAME_NDX], pStudents[ii].pLastName, nLastNameLen) != 0)
					{
						bFoundFlag = FALSE;
					}
				}
				else
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag)
			{
				if (nPatternElement[TEST1_NATIONALITY_NDX] == nNationalityLen)
				{
					if (strncmp(pPatternElement[TEST1_NATIONALITY_NDX], pStudents[ii].pNationality, nNationalityLen) != 0)
					{
						bFoundFlag = FALSE;
					}
				}
				else
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag)
			{
				strncpy((char*)&TmpBuff, pPatternElement[TEST1_BIRSTDAY_DAY_NDX], nPatternElement[TEST1_BIRSTDAY_DAY_NDX]);
				TmpBuff[nPatternElement[TEST1_BIRSTDAY_DAY_NDX]] = '\0';

				if (atoi((char*)&TmpBuff) != pStudents[ii].Birthdate.day)
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag)
			{
				if (strncmp(pPatternElement[TEST1_BIRSTDAY_MONTH_NDX], pStudents[ii].Birthdate.month, 3) != 0)
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag)
			{
				strncpy((char*)&TmpBuff, pPatternElement[TEST1_BIRSTDAY_YEAR_NDX], nPatternElement[TEST1_BIRSTDAY_YEAR_NDX]);
				TmpBuff[nPatternElement[TEST1_BIRSTDAY_YEAR_NDX]] = '\0';

				if (atoi((char*)&TmpBuff) != pStudents[ii].Birthdate.year)
				{
					bFoundFlag = FALSE;
				}
			}

			if (bFoundFlag) break;
		}
	}
	return bFoundFlag;
}

void main(int argc, char** argv[])
{
		
	STUDENT students[] = {
	{ "John", "Smith", "Britain", {1, "Feb", 2000 } },
	{ "Mary", "Weaver", "USA", { 2, "Mar", 2001 } },
	{ "James", "Carpenter", "Canada", {11, "Oct", 2002 } },
	{ "Elizabeth", "Clerk", "Ireland", { 21, "Dec", 2001 } }
	};
	const char* ptoSearch1 = "Smith, John born 1 February 2000 from Britain";
	printf("Smith, John born 1 February 2000 from Britain: %d\n", Exam(students, 4, ptoSearch1));

	const char* ptoSearch2 = "Weaver, Mary born 2 March 2001 from USA";
	printf("Weaver, Mary born 2 March 2001 from USA: %d\n", Exam(students, 4, ptoSearch2));

	const char* ptoSearch3 = "Carpenter, James born 11 October 2002 from Canada";
	printf("Carpenter, James born 11 October 2002 from Canada: %d\n", Exam(students, 4, ptoSearch3));

	const char* ptoSearch4 = "Clerk, Elizabeth born 21 December 2001 from Ireland";
	printf("Clerk, Elizabeth born 21 December 2001 from Ireland: %d\n", Exam(students, 4, ptoSearch4));

	const char* ptoSearch5 = "Matveev, Benedek born 30 June 1996 from Hungary";
	printf("Matveev, Benedek born 30 June 1996 from Hungary: %d\n", Exam(students, 4, ptoSearch5));
}
