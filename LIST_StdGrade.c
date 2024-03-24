#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Func_isValid.h"
#include "LIST_StdGrade.h"
//创建专业头节点并初始化
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


//添加专业节点包含通过专业编号查重的功能
void add_Major(struct Major** head_Major, char majorNum[10]) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (strcmp(temp->majorNum, majorNum) == 0) {
			printf("专业编号重复，添加失败。\n");
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
			//在链表尾部添加新节点
			temp = *head_Major;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
}
//通过专业编号查找专业节点并返回其地址
struct Major* search_Major(struct Major** head_Major, const char* majorNum) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (strcmp(temp->majorNum, majorNum) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // 未找到匹配的节点
}
//创建年级头节点，返回值为新创建的年级节点的地址，返回值为NULL表示创建失败，初始化年级节点的学生节点
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

//添加年级节点包含通过年级查重的功能，返回值为1表示添加成功，返回值为0表示添加失败
void add_Grade(struct Major* Major, int gradeNum) {
	struct Grade* temp = Major->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			printf("年级重复，添加失败。\n");
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
	//在链表尾部添加新节点
	{
		temp = Major->grade;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newNode;
	}
}

//通过年级查找年级节点并返回其地址
struct Grade* search_Grade(struct Major** Major, int gradeNum) {
	struct Grade* temp = (*Major)->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // 未找到匹配的节点
}


//创建学生节点
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
//添加学生节点包含通过在整个链表中进行学号查重的功能
void add_Student(struct Major** head_Major, int studentID, char majorNum[10], int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	if (tempMajor == NULL) {
		printf("专业不存在，添加失败。\n");
		return;
	}
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("年级不存在，添加失败。\n");
		return;
	}
	struct Student* tempStudent = tempGrade->student;
	while (tempStudent != NULL) {
		if (tempStudent->studentID == studentID) {
			printf("学号重复，添加失败。\n");
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



//通过学号在整个链表中查找单个学生节点
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
	return NULL;  // 未找到匹配的节点
}

//给学生节点添加成绩，包含通过课程名查重的功能，返回值为1表示添加成功，返回值为0表示添加失败，返回值为-1表示学生不存在，返回值为-2表示课程名重复
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
//修改指定学生的指定成绩，返回值为1表示修改成功，返回值为0表示修改失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
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
//删除指定学生的指定成绩，返回值为1表示删除成功，返回值为0表示删除失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
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
//删除指定学生的所有成绩，返回值为1表示删除成功，返回值为0表示删除失败，返回值为-1表示学生不存在
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
//删除指定学生，返回值为1表示删除成功，返回值为0表示删除失败
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
//删除指定年级，返回值为1表示删除成功，返回值为0表示删除失败
int delete_Grade(struct Major** head_Major, char majorNum[10], int gradeNum) {
	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (strcmp(tempMajor->majorNum, majorNum) == 0) {
			struct Grade* currentGrade = NULL;
			currentGrade = tempMajor->grade;
			struct Grade* prevGrade = NULL;

			while (currentGrade != NULL) {
				if (currentGrade->gradeNum == gradeNum) {
					// 删除年级节点
					if (prevGrade == NULL) {
						tempMajor->grade = currentGrade->next;
					}
					else {
						prevGrade->next = currentGrade->next;
					}

					// 删除年级下的所有学生及其成绩
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
					printf("年级删除成功。\n");
					return 1;
				}
				prevGrade = currentGrade;
				currentGrade = currentGrade->next;
			}
			printf("找不到指定的年级。\n");
			return 0;
		}
		tempMajor = tempMajor->next;
	}
	printf("找不到指定的专业。\n");
	return 0;
}

//删除指定专业，返回值为1表示删除成功，返回值为0表示删除失败
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
//查询单个学生的所有成绩
void query_Scores(struct Major** head_Major, int studentID) {
	struct Student* tempStudent = search_Student(head_Major, studentID);
	if (tempStudent == NULL) {
		printf("学生不存在。\n");
		return;
	}
	struct SubScore* temp = tempStudent->scores;
	if (temp == NULL) {
		printf("学生无成绩。\n");
		return;
	}
	printf("学生学号：%d\n", tempStudent->studentID);
	printf("学生成绩：\n");
	while (temp != NULL) {
		printf("课程名：%s\n", temp->courseName);
		printf("成绩：%f\n", temp->score);
		printf("修读学期：%s\n", temp->semester);
		if (temp->isExempted == 1) {
			printf("免修\n");
		}
		if (temp->isFailed == 1) {
			printf("挂科\n");
		}
		temp = temp->next;
	}
	return;
}

// 保存链表数据到文件
void saveTo_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
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
	printf("数据保存成功。\n");
}

// 从文件读入数据到链表
void loadFrom_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return;
	}

	clear_StdGrade(head_Major);

	char line[100];
	struct Major* currentMajor = NULL;
	struct Grade* currentGrade = NULL;
	struct Student* currentStudent = NULL;

	while (fgets(line, sizeof(line), file)) {
		if (strncmp(line, "Major: ", 7) == 0) {
			// 添加专业节点
			char majorNum[10];
			sscanf(line, "Major: %s", majorNum);
			add_Major(head_Major, majorNum);
			currentMajor = search_Major(head_Major, majorNum);
		}
		else if (strncmp(line, "Grade: ", 7) == 0) {
			// 添加年级节点
			int gradeNum;
			sscanf(line, "Grade: %d", &gradeNum);
			add_Grade(currentMajor, gradeNum);
			currentGrade = search_Grade(&currentMajor, gradeNum);
		}
		else if (strncmp(line, "Student: ", 9) == 0) {
			// 添加学生节点
			int studentID;
			sscanf(line, "Student: %d", &studentID);
			add_Student(head_Major, studentID, currentMajor->majorNum, currentGrade->gradeNum);
			currentStudent = search_Student(head_Major, studentID);
		}
		else if (strncmp(line, "Score: ", 7) == 0) {
			// 添加成绩节点
			char courseName[20];
			float score;
			char semester[5];
			int isExempted, isFailed;
			sscanf(line, "Score: %s %f %s %d %d", courseName, &score, semester, &isExempted, &isFailed);
			add_Score(head_Major, currentStudent->studentID, courseName, score, semester, isExempted, isFailed);
		}
	}

	fclose(file);
	printf("数据读取成功。\n");
}

// 清空链表数据
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

	printf("链表数据已清空。\n");
}