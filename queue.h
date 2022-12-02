#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

/**
 * @brief Cấu trúc của một node trong queue
 * @param data Giá trị của node
 * @param next Con trỏ trỏ đến node tiếp theo
 */
 
struct QueueNode{
	int data;
	struct QueueNode* next;
};

/**
 * @brief Cấu trúc của queue
 * @param front Con trỏ trỏ đến node đầu tiên trong queue
 * @param rear Con trỏ trỏ đến node cuối cùng trong queue
 */
struct Queue{
	struct QueueNode *front;
    struct QueueNode *rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* queue,int data);
int dequeue(struct Queue* queue);
int queueEmpty(struct Queue* queue);
void printQueue(struct Queue* queue);





#endif // QUEUE_H_INCLUDED