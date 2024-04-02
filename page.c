#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include"page.h"

/*Window Size: 1186 x 618
Client Size: 1173 x 611*/

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
/*颜色属性由两个十六进制数字指定 -- 第一个
对应于背景，第二个对应于前景。每个数字
可以为以下任何值:

    0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 浅绿色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色
*/
//启动界面 
void welcome() {
	system("color 07");	//设置为白字黑底
	HideCursor();		//为了美观 隐藏光标 
	cursor(0, 21);		//将光标定位在(0，21)处
	Windowstime();		//显示系统时间 
	int i, j;
	cursor(39, 8);
	printf("欢迎使用<吉林大学本科生成绩管理系统>");
	cursor(53, 12);
	printf("启动中...");
	cursor(20, 28);
	printf("Powered By————[计科23级05班课设第一组] <王率蔚> <欧丹丹> <施宇> <谷村狮童>\n");
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
	cursor(45, 12);
	printf("加载完成!");
	//ChangeConsoleColor(2);	//颜色从黑色渐变到白色
	Sleep(100);
	system("color 70");	//设置为黑字白底
	lockWindowSize();
	//setWindowSize(1680, 1024);	//修改窗口大小)
	//GetWindowSize();
	system("pause");
	//setWindowSize(1186, 618);	//修改窗口大小)
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


// 函数用于将控制台窗口的背景色从黑色渐变到白色
void ChangeConsoleColor(int duration) {
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	COLORREF black = RGB(0, 0, 0);
	COLORREF white = RGB(255, 255, 255);

	// 计算颜色增量
	int dr = GetRValue(white) / duration;
	int dg = GetGValue(white) / duration;
	int db = GetBValue(white) / duration;

	COLORREF color = black;

	for (int i = 0; i < duration; i++) {
		color = RGB(GetRValue(color) + dr, GetGValue(color) + dg, GetBValue(color) + db);

		// 设置控制台窗口背景色
		SetBkColor(hdc, color);
		system("cls");  // 清空控制台屏幕并触发重绘

		// 延时一段时间
		Sleep(1000);
	}

	ReleaseDC(hwnd, hdc);
}

// 锁定窗口大小
void lockWindowSize() {
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

// 修改窗口大小
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

// 获取当前窗口大小（包括边框）
void GetWindowSize() {
	HWND hwnd = GetForegroundWindow();
	RECT rect;
	GetWindowRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	printf("Window Size: %d x %d\n", width, height);
}

// 获取当前客户区大小（不包括边框）
void GetClientSize() {
	HWND hwnd = GetForegroundWindow();
	RECT rect;
	GetClientRect(hwnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	printf("Client Size: %d x %d\n", width, height);
}

