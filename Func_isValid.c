#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <conio.h> // getch()
#include "Func_isValid.h"


// 验证课程编号格式是否正确
//HWND currentWindow;


int Input_Keyboard_Char() {
    return _getch();
}

//函数 8.5 输入一行内容作为口令，并且掩盖输入的字符串
void Pass_Input_Line(char* Userinput) {
    Userinput[0] = 0;
    int buffer_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch) || isalpha(ch)) {
            if (buffer_cnt < 20) { // 这个地方最好定义一个常量去描述 20
                Userinput[buffer_cnt++] = ch;
                printf("*");
            }
        }
        else if (ch == 13 || ch == 10) {
            if (buffer_cnt != 0) {
                Userinput[buffer_cnt] = 0;
                putchar('\n');
                break;
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                Userinput[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
}

int Input_YN() {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (ch == 'Y' || ch == 'N' || ch == 'y' || ch == 'n') {
            buffer[0] = ch;
            buffer[1] = 0;
            if (buffer_cnt != 0) {
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                buffer_cnt++;
            }
            putchar(ch);
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt > 0) {
                putchar('\n');
                break;
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return isupper(buffer[0]) ? buffer[0] : buffer[0] - 'a' + 'A';
}

int Input_MF() {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (ch == 'M' || ch == 'F' || ch == 'm' || ch == 'f') {
            buffer[0] = ch;
            buffer[1] = 0;
            if (buffer_cnt != 0) {
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                buffer_cnt++;
            }
            putchar(ch);
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt > 0) {
                putchar('\n');
                break;
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return isupper(buffer[0]) ? buffer[0] : buffer[0] - 'a' + 'A';
}


//函数3.5//输入一个仅包含数字的字符串，传入数字的长度
int Input_Raw_Integer(int Num) {
    char buffer[20] = { 0 }; // buffer[Num + 1]
    int buffer_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch)) {
            if (buffer_cnt < Num) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if ((ch == 10 || ch == 13) && buffer_cnt == Num) {
            putchar('\n');
            break;
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return atoi(buffer);
}

//函数3.5//输入电话号
void Input_phoneNumber(char* ans) {
    char buffer[20] = { 0 }; // buffer[Num + 1]
    int buffer_cnt = 0;
    int Num = 11;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch)) {
            if (buffer_cnt < Num) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if ((ch == 10 || ch == 13) && buffer_cnt == Num) {
            putchar('\n');
            break;
        }
        else {
            putchar('\a'); // alarm
        }
    }
    strcpy(ans, buffer);
    return;
}

void Input_charNumber(char* ans, int cnt) {
    char buffer[20] = { 0 }; // buffer[Num + 1]
    int buffer_cnt = 0;
    int Num = cnt;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch)) {
            if (buffer_cnt < Num) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if ((ch == 10 || ch == 13) && buffer_cnt == Num) {
            putchar('\n');
            break;
        }
        else {
            putchar('\a'); // alarm
        }
    }
    strcpy(ans, buffer);
    return;
}

