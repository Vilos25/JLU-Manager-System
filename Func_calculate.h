#ifndef FUNC_CALCILATE_H
#define FUNC_CALCILATE_H

//������˺�ѡ�޵���ѧ�� 
float calculate_allmyscore(struct Major* head_Major, struct SubInfor* head_SubInfor, int studentID);

//�������GPA�����Ŀ����ѧ�� 
float calculate_myscore(struct Major* head_Major, struct SubInfor* head_SubInfor, int studentID);


//�����꼶��ѧ��������
int calculate_GradeStudentNum(struct Major* head_Major, int majorNum, int gradeNum);

//���ݻ�õķ���ת������Ӧ�ļ���
float exchange_GPA(float score);

//�������ƽ������ 
float calculate_GPA(struct Major* head_Major, int studentID, struct SubInfor* head_SubInfor);


//����������Ŀ�ӷֺ�ļ��� 
float finalGPA(struct Major* head_Major, int studentID, float add_GPA); //add_GPA��������Ŀ����ӷֵ�GPA 

//����ѧ��רҵ���� ������return -1�����Ҳ�����ѧ��
int Grade_ranking(struct Major* head_Major, int studentID, float add_GPA, float FinalGPA);


//��������������ѧ����GPA
void calculate_AllGPA(struct Major* head_Major, struct SubInfor* head_SubInfor);

//ֻ���꼶���Ը��꼶��ѧ���ɼ�����ð������
void Sort_Grade(struct Major* head_Major, int majorNum, int gradeNum);

//������꼶��ƽ������
float calculate_GradeAverageGPA(struct Major* head_Major, int majorNum, int gradeNum);

//��ȡϵͳʱ��
void getSystemTime(char* timeString);

#endif // !FUNC_CALCILATE_H

