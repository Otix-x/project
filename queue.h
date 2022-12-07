/**
 * @file queue.h
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief header file của queue.c
 * @date 2022-12-07
 * 
 */

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/**
 * @brief Cấu trúc của một node trong queue
 * @param data Giá trị của node
 * @param next Con trỏ trỏ đến node tiếp theo
 */
 
struct QueueNode{ 	// Cấu trúc của một node trong queue
	int data; 		// Giá trị của node
	struct QueueNode* next; 		// Con trỏ trỏ đến node tiếp theo
};

/**
 * @brief Cấu trúc của queue
 * @param front Con trỏ trỏ đến node đầu tiên trong queue
 * @param rear Con trỏ trỏ đến node cuối cùng trong queue
 */
struct Queue{ 	// Cấu trúc của queue
	struct QueueNode *front; 		// Con trỏ trỏ đến node đầu tiên trong queue
    struct QueueNode *rear;			// Con trỏ trỏ đến node cuối cùng trong queue
};

struct Queue* createQueue(); 	// Hàm tạo một queue mới
void enqueue(struct Queue* queue,int data); 	// Hàm thêm một node vào queue
int dequeue(struct Queue* queue); 	// Hàm lấy một node ra khỏi queue
int queueEmpty(struct Queue* queue);	// Hàm kiểm tra queue có rỗng hay không
void printQueue(struct Queue* queue);	// Hàm in queue


#endif // QUEUE_H_INCLUDED