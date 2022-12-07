/**
 * @file graph.c 
 * @author Nguyễn Xuân Phước - 20205232 (phuoc.nx205232@sis.hust.edu.vn)
 * @brief Định nghĩa các hàm thao tác với đồ thị
 * @date 2022-12-07
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

/**
 * @brief Hàm bỏ qua các dòng dữ liệu không cần thiết
 * 
 * @param f 
 * @return int 
 */
int ignoreLine(FILE *f){
    int c;
    while(c = fgetc(f), c != '\n' && c != EOF); // Bỏ qua các ký tự đến khi gặp ký tự xuống dòng hoặc ký tự EOF
    return c; // Trả về ký tự xuống dòng hoặc ký tự EOF
}

/**
 * @brief Hàm bỏ qua các dòng comment
 * 
 * @param f 
 */
void ignoreComments(FILE *f){ // Bỏ qua các dòng comment
    int c;
    while(c = fgetc(f), c == '#'){ // Nếu gặp ký tự # thì bỏ qua dòng đó
        ignoreLine(f);
    }
    ungetc(c,f); // Trả lại ký tự đọc được vào file
}

/**
 * @brief Hàm createNode() tạo một node mới với giá trị là vertex
 * 1. Cấp phát bộ nhớ cho node mới
 * 2. Gán giá trị cho node mới
 * 3. Trả về node mới
 * 
 * @param vertex Giá trị của node mới
 * @return struct Node* 
 */
struct Node* creatNode(int vertex){ // Tạo một node mới với giá trị là vertex
    struct Node* newNode = malloc(sizeof(struct Node)); // Cấp phát bộ nhớ cho node mới
    newNode->vertex = vertex; // Gán giá trị cho node mới
    newNode->next = NULL; // Khởi tạo node mới không có node kế tiếp
    newNode->prev = NULL; // Khởi tạo node mới không có node trước đó
    return newNode;
}

/**
 * @brief Hàm createGraph() tạo một đồ thị mới với số đỉnh là numVertices
 * 1. Cấp phát bộ nhớ cho đồ thị mới
 * 2. Khởi tạo số đỉnh cho đồ thị mới
 * 3. Khởi tạo danh sách kề cho đồ thị mới
 * 4. Trả về đồ thị mới
 * 
 * @param numVertices Số đỉnh của đồ thị mới
 * @return struct Graph* 
 */
struct Graph* createGraph(int numVertices){ // Tạo một đồ thị mới với số đỉnh là numVertices
    struct Graph* graph = malloc(sizeof(struct Graph)); // Cấp phát bộ nhớ cho đồ thị mới
    graph->numVertices = numVertices; // Khởi tạo số đỉnh cho đồ thị mới
    graph->head = malloc(numVertices*sizeof(struct Node*)); // Cấp phát bộ nhớ cho node đầu tiên của mỗi đỉnh
    graph->rear = malloc(numVertices*sizeof(struct Node*)); // Cấp phát bộ nhớ cho node cuối cùng của mỗi đỉnh
    for(int i=0;i<numVertices;++i){ 
        graph->head[i] = NULL; // Khởi tạo giá trị cho node đầu tiên của mỗi đỉnh
        graph->rear[i] = NULL; // Khởi tạo giá trị cho node cuối cùng của mỗi đỉnh
    }
    return graph;
}

/**
 * @brief Hàm addEdge() thêm cạnh vào đồ thị graph từ đỉnh src đến đỉnh dest
 * 1. Tạo một node mới với giá trị là dest
 * 2. Nếu đỉnh src chưa có cạnh nào đi ra thì node mới sẽ là cạnh đầu tiên của đỉnh src
 * 3. Nếu đỉnh src đã có cạnh đi ra thì node mới sẽ là cạnh cuối cùng của đỉnh src
 * 4. Nếu đỉnh dest chưa có cạnh nào đi vào thì node mới sẽ là cạnh đầu tiên của đỉnh dest
 * 5. Nếu đỉnh dest đã có cạnh đi vào thì node mới sẽ là cạnh cuối cùng của đỉnh dest
 * 
 * @param graph Đồ thị
 * @param src Đỉnh bắt đầu
 * @param dest Đỉnh kết thúc
 */
 
