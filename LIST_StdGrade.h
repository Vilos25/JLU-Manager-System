#ifndef STDGRADE_H
#define STDGRADE_H
struct Major* head_StdGrade;
//专业节点结构体
struct Major {
    char majorNum[10];  // 专业编号
    struct Major* next;  // 下一个专业节点的指针
    struct Grade* grade;//年级链表的头指针
};
//年级节点结构体
struct Grade {
    int gradeNum;  // 年级
    struct Grade* next;  // 下一个年级节点的指针
    struct Student* student;  // 学生链表的头指针
};
// 学生节点结构体
struct Student {
    int studentID;  // 学号
    int GPA;  // 平均学分绩点
    int rank;	// 排名
    char rankTime[20];	// 排名时间
    struct SubScore* scores;  // 成绩链表的头指针
    struct Student* next;  // 下一个学生节点的指针
};
// 学生成绩节点结构体
struct SubScore {
    char courseName[20];  // 课程名
    float score;  // 课程成绩
    char semester[5];  // 修读学期
    int isExempted;  // 是否免修
    int isFailed;  // 是否挂科
    struct SubScore* next;  // 下一个学生成绩节点的指针
};
//文件中函数声明和功能注释

// 创建专业头节点
struct Major* create_Major();

// 添加专业节点包含通过专业编号查重的功能
void add_Major(struct Major** head_Major, char majorNum[10]);

// 通过专业编号查找专业节点并返回其地址
struct Major* search_Major(struct Major** head_Major, const char* majorNum);

// 创建年级头节点并连接到专业节点
struct Grade* create_Grade(struct Major* major);

// 添加年级节点包含通过年级查重的功能
void add_Grade(struct Major* major, int gradeNum);

// 通过年级查找年级节点并返回其地址
struct Grade* search_Grade(struct Major* major, int gradeNum);

// 创建学生节点并连接到年级节点
struct Student* create_Student(struct Grade* grade);

// 添加学生节点包含通过在整个链表中进行学号查重的功能
void add_Student(struct Major** head_Major, int studentID, char majorNum[10], int gradeNum);

// 通过学号在整个链表中查找单个学生节点
struct Student* search_Student(struct Major** head_Major, int studentID);

// 给学生节点添加成绩，包含通过课程名查重的功能，返回值为1表示添加成功，返回值为0表示添加失败，返回值为-1表示学生不存在，返回值为-2表示课程名重复
int add_Score(struct Major** head_Major, int studentID, char courseName[20], float score, char semester[5], int isExempted, int isFailed);

// 修改指定学生的指定成绩，返回值为1表示修改成功，返回值为0表示修改失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
int update_Score(struct Major** head_Major, int studentID, char courseName[20], float newScore);

// 删除指定学生的指定成绩，返回值为1表示删除成功，返回值为0表示删除失败，返回值为-1表示学生不存在，返回值为-2表示课程名不存在
int delete_Score(struct Major** head_Major, int studentID, char courseName[20]);

// 删除指定学生的所有成绩，返回值为1表示删除成功，返回值为0表示删除失败，返回值为-1表示学生不存在
int delete_AllScore(struct Major** head_Major, int studentID);

// 删除指定学生，返回值为1表示删除成功，返回值为0表示删除失败
int delete_Student(struct Major** head_Major, int studentID);

// 删除指定年级，返回值为1表示删除成功，返回值为0表示删除失败
int delete_Grade(struct Major** head_Major, char majorNum[10], int gradeNum);

// 删除指定专业，返回值为1表示删除成功，返回值为0表示删除失败
int delete_Major(struct Major** head_Major, char majorNum[10]);

// 查询单个学生的所有成绩
void query_Scores(struct Major** head_Major, int studentID);

// 保存个链表到文件，设计格式为：专业编号-年级-学生学号-学生平均学分绩点-学生排名-排名时间-课程名-成绩-修读学期-是否免修-是否挂科，
// 每个数据之间用空格隔开，每个学生的成绩之间用逗号隔开，每个学生之间用分号隔开，每个年级之间用冒号隔开，每个专业之间用换行隔开
// 返回值为1表示保存成功，返回值为0表示保存失败，返回值为-1表示文件打开失败
int saveTo_StdGrade(struct Major** head_Major, char* filename);

// 从文件加载学生信息
int loadFrom_StdGrade(struct Major** head_Major, char* filename);

#endif
