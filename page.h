#ifndef PAGE_H
#define PAGE_H

void HideCursor();//���ع��
void AppearCursor();//�������
void cursor(int x, int y);//����궨λ����x,y��λ���� 
void Windowstime();//��ȡϵͳʱ�� 
void welcome();//������������ 
void PrintExit();//�˳�ϵͳ����
//��ɫ�Ӻ�ɫ���䵽��ɫ
void ChangeConsoleColor(int duration);
void lockWindowSize();//�������ڴ�С
void setWindowSize(int width, int height);//�޸Ĵ��ڴ�С
// ��ȡ��ǰ���ڴ�С�������߿�
void GetWindowSize();
// ��ȡ��ǰ�ͻ�����С���������߿�
void GetClientSize();
#endif
