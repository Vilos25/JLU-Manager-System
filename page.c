#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"page.h"
//隐藏光标 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//开启光标 
void AppearCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//将光标定位到（x,y）位置上 
void cursor(int x, int y)
{
	COORD coord;  // COORD是 Windows API中定义的一种结构 本质是一种结构体 
	coord.X = x;
	coord.Y = y;

	//GetStdHandle(STD_OUTPUT_HANDLE)是获取当前窗口的句柄 
	//SetConsoleCursorPosition(HANDLE,COORD)是将句柄（光标）设置到coord所在的坐标位置上 

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//获取系统时间 
void Windowstime()
{
	SYSTEMTIME sys;
	printf("\t\t\t\t\t  当前时间为：");
	GetLocalTime(&sys); //获取系统时间到程序的函数 
	printf("%4d-%02d-%02d %02d:%02d \n\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute); //按照年/月/日 时/分 格式打印
	return;
}
//启动界面 
void welcome() {
	system("color F4");	//设置为红字白底
	HideCursor();		//为了美观 隐藏光标 
	cursor(0, 21);		//将光标定位在(0，21)处
	Windowstime();		//显示系统时间 
	int i, j;
	cursor(44, 8);
	printf("欢迎使用成绩管理系统");
	cursor(53, 12);
	printf("启动中...");
	for (i = 0; i <= 100; i++) {
		cursor(28, 16);
		printf("<");
		for (j = 0; j < 50; j++) {	//打印进度条 
			if (j < i / 2)
				printf("*");
			else printf("o");
		}
		printf(">");
		printf("%d%%", i); //输出i%，%%为% 
		Sleep(20);	//每 20ms 进一格 
	}
	return;
}

//退出系统界面 
void PrintExit() {		//同启动界面 
	system("cls");
	system("color 8F");	//设置为金字黑底 
	HideCursor();
	cursor(0, 21);
	Windowstime();
	int i, j;
	cursor(44, 8);
	printf("感谢使用学生成绩管理系统");
	cursor(49, 12);
	printf("数据保存中...");
	for (i = 0; i <= 100; i++) {
		cursor(28, 16);
		printf("<");
		for (j = 0; j < 50; j++) {
			if (j < i / 2)
				printf("*");
			else printf("o");
		}
		printf(">");
		printf("%d%%", i);
		Sleep(5);
	}
	cursor(0, 26);
	return;
}