void addEdge(struct Graph* graph,int src,int dest){ // Thêm cạnh vào đồ thị graph từ đỉnh src đến đỉnh dest
    struct Node* newNode = creatNode(dest); // Tạo một node mới với giá trị là dest
    if(graph->head[src]==NULL){ // Nếu đỉnh src chưa có cạnh nào đi ra thì node mới sẽ là cạnh đầu tiên của đỉnh src
        graph->head[src] = newNode; // Cập nhật node đầu tiên của đỉnh src
        graph->rear[src] = newNode;
    }
    else{                       // Nếu đỉnh src đã có cạnh đi ra thì node mới sẽ là cạnh cuối cùng của đỉnh src
        newNode->prev = graph->rear[src]; // Cập nhật node cuối cùng của đỉnh src
        graph->rear[src]->next = newNode;
        graph->rear[src] = newNode;
    }
}

/**
 * @brief Hàm countVertices() đếm số đỉnh của đồ thị từ file f
 * 1. Mở file f
 * 2. Đọc số đỉnh đầu tiên của đồ thị
 * 3. Đóng file f
 * 4. Trả về số đỉnh của đồ thị
 * 
 * @param filename Tên file chứa đồ thị
 * @return int 
 */
int countVertices(char filename[]){ // Đếm số đỉnh của đồ thị từ file filename
    FILE *f = fopen(filename,"r");
    ignoreComments(f);
    int numVertices;                
    fscanf(f,"%d",&numVertices);  // Đọc số đỉnh đầu tiên của đồ thị
    int max = numVertices;
    while(fscanf(f,"%d",&numVertices)==1){ // Đọc các đỉnh tiếp theo
        max = numVertices > max ? numVertices : max; // Tìm đỉnh có giá trị lớn nhất
    } 
    fclose(f);
    return max+1;   // Trả về số đỉnh của đồ thị + 1 (vì đỉnh bắt đầu từ 0)
}

/**
 * @brief Hàm buildGraph() xây dựng đồ thị vô hướng từ file input
 * 1. Duyệt file input để lấy giá trị của các cạnh của đồ thị
 * 2. Thêm cạnh vào đồ thị
 * 
 * @param graph Đồ thị
 * @param f File chứa đồ thị
 */
void buildGraph(struct Graph* graph, FILE* f){  // Xây dựng đồ thị vô hướng từ file f
    ignoreComments(f);
    int src, dest;
    while(fscanf(f,"%d",&src) == 1, fscanf(f,"%d",&dest) == 1){ // Duyệt file f để lấy giá trị của các cạnh của đồ thị
        addEdge(graph,src,dest);    // Thêm cạnh vào đồ thị
    }
    fclose(f);
}

/**
 * @brief Hàm in đồ thị ra file f
 * 
 * @param graph Đồ thị
 * @param filename Tên file chứa đồ thị
 */
void printGraph(struct Graph* graph, FILE* filename){ // In đồ thị ra file filename
    for(int vertex=0; vertex < graph->numVertices; ++vertex){   // Duyệt các đỉnh của đồ thị
        struct Node* temp = graph->head[vertex]; // Lấy node đầu tiên của đỉnh
        fprintf(filename,"\nVertex %d: ",vertex); // In đỉnh ra file filename
        while(temp){    // Duyệt các node của đỉnh 
            fprintf(filename,"%d ",temp->vertex); // In các node ra file filename
            temp = temp->next; // Lấy node tiếp theo
        }
    }
}

/**
 * @brief Hàm duyệt đồ thị theo chiều rộng sử dụng cấu trúc hàng đợi QUEUE và in ra file f 
 * 1. Khởi tạo mảng visited để lưu trữ các đỉnh đã được duyệt
 * 2. Khởi tạo hàng đợi QUEUE
 * 3. Thêm đỉnh đầu tiên vào QUEUE
 * 4. Duyệt QUEUE cho đến khi QUEUE rỗng
 *      4.1 Lấy đỉnh đầu tiên ra khỏi QUEUE
 *      4.2 Nếu đỉnh đó chưa được duyệt thì in ra file f và đánh dấu đã duyệt
 *      4.3 Thêm các đỉnh kề của đỉnh vừa lấy ra khỏi QUEUE vào QUEUE
 *      4.4 Lặp lại cho đến khi QUEUE rỗng
 * 
 * @param graph Đồ thị
 * @param startVertex Đỉnh bắt đầu
 * @param numVertices Số đỉnh của đồ thị
 * @param f File chứa các đỉnh đã được duyệt
 */
