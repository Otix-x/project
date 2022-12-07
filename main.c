#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "stack.h"

void main_thread();
void sub_menu(char filechoice[]);
void sub_main(char input_file[], FILE* f1, FILE* f2, FILE* f3, FILE* f4);
void buildGraph(struct Graph* graph, FILE* f);

// Menu chính của chương trình
void menu(){
    printf("\n\n======================= MENU PROGRAM ========================\n");
    printf("\t1. Road network of California\n");
    printf("\t2. Road network of Pennsylvania\n");
    printf("\t3. Road network of Texas\n");
    printf("\tPress other key to exit the program\n");
    printf("=============================================================\n");
}

// Menu lựa chọn thuật toán
void sub_menu(char filechoice[]){
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> SUB MENU <<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("-----------------------%s-----------------------\n",filechoice);
    printf("\t1. Breadth First Search\n");
    printf("\t2. Depth First Search\n");
    printf("\t3. Check Vertex Cover\n");
    printf("\t4. Print Graph\n");
    printf("\tPress other key to back to MAIN MENU\n\n\n");
}


int main(){

    main_thread();
    return 0;

}

void main_thread(){
    menu();
    while(1){
        printf("\tEnter your choice: ");
        int choice ;
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
                printf("Thank you for using our program\n\tGOODBYE!\n");
                exit(1);
                break;
            }
        }

    }
}

/**
 * @brief Hàm sub_main() thực hiện việc nạp dữ liệu từ file và thực hiện các chức năng chính
 * 
 * @param input_file File chứa dữ liệu đồ thị
 * @param f1 File outputBFS
 * @param f2 File outputDFS
 * @param f3 File VertexCover.vc
 * @param f4 File outputGraph
 */
void sub_main(char input_file[], FILE *f1, FILE *f2, FILE *f3, FILE *f4){
    FILE *input_graph = fopen(input_file, "r");
    if (input_graph == NULL){
        printf("Error: Cannot open file!\n");
        exit(1);
    }

    // create a graph
    printf("\tCreating graph...\n");
    int numVertices = countVertices(input_file);
    struct Graph* graph = createGraph(numVertices);
    buildGraph(graph, input_graph);
    printf("\tGraph created!\n");
    

    while(1){
        int choice, start;
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                // Breadth First Search
                printf("\n~~~~~~~~~~~~~~~BREADTH FIRST SEARCH~~~~~~~~~~~~~~~\n");
                printf("\tStart vertex: ");
                scanf("%d",&start);
                BFS(graph, start, numVertices, f1);
                printf("\tDONE!\n\tPlease open outputBFS file to show the result \n");
                sub_menu("------------------------------");
                break;
            }
            case 2:{
                // Depth First Search
                printf("\n~~~~~~~~~~~~~~~DEPTH FIRST SEARCH~~~~~~~~~~~~~~~\n");
                printf("\tStart vertex: ");
                scanf("%d",&start);
                DFS(graph, start, numVertices, f2);
                printf("\tDONE!\n\tPlease open outputDFS file to show the result \n");
                sub_menu("------------------------------");
                break;
            }
            case 3:{
                // Check Vertex Cover
                if (f3 == NULL){
                    printf("\nError: Unable to open the file");
                    exit(1);
                }
                printf("~~~~~~~~~~~~~~~CHECK VERTEX COVER~~~~~~~~~~~~~~~\n");
                FILE* temp_input_file = fopen(input_file, "r");
                struct Graph* temp_graph = createGraph(numVertices);
                buildGraph(temp_graph, temp_input_file);                
                if (checkCover(temp_graph, f3)){
                    printf("\tThe graph is a vertex cover\n");
                }
                else{
                    printf("\tThe graph is not a vertex cover\n");
                }
                sub_menu("------------------------------");
                free(temp_graph);

                break;
            }
                
            case 4:{
                // Print Graph
                printf("\tPrinting graph...\n");
                printGraph(graph, f4);
                printf("\tGraph printed!\n\tPlease open outputGraph file to show the result \n");
                sub_menu("------------------------------");
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