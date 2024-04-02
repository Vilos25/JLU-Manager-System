#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include "Func_isValid.h"
#include "LIST_StdGrade.h"
#include "Func_calculate.h"
#include "LIST_SubInfor.h"
//����רҵͷ�ڵ㲢��ʼ��
struct Major* create_Major() {
	struct Major* newNode = (struct Major*)malloc(sizeof(struct Major));
	if (newNode != NULL) {
		//strcpy(newNode->majorNum, "0");
		newNode->majorNum = 0;
		newNode->next = NULL;
		struct Grade* newGrade = (struct Grade*)malloc(sizeof(struct Grade));
		if (newGrade != NULL) {
			newGrade->gradeNum = 0;
			newGrade->next = NULL;
			newGrade->student = NULL;
			newNode->grade = newGrade;
			struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
			if (newStudent != NULL) {
				newStudent->studentID = 0;
				newStudent->GPA = 0.0;
				newStudent->add_GPA = 0.0;
				newStudent->rank = 0;
				strcpy(newStudent->rankTime, "0");
				newStudent->scores = NULL;
				newStudent->next = NULL;
				newGrade->student = newStudent;
				struct SubScore* newScore = (struct SubScore*)malloc(sizeof(struct SubScore));
				if (newScore != NULL) {
					strcpy(newScore->courseName, "0");
					newScore->score = 0;
					strcpy(newScore->semester, "0");
					newScore->isExempted = 0;
					newScore->isretake = 0;
					newScore->isval = 0;
					newScore->isFailed = 0;
					newScore->perGPA = 0.0;
					newScore->next = NULL;
					newStudent->scores = newScore;
				}
			}

		}
	}
	return newNode;
}


