#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "LIST_StdGrade.h"
#include "LIST_SubInfor.h"
#include "Face.h"
#include "page.h"
#include "Free_List.h"
//文件命名
#define FILENAME_SUB "subjects.txt"
#define FILENAME_GRA "students.txt"
void Menu_SubInfor();
void Menu_StdGrade();
void First_Load();
struct Student* head_StdGrade = NULL;
struct SubInfor* head_SubInfor = NULL;
int main()
{
    First_Load();
    welcome();
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("1. 管理科目列表");
        cursor(26, 8);
        printf("2. 管理学生成绩");
        cursor(26, 10);
        printf("3. 退出");
        cursor(26, 12);
        printf("请输入选项：");
        cursor(26, 14);
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            Menu_SubInfor();
            break;
        }
        case 2:
            Menu_StdGrade();
            break;
        case 3:
            PrintExit();
            return 0;
        default:
            printf("无效的选项，请重新输入。\n");
            break;
        }
        printf("\n");
    }
}

//学生成绩菜单

void Menu_StdGrade(){
        int choice;
        int studentID;
        char courseName[20];
        float score;
        char semester[20];
        int isExempted;
        int isFailed;
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("已进入学生成绩管理菜单！\n\n");
        do {
            printf("1. 添加学生\n");
            printf("2. 录入学生成绩\n");
            printf("3. 修改学生成绩\n");
            printf("4. 删除学生成绩\n");
            printf("5. 查询单个学生的所有成绩\n");
            //printf("6. 从文件导入\n");
            printf("6. 保存到文件\n");
            printf("0. 退出\n");
            printf("请输入您的选择：");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("请输入学生学号：");
                scanf("%d", &studentID);
                addStudent(&head_StdGrade, studentID);
                break;
            case 2:
                printf("请输入学生学号：");
                scanf("%d", &studentID);
                struct Student* current = head_StdGrade;
                while (current != NULL) {
                    if (current->studentID == studentID)
                        break;
                    current = current->next;
                }
                if (current == NULL) {
                    printf("没有该名学生！\n");
                    break;
                }
                while (1) {
                    printf("请输入科目编号（两位字母加八位数字）：");
                    scanf("%s", courseName);

                    if (isValid_SubNum(courseName)) {
                        break;
                    }
                    else {
                        printf("课程编号格式不正确，请重新输入。\n");
                    }
                }
                printf("请输入成绩：");
                scanf("%f", &score);
                printf("请输入修读学期（四位有效数字，前两位年份，后两位01为第一学期，02为第二学期：");
                while (1) {
                    printf("请输入科目编号（两位字母加八位数字）：");
                    scanf("%s", semester);

                    if (isValid_SemesterNum(semester)) {
                        break;
                    }
                    else {
                        printf("修读学期格式不正确，请重新输入。\n");
                    }
                }
                printf("是否免修（1表示是，0表示否）：");
                scanf("%d", &isExempted);
                printf("是否挂科（1表示是，0表示否）：");
                scanf("%d", &isFailed);
                addScore(&head_StdGrade, studentID, courseName, score, semester, isExempted, isFailed);
                break;
            case 3:
                printf("请输入学生学号：");
                scanf("%d", &studentID);
                printf("请输入课程名：");
                scanf("%s", courseName);
                printf("请输入新的成绩：");
                scanf("%f", &score);
                updateScore(&head_StdGrade, studentID, courseName, score);
                break;
            case 4:
                printf("请输入学生学号：");
                scanf("%d", &studentID);
                printf("请输入要删除的课程名：");
                scanf("%s", courseName);
                deleteScore(&head_StdGrade, studentID, courseName);
                break;
            case 5:
                printf("请输入学生学号：");
                scanf("%d", &studentID);
                queryScores(&head_StdGrade, studentID);
                break;
            /*case 6:
                loadFromGrade("FILENAME_GRA");// 进行操作，例如添加学生、录入成绩等
                break;
            */
            case 6:
                // 保存学生信息到文件
                saveToGrade(&head_StdGrade, "FILENAME_GRA");
                break;
            case 0:
                printf("感谢使用成绩管理系统！\n");
                break;
            default:
                printf("无效的选择！\n");
                break;
            }
            printf("\n");
        } while (choice != 0);
        return;
}
//首次文件载入
void First_Load() {
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    loadFromGrade(&head_StdGrade, FILENAME_GRA);
}
//科目列表菜单
void Menu_SubInfor() {
    system("cls");
    system("color F0");
    HideCursor();
    cursor(26, 6);
    printf("已进入科目列表管理菜单！\n\n");
    int choice;
    //loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    while (1) {
        printf("1. 插入/修改科目\n");
        printf("2. 显示科目列表\n");
        printf("3. 保存到文件\n");
        printf("4. 从文件加载\n");
        printf("5. 删除科目\n");
        printf("6. 退出\n");
        printf("请输入选项：");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            struct SubInfor* newNode = create_SubInfor();
            if (checkAndReplace_SubInfor(&head_SubInfor, newNode)) {
                printf("科目已存在，是否覆盖？（Y/N）：");
                char answer;
                scanf(" %c", &answer);
                if (toupper(answer) == 'Y') {
                    delete_SubInfor(&head_SubInfor, newNode->SubInforNum);
                    insert_SubInfor(&head_SubInfor, newNode);
                    printf("科目已覆盖。\n");
                }
                else {
                    free(newNode);
                    printf("科目未插入到列表中。\n");
                }
            }
            else {
                insert_SubInfor(&head_SubInfor, newNode);
                printf("科目已插入到列表中。\n");
            }
            break;
        }
        case 2:
            display_SubInfor(head_SubInfor);
            break;
        case 3:
            saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
            printf("科目信息已保存到文件。\n");
            break;
        case 4:
            loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
            printf("已从文件加载科目信息。\n");
            break;
        case 5: {
            char subNum[MAX_NUM_LENGTH];
            printf("请输入要删除的科目编号：");
            scanf("%s", subNum);
            delete_SubInfor(&head_SubInfor, subNum);
            break;
        }
        case 6:
            printf("程序已退出。\n");
            return;
        default:
            printf("无效的选项，请重新输入。\n");
            break;
        }
        printf("\n");
    }
}