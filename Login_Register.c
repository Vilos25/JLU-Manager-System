//ע����.c�ļ��ܶ����Ϊ��һ����⣬��ʽ�ύʱ��ɾ������ע�͡�
//��898�У�����ǰ219��Ϊ��������ʣ�µ�Ϊ���������Ķ��塣
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
	//system("cls");
	system("color F0");
	AccountNode* Accrr[60] = { 0 };//��������Ϊ���ļ�������¼���˺ŵ�������
	AccountNode* Head = NULL;
	Head = (AccountNode*)malloc(sizeof(AccountNode));
	Head->Next = NULL;
	//Head = LIST_Account();
	Head = Start_Logging_Account(Head);//ԭ�����ڵ�ģ������
	//Display_Account(Head);//չʾ�����˺�����
	AccountNode* Stuhead = Find_DiferHead(Head, 1);//�����������зֱ��ҵ���һ��ѧ���˺š���һ������Ա�˺š���һ������Ա�˺š�
	AccountNode* Teahead = Find_DiferHead(Head, 2);
	AccountNode* Admhead = Find_DiferHead(Head, 3);//Adm��administator ����д����Ϊ����Ա��

	cursor(35, 3);
	printf("          ��ӭ���뼪�ִ�ѧ�������ɼ�����ϵͳ��\n");
