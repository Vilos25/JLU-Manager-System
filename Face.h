#ifndef FACE_H
#define FACE_H

//文件命名
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
//学籍变动菜单，包括显示链表内所有专业和年级,学籍查询，学籍变动（包含转专业和降级）
void Menu_StudentStatusChange();

void First_Load();
void End_Save();


#endif // !FACE_H
