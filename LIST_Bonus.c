//Ŀǰֻ�����ġ�����������ģ�����ݡ�
// LIST_BonusDev_Paper.txt  ���ϵͳ�������ݣ�����Ϊ�����ļ���
// LIST_newBonusDev_Paper.txt   ���Ԥ������������ӵ����ݡ�
// comp.txt  ������õ����ݲݸ�
// ����������������Ŀ��.txt�ļ�����ͬ��
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

// 1 �״� ���ļ���¼�� ����������ӷ���Ϣ
BonusNote* Start_Logging_bonusFile(void)
{
	CompNote* Comparr[50] = { 0 };
	PaperNote* Paperarr[50] = { 0 };
	ProjNote* Projarr[50] = { 0 };
	
	BonusNote* Head = (BonusNote*)malloc(sizeof(BonusNote));//����ѧ���������ͷ��㲻�����κ����ݡ�
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
		printf("�ļ���ʧ�ܣ���!\n");
		exit(0);
	}

	BonusNote* prrev = Head; //β����
	BonusNote* newnode = NULL;

	for (i = 0; !feof(fp); i++)
	{
		char line[100]; // ���ڶ�ȡÿ�еĻ�����

		// ��ȡһ������
		if (fgets(line, sizeof(line), fp) == NULL)
			break; // �ļ��������ȡ��������ѭ��

		// �ж��Ƿ�Ϊ����
		if (strlen(line) <= 1) // ֻ�������з����г���Ϊ1
			break; // �ļ�ĩβΪ���У�����ѭ��

		newnode = (BonusNote*)malloc(sizeof(BonusNote)); //Ϊÿ��¼����˺ſ��ٶ�̬�ڴ档
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
	//���ӷ���Ϣ������.txt�ļ��ж��� 
	Logging_CompNote(Head, Comparr, 1);
	Logging_PaperNote(Head, Paperarr, 1);
	Logging_ProjNote(Head, Projarr, 1);
	return Head;
}
/**************************************************************************************************************************/