void BFS(struct Graph* graph, int starVertex, int numVertices, FILE* filename){
    int *visited;   // Mảng lưu trữ các đỉnh đã được duyệt
    visited = (int*)calloc(numVertices,sizeof(int)); // Khởi tạo mảng visited
    struct Queue* queue = createQueue(); // Khởi tạo hàng đợi QUEUE

    visited[starVertex] = 1;    // Đánh dấu đỉnh bắt đầu đã được duyệt
    enqueue(queue,starVertex);  // Thêm đỉnh bắt đầu vào QUEUE
    while(!queueEmpty(queue)){  // Duyệt QUEUE cho đến khi QUEUE rỗng
        int currentVertex = dequeue(queue);     // Lấy đỉnh đầu tiên ra khỏi QUEUE
        fprintf(filename,"%d\n",currentVertex); // In đỉnh ra file f
        struct Node* temp = graph->head[currentVertex];     // Lấy node đầu tiên của đỉnh
        while(temp){    // Duyệt các node của đỉnh
            int adjVertex = temp->vertex;   // Lấy đỉnh kề của đỉnh vừa lấy ra khỏi QUEUE
            if(visited[adjVertex] == 0){    // Nếu đỉnh kề chưa được duyệt thì thêm vào QUEUE
                visited[adjVertex] = 1;     // Đánh dấu đỉnh kề đã được duyệt
                enqueue(queue,adjVertex);   // Thêm đỉnh kề vào QUEUE
            }
            temp = temp->next; // Lấy node tiếp theo
        }
    }
    free(visited);  // Giải phóng mảng visited
    fclose(filename); // Đóng file filename
}

/**
 * @brief Hàm duyệt đồ thị theo chiều sâu sử dụng cấu trúc ngăn xếp STACK
 * 1. Khởi tạo mảng visited để lưu trữ các đỉnh đã được duyệt
 * 2. Khởi tạo ngăn xếp STACK
 * 3. Thêm đỉnh đầu tiên vào STACK
 * 4. Duyệt STACK cho đến khi STACK rỗng
 *      4.1 Lấy đỉnh đầu tiên ra khỏi STACK
 *      4.2 Nếu đỉnh đó chưa được duyệt thì in ra file f và đánh dấu đã duyệt
 *      4.3 Thêm các đỉnh kề của đỉnh vừa lấy ra khỏi STACK vào STACK
 *      4.4 Lặp lại cho đến khi STACK rỗng
 * 
 * @param graph Đồ thị
 * @param startVertex Đỉnh bắt đầu
 * @param numVertices Số đỉnh của đồ thị
 * @param filename File chứa các đỉnh đã được duyệt
 * 
 */
void DFS(struct Graph* graph, int startVertex, int numVertices, FILE* filename){
    int *visited;   // Mảng lưu trữ các đỉnh đã được duyệt
    visited = (int*)calloc(numVertices, sizeof(int)); // Khởi tạo mảng visited
    create(); // Khởi tạo ngăn xếp STACK

    push(startVertex);  // Thêm đỉnh bắt đầu vào STACK
    while(stackEmpty() == 0){   // Duyệt STACK cho đến khi STACK rỗng
        int currentVertex = pTop -> data;   // Lấy đỉnh đầu tiên ra khỏi STACK
        pop();
        if(visited[currentVertex] == 0){    // Nếu đỉnh đó chưa được duyệt thì in ra file f 
            fprintf(filename,"%d\n",currentVertex);
            visited[currentVertex] = 1;     // Đánh dấu đỉnh đã được duyệt
        }
        struct Node* temp = graph->rear[currentVertex];     // Lấy node cuối cùng của đỉnh
        while(temp){    // Duyệt các node của đỉnh
            int adjVertex = temp->vertex;   // Lấy đỉnh kề của đỉnh vừa lấy ra khỏi STACK
            if(visited[adjVertex] == 0){   // Nếu đỉnh kề chưa được duyệt thì thêm vào STACK
                push(adjVertex);    // Thêm đỉnh kề vào STACK
            }
            temp = temp->prev;  // Lấy node trước đó
        }
    }
    free(visited); // Giải phóng mảng visited
    fclose(filename);
}




/**
 * @brief Hàm xóa đỉnh khỏi đồ thị  
 * 1. Xóa các cạnh kề của đỉnh đó
 * 2. Xóa đỉnh đó
 * 
 * @param graph Đồ thị
 * @param vertex Đỉnh cần xóa
 * 
 */
