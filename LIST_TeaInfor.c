#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIST_StdInfor.h"
#include "LIST_StdGrade.h"
#include "Func_isValid.h"
#include "LIST_TeaInfor.h"

// ����ͷ�ڵ�
TeaInfor* createHead_TeaInfor() {
    TeaInfor* head = (TeaInfor*)malloc(sizeof(TeaInfor));
    head->teacher.id = 0;
    head->next = NULL;
    return head;
}

// ��Ӹ���Ա��Ϣ����
void add_Teacher(TeaInfor* head_TeaInfor, int ID) {
    TeaInfor* newNode = (TeaInfor*)malloc(sizeof(TeaInfor));
    newNode->next = NULL;
    newNode->teacher.id = ID;
    int xy = 10;
    cursor(26, xy);
    printf("����������: ");
    scanf("%s", newNode->teacher.name);
    cursor(26, xy+=1);
    printf("������רҵ����: ");
    
    newNode->teacher.majorCode = Input_Raw_Integer(2);
    cursor(26, xy+=1);
    printf("����������꼶���� (1 �� 2): ");
    int numGrades = Input_1toNum(2);
    if (numGrades == 1) {
        cursor(26, xy+=1);
        printf("�������꼶: ");
        newNode->teacher.grades[0] = Input_Raw_Integer(2);
        newNode->teacher.grades[1] = 0;
    }
    else if (numGrades == 2) {
        cursor(26, xy+=1);
        printf("�������꼶1: ");
        newNode->teacher.grades[0] = Input_Raw_Integer(2);
        cursor(26, xy+=1);
        printf("�������꼶2: ");
        newNode->teacher.grades[1] = Input_Raw_Integer(2);
    }
    else {
        cursor(26, xy+=1);
        printf("������꼶������Ч��\n");
        free(newNode);
        return;
    }
    cursor(26, xy += 1);
    printf("�������Ա� (M �� F): ");
    newNode->teacher.gender = Input_MF();
    cursor(26, xy += 1);
    printf("������������ò: \n");
    cursor(26, xy += 1);
    printf("1. �й���Ա\n");
    cursor(26, xy += 1);
    printf("2. ������Ա\n");
    cursor(26, xy += 1);
    printf("3. Ⱥ��");
    cursor(26, xy += 1);
    int politicalStatusOption = Input_1toNum(3);

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
        cursor(26, xy += 1);
        printf("�����������òѡ����Ч��\n");
        free(newNode);


    }
    cursor(26, xy += 1);
    printf("������ѧ��: ");
    scanf("%s", newNode->teacher.education);
    cursor(26, xy += 1);
    printf("������绰����: ");
    Input_phoneNumber(newNode->teacher.phoneNumber);
    cursor(26, xy += 1);
    printf("�������������: ");
    Input_Email(newNode->teacher.email);

    // ���½ڵ��������β��
    TeaInfor* current = head_TeaInfor;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    cursor(26, xy += 1);
    printf("����Ա��Ϣ��ӳɹ���\n");
}

//��ѯ����Ա������ҵ�����1�����򷵻�0
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

//��ӡ����Ա��Ϣ
void print_Teacher(TeaInfor* head_TeaInfor, int ID) {
    TeaInfor* current = head_TeaInfor->next;
    while (current != NULL) {
        if (current->teacher.id == ID) {
            printf("���ţ�%d\t", current->teacher.id);
            printf("������%s\t", current->teacher.name);
            if (current->teacher.gender == 'M')
                printf("�Ա���\n");
            else
                printf("�Ա�Ů\n");
            int i = current->teacher.majorCode;
            printf("רҵ��%s\t", All_Aca[i]);
            printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            printf("������ò��%s\t", current->teacher.politicalStatus);
            printf("ѧ����%s\t", current->teacher.education);
            printf("�ֻ����룺%s\t", current->teacher.phoneNumber);
            printf("���䣺%s\n", current->teacher.email);
        }
        current = current->next;
    }
}

