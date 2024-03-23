#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Func_isValid.h"
// 验证课程编号格式是否正确
bool isValid_SubNum(const char* subNum) {
    int len = strlen(subNum);

    if (len != 10) {
        return false;
    }

    for (int i = 0; i < 2; i++) {
        if (!isalpha(subNum[i])) {
            return false;
        }
    }

    for (int i = 2; i < len; i++) {
        if (!isdigit(subNum[i])) {
            return false;
        }
    }

    return true;
}

bool isValid_SemesterNum(const char* semester) {
    // 检查字符串长度是否为4
    if (strlen(semester) != 4) {
        return false;
    }
    // 检查年份和学期的范围
    int year = (semester[0] - '0') * 10 + (semester[1] - '0');
    int term = (semester[2] - '0') * 10 + (semester[3] - '0');

    if (year >= 0 && year <= 99 && term >= 1 && term <= 2) {
        return true;
    }
    else {
        return false;
    }
}