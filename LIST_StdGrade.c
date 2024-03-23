#define _CRT_SECURE_NO_WARNINGS 1#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Func_isValid.h"
#include "LIST_StdGrade.h"

//专业节点结构体
struct Major {
    char majorNum[10];  // 专业编号
    struct Major* next;  // 下一个专业节点的指针
	struct Grade* grade;//年级链表的头指针
};
//年级节点结构体
struct Grade {
    int gradeNum;  // 年级
    struct Grade* next;  // 下一个年级节点的指针
	struct Student* student;  // 学生链表的头指针
};
// 学生节点结构体
struct Student {
    int studentID;  // 学号
    int GPA;  // 平均学分绩点
	int rank;	// 排名
	char rankTime[20];	// 排名时间
    struct SubScore* scores;  // 成绩链表的头指针
    struct Student* next;  // 下一个学生节点的指针
};
// 学生成绩节点结构体
struct SubScore {
    char courseName[20];  // 课程名
    float score;  // 课程成绩
    char semester[5];  // 修读学期
    int isExempted;  // 是否免修
    int isFailed;  // 是否挂科
    struct SubScore* next;  // 下一个学生成绩节点的指针
};
//创建专业头节点
struct Major* create_Major() {
	struct Major* newNode = (struct Major*)malloc(sizeof(struct Major));
	if (newNode != NULL) {
        strcpy(newNode->majorNum, "0");
		newNode->next = NULL;
	}
	return newNode;
}



