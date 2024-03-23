//释放内存
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "LIST_StdGrade.h"
#include "LIST_SubInfor.h"
void Func_Free(struct SubInfor* head)
{
    struct SubInfor* current = head;
    while (current != NULL) {
        struct SubInfor* next = current->next;
        free(current);
        current = next;
    }
}
void Func_FreeGrade(struct SubInfor* head)
{
    // 释放链表内存
    struct Student* currentStudent = head;
    while (currentStudent != NULL) {
        struct Student* tempStudent = currentStudent;
        struct SubScore* currentScore = currentStudent->scores;
        while (currentScore != NULL) {
            struct SubScore* tempScore = currentScore;
            currentScore = currentScore->next;
            free(tempScore);
        }
        currentStudent = currentStudent->next;
        free(tempStudent);
    }
}