int Input_intNumber(int cnt) {
    char buffer[20] = { 0 }; // buffer[Num + 1]
    int buffer_cnt = 0;
    int Num = cnt;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch)) {
            if (buffer_cnt < Num) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if ((ch == 10 || ch == 13) && buffer_cnt == Num) {
            putchar('\n');
            break;
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return atoi(buffer);
}

int Input_intNumberover(int cnt) {
    char buffer[20] = { 0 }; // buffer[Num + 1]
    int buffer_cnt = 0;
    int Num = cnt;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch)) {
            if (buffer_cnt < Num) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if (ch == 10 || ch == 13) {
            putchar('\n');
            break;
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return atoi(buffer);
}

//输入1到Num的单个数字，并纠正用户进行单项选择时的“输入错误”，防止用户因输入其它字符导致程序退出：
int Input_1toNum(int Num) {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch) && '1' <= ch && ch <= ('0' + min(Num, 9))) {
            buffer[0] = ch;
            buffer[1] = 0;
            if (buffer_cnt != 0) {
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                buffer_cnt++;
            }
            putchar(ch);
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                buffer[--buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt > 0) {
                putchar('\n');
                break;
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    return atoi(buffer);
}
/**************************************************************************************************************************/
//输入浮点数
float Input_Float(int Integer, int Decimal) {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    int dot_cnt = 0;
    int digit_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch) || ch == '.') {
            if (buffer_cnt < Integer + Decimal + 1) {
                if (isdigit(ch)) {
                    if (digit_cnt < Integer)
                    {
                        buffer[buffer_cnt++] = ch;
                        putchar(ch);
                        digit_cnt += 1;
                    }
                    else if (digit_cnt <= Integer && dot_cnt == 1) {
                        buffer[buffer_cnt++] = ch;
                        putchar(ch);
                    }
                    else
                    {
                        putchar('\a'); // alarm
                    }
                }

                else { // ch == '.'
                    if (dot_cnt == 0) {
                        buffer[buffer_cnt++] = ch;
                        putchar(ch);
                        dot_cnt += 1;
                    }
                    else {
                        putchar('\a'); // alarm
                    }
                }
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                --buffer_cnt;
                if (buffer[buffer_cnt] == '.') {
                    dot_cnt -= 1;
                }
                else if (dot_cnt == 0) {
                    digit_cnt -= 1;
                }
                buffer[buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
            else
            {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt > 0) {
                putchar('\n');
                break;
            }
            else
            {
                putchar('\a'); // alarm
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    if (dot_cnt == 1 && buffer_cnt == 1) {
        return 0;
    }
    else {
        float ans;
        sscanf(buffer, "%f", &ans);
        return ans;
    }
}

//输入邮箱
void Input_Email(char* ans) {
    int len = 25;
    char buffer[30] = { 0 };
    int buffer_cnt = 0;
    int at_cnt = 0; // 记录@的个数
    int dot_cnt = 0; // 记录小数点的个数
    while (1) {
        int ch = Input_Keyboard_Char();
        if (isdigit(ch) || ch == '.' || ch == '@' || isalpha(ch)) {
            if (buffer_cnt < len) {
                if (isdigit(ch) || isalpha(ch)) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                }
                else if (ch == '.' && buffer_cnt != 0) {
                    if (at_cnt == 1 && buffer[buffer_cnt - 1] != '@') { // ch == '.'
                        if (dot_cnt == 0) {
                            buffer[buffer_cnt++] = ch;
                            putchar(ch);
                            dot_cnt += 1;
                        }
                        else {
                            putchar('\a'); // alarm
                        }
                    }
                    else {
                        putchar('\a'); // alarm
                    }
                }
                else if (ch == '@' && buffer_cnt != 0) { // ch == '@'
                    if (at_cnt == 0) {
                        buffer[buffer_cnt++] = ch;
                        putchar(ch);
                        at_cnt += 1;
                    }
                    else {
                        putchar('\a'); // alarm
                    }
                }
                else {
                    putchar('\a'); // alarm
                }
            }
            else {
                putchar('\a'); // alarm
            }
        }

        else if (ch == 8) {
            if (buffer_cnt > 0) {
                --buffer_cnt;
                if (buffer[buffer_cnt] == '.') {
                    dot_cnt -= 1;
                }
                if (buffer[buffer_cnt] == '@') {
                    at_cnt -= 1;
                }
                buffer[buffer_cnt] = 0;
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt > 0 && dot_cnt == 1 && at_cnt == 1) {
                putchar('\n');
                break;
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    strcpy(ans, buffer);
}
/**************************************************************************************************************************/
//输入包含头两个字母外加8个数字的字符串
void Input_SubNum(char* ans) {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    int digit_cnt = 0;
    int alpha_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (buffer_cnt < 10 && (isalpha(ch) || isdigit(ch))) {
            if (isalpha(ch)) {
                if (alpha_cnt < 2) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                    alpha_cnt++;
                }
                else {
                    putchar('\a'); // alarm
                }
            }
            else if (alpha_cnt == 2 && isdigit(ch)) {
                if (digit_cnt < 8) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                    digit_cnt++;
                }
                else {
                    putchar('\a'); // alarm
                }
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                --buffer_cnt;
                if (isdigit(buffer[buffer_cnt])) {
                    digit_cnt--;
                }
                else {
                    alpha_cnt--;
                }
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt == 10) {
                putchar('\n');
                break;
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else {
            putchar('\a'); // alarm
        }

    }
    strcpy(ans, buffer);
    return;
}

//输入修读学期
void Input_SemesterNum(char* ans) {
    char buffer[12] = { 0 };
    int buffer_cnt = 0;
    int Y1_cnt = 0;
    int Y2_cnt = 0;
    int s_cnt = 0;
    int g_cnt = 0;
    while (1) {
        int ch = Input_Keyboard_Char();
        if (buffer_cnt < 11 && (isdigit(ch) || ch == '-')) {
            if (isdigit(ch)) {
                if (Y1_cnt < 4) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                    Y1_cnt++;
                }
                else if (Y1_cnt == 4 && Y2_cnt < 4 && g_cnt == 1) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                    Y2_cnt++;
                }
                else if (Y1_cnt == 4 && Y2_cnt == 4 && g_cnt == 2) {
                    buffer[buffer_cnt++] = ch;
                    putchar(ch);
                    s_cnt++;
                }
                else {
                    putchar('\a'); // alarm
                }
            }
            else if (ch == '-' && g_cnt < 1 && Y1_cnt == 4) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
                g_cnt++;
            }
            else if (ch == '-' && g_cnt == 1 && Y2_cnt == 4) {
                buffer[buffer_cnt++] = ch;
                putchar(ch);
                g_cnt++;
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 8) {
            if (buffer_cnt > 0) {
                --buffer_cnt;
                if (isdigit(buffer[buffer_cnt])) {

                    if (Y1_cnt == 4 && Y2_cnt == 4 && s_cnt == 1) {
                        s_cnt--;
                    }
                    else if (Y1_cnt == 4 && Y2_cnt <= 4 && Y2_cnt > 0) {
                        Y2_cnt--;
                    }
                    else if (Y1_cnt <= 4) {
                        Y1_cnt--;
                    }

                }
                else if (buffer[buffer_cnt] == '-') {
                    g_cnt--;
                }
                printf("%c%c%c", 8, 32, 8);
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else if (ch == 10 || ch == 13) {
            if (buffer_cnt == 11) {
                putchar('\n');
                break;
            }
            else {
                putchar('\a'); // alarm
            }
        }
        else {
            putchar('\a'); // alarm
        }
    }
    if (Y1_cnt == 4 && Y2_cnt == 4 && s_cnt == 1 && g_cnt == 2) {
        strcpy(ans, buffer);
        return;
    }
}




//谷村的代码

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

//检查学生学号
bool isValid_studentID(const char* studentID) {
    //检查长度是否为8
    if (strlen(studentID) != 8) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(studentID);
    for (int i = 0; i < length; i++) {
        if (!isdigit(studentID[i])) {
            return false;
        }
    }
    return true;
}

//检查辅导员工号格式是否正确
bool isValid_id(const char* id) {
    //检查长度是否为6
    if (strlen(id) != 6) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(id);
    for (int i = 0; i < length; i++) {
        if (!isdigit(id[i])) {
            return false;
        }
    }
    return true;
}

//检查专业编号格式是否正确
bool isValid_majorNum(const char* majorNum) {
    //检查长度是否为2位
    if (strlen(majorNum) != 2) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(majorNum);
    for (int i = 0; i < length; i++) {
        if (!isdigit(majorNum[i])) {
            return false;
        }
    }
    return true;
}



//检查专业名称格式是否正确
bool isValid_majorName(const char* majorName) {
    //检查长度是否大于20
    if (strlen(majorName) > 20) {
        return false;
    }
    else {
        return true;
    }
}

//检查姓名格式是否正确
bool isValid_name(const char* name) {
    //检查长度是否大于20
    if (strlen(name) > 20) {
        return false;
    }
    //不能有数字
    int length = strlen(name);
    for (int i = 0; i < length; i++) {
        if (!isalpha(name[i])) {
            return false;
        }
    }
    return true;
}

//检查年级格式
bool isValid_grade(const char* grade) {
    //检查长度是否为2位
    if (strlen(grade) != 2) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(grade);
    for (int i = 0; i < length; i++) {
        if (!isdigit(grade[i])) {
            return false;
        }
    }
    return true;
}

//检查班级格式
bool isValid_Class(const char* Class) {
    //检查长度是否为2位
    if (strlen(Class) != 2) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(Class);
    for (int i = 0; i < length; i++) {
        if (!isdigit(Class[i])) {
            return false;
        }
    }
    return true;
}

//检查电话号格式是否正确
bool isValid_phoneNumber(const char* phoneNumber) {
    //检查长度是否为11
    if (strlen(phoneNumber) != 11) {
        return false;
    }
    //检查是否都为数字
    int length = strlen(phoneNumber);
    for (int i = 0; i < length; i++) {
        if (!isdigit(phoneNumber[i])) {
            return false;
        }
    }
    return true;
}

//检查课程名称格式
bool isValid_SubName(const char* SubName) {
    //检查长度是否大于20
    if (strlen(SubName) > 20) {
        return false;
    }
    else {
        return true;
    }
}


//检查政治面貌格式
bool isValid_politicalStatus(const char* politicalStatus) {
    int len = strlen(politicalStatus);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(politicalStatus[i])) {
            return false;
        }
    }
    int x = atoi(politicalStatus);
    if (x != 0 && x != 1 && x != 2) {
        return false;
    }

    return true;
}

//检查性别格式
bool isValid_gender(const char* gender) {
    int len = strlen(gender);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(gender[i])) {
            return false;
        }
    }
    int x = atoi(gender);
    if (x != 0 && x != 1) {
        return false;
    }

    return true;
}

