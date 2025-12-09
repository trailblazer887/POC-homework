#include <stdio.h>
char *find_char(char const *sourse,
char const *chars){
    if (sourse == NULL || *sourse == '\0' || chars == NULL || *chars == '\0'){
        return NULL;
    }
    for (int i = 0; *(sourse + i) != '\0'; i++){
        for (int j = 0; *(chars + j) != '\0'; j++){
            if (*(sourse + i) == *(chars + j)){
                return (sourse + i); // 此处返回的是可修改指向内容的指针
            }
        }
    }
    return NULL;
}




int main(){
    char *sourse = "ABCDEF";
    char *chars = "XRCQEF";
    char *ptr = find_char(sourse, chars);
    if (ptr != NULL){
        printf("%c\n", *ptr);
    }else{
        printf("%s\n", "fail");
    }
    return 0;
}