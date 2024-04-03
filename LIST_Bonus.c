// LIST_BonusDev_Paper.txt  存放系统已有数据，并作为保存文件。
// LIST_newBonusDev_Paper.txt   存放预备用来批量添加的数据。
// 其他两种素质类项目的.txt文件作用同理
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <setjmp.h>
#include <windows.h> 

//#include "Login_Register.h"
#include "LIST_Bonus.h"
#define FILE_COMP "LIST_BonusDev_Comp.txt"
#define FILE_PAPER "LIST_BonusDev_Paper.txt"
#define FILE_PROJ "LIST_BonusDev_Proj.txt"
#define FILE_COMP_NEW "LIST_newBonusDev_Comp.txt"
#define FILE_PAPER_NEW "LIST_newBonusDev_Paper.txt"
#define FILE_PROJ_NEW "LIST_newBonusDev_Proj.txt"

/**************************************************************************************************************************/

// 1 首次 从文件中录入 所有素质类加分信息
BonusNote* Start_Logging_bonusFile(void)
{
	CompNote* Comparr[50] = { 0 };
	PaperNote* Paperarr[50] = { 0 };
	ProjNote* Projarr[50] = { 0 };

	BonusNote* Head = (BonusNote*)malloc(sizeof(BonusNote));//整个学生的链表的头结点不保存任何数据。
	memset(Head->Accountnum, 0, 20);
	memset(Head->Name, 0, 30);
	Head->Comphead = NULL;
	Head->Paperhead = NULL;
	Head->Projhead = NULL;
	Head->Next = NULL;
	Head->Bonusponit = 0.00;
	int i = 0;
	FILE* fp;
	if ((fp = fopen("LIST_Bonus_Account.txt", "r+")) == NULL)
	{
		printf("文件打开失败！！!\n");
		exit(0);
	}

	BonusNote* prrev = Head; //尾链表
	BonusNote* newnode = NULL;

	for (i = 0; !feof(fp); i++)
	{
		char line[100]; // 用于读取每行的缓冲区

		// 读取一行内容
		if (fgets(line, sizeof(line), fp) == NULL)
			break; // 文件结束或读取错误，跳出循环

		// 判断是否为空行
		if (strlen(line) <= 1) // 只包含换行符的行长度为1
			break; // 文件末尾为空行，跳出循环

		newnode = (BonusNote*)malloc(sizeof(BonusNote)); //为每个录入的账号开辟动态内存。
		memset(newnode->Accountnum, 0, 20);
		memset(newnode->Name, 0, 30);
		sscanf(line, "%s\t%s\t", newnode->Accountnum, newnode->Name);
		newnode->Comphead = NULL;
		newnode->Paperhead = NULL;
		newnode->Projhead = NULL;
		newnode->Next = NULL;
		newnode->Bonusponit = 0.00;

		prrev->Next = newnode;
		prrev = newnode;
	}
	fclose(fp);
	//将加分信息从三个.txt文件中读出 
	Logging_CompNote(Head, Comparr, 1);
	Logging_PaperNote(Head, Paperarr, 1);
	Logging_ProjNote(Head, Projarr, 1);
	return Head;
}
/**************************************************************************************************************************/

//增加学生节点，传入int类型的学号，char类型的姓名，返回一个新的学生节点
void Add_BonusNote_Node(BonusNote* Head, int ID, char Name[])
{
	char Acc[20] = { 0 };
	Int_To_Str(ID, Acc);
	BonusNote* newnode = (BonusNote*)malloc(sizeof(BonusNote));
	memset(newnode->Accountnum, 0, 20);
	memset(newnode->Name, 0, 30);
	strcpy(newnode->Accountnum, Acc);
	strcpy(newnode->Name, Name);
	newnode->Comphead = NULL;
	newnode->Paperhead = NULL;
	newnode->Projhead = NULL;
	newnode->Next = NULL;
	newnode->Bonusponit = 0.00;

	BonusNote* pcurrent = Head;
	while (pcurrent->Next != NULL) {
		pcurrent = pcurrent->Next;
	}
	pcurrent->Next = newnode;
	return;
}

