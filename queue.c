#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief Hàm tạo hàng đợi mới
 * 1. Cấp phát bộ nhớ cho hàng đợi
 * 2. Khởi tạo front và rear của hàng đợi
 * 3. Trả về con trỏ đến hàng đợi mới
 * 
 * @return struct Queue* 
 */
struct Queue* createQueue(){
	struct Queue *temp=(struct Queue*)malloc(sizeof(struct Queue));
	temp->front=temp->rear=NULL;
	return temp;

}

/**
 * @brief Hàm enqueue() thêm một node mới vào hàng đợi với giá trị là data
 * 1. Tạo một node mới với giá trị là data
 * 2. Nếu hàng đợi rỗng thì node mới là front và rear
 * 3. Nếu hàng đợi không rỗng thì node mới là rear->next và rear = node mới
 * 
 * @param queue Hàng đợi
 * @param data Giá trị của node mới
 */
 
void enqueue(struct Queue* queue,int key){
	struct QueueNode *temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	temp -> data = key;
	temp -> next = NULL;

    if(queue -> rear == NULL){
    	queue -> front = queue -> rear = temp;
		return;
    }
    
    queue -> rear -> next = temp;
    queue -> rear = temp;
    
}

/**
 * @ brief Hàm dequeue() truy xuất phần tử đầu tiên trong hàng đợi
 * 1. Kiểm tra xem hàng đợi có rỗng hay không
 * 2. Nếu rỗng thì trả về -1
 * 3. Nếu không rỗng thì trả về phần tử đầu tiên trong hàng đợi
 * 
 * @param queue Hàng đợi
 * @return Phần tử đầu tiên trong hàng đợi
 */

 
int dequeue(struct Queue *queue){
	if(queue -> front == NULL){
		return -1;
	}	
	struct QueueNode *temp = queue -> front;
	queue -> front = queue -> front -> next;
    if(queue->front==NULL){
    	queue->rear=NULL;
    }
    int Front = temp -> data;
    free(temp);
    return Front;
	
}

/**
 * @brief Hàm queueEmpty() kiểm tra xem hàng đợi có rỗng hay không
 * 
 */
int queueEmpty(struct Queue* queue){
	return queue -> rear ==NULL;
}

/**
 * @brief Hàm printQueue() in hàng đợi
 * @param queue Hàng đợi
 */
void printQueue(struct Queue* queue){
    struct QueueNode *temp = queue -> front;
    while(temp){
        printf("%d ",temp->data);
        temp = temp -> next;
    }
}