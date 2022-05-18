#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Node{
    int info;
    struct Node* left;
    struct Node* right;
    struct Node* par;
};

struct Node* root = NULL;
//Ищем элемент x в дереве и возвращаем соответствующий результат
void search(int x){
    struct Node* temp = root;
    while(temp&&!(temp->info==x)){
        if(x>temp->info){
            temp = temp->right;
        }
        else if(x<temp->info){
            temp = temp->left;
        }
    }
    if(temp&&temp->info==x){
        printf("\nElement %d is a part of the tree\n", x);
    }
    else{
        printf("\nElement %d is not a part of the tree\n", x);
    }
}
//Добавляем элемент в дерево, идя по нему пока не найдём либо свободное место, либо сам элемент
void add(int x){
    struct Node* ptr = (struct Node*)malloc(sizeof(struct Node));
    ptr->info = x;
    ptr->left = NULL;
    ptr->right = NULL;
    if(root == NULL){
        root = ptr;
        root->par = NULL;
    }
    else{
        struct Node* temp = root;
        struct Node* temp_par = NULL;
        while(temp){
            temp_par = temp;
            if(x>temp->info){
                temp = temp->right;
            }
            else if(x<temp->info){
                temp = temp->left;
            }
            else{
                temp = NULL;
            }
        }
        if(temp_par->info==x){
            printf("Element %d is already part of the tree\n", x);
            free(ptr);
        }
        else if(x>temp_par->info){
            temp_par->right=ptr;
            ptr->par=temp_par;
        }
        else{
            temp_par->left=ptr;
            ptr->par=temp_par;
        }
    }
}
//Находим элемент в дереве и заменяем его на крайне правый из левого поддерева, либо на крайне левый из правого поддерева
//не забывая соеденить вершины, которые разделяются при переносе
void del(int x){
    struct Node* temp = root;
    struct Node* temp_par = NULL;
    struct Node* temp_leaf = NULL;
    while(temp){
        temp_par = temp;
        if(x>temp->info){
            temp = temp->right;
        } else if(x<temp->info){
            temp = temp->left;
        } else{
            temp = NULL;
        }
    }
    if(temp_par->info==x){
        if(temp_par->left){
            temp=temp_par->left;
            if(temp->right){
                while(temp->right){
                    temp_leaf=temp;
                    temp=temp->right;
                }
                temp_leaf->right=temp->left;
                temp_par->info=temp->info;
                free(temp);
            }
            else{
                temp_par->info=temp->info;
                temp_par->left=temp->left;
                free(temp);
            }
        }
        else if(temp_par->right){
            temp=temp_par->right;
            if(temp->left){
                while(temp->left){
                    temp_leaf=temp;
                    temp=temp->left;
                }
                temp_leaf->left=temp->right;
                temp_par->info=temp->info;
                free(temp);
            }
            else{
                temp_par->info=temp->info;
                temp_par->right=temp->right;
                free(temp);
            }
        }
    }
    else{
        printf("There's no element %d in the tree\n", x);
    }
}
//Делаем обход в глубину печатая сначала левого сына, потом отца, потом правого сына
//Добавляем уже напечатанные вершины в вспомогательную очередь, чтобы не напечатать их дважды
//Обходим дерево пока не окажемся в корне дважды
void print_in_depth(){
    struct Node* temp = root;
    struct Node* temp2;
    int c;
    if(temp){
        c = 1;
    }
    else{
        c = 0;
        printf("\nThe tree is empty\n");
    }
    while(c){
        while(temp->left){
            temp=temp->left;
        }
        printf("%d   ", temp->info);
        add_in_q(temp->info);
        if(temp->right){
            temp=temp->right;
        }
        else if(temp!=root){
            temp=temp->par;
            temp2=temp->right;
            while((!(temp2)||look(temp2->info))&&temp->par){
                if(!(look(temp->info))){
                    printf("%d   ", temp->info);
                    add_in_q(temp->info);
                }
                temp=temp->par;
                temp2=temp->right;
            }
            if(temp==root&&!(look(temp->info))){
                printf("%d   ", temp->info);
                add_in_q(temp->info);
            }
            else if(temp==root&&look(temp->info)){
                c=0;
            }
            else if(!(look(temp->info))){
                printf("%d   ", temp->info);
                add_in_q(temp->info);
            }
            if(temp->right){
                temp=temp->right;
            }
            else{
                c=0;
            }
        }
        else{
            c=0;
        }
    }
    freeq();
}
//Делаем обход в ширину
//сначала добаляем адрес корня в вспомогательную очередь
//и пока вспомогательная очередь не пустая мы печатаем значение первой вершины в вспомогательной очереди, удаляя его оттуда
//и добавляем поочерёдно её левого и правого сына в всп. очередь если можем
void print_in_width(){
    if(!(root))
        printf("\nTree is empty\n");
    else{
        int x = root;
        add_in_q(x);
        while(check_if_empty()==0){
            struct Node* temp = take_from_q();
            printf("%d   ", temp->info);
            if(temp->left)
                add_in_q(temp->left);
            if(temp->right)
                add_in_q(temp->right);
        }
    }
}

int main()
{
    int choice=8;
    int x;
    while(choice){
        printf("What would you like to do with the tree?\n");
        printf("1 - add element to the tree\n");
        printf("2 - delete element from the tree\n");
        printf("3 - search for the element in the tree\n");
        printf("4 - print an in-order tree traversal\n");
        printf("5 - print a level order traversal\n");
        printf("0 - finish the programm\n");
        scanf(" %d", &choice);
        switch(choice){
        case 1:
            printf("Enter an element you would like to add\n");
            scanf(" %d", &x);
            add(x);
            break;
        case 2:
            printf("Enter an element you would like to delete\n");
            scanf(" %d", &x);
            del(x);
            break;
        case 3:
            printf("Enter an element you would like to search\n");
            int x;
            scanf(" %d", &x);
            search(x);
            break;
        case 4:
            print_in_depth();
            printf("\n");
            break;
        case 5:
            print_in_width();
            printf("\n");
            break;
        case 0:
            break;
        default:
            printf("Invalid option\n");
            break;
        }
    }
    return 0;
}
