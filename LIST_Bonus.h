#ifndef LIST_BONUS_H
#define LIST_BONUS_H

typedef struct Comp//竞赛
{
	char Accountnum[20];
	char CompName[50];
	char Winers[150];
	char ABC;
	int AwardGrade;
	char Sponsor[1000];//
	char Time[30];
	int Attribute;//Attribute意为“属性”，约定：批准 1 、审核中 2 、否决 3 ;
	float Ponit;
	struct Comp* Next;
}CompNote;

typedef struct Paper//论文
{
	char Accountnum[20];
	char PaperName[50];
	char Writers[150];  //第一作者才加分
	char Journal_Conference[150];//期刊名称/会议名称
	char Time[30];
	char Volume_Page[4][50]; //卷 / 期 / 论文号 / 页码范围
	int Attribute;
	float Ponit;
	struct Paper* Next;
}PaperNote;

typedef struct Proj//项目
{
	char Accountnum[20];
	char ProjName[50];
	char Members[150];
	char Advisor[30];
	char Start_time[30];
	char Finish_time[30];
	char ProjNum[30];
	int Role;  // 约定：1 为负责人，2 为第二名，3 为其它
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



BonusNote* Start_Logging_bonusFile(void);// 1 首次 从文件中录入 所有素质类加分信息
void Save_List_To_bonusFile(BonusNote* Head);//  将所有 加分项目 保存进文件

void Add_Mutiple_CompNote(BonusNote* Head);// 2 批量添加 多人的比赛项目
void Add_Mutiple_PaperNote(BonusNote* Head);// 3 批量添加 多人的论文信息
void Add_Mutiple_ProjNote(BonusNote* Head); // 4 批量添加 多人的国家级优秀结题项目信息

BonusNote* Add_Single_CompNote(BonusNote* Head, char Acc[], char Tea_Stu);// 5 录入单个 比赛项目 给某人
BonusNote* Add_Single_PaperNote(BonusNote* Head, char Acc[], char Tea_Stu);// 6 录入单个 论文项目 给某人
BonusNote* Add_Single_ProjNote(BonusNote* Head, char Acc[], char Tea_Stu);// 7 录入单个 结题项目 给某人

void Logging_CompNote(BonusNote* Head, CompNote* Comparr[], int Atri);// 8 从文件中批量录入 多人的比赛项目
void Logging_PaperNote(BonusNote* Head, PaperNote* Paperarr[], int Atri);// 9 从文件中批量录入 多人的论文信息
void Logging_ProjNote(BonusNote* Head, ProjNote* Projarr[], int Atri);// 10 从文件中批量录入 多人结题项目信息

void Save_CompList_ToFile(BonusNote* Head);// 11 将所有 比赛项目 保存进文件
void Save_PaperList_ToFile(BonusNote* Head);// 12 将所有 论文项目 保存进文件
void Save_ProjList_ToFile(BonusNote* Head);// 13 将所有 结题项目 保存进文件

float Calcul_Single_Bonusponit(BonusNote* Head, char Acc[]);// 17 计算 单个人 的有效加分绩点

void Display_Single_BonusNote(BonusNote* Head, int ID);// 18 打印 一个人 所有的加分项目

void Print_Single_Comp(CompNote* Head);// 19 打印 一个人 所有的比赛项目 (从人的角度打印）
void Print_Single_Paper(PaperNote* Head);// 20 打印 一个人 所有的论文项目
void Print_Single_Proj(ProjNote* Head);// 21 打印 一个人 所有的结题项目

void Display_All_CompNote(BonusNote* Head);// 22 打印 比赛项目 的所有加分内容 （从三大类项目的角度打印）
void Display_All_PaperNote(BonusNote* Head);// 23 打印 论文项目 的所有加分内容
void Display_All_ProjNote(BonusNote* Head);// 24 打印 结题项目 的所有加分内容

void Display_All_BonusInform(BonusNote* Head);// 25 打印 所有素质类加分信息

//以下是输入检查函数：
void Comp_Name_Input_Right(char* Compname);// 26 输入+检索 比赛名称
void Input_ABC(char* ABC);// 28 输入+检查 'A'/'B'/'C'
void Sponsor_Input_Right(char* Sponsor);// 29 输入+检索 主办单位名称
void Time_Input_Right(char* Time);// 30 输入+检查 时间

void Journal_Input_Right(char* Journal);// 31 输入+检索 期刊名称/会议名称
void Volume_Page_Input_Right(char Volume_Page[4][50]);// 32 输入+检查 卷/期/论文号/页码范围

void Pronum_Input_Right(char* ProjNum);// 34 输入+检查 项目编号

void Int_To_Str(int number, char* result);// 35 数字ID转成字符串账号

void Delet_Bonus(BonusNote* Head, int ID);// 36 学生自己选择删除部分加分项目
void Tea_Audit(BonusNote* Head, int TeaID);// 37 教师审核所有未审核的素质类加分

void Add_BonusNote_Node(BonusNote* Head, int ID, char Name[]);//增加学生节点，传入int类型的学号，char类型的姓名，返回一个新的学生节点

BonusNote* Find_BonusNote_ByAcc(BonusNote* Head, int ID);//通过账号查找学生节点，返回该节点的指针
#endif // !LIST_BONUS_H

