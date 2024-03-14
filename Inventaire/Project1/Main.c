#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Structure.h"


#define HEAP_SIZE 2048 * 2048 * 4
static uint8_t* heap = NULL;
static size_t heap_top = 0;
void* allocate(size_t size) {
    size_t old_top = heap_top;
    heap_top += size;
    assert(heap_top <= HEAP_SIZE);
    return &heap[old_top];
}

void push_back(Head* head, void* newData);

void ReadFile(Head* itemsList, Head* inventory) {


	FILE* file;
	
	file = fopen("data.csv", "r");
    if (file == NULL) {

        printf("Data file not found\n");
        return 1;
    }
    char buffer[256];
    char* data;
    
    while (fgets(buffer, 256, file)) {
       
        Item* item = allocate(sizeof(Item));
        memset(item, 0, sizeof(Item));
        data = strtok(buffer, ",");
        data = strtok(NULL, ",");

        strcpy(item->name, data);
        printf("Name: %s\t", item->name);
        
        data = strtok(NULL, ",");
        data = strtok(NULL, ",");
        
        item->value = atoi(data);
        printf(" Value: %d\n", item->value);

        push_back(itemsList, item);
    }

    fclose(file);

    return;
}

void push_back(Head* head, void* newData) {

    Node* n = (Node*)allocate(sizeof(Node));
    n->data = newData;
    n->prev = NULL;
    n->next = NULL;
    
    if (head->next == NULL && head->prev == NULL) {

        head->prev = n;
        head->next = n;
    }
    else {

        head->prev->next = n;
        n->prev = head->prev;
        head->prev = n;

    }

    return;

}

void* Search(Head* head, int value) {

    Node* temp = head->next;
    while( ((Item*)temp->data)->value != value)
    {
        if (temp == head->prev) {

            temp = NULL;
            break;
        }

        printf("\n%s\n", ((Item*)temp->data)->name);
        printf("\n%d\n", ((Item*)temp->data)->value);
        temp = temp->next;
    }
    return temp;
}

int main(int argc, char** argv) {
    heap = (uint8_t*)malloc(HEAP_SIZE);
    assert(heap != NULL);
    Head possible_items = { 0 };
    Head inventory = { 0 };
    Item object = { 0 };
    ReadFile(&possible_items, &inventory);
    push_back(&inventory, Search(&possible_items, 10));

    printf("\n%s\n", ((Item*)&inventory.data)->name);
    printf("\n%d\n", ((Item*)&inventory.data)->value);
 


}