void deleteVertex(struct Graph* graph, int vertex){     // Xóa đỉnh khỏi đồ thị
    struct Node* temp = graph -> head[vertex];  // Lấy node đầu tiên của đỉnh
    while(temp){    // Duyệt các node của đỉnh
        int currentVertex = temp->vertex;   // Lấy đỉnh kề của đỉnh đó
        struct Node* subVertex = graph -> head[currentVertex];   // Lấy node đầu tiên của đỉnh kề
        if(subVertex -> vertex == vertex){  // Nếu đỉnh kề đầu tiên của đỉnh kề là đỉnh cần xóa
            if (subVertex -> next){     // Nếu đỉnh kề đầu tiên của đỉnh kề có node tiếp theo
                graph -> head[currentVertex] -> vertex = subVertex -> next -> vertex;   // Gán giá trị của node tiếp theo cho node đầu tiên
                graph -> head[currentVertex] = subVertex -> next ;  // Gán node tiếp theo cho node đầu tiên
                free(subVertex);    // Giải phóng node đầu tiên
            }
            else{   // Nếu đỉnh kề đầu tiên của đỉnh kề không có node tiếp theo
                graph -> head[currentVertex] = NULL;    // Gán node đầu tiên bằng NULL
                free(subVertex);    // Giải phóng node đầu tiên
            }
            temp = temp -> next;    // Lấy node tiếp theo
            continue;   // Bỏ qua các câu lệnh phía dưới
        }

        while(subVertex -> next){   // Duyệt các node của đỉnh kề
            struct Node* nextVertex = subVertex -> next;    // Lấy node tiếp theo của đỉnh kề
            if(subVertex -> next -> next){  // Nếu node tiếp theo của đỉnh kề có node tiếp theo
                if(nextVertex -> vertex == vertex){     // Nếu node tiếp theo của đỉnh kề là đỉnh cần xóa
                    subVertex -> next -> vertex = nextVertex -> next -> vertex;     // Gán giá trị của node tiếp theo của node tiếp theo cho node tiếp theo
                    subVertex -> next = nextVertex -> next;     // Gán node tiếp theo của node tiếp theo cho node tiếp theo
                    free(nextVertex);   // Giải phóng node tiếp theo
                    break;  
                }
            }
            else{
                if(nextVertex -> vertex == vertex){     // Nếu node tiếp theo của đỉnh kề là đỉnh cần xóa
                    subVertex -> next = NULL;   // Gán node tiếp theo của đỉnh kề bằng NULL
                    free(nextVertex);   // Giải phóng node tiếp theo của đỉnh kề
                    break;
                }
            }
            subVertex = subVertex -> next;  // Lấy node tiếp theo của đỉnh kề
        }
        temp = temp -> next;    // Lấy node tiếp theo của đỉnh
    }
    graph -> head[vertex] = NULL;   // Gán node đầu tiên của đỉnh cần xóa bằng NULL
}

/**
 * @brief Hàm kiểm tra đỉnh bao phủ đồ thị
 * 1. Xóa các đỉnh đã được duyệt khỏi đồ thị
 * 2. Kiểm tra đồ thị còn đỉnh nào chưa được duyệt hay không
 *      2.1 Nếu còn thì đồ thị không bao phủ
 *      2.2 Nếu không còn thì đồ thị bao phủ
 * 
 * @param graph Đồ thị
 * @param filename File chứa các đỉnh cần kiểm tra
 */
int checkCover(struct Graph* graph, FILE* filename){    // Hàm kiểm tra đỉnh bao phủ đồ thị
    ignoreComments(filename);
    char c;
    int vertex;
    while((c = getc(filename)) != EOF){     // Duyệt các đỉnh trong file
        if( c == 'v') continue;     // Bỏ qua các đỉnh đã được duyệt
        else{   // Nếu đỉnh chưa được duyệt
            fscanf(filename,"%d",&vertex);  // Đọc giá trị của đỉnh
            deleteVertex(graph,vertex);     // Xóa đỉnh khỏi đồ thị
            c = getc(filename);             // Lấy ký tự tiếp theo
        }
    }
    fclose(filename);

    for(int i = 0; i < graph ->numVertices; ++i){  // Duyệt các đỉnh trong đồ thị
        if (graph -> head[i] != NULL)   // Nếu đỉnh chưa được duyệt
        return 0;       // Đồ thị không bao phủ
    }
    return 1;   // Đồ thị bao phủ
}