//���רҵ�ڵ����ͨ��רҵ��Ų��صĹ���
void add_Major(struct Major** head_Major, int majorNum) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (temp->majorNum == majorNum) {
			printf("רҵ����ظ������ʧ�ܡ�\n");
			return;
		}
		temp = temp->next;
	}

	
	struct Major* newNode = create_Major();
	if (newNode != NULL) {
		newNode->majorNum = majorNum;
		if(*head_Major == NULL)
			*head_Major = newNode;
		else {
			//������β������½ڵ�
			temp = *head_Major;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
}
//ͨ��רҵ��Ų���רҵ�ڵ㲢�������ַ
struct Major* search_Major(struct Major* head_Major, const int majorNum) {
	struct Major* temp = head_Major;
	while (temp != NULL) {
		if (temp->majorNum == majorNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}

//��һ��ѧ�ţ����Ҹ���ѧ�����ڵ��꼶�ڵ�
struct Grade* search_GradeByStudentID(struct Major** head_Major, int studentID) {
	struct Major* tempMajor = *head_Major;
	struct Grade* tempGrade;
	struct Student* tempStudent;
	while (tempMajor != NULL) {
		tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			tempStudent = tempGrade->student;
			while (tempStudent != NULL) {
				if (tempStudent->studentID == studentID) {
					return tempGrade;
				}
				tempStudent = tempStudent->next;
			}
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}

//��һ��ѧ�ţ����Ҹ���ѧ�����ڵ�רҵ�ڵ�
struct Major* search_MajorByStudentID(struct Major* head_Major, int studentID) {
	struct Major* tempMajor = head_Major;
	struct Grade* tempGrade;
	struct Student* tempStudent;
	while (tempMajor != NULL) {
		tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			tempStudent = tempGrade->student;
			while (tempStudent != NULL) {
				if (tempStudent->studentID == studentID) {
					return tempMajor;
				}
				tempStudent = tempStudent->next;
			}
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}

//�����꼶ͷ�ڵ㣬����ֵΪ�´������꼶�ڵ�ĵ�ַ������ֵΪNULL��ʾ����ʧ�ܣ���ʼ���꼶�ڵ��ѧ���ڵ�
struct Grade* create_Grade() {
	struct Grade* newNode = (struct Grade*)malloc(sizeof(struct Grade));
	if (newNode != NULL) {
		newNode->gradeNum = 0;
		newNode->next = NULL;
		newNode->student = NULL;
		struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
		if (newStudent != NULL) {
			newStudent->studentID = 0;
			newStudent->GPA = 0.0;
			newStudent->add_GPA = 0.0;
			newStudent->rank = 0;
			strcpy(newStudent->rankTime, "0");
			newStudent->scores = NULL;
			newStudent->next = NULL;
			newNode->student = newStudent;
			struct SubScore* newScore = (struct SubScore*)malloc(sizeof(struct SubScore));
			if (newScore != NULL) {
				strcpy(newScore->courseName, "0");
				newScore->score = 0;
				strcpy(newScore->semester, "0");
				newScore->isExempted = 0;
				newScore->isretake = 0;
				newScore->isval = 0;
				newScore->isFailed = 0;
				newScore->perGPA = 0.0;
				newScore->next = NULL;
				newStudent->scores = newScore;
			}
		}
	}
	return newNode;
}

//����꼶�ڵ����ͨ���꼶���صĹ��ܣ�����ֵΪ1��ʾ��ӳɹ�������ֵΪ0��ʾ���ʧ��
void add_Grade(struct Major* Major, int gradeNum) {
	struct Grade* temp = Major->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			printf("�꼶�ظ������ʧ�ܡ�\n");
			return;
		}
		temp = temp->next;
	}
	
	struct Grade* newNode = create_Grade();
	if (newNode != NULL) {
		newNode->gradeNum = gradeNum;
	}
	if (Major->grade == NULL)
		Major->grade = newNode;
	else
	//������β������½ڵ�
	{
		temp = Major->grade;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
}

//ͨ���꼶�����꼶�ڵ㲢�������ַ
struct Grade* search_Grade(struct Major** Major, int gradeNum) {
	struct Grade* temp = (*Major)->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}


//����ѧ���ڵ�
struct Student* create_Student() {
	struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
	if (newNode != NULL) {
		newNode->studentID = 0;
		newNode->GPA = 0.0;
		newNode->add_GPA = 0.0;
		newNode->rank = 0;
		strcpy(newNode->rankTime, "0");
		newNode->scores = NULL;
		newNode->next = NULL;
		struct SubScore* newScore = (struct SubScore*)malloc(sizeof(struct SubScore));
		if (newScore != NULL) {
			strcpy(newScore->courseName, "0");
			newScore->score = 0;
			strcpy(newScore->semester, "0");
			newScore->isExempted = 0;
			newScore->isretake = 0;
			newScore->isval = 0;
			newScore->isFailed = 0;
			newScore->perGPA = 0.0;
			newScore->next = NULL;
			newNode->scores = newScore;
		}
	}
	return newNode;
}
//���ѧ���ڵ����ͨ�������������н���ѧ�Ų��صĹ���
void add_Student(struct Major** head_Major, int studentID, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(*head_Major, majorNum);
	if (tempMajor == NULL) {
		printf("רҵ�����ڣ����ʧ�ܡ�\n");
		return;
	}
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("�꼶�����ڣ����ʧ�ܡ�\n");
		return;
	}
	struct Student* tempStudent = tempGrade->student;
	while (tempStudent != NULL) {
		if (tempStudent->studentID == studentID) {
			printf("ѧ���ظ������ʧ�ܡ�\n");
			return;
		}
		tempStudent = tempStudent->next;
	}
	
	struct Student* newNode = create_Student();
	if (newNode != NULL) {
		newNode->studentID = studentID;
		if(tempGrade->student == NULL)
			tempGrade->student = newNode;
		else {
			tempStudent = tempGrade->student;
			while (tempStudent->next != NULL) {
				tempStudent = tempStudent->next;
			}
			tempStudent->next = newNode;
		}
	}
}



//ͨ��ѧ�������������в��ҵ���ѧ���ڵ�
struct Student* search_Student(struct Major** head_Major, int studentID) {
	struct Major* tempMajor = *head_Major;
	struct Grade* tempGrade;
	struct Student* tempStudent;
	while (tempMajor != NULL) {
		tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			tempStudent = tempGrade->student;
			while (tempStudent != NULL) {
				if (tempStudent->studentID == studentID) {
					return tempStudent;
				}
				tempStudent = tempStudent->next;
			}
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}

//��ѧ���ڵ���ӳɼ�������ͨ���γ������صĹ��ܣ�����ֵΪ1��ʾ��ӳɹ�������ֵΪ0��ʾ���ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ظ��ͱ��Ϊ����
int add_Score(struct Major** head_Major, int studentID, char courseName[20], float score, char semester[20], int isExempted, int isval) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		return -1;
	}
	int choice = 0;
	system("cls");
	int xy = 6;
	struct SubScore* temp = tempStudent->scores;
	while (temp != NULL) {
		if (strcmp(temp->courseName, courseName) == 0) {
			if (temp->isretake == 1) {
				cursor(26, xy += 2);
				printf("�ÿγ��Ѵ��ڣ��������ޣ������޸���ת��<�޸ĳɼ�>ѡ�");
				Sleep(1000);
				return 0;
			}
			choice = 1;
		}
		temp = temp->next;
	}
	if (choice == 1)
	{
		cursor(26, xy += 2);
		printf("�ÿγ��Ѵ��ڣ��Ƿ�������޳ɼ���(1.��  2.��)");
		choice = Input_1toNum(2);
		if (choice == 2){
			return 0;
		}
	}
	struct SubScore* newNode = (struct SubScore*)malloc(sizeof(struct SubScore));
	if (newNode != NULL) {
		strcpy(newNode->courseName, courseName);
		newNode->score = score;
		strcpy(newNode->semester, semester);
		newNode->isExempted = isExempted;
		if (newNode->isExempted == 1)
			newNode->score = 90.0;
		newNode->isval = isval;
		if (newNode->score >= 60)
			newNode->isFailed = 0;
		else
			newNode->isFailed = 1;
		newNode->perGPA = exchange_GPA(newNode->score);
		if (choice == 1)
			newNode->isretake = 1;
		else
			newNode->isretake = 0;
		newNode->next = NULL;
		
		if (tempStudent->scores == NULL) {
			tempStudent->scores = newNode;
		}
		else {
			temp = tempStudent->scores;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		return 1;
	}
	return 0;
}
//�޸�ָ��ѧ����ָ���ɼ�������ֵΪ1��ʾ�޸ĳɹ�������ֵΪ0��ʾ�޸�ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ���������
int update_Score(struct Major** head_Major, int studentID, char courseName[20], float newScore) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		return -1;
	}
	int xy = 6;
	system("cls");
	struct SubScore* temp = tempStudent->scores;
	struct SubScore* first = NULL;
	struct SubScore* retake = NULL;
	while (temp != NULL) {
		if (strcmp(temp->courseName, courseName) == 0) {
			if (temp->isretake == 0) {
				first = temp;
			}
			else if(temp->isretake == 1){
				retake = temp;
			}
		}
		temp = temp->next;
	}
	if (retake != NULL && first != NULL) {
		cursor(26, xy += 2);
		printf("�ÿγ��ѱ����ޣ����޸����޳ɼ�");
		Sleep(1000);
		retake->score = newScore;
		retake->perGPA = exchange_GPA(newScore);
		if(first->score >= 60)
			first->isFailed = 0;
		else
			first->isFailed = 1;
		return 1;
	}
	else if(first != NULL){
		cursor(26, xy += 2);
		printf("�ÿγ�ֻ�����ޣ��Ƿ�Ҫ���ĳ��޳ɼ���(1.��  2.��): ");
		int choice = Input_1toNum(2);
		if (choice == 1)
		{
			first->score = newScore;
			first->perGPA = exchange_GPA(newScore);
			if (first->score >= 60)
				first->isFailed = 0;
			else
				first->isFailed = 1;
			return 1;
		}
		else {
			return 0;
		}
	}
	return -2;
}
//ɾ��ָ��ѧ����ָ���ɼ�������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ���������
int delete_Score(struct Major** head_Major, int studentID, char courseName[20]) {
	int xy = 6;
	system("cls");
	struct Student* tempStudent = search_Student(head_Major, studentID);

	if (tempStudent == NULL) {
		return -1;
	}
	struct SubScore* temp = tempStudent->scores;
	struct SubScore* temp2;
	struct SubScore* first = NULL;
	struct SubScore* retake = NULL;
	while(temp != NULL){
		if (strcmp(temp->courseName, courseName) == 0) {
			if (temp->isretake == 0) {
				first = temp;
			}
			else if (temp->isretake == 1) {
				retake = temp;
			}
		}
		temp = temp->next;
	}
	if (retake != NULL && first != NULL) {
		cursor(26, xy += 2);
		printf("�ÿγ��ѱ����ޣ���ɾ�����޳ɼ�");
		if (tempStudent->scores == retake) {
			tempStudent->scores = retake->next;
			free(retake);
		}
		else {
			temp = tempStudent->scores;
			while (temp->next != retake) {
				temp = temp->next;
			}
			temp->next = retake->next;
			free(retake);
		}
		Sleep(1000);
		return 1;
	}
	else if(first != NULL){
		cursor(26, xy += 2);
		printf("�ÿγ�ֻ�����ޣ��Ƿ�Ҫɾ�����޳ɼ���(1.��  2.��): ");
		int choice = Input_1toNum(2);
		if (choice == 1)
		{
			if (tempStudent->scores == first) {
				tempStudent->scores = first->next;
				free(first);
			}
			else {
				temp = tempStudent->scores;
				while (temp->next != first) {
					temp = temp->next;
				}
				temp->next = first->next;
				free(first);
			}
			return 1;
		}
		else {
			return 0;
		}
	}
	return -2;
}
//ɾ��ָ��ѧ�������гɼ�������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ�ܣ�����ֵΪ-1��ʾѧ��������
int delete_AllScore(struct Major** head_Major, int studentID) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		return -1;
	}
	struct SubScore* temp = tempStudent->scores;
	struct SubScore* temp2;
	while (temp != NULL) {
		temp2 = temp;
		temp = temp->next;
		free(temp2);
	}
	tempStudent->scores = NULL;
	return 1;
}
//ɾ��ָ��ѧ��������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Student(struct Major** head_Major, int studentID) {
	struct Major* tempMajor = *head_Major;
	struct Grade* tempGrade;
	struct Student* tempStudent;
	struct Student* tempStudent2;
	while (tempMajor != NULL) {
		tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			tempStudent = tempGrade->student;
			if (tempStudent != NULL) {
				if (tempStudent->studentID == studentID) {
					tempGrade->student = tempStudent->next;
					delete_AllScore(head_Major, studentID);
					free(tempStudent);
					return 1;
				}
				while (tempStudent->next != NULL) {
					if (tempStudent->next->studentID == studentID) {
						tempStudent2 = tempStudent->next;
						tempStudent->next = tempStudent->next->next;
						delete_AllScore(head_Major, studentID);
						free(tempStudent2);
						return 1;
					}
					tempStudent = tempStudent->next;
				}
			}
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return 0;
}
//��ʾָ���꼶������ѧ��
void display_Grade(struct Major* head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	if (tempMajor == NULL) {
		printf("�Ҳ���ָ����רҵ��\n");
		return;
	}
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("�Ҳ���ָ�����꼶��\n");
		return;
	}
	struct Student* tempStudent = tempGrade->student;
	if (tempStudent->next == NULL) {
		printf("���꼶��ѧ����\n");
		return;
	}
	//ֻ���꼶���Ը��꼶��ѧ���ɼ�����ð�����򲢸�������
	Sort_Grade(head_Major, majorNum, gradeNum);
	tempStudent = tempStudent->next;
	system("cls");
	int line = 0, Page = 1, cnt = 1;
	int rc40 = 0,rc30 = 0,rc20 = 0,rc10 = 0;
	float percent5 = 0, percent10 = 0, percent15 = 0, percent30 = 0, percent50 = 0;
	int tot = calculate_GradeStudentNum(head_Major, majorNum, gradeNum);
	while (tempStudent != NULL) {
		if(line==0)
		printf("\t%s-%s����%d��  ѧ���ɼ�����������%dҳ\n\n", All_Aca[majorNum / 100], ALL_Prof[majorNum / 100][majorNum % 100], gradeNum, Page++);
		printf("��ţ�%d \tѧ�ţ�%d\t\t", cnt++, tempStudent->studentID);
		tempStudent->GPA = calculate_GPA(head_Major, tempStudent->studentID, head_SubInfor);
		printf("GPA��%f\t\t", tempStudent->GPA + tempStudent->add_GPA);
		tempStudent->rank = Grade_ranking(head_Major, tempStudent->studentID, 0, tempStudent->GPA, gradeNum);
		printf("������%d \t", tempStudent->rank);
		printf("����ʱ�䣺%s\n", tempStudent->rankTime);

		if ((float)(tempStudent->rank + 1) / tot > 0.05 && percent5 == 0)
			percent5 = tempStudent->GPA;
		else if ((float)(tempStudent->rank + 1) / tot > 0.1 && percent10 == 0)
			percent10 = tempStudent->GPA;
		else if ((float)(tempStudent->rank + 1) / tot > 0.15 && percent15 == 0)
			percent15 = tempStudent->GPA;
		else if ((float)(tempStudent->rank + 1) / tot > 0.3 && percent30 == 0)
			percent30 = tempStudent->GPA;
		else if ((float)(tempStudent->rank + 1) / tot > 0.5 && percent50 == 0)
			percent50 = tempStudent->GPA;

		if (tempStudent->GPA >= 4.0)
			rc40++;
		else if (tempStudent->GPA >= 3.0)
			rc30++;
		else if (tempStudent->GPA >= 2.0)
			rc20++;
		else if (tempStudent->GPA >= 1.0)
			rc10++;
		tempStudent = tempStudent->next;
		line++;
		if (line == 27) {
			system("pause");
			printf("\n");
			line = 0;
		}
	}
	//���ͳ����Ϣ
	printf("\n\t\t\t�꼶�ɼ�ͳ��\n\n");
	printf("GPA�ֶΣ�\t4.0���ϣ�%d��\t3.0-3.9��%d��\t2.0-2.9��%d��\t1.0-1.9��%d��\n", rc40, rc30, rc20, rc10);
	printf("GPA�ֶΰٷֱȣ�\t4.0���ϣ�%.2f%%\t3.0-3.9��%.2f%%\t2.0-2.9��%.2f%%\t1.0-1.9��%.2f%%\n", (float)rc40 / tot * 100, (float)rc30 / tot * 100, (float)rc20 / tot * 100, (float)rc10 / tot * 100);
	printf("GPA�ٷֱȷֶΣ�\tǰ5%%��%.5f\tǰ10%%��%.5f\tǰ15%%��%.5f\tǰ30%%��%.5f\tǰ50%%��%.5f\n\n", percent5, percent10, percent15, percent30, percent50);
	printf("�ٷֱ�������ǰ5%%��%d��\tǰ10%%��%d��\tǰ15%%��%d��\tǰ30%%��%d��\tǰ50%%��%d��\n", (int)(tot * 0.05), (int)(tot * 0.1), (int)(tot * 0.15), (int)(tot * 0.3), (int)(tot * 0.5));
	return;
}


