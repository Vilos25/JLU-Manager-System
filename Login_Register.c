#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <setjmp.h>
#include <windows.h> 
#include "Login_Register.h"

jmp_buf Laststep4;
jmp_buf Laststep5;
int xy = 10;
int cho;

int Login_Register_Main(int* ID)
{
	system("color F0");
	AccountNode* Accrr[60] = { 0 };
	AccountNode* Head = NULL;
	Head = (AccountNode*)malloc(sizeof(AccountNode));
	Head->Next = NULL;
	Head = Start_Logging_Account(Head);
	AccountNode* Stuhead = Find_DiferHead(Head, 1);//从整条链表中分别找到第一个学生账号、第一个辅导员账号、第一个管理员账号。
	AccountNode* Teahead = Find_DiferHead(Head, 2);
	AccountNode* Admhead = Find_DiferHead(Head, 3);//Adm：administator 的缩写，意为管理员。

Laststep1: //以下所有顶格写的都是跳转回上一步的入口。
	setjmp(Laststep4);
	system("cls");
	printf("\n\n");
	printf("\t\t\t\t\t            __   __      __  __\n");
	printf("\t\t\t\t\t           / /  / /     / / / /\n");
	printf("\t\t\t\t\t      __  / /  / /     / / / /\n");
	printf("\t\t\t\t\t     / /_/ /  / /___  / /_/ /\n");
	printf("\t\t\t\t\t     \\____/  /_____/  \\____/\n");
	printf("\n");
	printf("\t\t\t\t\t* - - - - - - - - - - - - - - - - *\n");
	printf("\t\t\t\t\t|   <吉林大学> 学生成绩管理系统   |\n");
	printf("\t\t\t\t\t* - - - - - - - - - - - - - - - - *\n");
	int y = 12;
	cursor(30, y);
	printf("********************************************************\n");
	cursor(30, y++);
	printf("********************************************************\n");
	cursor(30, y++);
	printf("*********************              *********************\n");
	cursor(30, y++);
	printf("******************      <请登录>      ******************\n");
	cursor(30, y++);
	printf("****************                        ****************\n");
	cursor(30, y++);
	printf("****************   1：登录学生账号      ****************\n");
	cursor(30, y++);
	printf("****************   2：登录教师账号      ****************\n");
	cursor(30, y++);
	printf("****************   3：登录管理员账号    ****************\n");
	cursor(30, y++);
	printf("****************   4：退出              ****************\n");
	cursor(30, y++);
	printf("******************                    ******************\n");
	cursor(30, y++);
	printf("***********************          ***********************\n");
	cursor(30, y++);
	printf("********************************************************\n");
	cursor(30, y++);
	printf("********************************************************\n");
	int Choice;

	do {
		cursor(32, y += 2);
		printf("请输入你的选项:");
		Choice = Input_1toNum(4); //输入正确的单个选项数字（输入已包含纠正输入错误功能）。
	} while (!(1 <= Choice && Choice <= 4));

	char Intputacc[30] = { 0 };//此字符串表示以下（每个）输入的账号。
	char Intputpass[30] = { 0 };//此字符串表示以下（每个）输入的密码。
	int cnt = 0;//计数器：记录输入“账号——密码”组数，cnt=3时触发找回密码选项，同时cnt清零。

	switch (Choice) {
	case 1:
	{
		system("cls");
		Acc_Input_Right(Intputacc); //“输入账号”，“检查账号输入格式是否正确”，将正确形式的账号赋值给Intputacc。
		cursor(26, xy += 1);
		Pass_Input_Right(Intputpass);//“输入密码”，“检查密码输入格式是否正确”，将正确形式的密码赋值给Intputpass。
		while (!If_AccPass_Match(Choice, Head, Intputacc, Intputpass)) {//判断输入的“账号——密码”是否匹配。// 实参Choice的值 在形参中充当了 属性Attri 的值。

			cnt++;
			if (cnt >= 3) {//触发找回密码选项.
				cnt = 0;//cnt清零。
				Morm3_Match_Error(Head);//找回密码的函数
			}
			else {
				cursor(26, xy += 1);
				printf("账号或密码错误，重新输入：");
				Sleep(1000);
				system("cls");
			}

			Acc_Input_Right(Intputacc);
			cursor(26, xy += 1);
			Pass_Input_Right(Intputpass);
		}
	}
	break;
	case 2:
	case 3:
	{
		system("cls");
		Acc_Input_Right_Tea(Intputacc); //“输入账号”，“检查账号输入格式是否正确”，将正确形式的账号赋值给Intputacc。
		cursor(26, xy += 1);
		Pass_Input_Right(Intputpass);//“输入密码”，“检查密码输入格式是否正确”，将正确形式的密码赋值给Intputpass。
		while (!If_AccPass_Match(Choice, Head, Intputacc, Intputpass)) {//判断输入的“账号——密码”是否匹配。// 实参Choice的值 在形参中充当了 属性Attri 的值。

			cnt++;
			if (cnt >= 3) {//触发找回密码选项.
				cnt = 0;//cnt清零。
				Morm3_Match_Error(Head);//找回密码的函数
			}
			else {
				cursor(26, xy += 1);
				printf("账号或密码错误，重新输入：");
				Sleep(1000);
				system("cls");
			}

			Acc_Input_Right_Tea(Intputacc);
			cursor(26, xy += 1);
			Pass_Input_Right(Intputpass);
		}
	}
	break;
	case 4:
		Save_List_ToFile(Head);
		return 0;
	}
	cursor(26, xy += 1);
	printf("登录成功！");
	Sleep(1000);

	switch (Choice) {
	case 1:  /***学生系统入口函数名***/
		*ID = Str_To_IntArr(Intputacc);
		return 1;
		break;
	case 2: /***教师系统入口函数名***/
		*ID = Str_To_IntArr(Intputacc);
		return 2;
		break;
	case 3:
		system("cls");
		xy = 10;
		cursor(26, xy += 1);
		printf("请选择：\n");
		cursor(26, xy += 1);
		printf("\"1\"：管理学生成绩系统\n");
		cursor(26, xy += 1);
		printf("\"2\"：管理登录账号");
		cursor(26, xy += 1);
		int Choice1 = Input_1toNum(2);
		if (Choice1 == 1) {
			/***管理员系统入口函数名***/
			*ID = Str_To_IntArr(Intputacc);
			return 3;
		}
		else {
		Laststep2:
			system("cls");
			xy = 10;
			cursor(26, xy += 1);
			printf("请选择：");
			cursor(26, xy += 1);
			printf("\"1\"：进行批量操作");
			cursor(26, xy += 1);
			printf("\"2\"：进行单独操作");
			cursor(26, xy += 1);
			printf("\"3\"：返回上一步");
			cursor(26, xy += 1);
			int Choice2 = Input_1toNum(3);//输入正确的单个选项数字（已包含纠正输入错误功能）。

			if (Choice2 == 3) {
				printf("返回成功。\n");
				Sleep(1000);
				goto Laststep1;
			}
			else if (Choice2 == 1) {//进行批量操作
				system("cls");
				xy = 10;
				cursor(26, xy += 1);
				printf("请选择：");
				cursor(26, xy += 1);
				printf("\"1\"：批量注册账号");
				cursor(26, xy += 1);
				printf("\"2\"：批量删除账号");
				cursor(26, xy += 1);
				printf("\"3\"：批量初始化密码");
				cursor(26, xy += 1);
				printf("\"4\"：返回上一步");
				cursor(26, xy += 1);
				int Choice3 = Input_1toNum(4);//输入正确的单个选项数字（已包含纠正输入错误功能）。
				system("cls");
				switch (Choice3) {
				case 1://批量注册账号
					system("cls");
					xy = 10;
					cursor(26, xy += 1);

					int Num = 0;

					printf("请输入要注册的账号属性：\n注册学生账号(1)or教师账号(2)or管理员账号(3)？");
					cursor(26, xy += 2);
					int Attri = Input_1toNum(3);

					if (Attri == 1) { Num = Readfile(Head, Stuhead, Accrr, Attri); }//用Readfile函数批量读出文件中的账号并插入链表；插入位置由三个不同的“伪头结点”和属性Attri确定；返回值Num为成功新增的账号数。
					else if (Attri == 2) { Num = Readfile(Head, Teahead, Accrr, Attri); }
					else { Num = Readfile(Head, Admhead, Accrr, Attri); }
					cursor(26, xy += 3);
					printf("List_New_Account.txt读出成功！！！共读出%d个账号", Num);
					cursor(26, xy += 1);
					printf("已自动为您返回上一步。");
					Sleep(1000);
					goto Laststep2;
					break;

				case 2://批量删除账号
					system("cls");
					xy = 10;
					cursor(26, xy += 1);
					printf("请输入要删除的账号数：");
					Num = Input_Num();

					cursor(26, xy += 2);
					printf("删除学生账号(1)or教师账号(2)？");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					system("cls");
					if (cho == 1)
						Acc_Input_Right(Intputacc);
					else
						Acc_Input_Right_Tea(Intputacc);
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 1);
						printf("该账号不存在，请重新输入。");
						cursor(26, xy += 2);
						printf("删除学生账号(1)or教师账号(2)？");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						system("cls");
						if (cho == 1)
							Acc_Input_Right(Intputacc);
						else
							Acc_Input_Right_Tea(Intputacc);
					}

					Batch_Delete_Account(Head, Num, Intputacc);//从Intputacc开始批量删除Num个账号，不区分属性。

					cursor(26, xy += 1);
					printf("已自动为您返回上一步。");
					Sleep(1000);
					goto Laststep2;
					break;

				case 3://批量初始化密码
					system("cls");
					xy = 10;
					cursor(26, xy += 1);
					printf("请输入要修改密码的账号数：");
					Num = Input_Num();
					cursor(26, xy += 1);
					printf("学生账号(1)or教师账号(2)？");
					cho = Input_1toNum(2);
					system("cls");
					if (cho == 1)
						Acc_Input_Right(Intputacc);
					else
						Acc_Input_Right_Tea(Intputacc);
					cursor(26, xy += 1);
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 2);
						printf("该账号不存在，请重新输入。");

						cursor(26, xy += 2);
						printf("学生账号(1)or教师账号(2)？");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						system("cls");
						if (cho == 1)
							Acc_Input_Right(Intputacc);
						else
							Acc_Input_Right_Tea(Intputacc);
					}
					cursor(26, xy += 2);
					printf("输入新密码，");
					Pass_Input_Right(Intputpass);
					Batch_Change_Password(Head, Num, Intputacc, Intputpass);//从Intputacc开始批量修改Num个账号的密码为Intputpass，不区分属性。
					cursor(26, xy += 1);
					printf("已自动为您返回上一步。\n");
					Sleep(1000);
					goto Laststep2;
					break;

				case 4:
					printf("返回成功。\n");
					Sleep(500);
					goto Laststep2;
					break;
				}
			}
			else {  //Choice2=1，即单独操作的选项：
			Laststep3:
				setjmp(Laststep5);
				system("cls");
				xy = 10;
				cursor(26, xy += 1);
				printf("请选择：");
				cursor(26, xy += 1);
				printf("\"1\"：注册单个账号");
				cursor(26, xy += 1);
				printf("\"2\"：删除单个账号");
				cursor(26, xy += 1);
				printf("\"3\"：修改单个账号的密码");
				cursor(26, xy += 1);
				printf("\"4\"：返回上一步");
				cursor(26, xy += 1);
				int Choice4 = Input_1toNum(4);//输入正确的单个选项数字（已包含纠正输入错误功能）。
				system("cls");
				switch (Choice4) {
				case 1:
					Add_Account(Head);//注册单个账号的函数。
					cursor(26, xy += 2);
					printf("已自动为您返回上一步。\n");
					Sleep(1000);
					goto Laststep3;
					break;
				case 2:
				{
					cursor(26, xy += 1);
					printf("删除学生账号(1)or教师账号(2)？");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					system("cls");
					if (cho == 1)
						Acc_Input_Right(Intputacc);
					else
						Acc_Input_Right_Tea(Intputacc);//输入要删除的账号
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 1);
						printf("该账号不存在，请重新输入。");
						cursor(26, xy += 2);
						printf("删除学生账号(1)or教师账号(2)？");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						system("cls");
						if (cho == 1)
							Acc_Input_Right(Intputacc);
						else
							Acc_Input_Right_Tea(Intputacc);
					}
					Delete_Account(Head, Intputacc);//删除单个账号的函数
					cursor(26, xy += 1);
					printf("已自动为您返回上一步。\n");
					Sleep(1000);
					goto Laststep3;
				}
				break;
				case 3:
				{
					cursor(26, xy += 1);
					printf("学生账号(1)or教师账号(2)？");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					system("cls");
					if (cho == 1)
						Acc_Input_Right(Intputacc);
					else
						Acc_Input_Right_Tea(Intputacc);//输入要修改密码的账号
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 2);
						printf("该账号不存在，请重新输入。");

						cursor(26, xy += 2);
						printf("学生账号(1)or教师账号(2)？");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						system("cls");
						if (cho == 1)
							Acc_Input_Right(Intputacc);
						else
							Acc_Input_Right_Tea(Intputacc);
					}
					cursor(26, xy += 2);
					Change_Password(Head, Intputacc);//修改单个账号的密码的函数
					cursor(26, xy += 1);
					printf("已自动为您返回上一步。\n");
					Sleep(1000);
					goto Laststep3;
				}
				break;
				case 4:

					printf("返回成功。\n");
					Sleep(500);
					goto Laststep2;
				}
			}
			break;
		}
	}
	Save_List_ToFile(Head);
	return 0;

}

