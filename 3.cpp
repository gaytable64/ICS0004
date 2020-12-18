#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define TEST3_KEYWORD_NAME "Name:"
#define TEST3_KEYWORD_QUANTITY "Quantity:"
#define TEST3_KEYWORD_EXPIRES "Expires:"

typedef struct item
{
	char* pName;
	int quantity, write_off; //write_off: 0, if not expired yet, 1 if expired
} ITEM;

typedef ITEM* ITEMP;

ITEMP Exam(char* pInput, char* pItemName);

/* Date of expire: January 2019. */
int nMonthOfDate = 1, nYearOfDate = 2019;

/*  The segments contain 3 components: “ Name: <string>   Quantity: <integer>   Expires: <integer>-<integer>   ”
*/
ITEMP Exam(char* pInput, char* pItemName)
{
	ITEMP pOutStruc;
	char* pCurrentSegment;
	char* pNextSegment;
	char* pNameKeyword;
	char* pQuantityKeyword;
	char* pExpiresKeyword;
	char* pNameValue;
	char* pQuantityValue;
	char* pExpiresValue;
	char* pTmp1;
	char* pTmp2;
	char* pTmp3;
	char TmpBuff[64];
	char BuffQuantity[16];
	char BuffExpiresMonth[8];
	char BuffExpiresYear[8];
	int nItemNameLen;
	int nNameLen;
	int nQuantityLen;
	int nExpiresLen;
	int nSegmentLen;
	int nExpiresMonth;
	int nExpiresYear;
	int bEndOfSearch;

	if (pInput == NULL || pItemName == NULL)
	{
		pOutStruc = NULL;
	}
	else
	{
		pOutStruc = NULL;

		nItemNameLen = strlen(pItemName);

		pTmp1 = pInput;
		bEndOfSearch = FALSE;
		while (!bEndOfSearch)
		{
			/* Searching for the next segment */
			while (TRUE)
			{
				if (*pTmp1 == '\0')
				{
					/* End of input string */
					bEndOfSearch = TRUE;
					break;
				}

				if (*pTmp1 == ' ')
				{
					pTmp1++;
				}
				else
				{
					break;
				}
			}

			if (!bEndOfSearch)
			{
				pCurrentSegment = pTmp1;
				nSegmentLen = 0;
				while (*pTmp1++ != ']')
				{
					nSegmentLen++;
				}
				nSegmentLen++;
				pNextSegment = pTmp1;

				strncpy((char*)&TmpBuff, pCurrentSegment, nSegmentLen);
				TmpBuff[nSegmentLen] = '\0';

				pNameKeyword = strstr((char*)&TmpBuff, TEST3_KEYWORD_NAME);
				pQuantityKeyword = strstr((char*)&TmpBuff, TEST3_KEYWORD_QUANTITY);
				pExpiresKeyword = strstr((char*)&TmpBuff, TEST3_KEYWORD_EXPIRES);

				pNameValue = pNameKeyword + sizeof(TEST3_KEYWORD_NAME);
				pQuantityValue = pQuantityKeyword + sizeof(TEST3_KEYWORD_QUANTITY);
				pExpiresValue = pExpiresKeyword + sizeof(TEST3_KEYWORD_EXPIRES);

				for (nNameLen = 0, pTmp2 = pNameValue; *pTmp2 != ' '; pTmp2++) nNameLen++;
				for (nQuantityLen = 0, pTmp2 = pQuantityValue; *pTmp2 != ' '; pTmp2++) nQuantityLen++;
				for (nExpiresLen = 0, pTmp2 = pExpiresValue; *pTmp2 != ' '; pTmp2++) nExpiresLen++;

				if (nNameLen == nItemNameLen && strncmp(pNameValue, pItemName, nNameLen) == 0)
				{
					pOutStruc = (ITEMP)malloc(sizeof(ITEM) + nNameLen + 1);

					pOutStruc->pName = (char*)pOutStruc + sizeof(ITEM);
					strncpy(pOutStruc->pName, pNameValue, nNameLen);
					*(pOutStruc->pName + nNameLen) = '\0';

					strncpy((char*)&BuffQuantity, pQuantityValue, nQuantityLen);
					BuffQuantity[nQuantityLen] = '\0';
					pOutStruc->quantity = atoi((char*)&BuffQuantity);

					pTmp2 = pExpiresValue;

					pTmp3 = (char*)&BuffExpiresMonth;
					while (*pTmp2 != '-') *pTmp3++ = *pTmp2++;
					*pTmp3 = '\0';

					pTmp2++;

					pTmp3 = (char*)&BuffExpiresYear;
					while (*pTmp2 != ' ' && *pTmp2 != ']') *pTmp3++ = *pTmp2++;
					*pTmp3 = '\0';

					nExpiresMonth = atoi((char*)&BuffExpiresMonth);
					nExpiresYear = atoi((char*)&BuffExpiresYear);

					if (nYearOfDate > nExpiresYear)
					{
						pOutStruc->write_off = 1;
					}
					else
					{
						if (nYearOfDate == nExpiresYear
							&& nMonthOfDate > nExpiresMonth)
						{
							pOutStruc->write_off = 1;
						}
						else
						{
							pOutStruc->write_off = 0;
						}
					}

					bEndOfSearch = TRUE;
				}
			}
		}
	}

	return pOutStruc;
}

void main(int argc, char** argv[])
{
	char sInpStr[] = { "[ Name: Mackerel   Quantity: 1000   Expires: 10-2018   ]   [ Quantity: 500   Name: Sardine   Expires: 12-2017   ]   [ Expires: 1-2020   Quantity: 10000    Name: Tuna   ]" };
	char sItemName1[] = { "Sardine" };
	char sItemName2[] = { "Tuna" };
	char sItemName3[] = { "Mackerel" };
	char sItemName4[] = { "Whale" };
	ITEMP pItem;

	pItem = Exam((char*)&sInpStr, (char*)&sItemName1);
	if (pItem == NULL)
	{
		printf("%s - Item not found\n", sItemName1);
	}
	else
	{
		if (pItem->write_off == 1)
		{
			printf("%s - expired\n", pItem->pName);
		}
		else
		{
			printf("%s - not expired\n", pItem->pName);
		}
		free(pItem);
	}

	pItem = Exam((char*)&sInpStr, (char*)&sItemName2);
	if (pItem == NULL)
	{
		printf("%s - Item not found\n", sItemName2);
	}
	else
	{
		if (pItem->write_off == 1)
		{
			printf("%s - expired\n", pItem->pName);
		}
		else
		{
			printf("%s - not expired\n", pItem->pName);
		}
		free(pItem);
	}

	pItem = Exam((char*)&sInpStr, (char*)&sItemName3);
	if (pItem == NULL)
	{
		printf("%s - Item not found\n", sItemName3);
	}
	else
	{
		if (pItem->write_off == 1)
		{
			printf("%s - expired\n", pItem->pName);
		}
		else
		{
			printf("%s - not expired\n", pItem->pName);
		}
		free(pItem);
	}

	pItem = Exam((char*)&sInpStr, (char*)&sItemName4);
	if (pItem == NULL)
	{
		printf("%s - Item not found\n", sItemName4);
	}
	else
	{
		if (pItem->write_off == 1)
		{
			printf("%s - expired\n", pItem->pName);
		}
		else
		{
			printf("%s - not expired\n", pItem->pName);
		}
		free(pItem);
	}
}
