#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 老师信息结构体
typedef struct TeacherInformation {
    int id;                     // 工号
    char name[50];              // 姓名
    int majorCode;              // 专业编号
    char majorName[50];         // 专业名称
    int grades[2];              // 所带年级
    char gender;                // 性别
    char politicalStatus[50];   // 政治面貌
    char education[50];         // 学历
    char phoneNumber[20];       // 手机号码
    char email[50];             // 邮箱
} TeaInfor;

// 链表节点结构体
typedef struct Teacher {
    TeaInfor teacher;
    struct Teacher* next;
} Teacher;

Teacher* head = NULL;  // 链表头指针

// 函数声明
void addTeacher();
void searchTeacher();
void modifyTeacher();
void deleteTeacher();
void saveToFile();
void loadFromFile();
void printAllTeachers();
int tt() {
    int choice;
    // 程序初始化
    loadFromFile();
    while (1) {
        printf("\n---------------------------\n");
        printf("老师信息管理系统\n");
        printf("1. 添加老师信息\n");
        printf("2. 查询老师信息\n");
        printf("3. 修改老师信息\n");
        printf("4. 删除老师信息\n");
        printf("5. 保存到文件\n");
        printf("6. 从文件读取\n");
        printf("7. 打印所有老师信息\n");
        printf("8. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addTeacher();
            break;
        case 2:
            searchTeacher();
            break;
        case 3:
            modifyTeacher();
            break;
        case 4:
            deleteTeacher();
            break;
        case 5:
            saveToFile();
            break;
        case 6:
            loadFromFile();
            break;
        case 7:
            printAllTeachers();
        case 8:
            printf("谢谢使用，再见！\n");
            return 0;
        default:
            printf("无效的选择。\n");
        }
    }

    return 0;
}

// 添加老师信息函数
void addTeacher() {
    Teacher* newNode = (Teacher*)malloc(sizeof(Teacher));
    newNode->next = NULL;

    printf("请输入工号: ");
    scanf("%d", &newNode->teacher.id);
    printf("请输入姓名: ");
    scanf("%s", newNode->teacher.name);
    printf("请输入专业代码: ");
    scanf("%d", &newNode->teacher.majorCode);
    printf("请输入专业名称: ");
    scanf("%s", newNode->teacher.majorName);
    printf("请输入带的年级数量 (1 或 2): ");
    int numGrades;
    scanf("%d", &numGrades);
    if (numGrades == 1) {
        printf("请输入年级: ");
        scanf("%d", &newNode->teacher.grades[0]);
        newNode->teacher.grades[1] = 0;
    }
    else if (numGrades == 2) {
        printf("请输入年级1: ");
        scanf("%d", &newNode->teacher.grades[0]);
        printf("请输入年级2: ");
        scanf("%d", &newNode->teacher.grades[1]);
    }
    else {
        printf("输入的年级数量无效。\n");
        free(newNode);
        return;
    }
    printf("请输入性别 (M 或 F): ");
    scanf(" %c", &newNode->teacher.gender);
    printf("请输入政治面貌: \n");
    printf("1. 中共党员\n");
    printf("2. 共青团员\n");
    printf("3. 群众\n");
    int politicalStatusOption;
    scanf("%d", &politicalStatusOption);

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
        printf("输入的政治面貌选项无效。\n");
        free(newNode);
        
    }
    printf("请输入学历: ");
    scanf("%s", newNode->teacher.education);
    printf("请输入电话号码: ");
    scanf("%s", newNode->teacher.phoneNumber);
    printf("请输入电子邮箱: ");
    scanf("%s", newNode->teacher.email);

    // 将新节点插入链表头部
    newNode->next = head;
    head = newNode;

    printf("老师信息添加成功！\n");
}

