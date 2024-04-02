#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <Windows.h>
#include <setjmp.h>
#include "LIST_StdGrade.h"
#include "LIST_SubInfor.h"
#include "Face.h"
#include "page.h"
#include "Free_List.h"
#include "Func_calculate.h"
#include "Login_Register.h"
#include "Func_calculate.h"
#include "LIST_StdInfor.h"
#include "LIST_TeaInfor.h"
#include "Func_isValid.h"
#include "LIST_Bonus.h"

struct SubInfor* head_SubInfor = NULL;
struct Major* head_Major = NULL;
StdInfor* head_StdInfor = NULL;
TeaInfor* head_TeaInfor = NULL;
BonusNote* Head_Bonus = NULL;

// ѧ������������ӷ����
void Menu_Stu_bonus(BonusNote* Head, int ID);
// ��ʦ�������δ��˵�������ӷ�
void Tea_Audit(BonusNote* Head, int TeaID);
// 36 ѧ���Լ�ѡ��ɾ�����ּӷ���Ŀ
void Delet_Bonus(BonusNote* Head, int stu_ID);

int main()
{
    //currentWindow = GetActiveWindow();
    First_Load();
    welcome();
    int choice;
    int ID;
    while (1)
    {
        system("cls");
        choice = Login_Register_Main(&ID);
        if (choice == 2)
        {
            Menu_teacher(ID);
        }
        else if (choice == 1)
        {
            Menu_student(ID);
        }
        else if (choice == 3)
        {
            Menu_Admin();
        }
        else if (choice == 0)
        {
            End_Save();
            PrintExit();//�˳�
            return 0;
        }

    }
    return 0;
}
//ѧ���˵�
void Menu_student(int ID)
{
    int choice;
    if (search_StdInfor(head_StdInfor, ID) == NULL)
    {
        add_StdInfor(head_StdInfor, ID);
        printf("�㻹δ��д������Ϣ������д������Ϣ\n");
        Sleep(1000);
        // ����ѧ��ѧ�ţ�����ѧ����Ϣ
        modify_StdInfor(head_StdInfor, ID);
        saveTo_StdInfor(head_StdInfor, FILENAME_STD);
        system("pause");
    }
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        print_StdInfor(head_StdInfor, head_Major, ID);
        //cursor(26, 6);
        cursor(26, 10);
        printf("1. �޸ĸ�����Ϣ");
        cursor(26, 12);
        //cursor(26, 8);
        printf("2. ��ѯ���˳ɼ���&�꼶����");
        //cursor(26, 10);
        cursor(26, 14);
        printf("3. �����ҵ����ʼӷ�");
        cursor(26, 16);
        printf("4. �˳�");
        cursor(26, 18);
        printf("������ѡ�");
        cursor(26, 20);

        choice = Input_1toNum(4);
        switch (choice) {
        case 1: {
            system("cls");
            system("color F0");
            HideCursor();
            // ����ѧ��ѧ�ţ�����ѧ����Ϣ
            modify_StdInfor(head_StdInfor, ID);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            int studentID = ID;
            //��һ��ѧ�ţ����Ҹ���ѧ�����ڵ��꼶�ڵ�
            struct Grade* gradeNum = search_GradeByStudentID(&head_Major, studentID);

            //��һ��ѧ�ţ����Ҹ���ѧ�����ڵ�רҵ�ڵ�
            struct Major* majorNum = search_MajorByStudentID(head_Major, studentID);

            int i = query_Scores(&head_Major, studentID);
            if (i == 1) {
                printf("ѧ��������\n");
            }
            else if (i == 2)
            {
                printf("ѧ���޳ɼ�\n");
            }
            struct Student* Stu = search_Student(&head_Major, studentID);
            float add_GPA = Stu->add_GPA;
            float FinalGPA = finalGPA(head_Major, studentID, add_GPA);
            int result = Grade_ranking(head_Major, studentID, add_GPA, FinalGPA);
            float a;
            a = calculate_allmyscore(head_Major, head_SubInfor, studentID);
            printf("\n�����ѧ��Ϊ: %.1f \t", a);
            float b;
            b = calculate_myscore(head_Major, head_SubInfor, studentID);
            printf("����GPAѧ��Ϊ: %.1f \t", b);
            float c;
            c = calculate_GPA(head_Major, studentID, head_SubInfor);
            printf("����GPA: %.5f \t", c);
            printf("������ӷ�GPA: %.2f \t", add_GPA);
            printf("����GPA: %.5f \n", c + add_GPA);
            printf("����/�꼶������%d/%d \t", result, calculate_GradeStudentNum(head_Major, majorNum->majorNum, gradeNum->gradeNum));
            //�꼶ǰ�ٷ�֮��
            printf("�꼶ǰ%.2f%%\n", (float)result / calculate_GradeStudentNum(head_Major, majorNum->majorNum, gradeNum->gradeNum) * 100);
            system("pause");
            break;

        }
              void Print_Single_Comp(CompNote * Head);// 19 ��ӡ һ���� ���еı�����Ŀ (���˵ĽǶȴ�ӡ��
              void Print_Single_Paper(PaperNote * Head);// 20 ��ӡ һ���� ���е�������Ŀ
              void Print_Single_Proj(ProjNote * Head);// 21 ��ӡ һ���� ���еĽ�����Ŀ

              void Display_All_CompNote(BonusNote * Head);// 22 ��ӡ ������Ŀ �����мӷ����� ������������Ŀ�ĽǶȴ�ӡ��
              void Display_All_PaperNote(BonusNote * Head);// 23 ��ӡ ������Ŀ �����мӷ�����
              void Display_All_ProjNote(BonusNote * Head);// 24 ��ӡ ������Ŀ �����мӷ�����

              void Display_All_BonusInform(BonusNote * Head);// 25 ��ӡ ����������ӷ���Ϣ
        case 3:
            //���ʹ���˵�
            while (1)
            {
                BonusNote* BonusStr = Find_BonusNote_ByAcc(Head_Bonus, ID);
                if (BonusStr == NULL)
                {
                    StdInfor* Std = search_StdInfor(head_StdInfor, ID);
                    Add_BonusNote_Node(Head_Bonus, ID, Std->name);
                }
                system("cls");
                system("color F0");
                HideCursor();
                print_StdInfor(head_StdInfor, head_Major, ID);
                int xy = 6;
                cursor(26, xy);
                printf("1. ����������ӷ�\n");
                cursor(26, xy += 2);
                printf("2. �鿴���˼ӷּ�¼\n");
                cursor(26, xy += 2);
                printf("3. �������ָ���������ӷ���\n");//////////////////////////////            ������          ///////////////////////////////////////////////////////////////////////////////////////////////////////
                cursor(26, xy += 2);
                printf("4. �˳�\n");
                cursor(26, xy += 2);
                printf("������ѡ�");
                int choice = Input_1toNum(4);
                switch (choice) {
                case 1:
                    Menu_Stu_bonus(Head_Bonus, ID);
                    break;
                case 2:
                    while (1)
                    {
                        int flag = 0;
                        system("cls");
                        system("color F0");
                        HideCursor();
                        print_StdInfor(head_StdInfor, head_Major, ID);
                        int xy = 6;
                        BonusNote* Stu_B = Find_BonusNote_ByAcc(Head_Bonus, ID);
                        if (Stu_B->Next == NULL)
                        {
                            cursor(26, xy);
                            printf("δ�ҵ���ѧ���ļӷ���Ϣ��\n");
                            Sleep(1000);
                            break;
                        }
                        cursor(26, xy);
                        printf("1. �鿴���мӷּ�¼\n");
                        cursor(26, xy += 2);
                        printf("2. �鿴������Ŀ��¼\n");
                        cursor(26, xy += 2);
                        printf("3. �鿴������Ŀ��¼\n");
                        cursor(26, xy += 2);
                        printf("4. �鿴�󴴽�����Ŀ��¼\n");
                        cursor(26, xy += 2);
                        printf("5. �˳�\n");
                        cursor(26, xy += 2);
                        printf("������ѡ�");
                        int choice = Input_1toNum(5);
                        
                        switch (choice) {
                        case 1:
                            Display_Single_BonusNote(Head_Bonus, ID);
                            //system("pause");
                            break;
                        case 2:
                            system("cls");
                            Print_Single_Comp(Stu_B->Comphead);
                            system("pause");
                            break;
                        case 3:
                            system("cls");
                            Print_Single_Paper(Stu_B->Paperhead);
                            system("pause");
                            break;
                        case 4:
                            system("cls");
                            Print_Single_Proj(Stu_B->Projhead);
                            system("pause");
                            break;
                        case 5:
                            flag = 1;
                            break;
                        default:
                            printf("��Ч��ѡ����������롣\n");
                            break;
                        }
                        if (flag == 1)
                        {
                            break;
                        }
                        printf("\n");
                    }
                    break;
                case 3:
                    Delet_Bonus(Head_Bonus, ID); //////////////////////////////            ������          ///////////////////////////////////////////////////////////////////////////////////////////////////////
                    break;
                case 4:
                    return;
                default:
                    printf("��Ч��ѡ����������롣\n");
                    break;
                }
                printf("\n");
            }
        case 4:
            return;
        default:
            printf("��Ч��ѡ����������롣\n");
            break;
        }
        printf("\n");
    }
}
// ѧ������������ӷ����
void Menu_Stu_bonus(BonusNote* Head, int ID)
{
    do{
        system("cls");
        system("color F0");
        HideCursor();
        char Acc[8] = { 0 };
        Int_To_Str(ID, Acc);//��IDת���ַ���
        int Choice = 0;
        int xy = 6;
        cursor(26, xy);
        printf("1.���������Ŀ�ӷ�\n");
        cursor(26, xy+=2);
        printf("2.����������Ŀ�ӷ�\n");
        cursor(26, xy += 2);
        printf("3.������Ҽ����������Ŀ�ӷ�\n");
        cursor(26, xy += 2);
        printf("4.�˳�\n");
        cursor(26, xy += 2);
        printf("���������ѡ��");
        Choice = Input_1toNum(4);
        switch (Choice) {
        case 1:
            Add_Single_CompNote(Head, Acc, 's');
            continue;
        case 2:
            Add_Single_PaperNote(Head, Acc, 's');
            continue;
        case 3:
            Add_Single_ProjNote(Head, Acc, 's');
            continue;
        case 4:
            return;
        }
    } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
    return;
}

