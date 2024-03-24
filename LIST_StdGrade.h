#ifndef STDGRADE_H
#define STDGRADE_H

//רҵ�ڵ�ṹ��
struct Major {
    char majorNum[10];  // רҵ���
    struct Major* next;  // ��һ��רҵ�ڵ��ָ��
    struct Grade* grade;//�꼶������ͷָ��
};
//�꼶�ڵ�ṹ��
struct Grade {
    int gradeNum;  // �꼶
    struct Grade* next;  // ��һ���꼶�ڵ��ָ��
    struct Student* student;  // ѧ��������ͷָ��
};
// ѧ���ڵ�ṹ��
struct Student {
    int studentID;  // ѧ��
    int GPA;  // ƽ��ѧ�ּ���
    int rank;	// ����
    char rankTime[20];	// ����ʱ��
    struct SubScore* scores;  // �ɼ�������ͷָ��
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
//�ļ��к��������͹���ע��

// ����רҵͷ�ڵ�
struct Major* create_Major();

// ����רҵ�ڵ����ͨ��רҵ��Ų��صĹ���
void add_Major(struct Major** head_Major, char majorNum[10]);

// ͨ��רҵ��Ų���רҵ�ڵ㲢�������ַ
struct Major* search_Major(struct Major** head_Major, const char* majorNum);

// �����꼶ͷ�ڵ㲢���ӵ�רҵ�ڵ�
struct Grade* create_Grade();

// �����꼶�ڵ����ͨ���꼶���صĹ���
void add_Grade(struct Major* Major, int gradeNum);

// ͨ���꼶�����꼶�ڵ㲢�������ַ
struct Grade* search_Grade(struct Major** head_Major, int gradeNum);

// ����ѧ���ڵ㲢���ӵ��꼶�ڵ�
struct Student* create_Student();

// ����ѧ���ڵ����ͨ�������������н���ѧ�Ų��صĹ���
void add_Student(struct Major** head_Major, int studentID, char majorNum[10], int gradeNum);

// ͨ��ѧ�������������в��ҵ���ѧ���ڵ�
struct Student* search_Student(struct Major** head_Major, int studentID);

// ��ѧ���ڵ����ӳɼ�������ͨ���γ������صĹ��ܣ�����ֵΪ1��ʾ���ӳɹ�������ֵΪ0��ʾ����ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ����ظ�
int add_Score(struct Major** head_Major, int studentID, char courseName[20], float score, char semester[5], int isExempted, int isFailed);

// �޸�ָ��ѧ����ָ���ɼ�������ֵΪ1��ʾ�޸ĳɹ�������ֵΪ0��ʾ�޸�ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ���������
int update_Score(struct Major** head_Major, int studentID, char courseName[20], float newScore);

// ɾ��ָ��ѧ����ָ���ɼ�������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ���������
int delete_Score(struct Major** head_Major, int studentID, char courseName[20]);

// ɾ��ָ��ѧ�������гɼ�������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ�ܣ�����ֵΪ-1��ʾѧ��������
int delete_AllScore(struct Major** head_Major, int studentID);

// ɾ��ָ��ѧ��������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Student(struct Major** head_Major, int studentID);

// ɾ��ָ���꼶������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Grade(struct Major** head_Major, char majorNum[10], int gradeNum);

// ɾ��ָ��רҵ������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Major(struct Major** head_Major, char majorNum[10]);

// ��ѯ����ѧ�������гɼ�
void query_Scores(struct Major** head_Major, int studentID);

// ������������ļ�����Ƹ�ʽΪ��רҵ���-�꼶-ѧ��ѧ��-ѧ��ƽ��ѧ�ּ���-ѧ������-����ʱ��-�γ���-�ɼ�-�޶�ѧ��-�Ƿ�����-�Ƿ�ҿƣ�
// ÿ������֮���ÿո������ÿ��ѧ���ĳɼ�֮���ö��Ÿ�����ÿ��ѧ��֮���÷ֺŸ�����ÿ���꼶֮����ð�Ÿ�����ÿ��רҵ֮���û��и���
// ����ֵΪ1��ʾ����ɹ�������ֵΪ0��ʾ����ʧ�ܣ�����ֵΪ-1��ʾ�ļ���ʧ��
void saveTo_StdGrade(struct Major** head_Major, char* filename);

// ���ļ�����ѧ����Ϣ
void loadFrom_StdGrade(struct Major** head_Major, char* filename);

void clear_StdGrade(struct Major** head_Major);
#endif