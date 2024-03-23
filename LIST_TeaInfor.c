#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��ʦ��Ϣ�ṹ��
typedef struct TeacherInformation {
    int id;                     // ����
    char name[50];              // ����
    int majorCode;              // רҵ���
    char majorName[50];         // רҵ����
    int grades[2];              // �����꼶
    char gender;                // �Ա�
    char politicalStatus[50];   // ������ò
    char education[50];         // ѧ��
    char phoneNumber[20];       // �ֻ�����
    char email[50];             // ����
} TeaInfor;

// ����ڵ�ṹ��
typedef struct Teacher {
    TeaInfor teacher;
    struct Teacher* next;
} Teacher;

Teacher* head = NULL;  // ����ͷָ��

// ��������
void addTeacher();
void searchTeacher();
void modifyTeacher();
void deleteTeacher();
void saveToFile();
void loadFromFile();
void printAllTeachers();
int tt() {
    int choice;
    // �����ʼ��
    loadFromFile();
    while (1) {
        printf("\n---------------------------\n");
        printf("��ʦ��Ϣ����ϵͳ\n");
        printf("1. �����ʦ��Ϣ\n");
        printf("2. ��ѯ��ʦ��Ϣ\n");
        printf("3. �޸���ʦ��Ϣ\n");
        printf("4. ɾ����ʦ��Ϣ\n");
        printf("5. ���浽�ļ�\n");
        printf("6. ���ļ���ȡ\n");
        printf("7. ��ӡ������ʦ��Ϣ\n");
        printf("8. �˳�\n");
        printf("���������ѡ��: ");
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
            printf("ллʹ�ã��ټ���\n");
            return 0;
        default:
            printf("��Ч��ѡ��\n");
        }
    }

    return 0;
}

// �����ʦ��Ϣ����
void addTeacher() {
    Teacher* newNode = (Teacher*)malloc(sizeof(Teacher));
    newNode->next = NULL;

    printf("�����빤��: ");
    scanf("%d", &newNode->teacher.id);
    printf("����������: ");
    scanf("%s", newNode->teacher.name);
    printf("������רҵ����: ");
    scanf("%d", &newNode->teacher.majorCode);
    printf("������רҵ����: ");
    scanf("%s", newNode->teacher.majorName);
    printf("����������꼶���� (1 �� 2): ");
    int numGrades;
    scanf("%d", &numGrades);
    if (numGrades == 1) {
        printf("�������꼶: ");
        scanf("%d", &newNode->teacher.grades[0]);
        newNode->teacher.grades[1] = 0;
    }
    else if (numGrades == 2) {
        printf("�������꼶1: ");
        scanf("%d", &newNode->teacher.grades[0]);
        printf("�������꼶2: ");
        scanf("%d", &newNode->teacher.grades[1]);
    }
    else {
        printf("������꼶������Ч��\n");
        free(newNode);
        return;
    }
    printf("�������Ա� (M �� F): ");
    scanf(" %c", &newNode->teacher.gender);
    printf("������������ò: \n");
    printf("1. �й���Ա\n");
    printf("2. ������Ա\n");
    printf("3. Ⱥ��\n");
    int politicalStatusOption;
    scanf("%d", &politicalStatusOption);

    switch (politicalStatusOption) {
    case 1:
        strcpy(newNode->teacher.politicalStatus, "�й���Ա");
        break;
    case 2:
        strcpy(newNode->teacher.politicalStatus, "������Ա");
        break;
    case 3:
        strcpy(newNode->teacher.politicalStatus, "Ⱥ��");
        break;
    default:
        printf("�����������òѡ����Ч��\n");
        free(newNode);
        
    }
    printf("������ѧ��: ");
    scanf("%s", newNode->teacher.education);
    printf("������绰����: ");
    scanf("%s", newNode->teacher.phoneNumber);
    printf("�������������: ");
    scanf("%s", newNode->teacher.email);

    // ���½ڵ��������ͷ��
    newNode->next = head;
    head = newNode;

    printf("��ʦ��Ϣ��ӳɹ���\n");
}