/**************************************************************************************************************************/

// 36 ѧ���Լ�ѡ��ɾ�����ּӷ���Ŀ
void Delet_Bonus(BonusNote* Head, int stu_ID) {
    char Acc[20] = { 0 };
    Int_To_Str(stu_ID, Acc);
    BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
    while (strcmp(pcurrent->Accountnum,Acc)!=0) {//�ҵ����ѧ����ѧ���ڵ�
        if (pcurrent->Next == NULL)
        {
            printf("δ�ҵ���ѧ���ļӷ���Ϣ��\n");
            system("pause");
            return;
        }
        pcurrent = pcurrent->Next;
    }
        
    CompNote* pcurrent2 = pcurrent->Comphead;
    PaperNote* pcurrent3 = pcurrent->Paperhead;
    ProjNote* pcurrent4 = pcurrent->Projhead;
    CompNote* pprev2 = NULL;
    PaperNote* pprev3 = NULL;
    ProjNote* pprev4 = NULL;
    while (pcurrent2 != NULL)
    {
        //printf("___________________________________________________________________________________________________________________________________________\n");
        //printf("ѧ��\t����\t������Ŀ����\t���˺�˳��\t��������\t�񽱵ȼ�\t���쵥λ\t��ʱ��\t���״̬\tӦ�Ӽ���\n");
        //printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t������Ŀ����: \t%s\n", pcurrent2->CompName);
        printf("\t\t\t����/˳��: \t%s\n", pcurrent2->Winers);
        printf("\t\t\t��������: \t%c\n", pcurrent2->ABC);
        printf("\t\t\t�񽱵ȼ�: \t%d\n", pcurrent2->AwardGrade);
        printf("\t\t\t���쵥λ: \n%s\n", pcurrent2->Sponsor);
        printf("\t\t\t��ʱ��: \t%s\n", pcurrent2->Time);
        //printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
        if (pcurrent2->Attribute == 1) { printf("\t\t\t���״̬: \t��׼\n"); }
        else if (pcurrent2->Attribute == 2) { printf("\t\t\t���״̬: \t�����\n"); }
        else { printf("\t\t\t���״̬: \t���\n"); }
        printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent2->Ponit);
        printf("\n");
        printf("\t\t\t�Ƿ�ɾ������Ŀ��\n");
        printf("\t\t\t1��ɾ��\n");
        printf("\t\t\t2������\n");
        printf("\t\t\t3���˳�\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent2 != pcurrent->Comphead && a) {//ͨ��aֻ����һ��
            pprev2 = pcurrent->Comphead;
            while (pprev2->Next != pcurrent2) {//������� pcurrent2 ���� ����ͷ��㣬��ô�ҵ� pcurrent2 ����һ���ڵ� pprev2
                pprev2 = pprev2->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent2 = pcurrent->Comphead) //������� pcurrent2 �� ����ͷ�ڵ㣬��ô��һ���ڵ���ͷ��ԭ����ͷ�ͷ�
            {
                CompNote* pprev = pcurrent2;
                pcurrent->Comphead = pcurrent2->Next;
                pcurrent2 = pcurrent2->Next;
                free(pprev);
            }
            else                  //������� pcurrent2 ���� ����ͷ��㣬��ôֱ��ͨ�� pprev2 ɾ��pcurrent2
            {
                pprev2->Next = pcurrent2->Next;
                free(pcurrent2);
                pcurrent2 = pprev2->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            printf("\n\t\t\tɾ���ɹ���\n\n");
            break;
        case 2:
            break;
        case 3:
            return;
            break;
        }
    }

    while (pcurrent3 != NULL) {

        //printf("_____________________________________________________________________________________________________________________________________________________\n");
        //printf("ѧ��\t����\t��������\t�������ߺ�˳��\t�ڿ�����/��������\t����ʱ��\t��/��\t���ĺ�\tҳ�뷶Χ\t���״̬\tӦ�Ӽ���\n");
        //printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
        
        printf("\t\t\tѧ�ţ�\t%s\n", pcurrent->Accountnum);
        printf("\t\t\t������\t%s\n", pcurrent->Name);
        printf("\t\t\t�������ƣ�\t%s\n", pcurrent3->PaperName);
        printf("\t\t\t��������/˳��\t%s\n", pcurrent3->Writers);
        printf("\t\t\t�ڿ�����/�������ƣ�\t%s\n", pcurrent3->Journal_Conference);
        printf("\t\t\t����ʱ�䣺\t%s\n", pcurrent3->Time);
        printf("\t\t\t��/�ڣ�\t%s\t%s\t%s\n", pcurrent3->Volume_Page[0]);
        printf("\t\t\t���ĺ�: \t%s\n", pcurrent3->Volume_Page[1]);
        printf("\t\t\tҳ�뷶Χ: \t%s\n", pcurrent3->Volume_Page[2]);
        //printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
        if (pcurrent3->Attribute == 1) { printf("\t\t\t���״̬: \t��׼\n"); }
        else if (pcurrent3->Attribute == 2) { printf("\t\t\t���״̬: \t�����\n"); }
        else { printf("\t\t\t���״̬: \t���\n"); }
        printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent3->Ponit);
        printf("\n");
        
        printf("\t\t\t�Ƿ�ɾ������Ŀ��\n");
        printf("\t\t\t1��ɾ��\n");
        printf("\t\t\t2������\n");
        printf("\t\t\t3���˳�\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent3 != pcurrent->Paperhead && a) {//ͨ��aֻ����һ��
            pprev3 = pcurrent->Paperhead;
            while (pprev3->Next != pcurrent3) {//������� pcurrent3 ���� ����ͷ��㣬��ô�ҵ� pcurrent3 ����һ���ڵ� pprev3
                pprev3 = pprev3->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent3 = pcurrent->Paperhead) //������� pcurrent3 �� ����ͷ�ڵ㣬��ô��һ���ڵ���ͷ��ԭ����ͷ�ͷ�
            {
                CompNote* pprev = pcurrent3;
                pcurrent->Paperhead = pcurrent3->Next;
                pcurrent3 = pcurrent3->Next;
                free(pprev);
            }
            else                  //������� pcurrent3 ���� ����ͷ��㣬��ôֱ��ͨ�� pprev3 ɾ��pcurrent3
            {
                pprev3->Next = pcurrent3->Next;
                free(pcurrent3);
                pcurrent3 = pprev3->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            printf("\n\t\t\tɾ���ɹ���\n\n");
            break;
        case 2:
            break;
        case 3:
            return;
            break;
        }
    }

    while (pcurrent4 != NULL) {

        //printf("____________________________________________________________________________________________________________________________________________________________________\n");
        //printf("ͬ�����\t��Ŀ����\t���г�Ա��˳��\tָ����ʦ����\t�񽱵ȼ�\t����ʱ��\t����ʱ��\t��Ŀ���\t��������\t���״̬\tӦ�Ӽ���\n");
        //printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\tѧ�ţ�\t%s\n", pcurrent->Accountnum);
        printf("\t\t\t������\t%s\n", pcurrent->Name);
        printf("\t\t\t��Ŀ����: \t%s\n", pcurrent4->ProjName);
        printf("\t\t\t���г�Ա��˳��: \t%s\n", pcurrent4->Members);
        printf("\t\t\tָ����ʦ����: \t%s\n", pcurrent4->Advisor);
        printf("\t\t\t����ʱ��: \t%s\n", pcurrent4->Start_time);
        printf("\t\t\t����ʱ��: \t%s\n", pcurrent4->Finish_time);
        printf("\t\t\t��Ŀ���: \t%s\n", pcurrent4->ProjNum);
        //printf("\t\t\t��������: \t%d\n", pcurrent->Role);
        if (pcurrent4->Role == 1) { printf("\t\t\t��������: \t������\n"); }
        else if (pcurrent4->Role == 2) { printf("\t\t\t��������: \t��Ա\n"); }
        else { printf("\t\t\t��������: \t����\n"); }
        //printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
        if (pcurrent4->Attribute == 1) { printf("\t\t\t���״̬: \t��׼\n"); }
        else if (pcurrent4->Attribute == 2) { printf("\t\t\t���״̬: \t�����\n"); }
        else { printf("\t\t\t���״̬: \t���\n"); }
        printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent4->Ponit);
        printf("\n");

        printf("\t\t\t�Ƿ�ɾ������Ŀ��\n");
        printf("\t\t\t1��ɾ��\n");
        printf("\t\t\t2������\n");
        printf("\t\t\t3���˳�\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent4 != pcurrent->Projhead && a) {//ͨ��aֻ����һ��
            pprev4 = pcurrent->Projhead;
            while (pprev4->Next != pcurrent4) {//������� pcurrent4 ���� ����ͷ��㣬��ô�ҵ� pcurrent4 ����һ���ڵ� pprev4
                pprev4 = pprev4->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent4 = pcurrent->Projhead) //������� pcurrent4 �� ����ͷ�ڵ㣬��ô��һ���ڵ���ͷ��ԭ����ͷ�ͷ�
            {
                CompNote* pprev = pcurrent4;
                pcurrent->Projhead = pcurrent4->Next;
                pcurrent4 = pcurrent4->Next;
                free(pprev);
            }
            else                  //������� pcurrent4 ���� ����ͷ��㣬��ôֱ��ͨ�� pprev4 ɾ��pcurrent4
            {
                pprev4->Next = pcurrent4->Next;
                free(pcurrent4);
                pcurrent4 = pprev4->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            printf("\n\t\tɾ���ɹ���\n\n");
            break;
        case 2:
            break;
        case 3:
            return;
            break;
        }
    }
    struct Student* Stu = search_Student(&head_Major, stu_ID);
    Stu->add_GPA = pcurrent->Bonusponit;
    printf("\n\t\tѡ��ɾ��������\n\n");
}
/**************************************************************************************************************************/


