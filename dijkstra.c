#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#define INFINITY 9999
#define MAX 10

void dijkstra_alg(int *graph,int n,int start);

int main()
{
	int *array=(int*)malloc(MAX*MAX*sizeof(int));
	
	FILE *file;

	file=fopen("matrix.txt", "r");
	int i,j,n,u;
	printf("Enter number of vertices:");
	scanf("%d",&n);
	if(n>10)
	{
		printf("Overflow. Try again\n");
		return 0;
		
	}
	//iterate the graph using the adjecensy matrix from the given file
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if (!fscanf(file, "%i", & *(array+i*n+j)))
				break;
			printf("%i ",*(array+i*n+j)); 
		}
		printf("\n");
	}
	fclose(file);
	printf("\nEnter the starting node:");
	scanf("%d",&u);
	dijkstra_alg(array,n,u);
    printf("\n");
    free(array);
	system("pause");
	return 0;
}

void dijkstra_alg(int *graph,int n,int start)
//the function uses pointer to an array alongside the graph's nodes and the strating node 
{
	int cost[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,min_distance,next,i,j;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			//check for existing edge
			if( *(graph+i*n+j)==0)
				cost[i][j]=INFINITY;// none found
			else
				cost[i][j]= *(graph+i*n+j);// found edge 
		}
	}			
	
	// iterate the graph starting from the start node
	for(i=0;i<n;i++)
	{
		distance[i]=cost[start][i];
		pred[i]=start;
		visited[i]=0;
	}

	distance[start]=0;
	visited[start]=1;
	count=1;
	
	// go to the next node
	while(count<n-1)
	{
		min_distance=INFINITY;

		for(i=0;i<n;i++)
			if(distance[i]<min_distance&&!visited[i])
			{
				min_distance=distance[i];
				next=i;
			}

			visited[next]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(min_distance+cost[next][i]<distance[i])
					{
						distance[i]=min_distance+cost[next][i];
						pred[i]=next;
					}
		count++;
	}

	//save the result in a text file
	FILE *file;
	file=fopen("result.txt", "w");
	for(i=0;i<n;i++)
		if(i!=start)
		{
			fprintf(file, "\nDistance from node %d to node %d = %d", start, i, distance[i]);
			fprintf(file, "\nPath: %d",i);

			j=i;
			//show the nodes, which were used to get to another node
			do
			{
				j=pred[j];
				fprintf(file, "<-%d",j);
			}while(j!=start);
			fprintf(file, "\n");
	}
	fclose(file);
	printf("Success!Result is saved in result.txt\n");
}




