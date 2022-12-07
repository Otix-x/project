/**
 * @file Queue.c
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief Định nghĩa các hàm sử dụng trong hàng đợi (queue)
 * @date 2022-12-07
 * 
 */

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
	// Cấp phát bộ nhớ cho hàng đợi
	struct Queue *temp=(struct Queue*)malloc(sizeof(struct Queue));
	temp->front=temp->rear=NULL; // Khởi tạo front và rear
	return temp; // Trả về con trỏ đến hàng đợi mới

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
	// Tạo một node mới
	struct QueueNode *temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
	temp -> data = key;		// Gán giá trị cho node mới
	temp -> next = NULL;	// Node mới là node cuối cùng nên next = NULL
    if(queue -> rear == NULL){		// Nếu hàng đợi rỗng
    	queue -> front = queue -> rear = temp;	// Node mới là front và rear
		return; 	// Thoát khỏi hàm
    }   
    queue -> rear -> next = temp; // Node mới là rear->next
    queue -> rear = temp; 	// Node mới là rear
    
}

/**
 * @ brief Hàm dequeue() truy xuất phần tử đầu tiên trong hàng đợi
 * 1. Kiểm tra xem hàng đợi có rỗng hay không
 * 2. Nếu rỗng thì trả về 0
 * 3. Nếu không rỗng thì trả về phần tử đầu tiên trong hàng đợi
 * 
 * @param queue Hàng đợi
 * @return Phần tử đầu tiên trong hàng đợi
 */
int dequeue(struct Queue *queue){	// Truy xuất phần tử đầu tiên trong hàng đợi
	if(queue -> front == NULL){ 	// Nếu hàng đợi rỗng
		return -1; 					// Trả về -1
	}	
	struct QueueNode *temp = queue -> front; 	// Lưu lại phần tử đầu tiên
	queue -> front = queue -> front -> next;	// front = front->next
    if(queue->front==NULL){ 		// Nếu front = NULL
    	queue->rear=NULL;			// rear = NULL
    }
    int Front = temp -> data; 		// Lưu lại giá trị của phần tử đầu tiên
    free(temp); 					// Giải phóng bộ nhớ của phần tử đầu tiên
    return Front; 					// Trả về giá trị của phần tử đầu tiên
}

/**
 * @brief Hàm queueEmpty() kiểm tra xem hàng đợi có rỗng hay không
 * 
 */
int queueEmpty(struct Queue* queue){ 	// Kiểm tra xem hàng đợi có rỗng hay không
	return queue -> rear ==NULL; // Nếu rear = NULL thì hàng đợi rỗng
}

/**
 * @brief Hàm printQueue() in hàng đợi
 * @param queue Hàng đợi
 */
void printQueue(struct Queue* queue){
    struct QueueNode *temp = queue -> front; 	// Lưu lại phần tử đầu tiên
    while(temp){ 	// Duyệt hàng đợi
        printf("%d ",temp->data); 	// In giá trị của node
        temp = temp -> next; 	// Chuyển đến node tiếp theo 
    }
}