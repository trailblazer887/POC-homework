#include <stdio.h>
void reverse_string(char *string){
    if (string = NULL){
        return 0;
    }
    int length = 0;
    char *temp = string;
    while (*temp++ != '\0'){
        length += 1;
    }
    for (int i = 0; i < length / 2; i++){
        char tempch = *(string + length - 1 - i);
        *(string + length - 1 - i) = *(string + i);
        *(string + i) = tempch;
        
    }
}



int main(){
    char a[] = "hello";
    char *string = a;
    reverse_string(string);
    printf("%s\n", string);
    return 0;
}