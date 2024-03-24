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


//�״��ļ�����
void First_Load() {
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    //���ü��غ������ж��Ƿ���سɹ�
    loadFrom_StdGrade(&head_Major, FILENAME_GRA);
    //loadFromGrade(&head_StdGrade, FILENAME_GRA);
}
//ѧ���ɼ��˵�
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
    printf("�ѽ���ɼ�����˵���\n\n");

    while (1) {
        printf("1. ���רҵ\n");
        printf("2. ����꼶\n");
        printf("3. ���ѧ��\n");
        printf("4. ���ѧ���ɼ�\n");
        printf("5. �޸�ѧ���ɼ�\n");
        printf("6. ɾ��ѧ���ɼ�\n");
        printf("7. ɾ��ѧ��\n");
        printf("8. �������ݵ��ļ�\n");
        printf("9. ��ʾ����ѧ�������гɼ�\n");
        printf("10. �˳�ϵͳ\n");
        printf("����������ѡ��");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("������רҵ��ţ�");
            scanf("%s", majorNum);
            add_Major(&head_Major, majorNum);
            break;
        case 2:
            printf("������רҵ��ţ�");
            scanf("%s", majorNum);
            printf("�������꼶��");
            scanf("%d", &gradeNum);
            add_Grade(search_Major(&head_Major, majorNum), gradeNum);
            break;
        case 3:
            printf("������רҵ��ţ�");
            scanf("%s", majorNum);
            printf("�������꼶��");
            scanf("%d", &gradeNum);
            printf("������ѧ�ţ�");
            scanf("%d", &studentID);
            add_Student(&head_Major, studentID, majorNum, gradeNum);
            break;
        case 4:
            printf("������ѧ�ţ�");
            scanf("%d", &studentID);
            printf("������γ�����");
            scanf("%s", courseName);
            printf("������ɼ���");
            scanf("%f", &score);
            printf("�������޶�ѧ�ڣ�");
            scanf("%s", semester);
            printf("�������Ƿ����ޣ�0��ʾ��1��ʾ�ǣ���");
            scanf("%d", &isExempted);
            printf("�������Ƿ�ҿƣ�0��ʾ��1��ʾ�ǣ���");
            scanf("%d", &isFailed);
            if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == 1) {
                printf("��ӳɹ���\n");
            }
            else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -1) {
                printf("ѧ�������ڣ����ʧ�ܡ�\n");
            }
            else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -2) {
                printf("�γ����ظ������ʧ�ܡ�\n");
            }
            else {
                printf("���ʧ�ܡ�\n");
            }
            break;
        case 5:
            printf("������ѧ�ţ�");
            scanf("%d", &studentID);
            printf("������γ�����");
            scanf("%s", courseName);
            printf("�������µĳɼ���");
            scanf("%f", &newScore);
            if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                printf("�޸ĳɹ���\n");
            }
            else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                printf("ѧ�������ڣ��޸�ʧ�ܡ�\n");
            }
            else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                printf("�γ��������ڣ��޸�ʧ�ܡ�\n");
            }
            else {
                printf("�޸�ʧ�ܡ�\n");
            }
            break;
        case 6:
            printf("������ѧ�ţ�");
            scanf("%d", &studentID);
            printf("������γ�����");
            scanf("%s", courseName);
            if (delete_Score(&head_Major, studentID, courseName) == 1) {
                printf("ɾ���ɹ���\n");
            }
            else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                printf("ѧ�������ڣ�ɾ��ʧ�ܡ�\n");
            }
            else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                printf("�γ��������ڣ�ɾ��ʧ�ܡ�\n");
            }
            else {
                printf("ɾ��ʧ�ܡ�\n");
            }
            break;
        case 7:
            printf("������ѧ�ţ�");
            scanf("%d", &studentID);
            if (delete_Student(&head_Major, studentID) == 1) {
                printf("ɾ���ɹ���\n");
            }
            else {
                printf("ɾ��ʧ�ܡ�\n");
            }
            break;
        case 8:
            //���ñ��溯�����ж��Ƿ񱣴�ɹ�
            saveTo_StdGrade(&head_Major, "LIST_StdGrade.txt");
            break;
        case 9:
            printf("������ѧ��");
            scanf("%d", &studentID);
            query_Scores(&head_Major, studentID);
            break;
        case 10:
            printf("��лʹ�ã��ټ���\n");
            exit(0);
        default:
            printf("��Ч��ѡ�����������롣\n");
            break;
        }
    }
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
