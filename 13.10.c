#include <stdio.h>
// 4
int compare(void *a, void *b){
	return *(int*)b - *(int*)a;
}
void swap (char *a, char *b, int len){
	for (int i = 0; i < len; i++){
		char temp = *(b+i);
		*(b+i) = *(a+i);
		*(a+i) = temp;
	}
}
/*
void swap (char *a, char *b, int len){
	char *temp = malloc(len);
	memcpy(temp, b, len);
	memcpy(b, a, len);
	memcpy(a, temp, len);
}
*/

void sort(int (*cmp)(void *, void *), void *ls, int cnt, int element_len){
	// transform "void" into "char" to solve.
	for (int i = cnt - 1; i > 0; i--){
		for (int j = 0; j < i; j++){
			char *element_j0 = (char *)ls + j * element_len;
			char *element_j1 = (char *)ls + (j+1) * element_len;
			if (cmp(element_j0, element_j1) < 0){
				swap(element_j0, element_j1, element_len);
			}
		}
	}
}

// 5
void do_something(int ch, char *value){
	/*
	printf("%s\n", "go in the 'do_arg' function");
	printf("ch is %c\n", (char)ch);
	printf("value is %s\n", value); // has the risk of 'NULL'
	*/
}

void illegal(int ch){
	/*
	printf("%s\n", "go in the 'illegal_arg' function");
	printf("ch is %c\n", (char)ch);
	*/
}

char** do_args(int argc, char **argv, char *control,
		void (*do_arg)(int ch, char *value),
		void (*illegal_arg)(int ch)){
	int i, j;
	for (i = 1; i < argc && *argv[i] == '-';){ //in all command arg
		int i_upgrade = 0; 
		for (j = 1; argv[i][j] != '\0';){ //in every single command arg
			int j_upgrade = 0;
			int ch = (int)argv[i][j];
			int in_control = 0;
			for (int k = 0; control[k] != '\0'; k++){ // search in 'control'
				if (control[k] == ch){
					in_control = 1; // mean 'in control'
					if (control[k+1] != '+'){ // in 'control' has no '+'
						do_arg(ch, NULL);
						j++; // should go to next circle in single command
						j_upgrade = 1;
					}else{ // in 'control' has '+'
						if (argv[i][j+1] != '\0'){ // in single command has remain
							do_arg(ch, argv[i] + j + 1);
							i++; // should go to next circle in all command 
							i_upgrade = 1;
						}else if (i != argc - 1){ // ... has no remain && in all command has remain
							do_arg(ch, argv[i+1]);
							i += 2; // should go to next '2' circle in all command
							i_upgrade = 1;
						}else { // in both has no remain
							illegal_arg(ch); // end of dealing with '-'
							i++;
							j++; // has no special meaning, just end the cycle
							i_upgrade = 1;
							j_upgrade = 1;
						}
					}
					break;
				}
			}
			if (in_control == 0){ // not in 'control'
				illegal_arg(ch);
				j++; // should go to next circle in single command
				j_upgrade = 1;
			}
			if (i_upgrade){
				break;
			}
			if (j_upgrade){
				continue;
			}
			
		}
		if (i_upgrade){
			continue;
		}else{
			i++; // deal with a special jump-out situation: argv[i][j] == '\0'
		}
	}
	return (argv + i); //the 'premise' of right operation: the end of argv is 'NULL'
}
