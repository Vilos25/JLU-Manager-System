#ifndef LIST_BONUS_H
#define LIST_BONUS_H

typedef struct Comp//����
{
	char Accountnum[20];
	char CompName[50];
	char Winers[150];
	char ABC;
	int AwardGrade;
	char Sponsor[1000];//
	char Time[30];
	int Attribute;//Attribute��Ϊ�����ԡ���Լ������׼ 1 ������� 2 ����� 3 ;
	float Ponit;
	struct Comp* Next;
}CompNote;

typedef struct Paper//����
{
	char Accountnum[20];
	char PaperName[50];
	char Writers[150];  //��һ���߲żӷ�
	char Journal_Conference[150];//�ڿ�����/��������
	char Time[30];
	char Volume_Page[4][50]; //�� / �� / ���ĺ� / ҳ�뷶Χ
	int Attribute;
	float Ponit;
	struct Paper* Next;
}PaperNote;

typedef struct Proj//��Ŀ
{
	char Accountnum[20];
	char ProjName[50];
	char Members[150];
	char Advisor[30];
	char Start_time[30];
	char Finish_time[30];
	char ProjNum[30];
	int Role;  // Լ����1 Ϊ�����ˣ�2 Ϊ�ڶ�����3 Ϊ����
	int Attribute;
	float Ponit;
	struct Proj* Next;
}ProjNote;

typedef struct Bonus
{
	char Accountnum[20];
	char Name[30];
	CompNote* Comphead;
	PaperNote* Paperhead;
	ProjNote* Projhead;
	float Bonusponit;
	struct Bonus* Next;
}BonusNote;



BonusNote* Start_Logging_bonusFile(void);// 1 �״� ���ļ���¼�� ����������ӷ���Ϣ
void Save_List_To_bonusFile(BonusNote* Head);//  ������ �ӷ���Ŀ ������ļ�

void Add_Mutiple_CompNote(BonusNote* Head);// 2 ������� ���˵ı�����Ŀ
void Add_Mutiple_PaperNote(BonusNote* Head);// 3 ������� ���˵�������Ϣ
void Add_Mutiple_ProjNote(BonusNote* Head); // 4 ������� ���˵Ĺ��Ҽ����������Ŀ��Ϣ

BonusNote* Add_Single_CompNote(BonusNote* Head, char Acc[], char Tea_Stu);// 5 ¼�뵥�� ������Ŀ ��ĳ��
BonusNote* Add_Single_PaperNote(BonusNote* Head, char Acc[], char Tea_Stu);// 6 ¼�뵥�� ������Ŀ ��ĳ��
BonusNote* Add_Single_ProjNote(BonusNote* Head, char Acc[], char Tea_Stu);// 7 ¼�뵥�� ������Ŀ ��ĳ��

void Logging_CompNote(BonusNote* Head, CompNote* Comparr[], int Atri);// 8 ���ļ�������¼�� ���˵ı�����Ŀ
void Logging_PaperNote(BonusNote* Head, PaperNote* Paperarr[], int Atri);// 9 ���ļ�������¼�� ���˵�������Ϣ
void Logging_ProjNote(BonusNote* Head, ProjNote* Projarr[], int Atri);// 10 ���ļ�������¼�� ���˽�����Ŀ��Ϣ

void Save_CompList_ToFile(BonusNote* Head);// 11 ������ ������Ŀ ������ļ�
void Save_PaperList_ToFile(BonusNote* Head);// 12 ������ ������Ŀ ������ļ�
void Save_ProjList_ToFile(BonusNote* Head);// 13 ������ ������Ŀ ������ļ�

//BonusNote* Modify_CompAttr(BonusNote* Head, char Acc[], char Compname[]);// 14 �޸� ���˵ı�����Ŀ �ӷ�״̬
//BonusNote* Modify_PaperAttr(BonusNote* Head, char Acc[], char Papername[]);// 15 �޸� ���˵�������Ŀ �ӷ�״̬
//BonusNote* Modify_ProjAttr(BonusNote* Head, char Acc[], char Projname[]);// 16 �޸� ���˵Ľ�����Ŀ �ӷ�״̬

float Calcul_Single_Bonusponit(BonusNote* Head, char Acc[]);// 17 ���� ������ ����Ч�ӷּ���

void Display_Single_BonusNote(BonusNote* Head, int ID);// 18 ��ӡ һ���� ���еļӷ���Ŀ

void Print_Single_Comp(CompNote* Head);// 19 ��ӡ һ���� ���еı�����Ŀ (���˵ĽǶȴ�ӡ��
void Print_Single_Paper(PaperNote* Head);// 20 ��ӡ һ���� ���е�������Ŀ
void Print_Single_Proj(ProjNote* Head);// 21 ��ӡ һ���� ���еĽ�����Ŀ

void Display_All_CompNote(BonusNote* Head);// 22 ��ӡ ������Ŀ �����мӷ����� ������������Ŀ�ĽǶȴ�ӡ��
void Display_All_PaperNote(BonusNote* Head);// 23 ��ӡ ������Ŀ �����мӷ�����
void Display_All_ProjNote(BonusNote* Head);// 24 ��ӡ ������Ŀ �����мӷ�����

void Display_All_BonusInform(BonusNote* Head);// 25 ��ӡ ����������ӷ���Ϣ

//�����������麯����
void Comp_Name_Input_Right(char* Compname);// 26 ����+���� ��������
void Input_ABC(char* ABC);// 28 ����+��� 'A'/'B'/'C'
void Sponsor_Input_Right(char* Sponsor);// 29 ����+���� ���쵥λ����
void Time_Input_Right(char* Time);// 30 ����+��� ʱ��

void Journal_Input_Right(char* Journal);// 31 ����+���� �ڿ�����/��������
void Volume_Page_Input_Right(char Volume_Page[4][50]);// 32 ����+��� ��/��/���ĺ�/ҳ�뷶Χ

void Pronum_Input_Right(char* ProjNum);// 34 ����+��� ��Ŀ���

void Int_To_Str(int number, char* result);// 35 ����IDת���ַ����˺�

void Delet_Bonus(BonusNote* Head, int ID);// 36 ѧ���Լ�ѡ��ɾ�����ּӷ���Ŀ
void Tea_Audit(BonusNote* Head, int TeaID);// 37 ��ʦ�������δ��˵�������ӷ�

//����ѧ���ڵ㣬����int���͵�ѧ�ţ�char���͵�����������һ���µ�ѧ���ڵ�
void Add_BonusNote_Node(BonusNote* Head, int ID, char Name[]);

//ͨ���˺Ų���ѧ���ڵ㣬���ظýڵ��ָ��
BonusNote* Find_BonusNote_ByAcc(BonusNote* Head, int ID);
#endif // !LIST_BONUS_H

