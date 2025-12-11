// 1
#include <stdio.h>
int hermite(int n, int x){
    if (n <= 0){
        return 1;
    }else if (n == 1){
        return 2*x;
    }else{
        return 2*x*hermite(n-1, x) - 2*(n-1)*hermite(n-2, x);
    }
}

// 2
#include <stdio.h>
int gcd(int m, int n){
    if (m <= 0 || n <= 0){
        return 0;
    }
    if (m % n == 0){
        return n;
    }else{
        gcd(n, m % n);
    }
}

// 3
#include <stdio.h>
int ascii_to_integer(char *string){
    int sum = 0;
    while (*string != '\0'){
        if (*string < '0' || *string > '9'){
            return 0;
        }
        sum = sum * 10 + *string++ - '0';
    }
    return sum;
}

// 4
#include <stdio.h>
#include <stdarg.h>
int max_list(int first, ...){
    va_list list;
    if (first < 0){
        return -1;
    }
    va_start(list, first);
    int max_num = first, temp = 0;
    while ((temp = va_arg(list, int)) >= 0){
        if (temp > max_num){
            max_num = temp;
        }
    }
    va_end(list);
    return max_num;
}

// 6 (我的版本)
#include <stdio.h>
#include <string.h>
const char *ones[] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
                      "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN",
                      "EIGHTEEN", "NINETEEN"};
const char *tens[] = {"", "", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
int del = 0;

void normal_print(unsigned int n, char *buffer){
    int hud = n / 100, ten = n % 100;   
    if (hud){
        strcat(buffer, ones[hud]);
        strcat(buffer, " HUNDRED ");
    }
    if (ten){
        if (ten > 19){
            strcat(buffer, tens[ten / 10]);
            strcat(buffer, " ");
            strcat(buffer, ones[ten % 10]);
        }else{
            strcat(buffer, ones[ten]);
        }
        if (del != 0){
            strcat(buffer, " ");
        }
    }
}

void written_amount(unsigned int amount, char *buffer){
    if (amount == 0){
        strcat(buffer, "ZERO");
        return;
    }
    if (amount / 1000 != 0){
        del++;
        written_amount(amount / 1000, buffer);
    }
    

    normal_print(amount % 1000, buffer);


    if (amount % 1000 != 0){
        if (del == 3){
            strcat(buffer, "BILLION ");
            del--;
        }else if (del == 2){
            strcat(buffer, "MILLION ");
            del--;
        }else if (del == 1){
            strcat(buffer, "THOUSAND ");
            del--;
        }
    }else if (del != 0){
        del--;
    }
}

// 6 (AI版本)
#include <stdio.h>
#include <string.h>

// 基础数字拼写（0-19）
const char *ones[] = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
                      "TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN",
                      "EIGHTEEN", "NINETEEN"};
// 整十数拼写（0,10,20...90，前两位空）
const char *tens[] = {"", "", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};
// 大数单位（十亿、百万、千，按递归层级对应）
const char *large_units[] = {"BILLION", "MILLION", "THOUSAND"};

/**
 * 转换0-999为英文（核心子模块，无冗余空格）
 * @param n 0-999的数字
 * @param buffer 结果缓冲区
 * @return 是否成功转换（n>0时返回1，n=0返回0）
 */
int convert_hundreds(unsigned int n, char *buffer) {
    if (n == 0) return 0; // 0不转换（顶层单独处理）

    int len = strlen(buffer);
    int hundred = n / 100;
    int remainder = n % 100;

    // 处理百位
    if (hundred > 0) {
        if (len > 0) strcat(buffer, " "); // 非首个内容加间隔空格
        strcat(buffer, ones[hundred]);
        strcat(buffer, " HUNDRED");
    }

    // 处理十位+个位
    if (remainder > 0) {
        if (len > 0 || hundred > 0) strcat(buffer, " "); // 已有内容则加空格
        if (remainder < 20) {
            strcat(buffer, ones[remainder]); // 0-19直接拼
        } else {
            int ten = remainder / 10;
            int one = remainder % 10;
            strcat(buffer, tens[ten]); // 20/30...90
            if (one > 0) { // 个位非0才加
                strcat(buffer, " ");
                strcat(buffer, ones[one]);
            }
        }
    }
    return 1;
}

/**
 * 递归转换大数（核心逻辑，用层级替代全局变量）
 * @param amount 待转换数字
 * @param level 递归层级（0=个位段，1=千位段，2=百万段，3=十亿段）
 * @param buffer 结果缓冲区
 */
void convert_large(unsigned int amount, int level, char *buffer) {
    if (amount == 0) return;

    // 拆分当前段（每3位一段）
    unsigned int chunk = amount % 1000;
    convert_large(amount / 1000, level + 1, buffer);

    // 转换当前段并拼接大数单位
    if (convert_hundreds(chunk, buffer) && level > 0 && level <= 3) {
        strcat(buffer, " ");
        strcat(buffer, large_units[3 - level]); // 层级对应单位（1→THOUSAND，2→MILLION，3→BILLION）
    }
}

/**
 * 对外统一接口：数字转英文金额
 * @param amount 非负整数
 * @param buffer 结果缓冲区（建议长度≥500）
 */
void written_amount(unsigned int amount, char *buffer) {
    // 初始化缓冲区
    buffer[0] = '\0';

    // 特殊处理0
    if (amount == 0) {
        strcat(buffer, "ZERO");
        return;
    }

    // 递归转换大数
    convert_large(amount, 0, buffer);
}