//����Ա�˵�
void Menu_teacher(int ID)
{
    if (search_TeacherByID(head_TeaInfor, ID) == NULL)
    {
        system("cls");
        cursor(26, 6);
        printf("����δ��д������Ϣ������д������Ϣ\n");
        Sleep(1000);
        add_Teacher(head_TeaInfor, ID);
        // ����ѧ��ѧ�ţ�����ѧ����Ϣ
        //modify_Teacher(head_TeaInfor, ID);
        saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
        system("pause");
    }
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        print_Teacher(head_TeaInfor, ID);
        int xy = 6;
        cursor(26, xy);
        printf("1. �޸ĸ�����Ϣ");
        cursor(26, xy+=2);
        printf("2. ����ѧ���ɼ�");
        cursor(26, xy += 2);
        printf("3. ����ѧ�����ʼӷ�����");
        cursor(26, xy += 2);
        printf("4. �˳�");
        cursor(26, xy += 2);
        printf("������ѡ�");
        choice = Input_1toNum(4);
        switch (choice) {
        case 1: {
            modify_Teacher(head_TeaInfor, ID);
            break;
        }
        case 2:
            Menu_StdGrade(ID);
            break;
        case 3:
            Tea_Audit(Head_Bonus, ID);
            break;
        case 4:
            return;
        default:
            printf("��Ч��ѡ����������롣\n");
            break;
        }
        printf("\n");
    }
}

