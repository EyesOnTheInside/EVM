#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

struct q{
    int info;
    struct q* next;
};
struct q* fron = NULL;
struct q* rear = NULL;

void add_in_q(int x){
    struct q* ptr = (struct q*)malloc(sizeof(struct q));
    ptr->info = x;
    ptr->next = NULL;
    if(fron == NULL){
        fron = rear = ptr;
    } else {
        rear->next = ptr;
        rear = ptr;
    }
}

int take_from_q(){
    int x = fron->info;
    struct q* temp = fron;
    fron = fron->next;
    if(fron==NULL){
        rear = NULL;
    }
    free(temp);
    return x;
}

int look(int x){
    struct q* ptr = fron;
    while(ptr){
        if(ptr->info==x)
            return 1;
        ptr=ptr->next;
    }
    return 0;
}

void freeq(){
    struct q* temp = fron;
    struct q* ptr;
    while(temp){
        ptr=temp->next;
        free(temp);
        temp=ptr;
    }
    fron = NULL;
    rear = NULL;
}

int check_if_empty(){
    if(fron)
        return 0;
    return 1;
}

#endif // QUEUE_H_INCLUDED
