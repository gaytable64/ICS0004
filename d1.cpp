#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct { int day; char month[4]; int year; } DATE;
typedef struct {
    const char* pFirstName, * pLastName, * pNationality;
    DATE Birthdate;
} STUDENT;

char* setWord(char* pPattern, char* cursor, const char* toFind)
{
    cursor = strstr(pPattern, toFind);
    *cursor = 0;
    return cursor;
}

STUDENT getStudent(char* pOurPattern)
{
    STUDENT student;
    char* cursor = 0;
    cursor = setWord(pOurPattern, cursor, ",");
    student.pLastName = pOurPattern;
    pOurPattern = cursor + 2;//now it's at firstname
    cursor = setWord(pOurPattern, cursor, " born");
    student.pFirstName = pOurPattern;
    pOurPattern = cursor + 6;//string " born" is 5 chars +1 is first letter of the day of date
    cursor = setWord(pOurPattern, cursor, " ");
    student.Birthdate.day = atoi(pOurPattern);
    pOurPattern = cursor + 1;//first letter of the month
    cursor = pOurPattern + 3;//we're only interested in three letters, 0th, 1st and 2nd
    *cursor = 0;
    strcpy(student.Birthdate.month, pOurPattern);
    pOurPattern = cursor + 1;
    pOurPattern = strchr(pOurPattern, ' ') + 1;//first letter of the date
    cursor = setWord(pOurPattern, cursor, " ");
    student.Birthdate.year = atoi(pOurPattern);
    pOurPattern = cursor + 1;//this is to avoid the terminating zero
    pOurPattern = strstr(pOurPattern, "m ") + 2; //"from Canada" - we're standing on C right now
    student.pNationality = pOurPattern;
    return  student;
}

int Exam(STUDENT* pStudents, int nStudents, const char* pPattern)
{
    if (pStudents == 0 || *pPattern == 0 || pPattern == 0 || nStudents == 0)
        return 2;
    int result = 2;
    char* pOurPattern = (char*)malloc(strlen(pPattern) + 1);
    strcpy(pOurPattern, pPattern);//starts at firstname
    STUDENT stud = getStudent(pOurPattern);
    for (int i = 0; i < nStudents; i++) {
        if (
            strcmp(pStudents[i].pFirstName, stud.pFirstName) == 0 &&
            strcmp(pStudents[i].pLastName, stud.pLastName) == 0 &&
            strcmp(pStudents[i].pNationality, stud.pNationality) == 0 &&
            strcmp(pStudents[i].Birthdate.month, stud.Birthdate.month) == 0 &&
            pStudents[i].Birthdate.day == stud.Birthdate.day &&
            pStudents[i].Birthdate.year == stud.Birthdate.year
            )
            result = 1;
    }
    free(pOurPattern);
    return  result;
}

void printResult(int res)
{
    if (res == 1)
        printf("Student has been found\n");
    else
        printf("Student has not been found\n");
}

int main() {

    STUDENT students[] = {
            {"John", "Smith", "Britain", {1, "Feb", 2000}},
            {"James", "Carpenter", "Canada", {11, "Oct", 2002}},
            {"Mary", "Jane", "USA", {04, "Jan", 1996}},
            {"Sherlock", "Holmes", "Canaries", {28, "Feb", 1903}}
    };
    const char* ptoSearch = "Carpenter, James born 11 October 2002 from Canada";
    const char* potherToSearch = "Carpenter, Brut born 18 December 1996 from France";
    int resOne = Exam(students, 4, ptoSearch);
    int resTwo = Exam(students, 4, potherToSearch);
    printResult(resOne);
    printResult(resTwo);
    return 0;
}