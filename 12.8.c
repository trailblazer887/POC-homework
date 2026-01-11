#include <stdio.h>
typedef struct node{
    struct node *link;
    int value;
} Node;

// 2
Node* find(Node **rootp, int val){
    for (; *rootp != NULL && (*rootp) -> value != val; rootp = &((*rootp) -> link));
    return *rootp;
}

// 4
Node *sll_reverse(Node *first){
	if (first == NULL){
		return NULL;
	}else if (first -> link == NULL){
		return first;
	}
	Node *pointed = first;
	Node *adjust = first -> link;
	Node *next_pos = adjust -> link;
	first -> link = NULL;
	while (next_pos != NULL){
		adjust -> link = pointed;
		pointed = adjust;
		adjust = next_pos;
		next_pos = next_pos -> link;
	}
	adjust -> link = pointed;
	return adjust;
}

// 5
int sll_remove(Node **rootp, Node *node){
	if (rootp == NULL || *rootp == NULL || node == NULL){
		return 0;
	}
	for (; *rootp != NULL; rootp = &((*rootp) -> link)){
		if (*rootp == node){
			*rootp = node -> link;
			node -> link = NULL;
			return 1;
		}
	}
	return 0;
}

// 6
int dll_remove(Dnode *rootp, Dnode *node){
	if (rootp == NULL || node == NULL || rootp -> fwd == NULL){
		return 0;
	}
	Dnode *past = rootp;
	Dnode *flow = rootp -> fwd;
	for (; flow != NULL; past = flow, flow = flow -> fwd){
		if (flow == node){
			past -> fwd = node -> fwd;
			if (node -> fwd == NULL){
				rootp -> bwd = node -> bwd;
			}else{
				node -> fwd -> bwd = node -> bwd;
			}
			node -> fwd = NULL;
			node -> bwd = NULL;
			return 1;
		}
	}
	return 0;
}

// 7
typedef struct sub_strlink{
	char value[20];
	struct sub_strlink * link;
} Sub_strlink;
typedef struct strlink{
	char letter;
	struct strlink * next_series;
	Sub_strlink * first_element;
} Strlink;
int insert_new_word(Strlink **listp, char *val){
	//intialize
	Sub_strlink **rootp = NULL;
	// find series
	for (; *listp != NULL && (*listp) -> letter != *val; listp = &((*listp) -> next_series));
	if (*listp == NULL){
		return 0;
	}else{
		rootp = &((*listp) -> first_element);
	}
	// find through the link
	for (; *rootp != NULL && strcmp((*rootp) -> value, val) < 0; rootp = &((*rootp) -> link));
	if (*rootp == NULL || strcmp((*rootp) -> value, val) > 0){
		Sub_strlink *p = malloc(sizeof(Sub_strlink));
		strcpy(p -> value, val);
		p -> link = *rootp;
		*rootp = p;
		return 1;
	}
	if (strcmp((*rootp) -> value, val) == 0){
		return 0;
	}
	// do nothing
	return 0;
}