// 查询老师信息
void searchTeacher() {
    if (head == NULL) {
        printf("暂无老师信息。\n");
        return;
    }

    int choice;
    printf("请选择查询方式：\n");
    printf("1. 按工号查询\n");
    printf("2. 按姓名查询\n");
    printf("请输入你的选择: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        int id;
        printf("请输入要查询的老师工号: ");
        scanf("%d", &id);

        Teacher* current = head;
        while (current != NULL) {
            if (current->teacher.id == id) {
                printf("工号：%d\n", current->teacher.id);
                printf("姓名：%s\n", current->teacher.name);
                printf("专业编号：%d\n", current->teacher.majorCode);
                printf("专业名称：%s\n", current->teacher.majorName);
                printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                printf("性别：%c\n", current->teacher.gender);
                printf("政治面貌：%s\n", current->teacher.politicalStatus);
                printf("学历：%s\n", current->teacher.education);
                printf("手机号码：%s\n", current->teacher.phoneNumber);
                printf("邮箱：%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("未找到对应工号的老师信息。\n");
        break;
    }
    case 2: {
        char name[50];
        printf("请输入要查询的老师姓名: ");
        scanf("%s", name);

        Teacher* current = head;
        while (current != NULL) {
            if (strcmp(current->teacher.name, name) == 0) {
                printf("工号：%d\n", current->teacher.id);
                printf("姓名：%s\n", current->teacher.name);
                printf("专业编号：%d\n", current->teacher.majorCode);
                printf("专业名称：%s\n", current->teacher.majorName);
                printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                printf("性别：%c\n", current->teacher.gender);
                printf("政治面貌：%s\n", current->teacher.politicalStatus);
                printf("学历：%s\n", current->teacher.education);
                printf("手机号码：%s\n", current->teacher.phoneNumber);
                printf("邮箱：%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("未找到对应姓名的老师信息。\n");
        break;
    }
    default:
        printf("无效的选择。\n");
    }
}

// 修改老师信息
void modifyTeacher() {
    if (head == NULL) {
        printf("暂无老师信息。\n");
        return;
    }

    int id;
    printf("请输入要修改的老师工号: ");
    scanf("%d", &id);

    Teacher* current = head;
    while (current != NULL) {
        if (current->teacher.id == id) {
            printf("工号：%d\n", current->teacher.id);
            printf("姓名：%s\n", current->teacher.name);
            printf("专业编号：%d\n", current->teacher.majorCode);
            printf("专业名称：%s\n", current->teacher.majorName);
            printf("所带年级：%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            printf("性别：%c\n", current->teacher.gender);
            printf("政治面貌：%s\n", current->teacher.politicalStatus);
            printf("学历：%s\n", current->teacher.education);
            printf("手机号码：%s\n", current->teacher.phoneNumber);
            printf("邮箱：%s\n", current->teacher.email);

            printf("请输入修改后的信息：\n");
            printf("姓名: ");
            scanf("%s", current->teacher.name);
            printf("专业编号: ");
            scanf("%d", &current->teacher.majorCode);
            printf("专业名称: ");
            scanf("%s", current->teacher.majorName);
            printf("所带年级: ");
            scanf("%d", &current->teacher.grades[0]);
            scanf("%d", &current->teacher.grades[1]);
            printf("性别: ");
            scanf(" %c", &current->teacher.gender);
            printf("政治面貌: ");
            scanf("%s", current->teacher.politicalStatus);
            printf("学历: ");
            scanf("%s", current->teacher.education);
            printf("手机号码: ");
            scanf("%s", current->teacher.phoneNumber);
            printf("邮箱: ");
            scanf("%s", current->teacher.email);

            printf("修改成功！\n");
            return;
        }
        current = current->next;
    }

    printf("未找到对应工号的老师信息。\n");
}

void deleteTeacher() {
    if (head == NULL) {
        printf("暂无老师信息。\n");
        return;
    }

    int id;
    printf("请输入要删除的老师工号: ");
    scanf("%d", &id);

    Teacher* current = head;
    Teacher* previous = NULL;

    // 遍历链表查找要删除的节点
    while (current != NULL) {
        if (current->teacher.id == id) {
            // 找到要删除的节点
            if (previous == NULL) {
                // 要删除的节点是链表头节点
                head = current->next;
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

    printf("未找到对应工号的老师信息。\n");
}

// 打印所有老师信息
void printAllTeachers() {
    Teacher* current = head;
    if (current == NULL) {
        printf("没有老师信息可供打印。\n");
        return;
    }

    printf("所有老师信息如下：\n");
    printf("-------------------------------------------------------------------\n");
    printf("工号\t姓名\t专业代码\t专业名称\t年级\t性别\t政治面貌\t学历\t电话号码\t\t电子邮箱\n");
    printf("-------------------------------------------------------------------\n");

    while (current != NULL) {
        TeaInfor teacher = current->teacher;
        printf("%d\t%s\t%d\t\t%s\t\t%d %d\t%c\t%s\t\t%s\t%s\t\t%s\n",
            teacher.id,
            teacher.name,
            teacher.majorCode,
            teacher.majorName,
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
void saveToFile() {
    if (head == NULL) {
        printf("暂无老师信息。\n");
        return;
    }

    char filename[50] = "LIST_TeaInfor";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }
    Teacher* current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %d %s %d %d %c %s %s %s %s\n",
            current->teacher.id,
            current->teacher.name,
            current->teacher.majorCode,
            current->teacher.majorName,
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
    printf("保存成功！\n");
}

// 从文件读取
void loadFromFile() {
    char filename[50] = "LIST_TeaInfor";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }

    // 清空链表
    Teacher* current = head;
    while (current != NULL) {
        Teacher* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;

    // 从文件读取数据并创建链表
    while (!feof(file)) {
        Teacher* newNode = (Teacher*)malloc(sizeof(Teacher));
        newNode->next = NULL;

        fscanf(file, "%d %s %d %s %d %d %c %s %s %s %s\n",
            &newNode->teacher.id,
            newNode->teacher.name,
            &newNode->teacher.majorCode,
            newNode->teacher.majorName,
            &newNode->teacher.grades[0],
            &newNode->teacher.grades[1],
            &newNode->teacher.gender,
            newNode->teacher.politicalStatus,
            newNode->teacher.education,
            newNode->teacher.phoneNumber,
            newNode->teacher.email);

        // 将新节点插入链表头部
        newNode->next = head;
        head = newNode;
    }

    fclose(file);
    printf("读取成功！\n");
}