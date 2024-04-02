#ifndef FUNC_ISVAILD_H
#define FUNC_ISVAILD_H

#include <windows.h>
#include <stdbool.h>
//extern HWND currentWindow;


//����һ��������Ϊ��������ڸ�������ַ���
void Pass_Input_Line(char* Userinput);

//����3.5//����һ�����������ֵ��ַ������������ֵĳ���
int Input_Raw_Integer(int Num);

//����1��Num�ĵ������֣��������û����е���ѡ��ʱ�ġ�������󡱣���ֹ�û������������ַ����³����˳���
int Input_1toNum(int Num);

//���븡����
float Input_Float(int Integer, int Decimal);

//��������
void Input_Email(char* ans);

//����γ̱�ţ�����ͷ������ĸ���8�����ֵ��ַ���
void Input_SubNum(char* ans);

//�����޶�ѧ��
void Input_SemesterNum(char* ans);
//����3.5//����绰��
void Input_phoneNumber(char* ans);
//��������������ֵ��ַ������������ֵĳ���
void Input_charNumber(char* ans, int cnt);
//��������������֣��������ֵĳ���
int Input_intNumber(int cnt);
int Input_intNumberover(int cnt);
int Input_YN();

int Input_MF();



//�ȴ�Ĵ��룺
bool isValid_SubNum(const char* subNum);//�γ̱��
bool isValid_SemesterNum(const char* SemesterNum);//��ݺ�ѧ��
bool isValid_studentID(const char* studentID);//ѧ��ѧ��
bool isValid_id(const char* id);//����Ա����
bool isValid_majorNum(const char* majorNum);//רҵ���
bool isValid_majorName(const char* majorName);//רҵ����
bool isValid_name(const char* name);//����
bool isValid_grade(const char* grade);//�꼶
bool isValid_Class(const char* Class);//�༶
bool isValid_phoneNumber(const char* phoneNumber);//�绰��
bool isValid_SubName(const char* SubName);//�γ�����
bool isValid_politicalStatus(const char* politicalStatus);//������ò
bool isValid_gender(const char* gender);//�Ա�
bool isValid_Candidate(const char* Candidate);//�ڶ�
bool isValid_education(const char* education);//ѧ��
bool isValid_Accounttype(const char* Accounttype);//�˺�����
bool isValid_Password(const char* Password);//����
bool isValid_isExempted(const char* isExempted);//�Ƿ�����
bool isValid_isFailed(const char* isFailed);//�Ƿ�ҿ�
bool isValid_Score(const char* Score);//�ɼ�
bool isValid_Email(const char* email);//����


#endif // !ISVAILD_H

