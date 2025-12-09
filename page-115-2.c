#include <stdio.h>
int del_substr(char *str, char const *substr){
    if (substr != NULL && *substr == '\0'){
        return 1;
    }
    if (str == NULL || substr == NULL || *str == '\0'){
        return 0;
    }
    for (int i = 0; *(str + i) != '\0'; i++){
        for (int j = 0; ; j++){
            if (*(str + i + j) == '\0'){
                return 0;
            }
            if (*(str + i + j) != *(substr + j)){
                break;
            }
            if (*(substr + j + 1) == '\0'){
                for (int k = 1; ; k++){
                    if (*(str + i + j + k) == '\0'){
                        *(str + i + k - 1) = '\0';
                        return 1;
                    }
                    *(str + i + k - 1) = *(str + i + j + k);
                }
            }
        }
    }
    return 0;
}




int main(){
    char a[] = "CD123CDEFG";
    char b[] = "CDEFG";
    char *str = a;
    char *substr = b;
    printf("%d\n%s\n", del_substr(str, substr), str);
    return 0;
}