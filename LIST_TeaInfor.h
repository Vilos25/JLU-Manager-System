#ifndef LIST_TEAINFOR_H
#define LIST_TEAINFOR_H



// 辅导员信息结构体
typedef struct TeacherInformation {
    int id;                     // 工号
    char name[50];              // 姓名
    int majorCode;              // 专业编号
    int grades[2];              // 所带年级
    char gender;                // 性别
    char politicalStatus[50];   // 政治面貌
    char education[50];         // 学历
    char phoneNumber[15];       // 手机号码
    char email[50];             // 邮箱
    int t;                      // 是否初始化
} Teacher;

// 链表节点结构体
typedef struct Teacher {
    Teacher teacher;
    struct Teacher* next;
} TeaInfor;


// 函数声明
// 创建头节点
TeaInfor* createHead_TeaInfor();
// 添加辅导员信息函数
void add_Teacher(TeaInfor* head_TeaInfor, int ID);
//查询辅导员，如果找到返回地址
TeaInfor* search_TeacherByID(TeaInfor* head_TeaInfor, int ID);
//打印辅导员信息
void print_Teacher(TeaInfor* head_TeaInfor, int ID);
// 查询辅导员信息
void search_Teacher(TeaInfor* head_TeaInfor);
// 修改辅导员信息
void modify_Teacher(TeaInfor* head_TeaInfor, int id);
//删除辅导员信息
void delete_Teacher(TeaInfor* head_TeaInfor, int id);
// 打印所有辅导员信息
void print_AllTeachers(TeaInfor* head_TeaInfor);
// 保存到文件
void saveTo_TeaInfor(TeaInfor* head_TeaInfor, const char* fileName);
// 从文件读取
void loadFrom_TeaInfor(TeaInfor** head_TeaInfor, const char* fileName);

#endif // !TEAINFOR_H

