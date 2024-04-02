#ifndef FUNC_ISVAILD_H
#define FUNC_ISVAILD_H

#include <windows.h>
#include <stdbool.h>
//extern HWND currentWindow;


//输入一行内容作为口令，并且掩盖输入的字符串
void Pass_Input_Line(char* Userinput);

//函数3.5//输入一个仅包含数字的字符串，传入数字的长度
int Input_Raw_Integer(int Num);

//输入1到Num的单个数字，并纠正用户进行单项选择时的“输入错误”，防止用户因输入其它字符导致程序退出：
int Input_1toNum(int Num);

//输入浮点数
float Input_Float(int Integer, int Decimal);

//输入邮箱
void Input_Email(char* ans);

//输入课程编号，包含头两个字母外加8个数字的字符串
void Input_SubNum(char* ans);

//输入修读学期
void Input_SemesterNum(char* ans);
//函数3.5//输入电话号
void Input_phoneNumber(char* ans);
//输入仅仅包含数字的字符串，传入数字的长度
void Input_charNumber(char* ans, int cnt);
//输入仅仅包含数字，传入数字的长度
int Input_intNumber(int cnt);


int Input_YN();

int Input_MF();



//谷村的代码：
bool isValid_SubNum(const char* subNum);//课程编号
bool isValid_SemesterNum(const char* SemesterNum);//年份和学期
bool isValid_studentID(const char* studentID);//学生学号
bool isValid_id(const char* id);//辅导员工号
bool isValid_majorNum(const char* majorNum);//专业编号
bool isValid_majorName(const char* majorName);//专业名称
bool isValid_name(const char* name);//姓名
bool isValid_grade(const char* grade);//年级
bool isValid_Class(const char* Class);//班级
bool isValid_phoneNumber(const char* phoneNumber);//电话号
bool isValid_SubName(const char* SubName);//课程名称
bool isValid_politicalStatus(const char* politicalStatus);//政治面貌
bool isValid_gender(const char* gender);//性别
bool isValid_Candidate(const char* Candidate);//在读
bool isValid_education(const char* education);//学历
bool isValid_Accounttype(const char* Accounttype);//账号类型
bool isValid_Password(const char* Password);//密码
bool isValid_isExempted(const char* isExempted);//是否免修
bool isValid_isFailed(const char* isFailed);//是否挂科
bool isValid_Score(const char* Score);//成绩
bool isValid_Email(const char* email);//邮箱


#endif // !ISVAILD_H

