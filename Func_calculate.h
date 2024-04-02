#ifndef FUNC_CALCILATE_H
#define FUNC_CALCILATE_H

//计算个人含选修的总学分 
float calculate_allmyscore(struct Major* head_Major, struct StdGrade* head_SubInfor, int studentID);

//计算个人GPA算入科目的总学分 
float calculate_myscore(struct Major* head_Major, struct StdGrade* head_SubInfor, int studentID);


//计算年级内学生的人数
int calculate_GradeStudentNum(struct Major* head_Major, int majorNum, int gradeNum);

//根据获得的分数转换成相应的绩点
float exchange_GPA(float score);

//计算个人平均绩点 
float calculate_GPA(struct Major* head_Major, int studentID, struct SubInfor* head_SubInfor);


//计算素质项目加分后的绩点 
float finalGPA(struct Major* head_Major, int studentID, float add_GPA); //add_GPA是素质项目额外加分的GPA 

//计算学生专业排名 如果结果return -1代表找不到该学生
int Grade_ranking(struct Major* head_Major, int studentID, float add_GPA, float FinalGPA);


//计算链表中所有学生的GPA
void calculate_AllGPA(struct Major* head_Major, struct SubInfor* head_SubInfor);

//只给年级，对该年级的学生成绩进行冒泡排序
void Sort_Grade(struct Major* head_Major, int majorNum, int gradeNum);

//计算该年级的平均绩点
float calculate_GradeAverageGPA(struct Major* head_Major, int majorNum, int gradeNum);

//获取系统时间
void getSystemTime(char* timeString);

#endif // !FUNC_CALCILATE_H

