#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Func_isValid.h"
#include "LIST_SubInfor.h"
// 创建新节点
struct SubInfor* create_SubInfor() {
    struct SubInfor* newNode = (struct SubInfor*)malloc(sizeof(struct SubInfor));
    if (newNode != NULL) {
        int xy = 20;
        cursor(26, xy);
        printf("请输入科目名称：");
        scanf("%s", newNode->SubName);

        while (1) {
            cursor(26, xy+=1);
            printf("请输入科目编号（两位字母加八位数字）：");
            //scanf("%s", newNode->SubInforNum);
            Input_SubNum(newNode->SubInforNum);
            if (isValid_SubNum(newNode->SubInforNum)) {
                break;
            }
            else {
                cursor(26, xy += 1);
                printf("课程编号格式不正确，请重新输入。\n");
            }
        }
        cursor(26, xy += 1);
        printf("请输入科目分数：");
        //scanf("%f", &(newNode->SubInforScore));
        newNode->SubInforScore = Input_Float(2, 2);
        cursor(26, xy += 1);
        printf("请输入科目是否为计入保研GPA科目（2 表示是，1 表示否）：");
        //scanf("%d", &(newNode->SubRequired));
        newNode->SubRequired = Input_1toNum(2) - 1;

        newNode->next = NULL;
    }
    return newNode;
}


// 插入节点到链表
void insert_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode) {
    if (*head_SubInfor == NULL) {
        *head_SubInfor = newNode;
    }
    else {
        struct SubInfor* temp = *head_SubInfor;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    //printf("科目已插入到列表中。\n");
}

// 通过课程号查找节点并返回其地址
struct SubInfor* search_SubInfor(struct SubInfor* head_SubInfor, const char* subNum) {
    struct SubInfor* temp = head_SubInfor;

    while (temp != NULL) {
        if (strcmp(temp->SubInforNum, subNum) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;  // 未找到匹配的节点
}


// 修改课程信息
bool checkAndReplace_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode) {
    struct SubInfor* temp = *head_SubInfor;
    struct SubInfor* prev = NULL;

    // 遍历链表，比对课程号
    while (temp != NULL) {
        if (strcmp(temp->SubInforNum, newNode->SubInforNum) == 0) {
            return true;  // 存在相同的课程号
        }
        prev = temp;
        temp = temp->next;
    }

    return false;  // 不存在相同的课程号
}

// 显示链表中的科目信息
void display_SubInfor(struct SubInfor* head_SubInfor) {
    if (head_SubInfor == NULL) {
        printf("链表为空。\n");
        return;
    }

    struct SubInfor* temp = head_SubInfor;
    int count = 1;

    printf("科目列表：\n");

    while (temp != NULL) {
        printf("科目 %d:\n", count);
        printf("名称： %s\n", temp->SubName);
        printf("编号： %s\n", temp->SubInforNum);
        printf("分数： %.2f\n", temp->SubInforScore);
        printf("是否计入保研GPA： %s\n", temp->SubRequired ? "是" : "否");

        temp = temp->next;
        count++;
    }
    printf("库中课程总数为：%d\n", count - 1);
}

// 将链表中的科目信息保存到文件
void saveTo_SubInfor(struct SubInfor* head_SubInfor, const char* filename) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    struct SubInfor* temp = head_SubInfor;

    while (temp != NULL) {
        fprintf(file, "%s,%s,%.2f,%d\n", temp->SubName, temp->SubInforNum, temp->SubInforScore, temp->SubRequired);

        temp = temp->next;
    }

    fclose(file);
    //printf("科目信息已保存到文件。\n");
}
//清空链表
void clear_SubInfor(struct SubInfor** head_SubInfor) {
    struct SubInfor* temp = *head_SubInfor;
    struct SubInfor* next = NULL;

    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }

    *head_SubInfor = NULL;
    //printf("链表已清空。\n");
}

// 从文件中加载科目信息到链表
void loadFrom_SubInfor(struct SubInfor** head_SubInfor, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    // 清空链表
    clear_SubInfor(head_SubInfor);

    char line[100];

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ",");
        struct SubInfor* newNode = (struct SubInfor*)malloc(sizeof(struct SubInfor));
        if (newNode != NULL)
        {
            newNode->next = NULL;
            strcpy(newNode->SubName, token);
            token = strtok(NULL, ",");
            strcpy(newNode->SubInforNum, token);
            token = strtok(NULL, ",");
            newNode->SubInforScore = atof(token);
            token = strtok(NULL, ",");
            newNode->SubRequired = atoi(token);
        }

        insert_SubInfor(head_SubInfor, newNode);
    }

    fclose(file);
    printf("已从文件加载科目信息列表。\n");
}

// 删除指定科目节点
void delete_SubInfor(struct SubInfor** head_SubInfor, const char* subNum) {
    struct SubInfor* temp = *head_SubInfor;
    struct SubInfor* prev = NULL;
    //判断表是否为空
    if (temp == NULL)
    {
        printf("\n\t\t\t库为空！\n");
        return;
    }
    // 头节点就是要删除的节点
    if (temp != NULL && strcmp(temp->SubInforNum, subNum) == 0) {
        *head_SubInfor = temp->next;
        free(temp);
        printf("\n\t\t\t科目已删除。\n");
        return;
    }

    // 寻找要删除的节点
    while (temp != NULL && strcmp(temp->SubInforNum, subNum) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n\t\t\t找不到要删除的科目。\n");
        return;
    }

    if (prev == NULL) {
        *head_SubInfor = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
    printf("\n\t\t\t科目已删除。\n");
}