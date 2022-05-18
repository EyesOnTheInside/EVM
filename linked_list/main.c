#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Node{
    int info;
    int pos;
    struct Node* next;
};
struct Node* front = NULL;
struct Node* rear = NULL;
//Ищем подходящюю позицию пока либо не найдём её или не выйдем за пределы списка, возвращаем соответсвующий результат
void view(int key){
    struct Node* temp = front;
    int c = 1;
    while(c && temp != NULL){
        if(temp->pos != key)
            temp = temp->next;
        else
            c = 0;
    }
    c ? printf("Position '%d' is empty\n", key) : printf("%d\n", temp->info);
}
//Как и view, но ищется значение а не позиция
void find(int value){
    struct Node* temp = front;
    int c = 1;
    while(c&&temp){
        if(temp->info!=value)
            temp = temp->next;
        else
            c = 0;
    }
    if(!c)
        printf("%d\n", temp->pos);
    else
        printf("Element '%d' is not in the list\n", value);
}
//Печатаем весь список в порядке возрастания позиций
void print(int max){
    if(front){
        int curr = 1;
        printf("List ('position', 'element'): [ ");
        for(; curr<=max; curr++){
            if(find_in_q(curr)){
                struct Node* temp = front;
                while(temp->pos!=curr)
                    temp=temp->next;
                printf("(%d, %d) ", temp->pos, temp->info);
            }
        }
        curr=0;
        if(find_in_q(curr)){
            struct Node* temp = front;
            while(temp->pos!=curr)
                temp=temp->next;
            printf(" (%d, %d) ", temp->pos, temp->info);
        }
        printf("]\n");
    }
    else {
        printf("List is empty\n");
    }
}
//Добавляем элемент в список и его позицию в вспомогательную очередь
void add(int value, int key){
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    ptr->info = value;
    ptr->pos = key;
    ptr->next = NULL;
    if(front == NULL){
        front = rear = ptr;
        add_in_q(key);
    }
    else if(!find_in_q(key)){
        rear->next = ptr;
        rear = ptr;
        add_in_q(key);
    }
    else{
        printf("This position is taken\n");
    }
}
//удаляем элемент в данной позиции и саму позицию из вспомогательной очереди
void removel(int key){
    if(front&&front->next){
        struct Node* temp1 = front;
        struct Node* temp2 = NULL;
        while((temp1->pos != key)&&temp1){
            temp2 = temp1;
            temp1 = temp1->next;
        }
        if(temp1&&temp1!=front){
            temp2->next = temp1->next;
            del_from_q(key);
        }
        else if(temp1&&temp1==front){
            front = temp1->next;
            del_from_q(key);
        }
        else
            printf("Position %d is empty\n", key);
        free(temp1);
    }
    else if(front&&front->pos==key){
        free(front);
        front = NULL;
        del_from_q(key);
    }
    else{
        printf("Position %d is empty\n", key);
    }
}

int main()
{
    int max_pos;
    int ch = 8;
    while(ch != 0){
        printf("1 = add element to the list, 2 - remove element from the list, 3 - find position of an element, 4 - see element at given position, 5 - print whole list, 0 - exit\n");
        scanf(" %d", &ch);
        int value;
        int pos = -1;
        switch(ch){
        case 1:
            printf("Enter an element and where to add it (0 - end of the list, 1 - beginning of the list), example: 1 3, 6 2, 9 0\n");
            scanf(" %d %d", &value, &pos);
            if(pos < 0){
                printf("Position of an element should be equal or greater than 0\n");
            }
            else{
                add(value, pos);
                if(pos>max_pos)
                    max_pos=pos;
            }
            break;
        case 2:
            printf("Enter a position\n");
            scanf(" %d", &pos);
            if(pos < 0){
                printf("Position of an element should be equal or greater than 0\n");
            }
            else{
                removel(pos);
            }
            break;
        case 3:
            printf("Enter an element\n");
            scanf(" %d", &value);
            find(value);
            break;
        case 4:
            printf("Enter a position\n");
            scanf(" %d", &pos);
            if(pos < 0){
                printf("Position of an element should be equal or greater than 0\n");
            }
            else{
                view(pos, 1);
            }
            break;
        case 5:
            print(max_pos);
            break;
        default:
            break;
        }
    }
    return 0;
}
