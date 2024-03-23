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
//�ļ�����
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
        printf("1. �����Ŀ�б�");
        cursor(26, 8);
        printf("2. ����ѧ���ɼ�");
        cursor(26, 10);
        printf("3. �˳�");
        cursor(26, 12);
        printf("������ѡ�");
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
            printf("��Ч��ѡ����������롣\n");
            break;
        }
        printf("\n");
    }
}

//ѧ���ɼ��˵�

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
        printf("�ѽ���ѧ���ɼ�����˵���\n\n");
        do {
            printf("1. ���ѧ��\n");
            printf("2. ¼��ѧ���ɼ�\n");
            printf("3. �޸�ѧ���ɼ�\n");
            printf("4. ɾ��ѧ���ɼ�\n");
            printf("5. ��ѯ����ѧ�������гɼ�\n");
            //printf("6. ���ļ�����\n");
            printf("6. ���浽�ļ�\n");
            printf("0. �˳�\n");
            printf("����������ѡ��");
            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &studentID);
                addStudent(&head_StdGrade, studentID);
                break;
            case 2:
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &studentID);
                struct Student* current = head_StdGrade;
                while (current != NULL) {
                    if (current->studentID == studentID)
                        break;
                    current = current->next;
                }
                if (current == NULL) {
                    printf("û�и���ѧ����\n");
                    break;
                }
                while (1) {
                    printf("�������Ŀ��ţ���λ��ĸ�Ӱ�λ���֣���");
                    scanf("%s", courseName);

                    if (isValid_SubNum(courseName)) {
                        break;
                    }
                    else {
                        printf("�γ̱�Ÿ�ʽ����ȷ�����������롣\n");
                    }
                }
                printf("������ɼ���");
                scanf("%f", &score);
                printf("�������޶�ѧ�ڣ���λ��Ч���֣�ǰ��λ��ݣ�����λ01Ϊ��һѧ�ڣ�02Ϊ�ڶ�ѧ�ڣ�");
                while (1) {
                    printf("�������Ŀ��ţ���λ��ĸ�Ӱ�λ���֣���");
                    scanf("%s", semester);

                    if (isValid_SemesterNum(semester)) {
                        break;
                    }
                    else {
                        printf("�޶�ѧ�ڸ�ʽ����ȷ�����������롣\n");
                    }
                }
                printf("�Ƿ����ޣ�1��ʾ�ǣ�0��ʾ�񣩣�");
                scanf("%d", &isExempted);
                printf("�Ƿ�ҿƣ�1��ʾ�ǣ�0��ʾ�񣩣�");
                scanf("%d", &isFailed);
                addScore(&head_StdGrade, studentID, courseName, score, semester, isExempted, isFailed);
                break;
            case 3:
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &studentID);
                printf("������γ�����");
                scanf("%s", courseName);
                printf("�������µĳɼ���");
                scanf("%f", &score);
                updateScore(&head_StdGrade, studentID, courseName, score);
                break;
            case 4:
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &studentID);
                printf("������Ҫɾ���Ŀγ�����");
                scanf("%s", courseName);
                deleteScore(&head_StdGrade, studentID, courseName);
                break;
            case 5:
                printf("������ѧ��ѧ�ţ�");
                scanf("%d", &studentID);
                queryScores(&head_StdGrade, studentID);
                break;
            /*case 6:
                loadFromGrade("FILENAME_GRA");// ���в������������ѧ����¼��ɼ���
                break;
            */
            case 6:
                // ����ѧ����Ϣ���ļ�
                saveToGrade(&head_StdGrade, "FILENAME_GRA");
                break;
            case 0:
                printf("��лʹ�óɼ�����ϵͳ��\n");
                break;
            default:
                printf("��Ч��ѡ��\n");
                break;
            }
            printf("\n");
        } while (choice != 0);
        return;
}
//�״��ļ�����
void First_Load() {
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    loadFromGrade(&head_StdGrade, FILENAME_GRA);
}
//��Ŀ�б�˵�
void Menu_SubInfor() {
    system("cls");
    system("color F0");
    HideCursor();
    cursor(26, 6);
    printf("�ѽ����Ŀ�б����˵���\n\n");
    int choice;
    //loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    while (1) {
        printf("1. ����/�޸Ŀ�Ŀ\n");
        printf("2. ��ʾ��Ŀ�б�\n");
        printf("3. ���浽�ļ�\n");
        printf("4. ���ļ�����\n");
        printf("5. ɾ����Ŀ\n");
        printf("6. �˳�\n");
        printf("������ѡ�");
        scanf("%d", &choice);
        switch (choice) {
        case 1: {
            struct SubInfor* newNode = create_SubInfor();
            if (checkAndReplace_SubInfor(&head_SubInfor, newNode)) {
                printf("��Ŀ�Ѵ��ڣ��Ƿ񸲸ǣ���Y/N����");
                char answer;
                scanf(" %c", &answer);
                if (toupper(answer) == 'Y') {
                    delete_SubInfor(&head_SubInfor, newNode->SubInforNum);
                    insert_SubInfor(&head_SubInfor, newNode);
                    printf("��Ŀ�Ѹ��ǡ�\n");
                }
                else {
                    free(newNode);
                    printf("��Ŀδ���뵽�б��С�\n");
                }
            }
            else {
                insert_SubInfor(&head_SubInfor, newNode);
                printf("��Ŀ�Ѳ��뵽�б��С�\n");
            }
            break;
        }
        case 2:
            display_SubInfor(head_SubInfor);
            break;
        case 3:
            saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
            printf("��Ŀ��Ϣ�ѱ��浽�ļ���\n");
            break;
        case 4:
            loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
            printf("�Ѵ��ļ����ؿ�Ŀ��Ϣ��\n");
            break;
        case 5: {
            char subNum[MAX_NUM_LENGTH];
            printf("������Ҫɾ���Ŀ�Ŀ��ţ�");
            scanf("%s", subNum);
            delete_SubInfor(&head_SubInfor, subNum);
            break;
        }
        case 6:
            printf("�������˳���\n");
            return;
        default:
            printf("��Ч��ѡ����������롣\n");
            break;
        }
        printf("\n");
    }
}