#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"page.h"

/*Window Size: 1186 x 618
Client Size: 1173 x 611*/

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
/*��ɫ����������ʮ����������ָ�� -- ��һ��
��Ӧ�ڱ������ڶ�����Ӧ��ǰ����ÿ������
����Ϊ�����κ�ֵ:

    0 = ��ɫ       8 = ��ɫ
    1 = ��ɫ       9 = ����ɫ
    2 = ��ɫ       A = ����ɫ
    3 = ǳ��ɫ     B = ��ǳ��ɫ
    4 = ��ɫ       C = ����ɫ
    5 = ��ɫ       D = ����ɫ
    6 = ��ɫ       E = ����ɫ
    7 = ��ɫ       F = ����ɫ
*/
//�������� 
void welcome() {
	system("color 07");	//����Ϊ���ֺڵ�
	HideCursor();		//Ϊ������ ���ع�� 
	cursor(0, 21);		//����궨λ��(0��21)��
	Windowstime();		//��ʾϵͳʱ�� 
	int i, j;
	cursor(39, 8);
	printf("��ӭʹ��<���ִ�ѧ�������ɼ�����ϵͳ>");
	cursor(53, 12);
	printf("������...");
	cursor(20, 28);
	printf("Powered By��������[�ƿ�23��05������һ��] <����ε> <ŷ����> <ʩ��> <�ȴ�ʨͯ>\n");
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
	cursor(45, 12);
	printf("�������!");
	//ChangeConsoleColor(2);	//��ɫ�Ӻ�ɫ���䵽��ɫ
	Sleep(100);
	system("color 70");	//����Ϊ���ְ׵�
	lockWindowSize();
	//setWindowSize(1680, 1024);	//�޸Ĵ��ڴ�С)
	//GetWindowSize();
	system("pause");
	//setWindowSize(1186, 618);	//�޸Ĵ��ڴ�С)
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


// �������ڽ�����̨���ڵı���ɫ�Ӻ�ɫ���䵽��ɫ
void ChangeConsoleColor(int duration) {
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);

	// ������ɫ����
	int dr = GetRValue(white) / duration;
	int dg = GetGValue(white) / duration;
	int db = GetBValue(white) / duration;

	COLORREF color = black;

	for (int i = 0; i < duration; i++) {
		color = RGB(GetRValue(color) + dr, GetGValue(color) + dg, GetBValue(color) + db);

		// ���ÿ���̨���ڱ���ɫ
		SetBkColor(hdc, color);
		system("cls");  // ��տ���̨��Ļ�������ػ�

		// ��ʱһ��ʱ��
		Sleep(1000);
	}

	ReleaseDC(hwnd, hdc);
}

// �������ڴ�С
void lockWindowSize() {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

// �޸Ĵ��ڴ�С
void setWindowSize(int width, int height) {
	HWND hwnd = GetConsoleWindow();
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	POINT topLeft;
	topLeft.x = 0;
	topLeft.y = 0;
	ClientToScreen(hwnd, &topLeft);

	POINT bottomRight;
	bottomRight.x = width;
	bottomRight.y = height;
	ClientToScreen(hwnd, &bottomRight);

	int newWidth = bottomRight.x - topLeft.x;
	int newHeight = bottomRight.y - topLeft.y;

	if (SetWindowPos(hwnd, HWND_TOP, topLeft.x, topLeft.y, newWidth, newHeight, SWP_SHOWWINDOW)) {
		printf("Window size modified successfully.\n");
	}
	else {
		printf("Failed to modify window size.\n");
	}
}

// ��ȡ��ǰ���ڴ�С�������߿�
void GetWindowSize() {
	HWND hwnd = GetForegroundWindow();
	RECT rect;
	GetWindowRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	printf("Window Size: %d x %d\n", width, height);
}

// ��ȡ��ǰ�ͻ�����С���������߿�
void GetClientSize() {
	HWND hwnd = GetForegroundWindow();
	RECT rect;
	GetClientRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	printf("Client Size: %d x %d\n", width, height);
}

