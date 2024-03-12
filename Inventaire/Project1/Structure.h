#include <stdio.h>



typedef struct Node Node;

struct Node {
	void* data;
	Node* next;
	Node* prev;
} ;
typedef Node Head;

typedef struct Item {

	char* name[256];
	int value;
} Item;