#ifndef LOGIN_REGISTER_H
#define LOGIN_REGISTER_H

typedef struct Account
{
	char Accountnum[20];
	char Password[20];
	int Attribute;//Attribute意为“属性”，约定：学生 1 、教师 2 、管理员 3 ;
	char Name[30];
	char Phonenum[20];
	char Email[30];
	struct Account* Next;
}AccountNode;

AccountNode* Start_Logging_Account(AccountNode* Head);
AccountNode* Find_DiferHead(AccountNode* Head, int Attri);
void Display_Account(AccountNode* Head);

int Input_1toNum(int Num);
bool If_Inputs_1toNum(char Input[], int Num);
int Input_Num();
bool If_Inputs_Num(char Userinput8[]);

void Acc_Input_Right(char* Userinput);
void Acc_Input_Right_Tea(char* Userinput);
void Pass_Input_Right(char* Userinput);
void Phone_Input_Right(char* Userinput);
void Email_Input_Right(char* Userinput);

bool If_InputAcc_Format(char Input[]);
bool If_InputPass_Format(char Input[]);
bool If_InputPhone_Format(char Input[]);
bool If_InputEmail_Format(char Input[]);
bool If_InputAcc_Format_Tea(char Input[]);

bool If_AccPass_Match(int Attri, AccountNode* Head, char Intputacc[], char Intputpass[]);
AccountNode* Morm3_Match_Error(AccountNode* Head);


bool If_Acc_Exist(AccountNode* Head, char Input[]);
bool If_Phone_Exist(AccountNode* Head, char Input[]);
bool If_Email_Exist(AccountNode* Head, char Input[]);

AccountNode* Add_Account(AccountNode* Head);
AccountNode* Delete_Account(AccountNode* Head, char Account[]);
AccountNode* Change_Password(AccountNode* Head, char Account[]);

AccountNode* Phone_Change_Password(AccountNode* Head, char Inputphone[]);
AccountNode* Email_Change_Password(AccountNode* Head, char Inputemail[]);

int Readfile(AccountNode* Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri);//从 LIST_Account.txt 文件中批量读出的账号：
AccountNode* Access_AccList(AccountNode* Head, AccountNode* Diferhead, AccountNode* Accrr[], int Attri, int Num);
AccountNode* Batch_Delete_Account(AccountNode* Head, int m, char Account[]);
AccountNode* Batch_Change_Password(AccountNode* Head, int m, char Account[], char Newpass[]);

void Save_List_ToFile(AccountNode* Head);
int Login_Register_Main(int* ID);
void Free_account(AccountNode* Head);

int Str_To_IntArr(const char* Inputacc);
#endif