//ɾ��ָ���꼶������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Grade(struct Major** head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (tempMajor->majorNum == majorNum) {
			struct Grade* currentGrade = NULL;
			currentGrade = tempMajor->grade;
			struct Grade* prevGrade = NULL;

			while (currentGrade != NULL) {
				if (currentGrade->gradeNum == gradeNum) {
					// ɾ���꼶�ڵ�
					if (prevGrade == NULL) {
						tempMajor->grade = currentGrade->next;
					}
					else {
						prevGrade->next = currentGrade->next;
					}

					// ɾ���꼶�µ�����ѧ������ɼ�
					struct Student* currentStudent = currentGrade->student;
					while (currentStudent != NULL) {
						struct SubScore* currentScore = currentStudent->scores;
						while (currentScore != NULL) {
							struct SubScore* tempScore = currentScore;
							currentScore = currentScore->next;
							free(tempScore);
						}
						struct Student* tempStudent = currentStudent;
						currentStudent = currentStudent->next;
						free(tempStudent);
					}
					free(currentGrade);
					printf("�꼶ɾ���ɹ���\n");
					return 1;
				}
				prevGrade = currentGrade;
				currentGrade = currentGrade->next;
			}
			printf("�Ҳ���ָ�����꼶��\n");
			return 0;
		}
		tempMajor = tempMajor->next;
	}
	printf("�Ҳ���ָ����רҵ��\n");
	return 0;
}

