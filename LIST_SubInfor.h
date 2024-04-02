#ifndef SUBINFOR_H
#define SUBINFOR_H

struct SubInfor* head_SubInfor;

#define MAX_NAME_LENGTH 30
#define MAX_NUM_LENGTH 15
struct SubInfor {
    char SubName[MAX_NAME_LENGTH];
    char SubInforNum[MAX_NUM_LENGTH];
    float SubInforScore;
    int SubRequired;
    struct SubInfor* next;
};

// ��������

// ͨ���γ̺Ų��ҽڵ㲢�������ַ
struct SubInfor* search_SubInfor(struct SubInfor* head_SubInfor, const char* subNum);
// �����½ڵ�
struct SubInfor* create_SubInfor();
// ����ڵ㵽����
void insert_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode);
// ��ʾ�����еĿ�Ŀ��Ϣ
void display_SubInfor(struct SubInfor* head_SubInfor);

void saveTo_SubInfor(struct SubInfor* head_SubInfor, const char* filename);
void loadFrom_SubInfor(struct SubInfor** head_SubInfor, const char* filename);

// ɾ��ָ����Ŀ�ڵ�
void delete_SubInfor(struct SubInfor** head_SubInfor, const char* subNum);
// // �޸Ŀγ���Ϣ
bool checkAndReplace_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode);

#endif