// ��ѯ��ʦ��Ϣ
void searchTeacher() {
    if (head == NULL) {
        printf("������ʦ��Ϣ��\n");
        return;
    }

    int choice;
    printf("��ѡ���ѯ��ʽ��\n");
    printf("1. �����Ų�ѯ\n");
    printf("2. ��������ѯ\n");
    printf("���������ѡ��: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1: {
        int id;
        printf("������Ҫ��ѯ����ʦ����: ");
        scanf("%d", &id);

        Teacher* current = head;
        while (current != NULL) {
            if (current->teacher.id == id) {
                printf("���ţ�%d\n", current->teacher.id);
                printf("������%s\n", current->teacher.name);
                printf("רҵ��ţ�%d\n", current->teacher.majorCode);
                printf("רҵ���ƣ�%s\n", current->teacher.majorName);
                printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                printf("�Ա�%c\n", current->teacher.gender);
                printf("������ò��%s\n", current->teacher.politicalStatus);
                printf("ѧ����%s\n", current->teacher.education);
                printf("�ֻ����룺%s\n", current->teacher.phoneNumber);
                printf("���䣺%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("δ�ҵ���Ӧ���ŵ���ʦ��Ϣ��\n");
        break;
    }
    case 2: {
        char name[50];
        printf("������Ҫ��ѯ����ʦ����: ");
        scanf("%s", name);

        Teacher* current = head;
        while (current != NULL) {
            if (strcmp(current->teacher.name, name) == 0) {
                printf("���ţ�%d\n", current->teacher.id);
                printf("������%s\n", current->teacher.name);
                printf("רҵ��ţ�%d\n", current->teacher.majorCode);
                printf("רҵ���ƣ�%s\n", current->teacher.majorName);
                printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                printf("�Ա�%c\n", current->teacher.gender);
                printf("������ò��%s\n", current->teacher.politicalStatus);
                printf("ѧ����%s\n", current->teacher.education);
                printf("�ֻ����룺%s\n", current->teacher.phoneNumber);
                printf("���䣺%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("δ�ҵ���Ӧ��������ʦ��Ϣ��\n");
        break;
    }
    default:
        printf("��Ч��ѡ��\n");
    }
}

// �޸���ʦ��Ϣ
void modifyTeacher() {
    if (head == NULL) {
        printf("������ʦ��Ϣ��\n");
        return;
    }

    int id;
    printf("������Ҫ�޸ĵ���ʦ����: ");
    scanf("%d", &id);

    Teacher* current = head;
    while (current != NULL) {
        if (current->teacher.id == id) {
            printf("���ţ�%d\n", current->teacher.id);
            printf("������%s\n", current->teacher.name);
            printf("רҵ��ţ�%d\n", current->teacher.majorCode);
            printf("רҵ���ƣ�%s\n", current->teacher.majorName);
            printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            printf("�Ա�%c\n", current->teacher.gender);
            printf("������ò��%s\n", current->teacher.politicalStatus);
            printf("ѧ����%s\n", current->teacher.education);
            printf("�ֻ����룺%s\n", current->teacher.phoneNumber);
            printf("���䣺%s\n", current->teacher.email);

            printf("�������޸ĺ����Ϣ��\n");
            printf("����: ");
            scanf("%s", current->teacher.name);
            printf("רҵ���: ");
            scanf("%d", &current->teacher.majorCode);
            printf("רҵ����: ");
            scanf("%s", current->teacher.majorName);
            printf("�����꼶: ");
            scanf("%d", &current->teacher.grades[0]);
            scanf("%d", &current->teacher.grades[1]);
            printf("�Ա�: ");
            scanf(" %c", &current->teacher.gender);
            printf("������ò: ");
            scanf("%s", current->teacher.politicalStatus);
            printf("ѧ��: ");
            scanf("%s", current->teacher.education);
            printf("�ֻ�����: ");
            scanf("%s", current->teacher.phoneNumber);
            printf("����: ");
            scanf("%s", current->teacher.email);

            printf("�޸ĳɹ���\n");
            return;
        }
        current = current->next;
    }

    printf("δ�ҵ���Ӧ���ŵ���ʦ��Ϣ��\n");
}

void deleteTeacher() {
    if (head == NULL) {
        printf("������ʦ��Ϣ��\n");
        return;
    }

    int id;
    printf("������Ҫɾ������ʦ����: ");
    scanf("%d", &id);

    Teacher* current = head;
    Teacher* previous = NULL;

    // �����������Ҫɾ���Ľڵ�
    while (current != NULL) {
        if (current->teacher.id == id) {
            // �ҵ�Ҫɾ���Ľڵ�
            if (previous == NULL) {
                // Ҫɾ���Ľڵ�������ͷ�ڵ�
                head = current->next;
            }
            else {
                // Ҫɾ���Ľڵ����м��β���ڵ�
                previous->next = current->next;
            }

            free(current);
            printf("ɾ���ɹ���\n");
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("δ�ҵ���Ӧ���ŵ���ʦ��Ϣ��\n");
}

// ��ӡ������ʦ��Ϣ
void printAllTeachers() {
    Teacher* current = head;
    if (current == NULL) {
        printf("û����ʦ��Ϣ�ɹ���ӡ��\n");
        return;
    }

    printf("������ʦ��Ϣ���£�\n");
    printf("-------------------------------------------------------------------\n");
    printf("����\t����\tרҵ����\tרҵ����\t�꼶\t�Ա�\t������ò\tѧ��\t�绰����\t\t��������\n");
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

// ���浽�ļ�
void saveToFile() {
    if (head == NULL) {
        printf("������ʦ��Ϣ��\n");
        return;
    }

    char filename[50] = "LIST_TeaInfor";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
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
    printf("����ɹ���\n");
}

// ���ļ���ȡ
void loadFromFile() {
    char filename[50] = "LIST_TeaInfor";
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // �������
    Teacher* current = head;
    while (current != NULL) {
        Teacher* next = current->next;
        free(current);
        current = next;
    }
    head = NULL;

    // ���ļ���ȡ���ݲ���������
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

        // ���½ڵ��������ͷ��
        newNode->next = head;
        head = newNode;
    }

    fclose(file);
    printf("��ȡ�ɹ���\n");
}