//ɾ��ָ��רҵ������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Major(struct Major** head_Major, int majorNum) {
	struct Major* tempMajor = *head_Major;
	struct Major* tempMajor2;
	if (tempMajor != NULL) {
		if (tempMajor->majorNum == majorNum) {
			while (tempMajor->grade != NULL) {
				delete_Grade(head_Major, majorNum, tempMajor->grade->gradeNum);
			}
			tempMajor2 = tempMajor;
			*head_Major = tempMajor->next;
			free(tempMajor2);
			return 1;
		}
		while (tempMajor->next != NULL) {
			if (tempMajor->next->majorNum == majorNum) {
				while (tempMajor->next->grade != NULL) {
					delete_Grade(head_Major, majorNum, tempMajor->next->grade->gradeNum);
				}
				tempMajor2 = tempMajor->next;
				tempMajor->next = tempMajor->next->next;
				free(tempMajor2);
				return 1;
			}
			tempMajor = tempMajor->next;
		}
	}
	return 0;
}


int query_Scores(struct Major** head_Major, int studentID) {
    struct Student* tempStudent = search_Student(head_Major, studentID);
    if (tempStudent == NULL) {
        //printf("ѧ�������ڡ�\n");
        return 1;
    }
    struct SubScore* temp = tempStudent->scores->next;
    if (temp == NULL) {
        //printf("ѧ���޳ɼ���\n");
        return 2;
    }
	int g4 = 0, g3 = 0, g2 = 0, g1 = 0, g0 = 0;
    printf("ѧ��ѧ�ţ�%d\n", tempStudent->studentID);
    printf("%-15s %-22s %-8s %-8s %-13s %-10s %-8s %-8s %-8s %-8s\n", "�γ̱��", "�γ���", "ѧ��", "�ɼ�", "�޶�ѧ��", "��ü���", "�Ƿ�����", "�����ؿ�", "�Ƿ񼰸�", "�Ƿ���Ч");
    while (temp != NULL) {
        // ͨ���γ̺Ų��ҽڵ㲢�������ַ
        printf("%-15s %-21s  %-7.1f %-8.2f %-16s %-10.1f %-8s %-8s %-8s %-8s\n", temp->courseName, search_SubInfor(head_SubInfor, temp->courseName)->SubName,
			search_SubInfor(head_SubInfor, temp->courseName)->SubInforScore,
            temp->score, temp->semester, temp->perGPA, temp->isExempted == 1 ? "��" : "��", temp->isretake == 0 ? "����" : "����",
            temp->isFailed == 1 ? "�ҿ�" : "", temp->isval == 1 ? "��Ч" : "��Ч");
		if(temp->perGPA==4)
			g4++;
		else if(temp->perGPA>=3)
			g3++;
		else if(temp->perGPA>=2)
			g2++;
		else if(temp->perGPA>=1)
			g1++;
		else
			g0++;
        temp = temp->next;
    }
	printf("\n����ֲ���\t4.0��%d�� \t3.0-3.9��%d�� \t2.0-2.9��%d�� \t1.0-1.9��%d�� \t0-0.9��%d��\n", g4, g3, g2, g1, g0);
    return 0;
}

// �����������ݵ��ļ�
/*
void saveTo_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("�޷����ļ� %s\n", filename);
		return;
	}

	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (strcmp(tempMajor->majorNum, "0") == 0)
		{
			tempMajor = tempMajor->next;
			continue;
		}
		fprintf(file, "Major: %s\n", tempMajor->majorNum);
		struct Grade* tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			if (tempGrade->gradeNum == 0)
			{
				tempGrade = tempGrade->next;
				continue;
			}
			fprintf(file, "Grade: %d\n", tempGrade->gradeNum);

			struct Student* tempStudent = tempGrade->student;
			while (tempStudent != NULL) {
				if (tempStudent->studentID == 0)
				{
					tempStudent = tempStudent->next;
					continue;
				}
				fprintf(file, "Student: %d\n", tempStudent->studentID);

				struct SubScore* tempScore = tempStudent->scores;
				while (tempScore != NULL) {
					if (strcmp(tempScore->courseName, "0") == 0)
					{
						tempScore = tempScore->next;
						continue;
					}
					fprintf(file, "Score: %s %f %s %d %d\n", tempScore->courseName, tempScore->score, tempScore->semester, tempScore->isExempted, tempScore->isFailed);
					tempScore = tempScore->next;
				}

				tempStudent = tempStudent->next;
			}

			tempGrade = tempGrade->next;
		}

		tempMajor = tempMajor->next;
	}

	fclose(file);
	printf("���ݱ���ɹ���\n");
}
*/

