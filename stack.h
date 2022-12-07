/**
 * @file stack.h
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief header file của stack.c
 * @date 2022-12-07
 * 
 */

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/**
 * @brief Cấu trúc dữ liệu ngăn xếp
 *
 * @param data: lưu trữ dữ liệu
 * @param prev: con trỏ trỏ đến phần tử trước đó
 */
struct stackNode{
    int data;
    struct stackNode* prev;
};

struct stackNode* pTop;     // Con trỏ trỏ đến phần tử đầu tiên của stack
void create();      // Hàm tạo một stack mới
void push(int data);        // Hàm thêm một phần tử vào stack
void pop();         // Hàm lấy một phần tử ra khỏi stack
int stackEmpty();   // Hàm kiểm tra stack có rỗng hay không
void printStack();  // Hàm in stack



#endif // STACK_H_INCLUDED