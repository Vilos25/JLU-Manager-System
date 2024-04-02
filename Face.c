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

// 学生申请素质类加分入口
void Menu_Stu_bonus(BonusNote* Head, int ID);
// 教师审核所有未审核的素质类加分
void Tea_Audit(BonusNote* Head, int TeaID);
// 36 学生自己选择删除部分加分项目
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
            PrintExit();//退出
            return 0;
        }

    }
    return 0;
}
//学生菜单
void Menu_student(int ID)
{
    int choice;
    if (search_StdInfor(head_StdInfor, ID) == NULL)
    {
        add_StdInfor(head_StdInfor, ID);
        printf("你还未填写个人信息，请填写个人信息\n");
        Sleep(1000);
        // 给定学生学号，增加学生信息
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
        printf("1. 修改个人信息");
        cursor(26, 12);
        //cursor(26, 8);
        printf("2. 查询个人成绩表&年级排名");
        //cursor(26, 10);
        cursor(26, 14);
        printf("3. 管理我的素质加分");
        cursor(26, 16);
        printf("4. 退出");
        cursor(26, 18);
        printf("请输入选项：");
        cursor(26, 20);

        choice = Input_1toNum(4);
        switch (choice) {
        case 1: {
            system("cls");
            system("color F0");
            HideCursor();
            // 给定学生学号，增加学生信息
            modify_StdInfor(head_StdInfor, ID);
            system("pause");
            break;
        }
        case 2: {
            system("cls");
            int studentID = ID;
            //给一个学号，查找该名学生所在的年级节点
            struct Grade* gradeNum = search_GradeByStudentID(&head_Major, studentID);

            //给一个学号，查找该名学生所在的专业节点
            struct Major* majorNum = search_MajorByStudentID(head_Major, studentID);

            int i = query_Scores(&head_Major, studentID);
            if (i == 1) {
                printf("学生不存在\n");
            }
            else if (i == 2)
            {
                printf("学生无成绩\n");
            }
            struct Student* Stu = search_Student(&head_Major, studentID);
            float add_GPA = Stu->add_GPA;
            float FinalGPA = finalGPA(head_Major, studentID, add_GPA);
            int result = Grade_ranking(head_Major, studentID, add_GPA, FinalGPA);
            float a;
            a = calculate_allmyscore(head_Major, head_SubInfor, studentID);
            printf("\n获得总学分为: %.1f \t", a);
            float b;
            b = calculate_myscore(head_Major, head_SubInfor, studentID);
            printf("计入GPA学分为: %.1f \t", b);
            float c;
            c = calculate_GPA(head_Major, studentID, head_SubInfor);
            printf("基础GPA: %.5f \t", c);
            printf("素质类加分GPA: %.2f \t", add_GPA);
            printf("最终GPA: %.5f \n", c + add_GPA);
            printf("排名/年级人数：%d/%d \t", result, calculate_GradeStudentNum(head_Major, majorNum->majorNum, gradeNum->gradeNum));
            //年级前百分之几
            printf("年级前%.2f%%\n", (float)result / calculate_GradeStudentNum(head_Major, majorNum->majorNum, gradeNum->gradeNum) * 100);
            system("pause");
            break;

        }
              void Print_Single_Comp(CompNote * Head);// 19 打印 一个人 所有的比赛项目 (从人的角度打印）
              void Print_Single_Paper(PaperNote * Head);// 20 打印 一个人 所有的论文项目
              void Print_Single_Proj(ProjNote * Head);// 21 打印 一个人 所有的结题项目

              void Display_All_CompNote(BonusNote * Head);// 22 打印 比赛项目 的所有加分内容 （从三大类项目的角度打印）
              void Display_All_PaperNote(BonusNote * Head);// 23 打印 论文项目 的所有加分内容
              void Display_All_ProjNote(BonusNote * Head);// 24 打印 结题项目 的所有加分内容

              void Display_All_BonusInform(BonusNote * Head);// 25 打印 所有素质类加分信息
        case 3:
            //素质管理菜单
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
                printf("1. 申请素质类加分\n");
                cursor(26, xy += 2);
                printf("2. 查看个人加分记录\n");
                cursor(26, xy += 2);
                printf("3. 撤销部分个人素质类加分项\n");//////////////////////////////            改了这          ///////////////////////////////////////////////////////////////////////////////////////////////////////
                cursor(26, xy += 2);
                printf("4. 退出\n");
                cursor(26, xy += 2);
                printf("请输入选项：");
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
                            printf("未找到该学生的加分信息！\n");
                            Sleep(1000);
                            break;
                        }
                        cursor(26, xy);
                        printf("1. 查看所有加分记录\n");
                        cursor(26, xy += 2);
                        printf("2. 查看比赛项目记录\n");
                        cursor(26, xy += 2);
                        printf("3. 查看论文项目记录\n");
                        cursor(26, xy += 2);
                        printf("4. 查看大创结题项目记录\n");
                        cursor(26, xy += 2);
                        printf("5. 退出\n");
                        cursor(26, xy += 2);
                        printf("请输入选项：");
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
                            printf("无效的选项，请重新输入。\n");
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
                    Delet_Bonus(Head_Bonus, ID); //////////////////////////////            改了这          ///////////////////////////////////////////////////////////////////////////////////////////////////////
                    break;
                case 4:
                    return;
                default:
                    printf("无效的选项，请重新输入。\n");
                    break;
                }
                printf("\n");
            }
        case 4:
            return;
        default:
            printf("无效的选项，请重新输入。\n");
            break;
        }
        printf("\n");
    }
}
// 学生申请素质类加分入口
void Menu_Stu_bonus(BonusNote* Head, int ID)
{
    do{
        system("cls");
        system("color F0");
        HideCursor();
        char Acc[8] = { 0 };
        Int_To_Str(ID, Acc);//将ID转成字符串
        int Choice = 0;
        int xy = 6;
        cursor(26, xy);
        printf("1.申请比赛项目加分\n");
        cursor(26, xy+=2);
        printf("2.申请论文项目加分\n");
        cursor(26, xy += 2);
        printf("3.申请国家级优秀结题项目加分\n");
        cursor(26, xy += 2);
        printf("4.退出\n");
        cursor(26, xy += 2);
        printf("请输入你的选择：");
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
    } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
    return;
}

