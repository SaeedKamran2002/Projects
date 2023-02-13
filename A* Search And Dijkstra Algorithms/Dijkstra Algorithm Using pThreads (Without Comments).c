#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>

#define VERTICES (20000)          
#define MIN_EDGES_VERTEX (25)     
#define MAX_DIST (1000)           
#define INF_DIST (10000000)      
#define ZERO (0)                  
#define NTHREADS (40000)

float* Graph ;
float* Node_Shortest_Dist_1 ;
float* Node_Shortest_Dist_2 ;
int* Parent_Node ;
int* Edges_Per_Vertex ;
int* Completed_Node ;

int32_t current_node_1;
int32_t current_node_2;



struct timeval initial, final;


void Initialize_Array(int* Input_Array,int Value);

void Initialize_Dist_Array(float* Input_Array,float Value);

void Initialize_Graph(float* Graph,float Value);

void Set_Graph_Dist_Random(float* Graph, int* Edges_Per_Vertex);

int32_t Shortest_Distance_Node(float* Node_Shortest_Dist, uint32_t* Completed_Node);

void Shortest_Path_Computation_Serial(float* Graph, float* Node_Shortest_Dist, uint32_t* Parent_Node, uint32_t* Completed_Node, uint32_t Source);

double timetaken();

void Shortest_Path_Computation_Parallel(float* Graph, float* Node_Shortest_Dist, uint32_t* Parent_Node, uint32_t* Completed_Node, uint32_t Source);

void* new_loop(void* j);

int main(){
    printf("\nRunning Dijkstra Algorithm by PThreads\n");
    printf("\nVertices: %d\n", VERTICES);
    srand(8421);

    uint32_t Integer_Array = VERTICES * sizeof(int);
    uint32_t Float_Array = VERTICES * sizeof(float);
    uint64_t Size_Graph = VERTICES * VERTICES * sizeof(float);

    Graph = (float*)malloc(Size_Graph);
    Node_Shortest_Dist_1 = (float*)malloc(Float_Array);
    Node_Shortest_Dist_2 = (float*)malloc(Float_Array);
    Parent_Node = (int*)malloc(Integer_Array);
    Edges_Per_Vertex = (int*)malloc(Integer_Array);
    Completed_Node = (int*)malloc(Integer_Array);

    Initialize_Graph(Graph,(float)0);

    Initialize_Array(Edges_Per_Vertex,(int)0);

    Set_Graph_Dist_Random(Graph,Edges_Per_Vertex);

    free(Edges_Per_Vertex);

    uint32_t src=(rand()%VERTICES);

    gettimeofday(&initial,NULL);
    
    
    Shortest_Path_Computation_Serial(Graph,Node_Shortest_Dist_1,Parent_Node,Completed_Node,src);


    gettimeofday(&final,NULL);
    double diff=0;

    diff=timetaken();

    printf("Time taken for logic computation by CPU in seconds is %f\n",diff);
    
    gettimeofday(&initial,NULL);
    
    Shortest_Path_Computation_Parallel(Graph,Node_Shortest_Dist_2,Parent_Node,Completed_Node,src);

    gettimeofday(&final,NULL);
    double diff1=0;

    diff1=timetaken();

    printf("Time taken for logic computation by pthreads in seconds is %f\n",diff1);
 
    uint32_t k=0;
    uint32_t match=0;
    printf("That Much Faster = %f",diff - diff1);
   
    	
    free(Graph);
    free(Node_Shortest_Dist_1);
    free(Node_Shortest_Dist_2);
    free(Parent_Node);
    free(Completed_Node);
	
}

void Initialize_Graph(float* Graph,float Value){
    uint32_t i,j;
    for(i=0;i<VERTICES;i++){
        for(j=0;j<VERTICES;j++){
            Graph[i*VERTICES + j] = Value;
        }
    }
}

void Initialize_Array(int* Input_Array,int Value){
    uint32_t i;
    for(i=0;i<VERTICES;i++){
        Input_Array[i]=Value;
    }
}

void Initialize_Dist_Array(float* Input_Array,float Value){
    uint32_t i;
    for(i=0;i<VERTICES;i++){
        Input_Array[i]=Value;
    }
}

