#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIST_StdInfor.h"
#include "LIST_StdGrade.h"
#include "Func_isValid.h"
#include "LIST_TeaInfor.h"

// 创建头节点
TeaInfor* createHead_TeaInfor() {
    TeaInfor* head = (TeaInfor*)malloc(sizeof(TeaInfor));
    if (head != NULL)
    {
        head->teacher.id = 0;
        head->next = NULL;
        return head;
    }
    else return NULL;
}

// 添加辅导员信息函数
void add_Teacher(TeaInfor* head_TeaInfor, int ID) {
    TeaInfor* newNode = (TeaInfor*)malloc(sizeof(TeaInfor));
    newNode->next = NULL;
    newNode->teacher.id = ID;
    int xy = 10;
    cursor(26, xy);
    printf("请输入姓名: ");
    scanf("%s", newNode->teacher.name);
    cursor(26, xy+=1);
    printf("请输入专业代码: ");
    
    newNode->teacher.majorCode = Input_Raw_Integer(2);
    cursor(26, xy+=1);
    printf("请输入带的年级数量 (1 或 2): ");
    int numGrades = Input_1toNum(2);
    if (numGrades == 1) {
        cursor(26, xy+=1);
        printf("请输入年级: ");
        newNode->teacher.grades[0] = Input_Raw_Integer(2);
        newNode->teacher.grades[1] = 0;
    }
    else if (numGrades == 2) {
        cursor(26, xy+=1);
        printf("请输入年级1: ");
        newNode->teacher.grades[0] = Input_Raw_Integer(2);
        cursor(26, xy+=1);
        printf("请输入年级2: ");
        newNode->teacher.grades[1] = Input_Raw_Integer(2);
    }
    else {
        cursor(26, xy+=1);
        printf("输入的年级数量无效。\n");
        free(newNode);
        return;
    }
    cursor(26, xy += 1);
    printf("请输入性别 (M 或 F): ");
    newNode->teacher.gender = Input_MF();
    cursor(26, xy += 1);
    printf("请输入政治面貌: \n");
    cursor(26, xy += 1);
    printf("1. 中共党员\n");
    cursor(26, xy += 1);
    printf("2. 共青团员\n");
    cursor(26, xy += 1);
    printf("3. 群众");
    cursor(26, xy += 1);
    int politicalStatusOption = Input_1toNum(3);

    switch (politicalStatusOption) {
    case 1:
        strcpy(newNode->teacher.politicalStatus, "中共党员");
        break;
    case 2:
        strcpy(newNode->teacher.politicalStatus, "共青团员");
        break;
    case 3:
        strcpy(newNode->teacher.politicalStatus, "群众");
        break;
    default:
        cursor(26, xy += 1);
        printf("输入的政治面貌选项无效。\n");
        free(newNode);


    }
    cursor(26, xy += 1);
    printf("请输入学历: ");
    scanf("%s", newNode->teacher.education);
    cursor(26, xy += 1);
    printf("请输入电话号码: ");
    Input_phoneNumber(newNode->teacher.phoneNumber);
    cursor(26, xy += 1);
    printf("请输入电子邮箱: ");
    Input_Email(newNode->teacher.email);

    // 将新节点插入链表尾部
    TeaInfor* current = head_TeaInfor;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    cursor(26, xy += 1);
    printf("辅导员信息添加成功！\n");
}

