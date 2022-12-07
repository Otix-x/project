/**
 * @file stack.c
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief File chứa các hàm của stack
 * @date 2022-12-07
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


void create(){
    pTop = NULL;    // Khởi tạo stack rỗng
}

/**
 * @brief Hàm push() thêm một phần tử vào stack
 * 1. Tạo một node mới với giá trị là data
 * 2. Nếu stack rỗng thì node mới là top
 * 3. Nếu stack không rỗng thì node mới là top->next và top = node mới
 * 
 * @param data Giá trị của node mới
 */
void push(int data){    // Thêm một phần tử vào stack
    struct stackNode *temp = (struct stackNode*)malloc(sizeof(struct stackNode)); // 
    if(!temp){          // Nếu không còn bộ nhớ
        printf("\nHeap Overflow"); 
        exit(1);
    }
    temp -> data = data;    // Gán giá trị cho node mới
    temp -> prev = pTop;    // Node mới trỏ đến top
    pTop = temp;            // Cập nhật lại top
}

/**
 * @brief Hàm pop() truy xuất phần tử đầu tiên trong stack
 * 1. Kiểm tra xem stack có rỗng hay không
 * 2. Nếu rỗng thì trả về -1
 * 3. Nếu không rỗng thì trả về phần tử đầu tiên trong stack
 * 
 * @return Phần tử đầu tiên trong stack
 */
void pop(){         // Lấy một phần tử ra khỏi stack
    struct stackNode *temp;

    if(pTop == NULL){   // Nếu stack rỗng
        printf("\nStack Underflow");    // In ra thông báo
        exit(1);        
    }
    else{               // Nếu stack không rỗng
        temp = pTop;    // Gán giá trị temp với giá trị top 
        pTop = pTop->prev;  // Cập nhật lại top là giá trị kề trước đó 
        temp->prev = NULL;  // Cập nhật lại giá trị kề trước đó của temp là NULL
        free(temp);        // Giải phóng bộ nhớ của temp
    }
}

/**
 * @brief Hàm stackEmpty() kiểm tra xem stack có rỗng hay không
 * 
 */
int stackEmpty(){       // Kiểm tra stack có rỗng hay không
    return pTop == NULL;    // Nếu pTop = NULL thì stack rỗng 
}

/**
 * @brief Hàm printStack() in ra stack
 * 
 */
void printStack(){      // In ra stack 
    struct stackNode* temp;  // Khai báo biến temp   
    if(pTop == NULL){      // Nếu stack rỗng
        printf("\nStack is empty");     // In ra thông báo
        return;                    // Thoát khỏi hàm
    }
    else{   // Nếu stack không rỗng
        temp = pTop;       // Gán giá trị temp với giá trị top
        while(temp != NULL){    // Lặp đến khi temp = NULL
            printf("%d ", temp -> data);    // In ra giá trị của temp
            temp = temp -> prev; // Cập nhật lại temp là giá trị kề trước đó
        }
    }
}


