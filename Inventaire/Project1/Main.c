#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"




void main(Node* ItemsList, Node* Inventory, Items* Items) {


	FILE* file;
    ItemsList = NULL;
	
	file = fopen("data.csv", "r");
    if (file == NULL) {

        printf("Data file not found\n");
        return 1;
    }

    while (fgets(Items->name, sizeof(Items->name), file)) {
       
        Node* n = (Node*)malloc(sizeof(Node));
        n->data = Items;
        n->next = NULL;
        if (ItemsList->next != NULL) {

            n->next = ItemsList->next;
        }

        ItemsList->next = n;
    }
    fclose(file);
}