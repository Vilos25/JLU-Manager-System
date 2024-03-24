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
#define FILENAME_GRA "LIST_StdGrade.txt"
void Menu_SubInfor();
void Menu_StdGrade();
void First_Load();
struct Student* head_StdGrade = NULL;
struct Major* head_Major = NULL;
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


//首次文件载入
void First_Load() {
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    //调用加载函数并判断是否加载成功
    loadFrom_StdGrade(&head_Major, FILENAME_GRA);
    //loadFromGrade(&head_StdGrade, FILENAME_GRA);
}
//学生成绩菜单
void Menu_StdGrade()
{
    
    int choice;
    char majorNum[10];
    int gradeNum;
    int studentID;
    char courseName[20];
    float score;
    char semester[5];
    int isExempted;
    int isFailed;
    float newScore;
    system("cls");
    system("color F0");
    HideCursor();
    cursor(26, 6);
    printf("已进入成绩管理菜单！\n\n");

    while (1) {
        printf("1. 添加专业\n");
        printf("2. 添加年级\n");
        printf("3. 添加学生\n");
        printf("4. 添加学生成绩\n");
        printf("5. 修改学生成绩\n");
        printf("6. 删除学生成绩\n");
        printf("7. 删除学生\n");
        printf("8. 保存数据到文件\n");
        printf("9. 显示单个学生的所有成绩\n");
        printf("10. 退出系统\n");
        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("请输入专业编号：");
            scanf("%s", majorNum);
            add_Major(&head_Major, majorNum);
            break;
        case 2:
            printf("请输入专业编号：");
            scanf("%s", majorNum);
            printf("请输入年级：");
            scanf("%d", &gradeNum);
            add_Grade(search_Major(&head_Major, majorNum), gradeNum);
            break;
        case 3:
            printf("请输入专业编号：");
            scanf("%s", majorNum);
            printf("请输入年级：");
            scanf("%d", &gradeNum);
            printf("请输入学号：");
            scanf("%d", &studentID);
            add_Student(&head_Major, studentID, majorNum, gradeNum);
            break;
        case 4:
            printf("请输入学号：");
            scanf("%d", &studentID);
            printf("请输入课程名：");
            scanf("%s", courseName);
            printf("请输入成绩：");
            scanf("%f", &score);
            printf("请输入修读学期：");
            scanf("%s", semester);
            printf("请输入是否免修（0表示否，1表示是）：");
            scanf("%d", &isExempted);
            printf("请输入是否挂科（0表示否，1表示是）：");
            scanf("%d", &isFailed);
            if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == 1) {
                printf("添加成功。\n");
            }
            else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -1) {
                printf("学生不存在，添加失败。\n");
            }
            else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -2) {
                printf("课程名重复，添加失败。\n");
            }
            else {
                printf("添加失败。\n");
            }
            break;
        case 5:
            printf("请输入学号：");
            scanf("%d", &studentID);
            printf("请输入课程名：");
            scanf("%s", courseName);
            printf("请输入新的成绩：");
            scanf("%f", &newScore);
            if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                printf("修改成功。\n");
            }
            else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                printf("学生不存在，修改失败。\n");
            }
            else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                printf("课程名不存在，修改失败。\n");
            }
            else {
                printf("修改失败。\n");
            }
            break;
        case 6:
            printf("请输入学号：");
            scanf("%d", &studentID);
            printf("请输入课程名：");
            scanf("%s", courseName);
            if (delete_Score(&head_Major, studentID, courseName) == 1) {
                printf("删除成功。\n");
            }
            else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                printf("学生不存在，删除失败。\n");
            }
            else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                printf("课程名不存在，删除失败。\n");
            }
            else {
                printf("删除失败。\n");
            }
            break;
        case 7:
            printf("请输入学号：");
            scanf("%d", &studentID);
            if (delete_Student(&head_Major, studentID) == 1) {
                printf("删除成功。\n");
            }
            else {
                printf("删除失败。\n");
            }
            break;
        case 8:
            //调用保存函数并判断是否保存成功
            saveTo_StdGrade(&head_Major, "LIST_StdGrade.txt");
            break;
        case 9:
            printf("请输入学号");
            scanf("%d", &studentID);
            query_Scores(&head_Major, studentID);
            break;
        case 10:
            printf("感谢使用，再见！\n");
            exit(0);
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
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
