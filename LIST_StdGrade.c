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
//创建专业头节点并初始化
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


//添加专业节点包含通过专业编号查重的功能
void add_Major(struct Major** head_Major, int majorNum) {
	struct Major* temp = *head_Major;
	while (temp != NULL) {
		if (temp->majorNum == majorNum) {
			printf("专业编号重复，添加失败。\n");
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
struct Major* search_Major(struct Major* head_Major, const int majorNum) {
	struct Major* temp = head_Major;
	while (temp != NULL) {
		if (temp->majorNum == majorNum) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;  // 未找到匹配的节点
}

//给一个学号，查找该名学生所在的年级节点
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
	return NULL;  // 未找到匹配的节点
}

//给一个学号，查找该名学生所在的专业节点
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
//添加学生节点包含通过在整个链表中进行学号查重的功能
void add_Student(struct Major** head_Major, int studentID, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(*head_Major, majorNum);
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

//给学生节点添加成绩，包含通过课程名查重的功能，返回值为1表示添加成功，返回值为0表示添加失败，返回值为-1表示学生不存在，如果重复就标记为重修
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
				printf("该课程已存在，且已重修，如需修改请转到<修改成绩>选项。");
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
		printf("该课程已存在，是否添加重修成绩？(1.是  2.否)");
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
//修改指定学生的指定成绩，返回值为1表示修改成功，返回值为0表示修改失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
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
		printf("该课程已被重修，已修改重修成绩");
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
		printf("该课程只被初修，是否要更改初修成绩？(1.是  2.否): ");
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
//删除指定学生的指定成绩，返回值为1表示删除成功，返回值为0表示删除失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
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
		printf("该课程已被重修，已删除重修成绩");
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
		printf("该课程只被初修，是否要删除初修成绩？(1.是  2.否): ");
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
//显示指定年级的所有学生
void display_Grade(struct Major* head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	if (tempMajor == NULL) {
		printf("找不到指定的专业。\n");
		return;
	}
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	if (tempGrade == NULL) {
		printf("找不到指定的年级。\n");
		return;
	}
	struct Student* tempStudent = tempGrade->student;
	if (tempStudent->next == NULL) {
		printf("该年级无学生。\n");
		return;
	}
	//只给年级，对该年级的学生成绩进行冒泡排序并更新排名
	Sort_Grade(head_Major, majorNum, gradeNum);
	tempStudent = tempStudent->next;
	system("cls");
	int line = 0, Page = 1, cnt = 1;
	int rc40 = 0,rc30 = 0,rc20 = 0,rc10 = 0;
	float percent5 = 0, percent10 = 0, percent15 = 0, percent30 = 0, percent50 = 0;
	int tot = calculate_GradeStudentNum(head_Major, majorNum, gradeNum);
	while (tempStudent != NULL) {
		if(line==0)
		printf("\t%s-%s——%d级  学生成绩————第%d页\n\n", All_Aca[majorNum / 100], ALL_Prof[majorNum / 100][majorNum % 100], gradeNum, Page++);
		printf("序号：%d \t学号：%d\t\t", cnt++, tempStudent->studentID);
		tempStudent->GPA = calculate_GPA(head_Major, tempStudent->studentID, head_SubInfor);
		printf("GPA：%f\t\t", tempStudent->GPA + tempStudent->add_GPA);
		tempStudent->rank = Grade_ranking(head_Major, tempStudent->studentID, 0, tempStudent->GPA, gradeNum);
		printf("排名：%d \t", tempStudent->rank);
		printf("排名时间：%s\n", tempStudent->rankTime);

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
	//输出统计信息
	printf("\n\t\t\t年级成绩统计\n\n");
	printf("GPA分段：\t4.0以上：%d人\t3.0-3.9：%d人\t2.0-2.9：%d人\t1.0-1.9：%d人\n", rc40, rc30, rc20, rc10);
	printf("GPA分段百分比：\t4.0以上：%.2f%%\t3.0-3.9：%.2f%%\t2.0-2.9：%.2f%%\t1.0-1.9：%.2f%%\n", (float)rc40 / tot * 100, (float)rc30 / tot * 100, (float)rc20 / tot * 100, (float)rc10 / tot * 100);
	printf("GPA百分比分段：\t前5%%：%.5f\t前10%%：%.5f\t前15%%：%.5f\t前30%%：%.5f\t前50%%：%.5f\n\n", percent5, percent10, percent15, percent30, percent50);
	printf("百分比人数：前5%%：%d人\t前10%%：%d人\t前15%%：%d人\t前30%%：%d人\t前50%%：%d人\n", (int)(tot * 0.05), (int)(tot * 0.1), (int)(tot * 0.15), (int)(tot * 0.3), (int)(tot * 0.5));
	return;
}

//显示所有专业
void display_AllMajor(struct Major* head_Major) {
	struct Major* tempMajor = head_Major;
	if (tempMajor == NULL) {
		printf("无专业。\n");
		return;
	}
	system("cls");
	while (tempMajor != NULL) {
		printf("\n\t%s-%s  专业\n", All_Aca[tempMajor->majorNum / 100], ALL_Prof[tempMajor->majorNum / 100][tempMajor->majorNum % 100]);
		struct Grade* tempGrade = tempMajor->grade;
		while (tempGrade != NULL) {
			display_Grade(head_Major, tempMajor->majorNum, tempGrade->gradeNum);
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return;
}

//显示链表内的所有专业和所有年级
void display_AllMajorAndGrade(struct Major* head_Major) {
	struct Major* tempMajor = head_Major->next;
	if (tempMajor == NULL) {
		printf("无专业。\n");
		return;
	}
	system("cls");
	while (tempMajor != NULL) {
		printf("\n\n\t专业编号：%d  专业：<%s-%s> \t\t年级：", tempMajor->majorNum, All_Aca[tempMajor->majorNum / 100], ALL_Prof[tempMajor->majorNum / 100][tempMajor->majorNum % 100]);
		struct Grade* tempGrade = (tempMajor->grade)->next;
		while (tempGrade != NULL) {
			printf(" <%d级>", tempGrade->gradeNum);
			tempGrade = tempGrade->next;
		}
		tempMajor = tempMajor->next;
	}
	return;
}




//显示一个学生的专业和年级
void display_StudentMajorAndGrade(struct Major* head_Major, int studentID) {
	struct Major* tempMajor = search_MajorByStudentID(head_Major, studentID);
	if (tempMajor == NULL) {
		printf("\n\t\t\t找不到指定的学生。\n");
		return;
	}
	struct Grade* tempGrade = search_GradeByStudentID(&tempMajor, studentID);
	if (tempGrade == NULL) {
		printf("\n\t\t\t找不到指定的学生。\n");
		return;
	}
	//system("cls");
	printf("\n\n\t专业编号：<%d>  专业：<%s-%s> \t\t年级：", tempMajor->majorNum, All_Aca[tempMajor->majorNum / 100], ALL_Prof[tempMajor->majorNum / 100][tempMajor->majorNum % 100]);
	printf("<%d级>\n", tempGrade->gradeNum);
	return;
}

//将一个学生节点降级，返回值为1表示降级成功，返回值为0表示降级失败，返回值为-1表示学生不存在
int demote_Student(struct Major** head_Major, int studentID, int targetGradeNum) {
    struct Major* tempMajor = *head_Major;
    struct Grade* tempGrade;
    struct Student* tempStudent;
    while (tempMajor != NULL) {
        tempGrade = tempMajor->grade;
        while (tempGrade != NULL) {
            tempStudent = tempGrade->student;
            while (tempStudent != NULL) {
                if (tempStudent->studentID == studentID) {
                    // 保存当前年级节点和学生节点的信息
                    struct Grade* currentGrade = tempGrade;
                    struct Student* currentStudent = tempStudent;
                    // 在目标年级中查找学生节点
                    struct Grade* targetGrade = search_Grade(head_Major, targetGradeNum);
                    if (targetGrade == NULL) {
                        printf("目标年级不存在，降级失败。\n");
                        return 0;
                    }
                    // 在目标年级中查找学生节点是否已存在
                    struct Student* targetStudent = targetGrade->student;
                    while (targetStudent != NULL) {
                        if (targetStudent->studentID == studentID) {
                            printf("学生已存在于目标年级，降级失败。\n");
                            return 0;
                        }
                        targetStudent = targetStudent->next;
                    }
                    // 从当前年级中删除学生节点
                    if (currentGrade->student == currentStudent) {
                        currentGrade->student = currentStudent->next;
                    } else {
                        struct Student* prevStudent = currentGrade->student;
                        while (prevStudent->next != currentStudent) {
                            prevStudent = prevStudent->next;
                        }
                        prevStudent->next = currentStudent->next;
                    }
                    // 将学生节点添加到目标年级中
                    currentStudent->next = targetGrade->student;
                    targetGrade->student = currentStudent;
                    printf("学生降级成功。\n");
                    return 1;
                }
                tempStudent = tempStudent->next;
            }
            tempGrade = tempGrade->next;
        }
        tempMajor = tempMajor->next;
    }
    printf("学生不存在，降级失败。\n");
    return -1;
}

//将一个学生节点转到不同专业的同年级，返回值为1表示转专业成功，返回值为0表示转专业失败，返回值为-1表示学生不存在
int transfer_Student(struct Major** head_Major, int studentID, int targetMajorNum, int targetGradeNum) {
    struct Major* sourceMajor = search_MajorByStudentID(*head_Major, studentID);
    if (sourceMajor == NULL) {
        printf("\n\t\t\t\t学生不存在，学籍变动失败。\n");
        return -1;
    }
    struct Major* targetMajor = search_Major(*head_Major, targetMajorNum);
    if (targetMajor == NULL) {
        printf("\n\t\t\t\t目标专业不存在，学籍变动失败。\n");
        return 0;
    }
    struct Grade* sourceGrade = search_GradeByStudentID(&sourceMajor, studentID);
    if (sourceGrade == NULL) {
        printf("\n\t\t\t\t学生所在年级不存在，学籍变动失败。\n");
        return 0;
    }
    struct Grade* targetGrade = search_Grade(&targetMajor, targetGradeNum);
    if (targetGrade == NULL) {
        printf("\n\t\t\t\t目标年级不存在，学籍变动失败。\n");
        return 0;
    }
    struct Student* sourceStudent = search_Student(&sourceMajor, studentID);
    if (sourceStudent == NULL) {
        printf("\n\t\t\t\t学生不存在，学籍变动失败。\n");
        return -1;
    }
    struct Student* targetStudent = create_Student();
    if (targetStudent == NULL) {
        printf("\n\t\t\t\t内存分配失败，学籍变动失败。\n");
        return 0;
    }
    targetStudent->studentID = sourceStudent->studentID;
    targetStudent->GPA = sourceStudent->GPA;
    targetStudent->add_GPA = sourceStudent->add_GPA;
    targetStudent->rank = sourceStudent->rank;
    strcpy(targetStudent->rankTime, sourceStudent->rankTime);
    targetStudent->scores = sourceStudent->scores;
    targetStudent->next = (targetGrade->student)->next;
    (targetGrade->student)->next = targetStudent;
    if (sourceGrade->student == sourceStudent) {
        sourceGrade->student = sourceStudent->next;
    } else {
        struct Student* prevStudent = sourceGrade->student;
        while (prevStudent->next != sourceStudent) {
            prevStudent = prevStudent->next;
        }
        prevStudent->next = sourceStudent->next;
    }
    printf("\n\t\t\t\t学籍变动成功。\n");
    return 1;
}


//删除指定年级，返回值为1表示删除成功，返回值为0表示删除失败
int delete_Grade(struct Major** head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (tempMajor->majorNum == majorNum) {
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
        //printf("学生不存在。\n");
        return 1;
    }
    struct SubScore* temp = tempStudent->scores->next;
    if (temp == NULL) {
        //printf("学生无成绩。\n");
        return 2;
    }
	int g4 = 0, g3 = 0, g2 = 0, g1 = 0, g0 = 0;
    printf("学生学号：%d\n", tempStudent->studentID);
    printf("%-15s %-22s %-8s %-8s %-13s %-10s %-8s %-8s %-8s %-8s\n", "课程编号", "课程名", "学分", "成绩", "修读学期", "获得绩点", "是否免修", "重修重考", "是否及格", "是否有效");
    while (temp != NULL) {
        // 通过课程号查找节点并返回其地址
        printf("%-15s %-21s  %-7.1f %-8.2f %-16s %-10.1f %-8s %-8s %-8s %-8s\n", temp->courseName, search_SubInfor(head_SubInfor, temp->courseName)->SubName,
			search_SubInfor(head_SubInfor, temp->courseName)->SubInforScore,
            temp->score, temp->semester, temp->perGPA, temp->isExempted == 1 ? "是" : "否", temp->isretake == 0 ? "初修" : "重修",
            temp->isFailed == 1 ? "挂科" : "", temp->isval == 1 ? "无效" : "有效");
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
	printf("\n绩点分布：\t4.0：%d门 \t3.0-3.9：%d门 \t2.0-2.9：%d门 \t1.0-1.9：%d门 \t0-0.9：%d门\n", g4, g3, g2, g1, g0);
    return 0;
}

// 保存链表数据到文件
/*
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
*/

// 保存链表数据到文件(JSON格式)
void saveTo_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return;
	}

	// 开始构建JSON字符串
	fprintf(file, "{\n");

	struct Major* tempMajor = *head_Major;
	while (tempMajor != NULL) {
		if (tempMajor->majorNum == 0) {
			tempMajor = tempMajor->next;
			continue;
		}
		fprintf(file, "\t\"专业\": \"%d\"\n", tempMajor->majorNum);

		struct Grade* tempGrade = tempMajor->grade;
		fprintf(file, "\t\"各个年级\": [\n");
		while (tempGrade != NULL) {
			if (tempGrade->gradeNum == 0) {
				tempGrade = tempGrade->next;
				continue;
			}
			fprintf(file, "\t\t{\n");
			fprintf(file, "\t\t\t\"年级\": \"%d\"\n", tempGrade->gradeNum);

			struct Student* tempStudent = tempGrade->student;
			fprintf(file, "\t\t\t\"学生\": [\n");
			while (tempStudent != NULL) {
				if (tempStudent->studentID == 0) {
					tempStudent = tempStudent->next;
					continue;
				}
				fprintf(file, "\t\t\t\t{\n");
				fprintf(file, "\t\t\t\t\t\"学号\": \"%d\"\n", tempStudent->studentID);
				fprintf(file, "\t\t\t\t\t\"GPA\": \"%f\"\n", tempStudent->GPA);
				fprintf(file, "\t\t\t\t\t\"素质加分\": \"%f\"\n", tempStudent->add_GPA);
				fprintf(file, "\t\t\t\t\t\"排名\": \"%d\"\n", tempStudent->rank);
				fprintf(file, "\t\t\t\t\t\"排名时间\": \"%s\"\n", tempStudent->rankTime);

				struct SubScore* tempScore = tempStudent->scores;
				fprintf(file, "\t\t\t\t\t\"各科成绩\": [\n");
				while (tempScore != NULL) {
					if (strcmp(tempScore->courseName, "0") == 0) {
						tempScore = tempScore->next;
						continue;
					}
					fprintf(file, "\t\t\t\t\t\t{\n");
					fprintf(file, "\t\t\t\t\t\t\t\"课程号\": \"%s\"\n", tempScore->courseName);
					fprintf(file, "\t\t\t\t\t\t\t\"修读学期\": \"%s\"\n", tempScore->semester);
					fprintf(file, "\t\t\t\t\t\t\t\"课程成绩\": \"%f\"\n", tempScore->score);
					fprintf(file, "\t\t\t\t\t\t\t\"获得绩点\": \"%f\"\n", tempScore->perGPA);
					fprintf(file, "\t\t\t\t\t\t\t\"是否免修\": \"%d\"\n", tempScore->isExempted);
					fprintf(file, "\t\t\t\t\t\t\t\"重修重考\": \"%d\"\n", tempScore->isretake);
					fprintf(file, "\t\t\t\t\t\t\t\"是否及格\": \"%d\"\n", tempScore->isFailed);
					fprintf(file, "\t\t\t\t\t\t\t\"是否有效\": \"%d\"\n", tempScore->isval);
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

	// 结束构建JSON字符串
	fprintf(file, "}\n");

	fclose(file);
	//printf("数据保存成功。\n");
}

/*
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
*/

// 从文件读取JSON数据并构建链表
void loadFrom_StdGrade(struct Major** head_Major, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return;
	}

	//创建专业头节点
	clear_StdGrade(head_Major);
	*head_Major = create_Major();

	// 读取文件中的JSON数据
	/*fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	rewind(file);
	char* jsonBuffer = (char*)malloc(fileSize + 1);
	if (jsonBuffer == NULL) {
		fclose(file);
		printf("内存分配失败\n");
		return;
	}
	fread(jsonBuffer, 1, fileSize, file);
	jsonBuffer[fileSize] = '\0';

	char* jsonBufferCopy = strdup(jsonBuffer);  // 创建副本字符串
	char* line = strtok(jsonBufferCopy, "\n");
	*/
	// 解析JSON数据并构建链表
	struct Major* currentMajor = NULL;
	struct Grade* currentGrade = NULL;
	struct Student* currentStudent = NULL;
	struct SubScore* currentScore = NULL;
	
	
	char line[100];
	while (fgets(line, sizeof(line), file)) {
		// 解析每一行的数据
		char* key = strtok(line, ":");
		char* value = strtok(NULL, ":");
		if (key == NULL || value == NULL) {
			//line = strtok(NULL, "\n");
			continue;
		}

		// 去除开头和结尾的空格和双引号
		char* trimmedKey = strtok(key, "\"");
			trimmedKey = strtok(NULL, "\"");
		char* trimmedValue = strtok(value, "\"");
			trimmedValue = strtok(NULL, "\"");
		
		// 根据键值对的关系构建链表节点
		if (strcmp(trimmedKey, "专业") == 0) {
			// 创建专业节点
			int majorNum = atoi(trimmedValue);
			add_Major(head_Major, majorNum);
			currentMajor = search_Major(*head_Major, majorNum);
		}
		else if (strcmp(trimmedKey, "各个年级") == 0) {
			// 创建年级头节点
			currentGrade = create_Grade();
			if(currentMajor!=NULL)
				currentMajor->grade = currentGrade;
		}
		else if (strcmp(trimmedKey, "年级") == 0) {
			// 创建年级节点
			int gradeNum = atoi(trimmedValue);
			add_Grade(currentMajor, gradeNum);
			currentGrade = search_Grade(&currentMajor, gradeNum);
		}


		else if (strcmp(trimmedKey, "学生") == 0) {
			// 创建学生头节点
			currentStudent = create_Student();
			if(currentGrade!=NULL)
				currentGrade->student = currentStudent;
		}
		else if (strcmp(trimmedKey, "学号") == 0) {
			// 创建学生节点
			int studentID = atoi(trimmedValue);
			if(currentMajor!=NULL&& currentGrade!=NULL)
				add_Student(head_Major, studentID, currentMajor->majorNum, currentGrade->gradeNum);
			currentStudent = search_Student(head_Major, studentID);
			currentScore = currentStudent->scores;
		}
		else if (strcmp(trimmedKey, "GPA") == 0) {
			// 设置学生节点的其他字段
			if (currentStudent != NULL) {
				float gpa = atoi(trimmedValue);
				currentStudent->GPA = gpa;
			}
		}
		else if (strcmp(trimmedKey, "素质加分") == 0) {
			if (currentStudent != NULL) {
				float gpa = atoi(trimmedValue);
				currentStudent->add_GPA = gpa;
			}
		}
		else if (strcmp(trimmedKey, "排名") == 0) {
			if (currentStudent != NULL) {
				int rankk = atoi(trimmedValue);
				currentStudent->rank = rankk;
			}
		}
		else if (strcmp(trimmedKey, "排名时间") == 0) {
			if (currentStudent != NULL) {
				strcpy(currentStudent->rankTime, trimmedValue);
			}
		}

		
		else if (strcmp(trimmedKey, "课程号") == 0) {
			// 创建学生成绩节点
			if (currentStudent != NULL) {
				struct SubScore* newScore = (struct SubScore*)malloc(sizeof(struct SubScore));
				strcpy(newScore->courseName, trimmedValue);
				newScore->next = NULL;

				
				currentScore->next = newScore;
				currentScore = newScore;
			}
		}
		else if (strcmp(trimmedKey, "修读学期") == 0) {
			// 设置学生成绩节点的其他字段
			if (currentScore != NULL) {
				strcpy(currentScore->semester, trimmedValue);
			}
		}
		else if (strcmp(trimmedKey, "课程成绩") == 0) {
			if (currentScore != NULL) {
				float score = atof(trimmedValue);
				currentScore->score = score;
			}
		}
		
		else if (strcmp(trimmedKey, "获得绩点") == 0) {
			if (currentScore != NULL) {
				float perGPA = atof(trimmedValue);
				currentScore->perGPA = perGPA;
				//float Score = currentScore->score;
				currentScore->perGPA = exchange_GPA(currentScore->score);
			}
		}
		
		else if (strcmp(trimmedKey, "是否免修") == 0) {
			if (currentScore != NULL) {
				int isExempted = atoi(trimmedValue);
				currentScore->isExempted = isExempted;
			}
		}
		else if (strcmp(trimmedKey, "重修重考") == 0) {
			if (currentScore != NULL) {
				int isRetake = atoi(trimmedValue);
				currentScore->isretake = isRetake;
			}
		}
		else if (strcmp(trimmedKey, "是否及格") == 0) {
			if (currentScore != NULL) {
				int isFailed = atoi(trimmedValue);
				currentScore->isFailed = isFailed;
			}
		}
		else if (strcmp(trimmedKey, "是否有效") == 0) {
			if (currentScore != NULL) {
				int isValid = atoi(trimmedValue);
				currentScore->isval = isValid;
			}
		}

		//line = strtok(NULL, "\n");
	}

	// 释放内存并关闭文件
	//free(jsonBuffer);
	//free(jsonBufferCopy);
	fclose(file);

	printf("学生成绩数据加载成功！\n");
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

	printf("链表数据已初始化\n");
}



const char* All_Aca[] = {
	"",                            // 0号位置的占位符
	"01-哲学社会学院",             // 1
	"02-文学院",                   // 2
	"03-外国语学院",               // 3
	"04-艺术学院",                 // 4
	"05-体育学院",                 // 5
	"06-经济学院",                 // 6
	"07-法学院",                   // 7
	"08-行政学院",                 // 8
	"09-商学与管理学院B",          // 9
	"10-数学学院",                 // 10
	"11-物理学院",                 // 11
	"12-化学学院",                 // 12
	"13-生命科学学院",             // 13
	"14-机械与航空航天工程学院",   // 14
	"15-汽车工程学院",             // 15
	"16-材料科学与工程学院",       // 16
	"17-交通学院",                 // 17
	"18-生物与农业工程学院",       // 18
	"19-电子科学与工程学院",       // 19
	"20-通信工程学院",             // 20
	"21-计算机科学与技术学院",     // 21
	"22-地球科学学院",             // 22
	"23-地球探测科学与技术学院",   // 23
	"24-建设工程学院",             // 24
	"25-新能源与环境学院",         // 25
	"26-金融学院",                 // 26
	"27-公共卫生学院",             // 27
	"28-药学院",                   // 28
	"29-护理学院",                 // 29
	"30-东北亚学院",               // 30
	"",                            // 31号位置的占位符
	"",                            // 32号位置的占位符
	"33-口腔医学院",               // 33
	"34-商学与管理学院A",          // 34
	"35-商学与管理学院",           // 35
	"36-公共外交学院",             // 36
	"37-新闻与传播学院",           // 37
	"38-考古学院",                 // 38
	"39-马克思主义学院",           // 39
	"40-人工智能学院",             // 40
	"",                            // 41号位置的占位符
	"",                            // 42号位置的占位符
	"",                            // 43号位置的占位符
	"",                            // 44号位置的占位符
	"",                            // 45号位置的占位符
	"",                            // 46号位置的占位符
	"",                            // 47号位置的占位符
	"",                            // 48号位置的占位符
	"",                            // 49号位置的占位符
	"50-预科教育学院",             // 50
	"",                            // 51号位置的占位符
	"",                            // 52号位置的占位符
	"",                            // 53号位置的占位符
	"54-应用技术学院",             // 54
	"55-软件学院",                 // 55
	"",                            // 56号位置的占位符
	"",                            // 57号位置的占位符
	"",                            // 58号位置的占位符
	"",                            // 59号位置的占位符
	"60-国际语言学院",             // 60
	"",                            // 61号位置的占位符
	"",                            // 62号位置的占位符
	"",                            // 63号位置的占位符
	"",                            // 64号位置的占位符
	"65-仪器科学与电气工程学院",   // 65
	"",                            // 66号位置的占位符
	"",                            // 67号位置的占位符
	"",                            // 68号位置的占位符
	"",                            // 69号位置的占位符
	"70-临床医学院",               // 70
	"71-基础医学院",               // 71
	"",                            // 72号位置的占位符
	"",                            // 73号位置的占位符
	"",                            // 74号位置的占位符
	"75-白求恩第一临床医学院",     // 75
	"76-白求恩第二临床医学院",     // 76
	"77-白求恩第三临床医学院",     // 77
	"",                            // 78号位置的占位符
	"79-白求恩医学部",             // 79
	"",                            // 80号位置的占位符
	"81-动物医学学院",             // 81
	"82-植物科学学院",             // 82
	"83-军需科技学院",             // 83
	"84-农学部公共教学中心",       // 84
	"85-动物科学学院",             // 85
	"",                            // 86号位置的占位符
	"87-食品科学与工程学院",       // 87
};

const char* ALL_Prof[88][15] = {
	{""},                                                                                   // 0
	{"哲学（匡亚明班，拔尖学生培养基地）", "哲学", "社会学", "社会工作", "劳动与社会保障"}, // 1
	{"汉语言文学", "历史学"},                                                               // 2
	{"英语", "俄语", "俄语(高校专项计划)", "西班牙语", "日语", "朝鲜语",
	 "朝鲜语(高校专项计划)"}, // 3
	{"音乐表演(艺术专业)", "绘画(艺术专业)", "设计学", "视觉传达设计", "环境设计",
	 "产品设计(艺术专业)"},                                       // 4
	{"社会体育指导与管理"},                                       // 5
	{"经济学类", "经济学", "财政学", "金融学", "国际经济与贸易"}, // 6
	{"法学"},                                                     // 7
	{"政治学与行政学", "国际政治", "行政管理"},                   // 8
	{"会计学", "财务管理", "信用管理", "经济学（数量经济）", "工商管理", "市场营销", "人力资源管理",
	 "管理科学与工程", "信息管理与信息系统", "工程管理", "物流管理", "大数据管理与应用",
	 "档案学"},                                                                            // 9
	{"数学类", "数学与应用数学", "信息与计算科学", "统计学"},                              // 10
	{"物理学类", "应用物理学", "核物理", "光电信息科学与工程", "物理学（中外合作办学） "}, // 11
	{"化学类", "应用化学", "材料化学", "高分子材料与工程", "化学工程与工艺"},              // 12
	{"生物科学类", "生物技术", "生物工程类", "生物制药", "药物制剂"},                      // 13
	{"机械工程（饶斌班，本研 贯通）", "机械工程", "工业工程", "工程力学", "智能制造工程"}, // 14
	{"车辆工程（饶斌班，本研贯通）", "车辆工程", "工业设计", "能源与动力工程"},            // 15
	{"材料类", "材料科学与工程 ", "无机非金属材料工程", "材料成型及控制工程", "材料物理",
	 "材料物理(高校专项计划)"}, // 16
	{"交通运输类", "交通运输", "交通工程", "汽车服务工程", "道路桥梁与渡河工程", "物流工程",
	 "农业机械化及其自动化（饶斌班，本研贯通）", "农业机械化及其自动化", "仿生科学与工程"}, // 17
	{"农林经济管理"},                                                                       // 18
	{"电子信息类", "电子信息工程", "电子科学与技术", "微电子 科学与工程",
	 "电子信息科学与技术"}, // 19
	{"通信工程类", "通信工程(国家专项计划)", "信息工程", "空间信息与数字技术", "自动化",
	 "机器人工程"},                                                             // 20
	{"计算机科学与技术", "物联网工程", "网络空间安全"},                         // 21
	{"地质类", "地质学", "资源勘查工程", "土地资源管理"},                       // 22
	{"勘查技术与工程勘查技术与工程", "地理信息科学", "地球物理学", "测绘工程"}, // 23
	{"土木类", "土木工程", "地质工程"},                                         // 24
	{"水利类j", "水文与水资源工程", "地下水科学与工程", "环境科学与工程", "环境科学", "环境工程",
	 "环境工程(高校专项计划)", "新能源科学与工程"}, // 25
	{""},                                           // 26
	{"放射医学", "预防医学"},                       // 27
	{"药学", "临床药学"},                           // 28
	{"康复治疗学", "护理学"},                       // 29
	{"经济学（国别与区域经济）", "应用心理学", "经济学（匡亚明班，拔尖学生培养基地 ）",
	 "政治学与行政学政治学与行政学"},                                                       // 30
	{""},                                                                                   // 31
	{""},                                                                                   // 32
	{"口腔医学", "口腔医学（5+3一体化）"},                                                  // 33
	{""},                                                                                   // 34
	{""},                                                                                   // 35
	{"外交学"},                                                                             // 36
	{"新闻传播学类", "新闻学", "广告学", "广播电 视编导"},                                  // 37
	{"考古学", "文物与博物馆学"},                                                           // 38
	{"马克思主义理论（吕振羽班，本研贯通）", "马克思主义理论", "思想政治教育"},             // 39
	{"人工智能"},                                                                           // 40
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
	{"软件工程", "数据科学与大数据技术"},                                                   // 55
	{""},                                                                                   // 56
	{""},                                                                                   // 57
	{""},                                                                                   // 58
	{""},                                                                                   // 59
	{""},                                                                                   // 60
	{""},                                                                                   // 61
	{""},                                                                                   // 62
	{""},                                                                                   // 63
	{""},                                                                                   // 64
	{"仪器类", "测控技术与仪器", "智能感知工程", "电气工程及其自动化"},                     // 65
	{""},                                                                                   // 66
	{""},                                                                                   // 67
	{""},                                                                                   // 68
	{""},                                                                                   // 69
	{""},                                                                                   // 70
	{"生物医学科学"},                                                                       // 71
	{""},                                                                                   // 72
	{""},                                                                                   // 73
	{""},                                                                                   // 74
	{"临床医学（一院）", "临床医学（5+3一体化）（一院）", "临床医学（5+3一体化，儿科学）"}, // 75
	{"临床医学（二院）", "临床医学（5+3一体化）（二院）"},                                  // 76
	{"临床医 学（三院）", "临床医学（5+3一体化）（三院）"},                                 // 77
	{""},                                                                                   // 78
	{""},                                                                                   // 79
	{""},                                                                                   // 80
	{"动物医学(农林)", "动物医学(高校专项计划)"},                                           // 81
	{"植物生产", "农学", "园艺", "植物保护", "农业 资源与环境(农林)"},                      // 82
	{""},                                                                                   // 83
	{""},                                                                                   // 84
	{"动物科学(农林)"},                                                                     // 85
	{""},                                                                                   // 86
	{"食品科学与工程", "食品质量与安全"}                                                    // 87
};