#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_VERTICES 10
#define INF 100
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES];
int distance[MAX_VERTICES];

int choose(int distance[], int size, int visited[]) {
	int min = INT_MAX;
	int minpos = -1;
	for (int i = 0; i < size; i++) {
		if (!visited[i] && distance[i] < min) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print(int size) {
	static int step = 1;
	printf("STEP %d: distance: ", step++);

	for (int i = 0; i < size; i++) {
		if (distance[i] == INF) {
			printf(" * ");
		}
		else {
			printf("%2d ", distance[i]);
		}
	}
	printf("\n");
	printf(" found : ");
	for (int i = 0; i < size; i++) {
		printf("%2d", visited[i]);
	}
	printf("\n\n");
}

void dijkstra(GraphType* g, int start) {
	int u;
	for (int i = 0; i < g->n; i++) { // �Ÿ��� �ʱ�ȭ
		distance[i] = g->weight[start][i];
		visited[i] = FALSE;
	}
	visited[start] = TRUE;
	distance[start] = 0; 
	for (int i = 0; i < g->n - 1; i++) { // ó���� distance�� visited�� �Ѱ� true�� ���������ϱ� �������� 6���� ���� �˴ϴ�.
		print(g->n);
		u = choose(distance, g->n, visited);
		visited[u] = TRUE;
		for (int w = 0; w < g->n; w++) {
			if (!visited[w]) {
				if (distance[w] > distance[u] + g->weight[u][w]) {
					distance[w] = distance[u] + g->weight[u][w];
				}
			}
		}
	}
}

int main() {
	GraphType g = { 7,
	{{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{INF,4,0,2,INF,INF,INF},
	{INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{INF,INF,INF,4,5,INF,0}}
	};

	dijkstra(&g, 0);
}