// �����������ݵ��ļ�(JSON��ʽ)
void saveTo_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("�޷����ļ� %s\n", filename);
		return;
	}

	// ��ʼ����JSON�ַ���
	fprintf(file, "{\n");

	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (tempMajor->majorNum == 0) {
			tempMajor = tempMajor->next;
			continue;
		}
		fprintf(file, "\t\"רҵ\": \"%d\"\n", tempMajor->majorNum);

		struct Grade* tempGrade = tempMajor->grade;
		fprintf(file, "\t\"�����꼶\": [\n");
		while (tempGrade != NULL) {
			if (tempGrade->gradeNum == 0) {
				tempGrade = tempGrade->next;
				continue;
			}
			fprintf(file, "\t\t{\n");
			fprintf(file, "\t\t\t\"�꼶\": \"%d\"\n", tempGrade->gradeNum);

			struct Student* tempStudent = tempGrade->student;
			fprintf(file, "\t\t\t\"ѧ��\": [\n");
			while (tempStudent != NULL) {
				if (tempStudent->studentID == 0) {
					tempStudent = tempStudent->next;
					continue;
				}
				fprintf(file, "\t\t\t\t{\n");
				fprintf(file, "\t\t\t\t\t\"ѧ��\": \"%d\"\n", tempStudent->studentID);
				fprintf(file, "\t\t\t\t\t\"GPA\": \"%f\"\n", tempStudent->GPA);
				fprintf(file, "\t\t\t\t\t\"���ʼӷ�\": \"%f\"\n", tempStudent->add_GPA);
				fprintf(file, "\t\t\t\t\t\"����\": \"%d\"\n", tempStudent->rank);
				fprintf(file, "\t\t\t\t\t\"����ʱ��\": \"%s\"\n", tempStudent->rankTime);

				struct SubScore* tempScore = tempStudent->scores;
				fprintf(file, "\t\t\t\t\t\"���Ƴɼ�\": [\n");
				while (tempScore != NULL) {
					if (strcmp(tempScore->courseName, "0") == 0) {
						tempScore = tempScore->next;
						continue;
					}
					fprintf(file, "\t\t\t\t\t\t{\n");
					fprintf(file, "\t\t\t\t\t\t\t\"�γ̺�\": \"%s\"\n", tempScore->courseName);
					fprintf(file, "\t\t\t\t\t\t\t\"�޶�ѧ��\": \"%s\"\n", tempScore->semester);
					fprintf(file, "\t\t\t\t\t\t\t\"�γ̳ɼ�\": \"%f\"\n", tempScore->score);
					fprintf(file, "\t\t\t\t\t\t\t\"��ü���\": \"%f\"\n", tempScore->perGPA);
					fprintf(file, "\t\t\t\t\t\t\t\"�Ƿ�����\": \"%d\"\n", tempScore->isExempted);
					fprintf(file, "\t\t\t\t\t\t\t\"�����ؿ�\": \"%d\"\n", tempScore->isretake);
					fprintf(file, "\t\t\t\t\t\t\t\"�Ƿ񼰸�\": \"%d\"\n", tempScore->isFailed);
					fprintf(file, "\t\t\t\t\t\t\t\"�Ƿ���Ч\": \"%d\"\n", tempScore->isval);
					fprintf(file, "\t\t\t\t\t\t}");

					tempScore = tempScore->next;
					if (tempScore != NULL) {
						fprintf(file, ",");
					}
					fprintf(file, "\n");
				}

				fprintf(file, "\t\t\t\t\t],\n");
				fprintf(file, "\t\t\t\t}");

				tempStudent = tempStudent->next;
				if (tempStudent != NULL) {
					fprintf(file, ",");
				}
				fprintf(file, "\n");
			}

			fprintf(file, "\t\t\t],\n");
			fprintf(file, "\t\t}");

			tempGrade = tempGrade->next;
			if (tempGrade != NULL) {
				fprintf(file, ",");
			}
			fprintf(file, "\n");
		}

		fprintf(file, "\t]");

		tempMajor = tempMajor->next;
		if (tempMajor != NULL) {
			fprintf(file, ",");
		}
		fprintf(file, "\n");
	}

	// ��������JSON�ַ���
	fprintf(file, "}\n");

	fclose(file);
	printf("���ݱ���ɹ���\n");
}

/*
// ���ļ��������ݵ�����
void loadFrom_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷����ļ� %s\n", filename);
		return;
	}

	clear_StdGrade(head_Major);

	char line[100];
	struct Major* currentMajor = NULL;
	struct Grade* currentGrade = NULL;
	struct Student* currentStudent = NULL;

	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "Major: ", 7) == 0) {
			// ���רҵ�ڵ�
			char majorNum[10];
			sscanf(line, "Major: %s", majorNum);
			add_Major(head_Major, majorNum);
			currentMajor = search_Major(head_Major, majorNum);
		}
		else if (strncmp(line, "Grade: ", 7) == 0) {
			// ����꼶�ڵ�
			int gradeNum;
			sscanf(line, "Grade: %d", &gradeNum);
			add_Grade(currentMajor, gradeNum);
			currentGrade = search_Grade(&currentMajor, gradeNum);
		}
		else if (strncmp(line, "Student: ", 9) == 0) {
			// ���ѧ���ڵ�
			int studentID;
			sscanf(line, "Student: %d", &studentID);
			add_Student(head_Major, studentID, currentMajor->majorNum, currentGrade->gradeNum);
			currentStudent = search_Student(head_Major, studentID);
		}
		else if (strncmp(line, "Score: ", 7) == 0) {
			// ��ӳɼ��ڵ�
			char courseName[20];
			float score;
			char semester[5];
			int isExempted, isFailed;
			sscanf(line, "Score: %s %f %s %d %d", courseName, &score, semester, &isExempted, &isFailed);
			add_Score(head_Major, currentStudent->studentID, courseName, score, semester, isExempted, isFailed);
		}
	}

	fclose(file);
	printf("���ݶ�ȡ�ɹ���\n");
}
*/

