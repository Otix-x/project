#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

struct Node {
    int vertex;
    struct node *next;
    struct node *prev;
};

struct Graph {
    int numVertices;
    struct Node** head;
    struct Node** rear;
};

struct Node* createNode(int vertex);
struct Graph* createGraph(int numVertices);
void addEdge(struct Graph* graph,int src,int dest);
int countVertices(char *filename);
void buildGraph(struct Graph* graph,FILE *filename);
void printGraph(struct Graph* graph, FILE* f);
void BFS(struct Graph* graph,int startVertex, int numVertices, FILE* f);
void DFS(struct Graph* graph,int startVertex, int numVertices, FILE* f);
void deleteVertex(struct Graph* graph,int vertex);
void checkCover(struct Graph* graph, FILE* f);


#endif // GRAPH_H_INCLUDED