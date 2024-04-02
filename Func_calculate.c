#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "Func_calculate.h"
#include "LIST_StdGrade.h"
#include "LIST_SubInfor.h"


//������˺�ѡ�޵���ѧ�� 
float calculate_allmyscore(struct Major* head_Major,struct StdGrade* head_SubInfor,int studentID)
{
    //����ָ��ѧ�ŵ�ѧ���ڵ�
    
    struct Student* current = search_Student(&head_Major,  studentID);
    //printf("here\n");

    
    float my_score = 0;
    
    //����ҵ���ѧ���ڵ�
    if (current != NULL) {
        // ����ָ���γ����ĳɼ��ڵ�
        struct SubScore* currentScore = current->scores;
        while (currentScore != NULL) {
            if (currentScore->isval == 1) {
                currentScore = currentScore->next;
                continue;
            }
            if (currentScore->isretake != 0) {
                currentScore = currentScore->next;
                continue;
            }
            struct SubInfor* search = search_SubInfor(head_SubInfor, currentScore->courseName);
           if (search != NULL) {
               my_score += search->SubInforScore;
               search = search->next;
            }
            currentScore = currentScore->next;
        }
        //printf("������ѧ��ͳ�Ƴɹ�\n");
        return my_score;
    }
    else {
        //printf("�Ҳ�����Ӧ��ѧ��\n");
        return -1;
    }
    
}

//������˼���GPA����ѧ�� 
float calculate_myscore(struct Major* head_Major, struct StdGrade* head_SubInfor, int studentID)
{
    //����ָ��ѧ�ŵ�ѧ���ڵ�

    struct Student* current = search_Student(&head_Major, studentID);
    //printf("here\n");


    float my_score = 0;

    //����ҵ���ѧ���ڵ�
    if (current != NULL) {
        // ����ָ���γ����ĳɼ��ڵ�
        struct SubScore* currentScore = (current->scores)->next;
        while (currentScore != NULL) {
            if (currentScore->isval == 1) {
                currentScore = currentScore->next;
                continue;
            }
            if (currentScore->isretake != 0) {
                currentScore = currentScore->next;
                continue;
            }
            struct SubInfor* search = search_SubInfor(head_SubInfor, currentScore->courseName);   
            if (search != NULL) {
                if (search->SubRequired == 0) {
                    currentScore = currentScore->next;
                    continue;
                }
                my_score += search->SubInforScore;
                search = search->next;
            }
            currentScore = currentScore->next;
        }
        //printf("������ѧ��ͳ�Ƴɹ�\n");
        return my_score;
    }
    else {
        //printf("�Ҳ�����Ӧ��ѧ��\n");
        return -1;
    }

}

//���ݻ�õķ���ת������Ӧ�ļ���
float exchange_GPA(float score)
{
    float GPA;
    if (score >= 90) {
        GPA = 4.0;
    }
    else if(score >= 87) {
        GPA = 3.7;
    }
    else if (score >= 83) {
        GPA = 3.3;
    }
    else if (score >= 80) {
        GPA = 3.0;
    }
    else if (score >= 77) {
        GPA = 2.7;
    }
    else if (score >= 73) {
        GPA = 2.3;
    }
    else if (score >= 70) {
        GPA = 2.0;
    }
    else if (score >= 67) {
        GPA = 1.7;
    }
    else if (score >= 63) {
        GPA = 1.3;
    }
    else if (score >= 60) {
        GPA = 1.0;
    }
    else {
        GPA = 0;
    }
    return GPA;
}


//�������ƽ������ 
float calculate_GPA(struct Major* head_Major,int studentID,struct SubInfor* head_SubInfor)
{
    //����ָ��ѧ�ŵ�ѧ���ڵ�

    struct Student* current = search_Student(&head_Major, studentID);
    
    //printf("here\n");
    
    float sum = 0;   //ÿ��ѧ���뼨��˻�֮�� 
    float sum_score=calculate_myscore(head_Major, head_SubInfor, studentID); // ��ѧ�� 
    //printf("%f", sum_score);
    float averageGPA;
    //����ҵ���ѧ���ڵ�
    if (current != NULL) {
        struct SubScore* currentScore = current->scores->next;
        if(currentScore!=NULL){

            //struct SubInfor* search = search_SubInfor(head_SubInfor, currentScore->courseName);
            while (currentScore != NULL ) {

                struct SubInfor* search = search_SubInfor(head_SubInfor, currentScore->courseName);
                if (search == NULL) {
                    printf("�Ҳ����γ�: %s\n", currentScore->courseName);
                    currentScore = currentScore->next;
                    continue;
                }
                if (currentScore->isval == 0&& currentScore->isretake == 0)
                    sum += search->SubInforScore * exchange_GPA(currentScore->score);
                
                currentScore = currentScore->next;

            }
        }
        
        
        averageGPA = sum / sum_score;
        return averageGPA;
    }
    else {
        printf("�Ҳ�����Ӧ��ѧ��\n");
        return 0;
    }
}


//����������Ŀ�ӷֺ�ļ��� 
float finalGPA(struct Major* head_Major, int studentID, float add_GPA) //add_GPA��������Ŀ����ӷֵ�GPA 
{
    float FinalGPA = calculate_GPA(head_Major, studentID, head_SubInfor) + add_GPA;
    return FinalGPA;
}