Laststep1: //�������ж���д�Ķ�����ת����һ������ڡ�
	setjmp(Laststep4);
	system("cls");
	cursor(30, 6);
	printf("********************************************************\n");
	cursor(30, 17);
	printf("********************************************************\n");
	cursor(30, 8);
	printf("*********************              *********************\n");
	cursor(30, 9);
	printf("******************       ��½����     ******************\n");
	cursor(30, 10);
	printf("****************                        ****************\n");
	cursor(30, 11);
	printf("****************   1����¼ѧ���˺�      ****************\n");
	cursor(30, 12);
	printf("****************   2����¼��ʦ�˺�      ****************\n");
	cursor(30, 13);
	printf("****************   3����¼����Ա�˺�    ****************\n");
	cursor(30, 14);
	printf("****************   4���˳�              ****************\n");
	cursor(30, 15);
	printf("******************                    ******************\n");
	cursor(30, 16);
	printf("***********************          ***********************\n");
	cursor(30, 17);
	printf("********************************************************\n");
	cursor(30, 18);
	printf("********************************************************\n");
	int Choice;

	do {
		cursor(32, 24);
		printf("���������ѡ��:");
		Choice = Input_1toNum(4); //������ȷ�ĵ���ѡ�����֣������Ѱ���������������ܣ���
	} while (!(1 <= Choice && Choice <= 4));

	char Intputacc[30] = { 0 };//���ַ�����ʾ���£�ÿ����������˺š�
	char Intputpass[30] = { 0 };//���ַ�����ʾ���£�ÿ������������롣
	int cnt = 0;//����������¼���롰�˺š������롱������cnt=3ʱ�����һ�����ѡ�ͬʱcnt���㡣

	switch (Choice) {
	case 1:
	{	system("cls");
		strcpy(Intputacc, Acc_Input_Right()); //�������˺š���������˺������ʽ�Ƿ���ȷ��������ȷ��ʽ���˺Ÿ�ֵ��Intputacc��
		strcpy(Intputpass, Pass_Input_Right());//���������롱����������������ʽ�Ƿ���ȷ��������ȷ��ʽ�����븳ֵ��Intputpass��
		while (!If_AccPass_Match(Choice, Head, Intputacc, Intputpass)) {//�ж�����ġ��˺š������롱�Ƿ�ƥ�䡣// ʵ��Choice��ֵ ���β��г䵱�� ����Attri ��ֵ��

			cnt++;
			if (cnt >= 3) {//�����һ�����ѡ��.
				cnt = 0;//cnt���㡣
				Morm3_Match_Error(Head);//�һ�����ĺ���
			}
			else {
				cursor(26, xy += 1);
				printf("�˺Ż���������������룺");
				Sleep(1000);
				system("cls");
			}

			strcpy(Intputacc, Acc_Input_Right());
			strcpy(Intputpass, Pass_Input_Right());
		}
	}
	break;
	case 2:
	case 3:
	{	system("cls");
		strcpy(Intputacc, Acc_Input_Right_Tea()); //�������˺š���������˺������ʽ�Ƿ���ȷ��������ȷ��ʽ���˺Ÿ�ֵ��Intputacc��
		strcpy(Intputpass, Pass_Input_Right());//���������롱����������������ʽ�Ƿ���ȷ��������ȷ��ʽ�����븳ֵ��Intputpass��
		while (!If_AccPass_Match(Choice, Head, Intputacc, Intputpass)) {//�ж�����ġ��˺š������롱�Ƿ�ƥ�䡣// ʵ��Choice��ֵ ���β��г䵱�� ����Attri ��ֵ��
			
			cnt++;
			if (cnt >= 3) {//�����һ�����ѡ��.
				cnt = 0;//cnt���㡣
				Morm3_Match_Error(Head);//�һ�����ĺ���
			}
			else {
				cursor(26, xy += 1);
				printf("�˺Ż���������������룺");
				Sleep(1000);
				system("cls");
			}

			strcpy(Intputacc, Acc_Input_Right_Tea());
			strcpy(Intputpass, Pass_Input_Right());
		}
	}
	break;
	case 4:
		Save_List_ToFile(Head);
		return 0;
	}
	cursor(26,xy+=1 );
	printf("��¼�ɹ���");
	Sleep(1000);

	switch (Choice) {
	case 1:  /***ѧ��ϵͳ��ں�����***///(Intputacc); 
		*ID = Str_To_IntArr(Intputacc);//���������int*�͵ģ�ֱ�Ӹ���ID�ˣ����ý�����
		return 1;
		break;
	case 2: /***��ʦϵͳ��ں�����***///(Intputacc); 
		*ID = Str_To_IntArr(Intputacc);
		return 2;
		break;
	case 3:
		system("cls");
		xy=10;
		cursor(26, xy += 1);
		printf("��ѡ��\n");
		cursor(26, xy += 1);
		printf("\"1\"������ѧ���ɼ�ϵͳ\n");
		cursor(26, xy += 1);
		printf("\"2\"�������¼�˺�");
		cursor(26, xy += 1);
		int Choice1 = Input_1toNum(2);
		if (Choice1 == 1) {
			/***����Աϵͳ��ں�����***///(Intputacc); 
			*ID = Str_To_IntArr(Intputacc);
			return 3;
		}
		else {
		Laststep2:
			system("cls");
			xy = 10;
			cursor(26, xy += 1);
			printf("��ѡ��");
			cursor(26, xy += 1);
			printf("\"1\"��������������");
			cursor(26, xy += 1);
			printf("\"2\"�����е�������");
			cursor(26, xy += 1);
			printf("\"3\"��������һ��");
			cursor(26, xy += 1);
			int Choice2 = Input_1toNum(3);//������ȷ�ĵ���ѡ�����֣��Ѱ���������������ܣ���

			if (Choice2 == 3) {
				printf("���سɹ���\n");
				Sleep(1000);
				goto Laststep1;
			}
			else if (Choice2 == 1) {//������������
				system("cls");
				xy = 10;
				cursor(26, xy += 1);
				printf("��ѡ��");
				cursor(26, xy += 1);
				printf("\"1\"������ע���˺�");
				cursor(26, xy += 1);
				printf("\"2\"������ɾ���˺�");
				cursor(26, xy += 1);
				printf("\"3\"��������ʼ������");
				cursor(26, xy += 1);
				printf("\"4\"��������һ��");
				cursor(26, xy += 1);
				int Choice3 = Input_1toNum(4);//������ȷ�ĵ���ѡ�����֣��Ѱ���������������ܣ���
				system("cls");
				switch (Choice3) {
				case 1://����ע���˺�
					system("cls");
					xy = 10;
					cursor(26, xy += 1);
					printf("������Ҫע����˺�����\n");
					cursor(26, xy += 1);
					int Num = Input_1toNum(9);
					cursor(26, xy += 1);
					printf("������Ҫע����˺����ԣ�\n");
					cursor(26, xy += 1);
					int Attri = Input_1toNum(3);

					if (Attri == 1) { Num = Readfile(Head, Stuhead, Accrr, Attri); }//��Readfile�������������ļ��е��˺Ų�������������λ����������ͬ�ġ�αͷ��㡱������Attriȷ��������ֵNumΪ�ɹ��������˺�����
					else if (Attri == 2) { Num = Readfile(Head, Teahead, Accrr, Attri); }
					else { Num = Readfile(Head, Admhead, Accrr, Attri); }
					cursor(26, xy += 1);
					printf("List_New_Account.txt�����ɹ�������\n������%d���˺�\n", Num);
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep2;
					break;

				case 2://����ɾ���˺�
					system("cls");
					xy = 10;
					cursor(26, xy += 1);
					printf("������Ҫɾ�����˺�����\n");
					Num = Input_Num();
					cursor(26, xy += 1);
					printf("����Ҫ��ʼɾ�����˺ţ�\n");
					cursor(26, xy += 1);
					printf("ɾ��ѧ���˺�(1)or��ʦ�˺�(2)��");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					if(cho==1)
						strcpy(Intputacc, Acc_Input_Right());
					else
						strcpy(Intputacc, Acc_Input_Right_Tea());
					Batch_Delete_Account(Head, Num, Intputacc);//��Intputacc��ʼ����ɾ��Num���˺ţ����������ԡ�
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep2;
					break;

				case 3://������ʼ������
					system("cls");
					xy = 10;
					cursor(26, xy += 1);
					printf("������Ҫ�޸�������˺�����\n");
					cursor(26, xy += 1);
					Num = Input_Num();
					printf("����Ҫ��ʼ�޸ĵ��˺�,");
					printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					if(cho==1)
						strcpy(Intputacc, Acc_Input_Right());
					else
						strcpy(Intputacc, Acc_Input_Right_Tea());
					cursor(26, xy += 1);
					printf("���������룬");
					strcpy(Intputpass, Pass_Input_Right());
					Batch_Change_Password(Head, Num, Intputacc, Intputpass);//��Intputacc��ʼ�����޸�Num���˺ŵ�����ΪIntputpass�����������ԡ�
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep2;
					break;

				case 4:
					cursor(26, xy += 1);
					printf("���سɹ���\n");
					Sleep(1000);
					goto Laststep2;
					break;
				}
			}
			else {  //Choice2=1��������������ѡ�
			Laststep3:
				setjmp(Laststep5);
				system("cls");
				xy = 10;
				cursor(26, xy += 1);
				printf("��ѡ��");
				cursor(26, xy += 1);
				printf("\"1\"��ע�ᵥ���˺�");
				cursor(26, xy += 1);
				printf("\"2\"��ɾ�������˺�");
				cursor(26, xy += 1);
				printf("\"3\"���޸ĵ����˺ŵ�����");
				cursor(26, xy += 1);
				printf("\"4\"��������һ��");
				cursor(26, xy += 1);
				int Choice4 = Input_1toNum(4);//������ȷ�ĵ���ѡ�����֣��Ѱ���������������ܣ���
				system("cls");
				switch (Choice4) {
				case 1:
					Add_Account(Head);//ע�ᵥ���˺ŵĺ�����
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep3;
					break;
				case 2:
				{
					cursor(26, xy += 1);
					printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					if (cho == 1)
						strcpy(Intputacc, Acc_Input_Right());
					else
						strcpy(Intputacc, Acc_Input_Right_Tea());//����Ҫɾ�����˺�
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 1);
						printf("���˺Ų����ڣ����������룺\n");
						cursor(26, xy += 1);
						printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						if (cho == 1)
							strcpy(Intputacc, Acc_Input_Right());
						else
							strcpy(Intputacc, Acc_Input_Right_Tea());
					}
					Delete_Account(Head, Intputacc);//ɾ�������˺ŵĺ���
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep3;
				}
				break;
				case 3:
				{
					cursor(26, xy += 1);
					printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
					cursor(26, xy += 1);
					cho = Input_1toNum(2);
					if (cho == 1)
						strcpy(Intputacc, Acc_Input_Right());
					else
						strcpy(Intputacc, Acc_Input_Right_Tea());//����Ҫ�޸�������˺�
					while (!If_Acc_Exist(Head, Intputacc)) {
						cursor(26, xy += 1);
						printf("���˺Ų����ڣ����������룺\n");
						cursor(26, xy += 1);
						printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
						cursor(26, xy += 1);
						cho = Input_1toNum(2);
						if (cho == 1)
							strcpy(Intputacc, Acc_Input_Right());
						else
							strcpy(Intputacc, Acc_Input_Right_Tea());
					}
					Change_Password(Head, Intputacc);//�޸ĵ����˺ŵ�����ĺ���
					cursor(26, xy += 1);
					printf("���Զ�Ϊ��������һ����\n");
					Sleep(1000);
					goto Laststep3;
				}
				break;
				case 4:
					cursor(26, xy += 1);
					printf("���سɹ���\n");
					Sleep(1000);
					goto Laststep2;
				}
			}
			break;
		}
	}
	Save_List_ToFile(Head);
	return 0;

}

