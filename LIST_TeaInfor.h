#ifndef TEAINFOR_H
#define TEAINFOR_H

struct TeaInfor* head_SubInfor;

#define MAX_NAME_LENGTH 20
#define MAX_NUM_LENGTH 15
struct TeaInfor {
    char SubName[MAX_NAME_LENGTH];
    char SubInforNum[MAX_NUM_LENGTH];
    float SubInforScore;
    int SubRequired;
    struct SubInfor* next;
};

#endif // !TEAINFOR_H

