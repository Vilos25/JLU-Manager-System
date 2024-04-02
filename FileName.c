/*用 system(“color 0A”); 其中color后面的0是背景色代号，A是前景色代号。各颜色代码如下：
0=黑色 1=蓝色 2=绿色 3=湖蓝色 4=红色 5=紫色 6=黄色 7=白色 8=灰色 9=淡蓝色
A=淡绿色 B=淡浅绿色 C=淡红色 D=淡紫色 E=淡黄色 F=亮白色
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#include<string.h>
#define N 60
#define M 6
typedef struct student
{
	long long studentID;//学号 
	char studentname[15];//姓名 
	float score[M]; //M门课成绩 
	float aver;//M门课总分 
	float aver_;//M门课平均分 
}STUDENT;
int Inputscore(STUDENT stu[], int m);//输入学生信息并记录总学生数 
void Averscore(STUDENT stu[], int n, int m);//计算总分 以及平均分 
void Rankscore(STUDENT stu[], int n, int (*p)(float, float));//用指向函数的指针按总分升序排序或降序排序 
int Rankscore1(float a, float b);//按总分升序排序
int Rankscore2(float a, float b);//按总分降序排序 
void Studentscore(STUDENT stu[], int n, int (*f)(long long, long long));//用指向函数的指针按学号升序排序或降序排序
int Studentscore1(long long x, long long y);//按学号升序排序
int Studentscore2(long long x, long long y);//按学号降序排序
int Findscore(STUDENT stu[], long long studentID, int n);//查找学号为studentID的学生信息，并返回其下标i
int Findname(STUDENT stu[], char a[], int n);//按学生姓名查找学生，并返回其下标i 
int Deletescore(STUDENT stu[], int i, int n);//删除学号为studentID的学生信息，并返回此时还有的学生总人数 
int Appendscore(STUDENT stu[], int n, int m);//添加一个学生信息 
void Printscore(STUDENT stu[], int n, int m);//输出各学生所有信息及相应成绩
void Printscore_(STUDENT stu[], int i, int m);//将学号为studentID的学生信息输出 
int Readfile(STUDENT stu[], int m);//将学生信息从D:\\student_file.txt读出 
void Writefile(STUDENT stu[], int n, int m);//将学生信息写入D:\\studentfile.txt 
int main()
{
	int n, i, m;//指定要输入的课程门数，以及记录输入学生人数 
	long long studentID;
	char ch;
	char a[15];
	STUDENT stu[N];
	system("color F6");//实现界面,白色背景，黄色字体 
	do {
		system("cls");//清屏
		printf("***********************************************************************\n");
		printf("			****输入选择****	\n \n");
		printf("	1.如果你想将student_file.txt中的学生信息读出并显示，请输入G/g！\n \n");
		printf("	2.如果你想手动输入学生信息请输入H/h！\n \n");
		printf("***********************************************************************\n");
		scanf(" %c", &ch);
		if (ch == 'G' || ch == 'g')
		{
			printf("请输入学生学科数目m：\n");
			scanf("%d", &m);
			n = Readfile(stu, m);
			printf("student_file.txt读出成功！！！\n");
			Printscore(stu, n, m);
			Sleep(5000); //暂停程序5秒
		}
		else if (ch == 'H' || ch == 'h')
		{
			printf("请输入学生学科数目m：\n");
			scanf("%d", &m);
			printf("请输入学生信息:\n");
			n = Inputscore(stu, m);
		}
		else
		{
			printf("没有该选项！！！请输入I/i进行重新选择\n");
			scanf(" %c", &ch);
		}
	} while (ch == 'I' || ch == 'i');
	printf("我将计算各学生总分和平均分!\n");
	Averscore(stu, n, m);
	Sleep(2000);//使程序暂停两秒 
	do {
		system("cls");
		printf("您可以进行以下操作：\n \n");
		printf("***********************************************************************\n");
		printf("		………………****功能菜单****………………	");
		printf("\n");
		printf("	1.如果你想按总分排序并输出请输入A/a!	\n");
		printf("\n");
		printf("	2.如果你想按学号查找并输出该学生信息请输入B/b!\n");
		printf("\n");
		printf("	3.如果你想按姓名查找并输出该学生信息请输入U/u!\n");
		printf("\n");
		printf("	4.如果你想按学号查找并删除该学生信息并输出剩余学生信息请输入C/c!\n");
		printf("\n");
		printf("	5.如果你想按姓名查找并删除该学生信息并输出剩余学生信息请输入L/l!\n");
		printf("\n");
		printf("	6.如果你想按学号排序并输出学生信息请输入D/d!\n");
		printf("\n");
		printf("	7.如果你想添加一个学生信息并输出当前学生信息请输入E/e!\n \n");
		printf("***********************************************************************\n");
		scanf(" %c", &ch);
		if (ch == 'A' || ch == 'a')
		{
			system("cls");
			printf("按总分升序排序请输入X/x!\n \n");
			printf("按总分降序排序请输入Y/y!\n");
			scanf(" %c", &ch);
			do {
				if (ch == 'X' || ch == 'x')
				{
					Rankscore(stu, n, Rankscore1);
					Printscore(stu, n, m);
				}
				else if (ch == 'Y' || ch == 'y')
				{
					Rankscore(stu, n, Rankscore2);
					Printscore(stu, n, m);
				}
				else
				{
					printf("没有该功能选项！请输入V/v重新进入选择！！！\n");
					scanf(" %c", &ch);
				}
			} while (ch == 'V' || ch == 'v');
		}
		else if (ch == 'B' || ch == 'b')
		{
			system("cls");
			printf("请输入你想查找的学生学号:\n");
			scanf("%lld", &studentID);
			i = Findscore(stu, studentID, n);
			if (i == n - 1)
			{
				printf("不存在该学生信息！！！\n");
			}
			else
			{
				Printscore_(stu, i, m);
			}
		}
		else if (ch == 'U' || ch == 'u')
		{
			system("cls");
			printf("请输入你想查找学生姓名：\n");
			scanf("%s", a);
			i = Findname(stu, a, n);
			if (i == n - 1)
			{
				printf("不存在该学生信息！！！\n");
			}
			else
			{
				Printscore_(stu, i, m);
			}
		}
		else if (ch == 'C' || ch == 'c')
		{
			system("cls");
			printf("请输入你想删除的学生学号:\n");
			scanf("%lld", &studentID);
			i = Findscore(stu, studentID, n);
			if (i == n - 1)
			{
				printf("不存在该学生信息！！！\n");
			}
			else
			{
				n = Deletescore(stu, i, n);
				printf("剩余学生信息：\n");
				Printscore(stu, n, m);
			}
		}
		else if (ch == 'L' || ch == 'l')
		{
			system("cls");
			printf("请输入你想删除的学生学号:\n");
			scanf("%s", a);
			i = Findname(stu, a, n);
			if (i == n - 1)
			{
				printf("不存在该学生信息！！！\n");
			}
			else
			{
				n = Deletescore(stu, i, n);
				printf("剩余学生信息：\n");
				Printscore(stu, n, m);
			}
		}
		else if (ch == 'D' || ch == 'd')
		{
			do {
				system("cls");
				printf("按学号升序排序请输入P/p！\n");
				printf("\n");
				printf("按学号降序排序请输入O/o！\n");
				scanf(" %c", &ch);
				if (ch == 'P' || ch == 'p')
				{
					printf("按学号升序排序如下：\n");
					Studentscore(stu, n, Studentscore1);
					Printscore(stu, n, m);
				}
				else if (ch == 'O' || ch == 'o')
				{
					printf("按学号降序排序如下：\n");
					Studentscore(stu, n, Studentscore2);
					Printscore(stu, n, m);
				}
				else
				{
					printf("没有该选项！请输入S/s后重新进入功能！！！\n");
					scanf(" %c", &ch);
				}
			} while (ch == 'S' || ch == 's');
		}
		else if (ch == 'E' || ch == 'e')
		{
			system("cls");
			n = Appendscore(stu, n, m);
			Printscore(stu, n, m);
		}
		else
		{
			system("cls");
			printf("没有该功能选项!!!\n");
		}
		printf("如果你还想对学生信息进行操作请输入T/t!\n");
		scanf(" %c", &ch);
	} while (ch == 'T' || ch == 't');
	do {
		system("cls");
		printf("是否将学生信息写入studentfile.txt文件？\n");
		printf("若要写入保存请输入W/w:\n");
		scanf(" %c", &ch);
		if (ch == 'W' || ch == 'w')
		{
			Writefile(stu, n, m);
			printf("已成功将学生信息写入studentfile.txt!!!\n");
		}
		else
		{
			printf("文件还未保存是否放弃保存？\n");
			printf("若要保存请输入M/m:\n");
			scanf(" %c", &ch);
		}
	} while (ch == 'M' || ch == 'm');
	return 0;
}
//输入n个学生的学号，姓名，m门课程的成绩到结构体数组stu中 ,直到输入的分数为负数为止 
int Inputscore(STUDENT stu[], int m)
{
	int i = -1, j;
	do {
		i++;
		printf("Input record %d:学号：\t \t姓名:\t科目一成绩：\t科目二成绩：\t科目三成绩：\n", i + 1);
		scanf("%lld", &stu[i].studentID);
		scanf("%s", stu[i].studentname);//姓名可以输入汉字 
		for (j = 0; j < m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	} while (stu[i].score[0] >= 0 && stu[i].score[1] >= 0 && stu[i].score[2] >= 0);
	return i;
}
//计算各个学生的m门课程总分，存到aver中
void Averscore(STUDENT stu[], int n, int m)
{
	int i, j;
	float sum;
	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j < m; j++)
		{
			sum += stu[i].score[j];
		}
		stu[i].aver = sum;
		stu[i].aver_ = sum / m;
	}
}
//按学号升序排序或降序排序 
void Studentscore(STUDENT stu[], int n, int (*f)(long long, long long))
{
	STUDENT test;//声明一个结构体变量，在交换时实现信息全部交换 
	int i, j, k;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if ((*f)(stu[k].studentID, stu[j].studentID))
				k = j;
		}
		if (k != i)
		{
			test = stu[i];
			stu[i] = stu[k];
			stu[k] = test;
		}
	}
}
//利用指向函数的指针调用进行学号升序排序 
int Studentscore1(long long x, long long y)
{
	return x > y;
}
//利用指向函数的指针调用进行学号降序排序 
int Studentscore2(long long x, long long y)
{
	return x < y;
}
//按成绩排序从高到低 
void Rankscore(STUDENT stu[], int n, int (*p)(float, float))
{
	int i, j, k;
	STUDENT temp;
	for (i = 0; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if ((*p)(stu[k].aver, stu[j].aver))
				k = j;
		}
		if (k != i)
		{
			temp = stu[i];
			stu[i] = stu[k];
			stu[k] = temp;
		}
	}
}
//按总分升序排序
int Rankscore1(float a, float b)
{
	return a > b;
}
//按总分降序排序 
int Rankscore2(float a, float b)
{
	return a < b;
}
// 查找学号为studentID的学生信息，并返回其下标i
int Findscore(STUDENT stu[], long long studentID, int n)
{
	int i = 0;
	while (stu[i].studentID != studentID)
	{
		i++;
		if (i == n - 1)
		{
			return n - 1;//若执行该语句则证明，没有需要查找的学生信息 
		}
	}
	return i;
}
//按学生姓名查找学生，并返回其下标i 
int Findname(STUDENT stu[], char a[], int n)
{
	int i = 0;
	while (strcmp(stu[i].studentname, a))//按姓名查找学生，strcmp()函数严格区分大小写 
	{
		i++;
		if (i == n - 1)
		{
			return n - 1;//若执行该语句则证明，没有需要查找的学生信息 
		}
	}
	return i;
}
//将学号为studentID的学生信息输出 
void Printscore_(STUDENT stu[], int i, int m)
{
	int j;
	printf("学号：\t \t姓名:\t科目一成绩：\t科目二成绩：\t科目三：\t总分：\t平均分：\n");
	printf("%lld\t%s\t", stu[i].studentID, stu[i].studentname);
	for (j = 0; j < m; j++)
	{
		printf("%.2f\t \t", stu[i].score[j]);
	}
	printf("%.2f\t%.2f\n", stu[i].aver, stu[i].aver_);
}
//删除学号为studentID的学生信息，并返回此时还有的学生总人数 
int Deletescore(STUDENT stu[], int i, int n)
{
	for (; i + 1 < n; i++)//应用顺序表的思想将删除后的学生信息依次向前移 
	{
		stu[i] = stu[i + 1];
	}
	return i;//当i+1=n时退出循环，此时i为删除 studentID后的学生总人数 
}
//添加一个学生信息 
int Appendscore(STUDENT stu[], int n, int m)
{
	int i;
	float sum = 0;
	printf("请输入要添加学生信息：\n");
	printf("学号：\t \t姓名:\t科目一成绩：\t科目二成绩：\t科目三成绩：\n");
	scanf("%lld %s", &stu[n].studentID, stu[n].studentname);
	for (i = 0; i < m; i++)
	{
		scanf("%f", &stu[n].score[i]);
		sum += stu[n].score[i];
	}
	//由于新加入的学生没有总分和平均分，所以需要计算出来
	stu[n].aver = sum;
	stu[n].aver_ = sum / m;
	return n + 1;//此时学生总人数为n+1 
}
//将学生信息从D:\\student_file.txt读出 
int Readfile(STUDENT stu[], int m)
{
	int i, j;
	FILE* fp;
	if ((fp = fopen("D:\\student_file.txt", "r+")) == NULL)
	{
		printf("文件打开失败！！!\n");
		exit(0);
	}
	for (i = 0; !feof(fp); i++)
	{
		fscanf(fp, "%lld\t%s\t", &stu[i].studentID, stu[i].studentname);
		for (j = 0; j < m; j++)
		{
			fscanf(fp, "%f\t \t", &stu[i].score[j]);//读出时不能以%.2f形式 !!!!
		}
		stu[i].aver = 0.0;
		stu[i].aver_ = 0.0;
		//由于在学生成绩和信息读入时没有学生总分和平均分所以将其赋值为零 
	}
	fclose(fp);
	printf("Total students is %d.\n", i);//当读到为空时由于i++,此时读到的学生人数为i 
	return i;
}
//将学生信息写入D:\\studentfile.txt 
void Writefile(STUDENT stu[], int n, int m)
{
	FILE* fp;//定义文件指针 
	int i, j;
	if ((fp = fopen("D:\\studentfile.txt", "a+")) == NULL)//以追加的方式创建并打开studentfile.txt文件 
	{
		printf("创建studetfile.txt文件异常！！！\n");
		exit(0);
	}
	fprintf(fp, "学号：\t \t姓名:\t科目一成绩：\t科目二成绩：\t科目三成绩：\t总分：\t平均分：\n");
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%lld\t%s\t", stu[i].studentID, stu[i].studentname);
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%.2f\t \t", stu[i].score[j]);
		}
		fprintf(fp, "%.2f\t%.2f\n", stu[i].aver, stu[i].aver_);
	}
	fclose(fp);//关闭文件 
}
//按成绩排序输出各学生所有信息及相应成绩
void Printscore(STUDENT stu[], int n, int m)
{
	int i, j;
	printf("学号：\t \t姓名: \t科目一成绩：\t科目二成绩：\t科目三成绩：\t总分：\t平均分：\n");
	for (i = 0; i < n; i++)
	{
		printf("%lld\t%s\t", stu[i].studentID, stu[i].studentname);
		for (j = 0; j < m; j++)
		{
			printf("%.2f\t \t", stu[i].score[j]);
		}
		printf("%.2f\t%.2f\n", stu[i].aver, stu[i].aver_);
	}
}