//添加专业节点包含通过专业编号查重的功能
void add_Major(struct Major** head_Major, char majorNum[10]) {
	struct Major* newNode = create_Major();
	struct Major* temp = *head_Major;
	if (newNode != NULL) {
		while (temp->next != NULL) {
			if (strcmp(temp->majorNum, majorNum) == 0) {
				printf("专业编号重复，添加失败。\n");
				return;
			}
			temp = temp->next;
		}
		if (strcmp(temp->majorNum, majorNum) == 0) {
			printf("专业编号重复，添加失败。\n");
			return;
		}
		strcpy(newNode->majorNum, majorNum);
		temp->next = newNode;
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
//创建年级头节点并连接到专业节点
struct Grade* create_Grade(struct Major* major) {
	struct Grade* newNode = (struct Grade*)malloc(sizeof(struct Grade));
	if (newNode != NULL) {
		newNode->gradeNum = 0;
		newNode->next = NULL;
		newNode->student = NULL;
		major->grade = newNode;
	}
	return newNode;
}
//添加年级节点包含通过年级查重的功能
void add_Grade(struct Major* major, int gradeNum) {
	struct Grade* newNode = create_Grade(major);
	struct Grade* temp = major->grade;
	if (newNode != NULL) {
		while (temp->next != NULL) {
			if (temp->gradeNum == gradeNum) {
				printf("年级重复，添加失败。\n");
				return;
			}
			temp = temp->next;
		}
		if (temp->gradeNum == gradeNum) {
			printf("年级重复，添加失败。\n");
			return;
		}
		newNode->gradeNum = gradeNum;
		temp->next = newNode;
	}
}
//通过年级查找年级节点并返回其地址
struct Grade* search_Grade(struct Major* major, int gradeNum) {
	struct Grade* temp = major->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // 未找到匹配的节点
}
//创建学生节点并连接到年级节点
struct Student* create_Student(struct Grade* grade) {
	struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
	if (newNode != NULL) {
		newNode->studentID = 0;
		newNode->GPA = 0;
		newNode->rank = 0;
		strcpy(newNode->rankTime, "0");
		newNode->scores = NULL;
		newNode->next = NULL;
		grade->student = newNode;
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
	struct Grade* tempGrade = search_Grade(tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("年级不存在，添加失败。\n");
		return;
	}
	struct Student* newNode = create_Student(tempGrade);
	struct Student* tempStudent;
	if (newNode != NULL) {
		tempStudent = tempGrade->student;
		while (tempStudent->next != NULL) {
			if (tempStudent->studentID == studentID) {
				printf("学号重复，添加失败。\n");
				return;
			}
			tempStudent = tempStudent->next;
		}
		if (tempStudent->studentID == studentID) {
			printf("学号重复，添加失败。\n");
			return;
		}
		newNode->studentID = studentID;
		tempStudent->next = newNode;
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
	struct SubScore* newNode = (struct SubScore*)malloc(sizeof(struct SubScore));
	if (newNode != NULL) {
		strcpy(newNode->courseName, courseName);
		newNode->score = score;
		strcpy(newNode->semester, semester);
		newNode->isExempted = isExempted;
		newNode->isFailed = isFailed;
		newNode->next = NULL;
		struct SubScore* temp = tempStudent->scores;
		while (temp != NULL) {
			if (strcmp(temp->courseName, courseName) == 0) {
				return -2;
			}
			temp = temp->next;
		}
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
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	if (tempMajor == NULL) {
		return 0;
	}
	struct Grade* tempGrade = tempMajor->grade;
	struct Grade* tempGrade2;
	if (tempGrade != NULL) {
		if (tempGrade->gradeNum == gradeNum) {
			tempMajor->grade = tempGrade->next;
			while (tempGrade->student != NULL) {
				delete_AllScore(head_Major, tempGrade->student->studentID);
				tempGrade2 = tempGrade->student;
				tempGrade->student = tempGrade->student->next;
				free(tempGrade2);
			}
			free(tempGrade);
			return 1;
		}
		while (tempGrade->next != NULL) {
			if (tempGrade->next->gradeNum == gradeNum) {
				while (tempGrade->next->student != NULL) {
					delete_AllScore(head_Major, tempGrade->next->student->studentID);
					tempGrade2 = tempGrade->next->student;
					tempGrade->next->student = tempGrade->next->student->next;
					free(tempGrade2);
				}
				tempGrade2 = tempGrade->next;
				tempGrade->next = tempGrade->next->next;
				free(tempGrade2);
				return 1;
			}
			tempGrade = tempGrade->next;
		}
	}
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
}

//保存个链表到文件，设计格式为：专业编号-年级-学生学号-学生平均学分绩点-学生排名-排名时间-课程名-成绩-修读学期-是否免修-是否挂科，
// 每个数据之间用空格隔开，每个学生的成绩之间用逗号隔开，每个学生之间用分号隔开，每个年级之间用冒号隔开，每个专业之间用换行隔开
// 返回值为1表示保存成功，返回值为0表示保存失败，返回值为-1表示文件打开失败
int saveTo_StdGrade(struct Major** head_Major, char* filename) {
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		return -1;
	}
	struct Major* tempMajor = *head_Major;
	struct Grade* tempGrade;
	struct Student* tempStudent;
	struct SubScore* tempScore;
	while (tempMajor != NULL) {
		tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			tempStudent = tempGrade->student;
			while (tempStudent != NULL) {
				fprintf(fp, "%s-%d-%d-%d-%d-%s", tempMajor->majorNum, tempGrade->gradeNum, tempStudent->studentID, tempStudent->GPA, tempStudent->rank, tempStudent->rankTime);
				tempScore = tempStudent->scores;
				while (tempScore != NULL) {
					fprintf(fp, "-%s-%f-%s-%d-%d", tempScore->courseName, tempScore->score, tempScore->semester, tempScore->isExempted, tempScore->isFailed);
					tempScore = tempScore->next;
					if (tempScore != NULL) {
						fprintf(fp, ",");
					}
				}
				tempStudent = tempStudent->next;
				if (tempStudent != NULL) {
					fprintf(fp, ";");
				}
			}
			tempGrade = tempGrade->next;
			if (tempGrade != NULL) {
				fprintf(fp, ":");
			}
		}
		tempMajor = tempMajor->next;
		if (tempMajor != NULL) {
			fprintf(fp, "\n");
		}
	}
	fclose(fp);
	return 1;
}

// 从文件加载学生信息
int loadFrom_StdGrade(struct Major** head_Major, char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }
    char line[1000];
    while (fgets(line, sizeof(line), fp)) {
        char* token;
        char* majorNum;
        int gradeNum;
        int studentID;
        int GPA;
        int rank;
        char rankTime[20];
        char* courseName;
        float score;
        char semester[5];
        int isExempted;
        int isFailed;
        
        token = strtok(line, "-");
        majorNum = token;
        
        token = strtok(NULL, "-");
        gradeNum = atoi(token);
        
        token = strtok(NULL, "-");
        studentID = atoi(token);
        
        token = strtok(NULL, "-");
        GPA = atoi(token);
        
        token = strtok(NULL, "-");
        rank = atoi(token);
        
        token = strtok(NULL, "-");
        strcpy(rankTime, token);
        
        struct Major* tempMajor = search_Major(head_Major, majorNum);
        if (tempMajor == NULL) {
            tempMajor = create_Major();
            add_Major(head_Major, majorNum);
        }
        
        struct Grade* tempGrade = search_Grade(tempMajor, gradeNum);
        if (tempGrade == NULL) {
            tempGrade = create_Grade(tempMajor);
            add_Grade(tempMajor, gradeNum);
        }
        
        struct Student* tempStudent = create_Student(tempGrade);
        tempStudent->studentID = studentID;
        tempStudent->GPA = GPA;
        tempStudent->rank = rank;
        strcpy(tempStudent->rankTime, rankTime);
        
        token = strtok(NULL, "-");
        while (token != NULL) {
            courseName = token;
            
            token = strtok(NULL, "-");
            score = atof(token);
            
            token = strtok(NULL, "-");
            strcpy(semester, token);
            
            token = strtok(NULL, "-");
            isExempted = atoi(token);
            
            token = strtok(NULL, ",");
            if (token != NULL) {
                isFailed = atoi(token);
            } else {
                isFailed = atoi(token);
                token = strtok(NULL, "-");
            }
            
            struct SubScore* tempScore = (struct SubScore*)malloc(sizeof(struct SubScore));
            strcpy(tempScore->courseName, courseName);
            tempScore->score = score;
            strcpy(tempScore->semester, semester);
            tempScore->isExempted = isExempted;
            tempScore->isFailed = isFailed;
            tempScore->next = NULL;
            
            if (tempStudent->scores == NULL) {
                tempStudent->scores = tempScore;
            } else {
                struct SubScore* temp = tempStudent->scores;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = tempScore;
            }
            
            token = strtok(NULL, "-");
        }
    }
    fclose(fp);
    return 1;
}

