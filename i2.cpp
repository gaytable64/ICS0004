/*
 *Test 2.
 
 Write a function with prototype: STUDENT *Exam(char *pInput, char *pStudentName);

Here:
typedef struct student
{
char *pName;
int nMarks, *pMarks; //number of marks and pointer to array of marks
double AverageMark;
} STUDENT;

and the input string consists of segments “, , , ... ;“
for example: John Smith 4, 2, 5, 3; James Farmhand, 4;

The number of segments is not restricted and the number of marks of a student may be any (but nor 0 pieces). The marks are from interval 0...5.
There is only one space between the components of segments (i.e. after comma and colon)
But there may be any number (except 0 pieces) of spaces between segments (i.e. after semicolon)
The semicolon is after each segment.

The function must create a struct STUDENT for student whos name in specified by the pointer pStudentName and, extracting the needed information from the input string, fill its fields. The function returns the pointer to the created struct.

You may suppose that the input string is absolutely correct, i.e. its checking is not needed.
However, the student with the specified name may be not present in the input string.
In that case the function must return 0.

Write also main to test the code
 */

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct student {
    char* pName;
    int nMarks, * pMarks; //number of marks and pointer to array of marks
    double AverageMark;
}STUDENT;

STUDENT* Exam(char* pInput, char* pStudentName);

STUDENT* Exam(char* pInput, char* pStudentName) {
    char* pfound;
    STUDENT* Student = (STUDENT*)malloc(sizeof(STUDENT));
    int size_t = strlen(pStudentName);

    if (strstr(pInput, pStudentName) != NULL) {

        //pName
        Student->pName = (char*)malloc(sizeof(char) * size_t + 1);
        strcpy(Student->pName, pStudentName);

        pfound = strstr(pInput, pStudentName);

        //nMarks
        int i = 0;
        while (pfound[i + size_t + 1] != ';') {
            if (pfound[i + size_t + 1] == ' ' && (pfound[i + size_t + 3] == ',' || pfound[i + size_t + 3] == ';'))Student->nMarks++;
            i++;
        }

        //pMarks
        Student->pMarks = (int*)malloc(Student->nMarks * sizeof(int));
        int j = 0;
        for (i = 0; i < Student->nMarks; i++) {
            while (pfound[j + size_t + 1] != ';') {
                if (pfound[j + size_t + 1] == ' ' && (pfound[j + size_t + 3] == ',' || pfound[j + size_t + 3] == ';')) {
                    Student->pMarks[i] = atoi(&pfound[j + size_t + 2]);
                    Student->AverageMark += Student->pMarks[i];
                    j += 2;
                    break;
                }
                j++;
            }
        }

        //AverageMark
        Student->AverageMark /= Student->nMarks;

    }
    else { return 0; }

    return Student;
}

int main() {
    char Input[] = "James Farmhand,   4;   John Smith, 4,  2, 5,   3; Keisuke Konno, 3;";
    char StudentName[] = "John Smith";
    STUDENT* pStudent;

    if (Exam(Input, StudentName) == 0) {
        printf("No Data\n");
        exit(1);
    }
    else {
        pStudent = Exam(Input, StudentName);
        printf("Name:%s\nAverage:%f\n", pStudent->pName, pStudent->AverageMark);
    }

    return 0;
}