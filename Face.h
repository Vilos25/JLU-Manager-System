#ifndef FACE_H
#define FACE_H

//�ļ�����
#define FILENAME_SUB "LIST_SubInfor.txt"
#define FILENAME_GRA "LIST_StdGrade.txt"
#define FILENAME_STD "LIST_StdInfor.txt"
#define FILENAME_TEA "LIST_teaInfor.txt"
void Menu_SubInfor();
void Menu_student(int ID);
void Menu_teacher(int ID);
void Menu_StdGrade(int ID);
void Menu_Admin();
void Menu_adminTeacher();
void Menu_adminStdGrade();
void Menu_adminStdInfor();
//ѧ���䶯�˵���������ʾ����������רҵ���꼶,ѧ����ѯ��ѧ���䶯������תרҵ�ͽ�����
void Menu_StudentStatusChange();

void First_Load();
void End_Save();


#endif // !FACE_H
