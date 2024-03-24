#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Func_isValid.h"
#include "LIST_SubInfor.h"
// �����½ڵ�
struct SubInfor* create_SubInfor() {
    struct SubInfor* newNode = (struct SubInfor*)malloc(sizeof(struct SubInfor));
    if (newNode != NULL) {
        printf("�������Ŀ���ƣ�");
        scanf("%s", newNode->SubName);

        while (1) {
            printf("�������Ŀ��ţ���λ��ĸ�Ӱ�λ���֣���");
            scanf("%s", newNode->SubInforNum);

            if (isValid_SubNum(newNode->SubInforNum)) {
                break;
            }
            else {
                printf("�γ̱�Ÿ�ʽ����ȷ�����������롣\n");
            }
        }

        printf("�������Ŀ������");
        scanf("%f", &(newNode->SubInforScore));
        printf("�������Ŀ�Ƿ�Ϊ���ޣ�1 ��ʾ�ǣ�0 ��ʾ�񣩣�");
        scanf("%d", &(newNode->SubRequired));

        newNode->next = NULL;
    }
    return newNode;
}


// ����ڵ㵽����
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

    //printf("��Ŀ�Ѳ��뵽�б��С�\n");
}

// ͨ���γ̺Ų��ҽڵ㲢�������ַ
struct SubInfor* search_SubInfor(struct SubInfor* head_SubInfor, const char* subNum) {
    struct SubInfor* temp = head_SubInfor;

    while (temp != NULL) {
        if (strcmp(temp->SubInforNum, subNum) == 0) {
            return temp;
        }
        temp = temp->next;
    }

    return NULL;  // δ�ҵ�ƥ��Ľڵ�
}


// �޸Ŀγ���Ϣ
bool checkAndReplace_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode) {
    struct SubInfor* temp = *head_SubInfor;
    struct SubInfor* prev = NULL;

    // ���������ȶԿγ̺�
    while (temp != NULL) {
        if (strcmp(temp->SubInforNum, newNode->SubInforNum) == 0) {
            return true;  // ������ͬ�Ŀγ̺�
        }
        prev = temp;
        temp = temp->next;
    }

    return false;  // ��������ͬ�Ŀγ̺�
}

// ��ʾ�����еĿ�Ŀ��Ϣ
void display_SubInfor(struct SubInfor* head_SubInfor) {
    if (head_SubInfor == NULL) {
        printf("����Ϊ�ա�\n");
        return;
    }

    struct SubInfor* temp = head_SubInfor;
    int count = 1;

    printf("��Ŀ�б�\n");

    while (temp != NULL) {
        printf("��Ŀ %d:\n", count);
        printf("���ƣ� %s\n", temp->SubName);
        printf("��ţ� %s\n", temp->SubInforNum);
        printf("������ %.2f\n", temp->SubInforScore);
        printf("�Ƿ���ޣ� %s\n", temp->SubRequired ? "��" : "��");

        temp = temp->next;
        count++;
    }
    printf("���пγ�����Ϊ��%d\n", count-1);
}

// �������еĿ�Ŀ��Ϣ���浽�ļ�
void saveTo_SubInfor(struct SubInfor* head_SubInfor, const char* filename) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    struct SubInfor* temp = head_SubInfor;

    while (temp != NULL) {
        fprintf(file, "%s,%s,%.2f,%d\n", temp->SubName, temp->SubInforNum, temp->SubInforScore, temp->SubRequired);

        temp = temp->next;
    }

    fclose(file);
    //printf("��Ŀ��Ϣ�ѱ��浽�ļ���\n");
}
//�������
void clear_SubInfor(struct SubInfor** head_SubInfor) {
	struct SubInfor* temp = *head_SubInfor;
	struct SubInfor* next = NULL;

	while (temp != NULL) {
		next = temp->next;
		free(temp);
		temp = next;
	}

	*head_SubInfor = NULL;
	//printf("��������ա�\n");
}

// ���ļ��м��ؿ�Ŀ��Ϣ������
void loadFrom_SubInfor(struct SubInfor** head_SubInfor, const char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // �������
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
    //printf("�Ѵ��ļ����ؿ�Ŀ��Ϣ��\n");
}

// ɾ��ָ����Ŀ�ڵ�
void delete_SubInfor(struct SubInfor** head_SubInfor, const char* subNum) {
    struct SubInfor* temp = *head_SubInfor;
    struct SubInfor* prev = NULL;
    //�жϱ��Ƿ�Ϊ��
    if (temp == NULL)
    {
        printf("��Ϊ�գ�\n");
            return;
    }
    // ͷ�ڵ����Ҫɾ���Ľڵ�
    if (temp != NULL && strcmp(temp->SubInforNum, subNum) == 0) {
        *head_SubInfor = temp->next;
        free(temp);
        printf("��Ŀ��ɾ����\n");
        return;
    }

    // Ѱ��Ҫɾ���Ľڵ�
    while (temp != NULL && strcmp(temp->SubInforNum, subNum) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("�Ҳ���Ҫɾ���Ŀ�Ŀ��\n");
        return;
    }

    if (prev == NULL) {
        *head_SubInfor = temp->next;
    }
    else {
        prev->next = temp->next;
    }
    free(temp);
    printf("��Ŀ��ɾ����\n");
}