//����ѧ���ڵ㣬����int���͵�ѧ�ţ�char���͵�����������һ���µ�ѧ���ڵ�
void Add_BonusNote_Node(BonusNote* Head, int ID, char Name[])
{
	char Acc[20]={0};
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

void Save_List_To_bonusFile(BonusNote* Head)//  ������ �ӷ���Ŀ ������ļ�
{
	Save_CompList_ToFile(Head);//  ������ ������Ŀ ������ļ�
	Save_PaperList_ToFile(Head);//  ������ ������Ŀ ������ļ�
	Save_ProjList_ToFile(Head);//  ������ ������Ŀ ������ļ�
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
void Add_Mutiple_CompNote(BonusNote* Head)// 2 ������� ���˵ı�����Ŀ
{
	CompNote* newComparr[50] = { 0 };
	Logging_CompNote(Head, newComparr, 0);
}
void Add_Mutiple_PaperNote(BonusNote* Head)// 3 ������� ���˵�������Ϣ
{
	PaperNote* newPaperarr[50] = { 0 };
	Logging_PaperNote(Head, newPaperarr, 0);
}
void Add_Mutiple_ProjNote(BonusNote* Head)// 4 ������� ���˵Ĺ��Ҽ����������Ŀ��Ϣ
{ 
	ProjNote* newProjarr[50] = { 0 };
	Logging_ProjNote(Head, newProjarr, 0);
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
// 5 ¼�뵥�� ������Ŀ ��ĳ��
BonusNote* Add_Single_CompNote(BonusNote* Head, char Acc[], char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}
	CompNote* newnode = (CompNote*)malloc(sizeof(CompNote));//�����½ڵ㡣
	newnode->Next = NULL;

	strcpy(newnode->Accountnum, pcurrent->Accountnum);
	printf("\n���뾺����Ŀ����:\n");
	Comp_Name_Input_Right(newnode->CompName);//�����ѡ
	printf("\n��������˺�˳������֮�����öٺŸ�����\n");//(��������)
	scanf("%s",newnode->Winers);//ͨ��ָ��ı����ݡ�
	printf("\n�����뾺�����ͣ�\n");
	Input_ABC(&(newnode->ABC));
	printf("\n������񽱵ȼ���\n");
	newnode->AwardGrade = Input_1toNum(3);
	printf("���������쵥λ��\n");
	Sponsor_Input_Right(newnode->Sponsor);
	printf("\n�������ʱ�䣺");
	Time_Input_Right(newnode->Time);
	if (Tea_Stu == 't')//����Ǹ���Ա¼��
	{
		printf("������������ԣ�\n");//��ֱ������������ԣ�1/2/3������
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }//�����ѧ��¼�룬�������ֻ����2����������С�

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
		while (pcurrent2->Next != NULL) {//�ҵ�β���
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}

	if (newnode->Attribute == 1) {//����������Ϊ����׼��
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�������ѧ���ӷּ���
	}
	if (Tea_Stu == 't')//����Ǹ���Ա¼��
	{
		printf("\nΪ%s��Ӿ�����ӷ���Ŀ�ɹ���\n\n", pcurrent->Name);
	}
	else {
		printf("\n����ɹ��������ĵȴ���ʦ���ͨ����\n\n");
	}

	Display_All_CompNote(Head);//��ɾ
	return Head;
}
/**************************************************************************************************************************/

// 6 ¼�뵥�� ������Ŀ ��ĳ��
BonusNote* Add_Single_PaperNote(BonusNote* Head, char Acc[],char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}
	PaperNote* newnode = (PaperNote*)malloc(sizeof(PaperNote));//�����½ڵ㡣
	newnode->Next = NULL;

	strcpy(newnode->Accountnum, pcurrent->Accountnum);//ok
	printf("�������ڿ�����/�������ƣ�\n");
	Journal_Input_Right(newnode->Journal_Conference);//�����ѡ
	printf("\n������������:\n");
	scanf("%s", newnode->PaperName);
	//char new[50] = { 0 };
	//strncpy(new, newnode->PaperName, strlen(newnode->PaperName) - 1);
	printf("\n�������ߺ�˳������֮�����öٺŸ�����\n");//(��������)
	scanf("%s", newnode->Writers); //ͨ��ָ��ı����ݡ�
	printf("\n�����뷢��ʱ��,");
	Time_Input_Right(newnode->Time);//ok
	printf("��/��/���ĺ�/ҳ�뷶Χ��\n");
	Volume_Page_Input_Right(newnode->Volume_Page);//ok
	if (Tea_Stu == 't')
	{
		printf("������������ԣ�\n");
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }
	if (strcmp(newnode->Journal_Conference, "ҵ�繫��ѧ���ۺ϶����ڿ�") == 0)
	{
		newnode->Ponit = 0.40;
	}
	else if ((strcmp(newnode->Journal_Conference, "CCF - A�ڿ�") == 0) || (strcmp(newnode->Journal_Conference, "CCF-A���鳤��") == 0) || (strcmp(newnode->Journal_Conference, "CCF-B������������/���ѧ������") == 0))
	{
		newnode->Ponit = 0.20;
	}
	else if ((strcmp(newnode->Journal_Conference, "CCF-B�ڿ�����") == 0) || (strcmp(newnode->Journal_Conference, "�п�Ժ�ڿ�����һ������") == 0) || (strcmp(newnode->Journal_Conference, "CCFC������������/���ѧ������") == 0))
	{
		newnode->Ponit = 0.10;
	}
	else if ((strcmp(newnode->Journal_Conference, "Ӱ�����ӷ�0��SCI�����ڿ�����") == 0) || (strcmp(newnode->Journal_Conference, "CCF-C ���鳤��") == 0) || (strcmp(newnode->Journal_Conference, "�й���ѧ����Ϣ��ѧ��������о��뷢չ����������������ͼ��ѧѧ��������ѧ�����İ桢�Զ���ѧ�������ѧ������") == 0))
	{
		newnode->Ponit = 0.02;
	}
	else if (strcmp(newnode->Journal_Conference, "EI�����ڿ�") == 0)
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
		while (pcurrent2->Next != NULL) {//�ҵ�β���
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}
	if (newnode->Attribute == 1) {//����������Ϊ����׼��
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�������ѧ���ӷּ���
	}
	if (Tea_Stu == 't')//����Ǹ���Ա¼��
	{
		printf("\nΪ%s���������ӷ���Ŀ�ɹ���\n\n", pcurrent->Name);
	}
	else {
		printf("\n����ɹ��������ĵȴ���ʦ���ͨ����\n\n");
	}

	Display_All_PaperNote(Head);//��ɾ

	return Head;
}
/**************************************************************************************************************************/

// 7 ¼�뵥�� ������Ŀ ��ĳ��
BonusNote* Add_Single_ProjNote(BonusNote* Head, char Acc[], char Tea_Stu)
{
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}
	ProjNote* newnode = (ProjNote*)malloc(sizeof(ProjNote));//�����½ڵ㡣
	newnode->Next = NULL;

	strcpy(newnode->Accountnum, pcurrent->Accountnum);//ok

	printf("\n������Ŀ���ƣ�");
	//getchar();
	scanf("%s",newnode->ProjName);
	printf("���г�Ա��˳�򣺣�����֮�����öٺŸ�����\n");//(��������)
	
	scanf("%s",newnode->Members);//ͨ��ָ��ı����ݡ�
	printf("ָ����ʦ������\n");
	scanf("%s",newnode->Advisor);
	printf("����ʱ�䣺\n");
	Time_Input_Right(newnode->Start_time);//ok
	printf("����ʱ�䣺\n");
	Time_Input_Right(newnode->Finish_time);//ok
	printf("��Ŀ��ţ�\n");
	Pronum_Input_Right(newnode->ProjNum);//ֻ�����ּ���ĸ���ɣ�˳�򲻶�
	printf("�������������ʣ�\n");
	newnode->Role = Input_1toNum(3);//ok
	if (Tea_Stu == 't')
	{
		printf("������������ԣ�\n");
		newnode->Attribute = Input_1toNum(3);//ok
	}
	else { newnode->Attribute = 2; }

	if (newnode->Role == 1) { newnode->Ponit = 0.10; }
	else { newnode->Ponit = 0.05; }//������newnode->Role == 3����������ӷ֣�����Ϊ������ӷ���Ŀ��

	ProjNote* pcurrent2 = pcurrent->Projhead;
	if (pcurrent2 == NULL) {
		pcurrent->Projhead = newnode;
	}
	else {
		while (pcurrent2->Next != NULL) {//�ҵ�β���
			pcurrent2 = pcurrent2->Next;
		}
		pcurrent2->Next = newnode;
	}
	if (newnode->Attribute == 1) {//����������Ϊ����׼��
		pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�������ѧ���ӷּ���
	}
	if (Tea_Stu == 't')//����Ǹ���Ա¼��
	{
		printf("\nΪ%s��ӽ�����Ŀ��ӷ���Ŀ�ɹ���\n\n", pcurrent->Name);
	}
	else {
		printf("\n����ɹ��������ĵȴ���ʦ���ͨ����\n\n");
	}

	Display_All_PaperNote(Head);//��ɾ

	return Head;
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 8 ���ļ�������¼�� ���˵ı�����Ŀ
void Logging_CompNote(BonusNote* Head, CompNote* Comparr[], int Atri)
{
	int i = 0;
	FILE* fp1;
	if (Atri) {
		if ((fp1 = fopen(FILE_COMP, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	else {
		if ((fp1 = fopen(FILE_COMP_NEW, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp1); i++)
	{
		char line[1000]; // ���ڶ�ȡÿ�еĻ�����

		// ��ȡһ������
		if (fgets(line, sizeof(line), fp1) == NULL)
			break; // �ļ��������ȡ��������ѭ��

		// �ж��Ƿ�Ϊ����
		if (strlen(line) <= 1) // ֻ�������з����г���Ϊ1
			break; // �ļ�ĩβΪ���У�����ѭ��

		Comparr[i] = (CompNote*)malloc(sizeof(CompNote));
		Comparr[i]->Next = NULL;
		memset(Comparr[i]->Accountnum, 0, 20);
		memset(Comparr[i]->CompName, 0, 50);
		memset(Comparr[i]->Winers, 0, 150);
		memset(Comparr[i]->Sponsor, 0, 1000);
		memset(Comparr[i]->Time, 0, 30);

		sscanf(line, "%s\t%s\t%s\t%c\t%d\t%s\t%s\t%d\t%f\t", Comparr[i]->Accountnum, Comparr[i]->CompName, Comparr[i]->Winers, &Comparr[i]->ABC, &Comparr[i]->AwardGrade, Comparr[i]->Sponsor, Comparr[i]->Time, &Comparr[i]->Attribute, &Comparr[i]->Ponit);

		//����������
		BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
		while (!(strcmp(pcurrent->Accountnum, Comparr[i]->Accountnum) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
			pcurrent = pcurrent->Next;
		}

		CompNote* pcurrent2 = pcurrent->Comphead;
		if (pcurrent2 == NULL) {
			pcurrent->Comphead = Comparr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//�ҵ�β���
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Comparr[i];
		}

		if (Comparr[i]->Attribute == 1) {//����������Ϊ����׼��
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�������ѧ���ӷּ���
		}
	}
	fclose(fp1);
}
/**************************************************************************************************************************/

// 9 ���ļ�������¼�� ���˵�������Ϣ
void Logging_PaperNote(BonusNote* Head, PaperNote* Paperarr[], int Atri)
{
	int i = 0;
	FILE* fp2;
	if (Atri) {
		if ((fp2 = fopen(FILE_PAPER, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	else {
		if ((fp2 = fopen(FILE_PAPER_NEW, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp2); i++)
	{
		char line[1000]; // ���ڶ�ȡÿ�еĻ�����

		// ��ȡһ������
		if (fgets(line, sizeof(line), fp2) == NULL)
			break; // �ļ��������ȡ��������ѭ��

		// �ж��Ƿ�Ϊ����
		if (strlen(line) <= 1) // ֻ�������з����г���Ϊ1
			break; // �ļ�ĩβΪ���У�����ѭ��

		Paperarr[i] = (PaperNote*)malloc(sizeof(PaperNote));
		Paperarr[i]->Next = NULL;
		memset(Paperarr[i]->Accountnum, 0, 20);
		memset(Paperarr[i]->PaperName, 0,50);
		memset(Paperarr[i]->Writers, 0, 150);
		memset(Paperarr[i]->Journal_Conference, 0, 150);
		memset(Paperarr[i]->Time, 0, 30);
		memset(Paperarr[i]->Volume_Page[0], 0, 50);
		memset(Paperarr[i]->Volume_Page[1], 0, 50);
		memset(Paperarr[i]->Volume_Page[2], 0, 50);

		sscanf(line, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%f\t", Paperarr[i]->Accountnum, Paperarr[i]->PaperName, Paperarr[i]->Writers, Paperarr[i]->Journal_Conference, Paperarr[i]->Time, Paperarr[i]->Volume_Page[0], Paperarr[i]->Volume_Page[1], Paperarr[i]->Volume_Page[2], &Paperarr[i]->Attribute, &Paperarr[i]->Ponit);

		//����������
		BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
		while ( /*pcurrent != NULL &&*/ !(strcmp(pcurrent->Accountnum, Paperarr[i]->Accountnum) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
			pcurrent = pcurrent->Next;
		}

		PaperNote* pcurrent2 = pcurrent->Paperhead;
		if (pcurrent2 == NULL) {
			pcurrent->Paperhead = Paperarr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//�ҵ�β���
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Paperarr[i];
		}

		if (Paperarr[i]->Attribute == 1) {//����������Ϊ����׼��
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�������ѧ���ӷּ���
		}
	}
	fclose(fp2);
}
/**************************************************************************************************************************/

// 10 ���ļ�������¼�� ���˽�����Ŀ��Ϣ
void Logging_ProjNote(BonusNote* Head, ProjNote* Projarr[], int Atri)
{
	int i = 0;
	FILE* fp3;
	if (Atri) {
		if ((fp3 = fopen(FILE_PROJ, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	else {
		if ((fp3 = fopen(FILE_PROJ_NEW, "r+")) == NULL)
		{
			printf("�ļ���ʧ�ܣ���!\n");
			exit(0);
		}
	}
	for (i = 0; !feof(fp3); i++)
	{
		char line[1000]; // ���ڶ�ȡÿ�еĻ�����

		// ��ȡһ������
		if (fgets(line, sizeof(line), fp3) == NULL)
			break; // �ļ��������ȡ��������ѭ��

		// �ж��Ƿ�Ϊ����
		if (strlen(line) <= 1) // ֻ�������з����г���Ϊ1
			break; // �ļ�ĩβΪ���У�����ѭ��

		Projarr[i] = (ProjNote*)malloc(sizeof(ProjNote));
		Projarr[i]->Next = NULL;
		memset(Projarr[i]->Accountnum, 0, 20);
		memset(Projarr[i]->ProjName, 0, 50);
		memset(Projarr[i]->Members, 0, 150);
		memset(Projarr[i]->Advisor, 0, 30);
		memset(Projarr[i]->Start_time, 0, 30);
		memset(Projarr[i]->Finish_time, 0, 30);
		memset(Projarr[i]->ProjNum, 0, 30);
		
		sscanf(line, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%f\t", Projarr[i]->Accountnum, Projarr[i]->ProjName, Projarr[i]->Members, Projarr[i]->Advisor, Projarr[i]->Start_time, Projarr[i]->Finish_time, Projarr[i]->ProjNum, &Projarr[i]->Role ,&Projarr[i]->Attribute, &Projarr[i]->Ponit);
		//����������
		BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
		while (!(strcmp(pcurrent->Accountnum, Projarr[i]->Accountnum) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
			pcurrent = pcurrent->Next;
		}

		ProjNote* pcurrent2 = pcurrent->Projhead;
		if (pcurrent2 == NULL) {
			pcurrent->Projhead = Projarr[i];
		}
		else {
			while (pcurrent2->Next != NULL) {//�ҵ�β���
				pcurrent2 = pcurrent2->Next;
			}
			pcurrent2->Next = Projarr[i];
		}
		
		if (Projarr[i]->Attribute == 1) {//����������Ϊ����׼��
			pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, pcurrent->Accountnum);//�������ѧ���ӷּ���
		}
	}
	fclose(fp3);
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 11������ ������Ŀ ������ļ�
void Save_CompList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_COMP, "w");  // ��д��ģʽ���ļ������ļ��������򴴽���������������ļ�����
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return;
	}

	BonusNote* current = Head->Next;  // ������ͷ����ʼ����
	while (current != NULL) {
		CompNote* pcurrent2 = current->Comphead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%c\t%d\t%s\t%s\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->CompName, pcurrent2->Winers, pcurrent2->ABC, pcurrent2->AwardGrade, pcurrent2->Sponsor, pcurrent2->Time, pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // ��������һ���ڵ�
		}
		current = current->Next;
	}
	fclose(file);  // �ر��ļ�
}
/**************************************************************************************************************************/
// 12 ������ ������Ŀ ������ļ�

void Save_PaperList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_PAPER, "w");  // ��д��ģʽ���ļ������ļ��������򴴽���������������ļ�����
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return;
	}

	BonusNote* current = Head->Next;  // ������ͷ����ʼ����
	while (current != NULL) {
		PaperNote* pcurrent2 = current->Paperhead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->PaperName, pcurrent2->Writers, pcurrent2->Journal_Conference, pcurrent2->Time, pcurrent2->Volume_Page[0], pcurrent2->Volume_Page[1], pcurrent2->Volume_Page[2], pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // ��������һ���ڵ�
		}
		current = current->Next;
	}
	fclose(file);  // �ر��ļ�
}
/**************************************************************************************************************************/
// 13 ������ ������Ŀ ������ļ�

void Save_ProjList_ToFile(BonusNote* Head)
{
	FILE* file = fopen(FILE_PROJ, "w");  // ��д��ģʽ���ļ������ļ��������򴴽���������������ļ�����
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return;
	}

	BonusNote* current = Head->Next;  // ������ͷ����ʼ����
	while (current != NULL) {
		ProjNote* pcurrent2 = current->Projhead;

		while (pcurrent2 != NULL) {
			fprintf(file, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%.2f\n", pcurrent2->Accountnum, pcurrent2->ProjName, pcurrent2->Members, pcurrent2->Advisor, pcurrent2->Start_time, pcurrent2->Finish_time, pcurrent2->ProjNum, pcurrent2->Role ,pcurrent2->Attribute, pcurrent2->Ponit);
			pcurrent2 = pcurrent2->Next;  // ��������һ���ڵ�
		}
		current = current->Next;
	}
	fclose(file);  // �ر��ļ�
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 14 �޸� ���˵ı�����Ŀ �ӷ�״̬
//BonusNote* Modify_CompAttr(BonusNote* Head, char Acc[], char Compname[])
//{
//	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
//	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
//		pcurrent = pcurrent->Next;
//	}
//	CompNote* pcurrent2 = pcurrent->Comphead;
//	while (!(strcmp(pcurrent2->CompName, Compname) == 0)) {//�ҵ���Ӧ�������ơ���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βεľ�������Compname��Ȼ�����������У�
//		pcurrent2 = pcurrent2->Next;
//	}
//	printf("��ѡ�����Ŀ�Ƿ����ͨ����\n");
//	printf("1����׼\n");
//	printf("2�������\n");
//	printf("3�����\n");
//	pcurrent2->Attribute = Input_1toNum(3);
//	pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�����ѧ���ӷּ���
//	return Head;
//}
/**************************************************************************************************************************/

// 15 �޸� ���˵�������Ŀ �ӷ�״̬
//BonusNote* Modify_PaperAttr(BonusNote* Head, char Acc[], char Papername[])
//{
//	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
//	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
//		pcurrent = pcurrent->Next;
//	}
//	PaperNote* pcurrent2 = pcurrent->Paperhead;
//	while (!(strcmp(pcurrent2->PaperName, Papername) == 0)) {//�ҵ���Ӧ�������ơ���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε���������Papername��Ȼ�����������У�
//		pcurrent2 = pcurrent2->Next;
//	}
//	pcurrent2->Attribute = Input_1toNum(3);
//	pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�����ѧ���ӷּ���
//	return Head;
//}
/**************************************************************************************************************************/

// 16 �޸� ���˵Ľ�����Ŀ �ӷ�״̬
//BonusNote* Modify_ProjAttr(BonusNote* Head, char Acc[], char Projname[])
//{
//	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
//	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
//		pcurrent = pcurrent->Next;
//	}
//	ProjNote* pcurrent2 = pcurrent->Projhead;
//	while (!(strcmp(pcurrent2->ProjName, Projname) == 0)) {//�ҵ���Ӧ��Ŀ���ơ���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε���Ŀ����Projname��Ȼ�����������У�
//		pcurrent2 = pcurrent2->Next;
//	}
//	pcurrent2->Attribute = Input_1toNum(3);
//	pcurrent->Bonusponit = Calcul_Single_Bonusponit(Head, Acc);//�����ѧ���ӷּ���
//	return Head;
//}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 17 ���� ������ ����Ч�ӷּ���
float Calcul_Single_Bonusponit(BonusNote* Head, char Acc[])
{
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	float Bonus_sum = 0.00;
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}
		CompNote* pcurrent2 = pcurrent->Comphead;
		PaperNote* pcurrent3 = pcurrent->Paperhead;
		ProjNote* pcurrent4 = pcurrent->Projhead;
		while (pcurrent2 != NULL) {
			if (pcurrent2->Attribute == 1) { Bonus_sum += pcurrent2->Ponit; }
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

//ͨ���˺Ų���ѧ���ڵ㣬���ظýڵ��ָ��
BonusNote* Find_BonusNote_ByAcc(BonusNote* Head, int ID)
{
	char Acc[20] = { 0 };
	Int_To_Str(ID, Acc);// 36 ����IDת���ַ����˺�
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0) && pcurrent->Next != NULL) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}

	return pcurrent;
}

// 18 ��ӡ һ���� ���еļӷ���Ŀ
void Display_Single_BonusNote(BonusNote* Head, int ID)
{
	system("cls");
	char Acc[20]={ 0 };
	Int_To_Str(ID, Acc);// 36 ����IDת���ַ����˺�
	BonusNote* pcurrent = Head->Next;// Head->next�ǵ�һ��BonusNote���ݽڵ� 
	while (!(strcmp(pcurrent->Accountnum, Acc) == 0)&& pcurrent->Next!=NULL) {//�ҵ���Ӧ�˺š���ǰ��Ӧ�ò�ȡ��ʩ��ʹ�βε��˺�Acc��Ȼ�����������У�
		pcurrent = pcurrent->Next;
	}
	if(pcurrent->Next==NULL)
	{
		printf("δ�ҵ���ѧ����������ӷ���Ϣ��\n");
		Sleep(1000);
		return;
	}
	printf("\n\t\tѧ�ţ�%s\n", pcurrent->Accountnum);
	printf("\n\t\t������%s\n", pcurrent->Name);
	printf("\n");
	Print_Single_Comp(pcurrent->Comphead);
	printf("\n");
	Print_Single_Paper(pcurrent->Paperhead);
	printf("\n");
	Print_Single_Proj(pcurrent->Projhead);
	printf("\n");
	//printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n\t\t��ѧ���ܵ���Ч�ӷּ��㣺%.2f\n", pcurrent->Bonusponit );
	printf("\n");
	system("pause");
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 19 ��ӡ һ���� ���еı�����Ŀ (���˵ĽǶȴ�ӡ��
void Print_Single_Comp(CompNote* Head)
{
	if(Head==NULL)
		{
		printf("\n\t\t<������> : ��\n");
		return;
	}
	printf("\n\t\t<������>\n\n");
	//printf("___________________________________________________________________________________________________________________________________________\n");
	//printf("��� \t������Ŀ���� \t���˺�˳�� \t�������� \n �񽱵ȼ� \t���쵥λ \t��ʱ�� \t���״̬ \tӦ�Ӽ���\n");
	//printf("-------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		CompNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t���: %d\n", cnt);
			cnt++;
			printf("\t\t\t������Ŀ����: \t%s\n", pcurrent->CompName);
			printf("\t\t\t����/˳��: \t%s\n", pcurrent->Winers);
			printf("\t\t\t��������: \t%c\n", pcurrent->ABC);
			printf("\t\t\t�񽱵ȼ�: \t%d\n", pcurrent->AwardGrade);
			printf("\t\t\t���쵥λ: \n%s\n", pcurrent->Sponsor);
			printf("\t\t\t��ʱ��: \t%s\n", pcurrent->Time);
			//printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) {printf("\t\t\t���״̬: \t��׼\n");}
			else if(pcurrent->Attribute==2){printf("\t\t\t���״̬: \t�����\n");}
			else{printf("\t\t\t���״̬: \t���\n");}
			printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent->Ponit);
			printf("\n");

			//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("��\n"); }
}
/**************************************************************************************************************************/

// 20 ��ӡ һ���� ���е�������Ŀ
void Print_Single_Paper(PaperNote* Head)
{
	if(Head==NULL)
		{
		printf("\n\t\t<������> ����\n");
		return;
	}
	printf("\n\t\t<������>\n\n");
	//printf("_____________________________________________________________________________________________________________________________________________________\n");
	//printf("ͬ�����\t��������\t�������ߺ�˳��\t�ڿ�����/��������\t����ʱ��\t��/��\t���ĺ�\tҳ�뷶Χ\t���״̬\tӦ�Ӽ���\n");
	//printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		PaperNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t���: %d\n", cnt);
			cnt++;
			printf("\t\t\t��������: \t%s\n", pcurrent->PaperName);
			printf("\t\t\t��������/˳��: \t%s\n", pcurrent->Writers);
			printf("\t\t\t�ڿ�����/��������: \t%s\n", pcurrent->Journal_Conference);
			printf("\t\t\t����ʱ��: \t%s\n", pcurrent->Time);
			printf("\t\t\t��/��: \t%s\n", pcurrent->Volume_Page[0]);
			printf("\t\t\t���ĺ�: \t%s\n", pcurrent->Volume_Page[1]);
			printf("\t\t\tҳ�뷶Χ: \t%s\n", pcurrent->Volume_Page[2]);
			//printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) {printf("\t\t\t���״̬: \t��׼\n");}
			else if(pcurrent->Attribute==2){printf("\t\t\t���״̬: \t�����\n");}
			else{printf("\t\t\t���״̬: \t���\n");}
			printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent->Ponit);
			printf("\n");

			//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("��\n"); }
}
/**************************************************************************************************************************/

// 21 ��ӡ һ���� ���еĽ�����Ŀ
void Print_Single_Proj(ProjNote* Head)
{
	if(Head==NULL)
		{
		printf("\n\t\t<��Ŀ��> : ��\n");
		return;
	}
	printf("\n\t\t<��Ŀ��>\n");
	//printf("____________________________________________________________________________________________________________________________________________________________________\n");
	//printf("ͬ�����\t��Ŀ����\t���г�Ա��˳��\tָ����ʦ����\t����ʱ��\t����ʱ��\t��Ŀ���\t��������\t���״̬\tӦ�Ӽ���\n");
	//printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	if (Head != NULL) {
		int i = 0;
		int cnt = 1;
		ProjNote* pcurrent = Head;
		while (pcurrent != NULL) {
			printf("\t\t\t���: %d\n", cnt);
			cnt++;
			printf("\t\t\t��Ŀ����: \t%s\n", pcurrent->ProjName);
			printf("\t\t\t���г�Ա��˳��: \t%s\n", pcurrent->Members);
			printf("\t\t\tָ����ʦ����: \t%s\n", pcurrent->Advisor);
			printf("\t\t\t����ʱ��: \t%s\n", pcurrent->Start_time);
			printf("\t\t\t����ʱ��: \t%s\n", pcurrent->Finish_time);
			printf("\t\t\t��Ŀ���: \t%s\n", pcurrent->ProjNum);
			//printf("\t\t\t��������: \t%d\n", pcurrent->Role);
			if (pcurrent->Role == 1) {printf("\t\t\t��������: \t������\n");}
			else if(pcurrent->Role==2){printf("\t\t\t��������: \t��Ա\n");}
			else{printf("\t\t\t��������: \t����\n");}
			//printf("\t\t\t���״̬: \t%d\n", pcurrent->Attribute);
			if (pcurrent->Attribute == 1) {printf("\t\t\t���״̬: \t��׼\n");}
			else if(pcurrent->Attribute==2){printf("\t\t\t���״̬: \t�����\n");}
			else{printf("\t\t\t���״̬: \t���\n");}
			printf("\t\t\tӦ�Ӽ���: \t%.2f\n", pcurrent->Ponit);
			printf("\n");
			//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
			pcurrent = pcurrent->Next;
		}
	}
	else { printf("��\n"); }
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 22 ��ӡ ������Ŀ �����мӷ����� ������������Ŀ�ĽǶȴ�ӡ��
void Display_All_CompNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next�ǵ�һ��BonusNote���ݽڵ� 
	while (pcurrent != NULL) {
		if (pcurrent->Comphead == NULL) { ; }
		else
		{
			Print_Single_Comp(pcurrent->Comphead);
			printf("\n");
		}
		//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

// 23 ��ӡ ������Ŀ �����мӷ�����
void Display_All_PaperNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next�ǵ�һ��BonusNote���ݽڵ� 
	while (pcurrent != NULL) {
		if (pcurrent->Paperhead == NULL) { ; }
		else
		{
			Print_Single_Paper(pcurrent->Paperhead);
			printf("\n");
		}

		//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

// 24 ��ӡ ������Ŀ �����мӷ�����
void Display_All_ProjNote(BonusNote* Head)
{
	BonusNote* pcurrent = Head->Next;// Head->Next�ǵ�һ��BonusNote���ݽڵ� 
	while (pcurrent != NULL) {
		if (pcurrent->Projhead == NULL) { ; }
		else
		{
			Print_Single_Proj(pcurrent->Projhead);
			printf("\n");
		}
		//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
		pcurrent = pcurrent->Next;
	}
	printf("\n");
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/

// 25 ��ӡ ����������ӷ���Ϣ
void Display_All_BonusInform(BonusNote* Head)
{
	printf("�����ࣺ\n\n");
	Display_All_CompNote(Head);
	printf("�����ࣺ\n\n");
	Display_All_PaperNote(Head);
	printf("��Ŀ�ࣺ\n\n");
	Display_All_ProjNote(Head);
}
/**************************************************************************************************************************/

/**************************************************************************************************************************/
//�����������麯����
/**************************************************************************************************************************/

// 26 ����+���� ��������
void Comp_Name_Input_Right(char* Compname) {
	char Pattern[20][100] = {
		"�й��������� + ����ѧ�����´�ҵ����",
		"����ս����ȫ����ѧ������ѧ���Ƽ���Ʒ����",
		"ACM - ICPC���ʴ�ѧ��������ƾ���",
		"ȫ����ѧ����ѧ��ģ����",
		"�й���У���������",
		"ȫ����ѧ��Ƕ��ʽоƬ��ϵͳ��ƾ���",
		"ȫ����ѧ����Ϣ��ȫ����",
		"��ΪICT����",
		"���ű�ȫ���������Ϣ����רҵ�˲Ŵ���",
		"���й����������ѧ�������ƴ���",
		"ESRI���й���ѧ��GIS�����������",
		"������ѧ����ѧ��ģ����",
		"CCSP��ѧ�������ϵͳ�������ƾ���",
		"ȫ����ѧ����������ƾ���",
		"CCPC�й���ѧ��������ƾ���",
		"ȫ����ѧ����Ϣ��ȫ����",
		"����Ϊ�����й���ѧ��������ƾ���",
		"�й���У���������",
		"ȫ����У��������XNUCA",
		"�й���ѧ����������Ĵ���"
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

		printf("û��������������������롣\n");
	}
}
/**************************************************************************************************************************/

//// 27 ����+��� ��������
//void Multiple_People_Input_Right(char input[150]) {
//	bool isValid = false;
//
//	while (!isValid) {
//		memset(input, 0, 150);
//		//getchar();
//		scanf("%s",input);
//		
//		// ������ָ����Ƿ���Ҫ��Χ���������Ƿ�������
//		int countNames = 1;
//		bool allChinese = true;
//		for (int i = 0; i < strlen(input); i++) {
//			if (input[i] == '��') {
//				countNames++;
//				continue;
//			}
//			wchar_t wc;
//			mbtowc(&wc, &input[i], sizeof(wchar_t));
//			if (wc >= 0x4e00 && wc <= 0x9fff) {
//				continue;
//			}
//			else {
//				allChinese = false;
//				break;
//			}
//		}
//
//		if ( countNames <= 5 && allChinese) {
//
//			isValid = true;
//		}
//		else {
//			printf("�����������������롣\n");
//		}
//	}
//}


/**************************************************************************************************************************/

// 28 ����+��� 'A'/'B'/'C'
void Input_ABC(char* a) {
	bool isValid = false;
	char input = 0;
	while (!isValid) {
		input = _getch();
		printf("%c\n", input);
		input = toupper(input); // ������ת��Ϊ��д�ַ�
		if (input == 'A' || input == 'B' || input == 'C') {
			*a = input;
			isValid = true;
		}
		else {
			printf("�����������������롣\n");
		}
	}
}
/**************************************************************************************************************************/

// 29 ����+���� ���쵥λ����
void Sponsor_Input_Right(char* Sponsor) {
	
	char Pattern[20][500] = {
		"���������������簲ȫ����Ϣ���쵼С��칫�ҡ����ҷ�չ�͸ĸ�ίԱ�ᡢ��ҵ����Ϣ������������Դ��ᱣ�ϲ���������������ũҵ��������֪ʶ��Ȩ�֡�����Ժ����칫�ҡ��й���ѧԺ���й�����Ժ������Ժ��ƶ�����쵼С��칫�ҡ����������롢ʡ����",
		"���������롢�й���Э����������ȫ��ѧ�����ط�ʡ����������",
		"����ICPC�����",
		"�������߽�˾���й���ҵ��Ӧ����ѧѧ��",
		"�������ߵ�ѧУ�������רҵ��ѧָ��ίԱ�ᡢ�������ߵ�ѧУ�������רҵ��ѧָ��ίԱ�ᡢ�������ߵ�ѧУ��ѧ������γ̽�ѧָ��ίԱ�ᡢȫ���ߵ�ѧУ����������о���",
		"�й�����ѧ��",
		"�������ߵ�ѧУ��Ϣ��ȫ��רҵ��ѧָ��ίԱ��",
		"��Ϊ��˾",
		"��",
		"��",
		"�й���������Ϣѧ��",
		"������ѧ����Ӧ�����ϻ�",
		"�й������ѧ��",
		"�������ߵ�ѧУ��������ѧָ��ίԱ��",
		"�����������רҵ�ߵȽ�ѧָ��ίԱ��",
		"�������ߵ�ѧУ��Ϣ��ȫרҵ��ѧָ��ίԱ��",
		"�й��˹�����ѧ��",
		"�������ߵ�ѧУ�������רҵ��ѧָ��ίԱ�ᣬ�������ߵ�ѧУ�������רҵ��ѧָ��ίԱ�ᣬ�������ߵ�ѧУ��ѧ������γ̽�ѧָ��ίԱ��",
		"�й���ѧԺ���й�����ռ䰲ȫЭ�ᡢ��������������",
		"�й��˹�����ѧ��",
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

		printf("û��������쵥λ�����������롣\n");
	}
}
/**************************************************************************************************************************/

// 30 ����+��� ʱ��
void Time_Input_Right(char* Time) {
	bool isValid = false;
	while (!isValid) {
		printf("(���ڸ�ʽ��YYYY-MM-DD��\n");
		memset(Time, 0, 30);
		scanf("%s", Time);
		int i = 0;
		// ȷ��������ַ�������Ϊ10������YYYY-MM-DD����ʽ
		if (strlen(Time) == 10) {
			// ȷ��������ַ����ϡ�YYYY-MM-DD����ʽ
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
				if(i==10){ isValid = true; }

			}
		}
		if (!isValid) {
			printf("���ڸ�ʽ�������������롣\n");
		}
	}
}
/**************************************************************************************************************************/

// 31 ����+���� �ڿ�����/��������
void Journal_Input_Right(char* Journal) {
	char Pattern[15][200] = {
		"ҵ�繫��ѧ���ۺ϶����ڿ�",
		"CCF-A�ڿ�",
		"CCF-A���鳤��",
		"CCF-B������������/���ѧ������",
		"CCF-B�ڿ�����",
		"�п�Ժ�ڿ�����һ������",
		"CCFC������������ / ���ѧ������",
		"CCF-C�ڿ�����",
		"CCF-B���鳤��",
		"�п�Ժ�ڿ�������������",
		"�����ѧ�������ѧ�������ѧ������",
		"Ӱ�����ӷ�0��SCI�����ڿ�����",
		"CCF-C���鳤��",
		"�й���ѧ����Ϣ��ѧ��������о��뷢չ����������������ͼ��ѧѧ��������ѧ�����İ桢�Զ���ѧ�������ѧ������",
		"EI�����ڿ�"
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

		printf("û������ڿ�/���飬���������롣\n");
	}
}
/**************************************************************************************************************************/

// 32 ����+��� ��/��/���ĺ�/ҳ�뷶Χ
void Volume_Page_Input_Right(char Volume_Page[4][50]){    //char(*Volume_Page_Input_Right(char Volume_Page[4][50]))[50] {     //char (*(*F(char (*param)[50])))[4];
	char Pattern_volume_issue[] = "��[0-9]+���ڣ�[0-9]+";
	char Pattern_paper_number[] = "[A-Z]{2}-[0-9]{3}-[0-9]{7}";
	char Pattern_page_range[] = "[0-9]+-[0-9]+";

	int flag_volume_issue = 0;
	int flag_paper_number = 0;
	int flag_page_range = 0;
	char temp[50] = { 0 };

	while (!(flag_volume_issue && flag_paper_number && flag_page_range)) {
		// ������������޸���ʾ��Ϣ������Ҫ�޸�
		if (!flag_volume_issue) {
			printf("�밴�ա���*���ڣ�*���ĸ�ʽ��������ȷ�ľ������Ϣ������*���������һλ�����֣���\n");
			memset(temp, 0, 50);
			scanf("%s", temp);
			if (sscanf(temp, "%s", Pattern_volume_issue) == 1) {
				flag_volume_issue = 1;
				strcpy(Volume_Page[0], temp);
			}
		}

		if (!flag_paper_number) {
			printf("�밴�ա�AB-123-4567890���ĸ�ʽ��������ȷ�����ĺţ�ÿ����д��ĸ�����ֶ������滻��λ���̶�����\n");
			memset(temp, 0, 50);
			scanf("%s", temp);
			if (sscanf(temp, "%s", Pattern_paper_number) == 1) {
				flag_paper_number = 1;
				strcpy(Volume_Page[1], temp);
			}
		}

		if (!flag_page_range) {
			printf("�밴�ա�*-*���ĸ�ʽ��������ȷ��ҳ�뷶Χ������*���������һλ�����֣���\n");
			memset(temp, 0, 50);
			scanf("%s", temp);
			if (sscanf(temp, "%s", Pattern_page_range) == 1) {
				flag_page_range = 1;
				strcpy(Volume_Page[2], temp);
			}
		}
	}
}
/**************************************************************************************************************************/

//// 33 ����+��� ������
//void Pure_Chinese_Input_Right(char* Input) {
//	bool allChinese = false;
//	while (!allChinese) {
//		memset(Input, 0, 30);
//		scanf("%s", Input);
//		// ����������
//		for (int i = 0; i < strlen(Input); i++) {
//			wchar_t wc;
//			mbtowc(&wc, &Input[i], 4);
//			if (wc >= 0x4e00 && wc <= 0x9fff) {
//				continue;
//			}
//			else {
//				allChinese = false;
//				printf("�����������������룺\n");
//				break;
//			}
//		}
//	}
//}
/**************************************************************************************************************************/

// 34 ����+��� ��Ŀ���
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
				printf("�����������������룺\n");
				break;
			}
		}
		if (i == strlen(ProjNum)) { Flag = true; }
	}
}
/**************************************************************************************************************************/


/**************************************************************************************************************************/

// 35 ����IDת���ַ����˺�
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
	result[8] = '\0';  // ����ַ���������
}