//以下是所有 非主函数 的 定义 ：
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/



//函数2//在账号信息库的整条链表中分别找到第1个学生账号（Stuhead）、教师账号（Teahead）、管理员账号（Admhead），作为三个“伪链表头”：
AccountNode* Find_DiferHead(AccountNode* Head, int Attri)
{
	AccountNode* pcurrent = Head->Next;
	while (pcurrent != NULL && pcurrent->Attribute != Attri) {//找到第一个属性对应的账号就是“伪链表头”。
		pcurrent = pcurrent->Next;
	}
	return pcurrent;
}
/**************************************************************************************************************************/

//函数3//显示账号链表中的信息：
void Display_Account(AccountNode* Head)
{
	AccountNode* pcurrent = Head->Next;// Head->next是第一个数据节点 
	while (pcurrent != NULL) {
		printf("%s\t", pcurrent->Accountnum);
		printf("%s\t", pcurrent->Password);
		printf("%d\t", pcurrent->Attribute);
		printf("%s\t", pcurrent->Name);
		printf("%s\t", pcurrent->Phonenum);
		printf("%s\t", pcurrent->Email);
		printf("\n");

		pcurrent = pcurrent->Next;
	}
}
/**************************************************************************************************************************/

//函数5//检验用户输入是否为1到Num的单项选择：
bool If_Inputs_1toNum(char Input[], int Num)
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 1)) {//输入是否为一位。
		if (isdigit(Input[0])) {//这一位是否为数字。
			if ((Input[0] - '0') >= 1 && (Input[0] - '0') <= Num) {//这一位数字是否在1到Num之间。
				return true;
			}
			else { flag = false; }
		}
		else { flag = false; }
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/

//函数6//输入纯数字（包含纠正功能），防止用户因输入其它字符导致程序退出：
int Input_Num() {
	char Userinput[30] = { 0 };
	scanf("%s", Userinput);
	printf("\n");
	while (!If_Inputs_Num(Userinput)) //循环终止条件：用户正确纯数字。
	{
		printf("输入内容格式有误，请输入数字：\n");
		memset(Userinput, 0, 5); //清空字符串，防止残留给下次输入。

		scanf("%s", Userinput);
	}
	return (atoi(Userinput));
}
/**************************************************************************************************************************/

//函数7//检验用户输入是否为纯数字：
bool If_Inputs_Num(char Userinput8[]) {
	bool flag;
	flag = true;
	int i = 0;
	int len = strlen(Userinput8);
	for (i = 0; i < len; i++) {
		if (!isdigit(Userinput8[i])) {//检验字符串每一位是否为数字
			flag = false;
		}
	}
	return flag;
}
/**************************************************************************************************************************/

//函数8//包括了“输入账号”并“检查账号输入格式是否正确”功能：
void Acc_Input_Right(char* Userinput)
{
	memset(Userinput, 0, 30);
	xy = 9;
	cursor(26, xy);
	printf("请输入账号：");
	Input_charNumber(Userinput, 8);


	while (!If_InputAcc_Format(Userinput))//循环终止条件：用户正确格式的账号。
	{

		cursor(26, xy += 1);
		printf("输入内容格式有误，请输入8个数字的账号：\n");
		memset(Userinput, 0, 30);//清空字符串，防止残留给下次输入。
		Input_charNumber(Userinput, 8);

	}
}
/**************************************************************************************************************************/

//函数8//包括了“输入账号”并“检查账号输入格式是否正确”功能：
void Acc_Input_Right_Tea(char* Userinput)
{
	memset(Userinput, 0, 30);
	xy = 9;
	cursor(26, xy);
	printf("请输入账号：");
	Input_charNumber(Userinput, 6);


	while (!If_InputAcc_Format_Tea(Userinput))//循环终止条件：用户正确格式的账号。
	{

		cursor(26, xy += 1);
		printf("输入内容格式有误，请输入6个数字的账号：\n");
		memset(Userinput, 0, 30);//清空字符串，防止残留给下次输入。
		Input_charNumber(Userinput, 6);

	}
}
/**************************************************************************************************************************/

//函数9//包括了“输入密码”并“检查密码输入格式是否正确”功能：
void Pass_Input_Right(char* Userinput)
{
	memset(Userinput, 0, 30);
	printf("请输入密码：");

	Pass_Input_Line(Userinput);

	while (!If_InputPass_Format(Userinput))//循环终止条件：用户输入了正确格式的密码。
	{
		cursor(26, xy++);
		printf("输入内容格式有误，请输入只包含数字和字母的小于20个字符的密码：");
		memset(Userinput, 0, 30);//清空字符串，防止残留给下次输入。

		Pass_Input_Line(Userinput);
	}

}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
//函数11//包括了“输入手机号”并“检查手机号输入格式是否正确”功能：
void Phone_Input_Right(char* Userinput)
{
	memset(Userinput, 0, 30);

	Input_charNumber(Userinput, 11);

	while (!If_InputPhone_Format(Userinput))//循环终止条件：用户正确格式的手机号。
	{
		cursor(26, xy++);
		printf("输入内容格式有误，请输入11个数字的手机号：\n");
		memset(Userinput, 0, 30);//清空字符串，防止残留给下次输入。

		Input_charNumber(Userinput, 11);
	}

}
/**************************************************************************************************************************/

//函数12//包括了“输入邮箱”并“检查邮箱输入格式是否正确”功能：
void Email_Input_Right(char* Userinput)
{
	memset(Userinput, 0, 30);
	Input_Email(Userinput);

	while (!If_InputEmail_Format(Userinput))//循环终止条件：用户正确格式的邮箱。
	{
		cursor(26, xy++);
		printf("输入内容格式有误，请输入正确的邮箱：\n");
		memset(Userinput, 0, 30);//清空字符串，防止残留给下次输入。
		Input_Email(Userinput);
	}

}

/**************************************************************************************************************************/

//函数13//检验用户输入的账号格式是否正确：
bool If_InputAcc_Format(char Input[]) {
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 8)) {//输入是否为8位。
		int i;
		for (i = 0; i < 8; i++) {
			if (!(isdigit(Input[i]))) {//每一位是否为数字。
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/
//函数13//检验用户输入的账号格式是否正确：
bool If_InputAcc_Format_Tea(char Input[]) {
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 6)) {//输入是否为6位。
		int i;
		for (i = 0; i < 6; i++) {
			if (!(isdigit(Input[i]))) {//每一位是否为数字。
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}

//函数14//检验用户输入的密码格式是否正确：
bool If_InputPass_Format(char Input[])
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len < 20)) {//输入是否小于20位。
		int i;
		for (i = 0; i < len; i++) {
			if (!(isalnum(Input[i]))) {//每一位是否为数字/字母。
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

//函数16//检验用户输入的手机号格式是否正确：
bool If_InputPhone_Format(char Input[])
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 11)) {//输入是否为11位。
		int i;
		for (i = 0; i < 11; i++) {
			if (!(isdigit(Input[i]))) {//每一位是否为数字。
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}/**************************************************************************************************************************/

//函数17//检验用户输入的邮箱格式是否正确：
bool If_InputEmail_Format(char Input[])
{
	int At_count = 0;
	int Dot_count = 0;

	if (Input[0] == '_' || Input[0] == '.') {
		return false;  // 符号“_”或者“.”不能出现在电子邮件地址的开头
	}

	for (int i = 0; i < strlen(Input); i++) {
		if (Input[i] == '@') {
			At_count++;
		}
		else if (Input[i] == '.') {
			Dot_count++;
		}
	}

	if (At_count == 1 && Dot_count == 1) {// "@"和"."都有且只有一个。
		return true;
	}
	else {
		return false;
	}
}
/**************************************************************************************************************************/

//函数18//检验用户输入的账号、密码（格式已检验）是否匹配：
bool If_AccPass_Match(int Attri, AccountNode* Head, char Intputacc[], char Intputpass[])
{
	AccountNode* pcurrent = Find_DiferHead(Head, Attri);//用属性找到不同的“伪头结点”。
	while (pcurrent != NULL && !((pcurrent->Attribute == Attri) && (strcmp(pcurrent->Accountnum, Intputacc) == 0))) {//找到 属性匹配，账号匹配 的链表结点。
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) {//没找到相应的结点。
		return false;
	}
	else {//找到了相应的结点为pcurrent:
		if (strcmp(pcurrent->Password, Intputpass) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}
/**************************************************************************************************************************/

//函数19//用户输入的3轮账号密码都不匹配，询问并开启“忘记密码”选项：
AccountNode* Morm3_Match_Error(AccountNode* Head)
{
	cursor(26, xy += 1);
	printf("您已经输错3次，请是否选择忘记密码？");
	cursor(26, xy += 1);
	printf("输入 \"1\" ：是");
	cursor(26, xy += 1);
	printf("输入 \"2\" ：否");
	cursor(26, xy += 1);
	printf("输入 \"3\" ：返回上一步");
	cursor(26, xy += 1);
	printf("选项：");
	int Choice1 = Input_1toNum(3);//
	Sleep(1000);
	system("cls");
	if (Choice1 == 1) {
		xy = 10;
		cursor(26, xy += 1);
		printf("找回密码：请选择验证方式：");
		cursor(26, xy += 1);
		printf("输入 \"1\" ：手机号验证");
		cursor(26, xy += 1);
		printf("输入 \"2\" ：邮箱验证");
		cursor(26, xy += 1);
		printf("输入 \"3\" ：返回上一步");
		cursor(26, xy += 1);
		int Choice2 = Input_1toNum(3);//输入正确的1到3的单个选项数字（已包含纠正输入错误功能）。
		system("cls");
		if (Choice2 == 1) {
			xy = 10;
			cursor(26, xy += 1);
			printf("请输入您绑定的手机号：");
			char Inputphone[30] = { 0 };
			Phone_Input_Right(Inputphone);//输入手机号（已包含纠错功能）。
			while (!If_Phone_Exist(Head, Inputphone)) {

				cursor(26, xy += 1);
				printf("该手机号码不存在于任何账号，请重新输入：");
				cursor(26, xy += 1);
				Phone_Input_Right(Inputphone);
			}
			Phone_Change_Password(Head, Inputphone);//通过邮箱修改密码的函数。
			cursor(26, xy += 1);
			printf("密码修改成功，请重新登录：");//返回主函数继续输入账号密码。

		}
		else if (Choice2 == 2) {
			xy = 10;
			cursor(26, xy += 1);
			printf("请输入您绑定的邮箱：");
			char Inputemail[30] = { 0 };
			Email_Input_Right(Inputemail);//输入邮箱（已包含纠错功能）。
			while (!If_Email_Exist(Head, Inputemail)) {

				cursor(26, xy += 1);
				printf("该邮箱不存在于任何账号，请重新输入：");
				cursor(26, xy += 1);
				Email_Input_Right(Inputemail);
			}
			Email_Change_Password(Head, Inputemail);//通过邮箱修改密码的函数。
			cursor(26, xy += 1);
			printf("密码修改成功，请重新登录：");//返回主函数继续输入账号密码。
		}
		else {
			longjmp(Laststep4, 1);
		}
	}
	else if (Choice1 == 2) {
		cursor(26, 9);
		printf("好的，请重新输入账号和密码");//返回主函数继续输入账号密码。
	}
	else {
		longjmp(Laststep4, 1);//跨函数返回上一步。
	}

	return Head;
}
/**************************************************************************************************************************/

//函数20//检索输入的账号（格式已检验）是否存在：
bool If_Acc_Exist(AccountNode* Head, char Input[])
{
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Accountnum, Input) == 0)) {//循环停止条件：链表结束/找到对应账号。
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//链表结束。
	else { return true; }//找到对应账号。
}
/**************************************************************************************************************************/

//函数21//检索输入的手机号（格式已检验）是否存在：
bool If_Phone_Exist(AccountNode* Head, char Input[]) {
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Phonenum, Input) == 0)) {//循环停止条件：链表结束/找到对应手机号。
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//链表结束。
	else { return true; }//找到对应手机号。
}
/**************************************************************************************************************************/

//函数22//检索输入的邮箱（格式已检验）是否存在：
bool If_Email_Exist(AccountNode* Head, char Input[]) {
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Email, Input) == 0)) {//循环停止条件：链表结束/找到对应邮箱。
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//链表结束。
	else { return true; }//找到对应邮箱。
}
/**************************************************************************************************************************/

//函数23//管理员注册单个新账号的权限：
AccountNode* Add_Account(AccountNode* Head)
{
	xy = 10;
	cursor(26, xy += 1);
	printf("请选择：");
	cursor(26, xy += 1);
	printf("\"1\"：注册学生账号\n");
	cursor(26, xy += 1);
	printf("\"2\"：注册教师账号\n");
	cursor(26, xy += 1);
	printf("\"3\"：注册管理员账号\n");
	cursor(26, xy += 1);
	printf("\"4\"：返回上一步\n");
	cursor(26, xy += 1);

	int Attri = Input_1toNum(4);//输入正确的1到4的单个选项数字（已包含纠正输入错误功能）。

	if (Attri == 4) {//跨函数返回上一步。
		longjmp(Laststep5, 1);
	}
	else {//注册单个账号，属性为上面输入的Attri。
		AccountNode* newnode = (AccountNode*)malloc(sizeof(AccountNode));//创建新节点。
		newnode->Attribute = Attri;//填属性。
		newnode->Next = NULL;

		AccountNode* diferhead = Find_DiferHead(Head, Attri);//插入相应的“伪头结点”的下一位。

		newnode->Next = diferhead->Next;
		diferhead->Next = newnode;
		system("cls");
		if (Attri == 1)
			Acc_Input_Right(newnode->Accountnum);
		else
			Acc_Input_Right_Tea(newnode->Accountnum);
		xy = 10;
		cursor(20, xy++);
		Pass_Input_Right(newnode->Password);
		cursor(20, xy++);
		cursor(20, xy++);
		printf("请输入名字：");
		scanf("%s", newnode->Name);
		cursor(20, xy++);
		printf("请输入手机号：");
		Phone_Input_Right(newnode->Phonenum);
		cursor(20, xy++);
		printf("请输入邮箱：");
		Email_Input_Right(newnode->Email);
		cursor(20, xy += 2);
		printf("为%s注册成功！\n\n", newnode->Name);

	}
	return Head;
}
/**************************************************************************************************************************/

//函数24//管理员删除已知账号的权限：
AccountNode* Delete_Account(AccountNode* Head, char Account[])
{
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//找到对应账号。
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	//删除掉现在的 pcurrent节点
	pprev->Next = pcurrent->Next;
	free(pcurrent);
	pcurrent = pprev->Next;
	cursor(26, xy += 2);
	printf("删除成功！");
	cursor(26, xy++);
	//printf("%s\n", Account);

	return Head;
}
/**************************************************************************************************************************/

//函数25//管理员修改已知账号的密码的权限：
AccountNode* Change_Password(AccountNode* Head, char Account[])
{
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//找到对应账号。
		pcurrent = pcurrent->Next;
	}
	printf("新密码：");
	char Newpassword[20] = { 0 };
	scanf("%s", Newpassword);//输入新密码。
	while (!If_InputPass_Format(Newpassword))//检验新密码格式
	{
		cursor(26, xy++);
		printf("输入内容格式有误，请输入只包含数字和字母的小于20个字符的新密码：");
		memset(Newpassword, 0, 20);//清空字符串，防止残留的字符影响下次循环的输入。
		cursor(26, xy++);
		scanf("%s", Newpassword);
	}
	strcpy(pcurrent->Password, Newpassword);
	cursor(26, xy += 2);
	printf("为 %s 账号修改密码成功！", Account);
	return Head;
}
/**************************************************************************************************************************/

