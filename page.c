#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"page.h"
//���ع�� 
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//������� 
void AppearCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
//����궨λ����x,y��λ���� 
void cursor(int x, int y)
{
	COORD coord;  // COORD�� Windows API�ж����һ�ֽṹ ������һ�ֽṹ�� 
	coord.X = x;
	coord.Y = y;

	//GetStdHandle(STD_OUTPUT_HANDLE)�ǻ�ȡ��ǰ���ڵľ�� 
	//SetConsoleCursorPosition(HANDLE,COORD)�ǽ��������꣩���õ�coord���ڵ�����λ���� 

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//��ȡϵͳʱ�� 
void Windowstime()
{
	SYSTEMTIME sys;
	printf("\t\t\t\t\t  ��ǰʱ��Ϊ��");
	GetLocalTime(&sys); //��ȡϵͳʱ�䵽����ĺ��� 
	printf("%4d-%02d-%02d %02d:%02d \n\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute); //������/��/�� ʱ/�� ��ʽ��ӡ
	return;
}
//�������� 
void welcome() {
	system("color F4");	//����Ϊ���ְ׵�
	HideCursor();		//Ϊ������ ���ع�� 
	cursor(0, 21);		//����궨λ��(0��21)��
	Windowstime();		//��ʾϵͳʱ�� 
	int i, j;
	cursor(44, 8);
	printf("��ӭʹ�óɼ�����ϵͳ");
	cursor(53, 12);
	printf("������...");
	for (i = 0; i <= 100; i++) {
		cursor(28, 16);
		printf("<");
		for (j = 0; j < 50; j++) {	//��ӡ������ 
			if (j < i / 2)
				printf("*");
			else printf("o");
		}
		printf(">");
		printf("%d%%", i); //���i%��%%Ϊ% 
		Sleep(20);	//ÿ 20ms ��һ�� 
	}
	return;
}

//�˳�ϵͳ���� 
void PrintExit() {		//ͬ�������� 
	system("cls");
	system("color 8F");	//����Ϊ���ֺڵ� 
	HideCursor();
	cursor(0, 21);
	Windowstime();
	int i, j;
	cursor(44, 8);
	printf("��лʹ��ѧ���ɼ�����ϵͳ");
	cursor(49, 12);
	printf("���ݱ�����...");
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