//������꼶��ƽ������
float calculate_GradeAverageGPA(struct Major* head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	struct Student* tempStudent;
	float sum = 0;
	int count = 0;
	if (tempGrade != NULL) {
		tempStudent = (tempGrade->student)->next;
		while (tempStudent != NULL) {
			sum += tempStudent->GPA;
			count++;
			tempStudent = tempStudent->next;
		}
		return sum / count;
	}
}

//�����꼶��ѧ��������
int calculate_GradeStudentNum(struct Major* head_Major, int majorNum, int gradeNum) {
	struct Major* tempMajor = search_Major(head_Major, majorNum);
    if(tempMajor==NULL)
		return 0;
	struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
	struct Student* tempStudent;
	int count = 0;
	if (tempGrade != NULL) {
		tempStudent = (tempGrade->student)->next;
		while (tempStudent != NULL) {
			count++;
			tempStudent = tempStudent->next;
		}
		return count;
	}
}

//����ѧ���꼶���� ������return -1�����Ҳ�����ѧ��
int Grade_ranking(struct Major* head_Major, int studentID, float add_GPA,float FinalGPA)
{
    //����ָ��ѧ�ŵ�ѧ���ڵ�
    struct Grade* pop = search_GradeByStudentID(&head_Major, studentID);
    struct Student* current = search_Student(&head_Major, studentID);
    struct Student* search = pop->student;
    //printf("here\n");
    int rank = 1; //�ȼ��������ǵ�һ
    //����ҵ���ѧ���ڵ�
    if (current != NULL) {
        while (search != NULL) {
            struct Student* currentstd = search_Student(&head_Major, search->studentID);
            if (finalGPA( head_Major,currentstd->studentID, currentstd->add_GPA) > FinalGPA) {
                rank++;
            }
            search = search->next;
        }
        //printf("�����꼶��������%d,ռǰ�ٷ�֮%f", rank, 100.0 * rank / allstudents);
        return rank;
    }
    else {
        printf("�Ҳ�����Ӧ��ѧ��\n");
        return -1;
    }

}


//��������������ѧ����GPA
void calculate_AllGPA(struct Major* head_Major, struct SubInfor* head_SubInfor) {
    struct Major* tempMajor = head_Major->next;
    struct Grade* tempGrade;
    struct Student* tempStudent;
    while (tempMajor != NULL) {
        tempGrade = (tempMajor->grade)->next;
        while (tempGrade != NULL) {
            tempStudent = (tempGrade->student)->next;
            while (tempStudent != NULL) {
                tempStudent->GPA = calculate_GPA(head_Major, tempStudent->studentID, head_SubInfor);
                tempStudent = tempStudent->next;
            }
            tempGrade = tempGrade->next;
        }
        tempMajor = tempMajor->next;
    }
}


//��ȡϵͳʱ��
void getSystemTime(char* timeString) {
    time_t current_time;
    struct tm* time_info;

    // ��ȡ��ǰϵͳʱ��
    time(&current_time);
    time_info = localtime(&current_time);

    // ��ʽ��ʱ���ַ���
    strftime(timeString, 20, "%Y-%m-%d %H:%M:%S", time_info);
}


//ֻ���꼶���Ը��꼶��ѧ���ɼ�����ð������
void Sort_Grade(struct Major* head_Major, int majorNum, int gradeNum) {
    struct Major* tempMajor = search_Major(head_Major, majorNum);
    struct Grade* tempGrade = search_Grade(&tempMajor, gradeNum);
    struct Student* tempStudent;
    if (tempGrade != NULL) {
        tempStudent = (tempGrade->student)->next;
        while (tempStudent != NULL) {
            //tempStudent->GPA = calculate_GPA(head_Major, tempStudent->studentID, head_SubInfor);
            //tempStudent->rank = Grade_ranking(head_Major, tempStudent->studentID, tempStudent->add_GPA, tempStudent->GPA);
            getSystemTime(tempStudent->rankTime);
            tempStudent = tempStudent->next;
        }
        //ð������
        int flag = 1;
        struct Student* i, * j, * i0, * j0;
        while (flag)
        {
            i = (tempGrade->student)->next; 
            if (i == NULL)
                break;
            j = i->next;
            i0 = tempGrade->student; j0 = i;
            flag = 0;
            while (i != NULL)
            {
                while (j != NULL)
                {
                    if (i->GPA + i->add_GPA < j->GPA + j->add_GPA)
                    {
                        flag = 1;

                        if (i == j0)
                        {
                            j0->next = j->next;
                            j->next = i;
                            i0->next = j;
                            i = i0->next;
                            j = j0->next;
                        }
                        else
                        {
                            struct cell* tmp;
                            tmp = i->next;
                            i->next = j->next;
                            j->next = tmp;
                            i0->next = j;
                            j0->next = i;
                            i = i0->next;
                            j = j0->next;
                        }

                    }
          
                    j0 = j;
                    if (j == NULL)
                        break;
                    j = j->next;

                }
                i0 = i;
                i = i->next;
                j0 = i;
                if (i == NULL)
                    break;
                j = i->next;
            }

        }
        //��������
        int rank = 1;
        int score = 0;
        //tempGrade = search_Grade(&tempMajor, gradeNum);
        if (tempGrade != NULL) {
            tempStudent = (tempGrade->student)->next;
            while (tempStudent != NULL) {
                if (tempStudent->GPA + tempStudent->add_GPA != score) {
                    score = tempStudent->GPA + tempStudent->add_GPA;
                    tempStudent->rank = rank;
                    rank++;
                }
                tempStudent = tempStudent->next;
            }
        }

    }
    
    
    
    return;
}

