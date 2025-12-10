#include <stdio.h>
int eratosthenes(int n){
    if (n % 2 == 0){
        n--;
    }
    int flag[(n - 1) / 2];
    for (int i = 0; i < (n-1)/2; i++){
        flag[i] = 1;
    }
    for (int i = 0; i < (n-1)/2; i++){
        if (flag[i] == 0){
            continue;
        }
        for (int j = i; j < (n-1)/2; j+=2*i+3){
            if (j != i){
                flag[j] = 0;
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < (n-1/2); i++){
        if (flag[i] == 1){
            cnt++;
        }
    }
    return cnt + 1;
}


int main(){
    printf("%d\n", eratosthenes(20));
    return 0;
}