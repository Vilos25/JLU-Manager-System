#ifndef LIST_STDINFOR_H
#define LIST_STDINFOR_H
// ����ѧ����Ϣ�ṹ��
typedef struct StdInfor {
    int id;                  // ѧ��
    char name[50];           // ����
    int class;               // �༶
    char gender;             // �Ա�
    char politicalStatus[20];// ������ò
    char phoneNumber[15];    // �ֻ�����
    char email[50];          // ��������
    int isStudying;          // �Ƿ��ڶ�
    int t;				   // �Ƿ��ʼ��
    struct StdInfor* next;
} StdInfor;

// ��������ͷ�ڵ㣬����ͷ�ڵ��ַ
StdInfor* createStdInfor();

// ����ѧ��ѧ�ţ�����ѧ����Ϣ���������ַ
StdInfor* search_StdInfor(StdInfor* head, int studentId);

// ����ѧ��ѧ�ţ�����ѧ����Ϣ
void add_StdInfor(StdInfor* head, int studentId);

// �޸�ѧ����Ϣ
void modify_StdInfor(StdInfor* head, int studentId);

// ɾ��ѧ����Ϣ
void delete_StuInfor(StdInfor** head, int studentId);

// ��ѯѧ����Ϣ
void print_StdInfor(StdInfor* head, struct Major* head_Major, int studentId);

//��ӡ����ѧ����Ϣ
void printAll_StdInfor(StdInfor* head, struct Major* head_Major);

// ����ѧ����Ϣ���ļ�
void saveTo_StdInfor(StdInfor* head, const char* fileName);

// ���ļ�����ѧ����Ϣ
void loadFrom_StdInfor(StdInfor** head, const char* fileName);


#endif  // LIST_STDINFOR_H
