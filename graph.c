#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stack.h"
#include "queue.h"

// Hàm bỏ qua các dòng dữ liệu không cần thiết
int ignoreLine(FILE *f){
    int c;
    while(c = fgetc(f), c != '\n' && c != EOF);
    return c;
}

// Hàm bỏ qua các dòng comment
void ignoreComments(FILE *f){
    int c;
    while(c = fgetc(f), c == '#'){
        ignoreLine(f);
    }
    ungetc(c,f);
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
struct Node* creatNode(int vertex){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    newNode->prev = NULL;
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
struct Graph* createGraph(int numVertices){
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->head = (struct Node**)malloc(numVertices*sizeof(struct Node*));
    graph->rear = (struct Node**)malloc(numVertices*sizeof(struct Node*));
    for(int i=0;i<numVertices;i++){
        graph->head[i] = NULL;
        graph->rear[i] = NULL;
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
 
void addEdge(struct Graph* graph,int src,int dest){
    struct Node* newNode = creatNode(dest);
    if(graph->head[src]==NULL){
        graph->head[src] = newNode;
        graph->rear[src] = newNode;
    }
    else{
        newNode->prev = graph->rear[src];
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
int countVertices(char filename[]){
    FILE *f = fopen(filename,"r");
    ignoreComments(f);
    int numVertices;
    fscanf(f,"%d",&numVertices);
    int max = numVertices;
    for(;fscanf(f,"%d",&numVertices)!=EOF;){
        // Duyệt qua các cạnh của đồ thị để tìm đỉnh lớn nhất trong đồ thị để biết số đỉnh của đồ thị
        if(numVertices>max) max = numVertices;
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
 
void buildGraph(struct Graph* graph, FILE* f){
    ignoreComments(f);
    int src, dest;
    while(fscanf(f,"%d %d",&src,&dest)==2){
        addEdge(graph,src,dest);
        // addEdge(graph,dest,src);
    }
    fclose(f);
}

/**
 * @brief Hàm in đồ thị ra file f
 * 
 * @param graph Đồ thị
 * @param filename Tên file chứa đồ thị
 */
void printGraph(struct Graph* graph, FILE* filename){
    for(int vertex=0; vertex < graph->numVertices; ++vertex){
        struct Node* temp = graph->head[vertex];
        fprintf(filename,"\nV%d: ",vertex);
        while(temp){
            fprintf(filename,"%d ",temp->vertex);
            temp = temp->next;
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

void BFS(struct Graph* graph, int startVertex, int numVertices, FILE* filename){
    int *visited;
    visited = (int*)calloc(numVertices,sizeof(int));
    struct Queue* queue = createQueue();

    visited[startVertex] = 1;
    enqueue(queue,startVertex);
    while(!isEmpty(queue)){
        int currentVertex = dequeue(queue);
        fprintf(filename,"%d",currentVertex);
        struct Node* temp = graph->head[currentVertex];
        while(temp){
            int adjVertex = temp->vertex;
            if(!visited[adjVertex]){
                visited[adjVertex] = 1;
                enqueue(queue,adjVertex);
            }
            temp = temp->next;
        }
        free(visited);
        fclose(filename);
    }
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
    int *visited;
    visited = (int*)calloc(numVertices, sizeof(int));
    create();

    push(startVertex);
    while(isEmptyStack() == 0){
        int currentVertex = pTop -> data;
        pop();
        if(!visited[currentVertex]){
            visited[currentVertex] = 1;
            fprintf(filename,"%d",currentVertex);
        }
        struct Node* temp = graph->rear[currentVertex];
        while(temp){
            int adjVertex = temp->vertex;
            if(!visited[adjVertex]){
                push(adjVertex);
            }
            temp = temp->next;
        }
    }
    free(visited);
    fclose(filename);
}




/**
 * @brief Hàm xóa đỉnh khỏi đồ thị  
 * 
 * @param graph Đồ thị
 * @param vertex Đỉnh cần xóa
 * 
 */
void deleteVertex(struct Graph* graph, int vertex){
    struct Node* temp = graph -> head[vertex];
    while(temp){
        int currentVertex = temp->vertex;
        struct Node* subVertex = graph -> head[currentVertex];
        if(subVertex -> vertex == vertex){
            if (subVertex -> next){
                graph -> head[currentVertex] -> vertex = subVertex -> next -> vertex;
                graph -> head[currentVertex] = subVertex -> next ;
                free(subVertex);
            }
            else{
                graph -> head[currentVertex] = NULL;
                free(subVertex);
            }
            temp = temp -> next;
            continue;
        }

        while(subVertex -> next){
            struct Node* nextVertex = subVertex -> next;
            if(subVertex -> next -> next){
                if(nextVertex -> vertex == vertex){
                    subVertex -> next -> vertex = nextVertex -> next -> vertex;
                    subVertex -> next = nextVertex -> next;
                    free(nextVertex);
                    break;
                }
            }
            else{
                if(nextVertex -> vertex == vertex){
                    subVertex -> next = NULL;
                    free(nextVertex);
                    break;
                }
            }
            subVertex = subVertex -> next;
        }
        temp = temp -> next;
    }
    graph -> head[vertex] = NULL;
}

/**
 * @brief Hàm kiểm tra đỉnh bao phủ đồ thị
 * 
 * @param graph Đồ thị
 * @param filename File chứa các đỉnh cần kiểm tra
 */
int checkCover(struct Graph* graph, FILE* filename){
    ignoreComments(filename);
    char c;
    int vertex;
    while((c = getc(filename)) != EOF){
        if( c == 'v') continue;
        else{
            fscanf(filename,"%d",&vertex);
            deleteVertex(graph,vertex);
            c = getc(filename);
        }
    }
    fclose(filename);

    for(int i = 0; i < graph ->numVertices; ++i){
        if (graph -> head[i] != NULL) 
        return 0;
    }
    return 1;
}