//查询辅导员，如果找到返回1，否则返回0
TeaInfor* search_TeacherByID(TeaInfor* head_TeaInfor, int ID) {
    TeaInfor* current = head_TeaInfor;
    while (current != NULL) {
        if (current->teacher.id == ID) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

//打印辅导员信息
void print_Teacher(TeaInfor* head_TeaInfor, int ID) {
    TeaInfor* current = head_TeaInfor->next;
    while (current != NULL) {
        if (current->teacher.id == ID) {
            printf("工号：%d\t", current->teacher.id);
            printf("姓名：%s\t", current->teacher.name);
            if (current->teacher.gender == 'M')
                printf("性别：男\n");
            else
                printf("性别：女\n");
            int i = current->teacher.majorCode;
            printf("专业：%s\t", All_Aca[i]);
            printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            printf("政治面貌：%s\t", current->teacher.politicalStatus);
            printf("学历：%s\t", current->teacher.education);
            printf("手机号码：%s\t", current->teacher.phoneNumber);
            printf("邮箱：%s\n", current->teacher.email);
        }
        current = current->next;
    }
}

// 查询辅导员信息
void search_Teacher(TeaInfor* head_TeaInfor) {
    if (head_TeaInfor == NULL) {
        printf("暂无辅导员信息。\n");
        return;
    }

    int choice;
    printf("请选择查询方式：\n");
    printf("1. 按工号查询\n");
    printf("2. 按姓名查询\n");
    printf("请输入你的选择: ");
    //scanf("%d", &choice);
    choice = Input_1toNum(2);
    switch (choice) {
    case 1: {
        int id;
        printf("请输入要查询的辅导员工号: ");
        //scanf("%d", &id);
        id = Input_Raw_Integer(6);
        TeaInfor* current = head_TeaInfor;
        while (current != NULL) {
            if (current->teacher.id == id) {
                printf("工号：%d\n", current->teacher.id);
                printf("姓名：%s\n", current->teacher.name);
                printf("专业编号：%d\n", current->teacher.majorCode);
                int i = current->teacher.majorCode / 100; int j = current->teacher.majorCode % 100;
                printf("\t\t专业：%s—", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                if (current->teacher.gender == 'M')
                    printf("性别：男\t");
                else
                    printf("性别：女\t");
                printf("政治面貌：%s\n", current->teacher.politicalStatus);
                printf("学历：%s\n", current->teacher.education);
                printf("手机号码：%s\n", current->teacher.phoneNumber);
                printf("邮箱：%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("未找到对应工号的辅导员信息。\n");
        break;
    }
    case 2: {
        char name[50];
        printf("请输入要查询的辅导员姓名: ");
        scanf("%s", name);

        TeaInfor* current = head_TeaInfor;
        while (current != NULL) {
            if (strcmp(current->teacher.name, name) == 0) {
                printf("工号：%d\n", current->teacher.id);
                printf("姓名：%s\n", current->teacher.name);
                printf("专业编号：%d\n", current->teacher.majorCode);
                int i = current->teacher.majorCode / 100; int j = current->teacher.majorCode % 100;
                printf("\t\t专业：%s—", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("所带年级：%d, %d\t", current->teacher.grades[0], current->teacher.grades[1]);
                if (current->teacher.gender == 'M')
                    printf("性别：男\t");
                else
                    printf("性别：女\t");
                printf("政治面貌：%s\t", current->teacher.politicalStatus);
                printf("学历：%s\t", current->teacher.education);
                printf("手机号码：%s\t", current->teacher.phoneNumber);
                printf("邮箱：%s\t", current->teacher.email);
            }
            current = current->next;
        }
        printf("未找到对应姓名的辅导员信息。\n");
        break;
    }
    default:
        printf("无效的选择。\n");
    }
}

// 修改辅导员信息
void modify_Teacher(TeaInfor* head_TeaInfor, int id) {
    system("cls");
    system("color F0");
    HideCursor();

    if (head_TeaInfor == NULL) {
        printf("暂无辅导员信息。\n");
        return;
    }

    TeaInfor* current = head_TeaInfor;
    while (current != NULL) {
        if (current->teacher.id == id) {
            int xy;
            xy = 1;
            cursor(26, xy);
            printf("工号：%d\n", current->teacher.id);
            cursor(26, xy += 1);
            printf("姓名：%s\n", current->teacher.name);
            cursor(26, xy += 1);
            printf("专业编号：%d\n", current->teacher.majorCode);
            cursor(26, xy += 1);
            printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            cursor(26, xy += 1);
            if (current->teacher.gender == 'M')
                printf("性别：男\t");
            else
                printf("性别：女\t");
            cursor(26, xy += 1);
            printf("政治面貌：%s\n", current->teacher.politicalStatus);
            cursor(26, xy += 1);
            printf("学历：%s\n", current->teacher.education);
            cursor(26, xy += 1);
            printf("手机号码：%s\n", current->teacher.phoneNumber);
            cursor(26, xy += 1);
            printf("邮箱：%s\n", current->teacher.email);
            cursor(26, xy += 1);
            printf("\n");
            cursor(26, xy += 1);
            printf("下面对教师信息进行修改：\n");
            cursor(26, xy += 1);
            printf("姓名: ");
            scanf("%s", current->teacher.name);
            cursor(26, xy += 1);
            printf("专业编号: ");
            //scanf("%d", &current->teacher.majorCode);
            current->teacher.majorCode = Input_Raw_Integer(2);
            cursor(26, xy += 1);
            printf("所带年级:\n");
            cursor(26, xy += 1);
            printf("请输入带的年级数量 (1 或 2): ");
            int numGrades = Input_1toNum(2);
            if (numGrades == 1) {
				cursor(26, xy += 1);
				printf("输入年级:");
				current->teacher.grades[0] = Input_Raw_Integer(2);
				current->teacher.grades[1] = 0;
			}
			else if (numGrades == 2) {
				cursor(26, xy += 1);
				printf("输入第一个年级: ");
				current->teacher.grades[0] = Input_Raw_Integer(2);
				cursor(26, xy += 1);
				printf("输入第二个年级: ");
				current->teacher.grades[1] = Input_Raw_Integer(2);
			}
            cursor(26, xy += 1);
            printf("性别: ");
            //scanf(" %c", &current->teacher.gender);
            current->teacher.gender = Input_MF();
            cursor(26, xy += 1);
            printf("政治面貌: ");
            cursor(26, xy += 1);
            printf("1. 中共党员\n");
            cursor(26, xy += 1);
            printf("2. 共青团员\n");
            cursor(26, xy += 1);
            printf("3. 群众");
            cursor(26, xy += 1);
            int politicalStatusOption = Input_1toNum(3);

            switch (politicalStatusOption) {
            case 1:
                strcpy(current->teacher.politicalStatus, "中共党员");
                break;
            case 2:
                strcpy(current->teacher.politicalStatus, "共青团员");
                break;
            case 3:
                strcpy(current->teacher.politicalStatus, "群众");
                break;
            default:
                cursor(26, xy += 1);
                printf("输入的政治面貌选项无效。\n");
            }
            cursor(26, xy += 1);
            printf("学历: ");
            scanf("%s", current->teacher.education);
            cursor(26, xy += 1);
            printf("手机号码: ");
            //scanf("%s", &current->teacher.phoneNumber);
            Input_phoneNumber(current->teacher.phoneNumber);
            cursor(26, xy += 1);
            printf("邮箱: ");
            //scanf("%s", current->teacher.email);
            Input_Email(current->teacher.email);
            cursor(26, xy += 1);
            printf("修改成功！\n");
            Sleep(1000);
            return;
        }
        current = current->next;
    }

    printf("未找到对应工号的辅导员信息。\n");
}
//删除辅导员信息
void delete_Teacher(TeaInfor* head_TeaInfor, int id) {
    if (head_TeaInfor == NULL) {
        printf("暂无辅导员信息。\n");
        return;
    }

    TeaInfor* current = head_TeaInfor;
    TeaInfor* previous = NULL;

    // 遍历链表查找要删除的节点
    while (current != NULL) {
        if (current->teacher.id == id) {
            // 找到要删除的节点
            if (previous == NULL) {
                // 要删除的节点是链表头节点
                head_TeaInfor = current->next;
            }
            else {
                // 要删除的节点是中间或尾部节点
                previous->next = current->next;
            }

            free(current);
            printf("删除成功！\n");
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("未找到对应工号的辅导员信息。\n");
}

// 打印所有辅导员信息
void print_AllTeachers(TeaInfor* head_TeaInfor) {
    TeaInfor* current = head_TeaInfor->next;
    if (current == NULL) {
        printf("没有辅导员信息可供打印。\n");
        return;
    }

    printf("所有辅导员信息如下：\n");
    printf("-------------------------------------------------------------------\n");
    printf("工号\t姓名\t专业代码\t专业名称\t年级\t性别\t政治面貌\t学历\t电话号码\t\t电子邮箱\n");
    printf("-------------------------------------------------------------------\n");

    while (current != NULL) {
        Teacher teacher = current->teacher;
        printf("%d\t%s\t%d\t\t%s\t\t%d %d\t%c\t%s\t\t%s\t%s\t\t%s\n",
            teacher.id,
            teacher.name,
            teacher.majorCode,
            All_Aca[teacher.majorCode],
            teacher.grades[0],
            teacher.grades[1],
            teacher.gender,
            teacher.politicalStatus,
            teacher.education,
            teacher.phoneNumber,
            teacher.email);
        current = current->next;
    }

    printf("-------------------------------------------------------------------\n");
}

// 保存到文件
void saveTo_TeaInfor(TeaInfor* head_TeaInfor, const char* fileName) {
    if (head_TeaInfor == NULL) {
        printf("暂无辅导员信息。\n");
        return;
    }

    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }
    TeaInfor* current = head_TeaInfor->next;
    while (current != NULL && current->teacher.id != 0) {
        fprintf(file, "%d %s %d %d %d %c %s %s %s %s\n",
            current->teacher.id,
            current->teacher.name,
            current->teacher.majorCode,
            current->teacher.grades[0],
            current->teacher.grades[1],
            current->teacher.gender,
            current->teacher.politicalStatus,
            current->teacher.education,
            current->teacher.phoneNumber,
            current->teacher.email);

        current = current->next;
    }

    fclose(file);
    cursor(26,24);
    printf("教师信息保存成功！\n");
}

// 从文件读取
void loadFrom_TeaInfor(TeaInfor** head_TeaInfor, const char* fileName) {

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    // 清空链表
    TeaInfor* current = *head_TeaInfor;
    while (current != NULL) {
        TeaInfor* next = current->next;
        free(current);
        current = next;
    }
    *head_TeaInfor = createHead_TeaInfor();
    current = *head_TeaInfor;
    // 从文件读取数据并创建链表
    while (!feof(file)) {
        TeaInfor* newNode = (TeaInfor*)malloc(sizeof(TeaInfor));
        newNode->next = NULL;

        fscanf(file, "%d %s %d %d %d %c %s %s %s %s\n",
            &newNode->teacher.id,
            newNode->teacher.name,
            &newNode->teacher.majorCode,
            &newNode->teacher.grades[0],
            &newNode->teacher.grades[1],
            &newNode->teacher.gender,
            newNode->teacher.politicalStatus,
            newNode->teacher.education,
            newNode->teacher.phoneNumber,
            newNode->teacher.email);

        // 将新节点插入链表尾部
        TeaInfor* current1 = *head_TeaInfor;
        while (current1->next != NULL) {
            current1 = current1->next;
        }
        current1->next = newNode;
    }
    fclose(file);
    printf("教师信息读取成功！\n");
}