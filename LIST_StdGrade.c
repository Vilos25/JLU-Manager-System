#define _CRT_SECURE_NO_WARNINGS 1#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Func_isValid.h"
#include "LIST_StdGrade.h"

//רҵ�ڵ�ṹ��
struct Major {
    char majorNum[10];  // רҵ���
    struct Major* next;  // ��һ��רҵ�ڵ��ָ��
	struct Grade* grade;//�꼶�����ͷָ��
};
//�꼶�ڵ�ṹ��
struct Grade {
    int gradeNum;  // �꼶
    struct Grade* next;  // ��һ���꼶�ڵ��ָ��
	struct Student* student;  // ѧ�������ͷָ��
};
// ѧ���ڵ�ṹ��
struct Student {
    int studentID;  // ѧ��
    int GPA;  // ƽ��ѧ�ּ���
	int rank;	// ����
	char rankTime[20];	// ����ʱ��
    struct SubScore* scores;  // �ɼ������ͷָ��
    struct Student* next;  // ��һ��ѧ���ڵ��ָ��
};
// ѧ���ɼ��ڵ�ṹ��
struct SubScore {
    char courseName[20];  // �γ���
    float score;  // �γ̳ɼ�
    char semester[5];  // �޶�ѧ��
    int isExempted;  // �Ƿ�����
    int isFailed;  // �Ƿ�ҿ�
    struct SubScore* next;  // ��һ��ѧ���ɼ��ڵ��ָ��
};
//����רҵͷ�ڵ�
struct Major* create_Major() {
	struct Major* newNode = (struct Major*)malloc(sizeof(struct Major));
	if (newNode != NULL) {
        strcpy(newNode->majorNum, "0");
		newNode->next = NULL;
	}
	return newNode;
}



//���רҵ�ڵ����ͨ��רҵ��Ų��صĹ���
void add_Major(struct Major** head_Major, char majorNum[10]) {
	struct Major* newNode = create_Major();
	struct Major* temp = *head_Major;
	if (newNode != NULL) {
		while (temp->next != NULL) {
			if (strcmp(temp->majorNum, majorNum) == 0) {
				printf("רҵ����ظ������ʧ�ܡ�\n");
				return;
			}
			temp = temp->next;
		}
		if (strcmp(temp->majorNum, majorNum) == 0) {
			printf("רҵ����ظ������ʧ�ܡ�\n");
			return;
		}
		strcpy(newNode->majorNum, majorNum);
		temp->next = newNode;
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
//�����꼶ͷ�ڵ㲢���ӵ�רҵ�ڵ�
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
//����꼶�ڵ����ͨ���꼶���صĹ���
void add_Grade(struct Major* major, int gradeNum) {
	struct Grade* newNode = create_Grade(major);
	struct Grade* temp = major->grade;
	if (newNode != NULL) {
		while (temp->next != NULL) {
			if (temp->gradeNum == gradeNum) {
				printf("�꼶�ظ������ʧ�ܡ�\n");
				return;
			}
			temp = temp->next;
		}
		if (temp->gradeNum == gradeNum) {
			printf("�꼶�ظ������ʧ�ܡ�\n");
			return;
		}
		newNode->gradeNum = gradeNum;
		temp->next = newNode;
	}
}
//ͨ���꼶�����꼶�ڵ㲢�������ַ
struct Grade* search_Grade(struct Major* major, int gradeNum) {
	struct Grade* temp = major->grade;
	while (temp != NULL) {
		if (temp->gradeNum == gradeNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // δ�ҵ�ƥ��Ľڵ�
}
//����ѧ���ڵ㲢���ӵ��꼶�ڵ�
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
//���ѧ���ڵ����ͨ�������������н���ѧ�Ų��صĹ���
void add_Student(struct Major** head_Major, int studentID, char majorNum[10], int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	if (tempMajor == NULL) {
		printf("רҵ�����ڣ����ʧ�ܡ�\n");
		return;
	}
	struct Grade* tempGrade = search_Grade(tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("�꼶�����ڣ����ʧ�ܡ�\n");
		return;
	}
	struct Student* newNode = create_Student(tempGrade);
	struct Student* tempStudent;
	if (newNode != NULL) {
		tempStudent = tempGrade->student;
		while (tempStudent->next != NULL) {
			if (tempStudent->studentID == studentID) {
				printf("ѧ���ظ������ʧ�ܡ�\n");
				return;
			}
			tempStudent = tempStudent->next;
		}
		if (tempStudent->studentID == studentID) {
			printf("ѧ���ظ������ʧ�ܡ�\n");
			return;
		}
		newNode->studentID = studentID;
		tempStudent->next = newNode;
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
}

//����������ļ�����Ƹ�ʽΪ��רҵ���-�꼶-ѧ��ѧ��-ѧ��ƽ��ѧ�ּ���-ѧ������-����ʱ��-�γ���-�ɼ�-�޶�ѧ��-�Ƿ�����-�Ƿ�ҿƣ�
// ÿ������֮���ÿո������ÿ��ѧ���ĳɼ�֮���ö��Ÿ�����ÿ��ѧ��֮���÷ֺŸ�����ÿ���꼶֮����ð�Ÿ�����ÿ��רҵ֮���û��и���
// ����ֵΪ1��ʾ����ɹ�������ֵΪ0��ʾ����ʧ�ܣ�����ֵΪ-1��ʾ�ļ���ʧ��
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

// ���ļ�����ѧ����Ϣ
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