// ��ѯ����Ա��Ϣ
void search_Teacher(TeaInfor* head_TeaInfor) {
    if (head_TeaInfor == NULL) {
        printf("���޸���Ա��Ϣ��\n");
        return;
    }

    int choice;
    printf("��ѡ���ѯ��ʽ��\n");
    printf("1. �����Ų�ѯ\n");
    printf("2. ��������ѯ\n");
    printf("���������ѡ��: ");
    //scanf("%d", &choice);
    choice = Input_1toNum(2);
    switch (choice) {
    case 1: {
        int id;
        printf("������Ҫ��ѯ�ĸ���Ա����: ");
        //scanf("%d", &id);
        id = Input_Raw_Integer(6);
        TeaInfor* current = head_TeaInfor;
        while (current != NULL) {
            if (current->teacher.id == id) {
                printf("���ţ�%d\n", current->teacher.id);
                printf("������%s\n", current->teacher.name);
                printf("רҵ��ţ�%d\n", current->teacher.majorCode);
                int i = current->teacher.majorCode / 100; int j = current->teacher.majorCode % 100;
                printf("\t\tרҵ��%s��", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
                if (current->teacher.gender == 'M')
                    printf("�Ա���\t");
                else
                    printf("�Ա�Ů\t");
                printf("������ò��%s\n", current->teacher.politicalStatus);
                printf("ѧ����%s\n", current->teacher.education);
                printf("�ֻ����룺%s\n", current->teacher.phoneNumber);
                printf("���䣺%s\n", current->teacher.email);
            }
            current = current->next;
        }
        printf("δ�ҵ���Ӧ���ŵĸ���Ա��Ϣ��\n");
        break;
    }
    case 2: {
        char name[50];
        printf("������Ҫ��ѯ�ĸ���Ա����: ");
        scanf("%s", name);

        TeaInfor* current = head_TeaInfor;
        while (current != NULL) {
            if (strcmp(current->teacher.name, name) == 0) {
                printf("���ţ�%d\n", current->teacher.id);
                printf("������%s\n", current->teacher.name);
                printf("רҵ��ţ�%d\n", current->teacher.majorCode);
                int i = current->teacher.majorCode / 100; int j = current->teacher.majorCode % 100;
                printf("\t\tרҵ��%s��", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("�����꼶��%d, %d\t", current->teacher.grades[0], current->teacher.grades[1]);
                if (current->teacher.gender == 'M')
                    printf("�Ա���\t");
                else
                    printf("�Ա�Ů\t");
                printf("������ò��%s\t", current->teacher.politicalStatus);
                printf("ѧ����%s\t", current->teacher.education);
                printf("�ֻ����룺%s\t", current->teacher.phoneNumber);
                printf("���䣺%s\t", current->teacher.email);
            }
            current = current->next;
        }
        printf("δ�ҵ���Ӧ�����ĸ���Ա��Ϣ��\n");
        break;
    }
    default:
        printf("��Ч��ѡ��\n");
    }
}

// �޸ĸ���Ա��Ϣ
void modify_Teacher(TeaInfor* head_TeaInfor, int id) {
    system("cls");
    system("color F0");
    HideCursor();

    if (head_TeaInfor == NULL) {
        printf("���޸���Ա��Ϣ��\n");
        return;
    }

    TeaInfor* current = head_TeaInfor;
    while (current != NULL) {
        if (current->teacher.id == id) {
            int xy;
            xy = 1;
            cursor(26, xy);
            printf("���ţ�%d\n", current->teacher.id);
            cursor(26, xy += 1);
            printf("������%s\n", current->teacher.name);
            cursor(26, xy += 1);
            printf("רҵ��ţ�%d\n", current->teacher.majorCode);
            cursor(26, xy += 1);
            printf("�����꼶��%d, %d\n", current->teacher.grades[0], current->teacher.grades[1]);
            cursor(26, xy += 1);
            if (current->teacher.gender == 'M')
                printf("�Ա���\t");
            else
                printf("�Ա�Ů\t");
            cursor(26, xy += 1);
            printf("������ò��%s\n", current->teacher.politicalStatus);
            cursor(26, xy += 1);
            printf("ѧ����%s\n", current->teacher.education);
            cursor(26, xy += 1);
            printf("�ֻ����룺%s\n", current->teacher.phoneNumber);
            cursor(26, xy += 1);
            printf("���䣺%s\n", current->teacher.email);
            cursor(26, xy += 1);
            printf("\n");
            cursor(26, xy += 1);
            printf("����Խ�ʦ��Ϣ�����޸ģ�\n");
            cursor(26, xy += 1);
            printf("����: ");
            scanf("%s", current->teacher.name);
            cursor(26, xy += 1);
            printf("רҵ���: ");
            //scanf("%d", &current->teacher.majorCode);
            current->teacher.majorCode = Input_Raw_Integer(2);
            cursor(26, xy += 1);
            printf("�����꼶:\n");
            cursor(26, xy += 1);
            printf("����������꼶���� (1 �� 2): ");
            int numGrades = Input_1toNum(2);
            if (numGrades == 1) {
				cursor(26, xy += 1);
				printf("�����꼶:");
				current->teacher.grades[0] = Input_Raw_Integer(2);
				current->teacher.grades[1] = 0;
			}
			else if (numGrades == 2) {
				cursor(26, xy += 1);
				printf("�����һ���꼶: ");
				current->teacher.grades[0] = Input_Raw_Integer(2);
				cursor(26, xy += 1);
				printf("����ڶ����꼶: ");
				current->teacher.grades[1] = Input_Raw_Integer(2);
			}
            cursor(26, xy += 1);
            printf("�Ա�: ");
            //scanf(" %c", &current->teacher.gender);
            current->teacher.gender = Input_MF();
            cursor(26, xy += 1);
            printf("������ò: ");
            cursor(26, xy += 1);
            printf("1. �й���Ա\n");
            cursor(26, xy += 1);
            printf("2. ������Ա\n");
            cursor(26, xy += 1);
            printf("3. Ⱥ��");
            cursor(26, xy += 1);
            int politicalStatusOption = Input_1toNum(3);

            switch (politicalStatusOption) {
            case 1:
                strcpy(current->teacher.politicalStatus, "�й���Ա");
                break;
            case 2:
                strcpy(current->teacher.politicalStatus, "������Ա");
                break;
            case 3:
                strcpy(current->teacher.politicalStatus, "Ⱥ��");
                break;
            default:
                cursor(26, xy += 1);
                printf("�����������òѡ����Ч��\n");
            }
            cursor(26, xy += 1);
            printf("ѧ��: ");
            scanf("%s", current->teacher.education);
            cursor(26, xy += 1);
            printf("�ֻ�����: ");
            //scanf("%s", &current->teacher.phoneNumber);
            Input_phoneNumber(current->teacher.phoneNumber);
            cursor(26, xy += 1);
            printf("����: ");
            //scanf("%s", current->teacher.email);
            Input_Email(current->teacher.email);
            cursor(26, xy += 1);
            printf("�޸ĳɹ���\n");
            Sleep(1000);
            return;
        }
        current = current->next;
    }

    printf("δ�ҵ���Ӧ���ŵĸ���Ա��Ϣ��\n");
}
//ɾ������Ա��Ϣ
void delete_Teacher(TeaInfor* head_TeaInfor, int id) {
    if (head_TeaInfor == NULL) {
        printf("���޸���Ա��Ϣ��\n");
        return;
    }

    TeaInfor* current = head_TeaInfor;
    TeaInfor* previous = NULL;

    // �����������Ҫɾ���Ľڵ�
    while (current != NULL) {
        if (current->teacher.id == id) {
            // �ҵ�Ҫɾ���Ľڵ�
            if (previous == NULL) {
                // Ҫɾ���Ľڵ�������ͷ�ڵ�
                head_TeaInfor = current->next;
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

    printf("δ�ҵ���Ӧ���ŵĸ���Ա��Ϣ��\n");
}

// ��ӡ���и���Ա��Ϣ
void print_AllTeachers(TeaInfor* head_TeaInfor) {
    TeaInfor* current = head_TeaInfor->next;
    if (current == NULL) {
        printf("û�и���Ա��Ϣ�ɹ���ӡ��\n");
        return;
    }

    printf("���и���Ա��Ϣ���£�\n");
    printf("-------------------------------------------------------------------\n");
    printf("����\t����\tרҵ����\tרҵ����\t�꼶\t�Ա�\t������ò\tѧ��\t�绰����\t\t��������\n");
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

// ���浽�ļ�
void saveTo_TeaInfor(TeaInfor* head_TeaInfor, const char* fileName) {
    if (head_TeaInfor == NULL) {
        printf("���޸���Ա��Ϣ��\n");
        return;
    }

    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
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
    printf("��ʦ��Ϣ����ɹ���\n");
}

// ���ļ���ȡ
void loadFrom_TeaInfor(TeaInfor** head_TeaInfor, const char* fileName) {

    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // �������
    TeaInfor* current = *head_TeaInfor;
    while (current != NULL) {
        TeaInfor* next = current->next;
        free(current);
        current = next;
    }
    *head_TeaInfor = createHead_TeaInfor();
    current = *head_TeaInfor;
    // ���ļ���ȡ���ݲ���������
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

        // ���½ڵ��������β��
        TeaInfor* current1 = *head_TeaInfor;
        while (current1->next != NULL) {
            current1 = current1->next;
        }
        current1->next = newNode;
    }
    fclose(file);
    printf("��ʦ��Ϣ��ȡ�ɹ���\n");
}