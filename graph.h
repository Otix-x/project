/**
 * @file graph.h
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief header file của graph.c
 * @date 2022-12-07
 * 
 */

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

struct Node {   // Cấu trúc Node trong danh sách kề 
    int vertex;  // Lưu trữ giá trị của đỉnh
    struct Node *next;  // Con trỏ trỏ đến phần tử tiếp theo
    struct Node *prev;  // Con trỏ trỏ đến phần tử trước đó
};

struct Graph {  // Cấu trúc đồ thị
    int numVertices;    // Số đỉnh của đồ thị
    struct Node** head;     // Mảng các con trỏ trỏ đến đỉnh đầu tiên của danh sách kề
    struct Node** rear;     // Mảng các con trỏ trỏ đến đỉnh cuối cùng của danh sách kề
};

struct Node* createNode(int vertex);    // Hàm tạo một Node mới
struct Graph* createGraph(int numVertices);     // Hàm tạo một đồ thị mới
void addEdge(struct Graph* graph,int src,int dest);     // Hàm thêm cạnh vào đồ thị
int countVertices(char *filename);    // Hàm đếm số đỉnh của đồ thị
void buildGraph(struct Graph* graph,FILE *filename);    // Hàm xây dựng đồ thị
void printGraph(struct Graph* graph, FILE* filename);   // Hàm in đồ thị
void BFS(struct Graph* graph,int startVertex, int numVertices, FILE* f);    // Hàm duyệt đồ thị theo chiều rộng
void DFS(struct Graph* graph,int startVertex, int numVertices, FILE* f);    // Hàm duyệt đồ thị theo chiều sâu
void deleteVertex(struct Graph* graph,int vertex);  // Hàm xóa một đỉnh
int checkCover(struct Graph* graph, FILE* f);   // Hàm kiểm tra đồ thị có bao phủ hay không


#endif // GRAPH_H_INCLUDED