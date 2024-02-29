#include <stdio.h>


typedef struct Node Node;

struct Node {
	void* data;
	Node* next;
	Node* prev;
} ;

typedef struct Items {

	char* name;
	int value;
} Items;