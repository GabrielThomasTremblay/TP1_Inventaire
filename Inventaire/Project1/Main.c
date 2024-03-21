#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
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

        temp = temp->next;
    }
    return temp->data;
}
int Random(int min, int max) {
    int num = (rand() % (max - min + 1)) + min;

    return num;
}

int randomObject() {

    int num = Random(0, 4);

    if (num >= 4) {
        num = 1;
    }
    else if (num <= 4 && num >= 3) {
        num = 100;
    }
    else if (num <= 3 && num >= 2) {
        num = 50;
    }
    else if (num <= 2 && num >= 1) {
        num = 200;
    }
    else{
        num = 25;
    }


    return num;
}

void affichageInventaire(Head* inventaire) {

    printf("\nCurrent Inventory: \n");
    Node* temp = inventaire->next;
    while (temp != inventaire->prev)
    {

        printf("%s\t\t", ((Item*)temp->data)->name);
        printf("%d\n", ((Item*)temp->data)->value);
        temp = temp->next;
    }
}

void insertionSort(Head* inventaire) {

    
    Node* temp = inventaire->prev;
    inventaire = inventaire->next;
    Node* holder;
    while (inventaire != temp->prev) {

        
        while ((((Item*)inventaire->data)->value) < (((Item*)inventaire->prev->data)->value)){
            holder = inventaire->prev;

            inventaire->prev = inventaire->prev->prev;
            inventaire->prev->next = inventaire->next;
            inventaire->next = holder;
            inventaire->next->prev = inventaire;
        }
        inventaire = inventaire->next;
    }
}

int main(int argc, char** argv) {
    heap = (uint8_t*)malloc(HEAP_SIZE);
    assert(heap != NULL);
    srand(time(0));
    Head possible_items = { 0 };
    Head inventory = { 0 };
    Item object = { 0 };
    int numRepetition = Random(1, 20);
    ReadFile(&possible_items, &inventory);
    push_back(&inventory, Search(&possible_items, 10));
    for (int i = 0; i <= numRepetition; i++) {
        push_back(&inventory, Search(&possible_items, randomObject()));
    }
    affichageInventaire(&inventory);
    insertionSort(&inventory);
    affichageInventaire(&inventory);
    
 


}