// ���ļ���ȡJSON���ݲ���������
void loadFrom_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷����ļ� %s\n", filename);
		return;
	}

	//����רҵͷ�ڵ�
	clear_StdGrade(head_Major);
	*head_Major = create_Major();

	// ��ȡ�ļ��е�JSON����
	/*fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);
	char* jsonBuffer = (char*)malloc(fileSize + 1);
	if (jsonBuffer == NULL) {
		fclose(file);
		printf("�ڴ����ʧ��\n");
		return;
	}
	fread(jsonBuffer, 1, fileSize, file);
	jsonBuffer[fileSize] = '\0';

	char* jsonBufferCopy = strdup(jsonBuffer);  // ���������ַ���
	char* line = strtok(jsonBufferCopy, "\n");
	*/
	// ����JSON���ݲ���������
	struct Major* currentMajor = NULL;
	struct Grade* currentGrade = NULL;
	struct Student* currentStudent = NULL;
	struct SubScore* currentScore = NULL;
	
	
	char line[100];
	while (fgets(line, sizeof(line), file)) {
		// ����ÿһ�е�����
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");
		if (key == NULL || value == NULL) {
			//line = strtok(NULL, "\n");
			continue;
		}

		// ȥ����ͷ�ͽ�β�Ŀո��˫����
		char* trimmedKey = strtok(key, "\"");
			trimmedKey = strtok(NULL, "\"");
		char* trimmedValue = strtok(value, "\"");
			trimmedValue = strtok(NULL, "\"");
		
		// ���ݼ�ֵ�ԵĹ�ϵ��������ڵ�
		if (strcmp(trimmedKey, "רҵ") == 0) {
			// ����רҵ�ڵ�
			int majorNum = atoi(trimmedValue);
			add_Major(head_Major, majorNum);
			currentMajor = search_Major(*head_Major, majorNum);
		}
		else if (strcmp(trimmedKey, "�����꼶") == 0) {
			// �����꼶ͷ�ڵ�
			currentGrade = create_Grade();
			currentMajor->grade = currentGrade;
		}
		else if (strcmp(trimmedKey, "�꼶") == 0) {
			// �����꼶�ڵ�
			int gradeNum = atoi(trimmedValue);
			add_Grade(currentMajor, gradeNum);
			currentGrade = search_Grade(&currentMajor, gradeNum);
		}


		else if (strcmp(trimmedKey, "ѧ��") == 0) {
			// ����ѧ��ͷ�ڵ�
			currentStudent = create_Student();
			currentGrade->student = currentStudent;
		}
		else if (strcmp(trimmedKey, "ѧ��") == 0) {
			// ����ѧ���ڵ�
			int studentID = atoi(trimmedValue);
			add_Student(head_Major, studentID, currentMajor->majorNum, currentGrade->gradeNum);
			currentStudent = search_Student(head_Major, studentID);
			currentScore = currentStudent->scores;
		}
		else if (strcmp(trimmedKey, "GPA") == 0) {
			// ����ѧ���ڵ�������ֶ�
			if (currentStudent != NULL) {
				float gpa = atoi(trimmedValue);
				currentStudent->GPA = gpa;
			}
		}
		else if (strcmp(trimmedKey, "���ʼӷ�") == 0) {
			if (currentStudent != NULL) {
				float gpa = atoi(trimmedValue);
				currentStudent->add_GPA = gpa;
			}
		}
		else if (strcmp(trimmedKey, "����") == 0) {
			if (currentStudent != NULL) {
				int rankk = atoi(trimmedValue);
				currentStudent->rank = rankk;
			}
		}
		else if (strcmp(trimmedKey, "����ʱ��") == 0) {
			if (currentStudent != NULL) {
				strcpy(currentStudent->rankTime, trimmedValue);
			}
		}

		
		else if (strcmp(trimmedKey, "�γ̺�") == 0) {
			// ����ѧ���ɼ��ڵ�
			if (currentStudent != NULL) {
				struct SubScore* newScore = (struct SubScore*)malloc(sizeof(struct SubScore));
				strcpy(newScore->courseName, trimmedValue);
				newScore->next = NULL;

				
				currentScore->next = newScore;
				currentScore = newScore;
			}
		}
		else if (strcmp(trimmedKey, "�޶�ѧ��") == 0) {
			// ����ѧ���ɼ��ڵ�������ֶ�
			if (currentScore != NULL) {
				strcpy(currentScore->semester, trimmedValue);
			}
		}
		else if (strcmp(trimmedKey, "�γ̳ɼ�") == 0) {
			if (currentScore != NULL) {
				float score = atof(trimmedValue);
				currentScore->score = score;
			}
		}
		
		else if (strcmp(trimmedKey, "��ü���") == 0) {
			if (currentScore != NULL) {
				float perGPA = atof(trimmedValue);
				currentScore->perGPA = perGPA;
				//float Score = currentScore->score;
				currentScore->perGPA = exchange_GPA(currentScore->score);
			}
		}
		
		else if (strcmp(trimmedKey, "�Ƿ�����") == 0) {
			if (currentScore != NULL) {
				int isExempted = atoi(trimmedValue);
				currentScore->isExempted = isExempted;
			}
		}
		else if (strcmp(trimmedKey, "�����ؿ�") == 0) {
			if (currentScore != NULL) {
				int isRetake = atoi(trimmedValue);
				currentScore->isretake = isRetake;
			}
		}
		else if (strcmp(trimmedKey, "�Ƿ񼰸�") == 0) {
			if (currentScore != NULL) {
				int isFailed = atoi(trimmedValue);
				currentScore->isFailed = isFailed;
			}
		}
		else if (strcmp(trimmedKey, "�Ƿ���Ч") == 0) {
			if (currentScore != NULL) {
				int isValid = atoi(trimmedValue);
				currentScore->isval = isValid;
			}
		}

		//line = strtok(NULL, "\n");
	}

	// �ͷ��ڴ沢�ر��ļ�
	//free(jsonBuffer);
	//free(jsonBufferCopy);
	fclose(file);

	printf("ѧ���ɼ����ݼ��سɹ���\n");
}

// �����������
void clear_StdGrade(struct Major** head_Major) {
	struct Major* currentMajor = *head_Major;
	while (currentMajor != NULL) {
		struct Grade* currentGrade = currentMajor->grade;
		while (currentGrade != NULL) {
			struct Student* currentStudent = currentGrade->student;
			while (currentStudent != NULL) {
				struct SubScore* currentScore = currentStudent->scores;
				while (currentScore != NULL) {
					struct SubScore* tempScore = currentScore;
					currentScore = currentScore->next;
					free(tempScore);
				}
				struct Student* tempStudent = currentStudent;
				currentStudent = currentStudent->next;
				free(tempStudent);
			}
			struct Grade* tempGrade = currentGrade;
			currentGrade = currentGrade->next;
			free(tempGrade);
		}
		struct Major* tempMajor = currentMajor;
		*head_Major = currentMajor->next;
		free(tempMajor);
		currentMajor = *head_Major;
	}

	printf("���������ѳ�ʼ��\n");
}



