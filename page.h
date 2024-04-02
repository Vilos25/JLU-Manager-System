#ifndef PAGE_H
#define PAGE_H

void HideCursor();//隐藏光标
void AppearCursor();//开启光标
void cursor(int x, int y);//将光标定位到（x,y）位置上 
void Windowstime();//获取系统时间 
void welcome();//超市启动界面 
void PrintExit();//退出系统界面
//颜色从黑色渐变到白色
void ChangeConsoleColor(int duration);
void lockWindowSize();//锁定窗口大小
void setWindowSize(int width, int height);//修改窗口大小
// 获取当前窗口大小（包括边框）
void GetWindowSize();
// 获取当前客户区大小（不包括边框）
void GetClientSize();
#endif
