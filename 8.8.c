#include <stdio.h>
#include <stdarg.h>

// 6
int array_offset(int arrayinfo[], ...){
    int dim = *arrayinfo;
    int offset = 0;
    if (dim < 1 || dim > 10){
        return 1;
    }
    // ...类似检查

    // 初始化总差
    int total_dif = 1;
    for (int i = 1; i <= dim; i++){
        total_dif *= arrayinfo[2*i] - arrayinfo[2*i-1] + 1;
    }

    va_list list;
    va_start(list, arrayinfo);

    for (int i = 1; i <= dim; i++){
        int goal = va_arg(list, int);
        total_dif /= arrayinfo[2 * i] - arrayinfo[2 * i - 1] + 1;
        offset += (goal - arrayinfo[2*i-1]) * total_dif;
    }

    va_end(list);
    return offset;
}

// 7
// 思路同'6'

// 8 "八皇后问题" --> "递归"+"回溯"
int solution_count = 0;
// 检查(row, col)位置是否与已放置的皇后冲突
int is_safe(int row, int col, int queens[]) {
    for (int i = 0; i < row; i++) {
        // 同列 或 同对角线（行差=列差）
        if (queens[i] == col || (row - i) == abs(col - queens[i])) {
            return 0; // 冲突
        }
    }
    return 1; // 安全
}

// 递归放置皇后
void eight_queens(int row, int queens[]) {
    if (row == 8) { // 找到解
        solution_count++;
        printf("解%d: ", solution_count);
        for (int i = 0; i < 8; i++) {
            printf("[%d,%d] ", i, queens[i]);
        }
        printf("\n");
        return;
    }

    // 遍历当前行所有列
    for (int col = 0; col < 8; col++) {
        if (is_safe(row, col, queens)) {
            queens[row] = col; // 放置皇后
            eight_queens(row + 1, queens); // 递归下一行
            // 回溯：无需显式删除，queens[row]会被下一次循环覆盖
        }
    }
}