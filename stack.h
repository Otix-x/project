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

struct stackNode* pTop;
void create();
void push(int data);
void pop();
int isEmptyStack();
void printStack();



#endif // STACK_H_INCLUDED