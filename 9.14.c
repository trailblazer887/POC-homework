#include <stdio.h>
// 3
int my_strlen(char *dest, char* src){
    if (dest == NULL || src == NULL){
        return -1;
    }
    while (*dest != '\0' && *src != '\0'){
        *dest++ = *src++;
    }
    *dest = '\0';
    return 1;
}

// 4
int my_strcat(char *dest, char *src, int dest_len){
    if (dest == NULL || src == NULL || dest_len < 1){
        return -1;
    }
    for (; *dest != '\0'; dest++, dest_len--);
    while (dest_len > 1 && *src != '\0'){
        *dest++ = *src++;
        dest_len--;
    }
    *dest = '\0';
    return 1;
}

// 6
char*  my_strcpy_end(char *dest, char *src){
    while ((*dest++ = *src++) != '\0');
    return (dest - 1);
}

// 7
char *my_strrchr(char const *str, int ch){
    char const *temp = NULL;
    while (*str != '\0'){
        if (*str == ch){
            temp = str;
        }
        str++;
    }
    return temp;
}

// 8
char *my_strnchr(char const *str, int ch, int which){
    char *temp = str;
    while (*temp != '\0'){
        if (*temp == ch){
            which--;
            if (!which){
                return temp;
            }
        }
        temp++;
    }
    return NULL;
}

// 9
int count_chars(char const *str, char const *chars){
    int cnt = 0;
    while (*str != '\0'){
        char const *temp = chars;
        while (*temp != '\0'){
            if (*str == *temp){
                cnt++;
                break;
            }
            temp++;
        }
        str++;
    }
    return cnt;
}

// 10 双指针
int palindrome (char *string){
    if (string == NULL || *string == '\0'){
        return 1;
    }
    int flag = 1;
    char *left = string;
    char *right = string;
    for (; *right != '\0'; right++);
    while (1){
        for (; !isalpha(*left); left++);
        for (; !isalpha(*right); right--);
        if (left > right){
            break;
        }
        if (tolower(*left) != tolower(*right)){
            flag = 0;
            break;
        }
        left++;
        right--;
    }
    return flag;
}

//11
int count_the(char *string){
    int cnt = 0;
    char *word = strtok(string, " ");
    if (word == NULL){
        return cnt;
    }
    if (!strcmp(word, "the")){
        cnt++;
    }
    while ((word = strtok(NULL, " ")) != NULL){
        if (!strcmp(word, "the")){
            cnt++;
        }
    }
    return cnt;
}

// 12,13,14
int prepare_key(char *key){
    if (key == NULL || *key == '\0'){
        return 0;
    }
    int alphabet[26] = {0};
    char *key_copy = key;
    int cnt = 0;
    for (; *key_copy != '\0'; key_copy++){
        if (!isalpha(*key_copy)){
            return 0;
        }
        int low_ch = tolower(*key_copy);
        if (alphabet[low_ch - 'a'] == 0){
            alphabet[low_ch - 'a'] = 1;
            key[cnt] = (char)low_ch;
            cnt++;
        }
    }
    for (int i = 0; i < 26; i++){
        if (alphabet[i] == 0){
            key[cnt] = (char)(i + 'a');
            cnt++;
        }
    }
    key[cnt] = '\0';
    return 1;
}

void encrypt(char *data, char const *key){
    for (; *data != '\0'; data++){
        if (isalpha(*data)){
            if (islower(*data)){
                *data = key[(int)(*data) - 'a'];
            }else{
                *data = toupper(key[(int)((tolower)(*data)) - 'a']);
            }
        }
    }
}

void decrypt(char *data, char const* key){
    for (; *data != '\0'; data++){
        if (isalpha(*data)){
            int cnt = 0;
            for (; key[cnt] != '\0'; cnt++){
                if (tolower(*data) == key[cnt]){
                    if (isupper(*data)){
                        *data = toupper((char)cnt + 'a');
                    }else{
                        *data = (char)cnt + 'a';
                    }
                    break;
                }
            }
        }
    }
}

// 15
void dollars(char *dest, char const *src){
    if (*src == '\0' || src == NULL){
        strcpy(dest, "$0.00");
        return;
    }
    int len = 0;
    char const *src_copy = src;
    for (; *src_copy != '\0'; src_copy++){
        len++;
    }
    int remain = (len - 2) % 3;
    strcpy(dest, "$");
    if (len == 1){
        strcat(dest, "0.0");
        strcat(dest, src);
        return;
    }
    if (len == 2){
        strcat(dest, "0.");
        strcat(dest, src);
        return;
    }
    for (int i = 0; i < remain; i++){
        char temp[2] = {*src++, '\0'};
        strcat(dest, temp);
    }
    int cycle_cnt = (len-2-remain)/3;
    for (int i = 0; i < cycle_cnt; i++){
        strcat(dest, ",");
        for (int j = 0; j < 3; j++){
            char temp[2] = {*src++, '\0'};
            strcat(dest, temp);
        }
    }
    strcat(dest, ".");
    for (int i = 0; i < 2; i++){
        char temp[2] = {*src++, '\0'};
        strcat(dest, temp);
    }
}

// 16
int format(char *format_string, char const* digit_string){
    int behind_dot = 0, empty = 0;
    int digit_size = strlen(digit_string);
    int sum = 0; // 记录#的个数
    if (*digit_string == '\0'){
        return 0; // 错误处理
    }
    const char *fstr_still = format_string, *dstr_still = digit_string; // 保存指针原来位置
    for (; *format_string != '\0'; format_string++){
        if (*format_string == '.'){
            behind_dot = 1;
        }else if (*fstr_still == '#'){
            sum++;
        }
    } 
    if (digit_size > sum){ 
        return 0; // 错误处理
    }
    for (; *digit_string != '\0'; digit_string++); // 都移到右边,准备遍历
    format_string--;
    digit_string--;
    for (;fstr_still != format_string; format_string--){
        if (*format_string == '#'){ // #
            if (empty){
                if (behind_dot){
                    *format_string = '0';
                }else {
                    *format_string = '&';
                }
            }else {
                if ((*format_string = *digit_string) == '1'){
                    empty = 1;
                }else{
                    digit_string--;
                }
                
            }
            
        }else if (*format_string == ','){ // ,
            if (empty){
                *format_string = '&';
            }
        }else if (*format_string == '.'){ // .
            behind_dot = 0;
            if (empty){
                *(format_string - 1) = '0';
            }
        }
        
    }
    if (*format_string == '#'){ // format首位处理
        if (empty){
                *format_string = '&';
        }else {
            *format_string = *digit_string;
        }
    }
}