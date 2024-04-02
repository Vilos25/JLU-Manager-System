#ifndef LIST_STDINFOR_H
#define LIST_STDINFOR_H
// 定义学生信息结构体
typedef struct StdInfor {
    int id;                  // 学号
    char name[50];           // 姓名
    int class;               // 班级
    char gender;             // 性别
    char politicalStatus[20];// 政治面貌
    char phoneNumber[15];    // 手机号码
    char email[50];          // 电子邮箱
    int isStudying;          // 是否在读
    int t;				   // 是否初始化
    struct StdInfor* next;
} StdInfor;

// 创建链表头节点，返回头节点地址
StdInfor* createStdInfor();

// 给定学生学号，查找学生信息并返回其地址
StdInfor* search_StdInfor(StdInfor* head, int studentId);

// 给定学生学号，增加学生信息
void add_StdInfor(StdInfor* head, int studentId);

// 修改学生信息
void modify_StdInfor(StdInfor* head, int studentId);

// 删除学生信息
void delete_StuInfor(StdInfor** head, int studentId);

// 查询学生信息
void print_StdInfor(StdInfor* head, struct Major* head_Major, int studentId);

//打印所有学生信息
void printAll_StdInfor(StdInfor* head, struct Major* head_Major);

// 保存学生信息到文件
void saveTo_StdInfor(StdInfor* head, const char* fileName);

// 从文件加载学生信息
void loadFrom_StdInfor(StdInfor** head, const char* fileName);


#endif  // LIST_STDINFOR_H
