#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIST_StdInfor.h"
#include "LIST_StdGrade.h"

//��������ͷ�ڵ㣬����ͷ�ڵ��ַ
StdInfor* createStdInfor() {
    StdInfor* head = (StdInfor*)malloc(sizeof(StdInfor));
    head->next = NULL;
    return head;
}
//����ѧ��ѧ�ţ�����ѧ����Ϣ���������ַ
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

//����ѧ��ѧ�ţ�����ѧ����Ϣ
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


// �޸�ѧ����Ϣ
void modify_StdInfor(StdInfor* head, int studentId) {
    StdInfor* current = head;
    while (current != NULL) {
        if (current->id == studentId) {
            system("cls");
            int i = 6;
            cursor(26, i++);
            printf("������ѧ����Ϣ��\n");
            cursor(26, i++);
            printf("������");
            scanf("%s", current->name);
            cursor(26, i++);
            printf("�༶��");
            //scanf("%d", &(current->class));
            current->class = Input_Raw_Integer(2);
            cursor(26, i++);
            printf("�Ա�(M/F)��");
            //scanf(" %c", &(current->gender));
            current->gender = Input_MF();
            cursor(26, i++);
            printf("������������ò: \n");
            cursor(26, i++);
            printf("1. �й���Ա\n");
            cursor(26, i++);
            printf("2. ������Ա\n");
            cursor(26, i++);
            printf("3. Ⱥ��\n");
            cursor(26, i++);
            int flag = 1;
            while (flag)
            {
                int politicalStatusOption;
                //scanf("%d", &politicalStatusOption);
                politicalStatusOption = Input_1toNum(3);
                switch (politicalStatusOption) {
                case 1:
                    strcpy(current->politicalStatus, "�й���Ա");
                    flag = 0;
                    break;
                case 2:
                    strcpy(current->politicalStatus, "������Ա");
                    flag = 0;
                    break;
                case 3:
                    strcpy(current->politicalStatus, "Ⱥ��");
                    flag = 0;
                    break;
                default:
                    printf("�����������òѡ����Ч,����������\n");
                    break;
                }
            }
            cursor(26, i++);
            printf("�ֻ����룺");
            //scanf("%s", current->phoneNumber);
            Input_phoneNumber(current->phoneNumber);
            cursor(26, i++);
            printf("�������䣺");
            Input_Email(current->email);
            //scanf("%s", current->email);
            cursor(26, i++);
            printf("�Ƿ��ڶ���2Ϊ�ǣ�1Ϊ�񣩣�");
            //scanf("%d", &(current->isStudying));
            current->isStudying = Input_1toNum(2) - 1;
            current->t = 1;
            cursor(26, i++);
            printf("ѧ����Ϣ�޸ĳɹ���\n");
            return;
        }
        current = current->next;
    }

    printf("�Ҳ�����ѧ������Ϣ��\n");
}


// ɾ��ѧ����Ϣ
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
            printf("ѧ����Ϣɾ���ɹ���\n");
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("�Ҳ�����ѧ������Ϣ��\n");
}

//��ӡѧ����Ϣ

void print_StdInfor(StdInfor* head, struct Major* head_Major, int studentId) {
    StdInfor* current = head;
    while (current != NULL) {
        if (current->id == studentId) {
            printf("\n\t\tѧ�ţ�%d \t\t", current->id);
            printf("������%s \t", current->name);
            if (current->gender == 'M')
                printf("�Ա���\n");
            else
                printf("�Ա�Ů\n\t\t");
            struct Major* acc = search_MajorByStudentID(head_Major, studentId);
            if (acc != NULL)
            {
                int i = acc->majorNum / 100; int j = acc->majorNum % 100;
                printf("רҵ��%s��", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("�༶��%d \t", current->class);
                printf("������ò��%s \n\t\t", current->politicalStatus);
                printf("�ֻ����룺%s \t", current->phoneNumber);
                printf("�������䣺%s \t", current->email);
                printf("�Ƿ��ڶ���%s \n\t\t", current->isStudying ? "��" : "��");
            }
            else {
                printf("רҵ��δ֪\t");
				printf("�༶��%d \t", current->class);
				printf("������ò��%s \n\t\t", current->politicalStatus);
				printf("�ֻ����룺%s \t", current->phoneNumber);
				printf("�������䣺%s \t", current->email);
				printf("�Ƿ��ڶ���%s \n", current->isStudying ? "��" : "��");
            }
            return;
        }
        current = current->next;
    }

    printf("�Ҳ�����ѧ������Ϣ��\n");
}

// ����ѧ����Ϣ���ļ�
void saveTo_StdInfor(StdInfor* head, const char* fileName) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
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
    //printf("ѧ����Ϣ����ɹ���\n");
}

// ���ļ�����ѧ����Ϣ
void loadFrom_StdInfor(StdInfor** head, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // �������
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
    printf("ѧ����Ϣ���سɹ���\n");
}

//��ӡ����ѧ����Ϣ
void printAll_StdInfor(StdInfor* head, struct Major* head_Major) {
    StdInfor* current = head->next;
    while (current != NULL) {
        print_StdInfor(head, head_Major, current->id);
        current = current->next;
        printf("\n");
    }
}

//�ͷ�ѧ����Ϣ
void free_StdInfor(StdInfor* head) {
    StdInfor* current = head;
    while (current != NULL) {
        StdInfor* temp = current;
        current = current->next;
        free(temp);
    }
}