//函数26//手机验证通过后修改密码：
AccountNode* Phone_Change_Password(AccountNode* Head, char Inputphone[]) {
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Phonenum, Inputphone) == 0)) {//找到对应手机号。
		pcurrent = pcurrent->Next;
	}
	cursor(26, xy++);
	printf("请输入新密码，");
	Pass_Input_Right(pcurrent->Password);//输入新密码。
	return Head;
}
/**************************************************************************************************************************/

//函数27//邮箱验证通过后修改密码：
AccountNode* Email_Change_Password(AccountNode* Head, char Inputemail[]) {
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Email, Inputemail) == 0)) {//找到对应邮箱。
		pcurrent = pcurrent->Next;
	}
	cursor(26, xy++);
	printf("请输入新密码，");
	Pass_Input_Right(pcurrent->Password);
	return Head;
}

/**************************************************************************************************************************/

//函数28//从 LIST_Account.txt 文件中批量读出的账号：
int Readfile(AccountNode* Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri)
{
	int i = 0;//i是计数器，记录成功从文件中录入的账号数。
	FILE* fp;
	if ((fp = fopen("List_New_Account.txt", "r+")) == NULL)
	{
		cursor(26, xy++);
		printf("文件打开失败！！!\n");
		return 0;
	}
	for (i = 0; (!feof(fp)); i++)
	{
		Accrr[i] = (AccountNode*)malloc(sizeof(AccountNode));//为每个录入的账号信息开辟动态内存。
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%s", Accrr[i]->Accountnum, Accrr[i]->Password, &Accrr[i]->Attribute, Accrr[i]->Name, Accrr[i]->Phonenum, Accrr[i]->Email);
		Accrr[i]->Next = NULL;
		Accrr[i]->Attribute = Attri;
	}
	fclose(fp);
	Access_AccList(Head, Diferhead, Accrr, Attri, i);//将每个新节点“串”进链表里。//插入位置由三个不同的“伪头结点”和属性Attri确定；
	cursor(26, xy += 2);
	printf("共注册 %d 个新账号\n", i);
	return i; //返回读出的账号数。
}
/**************************************************************************************************************************/

