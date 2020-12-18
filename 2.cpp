#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct student
{
	char* pName;
	int nMarks, * pMarks; //number of marks and pointer to array of marks 
	double AverageMark;
} STUDENT;


typedef STUDENT* STUDENTP;

STUDENTP Exam(char* pInput, char* pStudentName);


/*  The input string: “<name>, <mark1>, <mark2>, ... ;“
**  for example: "John Smith, 4, 2, 5, 3;   James Farmhand, 4; ..."
*/
STUDENTP Exam(char* pInpStr, char* pStudentName)
{
	STUDENTP pOutStruc;
	char* pName;
	char* pMarks{};
	char* pTmp;
	char TmpBuff[8];
	int* pMarkArr;
	int nNameLen;
	int nSegmentLen;
	int nAllocLen;
	int nNumOfMarks;
	int nSumOfMarks;
	int bNameFlag;
	int bFirstComma;

	if (pInpStr == NULL || pStudentName == NULL)
	{
		pOutStruc = NULL;
	}
	else
	{
		pName = strstr(pInpStr, pStudentName);
		if (pName == NULL)
		{
			pOutStruc = NULL;
		}
		else
		{
			pTmp = pName;
			nNumOfMarks = 0;
			nSegmentLen = 0;
			nNameLen = 0;
			bNameFlag = TRUE;
			bFirstComma = TRUE;
			while (*pTmp != ';')
			{
				if (*pTmp == ',')
				{
					nNumOfMarks++;
					if (bFirstComma)
					{
						bNameFlag = FALSE;
						pMarks = pTmp;
						bFirstComma = FALSE;
					}
				}

				if (bNameFlag == TRUE)
				{
					nNameLen++;
				}

				pTmp++;
				nSegmentLen++;
			}
		}

		nAllocLen = sizeof(STUDENT) + nNumOfMarks * sizeof(int) + nNameLen + 1;
		pOutStruc = (STUDENTP)malloc(nAllocLen);
		if (pOutStruc != NULL)
		{
			pOutStruc->pName = (char*)(pOutStruc + sizeof(STUDENT) + nNumOfMarks * sizeof(int));
			strncpy(pOutStruc->pName, pName, nNameLen);
			*(pOutStruc->pName + nNameLen) = '\0';
			pOutStruc->nMarks = nNumOfMarks;
			pOutStruc->pMarks = (int*)(pOutStruc + sizeof(STUDENT));

			pMarkArr = pOutStruc->pMarks;

			while (*pMarks != ';')
			{
				while (*pMarks == ' ' || *pMarks == ',')
				{
					pMarks++;
				}
				pTmp = (char*)&TmpBuff;

				while (*pMarks != ',' && *pMarks != ';')
				{
					*pTmp++ = *pMarks++;
				}
				*pTmp = '\0';
				*pMarkArr++ = atoi((char*)&TmpBuff);

			}

			nSumOfMarks = 0;
			for (int ii = 0; ii < nNumOfMarks; ii++)
			{
				nSumOfMarks += pOutStruc->pMarks[ii];
			}

			pOutStruc->AverageMark = (double)nSumOfMarks / nNumOfMarks;
		}
	}

	return pOutStruc;
}

void main(int argc, char** argv[])
{
	char sInpStr[] = { "John Smith, 4, 2, 5, 3;   James Farmhand, 4;   James Carpenter, 4, 4, 5;   Benedek Matveev, 5, 5, 5, 5;" };
	char sStudentName1[] = { "John Smith" };
	char sStudentName2[] = { "James Farmhand" };
	char sStudentName3[] = { "James Carpenter" };
	char sStudentName4[] = { "Benedek Matveev" };
	STUDENTP pStudent;

	pStudent = Exam((char*)&sInpStr, (char*)&sStudentName1);
	printf("Name: %s, ", pStudent->pName);
	printf("Number of mark(s): ");
	for (int ii = 0; ii < pStudent->nMarks; ii++)
	{
		printf("%d, ", pStudent->pMarks[ii]);
	}
	printf(";\n");
	free(pStudent);

	pStudent = Exam((char*)&sInpStr, (char*)&sStudentName2);
	printf("Name: %s, ", pStudent->pName);
	printf("Number of mark(s): ");
	for (int ii = 0; ii < pStudent->nMarks; ii++)
	{
		printf("%d, ", pStudent->pMarks[ii]);
	}
	printf(";\n");
	free(pStudent);

	pStudent = Exam((char*)&sInpStr, (char*)&sStudentName3);
	printf("Name: %s, ", pStudent->pName);
	printf("Number of mark(s): ");
	for (int ii = 0; ii < pStudent->nMarks; ii++)
	{
		printf("%d, ", pStudent->pMarks[ii]);
	}
	printf(";\n");
	free(pStudent);

	pStudent = Exam((char*)&sInpStr, (char*)&sStudentName4);
	printf("Name: %s, ", pStudent->pName);
	printf("Number of mark(s): ");
	for (int ii = 0; ii < pStudent->nMarks; ii++)
	{
		printf("%d, ", pStudent->pMarks[ii]);
	}
	printf(";\n");
	free(pStudent);
}