void Save_List_To_bonusFile(BonusNote* Head)//  将所有 加分项目 保存进文件
{
	Save_CompList_ToFile(Head);//  将所有 比赛项目 保存进文件
	Save_PaperList_ToFile(Head);//  将所有 论文项目 保存进文件
	Save_ProjList_ToFile(Head);//  将所有 结题项目 保存进文件
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
void Add_Mutiple_CompNote(BonusNote* Head)// 2 批量添加 多人的比赛项目
{
	CompNote* newComparr[50] = { 0 };
	Logging_CompNote(Head, newComparr, 0);
}
void Add_Mutiple_PaperNote(BonusNote* Head)// 3 批量添加 多人的论文信息
{
	PaperNote* newPaperarr[50] = { 0 };
	Logging_PaperNote(Head, newPaperarr, 0);
}
void Add_Mutiple_ProjNote(BonusNote* Head)// 4 批量添加 多人的国家级优秀结题项目信息
{
	ProjNote* newProjarr[50] = { 0 };
	Logging_ProjNote(Head, newProjarr, 0);
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
// 5 录入单个 比赛项目 给某人
BonusNote* Add_Single_CompNote(BonusNote* Head, char Acc[], char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}
	CompNote* newnode = (CompNote*)malloc(sizeof(CompNote));//创建新节点。
	newnode->Next = NULL;

	system("cls");
	strcpy(newnode->Accountnum, pcurrent->Accountnum);
	printf("\n输入竞赛项目名称:\n");
	Comp_Name_Input_Right(newnode->CompName);//必须可选
	printf("\n请输入获奖人和顺序，人名之间请用顿号隔开：\n");//(二重数组)
	scanf("%s", newnode->Winers);//通过指针改变内容。
	printf("\n请输入竞赛类型：\n");
	Input_ABC(&(newnode->ABC));
	printf("\n请输入获奖等级：\n");
	newnode->AwardGrade = Input_1toNum(3);
	printf("请输入主办单位：\n");
	Sponsor_Input_Right(newnode->Sponsor);
	printf("\n请输入获奖时间：");
	Time_Input_Right(newnode->Time);
	if (Tea_Stu == 't')//如果是辅导员录入
	{
		printf("请输入审核属性：\n");//就直接输入审核属性，1/2/3都可能
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }//如果是学生录入，审核属性只能是2，即“审核中”

	if (newnode->ABC == 'A' && newnode->AwardGrade == 1) {
		newnode->Ponit = 0.40;
	}
	else if ((newnode->ABC == 'A' && newnode->AwardGrade == 2) || (newnode->ABC == 'B' && newnode->AwardGrade == 1)) {
		newnode->Ponit = 0.20;
	}
	else if ((newnode->ABC == 'A' && newnode->AwardGrade == 3) || (newnode->ABC == 'B' && newnode->AwardGrade == 2) || (newnode->ABC == 'C' && newnode->AwardGrade == 1)) {
		newnode->Ponit = 0.10;
	}
	else if ((newnode->ABC == 'B' && newnode->AwardGrade == 3) || (newnode->ABC == 'C' && newnode->AwardGrade == 2)) {
		newnode->Ponit = 0.05;
	}
	else {
		newnode->Ponit = 0.02;
	}

	CompNote* pcurrent2 = pcurrent->Comphead;
	if (pcurrent2 == NULL) {
		pcurrent->Comphead = newnode;
	}
	else {
		while (pcurrent2->Next != NULL) {//找到尾结点
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}

	if (newnode->Attribute == 1) {//如果审核属性为“批准”
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//就重算该学生加分绩点
	}
	if (Tea_Stu == 't')//如果是辅导员录入
	{
		printf("\n为%s添加竞赛类加分项目成功！\n\n", pcurrent->Name);
	}
	else {
		printf("\n申请成功！请耐心等待教师审核通过。\n\n");
	}

	return Head;
}
/**************************************************************************************************************************/

// 6 录入单个 论文项目 给某人
BonusNote* Add_Single_PaperNote(BonusNote* Head, char Acc[], char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}
	PaperNote* newnode = (PaperNote*)malloc(sizeof(PaperNote));//创建新节点。
	newnode->Next = NULL;

	system("cls");
	strcpy(newnode->Accountnum, pcurrent->Accountnum);//ok
	printf("请输入期刊名称/会议名称：\n");
	Journal_Input_Right(newnode->Journal_Conference);//必须可选
	printf("\n输入论文名称:\n");
	scanf("%s", newnode->PaperName);
	//char new[50] = { 0 };
	//strncpy(new, newnode->PaperName, strlen(newnode->PaperName) - 1);
	printf("\n所有作者和顺序，人名之间请用顿号隔开：\n");//(二重数组)
	scanf("%s", newnode->Writers); //通过指针改变内容。
	printf("\n请输入发表时间,");
	Time_Input_Right(newnode->Time);//ok
	printf("卷/期/论文号/页码范围：\n");
	Volume_Page_Input_Right(newnode->Volume_Page);//ok
	if (Tea_Stu == 't')
	{
		printf("请输入审核属性：\n");
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }
	if (strcmp(newnode->Journal_Conference, "业界公认学科综合顶级期刊") == 0)
	{
		newnode->Ponit = 0.40;
	}
	else if ((strcmp(newnode->Journal_Conference, "CCF - A期刊") == 0) || (strcmp(newnode->Journal_Conference, "CCF-A会议长文") == 0) || (strcmp(newnode->Journal_Conference, "CCF-B会议的最佳论文/最佳学生论文") == 0))
	{
		newnode->Ponit = 0.20;
	}
	else if ((strcmp(newnode->Journal_Conference, "CCF-B期刊论文") == 0) || (strcmp(newnode->Journal_Conference, "中科院期刊分区一区论文") == 0) || (strcmp(newnode->Journal_Conference, "CCFC会议的最佳论文/最佳学生论文") == 0))
	{
		newnode->Ponit = 0.10;
	}
	else if ((strcmp(newnode->Journal_Conference, "影响因子非0的SCI检索期刊论文") == 0) || (strcmp(newnode->Journal_Conference, "CCF-C 会议长文") == 0) || (strcmp(newnode->Journal_Conference, "中国科学：信息科学、计算机研究与发展、计算机辅助设计与图形学学报、电子学报中文版、自动化学报发表的学术论文") == 0))
	{
		newnode->Ponit = 0.02;
	}
	else if (strcmp(newnode->Journal_Conference, "EI检索期刊") == 0)
	{
		newnode->Ponit = 0.01;
	}
	else
	{
		newnode->Ponit = 0.05;
	}

	PaperNote* pcurrent2 = pcurrent->Paperhead;
	if (pcurrent2 == NULL) {
		pcurrent->Paperhead = newnode;
	}
	else {
		while (pcurrent2->Next != NULL) {//找到尾结点
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}
	if (newnode->Attribute == 1) {//如果审核属性为“批准”
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//就重算该学生加分绩点
	}
	if (Tea_Stu == 't')//如果是辅导员录入
	{
		printf("\n为%s添加论文类加分项目成功！\n\n", pcurrent->Name);
	}
	else {
		printf("\n申请成功！请耐心等待教师审核通过。\n\n");
	}

	return Head;
}
/**************************************************************************************************************************/

// 7 录入单个 结题项目 给某人
BonusNote* Add_Single_ProjNote(BonusNote* Head, char Acc[], char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}
	ProjNote* newnode = (ProjNote*)malloc(sizeof(ProjNote));//创建新节点。
	newnode->Next = NULL;

	strcpy(newnode->Accountnum, pcurrent->Accountnum);//ok

	system("cls");
	printf("\n输入项目名称：");
	//getchar();
	scanf("%s", newnode->ProjName);
	printf("所有成员和顺序：（人名之间请用顿号隔开）\n");//(二重数组)

	scanf("%s", newnode->Members);//通过指针改变内容。
	printf("指导教师姓名：\n");
	scanf("%s", newnode->Advisor);
	printf("立项时间：\n");
	Time_Input_Right(newnode->Start_time);//ok
	printf("结项时间：\n");
	Time_Input_Right(newnode->Finish_time);//ok
	printf("项目编号：\n");
	Pronum_Input_Right(newnode->ProjNum);//只由数字加字母构成，顺序不定
	printf("请输入责任性质：\n");
	newnode->Role = Input_1toNum(3);//ok
	if (Tea_Stu == 't')
	{
		printf("请输入审核属性：\n");
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }

	if (newnode->Role == 1) { newnode->Ponit = 0.10; }
	else { newnode->Ponit = 0.05; }//不会有newnode->Role == 3的情况。不加分，不作为素质类加分项目。

	ProjNote* pcurrent2 = pcurrent->Projhead;
	if (pcurrent2 == NULL) {
		pcurrent->Projhead = newnode;
	}
	else {
		while (pcurrent2->Next != NULL) {//找到尾结点
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}
	if (newnode->Attribute == 1) {//如果审核属性为“批准”
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//就重算该学生加分绩点
	}
	if (Tea_Stu == 't')//如果是辅导员录入
	{
		printf("\n为%s添加结题项目类加分项目成功！\n\n", pcurrent->Name);
	}
	else {
		printf("\n申请成功！请耐心等待教师审核通过。\n\n");
	}

	return Head;
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 8 从文件中批量录入 多人的比赛项目
void Logging_CompNote(BonusNote* Head, CompNote* Comparr[], int Atri)
{
	int i = 0;
	FILE* fp1;
	if (Atri) {
		if ((fp1 = fopen(FILE_COMP, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	else {
		if ((fp1 = fopen(FILE_COMP_NEW, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp1); i++)
	{
		char line[1000]; // 用于读取每行的缓冲区

		// 读取一行内容
		if (fgets(line, sizeof(line), fp1) == NULL)
			break; // 文件结束或读取错误，跳出循环

		// 判断是否为空行
		if (strlen(line) <= 1) // 只包含换行符的行长度为1
			break; // 文件末尾为空行，跳出循环

		Comparr[i] = (CompNote*)malloc(sizeof(CompNote));
		Comparr[i]->Next = NULL;
		memset(Comparr[i]->Accountnum, 0, 20);
		memset(Comparr[i]->CompName, 0, 50);
		memset(Comparr[i]->Winers, 0, 150);
		memset(Comparr[i]->Sponsor, 0, 1000);
		memset(Comparr[i]->Time, 0, 30);

		sscanf(line, "%s\t%s\t%s\t%c\t%d\t%s\t%s\t%d\t%f\t", Comparr[i]->Accountnum, Comparr[i]->CompName, Comparr[i]->Winers, &Comparr[i]->ABC, &Comparr[i]->AwardGrade, Comparr[i]->Sponsor, Comparr[i]->Time, &Comparr[i]->Attribute, &Comparr[i]->Ponit);

		//插入链表中
		BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
		while (!(strcmp(pcurrent->Accountnum, Comparr[i]->Accountnum) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
			pcurrent = pcurrent->Next;
		}

		CompNote* pcurrent2 = pcurrent->Comphead;
		if (pcurrent2 == NULL) {
			pcurrent->Comphead = Comparr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//找到尾结点
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Comparr[i];
		}

		if (Comparr[i]->Attribute == 1) {//如果审核属性为“批准”
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//就重算该学生加分绩点
		}
	}
	fclose(fp1);
}
/**************************************************************************************************************************/

// 9 从文件中批量录入 多人的论文信息
void Logging_PaperNote(BonusNote* Head, PaperNote* Paperarr[], int Atri)
{
	int i = 0;
	FILE* fp2;
	if (Atri) {
		if ((fp2 = fopen(FILE_PAPER, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	else {
		if ((fp2 = fopen(FILE_PAPER_NEW, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp2); i++)
	{
		char line[1000]; // 用于读取每行的缓冲区

		// 读取一行内容
		if (fgets(line, sizeof(line), fp2) == NULL)
			break; // 文件结束或读取错误，跳出循环

		// 判断是否为空行
		if (strlen(line) <= 1) // 只包含换行符的行长度为1
			break; // 文件末尾为空行，跳出循环

		Paperarr[i] = (PaperNote*)malloc(sizeof(PaperNote));
		Paperarr[i]->Next = NULL;
		memset(Paperarr[i]->Accountnum, 0, 20);
		memset(Paperarr[i]->PaperName, 0, 50);
		memset(Paperarr[i]->Writers, 0, 150);
		memset(Paperarr[i]->Journal_Conference, 0, 150);
		memset(Paperarr[i]->Time, 0, 30);
		memset(Paperarr[i]->Volume_Page[0], 0, 50);
		memset(Paperarr[i]->Volume_Page[1], 0, 50);
		memset(Paperarr[i]->Volume_Page[2], 0, 50);

		sscanf(line, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%f\t", Paperarr[i]->Accountnum, Paperarr[i]->PaperName, Paperarr[i]->Writers, Paperarr[i]->Journal_Conference, Paperarr[i]->Time, Paperarr[i]->Volume_Page[0], Paperarr[i]->Volume_Page[1], Paperarr[i]->Volume_Page[2], &Paperarr[i]->Attribute, &Paperarr[i]->Ponit);

		//插入链表中
		BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
		while ( /*pcurrent != NULL &&*/ !(strcmp(pcurrent->Accountnum, Paperarr[i]->Accountnum) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
			pcurrent = pcurrent->Next;
		}

		PaperNote* pcurrent2 = pcurrent->Paperhead;
		if (pcurrent2 == NULL) {
			pcurrent->Paperhead = Paperarr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//找到尾结点
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Paperarr[i];
		}

		if (Paperarr[i]->Attribute == 1) {//如果审核属性为“批准”
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//就重算该学生加分绩点
		}
	}
	fclose(fp2);
}
/**************************************************************************************************************************/

// 10 从文件中批量录入 多人结题项目信息
void Logging_ProjNote(BonusNote* Head, ProjNote* Projarr[], int Atri)
{
	int i = 0;
	FILE* fp3;
	if (Atri) {
		if ((fp3 = fopen(FILE_PROJ, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	else {
		if ((fp3 = fopen(FILE_PROJ_NEW, "r+")) == NULL)
		{
			printf("文件打开失败！！!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp3); i++)
	{
		char line[1000]; // 用于读取每行的缓冲区

		// 读取一行内容
		if (fgets(line, sizeof(line), fp3) == NULL)
			break; // 文件结束或读取错误，跳出循环

		// 判断是否为空行
		if (strlen(line) <= 1) // 只包含换行符的行长度为1
			break; // 文件末尾为空行，跳出循环

		Projarr[i] = (ProjNote*)malloc(sizeof(ProjNote));
		Projarr[i]->Next = NULL;
		memset(Projarr[i]->Accountnum, 0, 20);
		memset(Projarr[i]->ProjName, 0, 50);
		memset(Projarr[i]->Members, 0, 150);
		memset(Projarr[i]->Advisor, 0, 30);
		memset(Projarr[i]->Start_time, 0, 30);
		memset(Projarr[i]->Finish_time, 0, 30);
		memset(Projarr[i]->ProjNum, 0, 30);

		sscanf(line, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t", Projarr[i]->Accountnum, Projarr[i]->ProjName, Projarr[i]->Members, Projarr[i]->Advisor, Projarr[i]->Start_time, Projarr[i]->Finish_time, Projarr[i]->ProjNum, &Projarr[i]->Role, &Projarr[i]->Attribute, &Projarr[i]->Ponit);
		//插入链表中
		BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
		while (!(strcmp(pcurrent->Accountnum, Projarr[i]->Accountnum) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
			pcurrent = pcurrent->Next;
		}

		ProjNote* pcurrent2 = pcurrent->Projhead;
		if (pcurrent2 == NULL) {
			pcurrent->Projhead = Projarr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//找到尾结点
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Projarr[i];
		}

		if (Projarr[i]->Attribute == 1) {//如果审核属性为“批准”
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//就重算该学生加分绩点
		}
	}
	fclose(fp3);
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 11将所有 比赛项目 保存进文件
void Save_CompList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_COMP, "w");  // 以写入模式打开文件，若文件不存在则创建，若存在则清空文件内容
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}

	BonusNote* current = Head->Next;  // 从链表头部开始遍历
	while (current != NULL) {
		CompNote* pcurrent2 = current->Comphead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%c\t%d\t%s\t%s\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->CompName, pcurrent2->Winers, pcurrent2->ABC, pcurrent2->AwardGrade, pcurrent2->Sponsor, pcurrent2->Time, pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // 遍历至下一个节点
		}
		current = current->Next;
	}
	fclose(file);  // 关闭文件
}
/**************************************************************************************************************************/
// 12 将所有 论文项目 保存进文件

void Save_PaperList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_PAPER, "w");  // 以写入模式打开文件，若文件不存在则创建，若存在则清空文件内容
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}

	BonusNote* current = Head->Next;  // 从链表头部开始遍历
	while (current != NULL) {
		PaperNote* pcurrent2 = current->Paperhead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->PaperName, pcurrent2->Writers, pcurrent2->Journal_Conference, pcurrent2->Time, pcurrent2->Volume_Page[0], pcurrent2->Volume_Page[1], pcurrent2->Volume_Page[2], pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // 遍历至下一个节点
		}
		current = current->Next;
	}
	fclose(file);  // 关闭文件
}
/**************************************************************************************************************************/
// 13 将所有 结题项目 保存进文件

void Save_ProjList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_PROJ, "w");  // 以写入模式打开文件，若文件不存在则创建，若存在则清空文件内容
	if (file == NULL) {
		printf("无法打开文件\n");
		return;
	}

	BonusNote* current = Head->Next;  // 从链表头部开始遍历
	while (current != NULL) {
		ProjNote* pcurrent2 = current->Projhead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->ProjName, pcurrent2->Members, pcurrent2->Advisor, pcurrent2->Start_time, pcurrent2->Finish_time, pcurrent2->ProjNum, pcurrent2->Role, pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // 遍历至下一个节点
		}
		current = current->Next;
	}
	fclose(file);  // 关闭文件
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 17 计算 单个人 的有效加分绩点
float Calcul_Single_Bonusponit(BonusNote* Head, char Acc[])
{
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	float Bonus_sum = 0.00;
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}
	CompNote* pcurrent2 = pcurrent->Comphead;
	PaperNote* pcurrent3 = pcurrent->Paperhead;
	ProjNote* pcurrent4 = pcurrent->Projhead;
	int a = 0, b = 0, c = 0;
	float apoint = 0.00, bpoint = 0.00, cpoint = 0.00;
	while (pcurrent2 != NULL) {
		if (pcurrent2->Attribute == 1) { //比赛类型，同类取最高
			if (pcurrent2->ABC == 'A') {
				if (pcurrent2->Ponit > apoint) {
					Bonus_sum = Bonus_sum - apoint + pcurrent2->Ponit;
					apoint = pcurrent2->Ponit;
				}
			}
			if (pcurrent2->ABC == 'B') {
				if (pcurrent2->Ponit > bpoint) {
					Bonus_sum = Bonus_sum - bpoint + pcurrent2->Ponit;
					bpoint = pcurrent2->Ponit;
				}
			}
			if (pcurrent2->ABC == 'C') {
				if (pcurrent2->Ponit > cpoint) {
					Bonus_sum = Bonus_sum - cpoint + pcurrent2->Ponit;
					cpoint = pcurrent2->Ponit;
				}
			}
		}
		pcurrent2 = pcurrent2->Next;
	}
	while (pcurrent3 != NULL) {
		if (pcurrent3->Attribute == 1) { Bonus_sum += pcurrent3->Ponit; }
		pcurrent3 = pcurrent3->Next;
	}
	while (pcurrent4 != NULL) {
		if (pcurrent4->Attribute == 1) { Bonus_sum += pcurrent4->Ponit; }
		pcurrent4 = pcurrent4->Next;
	}
	if (Bonus_sum >= 0.4) { return 0.40; }
	else { return Bonus_sum; }
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

//通过账号查找学生节点，返回该节点的指针
BonusNote* Find_BonusNote_ByAcc(BonusNote* Head, int ID)
{
	char Acc[20] = { 0 };
	Int_To_Str(ID, Acc);// 36 数字ID转成字符串账号
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0) && pcurrent->Next != NULL) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}

	return pcurrent;
}

// 18 打印 一个人 所有的加分项目
void Display_Single_BonusNote(BonusNote* Head, int ID)
{
	system("cls");
	char Acc[20] = { 0 };
	Int_To_Str(ID, Acc);// 36 数字ID转成字符串账号
	BonusNote* pcurrent = Head->Next;// Head->next是第一个BonusNote数据节点 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0) && pcurrent->Next != NULL) {//找到对应账号。（前面应该采取措施，使形参的账号Acc必然存在于链表中）
		pcurrent = pcurrent->Next;
	}
	if (pcurrent->Next == NULL)
	{
		printf("未找到该学生的素质类加分信息！\n");
		Sleep(1000);
		return;
	}
	printf("\n\t\t学号：%s\n", pcurrent->Accountnum);
	printf("\n\t\t姓名：%s\n", pcurrent->Name);
	printf("\n");
	Print_Single_Comp(pcurrent->Comphead);
	printf("\n");
	Print_Single_Paper(pcurrent->Paperhead);
	printf("\n");
	Print_Single_Proj(pcurrent->Projhead);
	printf("\n");
	//printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t该学生总的有效加分绩点：%.2f\n", pcurrent->Bonusponit);
	printf("\n");
	system("pause");
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 19 打印 一个人 所有的比赛项目 (从人的角度打印）
void Print_Single_Comp(CompNote* Head)
{
	if (Head == NULL)
	{
		printf("\n\t\t<竞赛类> : 无\n");
		return;
	}
	printf("\n\t\t<竞赛类>\n\n");
	//printf("___________________________________________________________________________________________________________________________________________\n");
	//printf("序号 \t竞赛项目名称 \t获奖人和顺序 \t竞赛类型 \n 获奖等级 \t主办单位 \t获奖时间 \t审核状态 \t应加绩点\n");
	//printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		CompNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t序号: %d\n", cnt);
			cnt++;
			printf("\t\t\t竞赛项目名称: \t%s\n", pcurrent->CompName);
			printf("\t\t\t获奖人/顺序: \t%s\n", pcurrent->Winers);
			printf("\t\t\t竞赛类型: \t%c\n", pcurrent->ABC);
			printf("\t\t\t获奖等级: \t%d\n", pcurrent->AwardGrade);
			printf("\t\t\t主办单位: \n%s\n", pcurrent->Sponsor);
			printf("\t\t\t获奖时间: \t%s\n", pcurrent->Time);
			//printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
			else if (pcurrent->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
			else { printf("\t\t\t审核状态: \t否决\n"); }
			printf("\t\t\t应加绩点: \t%.2f\n", pcurrent->Ponit);
			printf("\n");

			//指针移动到下一个元素的首地址
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("无\n"); }
}
/**************************************************************************************************************************/

// 20 打印 一个人 所有的论文项目
void Print_Single_Paper(PaperNote* Head)
{
	if (Head == NULL)
	{
		printf("\n\t\t<论文类> ：无\n");
		return;
	}
	printf("\n\t\t<论文类>\n\n");
	//printf("_____________________________________________________________________________________________________________________________________________________\n");
	//printf("同类序号\t论文名称\t所有作者和顺序\t期刊名称/会议名称\t发表时间\t卷/期\t论文号\t页码范围\t审核状态\t应加绩点\n");
	//printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		PaperNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t序号: %d\n", cnt);
			cnt++;
			printf("\t\t\t论文名称: \t%s\n", pcurrent->PaperName);
			printf("\t\t\t所有作者/顺序: \t%s\n", pcurrent->Writers);
			printf("\t\t\t期刊名称/会议名称: \t%s\n", pcurrent->Journal_Conference);
			printf("\t\t\t发表时间: \t%s\n", pcurrent->Time);
			printf("\t\t\t卷/期: \t%s\n", pcurrent->Volume_Page[0]);
			printf("\t\t\t论文号: \t%s\n", pcurrent->Volume_Page[1]);
			printf("\t\t\t页码范围: \t%s\n", pcurrent->Volume_Page[2]);
			//printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
			else if (pcurrent->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
			else { printf("\t\t\t审核状态: \t否决\n"); }
			printf("\t\t\t应加绩点: \t%.2f\n", pcurrent->Ponit);
			printf("\n");

			//指针移动到下一个元素的首地址
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("无\n"); }
}
/**************************************************************************************************************************/

// 21 打印 一个人 所有的结题项目
void Print_Single_Proj(ProjNote* Head)
{
	if (Head == NULL)
	{
		printf("\n\t\t<项目类> : 无\n");
		return;
	}
	printf("\n\t\t<项目类>\n");
	//printf("____________________________________________________________________________________________________________________________________________________________________\n");
	//printf("同类序号\t项目名称\t所有成员和顺序\t指导教师姓名\t立项时间\t结项时间\t项目编号\t责任性质\t审核状态\t应加绩点\n");
	//printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		ProjNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t序号: %d\n", cnt);
			cnt++;
			printf("\t\t\t项目名称: \t%s\n", pcurrent->ProjName);
			printf("\t\t\t所有成员和顺序: \t%s\n", pcurrent->Members);
			printf("\t\t\t指导教师姓名: \t%s\n", pcurrent->Advisor);
			printf("\t\t\t立项时间: \t%s\n", pcurrent->Start_time);
			printf("\t\t\t结项时间: \t%s\n", pcurrent->Finish_time);
			printf("\t\t\t项目编号: \t%s\n", pcurrent->ProjNum);
			//printf("\t\t\t责任性质: \t%d\n", pcurrent->Role);
			if (pcurrent->Role == 1) { printf("\t\t\t责任性质: \t负责人\n"); }
			else if (pcurrent->Role == 2) { printf("\t\t\t责任性质: \t成员\n"); }
			else { printf("\t\t\t责任性质: \t其他\n"); }
			//printf("\t\t\t审核状态: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) { printf("\t\t\t审核状态: \t批准\n"); }
			else if (pcurrent->Attribute == 2) { printf("\t\t\t审核状态: \t审核中\n"); }
			else { printf("\t\t\t审核状态: \t否决\n"); }
			printf("\t\t\t应加绩点: \t%.2f\n", pcurrent->Ponit);
			printf("\n");
			//指针移动到下一个元素的首地址
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("无\n"); }
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 22 打印 比赛项目 的所有加分内容 （从三大类项目的角度打印）
void Display_All_CompNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next是第一个BonusNote数据节点 
	while (pcurrent != NULL) {
		if (pcurrent->Comphead == NULL) { ; }
		else
		{
			Print_Single_Comp(pcurrent->Comphead);
			printf("\n");
		}
		//指针移动到下一个元素的首地址
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

// 23 打印 论文项目 的所有加分内容
void Display_All_PaperNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next是第一个BonusNote数据节点 
	while (pcurrent != NULL) {
		if (pcurrent->Paperhead == NULL) { ; }
		else
		{
			Print_Single_Paper(pcurrent->Paperhead);
			printf("\n");
		}

		//指针移动到下一个元素的首地址
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

// 24 打印 结题项目 的所有加分内容
void Display_All_ProjNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next是第一个BonusNote数据节点 
	while (pcurrent != NULL) {
		if (pcurrent->Projhead == NULL) { ; }
		else
		{
			Print_Single_Proj(pcurrent->Projhead);
			printf("\n");
		}
		//指针移动到下一个元素的首地址
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 25 打印 所有素质类加分信息
void Display_All_BonusInform(BonusNote* Head)
{
	printf("竞赛类：\n\n");
	Display_All_CompNote(Head);
	system("pause");
	printf("论文类：\n\n");
	Display_All_PaperNote(Head);
	system("pause");
	printf("项目类：\n\n");
	Display_All_ProjNote(Head);
	system("pause");
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
//以下是输入检查函数：
/**************************************************************************************************************************/

// 26 输入+检索 比赛名称
void Comp_Name_Input_Right(char* Compname) {
	char Pattern[20][100] = {
		"中国“互联网 + ”大学生创新创业大赛",
		"“挑战杯”全国大学生课外学术科技作品竞赛",
		"ACM - ICPC国际大学生程序设计竞赛",
		"全国大学生数学建模竞赛",
		"中国高校计算机大赛",
		"全国大学生嵌入式芯片与系统设计竞赛",
		"全国大学生信息安全竞赛",
		"华为ICT大赛",
		"蓝桥杯全国软件和信息技术专业人才大赛",
		"“中国软件杯”大学生软件设计大赛",
		"ESRI杯中国大学生GIS软件开发大赛",
		"美国大学生数学建模竞赛",
		"CCSP大学生计算机系统与程序设计竞赛",
		"全国大学生物联网设计竞赛",
		"CCPC中国大学生程序设计竞赛",
		"全国大学生信息安全竞赛",
		"“华为杯”中国大学生智能设计竞赛",
		"中国高校计算机大赛",
		"全国高校网安联赛XNUCA",
		"中国大学生计算机博弈大赛"
	};
	while (1) {
		char input[100] = { 0 };
		scanf("%s", input);
		for (int i = 0; i < 20; i++) {
			if (strcmp(input, Pattern[i]) == 0) {
				strcpy(Compname, Pattern[i]);
				return;
			}
		}

		printf("没有这个比赛，请重新输入。\n");
	}
}
/**************************************************************************************************************************/

// 28 输入+检查 'A'/'B'/'C'
void Input_ABC(char* a) {
	bool isValid = false;
	char input = 0;
	while (!isValid) {
		input = _getch();
		printf("%c\n", input);
		input = toupper(input); // 将输入转换为大写字符
		if (input == 'A' || input == 'B' || input == 'C') {
			*a = input;
			isValid = true;
		}
		else {
			printf("输入有误，请重新输入。\n");
		}
	}
}
/**************************************************************************************************************************/

// 29 输入+检索 主办单位名称
void Sponsor_Input_Right(char* Sponsor) {

	char Pattern[20][500] = {
		"教育部、中央网络安全和信息化领导小组办公室、国家发展和改革委员会、工业和信息化部、人力资源社会保障部、环境保护部、农业部、国家知识产权局、国务院侨务办公室、中国科学院、中国工程院、国务院扶贫开发领导小组办公室、共青团中央、省政府",
		"共青团中央、中国科协、教育部和全国学联、地方省级人民政府",
		"美国ICPC基金会",
		"教育部高教司、中国工业与应用数学学会",
		"教育部高等学校计算机类专业教学指导委员会、教育部高等学校软件工程专业教学指导委员会、教育部高等学校大学计算机课程教学指导委员会、全国高等学校计算机教育研究会",
		"中国电子学会",
		"教育部高等学校信息安全类专业教学指导委员会",
		"华为公司",
		"工业和信息化部人才交流中心",
		"工业和信息化部教育部 江苏省人民政府",
		"中国测绘地理信息学会",
		"美国数学及其应用联合会",
		"中国计算机学会",
		"教育部高等学校计算机类教学指导委员会",
		"教育部计算机专业高等教学指导委员会",
		"教育部高等学校信息安全专业教学指导委员会",
		"中国人工智能学会",
		"教育部高等学校计算机类专业教学指导委员会，教育部高等学校软件工程专业教学指导委员会，教育部高等学校大学计算机课程教学指导委员会",
		"中国科学院、中国网络空间安全协会、深圳市人民政府",
		"中国人工智能学会",
	};
	while (1) {
		char input[500] = { 0 };
		scanf("%s", input);

		for (int i = 0; i < 20; i++) {
			if (strcmp(input, Pattern[i]) == 0) {
				strcpy(Sponsor, Pattern[i]);
				return;
			}
		}

		printf("没有这个主办单位，请重新输入。\n");
	}
}
/**************************************************************************************************************************/

// 30 输入+检查 时间
void Time_Input_Right(char* Time) {
	bool isValid = false;
	while (!isValid) {
		printf("(日期格式：YYYY-MM-DD）\n");
		memset(Time, 0, 30);
		scanf("%s", Time);
		int i = 0;
		// 确保输入的字符串长度为10，即“YYYY-MM-DD”格式
		if (strlen(Time) == 10) {
			// 确保输入的字符符合“YYYY-MM-DD”格式
			if (Time[4] == '-' && Time[7] == '-') {

				for (i = 0; i <= 9; i++) {
					if (i == 4 || i == 7) {
						continue;
					}
					else {
						if (!isdigit(Time[i])) {
							break;
						}
					}
				}
				if (i == 10) { isValid = true; }

			}
		}
		if (!isValid) {
			printf("日期格式错误，请重新输入。\n");
		}
	}
}
/**************************************************************************************************************************/

// 31 输入+检索 期刊名称/会议名称
void Journal_Input_Right(char* Journal) {
	char Pattern[15][200] = {
		"业界公认学科综合顶级期刊",
		"CCF-A期刊",
		"CCF-A会议长文",
		"CCF-B会议的最佳论文/最佳学生论文",
		"CCF-B期刊论文",
		"中科院期刊分区一区论文",
		"CCFC会议的最佳论文/最佳学生论文",
		"CCF-C期刊论文",
		"CCF-B会议长文",
		"中科院期刊分区二区论文",
		"计算机学报、软件学报发表的学术论文",
		"影响因子非0的SCI检索期刊论文",
		"CCF-C会议长文",
		"中国科学：信息科学、计算机研究与发展、计算机辅助设计与图形学学报、电子学报中文版、自动化学报发表的学术论文",
		"EI检索期刊"
	};
	while (1) {
		char input[200] = { 0 };
		scanf("%s", input);

		for (int i = 0; i < 15; i++) {
			if (strcmp(input, Pattern[i]) == 0) {
				strcpy(Journal, Pattern[i]);
				return;
			}
		}

		printf("没有这个期刊/会议，请重新输入。\n");
	}
}
/**************************************************************************************************************************/

// 32 输入+检查 卷/期/论文号/页码范围
void Volume_Page_Input_Right(char Volume_Page[4][50])
{    //char(*Volume_Page_Input_Right(char Volume_Page[4][50]))[50] {     //char (*(*F(char (*param)[50])))[4];

	int flag_paper_number = 0;
	int flag_page_range = 0;

	while (!(flag_paper_number && flag_page_range)) {
		// 重新输入或者修改提示信息根据需要修改

		printf("请按照“卷：*，期：*”的格式，输入正确的卷和期信息（其中*号填不仅限于一位的数字）：\n");
		memset(Volume_Page[0], 0, 50);
		scanf("%s", Volume_Page[0]);

		if (!flag_paper_number) {
			printf("请按照“AB-123-4567890”的格式，输入正确的论文号（每个大写字母和数字都可以替换，位数固定）：\n");
			memset(Volume_Page[1], 0, 50);
			scanf("%s", Volume_Page[1]);
			int i = 0;
			for (i = 0; i < 14; i++) {
				if (i >= 0 && i <= 1) {
					if (!isupper(Volume_Page[1][i])) {
						break;
					}
				}
				else if ((i >= 3 && i <= 5) || (i >= 7 && i <= 13)) {
					if (!isdigit(Volume_Page[1][i])) {
						break;
					}
				}
				else {
					if (Volume_Page[1][i] != '-') {
						break;
					}
				}
			}
			if (i == 14 && strlen(Volume_Page[1]) == 14) {
				flag_paper_number = 1;
			}
			else {
				printf("论文号输入错误。\n\n");
				continue;
			}
		}

		if (!flag_page_range) {
			printf("请按照“*-*”的格式，输入正确的页码范围（其中*号填不仅限于一位的数字）：\n");
			memset(Volume_Page[2], 0, 50);
			scanf("%s", Volume_Page[2]);
			int i = 0;
			for (i = 0; i < strlen(Volume_Page[2]); i++)
			{
				if (!isdigit(Volume_Page[2][i])) {
					break;
				}
			}
			if (i == strlen(Volume_Page[2])) {
				flag_page_range = 1;
			}
			else {
				printf("页码范围输入错误。\n\n");
				continue;
			}
		}
	}
}
/**************************************************************************************************************************/

// 34 输入+检查 项目编号
void Pronum_Input_Right(char* ProjNum) {
	bool Flag = false;
	while (!Flag) {
		int i = 0;
		memset(ProjNum, 0, 30);
		scanf("%s", ProjNum);
		for (i = 0; i < strlen(ProjNum); i++) {

			if (isalnum(ProjNum[i])) {
				continue;
			}
			else {
				printf("输入有误，请重新输入：\n");
				break;
			}
		}
		if (i == strlen(ProjNum)) { Flag = true; }
	}
}
/**************************************************************************************************************************/


/**************************************************************************************************************************/

// 35 数字ID转成字符串账号
void Int_To_Str(int number, char* result)
{
	result[0] = (number / 10000000) % 10 + '0';
	result[1] = (number / 1000000) % 10 + '0';
	result[2] = (number / 100000) % 10 + '0';
	result[3] = (number / 10000) % 10 + '0';
	result[4] = (number / 1000) % 10 + '0';
	result[5] = (number / 100) % 10 + '0';
	result[6] = (number / 10) % 10 + '0';
	result[7] = number % 10 + '0';
	result[8] = '\0';  // 添加字符串结束符
}