//检查在读格式
bool isValid_Candidate(const char* Candidate) {
    int len = strlen(Candidate);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(Candidate[i])) {
            return false;
        }
    }
    int x = atoi(Candidate);
    if (x != 0 && x != 1) {
        return false;
    }

    return true;
}

//检查学历格式
bool isValid_education(const char* education) {
    //检查长度是否大于20
    if (strlen(education) > 20) {
        return false;
    }
    //不能有数字
    int length = strlen(education);
    for (int i = 0; i < length; i++) {
        if (!isalpha(education[i])) {
            return false;
        }
    }
    return true;
}

//检查账号类型格式
bool isValid_Accounttype(const char* Accounttype) {
    int len = strlen(Accounttype);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(Accounttype[i])) {
            return false;
        }
    }
    int x = atoi(Accounttype);
    if (x != 0 && x != 1 && x != 2) {
        return false;
    }

    return true;
}

//检查密码格式
bool isValid_Password(const char* Password) {
    //检查长度是否大于20
    if (strlen(Password) > 20) {
        return false;
    }
    else {
        return true;
    }
}


//检查是否免修格式
bool isValid_isExempted(const char* isExempted) {
    int len = strlen(isExempted);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(isExempted[i])) {
            return false;
        }
    }
    int x = atoi(isExempted);
    if (x != 0 && x != 1) {
        return false;
    }

    return true;
}