//���������� �������� �� ���� ��
/**************************************************************************************************************************/
/**************************************************************************************************************************/
/**************************************************************************************************************************/

//����1//�˺���Ϣ�⣨ģ�⣩��ʵ��Ҫɾ�����������ֱ������������ͷ��һ���ļ���¼��������֪�˺���Ϣ����
AccountNode* LIST_Account(void) {
	AccountNode* head, * tmp, * p;
	head = tmp = p = NULL;

	head = (AccountNode*)malloc(sizeof(AccountNode));
	head->Next = NULL;

	tmp = head;
	int i = 0, j = 0;

	for (i = 1; i <= 3; i++) {
		for (j = 0; j < 3; j++) {
			AccountNode* newnode = (AccountNode*)malloc(sizeof(AccountNode));
			newnode->Attribute = i;   //����ͷû�д����һ������ 
			newnode->Next = NULL;

			tmp->Next = newnode;
			tmp = newnode;

			memset(newnode->Accountnum, 0, 20);
			strcpy(newnode->Accountnum, "2123050");
			newnode->Accountnum[7] = '1' + j + 3 * (i - 1);

			memset(newnode->Password, 0, 20);
			strcpy(newnode->Password, "12345678");

			memset(newnode->Name, 0, 30);
			strcpy(newnode->Name, "ŷ����");
			newnode->Name[6] = '1' + j + 3 * (i - 1);

			memset(newnode->Phonenum, 0, 20);
			strcpy(newnode->Phonenum, "1234567890");
			newnode->Phonenum[10] = '1' + j + 3 * (i - 1);

			memset(newnode->Email, 0, 30);
			strcpy(newnode->Email, "1234567890@qq.com");
			newnode->Email[9] = '1' + j + 3 * (i - 1);
		}
	}

	return head;//���ص�����ͷ
}
/**************************************************************************************************************************/

//����2//���˺���Ϣ������������зֱ��ҵ���1��ѧ���˺ţ�Stuhead������ʦ�˺ţ�Teahead��������Ա�˺ţ�Admhead������Ϊ������α����ͷ����
AccountNode* Find_DiferHead(AccountNode* Head, int Attri)
{
	AccountNode* pcurrent = Head->Next;
	while (pcurrent != NULL && pcurrent->Attribute != Attri) {//�ҵ���һ�����Զ�Ӧ���˺ž��ǡ�α����ͷ����
		pcurrent = pcurrent->Next;
	}
	return pcurrent;
}
/**************************************************************************************************************************/

//����3//��ʾ�˺������е���Ϣ��
void Display_Account(AccountNode* Head)
{
	AccountNode* pcurrent = Head->Next;// Head->next�ǵ�һ�����ݽڵ� 
	while (pcurrent != NULL) {
		printf("%s\t", pcurrent->Accountnum);
		printf("%s\t", pcurrent->Password);
		printf("%d\t", pcurrent->Attribute);
		printf("%s\t", pcurrent->Name);
		printf("%s\t", pcurrent->Phonenum);
		printf("%s\t", pcurrent->Email);
		printf("\n");

		//ָ���ƶ�����һ��Ԫ�ص��׵�ַ
		pcurrent = pcurrent->Next;
	}
}
/**************************************************************************************************************************/