const char* All_Aca[] = {
	"",                            // 0��λ�õ�ռλ��
	"01-��ѧ���ѧԺ",             // 1
	"02-��ѧԺ",                   // 2
	"03-�����ѧԺ",               // 3
	"04-����ѧԺ",                 // 4
	"05-����ѧԺ",                 // 5
	"06-����ѧԺ",                 // 6
	"07-��ѧԺ",                   // 7
	"08-����ѧԺ",                 // 8
	"09-��ѧ�����ѧԺB",          // 9
	"10-��ѧѧԺ",                 // 10
	"11-����ѧԺ",                 // 11
	"12-��ѧѧԺ",                 // 12
	"13-������ѧѧԺ",             // 13
	"14-��е�뺽�պ��칤��ѧԺ",   // 14
	"15-��������ѧԺ",             // 15
	"16-���Ͽ�ѧ�빤��ѧԺ",       // 16
	"17-��ͨѧԺ",                 // 17
	"18-������ũҵ����ѧԺ",       // 18
	"19-���ӿ�ѧ�빤��ѧԺ",       // 19
	"20-ͨ�Ź���ѧԺ",             // 20
	"21-�������ѧ�뼼��ѧԺ",     // 21
	"22-�����ѧѧԺ",             // 22
	"23-����̽���ѧ�뼼��ѧԺ",   // 23
	"24-���蹤��ѧԺ",             // 24
	"25-����Դ�뻷��ѧԺ",         // 25
	"26-����ѧԺ",                 // 26
	"27-��������ѧԺ",             // 27
	"28-ҩѧԺ",                   // 28
	"29-����ѧԺ",                 // 29
	"30-������ѧԺ",               // 30
	"",                            // 31��λ�õ�ռλ��
	"",                            // 32��λ�õ�ռλ��
	"33-��ǻҽѧԺ",               // 33
	"34-��ѧ�����ѧԺA",          // 34
	"35-��ѧ�����ѧԺ",           // 35
	"36-�����⽻ѧԺ",             // 36
	"37-�����봫��ѧԺ",           // 37
	"38-����ѧԺ",                 // 38
	"39-���˼����ѧԺ",           // 39
	"40-�˹�����ѧԺ",             // 40
	"",                            // 41��λ�õ�ռλ��
	"",                            // 42��λ�õ�ռλ��
	"",                            // 43��λ�õ�ռλ��
	"",                            // 44��λ�õ�ռλ��
	"",                            // 45��λ�õ�ռλ��
	"",                            // 46��λ�õ�ռλ��
	"",                            // 47��λ�õ�ռλ��
	"",                            // 48��λ�õ�ռλ��
	"",                            // 49��λ�õ�ռλ��
	"50-Ԥ�ƽ���ѧԺ",             // 50
	"",                            // 51��λ�õ�ռλ��
	"",                            // 52��λ�õ�ռλ��
	"",                            // 53��λ�õ�ռλ��
	"54-Ӧ�ü���ѧԺ",             // 54
	"55-���ѧԺ",                 // 55
	"",                            // 56��λ�õ�ռλ��
	"",                            // 57��λ�õ�ռλ��
	"",                            // 58��λ�õ�ռλ��
	"",                            // 59��λ�õ�ռλ��
	"60-��������ѧԺ",             // 60
	"",                            // 61��λ�õ�ռλ��
	"",                            // 62��λ�õ�ռλ��
	"",                            // 63��λ�õ�ռλ��
	"",                            // 64��λ�õ�ռλ��
	"65-������ѧ���������ѧԺ",   // 65
	"",                            // 66��λ�õ�ռλ��
	"",                            // 67��λ�õ�ռλ��
	"",                            // 68��λ�õ�ռλ��
	"",                            // 69��λ�õ�ռλ��
	"70-�ٴ�ҽѧԺ",               // 70
	"71-����ҽѧԺ",               // 71
	"",                            // 72��λ�õ�ռλ��
	"",                            // 73��λ�õ�ռλ��
	"",                            // 74��λ�õ�ռλ��
	"75-�������һ�ٴ�ҽѧԺ",     // 75
	"76-������ڶ��ٴ�ҽѧԺ",     // 76
	"77-����������ٴ�ҽѧԺ",     // 77
	"",                            // 78��λ�õ�ռλ��
	"79-�����ҽѧ��",             // 79
	"",                            // 80��λ�õ�ռλ��
	"81-����ҽѧѧԺ",             // 81
	"82-ֲ���ѧѧԺ",             // 82
	"83-����Ƽ�ѧԺ",             // 83
	"84-ũѧ��������ѧ����",       // 84
	"85-�����ѧѧԺ",             // 85
	"",                            // 86��λ�õ�ռλ��
	"87-ʳƷ��ѧ�빤��ѧԺ",       // 87
};

