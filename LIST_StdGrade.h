#ifndef STDGRADE_H
#define STDGRADE_H

//רҵ�ڵ�ṹ��
struct Major {
    int majorNum;  // ѧԺרҵ���
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
    float GPA;  // ƽ��ѧ�ּ���
    float add_GPA;  // ������Ŀ����ӷֵ�GPA
    int rank;	// ����
    char rankTime[20];	// ����ʱ��
    struct SubScore* scores;  // �ɼ������ͷָ��
    struct Student* next;  // ��һ��ѧ���ڵ��ָ��
};
// ѧ���ɼ��ڵ�ṹ��
struct SubScore {
    char courseName[20];  // �γ���
    char semester[15];  // �޶�ѧ��
    float score;  // �γ̳ɼ�
    float perGPA;  // ��ü���
    int isExempted;  // �Ƿ�����
    int isretake;    //�����ؿ�
    int isFailed;  // �Ƿ񼰸�
    int isval;  // �Ƿ���Ч
    struct SubScore* next;  // ��һ��ѧ���ɼ��ڵ��ָ��
};
//�ļ��к��������͹���ע��

// ����רҵͷ�ڵ�
struct Major* create_Major();

// ���רҵ�ڵ����ͨ��רҵ��Ų��صĹ���
void add_Major(struct Major** head_Major, int majorNum);

// ͨ��רҵ��Ų���רҵ�ڵ㲢�������ַ
struct Major* search_Major(struct Major* head_Major, const int majorNum);

// �����꼶ͷ�ڵ㲢���ӵ�רҵ�ڵ�
struct Grade* create_Grade();

// ����꼶�ڵ����ͨ���꼶���صĹ���
void add_Grade(struct Major* Major, int gradeNum);

// ͨ���꼶�����꼶�ڵ㲢�������ַ
struct Grade* search_Grade(struct Major** head_Major, int gradeNum);

// ����ѧ���ڵ㲢���ӵ��꼶�ڵ�
struct Student* create_Student();


//��һ��ѧ�ţ����Ҹ���ѧ�����ڵ��꼶�ڵ�
struct Grade* search_GradeByStudentID(struct Major** head_Major, int studentID);

//��һ��ѧ�ţ����Ҹ���ѧ�����ڵ�רҵ�ڵ�
struct Major* search_MajorByStudentID(struct Major* head_Major, int studentID);

// ���ѧ���ڵ����ͨ�������������н���ѧ�Ų��صĹ���
void add_Student(struct Major** head_Major, int studentID, int majorNum, int gradeNum);

// ͨ��ѧ�������������в��ҵ���ѧ���ڵ�
struct Student* search_Student(struct Major** head_Major, int studentID);

// ��ѧ���ڵ���ӳɼ�������ͨ���γ������صĹ��ܣ�����ֵΪ1��ʾ��ӳɹ�������ֵΪ0��ʾ���ʧ�ܣ�����ֵΪ-1��ʾѧ�������ڣ�����ֵΪ-2��ʾ�γ����ظ�
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
int delete_Grade(struct Major** head_Major, int majorNum, int gradeNum);

// ɾ��ָ��רҵ������ֵΪ1��ʾɾ���ɹ�������ֵΪ0��ʾɾ��ʧ��
int delete_Major(struct Major** head_Major, int majorNum);

// ��ѯ����ѧ�������гɼ�,1ѧ�������ڣ�2ѧ���޳ɼ���0��ѯ�ɹ�
int query_Scores(struct Major** head_Major, int studentID);

//��ʾָ���꼶������ѧ��
void display_Grade(struct Major* head_Major, int majorNum, int gradeNum);

// ����������ļ�����Ƹ�ʽΪ��רҵ���-�꼶-ѧ��ѧ��-ѧ��ƽ��ѧ�ּ���-ѧ������-����ʱ��-�γ���-�ɼ�-�޶�ѧ��-�Ƿ�����-�Ƿ�ҿƣ�
// ÿ������֮���ÿո������ÿ��ѧ���ĳɼ�֮���ö��Ÿ�����ÿ��ѧ��֮���÷ֺŸ�����ÿ���꼶֮����ð�Ÿ�����ÿ��רҵ֮���û��и���
// ����ֵΪ1��ʾ����ɹ�������ֵΪ0��ʾ����ʧ�ܣ�����ֵΪ-1��ʾ�ļ���ʧ��
void saveTo_StdGrade(struct Major** head_Major, char* filename);

// ���ļ�����ѧ����Ϣ
void loadFrom_StdGrade(struct Major** head_Major, char* filename);

void clear_StdGrade(struct Major** head_Major);

extern const char* All_Aca[];
extern const char* ALL_Prof[88][15];
// nstitutions


#endif
