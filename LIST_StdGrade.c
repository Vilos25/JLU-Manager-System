#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Func_isValid.h"
#include "LIST_StdGrade.h"
//����רҵͷ�ڵ㲢��ʼ��
struct Major* create_Major() {
	struct Major* newNode = (struct Major*)malloc(sizeof(struct Major));
	if (newNode != NULL) {
		strcpy(newNode->majorNum, "0");
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
				newStudent->GPA = 0;
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
					newScore->isFailed = 0;
					newScore->next = NULL;
					newStudent->scores = newScore;
				}
			}

		}
	}
	return newNode;
}


//���רҵ�ڵ����ͨ��רҵ��Ų��صĹ���
void add_Major(struct Major** head_Major, char majorNum[10]) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (strcmp(temp->majorNum, majorNum) == 0) {
			printf("רҵ����ظ������ʧ�ܡ�\n");
			return;
		}
		temp = temp->next;
	}
	
	struct Major* newNode = create_Major();
	if (newNode != NULL) {
		strcpy(newNode->majorNum, majorNum);
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
struct Major* search_Major(struct Major** head_Major, const char* majorNum) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (strcmp(temp->majorNum, majorNum) == 0) {
			return temp;
		}
		temp = temp->next;
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
			newStudent->GPA = 0;
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
				newScore->isFailed = 0;
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
		newNode->GPA = 0;
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
			newScore->isFailed = 0;
			newScore->next = NULL;
			newNode->scores = newScore;
		}
	}
	return newNode;
}
//���ѧ���ڵ����ͨ�������������н���ѧ�Ų��صĹ���
void add_Student(struct Major** head_Major, int studentID, char majorNum[10], int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
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

//��ѧ���ڵ���ӳɼ�������ͨ���γ������صĹ��ܣ�����ֵΪ1��ʾ��ӳɹ�������ֵΪ0��ʾ���ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ����ظ�
int add_Score(struct Major** head_Major, int studentID, char courseName[20], float score, char semester[5], int isExempted, int isFailed) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		return -1;
	}
	struct SubScore* temp = tempStudent->scores;
	while (temp != NULL) {
		if (strcmp(temp->courseName, courseName) == 0) {
			return -2;
		}
		temp = temp->next;
	}
	struct SubScore* newNode = (struct SubScore*)malloc(sizeof(struct SubScore));
	if (newNode != NULL) {
		strcpy(newNode->courseName, courseName);
		newNode->score = score;
		strcpy(newNode->semester, semester);
		newNode->isExempted = isExempted;
		newNode->isFailed = isFailed;
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
	struct SubScore* temp = tempStudent->scores;
	while (temp != NULL) {
		if (strcmp(temp->courseName, courseName) == 0) {
			temp->score = newScore;
			return 1;
		}
		temp = temp->next;
	}
	return -2;
}
//ɾ��ָ��ѧ����ָ���ɼ�������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ���������
int delete_Score(struct Major** head_Major, int studentID, char courseName[20]) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		return -1;
	}
	struct SubScore* temp = tempStudent->scores;
	struct SubScore* temp2;
	if (temp != NULL) {
		if (strcmp(temp->courseName, courseName) == 0) {
			tempStudent->scores = temp->next;
			free(temp);
			return 1;
		}
		while (temp->next != NULL) {
			if (strcmp(temp->next->courseName, courseName) == 0) {
				temp2 = temp->next;
				temp->next = temp->next->next;
				free(temp2);
				return 1;
			}
			temp = temp->next;
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
//ɾ��ָ���꼶������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Grade(struct Major** head_Major, char majorNum[10], int gradeNum) {
	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (strcmp(tempMajor->majorNum, majorNum) == 0) {
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
int delete_Major(struct Major** head_Major, char majorNum[10]) {
	struct Major* tempMajor = *head_Major;
	struct Major* tempMajor2;
	if (tempMajor != NULL) {
		if (strcmp(tempMajor->majorNum, majorNum) == 0) {
			while (tempMajor->grade != NULL) {
				delete_Grade(head_Major, majorNum, tempMajor->grade->gradeNum);
			}
			tempMajor2 = tempMajor;
			*head_Major = tempMajor->next;
			free(tempMajor2);
			return 1;
		}
		while (tempMajor->next != NULL) {
			if (strcmp(tempMajor->next->majorNum, majorNum) == 0) {
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
//��ѯ����ѧ�������гɼ�
void query_Scores(struct Major** head_Major, int studentID) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		printf("ѧ�������ڡ�\n");
		return;
	}
	struct SubScore* temp = tempStudent->scores;
	if (temp == NULL) {
		printf("ѧ���޳ɼ���\n");
		return;
	}
	printf("ѧ��ѧ�ţ�%d\n", tempStudent->studentID);
	printf("ѧ���ɼ���\n");
	while (temp != NULL) {
		printf("�γ�����%s\n", temp->courseName);
		printf("�ɼ���%f\n", temp->score);
		printf("�޶�ѧ�ڣ�%s\n", temp->semester);
		if (temp->isExempted == 1) {
			printf("����\n");
		}
		if (temp->isFailed == 1) {
			printf("�ҿ�\n");
		}
		temp = temp->next;
	}
	return;
}

// �����������ݵ��ļ�
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

	printf("������������ա�\n");
}