void Tea_Audit(BonusNote* Head, int TeaID)// 37 ��ʦ�������δ��˵�������ӷ�
{
    int tag = 0;
    BonusNote* pcurrent = Head->Next;
    TeaInfor* Tea = search_TeacherByID(head_TeaInfor, TeaID);
    while (pcurrent != NULL) {//////////////////////////////////////////////////////////////////////////////////////////////
        /*��ʦ��ѧ��רҵƥ�������*/
        int stu_ID = atoi(pcurrent->Accountnum);
        struct Major* StuM = search_MajorByStudentID(head_Major, stu_ID);
        if(StuM==NULL)
            		{
			pcurrent = pcurrent->Next;
			continue;
		}
        if(StuM->majorNum / 100 != Tea->teacher.majorCode)
		{
			pcurrent = pcurrent->Next;
			continue;
		}
        tag = 1;
        CompNote* pcurrent2 = pcurrent->Comphead;
        PaperNote* pcurrent3 = pcurrent->Paperhead;
        ProjNote* pcurrent4 = pcurrent->Projhead;

        system("cls");

        while (pcurrent2 != NULL)
        {
            if (pcurrent2->Attribute == 2)
            {
                //printf("___________________________________________________________________________________________________________________________________________\n");
                //printf("ѧ��\t����\t������Ŀ����\t���˺�˳��\t��������\t�񽱵ȼ�\t���쵥λ\t��ʱ��\t���״̬\tӦ�Ӽ���\n");
                //printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("\t\t\tѧ��: %s\n", pcurrent->Accountnum);
                printf("\t\t\t����: %s\n", pcurrent->Name);
                printf("\t\t\t������Ŀ����: %s\n", pcurrent2->CompName);
                printf("\t\t\t����/˳��: %s\n", pcurrent2->Winers);
                printf("\t\t\t��������: %c\n", pcurrent2->ABC);
                printf("\t\t\t�񽱵ȼ�: %d\n", pcurrent2->AwardGrade);
                printf("\t\t\t���쵥λ: %s\n", pcurrent2->Sponsor);
                printf("\t\t\t��ʱ��: %s\n", pcurrent2->Time);
                printf("\t\t\tӦ�Ӽ���: %.2f\n", pcurrent2->Ponit);

                printf("\n\t\t\t��ѡ�����Ŀ�Ƿ����ͨ����\n");
                printf("\t\t\t1����׼\n");
                printf("\t\t\t2�������\n");
                printf("\t\t\t3�����\n");
                printf("\t\t\t���ѡ��");
                pcurrent2->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            }
            pcurrent2 = pcurrent2->Next;
        }

        while (pcurrent3 != NULL) {
            if (pcurrent3->Attribute == 2)
            {
                //printf("_____________________________________________________________________________________________________________________________________________________\n");
                //printf("ѧ��\t����\t��������\t�������ߺ�˳��\t�ڿ�����/��������\t����ʱ��\t��/��\t���ĺ�\tҳ�뷶Χ\t���״̬\tӦ�Ӽ���\n");
                //printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
                
                printf("\t\t\tѧ��: %s\n", pcurrent->Accountnum);
                printf("\t\t\t����: %s\n", pcurrent->Name);
                printf("\t\t\t��������: %s\n", pcurrent3->PaperName);
                printf("\t\t\t��������/˳��: %s\n", pcurrent3->Writers);
                printf("\t\t\t�ڿ�����/��������: %s\n", pcurrent3->Journal_Conference);
                printf("\t\t\t����ʱ��: %s\n", pcurrent3->Time);
                printf("\t\t\t��/��: %s\n", pcurrent3->Volume_Page[0]);
                printf("\t\t\t���ĺ�: %s\n", pcurrent3->Volume_Page[1]);
                printf("\t\t\tҳ�뷶Χ: %s\n", pcurrent3->Volume_Page[2]);
                printf("\t\t\tӦ�Ӽ���: %.2f\n", pcurrent3->Ponit);
                printf("\n\t\t\t��ѡ�����Ŀ�Ƿ����ͨ����\n");
                printf("\t\t\t1����׼\n");
                printf("\t\t\t2�������\n");
                printf("\t\t\t3�����\n");
                printf("\t\t\t���ѡ��");
                pcurrent3->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            }
            pcurrent3 = pcurrent3->Next;
        }

        while (pcurrent4 != NULL) {
            if (pcurrent4->Attribute == 2)
            {
                //printf("____________________________________________________________________________________________________________________________________________________________________\n");
                //printf("ͬ�����\t��Ŀ����\t���г�Ա��˳��\tָ����ʦ����\t�񽱵ȼ�\t����ʱ��\t����ʱ��\t��Ŀ���\t��������\t���״̬\tӦ�Ӽ���\n");
                //printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                
                printf("\t\t\tѧ��: %s\n", pcurrent->Accountnum);
                printf("\t\t\t����: %s\n", pcurrent->Name);
                printf("\t\t\t��Ŀ����: %s\n", pcurrent4->ProjName);
                printf("\t\t\t���г�Ա/˳��: %s\n", pcurrent4->Members);
                printf("\t\t\tָ����ʦ����: %s\n", pcurrent4->Advisor);
                printf("\t\t\t�񽱵ȼ�: %d\n", pcurrent4->Attribute);
                printf("\t\t\t����ʱ��: %s\n", pcurrent4->Start_time);
                printf("\t\t\t����ʱ��: %s\n", pcurrent4->Finish_time);
                printf("\t\t\t��Ŀ���: %s\n", pcurrent4->ProjNum);
                printf("\t\t\t��������: %d\n", pcurrent4->Role);
                printf("\t\t\tӦ�Ӽ���: %.2f\n", pcurrent4->Ponit);
                printf("\n\t\t\t��ѡ�����Ŀ�Ƿ����ͨ����\n");
                printf("\t\t\t1����׼\n");
                printf("\t\t\t2�������\n");
                printf("\t\t\t3�����\n");
                printf("\t\t\t���ѡ��");
                pcurrent4->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�����ѧ���ӷּ���
            }
            pcurrent4 = pcurrent4->Next;
        }
        struct Student* Stu = search_Student(&head_Major, stu_ID);
        Stu->add_GPA = pcurrent->Bonusponit;

        pcurrent = pcurrent->Next;
    }
    if(tag==0)
        printf("\n\n\t\t\t��ǰ�޴������Ŀ\n");
    system("pause");
}

