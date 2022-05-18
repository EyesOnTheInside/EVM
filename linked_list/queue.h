#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
struct q{
    int info;
    struct q* next;
};
struct q* fron = NULL;
struct q* rear_q = NULL;

void add_in_q(int x){
    struct q* ptr = (struct q*)malloc(sizeof(struct q));
    ptr->info = x;
    ptr->next = NULL;
    if(fron){
        rear_q->next = ptr;
        rear_q = ptr;
    }
    else{
        fron = ptr;
        rear_q = ptr;
    }
}

int find_in_q(int x){
    struct q* temp = fron;
    while(temp&&temp->info!=x)
        temp=temp->next;
    if(temp)
        return 1;
    else
        return 0;
}

void del_from_q(int x){
    if(find_in_q(x)){
        struct q* temp = fron;
        struct q* temp_prev = temp;
        while(temp->info!=x){
            temp_prev=temp;
            temp=temp->next;
        }
        temp_prev->next=temp->next;
        if(temp==rear_q){
            rear_q=temp_prev;
        }
        free(temp);
    }
}

#endif // QUEUE_H_INCLUDED
