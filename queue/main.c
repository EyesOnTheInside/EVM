#include <stdio.h>
#include <stdlib.h>

struct Node{
    int info;
    struct Node* next;
};
struct Node* front = NULL;
struct Node* rear = NULL;
//Добавляем элемент в конец очереди
void add(int value){
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    ptr->info = value;
    ptr->next = NULL;
    if(front == NULL){
        front = rear = ptr;
    } else {
        rear->next = ptr;
        rear = ptr;
    }
    printf("\n");
}
//Удаляем элемент из начала
void removeq(){
    if(front == NULL){
        printf("\nQueue is empty\n\n");
    }
    else {
        struct Node* temp = front;
        front = front->next;
        printf("\nElement '%d' is removed\n\n", temp->info);
        free(temp);
    }
}
//Печатаем очередь начиная с front и заканчивая rear
void print(){
    if(front == NULL){
        printf("\nQueue is empty\n\n");
    }
    else {
        printf("\n");
        struct Node* temp;
        temp = front;
        while(temp->next){
            printf("%d<--", temp->info);
            temp = temp->next;
        }
        printf("%d\n\n", temp->info);
    }
}

int main()
{
    int value;
    int ch;
    while(ch != 0){
        printf("1 - add element to the end of the queue, 2 - remove element from the front, 3 - print queue, 4 - see element in the front, 0 - exit\n\n");
        scanf(" %d", &ch);
        switch(ch){
        case 1:
            printf("\nEnter an element to add\n\n");
            scanf(" %d", &value);
            add(value);
            break;
        case 2:
            removeq();
            break;
        case 3:
            print();
            break;
        case 4:
            if(front == NULL){
                printf("\nQueue is empty\n\n");
            } else {
                printf("\nElement in the front is '%d'\n\n", front->info);
            }
            break;
        default:
            break;
        }
    }
    return 0;
}
