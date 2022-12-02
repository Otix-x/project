#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"

void sub_menu(char filechoice[]);
void sub_main(char input_file[], FILE* f1, FILE* f2, FILE* f3, FILE* f4);
void main_thread();

// Menu chính của chương trình
void menu(){
    printf("\n\n======================= MENU PROGRAM =======================\n");
    printf("1. Road network of California\n");
    printf("2. Road network of Pennsylvania\n");
    printf("3. Road network of Texas\n");
    printf("Press other key to exit the program\n");
    printf("=============================================================\n");
}

// Menu lựa chọn thuật toán
void sub_menu(char filechoice[]){
    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> SUB MENU <<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("----------------------- %s -----------------------\n",filechoice);
    printf("1. Breadth First Search\n");
    printf("2. Depth First Search\n");
    printf("3. Check Vertex Cover\n");
    printf("4. Print Graph\n");
    printf("Press other key to back to MAIN MENU\n");
}


int main(){

    main_thread();
    return 0;

}

// 
/**
 * @brief Hàm sub_main() thực hiện việc nạp dữ liệu từ file và thực hiện các chức năng chính
 * 
 * @param input_file File chứa dữ liệu đồ thị
 * @param f1 File outputBFS
 * @param f2 File outputDFS
 * @param f3 File outputVertexCover
 * @param f4 File outputGraph
 */
void sub_main(char input_file[], FILE *f1, FILE *f2, FILE *f3, FILE *f4){
   

    FILE *input_graph = fopen(input_file, "r");
    if (input_graph == NULL){
        printf("Error: Cannot open file!\n");
        exit(1);
    }

    // create a graph
    printf("Creating graph...\n");
    int numVertices = countVertices(input_file);
    struct Graph* graph = createGraph(numVertices);
    buildGraph(graph, input_graph);
    printf("Graph created!\n");


    while(1){
        int choice, start;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("Enter start vertex: ");
        scanf("%d", &start);
        switch(choice){
            case 1:{
                // Breadth First Search
                printf("Breadth First Search\n");
                printf("Start vertex: %d\n", start);
                BFS(graph, start, numVertices, f1);
                printf("BFS done!\n");
                break;
            }
            case 2:{
                // Depth First Search
                printf("Depth First Search\n");
                printf("Start vertex: %d\n", start);
                DFS(graph, start, numVertices, f2);
                printf("DFS done!\n");
                break;
            }
            case 3:
                // Check Vertex Cover
                break;
            case 4:{
                // Print Graph
                printf("Printing graph...\n");
                printGraph(graph, f4);
                printf("Graph printed!\n");
                break;
            }
            default:
                printf("Back to MAIN MENU\n");
                main_thread();
                break;
        }
    }
    free(graph);
}

void main_thread(){
    menu();
    while(1){
        printf("Enter your choice: ");
        int choice =0;
        scanf("%d", &choice);
        switch(choice){
            case 1: {
                // Road network of California
                char input_file[] = "roadNet-CA.txt";
                FILE *f1 = fopen("outputBFS.txt", "w");
                FILE *f2 = fopen("outputDFS.txt", "w");
                FILE *f3 = fopen("roadNet-CA.vc", "r");
                FILE *f4 = fopen("outputGraph.txt", "w");
                sub_menu("Road network of California");
                sub_main(input_file, f1, f2, f3, f4);
            } break;
            case 2: {
                // Road network of Pennsylvania
                char input_file[] = "roadNet-PA.txt";
                FILE *f1 = fopen("outputBFS.txt", "w");
                FILE *f2 = fopen("outputDFS.txt", "w");
                FILE *f3 = fopen("roadNet-PA.vc", "r");
                FILE *f4 = fopen("outputGraph.txt", "w");
                sub_menu("Road network of Pennsylvania");
                sub_main(input_file, f1, f2, f3, f4);
            } break;
            case 3: {
                // Road network of Texas
                char input_file[] = "roadNet-TX.txt";
                FILE *f1 = fopen("outputBFS.txt", "w");
                FILE *f2 = fopen("outputDFS.txt", "w");
                FILE *f3 = fopen("roadNet-TX.vc", "r");
                FILE *f4 = fopen("outputGraph.txt", "w");
                sub_menu("Road network of Texas");
                sub_main(input_file, f1, f2, f3, f4);
            } break;
            default: {
                printf("Thank you for using our program. Goodbye!\n");
                exit(1);
                break;
            }
        }

    }
}

