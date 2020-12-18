/*
 Test 1.

Let us have
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

Write a function with prototype :
int Exam(STUDENT* pStudents, int nStudents, const char* pPattern);
where pStudents points to an array with length nStudents, for example:
STUDENT students[] = { {"John”,”Smith”,”Britain”, {1, “Feb”, 2000}},  {"Mary”,”Weaver”,”USA”, {2, “Mar”, 2001}},  {"James”,”Carpenter”,”Canada”, {11, “Oct”, 2002}},  {"Elizabeth”,”Clerk”,”Ireland”, {21, “Dec”, 2001}} };

The pattern is a string formatted as  “<last - name>, <first - name> born<day> <month - in - English> <year> from<country>”

Example :
const char* ptoSearch = “Carpenter, James born 11 October 2002 from Canada”;
printf(“ % s\n”, Exam(students, 4));

The output value is 1 if the student specified by pattern string is in the input array, and 0 if not.
For example, if the call is :
printf(“ % d\n”, Exam(students, 4, ptoSearch)); //prints 1

The input pointers may not be zeroand may not point to empty strings.Number of students may not be zero.
If those conditions are not satisfied, the function must return zero.
However, if those conditions are satisfied, we may be sure that the input data is 100 % correct.
The nationality is always presented by just one word.

Write also main to test the code and print the results.
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    int day;
    char month[4];
    int year;
} DATE;

typedef struct {
    const char* pFirstName, * pLastName, * pNationality;
    DATE Birthdate;
} STUDENT;

int Exam(STUDENT* pStudents, int nStudents, const char* pPattern);
const char* Month(STUDENT* pStudents, int num);

int Exam(STUDENT* pStudents, int nStudents, const char* pPattern) {
    char search_str[256];
    char* month;
    int i;

    for (i = 0; i < nStudents; i++) {
        month = (char*)Month(pStudents, i);
        sprintf(search_str, "%s, %s born %d %s %d from %s", pStudents[i].pLastName,
            pStudents[i].pFirstName,
            pStudents[i].Birthdate.day,
            month, pStudents[i].Birthdate.year,
            pStudents[i].pNationality);
        if (strcmp(search_str, pPattern) != 0) {
            printf("The student has been found!\n"); 
        }
        else
        {
            printf("The student is not in the database\n");
        }
        return 1;
    }

    return 0;
}

const char* Month(STUDENT* pStudents, const int num) {
    const char* month = 0;
    int i;
    const char months[][64] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

    for (i = 0; i < 12; i++) {
        if (strcmp(pStudents[num].Birthdate.month, months[i]) == 0) {
            switch (i) {
            case 0:
                month = "January";
                break;
            case 1:
                month = "February";
                break;
            case 2:
                month = "March";
                break;
            case 3:
                month = "April";
                break;
            case 4:
                month = "May";
                break;
            case 5:
                month = "June";
                break;
            case 6:
                month = "July";
                break;
            case 7:
                month = "August";
                break;
            case 8:
                month = "September";
                break;
            case 9:
                month = "October";
                break;
            case 10:
                month = "November";
                break;
            case 11:
                month = "December";
                break;
            }
        }
    }
    return month;
}



int main() {
    STUDENT students[] = { {"John","Smith","Britain",{1,"Feb",2000}},
                        {"Mary","Weaver","USA",{2,"Mar",2001}},
                        {"James","Carpenter","Canada",{11,"Oct",2002}},
                        {"Elizabeth","Clerk","Ireland",{21,"Dec",2001}} };
    const char* ptoSearch = "Carpenter, James born 11 October 2002 from Canada";

    printf("%d\n", Exam(students, 4, ptoSearch));

    return 0;
}
