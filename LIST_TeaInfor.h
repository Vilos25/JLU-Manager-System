#ifndef LIST_TEAINFOR_H
#define LIST_TEAINFOR_H



// ����Ա��Ϣ�ṹ��
typedef struct TeacherInformation {
    int id;                     // ����
    char name[50];              // ����
    int majorCode;              // רҵ���
    int grades[2];              // �����꼶
    char gender;                // �Ա�
    char politicalStatus[50];   // ������ò
    char education[50];         // ѧ��
    char phoneNumber[15];       // �ֻ�����
    char email[50];             // ����
    int t;                      // �Ƿ��ʼ��
} Teacher;

// ����ڵ�ṹ��
typedef struct Teacher {
    Teacher teacher;
    struct Teacher* next;
} TeaInfor;


// ��������
// ����ͷ�ڵ�
TeaInfor* createHead_TeaInfor();
// ��Ӹ���Ա��Ϣ����
void add_Teacher(TeaInfor* head_TeaInfor, int ID);
//��ѯ����Ա������ҵ����ص�ַ
TeaInfor* search_TeacherByID(TeaInfor* head_TeaInfor, int ID);
//��ӡ����Ա��Ϣ
void print_Teacher(TeaInfor* head_TeaInfor, int ID);
// ��ѯ����Ա��Ϣ
void search_Teacher(TeaInfor* head_TeaInfor);
// �޸ĸ���Ա��Ϣ
void modify_Teacher(TeaInfor* head_TeaInfor, int id);
//ɾ������Ա��Ϣ
void delete_Teacher(TeaInfor* head_TeaInfor, int id);
// ��ӡ���и���Ա��Ϣ
void print_AllTeachers(TeaInfor* head_TeaInfor);
// ���浽�ļ�
void saveTo_TeaInfor(TeaInfor* head_TeaInfor, const char* fileName);
// ���ļ���ȡ
void loadFrom_TeaInfor(TeaInfor** head_TeaInfor, const char* fileName);

#endif // !TEAINFOR_H