//����5//�����û������Ƿ�Ϊ1��Num�ĵ���ѡ��
bool If_Inputs_1toNum(char Input[], int Num)
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 1)) {//�����Ƿ�Ϊһλ��
		if (isdigit(Input[0])) {//��һλ�Ƿ�Ϊ���֡�
			if ((Input[0] - '0') >= 1 && (Input[0] - '0') <= Num) {//��һλ�����Ƿ���1��Num֮�䡣
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

//����6//���봿���֣������������ܣ�����ֹ�û������������ַ����³����˳���
int Input_Num() {
	char Userinput[30] = { 0 };
	scanf("%s", Userinput);
	printf("\n");
	while (!If_Inputs_Num(Userinput)) //ѭ����ֹ�������û���ȷ�����֡�
	{
		printf("�������ݸ�ʽ�������������֣�\n");
		memset(Userinput, 0, 5); //����ַ�������ֹ�������´����롣
		//getchar();
		scanf("%s", Userinput);
	}
	return (atoi(Userinput));
}
/**************************************************************************************************************************/

//����7//�����û������Ƿ�Ϊ�����֣�
bool If_Inputs_Num(char Userinput8[]) {
	bool flag;
	flag = true;
	int i=0;
	int len = strlen(Userinput8);
	for (i = 0; i < len; i++) {
		if (!isdigit(Userinput8[i])) {//�����ַ���ÿһλ�Ƿ�Ϊ����
			flag = false;
		}
	}
	return flag;
}
/**************************************************************************************************************************/

//����8//�����ˡ������˺š���������˺������ʽ�Ƿ���ȷ�����ܣ�
char* Acc_Input_Right()
{
	char Userinput[30] = { 0 };
	xy = 10;
	cursor(26, xy);
	printf("�������˺ţ�");
	Input_charNumber(Userinput, 8);
	//scanf("%s", Userinput);

	while (!If_InputAcc_Format(Userinput))//ѭ����ֹ�������û���ȷ��ʽ���˺š�
	{
		
		cursor(26, xy+=1);
		printf("�������ݸ�ʽ����������8�����ֵ��˺ţ�\n");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		Input_charNumber(Userinput, 8);
		//scanf("%s", Userinput);
	}
	return Userinput;
}
/**************************************************************************************************************************/

//����8//�����ˡ������˺š���������˺������ʽ�Ƿ���ȷ�����ܣ�
char* Acc_Input_Right_Tea()
{
	char Userinput[30] = { 0 };
	xy = 10;
	cursor(26, xy);
	printf("�������˺ţ�");
	Input_charNumber(Userinput, 6);
	//scanf("%s", Userinput);

	while (!If_InputAcc_Format_Tea(Userinput))//ѭ����ֹ�������û���ȷ��ʽ���˺š�
	{

		cursor(26, xy += 1);
		printf("�������ݸ�ʽ����������6�����ֵ��˺ţ�\n");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		Input_charNumber(Userinput, 6);
		//scanf("%s", Userinput);
	}
	return Userinput;
}
/**************************************************************************************************************************/

//����9//�����ˡ��������롱����������������ʽ�Ƿ���ȷ�����ܣ�
char* Pass_Input_Right()
{
	char Userinput[30] = { 0 };
	cursor(26, xy+=1);
	printf("���������룺");
	//getchar();
	//scanf("%s", Userinput);
	Pass_Input_Line(Userinput);

	while (!If_InputPass_Format(Userinput))//ѭ����ֹ�������û���������ȷ��ʽ�����롣
	{
		cursor(26, xy++);
		printf("�������ݸ�ʽ����������ֻ�������ֺ���ĸ��С��20���ַ������룺");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		//getchar();
		Pass_Input_Line(Userinput);
	}
	return Userinput;
}
/**************************************************************************************************************************/

//����10//�����ˡ���������������������������ʽ�Ƿ���ȷ�����ܣ�
char* Name_Input_Right()
{
	char Userinput[30] = { 0 };
	//getchar();
	scanf("%s", Userinput);
	//Input_charNumber(Userinput, 8);

	while (!If_InputName_Format(Userinput))//ѭ����ֹ�������û���ȷ��ʽ��������
	{
		cursor(26, xy++);
		printf("�������ݸ�ʽ����������ֻ�������ֺ���ĸ��С��30���ַ������֣�\n");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		//getchar();
		//Input_charNumber(Userinput, 8);
		scanf("%s", Userinput);
	}
	return Userinput;
}
/**************************************************************************************************************************/
//����11//�����ˡ������ֻ��š���������ֻ��������ʽ�Ƿ���ȷ�����ܣ�
char* Phone_Input_Right()
{
	char Userinput[30] = { 0 };
	//getchar();
	Input_charNumber(Userinput,11);
	//scanf("%s", Userinput);

	while (!If_InputPhone_Format(Userinput))//ѭ����ֹ�������û���ȷ��ʽ���ֻ��š�
	{
		cursor(26, xy++);
		printf("�������ݸ�ʽ����������11�����ֵ��ֻ��ţ�\n");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		//getchar();
		Input_charNumber(Userinput, 11);
		//scanf("%s", Userinput);
	}
	return Userinput;
}
/**************************************************************************************************************************/

//����12//�����ˡ��������䡱����������������ʽ�Ƿ���ȷ�����ܣ�
char* Email_Input_Right()
{
	char Userinput[30] = { 0 };
	//getchar();
	Input_Email(Userinput);
	//scanf("%s", Userinput);

	while (!If_InputEmail_Format(Userinput))//ѭ����ֹ�������û���ȷ��ʽ�����䡣
	{
		cursor(26, xy++);
		printf("�������ݸ�ʽ������������ȷ�����䣺\n");
		memset(Userinput, 0, 30);//����ַ�������ֹ�������´����롣
		//getchar();
		Input_Email(Userinput);
		//scanf("%s", Userinput);
	}
	return Userinput;
}

/**************************************************************************************************************************/

//����13//�����û�������˺Ÿ�ʽ�Ƿ���ȷ��
bool If_InputAcc_Format(char Input[]) {
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 8)) {//�����Ƿ�Ϊ8λ��
		int i;
		for (i = 0; i < 8; i++) {
			if (!(isdigit(Input[i]))) {//ÿһλ�Ƿ�Ϊ���֡�
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/
//����13//�����û�������˺Ÿ�ʽ�Ƿ���ȷ��
bool If_InputAcc_Format_Tea(char Input[]) {
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 6)) {//�����Ƿ�Ϊ6λ��
		int i;
		for (i = 0; i < 6; i++) {
			if (!(isdigit(Input[i]))) {//ÿһλ�Ƿ�Ϊ���֡�
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}

//����14//�����û�����������ʽ�Ƿ���ȷ��
bool If_InputPass_Format(char Input[])
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len < 20)) {//�����Ƿ�С��20λ��
		int i;
		for (i = 0; i < len; i++) {
			if (!(isalnum(Input[i]))) {//ÿһλ�Ƿ�Ϊ����/��ĸ��
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/
//����15//�����û������������ʽ�Ƿ���ȷ��
bool If_InputName_Format(char Input[])
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len < 30)) {//�����Ƿ�С��20λ��
		int i;
		for (i = 0; i < len; i++) {
			if (!(isalpha(Input[i]))) {//ÿһλ�Ƿ�Ϊ��ĸ��
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}
/**************************************************************************************************************************/

//����16//�����û�������ֻ��Ÿ�ʽ�Ƿ���ȷ��
bool If_InputPhone_Format(char Input[])
{
	bool flag;
	flag = true;
	int len = (int)strlen(Input);
	if ((len == 11)) {//�����Ƿ�Ϊ11λ��
		int i;
		for (i = 0; i < 11; i++) {
			if (!(isdigit(Input[i]))) {//ÿһλ�Ƿ�Ϊ���֡�
				return false;
			}
		}
	}
	else { flag = false; }
	return flag;
}/**************************************************************************************************************************/

//����17//�����û�����������ʽ�Ƿ���ȷ��
bool If_InputEmail_Format(char Input[])
{
	int At_count = 0;
	int Dot_count = 0;

	if (Input[0] == '_' || Input[0] == '.') {
		return false;  // ���š�_�����ߡ�.�����ܳ����ڵ����ʼ���ַ�Ŀ�ͷ
	}

	for (int i = 0; i < strlen(Input); i++) {
		if (Input[i] == '@') {
			At_count++;
		}
		else if (Input[i] == '.') {
			Dot_count++;
		}
	}

	if (At_count == 1 && Dot_count == 1) {// "@"��"."������ֻ��һ����
		return true;
	}
	else {
		return false;
	}
}
/**************************************************************************************************************************/

//����18//�����û�������˺š����루��ʽ�Ѽ��飩�Ƿ�ƥ�䣺
bool If_AccPass_Match(int Attri, AccountNode* Head, char Intputacc[], char Intputpass[])
{
	AccountNode* pcurrent = Find_DiferHead(Head, Attri);//�������ҵ���ͬ�ġ�αͷ��㡱��
	while (pcurrent != NULL && !((pcurrent->Attribute == Attri) && (strcmp(pcurrent->Accountnum, Intputacc) == 0))) {//�ҵ� ����ƥ�䣬�˺�ƥ�� �������㡣
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) {//û�ҵ���Ӧ�Ľ�㡣
		return false;
	}
	else {//�ҵ�����Ӧ�Ľ��Ϊpcurrent:
		if (strcmp(pcurrent->Password, Intputpass) == 0) {
			return true;
		}
		else {
			return false;
		}
	}
}
/**************************************************************************************************************************/

//����19//�û������3���˺����붼��ƥ�䣬ѯ�ʲ��������������롱ѡ�
AccountNode* Morm3_Match_Error(AccountNode* Head)
{
	cursor(26, xy += 1);
	printf("���Ѿ����3�Σ����Ƿ�ѡ���������룿");
	cursor(26, xy += 1);
	printf("���� \"1\" ����");
	cursor(26, xy += 1);
	printf("���� \"2\" ����");
	cursor(26, xy += 1);
	printf("���� \"3\" ��������һ��");
	cursor(26, xy += 1);
	printf("ѡ�");
	int Choice1 = Input_1toNum(3);//
	Sleep(1000);
	system("cls");
	if (Choice1 == 1) {
		xy = 10;
		cursor(26, xy += 1);
		printf("�һ����룺��ѡ����֤��ʽ��");
		cursor(26, xy += 1);
		printf("���� \"1\" ���ֻ�����֤");
		cursor(26, xy += 1);
		printf("���� \"2\" ��������֤");
		cursor(26, xy += 1);
		printf("���� \"3\" ��������һ��");
		cursor(26, xy += 1);
		int Choice2 = Input_1toNum(3);//������ȷ��1��3�ĵ���ѡ�����֣��Ѱ���������������ܣ���
		system("cls");
		if (Choice2 == 1) {
			xy = 10;
			cursor(26, xy += 1);
			printf("���������󶨵��ֻ��ţ�");
			char Inputphone[30] = { 0 };
			strcpy(Inputphone, Phone_Input_Right());//�����ֻ��ţ��Ѱ��������ܣ���
			while (!If_Phone_Exist(Head, Inputphone)) {
				
				cursor(26, xy += 1);
				printf("���ֻ����벻�������κ��˺ţ����������룺");
				cursor(26, xy += 1);
				strcpy(Inputphone, Phone_Input_Right());
			}
			Phone_Change_Password(Head, Inputphone);//ͨ�������޸�����ĺ�����
			cursor(26, xy += 1);
			printf("�����޸ĳɹ��������µ�¼��");//�������������������˺����롣

		}
		else if (Choice2 == 2) {
			xy = 10;
			cursor(26, xy += 1);
			printf("���������󶨵����䣺");
			char Inputemail[30] = { 0 };
			strcpy(Inputemail, Email_Input_Right());//�������䣨�Ѱ��������ܣ���
			while (!If_Email_Exist(Head, Inputemail)) {
				
				cursor(26, xy += 1);
				printf("�����䲻�������κ��˺ţ����������룺");
				cursor(26, xy += 1);
				strcpy(Inputemail, Email_Input_Right());
			}
			Email_Change_Password(Head, Inputemail);//ͨ�������޸�����ĺ�����
			cursor(26, xy += 1);
			printf("�����޸ĳɹ��������µ�¼��");//�������������������˺����롣
		}
		else {
			longjmp(Laststep4, 1);
		}
	}
	else if (Choice1 == 2) {
		cursor(26, 9);
		printf("�õģ������������˺ź�����");//�������������������˺����롣
	}
	else {
		longjmp(Laststep4, 1);//�纯��������һ����
	}

	return Head;
}
/**************************************************************************************************************************/

//����20//����������˺ţ���ʽ�Ѽ��飩�Ƿ���ڣ�
bool If_Acc_Exist(AccountNode* Head, char Input[])
{
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Accountnum, Input) == 0)) {//ѭ��ֹͣ�������������/�ҵ���Ӧ�˺š�
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//���������
	else { return true; }//�ҵ���Ӧ�˺š�
}
/**************************************************************************************************************************/

//����21//����������ֻ��ţ���ʽ�Ѽ��飩�Ƿ���ڣ�
bool If_Phone_Exist(AccountNode* Head, char Input[]) {
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Phonenum, Input) == 0)) {//ѭ��ֹͣ�������������/�ҵ���Ӧ�ֻ��š�
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//���������
	else { return true; }//�ҵ���Ӧ�ֻ��š�
}
/**************************************************************************************************************************/

//����22//������������䣨��ʽ�Ѽ��飩�Ƿ���ڣ�
bool If_Email_Exist(AccountNode* Head, char Input[]) {
	AccountNode* pcurrent = Head;
	while (pcurrent != NULL && !(strcmp(pcurrent->Email, Input) == 0)) {//ѭ��ֹͣ�������������/�ҵ���Ӧ���䡣
		pcurrent = pcurrent->Next;
	}
	if (pcurrent == NULL) { return false; }//���������
	else { return true; }//�ҵ���Ӧ���䡣
}
/**************************************************************************************************************************/

//����23//����Աע�ᵥ�����˺ŵ�Ȩ�ޣ�
AccountNode* Add_Account(AccountNode* Head)
{

	printf("\n�������������ֽ���ѡ��\n");
	printf("\"1\"��ע��ѧ���˺�\n");
	printf("\"2\"��ע���ʦ�˺�\n");
	printf("\"3\"��ע�����Ա�˺�\n");
	printf("\"4\"��������һ��\n");

	int Attri = Input_1toNum(4);//������ȷ��1��4�ĵ���ѡ�����֣��Ѱ���������������ܣ���

	if (Attri == 4) {//�纯��������һ����
		longjmp(Laststep5, 1);
	}
	else {//ע�ᵥ���˺ţ�����Ϊ���������Attri��
		AccountNode* newnode = (AccountNode*)malloc(sizeof(AccountNode));//�����½ڵ㡣
		newnode->Attribute = Attri;//�����ԡ�
		newnode->Next = NULL;

		AccountNode* diferhead = Find_DiferHead(Head, Attri);//������Ӧ�ġ�αͷ��㡱����һλ��

		newnode->Next = diferhead->Next;
		diferhead->Next = newnode;
		
		printf("\n���������˺�,");
		cursor(26, xy += 1);
		printf("ѧ���˺�(1)or��ʦ�˺�(2)��");
		cursor(26, xy += 1);
		cho = Input_1toNum(2);
		if (cho == 1)
			strcpy(newnode->Accountnum, Acc_Input_Right());
		else
			strcpy(newnode->Accountnum, Acc_Input_Right_Tea());

		printf("�봴������,");
		strcpy(newnode->Password, Pass_Input_Right());
		printf("�������˺��˵����֣�\n");
		strcpy(newnode->Name, Name_Input_Right());
		printf("�������˺��˵��ֻ��ţ�\n");
		strcpy(newnode->Phonenum, Phone_Input_Right());
		printf("�������˺��˵����䣺\n");
		strcpy(newnode->Email, Email_Input_Right());

		printf("\nΪ%sע��ɹ���\n\n", newnode->Name);

		Display_Account(Head);//��ɾ
	}
	return Head;
}
/**************************************************************************************************************************/

//����24//����Աɾ����֪�˺ŵ�Ȩ�ޣ�
AccountNode* Delete_Account(AccountNode* Head, char Account[])
{
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//�ҵ���Ӧ�˺š�
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	//ɾ�������ڵ� pcurrent�ڵ�
	pprev->Next = pcurrent->Next;
	free(pcurrent);
	pcurrent = pprev->Next;
	printf("ɾ���ɹ�����ɾ�����˺�Ϊ��");
	printf("%s\n", Account);
	Display_Account(Head);//��ɾ

	return Head;
}
/**************************************************************************************************************************/

//����25//����Ա�޸���֪�˺ŵ������Ȩ�ޣ�
AccountNode* Change_Password(AccountNode* Head, char Account[])
{
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//�ҵ���Ӧ�˺š�
		pcurrent = pcurrent->Next;
	}
	printf("�����������룺\n");
	//getchar();
	char Newpassword[20] = { 0 };
	scanf("%s", Newpassword);//���������롣
	while (!If_InputPass_Format(Newpassword))//�����������ʽ
	{
		printf("�������ݸ�ʽ����������ֻ�������ֺ���ĸ��С��20���ַ��������룺\n");
		memset(Newpassword, 0, 20);//����ַ�������ֹ�������ַ�Ӱ���´�ѭ�������롣
		//getchar();
		scanf("%s", Newpassword);
	}
	strcpy(pcurrent->Password, Newpassword);
	printf("�޸ĳɹ���������Ϊ��");
	printf("%s", Newpassword);

	Display_Account(Head);//��ɾ

	return Head;
}
/**************************************************************************************************************************/

//����26//�ֻ���֤ͨ�����޸����룺
AccountNode* Phone_Change_Password(AccountNode* Head, char Inputphone[]) {
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Phonenum, Inputphone) == 0)) {//�ҵ���Ӧ�ֻ��š�
		pcurrent = pcurrent->Next;
	}
	printf("�����������룺\n");
	//getchar();
	char Newpassword[20] = { 0 };
	scanf("%s", Newpassword);//���������롣
	
	while (!If_InputPass_Format(Newpassword))//�����������ʽ
	{
		printf("�������ݸ�ʽ����������ֻ�������ֺ���ĸ��С��20���ַ��������룺\n");
		memset(Newpassword, 0, 20);//����ַ�������ֹ�������ַ�Ӱ���´�ѭ�������롣
		//getchar();
		scanf("%s", Newpassword);
	}
	strcpy(pcurrent->Password, Newpassword);
	printf("������Ϊ��");
	printf("%s\n", Newpassword);//��ɾ

	Display_Account(Head);//��ɾ
	return Head;
}
/**************************************************************************************************************************/