//�״��ļ�����
void First_Load() {
    //���سɼ���Ϣ
    loadFrom_StdGrade(&head_Major, FILENAME_GRA);
    //���ؿγ���Ϣ
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    //����ѧ����Ϣ
    loadFrom_StdInfor(&head_StdInfor, FILENAME_STD);
    //���ظ���Ա��Ϣ
    loadFrom_TeaInfor(&head_TeaInfor, FILENAME_TEA);
    //��������������ѧ����GPA
    calculate_AllGPA(head_Major, head_SubInfor);
    //�������ʼӷ�ϵͳ
    Head_Bonus = Start_Logging_bonusFile();
}

//����ʱ�Զ�����
void End_Save()
{
    saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
    //���ü��غ������ж��Ƿ���سɹ�
    saveTo_StdGrade(&head_Major, FILENAME_GRA);
    //��������������ѧ����GPA
    calculate_AllGPA(head_Major, head_SubInfor);
    //����ѧ����Ϣ
    saveTo_StdInfor(head_StdInfor, FILENAME_STD);
    // ���渨��Ա��Ϣ
    saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
    // �������ʼӷ�ϵͳ
    Save_List_To_bonusFile(Head_Bonus);
}
void Menu_StdGrade(int ID) {
    int choice;
    int majorNum;
    int gradeNum;
    int studentID;
    char courseName[20];
    float score;
    char semester[5];
    int isExempted;
    int isFailed;
    float newScore;
    int teaGrade = 0;
    TeaInfor* Tea = search_TeacherByID(head_TeaInfor, ID);
    int teaMajor;
    int TeaM = Tea->teacher.majorCode;
    int xy = 6;
    int flag = 1, num = 0;
    while (flag)
    {
        system("cls");
        system("color F0");
        HideCursor();
        print_Teacher(head_TeaInfor, ID);
        if (Tea == NULL)
        {
            cursor(26, 6);
            printf("�����Ǹ���Ա���޷�����ɼ�����˵�\n");
            return;
        }
        num = 0;
        xy = 6;
        cursor(26, xy);
        printf("��ѡ����Ҫ�����רҵ��\n");
        for (int i = 0; i < 10; i++)
        {
            if (ALL_Prof[TeaM][i] != NULL)
            {
                cursor(26, xy += 2);
                printf("%d: %s\n", num + 1, ALL_Prof[TeaM][i]);
                num++;
            }
            else {
                break;
            }
        }
        cursor(26, xy += 2);
        printf("������ѡ�");
        int majorNum = Input_1toNum(num);
        teaMajor = majorNum + TeaM * 100 - 1;
        if (search_Major(head_Major, teaMajor) == NULL)
        {
            cursor(26, xy += 3);
            printf("רҵ�����ڣ�����������\n");
            Sleep(1000);
        }
        else
        {
            flag = 0;
        }
    }
    if (Tea->teacher.grades[1] != 0)
    {
        cursor(26, ++xy);
        printf("ѡ����Ҫ������꼶:");
        cursor(26, ++xy);
        printf("1: %d\t2: %d\n", Tea->teacher.grades[0], Tea->teacher.grades[1]);
        cursor(26, ++xy);
        int choice = Input_1toNum(2);
        teaGrade = Tea->teacher.grades[choice - 1];
    }
    else {
        teaGrade = Tea->teacher.grades[0] - 1;
    }

    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        print_Teacher(head_TeaInfor, ID);
        int i = teaMajor / 100; int j = teaMajor % 100;
        printf("���ڹ���\tרҵ��%s��", All_Aca[i]);
        printf("%s\t", ALL_Prof[i][j]);
        printf("�꼶: %d��\n", teaGrade);
        int xy = 3;
        cursor(26, xy+=2);
        printf(" �ѽ���ɼ�����˵���\n\n");
        cursor(26, xy+=2);
        printf("1. ���Ӹ��˳ɼ�");
        cursor(26, xy+=2);
        printf("2. �޸ĸ��˳ɼ�");
        cursor(26, xy+=2);
        printf("3. ɾ�����˳ɼ�");
        cursor(26, xy += 2);
        printf("4. �鿴���˳ɼ�");
        cursor(26, xy += 2);
        printf("5. �鿴�꼶�ɼ�");
        cursor(26, xy += 2);
        printf("6. �����ϼ��˵�");
        cursor(26, xy += 2);
        printf("������ѡ�");
        cursor(26, xy += 2);

        choice = Input_1toNum(6);
        switch (choice) {
        case 1: {
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                print_Teacher(head_TeaInfor, ID);
                int i = teaMajor / 100; int j = teaMajor % 100;
                printf("\n\t���ڹ���רҵ��%s��", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("\t�꼶: %d��\n", teaGrade);

                cursor(26, xy += 2);
                printf("������ѧ�ţ�");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("ѧ�������ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("�㲻�����ѧ���ĸ���Ա���޷���ӳɼ�\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("������γ̱�ţ�");
                Input_SubNum(courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
				{
					cursor(26, xy += 2);
					printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
					Sleep(1000);
					continue;
				}
                cursor(26, xy += 2);
                printf("������ɼ���");
                score = Input_Float(3, 2);
                cursor(26, xy += 2);
                printf("�������޶�ѧ�ڣ�");
                Input_SemesterNum(semester);
                cursor(26, xy += 2);
                printf("�������Ƿ����ޣ�1��ʾ�ǣ�2��ʾ�񣩣�");
                isExempted = Input_1toNum(2) - 1;
                cursor(26, xy += 2);
                printf("�������Ƿ�ҿƣ�1��ʾ��2��ʾ�ǣ���");
                isFailed = Input_1toNum(2) - 1;
                cursor(26, xy += 2);
                if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == 1) {
                    printf("��ӳɹ���\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -1) {
                    printf("ѧ�������ڣ����ʧ�ܡ�\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -2) {
                    printf("�γ̱���ظ������ʧ�ܡ�\n");
                }
                else {
                    printf("���ʧ�ܡ�\n");
                    Sleep(1000);
                }
                continue;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        }
        case 2: {
            // �޸ĸ��˳ɼ�
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, xy += 2);
                printf("������ѧ�ţ�");
                //scanf("%d", &studentID);

                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("ѧ�������ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("�㲻�����ѧ���ĸ���Ա���޷���ӳɼ�\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("������γ̱�ţ�");
                //scanf("%s", courseName);
                Input_SubNum(courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("�������µĳɼ���");
                //scanf("%f", &newScore);
                newScore = Input_Float(3, 2);
                if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                    cursor(26, xy += 2);
                    printf("�޸ĳɹ���\n");
                    continue;
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                    cursor(26, xy += 2);
                    printf("ѧ�������ڣ��޸�ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                    cursor(26, xy += 2);
                    printf("�γ̱�Ų����ڣ��޸�ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                else {
                    cursor(26, xy += 2);
                    printf("�޸�ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                // break; 
                continue;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;


        }
        case 3: {
            // ɾ�����˳ɼ�
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, xy += 2);
                printf("������ѧ�ţ�");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("ѧ�������ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("�㲻�����ѧ���ĸ���Ա���޷���ӳɼ�\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("������γ̱�ţ�");
                //scanf("%s", courseName);
                Input_SubNum(courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                if (delete_Score(&head_Major, studentID, courseName) == 1) {
                    cursor(26, xy += 2);
                    printf("ɾ���ɹ���\n");
                    Sleep(1000);
                    continue;
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                    cursor(26, xy += 2);
                    printf("ѧ�������ڣ�ɾ��ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                    cursor(26, xy += 2);
                    printf("�γ̱�Ų����ڣ�ɾ��ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                else {
                    cursor(26, xy += 2);
                    printf("ɾ��ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                //break;
                continue;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        }
        case 4: {
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                int studentID = 0;
                system("cls");
                cursor(26, xy += 2);
                
                printf("������ѧ�ţ�");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                system("cls");
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("ѧ��û�в��ҵ�������������롣\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("�㲻�����ѧ���ĸ���Ա���޷���ӳɼ�\n");
                    Sleep(1000);
                    continue;
                }

                int i = query_Scores(&head_Major, studentID);
                if (i == 1) {
                    cursor(26, xy += 2);
                    printf("ѧ��������\n");
                    Sleep(1000);
                    continue;
                }
                else if (i == 2)
                {
                    cursor(26, xy += 2);
                    printf("ѧ���޳ɼ�\n");
                    Sleep(1000);
                    continue;
                }
                struct Student* Stu = search_Student(&head_Major, studentID);
                float add_GPA = Stu->add_GPA;
                float FinalGPA = finalGPA(head_Major, studentID, add_GPA);
                int result = Grade_ranking(head_Major, studentID, add_GPA, FinalGPA);
                float a;
                a = calculate_allmyscore(head_Major, head_SubInfor, studentID);
                xy = 0;
                //cursor(26, xy += 2);
                cursor(26, 19);
                printf("�����ѧ��Ϊ: %.1f \t", a);
                float b;
                b = calculate_myscore(head_Major, head_SubInfor, studentID);
                //cursor(26, xy += 2);
                cursor(26, 20);
                printf("����GPAѧ��Ϊ: %.1f \t", b);
                float c;
                c = calculate_GPA(head_Major, studentID, head_SubInfor);
                //cursor(26, xy += 2);
                cursor(26, 21);
                printf("GPA: %.5f \t", c);
                ;
                //cursor(26, xy += 2);
                cursor(26, 22);
                printf("���ʼӷ�GPA: %.2f \t", add_GPA);
                //cursor(26, xy += 2);
                cursor(26, 23);
                printf("����GPA: %.5f \t", c + add_GPA);
                //cursor(26, xy += 2);
                cursor(26, 24);
                printf("����/�꼶������%d/%d \n", result, calculate_GradeStudentNum(head_Major, teaMajor, teaGrade));
                cursor(26, 25);
                system("pause");
                //cursor(26, xy += 4);
                cursor(26, 25);
                Display_Single_BonusNote(Head_Bonus, studentID);// 18 ��ӡ һ���� ���еļӷ���Ŀ
                continue;
            } while (cursor(30, 26), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        }
        case 5: {
            int xy = 6;
            system("cls");
            system("color F0");
            HideCursor();
            // �鿴�꼶�ɼ�
            display_Grade(head_Major, teaMajor, teaGrade);
            cursor(26, 30);
            printf("\n�꼶��������%d \t\t", calculate_GradeStudentNum(head_Major, teaMajor, teaGrade));
            cursor(26, 32);
            printf("�꼶ƽ�����㣺%f\n", calculate_GradeAverageGPA(head_Major, teaMajor, teaGrade));
            system("pause");
            break;


        }
        case 6: {
            return;
        }
        default:
            cursor(26, xy += 2);
            printf("��Ч��ѡ����������롣\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}


//����Ա�˵�����������Ա��Ϣ����ѧ����Ϣ�����γ���Ϣ�����ɼ�����
void Menu_Admin()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("�ѽ���ɼ�ϵͳ����˵���\n\n");
        cursor(26, 8);
        printf("1. ����Ա��Ϣ����");
        cursor(26, 10);
        printf("2. ѧ����Ϣ����");
        cursor(26, 12);
        printf("3. �γ���Ϣ����");
        cursor(26, 14);
        printf("4. ѧ���ɼ������");
        cursor(26, 16);
        printf("5. �˳�");
        cursor(26, 18);
        printf("����������ѡ��");
        choice = Input_1toNum(5);
        switch (choice) {
        case 1:
            Menu_adminTeacher();
            break;
        case 2:
            Menu_adminStdInfor();
            break;
        case 3:
            Menu_SubInfor();
            break;
        case 4:
            Menu_adminStdGrade();
            break;
        case 5:
            return;
        default:
            cursor(26, 20);
            printf("��Ч��ѡ����������롣\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//����Ա��Ϣ����˵�
void Menu_adminTeacher()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("�ѽ��븨��Ա��Ϣ����˵���\n\n");
        cursor(26, 8);
        printf("1. ��Ӹ���Ա");
        cursor(26, 10);
        printf("2. �޸ĸ���Ա��Ϣ");
        cursor(26, 12);
        printf("3. ɾ������Ա");
        cursor(26, 14);
        printf("4. ��ʾ����Ա��Ϣ");
        cursor(26, 16);
        printf("5. �˳�");
        cursor(26, 18);
        printf("����������ѡ��");
        choice = Input_1toNum(5);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("�����븨��Ա���ţ�");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) != NULL)
                {
                    cursor(26, 8);
                    printf("�ù����Ѵ��ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ����ӣ���Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                add_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("��ӳɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("�����븨��Ա���ţ�");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("�ù��Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ���޸ģ���Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                modify_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("�޸ĳɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("�����븨��Ա���ţ�");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("�ù��Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ��ɾ������Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                delete_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("ɾ���ɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            print_AllTeachers(head_TeaInfor);
            system("pause");
            break;
        case 5:
            return;
        default:
            cursor(26, 20);
            printf("��Ч��ѡ����������롣\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//ѧ����Ϣ����˵�
void Menu_adminStdInfor()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("�ѽ���ѧ����Ϣ����˵���\n\n");
        cursor(26, 8);
        printf("1. ���ѧ��");
        cursor(26, 10);
        printf("2. �޸�ѧ����Ϣ");
        cursor(26, 12);
        printf("3. ɾ��ѧ��");
        cursor(26, 14);
        printf("4. ��ʾѧ����Ϣ");
        cursor(26, 16);
        printf("5. �˳�");
        cursor(26, 18);
        printf("����������ѡ��");
        choice = Input_1toNum(5);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ��ѧ�ţ�");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) != NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ���Ѵ��ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ����ӣ���Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                add_StdInfor(head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("��ӳɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ��ѧ�ţ�");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ���޸ģ���Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                modify_StdInfor(head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("�޸ĳɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ��ѧ�ţ�");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ��ɾ������Y/N����"), toupper(Input_YN()) == 'N') {
                    break;
                }
                delete_StuInfor(&head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("ɾ���ɹ���\n");
                Sleep(1000);
                break;
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            printAll_StdInfor(head_StdInfor, head_Major);
            system("pause");
            break;
        case 5:
            return;
        default:
            cursor(26, 20);
            printf("��Ч��ѡ����������롣\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//ѧ���ɼ��˵�
void Menu_adminStdGrade() {
    int choice;
    int majorNum;
    int gradeNum;
    int studentID;
    char courseName[20];
    float score;
    char semester[5];
    int isExempted;
    int isFailed;
    float newScore;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 3);
        printf("�ѽ���ɼ������˵���");
        cursor(26, 5);
        printf("1. ���רҵ");
        cursor(26, 7);
        printf("2. ɾ��רҵ");
        cursor(26, 9);
        printf("3. ����꼶");
        cursor(26, 11);
        printf("4. ɾ���꼶");
        cursor(26, 13);
        printf("5. ���ѧ��");
        cursor(26, 15);
        printf("6. ���ѧ���ɼ�");
        cursor(26, 17);
        printf("7. �޸�ѧ���ɼ�");
        cursor(26, 19);
        printf("8. ɾ��ѧ���ɼ�");
        cursor(26, 21);
        printf("9. ɾ��ѧ��");
        cursor(26, 23);
        printf("10. ��ʾ����ѧ�������гɼ�");
        cursor(26, 25);
        printf("11. ��ʾָ��רҵ���꼶������ѧ���ɼ�");
        cursor(26, 27);
        printf("12. �˳�");
        cursor(26, 29);
        printf("����������ѡ��");
        choice = Input_intNumber(2);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) != NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�Ѵ��ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ����ӣ���Y/N����"), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Major(&head_Major, majorNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 10);
                printf("��ӳɹ���\n");
                Sleep(1000);
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("�Ƿ�ȷ��ɾ������Y/N����"), toupper(Input_YN()) == 'N') {
                    continue;
                }
                delete_Major(&head_Major, majorNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 10);
                printf("ɾ���ɹ���\n");
                Sleep(1000);
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("�������꼶��");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("���꼶�Ѵ��ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                if (printf("�Ƿ�ȷ����ӣ���Y/N����"), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Grade(search_Major(head_Major, majorNum), gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 12);
                printf("��ӳɹ���\n");
                Sleep(1000);
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("�������꼶��");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("���꼶�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                if (printf("�Ƿ�ȷ��ɾ������Y/N����"), toupper(Input_YN()) == 'N') {
                    continue;
                }
                delete_Grade(&head_Major, majorNum, gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 12);
                printf("ɾ���ɹ���\n");
                Sleep(1000);
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 5:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("�������꼶��");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("���꼶�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) != NULL)
                {
                    cursor(26, 12);
                    printf("��ѧ���Ѵ��ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 12);
                if (printf("�Ƿ�ȷ����ӣ���Y/N����"), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Student(&head_Major, studentID, majorNum, gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 14);
                printf("��ӳɹ���\n");
                Sleep(1000);
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 6:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("������γ̱�ţ�");
                scanf("%s", courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                printf("������ɼ���");
                scanf("%f", &score);
                printf("�������޶�ѧ�ڣ�");
                scanf("%s", semester);
                printf("�������Ƿ����ޣ�0��ʾ��1��ʾ�ǣ���");
                scanf("%d", &isExempted);
                printf("�������Ƿ�ҿƣ�0��ʾ��1��ʾ�ǣ���");
                scanf("%d", &isFailed);
                if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == 1) {
                    cursor(26, 10);
                    printf("��ӳɹ���\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -1) {
                    cursor(26, 10);
                    printf("ѧ�������ڣ����ʧ�ܡ�\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isFailed) == -2) {
                    cursor(26, 10);
                    printf("�γ̱���ظ������ʧ�ܡ�\n");
                }
                else {
                    cursor(26, 10);
                    printf("���ʧ�ܡ�\n");
                    Sleep(1000);
                }
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 7:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("������γ̱�ţ�");
                scanf("%s", courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                printf("�������µĳɼ���");
                scanf("%f", &newScore);
                if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                    cursor(26, 10);
                    printf("�޸ĳɹ���\n");
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                    cursor(26, 10);
                    printf("ѧ�������ڣ��޸�ʧ�ܡ�\n");
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                    cursor(26, 10);
                    printf("�γ̱�Ų����ڣ��޸�ʧ�ܡ�\n");
                }
                else {
                    cursor(26, 10);
                    printf("�޸�ʧ�ܡ�\n");
                    Sleep(1000);
                }
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 8:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("������γ̱�ţ�");
                scanf("%s", courseName);
                //�жϿγ̱���Ƿ��ڿγ���Ϣ��
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("�γ̱�Ų����ڣ����ʧ�ܡ�\n");
                    Sleep(1000);
                    continue;
                }
                if (delete_Score(&head_Major, studentID, courseName) == 1) {
                    cursor(26, 10);
                    printf("ɾ���ɹ���\n");
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                    cursor(26, 10);
                    printf("ѧ�������ڣ�ɾ��ʧ�ܡ�\n");
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                    cursor(26, 10);
                    printf("�γ̱�Ų����ڣ�ɾ��ʧ�ܡ�\n");
                }
                else {
                    cursor(26, 10);
                    printf("ɾ��ʧ�ܡ�\n");
                    Sleep(1000);
                }
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 9:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (delete_Student(&head_Major, studentID) == 1) {
                    cursor(26, 8);
                    printf("ɾ���ɹ���\n");
                }
                else {
                    cursor(26, 8);
                    printf("ɾ��ʧ�ܡ�\n");
                    Sleep(1000);
                }
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 10:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������ѧ�ţ�");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("��ѧ�Ų����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                int i = query_Scores(&head_Major, studentID);
                system("pause");
                if (i == 1) {
                    printf("ѧ��������\n");
                    continue;
                }
                else if (i == 2)
                {
                    printf("ѧ���޳ɼ�\n");
                    continue;
                }
                else {
                    struct Student* Stu = search_Student(&head_Major, studentID);
                    float add_GPA = Stu->add_GPA;
                    float FinalGPA = finalGPA(head_Major, studentID, add_GPA);
                    int result = Grade_ranking(head_Major, studentID, add_GPA, FinalGPA);
                    float a;
                    a = calculate_allmyscore(head_Major, head_SubInfor, studentID);
                    cursor(26, 28);
                    printf("\n�����ѧ��Ϊ: %.1f \t", a);
                    float b;
                    b = calculate_myscore(head_Major, head_SubInfor, studentID);
                    cursor(26, 29);
                    printf("����GPAѧ��Ϊ: %.1f \t", b);
                    float c;
                    c = calculate_GPA(head_Major, studentID, head_SubInfor);
                    cursor(26, 30);
                    printf("GPA: %.5f \t", c);
                    cursor(26, 31);
                    printf("���ʼӷ�GPA: %.2f \t", add_GPA);
                    cursor(26, 32);
                    printf("����GPA: %.5f \t", c + add_GPA);
                    cursor(26, 33);
                    system("pause");
                    Display_Single_BonusNote(Head_Bonus, studentID);// 18 ��ӡ һ���� ���еļӷ���Ŀ
                    system("pause");
                }
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 11:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("������רҵ��ţ�");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("��רҵ�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("�������꼶��");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("���꼶�����ڣ����������롣\n");
                    Sleep(1000);
                    continue;
                }
                display_Grade(head_Major, majorNum, gradeNum);
                system("pause");
            } while (cursor(26, 25), printf("�Ƿ��������Y/N����"), toupper(Input_YN()) == 'Y');
            break;
        case 12:
            return;
        default:
            cursor(26, 34);
            printf("��Ч��ѡ����������롣\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//��Ŀ�б�˵�
void Menu_SubInfor() {
    system("cls");
    system("color F0");
    HideCursor();
    cursor(26, 6);
    printf("�ѽ����Ŀ�б����˵���");
    int choice;
    while (1) {
        cursor(26, 7);
        printf("1. ����/�޸Ŀ�Ŀ");
        cursor(26, 8);
        printf("2. ��ʾ��Ŀ�б�");
        cursor(26, 9);
        printf("3. ���浽�ļ�");
        cursor(26, 10);
        printf("4. ���ļ�����");
        cursor(26, 11);
        printf("5. ɾ����Ŀ");
        cursor(26, 12);
        printf("6. �˳�");
        cursor(26, 13);
        printf("������ѡ�");
        //scanf("%d", &choice);
        choice = Input_1toNum(6);
        system("cls");
        switch (choice) {
        case 1: {
            struct SubInfor* newNode = create_SubInfor();
            if (checkAndReplace_SubInfor(&head_SubInfor, newNode)) {
                cursor(26, 7);
                printf("��Ŀ�Ѵ��ڣ��Ƿ񸲸ǣ���Y/N����");
                char answer = Input_YN();
                if (toupper(answer) == 'Y') {
                    delete_SubInfor(&head_SubInfor, newNode->SubInforNum);
                    insert_SubInfor(&head_SubInfor, newNode);
                    cursor(26, 8);
                    printf("��Ŀ�Ѹ��ǡ�\n");
                }
                else {
                    cursor(26, 8);
                    free(newNode);
                    printf("��Ŀδ���뵽�б��С�\n");
                }
            }
            else {
                cursor(26, 7);
                insert_SubInfor(&head_SubInfor, newNode);
                printf("��Ŀ�Ѳ��뵽�б��С�\n");
            }
            break;
        }
        case 2:
            system("cls");
            display_SubInfor(head_SubInfor);
            break;
        case 3:
            saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
            cursor(26, 7);
            printf("��Ŀ��Ϣ�ѱ��浽�ļ���\n");
            break;
        case 4:
            loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
            cursor(26, 7);
            printf("�Ѵ��ļ����ؿ�Ŀ��Ϣ��\n");
            break;
        case 5: {
            char subNum[MAX_NUM_LENGTH];
            cursor(26, 7);
            printf("������Ҫɾ���Ŀ�Ŀ��ţ�");
            scanf("%s", subNum);
            delete_SubInfor(&head_SubInfor, subNum);
            break;
        }
        case 6:
            cursor(26, 7);
            printf("�������˳���\n");
            return;
        default:
            printf("��Ч��ѡ����������롣\n");
            break;
        }
        printf("\n");
    }
}
