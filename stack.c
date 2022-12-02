#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void create(){
    pTop = NULL;
}

/**
 * @brief Hàm push() thêm một phần tử vào stack
 * 1. Tạo một node mới với giá trị là data
 * 2. Nếu stack rỗng thì node mới là top
 * 3. Nếu stack không rỗng thì node mới là top->next và top = node mới
 * 
 * @param data Giá trị của node mới
 */
void push(int data){
    struct stackNode *temp = (struct stackNode*)malloc(sizeof(struct stackNode));
    if(temp == NULL){
        printf("\nHeap Overflow");
        return;
    }
    temp->data = data;
    temp->prev = pTop;
    pTop = temp;
}

/**
 * @brief Hàm pop() truy xuất phần tử đầu tiên trong stack
 * 1. Kiểm tra xem stack có rỗng hay không
 * 2. Nếu rỗng thì trả về -1
 * 3. Nếu không rỗng thì trả về phần tử đầu tiên trong stack
 * 
 * @return Phần tử đầu tiên trong stack
 */
void pop(){
    if(pTop == NULL){
        printf("\nStack Underflow");
        exit(1);
    }
    else{
        struct stackNode *temp = pTop;
        int data = temp->data;
        pTop = pTop->prev;
        free(temp);
    }
}

/**
 * @brief Hàm isEmptyStack() kiểm tra xem stack có rỗng hay không
 * 
 */
int isEmptyStack(){
    return pTop == NULL;
}

/**
 * @brief Hàm printStack() in ra stack
 * 
 */
void printStack(){
    struct stackNode* temp;
    if(pTop == NULL){
        printf("\nStack is empty");
        return;
    }
    else{
        temp = pTop;
        while(temp != NULL){
            printf("%d ", temp->data);
            temp = temp->prev;
        }
    }
}