//����27//������֤ͨ�����޸����룺
AccountNode* Email_Change_Password(AccountNode* Head, char Inputemail[]) {
	AccountNode* pcurrent = Head;
	while (!(strcmp(pcurrent->Email, Inputemail) == 0)) {//�ҵ���Ӧ���䡣
		pcurrent = pcurrent->Next;
	}
	printf("�����������룺\n");
	//getchar();
	char Newpassword[20] = { 0 };
	scanf("%s", Newpassword);//���������롣
	while (!If_InputPass_Format(Newpassword))//�����������ʽ
	{
		printf("�������ݸ�ʽ����������ֻ�������ֺ���ĸ��С��20���ַ��������룺\n");
		memset(Newpassword, 0, 20);//����ַ�������ֹ�������ַ�Ӱ���´�ѭ�������롣
		scanf("%s", Newpassword);
	}
	strcpy(pcurrent->Password, Newpassword);
	printf("������Ϊ��");
	printf("%s\n", Newpassword);//��ɾ

	Display_Account(Head);//��ɾ
	return Head;
}

/**************************************************************************************************************************/

//����28//�� LIST_Account.txt �ļ��������������˺ţ�
int Readfile(AccountNode *Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri)
{
	int i = 0;//i�Ǽ���������¼�ɹ����ļ���¼����˺�����
	FILE* fp;
	if ((fp = fopen("D:\\VS����ʽ�ģ�\\Login & Resgister 2.0\\List_New_Account.txt", "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ���!\n");
		exit(0);
	}
	for (i = 0; (!feof(fp)); i++)
	{
		Accrr[i] = (AccountNode*)malloc(sizeof(AccountNode));//Ϊÿ��¼����˺���Ϣ���ٶ�̬�ڴ档
		fscanf(fp, "%s\t%s\t%d\t%s\t%s\t%s", Accrr[i]->Accountnum, Accrr[i]->Password, &Accrr[i]->Attribute, Accrr[i]->Name, Accrr[i]->Phonenum, Accrr[i]->Email);
		Accrr[i]->Next = NULL;
		Accrr[i]->Attribute = Attri;
	}
	fclose(fp);//�ر��ļ���
	Access_AccList(Head, Diferhead, Accrr, Attri, i);//��ÿ���½ڵ㡰�����������//����λ����������ͬ�ġ�αͷ��㡱������Attriȷ����
	printf("Total new account is %d.\n", i);//������Ϊ��ʱ����i++,��ʱ�������˺���Ϊi ��
	return i; //���ض������˺�����
}
/**************************************************************************************************************************/

//����29//�����ļ��ж�����˺Ų����˺�����
AccountNode* Access_AccList(AccountNode* Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri,int m) {//
	AccountNode* pprev = Diferhead;
	AccountNode* pcurrent = Diferhead->Next;
	while ((pcurrent != NULL)&&(pcurrent->Attribute == Attri)) {//��pcurrent�ҵ���һ�����ԣ���pprev�Ƕ�Ӧ���Ե����һ���˺š�
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	AccountNode* tmp = pprev;//pprev�Ƕ�Ӧ���Ե����һ���˺�,��tmp��ʾ��

	int i = 0;
	for (i = 0; i < m; i++) {
		tmp->Next = Accrr[i];//�½ڵ�����tmp���档
		tmp = Accrr[i];//�½ڵ���tmp��
	}
	tmp->Next = pcurrent;//�����½ڵ������ɺ����ϱ�ʾ��һ�����Ե�pcurrent�ڵ㡣ʹ�����������ϲ㡣
	Display_Account(Head);//��ɾ

	return Head;
}
/**************************************************************************************************************************/

//����30//����ɾ���˺ŵĺ�����
AccountNode* Batch_Delete_Account(AccountNode* Head, int Num, char Account[]) {
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	AccountNode* pcurrent_to_num = NULL;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//�ҵ���ʼɾ���Ķ�Ӧ�˺š�
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	pcurrent_to_num = pcurrent;//��pcurrent��ʼɾ����pprev����ɾ������������ʣ�µ�һ������
	int i = 0;
	for (i = 0; i < Num; i++) {//��forѭ��ɾ����Num���˺š�
		AccountNode* pcurrent_to_num2 = pcurrent_to_num->Next; //��pcurrent_to_num2���Ҫɾ�Ľڵ����һ����㡣
		free(pcurrent_to_num);
		pcurrent_to_num = pcurrent_to_num2;
	}
	pprev->Next = pcurrent_to_num;//����ʱpcurrent_to_num��ʾʣ��һ������ĵ�һ����㣬��pprev����ʣ�µ�һ������

	printf("ɾ���ɹ�����ɾ����%d���˺š�\n", Num);
	Display_Account(Head);//��ɾ
	return Head;
}
/**************************************************************************************************************************/

//����31//�����޸�����ĺ�����
AccountNode* Batch_Change_Password(AccountNode* Head, int m, char Account[], char Newpass[]) {
	AccountNode* pprev = Head;
	AccountNode* pcurrent = Head->Next;
	AccountNode* pcurrent_to_m = NULL;
	while (!(strcmp(pcurrent->Accountnum, Account) == 0)) {//�ҵ���ʼ�޸�����Ķ�Ӧ�˺š�
		pprev = pcurrent;
		pcurrent = pcurrent->Next;
	}
	pcurrent_to_m = pcurrent;//��pcurrent��ʼ�����룬pprev���øġ�
	int i = 0;
	for (i = 0; i < m|| pcurrent_to_m==NULL; i++) {
		strcpy(pcurrent_to_m->Password ,Newpass);//��pcurrent_to_m�����롣
		pcurrent_to_m = pcurrent_to_m->Next ;//pcurrent_to_mָ����һλ��
	}
	printf("�޸ĳɹ������޸���%d���˺ŵ����롣\n", m);

	Display_Account(Head);//��
	return Head;
}
/**************************************************************************************************************************/
AccountNode* Start_Logging_Account(AccountNode* Head)
{
	int i = 0;
	FILE* fp;
	if ((fp = fopen("LIST_Account.txt", "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ���!\n");
		exit(0);
	}

	AccountNode* prrev = Head; //β����
	AccountNode* newnode = NULL;

	for (i = 0; !feof(fp); i++)
	{
		char line[100]; // ���ڶ�ȡÿ�еĻ�����

		// ��ȡһ������
		if (fgets(line, sizeof(line), fp) == NULL)
			break; // �ļ��������ȡ��������ѭ��

		// �ж��Ƿ�Ϊ����
		if (strlen(line) <= 1) // ֻ�������з����г���Ϊ1
			break; // �ļ�ĩβΪ���У�����ѭ��

		newnode = (AccountNode*)malloc(sizeof(AccountNode)); //Ϊÿ��¼����˺���Ϣ���ٶ�̬�ڴ档
		sscanf(line, "%s\t%s\t%d\t%s\t%s\t%s", newnode->Accountnum, newnode->Password, &newnode->Attribute, newnode->Name, newnode->Phonenum, newnode->Email);
		newnode->Next = NULL;
		prrev->Next = newnode;
		prrev = newnode;
	}
	fclose(fp);
	return Head;
}
/**************************************************************************************************************************/
void Save_List_ToFile(AccountNode* Head)
{
	FILE* file = fopen("LIST_Account.txt", "w");  // ��д��ģʽ���ļ������ļ��������򴴽���������������ļ�����
	if (file == NULL) {
		printf("�޷����ļ�\n");
		return;
	}

	AccountNode* current = Head->Next;  // ������ͷ����ʼ����
	while (current != NULL) {
		fprintf(file, "%s \t%s \t%d \t%s \t %s\t %s\n", current->Accountnum, current->Password, current->Attribute, current->Name, current->Phonenum, current->Email);
		current = current->Next;  // ��������һ���ڵ�
	}
	fclose(file);  // �ر��ļ�
}

//����34//�ַ���ת���һά�������飺
int Str_To_IntArr(const char* Inputacc) {
	int length = strlen(Inputacc);
	int i = 0;
	int ans = 0;
	int* intArr = (int*)malloc(length * sizeof(int));  // Ϊ������������ڴ�ռ�

	if (intArr == NULL) {
		return NULL;  // ʧ��ʱ���ؿ�ָ��
	}

	for (i = 0; i < length; i++) {
		intArr[i] = Inputacc[i] - '0';  // ���ַ�ת��Ϊ�������洢������������
		ans = ans * 10 + intArr[i];
	}

	return ans;  // ������������ָ��
}
