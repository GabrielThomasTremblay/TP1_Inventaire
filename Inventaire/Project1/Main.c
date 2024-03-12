#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"

void ReadFile(Head* itemsList, Head* inventory) {


	FILE* file;
	
	file = fopen("data.csv", "r");
    if (file == NULL) {

        printf("Data file not found\n");
        return 1;
    }
    Item* item = malloc(sizeof(item));
    char buffer[256];
    char* data;
    
    while (fgets(buffer, sizeof(buffer)/ sizeof(buffer[0]), file)) {
       
        data = strtok(buffer, ",");
        data = strtok(NULL, ",");

        strcpy(item->name, data);
        printf("Name: %s\t", data);
        
        data = strtok(NULL, ",");
        data = strtok(NULL, ",");
        
        item->value = atoi(data);
        printf(" Value: %d\n", item->value);

        insertion(itemsList, item);
    }
    fclose(file);

    return;
}

insertion(Head* currNode, void* newData) {

    Node* n = (Node*)malloc(sizeof(n));
    n->data = newData;
    n->prev = NULL;
    n->next = NULL;
    if (currNode->next != NULL) {

        n->next = currNode->next;
        currNode->next->prev = n;
    }
    currNode->next = n;
    n->prev = currNode;

}

int main(int argc, char** argv) {
    Head possible_items = { 0 };
    Head inventory = { 0 };
    ReadFile(&possible_items, &inventory);


}