/**************************************************************************************************************************/

// 36 学生自己选择删除部分加分项目
void Delet_Bonus(BonusNote* Head, int stu_ID) {
    char Acc[20] = { 0 };
    Int_To_Str(stu_ID, Acc);
    BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
    while (strcmp(pcurrent->Accountnum,Acc)!=0) {//找到这个学生的学生节点
        if (pcurrent->Next == NULL)
        {
            printf("未找到该学生的加分信息！\n");
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
        //printf("学号\t姓名\t竞赛项目名称\t获奖人和顺序\t竞赛类型\t获奖等级\t主办单位\t获奖时间\t审核状态\t应加绩点\n");
        //printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t竞赛项目名称: \t%s\n", pcurrent2->CompName);
        printf("\t\t\t获奖人/顺序: \t%s\n", pcurrent2->Winers);
        printf("\t\t\t竞赛类型: \t%c\n", pcurrent2->ABC);
        printf("\t\t\t获奖等级: \t%d\n", pcurrent2->AwardGrade);
        printf("\t\t\t主办单位: \n%s\n", pcurrent2->Sponsor);
        printf("\t\t\t获奖时间: \t%s\n", pcurrent2->Time);
        //printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
        if (pcurrent2->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
        else if (pcurrent2->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
        else { printf("\t\t\t审核状态: \t否决\n"); }
        printf("\t\t\t应加绩点: \t%.2f\n", pcurrent2->Ponit);
        printf("\n");
        printf("\t\t\t是否删除该项目：\n");
        printf("\t\t\t1：删除\n");
        printf("\t\t\t2：保留\n");
        printf("\t\t\t3：退出\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent2 != pcurrent->Comphead && a) {//通过a只运行一遍
            pprev2 = pcurrent->Comphead;
            while (pprev2->Next != pcurrent2) {//如果现在 pcurrent2 不是 比赛头结点，那么找到 pcurrent2 的上一个节点 pprev2
                pprev2 = pprev2->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent2 = pcurrent->Comphead) //如果现在 pcurrent2 是 比赛头节点，那么下一个节点做头，原来的头释放
            {
                CompNote* pprev = pcurrent2;
                pcurrent->Comphead = pcurrent2->Next;
                pcurrent2 = pcurrent2->Next;
                free(pprev);
            }
            else                  //如果现在 pcurrent2 不是 比赛头结点，那么直接通过 pprev2 删掉pcurrent2
            {
                pprev2->Next = pcurrent2->Next;
                free(pcurrent2);
                pcurrent2 = pprev2->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            printf("\n\t\t\t删除成功！\n\n");
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
        //printf("学号\t姓名\t论文名称\t所有作者和顺序\t期刊名称/会议名称\t发表时间\t卷/期\t论文号\t页码范围\t审核状态\t应加绩点\n");
        //printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
        
        printf("\t\t\t学号：\t%s\n", pcurrent->Accountnum);
        printf("\t\t\t姓名：\t%s\n", pcurrent->Name);
        printf("\t\t\t论文名称：\t%s\n", pcurrent3->PaperName);
        printf("\t\t\t所有作者/顺序：\t%s\n", pcurrent3->Writers);
        printf("\t\t\t期刊名称/会议名称：\t%s\n", pcurrent3->Journal_Conference);
        printf("\t\t\t发表时间：\t%s\n", pcurrent3->Time);
        printf("\t\t\t卷/期：\t%s\t%s\t%s\n", pcurrent3->Volume_Page[0]);
        printf("\t\t\t论文号: \t%s\n", pcurrent3->Volume_Page[1]);
        printf("\t\t\t页码范围: \t%s\n", pcurrent3->Volume_Page[2]);
        //printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
        if (pcurrent3->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
        else if (pcurrent3->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
        else { printf("\t\t\t审核状态: \t否决\n"); }
        printf("\t\t\t应加绩点: \t%.2f\n", pcurrent3->Ponit);
        printf("\n");
        
        printf("\t\t\t是否删除该项目：\n");
        printf("\t\t\t1：删除\n");
        printf("\t\t\t2：保留\n");
        printf("\t\t\t3：退出\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent3 != pcurrent->Paperhead && a) {//通过a只运行一遍
            pprev3 = pcurrent->Paperhead;
            while (pprev3->Next != pcurrent3) {//如果现在 pcurrent3 不是 比赛头结点，那么找到 pcurrent3 的上一个节点 pprev3
                pprev3 = pprev3->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent3 = pcurrent->Paperhead) //如果现在 pcurrent3 是 比赛头节点，那么下一个节点做头，原来的头释放
            {
                CompNote* pprev = pcurrent3;
                pcurrent->Paperhead = pcurrent3->Next;
                pcurrent3 = pcurrent3->Next;
                free(pprev);
            }
            else                  //如果现在 pcurrent3 不是 比赛头结点，那么直接通过 pprev3 删掉pcurrent3
            {
                pprev3->Next = pcurrent3->Next;
                free(pcurrent3);
                pcurrent3 = pprev3->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            printf("\n\t\t\t删除成功！\n\n");
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
        //printf("同类序号\t项目名称\t所有成员和顺序\t指导教师姓名\t获奖等级\t立项时间\t结项时间\t项目编号\t责任性质\t审核状态\t应加绩点\n");
        //printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("\t\t\t学号：\t%s\n", pcurrent->Accountnum);
        printf("\t\t\t姓名：\t%s\n", pcurrent->Name);
        printf("\t\t\t项目名称: \t%s\n", pcurrent4->ProjName);
        printf("\t\t\t所有成员和顺序: \t%s\n", pcurrent4->Members);
        printf("\t\t\t指导教师姓名: \t%s\n", pcurrent4->Advisor);
        printf("\t\t\t立项时间: \t%s\n", pcurrent4->Start_time);
        printf("\t\t\t结项时间: \t%s\n", pcurrent4->Finish_time);
        printf("\t\t\t项目编号: \t%s\n", pcurrent4->ProjNum);
        //printf("\t\t\t责任性质: \t%d\n", pcurrent->Role);
        if (pcurrent4->Role == 1) { printf("\t\t\t责任性质: \t负责人\n"); }
        else if (pcurrent4->Role == 2) { printf("\t\t\t责任性质: \t成员\n"); }
        else { printf("\t\t\t责任性质: \t其他\n"); }
        //printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
        if (pcurrent4->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
        else if (pcurrent4->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
        else { printf("\t\t\t审核状态: \t否决\n"); }
        printf("\t\t\t应加绩点: \t%.2f\n", pcurrent4->Ponit);
        printf("\n");

        printf("\t\t\t是否删除该项目：\n");
        printf("\t\t\t1：删除\n");
        printf("\t\t\t2：保留\n");
        printf("\t\t\t3：退出\n");
        int choice = Input_1toNum(3);

        int a = 1;
        if (pcurrent4 != pcurrent->Projhead && a) {//通过a只运行一遍
            pprev4 = pcurrent->Projhead;
            while (pprev4->Next != pcurrent4) {//如果现在 pcurrent4 不是 比赛头结点，那么找到 pcurrent4 的上一个节点 pprev4
                pprev4 = pprev4->Next;
            }
            a = 0;
        }
        switch (choice) {
        case 1:
            if (pcurrent4 = pcurrent->Projhead) //如果现在 pcurrent4 是 比赛头节点，那么下一个节点做头，原来的头释放
            {
                CompNote* pprev = pcurrent4;
                pcurrent->Projhead = pcurrent4->Next;
                pcurrent4 = pcurrent4->Next;
                free(pprev);
            }
            else                  //如果现在 pcurrent4 不是 比赛头结点，那么直接通过 pprev4 删掉pcurrent4
            {
                pprev4->Next = pcurrent4->Next;
                free(pcurrent4);
                pcurrent4 = pprev4->Next;
            }
            pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            printf("\n\t\t删除成功！\n\n");
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
    printf("\n\t\t选择删除结束！\n\n");
}
/**************************************************************************************************************************/


//辅导员菜单
void Menu_teacher(int ID)
{
    if (search_TeacherByID(head_TeaInfor, ID) == NULL)
    {
        system("cls");
        cursor(26, 6);
        printf("您还未填写个人信息，请填写个人信息\n");
        Sleep(1000);
        add_Teacher(head_TeaInfor, ID);
        // 给定学生学号，增加学生信息
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
        printf("1. 修改个人信息");
        cursor(26, xy+=2);
        printf("2. 管理学生成绩");
        cursor(26, xy += 2);
        printf("3. 管理学生素质加分申请");
        cursor(26, xy += 2);
        printf("4. 退出");
        cursor(26, xy += 2);
        printf("请输入选项：");
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
            printf("无效的选项，请重新输入。\n");
            break;
        }
        printf("\n");
    }
}

void Tea_Audit(BonusNote* Head, int TeaID)// 37 教师审核所有未审核的素质类加分
{
    int tag = 0;
    BonusNote* pcurrent = Head->Next;
    TeaInfor* Tea = search_TeacherByID(head_TeaInfor, TeaID);
    while (pcurrent != NULL) {//////////////////////////////////////////////////////////////////////////////////////////////
        /*教师和学生专业匹配的条件*/
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
                //printf("学号\t姓名\t竞赛项目名称\t获奖人和顺序\t竞赛类型\t获奖等级\t主办单位\t获奖时间\t审核状态\t应加绩点\n");
                //printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("\t\t\t学号: %s\n", pcurrent->Accountnum);
                printf("\t\t\t姓名: %s\n", pcurrent->Name);
                printf("\t\t\t竞赛项目名称: %s\n", pcurrent2->CompName);
                printf("\t\t\t获奖人/顺序: %s\n", pcurrent2->Winers);
                printf("\t\t\t竞赛类型: %c\n", pcurrent2->ABC);
                printf("\t\t\t获奖等级: %d\n", pcurrent2->AwardGrade);
                printf("\t\t\t主办单位: %s\n", pcurrent2->Sponsor);
                printf("\t\t\t获奖时间: %s\n", pcurrent2->Time);
                printf("\t\t\t应加绩点: %.2f\n", pcurrent2->Ponit);

                printf("\n\t\t\t请选择该项目是否审核通过：\n");
                printf("\t\t\t1：批准\n");
                printf("\t\t\t2：审核中\n");
                printf("\t\t\t3：否决\n");
                printf("\t\t\t你的选择：");
                pcurrent2->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            }
            pcurrent2 = pcurrent2->Next;
        }

        while (pcurrent3 != NULL) {
            if (pcurrent3->Attribute == 2)
            {
                //printf("_____________________________________________________________________________________________________________________________________________________\n");
                //printf("学号\t姓名\t论文名称\t所有作者和顺序\t期刊名称/会议名称\t发表时间\t卷/期\t论文号\t页码范围\t审核状态\t应加绩点\n");
                //printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
                
                printf("\t\t\t学号: %s\n", pcurrent->Accountnum);
                printf("\t\t\t姓名: %s\n", pcurrent->Name);
                printf("\t\t\t论文名称: %s\n", pcurrent3->PaperName);
                printf("\t\t\t所有作者/顺序: %s\n", pcurrent3->Writers);
                printf("\t\t\t期刊名称/会议名称: %s\n", pcurrent3->Journal_Conference);
                printf("\t\t\t发表时间: %s\n", pcurrent3->Time);
                printf("\t\t\t卷/期: %s\n", pcurrent3->Volume_Page[0]);
                printf("\t\t\t论文号: %s\n", pcurrent3->Volume_Page[1]);
                printf("\t\t\t页码范围: %s\n", pcurrent3->Volume_Page[2]);
                printf("\t\t\t应加绩点: %.2f\n", pcurrent3->Ponit);
                printf("\n\t\t\t请选择该项目是否审核通过：\n");
                printf("\t\t\t1：批准\n");
                printf("\t\t\t2：审核中\n");
                printf("\t\t\t3：否决\n");
                printf("\t\t\t你的选择：");
                pcurrent3->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            }
            pcurrent3 = pcurrent3->Next;
        }

        while (pcurrent4 != NULL) {
            if (pcurrent4->Attribute == 2)
            {
                //printf("____________________________________________________________________________________________________________________________________________________________________\n");
                //printf("同类序号\t项目名称\t所有成员和顺序\t指导教师姓名\t获奖等级\t立项时间\t结项时间\t项目编号\t责任性质\t审核状态\t应加绩点\n");
                //printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                
                printf("\t\t\t学号: %s\n", pcurrent->Accountnum);
                printf("\t\t\t姓名: %s\n", pcurrent->Name);
                printf("\t\t\t项目名称: %s\n", pcurrent4->ProjName);
                printf("\t\t\t所有成员/顺序: %s\n", pcurrent4->Members);
                printf("\t\t\t指导教师姓名: %s\n", pcurrent4->Advisor);
                printf("\t\t\t获奖等级: %d\n", pcurrent4->Attribute);
                printf("\t\t\t立项时间: %s\n", pcurrent4->Start_time);
                printf("\t\t\t结项时间: %s\n", pcurrent4->Finish_time);
                printf("\t\t\t项目编号: %s\n", pcurrent4->ProjNum);
                printf("\t\t\t责任性质: %d\n", pcurrent4->Role);
                printf("\t\t\t应加绩点: %.2f\n", pcurrent4->Ponit);
                printf("\n\t\t\t请选择该项目是否审核通过：\n");
                printf("\t\t\t1：批准\n");
                printf("\t\t\t2：审核中\n");
                printf("\t\t\t3：否决\n");
                printf("\t\t\t你的选择：");
                pcurrent4->Attribute = Input_1toNum(3);
                pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//重算该学生加分绩点
            }
            pcurrent4 = pcurrent4->Next;
        }
        struct Student* Stu = search_Student(&head_Major, stu_ID);
        Stu->add_GPA = pcurrent->Bonusponit;

        pcurrent = pcurrent->Next;
    }
    if(tag==0)
        printf("\n\n\t\t\t当前无待审核项目\n");
    system("pause");
}

//首次文件载入
void First_Load() {
    //加载成绩信息
    loadFrom_StdGrade(&head_Major, FILENAME_GRA);
    //加载课程信息
    loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
    //加载学生信息
    loadFrom_StdInfor(&head_StdInfor, FILENAME_STD);
    //加载辅导员信息
    loadFrom_TeaInfor(&head_TeaInfor, FILENAME_TEA);
    //计算链表中所有学生的GPA
    calculate_AllGPA(head_Major, head_SubInfor);
    //加载素质加分系统
    Head_Bonus = Start_Logging_bonusFile();
}

//结束时自动保存
void End_Save()
{
    saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
    //调用加载函数并判断是否加载成功
    saveTo_StdGrade(&head_Major, FILENAME_GRA);
    //计算链表中所有学生的GPA
    calculate_AllGPA(head_Major, head_SubInfor);
    //加载学生信息
    saveTo_StdInfor(head_StdInfor, FILENAME_STD);
    // 保存辅导员信息
    saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
    // 保存素质加分系统
    Save_List_To_bonusFile(Head_Bonus);
}
void Menu_StdGrade(int ID) {
    int choice;
    int majorNum;
    int gradeNum;
    int studentID;
    char courseName[20];
    float score;
    char semester[20];
    int isExempted;
    int isval;
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
            printf("您不是辅导员，无法进入成绩管理菜单\n");
            return;
        }
        num = 0;
        xy = 6;
        cursor(26, xy);
        printf("请选择你要管理的专业：\n");
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
        printf("请输入选项：");
        int majorNum = Input_1toNum(num);
        teaMajor = majorNum + TeaM * 100 - 1;
        if (search_Major(head_Major, teaMajor) == NULL)
        {
            cursor(26, xy += 3);
            printf("专业不存在，请重新输入\n");
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
        printf("选择你要管理的年级:");
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
        printf("正在管理：\t专业：%s—", All_Aca[i]);
        printf("%s\t", ALL_Prof[i][j]);
        printf("年级: %d级\n", teaGrade);
        int xy = 3;
        cursor(26, xy+=2);
        printf(" 已进入成绩管理菜单！\n\n");
        cursor(26, xy+=2);
        printf("1. 增加个人成绩");
        cursor(26, xy+=2);
        printf("2. 修改个人成绩");
        cursor(26, xy+=2);
        printf("3. 删除个人成绩");
        cursor(26, xy += 2);
        printf("4. 查看个人成绩");
        cursor(26, xy += 2);
        printf("5. 查看年级成绩");
        cursor(26, xy += 2);
        printf("6. 返回上级菜单");
        cursor(26, xy += 2);
        printf("请输入选项：");
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
                printf("\n\t正在管理：专业：%s—", All_Aca[i]);
                printf("%s\t", ALL_Prof[i][j]);
                printf("\t年级: %d级\n", teaGrade);

                cursor(26, xy += 2);
                printf("请输入学号：");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("学生不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("你不是这个学生的辅导员，无法添加成绩\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("请输入课程编号：");
                Input_SubNum(courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
				{
					cursor(26, xy += 2);
					printf("课程编号不存在，添加失败。\n");
					Sleep(1000);
					continue;
				}
                cursor(26, xy += 2);
                printf("请输入成绩：");
                score = Input_Float(2, 2);
                cursor(26, xy += 2);
                printf("请输入修读学期：");
                Input_SemesterNum(semester);
                cursor(26, xy += 2);
                printf("请输入是否免修（1表示否，2表示是）：");
                isExempted = Input_1toNum(2) - 1;
                cursor(26, xy += 2);
                printf("请输入是否有效（1表示是，2表示否）：");
                isval = Input_1toNum(2) - 1;
                cursor(26, xy += 2);
                if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == 1) {
                    printf("添加成功。\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == -1) {
                    printf("学生不存在，添加失败。\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == -2) {
                    printf("课程编号重复，添加失败。\n");
                }
                else {
                    printf("添加失败。\n");
                    Sleep(1000);
                }
                continue;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        }
        case 2: {
            // 修改个人成绩
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, xy += 2);
                printf("请输入学号：");
                //scanf("%d", &studentID);

                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("学生不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("你不是这个学生的辅导员，无法添加成绩\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("请输入课程编号：");
                //scanf("%s", courseName);
                Input_SubNum(courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("课程编号不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("请输入新的成绩：");
                //scanf("%f", &newScore);
                newScore = Input_Float(2, 2);
                if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                    cursor(26, xy += 2);
                    printf("修改成功。\n");
                    continue;
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                    cursor(26, xy += 2);
                    printf("学生不存在，修改失败。\n");
                    Sleep(1000);
                    continue;
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                    cursor(26, xy += 2);
                    printf("课程编号不存在，修改失败。\n");
                    Sleep(1000);
                    continue;
                }
                else {
                    cursor(26, xy += 2);
                    printf("修改失败。\n");
                    Sleep(1000);
                    continue;
                }
                // break; 
                continue;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;


        }
        case 3: {
            // 删除个人成绩
            do {
                int xy = 6;
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, xy += 2);
                printf("请输入学号：");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("学生不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("你不是这个学生的辅导员，无法添加成绩\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, xy += 2);
                printf("请输入课程编号：");
                //scanf("%s", courseName);
                Input_SubNum(courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("课程编号不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }
                if (delete_Score(&head_Major, studentID, courseName) == 1) {
                    cursor(26, xy += 2);
                    printf("删除成功。\n");
                    Sleep(1000);
                    continue;
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                    cursor(26, xy += 2);
                    printf("学生不存在，删除失败。\n");
                    Sleep(1000);
                    continue;
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                    cursor(26, xy += 2);
                    printf("课程编号不存在，删除失败。\n");
                    Sleep(1000);
                    continue;
                }
                else {
                    cursor(26, xy += 2);
                    printf("删除失败。\n");
                    Sleep(1000);
                    continue;
                }
                //break;
                continue;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
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
                
                printf("请输入学号：");
                //scanf("%d", &studentID);
                studentID = Input_Raw_Integer(8);
                system("cls");
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, xy += 2);
                    printf("学生没有查找到，请检查你的输入。\n");
                    Sleep(1000);
                    continue;
                }

                struct Major* x = search_MajorByStudentID(head_Major, studentID);
                struct Grade* y = search_GradeByStudentID(&head_Major, studentID);
                if (x->majorNum != teaMajor || y->gradeNum != teaGrade)
                {
                    cursor(26, xy += 2);
                    printf("你不是这个学生的辅导员，无法查看成绩\n");
                    Sleep(1000);
                    continue;
                }

                int i = query_Scores(&head_Major, studentID);
                if (i == 1) {
                    cursor(26, xy += 2);
                    printf("学生不存在\n");
                    Sleep(1000);
                    continue;
                }
                else if (i == 2)
                {
                    cursor(26, xy += 2);
                    printf("学生无成绩\n");
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
                //cursor(26, 19);
                printf("\n\t\t\t获得总学分为: %.1f \t", a);
                float b;
                b = calculate_myscore(head_Major, head_SubInfor, studentID);
                //cursor(26, xy += 2);
                //cursor(26, 20);
                printf("\n\t\t\t计入GPA学分为: %.1f \t", b);
                float c;
                c = calculate_GPA(head_Major, studentID, head_SubInfor);
                //cursor(26, xy += 2);
                //cursor(26, 21);
                printf("\n\t\t\tGPA: %.5f \t", c);
                ;
                //cursor(26, xy += 2);
                //cursor(26, 22);
                printf("\n\t\t\t素质加分GPA: %.2f \t", add_GPA);
                //cursor(26, xy += 2);
                //cursor(26, 23);
                printf("\n\t\t\t最终GPA: %.5f \t", c + add_GPA);
                //cursor(26, xy += 2);
                //cursor(26, 24);
                printf("\n\t\t\t排名/年级人数：%d/%d \n\n", result, calculate_GradeStudentNum(head_Major, teaMajor, teaGrade));
                system("pause");
                //cursor(26, xy += 4);
                cursor(26, 25);
                Display_Single_BonusNote(Head_Bonus, studentID);// 18 打印 一个人 所有的加分项目
                continue;
            } while (cursor(30, 40), printf("是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        }
        case 5: {
            int xy = 6;
            system("cls");
            system("color F0");
            HideCursor();
            // 查看年级成绩
            display_Grade(head_Major, teaMajor, teaGrade);
            cursor(26, 30);
            printf("\n年级总人数：%d \t\t", calculate_GradeStudentNum(head_Major, teaMajor, teaGrade));
            cursor(26, 32);
            printf("年级平均绩点：%f\n", calculate_GradeAverageGPA(head_Major, teaMajor, teaGrade));
            system("pause");
            break;


        }
        case 6: {
            return;
        }
        default:
            cursor(26, xy += 2);
            printf("无效的选项，请重新输入。\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}


//管理员菜单，包括辅导员信息管理，学生信息管理，课程信息管理，成绩管理
void Menu_Admin()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("已进入成绩系统管理菜单！\n\n");
        cursor(26, 8);
        printf("1. 辅导员信息管理");
        cursor(26, 10);
        printf("2. 学生信息管理");
        cursor(26, 12);
        printf("3. 课程信息管理");
        cursor(26, 14);
        printf("4. 学生成绩库管理");
        cursor(26, 16);
        printf("5. 退出");
        cursor(26, 18);
        printf("请输入您的选择：");
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
            printf("无效的选项，请重新输入。\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//辅导员信息管理菜单
void Menu_adminTeacher()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("已进入辅导员信息管理菜单！\n\n");
        cursor(26, 8);
        printf("1. 添加辅导员");
        cursor(26, 10);
        printf("2. 修改辅导员信息");
        cursor(26, 12);
        printf("3. 删除辅导员");
        cursor(26, 14);
        printf("4. 显示辅导员信息");
        cursor(26, 16);
        printf("5. 退出");
        cursor(26, 18);
        printf("请输入您的选择：");
        choice = Input_1toNum(5);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入辅导员工号：");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) != NULL)
                {
                    cursor(26, 8);
                    printf("该工号已存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认添加？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                add_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("添加成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入辅导员工号：");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("该工号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认修改？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                modify_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("修改成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入辅导员工号：");
                int ID = Input_Raw_Integer(6);
                if (search_TeacherByID(head_TeaInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("该工号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认删除？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                delete_Teacher(head_TeaInfor, ID);
                saveTo_TeaInfor(head_TeaInfor, FILENAME_TEA);
                cursor(26, 10);
                printf("删除成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            system("cls");
            system("color F0");
            HideCursor();
            print_AllTeachers(head_TeaInfor);
            system("pause");
            break;
        case 5:
            return;
        default:
            cursor(26, 20);
            printf("无效的选项，请重新输入。\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//学生信息管理菜单
void Menu_adminStdInfor()
{
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("已进入学生信息管理菜单！\n\n");
        cursor(26, 8);
        printf("1. 添加学生");
        cursor(26, 10);
        printf("2. 修改学生信息");
        cursor(26, 12);
        printf("3. 删除学生");
        cursor(26, 14);
        printf("4. 显示学生信息");
        cursor(26, 16);
        printf("5. 退出");
        cursor(26, 18);
        printf("请输入您的选择：");
        choice = Input_1toNum(5);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学生学号：");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) != NULL)
                {
                    cursor(26, 8);
                    printf("该学号已存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认添加？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                add_StdInfor(head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("添加成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学生学号：");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认修改？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                modify_StdInfor(head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("修改成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学生学号：");
                int ID = Input_Raw_Integer(8);
                if (search_StdInfor(head_StdInfor, ID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认删除？（Y/N）："), toupper(Input_YN()) == 'N') {
                    break;
                }
                delete_StuInfor(&head_StdInfor, ID);
                saveTo_StdInfor(head_StdInfor, FILENAME_STD);
                cursor(26, 10);
                printf("删除成功。\n");
                Sleep(1000);
                break;
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            printAll_StdInfor(head_StdInfor, head_Major);
            system("pause");
            break;
        case 5:
            return;
        default:
            cursor(26, 20);
            printf("无效的选项，请重新输入。\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
}

//学生成绩菜单
void Menu_adminStdGrade() {
    int choice;
    int majorNum;
    int gradeNum;
    int studentID;
    char courseName[20];
    float score;
    char semester[20];
    int isExempted;
    int isval;
    float newScore;
    int flag = 0;
    while (flag==0) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 3);
        printf("已进入成绩库管理菜单！");
        cursor(26, 5);
        printf("1. 添加专业");
        cursor(26, 7);
        printf("2. 删除专业");
        cursor(26, 9);
        printf("3. 添加年级");
        cursor(26, 11);
        printf("4. 删除年级");
        cursor(26, 13);
        printf("5. 添加学生");
        cursor(26, 15);
        printf("6. 添加学生成绩");
        cursor(26, 17);
        printf("7. 修改学生成绩");
        cursor(26, 19);
        printf("8. 删除学生成绩");
        cursor(26, 21);
        printf("9. 删除学生");
        cursor(26, 23);
        printf("10. 显示单个学生的所有成绩");
        cursor(26, 25);
        printf("11. 显示指定专业、年级的所有学生成绩");
        cursor(26, 27);
        printf("12. 退出");
        cursor(26, 29);
        printf("请输入您的选择：");
        choice = Input_intNumberover(2);
        switch (choice) {
        case 1:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) != NULL)
                {
                    cursor(26, 8);
                    printf("该专业已存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认添加？（Y/N）："), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Major(&head_Major, majorNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 10);
                printf("添加成功。\n");
                Sleep(1000);
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 2:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("该专业不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                if (printf("是否确认删除？（Y/N）："), toupper(Input_YN()) == 'N') {
                    continue;
                }
                delete_Major(&head_Major, majorNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 10);
                printf("删除成功。\n");
                Sleep(1000);
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 3:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("该专业不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入年级：");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("该年级已存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                if (printf("是否确认添加？（Y/N）："), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Grade(search_Major(head_Major, majorNum), gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 12);
                printf("添加成功。\n");
                Sleep(1000);
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 4:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("该专业不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入年级：");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("该年级不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                if (printf("是否确认删除？（Y/N）："), toupper(Input_YN()) == 'N') {
                    continue;
                }
                delete_Grade(&head_Major, majorNum, gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 12);
                printf("删除成功。\n");
                Sleep(1000);
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 5:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("该专业不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入年级：");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("该年级不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 10);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) != NULL)
                {
                    cursor(26, 12);
                    printf("该学生已存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 12);
                if (printf("是否确认添加？（Y/N）："), toupper(Input_YN()) == 'N') {
                    continue;
                }
                add_Student(&head_Major, studentID, majorNum, gradeNum);
                saveTo_StdGrade(&head_Major, FILENAME_GRA);
                cursor(26, 14);
                printf("添加成功。\n");
                Sleep(1000);
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 6:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入课程编号：");
                scanf("%s", courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("课程编号不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }
                printf("请输入成绩：");
                score=Input_Float(2,2);
                printf("请输入修读学期：");
                Input_SemesterNum(semester);
                printf("请输入是否免修（1表示否，2表示是）：");
                isExempted=Input_1toNum(2)-1;
                printf("请输入是否有效（1表示是，2表示否）：");
                isval=Input_1toNum(2)-1;
                if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == 1) {
                    cursor(26, 10);
                    printf("添加成功。\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == -1) {
                    cursor(26, 10);
                    printf("学生不存在，添加失败。\n");
                }
                else if (add_Score(&head_Major, studentID, courseName, score, semester, isExempted, isval) == -2) {
                    cursor(26, 10);
                    printf("课程编号重复，添加失败。\n");
                }
                else {
                    cursor(26, 10);
                    printf("添加失败。\n");
                    Sleep(1000);
                }
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 7:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入课程编号：");
                scanf("%s", courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("课程编号不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }
                printf("请输入新的成绩：");
                scanf("%f", &newScore);
                if (update_Score(&head_Major, studentID, courseName, newScore) == 1) {
                    cursor(26, 10);
                    printf("修改成功。\n");
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -1) {
                    cursor(26, 10);
                    printf("学生不存在，修改失败。\n");
                }
                else if (update_Score(&head_Major, studentID, courseName, newScore) == -2) {
                    cursor(26, 10);
                    printf("课程编号不存在，修改失败。\n");
                }
                else {
                    cursor(26, 10);
                    printf("修改失败。\n");
                    Sleep(1000);
                }
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 8:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入课程编号：");
                scanf("%s", courseName);
                //判断课程编号是否在课程信息中
                if (search_SubInfor(head_SubInfor, courseName) == NULL)
                {
                    cursor(26, 10);
                    printf("课程编号不存在，添加失败。\n");
                    Sleep(1000);
                    continue;
                }
                if (delete_Score(&head_Major, studentID, courseName) == 1) {
                    cursor(26, 10);
                    printf("删除成功。\n");
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -1) {
                    cursor(26, 10);
                    printf("学生不存在，删除失败。\n");
                }
                else if (delete_Score(&head_Major, studentID, courseName) == -2) {
                    cursor(26, 10);
                    printf("课程编号不存在，删除失败。\n");
                }
                else {
                    cursor(26, 10);
                    printf("删除失败。\n");
                    Sleep(1000);
                }
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 9:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (delete_Student(&head_Major, studentID) == 1) {
                    cursor(26, 8);
                    printf("删除成功。\n");
                }
                else {
                    cursor(26, 8);
                    printf("删除失败。\n");
                    Sleep(1000);
                }
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 10:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入学号：");
                int studentID = Input_Raw_Integer(8);
                if (search_Student(&head_Major, studentID) == NULL)
                {
                    cursor(26, 8);
                    printf("该学号不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                int i = query_Scores(&head_Major, studentID);
                system("pause");
                if (i == 1) {
                    printf("学生不存在\n");
                    continue;
                }
                else if (i == 2)
                {
                    printf("学生无成绩\n");
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
                    printf("\n获得总学分为: %.1f \t", a);
                    float b;
                    b = calculate_myscore(head_Major, head_SubInfor, studentID);
                    cursor(26, 29);
                    printf("计入GPA学分为: %.1f \t", b);
                    float c;
                    c = calculate_GPA(head_Major, studentID, head_SubInfor);
                    cursor(26, 30);
                    printf("GPA: %.5f \t", c);
                    cursor(26, 31);
                    printf("素质加分GPA: %.2f \t", add_GPA);
                    cursor(26, 32);
                    printf("最终GPA: %.5f \t", c + add_GPA);
                    cursor(26, 33);
                    system("pause");
                    Display_Single_BonusNote(Head_Bonus, studentID);// 18 打印 一个人 所有的加分项目
                    system("pause");
                }
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 11:
            do {
                system("cls");
                system("color F0");
                HideCursor();
                cursor(26, 6);
                printf("请输入专业编号：");
                int majorNum = Input_Raw_Integer(4);
                if (search_Major(head_Major, majorNum) == NULL)
                {
                    cursor(26, 8);
                    printf("该专业不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                cursor(26, 8);
                printf("请输入年级：");
                int gradeNum = Input_Raw_Integer(2);
                struct Major* p = search_Major(head_Major, majorNum);
                if (search_Grade(&p, gradeNum) == NULL)
                {
                    cursor(26, 10);
                    printf("该年级不存在，请重新输入。\n");
                    Sleep(1000);
                    continue;
                }
                display_Grade(head_Major, majorNum, gradeNum);
                system("pause");
            } while (printf("\n\t\t\t\t\t是否继续？（Y/N）："), toupper(Input_YN()) == 'Y');
            break;
        case 12:
            flag = 1;
            break;
        default:
            cursor(26, 34);
            printf("无效的选项，请重新输入。\n");
            Sleep(1000);
            break;
        }
        printf("\n");
    }
    return;
}

//科目列表菜单
void Menu_SubInfor() {
    
    int choice;
    while (1) {
        system("cls");
        system("color F0");
        HideCursor();
        cursor(26, 6);
        printf("已进入科目列表管理菜单！");
        cursor(26, 7);
        printf("1. 插入/修改科目");
        cursor(26, 8);
        printf("2. 显示科目列表");
        cursor(26, 9);
        printf("3. 保存到文件");
        cursor(26, 10);
        printf("4. 从文件加载");
        cursor(26, 11);
        printf("5. 删除科目");
        cursor(26, 12);
        printf("6. 退出");
        cursor(26, 13);
        printf("请输入选项：");
        //scanf("%d", &choice);
        choice = Input_1toNum(6);
        system("cls");
        switch (choice) {
        case 1: {
            struct SubInfor* newNode = create_SubInfor();
            if (checkAndReplace_SubInfor(&head_SubInfor, newNode)) {
                cursor(26, 7);
                printf("科目已存在，是否覆盖？（Y/N）：");
                char answer = Input_YN();
                if (toupper(answer) == 'Y') {
                    delete_SubInfor(&head_SubInfor, newNode->SubInforNum);
                    insert_SubInfor(&head_SubInfor, newNode);
                    cursor(26, 8);
                    printf("科目已覆盖。\n");
                }
                else {
                    cursor(26, 8);
                    free(newNode);
                    printf("科目未插入到列表中。\n");
                }
            }
            else {
                cursor(26, 7);
                insert_SubInfor(&head_SubInfor, newNode);
                printf("科目已插入到列表中。\n");
            }
            system("pause");
            break;
        }
        case 2:
            system("cls");
            display_SubInfor(head_SubInfor);
            system("pause");
            break;
        case 3:
            saveTo_SubInfor(head_SubInfor, FILENAME_SUB);
            cursor(26, 7);
            printf("科目信息已保存到文件。\n");
            system("pause");
            break;
        case 4:
            loadFrom_SubInfor(&head_SubInfor, FILENAME_SUB);
            cursor(26, 7);
            printf("已从文件加载科目信息。\n");
            system("pause");
            break;
        case 5: {
            char subNum[MAX_NUM_LENGTH];
            cursor(26, 7);
            printf("请输入要删除的科目编号：");
            //scanf("%s", subNum);
            Input_SubNum(subNum);
            delete_SubInfor(&head_SubInfor, subNum);
            system("pause");
            break;
        }
        case 6:
            cursor(26, 7);
            printf("程序已退出。\n");
            system("pause");
            return;
        default:
            printf("无效的选项，请重新输入。\n");
            system("pause");
            break;
        }
        printf("\n");
    }
}
