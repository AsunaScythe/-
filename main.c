#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node{
    void *data;
    Node *next;
};

int get_length(Node*);

Node* find_value(Node*,void*,int);

void delete_Node(Node*,void (*)(void*));

int same(void*,void*,int);

Node* get_prev(Node*);

void print(Node*,void(*)(void*));

void print_reverse(Node*,void(*)(void*));

void insert_prev(Node**,void*);

void insert_after(Node**,void*);

void p_int(int *some){
    printf("%d",*some);
}

void d_int(int *some){
    free(some);
}

int main() {
    int len,
        i;
    Node *list = NULL;

    int *value;

    puts("Enter list length");
    scanf("%d",&len);

    for(i = 0;i < len;i++){
        printf("Enter %d element - ",i);
        value = calloc(sizeof(int),1);
        scanf("%d",value);
        insert_prev(&list,value);
    }
    puts("LIST:");
    print(list,p_int);

    puts("REVERS LIST");
    print_reverse(list,p_int);

    puts("Enter deleted value");
    scanf("%d",&i);

    delete_Node(find_value(list,&i,sizeof(int)),d_int);//если

    puts("LIST:");
    print(list,p_int);

    puts("REVERS LIST");

    print_reverse(list,p_int);

    return 0;
}
//нахождение длинны списка
int get_length(Node *some){
    int len;
    Node *curr;
    if(some != NULL)
        for(curr = some->next,len = 1;curr != some;curr = curr->next,len++);
    else
        len = 0;
    return len;
}

//поиск элемента по значению
Node* find_value(Node *some,void *value,int size){
    Node *curr;
    if(some != NULL && !same(some->data,value,size)) {
        for (curr = some->next; curr != some && !same(curr->data, value, size); curr = curr->next);
        if(curr == some)
            curr = NULL;
    }
    else if(some == NULL)
        curr = NULL;
    else curr = some;
    return curr;
}

//удаление элемента
void delete_Node(Node *some,void (*delete_data)(void*)){
    Node *prev;
    printf("%d",*(int*)some->data);
    prev = get_prev(some);
    prev->next = some->next;
    delete_data(some->data);
    free(some);
}

//сравнение на равно
int same(void *a,void *b,int size){
    for(;size > 0 && *(char*)a == *(char*)b;size--,a++,b++);
    return !size;
}

//получение предыдущего элемента
Node* get_prev(Node *some){
    Node *curr;
    if(some != NULL)
        for(curr = some;curr->next != some;curr = curr->next);
    else curr = NULL;
    return curr;
}

//вывод списка
void print(Node *some,void(*print_data)(void*)){
    Node *curr;
    if(some!=NULL){
        curr = some;
        do{
            print_data(curr->data);
            curr = curr->next;
            puts("");
        }while(curr != some);
    }
}

//вывод списка в обратном порядке
void print_reverse(Node*some,void(*print_data)(void*)){
    int len,
        i;
    void **array;

    len = get_length(some);
    array = calloc(sizeof(void*),len);

    for(i = 0;i<len;i++,some=some->next){
        array[i] = some->data;
    }

    for(;i>0;i--) {
        print_data(array[i - 1]);
        puts("");
    }

     free(array);
}

//вставка до
void insert_prev(Node **some,void *data){
    Node *new;
    new = calloc(sizeof(Node), 1);
    new->data = data;
    if(*some != NULL) {
        new->next = *some;
        get_prev(*some)->next = new;
    }
    else {
        *some = new;
        (*some)->next = new;
    }
}

//вставка после
void insert_after(Node **some,void *data){
    Node *new;
    new = calloc(sizeof(Node),1);
    new->data = data;
    if(*some!=NULL){
        new->next = (*some)->next;
        (*some)->next = new;
    }
    else {
        (*some) = new;
        (*some)->next = new;
    }
}


