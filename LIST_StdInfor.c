#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIST_StdInfor.h"
#include "LIST_StdGrade.h"

//创建链表头节点，返回头节点地址
StdInfor* createStdInfor() {
    StdInfor* head = (StdInfor*)malloc(sizeof(StdInfor));
    head->next = NULL;
    return head;
}
//给定学生学号，查找学生信息并返回其地址
StdInfor* search_StdInfor(StdInfor* head, int studentId) {
    StdInfor* current = head;
    while (current != NULL) {
        if (current->id == studentId) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//给定学生学号，增加学生信息
void add_StdInfor(StdInfor* head, int studentId) {
    StdInfor* newStudent = (StdInfor*)malloc(sizeof(StdInfor));
    newStudent->id = studentId;
    newStudent->t = 0;
    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
    }
    else {
        StdInfor* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newStudent;
    }

}


// 修改学生信息
void modify_StdInfor(StdInfor* head, int studentId) {
    StdInfor* current = head;
    while (current != NULL) {
        if (current->id == studentId) {
            system("cls");
            int i = 6;
            cursor(26, i++);
            printf("请输入学生信息：\n");
            cursor(26, i++);
            printf("姓名：");
            scanf("%s", current->name);
            cursor(26, i++);
            printf("班级：");
            //scanf("%d", &(current->class));
            current->class = Input_Raw_Integer(2);
            cursor(26, i++);
            printf("性别(M/F)：");
            //scanf(" %c", &(current->gender));
            current->gender = Input_MF();
            cursor(26, i++);
            printf("请输入政治面貌: \n");
            cursor(26, i++);
            printf("1. 中共党员\n");
            cursor(26, i++);
            printf("2. 共青团员\n");
            cursor(26, i++);
            printf("3. 群众\n");
            cursor(26, i++);
            int flag = 1;
            while (flag)
            {
                int politicalStatusOption;
                //scanf("%d", &politicalStatusOption);
                politicalStatusOption = Input_1toNum(3);
                switch (politicalStatusOption) {
                case 1:
                    strcpy(current->politicalStatus, "中共党员");
                    flag = 0;
                    break;
                case 2:
                    strcpy(current->politicalStatus, "共青团员");
                    flag = 0;
                    break;
                case 3:
                    strcpy(current->politicalStatus, "群众");
                    flag = 0;
                    break;
                default:
                    printf("输入的政治面貌选项无效,请重新输入\n");
                    break;
                }
            }
            cursor(26, i++);
            printf("手机号码：");
            //scanf("%s", current->phoneNumber);
            Input_phoneNumber(current->phoneNumber);
            cursor(26, i++);
            printf("电子邮箱：");
            Input_Email(current->email);
            //scanf("%s", current->email);
            cursor(26, i++);
            printf("是否在读（2为是，1为否）：");
            //scanf("%d", &(current->isStudying));
            current->isStudying = Input_1toNum(2) - 1;
            current->t = 1;
            cursor(26, i++);
            printf("学生信息修改成功！\n");
            return;
        }
        current = current->next;
    }

    printf("找不到该学生的信息！\n");
}


// 删除学生信息
void delete_StuInfor(StdInfor** head, int studentId) {
    StdInfor* current = *head;
    StdInfor* previous = NULL;

    while (current != NULL) {
        if (current->id == studentId) {
            if (previous == NULL) {
                *head = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            printf("学生信息删除成功！\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("找不到该学生的信息！\n");
}

//打印学生信息

void print_StdInfor(StdInfor* head, struct Major* head_Major, int studentId) {
    StdInfor* current = head;
    while (current != NULL) {
        if (current->id == studentId) {
            printf("\t\t学号：%d \t\t", current->id);
            printf("姓名：%s \t", current->name);
            if (current->gender == 'M')
                printf("性别：男\n");
            else
                printf("性别：女\n\t\t");
            struct Major* acc = search_MajorByStudentID(head_Major, studentId);
            if (acc != NULL)
            {
                int i = acc->majorNum / 100; int j = acc->majorNum % 100;
                printf("专业：%s—", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("班级：%d \t", current->class);
                printf("政治面貌：%s \n\t\t", current->politicalStatus);
                printf("手机号码：%s \t", current->phoneNumber);
                printf("电子邮箱：%s \t", current->email);
                printf("是否在读：%s \n\t\t", current->isStudying ? "是" : "否");
            }
            else {
                printf("专业：未知\t");
				printf("班级：%d \t", current->class);
				printf("政治面貌：%s \n\t\t", current->politicalStatus);
				printf("手机号码：%s \t", current->phoneNumber);
				printf("电子邮箱：%s \t", current->email);
				printf("是否在读：%s \n", current->isStudying ? "是" : "否");
            }
            return;
        }
        current = current->next;
    }

    printf("找不到该学生的信息！\n");
}

// 保存学生信息到文件
void saveTo_StdInfor(StdInfor* head, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    StdInfor* current = head->next;
    while (current != NULL) {
        fprintf(file, "%d %s %d %c %s %s %s %d\n", current->id, current->name, current->class,
            current->gender, current->politicalStatus, current->phoneNumber,
            current->email, current->isStudying);
        current = current->next;
    }

    fclose(file);
    //printf("学生信息保存成功！\n");
}

// 从文件加载学生信息
void loadFrom_StdInfor(StdInfor** head, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    // 清空链表
    StdInfor* current = *head;
    while (current != NULL) {
        StdInfor* temp = current;
        current = current->next;
        free(temp);
    }
    *head = createStdInfor();
    while (!feof(file)) {
        StdInfor* newStudent = (StdInfor*)malloc(sizeof(StdInfor));
        int result = fscanf(file, "%d %s %d %c %s %s %s %d\n", &(newStudent->id), newStudent->name,
            &(newStudent->class), &(newStudent->gender), newStudent->politicalStatus,
            newStudent->phoneNumber, newStudent->email, &(newStudent->isStudying));
        if (result == EOF) {
            free(newStudent);
            break;
        }
        newStudent->next = NULL;

        if (*head == NULL) {
            *head = newStudent;
        }
        else {
            current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
    }

    fclose(file);
    printf("学生信息加载成功！\n");
}

//打印所有学生信息
void printAll_StdInfor(StdInfor* head, struct Major* head_Major) {
    StdInfor* current = head->next;
    while (current != NULL) {
        print_StdInfor(head, head_Major, current->id);
        current = current->next;
        printf("\n");
    }
}

//释放学生信息
void free_StdInfor(StdInfor* head) {
    StdInfor* current = head;
    while (current != NULL) {
        StdInfor* temp = current;
        current = current->next;
        free(temp);
    }
}