void Set_Graph_Dist_Random(float* Graph, int* Edges_Per_Vertex){
    uint32_t i,Current_Edges,Random_Vertex;
    float Random_Dist;

    for(i=1;i<VERTICES;i++){
        Random_Vertex = (rand() % i);
        Random_Dist =(rand() % MAX_DIST) + 1;
        Graph[Random_Vertex*VERTICES + i] = Random_Dist;
        Graph[Random_Vertex + i*VERTICES] = Random_Dist;
        Edges_Per_Vertex[i] += 1;
        Edges_Per_Vertex[Random_Vertex] += 1;
    }

    for(i=0;i<VERTICES;i++){
        Current_Edges = Edges_Per_Vertex[i];
        while(Current_Edges < MIN_EDGES_VERTEX){
            Random_Vertex = (rand() % VERTICES);
            Random_Dist = (rand() % MAX_DIST) + 1;
            if((Random_Vertex != i)&&(Graph[Random_Vertex + i*VERTICES] == 0)){
                Graph[Random_Vertex + i*VERTICES] = Random_Dist;
                Graph[Random_Vertex*VERTICES + i] = Random_Dist;
                Edges_Per_Vertex[i] += 1;
                Current_Edges += 1;
            }
        }
    }
}

void Shortest_Path_Computation_Serial(float* Graph, float* Node_Shortest_Dist, uint32_t* Parent_Node, uint32_t* Completed_Node, uint32_t Source){

    Initialize_Array(Parent_Node,(int)-1);

    Initialize_Array(Completed_Node,(int)0);

    Initialize_Dist_Array(Node_Shortest_Dist,INF_DIST);

    Node_Shortest_Dist[Source]=0;
    uint32_t i,j;
    for(i=0;i<VERTICES;i++){

        current_node_1=Shortest_Distance_Node(Node_Shortest_Dist,Completed_Node);
        Completed_Node[current_node_1]=1;
        for(j=0;j<VERTICES;j++){
            uint32_t new_distance=Node_Shortest_Dist[current_node_1] + Graph[current_node_1*VERTICES + j];
            if ((Completed_Node[j] != 1) && (Graph[current_node_1*VERTICES + j] != (float)(0)) && (new_distance < Node_Shortest_Dist[j])){
                Node_Shortest_Dist[j] = new_distance;
                Parent_Node[j] = current_node_1;
            }
        }
    }
}

void Shortest_Path_Computation_Parallel(float* Graph, float* Node_Shortest_Dist, uint32_t* Parent_Node, uint32_t* Completed_Node, uint32_t Source){
    
    Initialize_Array(Parent_Node,(int)-1);

    Initialize_Array(Completed_Node,(int)0);

    Initialize_Dist_Array(Node_Shortest_Dist,INF_DIST);
    
    Node_Shortest_Dist[Source]=0;

    uint32_t i,j,l;
    for (i = 0; i < VERTICES; i++) {

        current_node_2 = Shortest_Distance_Node(Node_Shortest_Dist,Completed_Node);
        Completed_Node[current_node_2]=1;
        pthread_t threads[NTHREADS];
	pthread_attr_t attr;
	int rc;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

            
        for (j = 0; j < VERTICES/NTHREADS; j++) {
	    rc=pthread_create(&threads[j],&attr,(void*)new_loop,(void*) j);         
        }
		
	for(l=0; l < VERTICES/NTHREADS; l++){
	    pthread_join(threads[l],NULL);		
	}
    
        pthread_attr_destroy(&attr);
		
    }
}


void* new_loop(void* j){
	int k =((int) j)*NTHREADS;
	int tid;
	int new_distance;
	for(tid=k;tid<(k+NTHREADS);tid++){

	
    new_distance = Node_Shortest_Dist_2[current_node_2] + Graph[current_node_2*VERTICES + tid];
    if ((Completed_Node[tid] != 1) && (Graph[current_node_2*VERTICES + tid] != (float)(0)) && (new_distance < Node_Shortest_Dist_2[tid])){ //each thread will have different j & new_distance
    	Node_Shortest_Dist_2[tid] = new_distance;
        Parent_Node[tid] = current_node_2;
    }
	}
	pthread_exit(NULL);


}

int32_t Shortest_Distance_Node(float* Node_Shortest_Dist, uint32_t* Completed_Node){
    uint32_t node_distance=INF_DIST;
    int32_t node=-1;
    uint32_t i;
    for(i=0;i<VERTICES;i++){
        if((Node_Shortest_Dist[i]<node_distance) && (Completed_Node[i]==0)){
            node_distance=Node_Shortest_Dist[i];
            node=i;
        }
    }
    return node;
}

double timetaken(){
    double initial_s,final_s;
    double diff_s;
    initial_s= (double)initial.tv_sec*1000000 + (double)initial.tv_usec;
    final_s= (double)final.tv_sec*1000000 + (double)final.tv_usec;
    diff_s=(final_s-initial_s)/1000000;
    return diff_s;
    }