const char* ALL_Prof[88][15] = {
	{""},                                                                                   // 0
	{"��ѧ���������࣬�μ�ѧ���������أ�", "��ѧ", "���ѧ", "��Ṥ��", "�Ͷ�����ᱣ��"}, // 1
	{"��������ѧ", "��ʷѧ"},                                                               // 2
	{"Ӣ��", "����", "����(��Уר��ƻ�)", "��������", "����", "������",
	 "������(��Уר��ƻ�)"}, // 3
	{"���ֱ���(����רҵ)", "�滭(����רҵ)", "���ѧ", "�Ӿ��������", "�������",
	 "��Ʒ���(����רҵ)"},                                       // 4
	{"�������ָ�������"},                                       // 5
	{"����ѧ��", "����ѧ", "����ѧ", "����ѧ", "���ʾ�����ó��"}, // 6
	{"��ѧ"},                                                     // 7
	{"����ѧ������ѧ", "��������", "��������"},                   // 8
	{"���ѧ", "�������", "���ù���", "����ѧ���������ã�", "���̹���", "�г�Ӫ��", "������Դ����",
	 "�����ѧ�빤��", "��Ϣ��������Ϣϵͳ", "���̹���", "��������", "�����ݹ�����Ӧ��",
	 "����ѧ"},                                                                            // 9
	{"��ѧ��", "��ѧ��Ӧ����ѧ", "��Ϣ������ѧ", "ͳ��ѧ"},                              // 10
	{"����ѧ��", "Ӧ������ѧ", "������", "�����Ϣ��ѧ�빤��", "����ѧ�����������ѧ�� "}, // 11
	{"��ѧ��", "Ӧ�û�ѧ", "���ϻ�ѧ", "�߷��Ӳ����빤��", "��ѧ�����빤��"},              // 12
	{"�����ѧ��", "���＼��", "���﹤����", "������ҩ", "ҩ���Ƽ�"},                      // 13
	{"��е���̣��ı�࣬���� ��ͨ��", "��е����", "��ҵ����", "������ѧ", "�������칤��"}, // 14
	{"�������̣��ı�࣬���й�ͨ��", "��������", "��ҵ���", "��Դ�붯������"},            // 15
	{"������", "���Ͽ�ѧ�빤�� ", "�޻��ǽ������Ϲ���", "���ϳ��ͼ����ƹ���", "��������",
	 "��������(��Уר��ƻ�)"}, // 16
	{"��ͨ������", "��ͨ����", "��ͨ����", "�������񹤳�", "��·������ɺӹ���", "��������",
	 "ũҵ��е�������Զ������ı�࣬���й�ͨ��", "ũҵ��е�������Զ���", "������ѧ�빤��"}, // 17
	{"ũ�־��ù���"},                                                                       // 18
	{"������Ϣ��", "������Ϣ����", "���ӿ�ѧ�뼼��", "΢���� ��ѧ�빤��",
	 "������Ϣ��ѧ�뼼��"}, // 19
	{"ͨ�Ź�����", "ͨ�Ź���(����ר��ƻ�)", "��Ϣ����", "�ռ���Ϣ�����ּ���", "�Զ���",
	 "�����˹���"},                                                             // 20
	{"�������ѧ�뼼��", "����������", "����ռ䰲ȫ"},                         // 21
	{"������", "����ѧ", "��Դ���鹤��", "������Դ����"},                       // 22
	{"���鼼���빤�̿��鼼���빤��", "������Ϣ��ѧ", "��������ѧ", "��湤��"}, // 23
	{"��ľ��", "��ľ����", "���ʹ���"},                                         // 24
	{"ˮ����j", "ˮ����ˮ��Դ����", "����ˮ��ѧ�빤��", "������ѧ�빤��", "������ѧ", "��������",
	 "��������(��Уר��ƻ�)", "����Դ��ѧ�빤��"}, // 25
	{""},                                           // 26
	{"����ҽѧ", "Ԥ��ҽѧ"},                       // 27
	{"ҩѧ", "�ٴ�ҩѧ"},                           // 28
	{"��������ѧ", "����ѧ"},                       // 29
	{"����ѧ�����������򾭼ã�", "Ӧ������ѧ", "����ѧ���������࣬�μ�ѧ���������� ��",
	 "����ѧ������ѧ����ѧ������ѧ"},                                                       // 30
	{""},                                                                                   // 31
	{""},                                                                                   // 32
	{"��ǻҽѧ", "��ǻҽѧ��5+3һ�廯��"},                                                  // 33
	{""},                                                                                   // 34
	{""},                                                                                   // 35
	{"�⽻ѧ"},                                                                             // 36
	{"���Ŵ���ѧ��", "����ѧ", "���ѧ", "�㲥�� �ӱർ"},                                  // 37
	{"����ѧ", "�����벩���ѧ"},                                                           // 38
	{"���˼�������ۣ�������࣬���й�ͨ��", "���˼��������", "˼�����ν���"},             // 39
	{"�˹�����"},                                                                           // 40
	{""},                                                                                   // 41
	{""},                                                                                   // 42
	{""},                                                                                   // 43
	{""},                                                                                   // 44
	{""},                                                                                   // 45
	{""},                                                                                   // 46
	{""},                                                                                   // 47
	{""},                                                                                   // 48
	{""},                                                                                   // 49
	{""},                                                                                   // 50
	{""},                                                                                   // 51
	{""},                                                                                   // 52
	{""},                                                                                   // 53
	{""},                                                                                   // 54
	{"�������", "���ݿ�ѧ������ݼ���"},                                                   // 55
	{""},                                                                                   // 56
	{""},                                                                                   // 57
	{""},                                                                                   // 58
	{""},                                                                                   // 59
	{""},                                                                                   // 60
	{""},                                                                                   // 61
	{""},                                                                                   // 62
	{""},                                                                                   // 63
	{""},                                                                                   // 64
	{"������", "��ؼ���������", "���ܸ�֪����", "�������̼����Զ���"},                     // 65
	{""},                                                                                   // 66
	{""},                                                                                   // 67
	{""},                                                                                   // 68
	{""},                                                                                   // 69
	{""},                                                                                   // 70
	{"����ҽѧ��ѧ"},                                                                       // 71
	{""},                                                                                   // 72
	{""},                                                                                   // 73
	{""},                                                                                   // 74
	{"�ٴ�ҽѧ��һԺ��", "�ٴ�ҽѧ��5+3һ�廯����һԺ��", "�ٴ�ҽѧ��5+3һ�廯������ѧ��"}, // 75
	{"�ٴ�ҽѧ����Ժ��", "�ٴ�ҽѧ��5+3һ�廯������Ժ��"},                                  // 76
	{"�ٴ�ҽ ѧ����Ժ��", "�ٴ�ҽѧ��5+3һ�廯������Ժ��"},                                 // 77
	{""},                                                                                   // 78
	{""},                                                                                   // 79
	{""},                                                                                   // 80
	{"����ҽѧ(ũ��)", "����ҽѧ(��Уר��ƻ�)"},                                           // 81
	{"ֲ������", "ũѧ", "԰��", "ֲ�ﱣ��", "ũҵ ��Դ�뻷��(ũ��)"},                      // 82
	{""},                                                                                   // 83
	{""},                                                                                   // 84
	{"�����ѧ(ũ��)"},                                                                     // 85
	{""},                                                                                   // 86
	{"ʳƷ��ѧ�빤��", "ʳƷ�����밲ȫ"}                                                    // 87
};