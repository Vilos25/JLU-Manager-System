#ifndef SUBINFOR_H
#define SUBINFOR_H

struct SubInfor* head_SubInfor;

#define MAX_NAME_LENGTH 20
#define MAX_NUM_LENGTH 15
struct SubInfor {
    char SubName[MAX_NAME_LENGTH];
    char SubInforNum[MAX_NUM_LENGTH];
    float SubInforScore;
    int SubRequired;
    struct SubInfor* next;
};

// 函数声明

// 通过课程号查找节点并返回其地址
struct SubInfor* search_SubInfor(struct SubInfor* head_SubInfor, const char* subNum);
// 创建新节点
struct SubInfor* create_SubInfor();
// 插入节点到链表
void insert_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode);
// 显示链表中的科目信息
void display_SubInfor(struct SubInfor* head_SubInfor);

void saveTo_SubInfor(struct SubInfor* head_SubInfor, const char* filename);
void loadFrom_SubInfor(struct SubInfor** head_SubInfor, const char* filename);

// 删除指定科目节点
void delete_SubInfor(struct SubInfor** head_SubInfor, const char* subNum);
// // 修改课程信息
bool checkAndReplace_SubInfor(struct SubInfor** head_SubInfor, struct SubInfor* newNode);

#endif