//函数29//将从文件中读入的账号插入账号链表：
AccountNode* Access_AccList(AccountNode* Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri, int m) {//
	AccountNode* pprev = Diferhead;
	AccountNode* pcurrent = Diferhead->Next;
	while ((pcurrent != NULL) && (pcurrent->Attribute == Attri)) {//用pcurrent找到下一个属性，则pprev是对应属性的最后一个账号。
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	AccountNode* tmp = pprev;//pprev是对应属性的最后一个账号,用tmp表示。

	int i = 0;
	for (i = 0; i < m; i++) {
		tmp->Next = Accrr[i];//新节点连到tmp后面。
		tmp = Accrr[i];//新节点做tmp。
	}
	tmp->Next = pcurrent;//所有新节点接入完成后，连上表示下一个属性的pcurrent节点。使链表完整不断层。

	return Head;
}
/**************************************************************************************************************************/

//函数30//批量删除账号的函数。
AccountNode* Batch_Delete_Account(AccountNode* Head, int Num, char Account[]) {
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	AccountNode* pcurrent_to_num = NULL;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//开始删除的对应账号。
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	pcurrent_to_num = pcurrent;//从pcurrent开始删除，pprev不用删除，留着连接剩下的一段链表。
	int i = 0;
	for (i = 0; i < Num; i++) {//循环删除掉Num个账号。
		AccountNode* pcurrent_to_num2 = pcurrent_to_num->Next; //用pcurrent_to_num2标记要删的节点的下一个结点。
		free(pcurrent_to_num);
		pcurrent_to_num = pcurrent_to_num2;
	}
	pprev->Next = pcurrent_to_num;//，此时pcurrent_to_num表示剩下一段链表的第一个结点，用pprev连接剩下的一段链表。

	cursor(26, xy++);
	printf("删除成功！刚删除了%d个账号。\n", Num);
	return Head;
}
/**************************************************************************************************************************/

//函数31//批量修改密码的函数：
AccountNode* Batch_Change_Password(AccountNode* Head, int m, char Account[], char Newpass[]) {
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	AccountNode* pcurrent_to_m = NULL;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//找到开始修改密码的对应账号。
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	pcurrent_to_m = pcurrent;//从pcurrent开始改密码，pprev不用改。
	int i = 0;
	for (i = 0; i < m || pcurrent_to_m == NULL; i++) {
		strcpy(pcurrent_to_m->Password, Newpass);//给pcurrent_to_m改密码。
		pcurrent_to_m = pcurrent_to_m->Next;//pcurrent_to_m指向下一位。
	}
	cursor(26, xy += 2);
	printf("修改成功！刚修改了%d个账号的密码。\n", i);

	return Head;
}
/**************************************************************************************************************************/

//函数32//开始从文件中录入所有账号信息的函数：
AccountNode* Start_Logging_Account(AccountNode* Head)
{
	int i = 0;
	FILE* fp;
	if ((fp = fopen("LIST_Account.txt", "r+")) == NULL)
	{
		cursor(26, xy++);
		printf("文件打开失败！！!\n");
		exit(0);
	}

	AccountNode* prrev = Head; //尾链表
	AccountNode* newnode = NULL;

	for (i = 0; !feof(fp); i++)
	{
		char line[100]; // 用于读取每行的缓冲区

		if (fgets(line, sizeof(line), fp) == NULL)
			break; // 文件结束或读取错误，跳出循环

		// 判断是否为空行
		if (strlen(line) <= 1) // 只包含换行符的行长度为1
			break; // 文件末尾为空行，跳出循环

		newnode = (AccountNode*)malloc(sizeof(AccountNode)); //为每个录入的账号信息开辟动态内存。
		sscanf(line, "%s\t%s\t%d\t%s\t%s\t%s", newnode->Accountnum, newnode->Password, &newnode->Attribute, newnode->Name, newnode->Phonenum, newnode->Email);
		newnode->Next = NULL;
		prrev->Next = newnode;
		prrev = newnode;
	}
	fclose(fp);
	return Head;
}
/**************************************************************************************************************************/

//函数33//保存所有账号信息到文件的函数：
void Save_List_ToFile(AccountNode* Head)
{
	FILE* file = fopen("LIST_Account.txt", "w");
	if (file == NULL) {
		cursor(26, xy++);
		printf("无法打开文件\n");
		return;
	}

	AccountNode* current = Head->Next;
	while (current != NULL) {
		fprintf(file, "%s \t%s \t%d \t%s \t %s\t %s\n", current->Accountnum, current->Password, current->Attribute, current->Name, current->Phonenum, current->Email);
		current = current->Next;
	}
	fclose(file);
}
/**************************************************************************************************************************/

//函数34//字符串转变成一维整型数组：
int Str_To_IntArr(const char* Inputacc) {
	int length = strlen(Inputacc);
	int i = 0;
	int ans = 0;
	int* intArr = (int*)malloc(length * sizeof(int));  // 为整型数组分配内存空间

	for (i = 0; i < length; i++) {
		intArr[i] = Inputacc[i] - '0';  // 将字符转换为整数并存储到整型数组中
		ans = ans * 10 + intArr[i];
	}

	return ans;  // 返回整型
}
/**************************************************************************************************************************/

//函数35//释放内存：
void Free_account(AccountNode* Head)
{
	AccountNode* current = Head;
	while (current != NULL) {
		AccountNode* next = current->Next;
		free(current);
		current = next;
	}
}