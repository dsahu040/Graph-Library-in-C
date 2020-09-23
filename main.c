
#include <stdio.h>
#include "graph.h"

int main(int argc, char *argv[]){
	Graph *graph = graph_initialize();
	int choice,v1,v2,wt,ch = 0;
	int *ptr;
	int i =0;
	int result;
	char fname[100];
	do{
		printf("\n Choose any of the following operations:");
		printf("\n 1. Add Vertex \n 2. Contains vertex \n 3. Remove vertex \n 4. Add edge \n 5. Contains edge \n 6. Remove Edge");
		printf("\n 7. Number of vertices \n 8. Number of edges \n 9. Total weight \n 10. Get degree \n 11. Get edge weight \n 12. Check neighbor");
		printf("\n 13. Get predecessors \n 14. Get successors \n 15. Load Graph \n 16. Check path \n 17. Save file \n 18. Graph Dot \n");
		printf("Your choice : ");
		scanf("%d",&choice);
		switch(choice){
			case 1: printf("Vertex to add : ");
				scanf("%d",&v1);
				result = graph_add_vertex(graph,v1);
				if(result == 0){
					printf("\nVertex %d added successfully",v1);
				}else{
					printf("\nError adding vertex %d",v1);
				}
				graph_print(graph);
				break;
			case 2: printf("Vertex to check : ");
				scanf("%d",&v1);
				result = graph_contains_vertex(graph,v1);
				if(result == 1){
					printf("\nThe graph contains vertex %d",v1);
				}else{
					printf("\nNo vertex %d found!",v1);
				}
				graph_print(graph);
				break;	
			case 3: printf("Vertex to remove : ");
				scanf("%d",&v1);
				result = graph_remove_vertex(graph,v1);
				if(result == 0){
					printf("\nVertex %d removed successfully",v1);
				}else{
					printf("\nError in removing vertex %d",v1);
				}
				graph_print(graph);
				break;
			case 4: printf("Edge to add between which to vertices and the wt: ");
				scanf("%d %d %d",&v1,&v2,&wt);
				result = graph_add_edge(graph,v1,v2,wt);
				if(result == 0){
					printf("\nEdge added between %d and %d successfully",v1,v2);
				}else{
					printf("\nError in adding edge between %d and %d",v1,v2);
				}
				graph_print(graph);
				break;
			case 5: printf("Edge to be checked between which vertices : ");
				scanf("%d %d",&v1,&v2);
				result = graph_contains_edge(graph,v1,v2);
				if(result == 1){
					printf("\nEdge between %d and %d exists",v1,v2);
				}else{
					printf("\nEdge between %d and %d does not exist",v1,v2);
				}
				graph_print(graph);
				break;
			case 6: printf("Edge to be removed between which vertices : ");
				scanf("%d %d",&v1,&v2);
				result = graph_remove_edge(graph,v1,v2);
				if(result == 0){
					printf("\nEdge between %d and %d removed successfully",v1,v2);
				}else{
					printf("\nError in removing edge between %d and %d",v1,v2);
				}
				graph_print(graph);
				break;
			case 7: result = graph_num_vertices(graph);
				if(result == -1){
					printf("\nError in counting number of vertices");
				}else{
					printf("\nTotal number of vertices : %d",result);
				}
				graph_print(graph);
				break;
			case 8: result = graph_num_edges(graph);
				if(result == -1){
					printf("\nError in counting number of vertices");
				}else{
					printf("\nTotal number of edges : %d",result);
				}
				graph_print(graph);
				break;
			case 9: result = graph_total_weight(graph);
				if(result == -1){
					printf("\nError in calculating the weight of the graph");
				}else{
					printf("\nTotal weight of graph : %d",result);
				}
				graph_print(graph);				
				break;
			case 10:  printf("Get degree of which edge : ");
				scanf("%d",&v1);
				result = graph_get_degree(graph, v1);
				if(result == -1){
					printf("\nError in calculating the degree of vertex %d : \n", v1);
				}else{
					printf("\nTotal degree of vertex %d is : %d\n",v1,result);
				}
				graph_print(graph);				
				break;
			case 11:  printf("Edge weight between which vertices : ");
				scanf("%d %d",&v1,&v2);
				result = graph_get_edge_weight(graph, v1, v2);
				if(result == -1){
					printf("\nError in calculating the weight of the edge between %d to %d",v1,v2);
				}else{
					printf("\nWeight of the edge from %d to %d : %d",v1,v2,result);
				}
				graph_print(graph);				
				break;
			case 12:  printf("Check if two vertices are neighbors : ");
				scanf("%d %d",&v1,&v2);
				result = graph_is_neighbor(graph, v1, v2);
				if(result == 0){
					printf("\nNo edge between %d and %d",v1,v2);
				}else if(result == 1){
					printf("\n%d and %d are neighbors",v1,v2);
				}else{
					printf("\nError in finding neighbors");
				}
				graph_print(graph);				
				break;
			case 13:  printf("Enter the vertex : ");
				scanf("%d",&v1); 
				ptr = graph_get_predecessors(graph, v1);
				if(ptr == NULL){
					printf("\nError in getting predecessors");
				}else{
					printf("\nPredecessors of vertex %d are :",v1);
					i = 0;
					while(ptr[i] != -1){
						printf("\t %d",ptr[i]);
						i++;
					}
				}
				graph_print(graph);				
				break;
			case 14: printf("Enter the vertex : ");
				scanf("%d",&v1);
				ptr = graph_get_successors(graph, v1);
				if(ptr == NULL){
					printf("\nError in getting successors");
				}else{
					printf("\nSuccessors of vertex %d are :",v1);
					i = 0;
					while(ptr[i] != -1){
						printf("\t %d",ptr[i]);
						i++;
					}
				}
				graph_print(graph);				
				break;	
			case 15: printf("Enter the filename : ");
				scanf("%s",fname);
				result = graph_load_file(graph, fname);
				if(result == 0){
					printf("\n File loaded successfully \n");
				}else{
					printf("\n Error in loading file \n");
				}
				graph_print(graph);				
				break;	
			case 16: printf("Check if there is path between two vertices : ");
				scanf("%d %d",&v1,&v2);
				result = graph_has_path(graph, v1, v2);
				if(result == 0){
					printf("\nNo path between %d and %d\n",v1,v2);
				}else if(result == 1){
					printf("\n There is a path between %d and %d\n",v1,v2);
				}else{
					printf("\nError in finding neighbors");
				}
				graph_print(graph);	
				break;
			case 17: printf("Enter the filename to be created : ");
				scanf("%s",fname);
				result = graph_save_file(graph, fname);
				if(result == 0){
					printf("\n File saved successfully \n");
				}else{
					printf("\n Error in saving file \n");
				}
				break;
			case 18: printf("Enter the DOT filename to be created : ");
				scanf("%s",fname);
				graph_output_dot(graph, fname);
				break;
			default: printf("Invalid choice");
				break;
		}
		printf("\n Do you want to continue? (1/0): ");
		scanf("%d",&ch);		
	}while(ch == 1);
	return 0;
}