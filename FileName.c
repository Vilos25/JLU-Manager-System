/*�� system(��color 0A��); ����color�����0�Ǳ���ɫ���ţ�A��ǰ��ɫ���š�����ɫ�������£�
0=��ɫ 1=��ɫ 2=��ɫ 3=����ɫ 4=��ɫ 5=��ɫ 6=��ɫ 7=��ɫ 8=��ɫ 9=����ɫ
A=����ɫ B=��ǳ��ɫ C=����ɫ D=����ɫ E=����ɫ F=����ɫ
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#include<string.h>
#define N 60
#define M 6
typedef struct student
{
	long long studentID;//ѧ�� 
	char studentname[15];//���� 
	float score[M]; //M�ſγɼ� 
	float aver;//M�ſ��ܷ� 
	float aver_;//M�ſ�ƽ���� 
}STUDENT;
int Inputscore(STUDENT stu[], int m);//����ѧ����Ϣ����¼��ѧ���� 
void Averscore(STUDENT stu[], int n, int m);//�����ܷ� �Լ�ƽ���� 
void Rankscore(STUDENT stu[], int n, int (*p)(float, float));//��ָ������ָ�밴�ܷ���������������� 
int Rankscore1(float a, float b);//���ܷ���������
int Rankscore2(float a, float b);//���ֽܷ������� 
void Studentscore(STUDENT stu[], int n, int (*f)(long long, long long));//��ָ������ָ�밴ѧ�����������������
int Studentscore1(long long x, long long y);//��ѧ����������
int Studentscore2(long long x, long long y);//��ѧ�Ž�������
int Findscore(STUDENT stu[], long long studentID, int n);//����ѧ��ΪstudentID��ѧ����Ϣ�����������±�i
int Findname(STUDENT stu[], char a[], int n);//��ѧ����������ѧ�������������±�i 
int Deletescore(STUDENT stu[], int i, int n);//ɾ��ѧ��ΪstudentID��ѧ����Ϣ�������ش�ʱ���е�ѧ�������� 
int Appendscore(STUDENT stu[], int n, int m);//���һ��ѧ����Ϣ 
void Printscore(STUDENT stu[], int n, int m);//�����ѧ��������Ϣ����Ӧ�ɼ�
void Printscore_(STUDENT stu[], int i, int m);//��ѧ��ΪstudentID��ѧ����Ϣ��� 
int Readfile(STUDENT stu[], int m);//��ѧ����Ϣ��D:\\student_file.txt���� 
void Writefile(STUDENT stu[], int n, int m);//��ѧ����Ϣд��D:\\studentfile.txt 
int main()
{
	int n, i, m;//ָ��Ҫ����Ŀγ��������Լ���¼����ѧ������ 
	long long studentID;
	char ch;
	char a[15];
	STUDENT stu[N];
	system("color F6");//ʵ�ֽ���,��ɫ��������ɫ���� 
	do {
		system("cls");//����
		printf("***********************************************************************\n");
		printf("			****����ѡ��****	\n \n");
		printf("	1.������뽫student_file.txt�е�ѧ����Ϣ��������ʾ��������G/g��\n \n");
		printf("	2.��������ֶ�����ѧ����Ϣ������H/h��\n \n");
		printf("***********************************************************************\n");
		scanf(" %c", &ch);
		if (ch == 'G' || ch == 'g')
		{
			printf("������ѧ��ѧ����Ŀm��\n");
			scanf("%d", &m);
			n = Readfile(stu, m);
			printf("student_file.txt�����ɹ�������\n");
			Printscore(stu, n, m);
			Sleep(5000); //��ͣ����5��
		}
		else if (ch == 'H' || ch == 'h')
		{
			printf("������ѧ��ѧ����Ŀm��\n");
			scanf("%d", &m);
			printf("������ѧ����Ϣ:\n");
			n = Inputscore(stu, m);
		}
		else
		{
			printf("û�и�ѡ�����������I/i��������ѡ��\n");
			scanf(" %c", &ch);
		}
	} while (ch == 'I' || ch == 'i');
	printf("�ҽ������ѧ���ֺܷ�ƽ����!\n");
	Averscore(stu, n, m);
	Sleep(2000);//ʹ������ͣ���� 
	do {
		system("cls");
		printf("�����Խ������²�����\n \n");
		printf("***********************************************************************\n");
		printf("		������������****���ܲ˵�****������������	");
		printf("\n");
		printf("	1.������밴�ܷ��������������A/a!	\n");
		printf("\n");
		printf("	2.������밴ѧ�Ų��Ҳ������ѧ����Ϣ������B/b!\n");
		printf("\n");
		printf("	3.������밴�������Ҳ������ѧ����Ϣ������U/u!\n");
		printf("\n");
		printf("	4.������밴ѧ�Ų��Ҳ�ɾ����ѧ����Ϣ�����ʣ��ѧ����Ϣ������C/c!\n");
		printf("\n");
		printf("	5.������밴�������Ҳ�ɾ����ѧ����Ϣ�����ʣ��ѧ����Ϣ������L/l!\n");
		printf("\n");
		printf("	6.������밴ѧ���������ѧ����Ϣ������D/d!\n");
		printf("\n");
		printf("	7.����������һ��ѧ����Ϣ�������ǰѧ����Ϣ������E/e!\n \n");
		printf("***********************************************************************\n");
		scanf(" %c", &ch);
		if (ch == 'A' || ch == 'a')
		{
			system("cls");
			printf("���ܷ���������������X/x!\n \n");
			printf("���ֽܷ�������������Y/y!\n");
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
					printf("û�иù���ѡ�������V/v���½���ѡ�񣡣���\n");
					scanf(" %c", &ch);
				}
			} while (ch == 'V' || ch == 'v');
		}
		else if (ch == 'B' || ch == 'b')
		{
			system("cls");
			printf("������������ҵ�ѧ��ѧ��:\n");
			scanf("%lld", &studentID);
			i = Findscore(stu, studentID, n);
			if (i == n - 1)
			{
				printf("�����ڸ�ѧ����Ϣ������\n");
			}
			else
			{
				Printscore_(stu, i, m);
			}
		}
		else if (ch == 'U' || ch == 'u')
		{
			system("cls");
			printf("�������������ѧ��������\n");
			scanf("%s", a);
			i = Findname(stu, a, n);
			if (i == n - 1)
			{
				printf("�����ڸ�ѧ����Ϣ������\n");
			}
			else
			{
				Printscore_(stu, i, m);
			}
		}
		else if (ch == 'C' || ch == 'c')
		{
			system("cls");
			printf("����������ɾ����ѧ��ѧ��:\n");
			scanf("%lld", &studentID);
			i = Findscore(stu, studentID, n);
			if (i == n - 1)
			{
				printf("�����ڸ�ѧ����Ϣ������\n");
			}
			else
			{
				n = Deletescore(stu, i, n);
				printf("ʣ��ѧ����Ϣ��\n");
				Printscore(stu, n, m);
			}
		}
		else if (ch == 'L' || ch == 'l')
		{
			system("cls");
			printf("����������ɾ����ѧ��ѧ��:\n");
			scanf("%s", a);
			i = Findname(stu, a, n);
			if (i == n - 1)
			{
				printf("�����ڸ�ѧ����Ϣ������\n");
			}
			else
			{
				n = Deletescore(stu, i, n);
				printf("ʣ��ѧ����Ϣ��\n");
				Printscore(stu, n, m);
			}
		}
		else if (ch == 'D' || ch == 'd')
		{
			do {
				system("cls");
				printf("��ѧ����������������P/p��\n");
				printf("\n");
				printf("��ѧ�Ž�������������O/o��\n");
				scanf(" %c", &ch);
				if (ch == 'P' || ch == 'p')
				{
					printf("��ѧ�������������£�\n");
					Studentscore(stu, n, Studentscore1);
					Printscore(stu, n, m);
				}
				else if (ch == 'O' || ch == 'o')
				{
					printf("��ѧ�Ž����������£�\n");
					Studentscore(stu, n, Studentscore2);
					Printscore(stu, n, m);
				}
				else
				{
					printf("û�и�ѡ�������S/s�����½��빦�ܣ�����\n");
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
			printf("û�иù���ѡ��!!!\n");
		}
		printf("����㻹���ѧ����Ϣ���в���������T/t!\n");
		scanf(" %c", &ch);
	} while (ch == 'T' || ch == 't');
	do {
		system("cls");
		printf("�Ƿ�ѧ����Ϣд��studentfile.txt�ļ���\n");
		printf("��Ҫд�뱣��������W/w:\n");
		scanf(" %c", &ch);
		if (ch == 'W' || ch == 'w')
		{
			Writefile(stu, n, m);
			printf("�ѳɹ���ѧ����Ϣд��studentfile.txt!!!\n");
		}
		else
		{
			printf("�ļ���δ�����Ƿ�������棿\n");
			printf("��Ҫ����������M/m:\n");
			scanf(" %c", &ch);
		}
	} while (ch == 'M' || ch == 'm');
	return 0;
}
//����n��ѧ����ѧ�ţ�������m�ſγ̵ĳɼ����ṹ������stu�� ,ֱ������ķ���Ϊ����Ϊֹ 
int Inputscore(STUDENT stu[], int m)
{
	int i = -1, j;
	do {
		i++;
		printf("Input record %d:ѧ�ţ�\t \t����:\t��Ŀһ�ɼ���\t��Ŀ���ɼ���\t��Ŀ���ɼ���\n", i + 1);
		scanf("%lld", &stu[i].studentID);
		scanf("%s", stu[i].studentname);//�����������뺺�� 
		for (j = 0; j < m; j++)
		{
			scanf("%f", &stu[i].score[j]);
		}
	} while (stu[i].score[0] >= 0 && stu[i].score[1] >= 0 && stu[i].score[2] >= 0);
	return i;
}
//�������ѧ����m�ſγ��ܷ֣��浽aver��
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
//��ѧ����������������� 
void Studentscore(STUDENT stu[], int n, int (*f)(long long, long long))
{
	STUDENT test;//����һ���ṹ��������ڽ���ʱʵ����Ϣȫ������ 
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
//����ָ������ָ����ý���ѧ���������� 
int Studentscore1(long long x, long long y)
{
	return x > y;
}
//����ָ������ָ����ý���ѧ�Ž������� 
int Studentscore2(long long x, long long y)
{
	return x < y;
}
//���ɼ�����Ӹߵ��� 
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
//���ܷ���������
int Rankscore1(float a, float b)
{
	return a > b;
}
//���ֽܷ������� 
int Rankscore2(float a, float b)
{
	return a < b;
}
// ����ѧ��ΪstudentID��ѧ����Ϣ�����������±�i
int Findscore(STUDENT stu[], long long studentID, int n)
{
	int i = 0;
	while (stu[i].studentID != studentID)
	{
		i++;
		if (i == n - 1)
		{
			return n - 1;//��ִ�и������֤����û����Ҫ���ҵ�ѧ����Ϣ 
		}
	}
	return i;
}
//��ѧ����������ѧ�������������±�i 
int Findname(STUDENT stu[], char a[], int n)
{
	int i = 0;
	while (strcmp(stu[i].studentname, a))//����������ѧ����strcmp()�����ϸ����ִ�Сд 
	{
		i++;
		if (i == n - 1)
		{
			return n - 1;//��ִ�и������֤����û����Ҫ���ҵ�ѧ����Ϣ 
		}
	}
	return i;
}
//��ѧ��ΪstudentID��ѧ����Ϣ��� 
void Printscore_(STUDENT stu[], int i, int m)
{
	int j;
	printf("ѧ�ţ�\t \t����:\t��Ŀһ�ɼ���\t��Ŀ���ɼ���\t��Ŀ����\t�ܷ֣�\tƽ���֣�\n");
	printf("%lld\t%s\t", stu[i].studentID, stu[i].studentname);
	for (j = 0; j < m; j++)
	{
		printf("%.2f\t \t", stu[i].score[j]);
	}
	printf("%.2f\t%.2f\n", stu[i].aver, stu[i].aver_);
}
//ɾ��ѧ��ΪstudentID��ѧ����Ϣ�������ش�ʱ���е�ѧ�������� 
int Deletescore(STUDENT stu[], int i, int n)
{
	for (; i + 1 < n; i++)//Ӧ��˳����˼�뽫ɾ�����ѧ����Ϣ������ǰ�� 
	{
		stu[i] = stu[i + 1];
	}
	return i;//��i+1=nʱ�˳�ѭ������ʱiΪɾ�� studentID���ѧ�������� 
}
//���һ��ѧ����Ϣ 
int Appendscore(STUDENT stu[], int n, int m)
{
	int i;
	float sum = 0;
	printf("������Ҫ���ѧ����Ϣ��\n");
	printf("ѧ�ţ�\t \t����:\t��Ŀһ�ɼ���\t��Ŀ���ɼ���\t��Ŀ���ɼ���\n");
	scanf("%lld %s", &stu[n].studentID, stu[n].studentname);
	for (i = 0; i < m; i++)
	{
		scanf("%f", &stu[n].score[i]);
		sum += stu[n].score[i];
	}
	//�����¼����ѧ��û���ֺܷ�ƽ���֣�������Ҫ�������
	stu[n].aver = sum;
	stu[n].aver_ = sum / m;
	return n + 1;//��ʱѧ��������Ϊn+1 
}
//��ѧ����Ϣ��D:\\student_file.txt���� 
int Readfile(STUDENT stu[], int m)
{
	int i, j;
	FILE* fp;
	if ((fp = fopen("D:\\student_file.txt", "r+")) == NULL)
	{
		printf("�ļ���ʧ�ܣ���!\n");
		exit(0);
	}
	for (i = 0; !feof(fp); i++)
	{
		fscanf(fp, "%lld\t%s\t", &stu[i].studentID, stu[i].studentname);
		for (j = 0; j < m; j++)
		{
			fscanf(fp, "%f\t \t", &stu[i].score[j]);//����ʱ������%.2f��ʽ !!!!
		}
		stu[i].aver = 0.0;
		stu[i].aver_ = 0.0;
		//������ѧ���ɼ�����Ϣ����ʱû��ѧ���ֺܷ�ƽ�������Խ��丳ֵΪ�� 
	}
	fclose(fp);
	printf("Total students is %d.\n", i);//������Ϊ��ʱ����i++,��ʱ������ѧ������Ϊi 
	return i;
}
//��ѧ����Ϣд��D:\\studentfile.txt 
void Writefile(STUDENT stu[], int n, int m)
{
	FILE* fp;//�����ļ�ָ�� 
	int i, j;
	if ((fp = fopen("D:\\studentfile.txt", "a+")) == NULL)//��׷�ӵķ�ʽ��������studentfile.txt�ļ� 
	{
		printf("����studetfile.txt�ļ��쳣������\n");
		exit(0);
	}
	fprintf(fp, "ѧ�ţ�\t \t����:\t��Ŀһ�ɼ���\t��Ŀ���ɼ���\t��Ŀ���ɼ���\t�ܷ֣�\tƽ���֣�\n");
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%lld\t%s\t", stu[i].studentID, stu[i].studentname);
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%.2f\t \t", stu[i].score[j]);
		}
		fprintf(fp, "%.2f\t%.2f\n", stu[i].aver, stu[i].aver_);
	}
	fclose(fp);//�ر��ļ� 
}
//���ɼ����������ѧ��������Ϣ����Ӧ�ɼ�
void Printscore(STUDENT stu[], int n, int m)
{
	int i, j;
	printf("ѧ�ţ�\t \t����: \t��Ŀһ�ɼ���\t��Ŀ���ɼ���\t��Ŀ���ɼ���\t�ܷ֣�\tƽ���֣�\n");
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