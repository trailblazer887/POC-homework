#include <stdio.h>

// 1
void *my_calloc(size_t num_elements,
size_t element_size){
    size_t len = num_elements * element_size;
    if (len / num_elements == element_size){ // overflow
        return NULL;
    }
    char *temp = (char*)malloc(len);
    if (temp == NULL){ // error
        return NULL;
    }
    for (int i = 0; i < len; i++){
        *(temp + i) = 0;
    }
    return (void*)temp;
}

// 2
int* int2ls(){
    int cnt = 0;
    int value;
    int size = 100;
    int *ls = malloc((size+1) * sizeof(int));
    if (ls == NULL){
        return NULL;
    }
    while (scanf("%d", &value) == 1){
		cnt++;
        if (cnt > size){
            size += 100;
            int* temp = realloc(ls, (size+1) * sizeof(int));
            if (temp == NULL){
                free(ls);
                return NULL;
            }
            ls = temp;
        }
        ls[cnt] = value;
	}
    ls[0] = cnt;
    if (cnt < size){
        int *temp = realloc(ls, (cnt+1) * sizeof(int));
        if (temp != NULL){
            ls = temp;
        }
    }
    return ls;
}

// 3
char* string(){
    int len = 100;
    char *str = malloc(len);
    if (str == NULL){
        return NULL;
    }
    int ch, cnt = 0;
    while ((ch = fgetc(stdin)) != EOF){
        cnt++;
        if (cnt > len - 1){
            len += 100;
            char* temp = realloc(str, len);
            if (temp == NULL){
                free(str);
                return NULL;
            }
            str = temp;
        }
        str[cnt-1] = (char)ch;
    }
    str[cnt] = '\0';
    char *temp = realloc(str, cnt + 1);
    if (temp != NULL){
        str = temp;
    }
    return str;
}