//检查是否挂科格式
bool isValid_isFailed(const char* isFailed) {
    int len = strlen(isFailed);

    if (len != 1) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (!isdigit(isFailed[i])) {
            return false;
        }
    }
    int x = atoi(isFailed);
    if (x != 0 && x != 1) {
        return false;
    }

    return true;
}

//检查成绩格式
bool isValid_Score(const char* Score) {
    if (Score == NULL || strlen(Score) == 0) {
        return false;
    }

    // 成绩字符串应只包含数字，可能包含一个小数点  
    bool hasDecimal = false;

    for (size_t i = 0; i < strlen(Score); ++i) {
        if (isdigit(Score[i])) {
            // 数字是有效的  
        }
        else if (Score[i] == '.') {
            if (hasDecimal || i == 0 || i == strlen(Score) - 1) {
                return false; // 小数点位置不正确  
            }
            hasDecimal = true;
        }
        else {
            return false; // 包含非数字非小数点字符  
        }
    }

    // 转换字符串为浮点数并检查范围  
    float fScore = atof(Score);
    if (fScore < 0 || fScore > 100) {
        return false;
    }

    // 如果没有小数点，则必须确保是整数且范围正确  
    if (!hasDecimal) {
        if (fScore != (int)fScore) {
            return false; // 不是整数  
        }
    }
    else {
        // 如果有小数点，确保精确到小数点后一位  
        int decimalPlaces = strlen(strrchr(Score, '.')) - 1;  // 计算小数点后的位数
        if (decimalPlaces > 1) {
            return false; // 超过一位小数
        }
    }

    return true;
}

//检查邮箱格式
bool isValid_Email(const char* email) {
    if (email == NULL) {
        return false;
    }

    const char* atSymbol = strchr(email, '@');
    if (atSymbol == NULL) {
        // 没有找到 '@' 符号  
        return false;
    }

    // 检查本地部分  
    size_t localPartLen = atSymbol - email;
    if (localPartLen == 0 || localPartLen > 64) {
        // 本地部分不能为空或超过64个字符  
        return false;
    }
    bool previousWasDot = false;
    for (size_t i = 0; i < localPartLen; ++i) {
        char c = email[i];
        if (c == '.') {
            if (previousWasDot) {
                // 连续的点号  
                return false;
            }
            previousWasDot = true;
        }
        else if (!isalnum(c) && c != '_' && c != '-') {
            // 不是字母、数字、下划线或连字符  
            return false;
        }
        else {
            previousWasDot = false;
        }
        if (i == 0 && (c == '-' || c == '.')) {
            // 本地部分不能以连字符或点号开头  
            return false;
        }
        if (i == localPartLen - 1 && (c == '-' || c == '.')) {
            // 本地部分不能以连字符或点号结尾  
            return false;
        }
    }

    // 检查域名部分  
    size_t domainPartLen = strlen(atSymbol + 1);
    if (domainPartLen == 0 || domainPartLen > 253) {
        // 域名部分不能为空或超过253个字符  
        return false;
    }
    bool previousWasHyphen = false;
    bool isTopLevelDomain = true; // 用来标记是否正在检查顶级域名  
    for (size_t i = 0; i < domainPartLen; ++i) {
        char c = atSymbol[i + 1];
        if (c == '-') {
            if (previousWasHyphen || i == 0 || (i == domainPartLen - 1 && isTopLevelDomain)) {
                // 连续的连字符，或者以连字符开头或结尾（顶级域名除外）  
                return false;
            }
            previousWasHyphen = true;
        }
        else if (!isalnum(c) && c != '.') {
            // 不是字母、数字或点号  
            return false;
        }
        else {
            previousWasHyphen = false;
        }
        if (c == '.') {
            isTopLevelDomain = true;
        }
        else if (isTopLevelDomain) {
            isTopLevelDomain = false;
        }
    }

    return true;
}